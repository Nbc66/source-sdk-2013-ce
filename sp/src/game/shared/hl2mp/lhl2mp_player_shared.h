//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#ifndef LHL2MP_PLAYER_SHARED_H
#define LHL2MP_PLAYER_SHARED_H
#pragma once

#ifdef CLIENT_DLL
	#include "hl2mp/c_hl2mp_player.h"
#else
	#include "hl2mp/hl2mp_player.h"
#endif

/* type for CHL2MP_Player functions */
typedef CHL2MP_Player lua_CHL2MP_Player;



/*
** access functions (stack -> C)
*/

LUA_API lua_CHL2MP_Player     *(lua_tohl2mpplayer) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushhl2mpplayer) (lua_State *L, lua_CHL2MP_Player *pPlayer);



LUALIB_API lua_CHL2MP_Player *(luaL_checkhl2mpplayer) (lua_State *L, int narg);
LUALIB_API lua_CHL2MP_Player *(luaL_opthl2mpplayer) (lua_State *L, int narg,
                                                                   lua_CHL2MP_Player *def);


#endif //LHL2MP_PLAYER_SHARED_h
