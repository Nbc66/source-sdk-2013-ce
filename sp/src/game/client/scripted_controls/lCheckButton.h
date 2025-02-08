//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef VGUI_LCHECKBUTTON_H
#define VGUI_LCHECKBUTTON_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/CheckButton.h>

namespace vgui
{

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class LCheckButton : public CheckButton
{
	DECLARE_CLASS_SIMPLE( LCheckButton, CheckButton );

public:
	LCheckButton(Panel *parent, const char *panelName, const char *text, lua_State *L);
	virtual ~LCheckButton();

protected:
	MESSAGE_FUNC( OnCheckButtonChecked, "CheckButtonChecked" );

public:
#if defined( LUA_SDK )
	lua_State *m_lua_State;
	int m_nTableReference;
	int m_nRefCount;
#endif
};

} // namespace vgui

#define BEGIN_LUA_CALL_CHECKBUTTON_METHOD(functionName) \
  if (m_nTableReference >= 0) { \
    lua_getref(m_lua_State, m_nTableReference); \
    lua_getfield(m_lua_State, -1, functionName); \
    lua_remove(m_lua_State, -2); \
    if (lua_isfunction(m_lua_State, -1)) { \
      int args = 0; \
	  lua_pushcheckbutton(m_lua_State, this); \
	  ++args;

/* type for CheckButton functions */
typedef vgui::CheckButton lua_CheckButton;



/*
** access functions (stack -> C)
*/

LUA_API lua_CheckButton     *(lua_tocheckbutton) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushcheckbutton) (lua_State *L, lua_CheckButton *pCheckButton);



LUALIB_API lua_CheckButton *(luaL_checkcheckbutton) (lua_State *L, int narg);

#endif // VGUI_LCHECKBUTTON_H
