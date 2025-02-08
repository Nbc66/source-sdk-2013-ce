//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#define lrecipientfilter_cpp

#include "cbase.h"
#include "recipientfilter.h"
#include "luamanager.h"
#include "luasrclib.h"

#ifdef CLIENT
#else
#include "lrecipientfilter.h"
#endif

#include "lbaseplayer_shared.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"



static lua_CRecipientFilter *s_pFilter = new CRecipientFilter();
static lua_CPASFilter *s_pPASFilter = new CPASFilter();

/*
** access functions (stack -> C)
*/


LUA_API lua_CRecipientFilter &(lua_torecipientfilter) (lua_State *L, int idx) {
  lua_CRecipientFilter **ppFilter = (lua_CRecipientFilter **)lua_touserdata(L, idx);
  return **ppFilter;
}


LUA_API lua_CPASFilter &(lua_topasfilter) (lua_State *L, int idx) {
  lua_CPASFilter **ppFilter = (lua_CPASFilter **)lua_touserdata(L, idx);
  return **ppFilter;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushrecipientfilter (lua_State *L, lua_CRecipientFilter &filter) {
  lua_CRecipientFilter **ppFilter = (lua_CRecipientFilter **)lua_newuserdata(L, sizeof(lua_CRecipientFilter));
  s_pFilter->Reset();
  s_pFilter->CopyFrom(filter);
  *ppFilter = s_pFilter;
  luaL_getmetatable(L, "CRecipientFilter");
  lua_setmetatable(L, -2);
}


LUA_API void lua_pushpasfilter (lua_State *L, lua_CPASFilter &filter) {
  lua_CPASFilter **ppFilter = (lua_CPASFilter **)lua_newuserdata(L, sizeof(lua_CPASFilter));
  s_pPASFilter->Reset();
  s_pPASFilter->CopyFrom(filter);
  *ppFilter = s_pPASFilter;
  luaL_getmetatable(L, "CPASFilter");
  lua_setmetatable(L, -2);
}




LUALIB_API lua_CRecipientFilter &(luaL_checkrecipientfilter) (lua_State *L, int narg) {
  lua_CRecipientFilter *d = (lua_CRecipientFilter *)lua_touserdata(L, narg);
  if (!d)
    luaL_typerror(L, narg, "CRecipientFilter");
  return **(lua_CRecipientFilter **)d;
}


LUALIB_API lua_CPASFilter &(luaL_checkpasfilter) (lua_State *L, int narg) {
  lua_CPASFilter **d = (lua_CPASFilter **)luaL_checkudata(L, narg, "CPASFilter");
  return **d;
}


static int CRecipientFilter_AddAllPlayers (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).AddAllPlayers();
  return 0;
}

static int CRecipientFilter_AddRecipient (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).AddRecipient(luaL_checkplayer(L, 2));
  return 0;
}

static int CRecipientFilter_AddRecipientsByPAS (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).AddRecipientsByPAS(luaL_checkvector(L, 2));
  return 0;
}

static int CRecipientFilter_AddRecipientsByPVS (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).AddRecipientsByPVS(luaL_checkvector(L, 2));
  return 0;
}

static int CRecipientFilter_CopyFrom (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).CopyFrom(luaL_checkrecipientfilter(L, 2));
  return 0;
}

static int CRecipientFilter_GetRecipientCount (lua_State *L) {
  lua_pushinteger(L, luaL_checkrecipientfilter(L, 1).GetRecipientCount());
  return 1;
}

static int CRecipientFilter_GetRecipientIndex (lua_State *L) {
  lua_pushinteger(L, luaL_checkrecipientfilter(L, 1).GetRecipientIndex(luaL_checkint(L, 2)));
  return 1;
}

static int CRecipientFilter_IgnorePredictionCull (lua_State *L) {
  lua_pushboolean(L, luaL_checkrecipientfilter(L, 1).IgnorePredictionCull());
  return 1;
}

static int CRecipientFilter_IsInitMessage (lua_State *L) {
  lua_pushboolean(L, luaL_checkrecipientfilter(L, 1).IsInitMessage());
  return 1;
}

static int CRecipientFilter_IsReliable (lua_State *L) {
  lua_pushboolean(L, luaL_checkrecipientfilter(L, 1).IsReliable());
  return 1;
}

static int CRecipientFilter_IsUsingPredictionRules (lua_State *L) {
  lua_pushboolean(L, luaL_checkrecipientfilter(L, 1).IsUsingPredictionRules());
  return 1;
}

static int CRecipientFilter_MakeInitMessage (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).MakeInitMessage();
  return 0;
}

static int CRecipientFilter_MakeReliable (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).MakeReliable();
  return 0;
}

static int CRecipientFilter_RemoveAllRecipients (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).RemoveAllRecipients();
  return 0;
}

static int CRecipientFilter_RemoveRecipient (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).RemoveRecipient(luaL_checkplayer(L, 2));
  return 0;
}

static int CRecipientFilter_RemoveRecipientByPlayerIndex (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).RemoveRecipientByPlayerIndex(luaL_checkint(L, 2));
  return 0;
}

static int CRecipientFilter_RemoveRecipientsByPVS (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).RemoveRecipientsByPVS(luaL_checkvector(L, 2));
  return 0;
}

static int CRecipientFilter_Reset (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).Reset();
  return 0;
}

static int CRecipientFilter_SetIgnorePredictionCull (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).SetIgnorePredictionCull(luaL_checkboolean(L, 2));
  return 0;
}

static int CRecipientFilter_UsePredictionRules (lua_State *L) {
  luaL_checkrecipientfilter(L, 1).UsePredictionRules();
  return 0;
}

static int CRecipientFilter___tostring (lua_State *L) {
  lua_pushfstring(L, "CRecipientFilter: %p", luaL_checkudata(L, 1, "CRecipientFilter"));
  return 1;
}


static const luaL_Reg CRecipientFiltermeta[] = {
  {"AddAllPlayers", CRecipientFilter_AddAllPlayers},
  {"AddRecipient", CRecipientFilter_AddRecipient},
  {"AddRecipientsByPAS", CRecipientFilter_AddRecipientsByPAS},
  {"AddRecipientsByPVS", CRecipientFilter_AddRecipientsByPVS},
  {"CopyFrom", CRecipientFilter_CopyFrom},
  {"GetRecipientCount", CRecipientFilter_GetRecipientCount},
  {"GetRecipientIndex", CRecipientFilter_GetRecipientIndex},
  {"IgnorePredictionCull", CRecipientFilter_IgnorePredictionCull},
  {"IsInitMessage", CRecipientFilter_IsInitMessage},
  {"IsReliable", CRecipientFilter_IsReliable},
  {"IsUsingPredictionRules", CRecipientFilter_IsUsingPredictionRules},
  {"MakeInitMessage", CRecipientFilter_MakeInitMessage},
  {"MakeReliable", CRecipientFilter_MakeReliable},
  {"RemoveAllRecipients", CRecipientFilter_RemoveAllRecipients},
  {"RemoveRecipient", CRecipientFilter_RemoveRecipient},
  {"RemoveRecipientByPlayerIndex", CRecipientFilter_RemoveRecipientByPlayerIndex},
  {"RemoveRecipientsByPVS", CRecipientFilter_RemoveRecipientsByPVS},
  {"Reset", CRecipientFilter_Reset},
  {"SetIgnorePredictionCull", CRecipientFilter_SetIgnorePredictionCull},
  {"UsePredictionRules", CRecipientFilter_UsePredictionRules},
  {"__tostring", CRecipientFilter___tostring},
  {NULL, NULL}
};


static int luasrc_CRecipientFilter (lua_State *L) {
  CRecipientFilter filter;
  lua_pushrecipientfilter(L, filter);
  return 1;
}


static const luaL_Reg CRecipientFilter_funcs[] = {
  {"CRecipientFilter", luasrc_CRecipientFilter},
  {NULL, NULL}
};


/*
** Open CRecipientFilter object
*/
LUALIB_API int luaopen_CRecipientFilter (lua_State *L) {
  luaL_newmetatable(L, LUA_RECIPIENTFILTERLIBNAME);
  luaL_register(L, NULL, CRecipientFiltermeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "recipientfilter");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "recipientfilter" */
  luaL_register(L, "_G", CRecipientFilter_funcs);
  lua_pop(L, 1);
  return 1;
}


static int CPASFilter___index (lua_State *L) {
  lua_getmetatable(L, 1);
  lua_pushvalue(L, 2);
  lua_gettable(L, -2);
  if (lua_isnil(L, -1)) {
    lua_pop(L, 2);
    luaL_getmetatable(L, "CRecipientFilter");
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
  }
  return 1;
}

static int CPASFilter___tostring (lua_State *L) {
  lua_pushfstring(L, "CPASFilter: %p", luaL_checkudata(L, 1, "CPASFilter"));
  return 1;
}


static const luaL_Reg CPASFiltermeta[] = {
  {"__index", CPASFilter___index},
  {"__tostring", CPASFilter___tostring},
  {NULL, NULL}
};


static int luasrc_CPASFilter (lua_State *L) {
  CPASFilter filter(luaL_checkvector(L, 1));
  lua_pushpasfilter(L, filter);
  return 1;
}


static const luaL_Reg CPASFilter_funcs[] = {
  {"CPASFilter", luasrc_CPASFilter},
  {NULL, NULL}
};


/*
** Open CPASFilter object
*/
LUALIB_API int luaopen_CPASFilter (lua_State *L) {
  luaL_newmetatable(L, LUA_PASFILTERLIBNAME);
  luaL_register(L, NULL, CPASFiltermeta);
  lua_pushstring(L, "recipientfilter");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "recipientfilter" */
  luaL_register(L, "_G", CPASFilter_funcs);
  lua_pop(L, 1);
  return 1;
}