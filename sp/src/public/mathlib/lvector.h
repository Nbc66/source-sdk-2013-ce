//====== Copyright © 1996-2005, Valve Corporation, All rights reserved. =======//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//

#ifndef LVECTOR_H
#define LVECTOR_H

#ifdef _WIN32
#pragma once
#endif

/* type for Vector functions */
typedef Vector lua_Vector;


/* type for QAngle functions */
typedef QAngle lua_QAngle;



/*
** access functions (stack -> C)
*/

LUA_API lua_Vector     &(lua_tovector) (lua_State *L, int idx);
LUA_API lua_QAngle     &(lua_toangle) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushvector) (lua_State *L, lua_Vector &v);
LUA_API void  (lua_pushangle) (lua_State *L, lua_QAngle &v);



LUALIB_API lua_Vector &(luaL_checkvector) (lua_State *L, int narg);
LUALIB_API lua_QAngle &(luaL_checkangle) (lua_State *L, int narg);
LUALIB_API lua_Vector &(luaL_optvector) (lua_State *L, int narg,
                                                       lua_Vector *def);
LUALIB_API lua_QAngle &(luaL_optangle) (lua_State *L, int narg,
                                                      lua_QAngle *def);


#endif

