//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Public interfaces to vphysics DLL
//
// $NoKeywords: $
//=============================================================================//

#define lvphysics_interface_cpp

#include "cbase.h"
#include "vphysics_interface.h"
#include "vphysics/performance.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lvphysics_interface.h"
#include "vphysics/lperformance.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

/*
** access functions (stack -> C)
*/


LUA_API lua_IPhysicsObject *lua_tophysicsobject (lua_State *L, int idx) {
  lua_IPhysicsObject **ppPhysicsObject = (lua_IPhysicsObject **)lua_touserdata(L, idx);
  return *ppPhysicsObject;
}


LUA_API lua_surfacephysicsparams_t lua_tosurfacephysicsparams (lua_State *L, int idx) {
  luaL_checktype(L, idx, LUA_TTABLE);
  surfacephysicsparams_t physics;
  lua_getfield(L, idx, "friction");
  if (!lua_isnil(L, -1))
    physics.friction = luaL_checknumber(L, -1);
  else
    physics.friction = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "elasticity");
  if (!lua_isnil(L, -1))
    physics.elasticity = luaL_checknumber(L, -1);
  else
    physics.elasticity = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "density");
  if (!lua_isnil(L, -1))
    physics.density = luaL_checknumber(L, -1);
  else
    physics.density = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "thickness");
  if (!lua_isnil(L, -1))
    physics.thickness = luaL_checknumber(L, -1);
  else
    physics.thickness = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "dampening");
  if (!lua_isnil(L, -1))
    physics.dampening = luaL_checknumber(L, -1);
  else
    physics.dampening = 0;
  lua_pop(L, 1);
  return physics;
}


LUA_API lua_surfaceaudioparams_t lua_tosurfaceaudioparams (lua_State *L, int idx) {
  luaL_checktype(L, idx, LUA_TTABLE);
  surfaceaudioparams_t audio;
  lua_getfield(L, idx, "reflectivity");
  if (!lua_isnil(L, -1))
    audio.reflectivity = luaL_checknumber(L, -1);
  else
    audio.reflectivity = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "hardnessFactor");
  if (!lua_isnil(L, -1))
    audio.hardnessFactor = luaL_checknumber(L, -1);
  else
    audio.hardnessFactor = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "roughnessFactor");
  if (!lua_isnil(L, -1))
    audio.roughnessFactor = luaL_checknumber(L, -1);
  else
    audio.roughnessFactor = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "roughThreshold");
  if (!lua_isnil(L, -1))
    audio.roughThreshold = luaL_checknumber(L, -1);
  else
    audio.roughThreshold = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "hardThreshold");
  if (!lua_isnil(L, -1))
    audio.hardThreshold = luaL_checknumber(L, -1);
  else
    audio.hardThreshold = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "hardVelocityThreshold");
  if (!lua_isnil(L, -1))
    audio.hardVelocityThreshold = luaL_checknumber(L, -1);
  else
    audio.hardVelocityThreshold = 0;
  lua_pop(L, 1);
  return audio;
}


LUA_API lua_surfacesoundnames_t lua_tosurfacesoundnames (lua_State *L, int idx) {
  luaL_checktype(L, idx, LUA_TTABLE);
  surfacesoundnames_t sounds;
  lua_getfield(L, idx, "stepleft");
  if (!lua_isnil(L, -1))
    sounds.stepleft = (unsigned short)luaL_checkinteger(L, -1);
  else
    sounds.stepleft = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "stepright");
  if (!lua_isnil(L, -1))
    sounds.stepright = (unsigned short)luaL_checkinteger(L, -1);
  else
    sounds.stepright = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "impactSoft");
  if (!lua_isnil(L, -1))
    sounds.impactSoft = (unsigned short)luaL_checkinteger(L, -1);
  else
    sounds.impactSoft = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "impactHard");
  if (!lua_isnil(L, -1))
    sounds.impactHard = (unsigned short)luaL_checkinteger(L, -1);
  else
    sounds.impactHard = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "scrapeSmooth");
  if (!lua_isnil(L, -1))
    sounds.scrapeSmooth = (unsigned short)luaL_checkinteger(L, -1);
  else
    sounds.scrapeSmooth = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "scrapeRough");
  if (!lua_isnil(L, -1))
    sounds.scrapeRough = (unsigned short)luaL_checkinteger(L, -1);
  else
    sounds.scrapeRough = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "bulletImpact");
  if (!lua_isnil(L, -1))
    sounds.bulletImpact = (unsigned short)luaL_checkinteger(L, -1);
  else
    sounds.bulletImpact = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "rolling");
  if (!lua_isnil(L, -1))
    sounds.rolling = (unsigned short)luaL_checkinteger(L, -1);
  else
    sounds.rolling = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "breakSound");
  if (!lua_isnil(L, -1))
    sounds.breakSound = (unsigned short)luaL_checkinteger(L, -1);
  else
    sounds.breakSound = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "strainSound");
  if (!lua_isnil(L, -1))
    sounds.strainSound = (unsigned short)luaL_checkinteger(L, -1);
  else
    sounds.strainSound = 0;
  lua_pop(L, 1);
  return sounds;
}


LUA_API lua_surfacesoundhandles_t lua_tosurfacesoundhandles (lua_State *L, int idx) {
  luaL_checktype(L, idx, LUA_TTABLE);
  surfacesoundhandles_t soundhandles;
  lua_getfield(L, idx, "stepleft");
  if (!lua_isnil(L, -1))
    soundhandles.stepleft = (short)luaL_checkinteger(L, -1);
  else
    soundhandles.stepleft = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "stepright");
  if (!lua_isnil(L, -1))
    soundhandles.stepright = (short)luaL_checkinteger(L, -1);
  else
    soundhandles.stepright = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "impactSoft");
  if (!lua_isnil(L, -1))
    soundhandles.impactSoft = (short)luaL_checkinteger(L, -1);
  else
    soundhandles.impactSoft = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "impactHard");
  if (!lua_isnil(L, -1))
    soundhandles.impactHard = (short)luaL_checkinteger(L, -1);
  else
    soundhandles.impactHard = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "scrapeSmooth");
  if (!lua_isnil(L, -1))
    soundhandles.scrapeSmooth = (short)luaL_checkinteger(L, -1);
  else
    soundhandles.scrapeSmooth = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "scrapeRough");
  if (!lua_isnil(L, -1))
    soundhandles.scrapeRough = (short)luaL_checkinteger(L, -1);
  else
    soundhandles.scrapeRough = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "bulletImpact");
  if (!lua_isnil(L, -1))
    soundhandles.bulletImpact = (short)luaL_checkinteger(L, -1);
  else
    soundhandles.bulletImpact = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "rolling");
  if (!lua_isnil(L, -1))
    soundhandles.rolling = (short)luaL_checkinteger(L, -1);
  else
    soundhandles.rolling = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "breakSound");
  if (!lua_isnil(L, -1))
    soundhandles.breakSound = (short)luaL_checkinteger(L, -1);
  else
    soundhandles.breakSound = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "strainSound");
  if (!lua_isnil(L, -1))
    soundhandles.strainSound = (short)luaL_checkinteger(L, -1);
  else
    soundhandles.strainSound = 0;
  lua_pop(L, 1);
  return soundhandles;
}


LUA_API lua_surfacegameprops_t lua_tosurfacegameprops (lua_State *L, int idx) {
  luaL_checktype(L, idx, LUA_TTABLE);
  surfacegameprops_t game;
  lua_getfield(L, idx, "maxSpeedFactor");
  if (!lua_isnil(L, -1))
    game.maxSpeedFactor = luaL_checknumber(L, -1);
  else
    game.maxSpeedFactor = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "jumpFactor");
  if (!lua_isnil(L, -1))
    game.jumpFactor = luaL_checknumber(L, -1);
  else
    game.jumpFactor = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "material");
  if (!lua_isnil(L, -1))
    game.material = (unsigned short)luaL_checkinteger(L, -1);
  else
    game.material = 0;
  lua_pop(L, 1);

  lua_getfield(L, idx, "climbable");
  if (!lua_isnil(L, -1))
    game.climbable = (unsigned char)luaL_checkinteger(L, -1);
  else
    game.climbable = 0;
  lua_pop(L, 1);
  lua_getfield(L, idx, "pad");
  if (!lua_isnil(L, -1))
    game.pad = (unsigned char)luaL_checkinteger(L, -1);
  else
    game.pad = 0;
  lua_pop(L, 1);
  return game;
}


#pragma warning (disable : 4701)


LUA_API lua_surfacedata_t lua_tosurfacedata (lua_State *L, int idx) {
  luaL_checktype(L, idx, LUA_TTABLE);
  surfacedata_t surface;
  lua_getfield(L, idx, "physics");
  if (!lua_isnil(L, -1))
    surface.physics = lua_tosurfacephysicsparams(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "audio");
  if (!lua_isnil(L, -1))
    surface.audio = lua_tosurfaceaudioparams(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "sounds");
  if (!lua_isnil(L, -1))
    surface.sounds = lua_tosurfacesoundnames(L, -1);
  lua_pop(L, 1);
  lua_getfield(L, idx, "game");
  if (!lua_isnil(L, -1))
    surface.game = lua_tosurfacegameprops(L, -1);
  lua_pop(L, 1);

  lua_getfield(L, idx, "soundhandles");
  if (!lua_isnil(L, -1))
    surface.soundhandles = lua_tosurfacesoundhandles(L, -1);
  lua_pop(L, 1);
  return surface;
}


LUA_API lua_IPhysicsSurfaceProps *lua_tophysicssurfaceprops (lua_State *L, int idx) {
  lua_IPhysicsSurfaceProps **ppProps = (lua_IPhysicsSurfaceProps **)lua_touserdata(L, idx);
  return *ppProps;
}



/*
** push functions (C -> stack)
*/


// FIXME?: So here's the deal folks; in the Source SDK storing physics objects
// long-term is not done frequently. This is because physics objects are, for
// the majority of the time, tied to plain physics props or other similar
// movable entities.
// 
// In the Lau SDK, we want to promote the storage of the entity in variables in
// Lua instead, which mirrors internal code storing entities in handles. There
// are no handles for IPhysicsObjects in the Source SDK, so here we use a
// pointer to a pointer.
// 
// This means this object is unsafe in Lua, since the entity which this physics
// object is tied to could be gone when you attempt to use it.
// 
// Henry wrote up a handle system for this, so if we need to end up using that
// due to unforeseen logical issues, we will.
LUA_API void lua_pushphysicsobject (lua_State *L, lua_IPhysicsObject *pPhysicsObject) {
  if (pPhysicsObject == NULL)
    lua_pushnil(L);
  else {
    lua_IPhysicsObject **ppPhysicsObject = (lua_IPhysicsObject **)lua_newuserdata(L, sizeof(pPhysicsObject));
    *ppPhysicsObject = pPhysicsObject;
    luaL_getmetatable(L, "IPhysicsObject");
    lua_setmetatable(L, -2);
  }
}


LUA_API void lua_pushsurfacephysicsparams (lua_State *L, lua_surfacephysicsparams_t *pphysics) {
  lua_newtable(L);
  lua_pushnumber(L, pphysics->friction);
  lua_setfield(L, -2, "friction");
  lua_pushnumber(L, pphysics->elasticity);
  lua_setfield(L, -2, "elasticity");
  lua_pushnumber(L, pphysics->density);
  lua_setfield(L, -2, "density");
  lua_pushnumber(L, pphysics->thickness);
  lua_setfield(L, -2, "thickness");
  lua_pushnumber(L, pphysics->dampening);
  lua_setfield(L, -2, "dampening");
}


LUA_API void lua_pushsurfaceaudioparams (lua_State *L, lua_surfaceaudioparams_t *paudio) {
  lua_newtable(L);
  lua_pushnumber(L, paudio->reflectivity);
  lua_setfield(L, -2, "reflectivity");
  lua_pushnumber(L, paudio->hardnessFactor);
  lua_setfield(L, -2, "hardnessFactor");
  lua_pushnumber(L, paudio->roughnessFactor);
  lua_setfield(L, -2, "roughnessFactor");

  lua_pushnumber(L, paudio->roughThreshold);
  lua_setfield(L, -2, "roughThreshold");
  lua_pushnumber(L, paudio->hardThreshold);
  lua_setfield(L, -2, "hardThreshold");
  lua_pushnumber(L, paudio->hardVelocityThreshold);
  lua_setfield(L, -2, "hardVelocityThreshold");
}


LUA_API void lua_pushsurfacesoundnames (lua_State *L, lua_surfacesoundnames_t *psounds) {
  lua_newtable(L);
  lua_pushinteger(L, psounds->stepleft);
  lua_setfield(L, -2, "stepleft");
  lua_pushinteger(L, psounds->stepright);
  lua_setfield(L, -2, "stepright");

  lua_pushinteger(L, psounds->impactSoft);
  lua_setfield(L, -2, "impactSoft");
  lua_pushinteger(L, psounds->impactHard);
  lua_setfield(L, -2, "impactHard");

  lua_pushinteger(L, psounds->scrapeSmooth);
  lua_setfield(L, -2, "scrapeSmooth");
  lua_pushinteger(L, psounds->scrapeRough);
  lua_setfield(L, -2, "scrapeRough");

  lua_pushinteger(L, psounds->bulletImpact);
  lua_setfield(L, -2, "bulletImpact");
  lua_pushinteger(L, psounds->rolling);
  lua_setfield(L, -2, "rolling");

  lua_pushinteger(L, psounds->breakSound);
  lua_setfield(L, -2, "breakSound");
  lua_pushinteger(L, psounds->strainSound);
  lua_setfield(L, -2, "strainSound");
}


LUA_API void lua_pushsurfacesoundhandles (lua_State *L, lua_surfacesoundhandles_t *psoundhandles) {
  lua_newtable(L);
  lua_pushinteger(L, psoundhandles->stepleft);
  lua_setfield(L, -2, "stepleft");
  lua_pushinteger(L, psoundhandles->stepright);
  lua_setfield(L, -2, "stepright");

  lua_pushinteger(L, psoundhandles->impactSoft);
  lua_setfield(L, -2, "impactSoft");
  lua_pushinteger(L, psoundhandles->impactHard);
  lua_setfield(L, -2, "impactHard");

  lua_pushinteger(L, psoundhandles->scrapeSmooth);
  lua_setfield(L, -2, "scrapeSmooth");
  lua_pushinteger(L, psoundhandles->scrapeRough);
  lua_setfield(L, -2, "scrapeRough");

  lua_pushinteger(L, psoundhandles->bulletImpact);
  lua_setfield(L, -2, "bulletImpact");
  lua_pushinteger(L, psoundhandles->rolling);
  lua_setfield(L, -2, "rolling");

  lua_pushinteger(L, psoundhandles->breakSound);
  lua_setfield(L, -2, "breakSound");
  lua_pushinteger(L, psoundhandles->strainSound);
  lua_setfield(L, -2, "strainSound");
}


LUA_API void lua_pushsurfacegameprops (lua_State *L, lua_surfacegameprops_t *pgame) {
  lua_newtable(L);
  lua_pushnumber(L, pgame->maxSpeedFactor);
  lua_setfield(L, -2, "maxSpeedFactor");
  lua_pushnumber(L, pgame->jumpFactor);
  lua_setfield(L, -2, "jumpFactor");

  lua_pushinteger(L, pgame->material);
  lua_setfield(L, -2, "material");

  lua_pushinteger(L, pgame->climbable);
  lua_setfield(L, -2, "climbable");
  lua_pushinteger(L, pgame->pad);
  lua_setfield(L, -2, "pad");
}


LUA_API void lua_pushsurfacedata (lua_State *L, lua_surfacedata_t *psurface) {
  lua_newtable(L);
  lua_pushsurfacephysicsparams(L, &psurface->physics);
  lua_setfield(L, -2, "physics");
  lua_pushsurfaceaudioparams(L, &psurface->audio);
  lua_setfield(L, -2, "audio");
  lua_pushsurfacesoundnames(L, &psurface->sounds);
  lua_setfield(L, -2, "sounds");
  lua_pushsurfacegameprops(L, &psurface->game);
  lua_setfield(L, -2, "game");

  lua_pushsurfacesoundhandles(L, &psurface->soundhandles);
  lua_setfield(L, -2, "soundhandles");
}


LUA_API void lua_pushphysicssurfaceprops (lua_State *L, lua_IPhysicsSurfaceProps *pProps) {
  if (pProps == NULL)
    lua_pushnil(L);
  else {
    lua_IPhysicsSurfaceProps **ppProps = (lua_IPhysicsSurfaceProps **)lua_newuserdata(L, sizeof(pProps));
    *ppProps = pProps;
    luaL_getmetatable(L, "IPhysicsSurfaceProps");
    lua_setmetatable(L, -2);
  }
}


LUALIB_API lua_IPhysicsObject *luaL_checkphysicsobject (lua_State *L, int narg) {
  lua_IPhysicsObject *d = lua_tophysicsobject(L, narg);
  if (d == NULL)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "IPhysicsObject expected, got NULL physicsobject");
  return d;
}


LUALIB_API lua_IPhysicsSurfaceProps *luaL_checkphysicssurfaceprops (lua_State *L, int narg) {
  lua_IPhysicsSurfaceProps **d = (lua_IPhysicsSurfaceProps **)luaL_checkudata(L, narg, "IPhysicsSurfaceProps");
  return *d;
}


static int physenv_CleanupDeleteList (lua_State *L) {
  physenv->CleanupDeleteList();
  return 0;
}

static int physenv_ClearStats (lua_State *L) {
  physenv->ClearStats();
  return 0;
}

static int physenv_DebugCheckContacts (lua_State *L) {
  physenv->DebugCheckContacts();
  return 0;
}

static int physenv_GetActiveObjectCount (lua_State *L) {
  lua_pushnumber(L, physenv->GetActiveObjectCount());
  return 1;
}

static int physenv_GetAirDensity (lua_State *L) {
  lua_pushnumber(L, physenv->GetAirDensity());
  return 1;
}

static int physenv_GetGravity (lua_State *L) {
  Vector pGravityVector;
  physenv->GetGravity(&pGravityVector);
  lua_pushvector(L, pGravityVector);
  return 1;
}

static int physenv_GetNextFrameTime (lua_State *L) {
  lua_pushnumber(L, physenv->GetNextFrameTime());
  return 1;
}

static int physenv_GetPerformanceSettings (lua_State *L) {
  physics_performanceparams_t pOutput;
  physenv->GetPerformanceSettings(&pOutput);
  lua_pushperformanceparams(L, &pOutput);
  return 1;
}

static int physenv_GetSimulationTime (lua_State *L) {
  lua_pushnumber(L, physenv->GetSimulationTime());
  return 1;
}

static int physenv_GetSimulationTimestep (lua_State *L) {
  lua_pushnumber(L, physenv->GetSimulationTimestep());
  return 1;
}

static int physenv_IsInSimulation (lua_State *L) {
  lua_pushboolean(L, physenv->IsInSimulation());
  return 1;
}

static int physenv_PostRestore (lua_State *L) {
  physenv->PostRestore();
  return 0;
}

static int physenv_ResetSimulationClock (lua_State *L) {
  physenv->ResetSimulationClock();
  return 0;
}

static int physenv_SetAirDensity (lua_State *L) {
  physenv->SetAirDensity(luaL_checknumber(L, 1));
  return 0;
}

static int physenv_SetGravity (lua_State *L) {
  physenv->SetGravity(luaL_checkvector(L, 1));
  return 0;
}

static int physenv_SetPerformanceSettings (lua_State *L) {
  physenv->SetPerformanceSettings(&lua_toperformanceparams(L, 1));
  return 0;
}

static int physenv_SetQuickDelete (lua_State *L) {
  physenv->SetQuickDelete(luaL_checkboolean(L, 1));
  return 0;
}

static int physenv_SetSimulationTimestep (lua_State *L) {
  physenv->SetSimulationTimestep(luaL_checknumber(L, 1));
  return 0;
}

static int physenv_Simulate (lua_State *L) {
  physenv->Simulate(luaL_checknumber(L, 1));
  return 0;
}


static const luaL_Reg physenvlib[] = {
  {"CleanupDeleteList",  physenv_CleanupDeleteList},
  {"ClearStats",  physenv_ClearStats},
  {"DebugCheckContacts",  physenv_DebugCheckContacts},
  {"GetActiveObjectCount",  physenv_GetActiveObjectCount},
  {"GetAirDensity",  physenv_GetAirDensity},
  {"GetGravity",  physenv_GetGravity},
  {"GetNextFrameTime",  physenv_GetNextFrameTime},
  {"GetPerformanceSettings",  physenv_GetPerformanceSettings},
  {"GetSimulationTime",  physenv_GetSimulationTime},
  {"GetSimulationTimestep",  physenv_GetSimulationTimestep},
  {"IsInSimulation",  physenv_IsInSimulation},
  {"PostRestore",  physenv_PostRestore},
  {"ResetSimulationClock",  physenv_ResetSimulationClock},
  {"SetAirDensity",  physenv_SetAirDensity},
  {"SetGravity",  physenv_SetGravity},
  {"SetPerformanceSettings",  physenv_SetPerformanceSettings},
  {"SetQuickDelete",  physenv_SetQuickDelete},
  {"SetSimulationTimestep",  physenv_SetSimulationTimestep},
  {"Simulate",  physenv_Simulate},
  {NULL, NULL}
};


/*
** Open physenv library
*/
LUALIB_API int luaopen_physenv (lua_State *L) {
  luaL_register(L, LUA_PHYSENVLIBNAME, physenvlib);
  return 1;
}


static int IPhysicsObject_AddVelocity (lua_State *L) {
  Vector velocity = luaL_checkvector(L, 2);
  AngularImpulse angularVelocity = luaL_checkvector(L, 3);
  luaL_checkphysicsobject(L, 1)->AddVelocity(&velocity, &angularVelocity);
  return 0;
}

static int IPhysicsObject_ApplyForceCenter (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->ApplyForceCenter(luaL_checkvector(L, 2));
  return 0;
}

static int IPhysicsObject_ApplyForceOffset (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->ApplyForceOffset(luaL_checkvector(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int IPhysicsObject_ApplyTorqueCenter (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->ApplyTorqueCenter(luaL_checkvector(L, 2));
  return 0;
}

static int IPhysicsObject_BecomeHinged (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->BecomeHinged(luaL_checkint(L, 2));
  return 0;
}

static int IPhysicsObject_BecomeTrigger (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->BecomeTrigger();
  return 0;
}

static int IPhysicsObject_CalculateAngularDrag (lua_State *L) {
  lua_pushnumber(L, luaL_checkphysicsobject(L, 1)->CalculateAngularDrag(luaL_checkvector(L, 2)));
  return 1;
}

static int IPhysicsObject_CalculateForceOffset (lua_State *L) {
  Vector centerForce, centerTorque;
  luaL_checkphysicsobject(L, 1)->CalculateForceOffset(luaL_checkvector(L, 2), luaL_checkvector(L, 3), &centerForce, &centerTorque);
  lua_pushvector(L, centerForce);
  lua_pushvector(L, centerTorque);
  return 2;
}

static int IPhysicsObject_CalculateLinearDrag (lua_State *L) {
  lua_pushnumber(L, luaL_checkphysicsobject(L, 1)->CalculateLinearDrag(luaL_checkvector(L, 2)));
  return 1;
}

static int IPhysicsObject_CalculateVelocityOffset (lua_State *L) {
  Vector centerVelocity, centerAngularVelocity;
  luaL_checkphysicsobject(L, 1)->CalculateVelocityOffset(luaL_checkvector(L, 2), luaL_checkvector(L, 3), &centerVelocity, &centerAngularVelocity);
  lua_pushvector(L, centerVelocity);
  lua_pushvector(L, centerAngularVelocity);
  return 2;
}

static int IPhysicsObject_EnableCollisions (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->EnableCollisions(luaL_checkboolean(L, 2));
  return 0;
}

static int IPhysicsObject_EnableDrag (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->EnableDrag(luaL_checkboolean(L, 2));
  return 0;
}

static int IPhysicsObject_EnableGravity (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->EnableGravity(luaL_checkboolean(L, 2));
  return 0;
}

static int IPhysicsObject_EnableMotion (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->EnableMotion(luaL_checkboolean(L, 2));
  return 0;
}

static int IPhysicsObject_GetCallbackFlags (lua_State *L) {
  lua_pushinteger(L, luaL_checkphysicsobject(L, 1)->GetCallbackFlags());
  return 1;
}

static int IPhysicsObject_GetContactPoint (lua_State *L) {
  Vector contactPoint;
  IPhysicsObject *contactObject;
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->GetContactPoint(&contactPoint, &contactObject));
  lua_pushvector(L, contactPoint);
  lua_pushphysicsobject(L, contactObject);
  return 3;
}

static int IPhysicsObject_GetContents (lua_State *L) {
  lua_pushinteger(L, luaL_checkphysicsobject(L, 1)->GetContents());
  return 1;
}

static int IPhysicsObject_GetDamping (lua_State *L) {
  float speed, rot;
  luaL_checkphysicsobject(L, 1)->GetDamping(&speed, &rot);
  lua_pushnumber(L, speed);
  lua_pushnumber(L, rot);
  return 2;
}

static int IPhysicsObject_GetEnergy (lua_State *L) {
  lua_pushnumber(L, luaL_checkphysicsobject(L, 1)->GetEnergy());
  return 1;
}

static int IPhysicsObject_GetGameFlags (lua_State *L) {
  lua_pushinteger(L, luaL_checkphysicsobject(L, 1)->GetGameFlags());
  return 1;
}

static int IPhysicsObject_GetGameIndex (lua_State *L) {
  lua_pushinteger(L, luaL_checkphysicsobject(L, 1)->GetGameIndex());
  return 1;
}

static int IPhysicsObject_GetImplicitVelocity (lua_State *L) {
  Vector velocity, angularVelocity;
  luaL_checkphysicsobject(L, 1)->GetImplicitVelocity(&velocity, &angularVelocity);
  lua_pushvector(L, velocity);
  lua_pushvector(L, angularVelocity);
  return 2;
}

static int IPhysicsObject_GetInertia (lua_State *L) {
  lua_pushvector(L, luaL_checkphysicsobject(L, 1)->GetInertia());
  return 1;
}

static int IPhysicsObject_GetInvInertia (lua_State *L) {
  lua_pushvector(L, luaL_checkphysicsobject(L, 1)->GetInvInertia());
  return 1;
}

static int IPhysicsObject_GetInvMass (lua_State *L) {
  lua_pushnumber(L, luaL_checkphysicsobject(L, 1)->GetInvMass());
  return 1;
}

static int IPhysicsObject_GetMass (lua_State *L) {
  lua_pushnumber(L, luaL_checkphysicsobject(L, 1)->GetMass());
  return 1;
}

static int IPhysicsObject_GetMassCenterLocalSpace (lua_State *L) {
  lua_pushvector(L, luaL_checkphysicsobject(L, 1)->GetMassCenterLocalSpace());
  return 1;
}

static int IPhysicsObject_GetMaterialIndex (lua_State *L) {
  lua_pushinteger(L, luaL_checkphysicsobject(L, 1)->GetMaterialIndex());
  return 1;
}

static int IPhysicsObject_GetName (lua_State *L) {
  lua_pushstring(L, luaL_checkphysicsobject(L, 1)->GetName());
  return 1;
}

static int IPhysicsObject_GetPosition (lua_State *L) {
  Vector worldPosition;
  QAngle angles;
  luaL_checkphysicsobject(L, 1)->GetPosition(&worldPosition, &angles);
  lua_pushvector(L, worldPosition);
  lua_pushangle(L, angles);
  return 2;
}

static int IPhysicsObject_GetShadowPosition (lua_State *L) {
  Vector position;
  QAngle angles;
  lua_pushinteger(L, luaL_checkphysicsobject(L, 1)->GetShadowPosition(&position, &angles));
  lua_pushvector(L, position);
  lua_pushangle(L, angles);
  return 3;
}

static int IPhysicsObject_GetSphereRadius (lua_State *L) {
  lua_pushnumber(L, luaL_checkphysicsobject(L, 1)->GetSphereRadius());
  return 1;
}

static int IPhysicsObject_GetVelocity (lua_State *L) {
  Vector velocity, angularVelocity;
  luaL_checkphysicsobject(L, 1)->GetVelocity(&velocity, &angularVelocity);
  lua_pushvector(L, velocity);
  lua_pushvector(L, angularVelocity);
  return 2;
}

static int IPhysicsObject_GetVelocityAtPoint (lua_State *L) {
  Vector pVelocity;
  luaL_checkphysicsobject(L, 1)->GetVelocityAtPoint(luaL_checkvector(L, 2), &pVelocity);
  lua_pushvector(L, pVelocity);
  return 1;
}

static int IPhysicsObject_IsAsleep (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsAsleep());
  return 1;
}

static int IPhysicsObject_IsAttachedToConstraint (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsAttachedToConstraint(luaL_checkboolean(L, 2)));
  return 1;
}

static int IPhysicsObject_IsCollisionEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsCollisionEnabled());
  return 1;
}

static int IPhysicsObject_IsDragEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsDragEnabled());
  return 1;
}

static int IPhysicsObject_IsFluid (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsFluid());
  return 1;
}

static int IPhysicsObject_IsGravityEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsGravityEnabled());
  return 1;
}

static int IPhysicsObject_IsHinged (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsHinged());
  return 1;
}

static int IPhysicsObject_IsMotionEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsMotionEnabled());
  return 1;
}

static int IPhysicsObject_IsMoveable (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsMoveable());
  return 1;
}

static int IPhysicsObject_IsStatic (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsStatic());
  return 1;
}

static int IPhysicsObject_IsTrigger (lua_State *L) {
  lua_pushboolean(L, luaL_checkphysicsobject(L, 1)->IsTrigger());
  return 1;
}

static int IPhysicsObject_LocalToWorld (lua_State *L) {
  Vector worldPosition;
  luaL_checkphysicsobject(L, 1)->LocalToWorld(&worldPosition, luaL_checkvector(L, 2));
  lua_pushvector(L, worldPosition);
  return 1;
}

static int IPhysicsObject_LocalToWorldVector (lua_State *L) {
  Vector worldVector;
  luaL_checkphysicsobject(L, 1)->LocalToWorldVector(&worldVector, luaL_checkvector(L, 2));
  lua_pushvector(L, worldVector);
  return 1;
}

static int IPhysicsObject_OutputDebugInfo (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->OutputDebugInfo();
  return 0;
}

static int IPhysicsObject_RecheckCollisionFilter (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->RecheckCollisionFilter();
  return 0;
}

static int IPhysicsObject_RecheckContactPoints (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->RecheckContactPoints();
  return 0;
}

static int IPhysicsObject_RemoveHinged (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->RemoveHinged();
  return 0;
}

static int IPhysicsObject_RemoveShadowController (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->RemoveShadowController();
  return 0;
}

static int IPhysicsObject_RemoveTrigger (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->RemoveTrigger();
  return 0;
}

static int IPhysicsObject_SetBuoyancyRatio (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->SetBuoyancyRatio(luaL_checknumber(L, 2));
  return 0;
}

static int IPhysicsObject_SetCallbackFlags (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->SetCallbackFlags(luaL_checkint(L, 2));
  return 0;
}

static int IPhysicsObject_SetContents (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->SetContents(luaL_checkint(L, 2));
  return 0;
}

static int IPhysicsObject_SetDragCoefficient (lua_State *L) {
  float pDrag = luaL_checknumber(L, 2);
  float pAngularDrag = luaL_checknumber(L, 3);
  luaL_checkphysicsobject(L, 1)->SetDragCoefficient(&pDrag, &pAngularDrag);
  return 0;
}

static int IPhysicsObject_SetGameFlags (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->SetGameFlags(luaL_checkint(L, 2));
  return 0;
}

static int IPhysicsObject_SetGameIndex (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->SetGameIndex(luaL_checkint(L, 2));
  return 0;
}

static int IPhysicsObject_SetMass (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->SetMass(luaL_checknumber(L, 2));
  return 0;
}

static int IPhysicsObject_SetMaterialIndex (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->SetMaterialIndex(luaL_checkint(L, 2));
  return 0;
}

static int IPhysicsObject_SetShadow (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->SetShadow(luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checkboolean(L, 4), luaL_checkboolean(L, 5));
  return 0;
}

static int IPhysicsObject_SetVelocity (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->SetVelocity(&luaL_checkvector(L, 2), &luaL_checkvector(L, 3));
  return 0;
}

static int IPhysicsObject_SetVelocityInstantaneous (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->SetVelocityInstantaneous(&luaL_checkvector(L, 2), &luaL_checkvector(L, 3));
  return 0;
}

static int IPhysicsObject_Sleep (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->Sleep();
  return 0;
}

static int IPhysicsObject_Wake (lua_State *L) {
  luaL_checkphysicsobject(L, 1)->Wake();
  return 0;
}

static int IPhysicsObject_WorldToLocal (lua_State *L) {
  Vector localPosition;
  luaL_checkphysicsobject(L, 1)->WorldToLocal(&localPosition, luaL_checkvector(L, 2));
  lua_pushvector(L, localPosition);
  return 1;
}

static int IPhysicsObject_WorldToLocalVector (lua_State *L) {
  Vector localVector;
  luaL_checkphysicsobject(L, 1)->WorldToLocalVector(&localVector, luaL_checkvector(L, 2));
  lua_pushvector(L, localVector);
  return 1;
}

static int IPhysicsObject___tostring (lua_State *L) {
  lua_pushfstring(L, "IPhysicsObject: %p", luaL_checkudata(L, 1, "IPhysicsObject"));
  return 1;
}


static const luaL_Reg IPhysicsObjectmeta[] = {
  {"AddVelocity", IPhysicsObject_AddVelocity},
  {"ApplyForceCenter", IPhysicsObject_ApplyForceCenter},
  {"ApplyForceOffset", IPhysicsObject_ApplyForceOffset},
  {"ApplyTorqueCenter", IPhysicsObject_ApplyTorqueCenter},
  {"BecomeHinged", IPhysicsObject_BecomeHinged},
  {"BecomeTrigger", IPhysicsObject_BecomeTrigger},
  {"CalculateAngularDrag", IPhysicsObject_CalculateAngularDrag},
  {"CalculateForceOffset", IPhysicsObject_CalculateForceOffset},
  {"CalculateLinearDrag", IPhysicsObject_CalculateLinearDrag},
  {"CalculateVelocityOffset", IPhysicsObject_CalculateVelocityOffset},
  {"EnableCollisions", IPhysicsObject_EnableCollisions},
  {"EnableDrag", IPhysicsObject_EnableDrag},
  {"EnableGravity", IPhysicsObject_EnableGravity},
  {"EnableMotion", IPhysicsObject_EnableMotion},
  {"GetCallbackFlags", IPhysicsObject_GetCallbackFlags},
  {"GetContactPoint", IPhysicsObject_GetContactPoint},
  {"GetContents", IPhysicsObject_GetContents},
  {"GetDamping", IPhysicsObject_GetDamping},
  {"GetEnergy", IPhysicsObject_GetEnergy},
  {"GetGameFlags", IPhysicsObject_GetGameFlags},
  {"GetGameIndex", IPhysicsObject_GetGameIndex},
  {"GetImplicitVelocity", IPhysicsObject_GetImplicitVelocity},
  {"GetInertia", IPhysicsObject_GetInertia},
  {"GetInvInertia", IPhysicsObject_GetInvInertia},
  {"GetInvMass", IPhysicsObject_GetInvMass},
  {"GetMass", IPhysicsObject_GetMass},
  {"GetMassCenterLocalSpace", IPhysicsObject_GetMassCenterLocalSpace},
  {"GetMaterialIndex", IPhysicsObject_GetMaterialIndex},
  {"GetName", IPhysicsObject_GetName},
  {"GetPosition", IPhysicsObject_GetPosition},
  {"GetShadowPosition", IPhysicsObject_GetShadowPosition},
  {"GetSphereRadius", IPhysicsObject_GetSphereRadius},
  {"GetVelocity", IPhysicsObject_GetVelocity},
  {"GetVelocityAtPoint", IPhysicsObject_GetVelocityAtPoint},
  {"IsAsleep", IPhysicsObject_IsAsleep},
  {"IsAttachedToConstraint", IPhysicsObject_IsAttachedToConstraint},
  {"IsCollisionEnabled", IPhysicsObject_IsCollisionEnabled},
  {"IsDragEnabled", IPhysicsObject_IsDragEnabled},
  {"IsFluid", IPhysicsObject_IsFluid},
  {"IsGravityEnabled", IPhysicsObject_IsGravityEnabled},
  {"IsHinged", IPhysicsObject_IsHinged},
  {"IsMotionEnabled", IPhysicsObject_IsMotionEnabled},
  {"IsMoveable", IPhysicsObject_IsMoveable},
  {"IsStatic", IPhysicsObject_IsStatic},
  {"IsTrigger", IPhysicsObject_IsTrigger},
  {"LocalToWorld", IPhysicsObject_LocalToWorld},
  {"LocalToWorldVector", IPhysicsObject_LocalToWorldVector},
  {"OutputDebugInfo", IPhysicsObject_OutputDebugInfo},
  {"RecheckCollisionFilter", IPhysicsObject_RecheckCollisionFilter},
  {"RecheckContactPoints", IPhysicsObject_RecheckContactPoints},
  {"RemoveHinged", IPhysicsObject_RemoveHinged},
  {"RemoveShadowController", IPhysicsObject_RemoveShadowController},
  {"RemoveTrigger", IPhysicsObject_RemoveTrigger},
  {"SetBuoyancyRatio", IPhysicsObject_SetBuoyancyRatio},
  {"SetCallbackFlags", IPhysicsObject_SetCallbackFlags},
  {"SetContents", IPhysicsObject_SetContents},
  {"SetDragCoefficient", IPhysicsObject_SetDragCoefficient},
  {"SetGameFlags", IPhysicsObject_SetGameFlags},
  {"SetGameIndex", IPhysicsObject_SetGameIndex},
  {"SetMass", IPhysicsObject_SetMass},
  {"SetMaterialIndex", IPhysicsObject_SetMaterialIndex},
  {"SetShadow", IPhysicsObject_SetShadow},
  {"SetVelocity", IPhysicsObject_SetVelocity},
  {"SetVelocityInstantaneous", IPhysicsObject_SetVelocityInstantaneous},
  {"Sleep", IPhysicsObject_Sleep},
  {"Wake", IPhysicsObject_Wake},
  {"WorldToLocal", IPhysicsObject_WorldToLocal},
  {"WorldToLocalVector", IPhysicsObject_WorldToLocalVector},
  {"__tostring", IPhysicsObject___tostring},
  {NULL, NULL}
};


/*
** Open IPhysicsObject object
*/
LUALIB_API int luaopen_IPhysicsObject (lua_State *L) {
  luaL_newmetatable(L, LUA_PHYSICSOBJECTLIBNAME);
  luaL_register(L, NULL, IPhysicsObjectmeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "physicsobject");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "physicsobject" */
  return 1;
}


static int IPhysicsSurfaceProps_GetPhysicsParameters (lua_State *L) {
  surfacephysicsparams_t pParamsOut;
  luaL_checkphysicssurfaceprops(L, 1)->GetPhysicsParameters(luaL_checkint(L, 2), &pParamsOut);
  lua_pushsurfacephysicsparams(L, &pParamsOut);
  return 1;
}

static int IPhysicsSurfaceProps_GetPhysicsProperties (lua_State *L) {
  float density, thickness, friction, elasticity;
  luaL_checkphysicssurfaceprops(L, 1)->GetPhysicsProperties(luaL_checkint(L, 2), &density, &thickness, &friction, &elasticity);
  lua_pushnumber(L, density);
  lua_pushnumber(L, thickness);
  lua_pushnumber(L, friction);
  lua_pushnumber(L, elasticity);
  return 4;
}

static int IPhysicsSurfaceProps_GetPropName (lua_State *L) {
  lua_pushstring(L, luaL_checkphysicssurfaceprops(L, 1)->GetPropName(luaL_checkint(L, 2)));
  return 1;
}

static int IPhysicsSurfaceProps_GetString (lua_State *L) {
  lua_pushstring(L, luaL_checkphysicssurfaceprops(L, 1)->GetString((unsigned short)luaL_checkinteger(L, 2)));
  return 1;
}

static int IPhysicsSurfaceProps_GetSurfaceData (lua_State *L) {
  lua_pushsurfacedata(L, luaL_checkphysicssurfaceprops(L, 1)->GetSurfaceData(luaL_checkint(L, 2)));
  return 1;
}

static int IPhysicsSurfaceProps_GetSurfaceIndex (lua_State *L) {
  lua_pushinteger(L, luaL_checkphysicssurfaceprops(L, 1)->GetSurfaceIndex(luaL_checkstring(L, 2)));
  return 1;
}

static int IPhysicsSurfaceProps_ParseSurfaceData (lua_State *L) {
  lua_pushinteger(L, luaL_checkphysicssurfaceprops(L, 1)->ParseSurfaceData(luaL_checkstring(L, 2), luaL_checkstring(L, 3)));
  return 1;
}

static int IPhysicsSurfaceProps_SurfacePropCount (lua_State *L) {
  lua_pushinteger(L, luaL_checkphysicssurfaceprops(L, 1)->SurfacePropCount());
  return 1;
}

static int IPhysicsSurfaceProps___tostring (lua_State *L) {
  lua_pushfstring(L, "IPhysicsSurfaceProps: %p", luaL_checkudata(L, 1, "IPhysicsSurfaceProps"));
  return 1;
}


static const luaL_Reg IPhysicsSurfacePropsmeta[] = {
  {"GetPhysicsParameters", IPhysicsSurfaceProps_GetPhysicsParameters},
  {"GetPhysicsProperties", IPhysicsSurfaceProps_GetPhysicsProperties},
  {"GetPropName", IPhysicsSurfaceProps_GetPropName},
  {"GetString", IPhysicsSurfaceProps_GetString},
  {"GetSurfaceData", IPhysicsSurfaceProps_GetSurfaceData},
  {"GetSurfaceIndex", IPhysicsSurfaceProps_GetSurfaceIndex},
  {"ParseSurfaceData", IPhysicsSurfaceProps_ParseSurfaceData},
  {"SurfacePropCount", IPhysicsSurfaceProps_SurfacePropCount},
  {"__tostring", IPhysicsSurfaceProps___tostring},
  {NULL, NULL}
};


/*
** Open IPhysicsSurfaceProps object
*/
LUALIB_API int luaopen_IPhysicsSurfaceProps (lua_State *L) {
  luaL_newmetatable(L, LUA_PHYSICSSURFACEPROPSLIBNAME);
  luaL_register(L, NULL, IPhysicsSurfacePropsmeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "physicssurfaceprops");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "physicssurfaceprops" */
  lua_pushphysicssurfaceprops(L, physprops);
  lua_setglobal(L, "physprops");  /* set global physprops */
  return 1;
}

