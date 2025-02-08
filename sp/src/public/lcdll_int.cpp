//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Interfaces between the client.dll and engine
//
//===========================================================================//

#define lcdll_int_cpp

#include "cbase.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"



static int engine_ActivateOccluder (lua_State *L) {
  engine->ActivateOccluder(luaL_checkint(L, 1), luaL_checkboolean(L, 2));
  return 0;
}

static int engine_ChangeTeam (lua_State *L) {
  engine->ChangeTeam(luaL_checkstring(L, 1));
  return 0;
}

static int engine_CheckDoneKeyTrapping (lua_State *L) {
  ButtonCode_t code = (ButtonCode_t)luaL_checkint(L, 1);
  lua_pushboolean(L, engine->CheckDoneKeyTrapping(code));
  return 1;
}

static int engine_CheckPoint (lua_State *L) {
  engine->CheckPoint(luaL_checkstring(L, 1));
  return 0;
}

static int engine_ClientCmd (lua_State *L) {
  engine->ClientCmd(luaL_checkstring(L, 1));
  return 0;
}

static int engine_ClientCmd_Unrestricted (lua_State *L) {
  engine->ClientCmd_Unrestricted(luaL_checkstring(L, 1));
  return 0;
}

static int engine_Con_IsVisible (lua_State *L) {
  lua_pushboolean(L, engine->Con_IsVisible());
  return 1;
}

static int engine_CopyFrameBufferToMaterial (lua_State *L) {
  lua_pushboolean(L, engine->CopyFrameBufferToMaterial(luaL_checkstring(L, 1)));
  return 1;
}

static int engine_CullBox (lua_State *L) {
  lua_pushboolean(L, engine->CullBox(luaL_checkvector(L, 1), luaL_checkvector(L, 2)));
  return 1;
}

static int engine_DoesBoxTouchAreaFrustum (lua_State *L) {
  lua_pushboolean(L, engine->DoesBoxTouchAreaFrustum(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checkint(L, 3)));
  return 1;
}

static int engine_DrawPortals (lua_State *L) {
  engine->DrawPortals();
  return 0;
}

static int engine_EngineStats_BeginFrame (lua_State *L) {
  engine->EngineStats_BeginFrame();
  return 0;
}

static int engine_EngineStats_EndFrame (lua_State *L) {
  engine->EngineStats_EndFrame();
  return 0;
}

static int engine_ExecuteClientCmd (lua_State *L) {
  engine->ExecuteClientCmd(luaL_checkstring(L, 1));
  return 0;
}

static int engine_FireEvents (lua_State *L) {
  engine->FireEvents();
  return 0;
}

static int engine_GameLumpSize (lua_State *L) {
  engine->GameLumpSize(luaL_checkint(L, 1));
  return 1;
}

static int engine_GameLumpVersion (lua_State *L) {
  engine->GameLumpVersion(luaL_checkint(L, 1));
  return 1;
}

static int engine_GetAppID (lua_State *L) {
  lua_pushinteger(L, engine->GetAppID());
  return 1;
}

static int engine_GetDXSupportLevel (lua_State *L) {
  lua_pushinteger(L, engine->GetDXSupportLevel());
  return 1;
}

static int engine_GetEngineBuildNumber (lua_State *L) {
  lua_pushinteger(L, engine->GetEngineBuildNumber());
  return 1;
}

static int engine_GetGameDirectory (lua_State *L) {
  lua_pushstring(L, engine->GetGameDirectory());
  return 1;
}

static int engine_GetLastTimeStamp (lua_State *L) {
  lua_pushnumber(L, engine->GetLastTimeStamp());
  return 1;
}

static int engine_GetLevelName (lua_State *L) {
  lua_pushstring(L, engine->GetLevelName());
  return 1;
}

static int engine_GetLightForPoint (lua_State *L) {
  Vector v = engine->GetLightForPoint(luaL_checkvector(L, 1), luaL_checkboolean(L, 2));
  lua_pushvector(L, v);
  return 1;
}

static int engine_GetLightForPointFast (lua_State *L) {
  Vector v = engine->GetLightForPointFast(luaL_checkvector(L, 1), luaL_checkboolean(L, 2));
  lua_pushvector(L, v);
  return 1;
}

static int engine_GetLocalPlayer (lua_State *L) {
  lua_pushinteger(L, engine->GetLocalPlayer());
  return 1;
}

static int engine_GetMainMenuBackgroundName (lua_State *L) {
  char * dest = "";
  engine->GetMainMenuBackgroundName(dest, luaL_checkint(L, 2));
  lua_pushstring(L, dest);
  return 1;
}

static int engine_GetMapEntitiesString (lua_State *L) {
  lua_pushstring(L, engine->GetMapEntitiesString());
  return 1;
}

static int engine_GetMaxClients (lua_State *L) {
  lua_pushinteger(L, engine->GetMaxClients());
  return 1;
}

static int engine_GetMostRecentSaveGame (lua_State *L) {
  lua_pushstring(L, engine->GetMostRecentSaveGame());
  return 1;
}

static int engine_GetPlayerForUserID (lua_State *L) {
  lua_pushinteger(L, engine->GetPlayerForUserID(luaL_checkint(L, 1)));
  return 1;
}

static int engine_GetPlayerInfo (lua_State *L) {
  player_info_t pinfo;
  lua_pushboolean(L, engine->GetPlayerInfo(luaL_checkint(L, 1), &pinfo));
  lua_newtable(L);
  lua_pushstring(L, "name");
  lua_pushstring(L, pinfo.name);
  lua_settable(L, -3);
  lua_pushstring(L, "userID");
  lua_pushinteger(L, pinfo.userID);
  lua_settable(L, -3);
  lua_pushstring(L, "guid");
  lua_pushstring(L, pinfo.guid);
  lua_settable(L, -3);
  lua_pushstring(L, "friendsID");
  lua_pushinteger(L, pinfo.friendsID);
  lua_settable(L, -3);
  lua_pushstring(L, "friendsName");
  lua_pushstring(L, pinfo.friendsName);
  lua_settable(L, -3);
  lua_pushstring(L, "fakeplayer");
  lua_pushboolean(L, pinfo.fakeplayer);
  lua_settable(L, -3);
  lua_pushstring(L, "ishltv");
  lua_pushboolean(L, pinfo.ishltv);
  lua_settable(L, -3);
  return 2;
}

static int engine_GetProductVersionString (lua_State *L) {
  lua_pushstring(L, engine->GetProductVersionString());
  return 1;
}

static int engine_GetScreenAspectRatio (lua_State *L) {
  lua_pushnumber(L, engine->GetScreenAspectRatio());
  return 1;
}

static int engine_GetScreenSize (lua_State *L) {
  int width, height;
  engine->GetScreenSize(width, height);
  lua_pushinteger(L, width);
  lua_pushinteger(L, height);
  return 2;
}

static int engine_GetUILanguage (lua_State *L) {
  char * dest = "";
  engine->GetUILanguage(dest, luaL_checkint(L, 1));
  lua_pushstring(L, dest);
  return 1;
}

static int engine_GrabPreColorCorrectedFrame (lua_State *L) {
  engine->GrabPreColorCorrectedFrame(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int engine_IsBoxInViewCluster (lua_State *L) {
  luaL_checkint(L, engine->IsBoxInViewCluster(luaL_checkvector(L, 1), luaL_checkvector(L, 2)));
  return 1;
}

static int engine_IsBoxVisible (lua_State *L) {
  luaL_checkint(L, engine->IsBoxVisible(luaL_checkvector(L, 1), luaL_checkvector(L, 2)));
  return 1;
}

static int engine_IsConnected (lua_State *L) {
  lua_pushboolean(L, engine->IsConnected());
  return 1;
}

static int engine_IsDrawingLoadingImage (lua_State *L) {
  lua_pushboolean(L, engine->IsDrawingLoadingImage());
  return 1;
}

static int engine_IsHammerRunning (lua_State *L) {
  lua_pushboolean(L, engine->IsHammerRunning());
  return 1;
}

static int engine_IsHLTV (lua_State *L) {
  lua_pushboolean(L, engine->IsHLTV());
  return 1;
}

static int engine_IsInEditMode (lua_State *L) {
  lua_pushboolean(L, engine->IsInEditMode());
  return 1;
}

static int engine_IsInGame (lua_State *L) {
  lua_pushboolean(L, engine->IsInGame());
  return 1;
}

static int engine_IsLevelMainMenuBackground (lua_State *L) {
  lua_pushboolean(L, engine->IsLevelMainMenuBackground());
  return 1;
}

static int engine_IsLowViolence (lua_State *L) {
  lua_pushboolean(L, engine->IsLowViolence());
  return 1;
}

static int engine_IsOccluded (lua_State *L) {
  luaL_checkboolean(L, engine->IsOccluded(luaL_checkvector(L, 1), luaL_checkvector(L, 2)));
  return 1;
}

static int engine_IsPaused (lua_State *L) {
  lua_pushboolean(L, engine->IsPaused());
  return 1;
}

static int engine_IsPlayingDemo (lua_State *L) {
  lua_pushboolean(L, engine->IsPlayingDemo());
  return 1;
}

static int engine_IsPlayingTimeDemo (lua_State *L) {
  lua_pushboolean(L, engine->IsPlayingTimeDemo());
  return 1;
}

static int engine_IsRecordingDemo (lua_State *L) {
  lua_pushboolean(L, engine->IsRecordingDemo());
  return 1;
}

static int engine_IsSaveInProgress (lua_State *L) {
  lua_pushboolean(L, engine->IsSaveInProgress());
  return 1;
}

static int engine_IsSkyboxVisibleFromPoint (lua_State *L) {
  lua_pushinteger(L, engine->IsSkyboxVisibleFromPoint(luaL_checkvector(L, 1)));
  return 1;
}

static int engine_IsTakingScreenshot (lua_State *L) {
  lua_pushboolean(L, engine->IsTakingScreenshot());
  return 1;
}

static int engine_Key_BindingForKey (lua_State *L) {
  ButtonCode_t code = (ButtonCode_t)luaL_checkint(L, 1);
  lua_pushstring(L, engine->Key_BindingForKey(code));
  return 1;
}

static int engine_Key_LookupBinding (lua_State *L) {
  lua_pushstring(L, engine->Key_LookupBinding(luaL_checkstring(L, 1)));
  return 1;
}

static int engine_LevelLeafCount (lua_State *L) {
  lua_pushinteger(L, engine->LevelLeafCount());
  return 1;
}

static int engine_LightStyleValue (lua_State *L) {
  lua_pushnumber(L, engine->LightStyleValue(luaL_checkint(L, 1)));
  return 1;
}

static int engine_LinearToGamma (lua_State *L) {
  float linear = luaL_checknumber(L, 1);
  float gamma;
  engine->LinearToGamma(&linear, &gamma);
  lua_pushnumber(L, gamma);
  return 1;
}

static int engine_MapHasHDRLighting (lua_State *L) {
  lua_pushboolean(L, engine->MapHasHDRLighting());
  return 1;
}

static int engine_MapLoadFailed (lua_State *L) {
  lua_pushboolean(L, engine->MapLoadFailed());
  return 1;
}

static int engine_OnStorageDeviceDetached (lua_State *L) {
  engine->OnStorageDeviceDetached();
  return 0;
}

static int engine_REMOVED_SteamProcessCall (lua_State *L) {
  bool finished = luaL_checkboolean(L, 1);
  lua_pushboolean(L, engine->REMOVED_SteamProcessCall(finished));
  return 1;
}

static int engine_ResetDemoInterpolation (lua_State *L) {
  engine->ResetDemoInterpolation();
  return 0;
}

static int engine_SentenceGroupIndexFromName (lua_State *L) {
  lua_pushinteger(L, engine->SentenceGroupIndexFromName(luaL_checkstring(L, 1)));
  return 1;
}

static int engine_SentenceGroupNameFromIndex (lua_State *L) {
  lua_pushstring(L, engine->SentenceGroupNameFromIndex(luaL_checkint(L, 1)));
  return 1;
}

static int engine_SentenceIndexFromName (lua_State *L) {
  lua_pushinteger(L, engine->SentenceIndexFromName(luaL_checkstring(L, 1)));
  return 1;
}

static int engine_SentenceLength (lua_State *L) {
  lua_pushnumber(L, engine->SentenceLength(luaL_checkint(L, 1)));
  return 1;
}

static int engine_SentenceNameFromIndex (lua_State *L) {
  lua_pushstring(L, engine->SentenceNameFromIndex(luaL_checkint(L, 1)));
  return 1;
}

static int engine_ServerCmd (lua_State *L) {
  engine->ServerCmd(luaL_checkstring(L, 1), luaL_checkboolean(L, 2));
  return 0;
}

static int engine_SetMapLoadFailed (lua_State *L) {
  engine->SetMapLoadFailed(luaL_checkboolean(L, 1));
  return 0;
}

static int engine_SetRestrictClientCommands (lua_State *L) {
  engine->SetRestrictClientCommands(luaL_checkboolean(L, 1));
  return 0;
}

static int engine_SetRestrictServerCommands (lua_State *L) {
  engine->SetRestrictServerCommands(luaL_checkboolean(L, 1));
  return 0;
}

static int engine_Sound_ExtraUpdate (lua_State *L) {
  engine->Sound_ExtraUpdate();
  return 0;
}

static int engine_StartKeyTrapMode (lua_State *L) {
  engine->StartKeyTrapMode();
  return 0;
}

static int engine_StartXboxExitingProcess (lua_State *L) {
  engine->StartXboxExitingProcess();
  return 0;
}

static int engine_SupportsHDR (lua_State *L) {
  lua_pushboolean(L, engine->SupportsHDR());
  return 1;
}

static int engine_Time (lua_State *L) {
  lua_pushnumber(L, engine->Time());
  return 1;
}


static const luaL_Reg enginelib[] = {
  {"ActivateOccluder",   engine_ActivateOccluder},
  {"ChangeTeam",  engine_ChangeTeam},
  {"CheckDoneKeyTrapping",  engine_CheckDoneKeyTrapping},
  {"CheckPoint",  engine_CheckPoint},
  {"ClientCmd", engine_ClientCmd},
  {"ClientCmd_Unrestricted",  engine_ClientCmd_Unrestricted},
  {"Con_IsVisible",  engine_Con_IsVisible},
  {"CopyFrameBufferToMaterial",   engine_CopyFrameBufferToMaterial},
  {"CullBox",   engine_CullBox},
  {"DoesBoxTouchAreaFrustum",   engine_DoesBoxTouchAreaFrustum},
  {"DrawPortals",   engine_DrawPortals},
  {"EngineStats_BeginFrame",   engine_EngineStats_BeginFrame},
  {"EngineStats_EndFrame",   engine_EngineStats_EndFrame},
  {"GameLumpSize",   engine_GameLumpSize},
  {"GetAppID",   engine_GetAppID},
  {"GetDXSupportLevel", engine_GetDXSupportLevel},
  {"GetEngineBuildNumber",   engine_GetEngineBuildNumber},
  {"GetGameDirectory", engine_GetGameDirectory},
  {"GetLastTimeStamp", engine_GetLastTimeStamp},
  {"GetLevelName",   engine_GetLevelName},
  {"GetLightForPoint",   engine_GetLightForPoint},
  {"GetLightForPointFast",   engine_GetLightForPointFast},
  {"GetLocalPlayer",   engine_GetLocalPlayer},
  {"GetMainMenuBackgroundName",   engine_GetMainMenuBackgroundName},
  {"GetMapEntitiesString",   engine_GetMapEntitiesString},
  {"GetMaxClients",   engine_GetMaxClients},
  {"GetMostRecentSaveGame",   engine_GetMostRecentSaveGame},
  {"GetPlayerForUserID",   engine_GetPlayerForUserID},
  {"GetPlayerInfo",   engine_GetPlayerInfo},
  {"GetProductVersionString",   engine_GetProductVersionString},
  {"GetScreenAspectRatio",     engine_GetScreenAspectRatio},
  {"GetScreenSize",     engine_GetScreenSize},
  {"GetUILanguage",     engine_GetUILanguage},
  {"GrabPreColorCorrectedFrame",     engine_GrabPreColorCorrectedFrame},
  {"IsBoxInViewCluster",     engine_IsBoxInViewCluster},
  {"IsBoxVisible",     engine_IsBoxVisible},
  {"IsConnected", engine_IsConnected},
  {"IsDrawingLoadingImage",   engine_IsDrawingLoadingImage},
  {"IsHammerRunning",   engine_IsHammerRunning},
  {"IsHLTV",  engine_IsHLTV},
  {"IsInEditMode",  engine_IsInEditMode},
  {"IsInGame",  engine_IsInGame},
  {"IsLevelMainMenuBackground",  engine_IsLevelMainMenuBackground},
  {"IsLowViolence",  engine_IsLowViolence},
  {"IsOccluded",  engine_IsOccluded},
  {"IsPaused",  engine_IsPaused},
  {"IsPlayingDemo",  engine_IsPlayingDemo},
  {"IsPlayingTimeDemo",  engine_IsPlayingTimeDemo},
  {"IsRecordingDemo",  engine_IsRecordingDemo},
  {"IsSaveInProgress",   engine_IsSaveInProgress},
  {"IsSkyboxVisibleFromPoint",   engine_IsSkyboxVisibleFromPoint},
  {"IsTakingScreenshot",   engine_IsTakingScreenshot},
  {"Key_BindingForKey",   engine_Key_BindingForKey},
  {"Key_LookupBinding",   engine_Key_LookupBinding},
  {"LevelLeafCount",   engine_LevelLeafCount},
  {"LightStyleValue",   engine_LightStyleValue},
  {"LinearToGamma",   engine_LinearToGamma},
  {"MapHasHDRLighting",   engine_MapHasHDRLighting},
  {"MapLoadFailed",   engine_MapLoadFailed},
  {"OnStorageDeviceDetached",   engine_OnStorageDeviceDetached},
  {"REMOVED_SteamProcessCall",   engine_REMOVED_SteamProcessCall},
  {"ResetDemoInterpolation",   engine_ResetDemoInterpolation},
  {"SentenceGroupIndexFromName",   engine_SentenceGroupIndexFromName},
  {"SentenceGroupNameFromIndex",   engine_SentenceGroupNameFromIndex},
  {"SentenceIndexFromName",   engine_SentenceIndexFromName},
  {"SentenceLength",   engine_SentenceLength},
  {"SentenceNameFromIndex",   engine_SentenceNameFromIndex},
  {"ServerCmd",   engine_ServerCmd},
  {"SetMapLoadFailed",   engine_SetMapLoadFailed},
  {"SetRestrictClientCommands",   engine_SetRestrictClientCommands},
  {"SetRestrictServerCommands",   engine_SetRestrictServerCommands},
  {"Sound_ExtraUpdate",   engine_Sound_ExtraUpdate},
  {"StartKeyTrapMode",   engine_StartKeyTrapMode},
  {"StartXboxExitingProcess",   engine_StartXboxExitingProcess},
  {"SupportsHDR",   engine_SupportsHDR},
  {"Time",   engine_Time},
  {NULL, NULL}
};


/*
** Open engine library
*/
LUALIB_API int luaopen_engine (lua_State *L) {
  luaL_register(L, LUA_ENGINELIBNAME, enginelib);
  return 1;
}

