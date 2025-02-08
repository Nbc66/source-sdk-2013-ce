//====== Copyright © 1996-2005, Valve Corporation, All rights reserved. =======//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//

#define lvector_cpp

#include "cbase.h"
#include "vector.h"
#include "fmtstr.h"
#include "lua.hpp"
#include "luasrclib.h"
#include "lvector.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

/*
** access functions (stack -> C)
*/


LUA_API lua_Vector &lua_tovector (lua_State *L, int idx) {
  lua_Vector *v = (lua_Vector *)luaL_checkudata(L, idx, "Vector");
  return *v;
}


LUA_API lua_QAngle &lua_toangle (lua_State *L, int idx) {
  lua_QAngle *v = (lua_QAngle *)luaL_checkudata(L, idx, "QAngle");
  return *v;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushvector (lua_State *L, lua_Vector &v) {
  lua_Vector *pVec = (lua_Vector *)lua_newuserdata(L, sizeof(lua_Vector));
  *pVec = v;
  luaL_getmetatable(L, "Vector");
  lua_setmetatable(L, -2);
}


LUA_API void lua_pushangle (lua_State *L, lua_QAngle &v) {
  lua_QAngle *pVec = (lua_QAngle *)lua_newuserdata(L, sizeof(lua_QAngle));
  *pVec = v;
  luaL_getmetatable(L, "QAngle");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_Vector &luaL_checkvector (lua_State *L, int narg) {
  lua_Vector *d = (lua_Vector *)luaL_checkudata(L, narg, "Vector");
  return *d;
}


LUALIB_API lua_QAngle &luaL_checkangle (lua_State *L, int narg) {
  lua_QAngle *d = (lua_QAngle *)luaL_checkudata(L, narg, "QAngle");
  return *d;
}


LUALIB_API lua_Vector &luaL_optvector (lua_State *L, int narg,
                                                     Vector *def) {
  return luaL_opt(L, luaL_checkvector, narg, *def);
}


LUALIB_API lua_QAngle &luaL_optangle (lua_State *L, int narg,
                                                     QAngle *def) {
  return luaL_opt(L, luaL_checkangle, narg, *def);
}


static int Vector_Cross (lua_State *L) {
  lua_pushvector(L, luaL_checkvector(L, 1).Cross(luaL_checkvector(L, 2)));
  return 1;
}

static int Vector_DistTo (lua_State *L) {
  lua_pushnumber(L, luaL_checkvector(L, 1).DistTo(luaL_checkvector(L, 2)));
  return 1;
}

static int Vector_DistToSqr (lua_State *L) {
  lua_pushnumber(L, luaL_checkvector(L, 1).DistToSqr(luaL_checkvector(L, 2)));
  return 1;
}

static int Vector_Dot (lua_State *L) {
  lua_pushnumber(L, luaL_checkvector(L, 1).Dot(luaL_checkvector(L, 2)));
  return 1;
}

static int Vector_Init (lua_State *L) {
  luaL_checkvector(L, 1).Init(luaL_optnumber(L, 2, 0.0f), luaL_optnumber(L, 3, 0.0f), luaL_optnumber(L, 4, 0.0f));
  return 0;
}

static int Vector_Invalidate (lua_State *L) {
  luaL_checkvector(L, 1).Invalidate();
  return 0;
}

static int Vector_IsLengthGreaterThan (lua_State *L) {
  lua_pushboolean(L, luaL_checkvector(L, 1).IsLengthGreaterThan(luaL_checknumber(L, 2)));
  return 1;
}

static int Vector_IsLengthLessThan (lua_State *L) {
  lua_pushboolean(L, luaL_checkvector(L, 1).IsLengthLessThan(luaL_checknumber(L, 2)));
  return 1;
}

static int Vector_IsValid (lua_State *L) {
  lua_pushboolean(L, luaL_checkvector(L, 1).IsValid());
  return 1;
}

static int Vector_Length (lua_State *L) {
  lua_pushnumber(L, luaL_checkvector(L, 1).Length());
  return 1;
}

static int Vector_Length2D (lua_State *L) {
  lua_pushnumber(L, luaL_checkvector(L, 1).Length2D());
  return 1;
}

static int Vector_Length2DSqr (lua_State *L) {
  lua_pushnumber(L, luaL_checkvector(L, 1).Length2DSqr());
  return 1;
}

static int Vector_LengthSqr (lua_State *L) {
  lua_pushnumber(L, luaL_checkvector(L, 1).LengthSqr());
  return 1;
}

static int Vector_Max (lua_State *L) {
  lua_pushvector(L, luaL_checkvector(L, 1).Max(luaL_checkvector(L, 2)));
  return 1;
}

static int Vector_Min (lua_State *L) {
  lua_pushvector(L, luaL_checkvector(L, 1).Min(luaL_checkvector(L, 2)));
  return 1;
}

static int Vector_MulAdd (lua_State *L) {
  luaL_checkvector(L, 1).MulAdd(luaL_checkvector(L, 2), luaL_checkvector(L, 3), luaL_checknumber(L, 4));
  return 0;
}

static int Vector_Negate (lua_State *L) {
  luaL_checkvector(L, 1).Negate();
  return 0;
}

static int Vector_NormalizeInPlace (lua_State *L) {
  lua_pushnumber(L, luaL_checkvector(L, 1).NormalizeInPlace());
  return 1;
}

static int Vector_Random (lua_State *L) {
  luaL_checkvector(L, 1).Random(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  return 0;
}

static int Vector_WithinAABox (lua_State *L) {
  lua_pushboolean(L, luaL_checkvector(L, 1).WithinAABox(luaL_checkvector(L, 2), luaL_checkvector(L, 3)));
  return 1;
}

static int Vector_Zero (lua_State *L) {
  luaL_checkvector(L, 1).Zero();
  return 0;
}

static int Vector___index (lua_State *L) {
  Vector v = luaL_checkvector(L, 1);
  const char *field = luaL_checkstring(L, 2);
  if (strcmp(field, "x") == 0)
    lua_pushnumber(L, v.x);
  else if (strcmp(field, "y") == 0)
    lua_pushnumber(L, v.y);
  else if (strcmp(field, "z") == 0)
    lua_pushnumber(L, v.z);
  else {
    lua_getmetatable(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
  }
  return 1;
}

static int Vector___newindex (lua_State *L) {
  const char *field = luaL_checkstring(L, 2);
  if (strcmp(field, "x") == 0)
    luaL_checkvector(L, 1).x = (vec_t)luaL_checknumber(L, 3);
  else if (strcmp(field, "y") == 0)
    luaL_checkvector(L, 1).y = (vec_t)luaL_checknumber(L, 3);
  else if (strcmp(field, "z") == 0)
    luaL_checkvector(L, 1).z = (vec_t)luaL_checknumber(L, 3);
  return 0;
}

static int Vector___tostring (lua_State *L) {
  lua_pushfstring(L, "Vector: %s", VecToString( luaL_checkvector(L, 1) ));
  return 1;
}

static int Vector___eq (lua_State *L) {
  lua_pushboolean(L, luaL_checkvector(L, 1) == luaL_checkvector(L, 2));
  return 1;
}

static int Vector___add (lua_State *L) {
  lua_pushvector(L, luaL_checkvector(L, 1) + luaL_checkvector(L, 2));
  return 1;
}

static int Vector___sub (lua_State *L) {
  lua_pushvector(L, luaL_checkvector(L, 1) - luaL_checkvector(L, 2));
  return 1;
}

static int Vector___mul (lua_State *L) {
  switch(lua_type(L, 1)) {
	case LUA_TNUMBER:
      lua_pushvector(L, luaL_checknumber(L, 1) * luaL_checkvector(L, 2));
	  break;
	case LUA_TUSERDATA:
	default:
      lua_pushvector(L, luaL_checkvector(L, 1) * luaL_checknumber(L, 2));
	  break;
  }
  return 1;
}

static int Vector___div (lua_State *L) {
  lua_pushvector(L, luaL_checkvector(L, 1) / luaL_checknumber(L, 2));
  return 1;
}

static int Vector___unm (lua_State *L) {
  lua_pushvector(L, -luaL_checkvector(L, 1));
  return 1;
}


static const luaL_Reg Vectormeta[] = {
  {"Cross", Vector_Cross},
  {"DistTo", Vector_DistTo},
  {"DistToSqr", Vector_DistToSqr},
  {"Dot", Vector_Dot},
  {"Init", Vector_Init},
  {"Invalidate", Vector_Invalidate},
  {"IsLengthGreaterThan", Vector_IsLengthGreaterThan},
  {"IsLengthLessThan", Vector_IsLengthLessThan},
  {"IsValid", Vector_IsValid},
  {"Length", Vector_Length},
  {"Length2D", Vector_Length2D},
  {"Length2DSqr", Vector_Length2DSqr},
  {"LengthSqr", Vector_LengthSqr},
  {"Max", Vector_Max},
  {"Min", Vector_Min},
  {"MulAdd", Vector_MulAdd},
  {"Negate", Vector_Negate},
  {"NormalizeInPlace", Vector_NormalizeInPlace},
  {"Random", Vector_Random},
  {"WithinAABox", Vector_WithinAABox},
  {"Zero", Vector_Zero},
  {"__index", Vector___index},
  {"__newindex", Vector___newindex},
  {"__tostring", Vector___tostring},
  {"__eq", Vector___eq},
  {"__add", Vector___add},
  {"__sub", Vector___sub},
  {"__mul", Vector___mul},
  {"__div", Vector___div},
  {"__unm", Vector___unm},
  {NULL, NULL}
};


static int luasrc_Vector (lua_State *L) {
  lua_pushvector(L, Vector((vec_t)luaL_optnumber(L, 1, 0.0f), (vec_t)luaL_optnumber(L, 2, 0.0f), (vec_t)luaL_optnumber(L, 3, 0.0f)));
  return 1;
}


static const luaL_Reg Vector_funcs[] = {
  {"Vector", luasrc_Vector},
  {NULL, NULL}
};


/*
** Open Vector object
*/
LUALIB_API int luaopen_Vector (lua_State *L) {
  luaL_newmetatable(L, LUA_VECTORLIBNAME);
  luaL_register(L, NULL, Vectormeta);
  lua_pushstring(L, "vector");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "vector" */
  luaL_register(L, "_G", Vector_funcs);
  lua_pop(L, 1);
  Vector origin = vec3_origin;
  lua_pushvector(L, origin);
  lua_setglobal(L, "vec3_origin");  /* set global vec3_origin */
  Vector invalid = vec3_invalid;
  lua_pushvector(L, invalid);
  lua_setglobal(L, "vec3_invalid");  /* set global vec3_invalid */
  return 1;
}


static int QAngle_Init (lua_State *L) {
  luaL_checkangle(L, 1).Init(luaL_optnumber(L, 1, 0.0f), luaL_optnumber(L, 1, 0.0f), luaL_optnumber(L, 1, 0.0f));
  return 0;
}

static int QAngle_Invalidate (lua_State *L) {
  luaL_checkangle(L, 1).Invalidate();
  return 0;
}

static int QAngle_IsValid (lua_State *L) {
  lua_pushboolean(L, luaL_checkangle(L, 1).IsValid());
  return 1;
}

static int QAngle_Length (lua_State *L) {
  lua_pushnumber(L, luaL_checkangle(L, 1).Length());
  return 1;
}

static int QAngle_LengthSqr (lua_State *L) {
  lua_pushnumber(L, luaL_checkangle(L, 1).LengthSqr());
  return 1;
}

static int QAngle___index (lua_State *L) {
  QAngle v = luaL_checkangle(L, 1);
  const char *field = luaL_checkstring(L, 2);
  if (strcmp(field, "x") == 0)
    lua_pushnumber(L, v.x);
  else if (strcmp(field, "y") == 0)
    lua_pushnumber(L, v.y);
  else if (strcmp(field, "z") == 0)
    lua_pushnumber(L, v.z);
  else {
    lua_getmetatable(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
  }
  return 1;
}

static int QAngle___newindex (lua_State *L) {
  const char *field = luaL_checkstring(L, 2);
  if (strcmp(field, "x") == 0)
    luaL_checkangle(L, 1).x = (vec_t)luaL_checknumber(L, 3);
  else if (strcmp(field, "y") == 0)
    luaL_checkangle(L, 1).y = (vec_t)luaL_checknumber(L, 3);
  else if (strcmp(field, "z") == 0)
    luaL_checkangle(L, 1).z = (vec_t)luaL_checknumber(L, 3);
  return 0;
}

static int QAngle___tostring (lua_State *L) {
  lua_pushfstring(L, VecToString( luaL_checkangle(L, 1) ));
  return 1;
}

static int QAngle___eq (lua_State *L) {
  lua_pushboolean(L, luaL_checkangle(L, 1) == luaL_checkangle(L, 2));
  return 1;
}

static int QAngle___add (lua_State *L) {
  lua_pushangle(L, luaL_checkangle(L, 1) + luaL_checkangle(L, 2));
  return 1;
}

static int QAngle___sub (lua_State *L) {
  lua_pushangle(L, luaL_checkangle(L, 1) - luaL_checkangle(L, 2));
  return 1;
}

static int QAngle___mul (lua_State *L) {
  lua_pushangle(L, luaL_checkangle(L, 1) * luaL_checknumber(L, 2));
  return 1;
}

static int QAngle___div (lua_State *L) {
  lua_pushangle(L, luaL_checkangle(L, 1) / luaL_checknumber(L, 2));
  return 1;
}

static int QAngle___unm (lua_State *L) {
  lua_pushangle(L, -luaL_checkangle(L, 1));
  return 1;
}


static const luaL_Reg QAnglemeta[] = {
  {"Init", QAngle_Init},
  {"Invalidate", QAngle_Invalidate},
  {"IsValid", QAngle_IsValid},
  {"Length", QAngle_Length},
  {"LengthSqr", QAngle_LengthSqr},
  {"__index", QAngle___index},
  {"__newindex", QAngle___newindex},
  {"__tostring", QAngle___tostring},
  {"__eq", QAngle___eq},
  {"__add", QAngle___add},
  {"__sub", QAngle___sub},
  {"__mul", QAngle___mul},
  {"__div", QAngle___div},
  {"__unm", QAngle___unm},
  {NULL, NULL}
};


static int luasrc_QAngle (lua_State *L) {
  lua_pushangle(L, QAngle((vec_t)luaL_optnumber(L, 1, 0.0f), (vec_t)luaL_optnumber(L, 2, 0.0f), (vec_t)luaL_optnumber(L, 3, 0.0f)));
  return 1;
}


static const luaL_Reg QAngle_funcs[] = {
  {"QAngle", luasrc_QAngle},
  {NULL, NULL}
};


/*
** Open QAngle object
*/
LUALIB_API int luaopen_QAngle (lua_State *L) {
  luaL_newmetatable(L, LUA_QANGLELIBNAME);
  luaL_register(L, NULL, QAnglemeta);
  lua_pushstring(L, "angle");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "angle" */
  luaL_register(L, "_G", QAngle_funcs);
  lua_pop(L, 1);
  QAngle v = vec3_angle;
  lua_pushangle(L, v);
  lua_setglobal(L, "vec3_angle");  /* set global vec3_angle */
  return 1;
}

