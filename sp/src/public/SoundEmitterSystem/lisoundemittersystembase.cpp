//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#define lisoundemittersystembase_cpp

#include "cbase.h"
#include "luamanager.h"
#include "lisoundemittersystembase.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


/*
** access functions (stack -> C)
*/


LUA_API lua_CSoundParameters lua_tosoundparameters (lua_State *L, int idx) {
  luaL_checktype(L, idx, LUA_TTABLE);
  CSoundParameters SoundParameters = CSoundParameters();
  lua_getfield(L, idx, "channel");
  if (!lua_isnil(L, -1))
    SoundParameters.channel = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "volume");
  if (!lua_isnil(L, -1))
    SoundParameters.volume = luaL_checknumber(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "pitch");
  if (!lua_isnil(L, -1))
    SoundParameters.pitch = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "pitchlow");
  if (!lua_isnil(L, -1))
    SoundParameters.pitchlow = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "pitchhigh");
  if (!lua_isnil(L, -1))
    SoundParameters.pitchhigh = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "soundlevel");
  if (!lua_isnil(L, -1))
    SoundParameters.soundlevel = (soundlevel_t)luaL_checkinteger(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "play_to_owner_only");
  if (!lua_isnil(L, -1))
    SoundParameters.play_to_owner_only = luaL_checkboolean(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "count");
  if (!lua_isnil(L, -1))
    SoundParameters.count = luaL_checkint(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "soundname");
  if (!lua_isnil(L, -1)) {
	Q_strncpy(SoundParameters.soundname, luaL_checkstring(L, -1), 128);
	SoundParameters.soundname[ 128 ] = '\0';
  }
  lua_pop(L, 1);
  lua_getfield(L, idx, "delay_msec");
  if (!lua_isnil(L, -1))
    SoundParameters.delay_msec = luaL_checkint(L, -1);
  lua_pop(L, 1);
  return SoundParameters;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushsoundparameters (lua_State *L, lua_CSoundParameters &params) {
  lua_newtable(L);
  lua_pushinteger(L, params.channel);
  lua_setfield(L, -2, "channel");
  lua_pushnumber(L, params.volume);
  lua_setfield(L, -2, "volume");
  lua_pushinteger(L, params.pitch);
  lua_setfield(L, -2, "pitch");
  lua_pushinteger(L, params.pitchlow);
  lua_setfield(L, -2, "pitchlow");
  lua_pushinteger(L, params.pitchhigh);
  lua_setfield(L, -2, "pitchhigh");
  lua_pushinteger(L, params.soundlevel);
  lua_setfield(L, -2, "soundlevel");
  lua_pushboolean(L, params.play_to_owner_only);
  lua_setfield(L, -2, "play_to_owner_only");
  lua_pushinteger(L, params.count);
  lua_setfield(L, -2, "count");
  lua_pushstring(L, params.soundname);
  lua_setfield(L, -2, "soundname");
  lua_pushinteger(L, params.delay_msec);
  lua_setfield(L, -2, "delay_msec");
}
