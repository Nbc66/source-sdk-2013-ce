//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $NoKeywords: $
//===========================================================================//

#define liconvar_cpp

#include "cbase.h"
#include "luamanager.h"
#include "luasrclib.h"


/*
** Open FCVAR library
*/
LUALIB_API int luaopen_FCVAR (lua_State *L) {
  BEGIN_LUA_SET_ENUM_LIB(L, LUA_FCVARLIBNAME);
    lua_pushenum(L, FCVAR_NONE, "NONE");

    lua_pushenum(L, FCVAR_UNREGISTERED, "UNREGISTERED");
    lua_pushenum(L, FCVAR_DEVELOPMENTONLY, "DEVELOPMENTONLY");
    lua_pushenum(L, FCVAR_GAMEDLL, "GAMEDLL");
    lua_pushenum(L, FCVAR_CLIENTDLL, "CLIENTDLL");
    lua_pushenum(L, FCVAR_HIDDEN, "HIDDEN");

    lua_pushenum(L, FCVAR_PROTECTED, "PROTECTED");
    lua_pushenum(L, FCVAR_SPONLY, "SPONLY");
    lua_pushenum(L, FCVAR_ARCHIVE, "ARCHIVE");
    lua_pushenum(L, FCVAR_NOTIFY, "NOTIFY");
    lua_pushenum(L, FCVAR_USERINFO, "USERINFO");
    lua_pushenum(L, FCVAR_CHEAT, "CHEAT");

    lua_pushenum(L, FCVAR_PRINTABLEONLY, "PRINTABLEONLY");
    lua_pushenum(L, FCVAR_UNLOGGED, "UNLOGGED");
    lua_pushenum(L, FCVAR_NEVER_AS_STRING, "NEVER_AS_STRING");

	lua_pushenum(L, FCVAR_REPLICATED, "REPLICATED");
	lua_pushenum(L, FCVAR_DEMO, "DEMO");
	lua_pushenum(L, FCVAR_DONTRECORD, "DONTRECORD");

	lua_pushenum(L, FCVAR_NOT_CONNECTED, "NOT_CONNECTED");

	lua_pushenum(L, FCVAR_ARCHIVE_XBOX, "ARCHIVE_XBOX");
	lua_pushenum(L, FCVAR_SERVER_CAN_EXECUTE, "SERVER_CAN_EXECUTE");
	lua_pushenum(L, FCVAR_SERVER_CANNOT_QUERY, "SERVER_CANNOT_QUERY");
	lua_pushenum(L, FCVAR_CLIENTCMD_CAN_EXECUTE, "CLIENTCMD_CAN_EXECUTE");
  END_LUA_SET_ENUM_LIB(L);
  return 0;
}
