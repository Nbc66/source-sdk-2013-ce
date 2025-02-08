//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Spawn and use functions for editor-placed triggers.
//
//===========================================================================//

#include "cbase.h"
#include "luamanager.h"
#include "lbaseentity_shared.h"
#include "filters.h"
#include "basescriptedtrigger.h"
#include "saverestore_utlvector.h"
#include "iservervehicle.h"
#include "ai_behavior_follow.h"
#include "ai_behavior_lead.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Global Savedata for base trigger
BEGIN_DATADESC( CBaseScriptedTrigger )

	// Keyfields
	DEFINE_KEYFIELD( m_iFilterName,	FIELD_STRING,	"filtername" ),
	DEFINE_FIELD( m_hFilter,	FIELD_EHANDLE ),
	DEFINE_KEYFIELD( m_bDisabled,		FIELD_BOOLEAN,	"StartDisabled" ),
	DEFINE_UTLVECTOR( m_hTouchingEntities, FIELD_EHANDLE ),

	// Inputs	
	DEFINE_INPUTFUNC( FIELD_VOID, "Enable", InputEnable ),
	DEFINE_INPUTFUNC( FIELD_VOID, "Disable", InputDisable ),
	DEFINE_INPUTFUNC( FIELD_VOID, "Toggle", InputToggle ),
	DEFINE_INPUTFUNC( FIELD_VOID, "TouchTest", InputTouchTest ),

	DEFINE_INPUTFUNC( FIELD_VOID, "StartTouch", InputStartTouch ),
	DEFINE_INPUTFUNC( FIELD_VOID, "EndTouch", InputEndTouch ),

	// Outputs
	DEFINE_OUTPUT( m_OnStartTouch, "OnStartTouch"),
	DEFINE_OUTPUT( m_OnStartTouchAll, "OnStartTouchAll"),
	DEFINE_OUTPUT( m_OnEndTouch, "OnEndTouch"),
	DEFINE_OUTPUT( m_OnEndTouchAll, "OnEndTouchAll"),
	DEFINE_OUTPUT( m_OnTouching, "OnTouching" ),
	DEFINE_OUTPUT( m_OnNotTouching, "OnNotTouching" ),

END_DATADESC()


static CUtlDict< CEntityFactory<CBaseScriptedTrigger>*, unsigned short > m_TriggerFactoryDatabase;

void RegisterScriptedTrigger( const char *className )
{
	if ( EntityFactoryDictionary()->FindFactory( className ) )
	{
		return;
	}

	unsigned short lookup = m_TriggerFactoryDatabase.Find( className );
	if ( lookup != m_TriggerFactoryDatabase.InvalidIndex() )
	{
		return;
	}

	CEntityFactory<CBaseScriptedTrigger> *pFactory = new CEntityFactory<CBaseScriptedTrigger>( className );

	lookup = m_TriggerFactoryDatabase.Insert( className, pFactory );
	Assert( lookup != m_TriggerFactoryDatabase.InvalidIndex() );
}

void ResetTriggerFactoryDatabase( void )
{
	for ( int i=m_TriggerFactoryDatabase.First(); i != m_TriggerFactoryDatabase.InvalidIndex(); i=m_TriggerFactoryDatabase.Next( i ) )
	{
		delete m_TriggerFactoryDatabase[ i ];
	}
	m_TriggerFactoryDatabase.RemoveAll();
}


CBaseScriptedTrigger::CBaseScriptedTrigger( void )
{
#ifdef LUA_SDK
	m_nTableReference = LUA_NOREF;
#endif
}

CBaseScriptedTrigger::~CBaseScriptedTrigger( void )
{
#ifdef LUA_SDK
	lua_unref( L, m_nTableReference );
#endif
}

void CBaseScriptedTrigger::LoadScriptedTrigger( void )
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

void CBaseScriptedTrigger::InitScriptedTrigger( void )
{
#if defined ( LUA_SDK )
#if 0
	// Let the instance reinitialize itself for the client.
	if ( m_nTableReference != LUA_NOREF )
		return;
#endif

	SetThink( &CBaseScriptedTrigger::Think );
	SetNextThink( gpGlobals->curtime );

	SetTouch( &CBaseScriptedTrigger::Touch );

	char className[ 255 ];
 	Q_strncpy( className, GetClassname(), sizeof( className ) );
 	Q_strlower( className );
	SetClassname( className );

	lua_getglobal( L, "entity" );
	if ( lua_istable( L, -1 ) )
	{
		lua_getfield( L, -1, "get" );
		if ( lua_isfunction( L, -1 ) )
		{
			lua_remove( L, -2 );
			lua_pushstring( L, className );
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

	if ( m_nTableReference == LUA_NOREF )
	{
		LoadScriptedTrigger();
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
				LoadScriptedTrigger();
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

	BEGIN_LUA_CALL_TRIGGER_METHOD( "Initialize" );
	END_LUA_CALL_TRIGGER_METHOD( 0, 0 );
#endif
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void CBaseScriptedTrigger::Spawn()
{
	BaseClass::Spawn();

	InitScriptedTrigger();
}


//-----------------------------------------------------------------------------
// Purpose: Returns true if this entity passes the filter criteria, false if not.
// Input  : pOther - The entity to be filtered.
//-----------------------------------------------------------------------------
bool CBaseScriptedTrigger::PassesTriggerFilters(CBaseEntity *pOther)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_TRIGGER_METHOD( "PassesTriggerFilters" );
		lua_pushentity( L, pOther );
	END_LUA_CALL_TRIGGER_METHOD( 1, 1 );

	RETURN_LUA_BOOLEAN();
#endif

	return BaseClass::PassesTriggerFilters( pOther );
}

void CBaseScriptedTrigger::Think()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_TRIGGER_METHOD( "Think" );
	END_LUA_CALL_TRIGGER_METHOD( 0, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Called when an entity starts touching us.
// Input  : pOther - The entity that is touching us.
//-----------------------------------------------------------------------------
void CBaseScriptedTrigger::StartTouch(CBaseEntity *pOther)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_TRIGGER_METHOD( "StartTouch" );
		lua_pushentity( L, pOther );
	END_LUA_CALL_TRIGGER_METHOD( 1, 0 );
#endif
}


void CBaseScriptedTrigger::Touch(CBaseEntity *pOther)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_TRIGGER_METHOD( "Touch" );
		lua_pushentity( L, pOther );
	END_LUA_CALL_TRIGGER_METHOD( 1, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Called when an entity stops touching us.
// Input  : pOther - The entity that was touching us.
//-----------------------------------------------------------------------------
void CBaseScriptedTrigger::EndTouch(CBaseEntity *pOther)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_TRIGGER_METHOD( "EndTouch" );
		lua_pushentity( L, pOther );
	END_LUA_CALL_TRIGGER_METHOD( 1, 0 );
#endif
}


