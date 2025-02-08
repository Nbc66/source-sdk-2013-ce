//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//
#define lienginevgui_cpp

#include "cbase.h"
#include "ienginevgui.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "vgui_controls/lPanel.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Forward declarations.
namespace vgui
{
	class Panel;
};


static int enginevgui_GetPanel (lua_State *L) {
  lua_pushpanel(L, enginevgui->GetPanel((VGuiPanel_t)luaL_checkint(L, 1)));
  return 1;
}

static int enginevgui_IsGameUIVisible (lua_State *L) {
  lua_pushboolean(L, enginevgui->IsGameUIVisible());
  return 1;
}


static const luaL_Reg enginevguilib[] = {
  {"GetPanel",   enginevgui_GetPanel},
  {"IsGameUIVisible",   enginevgui_IsGameUIVisible},
  {NULL, NULL}
};


/*
** Open enginevgui library
*/
LUALIB_API int luaopen_enginevgui (lua_State *L) {
  luaL_register(L, LUA_ENGINEVGUILIBNAME, enginevguilib);
  return 1;
}

