//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//

#ifndef LIMATERIAL_H
#define LIMATERIAL_H

#ifdef _WIN32
#pragma once
#endif

/* type for IMaterial functions */
typedef IMaterial lua_IMaterial;



/*
** access functions (stack -> C)
*/

LUA_API lua_IMaterial      *(lua_tomaterial) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushmaterial) (lua_State *L, lua_IMaterial *pMaterial);



LUALIB_API lua_IMaterial *(luaL_checkmaterial) (lua_State *L, int narg);


#endif // LIMATERIAL_H
