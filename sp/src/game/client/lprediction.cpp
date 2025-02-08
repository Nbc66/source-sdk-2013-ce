//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#define lprediction_cpp

#include "cbase.h"
#include "prediction.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static int prediction_GetIdealPitch (lua_State *L) {
  lua_pushnumber(L, prediction->GetIdealPitch());
  return 1;
}

static int prediction_GetIncomingPacketNumber (lua_State *L) {
  lua_pushinteger(L, prediction->GetIncomingPacketNumber());
  return 1;
}

static int prediction_GetLocalViewAngles (lua_State *L) {
  QAngle ang;
  prediction->GetLocalViewAngles(ang);
  lua_pushangle(L, ang);
  return 1;
}

static int prediction_GetViewAngles (lua_State *L) {
  QAngle ang;
  prediction->GetViewAngles(ang);
  lua_pushangle(L, ang);
  return 1;
}

static int prediction_GetViewOrigin (lua_State *L) {
  Vector org;
  prediction->GetViewOrigin(org);
  lua_pushvector(L, org);
  return 1;
}

static int prediction_InPrediction (lua_State *L) {
  lua_pushboolean(L, prediction->InPrediction());
  return 1;
}

static int prediction_IsFirstTimePredicted (lua_State *L) {
  lua_pushboolean(L, prediction->IsFirstTimePredicted());
  return 1;
}

static int prediction_OnReceivedUncompressedPacket (lua_State *L) {
  prediction->OnReceivedUncompressedPacket();
  return 0;
}

static int prediction_PostEntityPacketReceived (lua_State *L) {
  prediction->PostEntityPacketReceived();
  return 0;
}

static int prediction_PostNetworkDataReceived (lua_State *L) {
  prediction->PostNetworkDataReceived(luaL_checkint(L, 1));
  return 0;
}

static int prediction_PreEntityPacketReceived (lua_State *L) {
  prediction->PreEntityPacketReceived(luaL_checkint(L, 1), luaL_checkint(L, 2));
  return 0;
}

static int prediction_SetLocalViewAngles (lua_State *L) {
  prediction->SetLocalViewAngles(luaL_checkangle(L, 1));
  return 0;
}

static int prediction_SetViewAngles (lua_State *L) {
  prediction->SetViewAngles(luaL_checkangle(L, 1));
  return 0;
}

static int prediction_SetViewOrigin (lua_State *L) {
  prediction->SetViewOrigin(luaL_checkvector(L, 1));
  return 0;
}

static int prediction_Update (lua_State *L) {
  prediction->Update(luaL_checkint(L, 1), luaL_checkboolean(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}


static const luaL_Reg predictionlib[] = {
  {"GetIdealPitch",   prediction_GetIdealPitch},
  {"GetIncomingPacketNumber",   prediction_GetIncomingPacketNumber},
  {"GetLocalViewAngles",   prediction_GetLocalViewAngles},
  {"GetViewAngles",   prediction_GetViewAngles},
  {"GetViewOrigin",   prediction_GetViewOrigin},
  {"InPrediction",   prediction_InPrediction},
  {"IsFirstTimePredicted",   prediction_IsFirstTimePredicted},
  {"OnReceivedUncompressedPacket",   prediction_OnReceivedUncompressedPacket},
  {"PostEntityPacketReceived",   prediction_PostEntityPacketReceived},
  {"PostNetworkDataReceived",   prediction_PostNetworkDataReceived},
  {"PreEntityPacketReceived",   prediction_PreEntityPacketReceived},
  {"SetLocalViewAngles",   prediction_SetLocalViewAngles},
  {"SetViewAngles",   prediction_SetViewAngles},
  {"SetViewOrigin",   prediction_SetViewOrigin},
  {"Update",   prediction_Update},
  {NULL, NULL}
};


/*
** Open prediction library
*/
LUALIB_API int luaopen_prediction (lua_State *L) {
  luaL_register(L, LUA_PREDICTIONLIBNAME, predictionlib);
  return 1;
}
