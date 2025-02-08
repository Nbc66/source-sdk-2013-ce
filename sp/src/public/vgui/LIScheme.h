//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LISCHEME_H
#define LISCHEME_H

#ifdef _WIN32
#pragma once
#endif


/* type for IScheme functions */
typedef vgui::IScheme lua_IScheme;



/*
** access functions (stack -> C)
*/

LUA_API lua_IScheme             *(lua_toischeme) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushischeme) (lua_State *L, lua_IScheme *pScheme);



LUALIB_API lua_IScheme *(luaL_checkischeme) (lua_State *L, int narg);


#endif // LISCHEME_H
