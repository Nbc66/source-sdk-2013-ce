//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//

#define limaterial_cpp

#include "cbase.h"
#include "imaterial.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "limaterial.h"
#include "mathlib/lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


/*
** access functions (stack -> C)
*/


LUA_API lua_IMaterial *lua_tomaterial (lua_State *L, int idx) {
  lua_IMaterial **ppMaterial = (lua_IMaterial **)lua_touserdata(L, idx);
  return *ppMaterial;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushmaterial (lua_State *L, lua_IMaterial *pMaterial) {
  if (pMaterial == NULL)
    lua_pushnil(L);
  else {
    lua_IMaterial **ppMaterial = (lua_IMaterial **)lua_newuserdata(L, sizeof(pMaterial));
    *ppMaterial = pMaterial;
    luaL_getmetatable(L, "IMaterial");
    lua_setmetatable(L, -2);
  }
}


LUALIB_API lua_IMaterial *luaL_checkmaterial (lua_State *L, int narg) {
  lua_IMaterial **d = (lua_IMaterial **)luaL_checkudata(L, narg, "IMaterial");
  return *d;
}


static int IMaterial_AddRef (lua_State *L) {
  luaL_checkmaterial(L, 1)->AddRef();
  return 0;
}

static int IMaterial_AlphaModulate (lua_State *L) {
  luaL_checkmaterial(L, 1)->AlphaModulate(luaL_checknumber(L, 1));
  return 0;
}

static int IMaterial_ColorModulate (lua_State *L) {
  luaL_checkmaterial(L, 1)->ColorModulate(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  return 0;
}

static int IMaterial_DecrementReferenceCount (lua_State *L) {
  luaL_checkmaterial(L, 1)->DecrementReferenceCount();
  return 0;
}

static int IMaterial_DeleteIfUnreferenced (lua_State *L) {
  luaL_checkmaterial(L, 1)->DeleteIfUnreferenced();
  return 0;
}

static int IMaterial_GetAlphaModulation (lua_State *L) {
  lua_pushnumber(L, luaL_checkmaterial(L, 1)->GetAlphaModulation());
  return 1;
}

static int IMaterial_GetColorModulation (lua_State *L) {
  float r, g, b;
  luaL_checkmaterial(L, 1)->GetColorModulation(&r, &g, &b);
  lua_pushnumber(L, r);
  lua_pushnumber(L, g);
  lua_pushnumber(L, b);
  return 3;
}

static int IMaterial_GetEnumerationID (lua_State *L) {
  lua_pushinteger(L, luaL_checkmaterial(L, 1)->GetEnumerationID());
  return 1;
}

static int IMaterial_GetMappingHeight (lua_State *L) {
  lua_pushinteger(L, luaL_checkmaterial(L, 1)->GetMappingHeight());
  return 1;
}

static int IMaterial_GetMappingWidth (lua_State *L) {
  lua_pushinteger(L, luaL_checkmaterial(L, 1)->GetMappingWidth());
  return 1;
}

static int IMaterial_GetMaterialPage (lua_State *L) {
  lua_pushmaterial(L, luaL_checkmaterial(L, 1)->GetMaterialPage());
  return 1;
}

static int IMaterial_GetMaterialVarFlag (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->GetMaterialVarFlag((MaterialVarFlags_t)luaL_checkint(L, 1)));
  return 1;
}

static int IMaterial_GetMorphFormat (lua_State *L) {
  lua_pushinteger(L, luaL_checkmaterial(L, 1)->GetMorphFormat());
  return 1;
}

static int IMaterial_GetName (lua_State *L) {
  lua_pushstring(L, luaL_checkmaterial(L, 1)->GetName());
  return 1;
}

static int IMaterial_GetNumAnimationFrames (lua_State *L) {
  lua_pushinteger(L, luaL_checkmaterial(L, 1)->GetNumAnimationFrames());
  return 1;
}

static int IMaterial_GetNumPasses (lua_State *L) {
  lua_pushinteger(L, luaL_checkmaterial(L, 1)->GetNumPasses());
  return 1;
}

static int IMaterial_GetPropertyFlag (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->GetPropertyFlag((MaterialPropertyTypes_t)luaL_checkint(L, 1)));
  return 1;
}

static int IMaterial_GetReflectivity (lua_State *L) {
  luaL_checkmaterial(L, 1)->GetReflectivity(luaL_checkvector(L, 2));
  return 0;
}

static int IMaterial_GetShaderName (lua_State *L) {
  lua_pushstring(L, luaL_checkmaterial(L, 1)->GetShaderName());
  return 1;
}

static int IMaterial_GetTextureGroupName (lua_State *L) {
  lua_pushstring(L, luaL_checkmaterial(L, 1)->GetTextureGroupName());
  return 1;
}

static int IMaterial_GetTextureMemoryBytes (lua_State *L) {
  lua_pushinteger(L, luaL_checkmaterial(L, 1)->GetTextureMemoryBytes());
  return 1;
}

static int IMaterial_HasProxy (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->HasProxy());
  return 1;
}

static int IMaterial_IncrementReferenceCount (lua_State *L) {
  luaL_checkmaterial(L, 1)->IncrementReferenceCount();
  return 0;
}

static int IMaterial_InMaterialPage (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->InMaterialPage());
  return 1;
}

static int IMaterial_IsAlphaTested (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->IsAlphaTested());
  return 1;
}

static int IMaterial_IsErrorMaterial (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->IsErrorMaterial());
  return 1;
}

static int IMaterial_IsSpriteCard (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->IsSpriteCard());
  return 1;
}

static int IMaterial_IsTranslucent (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->IsTranslucent());
  return 1;
}

static int IMaterial_IsTwoSided (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->IsTwoSided());
  return 1;
}

static int IMaterial_IsVertexLit (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->IsVertexLit());
  return 1;
}

static int IMaterial_NeedsFullFrameBufferTexture (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->NeedsFullFrameBufferTexture(luaL_optboolean(L, 1, 1)));
  return 1;
}

static int IMaterial_NeedsLightmapBlendAlpha (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->NeedsLightmapBlendAlpha());
  return 1;
}

static int IMaterial_NeedsPowerOfTwoFrameBufferTexture (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->NeedsPowerOfTwoFrameBufferTexture(luaL_optboolean(L, 1, 1)));
  return 1;
}

static int IMaterial_NeedsSoftwareLighting (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->NeedsSoftwareLighting());
  return 1;
}

static int IMaterial_NeedsSoftwareSkinning (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->NeedsSoftwareSkinning());
  return 1;
}

static int IMaterial_NeedsTangentSpace (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->NeedsTangentSpace());
  return 1;
}

static int IMaterial_RecomputeStateSnapshots (lua_State *L) {
  luaL_checkmaterial(L, 1)->RecomputeStateSnapshots();
  return 0;
}

static int IMaterial_Refresh (lua_State *L) {
  luaL_checkmaterial(L, 1)->Refresh();
  return 0;
}

static int IMaterial_RefreshPreservingMaterialVars (lua_State *L) {
  luaL_checkmaterial(L, 1)->RefreshPreservingMaterialVars();
  return 0;
}

static int IMaterial_Release (lua_State *L) {
  luaL_checkmaterial(L, 1)->Release();
  return 0;
}

static int IMaterial_SetMaterialVarFlag (lua_State *L) {
  luaL_checkmaterial(L, 1)->SetMaterialVarFlag((MaterialVarFlags_t)luaL_checkint(L, 1), luaL_checkboolean(L, 2));
  return 0;
}

static int IMaterial_SetShader (lua_State *L) {
  luaL_checkmaterial(L, 1)->SetShader(luaL_checkstring(L, 1));
  return 0;
}

static int IMaterial_SetUseFixedFunctionBakedLighting (lua_State *L) {
  luaL_checkmaterial(L, 1)->SetUseFixedFunctionBakedLighting(luaL_checkboolean(L, 1));
  return 0;
}

static int IMaterial_ShaderParamCount (lua_State *L) {
  lua_pushinteger(L, luaL_checkmaterial(L, 1)->ShaderParamCount());
  return 1;
}

static int IMaterial_UsesEnvCubemap (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->UsesEnvCubemap());
  return 1;
}

static int IMaterial_WasReloadedFromWhitelist (lua_State *L) {
  lua_pushboolean(L, luaL_checkmaterial(L, 1)->WasReloadedFromWhitelist());
  return 1;
}

static int IMaterial___tostring (lua_State *L) {
  lua_pushfstring(L, "IMaterial: %s", luaL_checkmaterial(L, 1)->GetName());
  return 1;
}


static const luaL_Reg IMaterialmeta[] = {
  {"AddRef", IMaterial_AddRef},
  {"AlphaModulate", IMaterial_AlphaModulate},
  {"ColorModulate", IMaterial_ColorModulate},
  {"DecrementReferenceCount", IMaterial_DecrementReferenceCount},
  {"DeleteIfUnreferenced", IMaterial_DeleteIfUnreferenced},
  {"GetAlphaModulation", IMaterial_GetAlphaModulation},
  {"GetColorModulation", IMaterial_GetColorModulation},
  {"GetEnumerationID", IMaterial_GetEnumerationID},
  {"GetMappingHeight", IMaterial_GetMappingHeight},
  {"GetMappingWidth", IMaterial_GetMappingWidth},
  {"GetMaterialPage", IMaterial_GetMaterialPage},
  {"GetMaterialVarFlag", IMaterial_GetMaterialVarFlag},
  {"GetMorphFormat", IMaterial_GetMorphFormat},
  {"GetName", IMaterial_GetName},
  {"GetNumAnimationFrames", IMaterial_GetNumAnimationFrames},
  {"GetNumPasses", IMaterial_GetNumPasses},
  {"GetPropertyFlag", IMaterial_GetPropertyFlag},
  {"GetReflectivity", IMaterial_GetReflectivity},
  {"GetShaderName", IMaterial_GetShaderName},
  {"GetTextureGroupName", IMaterial_GetTextureGroupName},
  {"GetTextureMemoryBytes", IMaterial_GetTextureMemoryBytes},
  {"IncrementReferenceCount", IMaterial_IncrementReferenceCount},
  {"InMaterialPage", IMaterial_InMaterialPage},
  {"IsAlphaTested", IMaterial_IsAlphaTested},
  {"IsErrorMaterial", IMaterial_IsErrorMaterial},
  {"IsSpriteCard", IMaterial_IsSpriteCard},
  {"IsTranslucent", IMaterial_IsTranslucent},
  {"IsTwoSided", IMaterial_IsTwoSided},
  {"IsVertexLit", IMaterial_IsVertexLit},
  {"NeedsFullFrameBufferTexture", IMaterial_NeedsFullFrameBufferTexture},
  {"NeedsLightmapBlendAlpha", IMaterial_NeedsLightmapBlendAlpha},
  {"NeedsPowerOfTwoFrameBufferTexture", IMaterial_NeedsPowerOfTwoFrameBufferTexture},
  {"NeedsSoftwareLighting", IMaterial_NeedsSoftwareLighting},
  {"NeedsSoftwareSkinning", IMaterial_NeedsSoftwareSkinning},
  {"NeedsTangentSpace", IMaterial_NeedsTangentSpace},
  {"RecomputeStateSnapshots", IMaterial_RecomputeStateSnapshots},
  {"Refresh", IMaterial_Refresh},
  {"RefreshPreservingMaterialVars", IMaterial_RefreshPreservingMaterialVars},
  {"Release", IMaterial_Release},
  {"SetMaterialVarFlag", IMaterial_SetMaterialVarFlag},
  {"SetShader", IMaterial_SetShader},
  {"SetUseFixedFunctionBakedLighting", IMaterial_SetUseFixedFunctionBakedLighting},
  {"ShaderParamCount", IMaterial_ShaderParamCount},
  {"UsesEnvCubemap", IMaterial_UsesEnvCubemap},
  {"WasReloadedFromWhitelist", IMaterial_WasReloadedFromWhitelist},
  {"__tostring", IMaterial___tostring},
  {NULL, NULL}
};


/*
** Open IMaterial object
*/
LUALIB_API int luaopen_IMaterial (lua_State *L) {
  luaL_newmetatable(L, LUA_MATERIALLIBNAME);
  luaL_register(L, NULL, IMaterialmeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "material");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "material" */
  return 1;
}

