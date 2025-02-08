//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LCOLOR_H
#define LCOLOR_H

#ifdef _WIN32
#pragma once
#endif

/* type for Color functions */
typedef Color lua_Color;



/*
** access functions (stack -> C)
*/

LUA_API lua_Color      &(lua_tocolor) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushcolor) (lua_State *L, lua_Color &clr);



LUALIB_API lua_Color &(luaL_checkcolor) (lua_State *L, int narg);


#endif // LCOLOR_H
