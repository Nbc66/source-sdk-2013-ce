//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#define lColor_cpp

#include "cbase.h"
#include "Color.h"
#include "fmtstr.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "lColor.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

/*
** access functions (stack -> C)
*/


LUA_API lua_Color &lua_tocolor (lua_State *L, int idx) {
  lua_Color *clr = (lua_Color *)luaL_checkudata(L, idx, "Color");
  return *clr;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushcolor (lua_State *L, lua_Color &clr) {
  lua_Color *pColor = (lua_Color *)lua_newuserdata(L, sizeof(lua_Color));
  *pColor = clr;
  luaL_getmetatable(L, "Color");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_Color &luaL_checkcolor (lua_State *L, int narg) {
  lua_Color *d = (lua_Color *)luaL_checkudata(L, narg, "Color");
  return *d;
}


static int Color_a (lua_State *L) {
  lua_pushinteger(L, luaL_checkcolor(L, 1).a());
  return 1;
}

static int Color_b (lua_State *L) {
  lua_pushinteger(L, luaL_checkcolor(L, 1).b());
  return 1;
}

static int Color_g (lua_State *L) {
  lua_pushinteger(L, luaL_checkcolor(L, 1).g());
  return 1;
}

static int Color_GetColor (lua_State *L) {
  int r, g, b, a;
  luaL_checkcolor(L, 1).GetColor(r, g, b, a);
  lua_pushinteger(L, r);
  lua_pushinteger(L, g);
  lua_pushinteger(L, b);
  lua_pushinteger(L, a);
  return 4;
}

static int Color_GetRawColor (lua_State *L) {
  lua_pushinteger(L, luaL_checkcolor(L, 1).GetRawColor());
  return 1;
}

static int Color_r (lua_State *L) {
  lua_pushinteger(L, luaL_checkcolor(L, 1).r());
  return 1;
}

static int Color_SetColor (lua_State *L) {
  luaL_checkcolor(L, 1).SetColor(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_optint(L, 4, 255));
  return 0;
}

static int Color_SetRawColor (lua_State *L) {
  luaL_checkcolor(L, 1).SetRawColor(luaL_checkint(L, 1));
  return 0;
}

static int Color___tostring (lua_State *L) {
  Color color = luaL_checkcolor(L, 1);
  lua_pushfstring(L, "Color: %s", static_cast<const char *>(CFmtStr("(%i, %i, %i, %i)", color.r(), color.g(), color.b(), color.a())));
  return 1;
}

static int Color___eq (lua_State *L) {
  lua_pushboolean(L, luaL_checkcolor(L, 1) == luaL_checkcolor(L, 2));
  return 1;
}


static const luaL_Reg Colormeta[] = {
  {"a", Color_a},
  {"b", Color_b},
  {"g", Color_g},
  {"GetColor", Color_GetColor},
  {"GetRawColor", Color_GetRawColor},
  {"r", Color_r},
  {"SetColor", Color_SetColor},
  {"SetRawColor", Color_SetRawColor},
  {"__tostring", Color___tostring},
  {"__eq", Color___eq},
  {NULL, NULL}
};


static int luasrc_Color (lua_State *L) {
  Color clr = Color(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_optint(L, 4, 255));
  lua_pushcolor(L, clr);
  return 1;
}


static const luaL_Reg Color_funcs[] = {
  {"Color", luasrc_Color},
  {NULL, NULL}
};


/*
** Open Color object
*/
LUALIB_API int luaopen_Color (lua_State *L) {
  luaL_newmetatable(L, LUA_COLORLIBNAME);
  luaL_register(L, NULL, Colormeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "color");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "color" */
  luaL_register(L, "_G", Color_funcs);
  lua_pop(L, 1);
  return 1;
}

