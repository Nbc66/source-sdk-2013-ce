//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
//
// VMatrix always postmultiply vectors as in Ax = b.
// Given a set of basis vectors ((F)orward, (L)eft, (U)p), and a (T)ranslation, 
// a matrix to transform a vector into that space looks like this:
// Fx Lx Ux Tx
// Fy Ly Uy Ty
// Fz Lz Uz Tz
// 0   0  0  1

// Note that concatenating matrices needs to multiply them in reverse order.
// ie: if I want to apply matrix A, B, then C, the equation needs to look like this:
// C * B * A * v
// ie:
// v = A * v;
// v = B * v;
// v = C * v;
//=============================================================================

#define lvmatrix_cpp

#include "cbase.h"
#include <string.h>
#include "mathlib/vmatrix.h"
#include "mathlib/vector.h"
#include "mathlib/mathlib.h"
#include "fmtstr.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "lvmatrix.h"
#include "lvector.h"
#include "lmathlib.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

/*
** access functions (stack -> C)
*/


LUA_API lua_VMatrix &lua_tovmatrix (lua_State *L, int idx) {
  lua_VMatrix *matrix = (lua_VMatrix *)luaL_checkudata(L, idx, "VMatrix");
  return *matrix;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushvmatrix (lua_State *L, lua_VMatrix &matrix) {
  lua_VMatrix *pMat = (lua_VMatrix *)lua_newuserdata(L, sizeof(lua_VMatrix));
  *pMat = matrix;
  luaL_getmetatable(L, "VMatrix");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_VMatrix &luaL_checkvmatrix (lua_State *L, int narg) {
  lua_VMatrix *d = (lua_VMatrix *)luaL_checkudata(L, narg, "VMatrix");
  return *d;
}


static int VMatrix_ApplyRotation (lua_State *L) {
  lua_pushvector(L, luaL_checkvmatrix(L, 1).ApplyRotation(luaL_checkvector(L, 2)));
  return 1;
}

static int VMatrix_As3x4 (lua_State *L) {
  lua_pushmatrix(L, luaL_checkvmatrix(L, 1).As3x4());
  return 1;
}

static int VMatrix_Base (lua_State *L) {
  lua_pushnumber(L, *luaL_checkvmatrix(L, 1).Base());
  return 1;
}

static int VMatrix_CopyFrom3x4 (lua_State *L) {
  luaL_checkvmatrix(L, 1).CopyFrom3x4(luaL_checkmatrix(L, 2));
  return 0;
}

static int VMatrix_GetBasisVectors (lua_State *L) {
  luaL_checkvmatrix(L, 1).GetBasisVectors(luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_checkvector(L, 4));
  return 0;
}

static int VMatrix_GetForward (lua_State *L) {
  lua_pushvector(L, luaL_checkvmatrix(L, 1).GetForward());
  return 1;
}

static int VMatrix_GetLeft (lua_State *L) {
  lua_pushvector(L, luaL_checkvmatrix(L, 1).GetLeft());
  return 1;
}

static int VMatrix_GetScale (lua_State *L) {
  lua_pushvector(L, luaL_checkvmatrix(L, 1).GetScale());
  return 1;
}

static int VMatrix_GetTranslation (lua_State *L) {
  lua_pushvector(L, luaL_checkvmatrix(L, 1).GetTranslation());
  return 1;
}

static int VMatrix_GetUp (lua_State *L) {
  lua_pushvector(L, luaL_checkvmatrix(L, 1).GetUp());
  return 1;
}

static int VMatrix_Identity (lua_State *L) {
  luaL_checkvmatrix(L, 1).Identity();
  return 0;
}

static int VMatrix_Init (lua_State *L) {
  if (lua_gettop(L) < 17)
    luaL_checkvmatrix(L, 1).Init(luaL_checkmatrix(L, 2));
  else
    luaL_checkvmatrix(L, 1).Init(luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5), luaL_checknumber(L, 6), luaL_checknumber(L, 7), luaL_checknumber(L, 8), luaL_checknumber(L, 9), luaL_checknumber(L, 10), luaL_checknumber(L, 11), luaL_checknumber(L, 12), luaL_checknumber(L, 13), luaL_checknumber(L, 14), luaL_checknumber(L, 15), luaL_checknumber(L, 16), luaL_checknumber(L, 17));
  return 0;
}

static int VMatrix_InverseGeneral (lua_State *L) {
  lua_pushboolean(L, luaL_checkvmatrix(L, 1).InverseGeneral(luaL_checkvmatrix(L, 2)));
  return 1;
}

static int VMatrix_InverseTR (lua_State *L) {
  lua_pushvmatrix(L, luaL_checkvmatrix(L, 1).InverseTR());
  return 1;
}

static int VMatrix_IsIdentity (lua_State *L) {
  lua_pushboolean(L, luaL_checkvmatrix(L, 1).IsIdentity());
  return 1;
}

static int VMatrix_IsRotationMatrix (lua_State *L) {
  lua_pushboolean(L, luaL_checkvmatrix(L, 1).IsRotationMatrix());
  return 1;
}

static int VMatrix_MatrixMul (lua_State *L) {
  luaL_checkvmatrix(L, 1).MatrixMul(luaL_checkvmatrix(L, 2), luaL_checkvmatrix(L, 3));
  return 0;
}

static int VMatrix_NormalizeBasisVectors (lua_State *L) {
  lua_pushvmatrix(L, luaL_checkvmatrix(L, 1).NormalizeBasisVectors());
  return 1;
}

static int VMatrix_PostTranslate (lua_State *L) {
  luaL_checkvmatrix(L, 1).PostTranslate(luaL_checkvector(L, 2));
  return 0;
}

static int VMatrix_PreTranslate (lua_State *L) {
  luaL_checkvmatrix(L, 1).PreTranslate(luaL_checkvector(L, 2));
  return 0;
}

static int VMatrix_Scale (lua_State *L) {
  lua_pushvmatrix(L, luaL_checkvmatrix(L, 1).Scale(luaL_checkvector(L, 2)));
  return 1;
}

static int VMatrix_Set3x4 (lua_State *L) {
  luaL_checkvmatrix(L, 1).Set3x4(luaL_checkmatrix(L, 2));
  return 0;
}

static int VMatrix_SetBasisVectors (lua_State *L) {
  luaL_checkvmatrix(L, 1).SetBasisVectors(luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_checkvector(L, 4));
  return 0;
}

static int VMatrix_SetForward (lua_State *L) {
  luaL_checkvmatrix(L, 1).SetForward(luaL_checkvector(L, 2));
  return 0;
}

static int VMatrix_SetLeft (lua_State *L) {
  luaL_checkvmatrix(L, 1).SetLeft(luaL_checkvector(L, 2));
  return 0;
}

static int VMatrix_SetTranslation (lua_State *L) {
  luaL_checkvmatrix(L, 1).SetTranslation(luaL_checkvector(L, 2));
  return 0;
}

static int VMatrix_SetUp (lua_State *L) {
  luaL_checkvmatrix(L, 1).SetUp(luaL_checkvector(L, 2));
  return 0;
}

static int VMatrix_SetupMatrixOrgAngles (lua_State *L) {
  luaL_checkvmatrix(L, 1).SetupMatrixOrgAngles(luaL_checkvector(L, 2), luaL_checkangle(L, 3));
  return 0;
}

static int VMatrix_Transpose (lua_State *L) {
  lua_pushvmatrix(L, luaL_checkvmatrix(L, 1).Transpose());
  return 1;
}

static int VMatrix_Transpose3x3 (lua_State *L) {
  lua_pushvmatrix(L, luaL_checkvmatrix(L, 1).Transpose3x3());
  return 1;
}

static int VMatrix_V3Mul (lua_State *L) {
  luaL_checkvmatrix(L, 1).V3Mul(luaL_checkvector(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int VMatrix_VMul3x3 (lua_State *L) {
  lua_pushvector(L, luaL_checkvmatrix(L, 1).VMul3x3(luaL_checkvector(L, 2)));
  return 1;
}

static int VMatrix_VMul3x3Transpose (lua_State *L) {
  lua_pushvector(L, luaL_checkvmatrix(L, 1).VMul3x3Transpose(luaL_checkvector(L, 2)));
  return 1;
}

static int VMatrix_VMul4x3 (lua_State *L) {
  lua_pushvector(L, luaL_checkvmatrix(L, 1).VMul4x3(luaL_checkvector(L, 2)));
  return 1;
}

static int VMatrix_VMul4x3Transpose (lua_State *L) {
  lua_pushvector(L, luaL_checkvmatrix(L, 1).VMul4x3Transpose(luaL_checkvector(L, 2)));
  return 1;
}

static int VMatrix___index (lua_State *L) {
  VMatrix matrix = luaL_checkvmatrix(L, 1);
  const char *field = luaL_checkstring(L, 2);
  if (strcmp(field, "0") == 0) {
    lua_newtable(L);
	for (int j = 0; j < 4; j++)
	{
		lua_pushinteger(L, j);
		lua_pushnumber(L, matrix[0][j]);
		lua_settable(L, -3);
	}
  } else if (strcmp(field, "1") == 0) {
    lua_newtable(L);
	for (int j = 0; j < 4; j++)
	{
		lua_pushinteger(L, j);
		lua_pushnumber(L, matrix[1][j]);
		lua_settable(L, -3);
	}
  } else if (strcmp(field, "2") == 0) {
    lua_newtable(L);
	for (int j = 0; j < 4; j++)
	{
		lua_pushinteger(L, j);
		lua_pushnumber(L, matrix[2][j]);
		lua_settable(L, -3);
	}
  } else {
    lua_getmetatable(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
  }
  return 1;
}

static int VMatrix___newindex (lua_State *L) {
  // TODO
  return 0;
}

static int VMatrix___tostring (lua_State *L) {
  lua_pushfstring(L, "VMatrix: %s", VMatToString( luaL_checkvmatrix(L, 1) ));
  return 1;
}

static int VMatrix___eq (lua_State *L) {
  lua_pushboolean(L, luaL_checkvmatrix(L, 1) == luaL_checkvmatrix(L, 2));
  return 1;
}

static int VMatrix___add (lua_State *L) {
  lua_pushvmatrix(L, luaL_checkvmatrix(L, 1) + luaL_checkvmatrix(L, 2));
  return 1;
}

static int VMatrix___sub (lua_State *L) {
  lua_pushvmatrix(L, luaL_checkvmatrix(L, 1) - luaL_checkvmatrix(L, 2));
  return 1;
}

static int VMatrix___mul (lua_State *L) {
  lua_pushvmatrix(L, luaL_checkvmatrix(L, 1) * luaL_checkvmatrix(L, 2));
  return 1;
}

static int VMatrix___unm (lua_State *L) {
  lua_pushvmatrix(L, -luaL_checkvmatrix(L, 1));
  return 1;
}


static const luaL_Reg VMatrixmeta[] = {
  {"ApplyRotation", VMatrix_ApplyRotation},
  {"As3x4", VMatrix_As3x4},
  {"Base", VMatrix_Base},
  {"CopyFrom3x4", VMatrix_CopyFrom3x4},
  {"GetBasisVectors", VMatrix_GetBasisVectors},
  {"GetForward", VMatrix_GetForward},
  {"GetLeft", VMatrix_GetLeft},
  {"GetScale", VMatrix_GetScale},
  {"GetTranslation", VMatrix_GetTranslation},
  {"GetUp", VMatrix_GetUp},
  {"Identity", VMatrix_Identity},
  {"Init", VMatrix_Init},
  {"InverseGeneral", VMatrix_InverseGeneral},
  {"InverseTR", VMatrix_InverseTR},
  {"IsIdentity", VMatrix_IsIdentity},
  {"IsRotationMatrix", VMatrix_IsRotationMatrix},
  {"MatrixMul", VMatrix_MatrixMul},
  {"NormalizeBasisVectors", VMatrix_NormalizeBasisVectors},
  {"PostTranslate", VMatrix_PostTranslate},
  {"PreTranslate", VMatrix_PreTranslate},
  {"Scale", VMatrix_Scale},
  {"Set3x4", VMatrix_Set3x4},
  {"SetBasisVectors", VMatrix_SetBasisVectors},
  {"SetForward", VMatrix_SetForward},
  {"SetLeft", VMatrix_SetLeft},
  {"SetTranslation", VMatrix_SetTranslation},
  {"SetUp", VMatrix_SetUp},
  {"SetupMatrixOrgAngles", VMatrix_SetupMatrixOrgAngles},
  {"Transpose", VMatrix_Transpose},
  {"Transpose3x3", VMatrix_Transpose3x3},
  {"V3Mul", VMatrix_V3Mul},
  {"VMul3x3", VMatrix_VMul3x3},
  {"VMul3x3Transpose", VMatrix_VMul3x3Transpose},
  {"VMul4x3", VMatrix_VMul4x3},
  {"VMul4x3Transpose", VMatrix_VMul4x3Transpose},
  {"__index", VMatrix___index},
  {"__newindex", VMatrix___newindex},
  {"__tostring", VMatrix___tostring},
  {"__eq", VMatrix___eq},
  {"__add", VMatrix___add},
  {"__sub", VMatrix___sub},
  {"__mul", VMatrix___mul},
  {"__unm", VMatrix___unm},
  {NULL, NULL}
};


static int luasrc_VMatrix (lua_State *L) {
  if (lua_gettop(L) < 1) {
    VMatrix matrix = VMatrix();
    memset( &matrix, 0, sizeof( VMatrix ) );
    lua_pushvmatrix(L, matrix);
  } else if (lua_gettop(L) < 3) {
    VMatrix matrix = VMatrix(luaL_checkmatrix(L, 1));
    lua_pushvmatrix(L, matrix);
  } else if (lua_gettop(L) < 16) {
    VMatrix matrix = VMatrix(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3));
    lua_pushvmatrix(L, matrix);
  } else {
    VMatrix matrix = VMatrix(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5), luaL_checknumber(L, 6), luaL_checknumber(L, 7), luaL_checknumber(L, 8), luaL_checknumber(L, 9), luaL_checknumber(L, 10), luaL_checknumber(L, 11), luaL_checknumber(L, 12), luaL_checknumber(L, 13), luaL_checknumber(L, 14), luaL_checknumber(L, 15), luaL_checknumber(L, 16));
    lua_pushvmatrix(L, matrix);
  }
  return 1;
}


static const luaL_Reg _G_funcs[] = {
  {"VMatrix", luasrc_VMatrix},
  {NULL, NULL}
};


static int vmatrix_SetupMatrixIdentity (lua_State *L) {
  lua_pushvmatrix(L, SetupMatrixIdentity());
  return 1;
}

static int vmatrix_SetupMatrixScale (lua_State *L) {
  lua_pushvmatrix(L, SetupMatrixScale(luaL_checkvector(L, 1)));
  return 1;
}

static int vmatrix_SetupMatrixTranslation (lua_State *L) {
  lua_pushvmatrix(L, SetupMatrixTranslation(luaL_checkvector(L, 1)));
  return 1;
}

static int vmatrix_SetupMatrixAxisRot (lua_State *L) {
  lua_pushvmatrix(L, SetupMatrixAxisRot(luaL_checkvector(L, 1), luaL_checknumber(L, 2)));
  return 1;
}

static int vmatrix_SetupMatrixAngles (lua_State *L) {
  lua_pushvmatrix(L, SetupMatrixAngles(luaL_checkangle(L, 1)));
  return 1;
}

static int vmatrix_SetupMatrixOrgAngles (lua_State *L) {
  lua_pushvmatrix(L, SetupMatrixOrgAngles(luaL_checkvector(L, 1), luaL_checkangle(L, 2)));
  return 1;
}

static int vmatrix_VMatToString (lua_State *L) {
  lua_pushstring(L, VMatToString(luaL_checkvmatrix(L, 1)));
  return 1;
}

static int vmatrix_MatrixSetIdentity (lua_State *L) {
  MatrixSetIdentity(luaL_checkvmatrix(L, 1));
  return 0;
}

static int vmatrix_MatrixTranspose (lua_State *L) {
  MatrixTranspose(luaL_checkvmatrix(L, 1), luaL_checkvmatrix(L, 2));
  return 0;
}

static int vmatrix_MatrixCopy (lua_State *L) {
  MatrixCopy(luaL_checkvmatrix(L, 1), luaL_checkvmatrix(L, 2));
  return 0;
}

static int vmatrix_MatrixMultiply (lua_State *L) {
  MatrixMultiply(luaL_checkvmatrix(L, 1), luaL_checkvmatrix(L, 2), luaL_checkvmatrix(L, 3));
  return 0;
}

static int vmatrix_MatrixGetColumn (lua_State *L) {
  MatrixGetColumn(luaL_checkvmatrix(L, 1), luaL_checkint(L, 2), &luaL_checkvector(L, 3));
  return 0;
}

static int vmatrix_MatrixSetColumn (lua_State *L) {
  MatrixSetColumn(luaL_checkvmatrix(L, 1), luaL_checkint(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int vmatrix_MatrixGetRow (lua_State *L) {
  MatrixGetRow(luaL_checkvmatrix(L, 1), luaL_checkint(L, 2), &luaL_checkvector(L, 3));
  return 0;
}

static int vmatrix_MatrixSetRow (lua_State *L) {
  MatrixSetRow(luaL_checkvmatrix(L, 1), luaL_checkint(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int vmatrix_Vector3DMultiply (lua_State *L) {
  Vector3DMultiply(luaL_checkvmatrix(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int vmatrix_Vector3DMultiplyPositionProjective (lua_State *L) {
  Vector3DMultiplyPositionProjective(luaL_checkvmatrix(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int vmatrix_Vector3DMultiplyProjective (lua_State *L) {
  Vector3DMultiplyProjective(luaL_checkvmatrix(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int vmatrix_Vector3DMultiplyTranspose (lua_State *L) {
  Vector3DMultiplyTranspose(luaL_checkvmatrix(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int vmatrix_MatrixBuildTranslation (lua_State *L) {
  switch(lua_type(L, 2)) {
	case LUA_TNUMBER:
	default:
	  MatrixBuildTranslation(luaL_checkvmatrix(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
	  break;
	case LUA_TUSERDATA:
      if (luaL_checkudata(L, 2, "Vector"))
	    MatrixBuildTranslation(luaL_checkvmatrix(L, 1), luaL_checkvector(L, 2));
	  else
	    luaL_typerror(L, 2, "Vector");
	  break;
  }
  return 0;
}

static int vmatrix_MatrixTranslate (lua_State *L) {
  MatrixTranslate(luaL_checkvmatrix(L, 1), luaL_checkvector(L, 2));
  return 0;
}

static int vmatrix_MatrixBuildRotationAboutAxis (lua_State *L) {
  MatrixBuildRotationAboutAxis(luaL_checkvmatrix(L, 1), luaL_checkvector(L, 2), luaL_checknumber(L, 3));
  return 0;
}

static int vmatrix_MatrixBuildRotateZ (lua_State *L) {
  MatrixBuildRotateZ(luaL_checkvmatrix(L, 1), luaL_checknumber(L, 2));
  return 0;
}

static int vmatrix_MatrixRotate (lua_State *L) {
  MatrixRotate(luaL_checkvmatrix(L, 1), luaL_checkvector(L, 2), luaL_checknumber(L, 3));
  return 0;
}

static int vmatrix_MatrixBuildRotation (lua_State *L) {
  MatrixBuildRotation(luaL_checkvmatrix(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3));
  return 0;
}

static int vmatrix_MatrixBuildScale (lua_State *L) {
  switch(lua_type(L, 2)) {
	case LUA_TNUMBER:
	default:
	  MatrixBuildScale(luaL_checkvmatrix(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
	  break;
	case LUA_TUSERDATA:
      if (luaL_checkudata(L, 2, "Vector"))
	    MatrixBuildScale(luaL_checkvmatrix(L, 1), luaL_checkvector(L, 2));
	  else
	    luaL_typerror(L, 2, "Vector");
	  break;
  }
  return 0;
}

static int vmatrix_MatrixBuildPerspective (lua_State *L) {
  MatrixBuildPerspective(luaL_checkvmatrix(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5));
  return 0;
}

static int vmatrix_CalculateAABBFromProjectionMatrix (lua_State *L) {
  CalculateAABBFromProjectionMatrix(luaL_checkvmatrix(L, 1), &luaL_checkvector(L, 2), &luaL_checkvector(L, 3));
  return 0;
}

static int vmatrix_CalculateSphereFromProjectionMatrix (lua_State *L) {
  float flRadius = 0;
  CalculateSphereFromProjectionMatrix(luaL_checkvmatrix(L, 1), &luaL_checkvector(L, 2), &flRadius);
  lua_pushnumber(L, flRadius);
  return 1;
}

static int vmatrix_MatrixFromAngles (lua_State *L) {
  MatrixFromAngles(luaL_checkangle(L, 1), luaL_checkvmatrix(L, 2));
  return 0;
}

static int vmatrix_MatrixToAngles (lua_State *L) {
  MatrixToAngles(luaL_checkvmatrix(L, 1), luaL_checkangle(L, 2));
  return 0;
}

static int vmatrix_MatrixInverseTR (lua_State *L) {
  MatrixInverseTR(luaL_checkvmatrix(L, 1), luaL_checkvmatrix(L, 2));
  return 0;
}

static int vmatrix_MatrixInverseGeneral (lua_State *L) {
  MatrixInverseGeneral(luaL_checkvmatrix(L, 1), luaL_checkvmatrix(L, 2));
  return 0;
}

static int vmatrix_MatrixInverseTranspose (lua_State *L) {
  MatrixInverseTranspose(luaL_checkvmatrix(L, 1), luaL_checkvmatrix(L, 2));
  return 0;
}


static const luaL_Reg VMatrix_funcs[] = {
  {"SetupMatrixIdentity", vmatrix_SetupMatrixIdentity},
  {"SetupMatrixScale", vmatrix_SetupMatrixScale},
  {"SetupMatrixTranslation", vmatrix_SetupMatrixTranslation},
  {"SetupMatrixAxisRot", vmatrix_SetupMatrixAxisRot},
  {"SetupMatrixAngles", vmatrix_SetupMatrixAngles},
  {"SetupMatrixOrgAngles", vmatrix_SetupMatrixOrgAngles},
  {"VMatToString", vmatrix_VMatToString},
  {"MatrixSetIdentity", vmatrix_MatrixSetIdentity},
  {"MatrixTranspose", vmatrix_MatrixTranspose},
  {"MatrixCopy", vmatrix_MatrixCopy},
  {"MatrixMultiply", vmatrix_MatrixMultiply},
  {"MatrixGetColumn", vmatrix_MatrixGetColumn},
  {"MatrixSetColumn", vmatrix_MatrixSetColumn},
  {"MatrixGetRow", vmatrix_MatrixGetRow},
  {"MatrixSetRow", vmatrix_MatrixSetRow},
  {"Vector3DMultiply", vmatrix_Vector3DMultiply},
  {"Vector3DMultiplyPositionProjective", vmatrix_Vector3DMultiplyPositionProjective},
  {"Vector3DMultiplyProjective", vmatrix_Vector3DMultiplyProjective},
  {"Vector3DMultiplyTranspose", vmatrix_Vector3DMultiplyTranspose},
  {"MatrixBuildTranslation", vmatrix_MatrixBuildTranslation},
  {"MatrixTranslate", vmatrix_MatrixTranslate},
  {"MatrixBuildRotationAboutAxis", vmatrix_MatrixBuildRotationAboutAxis},
  {"MatrixBuildRotateZ", vmatrix_MatrixBuildRotateZ},
  {"MatrixRotate", vmatrix_MatrixRotate},
  {"MatrixBuildRotation", vmatrix_MatrixBuildRotation},
  {"MatrixBuildScale", vmatrix_MatrixBuildScale},
  {"MatrixBuildPerspective", vmatrix_MatrixBuildPerspective},
  {"CalculateAABBFromProjectionMatrix", vmatrix_CalculateAABBFromProjectionMatrix},
  {"CalculateSphereFromProjectionMatrix", vmatrix_CalculateSphereFromProjectionMatrix},
  {"MatrixFromAngles", vmatrix_MatrixFromAngles},
  {"MatrixToAngles", vmatrix_MatrixToAngles},
  {"MatrixInverseTR", vmatrix_MatrixInverseTR},
  {"MatrixInverseGeneral", vmatrix_MatrixInverseGeneral},
  {"MatrixInverseTranspose", vmatrix_MatrixInverseTranspose},
  {NULL, NULL}
};


/*
** Open VMatrix object
*/
LUALIB_API int luaopen_VMatrix (lua_State *L) {
  luaL_newmetatable(L, "VMatrix");
  luaL_register(L, NULL, VMatrixmeta);
  lua_pushstring(L, "vmatrix");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "vmatrix" */
  luaL_register(L, "_G", _G_funcs);
  lua_pop(L, 2);
  luaL_register(L, LUA_VMATRIXLIBNAME, VMatrix_funcs);
  return 1;
}


