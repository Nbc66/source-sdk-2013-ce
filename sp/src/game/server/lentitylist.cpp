//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#define lentitylist_cpp

#include "cbase.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lbaseentity_shared.h"
#include "mathlib/lVector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

/*static int gEntList_AddPostClientMessageEntity(lua_State* L) {
  gEntList.AddPostClientMessageEntity(luaL_checkentity(L, 1));
  return 0;
}*/

static int gEntList_CleanupDeleteList (lua_State *L) {
  gEntList.CleanupDeleteList();
  return 0;
}

static int gEntList_Clear (lua_State *L) {
  gEntList.Clear();
  return 0;
}

static int gEntList_FindEntityByClassname (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityByClassname(lua_toentity(L, 1), luaL_checkstring(L, 2)));
  return 1;
}

static int gEntList_FindEntityByClassnameNearest (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityByClassnameNearest(luaL_checkstring(L, 1), luaL_checkvector(L, 2), luaL_checknumber(L, 3)/*, luaL_optint(L, 4, BRUSHPRECISION_NORMAL)*/));
  return 1;
}

static int gEntList_FindEntityByClassnameWithin (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityByClassnameWithin(lua_toentity(L, 1), luaL_checkstring(L, 2), luaL_checkvector(L, 3), luaL_checknumber(L, 4)/*, luaL_optint(L, 5, BRUSHPRECISION_NORMAL)*/));
  return 1;
}

static int gEntList_FindEntityByModel (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityByModel(lua_toentity(L, 1), luaL_checkstring(L, 2)));
  return 1;
}

static int gEntList_FindEntityByName (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityByName(lua_toentity(L, 1), luaL_checkstring(L, 2), luaL_optentity(L, 3, 0), luaL_optentity(L, 4, 0), luaL_optentity(L, 5, 0)));
  return 1;
}

static int gEntList_FindEntityByNameNearest (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityByNameNearest(luaL_checkstring(L, 1), luaL_checkvector(L, 2), luaL_checknumber(L, 3), luaL_optentity(L, 4, 0), luaL_optentity(L, 5, 0), luaL_optentity(L, 6, 0)/*, luaL_optint(L, 7, BRUSHPRECISION_NORMAL)*/));
  return 1;
}

static int gEntList_FindEntityByNameWithin (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityByNameWithin(lua_toentity(L, 1), luaL_checkstring(L, 2), luaL_checkvector(L, 3), luaL_checknumber(L, 4), luaL_optentity(L, 5, 0), luaL_optentity(L, 6, 0), luaL_optentity(L, 7, 0)/*, luaL_optint(L, 7, BRUSHPRECISION_NORMAL)*/));
  return 1;
}

static int gEntList_FindEntityByTarget (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityByTarget(lua_toentity(L, 1), luaL_checkstring(L, 2)));
  return 1;
}

static int gEntList_FindEntityClassNearestFacing (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityClassNearestFacing(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checknumber(L, 3), (char *)luaL_checkstring(L, 4)));
  return 1;
}

static int gEntList_FindEntityGeneric (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityGeneric(lua_toentity(L, 1), luaL_checkstring(L, 2), luaL_optentity(L, 3, 0), luaL_optentity(L, 4, 0), luaL_optentity(L, 5, 0)));
  return 1;
}

static int gEntList_FindEntityGenericNearest (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityGenericNearest(luaL_checkstring(L, 1), luaL_checkvector(L, 2), luaL_checknumber(L, 3), luaL_optentity(L, 4, 0), luaL_optentity(L, 5, 0), luaL_optentity(L, 6, 0)/*, luaL_optint(L, 7, BRUSHPRECISION_NORMAL)*/));
  return 1;
}

static int gEntList_FindEntityGenericWithin (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityGenericWithin(lua_toentity(L, 1), luaL_checkstring(L, 2), luaL_checkvector(L, 3), luaL_checknumber(L, 4), luaL_optentity(L, 5, 0), luaL_optentity(L, 6, 0), luaL_optentity(L, 7, 0)/*, luaL_optint(L, 8, BRUSHPRECISION_NORMAL)*/));
  return 1;
}

static int gEntList_FindEntityInSphere (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityInSphere(lua_toentity(L, 1), luaL_checkvector(L, 2), luaL_checknumber(L, 3)));
  return 1;
}

static int gEntList_FindEntityNearestFacing (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityNearestFacing(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checknumber(L, 3)));
  return 1;
}

static int gEntList_FindEntityProcedural (lua_State *L) {
  lua_pushentity(L, gEntList.FindEntityProcedural(luaL_checkstring(L, 1), luaL_optentity(L, 2, 0), luaL_optentity(L, 3, 0), luaL_optentity(L, 4, 0)));
  return 1;
}

static int gEntList_FirstEnt (lua_State *L) {
  lua_pushentity(L, gEntList.FirstEnt());
  return 1;
}

static int gEntList_IsClearingEntities (lua_State *L) {
  lua_pushboolean(L, gEntList.IsClearingEntities());
  return 1;
}

static int gEntList_NextEnt (lua_State *L) {
  lua_pushentity(L, gEntList.NextEnt(lua_toentity(L, 1)));
  return 1;
}

static int gEntList_NotifyCreateEntity (lua_State *L) {
  gEntList.NotifyCreateEntity(luaL_checkentity(L, 1));
  return 0;
}

static int gEntList_NotifySpawn (lua_State *L) {
  gEntList.NotifySpawn(luaL_checkentity(L, 1));
  return 0;
}

static int gEntList_NumberOfEdicts (lua_State *L) {
  lua_pushinteger(L, gEntList.NumberOfEdicts());
  return 1;
}

static int gEntList_NumberOfEntities (lua_State *L) {
  lua_pushinteger(L, gEntList.NumberOfEntities());
  return 1;
}

/*static int gEntList_PostClientMessagesSent(lua_State* L) {
  gEntList.PostClientMessagesSent();
  return 0;
}*/

static int gEntList_ReportEntityFlagsChanged (lua_State *L) {
  gEntList.ReportEntityFlagsChanged(luaL_checkentity(L, 1), (unsigned int)luaL_checkinteger(L, 2), (unsigned int)luaL_checkinteger(L, 3));
  return 0;
}

static int gEntList_ResetDeleteList (lua_State *L) {
  lua_pushinteger(L, gEntList.ResetDeleteList());
  return 1;
}


static const luaL_Reg gEntListlib[] = {
  //{"AddPostClientMessageEntity",   gEntList_AddPostClientMessageEntity},
  {"CleanupDeleteList",   gEntList_CleanupDeleteList},
  {"Clear",   gEntList_Clear},
  {"FindEntityByClassname",   gEntList_FindEntityByClassname},
  {"FindEntityByClassnameNearest",   gEntList_FindEntityByClassnameNearest},
  {"FindEntityByClassnameWithin",   gEntList_FindEntityByClassnameWithin},
  {"FindEntityByModel",   gEntList_FindEntityByModel},
  {"FindEntityByName",   gEntList_FindEntityByName},
  {"FindEntityByNameNearest",   gEntList_FindEntityByNameNearest},
  {"FindEntityByNameWithin",   gEntList_FindEntityByNameWithin},
  {"FindEntityByTarget",   gEntList_FindEntityByTarget},
  {"FindEntityClassNearestFacing",   gEntList_FindEntityClassNearestFacing},
  {"FindEntityGeneric",   gEntList_FindEntityGeneric},
  {"FindEntityGenericNearest",   gEntList_FindEntityGenericNearest},
  {"FindEntityGenericWithin",   gEntList_FindEntityGenericWithin},
  {"FindEntityInSphere",   gEntList_FindEntityInSphere},
  {"FindEntityNearestFacing",   gEntList_FindEntityNearestFacing},
  {"FindEntityProcedural",   gEntList_FindEntityProcedural},
  {"FirstEnt",   gEntList_FirstEnt},
  {"IsClearingEntities",   gEntList_IsClearingEntities},
  {"NextEnt",   gEntList_NextEnt},
  {"NotifyCreateEntity",   gEntList_NotifyCreateEntity},
  {"NotifySpawn",   gEntList_NotifySpawn},
  {"NumberOfEdicts",   gEntList_NumberOfEdicts},
  {"NumberOfEntities",   gEntList_NumberOfEntities},
  //{"PostClientMessagesSent",   gEntList_PostClientMessagesSent},
  {"ReportEntityFlagsChanged",   gEntList_ReportEntityFlagsChanged},
  {"ResetDeleteList",   gEntList_ResetDeleteList},
  {NULL, NULL}
};


/*
** Open gEntList library
*/
LUALIB_API int luaopen_gEntList (lua_State *L) {
  luaL_register(L, LUA_ENTLISTLIBNAME, gEntListlib);
  return 1;
}

