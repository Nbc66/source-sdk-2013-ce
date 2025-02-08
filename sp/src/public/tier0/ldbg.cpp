//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ========//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#define ldbg_cpp

#include "cbase.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "lColor.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"



static int luasrc_SpewActivate (lua_State *L) {
  SpewActivate(luaL_checkstring(L, 1), luaL_checkint(L, 2));
  return 0;
}

static int luasrc_IsSpewActive (lua_State *L) {
  lua_pushboolean(L, IsSpewActive(luaL_checkstring(L, 1), luaL_checkint(L, 2)));
  return 1;
}

static int luasrc_Msg (lua_State *L) {
  Msg(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_DMsg (lua_State *L) {
  DMsg(luaL_checkstring(L, 1), luaL_checkint(L, 2), luaL_checkstring(L, 3));
  return 0;
}

static int luasrc_Warning (lua_State *L) {
  Warning(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_DWarning (lua_State *L) {
  DWarning(luaL_checkstring(L, 1), luaL_checkint(L, 2), luaL_checkstring(L, 3));
  return 0;
}

static int luasrc_Log (lua_State *L) {
  Log(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_DLog (lua_State *L) {
  DLog(luaL_checkstring(L, 1), luaL_checkint(L, 2), luaL_checkstring(L, 3));
  return 0;
}

static int luasrc_Error (lua_State *L) {
  Error(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_DevMsg (lua_State *L) {
  DevMsg(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_DevWarning (lua_State *L) {
  DevWarning(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_DevLog (lua_State *L) {
  DevLog(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_ConColorMsg (lua_State *L) {
  ConColorMsg(luaL_checkcolor(L, 1), luaL_checkstring(L, 2));
  return 0;
}

static int luasrc_ConMsg (lua_State *L) {
  ConMsg(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_ConWarning (lua_State *L) {
  ConWarning(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_ConLog (lua_State *L) {
  ConLog(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_ConDColorMsg (lua_State *L) {
  ConDColorMsg(luaL_checkcolor(L, 1), luaL_checkstring(L, 2));
  return 0;
}

static int luasrc_ConDMsg (lua_State *L) {
  ConDMsg(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_ConDWarning (lua_State *L) {
  ConDWarning(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_ConDLog (lua_State *L) {
  ConDLog(luaL_checkstring(L, 1));
  return 0;
}

static int luasrc_NetMsg (lua_State *L) {
  NetMsg(luaL_checkint(L, 1), luaL_checkstring(L, 2));
  return 0;
}

static int luasrc_NetWarning (lua_State *L) {
  NetWarning(luaL_checkint(L, 1), luaL_checkstring(L, 2));
  return 0;
}

static int luasrc_NetLog (lua_State *L) {
  NetLog(luaL_checkint(L, 1), luaL_checkstring(L, 2));
  return 0;
}


static const luaL_Reg dbg_funcs[] = {
  {"SpewActivate",  luasrc_SpewActivate},
  {"IsSpewActive",  luasrc_IsSpewActive},
  {"Msg",  luasrc_Msg},
  {"DMsg",  luasrc_DMsg},
  {"Warning",  luasrc_Warning},
  {"DWarning",  luasrc_DWarning},
  {"Log",  luasrc_Log},
  {"DLog",  luasrc_DLog},
  {"Error",  luasrc_Error},
  {"DevMsg",  luasrc_DevMsg},
  {"DevWarning",  luasrc_DevWarning},
  {"DevLog",  luasrc_DevLog},
  {"ConColorMsg",  luasrc_ConColorMsg},
  {"ConMsg",  luasrc_ConMsg},
  {"ConWarning",  luasrc_ConWarning},
  {"ConLog",  luasrc_ConLog},
  {"ConDColorMsg",  luasrc_ConDColorMsg},
  {"ConDMsg",  luasrc_ConDMsg},
  {"ConDWarning",  luasrc_ConDWarning},
  {"ConDLog",  luasrc_ConDLog},
  {"NetMsg",  luasrc_NetMsg},
  {"NetWarning",  luasrc_NetWarning},
  {"NetLog",  luasrc_NetLog},
  {NULL, NULL}
};


LUALIB_API int luaopen_dbg (lua_State *L) {
  luaL_register(L, LUA_DBGLIBNAME, dbg_funcs);
  return 1;
}

