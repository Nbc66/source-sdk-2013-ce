//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//

#define lbspflags_cpp

#include "cbase.h"
#include "bspflags.h"
#include "luamanager.h"
#include "luasrclib.h"


/*
** Open CONTENTS library
*/
LUALIB_API int luaopen_CONTENTS (lua_State *L) {
  BEGIN_LUA_SET_ENUM_LIB(L, LUA_CONTENTSLIBNAME);
    lua_pushenum(L, CONTENTS_EMPTY, "EMPTY");

    lua_pushenum(L, CONTENTS_SOLID, "SOLID");
    lua_pushenum(L, CONTENTS_WINDOW, "WINDOW");
    lua_pushenum(L, CONTENTS_AUX, "AUX");
    lua_pushenum(L, CONTENTS_GRATE, "GRATE");
    lua_pushenum(L, CONTENTS_SLIME, "SLIME");
    lua_pushenum(L, CONTENTS_WATER, "WATER");
    lua_pushenum(L, CONTENTS_BLOCKLOS, "BLOCKLOS");
    lua_pushenum(L, CONTENTS_OPAQUE, "OPAQUE");

    lua_pushenum(L, CONTENTS_TESTFOGVOLUME, "TESTFOGVOLUME");
    lua_pushenum(L, CONTENTS_UNUSED, "UNUSED");

    lua_pushenum(L, CONTENTS_TEAM1, "TEAM1");
    lua_pushenum(L, CONTENTS_TEAM2, "TEAM2");

    lua_pushenum(L, CONTENTS_IGNORE_NODRAW_OPAQUE, "IGNORE_NODRAW_OPAQUE");

    lua_pushenum(L, CONTENTS_MOVEABLE, "MOVEABLE");

    lua_pushenum(L, CONTENTS_AREAPORTAL, "AREAPORTAL");

	lua_pushenum(L, CONTENTS_PLAYERCLIP, "PLAYERCLIP");
	lua_pushenum(L, CONTENTS_MONSTERCLIP, "MONSTERCLIP");

	lua_pushenum(L, CONTENTS_CURRENT_0, "CURRENT_0");
	lua_pushenum(L, CONTENTS_CURRENT_90, "CURRENT_90");
	lua_pushenum(L, CONTENTS_CURRENT_180, "CURRENT_180");
	lua_pushenum(L, CONTENTS_CURRENT_270, "CURRENT_270");
	lua_pushenum(L, CONTENTS_CURRENT_UP, "CURRENT_UP");
	lua_pushenum(L, CONTENTS_CURRENT_DOWN, "CURRENT_DOWN");

	lua_pushenum(L, CONTENTS_ORIGIN, "ORIGIN");

	lua_pushenum(L, CONTENTS_MONSTER, "MONSTER");
	lua_pushenum(L, CONTENTS_DEBRIS, "DEBRIS");
	lua_pushenum(L, CONTENTS_DETAIL, "DETAIL");
	lua_pushenum(L, CONTENTS_TRANSLUCENT, "TRANSLUCENT");
	lua_pushenum(L, CONTENTS_LADDER, "LADDER");
	lua_pushenum(L, CONTENTS_HITBOX, "HITBOX");
  END_LUA_SET_ENUM_LIB(L);
  return 0;
}


/*
** Open SURF library
*/
LUALIB_API int luaopen_SURF (lua_State *L) {
  BEGIN_LUA_SET_ENUM_LIB(L, LUA_SURFLIBNAME);
    lua_pushenum(L, SURF_LIGHT, "LIGHT");
    lua_pushenum(L, SURF_SKY2D, "SKY2D");
    lua_pushenum(L, SURF_SKY, "SKY");
    lua_pushenum(L, SURF_WARP, "WARP");
    lua_pushenum(L, SURF_TRANS, "TRANS");
    lua_pushenum(L, SURF_NOPORTAL, "NOPORTAL");
    lua_pushenum(L, SURF_TRIGGER, "TRIGGER");
    lua_pushenum(L, SURF_NODRAW, "NODRAW");

    lua_pushenum(L, SURF_HINT, "HINT");

    lua_pushenum(L, SURF_SKIP, "SKIP");
    lua_pushenum(L, SURF_NOLIGHT, "NOLIGHT");
    lua_pushenum(L, SURF_BUMPLIGHT, "BUMPLIGHT");
    lua_pushenum(L, SURF_NOSHADOWS, "NOSHADOWS");
    lua_pushenum(L, SURF_NODECALS, "NODECALS");
    lua_pushenum(L, SURF_NOCHOP, "NOCHOP");
    lua_pushenum(L, SURF_HITBOX, "HITBOX");
  END_LUA_SET_ENUM_LIB(L);
  return 0;
}


/*
** Open MASK library
*/
LUALIB_API int luaopen_MASK (lua_State *L) {
  BEGIN_LUA_SET_ENUM_LIB(L, LUA_MASKLIBNAME);
    lua_pushenum(L, MASK_ALL, "ALL");
    lua_pushenum(L, MASK_SOLID, "SOLID");
    lua_pushenum(L, MASK_PLAYERSOLID, "PLAYERSOLID");
    lua_pushenum(L, MASK_NPCSOLID, "NPCSOLID");
    lua_pushenum(L, MASK_WATER, "WATER");
    lua_pushenum(L, MASK_OPAQUE, "OPAQUE");
    lua_pushenum(L, MASK_OPAQUE_AND_NPCS, "OPAQUE_AND_NPCS");
    lua_pushenum(L, MASK_BLOCKLOS, "BLOCKLOS");
    lua_pushenum(L, MASK_BLOCKLOS_AND_NPCS, "BLOCKLOS_AND_NPCS");
    lua_pushenum(L, MASK_VISIBLE, "VISIBLE");
    lua_pushenum(L, MASK_VISIBLE_AND_NPCS, "VISIBLE_AND_NPCS");
    lua_pushenum(L, MASK_SHOT, "SHOT");
    lua_pushenum(L, MASK_SHOT_HULL, "SHOT_HULL");
    lua_pushenum(L, MASK_SHOT_PORTAL, "SHOT_PORTAL");
    lua_pushenum(L, MASK_SOLID_BRUSHONLY, "SOLID_BRUSHONLY");
    lua_pushenum(L, MASK_PLAYERSOLID_BRUSHONLY, "PLAYERSOLID_BRUSHONLY");
    lua_pushenum(L, MASK_NPCSOLID_BRUSHONLY, "NPCSOLID_BRUSHONLY");
    lua_pushenum(L, MASK_NPCWORLDSTATIC, "NPCWORLDSTATIC");
    lua_pushenum(L, MASK_SPLITAREAPORTAL, "SPLITAREAPORTAL");

    lua_pushenum(L, MASK_CURRENT, "CURRENT");

    lua_pushenum(L, MASK_DEADSOLID, "DEADSOLID");
  END_LUA_SET_ENUM_LIB(L);
  return 0;
}
