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

#ifndef LVMATRIX_H
#define LVMATRIX_H

#ifdef _WIN32
#pragma once
#endif

/* type for VMatrix functions */
typedef VMatrix lua_VMatrix;



/*
** access functions (stack -> C)
*/

LUA_API lua_VMatrix     &(lua_tovmatrix) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushvmatrix) (lua_State *L, lua_VMatrix &matrix);



LUALIB_API lua_VMatrix &(luaL_checkvmatrix) (lua_State *L, int narg);

#endif


