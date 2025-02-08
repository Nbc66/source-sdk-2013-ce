//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#define lnetworkstringtabledefs_cpp

#include "cbase.h"
#include "networkstringtabledefs.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lnetworkstringtabledefs.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


/*
** access functions (stack -> C)
*/


LUA_API lua_INetworkStringTable *lua_tostringtable (lua_State *L, int idx) {
  lua_INetworkStringTable **ppNetworkStringTable = (lua_INetworkStringTable **)lua_touserdata(L, idx);
  return *ppNetworkStringTable;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushstringtable (lua_State *L, lua_INetworkStringTable *pNetworkStringTable) {
  if (pNetworkStringTable == NULL)
    lua_pushnil(L);
  else {
    lua_INetworkStringTable **ppNetworkStringTable = (lua_INetworkStringTable **)lua_newuserdata(L, sizeof(pNetworkStringTable));
    *ppNetworkStringTable = pNetworkStringTable;
    luaL_getmetatable(L, "INetworkStringTable");
    lua_setmetatable(L, -2);
  }
}


LUALIB_API lua_INetworkStringTable *luaL_checkstringtable (lua_State *L, int narg) {
  lua_INetworkStringTable **d = (lua_INetworkStringTable **)luaL_checkudata(L, narg, "INetworkStringTable");
  return *d;
}


static int INetworkStringTable_AddString (lua_State *L) {
  lua_pushinteger(L, luaL_checkstringtable(L, 1)->AddString(luaL_checkboolean(L, 2), luaL_checkstring(L, 3)));
  return 1;
}

static int INetworkStringTable_ChangedSinceTick (lua_State *L) {
  lua_pushboolean(L, luaL_checkstringtable(L, 1)->ChangedSinceTick(luaL_checkint(L, 2)));
  return 1;
}

static int INetworkStringTable_FindStringIndex (lua_State *L) {
  lua_pushinteger(L, luaL_checkstringtable(L, 1)->FindStringIndex(luaL_checkstring(L, 2)));
  return 1;
}

static int INetworkStringTable_GetEntryBits (lua_State *L) {
  lua_pushinteger(L, luaL_checkstringtable(L, 1)->GetEntryBits());
  return 1;
}

static int INetworkStringTable_GetMaxStrings (lua_State *L) {
  lua_pushinteger(L, luaL_checkstringtable(L, 1)->GetMaxStrings());
  return 1;
}

static int INetworkStringTable_GetNumStrings (lua_State *L) {
  lua_pushinteger(L, luaL_checkstringtable(L, 1)->GetNumStrings());
  return 1;
}

static int INetworkStringTable_GetString (lua_State *L) {
  lua_pushstring(L, luaL_checkstringtable(L, 1)->GetString(luaL_checkint(L, 2)));
  return 1;
}

static int INetworkStringTable_GetTableId (lua_State *L) {
  lua_pushinteger(L, luaL_checkstringtable(L, 1)->GetTableId());
  return 1;
}

static int INetworkStringTable_GetTableName (lua_State *L) {
  lua_pushstring(L, luaL_checkstringtable(L, 1)->GetTableName());
  return 1;
}

static int INetworkStringTable_SetStringUserData (lua_State *L) {
  luaL_checkstringtable(L, 1)->SetStringUserData(luaL_checkint(L, 2), strlen( luaL_checkstring(L, 3) ) + 1, luaL_checkstring(L, 3));
  return 0;
}

static int INetworkStringTable_SetTick (lua_State *L) {
  luaL_checkstringtable(L, 1)->SetTick(luaL_checkint(L, 2));
  return 0;
}

static int INetworkStringTable___tostring (lua_State *L) {
  INetworkStringTable *pNetworkStringTable = luaL_checkstringtable(L, 1);
  lua_pushfstring(L, "INetworkStringTable: %s", pNetworkStringTable->GetTableName());
  return 1;
}


static const luaL_Reg INetworkStringTablemeta[] = {
  {"AddString", INetworkStringTable_AddString},
  {"ChangedSinceTick", INetworkStringTable_ChangedSinceTick},
  {"FindStringIndex", INetworkStringTable_FindStringIndex},
  {"GetEntryBits", INetworkStringTable_GetEntryBits},
  {"GetMaxStrings", INetworkStringTable_GetMaxStrings},
  {"GetNumStrings", INetworkStringTable_GetNumStrings},
  {"GetString", INetworkStringTable_GetString},
  {"GetTableId", INetworkStringTable_GetTableId},
  {"GetTableName", INetworkStringTable_GetTableName},
  {"SetStringUserData", INetworkStringTable_SetStringUserData},
  {"SetTick", INetworkStringTable_SetTick},
  {"__tostring", INetworkStringTable___tostring},
  {NULL, NULL}
};


/*
** Open INetworkStringTable object
*/
LUALIB_API int luaopen_INetworkStringTable (lua_State *L) {
  luaL_newmetatable(L, LUA_INETWORKSTRINGTABLELIBNAME);
  luaL_register(L, NULL, INetworkStringTablemeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "networkstringtable");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "effect" */
  return 1;
}


// Engine interfaces.
extern INetworkStringTableContainer *networkstringtable;

static int networkstringtable_CreateStringTable (lua_State *L) {
  networkstringtable->CreateStringTable(luaL_checkstring(L, 1), luaL_checkint(L, 2), luaL_optint(L, 3, 0), luaL_optint(L, 4, 0));
  return 0;
}

static int networkstringtable_CreateStringTableEx (lua_State *L) {
  lua_pushstringtable(L, networkstringtable->CreateStringTableEx(luaL_checkstring(L, 1), luaL_checkint(L, 2), luaL_optint(L, 3, 0), luaL_optint(L, 4, 0), luaL_optboolean(L, 5, 0)));
  return 1;
}

static int networkstringtable_FindTable (lua_State *L) {
  lua_pushstringtable(L, networkstringtable->FindTable(luaL_checkstring(L, 1)));
  return 1;
}

static int networkstringtable_GetNumTables (lua_State *L) {
  lua_pushinteger(L, networkstringtable->GetNumTables());
  return 1;
}

static int networkstringtable_GetTable (lua_State *L) {
  lua_pushstringtable(L, networkstringtable->GetTable(luaL_checkint(L, 1)));
  return 1;
}

static int networkstringtable_RemoveAllTables (lua_State *L) {
  networkstringtable->RemoveAllTables();
  return 0;
}

static int networkstringtable_SetAllowClientSideAddString (lua_State *L) {
  networkstringtable->SetAllowClientSideAddString(luaL_checkstringtable(L, 1), luaL_checkboolean(L, 2));
  return 0;
}


static const luaL_Reg networkstringtablelib[] = {
  {"CreateStringTable",   networkstringtable_CreateStringTable},
  {"CreateStringTableEx",   networkstringtable_CreateStringTableEx},
  {"FindTable",   networkstringtable_FindTable},
  {"GetNumTables",   networkstringtable_GetNumTables},
  {"GetTable",   networkstringtable_GetTable},
  {"RemoveAllTables",   networkstringtable_RemoveAllTables},
  {"SetAllowClientSideAddString",   networkstringtable_SetAllowClientSideAddString},
  {NULL, NULL}
};


/*
** Open networkstringtable library
*/
LUALIB_API int luaopen_networkstringtable (lua_State *L) {
  luaL_register(L, LUA_NETWORKSTRINGTABLELIBNAME, networkstringtablelib);
  return 1;
}

