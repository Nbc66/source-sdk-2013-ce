//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LNETWORKSTRINGTABLEDEFS_H
#define LNETWORKSTRINGTABLEDEFS_H
#ifdef _WIN32
#pragma once
#endif

#include "networkstringtabledefs.h"

/* type for INetworkStringTable functions */
typedef INetworkStringTable lua_INetworkStringTable;



/*
** access functions (stack -> C)
*/

LUA_API lua_INetworkStringTable     *(lua_tostringtable) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushstringtable) (lua_State *L, lua_INetworkStringTable *pNetworkStringTable);



LUALIB_API lua_INetworkStringTable *(luaL_checkstringtable) (lua_State *L, int narg);


#endif // LNETWORKSTRINGTABLEDEFS_H
