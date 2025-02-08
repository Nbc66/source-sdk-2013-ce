//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
//===========================================================================//

#define lmathlib_cpp

#include "cbase.h"
#include "mathlib.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "lmathlib.h"
#include "lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

/*
** access functions (stack -> C)
*/


LUA_API lua_matrix3x4_t &lua_tomatrix (lua_State *L, int idx) {
  lua_matrix3x4_t *matrix = (lua_matrix3x4_t *)luaL_checkudata(L, idx, "matrix3x4_t");
  return *matrix;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushmatrix (lua_State *L, lua_matrix3x4_t &matrix) {
  lua_matrix3x4_t *pMat = (lua_matrix3x4_t *)lua_newuserdata(L, sizeof(lua_matrix3x4_t));
  *pMat = matrix;
  luaL_getmetatable(L, "matrix3x4_t");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_matrix3x4_t &luaL_checkmatrix (lua_State *L, int narg) {
  lua_matrix3x4_t *d = (lua_matrix3x4_t *)luaL_checkudata(L, narg, "matrix3x4_t");
  return *d;
}


static int matrix3x4_t_Base (lua_State *L) {
  lua_pushnumber(L, *luaL_checkmatrix(L, 1).Base());
  return 1;
}

static int matrix3x4_t_Init (lua_State *L) {
  luaL_checkmatrix(L, 1).Init(luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_checkvector(L, 4), luaL_checkvector(L, 5));
  return 0;
}

static int matrix3x4_t_Invalidate (lua_State *L) {
  luaL_checkmatrix(L, 1).Invalidate();
  return 0;
}

static int matrix3x4_t___index (lua_State *L) {
  matrix3x4_t matrix = luaL_checkmatrix(L, 1);
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

static int matrix3x4_t___newindex (lua_State *L) {
  // TODO
  return 0;
}

static int matrix3x4_t___tostring (lua_State *L) {
  matrix3x4_t matrix = luaL_checkmatrix(L, 1);
  lua_pushfstring(L, "matrix3x4_t: %f, %f, %f, %f\n             %f, %f, %f, %f\n             %f, %f, %f, %f",
    matrix[0][0],	matrix[0][1], matrix[0][2], matrix[0][3],
    matrix[1][0],	matrix[1][1], matrix[1][2], matrix[1][3],
    matrix[2][0],	matrix[2][1], matrix[2][2], matrix[2][3]
  );
  return 1;
}


static const luaL_Reg matrix3x4_tmeta[] = {
  {"Base", matrix3x4_t_Base},
  {"Init", matrix3x4_t_Init},
  {"Invalidate", matrix3x4_t_Invalidate},
  {"__index", matrix3x4_t___index},
  {"__newindex", matrix3x4_t___newindex},
  {"__tostring", matrix3x4_t___tostring},
  {NULL, NULL}
};


static int luasrc_matrix3x4_t (lua_State *L) {
  if (lua_gettop(L) < 4) {
    matrix3x4_t matrix;
    memset( &matrix, 0, sizeof( matrix3x4_t ) );
    lua_pushmatrix(L, matrix);
  } else if (lua_gettop(L) < 12) {
    matrix3x4_t matrix = matrix3x4_t(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_checkvector(L, 4));
    lua_pushmatrix(L, matrix);
  } else {
    matrix3x4_t matrix = matrix3x4_t(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5), luaL_checknumber(L, 6), luaL_checknumber(L, 7), luaL_checknumber(L, 8), luaL_checknumber(L, 9), luaL_checknumber(L, 10), luaL_checknumber(L, 11), luaL_checknumber(L, 12));
    lua_pushmatrix(L, matrix);
  }
  return 1;
}


static const luaL_Reg matrix3x4_t_funcs[] = {
  {"matrix3x4_t", luasrc_matrix3x4_t},
  {NULL, NULL}
};


/*
** Open matrix3x4_t object
*/
LUALIB_API int luaopen_matrix3x4_t (lua_State *L) {
  luaL_newmetatable(L, LUA_MATRIXLIBNAME);
  luaL_register(L, NULL, matrix3x4_tmeta);
  lua_pushstring(L, "matrix");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "matrix" */
  luaL_register(L, "_G", matrix3x4_t_funcs);
  lua_pop(L, 1);
  return 1;
}


static int mathlib_clamp (lua_State *L) {
  lua_pushnumber(L, clamp(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3)));
  return 1;
}

static int mathlib_AngleVectors (lua_State *L) {
  if (lua_gettop(L) > 2)
    AngleVectors(luaL_checkangle(L, 1), &luaL_checkvector(L, 2), &luaL_checkvector(L, 3), &luaL_checkvector(L, 4));
  else
    AngleVectors(luaL_checkangle(L, 1), &luaL_checkvector(L, 2));
  return 0;
}

static int mathlib_VectorAngles (lua_State *L) {
  if (lua_gettop(L) > 2)
    VectorAngles(luaL_checkvector(L, 1), luaL_checkvector(L, 2), luaL_checkangle(L, 3));
  else
    VectorAngles(luaL_checkvector(L, 1), luaL_checkangle(L, 2));
  return 0;
}


static const luaL_Reg mathliblib[] = {
  {"clamp",   mathlib_clamp},
  {"AngleVectors",   mathlib_AngleVectors},
  {"VectorAngles",   mathlib_VectorAngles},
  {NULL, NULL}
};


/*
** Open mathlib library
*/
LUALIB_API int luaopen_mathlib (lua_State *L) {
  luaL_register(L, LUA_MATHLIBLIBNAME, mathliblib);
  return 1;
}

