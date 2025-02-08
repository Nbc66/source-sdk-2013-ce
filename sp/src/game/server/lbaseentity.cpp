//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The base class from which all game entities are derived.
//
//===========================================================================//

#define lbaseentity_cpp

#include "cbase.h"
#include "luamanager.h"
#include "lbaseentity_shared.h"
#include "ltakedamageinfo.h"
#include "mathlib/lvector.h"
#include "items.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static int CBaseEntity_RecalcHasPlayerChildBit (lua_State *L) {
  luaL_checkentity(L, 1)->RecalcHasPlayerChildBit();
  return 0;
}

static int CBaseEntity_DoesHavePlayerChild (lua_State *L) {
  luaL_checkentity(L, 1)->DoesHavePlayerChild();
  return 1;
}

static int CBaseEntity_SetNavIgnore (lua_State *L) {
  luaL_checkentity(L, 1)->SetNavIgnore(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_ClearNavIgnore (lua_State *L) {
  luaL_checkentity(L, 1)->ClearNavIgnore();
  return 0;
}

static int CBaseEntity_IsNavIgnored (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsNavIgnored());
  return 1;
}

static int CBaseEntity_SetTransmitState (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->SetTransmitState(luaL_checkinteger(L, 2)));
  return 1;
}

static int CBaseEntity_GetTransmitState (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetTransmitState());
  return 1;
}

static int CBaseEntity_UpdateTransmitState (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->UpdateTransmitState());
  return 1;
}

static int CBaseEntity_IncrementTransmitStateOwnedCounter (lua_State *L) {
  luaL_checkentity(L, 1)->IncrementTransmitStateOwnedCounter();
  return 0;
}

static int CBaseEntity_DecrementTransmitStateOwnedCounter (lua_State *L) {
  luaL_checkentity(L, 1)->DecrementTransmitStateOwnedCounter();
  return 0;
}

static int CBaseEntity_DetectInSkybox (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->DetectInSkybox());
  return 1;
}

static int CBaseEntity_GetEntitySkybox (lua_State *L) {
  lua_pushentity(L, (CBaseEntity *)luaL_checkentity(L, 1)->GetEntitySkybox());
  return 1;
}

static int CBaseEntity_PostConstructor (lua_State *L) {
  luaL_checkentity(L, 1)->PostConstructor(luaL_checkstring(L, 2));
  return 0;
}

static int CBaseEntity_PostClientActive (lua_State *L) {
  luaL_checkentity(L, 1)->PostClientActive();
  return 0;
}

static int CBaseEntity_ValidateEntityConnections (lua_State *L) {
  luaL_checkentity(L, 1)->ValidateEntityConnections();
  return 0;
}

/*static int CBaseEntity_PostClientMessagesSent(lua_State* L) {
  luaL_checkentity(L, 1)->PostClientMessagesSent();
  return 0;
}*/

static int CBaseEntity_SetName (lua_State *L) {
  luaL_checkentity(L, 1)->SetName(MAKE_STRING( luaL_checkstring(L, 2) ));
  return 0;
}

static int CBaseEntity_GetEntityName (lua_State *L) {
  lua_pushstring(L, STRING( luaL_checkentity(L, 1)->GetEntityName()));
  return 1;
}

static int CBaseEntity_NameMatches (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->NameMatches(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseEntity_ClassMatches (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->ClassMatches(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseEntity_GetSpawnFlags (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetSpawnFlags());
  return 1;
}

static int CBaseEntity_AddSpawnFlags (lua_State *L) {
  luaL_checkentity(L, 1)->AddSpawnFlags(luaL_checkinteger(L, 2));
  return 0;
}

static int CBaseEntity_RemoveSpawnFlags (lua_State *L) {
  luaL_checkentity(L, 1)->RemoveSpawnFlags(luaL_checkinteger(L, 2));
  return 0;
}

static int CBaseEntity_ClearSpawnFlags (lua_State *L) {
  luaL_checkentity(L, 1)->ClearSpawnFlags();
  return 0;
}

static int CBaseEntity_HasSpawnFlags (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->HasSpawnFlags(luaL_checkinteger(L, 2)));
  return 1;
}

static int CBaseEntity_MakeDormant (lua_State *L) {
  luaL_checkentity(L, 1)->MakeDormant();
  return 0;
}

static int CBaseEntity_RemoveDeferred (lua_State *L) {
  luaL_checkentity(L, 1)->RemoveDeferred();
  return 0;
}

static int CBaseEntity_AcceptInput (lua_State *L) {
  variant_t emptyVariant;
  lua_pushboolean(L, luaL_checkentity(L, 1)->AcceptInput(luaL_checkstring(L, 2), lua_toentity(L, 3), lua_toentity(L, 4), emptyVariant, luaL_checkint(L, 5)));
  return 1;
}

static int CBaseEntity_GetInputDispatchEffectPosition (lua_State *L) {
  Vector pVector;
  QAngle pAngle;
  luaL_checkentity(L, 1)->GetInputDispatchEffectPosition(luaL_checkstring(L, 2), pVector, pAngle);
  lua_pushvector(L, pVector);
  lua_pushangle(L, pAngle);
  return 2;
}

static int CBaseEntity_EntityText (lua_State *L) {
  luaL_checkentity(L, 1)->EntityText(luaL_checkinteger(L, 2), luaL_checkstring(L, 3), luaL_checknumber(L, 4), luaL_checkinteger(L, 5), luaL_checkinteger(L, 6), luaL_checkinteger(L, 7), luaL_checkinteger(L, 8));
  return 0;
}

static int CBaseEntity_DrawDebugGeometryOverlays (lua_State *L) {
  luaL_checkentity(L, 1)->DrawDebugGeometryOverlays();
  return 0;
}

static int CBaseEntity_DrawDebugTextOverlays (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->DrawDebugTextOverlays());
  return 1;
}

static int CBaseEntity_DrawTimedOverlays (lua_State *L) {
  luaL_checkentity(L, 1)->DrawTimedOverlays();
  return 0;
}

static int CBaseEntity_DrawBBoxOverlay (lua_State *L) {
  luaL_checkentity(L, 1)->DrawBBoxOverlay(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_DrawAbsBoxOverlay (lua_State *L) {
  luaL_checkentity(L, 1)->DrawAbsBoxOverlay();
  return 0;
}

static int CBaseEntity_DrawRBoxOverlay (lua_State *L) {
  luaL_checkentity(L, 1)->DrawRBoxOverlay();
  return 0;
}

static int CBaseEntity_SendDebugPivotOverlay (lua_State *L) {
  luaL_checkentity(L, 1)->SendDebugPivotOverlay();
  return 0;
}

static int CBaseEntity_AddTimedOverlay (lua_State *L) {
  luaL_checkentity(L, 1)->AddTimedOverlay(luaL_checkstring(L, 2), luaL_checkinteger(L, 3));
  return 0;
}

static int CBaseEntity_RequiredEdictIndex (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->RequiredEdictIndex());
  return 1;
}

static int CBaseEntity_MoveDone (lua_State *L) {
  luaL_checkentity(L, 1)->MoveDone();
  return 0;
}

static int CBaseEntity_Instance (lua_State *L) {
  lua_pushentity(L, CBaseEntity::Instance(luaL_checkinteger(L, 1)));
  return 1;
}

static int CBaseEntity_AddContext (lua_State *L) {
  luaL_checkentity(L, 1)->AddContext(luaL_checkstring(L, 2));
  return 0;
}

static int CBaseEntity_DispatchResponse (lua_State *L) {
  luaL_checkentity(L, 1)->DispatchResponse(luaL_checkstring(L, 2));
  return 0;
}

static int CBaseEntity_Classify (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->Classify());
  return 1;
}

static int CBaseEntity_DeathNotice (lua_State *L) {
  luaL_checkentity(L, 1)->DeathNotice(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_ShouldAttractAutoAim (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->ShouldAttractAutoAim(luaL_checkentity(L, 2)));
  return 1;
}

static int CBaseEntity_GetAutoAimRadius (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetAutoAimRadius());
  return 1;
}

static int CBaseEntity_GetAutoAimCenter (lua_State *L) {
  lua_pushvector(L, luaL_checkentity(L, 1)->GetAutoAimCenter());
  return 1;
}

static int CBaseEntity_PassesDamageFilter (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->PassesDamageFilter(luaL_checkdamageinfo(L, 2)));
  return 1;
}

static int CBaseEntity_CanBeHitByMeleeAttack (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->CanBeHitByMeleeAttack(luaL_checkentity(L, 2)));
  return 1;
}

static int CBaseEntity_OnTakeDamage (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->OnTakeDamage(luaL_checkdamageinfo(L, 2)));
  return 1;
}

static int CBaseEntity_TakeDamage (lua_State *L) {
  luaL_checkentity(L, 1)->TakeDamage(luaL_checkdamageinfo(L, 2));
  return 0;
}

static int CBaseEntity_TakeHealth (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->TakeHealth(luaL_checkinteger(L, 2), luaL_checkinteger(L, 3)));
  return 1;
}

static int CBaseEntity_Event_Killed (lua_State *L) {
  luaL_checkentity(L, 1)->Event_Killed(luaL_checkdamageinfo(L, 2));
  return 0;
}

static int CBaseEntity_Event_KilledOther (lua_State *L) {
  luaL_checkentity(L, 1)->Event_KilledOther(luaL_checkentity(L, 2), luaL_checkdamageinfo(L, 3));
  return 0;
}

static int CBaseEntity_IsTriggered (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsTriggered(luaL_checkentity(L, 2)));
  return 1;
}

static int CBaseEntity_GetDelay (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetDelay());
  return 1;
}

static int CBaseEntity_IsMoving (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsMoving());
  return 1;
}

static int CBaseEntity_IsWorld (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsWorld());
  return 1;
}

static int CBaseEntity_AddPoints (lua_State *L) {
  luaL_checkentity(L, 1)->AddPoints(luaL_checkinteger(L, 2), luaL_checkboolean(L, 3));
  return 0;
}

static int CBaseEntity_AddPointsToTeam (lua_State *L) {
  luaL_checkentity(L, 1)->AddPointsToTeam(luaL_checkinteger(L, 2), luaL_checkboolean(L, 3));
  return 0;
}

static int CBaseEntity_OnControls (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->OnControls(luaL_checkentity(L, 2)));
  return 1;
}

static int CBaseEntity_HasTarget (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->HasTarget(MAKE_STRING( luaL_checkstring(L, 2) )));
  return 1;
}

static int CBaseEntity_IsNetClient (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsNetClient());
  return 1;
}

static int CBaseEntity_IsTemplate (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsTemplate());
  return 1;
}

static int CBaseEntity_IsViewable (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsViewable());
  return 1;
}

static int CBaseEntity_IsInAnyTeam (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsInAnyTeam());
  return 1;
}

static int CBaseEntity_TeamID (lua_State *L) {
  lua_pushstring(L, luaL_checkentity(L, 1)->TeamID());
  return 1;
}

static int CBaseEntity_CanStandOn (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->CanStandOn(luaL_checkentity(L, 2)));
  return 1;
}

static int CBaseEntity_GetEnemy (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->GetEnemy());
  return 1;
}

static int CBaseEntity_VelocityPunch (lua_State *L) {
  luaL_checkentity(L, 1)->VelocityPunch(luaL_checkvector(L, 2));
  return 0;
}

static int CBaseEntity_GetNextTarget (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->GetNextTarget());
  return 1;
}

static int CBaseEntity_Use (lua_State *L) {
  luaL_checkentity(L, 1)->Use(luaL_checkentity(L, 2), luaL_checkentity(L, 3), (USE_TYPE)luaL_checkinteger(L, 4), luaL_checknumber(L, 5));
  return 0;
}

static int CBaseEntity_StartTouch (lua_State *L) {
  luaL_checkentity(L, 1)->StartTouch(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_Touch (lua_State *L) {
  luaL_checkentity(L, 1)->Touch(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_EndTouch (lua_State *L) {
  luaL_checkentity(L, 1)->EndTouch(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_StartBlocked (lua_State *L) {
  luaL_checkentity(L, 1)->StartBlocked(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_Blocked (lua_State *L) {
  luaL_checkentity(L, 1)->Blocked(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_EndBlocked (lua_State *L) {
  luaL_checkentity(L, 1)->EndBlocked();
  return 0;
}

static int CBaseEntity_PhysicsTouchTriggers (lua_State *L) {
  luaL_checkentity(L, 1)->PhysicsTouchTriggers();
  return 0;
}

static int CBaseEntity_SUB_DoNothing (lua_State *L) {
  luaL_checkentity(L, 1)->SUB_DoNothing();
  return 0;
}

static int CBaseEntity_SUB_StartFadeOut (lua_State *L) {
  luaL_checkentity(L, 1)->SUB_StartFadeOut(luaL_optnumber(L, 2, 10.0f), luaL_optboolean(L, 3, true));
  return 0;
}

static int CBaseEntity_SUB_StartFadeOutInstant (lua_State *L) {
  luaL_checkentity(L, 1)->SUB_StartFadeOutInstant();
  return 0;
}

static int CBaseEntity_SUB_FadeOut (lua_State *L) {
  luaL_checkentity(L, 1)->SUB_FadeOut();
  return 0;
}

static int CBaseEntity_SUB_Vanish (lua_State *L) {
  luaL_checkentity(L, 1)->SUB_Vanish();
  return 0;
}

static int CBaseEntity_SUB_CallUseToggle (lua_State *L) {
  luaL_checkentity(L, 1)->SUB_CallUseToggle();
  return 0;
}

static int CBaseEntity_SUB_PerformFadeOut (lua_State *L) {
  luaL_checkentity(L, 1)->SUB_PerformFadeOut();
  return 0;
}

static int CBaseEntity_SUB_AllowedToFade (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->SUB_AllowedToFade());
  return 1;
}

static int CBaseEntity_Teleport (lua_State *L) {
  luaL_checkentity(L, 1)->Teleport(&luaL_checkvector(L, 2), &luaL_checkangle(L, 3), &luaL_checkvector(L, 4));
  return 0;
}

static int CBaseEntity_ShouldToggle (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->ShouldToggle((USE_TYPE)luaL_checkinteger(L, 2), luaL_checkinteger(L, 3)));
  return 1;
}

static int CBaseEntity_Respawn (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->Respawn());
  return 1;
}

static int CBaseEntity_TraceAttackToTriggers (lua_State *L) {
  luaL_checkentity(L, 1)->TraceAttackToTriggers(luaL_checkdamageinfo(L, 2), luaL_checkvector(L, 3), luaL_checkvector(L, 4), luaL_checkvector(L, 5));
  return 0;
}

static int CBaseEntity_Intersects (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->Intersects(luaL_checkentity(L, 2)));
  return 1;
}

static int CBaseEntity_IsLockedByMaster (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsLockedByMaster());
  return 1;
}

static int CBaseEntity_SetMaxHealth (lua_State *L) {
  luaL_checkentity(L, 1)->SetMaxHealth(luaL_checkinteger(L, 2));
  return 0;
}

static int CBaseEntity_DumpResponseCriteria (lua_State *L) {
  luaL_checkentity(L, 1)->DumpResponseCriteria();
  return 0;
}

static int CBaseEntity_Create (lua_State *L) {
  lua_pushentity(L, CBaseEntity::Create(luaL_checkstring(L, 1), luaL_checkvector(L, 2), luaL_checkangle(L, 3), luaL_optentity(L, 4, NULL)));
  return 1;
}

static int CBaseEntity_CreateNoSpawn (lua_State *L) {
  lua_pushentity(L, CBaseEntity::CreateNoSpawn(luaL_checkstring(L, 1), luaL_checkvector(L, 2), luaL_checkangle(L, 3), luaL_optentity(L, 4, NULL)));
  return 1;
}

static int CBaseEntity_GetDamageType (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetDamageType());
  return 1;
}

static int CBaseEntity_GetDamage (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetDamage());
  return 1;
}

static int CBaseEntity_SetDamage (lua_State *L) {
  luaL_checkentity(L, 1)->SetDamage(luaL_checkinteger(L, 2));
  return 0;
}

static int CBaseEntity_BodyTarget (lua_State *L) {
  lua_pushvector(L, luaL_checkentity(L, 1)->BodyTarget(luaL_checkvector(L, 2), luaL_optboolean(L, 3, true)));
  return 1;
}

static int CBaseEntity_HeadTarget (lua_State *L) {
  lua_pushvector(L, luaL_checkentity(L, 1)->HeadTarget(luaL_checkvector(L, 2)));
  return 1;
}

static int CBaseEntity_GetSmoothedVelocity (lua_State *L) {
  lua_pushvector(L, luaL_checkentity(L, 1)->GetSmoothedVelocity());
  return 1;
}

static int CBaseEntity_GetVelocity (lua_State *L) {
  Vector vVelocity;
  AngularImpulse vAngVelocity;
  luaL_checkentity(L, 1)->GetVelocity(&vVelocity, &vAngVelocity);
  lua_pushvector(L, vVelocity);
  lua_pushvector(L, (Vector &)vAngVelocity);
  return 2;
}

static int CBaseEntity_GetFriction (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetFriction());
  return 1;
}

static int CBaseEntity_FVisible (lua_State *L) {
  if (lua_isuserdata(L, 2) && luaL_checkudata(L, 2, "Vector"))
	lua_pushboolean(L, luaL_checkentity(L, 1)->FVisible(luaL_checkvector(L, 2), luaL_optinteger(L, 3, MASK_BLOCKLOS)));
  else
	lua_pushboolean(L, luaL_checkentity(L, 1)->FVisible(luaL_checkentity(L, 2), luaL_optinteger(L, 3, MASK_BLOCKLOS)));
  return 1;
}

static int CBaseEntity_GetReceivedDamageScale (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetReceivedDamageScale(luaL_checkentity(L, 2)));
  return 1;
}

static int CBaseEntity_GetGroundVelocityToApply (lua_State *L) {
  Vector vecGroundVel;
  luaL_checkentity(L, 1)->GetGroundVelocityToApply(vecGroundVel);
  lua_pushvector(L, vecGroundVel);
  return 1;
}

static int CBaseEntity_PhysicsSplash (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->PhysicsSplash(luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5)));
  return 1;
}

static int CBaseEntity_Splash (lua_State *L) {
  luaL_checkentity(L, 1)->Splash();
  return 0;
}

static int CBaseEntity_ClearSolidFlags (lua_State *L) {
  luaL_checkentity(L, 1)->ClearSolidFlags();
  return 0;
}

static int CBaseEntity_SetElasticity (lua_State *L) {
  luaL_checkentity(L, 1)->SetElasticity(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetShadowCastDistance (lua_State *L) {
  if (!lua_isnoneornil(L, 3))
	luaL_checkentity(L, 1)->SetShadowCastDistance(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  else
	luaL_checkentity(L, 1)->SetShadowCastDistance(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_GetLocalTime (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetLocalTime());
  return 1;
}

static int CBaseEntity_IncrementLocalTime (lua_State *L) {
  luaL_checkentity(L, 1)->IncrementLocalTime(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_GetMoveDoneTime (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetMoveDoneTime());
  return 1;
}

static int CBaseEntity_SetMoveDoneTime (lua_State *L) {
  luaL_checkentity(L, 1)->SetMoveDoneTime(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_GetSoundEmissionOrigin (lua_State *L) {
  lua_pushvector(L, luaL_checkentity(L, 1)->GetSoundEmissionOrigin());
  return 1;
}

static int CBaseEntity_IsItem (lua_State *L) {
  CItem *pItem = dynamic_cast<CItem *>(luaL_checkentity(L, 1));

  if( pItem )
  {
    lua_pushboolean(L, true);
  }
  else
  {
    lua_pushboolean(L, false);
  }
  return 1;
}


static const luaL_Reg CBaseEntitymeta[] = {
  {"RecalcHasPlayerChildBit", CBaseEntity_RecalcHasPlayerChildBit},
  {"DoesHavePlayerChild", CBaseEntity_DoesHavePlayerChild},
  {"SetNavIgnore", CBaseEntity_SetNavIgnore},
  {"ClearNavIgnore", CBaseEntity_ClearNavIgnore},
  {"IsNavIgnored", CBaseEntity_IsNavIgnored},
  {"SetTransmitState", CBaseEntity_SetTransmitState},
  {"GetTransmitState", CBaseEntity_GetTransmitState},
  {"UpdateTransmitState", CBaseEntity_UpdateTransmitState},
  {"IncrementTransmitStateOwnedCounter", CBaseEntity_IncrementTransmitStateOwnedCounter},
  {"DecrementTransmitStateOwnedCounter", CBaseEntity_DecrementTransmitStateOwnedCounter},
  {"DetectInSkybox", CBaseEntity_DetectInSkybox},
  {"GetEntitySkybox", CBaseEntity_GetEntitySkybox},
  {"PostConstructor", CBaseEntity_PostConstructor},
  {"PostClientActive", CBaseEntity_PostClientActive},
  {"ValidateEntityConnections", CBaseEntity_ValidateEntityConnections},
  //{"PostClientMessagesSent", CBaseEntity_PostClientMessagesSent},
  {"SetName", CBaseEntity_SetName},
  {"GetEntityName", CBaseEntity_GetEntityName},
  {"NameMatches", CBaseEntity_NameMatches},
  {"ClassMatches", CBaseEntity_ClassMatches},
  {"GetSpawnFlags", CBaseEntity_GetSpawnFlags},
  {"AddSpawnFlags", CBaseEntity_AddSpawnFlags},
  {"RemoveSpawnFlags", CBaseEntity_RemoveSpawnFlags},
  {"ClearSpawnFlags", CBaseEntity_ClearSpawnFlags},
  {"HasSpawnFlags", CBaseEntity_HasSpawnFlags},
  {"MakeDormant", CBaseEntity_MakeDormant},
  {"RemoveDeferred", CBaseEntity_RemoveDeferred},
  {"AcceptInput", CBaseEntity_AcceptInput},
  {"GetInputDispatchEffectPosition", CBaseEntity_GetInputDispatchEffectPosition},
  {"EntityText", CBaseEntity_EntityText},
  {"DrawDebugGeometryOverlays", CBaseEntity_DrawDebugGeometryOverlays},
  {"DrawDebugTextOverlays", CBaseEntity_DrawDebugTextOverlays},
  {"DrawTimedOverlays", CBaseEntity_DrawTimedOverlays},
  {"DrawBBoxOverlay", CBaseEntity_DrawBBoxOverlay},
  {"DrawAbsBoxOverlay", CBaseEntity_DrawAbsBoxOverlay},
  {"DrawRBoxOverlay", CBaseEntity_DrawRBoxOverlay},
  {"SendDebugPivotOverlay", CBaseEntity_SendDebugPivotOverlay},
  {"AddTimedOverlay", CBaseEntity_AddTimedOverlay},
  {"RequiredEdictIndex", CBaseEntity_RequiredEdictIndex},
  {"MoveDone", CBaseEntity_MoveDone},
  {"Instance", CBaseEntity_Instance},
  {"AddContext", CBaseEntity_AddContext},
  {"DispatchResponse", CBaseEntity_DispatchResponse},
  {"Classify", CBaseEntity_Classify},
  {"DeathNotice", CBaseEntity_DeathNotice},
  {"ShouldAttractAutoAim", CBaseEntity_ShouldAttractAutoAim},
  {"GetAutoAimRadius", CBaseEntity_GetAutoAimRadius},
  {"GetAutoAimCenter", CBaseEntity_GetAutoAimCenter},
  {"PassesDamageFilter", CBaseEntity_PassesDamageFilter},
  {"CanBeHitByMeleeAttack", CBaseEntity_CanBeHitByMeleeAttack},
  {"OnTakeDamage", CBaseEntity_OnTakeDamage},
  {"TakeDamage", CBaseEntity_TakeDamage},
  {"TakeHealth", CBaseEntity_TakeHealth},
  {"Event_Killed", CBaseEntity_Event_Killed},
  {"Event_KilledOther", CBaseEntity_Event_KilledOther},
  {"IsTriggered", CBaseEntity_IsTriggered},
  {"GetDelay", CBaseEntity_GetDelay},
  {"IsMoving", CBaseEntity_IsMoving},
  {"IsWorld", CBaseEntity_IsWorld},
  {"AddPoints", CBaseEntity_AddPoints},
  {"AddPointsToTeam", CBaseEntity_AddPointsToTeam},
  {"OnControls", CBaseEntity_OnControls},
  {"HasTarget", CBaseEntity_HasTarget},
  {"IsNetClient", CBaseEntity_IsNetClient},
  {"IsTemplate", CBaseEntity_IsTemplate},
  {"IsViewable", CBaseEntity_IsViewable},
  {"IsInAnyTeam", CBaseEntity_IsInAnyTeam},
  {"TeamID", CBaseEntity_TeamID},
  {"CanStandOn", CBaseEntity_CanStandOn},
  {"GetEnemy", CBaseEntity_GetEnemy},
  {"VelocityPunch", CBaseEntity_VelocityPunch},
  {"GetNextTarget", CBaseEntity_GetNextTarget},
  {"Use", CBaseEntity_Use},
  {"StartTouch", CBaseEntity_StartTouch},
  {"Touch", CBaseEntity_Touch},
  {"EndTouch", CBaseEntity_EndTouch},
  {"StartBlocked", CBaseEntity_StartBlocked},
  {"Blocked", CBaseEntity_Blocked},
  {"EndBlocked", CBaseEntity_EndBlocked},
  {"PhysicsTouchTriggers", CBaseEntity_PhysicsTouchTriggers},
  {"SUB_DoNothing", CBaseEntity_SUB_DoNothing},
  {"SUB_StartFadeOut", CBaseEntity_SUB_StartFadeOut},
  {"SUB_StartFadeOutInstant", CBaseEntity_SUB_StartFadeOutInstant},
  {"SUB_FadeOut", CBaseEntity_SUB_FadeOut},
  {"SUB_Vanish", CBaseEntity_SUB_Vanish},
  {"SUB_CallUseToggle", CBaseEntity_SUB_CallUseToggle},
  {"SUB_PerformFadeOut", CBaseEntity_SUB_PerformFadeOut},
  {"SUB_AllowedToFade", CBaseEntity_SUB_AllowedToFade},
  {"Teleport", CBaseEntity_Teleport},
  {"ShouldToggle", CBaseEntity_ShouldToggle},
  {"Respawn", CBaseEntity_Respawn},
  {"TraceAttackToTriggers", CBaseEntity_TraceAttackToTriggers},
  {"Intersects", CBaseEntity_Intersects},
  {"IsLockedByMaster", CBaseEntity_IsLockedByMaster},
  {"SetMaxHealth", CBaseEntity_SetMaxHealth},
  {"DumpResponseCriteria", CBaseEntity_DumpResponseCriteria},
  {"Create", CBaseEntity_Create},
  {"CreateNoSpawn", CBaseEntity_CreateNoSpawn},
  {"GetDamageType", CBaseEntity_GetDamageType},
  {"GetDamage", CBaseEntity_GetDamage},
  {"SetDamage", CBaseEntity_SetDamage},
  {"BodyTarget", CBaseEntity_BodyTarget},
  {"HeadTarget", CBaseEntity_HeadTarget},
  {"GetSmoothedVelocity", CBaseEntity_GetSmoothedVelocity},
  {"GetVelocity", CBaseEntity_GetVelocity},
  {"GetFriction", CBaseEntity_GetFriction},
  {"FVisible", CBaseEntity_FVisible},
  {"GetReceivedDamageScale", CBaseEntity_GetReceivedDamageScale},
  {"GetGroundVelocityToApply", CBaseEntity_GetGroundVelocityToApply},
  {"PhysicsSplash", CBaseEntity_PhysicsSplash},
  {"Splash", CBaseEntity_Splash},
  {"ClearSolidFlags", CBaseEntity_ClearSolidFlags},
  {"SetElasticity", CBaseEntity_SetElasticity},
  {"SetShadowCastDistance", CBaseEntity_SetShadowCastDistance},
  {"GetLocalTime", CBaseEntity_GetLocalTime},
  {"IncrementLocalTime", CBaseEntity_IncrementLocalTime},
  {"GetMoveDoneTime", CBaseEntity_GetMoveDoneTime},
  {"SetMoveDoneTime", CBaseEntity_SetMoveDoneTime},
  {"GetSoundEmissionOrigin", CBaseEntity_GetSoundEmissionOrigin},
  {"IsItem", CBaseEntity_IsItem},
  {NULL, NULL}
};


/*
** Open CBaseEntity object
*/
LUALIB_API int luaopen_CBaseEntity (lua_State *L) {
  luaL_getmetatable(L, "CBaseEntity");
  if (lua_isnoneornil(L, -1)) {
    lua_pop(L, 1);
    luaL_newmetatable(L, "CBaseEntity");
  }
  luaL_register(L, NULL, CBaseEntitymeta);
  return 1;
}

