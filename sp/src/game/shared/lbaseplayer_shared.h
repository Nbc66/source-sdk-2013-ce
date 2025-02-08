//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LBASEPLAYER_SHARED_H
#define LBASEPLAYER_SHARED_H
#ifdef _WIN32
#pragma once
#endif

/* type for CBasePlayer functions */
typedef CBasePlayer lua_CBasePlayer;



/*
** access functions (stack -> C)
*/

LUA_API lua_CBasePlayer     *(lua_toplayer) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushplayer) (lua_State *L, lua_CBasePlayer *pPlayer);



LUALIB_API lua_CBasePlayer *(luaL_checkplayer) (lua_State *L, int narg);
LUALIB_API lua_CBasePlayer *(luaL_optplayer) (lua_State *L, int narg,
                                                            lua_CBasePlayer *def);


#endif // LBASEPLAYER_SHARED_H
