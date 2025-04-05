//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//

#include "cbase.h"
#include "basescripted.h"

#ifdef CLIENT_DLL
#include "lc_baseanimating.h"
#else
#include "lbaseanimating.h"
#endif
#include "lbaseentity_shared.h"
#include "lvphysics_interface.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//#include "tier1/checksum_crc.h" // For CRC32_t

#define SCRIPTED_ENTITY_SAVE_VERSION 1

enum ScriptedEntitySaveFlags_t {
	SESF_HAS_LUA_TABLE = (1 << 0),
};

struct ScriptedSaveHeader_t
{
    ScriptedSaveHeader_t()
		: version(SESF_HAS_LUA_TABLE),
		flags(0),
        luaTablePairCount(0)
	{
	}

	short version;
	unsigned flags;
	unsigned luaTablePairCount;
	

	DECLARE_SIMPLE_DATADESC();
};

BEGIN_SIMPLE_DATADESC(ScriptedSaveHeader_t)
DEFINE_FIELD(version, FIELD_SHORT),
DEFINE_FIELD(flags, FIELD_INTEGER),
DEFINE_FIELD(luaTablePairCount, FIELD_INTEGER),
END_DATADESC()

IMPLEMENT_NETWORKCLASS_ALIASED( BaseScripted, DT_BaseScripted )

BEGIN_NETWORK_TABLE( CBaseScripted, DT_BaseScripted )
#ifdef CLIENT_DLL
	RecvPropString( RECVINFO( m_iScriptedClassname ) ),
#else
	SendPropString( SENDINFO( m_iScriptedClassname ) ),
#endif
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA(	CBaseScripted )
END_PREDICTION_DATA()

#ifdef GAME_DLL
BEGIN_DATADESC(CBaseScripted)
END_DATADESC()
#endif

#ifdef CLIENT_DLL
static C_BaseEntity *CCBaseScriptedFactory( void )
{
	return static_cast< C_BaseEntity * >( new CBaseScripted );
};
#endif

#ifndef CLIENT_DLL
static CUtlDict< CEntityFactory<CBaseScripted>*, unsigned short > m_EntityFactoryDatabase;
#endif

void RegisterScriptedEntity( const char *className )
{
#ifdef CLIENT_DLL
	if ( GetClassMap().FindFactory( className ) )
	{
		return;
	}

	GetClassMap().Add( className, "CBaseScripted", sizeof( CBaseScripted ),
		&CCBaseScriptedFactory, true );
#else
	if ( EntityFactoryDictionary()->FindFactory( className ) )
	{
		return;
	}

	unsigned short lookup = m_EntityFactoryDatabase.Find( className );
	if ( lookup != m_EntityFactoryDatabase.InvalidIndex() )
	{
		return;
	}

	CEntityFactory<CBaseScripted> *pFactory = new CEntityFactory<CBaseScripted>( className );

	lookup = m_EntityFactoryDatabase.Insert( className, pFactory );
	Assert( lookup != m_EntityFactoryDatabase.InvalidIndex() );
#endif
}

void ResetEntityFactoryDatabase( void )
{
#ifdef CLIENT_DLL
#ifdef LUA_SDK
	GetClassMap().RemoveAllScripted();
#endif
#else
	for ( int i=m_EntityFactoryDatabase.First(); i != m_EntityFactoryDatabase.InvalidIndex(); i=m_EntityFactoryDatabase.Next( i ) )
	{
		delete m_EntityFactoryDatabase[ i ];
	}
	m_EntityFactoryDatabase.RemoveAll();
#endif
}

CBaseScripted::CBaseScripted( void )
{
#ifdef LUA_SDK
	// UNDONE: We're done in CBaseEntity
	m_nTableReference = LUA_NOREF;
#endif
}

CBaseScripted::~CBaseScripted( void )
{
	// Andrew; This is actually done in CBaseEntity. I'm doing it here because
	// this is the class that initialized the reference.
#ifdef LUA_SDK
	lua_unref( L, m_nTableReference );
#endif
}
#ifdef GAME_DLL
void CBaseScripted::OnSave(IEntitySaveUtils* pUtils)
{
    //TODO: find some way to save think and touch correctly? This is just dumb but it prevents complaining and crashing.
	SetThink(NULL);
	SetTouch(NULL);
	BaseClass::OnSave(pUtils);
}


#endif

// Assuming SESF_HAS_LUA_TABLE is defined in a header, e.g.:
// #define SESF_HAS_LUA_TABLE 0x01

void CBaseScripted::SaveEntity(ISave& save, CBaseEntity* entity) {
    if (!L) {
        printf("SaveEntity: Lua state is null\n");
        return;
    }

    ScriptedSaveHeader_t saveHeader;

    saveHeader.version = 1; // Version number for future compatibility

    // Call Lua "Save" function to determine if there's a table
    lua_pushentity(L, entity);           // stack: [entity]
    lua_getfield(L, -1, "Save");         // stack: [entity, entity.Save]
    if (lua_isfunction(L, -1)) {
        lua_pushvalue(L, -2);            // stack: [entity, entity.Save, entity]
        if (lua_pcall(L, 1, 1, 0) == 0 && lua_istable(L, -1)) {
            saveHeader.flags |= SESF_HAS_LUA_TABLE; // Table is present

            // Debug: Check stack size and type at -1
            int top = lua_gettop(L);
            DevWarning("Stack size: %d, Type at -1: %s\n", top, lua_typename(L, lua_type(L, -1)));

            int pairCount = GetSupportedPairCount(L, -1);
            saveHeader.luaTablePairCount = pairCount;
        }
        else {
            lua_pop(L, 1);               // Pop non-table result
        }
    }
    else {
        lua_pop(L, 1);                   // Pop non-function
    }

  

    if (!save.WriteFields("scripteddata", &saveHeader, NULL, saveHeader.m_DataMap.dataDesc, saveHeader.m_DataMap.dataNumFields))
        return;

    // Write version and flags
   

    if (saveHeader.flags & SESF_HAS_LUA_TABLE) {
        // Table is on the stack from the Lua call
     
        SaveTable(L, save);

        lua_pop(L, 1);                   // Pop the table
    }
    lua_pop(L, 1);                       // Pop the entity
}

void CBaseScripted::RestoreEntity(IRestore& restore, CBaseEntity* entity) {
    if (!L) {
        printf("RestoreEntity: Lua state is null\n");
        return;
    }

    InitScriptedEntity(); // Initialize Lua state since Spawn isn’t called yet

    ScriptedSaveHeader_t saveHeader;

    if (!restore.ReadFields("scripteddata", &saveHeader, NULL, saveHeader.m_DataMap.dataDesc, saveHeader.m_DataMap.dataNumFields))
        return;

    //DevWarning("RestoreEntity: Version= %d, Flags= 0x%x, luaTablePairCount= %d\n", saveHeader.version, saveHeader.flags, saveHeader.luaTablePairCount);

    if (saveHeader.flags & SESF_HAS_LUA_TABLE) {

        lua_pushentity(L, entity);       // stack: [entity]
        lua_newtable(L);                 // stack: [entity, table]
        RestoreTable(L, restore);
       

       
        // Call Lua "Restore" function
        lua_getfield(L, -2, "Restore");  // stack: [entity, table, entity.Restore]
        if (lua_isfunction(L, -1)) {
            lua_pushvalue(L, -3);        // stack: [entity, table, entity.Restore, entity]
            lua_pushvalue(L, -3);        // stack: [entity, table, entity.Restore, entity, table]
            //printf("RestoreEntity: Calling Lua Restore\n");
            if (lua_pcall(L, 2, 0, 0) != 0) {
                DevWarning("RestoreEntity: Lua error: %s\n", lua_tostring(L, -1));
                lua_pop(L, 1);
            }
        }
        else {
            lua_pop(L, 1);               // Pop non-function
        }
        lua_pop(L, 2);                   // Pop entity and table
    }
}

int CBaseScripted::Save(ISave& save) {
    SaveEntity(save, this);
    int status = BaseClass::Save(save);
    if (!status) return 0;
    return status;
}

int CBaseScripted::Restore(IRestore& restore) {
    RestoreEntity(restore, this);
    int status = BaseClass::Restore(restore);
    if (!status) return 0;
    return status;
}

int CBaseScripted::GetSupportedPairCount(lua_State* L, int tableIndex) {
    // Validate Lua state and stack
    if (!L || lua_gettop(L) < 1 || tableIndex == 0) {
        DevWarning("Invalid Lua state or tableIndex: %d, Stack size: %d\n", tableIndex, lua_gettop(L));
        return 0;
    }

    // Convert tableIndex to absolute index
    int absIndex = tableIndex > 0 ? tableIndex : lua_gettop(L) + tableIndex + 1;

    // Ensure the value at absIndex is a table
    if (!lua_istable(L, absIndex)) {
        //DevLog("Value at index %d is not a table, type: %s\n", absIndex, lua_typename(L, lua_type(L, absIndex)));
        return 0;
    }

    int count = 0;
    lua_pushnil(L); // stack: [..., table, nil]
    while (lua_next(L, absIndex)) { // stack: [..., table, key, value]
        int key_type = lua_type(L, -2);
        int value_type = lua_type(L, -1);
        if ((key_type == LUA_TSTRING || key_type == LUA_TNUMBER) &&
            (value_type == LUA_TNUMBER || value_type == LUA_TSTRING ||
                value_type == LUA_TBOOLEAN || value_type == LUA_TTABLE)) {
            count++;
        }
        lua_pop(L, 1); // Pop value; stack: [..., table, key]
    }
    return count;
}

void CBaseScripted::SaveTable(lua_State* L, ISave& save) {
    // Ensure the table is at the top of the stack
    if (!lua_istable(L, -1)) {
        DevWarning("SaveTable: Expected table at -1, got %s\n", lua_typename(L, lua_type(L, -1)));
        return;
    }

    // Count supported key-value pairs
    int count = GetSupportedPairCount(L, -1);
    save.WriteInt(&count);

    // Save supported pairs
    lua_pushnil(L); // stack: [table, nil]
    while (lua_next(L, -2)) { // stack: [table, key, value]
        int key_type = lua_type(L, -2);
        int value_type = lua_type(L, -1);
        if ((key_type == LUA_TSTRING || key_type == LUA_TNUMBER) &&
            (value_type == LUA_TNUMBER || value_type == LUA_TSTRING ||
                value_type == LUA_TBOOLEAN || value_type == LUA_TTABLE)) {
            // Save key
            save.WriteInt(&key_type);
            if (key_type == LUA_TSTRING) {
                const char* key = lua_tostring(L, -2);
                int len = strlen(key) + 1;
                save.WriteInt(&len);
                save.WriteString(key);
            }
            else { // LUA_TNUMBER
                float key_num = (float)lua_tonumber(L, -2);
                save.WriteFloat(&key_num);
            }

            // Save value
            save.WriteInt(&value_type);
            switch (value_type) {
            case LUA_TNUMBER: {
                float num = (float)lua_tonumber(L, -1);
                save.WriteFloat(&num);
                break;
            }
            case LUA_TSTRING: {
                const char* str = lua_tostring(L, -1);
                int len = strlen(str) + 1;
                save.WriteInt(&len);
                save.WriteString(str);
                break;
            }
            case LUA_TBOOLEAN: {
                int bool_val = lua_toboolean(L, -1);
                save.WriteInt(&bool_val);
                break;
            }
            case LUA_TTABLE: {
                // Save the current stack size to restore later
                int top = lua_gettop(L); // Should be 3: [table, key, value]
                // Push the nested table to the top
                lua_pushvalue(L, -1); // stack: [table, key, value, value]
                SaveTable(L, save);   // Process nested table
                // Restore stack to [table, key, value]
                lua_settop(L, top);
                break;
            }
            }
        }
        lua_pop(L, 1); // Pop value; stack: [table, key]
    }
}

void CBaseScripted::RestoreTable(lua_State* L, IRestore& restore) {
    // Ensure the table is at the top of the stack
    if (!lua_istable(L, -1)) {
        DevWarning("RestoreTable: Expected table at -1, got %s\n", lua_typename(L, lua_type(L, -1)));
        return;
    }

    int count;
    restore.ReadInt(&count);
    //DevLog("RestoreTable: Count=%d\n", count);

    for (int i = 0; i < count; i++) {
        // Save the stack top to restore later in case of errors
        int top = lua_gettop(L); // Should be 1: [table]

        int key_type;
        restore.ReadInt(&key_type);

        // Read the key
        if (key_type == LUA_TSTRING) {
            int len;
            restore.ReadInt(&len);

            char* key = new char[len];
            restore.ReadString(key, len, 0);
            lua_pushstring(L, key);
            delete[] key;
        }
        else if (key_type == LUA_TNUMBER) {
            float key_num;
            restore.ReadFloat(&key_num);
            lua_pushnumber(L, (double)key_num);
        }
        else {
            DevWarning("RestoreTable: Unsupported key type %d at pair %d, skipping\n", key_type, i);
            continue; // Skip this pair without pushing anything
        }

        // Read the value type
        int value_type;
        restore.ReadInt(&value_type);

        // Read the value
        switch (value_type) {
        case LUA_TNUMBER: {
            float num;
            restore.ReadFloat(&num);
            lua_pushnumber(L, (double)num);
            break;
        }
        case LUA_TSTRING: {
            int len;
            restore.ReadInt(&len);

            char* str = new char[len];
            restore.ReadString(str, len, 0);
            lua_pushstring(L, str);
            delete[] str;
            break;
        }
        case LUA_TBOOLEAN: {
            int bool_val;
            restore.ReadInt(&bool_val);
            lua_pushboolean(L, bool_val);
            break;
        }
        case LUA_TTABLE: {
            lua_newtable(L); // Create nested table; stack: [table, key, nested_table]
            RestoreTable(L, restore); // Recursively restore the nested table
            break;
        }
        default:
            DevWarning("RestoreTable: Unsupported value type %d at pair %d, skipping\n", value_type, i);
            lua_pop(L, 1); // Pop the key
            continue;
        }

        // Set the key-value pair in the table (table at -3, key at -2, value at -1)
        lua_settable(L, -3);

        // Ensure the stack is clean (should be back to [table])
        if (lua_gettop(L) != top) {
            DevWarning("RestoreTable: Stack imbalance after pair %d, expected %d, got %d\n", i, top, lua_gettop(L));
            lua_settop(L, top);
        }
    }
}




void CBaseScripted::LoadScriptedEntity( void )
{
	lua_getglobal( L, "entity" );
	if ( lua_istable( L, -1 ) )
	{
		lua_getfield( L, -1, "get" );
		if ( lua_isfunction( L, -1 ) )
		{
			lua_remove( L, -2 );
			lua_pushstring( L, GetClassname() );
			luasrc_pcall( L, 1, 1, 0 );
		}
		else
		{
			lua_pop( L, 2 );
		}
	}
	else
	{
		lua_pop( L, 1 );
	}
}

void CBaseScripted::InitScriptedEntity(void)
{
#if defined ( LUA_SDK )
#if 0
#ifndef CLIENT_DLL
	// Let the instance reinitialize itself for the client.
	if ( m_nTableReference != LUA_NOREF )
		return;
#endif
#endif

	SetThink( &CBaseScripted::Think );
#ifdef CLIENT_DLL
	SetNextClientThink( gpGlobals->curtime );
#endif
	SetNextThink( gpGlobals->curtime );

	SetTouch( &CBaseScripted::Touch );

	char className[ 255 ];
#if defined ( CLIENT_DLL )
	if ( strlen( GetScriptedClassname() ) > 0 )
		Q_strncpy( className, GetScriptedClassname(), sizeof( className ) );
	else
		Q_strncpy( className, GetClassname(), sizeof( className ) );
#else
	Q_strncpy( m_iScriptedClassname.GetForModify(), GetClassname(), sizeof( className ) );
 	Q_strncpy( className, GetClassname(), sizeof( className ) );
#endif
 	Q_strlower( className );
	SetClassname( className );

	if ( m_nTableReference == LUA_NOREF )
	{
		LoadScriptedEntity();
		m_nTableReference = luaL_ref( L, LUA_REGISTRYINDEX );
	}
	else
	{
		lua_getglobal( L, "table" );
		if ( lua_istable( L, -1 ) )
		{
			lua_getfield( L, -1, "merge" );
			if ( lua_isfunction( L, -1 ) )
			{
				lua_remove( L, -2 );
				lua_getref( L, m_nTableReference );
				LoadScriptedEntity();
				luasrc_pcall( L, 2, 0, 0 );
			}
			else
			{
				lua_pop( L, 2 );
			}
		}
		else
		{
			lua_pop( L, 1 );
		}
	}

	BEGIN_LUA_CALL_ENTITY_METHOD( "Initialize" );
	END_LUA_CALL_ENTITY_METHOD( 0, 0 );
#endif
}


#ifdef CLIENT_DLL
int CBaseScripted::DrawModel( int flags )
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_ENTITY_METHOD( "DrawModel" );
		lua_pushinteger( L, flags );
	END_LUA_CALL_ENTITY_METHOD( 1, 1 );

	RETURN_LUA_INTEGER();
#endif

	return BaseClass::DrawModel( flags );
}

void CBaseScripted::OnDataChanged( DataUpdateType_t updateType )
{
	BaseClass::OnDataChanged( updateType );

	if ( updateType == DATA_UPDATE_CREATED )
	{
		if ( m_iScriptedClassname.Get() )
		{
			SetClassname( m_iScriptedClassname.Get() );
			InitScriptedEntity();
		}
	}
}

const char *CBaseScripted::GetScriptedClassname( void )
{
	if ( m_iScriptedClassname.Get() )
		return m_iScriptedClassname.Get();
	return BaseClass::GetClassname();
}
#endif

void CBaseScripted::Spawn( void )
{
	BaseClass::Spawn();

#ifndef CLIENT_DLL
	InitScriptedEntity();
#endif
}

void CBaseScripted::Precache( void )
{
	BaseClass::Precache();

	// InitScriptedEntity();
}

#ifdef CLIENT_DLL
void CBaseScripted::ClientThink()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_ENTITY_METHOD( "ClientThink" );
	END_LUA_CALL_ENTITY_METHOD( 0, 0 );
#endif
}
#endif

void CBaseScripted::Think()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_ENTITY_METHOD( "Think" );
	END_LUA_CALL_ENTITY_METHOD( 0, 0 );
#endif
}

void CBaseScripted::StartTouch( CBaseEntity *pOther )
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_ENTITY_METHOD( "StartTouch" );
		lua_pushentity( L, pOther );
	END_LUA_CALL_ENTITY_METHOD( 1, 0 );
#endif
}

void CBaseScripted::Touch( CBaseEntity *pOther )
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_ENTITY_METHOD( "Touch" );
		lua_pushentity( L, pOther );
	END_LUA_CALL_ENTITY_METHOD( 1, 0 );
#endif
}

void CBaseScripted::EndTouch( CBaseEntity *pOther )
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_ENTITY_METHOD( "EndTouch" );
		lua_pushentity( L, pOther );
	END_LUA_CALL_ENTITY_METHOD( 1, 0 );
#endif
}
#ifndef CLIENT_DLL
int CBaseScripted::DrawDebugTextOverlays(void)
{
	
#ifdef LUA_SDK
	BEGIN_LUA_CALL_ENTITY_METHOD("DrawDebugTextOverlays");
	END_LUA_CALL_ENTITY_METHOD(0, 1);

	RETURN_LUA_INTEGER();
#endif

	return BaseClass::DrawDebugTextOverlays();
}
#endif
void CBaseScripted::VPhysicsUpdate( IPhysicsObject *pPhysics )
{
	BaseClass::VPhysicsUpdate( pPhysics );

#ifdef LUA_SDK
	BEGIN_LUA_CALL_ENTITY_METHOD( "VPhysicsUpdate" );
		lua_pushphysicsobject( L, pPhysics );
	END_LUA_CALL_ENTITY_METHOD( 1, 0 );
#endif
}

void CBaseScripted::OnRestore()
{
	BaseClass::OnRestore();

	// Reassign Think and Touch functions since we don't save these at all and is variable betweem each scripted entity.
	SetThink(&CBaseScripted::Think);
	SetTouch(&CBaseScripted::Touch);

	// Reset next think time
	SetNextThink(gpGlobals->curtime);


	BEGIN_LUA_CALL_ENTITY_METHOD("OnRestore");
	END_LUA_CALL_ENTITY_METHOD(0, 0);
}

