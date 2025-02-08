//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
//===========================================================================//

#ifndef LMATHLIB_H
#define LMATHLIB_H

#ifdef _WIN32
#pragma once
#endif

/* type for matrix3x4_t functions */
typedef matrix3x4_t lua_matrix3x4_t;



/*
** access functions (stack -> C)
*/

LUA_API lua_matrix3x4_t     &(lua_tomatrix) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushmatrix) (lua_State *L, lua_matrix3x4_t &v);



LUALIB_API lua_matrix3x4_t &(luaL_checkmatrix) (lua_State *L, int narg);


#endif

