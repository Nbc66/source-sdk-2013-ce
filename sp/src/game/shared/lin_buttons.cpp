//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#define lin_buttons_cpp

#include "cbase.h"
#include "in_buttons.h"
#include "luamanager.h"
#include "luasrclib.h"


/*
** Open IN library
*/
LUALIB_API int luaopen_IN (lua_State *L) {
  BEGIN_LUA_SET_ENUM_LIB(L, LUA_INLIBNAME);
    lua_pushenum(L, IN_ATTACK, "ATTACK");
    lua_pushenum(L, IN_JUMP, "JUMP");
    lua_pushenum(L, IN_DUCK, "DUCK");
    lua_pushenum(L, IN_FORWARD, "FORWARD");
    lua_pushenum(L, IN_BACK, "BACK");
    lua_pushenum(L, IN_USE, "USE");
    lua_pushenum(L, IN_CANCEL, "CANCEL");
    lua_pushenum(L, IN_LEFT, "LEFT");
    lua_pushenum(L, IN_RIGHT, "RIGHT");
    lua_pushenum(L, IN_MOVELEFT, "MOVELEFT");
    lua_pushenum(L, IN_MOVERIGHT, "MOVERIGHT");
    lua_pushenum(L, IN_ATTACK2, "ATTACK2");
    lua_pushenum(L, IN_RUN, "RUN");
    lua_pushenum(L, IN_RELOAD, "RELOAD");
    lua_pushenum(L, IN_ALT1, "ALT1");
    lua_pushenum(L, IN_ALT2, "ALT2");
    lua_pushenum(L, IN_SCORE, "SCORE");
    lua_pushenum(L, IN_SPEED, "SPEED");
    lua_pushenum(L, IN_WALK, "WALK");
    lua_pushenum(L, IN_ZOOM, "ZOOM");
    lua_pushenum(L, IN_WEAPON1, "WEAPON1");
    lua_pushenum(L, IN_WEAPON2, "WEAPON2");
    lua_pushenum(L, IN_BULLRUSH, "BULLRUSH");
    lua_pushenum(L, IN_GRENADE1, "GRENADE1");
    lua_pushenum(L, IN_GRENADE2, "GRENADE2");
  END_LUA_SET_ENUM_LIB(L);
  return 0;
}