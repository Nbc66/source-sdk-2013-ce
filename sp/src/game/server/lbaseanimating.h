//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef LBASEANIMATING_H
#define LBASEANIMATING_H
#ifdef _WIN32
#pragma once
#endif

/* type for CBaseAnimating functions */
typedef CBaseAnimating lua_CBaseAnimating;



/*
** access functions (stack -> C)
*/

LUA_API lua_CBaseAnimating     *(lua_toanimating) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushanimating) (lua_State *L, lua_CBaseAnimating *pEntity);



LUALIB_API lua_CBaseAnimating *(luaL_checkanimating) (lua_State *L, int narg);


#endif // LBASEANIMATING_H
