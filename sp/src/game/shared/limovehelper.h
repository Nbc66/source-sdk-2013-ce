//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LIMOVEHELPER_H
#define LIMOVEHELPER_H

#ifdef _WIN32
#pragma once
#endif


/* type for IMoveHelper functions */
typedef IMoveHelper lua_IMoveHelper;



/*
** access functions (stack -> C)
*/

LUA_API lua_IMoveHelper             *(lua_tomovehelper) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushmovehelper) (lua_State *L, lua_IMoveHelper *pHelper);



LUALIB_API lua_IMoveHelper *(luaL_checkmovehelper) (lua_State *L, int narg);


#endif // LIMOVEHELPER_H
