//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#define lipredictionsystem_cpp

#include "cbase.h"
#include "ipredictionsystem.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lbaseentity_shared.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static int IPredictionSystem_SuppressEvents (lua_State *L) {
  IPredictionSystem::SuppressEvents(luaL_checkboolean(L, 1));
  return 0;
}

static int IPredictionSystem_SuppressHostEvents (lua_State *L) {
  IPredictionSystem::SuppressHostEvents(lua_toentity(L, 1));
  return 0;
}


static const luaL_Reg IPredictionSystemlib[] = {
  {"SuppressEvents",   IPredictionSystem_SuppressEvents},
  {"SuppressHostEvents", IPredictionSystem_SuppressHostEvents},
  {NULL, NULL}
};


/*
** Open IPredictionSystem library
*/
LUALIB_API int luaopen_IPredictionSystem (lua_State *L) {
  luaL_register(L, LUA_PREDICTIONSYSTEMLIBNAME, IPredictionSystemlib);
  return 1;
}
