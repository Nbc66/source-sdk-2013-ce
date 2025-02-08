
//====== Copyright © 1996-2004, Valve Corporation, All rights reserved. =======
//
// Purpose: interface to friends data in Steam
//
//=============================================================================

#define listeamfriends_cpp

#include "cbase.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "listeamfriends.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


/*
** access functions (stack -> C)
*/


LUA_API lua_ISteamFriends *lua_tosteamfriends (lua_State *L, int idx) {
  lua_ISteamFriends **ppSteamFriends = (lua_ISteamFriends **)lua_touserdata(L, idx);
  return *ppSteamFriends;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushsteamfriends (lua_State *L, ISteamFriends *pSteamFriends) {
  if (pSteamFriends == NULL)
    lua_pushnil(L);
  else {
    lua_ISteamFriends **ppSteamFriends = (lua_ISteamFriends **)lua_newuserdata(L, sizeof(pSteamFriends));
    *ppSteamFriends = pSteamFriends;
    luaL_getmetatable(L, "ISteamFriends");
    lua_setmetatable(L, -2);
  }
}


LUALIB_API lua_ISteamFriends *luaL_checksteamfriends (lua_State *L, int narg) {
  lua_ISteamFriends *d = (lua_ISteamFriends *)luaL_checkudata(L, narg, "ISteamFriends");
  return d;
}


static int ISteamFriends_ActivateGameOverlay (lua_State *L) {
  luaL_checksteamfriends(L, 1)->ActivateGameOverlay(luaL_checkstring(L, 2));
  return 0;
}

static int ISteamFriends_GetClanCount (lua_State *L) {
  lua_pushinteger(L, luaL_checksteamfriends(L, 1)->GetClanCount());
  return 1;
}

static int ISteamFriends_GetFriendCount (lua_State *L) {
  lua_pushinteger(L, luaL_checksteamfriends(L, 1)->GetFriendCount(luaL_checkint(L, 2)));
  return 1;
}

static int ISteamFriends_GetPersonaName (lua_State *L) {
  lua_pushstring(L, luaL_checksteamfriends(L, 1)->GetPersonaName());
  return 1;
}

static int ISteamFriends_GetPersonaState (lua_State *L) {
  lua_pushinteger(L, luaL_checksteamfriends(L, 1)->GetPersonaState());
  return 1;
}

static int ISteamFriends_SetPersonaName (lua_State *L) {
  luaL_checksteamfriends(L, 1)->SetPersonaName(luaL_checkstring(L, 2));
  return 0;
}

static int ISteamFriends___tostring (lua_State *L) {
  ISteamFriends *pSteamFriends = luaL_checksteamfriends(L, 1);
  lua_pushfstring(L, "ISteamFriends: %s", pSteamFriends->GetPersonaName());
  return 1;
}


static const luaL_Reg ISteamFriendsmeta[] = {
  {"ActivateGameOverlay", ISteamFriends_ActivateGameOverlay},
  {"GetClanCount", ISteamFriends_GetClanCount},
  {"GetFriendCount", ISteamFriends_GetFriendCount},
  {"GetPersonaName", ISteamFriends_GetPersonaName},
  {"GetPersonaState", ISteamFriends_GetPersonaState},
  {"SetPersonaName", ISteamFriends_SetPersonaName},
  {"__tostring", ISteamFriends___tostring},
  {NULL, NULL}
};


/*
** Open ISteamFriends object
*/
LUALIB_API int luaopen_ISteamFriends (lua_State *L) {
  luaL_newmetatable(L, LUA_STEAMFRIENDSLIBNAME);
  luaL_register(L, NULL, ISteamFriendsmeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "steamfriends");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "steamfriends" */
  return 1;
}

