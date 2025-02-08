//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
//
//  cdll_int.h
//
// 4-23-98  
// JOHN:  client dll interface declarations
//

#define lglobalvars_base_cpp

#include "cbase.h"
#include "engine/ivdebugoverlay.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "mathlib/lvector.h"
#include "lColor.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"



static int debugoverlay_AddBoxOverlay (lua_State *L) {
  debugoverlay->AddBoxOverlay(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_checkangle(L, 4), luaL_checkint(L, 5), luaL_checkint(L, 6), luaL_checkint(L, 7), luaL_checkint(L, 8), luaL_checknumber(L, 9));
  return 0;
}

static int debugoverlay_AddBoxOverlay2 (lua_State *L) {
  debugoverlay->AddBoxOverlay2(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_checkangle(L, 4), luaL_checkcolor(L, 5), luaL_checkcolor(L, 6), luaL_checknumber(L, 7));
  return 0;
}

static int debugoverlay_AddGridOverlay (lua_State *L) {
  debugoverlay->AddGridOverlay(luaL_checkvector(L, 1));
  return 0;
}

static int debugoverlay_AddLineOverlay (lua_State *L) {
  debugoverlay->AddLineOverlay(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkboolean(L, 6), luaL_checknumber(L, 7));
  return 0;
}

static int debugoverlay_AddLineOverlayAlpha (lua_State *L) {
  debugoverlay->AddLineOverlayAlpha(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkint(L, 6), luaL_checkboolean(L, 7), luaL_checknumber(L, 8));
  return 0;
}

static int debugoverlay_AddScreenTextOverlay (lua_State *L) {
  debugoverlay->AddScreenTextOverlay(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkint(L, 6), luaL_checkboolean(L, 7), luaL_checkstring(L, 8));
  return 0;
}

static int debugoverlay_AddSweptBoxOverlay (lua_State *L) {
  debugoverlay->AddSweptBoxOverlay(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_checkvector(L, 4), luaL_checkangle(L, 5), luaL_checkint(L, 6), luaL_checkint(L, 7), luaL_checkint(L, 8), luaL_checkint(L, 9), luaL_checknumber(L, 10));
  return 0;
}

static int debugoverlay_AddTriangleOverlay (lua_State *L) {
  debugoverlay->AddTriangleOverlay(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkint(L, 6), luaL_checkint(L, 7), luaL_checkboolean(L, 8), luaL_checknumber(L, 9));
  return 0;
}

static int debugoverlay_ClearAllOverlays (lua_State *L) {
  debugoverlay->ClearAllOverlays();
  return 0;
}

static int debugoverlay_ClearDeadOverlays (lua_State *L) {
  debugoverlay->ClearDeadOverlays();
  return 0;
}

static int debugoverlay_ScreenPosition (lua_State *L) {
  lua_pushinteger(L, debugoverlay->ScreenPosition(luaL_checkvector(L, 1), luaL_checkvector(L, 2)));
  return 0;
}


static const luaL_Reg debugoverlaylib[] = {
  {"AddBoxOverlay",   debugoverlay_AddBoxOverlay},
  {"AddBoxOverlay2",   debugoverlay_AddBoxOverlay2},
  {"AddGridOverlay",   debugoverlay_AddGridOverlay},
  {"AddLineOverlay",   debugoverlay_AddLineOverlay},
  {"AddLineOverlayAlpha",   debugoverlay_AddLineOverlayAlpha},
  {"AddScreenTextOverlay",   debugoverlay_AddScreenTextOverlay},
  {"AddSweptBoxOverlay",   debugoverlay_AddSweptBoxOverlay},
  {"AddTriangleOverlay",   debugoverlay_AddTriangleOverlay},
  {"ClearAllOverlays",   debugoverlay_ClearAllOverlays},
  {"ClearDeadOverlays",   debugoverlay_ClearDeadOverlays},
  {"ScreenPosition",   debugoverlay_ScreenPosition},
  {NULL, NULL}
};


/*
** Open debugoverlay library
*/
LUALIB_API int luaopen_debugoverlay (lua_State *L) {
  luaL_register(L, LUA_DEBUGOVERLAYLIBNAME, debugoverlaylib);
  return 1;
}

