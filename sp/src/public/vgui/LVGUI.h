//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Basic header for using vgui
//
// $NoKeywords: $
//=============================================================================//

#ifndef LVGUI_H
#define LVGUI_H

#ifdef _WIN32
#pragma once
#endif

/* type for HScheme functions */
typedef vgui::HScheme lua_HScheme;


/* type for HFont functions */
typedef vgui::HFont lua_HFont;



/*
** access functions (stack -> C)
*/

LUA_API lua_HScheme     (lua_toscheme) (lua_State *L, int idx);
LUA_API lua_HFont     (lua_tofont) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushscheme) (lua_State *L, lua_HScheme hScheme);
LUA_API void  (lua_pushfont) (lua_State *L, lua_HFont hFont);



LUALIB_API lua_HScheme (luaL_checkscheme) (lua_State *L, int narg);
LUALIB_API lua_HFont (luaL_checkfont) (lua_State *L, int narg);


#endif // LVGUI_H
