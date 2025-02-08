//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "takedamageinfo.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "ltakedamageinfo.h"
#include "lbaseentity_shared.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


/*
** access functions (stack -> C)
*/


LUA_API lua_CTakeDamageInfo &lua_todamageinfo (lua_State *L, int idx) {
  lua_CTakeDamageInfo *info = (lua_CTakeDamageInfo *)lua_touserdata(L, idx);
  return *info;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushdamageinfo (lua_State *L, lua_CTakeDamageInfo &info) {
  lua_CTakeDamageInfo *pInfo = (lua_CTakeDamageInfo *)lua_newuserdata(L, sizeof(lua_CTakeDamageInfo));
  *pInfo = info;
  luaL_getmetatable(L, "CTakeDamageInfo");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_CTakeDamageInfo &luaL_checkdamageinfo (lua_State *L, int narg) {
  lua_CTakeDamageInfo *d = (lua_CTakeDamageInfo *)luaL_checkudata(L, narg, "CTakeDamageInfo");
  return *d;
}


static int CTakeDamageInfo_AddDamage (lua_State *L) {
  luaL_checkdamageinfo(L, 1).AddDamage(luaL_checknumber(L, 2));
  return 0;
}

static int CTakeDamageInfo_AddDamageType (lua_State *L) {
  luaL_checkdamageinfo(L, 1).AddDamageType(luaL_checkint(L, 2));
  return 0;
}

static int CTakeDamageInfo_AdjustPlayerDamageInflictedForSkillLevel (lua_State *L) {
  luaL_checkdamageinfo(L, 1).AdjustPlayerDamageInflictedForSkillLevel();
  return 0;
}

static int CTakeDamageInfo_AdjustPlayerDamageTakenForSkillLevel (lua_State *L) {
  luaL_checkdamageinfo(L, 1).AdjustPlayerDamageTakenForSkillLevel();
  return 0;
}

static int CTakeDamageInfo_BaseDamageIsValid (lua_State *L) {
  lua_pushboolean(L, luaL_checkdamageinfo(L, 1).BaseDamageIsValid());
  return 1;
}

static int CTakeDamageInfo_CopyDamageToBaseDamage (lua_State *L) {
  luaL_checkdamageinfo(L, 1).CopyDamageToBaseDamage();
  return 0;
}

static int CTakeDamageInfo_DebugGetDamageTypeString (lua_State *L) {
  char outbuf[256];
  outbuf[0] = '\0';
  luaL_checkdamageinfo(L, 1).DebugGetDamageTypeString(luaL_checkint(L, 2), outbuf, sizeof( outbuf ));
  lua_pushstring(L, outbuf);
  return 1;
}

static int CTakeDamageInfo_GetAmmoName (lua_State *L) {
  lua_pushstring(L, luaL_checkdamageinfo(L, 1).GetAmmoName());
  return 1;
}

static int CTakeDamageInfo_GetAmmoType (lua_State *L) {
  lua_pushinteger(L, luaL_checkdamageinfo(L, 1).GetAmmoType());
  return 1;
}

static int CTakeDamageInfo_GetAttacker (lua_State *L) {
  lua_pushentity(L, luaL_checkdamageinfo(L, 1).GetAttacker());
  return 1;
}

static int CTakeDamageInfo_GetBaseDamage (lua_State *L) {
  lua_pushnumber(L, luaL_checkdamageinfo(L, 1).GetBaseDamage());
  return 1;
}

static int CTakeDamageInfo_GetDamage (lua_State *L) {
  lua_pushnumber(L, luaL_checkdamageinfo(L, 1).GetDamage());
  return 1;
}

static int CTakeDamageInfo_GetDamageCustom (lua_State *L) {
  lua_pushinteger(L, luaL_checkdamageinfo(L, 1).GetDamageCustom());
  return 1;
}

static int CTakeDamageInfo_GetDamageForce (lua_State *L) {
  lua_pushvector(L, luaL_checkdamageinfo(L, 1).GetDamageForce());
  return 1;
}

static int CTakeDamageInfo_GetDamagePosition (lua_State *L) {
  lua_pushvector(L, luaL_checkdamageinfo(L, 1).GetDamagePosition());
  return 1;
}

static int CTakeDamageInfo_GetDamageStats (lua_State *L) {
  lua_pushinteger(L, luaL_checkdamageinfo(L, 1).GetDamageStats());
  return 1;
}

static int CTakeDamageInfo_GetDamageType (lua_State *L) {
  lua_pushinteger(L, luaL_checkdamageinfo(L, 1).GetDamageType());
  return 1;
}

static int CTakeDamageInfo_GetInflictor (lua_State *L) {
  lua_pushentity(L, luaL_checkdamageinfo(L, 1).GetInflictor());
  return 1;
}

static int CTakeDamageInfo_GetMaxDamage (lua_State *L) {
  lua_pushnumber(L, luaL_checkdamageinfo(L, 1).GetMaxDamage());
  return 1;
}

static int CTakeDamageInfo_GetReportedPosition (lua_State *L) {
  lua_pushvector(L, luaL_checkdamageinfo(L, 1).GetReportedPosition());
  return 1;
}

static int CTakeDamageInfo_GetWeapon (lua_State *L) {
  lua_pushentity(L, luaL_checkdamageinfo(L, 1).GetWeapon());
  return 1;
}

static int CTakeDamageInfo_ScaleDamage (lua_State *L) {
  luaL_checkdamageinfo(L, 1).ScaleDamage(luaL_checknumber(L, 2));
  return 0;
}

static int CTakeDamageInfo_ScaleDamageForce (lua_State *L) {
  luaL_checkdamageinfo(L, 1).ScaleDamageForce(luaL_checknumber(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetAmmoType (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetAmmoType(luaL_checkint(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetAttacker (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetAttacker(luaL_checkentity(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetDamage (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetDamage(luaL_checknumber(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetDamageCustom (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetDamageCustom(luaL_checkint(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetDamageForce (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetDamageForce(luaL_checkvector(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetDamagePosition (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetDamagePosition(luaL_checkvector(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetDamageStats (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetDamageStats(luaL_checkint(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetDamageType (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetDamageType(luaL_checkint(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetInflictor (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetInflictor(luaL_checkentity(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetMaxDamage (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetMaxDamage(luaL_checknumber(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetReportedPosition (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetReportedPosition(luaL_checkvector(L, 2));
  return 0;
}

static int CTakeDamageInfo_SetWeapon (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SetWeapon(luaL_checkentity(L, 2));
  return 0;
}

static int CTakeDamageInfo_SubtractDamage (lua_State *L) {
  luaL_checkdamageinfo(L, 1).SubtractDamage(luaL_checknumber(L, 2));
  return 0;
}

static int CTakeDamageInfo___tostring (lua_State *L) {
  lua_pushfstring(L, "CTakeDamageInfo: %p", luaL_checkudata(L, 1, "CTakeDamageInfo"));
  return 1;
}


static const luaL_Reg CTakeDamageInfometa[] = {
  {"AddDamage", CTakeDamageInfo_AddDamage},
  {"AddDamageType", CTakeDamageInfo_AddDamageType},
  {"AdjustPlayerDamageInflictedForSkillLevel", CTakeDamageInfo_AdjustPlayerDamageInflictedForSkillLevel},
  {"AdjustPlayerDamageTakenForSkillLevel", CTakeDamageInfo_AdjustPlayerDamageTakenForSkillLevel},
  {"BaseDamageIsValid", CTakeDamageInfo_BaseDamageIsValid},
  {"CopyDamageToBaseDamage", CTakeDamageInfo_CopyDamageToBaseDamage},
  {"DebugGetDamageTypeString", CTakeDamageInfo_DebugGetDamageTypeString},
  {"GetAmmoName", CTakeDamageInfo_GetAmmoName},
  {"GetAmmoType", CTakeDamageInfo_GetAmmoType},
  {"GetAttacker", CTakeDamageInfo_GetAttacker},
  {"GetBaseDamage", CTakeDamageInfo_GetBaseDamage},
  {"GetDamage", CTakeDamageInfo_GetDamage},
  {"GetDamageCustom", CTakeDamageInfo_GetDamageCustom},
  {"GetDamageForce", CTakeDamageInfo_GetDamageForce},
  {"GetDamagePosition", CTakeDamageInfo_GetDamagePosition},
  {"GetDamageStats", CTakeDamageInfo_GetDamageStats},
  {"GetDamageType", CTakeDamageInfo_GetDamageType},
  {"GetInflictor", CTakeDamageInfo_GetInflictor},
  {"GetMaxDamage", CTakeDamageInfo_GetMaxDamage},
  {"GetReportedPosition", CTakeDamageInfo_GetReportedPosition},
  {"GetWeapon", CTakeDamageInfo_GetWeapon},
  {"ScaleDamage", CTakeDamageInfo_ScaleDamage},
  {"ScaleDamageForce", CTakeDamageInfo_ScaleDamageForce},
  {"SetAmmoType", CTakeDamageInfo_SetAmmoType},
  {"SetAttacker", CTakeDamageInfo_SetAttacker},
  {"SetDamage", CTakeDamageInfo_SetDamage},
  {"SetDamageCustom", CTakeDamageInfo_SetDamageCustom},
  {"SetDamageForce", CTakeDamageInfo_SetDamageForce},
  {"SetDamagePosition", CTakeDamageInfo_SetDamagePosition},
  {"SetDamageStats", CTakeDamageInfo_SetDamageStats},
  {"SetDamageType", CTakeDamageInfo_SetDamageType},
  {"SetInflictor", CTakeDamageInfo_SetInflictor},
  {"SetMaxDamage", CTakeDamageInfo_SetMaxDamage},
  {"SetReportedPosition", CTakeDamageInfo_SetReportedPosition},
  {"SetWeapon", CTakeDamageInfo_SetWeapon},
  {"SubtractDamage", CTakeDamageInfo_SubtractDamage},
  {"__tostring", CTakeDamageInfo___tostring},
  {NULL, NULL}
};


static int luasrc_CTakeDamageInfo (lua_State *L) {
  if (lua_gettop(L) < 4) {
    CTakeDamageInfo info = CTakeDamageInfo();
    lua_pushdamageinfo(L, info);
  } else if (lua_gettop(L) <= 5) {
    CTakeDamageInfo info = CTakeDamageInfo(luaL_checkentity(L, 1), luaL_checkentity(L, 2), luaL_checknumber(L, 3), luaL_checkint(L, 4), luaL_optint(L, 5, 0));
    lua_pushdamageinfo(L, info);
  } else if (lua_gettop(L) <= 6) {
    CTakeDamageInfo info = CTakeDamageInfo(luaL_checkentity(L, 1), luaL_checkentity(L, 2), luaL_checkentity(L, 3), luaL_checknumber(L, 4), luaL_checkint(L, 5), luaL_optint(L, 6, 0));
    lua_pushdamageinfo(L, info);
  } else if (lua_gettop(L) < 9) {
    CTakeDamageInfo info = CTakeDamageInfo(luaL_checkentity(L, 1), luaL_checkentity(L, 2), luaL_checkvector(L, 3), luaL_checkvector(L, 4), luaL_checknumber(L, 5), luaL_checkint(L, 6), luaL_optint(L, 7, 0), &luaL_optvector(L, 8, NULL));
    lua_pushdamageinfo(L, info);
  } else {
    CTakeDamageInfo info = CTakeDamageInfo(luaL_checkentity(L, 1), luaL_checkentity(L, 2), luaL_checkentity(L, 3), luaL_checkvector(L, 4), luaL_checkvector(L, 5), luaL_checknumber(L, 6), luaL_checkint(L, 7), luaL_optint(L, 8, 0), &luaL_optvector(L, 9, NULL));
    lua_pushdamageinfo(L, info);
  }
  return 1;
}

static int luasrc_ClearMultiDamage (lua_State *L) {
  ClearMultiDamage();
  return 0;
}

static int luasrc_ApplyMultiDamage (lua_State *L) {
  ApplyMultiDamage();
  return 0;
}

static int luasrc_AddMultiDamage (lua_State *L) {
  AddMultiDamage(luaL_checkdamageinfo(L, 1), luaL_checkentity(L, 2));
  return 0;
}

static int luasrc_ImpulseScale (lua_State *L) {
  lua_pushnumber(L, ImpulseScale(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
  return 1;
}

static int luasrc_CalculateExplosiveDamageForce (lua_State *L) {
  CalculateExplosiveDamageForce(&luaL_checkdamageinfo(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_optnumber(L, 4, 1.0));
  return 0;
}

static int luasrc_CalculateBulletDamageForce (lua_State *L) {
  CalculateBulletDamageForce(&luaL_checkdamageinfo(L, 1), luaL_checkint(L, 2), luaL_checkvector(L, 3), luaL_checkvector(L, 4), luaL_optnumber(L, 5, 1.0));
  return 0;
}

static int luasrc_CalculateMeleeDamageForce (lua_State *L) {
  CalculateMeleeDamageForce(&luaL_checkdamageinfo(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_optnumber(L, 4, 1.0));
  return 0;
}

static int luasrc_GuessDamageForce (lua_State *L) {
  GuessDamageForce(&luaL_checkdamageinfo(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_optnumber(L, 4, 1.0));
  return 0;
}


static const luaL_Reg CTakeDamageInfo_funcs[] = {
  {"CTakeDamageInfo", luasrc_CTakeDamageInfo},
  {"ClearMultiDamage", luasrc_ClearMultiDamage},
  {"ApplyMultiDamage", luasrc_ApplyMultiDamage},
  {"AddMultiDamage", luasrc_AddMultiDamage},
  {"ImpulseScale", luasrc_ImpulseScale},
  {"CalculateExplosiveDamageForce", luasrc_CalculateExplosiveDamageForce},
  {"CalculateBulletDamageForce", luasrc_CalculateBulletDamageForce},
  {"CalculateMeleeDamageForce", luasrc_CalculateMeleeDamageForce},
  {"GuessDamageForce", luasrc_GuessDamageForce},
  {NULL, NULL}
};


/*
** Open CTakeDamageInfo object
*/
LUALIB_API int luaopen_CTakeDamageInfo (lua_State *L) {
  luaL_newmetatable(L, LUA_TAKEDAMAGEINFOLIBNAME);
  luaL_register(L, NULL, CTakeDamageInfometa);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "damageinfo");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "damageinfo" */
  luaL_register(L, "_G", CTakeDamageInfo_funcs);
  lua_pop(L, 1);
  return 1;
}

