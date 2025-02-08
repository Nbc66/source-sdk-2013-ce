//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LTAKEDAMAGEINFO_H
#define LTAKEDAMAGEINFO_H
#ifdef _WIN32
#pragma once
#endif


/* type for CTakeDamageInfo functions */
typedef CTakeDamageInfo lua_CTakeDamageInfo;



/*
** access functions (stack -> C)
*/

LUA_API lua_CTakeDamageInfo     &(lua_todamageinfo) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushdamageinfo) (lua_State *L, lua_CTakeDamageInfo &info);



LUALIB_API lua_CTakeDamageInfo &(luaL_checkdamageinfo) (lua_State *L, int narg);


#endif // LTAKEDAMAGEINFO_H
