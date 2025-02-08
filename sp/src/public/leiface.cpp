//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//

#define leiface_cpp

#include "cbase.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lbaseentity_shared.h"
#include "lbaseplayer_shared.h"
#include "linetchannelinfo.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Engine interfaces.
// IVEngineServer	*engine = NULL;

static int engine_AllowImmediateEdictReuse (lua_State *L) {
  engine->AllowImmediateEdictReuse();
  return 0;
}

static int engine_ChangeLevel (lua_State *L) {
  engine->ChangeLevel(luaL_checkstring(L, 1), luaL_optstring(L, 2, NULL));
  return 0;
}

static int engine_ChangeTeam (lua_State *L) {
  engine->ChangeTeam(luaL_checkstring(L, 1));
  return 0;
}

static int engine_CheckAreasConnected (lua_State *L) {
  lua_pushinteger(L, engine->CheckAreasConnected(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2)));
  return 1;
}

static int engine_CopyFile (lua_State *L) {
  lua_pushboolean(L, engine->CopyFile(luaL_checkstring(L, 1), luaL_checkstring(L, 2)));
  return 1;
}

static int engine_CreateFakeClient (lua_State *L) {
  edict_t *pEdict = engine->CreateFakeClient(luaL_checkstring(L, 1));

  if (!pEdict)
  {
    Msg( "Failed to create Bot.\n");
    return 0;
  }

  CBasePlayer *pPlayer = ((CBasePlayer*)CBaseEntity::Instance( pEdict ));
  lua_pushplayer(L, pPlayer);
  return 1;
}

static int engine_ForceExactFile (lua_State *L) {
  engine->ForceExactFile(luaL_checkstring(L, 1));
  return 0;
}

static int engine_ForceSimpleMaterial (lua_State *L) {
  engine->ForceSimpleMaterial(luaL_checkstring(L, 1));
  return 0;
}

static int engine_GetAppID (lua_State *L) {
  lua_pushinteger(L, engine->GetAppID());
  return 1;
}

static int engine_GetClientConVarValue (lua_State *L) {
  lua_pushstring(L, engine->GetClientConVarValue(luaL_checkinteger(L, 1), luaL_checkstring(L, 2)));
  return 1;
}

static int engine_GetEntityCount (lua_State *L) {
  lua_pushinteger(L, engine->GetEntityCount());
  return 1;
}

static int engine_GetGameDir (lua_State *L) {
  char gamePath[256];
  engine->GetGameDir( gamePath, 256 );
  lua_pushstring(L, gamePath);
  return 1;
}

static int engine_GetMapEntitiesString (lua_State *L) {
  lua_pushstring(L, engine->GetMapEntitiesString());
  return 1;
}

static int engine_GetMostRecentlyLoadedFileName (lua_State *L) {
  lua_pushstring(L, engine->GetMostRecentlyLoadedFileName());
  return 1;
}

static int engine_GetPlayerNetInfo (lua_State *L) {
  lua_pushnetchannel(L, engine->GetPlayerNetInfo(luaL_checkinteger(L, 1)));
  return 1;
}

static int engine_GetSaveFileName (lua_State *L) {
  lua_pushstring(L, engine->GetSaveFileName());
  return 1;
}

static int engine_IndexOfEdict (lua_State *L) {
  lua_pushinteger(L, engine->IndexOfEdict(luaL_checkentity(L, 1)->edict()));
  return 1;
}

static int engine_InsertServerCommand (lua_State *L) {
  engine->InsertServerCommand(luaL_checkstring(L, 1));
  return 0;
}

static int engine_IsDecalPrecached (lua_State *L) {
  lua_pushboolean(L, engine->IsDecalPrecached(luaL_checkstring(L, 1)));
  return 1;
}

static int engine_IsDedicatedServer (lua_State *L) {
  lua_pushboolean(L, engine->IsDedicatedServer());
  return 1;
}

static int engine_IsGenericPrecached (lua_State *L) {
  lua_pushboolean(L, engine->IsGenericPrecached(luaL_checkstring(L, 1)));
  return 1;
}

static int engine_IsInCommentaryMode (lua_State *L) {
  lua_pushinteger(L, engine->IsInCommentaryMode());
  return 1;
}

static int engine_IsInEditMode (lua_State *L) {
  lua_pushinteger(L, engine->IsInEditMode());
  return 1;
}

static int engine_IsInternalBuild (lua_State *L) {
  lua_pushboolean(L, engine->IsInternalBuild());
  return 1;
}

static int engine_IsLowViolence (lua_State *L) {
  lua_pushboolean(L, engine->IsLowViolence());
  return 1;
}

static int engine_IsMapValid (lua_State *L) {
  lua_pushinteger(L, engine->IsMapValid(luaL_checkstring(L, 1)));
  return 1;
}

static int engine_IsModelPrecached (lua_State *L) {
  lua_pushboolean(L, engine->IsModelPrecached(luaL_checkstring(L, 1)));
  return 1;
}

static int engine_IsPaused (lua_State *L) {
  lua_pushboolean(L, engine->IsPaused());
  return 1;
}

static int engine_LightStyle (lua_State *L) {
  engine->LightStyle(luaL_checkinteger(L, 1), luaL_checkstring(L, 2));
  return 0;
}

static int engine_LoadAdjacentEnts (lua_State *L) {
  engine->LoadAdjacentEnts(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
  return 0;
}

static int engine_LoadGameState (lua_State *L) {
  lua_pushboolean(L, engine->LoadGameState(luaL_checkstring(L, 1), luaL_checkboolean(L, 2)));
  return 1;
}

static int engine_LockNetworkStringTables (lua_State *L) {
  lua_pushboolean(L, engine->LockNetworkStringTables(luaL_checkboolean(L, 1)));
  return 1;
}

static int engine_LogPrint (lua_State *L) {
  engine->LogPrint(luaL_checkstring(L, 1));
  return 0;
}

static int engine_MessageEnd (lua_State *L) {
  engine->MessageEnd();
  return 0;
}

static int engine_MultiplayerEndGame (lua_State *L) {
  engine->MultiplayerEndGame();
  return 0;
}

static int engine_NotifyEdictFlagsChange (lua_State *L) {
  engine->NotifyEdictFlagsChange(luaL_checkinteger(L, 1));
  return 0;
}

static int engine_PrecacheDecal (lua_State *L) {
  lua_pushinteger(L, engine->PrecacheDecal(luaL_checkstring(L, 1), luaL_checkboolean(L, 2)));
  return 1;
}

static int engine_PrecacheGeneric (lua_State *L) {
  lua_pushinteger(L, engine->PrecacheGeneric(luaL_checkstring(L, 1), luaL_checkboolean(L, 2)));
  return 1;
}

static int engine_PrecacheModel (lua_State *L) {
  lua_pushinteger(L, engine->PrecacheModel(luaL_checkstring(L, 1), luaL_checkboolean(L, 2)));
  return 1;
}

static int engine_PrecacheSentenceFile (lua_State *L) {
  lua_pushinteger(L, engine->PrecacheSentenceFile(luaL_checkstring(L, 1), luaL_checkboolean(L, 2)));
  return 1;
}

static int engine_SentenceGroupIndexFromName (lua_State *L) {
  lua_pushinteger(L, engine->SentenceGroupIndexFromName(luaL_checkstring(L, 1)));
  return 1;
}

static int engine_SentenceGroupNameFromIndex (lua_State *L) {
  lua_pushstring(L, engine->SentenceGroupNameFromIndex(luaL_checkinteger(L, 1)));
  return 1;
}

static int engine_SentenceIndexFromName (lua_State *L) {
  lua_pushinteger(L, engine->SentenceIndexFromName(luaL_checkstring(L, 1)));
  return 1;
}

static int engine_SentenceLength (lua_State *L) {
  lua_pushnumber(L, engine->SentenceLength(luaL_checkinteger(L, 1)));
  return 1;
}

static int engine_SentenceNameFromIndex (lua_State *L) {
  lua_pushstring(L, engine->SentenceNameFromIndex(luaL_checkinteger(L, 1)));
  return 1;
}

static int engine_ServerCommand (lua_State *L) {
  engine->ServerCommand(luaL_checkstring(L, 1));
  return 0;
}

static int engine_ServerExecute (lua_State *L) {
  engine->ServerExecute();
  return 0;
}

static int engine_SetAreaPortalState (lua_State *L) {
  engine->SetAreaPortalState(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2));
  return 0;
}

static int engine_SetDedicatedServerBenchmarkMode (lua_State *L) {
  engine->SetDedicatedServerBenchmarkMode(luaL_checkboolean(L, 1));
  return 0;
}

static int engine_Time (lua_State *L) {
  lua_pushnumber(L, engine->Time());
  return 1;
}


static const luaL_Reg enginelib[] = {
  {"AllowImmediateEdictReuse",   engine_AllowImmediateEdictReuse},
  {"ChangeLevel",  engine_ChangeLevel},
  {"ChangeTeam",  engine_ChangeTeam},
  {"CheckAreasConnected", engine_CheckAreasConnected},
  {"CopyFile", engine_CopyFile},
  {"CreateFakeClient", engine_CreateFakeClient},
  {"ForceExactFile", engine_ForceExactFile},
  {"ForceSimpleMaterial", engine_ForceSimpleMaterial},
  {"GetAppID", engine_GetAppID},
  {"GetClientConVarValue", engine_GetClientConVarValue},
  {"GetEntityCount", engine_GetEntityCount},
  {"GetGameDir", engine_GetGameDir},
  {"GetMapEntitiesString", engine_GetMapEntitiesString},
  {"GetMostRecentlyLoadedFileName", engine_GetMostRecentlyLoadedFileName},
  {"GetPlayerNetInfo", engine_GetPlayerNetInfo},
  {"GetSaveFileName", engine_GetSaveFileName},
  {"IndexOfEdict", engine_IndexOfEdict},
  {"InsertServerCommand", engine_InsertServerCommand},
  {"IsDecalPrecached", engine_IsDecalPrecached},
  {"IsDedicatedServer", engine_IsDedicatedServer},
  {"IsGenericPrecached", engine_IsGenericPrecached},
  {"IsInCommentaryMode", engine_IsInCommentaryMode},
  {"IsInEditMode", engine_IsInEditMode},
  {"IsInternalBuild", engine_IsInternalBuild},
  {"IsLowViolence", engine_IsLowViolence},
  {"IsMapValid", engine_IsMapValid},
  {"IsModelPrecached", engine_IsModelPrecached},
  {"IsPaused", engine_IsPaused},
  {"LoadAdjacentEnts", engine_LoadAdjacentEnts},
  {"LoadGameState", engine_LoadGameState},
  {"LockNetworkStringTables", engine_LockNetworkStringTables},
  {"LogPrint", engine_LogPrint},
  {"MessageEnd", engine_MessageEnd},
  {"MultiplayerEndGame", engine_MultiplayerEndGame},
  {"NotifyEdictFlagsChange", engine_NotifyEdictFlagsChange},
  {"PrecacheDecal", engine_PrecacheDecal},
  {"PrecacheGeneric", engine_PrecacheGeneric},
  {"PrecacheModel", engine_PrecacheModel},
  {"PrecacheSentenceFile", engine_PrecacheSentenceFile},
  {"SentenceGroupIndexFromName", engine_SentenceGroupIndexFromName},
  {"SentenceGroupNameFromIndex", engine_SentenceGroupNameFromIndex},
  {"SentenceIndexFromName", engine_SentenceIndexFromName},
  {"SentenceLength", engine_SentenceLength},
  {"SentenceNameFromIndex", engine_SentenceNameFromIndex},
  {"ServerCommand", engine_ServerCommand},
  {"ServerExecute", engine_ServerExecute},
  {"SetAreaPortalState", engine_SetAreaPortalState},
  {"SetDedicatedServerBenchmarkMode", engine_SetDedicatedServerBenchmarkMode},
  {"Time", engine_Time},
  {NULL, NULL}
};


/*
** Open engine library
*/
LUALIB_API int luaopen_engine (lua_State *L) {
  luaL_register(L, LUA_ENGINELIBNAME, enginelib);
  return 1;
}

