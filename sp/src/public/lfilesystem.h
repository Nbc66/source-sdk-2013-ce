//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#ifndef LFILESYSTEM_H
#define LFILESYSTEM_H

#ifdef _WIN32
#pragma once
#endif

/* type for FileHandle_t functions */
typedef FileHandle_t lua_FileHandle_t;



/*
** access functions (stack -> C)
*/

LUA_API lua_FileHandle_t     &(lua_tofilehandle) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushfilehandle) (lua_State *L, lua_FileHandle_t hFile);



LUALIB_API lua_FileHandle_t &(luaL_checkfilehandle) (lua_State *L, int narg);


#endif // LFILESYSTEM_H
