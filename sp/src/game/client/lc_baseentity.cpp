//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//
#define lc_baseentity_cpp

#include "cbase.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lbaseentity_shared.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


static int CBaseEntity_SpawnClientEntity (lua_State *L) {
  luaL_checkentity(L, 1)->SpawnClientEntity();
  return 0;
}

static int CBaseEntity_Interp_HierarchyUpdateInterpolationAmounts (lua_State *L) {
  luaL_checkentity(L, 1)->Interp_HierarchyUpdateInterpolationAmounts();
  return 0;
}

static int CBaseEntity_Init (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->Init(luaL_checkint(L, 2), luaL_checkint(L, 3)));
  return 1;
}

static int CBaseEntity_Term (lua_State *L) {
  luaL_checkentity(L, 1)->Term();
  return 0;
}

static int CBaseEntity_EnableInToolView (lua_State *L) {
  luaL_checkentity(L, 1)->EnableInToolView(luaL_checkboolean(L, 2));
  return 0;
}

static int CBaseEntity_IsEnabledInToolView (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsEnabledInToolView());
  return 1;
}

static int CBaseEntity_SetToolRecording (lua_State *L) {
  luaL_checkentity(L, 1)->SetToolRecording(luaL_checkboolean(L, 2));
  return 0;
}

static int CBaseEntity_IsToolRecording (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsToolRecording());
  return 1;
}

static int CBaseEntity_HasRecordedThisFrame (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->HasRecordedThisFrame());
  return 1;
}

static int CBaseEntity_RecordToolMessage (lua_State *L) {
  luaL_checkentity(L, 1)->RecordToolMessage();
  return 0;
}

static int CBaseEntity_DontRecordInTools (lua_State *L) {
  luaL_checkentity(L, 1)->DontRecordInTools();
  return 0;
}

static int CBaseEntity_ShouldRecordInTools (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->ShouldRecordInTools());
  return 1;
}

static int CBaseEntity_Release (lua_State *L) {
  luaL_checkentity(L, 1)->Release();
  return 0;
}

static int CBaseEntity_GetRenderOrigin (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->GetRenderOrigin();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_GetRenderAngles (lua_State *L) {
  QAngle v = luaL_checkentity(L, 1)->GetRenderAngles();
  lua_pushangle(L, v);
  return 1;
}

static int CBaseEntity_GetObserverCamOrigin (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->GetObserverCamOrigin();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_IsTwoPass (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsTwoPass());
  return 1;
}

static int CBaseEntity_UsesPowerOfTwoFrameBufferTexture (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->UsesPowerOfTwoFrameBufferTexture());
  return 1;
}

static int CBaseEntity_UsesFullFrameBufferTexture (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->UsesFullFrameBufferTexture());
  return 1;
}

static int CBaseEntity_DrawModel (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->DrawModel(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseEntity_ComputeFxBlend (lua_State *L) {
  luaL_checkentity(L, 1)->ComputeFxBlend();
  return 0;
}

static int CBaseEntity_GetFxBlend (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetFxBlend());
  return 1;
}

static int CBaseEntity_LODTest (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->LODTest());
  return 1;
}

static int CBaseEntity_SetNextClientThink (lua_State *L) {
  luaL_checkentity(L, 1)->SetNextClientThink(luaL_checknumber(L, 2));
  return 0;
}


static const luaL_Reg CBaseEntitymeta[] = {
  {"SpawnClientEntity", CBaseEntity_SpawnClientEntity},
  {"Interp_HierarchyUpdateInterpolationAmounts", CBaseEntity_Interp_HierarchyUpdateInterpolationAmounts},
  {"Init", CBaseEntity_Init},
  {"Term", CBaseEntity_Term},
  {"EnableInToolView", CBaseEntity_EnableInToolView},
  {"IsEnabledInToolView", CBaseEntity_IsEnabledInToolView},
  {"SetToolRecording", CBaseEntity_SetToolRecording},
  {"IsToolRecording", CBaseEntity_IsToolRecording},
  {"HasRecordedThisFrame", CBaseEntity_HasRecordedThisFrame},
  {"RecordToolMessage", CBaseEntity_RecordToolMessage},
  {"DontRecordInTools", CBaseEntity_DontRecordInTools},
  {"ShouldRecordInTools", CBaseEntity_ShouldRecordInTools},
  {"Release", CBaseEntity_Release},
  {"GetRenderOrigin", CBaseEntity_GetRenderOrigin},
  {"GetRenderAngles", CBaseEntity_GetRenderAngles},
  {"GetObserverCamOrigin", CBaseEntity_GetObserverCamOrigin},
  {"IsTwoPass", CBaseEntity_IsTwoPass},
  {"UsesPowerOfTwoFrameBufferTexture", CBaseEntity_UsesPowerOfTwoFrameBufferTexture},
  {"UsesFullFrameBufferTexture", CBaseEntity_UsesFullFrameBufferTexture},
  {"DrawModel", CBaseEntity_DrawModel},
  {"ComputeFxBlend", CBaseEntity_ComputeFxBlend},
  {"GetFxBlend", CBaseEntity_GetFxBlend},
  {"LODTest", CBaseEntity_LODTest},
  {"SetNextClientThink", CBaseEntity_SetNextClientThink},
  {NULL, NULL}
};


/*
** Open CBaseEntity object
*/
LUALIB_API int luaopen_CBaseEntity (lua_State *L) {
  luaL_getmetatable(L, LUA_BASEENTITYLIBNAME);
  if (lua_isnoneornil(L, -1)) {
    lua_pop(L, 1);
    luaL_newmetatable(L, LUA_BASEENTITYLIBNAME);
  }
  luaL_register(L, NULL, CBaseEntitymeta);
  return 1;
}

