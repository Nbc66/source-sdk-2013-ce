//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
//===========================================================================//

#define leiface_cpp

#include "cbase.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lColor.h"
#include "lconvar.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


static int cvar_AllocateDLLIdentifier (lua_State *L) {
  lua_pushinteger(L, cvar->AllocateDLLIdentifier());
  return 1;
}

static int cvar_ConsoleColorPrintf (lua_State *L) {
  cvar->ConsoleColorPrintf(luaL_checkcolor(L, 1), luaL_checkstring(L, 2));
  return 0;
}

static int cvar_ConsoleDPrintf (lua_State *L) {
  cvar->ConsoleDPrintf(luaL_checkstring(L, 1));
  return 0;
}

static int cvar_ConsolePrintf (lua_State *L) {
  cvar->ConsolePrintf(luaL_checkstring(L, 1));
  return 0;
}

static int cvar_FindVar (lua_State *L) {
  lua_pushconvar(L, cvar->FindVar(luaL_checkstring(L, 1)));
  return 1;
}

static int cvar_GetCommandLineValue (lua_State *L) {
  lua_pushstring(L, cvar->GetCommandLineValue(luaL_checkstring(L, 1)));
  return 1;
}

static int cvar_RevertFlaggedConVars (lua_State *L) {
  cvar->RevertFlaggedConVars(luaL_checkint(L, 1));
  return 0;
}


static const luaL_Reg cvarlib[] = {
  {"AllocateDLLIdentifier",   cvar_AllocateDLLIdentifier},
  {"ConsoleColorPrintf",   cvar_ConsoleColorPrintf},
  {"ConsoleDPrintf",   cvar_ConsoleDPrintf},
  {"ConsolePrintf",   cvar_ConsolePrintf},
  {"FindVar",   cvar_FindVar},
  {"GetCommandLineValue",   cvar_GetCommandLineValue},
  {"RevertFlaggedConVars",   cvar_RevertFlaggedConVars},
  {NULL, NULL}
};


void CV_GlobalChange_Lua( IConVar *var, const char *pOldString, float flOldValue )
{
  lua_getglobal(L, "cvar");
  if (lua_istable(L, -1)) {
	lua_getfield(L, -1, "CallGlobalChangeCallbacks");
	if (lua_isfunction(L, -1)) {
	  lua_remove(L, -2);
	  lua_pushconvar(L, cvar->FindVar(var->GetName()));
	  lua_pushstring(L, pOldString);
	  lua_pushnumber(L, flOldValue);
	  luasrc_pcall(L, 3, 0, 0);
	}
	else
	  lua_pop(L, 2);
  }
  else
    lua_pop(L, 1);
}

void InstallGlobalChangeCallbacks( void )
{
	// Install the global cvar callback
	cvar->InstallGlobalChangeCallback( CV_GlobalChange_Lua );
}

void RemoveGlobalChangeCallbacks( void )
{
	// Remove the global cvar callback
	cvar->RemoveGlobalChangeCallback( CV_GlobalChange_Lua );
}


/*
** Open cvar library
*/
LUALIB_API int luaopen_cvar (lua_State *L) {
  luaL_register(L, LUA_CVARLIBNAME, cvarlib);
  InstallGlobalChangeCallbacks();
  return 1;
}

