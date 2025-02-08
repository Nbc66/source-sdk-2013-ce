//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef BASESCRIPTEDTRIGGER_H
#define BASESCRIPTEDTRIGGER_H
#ifdef _WIN32
#pragma once
#endif

#include "triggers.h"
#include "entityoutput.h"

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CBaseScriptedTrigger : public CBaseTrigger
{
	DECLARE_CLASS( CBaseScriptedTrigger, CBaseTrigger );
public:
	CBaseScriptedTrigger();
	~CBaseScriptedTrigger();
	
	void LoadScriptedTrigger( void );
	void InitScriptedTrigger( void );
	void Think();	

	void Spawn( void );

	virtual bool PassesTriggerFilters(CBaseEntity *pOther);
	virtual void StartTouch(CBaseEntity *pOther);
	virtual void Touch(CBaseEntity *pOther);
	virtual void EndTouch(CBaseEntity *pOther);

	// by default, triggers don't deal with TraceAttack
	void TraceAttack(CBaseEntity *pAttacker, float flDamage, const Vector &vecDir, trace_t *ptr, int bitsDamageType) {}

protected:

	DECLARE_DATADESC();
};

void RegisterScriptedTrigger( const char *szClassname );
void ResetTriggerFactoryDatabase( void );

#endif // BASESCRIPTEDTRIGGER_H
