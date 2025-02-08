//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The base class from which all game entities are derived.
//
//===========================================================================//

#define lbaseentity_shared_cpp

#include "cbase.h"
#ifdef CLIENT_DLL
#include "c_recipientfilter.h"
#define CRecipientFilter C_RecipientFilter
#else
#include "recipientfilter.h"
#endif
#include "takedamageinfo.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lbaseentity_shared.h"
#ifdef CLIENT_DLL
#include "lc_baseanimating.h"
#include "lc_recipientfilter.h"
#else
#include "lbaseanimating.h"
#include "lrecipientfilter.h"
#endif
#include "lbaseplayer_shared.h"
#include "lgametrace.h"
#include "SoundEmitterSystem/lisoundemittersystembase.h"
#include "lshareddefs.h"
#include "ltakedamageinfo.h"
#include "mathlib/lvector.h"
#include "lvphysics_interface.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


/*
** access functions (stack -> C)
*/


LUA_API lua_CBaseEntity *lua_toentity (lua_State *L, int idx) {
  CBaseHandle *hEntity = dynamic_cast<CBaseHandle *>((CBaseHandle *)lua_touserdata(L, idx));
  if (hEntity == NULL)
    return NULL;
  return dynamic_cast<lua_CBaseEntity *>(hEntity->Get());
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushentity (lua_State *L, CBaseEntity *pEntity) {
  CBaseHandle *hEntity = (CBaseHandle *)lua_newuserdata(L, sizeof(CBaseHandle));
  hEntity->Set(pEntity);
  luaL_getmetatable(L, "CBaseEntity");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_CBaseEntity *luaL_checkentity (lua_State *L, int narg) {
  lua_CBaseEntity *d = lua_toentity(L, narg);
  if (d == NULL)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "CBaseEntity expected, got NULL entity");
  return d;
}


LUALIB_API lua_CBaseEntity *luaL_optentity (lua_State *L, int narg,
                                                          CBaseEntity *def) {
  return luaL_opt(L, luaL_checkentity, narg, def);
}


static int CBaseEntity_Activate (lua_State *L) {
  luaL_checkentity(L, 1)->Activate();
  return 0;
}

static int CBaseEntity_AddDataObjectType (lua_State *L) {
  luaL_checkentity(L, 1)->AddDataObjectType(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_AddEffects (lua_State *L) {
  luaL_checkentity(L, 1)->AddEffects(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_AddEFlags (lua_State *L) {
  luaL_checkentity(L, 1)->AddEFlags(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_AddFlag (lua_State *L) {
  luaL_checkentity(L, 1)->AddFlag(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_AddSolidFlags (lua_State *L) {
  luaL_checkentity(L, 1)->AddSolidFlags(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_ApplyAbsVelocityImpulse (lua_State *L) {
  luaL_checkentity(L, 1)->ApplyAbsVelocityImpulse(luaL_checkvector(L, 2));
  return 0;
}

static int CBaseEntity_ApplyLocalAngularVelocityImpulse (lua_State *L) {
  luaL_checkentity(L, 1)->ApplyLocalAngularVelocityImpulse((AngularImpulse &)luaL_checkvector(L, 2));
  return 0;
}

static int CBaseEntity_BlocksLOS (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->BlocksLOS());
  return 1;
}

static int CBaseEntity_BloodColor (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->BloodColor());
  return 1;
}

static int CBaseEntity_BoundingRadius (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->BoundingRadius());
  return 1;
}

static int CBaseEntity_ChangeTeam (lua_State *L) {
  luaL_checkentity(L, 1)->ChangeTeam(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_ClearEffects (lua_State *L) {
  luaL_checkentity(L, 1)->ClearEffects();
  return 0;
}

static int CBaseEntity_ClearFlags (lua_State *L) {
  luaL_checkentity(L, 1)->ClearFlags();
  return 0;
}

static int CBaseEntity_CollisionRulesChanged (lua_State *L) {
  luaL_checkentity(L, 1)->CollisionRulesChanged();
  return 0;
}

static int CBaseEntity_ComputeAbsDirection (lua_State *L) {
  luaL_checkentity(L, 1)->ComputeAbsDirection(luaL_checkvector(L, 2), &luaL_checkvector(L, 3));
  return 0;
}

static int CBaseEntity_ComputeAbsPosition (lua_State *L) {
  luaL_checkentity(L, 1)->ComputeAbsPosition(luaL_checkvector(L, 2), &luaL_checkvector(L, 3));
  return 0;
}

static int CBaseEntity_ComputeWorldSpaceSurroundingBox (lua_State *L) {
  luaL_checkentity(L, 1)->ComputeWorldSpaceSurroundingBox(&luaL_checkvector(L, 2), &luaL_checkvector(L, 3));
  return 0;
}

static int CBaseEntity_CreateDataObject (lua_State *L) {
  luaL_checkentity(L, 1)->CreateDataObject(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_CreatePredictedEntityByName (lua_State *L) {
  lua_pushentity(L, CBaseEntity::CreatePredictedEntityByName(luaL_checkstring(L, 2), luaL_checkstring(L, 3), luaL_checkint(L, 4), luaL_optboolean(L, 5, 0)));
  return 1;
}

static int CBaseEntity_CreateVPhysics (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->CreateVPhysics());
  return 1;
}

static int CBaseEntity_DamageDecal (lua_State *L) {
  lua_pushstring(L, luaL_checkentity(L, 1)->DamageDecal(luaL_checkint(L, 2), luaL_checkint(L, 3)));
  return 1;
}

static int CBaseEntity_DecalTrace (lua_State *L) {
  luaL_checkentity(L, 1)->DecalTrace(&luaL_checktrace(L, 2), luaL_checkstring(L, 3));
  return 0;
}

static int CBaseEntity_DestroyAllDataObjects (lua_State *L) {
  luaL_checkentity(L, 1)->DestroyAllDataObjects();
  return 0;
}

static int CBaseEntity_DestroyDataObject (lua_State *L) {
  luaL_checkentity(L, 1)->DestroyDataObject(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_DispatchTraceAttack (lua_State *L) {
  luaL_checkentity(L, 1)->DispatchTraceAttack(luaL_checkdamageinfo(L, 2), luaL_checkvector(L, 3), &luaL_checktrace(L, 4));
  return 0;
}

static int CBaseEntity_DoImpactEffect (lua_State *L) {
  luaL_checkentity(L, 1)->DoImpactEffect(luaL_checktrace(L, 2), luaL_checkint(L, 3));
  return 1;
}

static int CBaseEntity_EarPosition (lua_State *L) {
  lua_pushvector(L, luaL_checkentity(L, 1)->EarPosition());
  return 1;
}

static int CBaseEntity_EmitAmbientSound (lua_State *L) {
  float duration = luaL_optnumber(L, 6, 0);
  CBaseEntity::EmitAmbientSound(luaL_checkint(L, 1), luaL_checkvector(L, 2), luaL_checkstring(L, 3), luaL_optint(L, 4, 0), luaL_optnumber(L, 5, 0.0f), &duration);
  return 0;
}

static int CBaseEntity_EmitSound (lua_State *L) {
  if (lua_isuserdata(L, 1) && lua_toentity(L, 1)) {
    float duration = 0;
	luaL_checkentity(L, 1)->EmitSound(luaL_checkstring(L, 2), luaL_optnumber(L, 3, 0.0f), &duration);
	lua_pushnumber(L, duration);
	return 1;
  } else if (lua_isuserdata(L, 1) && dynamic_cast<CRecipientFilter *>((CRecipientFilter *)lua_touserdata(L, 1))) {
    switch(lua_type(L, 3)) {
      case LUA_TSTRING:
        {
          if (lua_gettop(L) <= 3)
            CBaseEntity::EmitSound(luaL_checkrecipientfilter(L, 1), luaL_checkint(L, 2), luaL_checkstring(L, 3));
          else {
            float duration = 0;
            CBaseEntity::EmitSound(luaL_checkrecipientfilter(L, 1), luaL_checkint(L, 2), luaL_checkstring(L, 3), &luaL_checkvector(L, 4), luaL_optnumber(L, 5, 0.0f), &duration);
            lua_pushnumber(L, duration);
            return 1;
          }
          break;
        }
      case LUA_TTABLE:
        {
          EmitSound_t ep;
		  lua_toemitsound(L, 3, ep);

          CBaseEntity::EmitSound(luaL_checkrecipientfilter(L, 1), luaL_checkint(L, 2), ep);
          break;
        }
      default:
        luaL_typerror(L, 3, "string or CRecipientFilter");
        break;
    }
  } else
    luaL_typerror(L, 1, "CBaseEntity or CRecipientFilter");
  return 0;
}

static int CBaseEntity_EndGroundContact (lua_State *L) {
  luaL_checkentity(L, 1)->EndGroundContact(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_EndTouch (lua_State *L) {
  luaL_checkentity(L, 1)->EndTouch(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_entindex (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->entindex());
  return 1;
}

static int CBaseEntity_EntityToWorldSpace (lua_State *L) {
  luaL_checkentity(L, 1)->EntityToWorldSpace(luaL_checkvector(L, 2), &luaL_checkvector(L, 3));
  return 0;
}

static int CBaseEntity_EyeAngles (lua_State *L) {
  QAngle v = luaL_checkentity(L, 1)->EyeAngles();
  lua_pushangle(L, v);
  return 1;
}

static int CBaseEntity_EyePosition (lua_State *L) {
  lua_pushvector(L, luaL_checkentity(L, 1)->EyePosition());
  return 1;
}

static int CBaseEntity_FireBullets (lua_State *L) {
  luaL_checkentity(L, 1)->FireBullets(lua_tofirebulletsinfo(L, 2));
  return 0;
}

static int CBaseEntity_FirstMoveChild (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->FirstMoveChild());
  return 1;
}

static int CBaseEntity_FollowEntity (lua_State *L) {
  luaL_checkentity(L, 1)->FollowEntity(luaL_checkentity(L, 2), luaL_checkboolean(L, 3));
  return 0;
}

static int CBaseEntity_GenderExpandString (lua_State *L) {
  char out[128];
  out[0] = '\0';
  luaL_checkentity(L, 1)->GenderExpandString(luaL_checkstring(L, 2), out, sizeof( out ));
  lua_pushstring(L, out);
  return 1;
}

static int CBaseEntity_GetAbsAngles (lua_State *L) {
  QAngle v = luaL_checkentity(L, 1)->GetAbsAngles();
  lua_pushangle(L, v);
  return 1;
}

static int CBaseEntity_GetAbsOrigin (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->GetAbsOrigin();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_GetAbsVelocity (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->GetAbsVelocity();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_GetAnimTime (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetAnimTime());
  return 1;
}

static int CBaseEntity_GetBaseAnimating (lua_State *L) {
  lua_pushanimating(L, luaL_checkentity(L, 1)->GetBaseAnimating());
  return 1;
}

static int CBaseEntity_GetBaseEntity (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->GetBaseEntity());
  return 1;
}

static int CBaseEntity_GetBaseVelocity (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->GetBaseVelocity();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_GetCheckUntouch (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->GetCheckUntouch());
  return 1;
}

static int CBaseEntity_GetClassname (lua_State *L) {
  lua_pushstring(L, luaL_checkentity(L, 1)->GetClassname());
  return 1;
}

static int CBaseEntity_GetCollisionGroup (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetCollisionGroup());
  return 1;
}

static int CBaseEntity_GetDataObject (lua_State *L) {
  luaL_checkentity(L, 1)->GetDataObject(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_GetDebugName (lua_State *L) {
  lua_pushstring(L, luaL_checkentity(L, 1)->GetDebugName());
  return 1;
}

static int CBaseEntity_GetDLLType (lua_State *L) {
  lua_pushstring(L, CBaseEntity::GetDLLType());
  return 1;
}

static int CBaseEntity_GetEffectEntity (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->GetEffectEntity());
  return 1;
}

static int CBaseEntity_GetEffects (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetEffects());
  return 1;
}

static int CBaseEntity_GetEFlags (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetEFlags());
  return 1;
}

static int CBaseEntity_GetElasticity (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetElasticity());
  return 1;
}

static int CBaseEntity_GetFirstThinkTick (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetFirstThinkTick());
  return 1;
}

static int CBaseEntity_GetFlags (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetFlags());
  return 1;
}

static int CBaseEntity_GetFollowedEntity (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->GetFollowedEntity());
  return 1;
}

static int CBaseEntity_GetGravity (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetGravity());
  return 1;
}

static int CBaseEntity_GetGroundChangeTime (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetGroundChangeTime());
  return 1;
}

static int CBaseEntity_GetGroundEntity (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->GetGroundEntity());
  return 1;
}

static int CBaseEntity_GetHealth (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetHealth());
  return 1;
}

static int CBaseEntity_GetKeyValue (lua_State *L) {
  char szValue[256];
  szValue[0] = '\0';
  lua_pushboolean(L, luaL_checkentity(L, 1)->GetKeyValue(luaL_checkstring(L, 2), szValue, sizeof( szValue )));
  lua_pushstring(L, szValue);
  return 2;
}

static int CBaseEntity_GetLastThink (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetLastThink(luaL_optstring(L, 2, 0)));
  return 1;
}

static int CBaseEntity_GetLastThinkTick (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetLastThinkTick(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseEntity_GetLocalAngles (lua_State *L) {
  // Create an angle object, then push a copy of the angle
  QAngle dst;
  VectorCopy(luaL_checkentity(L, 1)->GetLocalAngles(), dst);
  lua_pushangle(L, dst);
  return 1;
}

static int CBaseEntity_GetLocalAngularVelocity (lua_State *L) {
  QAngle v = luaL_checkentity(L, 1)->GetLocalAngularVelocity();
  lua_pushangle(L, v);
  return 1;
}

static int CBaseEntity_GetLocalOrigin (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->GetLocalOrigin();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_GetLocalVelocity (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->GetLocalVelocity();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_GetMaxHealth (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetMaxHealth());
  return 1;
}

static int CBaseEntity_GetModelIndex (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetModelIndex());
  return 1;
}

static int CBaseEntity_GetModelName (lua_State *L) {
  lua_pushstring(L, STRING( luaL_checkentity(L, 1)->GetModelName() ));
  return 1;
}

static int CBaseEntity_GetMoveParent (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->GetMoveParent());
  return 1;
}

static int CBaseEntity_GetMoveType (lua_State *L) {
  lua_pushinteger(L, (MoveType_t)luaL_checkentity(L, 1)->GetMoveType());
  return 1;
}

static int CBaseEntity_GetOwnerEntity (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->GetOwnerEntity());
  return 1;
}

static int CBaseEntity_GetParametersForSound (lua_State *L) {
  CSoundParameters params;
  lua_pushboolean(L, CBaseEntity::GetParametersForSound(luaL_checkstring(L, 1), params, luaL_optstring(L, 2, NULL)));
  lua_pushsoundparameters(L, params);
  return 2;
}

static int CBaseEntity_GetPredictionPlayer (lua_State *L) {
  lua_pushplayer(L, CBaseEntity::GetPredictionPlayer());
  return 1;
}

static int CBaseEntity_GetPredictionRandomSeed (lua_State *L) {
  lua_pushinteger(L, CBaseEntity::GetPredictionRandomSeed());
  return 1;
}

static int CBaseEntity_GetRefTable (lua_State *L) {
  CBaseEntity *pEntity = luaL_checkentity(L, 1);
  if (pEntity->m_nTableReference == LUA_NOREF)
    lua_pushnil(L);
  else
    lua_getref(L, pEntity->m_nTableReference);
  return 1;
}

static int CBaseEntity_GetSimulatingPlayer (lua_State *L) {
  lua_pushplayer(L, luaL_checkentity(L, 1)->GetSimulatingPlayer());
  return 1;
}

static int CBaseEntity_GetSimulationTime (lua_State *L) {
  lua_pushnumber(L, luaL_checkentity(L, 1)->GetSimulationTime());
  return 1;
}

static int CBaseEntity_GetSolid (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetSolid());
  return 1;
}

static int CBaseEntity_GetSolidFlags (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetSolidFlags());
  return 1;
}

static int CBaseEntity_GetSoundDuration (lua_State *L) {
  lua_pushnumber(L, CBaseEntity::GetSoundDuration(luaL_checkstring(L, 1), luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseEntity_GetSoundSourceIndex (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetSoundSourceIndex());
  return 1;
}

static int CBaseEntity_GetTeamNumber (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetTeamNumber());
  return 1;
}

static int CBaseEntity_GetTextureFrameIndex (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetTextureFrameIndex());
  return 1;
}

static int CBaseEntity_GetTouchTrace (lua_State *L) {
  trace_t tr;
  tr = CBaseEntity::GetTouchTrace();
  lua_pushtrace(L, tr);
  return 1;
}

static int CBaseEntity_GetTracerAttachment (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetTracerAttachment());
  return 1;
}

static int CBaseEntity_GetTracerType (lua_State *L) {
  lua_pushstring(L, luaL_checkentity(L, 1)->GetTracerType());
  return 1;
}

static int CBaseEntity_GetVectors (lua_State *L) {
  Vector forward, right, up;
  luaL_checkentity(L, 1)->GetVectors(&forward, &right, &up);
  lua_pushvector(L, forward);
  lua_pushvector(L, right);
  lua_pushvector(L, up);
  return 3;
}

static int CBaseEntity_GetViewOffset (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->GetViewOffset();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_GetWaterLevel (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetWaterLevel());
  return 1;
}

static int CBaseEntity_GetWaterType (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->GetWaterType());
  return 1;
}

static int CBaseEntity_HasDataObjectType (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->HasDataObjectType(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseEntity_HasNPCsOnIt (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->HasNPCsOnIt());
  return 1;
}

static int CBaseEntity_ImpactTrace (lua_State *L) {
  luaL_checkentity(L, 1)->ImpactTrace(&luaL_checktrace(L, 2), luaL_checkint(L, 3), (char *)luaL_optstring(L, 4, 0));
  return 0;
}

static int CBaseEntity_InSameTeam (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->InSameTeam(luaL_checkentity(L, 2)));
  return 1;
}

static int CBaseEntity_IsAbsQueriesValid (lua_State *L) {
  lua_pushboolean(L, CBaseEntity::IsAbsQueriesValid());
  return 1;
}

static int CBaseEntity_IsAIWalkable (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsAIWalkable());
  return 1;
}

static int CBaseEntity_IsAlive (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsAlive());
  return 1;
}

static int CBaseEntity_IsAnimatedEveryTick (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsAnimatedEveryTick());
  return 1;
}

static int CBaseEntity_IsBaseObject (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsBaseObject());
  return 1;
}

static int CBaseEntity_IsBaseTrain (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsBaseTrain());
  return 1;
}

static int CBaseEntity_IsBSPModel (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsBSPModel());
  return 1;
}

static int CBaseEntity_IsClient (lua_State *L) {
  lua_pushboolean(L, CBaseEntity::IsClient());
  return 1;
}

static int CBaseEntity_IsCurrentlyTouching (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsCurrentlyTouching());
  return 1;
}

static int CBaseEntity_IsDormant (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsDormant());
  return 1;
}

static int CBaseEntity_IsEffectActive (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsEffectActive(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseEntity_IsEFlagSet (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsEFlagSet(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseEntity_IsFloating (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsFloating());
  return 1;
}

static int CBaseEntity_IsFollowingEntity (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsFollowingEntity());
  return 1;
}

static int CBaseEntity_IsInWorld (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsInWorld());
  return 1;
}

static int CBaseEntity_IsMarkedForDeletion (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsMarkedForDeletion());
  return 1;
}

static int CBaseEntity_IsNPC (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsNPC());
  return 1;
}

static int CBaseEntity_IsPlayer (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsPlayer());
  return 1;
}

static int CBaseEntity_IsPlayerSimulated (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsPlayerSimulated());
  return 1;
}

static int CBaseEntity_IsPointSized (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsPointSized());
  return 1;
}

static int CBaseEntity_IsPrecacheAllowed (lua_State *L) {
  lua_pushboolean(L, CBaseEntity::IsPrecacheAllowed());
  return 1;
}

static int CBaseEntity_IsServer (lua_State *L) {
  lua_pushboolean(L, CBaseEntity::IsServer());
  return 1;
}

static int CBaseEntity_IsSimulatedEveryTick (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsSimulatedEveryTick());
  return 1;
}

static int CBaseEntity_IsSimulatingOnAlternateTicks (lua_State *L) {
  lua_pushboolean(L, CBaseEntity::IsSimulatingOnAlternateTicks());
  return 1;
}

static int CBaseEntity_IsSolid (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsSolid());
  return 1;
}

static int CBaseEntity_IsSolidFlagSet (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsSolidFlagSet(luaL_checkint(L, 2)));
  return 1;
}

static int CBaseEntity_IsStandable (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsStandable());
  return 1;
}

static int CBaseEntity_IsTransparent (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsTransparent());
  return 1;
}

static int CBaseEntity_IsWeapon (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->IsWeapon());
  return 1;
}

static int CBaseEntity_KeyValue (lua_State *L) {
  switch(lua_type(L, 3)) {
	case LUA_TNUMBER:
	  lua_pushboolean(L, luaL_checkentity(L, 1)->KeyValue(luaL_checkstring(L, 2), luaL_checknumber(L, 3)));
	  break;
	case LUA_TSTRING:
	default:
	  lua_pushboolean(L, luaL_checkentity(L, 1)->KeyValue(luaL_checkstring(L, 2), luaL_checkstring(L, 3)));
	  break;
	case LUA_TUSERDATA:
      if (luaL_checkudata(L, 3, "Vector"))
	    lua_pushboolean(L, luaL_checkentity(L, 1)->KeyValue(luaL_checkstring(L, 2), luaL_checkvector(L, 3)));
	  else
	    luaL_typerror(L, 3, "Vector");
	  break;
  }
  return 1;
}

static int CBaseEntity_LocalEyeAngles (lua_State *L) {
  QAngle v = luaL_checkentity(L, 1)->LocalEyeAngles();
  lua_pushangle(L, v);
  return 1;
}

static int CBaseEntity_NextMovePeer (lua_State *L) {
  lua_pushentity(L, luaL_checkentity(L, 1)->NextMovePeer());
  return 1;
}

static int CBaseEntity_ObjectCaps (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->ObjectCaps());
  return 1;
}

static int CBaseEntity_OnRestore (lua_State *L) {
  luaL_checkentity(L, 1)->OnRestore();
  return 0;
}

static int CBaseEntity_PhysicsCheckForEntityUntouch (lua_State *L) {
  luaL_checkentity(L, 1)->PhysicsCheckForEntityUntouch();
  return 0;
}

static int CBaseEntity_PhysicsCheckWater (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->PhysicsCheckWater());
  return 1;
}

static int CBaseEntity_PhysicsCheckWaterTransition (lua_State *L) {
  luaL_checkentity(L, 1)->PhysicsCheckWaterTransition();
  return 0;
}

static int CBaseEntity_PhysicsImpact (lua_State *L) {
  luaL_checkentity(L, 1)->PhysicsImpact(luaL_checkentity(L, 2), luaL_checktrace(L, 3));
  return 0;
}

static int CBaseEntity_PhysicsMarkEntitiesAsTouching (lua_State *L) {
  luaL_checkentity(L, 1)->PhysicsMarkEntitiesAsTouching(luaL_checkentity(L, 2), luaL_checktrace(L, 3));
  return 0;
}

static int CBaseEntity_PhysicsNotifyOtherOfGroundRemoval (lua_State *L) {
  CBaseEntity::PhysicsNotifyOtherOfGroundRemoval(luaL_checkentity(L, 1), luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_PhysicsNotifyOtherOfUntouch (lua_State *L) {
  CBaseEntity::PhysicsNotifyOtherOfUntouch(luaL_checkentity(L, 1), luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_PhysicsRemoveGroundList (lua_State *L) {
  CBaseEntity::PhysicsRemoveGroundList(luaL_checkentity(L, 1));
  return 0;
}

static int CBaseEntity_PhysicsRemoveTouchedList (lua_State *L) {
  CBaseEntity::PhysicsRemoveTouchedList(luaL_checkentity(L, 1));
  return 0;
}

static int CBaseEntity_PhysicsSimulate (lua_State *L) {
  luaL_checkentity(L, 1)->PhysicsSimulate();
  return 0;
}

static int CBaseEntity_PhysicsSolidMaskForEntity (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->PhysicsSolidMaskForEntity());
  return 1;
}

static int CBaseEntity_PhysicsStartGroundContact (lua_State *L) {
  luaL_checkentity(L, 1)->PhysicsStartGroundContact(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_Precache (lua_State *L) {
  luaL_checkentity(L, 1)->Precache();
  return 0;
}

static int CBaseEntity_PrecacheModel (lua_State *L) {
  lua_pushinteger(L, CBaseEntity::PrecacheModel(luaL_checkstring(L, 1)));
  return 1;
}

static int CBaseEntity_PrecacheScriptSound (lua_State *L) {
  lua_pushinteger(L, CBaseEntity::PrecacheScriptSound(luaL_checkstring(L, 1)));
  return 1;
}

static int CBaseEntity_PrecacheSound (lua_State *L) {
  lua_pushboolean(L, CBaseEntity::PrecacheSound(luaL_checkstring(L, 1)));
  return 1;
}

static int CBaseEntity_PrefetchScriptSound (lua_State *L) {
  CBaseEntity::PrefetchScriptSound(luaL_checkstring(L, 1));
  return 0;
}

static int CBaseEntity_PrefetchSound (lua_State *L) {
  CBaseEntity::PrefetchSound(luaL_checkstring(L, 1));
  return 0;
}

static int CBaseEntity_RegisterThinkContext (lua_State *L) {
  lua_pushinteger(L, luaL_checkentity(L, 1)->RegisterThinkContext(luaL_checkstring(L, 2)));
  return 1;
}

static int CBaseEntity_Remove (lua_State *L) {
  luaL_checkentity(L, 1)->Remove();
  return 0;
}

static int CBaseEntity_RemoveAllDecals (lua_State *L) {
  luaL_checkentity(L, 1)->RemoveAllDecals();
  return 0;
}

static int CBaseEntity_RemoveDataObjectType (lua_State *L) {
  luaL_checkentity(L, 1)->RemoveDataObjectType(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_RemoveEffects (lua_State *L) {
  luaL_checkentity(L, 1)->RemoveEffects(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_RemoveEFlags (lua_State *L) {
  luaL_checkentity(L, 1)->RemoveEFlags(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_RemoveFlag (lua_State *L) {
  luaL_checkentity(L, 1)->RemoveFlag(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_RemoveSolidFlags (lua_State *L) {
  luaL_checkentity(L, 1)->RemoveSolidFlags(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetAbsAngles (lua_State *L) {
  luaL_checkentity(L, 1)->SetAbsAngles(luaL_checkangle(L, 2));
  return 0;
}

static int CBaseEntity_SetAbsOrigin (lua_State *L) {
  luaL_checkentity(L, 1)->SetAbsOrigin(luaL_checkvector(L, 2));
  return 0;
}

static int CBaseEntity_SetAbsQueriesValid (lua_State *L) {
  CBaseEntity::SetAbsQueriesValid(luaL_checkboolean(L, 1));
  return 0;
}

static int CBaseEntity_SetAbsVelocity (lua_State *L) {
  luaL_checkentity(L, 1)->SetAbsVelocity(luaL_checkvector(L, 2));
  return 0;
}

static int CBaseEntity_SetAIWalkable (lua_State *L) {
  luaL_checkentity(L, 1)->SetAIWalkable(luaL_checkboolean(L, 2));
  return 0;
}

static int CBaseEntity_SetAllowPrecache (lua_State *L) {
  CBaseEntity::SetAllowPrecache(luaL_checkboolean(L, 1));
  return 0;
}

static int CBaseEntity_SetAnimatedEveryTick (lua_State *L) {
  luaL_checkentity(L, 1)->SetAnimatedEveryTick(luaL_checkboolean(L, 2));
  return 0;
}

static int CBaseEntity_SetAnimTime (lua_State *L) {
  luaL_checkentity(L, 1)->SetAnimTime(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetBaseVelocity (lua_State *L) {
  luaL_checkentity(L, 1)->SetBaseVelocity(luaL_checkvector(L, 2));
  return 0;
}

static int CBaseEntity_SetBlocksLOS (lua_State *L) {
  luaL_checkentity(L, 1)->SetBlocksLOS(luaL_checkboolean(L, 2));
  return 0;
}

static int CBaseEntity_SetCheckUntouch (lua_State *L) {
  luaL_checkentity(L, 1)->SetCheckUntouch(luaL_checkboolean(L, 2));
  return 0;
}

static int CBaseEntity_SetClassname (lua_State *L) {
  luaL_checkentity(L, 1)->SetClassname(luaL_checkstring(L, 2));
  return 0;
}

static int CBaseEntity_SetCollisionBounds (lua_State *L) {
  luaL_checkentity(L, 1)->SetCollisionBounds(luaL_checkvector(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int CBaseEntity_SetCollisionGroup (lua_State *L) {
  luaL_checkentity(L, 1)->SetCollisionGroup(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetEffectEntity (lua_State *L) {
  luaL_checkentity(L, 1)->SetEffectEntity(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_SetEffects (lua_State *L) {
  luaL_checkentity(L, 1)->SetEffects(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetEFlags (lua_State *L) {
  luaL_checkentity(L, 1)->SetEFlags(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetFriction (lua_State *L) {
  luaL_checkentity(L, 1)->SetFriction(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetGravity (lua_State *L) {
  luaL_checkentity(L, 1)->SetGravity(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetGroundChangeTime (lua_State *L) {
  luaL_checkentity(L, 1)->SetGroundChangeTime(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetGroundEntity (lua_State *L) {
  luaL_checkentity(L, 1)->SetGroundEntity(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_SetHealth (lua_State *L) {
  luaL_checkentity(L, 1)->SetHealth(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetLocalAngles (lua_State *L) {
  luaL_checkentity(L, 1)->SetLocalAngles(luaL_checkangle(L, 2));
  return 0;
}

static int CBaseEntity_SetLocalAngularVelocity (lua_State *L) {
  luaL_checkentity(L, 1)->SetLocalAngularVelocity(luaL_checkangle(L, 2));
  return 0;
}

static int CBaseEntity_SetLocalOrigin (lua_State *L) {
  luaL_checkentity(L, 1)->SetLocalOrigin(luaL_checkvector(L, 2));
  return 0;
}

static int CBaseEntity_SetLocalVelocity (lua_State *L) {
  luaL_checkentity(L, 1)->SetLocalVelocity(luaL_checkvector(L, 2));
  return 0;
}

static int CBaseEntity_SetModel (lua_State *L) {
#ifdef CLIENT_DLL
  lua_pushboolean(L, luaL_checkentity(L, 1)->SetModel(luaL_checkstring(L, 2)));
  return 1;
#else
  luaL_checkentity(L, 1)->SetModel(luaL_checkstring(L, 2));
  return 0;
#endif
}

static int CBaseEntity_SetModelIndex (lua_State *L) {
  luaL_checkentity(L, 1)->SetModelIndex(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetModelName (lua_State *L) {
  string_t name = *(string_t *)luaL_checkstring(L, 2);
  luaL_checkentity(L, 1)->SetModelName(name);
  return 0;
}

static int CBaseEntity_SetMoveCollide (lua_State *L) {
  luaL_checkentity(L, 1)->SetMoveCollide((MoveCollide_t)luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetMoveType (lua_State *L) {
  luaL_checkentity(L, 1)->SetMoveType((MoveType_t)luaL_checkint(L, 2), (MoveCollide_t)luaL_optint(L, 3, MOVECOLLIDE_DEFAULT));
  return 0;
}

static int CBaseEntity_SetNextThink (lua_State *L) {
  luaL_checkentity(L, 1)->SetNextThink(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetOwnerEntity (lua_State *L) {
  luaL_checkentity(L, 1)->SetOwnerEntity(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_SetParent (lua_State *L) {
  luaL_checkentity(L, 1)->SetParent(luaL_checkentity(L, 2), luaL_optint(L, 3, 0));
  return 0;
}

static int CBaseEntity_SetPlayerSimulated (lua_State *L) {
  luaL_checkentity(L, 1)->SetPlayerSimulated(luaL_checkplayer(L, 2));
  return 0;
}

static int CBaseEntity_SetPredictionEligible (lua_State *L) {
  luaL_checkentity(L, 1)->SetPredictionEligible(luaL_checkboolean(L, 2));
  return 0;
}

static int CBaseEntity_SetPredictionPlayer (lua_State *L) {
  CBaseEntity::SetPredictionPlayer(luaL_checkplayer(L, 1));
  return 0;
}

static int CBaseEntity_SetRenderColor (lua_State *L) {
  luaL_checkentity(L, 1)->SetRenderColor(luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_optnumber(L, 5, 255));
  return 0;
}

static int CBaseEntity_SetRenderColorA (lua_State *L) {
  luaL_checkentity(L, 1)->SetRenderColorA(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetRenderColorB (lua_State *L) {
  luaL_checkentity(L, 1)->SetRenderColorB(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetRenderColorG (lua_State *L) {
  luaL_checkentity(L, 1)->SetRenderColorG(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetRenderColorR (lua_State *L) {
  luaL_checkentity(L, 1)->SetRenderColorR(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetSimulatedEveryTick (lua_State *L) {
  luaL_checkentity(L, 1)->SetSimulatedEveryTick(luaL_checkboolean(L, 2));
  return 0;
}

static int CBaseEntity_SetSimulationTime (lua_State *L) {
  luaL_checkentity(L, 1)->SetSimulationTime(luaL_checknumber(L, 2));
  return 0;
}

static int CBaseEntity_SetSize (lua_State *L) {
  luaL_checkentity(L, 1)->SetSize(luaL_checkvector(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int CBaseEntity_SetSolid (lua_State *L) {
  luaL_checkentity(L, 1)->SetSolid((SolidType_t)luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetSolidFlags (lua_State *L) {
  luaL_checkentity(L, 1)->SetSolidFlags(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetTextureFrameIndex (lua_State *L) {
  luaL_checkentity(L, 1)->SetTextureFrameIndex(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetViewOffset (lua_State *L) {
  luaL_checkentity(L, 1)->SetViewOffset(luaL_checkvector(L, 2));
  return 0;
}

static int CBaseEntity_SetWaterLevel (lua_State *L) {
  luaL_checkentity(L, 1)->SetWaterLevel(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_SetWaterType (lua_State *L) {
  luaL_checkentity(L, 1)->SetWaterType(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_ShouldCollide (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->ShouldCollide(luaL_checkint(L, 2), luaL_checkint(L, 3)));
  return 1;
}

static int CBaseEntity_ShouldSavePhysics (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->ShouldSavePhysics());
  return 1;
}

static int CBaseEntity_Spawn (lua_State *L) {
  luaL_checkentity(L, 1)->Spawn();
  return 0;
}

static int CBaseEntity_StartGroundContact (lua_State *L) {
  luaL_checkentity(L, 1)->StartGroundContact(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_StartTouch (lua_State *L) {
  luaL_checkentity(L, 1)->StartTouch(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_StopFollowingEntity (lua_State *L) {
  luaL_checkentity(L, 1)->StopFollowingEntity();
  return 0;
}

static int CBaseEntity_SUB_Remove (lua_State *L) {
  luaL_checkentity(L, 1)->SUB_Remove();
  return 0;
}

static int CBaseEntity_Think (lua_State *L) {
  luaL_checkentity(L, 1)->Think();
  return 0;
}

static int CBaseEntity_ToggleFlag (lua_State *L) {
  luaL_checkentity(L, 1)->ToggleFlag(luaL_checkint(L, 2));
  return 0;
}

static int CBaseEntity_Touch (lua_State *L) {
  luaL_checkentity(L, 1)->Touch(luaL_checkentity(L, 2));
  return 0;
}

static int CBaseEntity_TraceBleed (lua_State *L) {
  luaL_checkentity(L, 1)->TraceBleed(luaL_checknumber(L, 2), luaL_checkvector(L, 3), &luaL_checktrace(L, 4), luaL_checkint(L, 5));
  return 0;
}

static int CBaseEntity_UnsetPlayerSimulated (lua_State *L) {
  luaL_checkentity(L, 1)->UnsetPlayerSimulated();
  return 0;
}

static int CBaseEntity_UpdateOnRemove (lua_State *L) {
  luaL_checkentity(L, 1)->UpdateOnRemove();
  return 0;
}

static int CBaseEntity_VPhysicsDestroyObject (lua_State *L) {
  luaL_checkentity(L, 1)->VPhysicsDestroyObject();
  return 0;
}

static int CBaseEntity_VPhysicsGetObject (lua_State *L) {
  lua_pushphysicsobject(L, luaL_checkentity(L, 1)->VPhysicsGetObject());
  return 1;
}

static int CBaseEntity_VPhysicsGetObjectList (lua_State *L) {
  IPhysicsObject *pList[VPHYSICS_MAX_OBJECT_LIST_COUNT];
  int count = luaL_checkentity(L, 1)->VPhysicsGetObjectList( pList, ARRAYSIZE(pList) );
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

static int CBaseEntity_VPhysicsInitNormal (lua_State *L) {
  // TODO: Implement a Lua solid_t object.
  lua_pushphysicsobject(L, luaL_checkentity(L, 1)->VPhysicsInitNormal((SolidType_t)luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkboolean(L, 4)));
  return 1;
}

static int CBaseEntity_VPhysicsInitStatic (lua_State *L) {
  lua_pushphysicsobject(L, luaL_checkentity(L, 1)->VPhysicsInitStatic());
  return 1;
}

static int CBaseEntity_VPhysicsIsFlesh (lua_State *L) {
  lua_pushboolean(L, luaL_checkentity(L, 1)->VPhysicsIsFlesh());
  return 1;
}

static int CBaseEntity_VPhysicsSetObject (lua_State *L) {
  luaL_checkentity(L, 1)->VPhysicsSetObject(luaL_checkphysicsobject(L, 2));
  return 0;
}

static int CBaseEntity_VPhysicsUpdate (lua_State *L) {
  luaL_checkentity(L, 1)->VPhysicsUpdate(luaL_checkphysicsobject(L, 2));
  return 0;
}

static int CBaseEntity_WakeRestingObjects (lua_State *L) {
  luaL_checkentity(L, 1)->WakeRestingObjects();
  return 0;
}

static int CBaseEntity_WorldAlignMaxs (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->WorldAlignMaxs();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_WorldAlignMins (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->WorldAlignMins();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_WorldAlignSize (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->WorldAlignSize();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_WorldSpaceCenter (lua_State *L) {
  Vector v = luaL_checkentity(L, 1)->WorldSpaceCenter();
  lua_pushvector(L, v);
  return 1;
}

static int CBaseEntity_WorldToEntitySpace (lua_State *L) {
  luaL_checkentity(L, 1)->WorldToEntitySpace(luaL_checkvector(L, 2), &luaL_checkvector(L, 3));
  return 0;
}

static int CBaseEntity___index (lua_State *L) {
  CBaseEntity *pEntity = lua_toentity(L, 1);
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
  if (Q_strcmp(field, "m_bAllowPrecache") == 0)
    lua_pushboolean(L, pEntity->m_bAllowPrecache);
  else if (Q_strcmp(field, "m_flAnimTime") == 0)
    lua_pushnumber(L, pEntity->m_flAnimTime);
  else if (Q_strcmp(field, "m_flSimulationTime") == 0)
    lua_pushnumber(L, pEntity->m_flSimulationTime);
  else if (Q_strcmp(field, "m_flSpeed") == 0)
    lua_pushnumber(L, pEntity->m_flSpeed);
  else if (Q_strcmp(field, "m_iClassname") == 0)
    lua_pushstring(L, STRING( pEntity->m_iClassname ));
  else if (Q_strcmp(field, "m_iHealth") == 0)
    lua_pushinteger(L, pEntity->m_iHealth);
  else if (Q_strcmp(field, "m_nLastThinkTick") == 0)
    lua_pushinteger(L, pEntity->m_nLastThinkTick);
  else if (Q_strcmp(field, "m_nModelIndex") == 0)
    lua_pushinteger(L, pEntity->m_nModelIndex);
  else if (Q_strcmp(field, "touchStamp") == 0)
    lua_pushinteger(L, pEntity->touchStamp);
  else if (pEntity->m_nTableReference != LUA_NOREF) {
    lua_getref(L, pEntity->m_nTableReference);
    lua_getfield(L, -1, field);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 2);
      lua_getmetatable(L, 1);
      lua_getfield(L, -1, field);
    }
  }
  else {
    lua_getmetatable(L, 1);
    lua_getfield(L, -1, field);
  }
  return 1;
}

static int CBaseEntity___newindex (lua_State *L) {
  CBaseEntity *pEntity = lua_toentity(L, 1);
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
  if (Q_strcmp(field, "m_bAllowPrecache") == 0)
    pEntity->m_bAllowPrecache = luaL_checkboolean(L, 3);
  else if (Q_strcmp(field, "m_flAnimTime") == 0)
    pEntity->m_flAnimTime = luaL_checknumber(L, 3);
  else if (Q_strcmp(field, "m_flSimulationTime") == 0)
    pEntity->m_flSimulationTime = luaL_checknumber(L, 3);
  else if (Q_strcmp(field, "m_flSpeed") == 0)
    pEntity->m_flSpeed = luaL_checknumber(L, 3);
  else if (Q_strcmp(field, "m_iClassname") == 0)
    pEntity->m_iClassname = MAKE_STRING( luaL_checkstring(L, 3) );
  else if (Q_strcmp(field, "m_iHealth") == 0)
    pEntity->m_iHealth = luaL_checkint(L, 3);
  else if (Q_strcmp(field, "m_nLastThinkTick") == 0)
    pEntity->m_nLastThinkTick = luaL_checkint(L, 3);
  else if (Q_strcmp(field, "m_nModelIndex") == 0)
    pEntity->m_nModelIndex = luaL_checkint(L, 3);
  else if (Q_strcmp(field, "touchStamp") == 0)
    pEntity->touchStamp = luaL_checkint(L, 3);
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

static int CBaseEntity___eq (lua_State *L) {
  lua_pushboolean(L, lua_toentity(L, 1) == lua_toentity(L, 2));
  return 1;
}

static int CBaseEntity___tostring (lua_State *L) {
  CBaseEntity *pEntity = lua_toentity(L, 1);
  if (pEntity == NULL)
    lua_pushstring(L, "NULL");
  else
    lua_pushfstring(L, "CBaseEntity: %d %s", pEntity->entindex(), pEntity->GetClassname());
  return 1;
}


static const luaL_Reg CBaseEntitymeta[] = {
  {"Activate", CBaseEntity_Activate},
  {"AddDataObjectType", CBaseEntity_AddDataObjectType},
  {"AddEffects", CBaseEntity_AddEffects},
  {"AddEFlags", CBaseEntity_AddEFlags},
  {"AddFlag", CBaseEntity_AddFlag},
  {"AddSolidFlags", CBaseEntity_AddSolidFlags},
  {"ApplyAbsVelocityImpulse", CBaseEntity_ApplyAbsVelocityImpulse},
  {"ApplyLocalAngularVelocityImpulse", CBaseEntity_ApplyLocalAngularVelocityImpulse},
  {"BlocksLOS", CBaseEntity_BlocksLOS},
  {"BloodColor", CBaseEntity_BloodColor},
  {"BoundingRadius", CBaseEntity_BoundingRadius},
  {"ChangeTeam", CBaseEntity_ChangeTeam},
  {"ClearEffects", CBaseEntity_ClearEffects},
  {"ClearFlags", CBaseEntity_ClearFlags},
  {"CollisionRulesChanged", CBaseEntity_CollisionRulesChanged},
  {"ComputeAbsDirection", CBaseEntity_ComputeAbsDirection},
  {"ComputeAbsPosition", CBaseEntity_ComputeAbsPosition},
  {"ComputeWorldSpaceSurroundingBox", CBaseEntity_ComputeWorldSpaceSurroundingBox},
  {"CreateDataObject", CBaseEntity_CreateDataObject},
  {"CreatePredictedEntityByName", CBaseEntity_CreatePredictedEntityByName},
  {"CreateVPhysics", CBaseEntity_CreateVPhysics},
  {"DamageDecal", CBaseEntity_DamageDecal},
  {"DecalTrace", CBaseEntity_DecalTrace},
  {"DestroyAllDataObjects", CBaseEntity_DestroyAllDataObjects},
  {"DestroyDataObject", CBaseEntity_DestroyDataObject},
  {"DispatchTraceAttack", CBaseEntity_DispatchTraceAttack},
  {"DoImpactEffect", CBaseEntity_DoImpactEffect},
  {"EarPosition", CBaseEntity_EarPosition},
  {"EmitSound", CBaseEntity_EmitSound},
  {"EmitAmbientSound", CBaseEntity_EmitAmbientSound},
  {"EndGroundContact", CBaseEntity_EndGroundContact},
  {"EndTouch", CBaseEntity_EndTouch},
  {"entindex", CBaseEntity_entindex},
  {"EntityToWorldSpace", CBaseEntity_EntityToWorldSpace},
  {"EyeAngles", CBaseEntity_EyeAngles},
  {"EyePosition", CBaseEntity_EyePosition},
  {"FireBullets", CBaseEntity_FireBullets},
  {"FirstMoveChild", CBaseEntity_FirstMoveChild},
  {"FollowEntity", CBaseEntity_FollowEntity},
  {"GenderExpandString", CBaseEntity_GenderExpandString},
  {"GetAbsAngles", CBaseEntity_GetAbsAngles},
  {"GetAbsOrigin", CBaseEntity_GetAbsOrigin},
  {"GetAbsVelocity", CBaseEntity_GetAbsVelocity},
  {"GetAnimTime", CBaseEntity_GetAnimTime},
  {"GetBaseAnimating", CBaseEntity_GetBaseAnimating},
  {"GetBaseEntity", CBaseEntity_GetBaseEntity},
  {"GetBaseVelocity", CBaseEntity_GetBaseVelocity},
  {"GetCheckUntouch", CBaseEntity_GetCheckUntouch},
  {"GetClassname", CBaseEntity_GetClassname},
  {"GetCollisionGroup", CBaseEntity_GetCollisionGroup},
  {"GetDataObject", CBaseEntity_GetDataObject},
  {"GetDebugName", CBaseEntity_GetDebugName},
  {"GetDLLType", CBaseEntity_GetDLLType},
  {"GetEffectEntity", CBaseEntity_GetEffectEntity},
  {"GetEffects", CBaseEntity_GetEffects},
  {"GetEFlags", CBaseEntity_GetEFlags},
  {"GetElasticity", CBaseEntity_GetElasticity},
  {"GetFirstThinkTick", CBaseEntity_GetFirstThinkTick},
  {"GetFlags", CBaseEntity_GetFlags},
  {"GetFollowedEntity", CBaseEntity_GetFollowedEntity},
  {"GetGravity", CBaseEntity_GetGravity},
  {"GetGroundChangeTime", CBaseEntity_GetGroundChangeTime},
  {"GetGroundEntity", CBaseEntity_GetGroundEntity},
  {"GetHealth", CBaseEntity_GetHealth},
  {"GetKeyValue", CBaseEntity_GetKeyValue},
  {"GetLastThink", CBaseEntity_GetLastThink},
  {"GetLastThinkTick", CBaseEntity_GetLastThinkTick},
  {"GetLocalAngles", CBaseEntity_GetLocalAngles},
  {"GetLocalAngularVelocity", CBaseEntity_GetLocalAngularVelocity},
  {"GetLocalOrigin", CBaseEntity_GetLocalOrigin},
  {"GetLocalVelocity", CBaseEntity_GetLocalVelocity},
  {"GetMaxHealth", CBaseEntity_GetMaxHealth},
  {"GetModelIndex", CBaseEntity_GetModelIndex},
  {"GetModelName", CBaseEntity_GetModelName},
  {"GetMoveParent", CBaseEntity_GetMoveParent},
  {"GetMoveType", CBaseEntity_GetMoveType},
  {"GetOwnerEntity", CBaseEntity_GetOwnerEntity},
  {"GetParametersForSound", CBaseEntity_GetParametersForSound},
  {"GetPredictionPlayer", CBaseEntity_GetPredictionPlayer},
  {"GetPredictionRandomSeed", CBaseEntity_GetPredictionRandomSeed},
  {"GetSimulatingPlayer", CBaseEntity_GetSimulatingPlayer},
  {"GetSimulationTime", CBaseEntity_GetSimulationTime},
  {"GetSolid", CBaseEntity_GetSolid},
  {"GetSolidFlags", CBaseEntity_GetSolidFlags},
  {"GetSoundDuration", CBaseEntity_GetSoundDuration},
  {"GetSoundSourceIndex", CBaseEntity_GetSoundSourceIndex},
  {"GetTeamNumber", CBaseEntity_GetTeamNumber},
  {"GetTextureFrameIndex", CBaseEntity_GetTextureFrameIndex},
  {"GetTouchTrace", CBaseEntity_GetTouchTrace},
  {"GetTracerAttachment", CBaseEntity_GetTracerAttachment},
  {"GetTracerType", CBaseEntity_GetTracerType},
  {"GetVectors", CBaseEntity_GetVectors},
  {"GetViewOffset", CBaseEntity_GetViewOffset},
  {"GetWaterLevel", CBaseEntity_GetWaterLevel},
  {"GetWaterType", CBaseEntity_GetWaterType},
  {"HasDataObjectType", CBaseEntity_HasDataObjectType},
  {"HasNPCsOnIt", CBaseEntity_HasNPCsOnIt},
  {"ImpactTrace", CBaseEntity_ImpactTrace},
  {"InSameTeam", CBaseEntity_InSameTeam},
  {"IsAbsQueriesValid", CBaseEntity_IsAbsQueriesValid},
  {"IsAIWalkable", CBaseEntity_IsAIWalkable},
  {"IsAlive", CBaseEntity_IsAlive},
  {"IsAnimatedEveryTick", CBaseEntity_IsAnimatedEveryTick},
  {"IsBaseObject", CBaseEntity_IsBaseObject},
  {"IsBaseTrain", CBaseEntity_IsBaseTrain},
  {"IsBSPModel", CBaseEntity_IsBSPModel},
  {"IsClient", CBaseEntity_IsClient},
  {"IsCurrentlyTouching", CBaseEntity_IsCurrentlyTouching},
  {"IsDormant", CBaseEntity_IsDormant},
  {"IsEffectActive", CBaseEntity_IsEffectActive},
  {"IsEFlagSet", CBaseEntity_IsEFlagSet},
  {"IsFloating", CBaseEntity_IsFloating},
  {"IsFollowingEntity", CBaseEntity_IsFollowingEntity},
  {"IsInWorld", CBaseEntity_IsInWorld},
  {"IsMarkedForDeletion", CBaseEntity_IsMarkedForDeletion},
  {"IsNPC", CBaseEntity_IsNPC},
  {"IsPlayer", CBaseEntity_IsPlayer},
  {"IsPlayerSimulated", CBaseEntity_IsPlayerSimulated},
  {"IsPointSized", CBaseEntity_IsPointSized},
  {"IsPrecacheAllowed", CBaseEntity_IsPrecacheAllowed},
  {"IsServer", CBaseEntity_IsServer},
  {"IsSimulatedEveryTick", CBaseEntity_IsSimulatedEveryTick},
  {"IsSimulatingOnAlternateTicks", CBaseEntity_IsSimulatingOnAlternateTicks},
  {"IsSolid", CBaseEntity_IsSolid},
  {"IsSolidFlagSet", CBaseEntity_IsSolidFlagSet},
  {"IsStandable", CBaseEntity_IsStandable},
  {"IsTransparent", CBaseEntity_IsTransparent},
  {"IsWeapon", CBaseEntity_IsWeapon},
  {"KeyValue", CBaseEntity_KeyValue},
  {"LocalEyeAngles", CBaseEntity_LocalEyeAngles},
  {"NextMovePeer", CBaseEntity_NextMovePeer},
  {"ObjectCaps", CBaseEntity_ObjectCaps},
  {"OnRestore", CBaseEntity_OnRestore},
  {"PhysicsCheckForEntityUntouch", CBaseEntity_PhysicsCheckForEntityUntouch},
  {"PhysicsCheckWater", CBaseEntity_PhysicsCheckWater},
  {"PhysicsCheckWaterTransition", CBaseEntity_PhysicsCheckWaterTransition},
  {"PhysicsImpact", CBaseEntity_PhysicsImpact},
  {"PhysicsMarkEntitiesAsTouching", CBaseEntity_PhysicsMarkEntitiesAsTouching},
  {"PhysicsNotifyOtherOfGroundRemoval", CBaseEntity_PhysicsNotifyOtherOfGroundRemoval},
  {"PhysicsNotifyOtherOfUntouch", CBaseEntity_PhysicsNotifyOtherOfUntouch},
  {"PhysicsRemoveGroundList", CBaseEntity_PhysicsRemoveGroundList},
  {"PhysicsRemoveTouchedList", CBaseEntity_PhysicsRemoveTouchedList},
  {"PhysicsSimulate", CBaseEntity_PhysicsSimulate},
  {"PhysicsSolidMaskForEntity", CBaseEntity_PhysicsSolidMaskForEntity},
  {"PhysicsStartGroundContact", CBaseEntity_PhysicsStartGroundContact},
  {"Precache", CBaseEntity_Precache},
  {"PrecacheModel", CBaseEntity_PrecacheModel},
  {"PrecacheScriptSound", CBaseEntity_PrecacheScriptSound},
  {"PrecacheSound", CBaseEntity_PrecacheSound},
  {"PrefetchScriptSound", CBaseEntity_PrefetchScriptSound},
  {"PrefetchSound", CBaseEntity_PrefetchSound},
  {"RegisterThinkContext", CBaseEntity_RegisterThinkContext},
  {"Remove", CBaseEntity_Remove},
  {"RemoveAllDecals", CBaseEntity_RemoveAllDecals},
  {"RemoveDataObjectType", CBaseEntity_RemoveDataObjectType},
  {"RemoveEffects", CBaseEntity_RemoveEffects},
  {"RemoveEFlags", CBaseEntity_RemoveEFlags},
  {"RemoveFlag", CBaseEntity_RemoveFlag},
  {"RemoveSolidFlags", CBaseEntity_RemoveSolidFlags},
  {"SetAbsAngles", CBaseEntity_SetAbsAngles},
  {"SetAbsOrigin", CBaseEntity_SetAbsOrigin},
  {"SetAbsQueriesValid", CBaseEntity_SetAbsQueriesValid},
  {"SetAbsVelocity", CBaseEntity_SetAbsVelocity},
  {"SetAIWalkable", CBaseEntity_SetAIWalkable},
  {"SetAllowPrecache", CBaseEntity_SetAllowPrecache},
  {"SetAnimatedEveryTick", CBaseEntity_SetAnimatedEveryTick},
  {"SetAnimTime", CBaseEntity_SetAnimTime},
  {"SetBaseVelocity", CBaseEntity_SetBaseVelocity},
  {"SetBlocksLOS", CBaseEntity_SetBlocksLOS},
  {"SetCheckUntouch", CBaseEntity_SetCheckUntouch},
  {"SetClassname", CBaseEntity_SetClassname},
  {"SetCollisionBounds", CBaseEntity_SetCollisionBounds},
  {"SetCollisionGroup", CBaseEntity_SetCollisionGroup},
  {"SetEffectEntity", CBaseEntity_SetEffectEntity},
  {"SetEffects", CBaseEntity_SetEffects},
  {"SetEFlags", CBaseEntity_SetEFlags},
  {"SetFriction", CBaseEntity_SetFriction},
  {"SetGravity", CBaseEntity_SetGravity},
  {"SetGroundChangeTime", CBaseEntity_SetGroundChangeTime},
  {"SetGroundEntity", CBaseEntity_SetGroundEntity},
  {"SetHealth", CBaseEntity_SetHealth},
  {"SetLocalAngles", CBaseEntity_SetLocalAngles},
  {"SetLocalAngularVelocity", CBaseEntity_SetLocalAngularVelocity},
  {"SetLocalOrigin", CBaseEntity_SetLocalOrigin},
  {"SetLocalVelocity", CBaseEntity_SetLocalVelocity},
  {"SetModel", CBaseEntity_SetModel},
  {"SetModelIndex", CBaseEntity_SetModelIndex},
  {"SetModelName", CBaseEntity_SetModelName},
  {"SetMoveCollide", CBaseEntity_SetMoveCollide},
  {"SetMoveType", CBaseEntity_SetMoveType},
  {"SetNextThink", CBaseEntity_SetNextThink},
  {"SetOwnerEntity", CBaseEntity_SetOwnerEntity},
  {"SetParent", CBaseEntity_SetParent},
  {"SetPlayerSimulated", CBaseEntity_SetPlayerSimulated},
  {"SetPredictionEligible", CBaseEntity_SetPredictionEligible},
  {"SetPredictionPlayer", CBaseEntity_SetPredictionPlayer},
  {"SetRenderColor", CBaseEntity_SetRenderColor},
  {"SetRenderColorA", CBaseEntity_SetRenderColorA},
  {"SetRenderColorB", CBaseEntity_SetRenderColorB},
  {"SetRenderColorG", CBaseEntity_SetRenderColorG},
  {"SetRenderColorR", CBaseEntity_SetRenderColorR},
  {"SetSimulatedEveryTick", CBaseEntity_SetSimulatedEveryTick},
  {"SetSimulationTime", CBaseEntity_SetSimulationTime},
  {"SetSize", CBaseEntity_SetSize},
  {"SetSolid", CBaseEntity_SetSolid},
  {"SetSolidFlags", CBaseEntity_SetSolidFlags},
  {"SetTextureFrameIndex", CBaseEntity_SetTextureFrameIndex},
  {"SetViewOffset", CBaseEntity_SetViewOffset},
  {"SetWaterLevel", CBaseEntity_SetWaterLevel},
  {"SetWaterType", CBaseEntity_SetWaterType},
  {"ShouldCollide", CBaseEntity_ShouldCollide},
  {"ShouldSavePhysics", CBaseEntity_ShouldSavePhysics},
  {"Spawn", CBaseEntity_Spawn},
  {"StartGroundContact", CBaseEntity_StartGroundContact},
  {"StartTouch", CBaseEntity_StartTouch},
  {"StopFollowingEntity", CBaseEntity_StopFollowingEntity},
  {"SUB_Remove", CBaseEntity_SUB_Remove},
  {"Think", CBaseEntity_Think},
  {"ToggleFlag", CBaseEntity_ToggleFlag},
  {"Touch", CBaseEntity_Touch},
  {"TraceBleed", CBaseEntity_TraceBleed},
  {"UnsetPlayerSimulated", CBaseEntity_UnsetPlayerSimulated},
  {"UpdateOnRemove", CBaseEntity_UpdateOnRemove},
  {"VPhysicsDestroyObject", CBaseEntity_VPhysicsDestroyObject},
  {"VPhysicsGetObject", CBaseEntity_VPhysicsGetObject},
  {"VPhysicsGetObjectList", CBaseEntity_VPhysicsGetObjectList},
  {"VPhysicsInitNormal", CBaseEntity_VPhysicsInitNormal},
  {"VPhysicsInitStatic", CBaseEntity_VPhysicsInitStatic},
  {"VPhysicsIsFlesh", CBaseEntity_VPhysicsIsFlesh},
  {"VPhysicsSetObject", CBaseEntity_VPhysicsSetObject},
  {"VPhysicsUpdate", CBaseEntity_VPhysicsUpdate},
  {"WakeRestingObjects", CBaseEntity_WakeRestingObjects},
  {"WorldAlignMaxs", CBaseEntity_WorldAlignMaxs},
  {"WorldAlignMins", CBaseEntity_WorldAlignMins},
  {"WorldAlignSize", CBaseEntity_WorldAlignSize},
  {"WorldSpaceCenter", CBaseEntity_WorldSpaceCenter},
  {"WorldToEntitySpace", CBaseEntity_WorldToEntitySpace},
  {"__index", CBaseEntity___index},
  {"__newindex", CBaseEntity___newindex},
  {"__eq", CBaseEntity___eq},
  {"__tostring", CBaseEntity___tostring},
  {NULL, NULL}
};


static int luasrc_CreateEntityByName (lua_State *L) {
  lua_pushentity(L, CreateEntityByName(luaL_checkstring(L, 1)));
  return 1;
}


static const luaL_Reg CBaseEntity_funcs[] = {
  {"CreateEntityByName", luasrc_CreateEntityByName},
  {NULL, NULL}
};


/*
** Open CBaseEntity object
*/
LUALIB_API int luaopen_CBaseEntity_shared (lua_State *L) {
  luaL_getmetatable(L, LUA_BASEENTITYLIBNAME);
  if (lua_isnoneornil(L, -1)) {
    lua_pop(L, 1);
    luaL_newmetatable(L, LUA_BASEENTITYLIBNAME);
  }
  luaL_register(L, NULL, CBaseEntitymeta);
  lua_pushstring(L, "entity");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "entity" */
  luaL_register(L, "_G", CBaseEntity_funcs);
  lua_pop(L, 1);
  lua_pushentity(L, NULL);
  lua_setglobal(L, "NULL");  /* set global NULL */
  return 1;
}

