//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#ifndef LPANEL_H
#define LPANEL_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/Panel.h>

using namespace vgui;

/* type for Panel functions */
typedef Panel lua_Panel;



/*
** access functions (stack -> C)
*/

LUA_API lua_Panel     *(lua_topanel) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushpanel) (lua_State *L, lua_Panel *pPanel);
LUA_API void  (lua_pushpanel) (lua_State *L, VPANEL panel);



LUALIB_API lua_Panel *(luaL_checkpanel) (lua_State *L, int narg);
LUALIB_API VPANEL     (luaL_checkvpanel) (lua_State *L, int narg);
LUALIB_API lua_Panel *(luaL_optpanel) (lua_State *L, int narg,
                                                     lua_Panel *def);


#endif // LPANEL_H
