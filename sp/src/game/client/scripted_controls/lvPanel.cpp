//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//


#include <cbase.h>
#include <vgui_int.h>
#include <luamanager.h>
#include <vgui_controls/lPanel.h>

#include <scripted_controls/lPanel.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
LPanel::LPanel(Panel *parent, const char *panelName, lua_State *L) : Panel(parent, panelName)
{
#if defined( LUA_SDK )
	m_lua_State = L;
	m_nTableReference = LUA_NOREF;
	m_nRefCount = 0;
#endif // LUA_SDK
}

//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
LPanel::~LPanel()
{
#if defined( LUA_SDK )
	lua_unref( m_lua_State, m_nTableReference );
#endif // LUA_SDK
}

//-----------------------------------------------------------------------------
// Purpose: Screen size change notification handler
//-----------------------------------------------------------------------------
void LPanel::OnScreenSizeChanged(int nOldWide, int nOldTall)
{
	BaseClass::OnScreenSizeChanged(nOldWide, nOldTall);

#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnScreenSizeChanged" );
		lua_pushinteger( m_lua_State, nOldWide );
		lua_pushinteger( m_lua_State, nOldTall );
	END_LUA_CALL_PANEL_METHOD( 2, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void LPanel::PaintBorder()
{
	BaseClass::PaintBorder();

#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "PaintBorder" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void LPanel::PaintBackground()
{ 
	BaseClass::PaintBackground();

#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "PaintBackground" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void LPanel::Paint()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "Paint" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void LPanel::PostChildPaint()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "PostChildPaint" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Draws a black rectangle around the panel.
//-----------------------------------------------------------------------------
void LPanel::PaintBuildOverlay()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "PaintBuildOverlay" );
	END_LUA_CALL_PANEL_METHOD( 0, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::PaintBuildOverlay();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void LPanel::OnChildAdded(VPANEL child)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnChildAdded" );
		lua_pushpanel( m_lua_State, child );
	END_LUA_CALL_PANEL_METHOD( 0, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnChildAdded(child);
}

//-----------------------------------------------------------------------------
// Purpose: default message handler
//-----------------------------------------------------------------------------
void LPanel::OnSizeChanged(int newWide, int newTall)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnSizeChanged" );
		lua_pushinteger( m_lua_State, newWide );
		lua_pushinteger( m_lua_State, newTall );
	END_LUA_CALL_PANEL_METHOD( 2, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnSizeChanged(newWide, newTall);
}

//-----------------------------------------------------------------------------
// Purpose: Called every frame the panel is visible, designed to be overridden
//-----------------------------------------------------------------------------
void LPanel::OnThink()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnThink" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

// input messages handlers (designed for override)
void LPanel::OnCursorMoved(int x, int y)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnCursorMoved" );
		lua_pushinteger( m_lua_State, x );
		lua_pushinteger( m_lua_State, y );
	END_LUA_CALL_PANEL_METHOD( 2, 0 );
#endif
}

void LPanel::OnCursorEntered()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnCursorEntered" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

void LPanel::OnCursorExited()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnCursorExited" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

void LPanel::OnMousePressed(MouseCode code)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnMousePressed" );
		lua_pushinteger( m_lua_State, code );
	END_LUA_CALL_PANEL_METHOD( 1, 0 );
#endif
}

void LPanel::OnMouseDoublePressed(MouseCode code)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnMouseDoublePressed" );
		lua_pushinteger( m_lua_State, code );
	END_LUA_CALL_PANEL_METHOD( 1, 0 );
#endif
}

void LPanel::OnMouseTriplePressed(MouseCode code)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnMouseTriplePressed" );
		lua_pushinteger( m_lua_State, code );
	END_LUA_CALL_PANEL_METHOD( 1, 0 );
#endif
}

void LPanel::OnMouseReleased(MouseCode code)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnMouseReleased" );
		lua_pushinteger( m_lua_State, code );
	END_LUA_CALL_PANEL_METHOD( 1, 0 );
#endif
}

void LPanel::OnMouseWheeled(int delta)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnMouseWheeled" );
		lua_pushinteger( m_lua_State, delta );
	END_LUA_CALL_PANEL_METHOD( 1, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnMouseWheeled(delta);
}

// base implementation forwards Key messages to the Panel's parent - override to 'swallow' the input
void LPanel::OnKeyCodePressed(KeyCode code)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnKeyCodePressed" );
		lua_pushinteger( m_lua_State, code );
	END_LUA_CALL_PANEL_METHOD( 1, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnKeyCodePressed(code);
}

void LPanel::OnKeyCodeTyped(KeyCode code)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnKeyCodeTyped" );
		lua_pushinteger( m_lua_State, code );
	END_LUA_CALL_PANEL_METHOD( 1, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnKeyCodeTyped(code);
}

void LPanel::OnKeyCodeReleased(KeyCode code)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnKeyCodeReleased" );
		lua_pushinteger( m_lua_State, code );
	END_LUA_CALL_PANEL_METHOD( 1, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnKeyCodeReleased(code);
}

void LPanel::OnKeyFocusTicked()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnKeyFocusTicked" );
	END_LUA_CALL_PANEL_METHOD( 0, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnKeyFocusTicked();
}

void LPanel::OnMouseFocusTicked()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnMouseFocusTicked" );
	END_LUA_CALL_PANEL_METHOD( 0, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnMouseFocusTicked();
}

//-----------------------------------------------------------------------------
// Purpose: Called after a panel requests focus to fix up the whole chain
//-----------------------------------------------------------------------------
void LPanel::OnRequestFocus(VPANEL subFocus, VPANEL defaultPanel)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnRequestFocus" );
		lua_pushpanel( m_lua_State, subFocus );
		lua_pushpanel( m_lua_State, defaultPanel );
	END_LUA_CALL_PANEL_METHOD( 2, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnRequestFocus(subFocus, defaultPanel);
}

//-----------------------------------------------------------------------------
// Purpose: Called when a panel loses it's mouse capture
//-----------------------------------------------------------------------------
void LPanel::OnMouseCaptureLost()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnMouseCaptureLost" );
	END_LUA_CALL_PANEL_METHOD( 0, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnMouseCaptureLost();
}

void LPanel::PerformLayout()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "PerformLayout" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Called when a panel receives a command message from another panel
//-----------------------------------------------------------------------------
void LPanel::OnCommand(const char *command)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnCommand" );
		lua_pushstring( m_lua_State, command );
	END_LUA_CALL_PANEL_METHOD( 1, 1 );

	RETURN_LUA_PANEL_NONE();
#endif
	BaseClass::OnCommand( command );
}

//-----------------------------------------------------------------------------
// Purpose: panel gained focus message
//-----------------------------------------------------------------------------
void LPanel::OnSetFocus()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnSetFocus" );
	END_LUA_CALL_PANEL_METHOD( 0, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnSetFocus();
}

//-----------------------------------------------------------------------------
// Purpose: panel lost focus message
//-----------------------------------------------------------------------------
void LPanel::OnKillFocus()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnKillFocus" );
	END_LUA_CALL_PANEL_METHOD( 0, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnKillFocus();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void LPanel::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);

#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "ApplySchemeSettings" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}


//-----------------------------------------------------------------------------
// Purpose: Loads panel details from the resource info
//-----------------------------------------------------------------------------
void LPanel::ApplySettings(KeyValues *inResourceData)
{
	BaseClass::ApplySettings( inResourceData );

#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "ApplySettings" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: called whenever the panel moves
//-----------------------------------------------------------------------------
void LPanel::OnMove()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnMove" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: empty function
//-----------------------------------------------------------------------------
void LPanel::OnTick()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnTick" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Handles a message
//			Dispatches the message to a set of message maps
//-----------------------------------------------------------------------------
void LPanel::OnMessage(const KeyValues *params, VPANEL ifromPanel)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnMessage" );
		lua_pushpanel( m_lua_State, ifromPanel );
	END_LUA_CALL_PANEL_METHOD( 1, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnMessage( params, ifromPanel );
}

//-----------------------------------------------------------------------------
// Purpose: Called to delete the panel
//-----------------------------------------------------------------------------
void LPanel::OnDelete()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PANEL_METHOD( "OnDelete" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif

	BaseClass::OnDelete();
}

static int luasrc_Panel (lua_State *L) {
  Panel *pPanel = new LPanel(luaL_optpanel(L, 1, VGui_GetClientLuaRootPanel()), luaL_optstring(L, 2, NULL), L);
  lua_pushpanel(L, pPanel);
  return 1;
}


static const luaL_Reg Panel_funcs[] = {
  {"Panel", luasrc_Panel},
  {NULL, NULL}
};


/*
** Open Panel object
*/
LUALIB_API int luaopen_vgui_Panel(lua_State *L) {
  luaL_register(L, "vgui", Panel_funcs);
  lua_pop(L, 1);
  return 1;
}
