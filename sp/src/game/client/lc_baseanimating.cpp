//===== Copy	right © 1996-2005, Valve Corporation, All rights reserved. ==//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//
#define lc_baseanimating_cpp

#include "cbase.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lc_baseanimating.h"
#include "lbaseentity_shared.h"
#include "lbaseplayer_shared.h"
#include "mathlib/lvector.h"
#include "lvphysics_interface.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

/*
** access functions (stack -> C)
*/


LUA_API lua_CBaseAnimating *lua_toanimating (lua_State *L, int idx) {
  CBaseHandle *hEntity = dynamic_cast<CBaseHandle *>((CBaseHandle *)lua_touserdata(L, idx));
  if (hEntity == NULL)
    return NULL;
  return dynamic_cast<lua_CBaseAnimating *>(hEntity->Get());
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushanimating (lua_State *L, CBaseAnimating *pEntity) {
  CBaseHandle *hEntity = (CBaseHandle *)lua_newuserdata(L, sizeof(CBaseHandle));
  hEntity->Set(pEntity);
  luaL_getmetatable(L, "CBaseAnimating");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_CBaseAnimating *luaL_checkanimating (lua_State *L, int narg) {
  lua_CBaseAnimating *d = lua_toanimating(L, narg);
  if (d == NULL)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "CBaseAnimating expected, got NULL entity");
  return d;
}


static int CBaseAnimating_AddEntity (lua_State *L) {
  luaL_checkanimating(L, 1)->AddEntity();
  return 0;
}

static int CBaseAnimating_AddToClientSideAnimationList (lua_State *L) {
  luaL_checkanimating(L, 1)->AddToClientSideAnimationList();
  return 0;
}

static int CBaseAnimating_BecomeRagdollOnClient (lua_State *L) {
  lua_pushanimating(L, luaL_checkanimating(L, 1)->BecomeRagdollOnClient());
  return 1;
}

static int CBaseAnimating_CalculateIKLocks (lua_State *L) {
  luaL_checkanimating(L, 1)->CalculateIKLocks(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseAnimating_ClampCycle (lua_State *L) {
  lua_pushnumber(L, luaL_checkanimating(L, 1)->ClampCycle(luaL_checknumber(L, 2), luaL_checkboolean(L, 3)));
  return 1;
}

static int CBaseAnimating_Clear (lua_State *L) {
  luaL_checkanimating(L, 1)->Clear();
  return 0;
}

static int CBaseAnimating_ClearRagdoll (lua_State *L) {
  luaL_checkanimating(L, 1)->ClearRagdoll();
  return 0;
}

static int CBaseAnimating_ClientSideAnimationChanged (lua_State *L) {
  luaL_checkanimating(L, 1)->ClientSideAnimationChanged();
  return 0;
}

static int CBaseAnimating_ComputeClientSideAnimationFlags (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->ComputeClientSideAnimationFlags());
  return 1;
}

static int CBaseAnimating_ComputeEntitySpaceHitboxSurroundingBox (lua_State *L) {
  Vector pVecWorldMins, pVecWorldMaxs;
  lua_pushboolean(L, luaL_checkanimating(L, 1)->ComputeEntitySpaceHitboxSurroundingBox(&pVecWorldMins, &pVecWorldMaxs));
  lua_pushvector(L, pVecWorldMins);
  lua_pushvector(L, pVecWorldMaxs);
  return 3;
}

static int CBaseAnimating_ComputeHitboxSurroundingBox (lua_State *L) {
  Vector pVecWorldMins, pVecWorldMaxs;
  lua_pushboolean(L, luaL_checkanimating(L, 1)->ComputeHitboxSurroundingBox(&pVecWorldMins, &pVecWorldMaxs));
  lua_pushvector(L, pVecWorldMins);
  lua_pushvector(L, pVecWorldMaxs);
  return 3;
}

static int CBaseAnimating_CreateRagdollCopy (lua_State *L) {
  lua_pushanimating(L, luaL_checkanimating(L, 1)->CreateRagdollCopy());
  return 1;
}

static int CBaseAnimating_CreateUnragdollInfo (lua_State *L) {
  luaL_checkanimating(L, 1)->CreateUnragdollInfo(luaL_checkanimating(L, 2));
  return 0;
}

static int CBaseAnimating_DisableMuzzleFlash (lua_State *L) {
  luaL_checkanimating(L, 1)->DisableMuzzleFlash();
  return 0;
}

static int CBaseAnimating_DispatchMuzzleEffect (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->DispatchMuzzleEffect(luaL_checkstring(L, 2), luaL_checkboolean(L, 3)));
  return 1;
}

static int CBaseAnimating_DoMuzzleFlash (lua_State *L) {
  luaL_checkanimating(L, 1)->DoMuzzleFlash();
  return 0;
}

static int CBaseAnimating_DrawClientHitboxes (lua_State *L) {
  luaL_checkanimating(L, 1)->DrawClientHitboxes(luaL_optnumber(L, 2, 0.0f), luaL_optboolean(L, 3, false));
  return 0;
}

static int CBaseAnimating_DrawModel (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->DrawModel(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_FindBodygroupByName (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->FindBodygroupByName(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseAnimating_FindFollowedEntity (lua_State *L) {
  lua_pushanimating(L, luaL_checkanimating(L, 1)->FindFollowedEntity());
  return 1;
}

static int CBaseAnimating_FindTransitionSequence (lua_State *L) {
  int piDir;
  lua_pushinteger(L, luaL_checkanimating(L, 1)->FindTransitionSequence(luaL_checkint(L, 2), luaL_checkint(L, 3), &piDir));
  lua_pushinteger(L, piDir);
  return 2;
}

static int CBaseAnimating_FireEvent (lua_State *L) {
  luaL_checkanimating(L, 1)->FireEvent(luaL_checkvector(L, 2), luaL_checkangle(L, 3), luaL_checkint(L, 4), luaL_checkstring(L, 5));
  return 0;
}

static int CBaseAnimating_FireObsoleteEvent (lua_State *L) {
  luaL_checkanimating(L, 1)->FireObsoleteEvent(luaL_checkvector(L, 2), luaL_checkangle(L, 3), luaL_checkint(L, 4), luaL_checkstring(L, 5));
  return 0;
}

static int CBaseAnimating_ForceClientSideAnimationOn (lua_State *L) {
  luaL_checkanimating(L, 1)->ForceClientSideAnimationOn();
  return 0;
}

static int CBaseAnimating_FrameAdvance (lua_State *L) {
  lua_pushnumber(L, luaL_checkanimating(L, 1)->FrameAdvance(luaL_optnumber(L, 2, 0.0f)));
  return 1;
}

static int CBaseAnimating_GetAimEntOrigin (lua_State *L) {
  luaL_checkanimating(L, 1)->GetAimEntOrigin(luaL_checkentity(L, 2), &luaL_checkvector(L, 3), &luaL_checkangle(L, 4));
  return 0;
}

static int CBaseAnimating_GetAnimTimeInterval (lua_State *L) {
  lua_pushnumber(L, luaL_checkanimating(L, 1)->GetAnimTimeInterval());
  return 1;
}

static int CBaseAnimating_GetAttachment (lua_State *L) {
  switch(lua_type(L, 2)) {
	case LUA_TNUMBER:
      {
        if (lua_gettop(L) <= 3)
          lua_pushboolean(L, luaL_checkanimating(L, 1)->GetAttachment(luaL_checkint(L, 2), luaL_checkvector(L, 3)));
        else
          lua_pushboolean(L, luaL_checkanimating(L, 1)->GetAttachment(luaL_checkint(L, 2), luaL_checkvector(L, 3), luaL_checkangle(L, 4)));
        break;
      }
	case LUA_TSTRING:
	default:
      {
        if (lua_gettop(L) <= 3)
          lua_pushboolean(L, luaL_checkanimating(L, 1)->GetAttachment(luaL_checkstring(L, 2), luaL_checkvector(L, 3)));
        else
          lua_pushboolean(L, luaL_checkanimating(L, 1)->GetAttachment(luaL_checkstring(L, 2), luaL_checkvector(L, 3), luaL_checkangle(L, 4)));
        break;
	  }
  }
  return 1;
}

static int CBaseAnimating_GetAttachmentLocal (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->GetAttachmentLocal(luaL_checkint(L, 2), luaL_checkvector(L, 3), luaL_checkangle(L, 4)));
  return 1;
}

static int CBaseAnimating_GetAttachmentVelocity (lua_State *L) {
  Vector originVel;
  Quaternion angleVel;
  lua_pushboolean(L, luaL_checkanimating(L, 1)->GetAttachmentVelocity(luaL_checkint(L, 2), originVel, angleVel));
  lua_pushvector(L, originVel);
  // Todo: implement Quaternion class!!
  // lua_pushquaternion(L, &angleVel);
  return 2;
}

static int CBaseAnimating_GetBaseAnimating (lua_State *L) {
  lua_pushanimating(L, luaL_checkanimating(L, 1)->GetBaseAnimating());
  return 1;
}

static int CBaseAnimating_GetBlendedLinearVelocity (lua_State *L) {
  Vector pVec;
  luaL_checkanimating(L, 1)->GetBlendedLinearVelocity(&pVec);
  lua_pushvector(L, pVec);
  return 1;
}

static int CBaseAnimating_GetBody (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetBody());
  return 1;
}

static int CBaseAnimating_GetBodygroup (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetBodygroup(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetBodygroupCount (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetBodygroupCount(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetBodygroupName (lua_State *L) {
  lua_pushstring(L, luaL_checkanimating(L, 1)->GetBodygroupName(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetBoneControllers (lua_State *L) {
  float controllers[MAXSTUDIOBONECTRLS];
  luaL_checkanimating(L, 1)->GetBoneControllers(controllers);
  int i;
  for( i=0; i < MAXSTUDIOBONECTRLS; i++)
  {
	  lua_pushnumber(L, controllers[ i ]);
  }
  return MAXSTUDIOBONECTRLS;
}

static int CBaseAnimating_GetBonePosition (lua_State *L) {
  luaL_checkanimating(L, 1)->GetBonePosition(luaL_checkint(L, 2), luaL_checkvector(L, 3), luaL_checkangle(L, 4));
  return 0;
}

static int CBaseAnimating_GetClientSideFade (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetClientSideFade());
  return 1;
}

static int CBaseAnimating_GetCollideType (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetCollideType());
  return 1;
}

static int CBaseAnimating_GetCycle (lua_State *L) {
  lua_pushnumber(L, luaL_checkanimating(L, 1)->GetCycle());
  return 1;
}

static int CBaseAnimating_GetFlexControllerName (lua_State *L) {
  lua_pushstring(L, luaL_checkanimating(L, 1)->GetFlexControllerName((LocalFlexController_t)luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetFlexControllerType (lua_State *L) {
  lua_pushstring(L, luaL_checkanimating(L, 1)->GetFlexControllerType((LocalFlexController_t)luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetFlexDescFacs (lua_State *L) {
  lua_pushstring(L, luaL_checkanimating(L, 1)->GetFlexDescFacs(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetHitboxSet (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetHitboxSet());
  return 1;
}

static int CBaseAnimating_GetHitboxSetCount (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetHitboxSetCount());
  return 1;
}

static int CBaseAnimating_GetHitboxSetName (lua_State *L) {
  lua_pushstring(L, luaL_checkanimating(L, 1)->GetHitboxSetName());
  return 1;
}

/*static int CBaseAnimating_GetModelWidthScale(lua_State* L) {
  lua_pushnumber(L, luaL_checkanimating(L, 1)->GetModelWidthScale());
  return 1;
}*/

static int CBaseAnimating_GetNumBodyGroups (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetNumBodyGroups());
  return 1;
}

static int CBaseAnimating_GetNumFlexControllers (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetNumFlexControllers());
  return 1;
}

static int CBaseAnimating_GetPlaybackRate (lua_State *L) {
  lua_pushnumber(L, luaL_checkanimating(L, 1)->GetPlaybackRate());
  return 1;
}

static int CBaseAnimating_GetPoseParameter (lua_State *L) {
  lua_pushnumber(L, luaL_checkanimating(L, 1)->GetPoseParameter(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetPoseParameterRange (lua_State *L) {
  float minValue, maxValue;
  lua_pushboolean(L, luaL_checkanimating(L, 1)->GetPoseParameterRange(luaL_checkint(L, 2), minValue, maxValue));
  lua_pushnumber(L, minValue);
  lua_pushnumber(L, maxValue);
  return 3;
}

static int CBaseAnimating_GetRenderAngles (lua_State *L) {
  QAngle v = luaL_checkanimating(L, 1)->GetRenderAngles();
  lua_pushangle(L, v);
  return 1;
}

static int CBaseAnimating_GetRenderBounds (lua_State *L) {
  Vector theMins, theMaxs;
  luaL_checkanimating(L, 1)->GetRenderBounds(theMins, theMaxs);
  lua_pushvector(L, theMins);
  lua_pushvector(L, theMaxs);
  return 2;
}

static int CBaseAnimating_GetRenderOrigin (lua_State *L) {
  Vector v = luaL_checkanimating(L, 1)->GetRenderOrigin();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseAnimating_GetSequence (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetSequence());
  return 1;
}

static int CBaseAnimating_GetSequenceActivity (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetSequenceActivity(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetSequenceActivityName (lua_State *L) {
  lua_pushstring(L, luaL_checkanimating(L, 1)->GetSequenceActivityName(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetSequenceGroundSpeed (lua_State *L) {
  lua_pushnumber(L, luaL_checkanimating(L, 1)->GetSequenceGroundSpeed(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetSequenceLinearMotion (lua_State *L) {
  Vector pVec;
  luaL_checkanimating(L, 1)->GetSequenceLinearMotion(luaL_checkint(L, 2), &pVec);
  lua_pushvector(L, pVec);
  return 1;
}

static int CBaseAnimating_GetSequenceName (lua_State *L) {
  lua_pushstring(L, luaL_checkanimating(L, 1)->GetSequenceName(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_GetServerIntendedCycle (lua_State *L) {
  lua_pushnumber(L, luaL_checkanimating(L, 1)->GetServerIntendedCycle());
  return 1;
}

static int CBaseAnimating_GetSkin (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->GetSkin());
  return 1;
}

static int CBaseAnimating_IgniteRagdoll (lua_State *L) {
  luaL_checkanimating(L, 1)->IgniteRagdoll(luaL_checkanimating(L, 2));
  return 0;
}

static int CBaseAnimating_InitBoneSetupThreadPool (lua_State *L) {
  CBaseAnimating::InitBoneSetupThreadPool();
  return 0;
}

static int CBaseAnimating_InitModelEffects (lua_State *L) {
  luaL_checkanimating(L, 1)->InitModelEffects();
  return 0;
}

static int CBaseAnimating_InternalDrawModel (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->InternalDrawModel(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_Interpolate (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->Interpolate(luaL_checknumber(L, 2)));
  return 1;
}

static int CBaseAnimating_InvalidateBoneCache (lua_State *L) {
  luaL_checkanimating(L, 1)->InvalidateBoneCache();
  return 0;
}

static int CBaseAnimating_InvalidateBoneCaches (lua_State *L) {
  CBaseAnimating::InvalidateBoneCaches();
  return 0;
}

static int CBaseAnimating_InvalidateMdlCache (lua_State *L) {
  luaL_checkanimating(L, 1)->InvalidateMdlCache();
  return 0;
}

static int CBaseAnimating_IsActivityFinished (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->IsActivityFinished());
  return 1;
}

static int CBaseAnimating_IsBoneCacheValid (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->IsBoneCacheValid());
  return 1;
}

static int CBaseAnimating_IsOnFire (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->IsOnFire());
  return 1;
}

static int CBaseAnimating_IsRagdoll (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->IsRagdoll());
  return 1;
}

static int CBaseAnimating_IsSelfAnimating (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->IsSelfAnimating());
  return 1;
}

static int CBaseAnimating_IsSequenceFinished (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->IsSequenceFinished());
  return 1;
}

static int CBaseAnimating_IsSequenceLooping (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->IsSequenceLooping(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_IsViewModel (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->IsViewModel());
  return 1;
}

static int CBaseAnimating_LookupActivity (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->LookupActivity(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseAnimating_LookupAttachment (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->LookupAttachment(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseAnimating_LookupBone (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->LookupBone(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseAnimating_LookupPoseParameter (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->LookupPoseParameter(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseAnimating_LookupRandomAttachment (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->LookupRandomAttachment(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseAnimating_LookupSequence (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->LookupSequence(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseAnimating_NotifyShouldTransmit (lua_State *L) {
  luaL_checkanimating(L, 1)->NotifyShouldTransmit((ShouldTransmitState_t)luaL_checkint(L, 2));
  return 0;
}

static int CBaseAnimating_OnDataChanged (lua_State *L) {
  luaL_checkanimating(L, 1)->OnDataChanged((DataUpdateType_t)luaL_checkint(L, 2));
  return 0;
}

static int CBaseAnimating_OnPreDataChanged (lua_State *L) {
  luaL_checkanimating(L, 1)->OnPreDataChanged((DataUpdateType_t)luaL_checkint(L, 2));
  return 0;
}

static int CBaseAnimating_PopBoneAccess (lua_State *L) {
  C_BaseAnimating::PopBoneAccess(luaL_checkstring(L, 1));
  return 0;
}

static int CBaseAnimating_PostDataUpdate (lua_State *L) {
  luaL_checkanimating(L, 1)->PostDataUpdate((DataUpdateType_t)luaL_checkint(L, 2));
  return 0;
}

static int CBaseAnimating_PreDataUpdate (lua_State *L) {
  luaL_checkanimating(L, 1)->PreDataUpdate((DataUpdateType_t)luaL_checkint(L, 2));
  return 0;
}

static int CBaseAnimating_ProcessMuzzleFlashEvent (lua_State *L) {
  luaL_checkanimating(L, 1)->ProcessMuzzleFlashEvent();
  return 0;
}

static int CBaseAnimating_PushAllowBoneAccess (lua_State *L) {
  C_BaseAnimating::PushAllowBoneAccess(luaL_checkboolean(L, 1), luaL_checkboolean(L, 2), luaL_checkstring(L, 3));
  return 0;
}

static int CBaseAnimating_RagdollMoved (lua_State *L) {
  luaL_checkanimating(L, 1)->RagdollMoved();
  return 0;
}

static int CBaseAnimating_Release (lua_State *L) {
  luaL_checkanimating(L, 1)->Release();
  return 0;
}

static int CBaseAnimating_RemoveFromClientSideAnimationList (lua_State *L) {
  luaL_checkanimating(L, 1)->RemoveFromClientSideAnimationList();
  return 0;
}

/*static int CBaseAnimating_ResetEventsParity(lua_State* L) {
  luaL_checkanimating(L, 1)->ResetEventsParity();
  return 0;
}*/

static int CBaseAnimating_ResetLatched (lua_State *L) {
  luaL_checkanimating(L, 1)->ResetLatched();
  return 0;
}

static int CBaseAnimating_ResetSequence (lua_State *L) {
  luaL_checkanimating(L, 1)->ResetSequence(luaL_checkint(L, 2));
  return 0;
}

static int CBaseAnimating_ResetSequenceInfo (lua_State *L) {
  luaL_checkanimating(L, 1)->ResetSequenceInfo();
  return 0;
}

static int CBaseAnimating_RetrieveRagdollInfo (lua_State *L) {
  Vector pos;
  Quaternion q;
  lua_pushboolean(L, luaL_checkanimating(L, 1)->RetrieveRagdollInfo(&pos, &q));
  lua_pushvector(L, pos);
  // Todo: implement Quaternion class!!
  // lua_pushquaternion(L, &q);
  return 2;
}

static int CBaseAnimating_SelectWeightedSequence (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->SelectWeightedSequence(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_SequenceDuration (lua_State *L) {
  if (lua_isnoneornil(L, 2))
    lua_pushnumber(L, luaL_checkanimating(L, 1)->SequenceDuration());
  else
	lua_pushnumber(L, luaL_checkanimating(L, 1)->SequenceDuration(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseAnimating_SequenceLoops (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->SequenceLoops());
  return 1;
}

static int CBaseAnimating_SetBodygroup (lua_State *L) {
  luaL_checkanimating(L, 1)->SetBodygroup(luaL_checkint(L, 2), luaL_checkint(L, 3));
  return 0;
}

static int CBaseAnimating_SetBoneController (lua_State *L) {
  lua_pushnumber(L, luaL_checkanimating(L, 1)->SetBoneController(luaL_checkint(L, 2), luaL_checknumber(L, 3)));
  return 1;
}

static int CBaseAnimating_SetCycle (lua_State *L) {
  luaL_checkanimating(L, 1)->SetCycle(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseAnimating_SetHitboxSet (lua_State *L) {
  luaL_checkanimating(L, 1)->SetHitboxSet(luaL_checkint(L, 2));
  return 0;
}

static int CBaseAnimating_SetHitboxSetByName (lua_State *L) {
  luaL_checkanimating(L, 1)->SetHitboxSetByName(luaL_checkstring(L, 2));
  return 0;
}

/*static int CBaseAnimating_SetModelWidthScale(lua_State* L) {
  luaL_checkanimating(L, 1)->SetModelWidthScale(luaL_checknumber(L, 2));
  return 0;
}*/

static int CBaseAnimating_SetPlaybackRate (lua_State *L) {
  luaL_checkanimating(L, 1)->SetPlaybackRate(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseAnimating_SetPoseParameter (lua_State *L) {
  switch(lua_type(L, 2)) {
	case LUA_TNUMBER:
	  lua_pushnumber(L, luaL_checkanimating(L, 1)->SetPoseParameter(luaL_checkint(L, 2), luaL_checknumber(L, 3)));
	  break;
	case LUA_TSTRING:
	default:
	  lua_pushnumber(L, luaL_checkanimating(L, 1)->SetPoseParameter(luaL_checkstring(L, 2), luaL_checknumber(L, 3)));
	  break;
  }
  return 1;
}

static int CBaseAnimating_SetPredictable (lua_State *L) {
  luaL_checkanimating(L, 1)->SetPredictable(luaL_checkboolean(L, 2));
  return 0;
}

static int CBaseAnimating_SetPredictionEligible (lua_State *L) {
  luaL_checkanimating(L, 1)->SetPredictionEligible(luaL_checkboolean(L, 2));
  return 0;
}

static int CBaseAnimating_SetPredictionPlayer (lua_State *L) {
  luaL_checkanimating(L, 1)->SetPredictionPlayer(luaL_checkplayer(L, 2));
  return 0;
}

static int CBaseAnimating_SetReceivedSequence (lua_State *L) {
  luaL_checkanimating(L, 1)->SetReceivedSequence();
  return 0;
}

static int CBaseAnimating_SetSequence (lua_State *L) {
  luaL_checkanimating(L, 1)->SetSequence(luaL_checkint(L, 2));
  return 0;
}

static int CBaseAnimating_SetServerIntendedCycle (lua_State *L) {
  luaL_checkanimating(L, 1)->SetServerIntendedCycle(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseAnimating_ShadowCastType (lua_State *L) {
  lua_pushinteger(L, luaL_checkanimating(L, 1)->ShadowCastType());
  return 1;
}

static int CBaseAnimating_ShouldMuzzleFlash (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->ShouldMuzzleFlash());
  return 1;
}

static int CBaseAnimating_ShouldResetSequenceOnNewModel (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->ShouldResetSequenceOnNewModel());
  return 1;
}

static int CBaseAnimating_ShutdownBoneSetupThreadPool (lua_State *L) {
  CBaseAnimating::ShutdownBoneSetupThreadPool();
  return 0;
}

static int CBaseAnimating_Simulate (lua_State *L) {
  luaL_checkanimating(L, 1)->Simulate();
  return 0;
}

static int CBaseAnimating_StudioFrameAdvance (lua_State *L) {
  luaL_checkanimating(L, 1)->StudioFrameAdvance();
  return 0;
}

static int CBaseAnimating_ThreadedBoneSetup (lua_State *L) {
  CBaseAnimating::ThreadedBoneSetup();
  return 0;
}

static int CBaseAnimating_TransferDissolveFrom (lua_State *L) {
  luaL_checkanimating(L, 1)->TransferDissolveFrom(luaL_checkanimating(L, 2));
  return 0;
}

static int CBaseAnimating_UncorrectViewModelAttachment (lua_State *L) {
  luaL_checkanimating(L, 1)->UncorrectViewModelAttachment(luaL_checkvector(L, 2));
  return 0;
}

static int CBaseAnimating_UpdateClientSideAnimation (lua_State *L) {
  luaL_checkanimating(L, 1)->UpdateClientSideAnimation();
  return 0;
}

static int CBaseAnimating_UpdateClientSideAnimations (lua_State *L) {
  CBaseAnimating::UpdateClientSideAnimations();
  return 0;
}

static int CBaseAnimating_UpdateIKLocks (lua_State *L) {
  luaL_checkanimating(L, 1)->UpdateIKLocks(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseAnimating_UseClientSideAnimation (lua_State *L) {
  luaL_checkanimating(L, 1)->UseClientSideAnimation();
  return 0;
}

static int CBaseAnimating_UsesPowerOfTwoFrameBufferTexture (lua_State *L) {
  lua_pushboolean(L, luaL_checkanimating(L, 1)->UsesPowerOfTwoFrameBufferTexture());
  return 1;
}

static int CBaseAnimating_VPhysicsGetObjectList (lua_State *L) {
  IPhysicsObject *pList[VPHYSICS_MAX_OBJECT_LIST_COUNT];
  int count = luaL_checkanimating(L, 1)->VPhysicsGetObjectList( pList, ARRAYSIZE(pList) );
  lua_pushinteger(L, count);
  lua_newtable(L);
  for( int i = 0 ; i < count ; i++ )
  {
	  lua_pushinteger(L, i);
	  lua_pushphysicsobject(L, pList[i]);
	  lua_settable(L, -3);
  }
  return 2;
}

static int CBaseAnimating_VPhysicsUpdate (lua_State *L) {
  luaL_checkanimating(L, 1)->VPhysicsUpdate(luaL_checkphysicsobject(L, 2));
  return 0;
}

static int CBaseAnimating___index (lua_State *L) {
  CBaseAnimating *pEntity = lua_toanimating(L, 1);
  if (pEntity == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
	lua_pushfstring(L, "%s:%d: attempt to index a NULL entity", ar2.short_src, ar1.currentline);
	return lua_error(L);
  }
  if (pEntity->m_nTableReference != LUA_NOREF) {
    lua_getref(L, pEntity->m_nTableReference);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 2);
      lua_getmetatable(L, 1);
      lua_pushvalue(L, 2);
      lua_gettable(L, -2);
      if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        luaL_getmetatable(L, "CBaseEntity");
        lua_pushvalue(L, 2);
        lua_gettable(L, -2);
      }
    }
  }
  else {
    lua_getmetatable(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 2);
      luaL_getmetatable(L, "CBaseEntity");
      lua_pushvalue(L, 2);
      lua_gettable(L, -2);
    }
  }
  return 1;
}

static int CBaseAnimating___newindex (lua_State *L) {
  CBaseAnimating *pEntity = lua_toanimating(L, 1);
  if (pEntity == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
	lua_pushfstring(L, "%s:%d: attempt to index a NULL entity", ar2.short_src, ar1.currentline);
	return lua_error(L);
  }
  const char *field = luaL_checkstring(L, 2);
  if (Q_strcmp(field, "m_bClientSideAnimation") == 0)
    pEntity->m_bClientSideAnimation = luaL_checkboolean(L, 3);
  else if (Q_strcmp(field, "m_bLastClientSideFrameReset") == 0)
    pEntity->m_bLastClientSideFrameReset = luaL_checkboolean(L, 3);
  else if (Q_strcmp(field, "m_nBody") == 0)
    pEntity->m_nBody = luaL_checkint(L, 3);
  else if (Q_strcmp(field, "m_nHitboxSet") == 0)
    pEntity->m_nHitboxSet = luaL_checkint(L, 3);
  else if (Q_strcmp(field, "m_nSkin") == 0)
    pEntity->m_nSkin = luaL_checkint(L, 3);
  else {
    if (pEntity->m_nTableReference == LUA_NOREF) {
      lua_newtable(L);
      pEntity->m_nTableReference = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_getref(L, pEntity->m_nTableReference);
    lua_pushvalue(L, 3);
    lua_setfield(L, -2, field);
	lua_pop(L, 1);
  }
  return 0;
}

static int CBaseAnimating___eq (lua_State *L) {
  lua_pushboolean(L, lua_toanimating(L, 1) == lua_toanimating(L, 2));
  return 1;
}

static int CBaseAnimating___tostring (lua_State *L) {
  CBaseAnimating *pEntity = lua_toanimating(L, 1);
  if (pEntity == NULL)
    lua_pushstring(L, "NULL");
  else
    lua_pushfstring(L, "CBaseAnimating: %d \"%s\"", pEntity->entindex(), pEntity->GetClassname());
  return 1;
}


static const luaL_Reg CBaseAnimatingmeta[] = {
  {"AddEntity", CBaseAnimating_AddEntity},
  {"AddToClientSideAnimationList", CBaseAnimating_AddToClientSideAnimationList},
  {"BecomeRagdollOnClient", CBaseAnimating_BecomeRagdollOnClient},
  {"CalculateIKLocks", CBaseAnimating_CalculateIKLocks},
  {"ClampCycle", CBaseAnimating_ClampCycle},
  {"Clear", CBaseAnimating_Clear},
  {"ClearRagdoll", CBaseAnimating_ClearRagdoll},
  {"ClientSideAnimationChanged", CBaseAnimating_ClientSideAnimationChanged},
  {"ComputeClientSideAnimationFlags", CBaseAnimating_ComputeClientSideAnimationFlags},
  {"ComputeEntitySpaceHitboxSurroundingBox", CBaseAnimating_ComputeEntitySpaceHitboxSurroundingBox},
  {"ComputeHitboxSurroundingBox", CBaseAnimating_ComputeHitboxSurroundingBox},
  {"CreateRagdollCopy", CBaseAnimating_CreateRagdollCopy},
  {"CreateUnragdollInfo", CBaseAnimating_CreateUnragdollInfo},
  {"DisableMuzzleFlash", CBaseAnimating_DisableMuzzleFlash},
  {"DispatchMuzzleEffect", CBaseAnimating_DispatchMuzzleEffect},
  {"DoMuzzleFlash", CBaseAnimating_DoMuzzleFlash},
  {"DrawClientHitboxes", CBaseAnimating_DrawClientHitboxes},
  {"DrawModel", CBaseAnimating_DrawModel},
  {"FindBodygroupByName", CBaseAnimating_FindBodygroupByName},
  {"FindFollowedEntity", CBaseAnimating_FindFollowedEntity},
  {"FindTransitionSequence", CBaseAnimating_FindTransitionSequence},
  {"FireEvent", CBaseAnimating_FireEvent},
  {"FireObsoleteEvent", CBaseAnimating_FireObsoleteEvent},
  {"ForceClientSideAnimationOn", CBaseAnimating_ForceClientSideAnimationOn},
  {"FrameAdvance", CBaseAnimating_FrameAdvance},
  {"GetAimEntOrigin", CBaseAnimating_GetAimEntOrigin},
  {"GetAnimTimeInterval", CBaseAnimating_GetAnimTimeInterval},
  {"GetAttachment", CBaseAnimating_GetAttachment},
  {"GetAttachmentLocal", CBaseAnimating_GetAttachmentLocal},
  {"GetAttachmentVelocity", CBaseAnimating_GetAttachmentVelocity},
  {"GetBaseAnimating", CBaseAnimating_GetBaseAnimating},
  {"GetBlendedLinearVelocity", CBaseAnimating_GetBlendedLinearVelocity},
  {"GetBody", CBaseAnimating_GetBody},
  {"GetBodygroup", CBaseAnimating_GetBodygroup},
  {"GetBodygroupCount", CBaseAnimating_GetBodygroupCount},
  {"GetBodygroupName", CBaseAnimating_GetBodygroupName},
  {"GetBoneControllers", CBaseAnimating_GetBoneControllers},
  {"GetBonePosition", CBaseAnimating_GetBonePosition},
  {"GetClientSideFade", CBaseAnimating_GetClientSideFade},
  {"GetCollideType", CBaseAnimating_GetCollideType},
  {"GetCycle", CBaseAnimating_GetCycle},
  {"GetFlexControllerName", CBaseAnimating_GetFlexControllerName},
  {"GetFlexControllerType", CBaseAnimating_GetFlexControllerType},
  {"GetFlexDescFacs", CBaseAnimating_GetFlexDescFacs},
  {"GetHitboxSet", CBaseAnimating_GetHitboxSet},
  {"GetHitboxSetCount", CBaseAnimating_GetHitboxSetCount},
  {"GetHitboxSetName", CBaseAnimating_GetHitboxSetName},
  //{"GetModelWidthScale", CBaseAnimating_GetModelWidthScale},
  {"GetNumBodyGroups", CBaseAnimating_GetNumBodyGroups},
  {"GetNumFlexControllers", CBaseAnimating_GetNumFlexControllers},
  {"GetPlaybackRate", CBaseAnimating_GetPlaybackRate},
  {"GetPoseParameter", CBaseAnimating_GetPoseParameter},
  {"GetPoseParameterRange", CBaseAnimating_GetPoseParameterRange},
  {"GetRenderAngles", CBaseAnimating_GetRenderAngles},
  {"GetRenderBounds", CBaseAnimating_GetRenderBounds},
  {"GetRenderOrigin", CBaseAnimating_GetRenderOrigin},
  {"GetSequence", CBaseAnimating_GetSequence},
  {"GetSequenceActivity", CBaseAnimating_GetSequenceActivity},
  {"GetSequenceActivityName", CBaseAnimating_GetSequenceActivityName},
  {"GetSequenceGroundSpeed", CBaseAnimating_GetSequenceGroundSpeed},
  {"GetSequenceLinearMotion", CBaseAnimating_GetSequenceLinearMotion},
  {"GetSequenceName", CBaseAnimating_GetSequenceName},
  {"GetServerIntendedCycle", CBaseAnimating_GetServerIntendedCycle},
  {"GetSkin", CBaseAnimating_GetSkin},
  {"IgniteRagdoll", CBaseAnimating_IgniteRagdoll},
  {"InitBoneSetupThreadPool", CBaseAnimating_InitBoneSetupThreadPool},
  {"InitModelEffects", CBaseAnimating_InitModelEffects},
  {"InternalDrawModel", CBaseAnimating_InternalDrawModel},
  {"Interpolate", CBaseAnimating_Interpolate},
  {"InvalidateBoneCache", CBaseAnimating_InvalidateBoneCache},
  {"InvalidateBoneCaches", CBaseAnimating_InvalidateBoneCaches},
  {"InvalidateMdlCache", CBaseAnimating_InvalidateMdlCache},
  {"IsActivityFinished", CBaseAnimating_IsActivityFinished},
  {"IsBoneCacheValid", CBaseAnimating_IsBoneCacheValid},
  {"IsOnFire", CBaseAnimating_IsOnFire},
  {"IsRagdoll", CBaseAnimating_IsRagdoll},
  {"IsSelfAnimating", CBaseAnimating_IsSelfAnimating},
  {"IsSequenceFinished", CBaseAnimating_IsSequenceFinished},
  {"IsSequenceLooping", CBaseAnimating_IsSequenceLooping},
  {"IsViewModel", CBaseAnimating_IsViewModel},
  {"LookupActivity", CBaseAnimating_LookupActivity},
  {"LookupAttachment", CBaseAnimating_LookupAttachment},
  {"LookupBone", CBaseAnimating_LookupBone},
  {"LookupPoseParameter", CBaseAnimating_LookupPoseParameter},
  {"LookupRandomAttachment", CBaseAnimating_LookupRandomAttachment},
  {"LookupSequence", CBaseAnimating_LookupSequence},
  {"NotifyShouldTransmit", CBaseAnimating_NotifyShouldTransmit},
  {"OnDataChanged", CBaseAnimating_OnDataChanged},
  {"OnPreDataChanged", CBaseAnimating_OnPreDataChanged},
  {"PopBoneAccess", CBaseAnimating_PopBoneAccess},
  {"PostDataUpdate", CBaseAnimating_PostDataUpdate},
  {"PreDataUpdate", CBaseAnimating_PreDataUpdate},
  {"ProcessMuzzleFlashEvent", CBaseAnimating_ProcessMuzzleFlashEvent},
  {"PushAllowBoneAccess", CBaseAnimating_PushAllowBoneAccess},
  {"RagdollMoved", CBaseAnimating_RagdollMoved},
  {"Release", CBaseAnimating_Release},
  {"RemoveFromClientSideAnimationList", CBaseAnimating_RemoveFromClientSideAnimationList},
  //{"ResetEventsParity", CBaseAnimating_ResetEventsParity},
  {"ResetLatched", CBaseAnimating_ResetLatched},
  {"ResetSequence", CBaseAnimating_ResetSequence},
  {"ResetSequenceInfo", CBaseAnimating_ResetSequenceInfo},
  {"RetrieveRagdollInfo", CBaseAnimating_RetrieveRagdollInfo},
  {"SelectWeightedSequence", CBaseAnimating_SelectWeightedSequence},
  {"SequenceDuration", CBaseAnimating_SequenceDuration},
  {"SequenceLoops", CBaseAnimating_SequenceLoops},
  {"SetBodygroup", CBaseAnimating_SetBodygroup},
  {"SetBoneController", CBaseAnimating_SetBoneController},
  {"SetCycle", CBaseAnimating_SetCycle},
  {"SetHitboxSet", CBaseAnimating_SetHitboxSet},
  {"SetHitboxSetByName", CBaseAnimating_SetHitboxSetByName},
  //{"SetModelWidthScale", CBaseAnimating_SetModelWidthScale},
  {"SetPlaybackRate", CBaseAnimating_SetPlaybackRate},
  {"SetPoseParameter", CBaseAnimating_SetPoseParameter},
  {"SetPredictable", CBaseAnimating_SetPredictable},
  {"SetPredictionEligible", CBaseAnimating_SetPredictionEligible},
  {"SetPredictionPlayer", CBaseAnimating_SetPredictionPlayer},
  {"SetReceivedSequence", CBaseAnimating_SetReceivedSequence},
  {"SetSequence", CBaseAnimating_SetSequence},
  {"SetServerIntendedCycle", CBaseAnimating_SetServerIntendedCycle},
  {"ShadowCastType", CBaseAnimating_ShadowCastType},
  {"ShouldMuzzleFlash", CBaseAnimating_ShouldMuzzleFlash},
  {"ShouldResetSequenceOnNewModel", CBaseAnimating_ShouldResetSequenceOnNewModel},
  {"ShutdownBoneSetupThreadPool", CBaseAnimating_ShutdownBoneSetupThreadPool},
  {"Simulate", CBaseAnimating_Simulate},
  {"StudioFrameAdvance", CBaseAnimating_StudioFrameAdvance},
  {"ThreadedBoneSetup", CBaseAnimating_ThreadedBoneSetup},
  {"TransferDissolveFrom", CBaseAnimating_TransferDissolveFrom},
  {"UncorrectViewModelAttachment", CBaseAnimating_UncorrectViewModelAttachment},
  {"UpdateClientSideAnimation", CBaseAnimating_UpdateClientSideAnimation},
  {"UpdateClientSideAnimations", CBaseAnimating_UpdateClientSideAnimations},
  {"UpdateIKLocks", CBaseAnimating_UpdateIKLocks},
  {"UseClientSideAnimation", CBaseAnimating_UseClientSideAnimation},
  {"UsesPowerOfTwoFrameBufferTexture", CBaseAnimating_UsesPowerOfTwoFrameBufferTexture},
  {"VPhysicsGetObjectList", CBaseAnimating_VPhysicsGetObjectList},
  {"VPhysicsUpdate", CBaseAnimating_VPhysicsUpdate},
  {"__index", CBaseAnimating___index},
  {"__newindex", CBaseAnimating___newindex},
  {"__eq", CBaseAnimating___eq},
  {"__tostring", CBaseAnimating___tostring},
  {NULL, NULL}
};


/*
** Open CBaseAnimating object
*/
LUALIB_API int luaopen_CBaseAnimating (lua_State *L) {
  luaL_newmetatable(L, LUA_BASEANIMATINGLIBNAME);
  luaL_register(L, NULL, CBaseAnimatingmeta);
  lua_pushstring(L, "entity");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "entity" */
  return 1;
}

