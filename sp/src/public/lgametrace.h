//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef LGAMETRACE_H
#define LGAMETRACE_H
#ifdef _WIN32
#pragma once
#endif


/* type for CGameTrace functions */
typedef CGameTrace lua_CGameTrace;



/*
** access functions (stack -> C)
*/

LUA_API lua_CGameTrace     &(lua_totrace) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushtrace) (lua_State *L, lua_CGameTrace &tr);



LUALIB_API lua_CGameTrace &(luaL_checktrace) (lua_State *L, int narg);


#endif // LGAMETRACE_H

