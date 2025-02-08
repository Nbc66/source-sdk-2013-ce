//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Random number generator
//
// $Workfile: $
// $NoKeywords: $
//===========================================================================//

#define lrandom_cpp

#include "cbase.h"
#include "lua.hpp"
#include "luasrclib.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"



static int random_RandomFloat (lua_State *L) {
  lua_pushnumber(L, random->RandomFloat(luaL_optnumber(L, 1, 0.0f), luaL_optnumber(L, 2, 0.0f)));
  return 1;
}

static int random_RandomFloatExp (lua_State *L) {
  lua_pushnumber(L, random->RandomFloatExp(luaL_optnumber(L, 1, 0.0f), luaL_optnumber(L, 2, 0.0f), luaL_optnumber(L, 3, 1.0f)));
  return 1;
}

static int random_RandomInt (lua_State *L) {
  lua_pushinteger(L, random->RandomInt(luaL_checkint(L, 1), luaL_checkint(L, 2)));
  return 1;
}

static int random_SetSeed (lua_State *L) {
  random->SetSeed(luaL_checkint(L, 1));
  return 0;
}


static const luaL_Reg randomlib[] = {
  {"RandomFloat",   random_RandomFloat},
  {"RandomFloatExp",   random_RandomFloatExp},
  {"RandomInt",   random_RandomInt},
  {"SetSeed",   random_SetSeed},
  {NULL, NULL}
};


#if 0
static int luasrc_RandomSeed (lua_State *L) {
  RandomSeed(luaL_checkint(L, 1));
  return 0;
}

static int luasrc_RandomFloat (lua_State *L) {
  lua_pushnumber(L, RandomFloat(luaL_optnumber(L, 1, 0.0f), luaL_optnumber(L, 2, 0.0f)));
  return 1;
}

static int luasrc_RandomFloatExp (lua_State *L) {
  lua_pushnumber(L, RandomFloatExp(luaL_optnumber(L, 1, 0.0f), luaL_optnumber(L, 2, 1.0f), luaL_optnumber(L, 3, 1.0f)));
  return 1;
}

static int luasrc_RandomInt (lua_State *L) {
  lua_pushinteger(L, RandomInt(luaL_checkint(L, 1), luaL_checkint(L, 2)));
  return 1;
}

static int luasrc_RandomGaussianFloat (lua_State *L) {
  lua_pushnumber(L, RandomGaussianFloat(luaL_optnumber(L, 1, 0.0f), luaL_optnumber(L, 2, 1.0f)));
  return 1;
}


static const luaL_Reg random_funcs[] = {
  {"RandomSeed",  luasrc_RandomSeed},
  {"RandomFloat",  luasrc_RandomFloat},
  {"RandomFloatExp",  luasrc_RandomFloatExp},
  {"RandomInt",  luasrc_RandomInt},
  {"RandomGaussianFloat",  luasrc_RandomGaussianFloat},
  {NULL, NULL}
};
#endif


/*
** Open random library
*/
LUALIB_API int luaopen_random (lua_State *L) {
  luaL_register(L, LUA_RANDOMLIBNAME, randomlib);
  // UNDONE: this has always been redundant.
  // luaL_register(L, "_G", random_funcs);
  return 1;
}

