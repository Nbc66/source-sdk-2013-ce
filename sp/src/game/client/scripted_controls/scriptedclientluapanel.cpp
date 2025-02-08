//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Client DLL VGUI2 Viewport
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"

// our definition
#include "scriptedclientluapanel.h"

// lua hooks
#ifdef LUA_SDK
#include "luamanager.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

using namespace vgui;

//================================================================
CScriptedClientLuaPanel::CScriptedClientLuaPanel() : vgui::EditablePanel( NULL, "CScriptedClientLuaPanel")
{
	SetKeyBoardInputEnabled( false );
	SetMouseInputEnabled( false );

	SetProportional( true );
}

void CScriptedClientLuaPanel::CreateDefaultPanels( void )
{
	// Was a nice idea, but is called on game init and not level init
#if 0
	BEGIN_LUA_CALL_HOOK( "CreateDefaultPanels" );
	END_LUA_CALL_HOOK( 0, 0 );
#endif
}


//-----------------------------------------------------------------------------
// Purpose: called when the VGUI subsystem starts up
//			Creates the sub panels and initialises them
//-----------------------------------------------------------------------------
void CScriptedClientLuaPanel::Start( IGameUIFuncs *pGameUIFuncs, IGameEventManager2 * pGameEventManager )
{
	CreateDefaultPanels();
}

//-----------------------------------------------------------------------------
// Purpose: Sets the parent for each panel to use
//-----------------------------------------------------------------------------
void CScriptedClientLuaPanel::SetParent(vgui::VPANEL parent)
{
	EditablePanel::SetParent( parent );
	// force ourselves to be proportional - when we set our parent above, if our new
	// parent happened to be non-proportional (such as the vgui root panel), we got
	// slammed to be nonproportional
	EditablePanel::SetProportional( true );
}

void CScriptedClientLuaPanel::Paint()
{
}
