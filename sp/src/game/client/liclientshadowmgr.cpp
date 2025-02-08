//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//

#define liclientshadowmgr_cpp

#include "cbase.h"
#include "luamanager.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"



static int g_pClientShadowMgr_AdvanceFrame (lua_State *L) {
  g_pClientShadowMgr->AdvanceFrame();
  return 0;
}

static int g_pClientShadowMgr_GetShadowDirection (lua_State *L) {
  Vector v = g_pClientShadowMgr->GetShadowDirection();
  lua_pushvector(L, v);
  return 1;
}

static int g_pClientShadowMgr_RenderShadowTexture (lua_State *L) {
  g_pClientShadowMgr->RenderShadowTexture(luaL_checkint(L, 1), luaL_checkint(L, 2));
  return 0;
}

static int g_pClientShadowMgr_SetShadowBlobbyCutoffArea (lua_State *L) {
  g_pClientShadowMgr->SetShadowBlobbyCutoffArea(luaL_checknumber(L, 1));
  return 0;
}

static int g_pClientShadowMgr_SetShadowColor (lua_State *L) {
  g_pClientShadowMgr->SetShadowColor(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3));
  return 0;
}

static int g_pClientShadowMgr_SetShadowDirection (lua_State *L) {
  g_pClientShadowMgr->SetShadowDirection(luaL_checkvector(L, 1));
  return 0;
}

static int g_pClientShadowMgr_SetShadowDistance (lua_State *L) {
  g_pClientShadowMgr->SetShadowDistance(luaL_checknumber(L, 1));
  return 0;
}

static int g_pClientShadowMgr_SetShadowsDisabled (lua_State *L) {
  g_pClientShadowMgr->SetShadowsDisabled(luaL_checkboolean(L, 1));
  return 0;
}

static int g_pClientShadowMgr_UnlockAllShadowDepthTextures (lua_State *L) {
  g_pClientShadowMgr->UnlockAllShadowDepthTextures();
  return 0;
}


static const luaL_Reg g_pClientShadowMgrlib[] = {
  {"AdvanceFrame",   g_pClientShadowMgr_AdvanceFrame},
  {"GetShadowDirection",   g_pClientShadowMgr_GetShadowDirection},
  {"RenderShadowTexture",   g_pClientShadowMgr_RenderShadowTexture},
  {"SetShadowBlobbyCutoffArea",   g_pClientShadowMgr_SetShadowBlobbyCutoffArea},
  {"SetShadowColor",   g_pClientShadowMgr_SetShadowColor},
  {"SetShadowDirection",   g_pClientShadowMgr_SetShadowDirection},
  {"SetShadowDistance",   g_pClientShadowMgr_SetShadowDistance},
  {"UnlockAllShadowDepthTextures",   g_pClientShadowMgr_UnlockAllShadowDepthTextures},
  {NULL, NULL}
};


/*
** Open g_pClientShadowMgr library
*/
LUALIB_API int luaopen_g_pClientShadowMgr (lua_State *L) {
  luaL_register(L, "g_pClientShadowMgr", g_pClientShadowMgrlib);
  return 1;
}

