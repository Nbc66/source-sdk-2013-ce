//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#define lgametrace_cpp

#include "cbase.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lgametrace.h"
#include "lcmodel.h"
#include "lbaseentity_shared.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


/*
** access functions (stack -> C)
*/


LUA_API lua_CGameTrace &lua_totrace (lua_State *L, int idx) {
  lua_CGameTrace *tr = (lua_CGameTrace *)lua_touserdata(L, idx);
  return *tr;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushtrace (lua_State *L, lua_CGameTrace &tr) {
  lua_CGameTrace *ptr = (lua_CGameTrace *)lua_newuserdata(L, sizeof(lua_CGameTrace));
  *ptr = tr;
  luaL_getmetatable(L, "CGameTrace");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_CGameTrace &luaL_checktrace (lua_State *L, int narg) {
  lua_CGameTrace *d = (lua_CGameTrace *)luaL_checkudata(L, narg, "CGameTrace");
  return *d;
}


static int CGameTrace_DidHit (lua_State *L) {
  lua_pushboolean(L, luaL_checktrace(L, 1).DidHit());
  return 1;
}

static int CGameTrace_DidHitNonWorldEntity (lua_State *L) {
  lua_pushboolean(L, luaL_checktrace(L, 1).DidHitNonWorldEntity());
  return 1;
}

static int CGameTrace_DidHitWorld (lua_State *L) {
  lua_pushboolean(L, luaL_checktrace(L, 1).DidHitWorld());
  return 1;
}

static int CGameTrace_GetEntityIndex (lua_State *L) {
  lua_pushinteger(L, luaL_checktrace(L, 1).GetEntityIndex());
  return 1;
}

static int CGameTrace_IsDispSurface (lua_State *L) {
  lua_pushboolean(L, luaL_checktrace(L, 1).IsDispSurface());
  return 1;
}

static int CGameTrace_IsDispSurfaceBuildable (lua_State *L) {
  lua_pushboolean(L, luaL_checktrace(L, 1).IsDispSurfaceBuildable());
  return 1;
}

static int CGameTrace_IsDispSurfaceProp1 (lua_State *L) {
  lua_pushboolean(L, luaL_checktrace(L, 1).IsDispSurfaceProp1());
  return 1;
}

static int CGameTrace_IsDispSurfaceProp2 (lua_State *L) {
  lua_pushboolean(L, luaL_checktrace(L, 1).IsDispSurfaceProp2());
  return 1;
}

static int CGameTrace_IsDispSurfaceWalkable (lua_State *L) {
  lua_pushboolean(L, luaL_checktrace(L, 1).IsDispSurfaceWalkable());
  return 1;
}

static int CGameTrace___index (lua_State *L) {
    trace_t tr;
    tr = luaL_checktrace(L, 1);
  const char *field = luaL_checkstring(L, 2);
  if (Q_strcmp(field, "allsolid") == 0)
    lua_pushboolean(L, tr.allsolid);
  else if (Q_strcmp(field, "contents") == 0)
    lua_pushinteger(L, tr.contents);
  else if (Q_strcmp(field, "dispFlags") == 0)
    lua_pushinteger(L, tr.dispFlags);
  else if (Q_strcmp(field, "endpos") == 0)
    lua_pushvector(L, tr.endpos);
  else if (Q_strcmp(field, "fraction") == 0)
    lua_pushnumber(L, tr.fraction);
  else if (Q_strcmp(field, "fractionleftsolid") == 0)
    lua_pushnumber(L, tr.fractionleftsolid);
  else if (Q_strcmp(field, "hitbox") == 0)
    lua_pushinteger(L, tr.hitbox);
  else if (Q_strcmp(field, "hitgroup") == 0)
    lua_pushinteger(L, tr.hitgroup);
  else if (Q_strcmp(field, "m_pEnt") == 0)
    lua_pushentity(L, tr.m_pEnt);
  else if (Q_strcmp(field, "physicsbone") == 0)
    lua_pushinteger(L, tr.physicsbone);
  else if (Q_strcmp(field, "startpos") == 0)
    lua_pushvector(L, tr.startpos);
  else if (Q_strcmp(field, "startsolid") == 0)
    lua_pushboolean(L, tr.startsolid);
  else if (Q_strcmp(field, "surface") == 0)
    lua_pushcsurface(L, tr.surface);
  else {
    lua_getmetatable(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
  }
  return 1;
}

static int CGameTrace___newindex (lua_State *L) {
  const char *field = luaL_checkstring(L, 2);
  if (Q_strcmp(field, "allsolid") == 0)
    luaL_checktrace(L, 1).allsolid = luaL_checkboolean(L, 3);
  else if (Q_strcmp(field, "contents") == 0)
    luaL_checktrace(L, 1).contents = luaL_checkint(L, 3);
  else if (Q_strcmp(field, "dispFlags") == 0)
    luaL_checktrace(L, 1).dispFlags = luaL_checkint(L, 3);
  else if (Q_strcmp(field, "endpos") == 0)
    luaL_checktrace(L, 1).endpos = luaL_checkvector(L, 3);
  else if (Q_strcmp(field, "fraction") == 0)
    luaL_checktrace(L, 1).fraction = luaL_checknumber(L, 3);
  else if (Q_strcmp(field, "fractionleftsolid") == 0)
    luaL_checktrace(L, 1).fractionleftsolid = luaL_checknumber(L, 3);
  else if (Q_strcmp(field, "hitbox") == 0)
    luaL_checktrace(L, 1).hitbox = luaL_checkint(L, 3);
  else if (Q_strcmp(field, "hitgroup") == 0)
    luaL_checktrace(L, 1).hitgroup = luaL_checkint(L, 3);
  else if (Q_strcmp(field, "m_pEnt") == 0)
    luaL_checktrace(L, 1).m_pEnt = lua_toentity(L, 3);
  else if (Q_strcmp(field, "physicsbone") == 0)
    luaL_checktrace(L, 1).physicsbone = luaL_checkint(L, 3);
  else if (Q_strcmp(field, "startpos") == 0)
    luaL_checktrace(L, 1).startpos = luaL_checkvector(L, 3);
  else if (Q_strcmp(field, "startsolid") == 0)
    luaL_checktrace(L, 1).startsolid = luaL_checkboolean(L, 3);
  return 0;
}

static int CGameTrace___tostring (lua_State *L) {
  lua_pushfstring(L, "CGameTrace: %p", luaL_checkudata(L, 1, "CGameTrace"));
  return 1;
}


static const luaL_Reg CGameTracemeta[] = {
  {"DidHit", CGameTrace_DidHit},
  {"DidHitNonWorldEntity", CGameTrace_DidHitNonWorldEntity},
  {"DidHitWorld", CGameTrace_DidHitWorld},
  {"GetEntityIndex", CGameTrace_GetEntityIndex},
  {"IsDispSurface", CGameTrace_IsDispSurface},
  {"IsDispSurfaceBuildable", CGameTrace_IsDispSurfaceBuildable},
  {"IsDispSurfaceProp1", CGameTrace_IsDispSurfaceProp1},
  {"IsDispSurfaceProp2", CGameTrace_IsDispSurfaceProp2},
  {"IsDispSurfaceWalkable", CGameTrace_IsDispSurfaceWalkable},
  {"__index", CGameTrace___index},
  {"__newindex", CGameTrace___newindex},
  {"__tostring", CGameTrace___tostring},
  {NULL, NULL}
};


static int luasrc_trace_t (lua_State *L) {
  trace_t tr;
  memset( &tr, 0, sizeof( trace_t ) );
  lua_pushtrace(L, tr);
  return 1;
}


static const luaL_Reg CGameTrace_funcs[] = {
  {"trace_t", luasrc_trace_t},
  {NULL, NULL}
};


/*
** Open CGameTrace object
*/
LUALIB_API int luaopen_CGameTrace (lua_State *L) {
  luaL_newmetatable(L, LUA_GAMETRACELIBNAME);
  luaL_register(L, NULL, CGameTracemeta);
  lua_pushstring(L, "trace");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "trace" */
  luaL_register(L, "_G", CGameTrace_funcs);
  lua_pop(L, 1);
  return 1;
}

