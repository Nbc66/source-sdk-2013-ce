//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//
#define linetchannelinfo_cpp

#include "cbase.h"
#include "inetchannelinfo.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "linetchannelinfo.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


/*
** access functions (stack -> C)
*/


LUA_API lua_INetChannelInfo *lua_tonetchannel (lua_State *L, int idx) {
  lua_INetChannelInfo *pNetChannel = *(lua_INetChannelInfo **)luaL_checkudata(L, idx, "INetChannelInfo");
  return pNetChannel;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushnetchannel (lua_State *L, INetChannelInfo *netchannel) {
  if (netchannel == NULL)
    lua_pushnil(L);
  else {
    lua_INetChannelInfo **ppNetChannel = (lua_INetChannelInfo **)lua_newuserdata(L, sizeof(netchannel));
    *ppNetChannel = netchannel;
    luaL_getmetatable(L, "INetChannelInfo");
    lua_setmetatable(L, -2);
  }
}


LUALIB_API lua_INetChannelInfo *luaL_checknetchannel (lua_State *L, int narg) {
  lua_INetChannelInfo *d = *(lua_INetChannelInfo **)luaL_checkudata(L, narg, "INetChannelInfo");
  return d;
}


static int INetChannelInfo_GetAddress (lua_State *L) {
  lua_pushstring(L, luaL_checknetchannel(L, 1)->GetAddress());
  return 1;
}

static int INetChannelInfo_GetAvgChoke (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetAvgChoke(luaL_checkinteger(L, 2)));
  return 1;
}

static int INetChannelInfo_GetAvgData (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetAvgData(luaL_checkinteger(L, 2)));
  return 1;
}

static int INetChannelInfo_GetAvgLatency (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetAvgLatency(luaL_checkinteger(L, 2)));
  return 1;
}

static int INetChannelInfo_GetAvgLoss (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetAvgLoss(luaL_checkinteger(L, 2)));
  return 1;
}

static int INetChannelInfo_GetAvgPackets (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetAvgPackets(luaL_checkinteger(L, 2)));
  return 1;
}

static int INetChannelInfo_GetBufferSize (lua_State *L) {
  lua_pushinteger(L, luaL_checknetchannel(L, 1)->GetBufferSize());
  return 1;
}

static int INetChannelInfo_GetCommandInterpolationAmount (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetCommandInterpolationAmount(luaL_checkinteger(L, 2), luaL_checkinteger(L, 3)));
  return 1;
}

static int INetChannelInfo_GetDataRate (lua_State *L) {
  lua_pushinteger(L, luaL_checknetchannel(L, 1)->GetDataRate());
  return 1;
}

static int INetChannelInfo_GetLatency (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetLatency(luaL_checkinteger(L, 2)));
  return 1;
}

static int INetChannelInfo_GetName (lua_State *L) {
  lua_pushstring(L, luaL_checknetchannel(L, 1)->GetName());
  return 1;
}

static int INetChannelInfo_GetPacketBytes (lua_State *L) {
  lua_pushinteger(L, luaL_checknetchannel(L, 1)->GetPacketBytes(luaL_checkinteger(L, 2), luaL_checkinteger(L, 3), luaL_checkinteger(L, 4)));
  return 1;
}

static int INetChannelInfo_GetPacketResponseLatency (lua_State *L) {
  int pnLatencyMsecs, pnChoke;
  luaL_checknetchannel(L, 1)->GetPacketResponseLatency(luaL_checkinteger(L, 2), luaL_checkinteger(L, 3), &pnLatencyMsecs, &pnChoke);
  lua_pushinteger(L, pnLatencyMsecs);
  lua_pushinteger(L, pnChoke);
  return 2;
}

static int INetChannelInfo_GetPacketTime (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetPacketTime(luaL_checkinteger(L, 2), luaL_checkinteger(L, 3)));
  return 1;
}

static int INetChannelInfo_GetRemoteFramerate (lua_State *L) {
  float pflFrameTime, pflFrameTimeStdDeviation;
  luaL_checknetchannel(L, 1)->GetRemoteFramerate(&pflFrameTime, &pflFrameTimeStdDeviation);
  lua_pushnumber(L, pflFrameTime);
  lua_pushnumber(L, pflFrameTimeStdDeviation);
  return 2;
}

static int INetChannelInfo_GetSequenceNr (lua_State *L) {
  lua_pushinteger(L, luaL_checknetchannel(L, 1)->GetSequenceNr(luaL_checkinteger(L, 2)));
  return 1;
}

static int INetChannelInfo_GetStreamProgress (lua_State *L) {
  int received, total;
  lua_pushboolean(L, luaL_checknetchannel(L, 1)->GetStreamProgress(luaL_checkinteger(L, 2), &received, &total));
  lua_pushinteger(L, received);
  lua_pushinteger(L, total);
  return 3;
}

static int INetChannelInfo_GetTime (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetTime());
  return 1;
}

static int INetChannelInfo_GetTimeConnected (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetTimeConnected());
  return 1;
}

static int INetChannelInfo_GetTimeoutSeconds (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetTimeoutSeconds());
  return 1;
}

static int INetChannelInfo_GetTimeSinceLastReceived (lua_State *L) {
  lua_pushnumber(L, luaL_checknetchannel(L, 1)->GetTimeSinceLastReceived());
  return 1;
}

static int INetChannelInfo_GetTotalData (lua_State *L) {
  lua_pushinteger(L, luaL_checknetchannel(L, 1)->GetTotalData(luaL_checkinteger(L, 2)));
  return 1;
}

static int INetChannelInfo_IsLoopback (lua_State *L) {
  lua_pushboolean(L, luaL_checknetchannel(L, 1)->IsLoopback());
  return 1;
}

static int INetChannelInfo_IsPlayback (lua_State *L) {
  lua_pushboolean(L, luaL_checknetchannel(L, 1)->IsPlayback());
  return 1;
}

static int INetChannelInfo_IsTimingOut (lua_State *L) {
  lua_pushboolean(L, luaL_checknetchannel(L, 1)->IsTimingOut());
  return 1;
}

static int INetChannelInfo_IsValidPacket (lua_State *L) {
  lua_pushboolean(L, luaL_checknetchannel(L, 1)->IsValidPacket(luaL_checkinteger(L, 2), luaL_checkinteger(L, 3)));
  return 1;
}

static int INetChannelInfo___tostring (lua_State *L) {
  lua_pushfstring(L, "INetChannelInfo: %p", luaL_checkudata(L, 1, "INetChannelInfo"));
  return 1;
}


static const luaL_Reg INetChannelInfometa[] = {
  {"GetAddress", INetChannelInfo_GetAddress},
  {"GetAvgChoke", INetChannelInfo_GetAvgChoke},
  {"GetAvgData", INetChannelInfo_GetAvgData},
  {"GetAvgLatency", INetChannelInfo_GetAvgLatency},
  {"GetAvgLoss", INetChannelInfo_GetAvgLoss},
  {"GetAvgPackets", INetChannelInfo_GetAvgPackets},
  {"GetBufferSize", INetChannelInfo_GetBufferSize},
  {"GetCommandInterpolationAmount", INetChannelInfo_GetCommandInterpolationAmount},
  {"GetDataRate", INetChannelInfo_GetDataRate},
  {"GetLatency", INetChannelInfo_GetLatency},
  {"GetName", INetChannelInfo_GetName},
  {"GetPacketBytes", INetChannelInfo_GetPacketBytes},
  {"GetPacketResponseLatency", INetChannelInfo_GetPacketResponseLatency},
  {"GetPacketTime", INetChannelInfo_GetPacketTime},
  {"GetRemoteFramerate", INetChannelInfo_GetRemoteFramerate},
  {"GetSequenceNr", INetChannelInfo_GetSequenceNr},
  {"GetStreamProgress", INetChannelInfo_GetStreamProgress},
  {"GetTime", INetChannelInfo_GetTime},
  {"GetTimeConnected", INetChannelInfo_GetTimeConnected},
  {"GetTimeoutSeconds", INetChannelInfo_GetTimeoutSeconds},
  {"GetTimeSinceLastReceived", INetChannelInfo_GetTimeSinceLastReceived},
  {"GetTotalData", INetChannelInfo_GetTotalData},
  {"IsLoopback", INetChannelInfo_IsLoopback},
  {"IsPlayback", INetChannelInfo_IsPlayback},
  {"IsTimingOut", INetChannelInfo_IsTimingOut},
  {"IsValidPacket", INetChannelInfo_IsValidPacket},
  {"__tostring", INetChannelInfo___tostring},
  {NULL, NULL}
};


/*
** Open INetChannelInfo object
*/
LUALIB_API int luaopen_INetChannelInfo (lua_State *L) {
  luaL_newmetatable(L, LUA_NETCHANNELINFOLIBNAME);
  luaL_register(L, NULL, INetChannelInfometa);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "netchannelinfo");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "netchannelinfo" */
  return 1;
}

