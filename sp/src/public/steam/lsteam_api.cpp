//====== Copyright © 1996-2004, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#define lsteam_api_cpp

#include "cbase.h"
#include "steam_api.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "listeamfriends.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static int steamapicontext_SteamFriends (lua_State *L) {
  lua_pushsteamfriends(L, steamapicontext->SteamFriends());
  return 1;
}


static const luaL_Reg steamapicontextlib[] = {
  {"SteamFriends",   steamapicontext_SteamFriends},
  {NULL, NULL}
};


/*
** Open steamapicontext library
*/
LUALIB_API int luaopen_steamapicontext (lua_State *L) {
  luaL_register(L, LUA_STEAMAPICONTEXTLIBNAME, steamapicontextlib);
  return 1;
}

