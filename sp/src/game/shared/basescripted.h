//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//

#ifndef BASESCRIPTED_H
#define BASESCRIPTED_H

#include "predictable_entity.h"
#include "baseentity_shared.h"
#include "luamanager.h"
#include "saverestore.h"

#if defined( CLIENT_DLL )
#define CBaseScripted C_BaseScripted

#endif 

class CBaseScripted : /* public CBaseEntity */ public CBaseAnimating
{
public:
	// DECLARE_CLASS( CBaseScripted, CBaseEntity );
	DECLARE_CLASS( CBaseScripted, CBaseAnimating );
	DECLARE_PREDICTABLE();
	DECLARE_NETWORKCLASS();
#ifndef CLIENT_DLL
	DECLARE_DATADESC();
#endif // !CLIENT_DLL

	CBaseScripted();
	~CBaseScripted();

	

	bool	IsScripted( void ) const { return true; }
	
	// CBaseEntity overrides.
public:
	void	Think();	

	void	Spawn( void );
	void	Precache( void );
	void	LoadScriptedEntity( void );
	void	InitScriptedEntity( void );
	
	void	SaveEntity(ISave& save, CBaseEntity* pentity);
	void	RestoreEntity(IRestore& restore, CBaseEntity* pentity);
	void	RestoreTable(lua_State* L, IRestore& restore);
	void	SaveTable(lua_State* L, ISave& save);

	virtual int				Save(ISave& save);
	virtual int				Restore(IRestore& restore);
	int						GetSupportedPairCount(lua_State* L, int tableIndex);
#ifdef GAME_DLL
	void			OnSave(IEntitySaveUtils* pUtils);
	
	
#endif
	void	StartTouch( CBaseEntity *pOther );
	void	Touch( CBaseEntity *pOther ); 
	void	EndTouch( CBaseEntity *pOther );
#ifndef CLIENT_DLL
	virtual int  DrawDebugTextOverlays(void);
#endif

	virtual void OnRestore(void);

#ifdef CLIENT_DLL
	// model specific
	virtual int DrawModel( int flags );
#endif

	virtual void VPhysicsUpdate( IPhysicsObject *pPhysics );

#ifdef CLIENT_DLL
// IClientThinkable.
public:
	// Called whenever you registered for a think message (with SetNextClientThink).
	virtual void	ClientThink();

	virtual void	OnDataChanged( DataUpdateType_t updateType );
	virtual const char *GetScriptedClassname( void );
#endif

private:
	CBaseScripted( const CBaseScripted & ); // not defined, not accessible

	CNetworkString( m_iScriptedClassname, 255 );
};

void RegisterScriptedEntity( const char *szClassname );
void ResetEntityFactoryDatabase( void );

#endif


