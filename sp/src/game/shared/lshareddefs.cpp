//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Definitions that are shared by the game DLL and the client DLL.
//
// $NoKeywords: $
//=============================================================================//

#define lshareddefs_cpp

#include "cbase.h"
#include "ammodef.h"
#include "luamanager.h"
#include "lshareddefs.h"
#include "lbaseentity_shared.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


/*
** access functions (stack -> C)
*/


LUA_API lua_FireBulletsInfo_t lua_tofirebulletsinfo (lua_State *L, int idx) {
  luaL_checktype(L, idx, LUA_TTABLE);
  FireBulletsInfo_t info;
  lua_getfield(L, idx, "m_bPrimaryAttack");
  if (!lua_isnil(L, -1))
    info.m_bPrimaryAttack = luaL_checkboolean(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_flDamageForceScale");
  if (!lua_isnil(L, -1))
    info.m_flDamageForceScale = luaL_checknumber(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_flDistance");
  if (!lua_isnil(L, -1))
    info.m_flDistance = luaL_checknumber(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_iAmmoType");
  if (!lua_isnil(L, -1))
    info.m_iAmmoType = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_flDamage");
  if (!lua_isnil(L, -1))
    info.m_flDamage = luaL_checklong(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_iPlayerDamage");
  if (!lua_isnil(L, -1))
    info.m_iPlayerDamage = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_iShots");
  if (!lua_isnil(L, -1))
    info.m_iShots = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_iTracerFreq");
  if (!lua_isnil(L, -1))
    info.m_iTracerFreq = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_nFlags");
  if (!lua_isnil(L, -1))
    info.m_nFlags = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_pAdditionalIgnoreEnt");
  if (!lua_isnil(L, -1))
    info.m_pAdditionalIgnoreEnt = lua_toentity(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_pAttacker");
  if (!lua_isnil(L, -1))
    info.m_pAttacker = lua_toentity(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_vecDirShooting");
  if (!lua_isnil(L, -1))
    info.m_vecDirShooting = luaL_checkvector(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_vecSpread");
  if (!lua_isnil(L, -1))
    info.m_vecSpread = luaL_checkvector(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_vecSrc");
  if (!lua_isnil(L, -1))
    info.m_vecSrc = luaL_checkvector(L, -1);
  lua_pop(L, 1);
  return info;
}

LUA_API void lua_toemitsound (lua_State *L, int idx, EmitSound_t &ep) {
  luaL_checktype(L, idx, LUA_TTABLE);
  lua_getfield(L, idx, "m_nChannel");
  if (!lua_isnil(L, -1))
    ep.m_nChannel = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_pSoundName");
  if (!lua_isnil(L, -1))
    ep.m_pSoundName = luaL_checkstring(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_flVolume");
  if (!lua_isnil(L, -1))
    ep.m_flVolume = luaL_checknumber(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_SoundLevel");
  if (!lua_isnil(L, -1))
    ep.m_SoundLevel = (soundlevel_t)luaL_checkinteger(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_nFlags");
  if (!lua_isnil(L, -1))
    ep.m_nFlags = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_nPitch");
  if (!lua_isnil(L, -1))
    ep.m_nPitch = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_pOrigin");
  if (!lua_isnil(L, -1))
    ep.m_pOrigin = &luaL_checkvector(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_flSoundTime");
  if (!lua_isnil(L, -1))
    ep.m_flSoundTime = luaL_checknumber(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "m_pflSoundDuration");
  if (!lua_isnil(L, -1)) {
    float duration = luaL_checknumber(L, -1);
    ep.m_pflSoundDuration = &duration;
  }
  lua_pop(L, 1);
}

