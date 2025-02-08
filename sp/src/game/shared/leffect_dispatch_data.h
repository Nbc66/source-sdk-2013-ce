//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#ifndef LEFFECT_DISPATCH_DATA_H
#define LEFFECT_DISPATCH_DATA_H
#ifdef _WIN32
#pragma once
#endif


/* type for CEffectData functions */
typedef CEffectData lua_CEffectData;



/*
** access functions (stack -> C)
*/

LUA_API lua_CEffectData     &(lua_toeffect) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pusheffect) (lua_State *L, lua_CEffectData &data);



LUALIB_API lua_CEffectData &(luaL_checkeffect) (lua_State *L, int narg);


#endif // LEFFECT_DISPATCH_DATA_H
