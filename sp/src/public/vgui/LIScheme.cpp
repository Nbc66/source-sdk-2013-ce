//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#define LIScheme_cpp

#include "cbase.h"
#include "vgui/ischeme.h"
#include "vgui_controls/Controls.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "vgui/lischeme.h"
#include "vgui/lvgui.h"
#include "vgui_controls/lPanel.h"
#include "lColor.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

using namespace vgui;



/*
** access functions (stack -> C)
*/


LUA_API lua_IScheme *lua_toischeme (lua_State *L, int idx) {
  lua_IScheme **ppScheme = (lua_IScheme **)lua_touserdata(L, idx);
  return *ppScheme;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushischeme (lua_State *L, lua_IScheme *pScheme) {
  if (pScheme == NULL)
    lua_pushnil(L);
  else {
    lua_IScheme **ppScheme = (lua_IScheme **)lua_newuserdata(L, sizeof(lua_IScheme));
    *ppScheme = pScheme;
    luaL_getmetatable(L, "IScheme");
    lua_setmetatable(L, -2);
  }
}


LUALIB_API lua_IScheme *luaL_checkischeme (lua_State *L, int narg) {
  lua_IScheme **d = (lua_IScheme **)luaL_checkudata(L, narg, "IScheme");
  return *d;
}


static int IScheme_GetColor (lua_State *L) {
  lua_pushcolor(L, luaL_checkischeme(L, 1)->GetColor(luaL_checkstring(L, 2), luaL_checkcolor(L, 3)));
  return 1;
}

static int IScheme_GetFont (lua_State *L) {
  lua_pushfont(L, luaL_checkischeme(L, 1)->GetFont(luaL_checkstring(L, 2), luaL_optboolean(L, 3, false)));
  return 1;
}

static int IScheme_GetFontName (lua_State *L) {
  lua_pushstring(L, luaL_checkischeme(L, 1)->GetFontName(luaL_checkfont(L, 2)));
  return 1;
}

static int IScheme_GetResourceString (lua_State *L) {
  lua_pushstring(L, luaL_checkischeme(L, 1)->GetResourceString(luaL_checkstring(L, 2)));
  return 1;
}

static int IScheme___tostring (lua_State *L) {
  lua_pushfstring(L, "IScheme: %p", luaL_checkudata(L, 1, "IScheme"));
  return 1;
}


static const luaL_Reg ISchememeta[] = {
  {"GetColor", IScheme_GetColor},
  {"GetFont", IScheme_GetFont},
  {"GetFontName", IScheme_GetFontName},
  {"GetResourceString", IScheme_GetResourceString},
  {"__tostring", IScheme___tostring},
  {NULL, NULL}
};


/*
** Open IScheme object
*/
LUALIB_API int luaopen_IScheme (lua_State *L) {
  luaL_newmetatable(L, LUA_ISCHEMELIBNAME);
  luaL_register(L, NULL, ISchememeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "ischeme");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "ischeme" */
  return 1;
}


static int scheme_GetDefaultScheme (lua_State *L) {
  lua_pushscheme(L, scheme()->GetDefaultScheme());
  return 1;
}

static int scheme_GetIScheme (lua_State *L) {
  lua_pushischeme(L, scheme()->GetIScheme(luaL_checkscheme(L, 1)));
  return 1;
}

static int scheme_GetProportionalNormalizedValue (lua_State *L) {
  lua_pushinteger(L, scheme()->GetProportionalNormalizedValue(luaL_checkint(L, 1)));
  return 1;
}

static int scheme_GetProportionalNormalizedValueEx (lua_State *L) {
  lua_pushinteger(L, scheme()->GetProportionalNormalizedValueEx(luaL_checkscheme(L, 1), luaL_checkint(L, 2)));
  return 1;
}

static int scheme_GetProportionalScaledValue (lua_State *L) {
  lua_pushinteger(L, scheme()->GetProportionalScaledValue(luaL_checkint(L, 1)));
  return 1;
}

static int scheme_GetProportionalScaledValueEx (lua_State *L) {
  lua_pushinteger(L, scheme()->GetProportionalScaledValueEx(luaL_checkscheme(L, 1), luaL_checkint(L, 2)));
  return 1;
}

static int scheme_GetScheme (lua_State *L) {
  lua_pushscheme(L, scheme()->GetScheme(luaL_checkstring(L, 1)));
  return 1;
}

static int scheme_LoadSchemeFromFile (lua_State *L) {
  lua_pushscheme(L, scheme()->LoadSchemeFromFile(luaL_checkstring(L, 1), luaL_checkstring(L, 2)));
  return 1;
}

static int scheme_LoadSchemeFromFileEx (lua_State *L) {
  lua_pushscheme(L, scheme()->LoadSchemeFromFileEx(luaL_checkvpanel(L, 1), luaL_checkstring(L, 2), luaL_checkstring(L, 3)));
  return 1;
}

static int scheme_ReloadFonts (lua_State *L) {
  scheme()->ReloadFonts();
  return 0;
}

static int scheme_ReloadSchemes (lua_State *L) {
  scheme()->ReloadSchemes();
  return 0;
}


static const luaL_Reg schemelib[] = {
  {"GetDefaultScheme",   scheme_GetDefaultScheme},
  {"GetIScheme",   scheme_GetIScheme},
  {"GetProportionalNormalizedValue",   scheme_GetProportionalNormalizedValue},
  {"GetProportionalNormalizedValueEx",   scheme_GetProportionalNormalizedValueEx},
  {"GetProportionalScaledValue",   scheme_GetProportionalScaledValue},
  {"GetProportionalScaledValueEx",   scheme_GetProportionalScaledValueEx},
  {"GetScheme",   scheme_GetScheme},
  {"LoadSchemeFromFile",   scheme_LoadSchemeFromFile},
  {"LoadSchemeFromFileEx",   scheme_LoadSchemeFromFileEx},
  {"ReloadFonts",   scheme_ReloadFonts},
  {"ReloadSchemes",   scheme_ReloadSchemes},
  {NULL, NULL}
};


/*
** Open scheme library
*/
LUALIB_API int luaopen_scheme (lua_State *L) {
  luaL_register(L, LUA_SCHEMELIBNAME, schemelib);
  return 1;
}

