//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Basic header for using vgui
//
// $NoKeywords: $
//=============================================================================//

#define lvgui_cpp

#include "cbase.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "lvgui.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


using namespace vgui;


/*
** access functions (stack -> C)
*/


LUA_API lua_HScheme lua_toscheme (lua_State *L, int idx) {
  lua_HScheme hScheme = *(lua_HScheme *)lua_touserdata(L, idx);
  return hScheme;
}


LUA_API lua_HFont lua_tofont (lua_State *L, int idx) {
  lua_HFont hFont = *(lua_HFont *)lua_touserdata(L, idx);
  return hFont;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushscheme (lua_State *L, HScheme hScheme) {
  lua_HScheme *phScheme = (lua_HFont *)lua_newuserdata(L, sizeof(hScheme));
  *phScheme = hScheme;
  luaL_getmetatable(L, "HScheme");
  lua_setmetatable(L, -2);
}


LUA_API void lua_pushfont (lua_State *L, HFont hFont) {
  lua_HFont *phFont = (lua_HFont *)lua_newuserdata(L, sizeof(hFont));
  *phFont = hFont;
  luaL_getmetatable(L, "HFont");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_HScheme luaL_checkscheme (lua_State *L, int narg) {
  lua_HScheme *d = (lua_HScheme *)luaL_checkudata(L, narg, "HScheme");
  return *d;
}


LUALIB_API lua_HFont luaL_checkfont (lua_State *L, int narg) {
  lua_HFont *d = (lua_HFont *)luaL_checkudata(L, narg, "HFont");
  return *d;
}


static int HScheme___tostring (lua_State *L) {
  HScheme hScheme = luaL_checkscheme(L, 1);
  lua_pushfstring(L, "HScheme: %d", hScheme);
  return 1;
}


static const luaL_Reg HSchememeta[] = {
  {"__tostring", HScheme___tostring},
  {NULL, NULL}
};


/*
** Open HScheme object
*/
LUALIB_API int luaopen_HScheme (lua_State *L) {
  luaL_newmetatable(L, LUA_HSCHEMELIBNAME);
  luaL_register(L, NULL, HSchememeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "scheme");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "scheme" */
  return 1;
}


static int HFont___tostring (lua_State *L) {
  HFont hFont = luaL_checkfont(L, 1);
  if (hFont == INVALID_FONT)
    lua_pushstring(L, "INVALID_FONT");
  else
    lua_pushfstring(L, "HFont: %d", hFont);
  return 1;
}


static const luaL_Reg HFontmeta[] = {
  {"__tostring", HFont___tostring},
  {NULL, NULL}
};


/*
** Open HFont object
*/
LUALIB_API int luaopen_HFont (lua_State *L) {
  luaL_newmetatable(L, LUA_FONTLIBNAME);
  luaL_register(L, NULL, HFontmeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "font");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "font" */
  lua_pushfont(L, INVALID_FONT);
  lua_setglobal(L, "INVALID_FONT");  /* set global INVALID_FONT */
  return 1;
}
