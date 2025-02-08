//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LBASEENTITY_SHARED_H
#define LBASEENTITY_SHARED_H
#ifdef _WIN32
#pragma once
#endif

/* type for CBaseEntity functions */
typedef CBaseEntity lua_CBaseEntity;



/*
** access functions (stack -> C)
*/

LUA_API lua_CBaseEntity     *(lua_toentity) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushentity) (lua_State *L, lua_CBaseEntity *pEntity);



LUALIB_API lua_CBaseEntity *(luaL_checkentity) (lua_State *L, int narg);
LUALIB_API lua_CBaseEntity *(luaL_optentity) (lua_State *L, int narg,
                                                            lua_CBaseEntity *def);


#endif // LBASEENTITY_SHARED_H
