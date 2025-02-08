//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#define lhl2mp_player_shared_cpp

#include "cbase.h"

#include "hl2mp/hl2mp_player_shared.h"

#include "luamanager.h"
#include "lhl2mp_player_shared.h"
#include "lbaseentity_shared.h"
#ifdef CLIENT_DLL
#include "lc_baseanimating.h"
#else
#include "lbaseanimating.h"
#endif
#include "mathlib/lvector.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"
#include "luasrclib.h"


/*
** access functions (stack -> C)
*/


LUA_API lua_CHL2MP_Player *lua_tohl2mpplayer (lua_State *L, int idx) {
  CBaseHandle *hPlayer = dynamic_cast<CBaseHandle *>((CBaseHandle *)lua_touserdata(L, idx));
  if (hPlayer == NULL)
    return NULL;
  return dynamic_cast<lua_CHL2MP_Player *>(hPlayer->Get());
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushhl2mpplayer (lua_State *L, CHL2MP_Player *pPlayer) {
  CBaseHandle *hPlayer = (CBaseHandle *)lua_newuserdata(L, sizeof(CBaseHandle));
  hPlayer->Set(pPlayer);
  luaL_getmetatable(L, "CHL2MP_Player");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_CHL2MP_Player *luaL_checkhl2mpplayer (lua_State *L, int narg) {
  lua_CHL2MP_Player *d = lua_tohl2mpplayer(L, narg);
  if (d == NULL)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "CHL2MP_Player expected, got NULL entity");
  return d;
}


LUALIB_API lua_CHL2MP_Player *luaL_opthl2mpplayer (lua_State *L, int narg,
                                                                 CHL2MP_Player *def) {
  return luaL_opt(L, luaL_checkhl2mpplayer, narg, def);
}


static int CHL2MP_Player_BecomeRagdollOnClient (lua_State *L) {
#ifdef CLIENT_DLL
  lua_pushanimating(L, luaL_checkhl2mpplayer(L, 1)->BecomeRagdollOnClient());
#else
  lua_pushboolean(L, luaL_checkhl2mpplayer(L, 1)->BecomeRagdollOnClient(luaL_checkvector(L, 2)));
#endif
  return 1;
}

static int CHL2MP_Player_CalculateIKLocks (lua_State *L) {
  luaL_checkhl2mpplayer(L, 1)->CalculateIKLocks(luaL_checknumber(L, 2));
  return 0;
}

static int CHL2MP_Player_CalcView (lua_State *L) {
  Vector eyeOrigin;
  QAngle eyeAngles;
  float zNear, zFar, fov;
  luaL_checkhl2mpplayer(L, 1)->CalcView(eyeOrigin, eyeAngles, zNear, zFar, fov);
  lua_pushvector(L, eyeOrigin);
  lua_pushangle(L, eyeAngles);
  lua_pushnumber(L, zNear);
  lua_pushnumber(L, zFar);
  lua_pushnumber(L, fov);
  return 5;
}

static int CHL2MP_Player_CanSprint (lua_State *L) {
  lua_pushboolean(L, luaL_checkhl2mpplayer(L, 1)->CanSprint());
  return 1;
}

static int CHL2MP_Player_DoAnimationEvent (lua_State *L) {
  luaL_checkhl2mpplayer(L, 1)->DoAnimationEvent((PlayerAnimEvent_t)luaL_checkint(L, 2), luaL_optinteger(L, 3, 0));
  return 0;
}

static int CHL2MP_Player___index (lua_State *L) {
  CHL2MP_Player *pPlayer = lua_tohl2mpplayer(L, 1);
  if (pPlayer == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
	lua_pushfstring(L, "%s:%d: attempt to index a NULL entity", ar2.short_src, ar1.currentline);
	return lua_error(L);
  }
  const char *field = luaL_checkstring(L, 2);
#ifdef CLIENT_DLL
  if (Q_strcmp(field, "m_fNextThinkPushAway") == 0)
  {
      //lua_pushnumber(L, pPlayer->m_fNextThinkPushAway);
  }  
  else {
#endif
    if (pPlayer->m_nTableReference != LUA_NOREF) {
      lua_getref(L, pPlayer->m_nTableReference);
      lua_getfield(L, -1, field);
      if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        lua_getmetatable(L, 1);
        lua_getfield(L, -1, field);
        if (lua_isnil(L, -1)) {
          lua_pop(L, 2);
          luaL_getmetatable(L, "CBasePlayer");
          lua_getfield(L, -1, field);
          if (lua_isnil(L, -1)) {
            lua_pop(L, 2);
            luaL_getmetatable(L, "CBaseAnimating");
            lua_getfield(L, -1, field);
            if (lua_isnil(L, -1)) {
              lua_pop(L, 2);
              luaL_getmetatable(L, "CBaseEntity");
              lua_getfield(L, -1, field);
            }
          }
        }
      }
    }
    else {
      lua_getmetatable(L, 1);
      lua_getfield(L, -1, field);
      if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        luaL_getmetatable(L, "CBasePlayer");
        lua_getfield(L, -1, field);
        if (lua_isnil(L, -1)) {
          lua_pop(L, 2);
          luaL_getmetatable(L, "CBaseAnimating");
          lua_getfield(L, -1, field);
          if (lua_isnil(L, -1)) {
            lua_pop(L, 2);
            luaL_getmetatable(L, "CBaseEntity");
            lua_getfield(L, -1, field);
          }
        }
      }
    }
#ifdef CLIENT_DLL
  }
#endif
  return 1;
}

static int CHL2MP_Player___newindex (lua_State *L) {
  CHL2MP_Player *pPlayer = lua_tohl2mpplayer(L, 1);
  if (pPlayer == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
	lua_pushfstring(L, "%s:%d: attempt to index a NULL entity", ar2.short_src, ar1.currentline);
	return lua_error(L);
  }
  const char *field = luaL_checkstring(L, 2);
#ifdef CLIENT_DLL
  if (Q_strcmp(field, "m_fNextThinkPushAway") == 0)
  { 
      //pPlayer->m_fNextThinkPushAway = luaL_checknumber(L, 3);
  }
  else {
#endif
    if (pPlayer->m_nTableReference == LUA_NOREF) {
      lua_newtable(L);
      pPlayer->m_nTableReference = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_getref(L, pPlayer->m_nTableReference);
    lua_pushvalue(L, 3);
    lua_setfield(L, -2, field);
	lua_pop(L, 1);
#ifdef CLIENT_DLL
  }
#endif
  return 0;
}

static int CHL2MP_Player___eq (lua_State *L) {
  lua_pushboolean(L, lua_tohl2mpplayer(L, 1) == lua_tohl2mpplayer(L, 2));
  return 1;
}

static int CHL2MP_Player___tostring (lua_State *L) {
  CHL2MP_Player *pPlayer = lua_tohl2mpplayer(L, 1);
  if (pPlayer == NULL)
    lua_pushstring(L, "NULL");
  else
    lua_pushfstring(L, "CHL2MP_Player: %d \"%s\"", pPlayer->GetUserID(), pPlayer->GetPlayerName());
  return 1;
}


static const luaL_Reg CHL2MP_Playermeta[] = {
  {"BecomeRagdollOnClient", CHL2MP_Player_BecomeRagdollOnClient},
  {"CalculateIKLocks", CHL2MP_Player_CalculateIKLocks},
  {"CalcView", CHL2MP_Player_CalcView},
  {"CanSprint", CHL2MP_Player_CanSprint},
  {"DoAnimationEvent", CHL2MP_Player_DoAnimationEvent},
  {"__index", CHL2MP_Player___index},
  {"__newindex", CHL2MP_Player___newindex},
  {"__eq", CHL2MP_Player___eq},
  {"__tostring", CHL2MP_Player___tostring},
  {NULL, NULL}
};


static int luasrc_ToHL2MPPlayer (lua_State *L) {
  lua_pushhl2mpplayer(L, ToHL2MPPlayer(lua_toentity(L, 1)));
  return 1;
}


static const luaL_Reg CHL2MP_Player_funcs[] = {
  {"ToHL2MPPlayer", luasrc_ToHL2MPPlayer},
  {NULL, NULL}
};

/*
** Open CHL2MP_Player object
*/
LUALIB_API int luaopen_CHL2MP_Player_shared (lua_State *L) {
  luaL_newmetatable(L, "CHL2MP_Player");
  luaL_register(L, NULL, CHL2MP_Playermeta);
  lua_pushstring(L, "entity");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "entity" */
  luaL_register(L, "_G", CHL2MP_Player_funcs);
  lua_pop(L, 1);
  return 1;
}

