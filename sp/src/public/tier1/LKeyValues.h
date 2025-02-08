//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LKEYVALUES_H
#define LKEYVALUES_H
#ifdef _WIN32
#pragma once
#endif


/* type for KeyValues functions */
typedef KeyValues lua_KeyValues;



/*
** access functions (stack -> C)
*/

LUA_API lua_KeyValues     *(lua_tokeyvalues) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushkeyvalues) (lua_State *L, lua_KeyValues *pKV);



LUALIB_API lua_KeyValues *(luaL_checkkeyvalues) (lua_State *L, int narg);
LUALIB_API lua_KeyValues *(luaL_optkeyvalues) (lua_State *L, int narg,
                                                             lua_KeyValues *def);


#endif // LKEYVALUES_H
