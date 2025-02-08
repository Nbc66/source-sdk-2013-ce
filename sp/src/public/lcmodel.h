//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//

#ifndef LCMODEL_H
#define LCMODEL_H
#ifdef _WIN32
#pragma once
#endif

/*
==============================================================

COLLISION DETECTION

==============================================================
*/

LUA_API void lua_pushcsurface (lua_State *L, csurface_t surface) {
  lua_newtable(L);
  lua_pushinteger(L, surface.flags);
  lua_setfield(L, -2, "flags");
  lua_pushstring(L, surface.name);
  lua_setfield(L, -2, "name");
  lua_pushinteger(L, surface.surfaceProps);
  lua_setfield(L, -2, "surfaceProps");
}

#endif // LCMODEL_H

	