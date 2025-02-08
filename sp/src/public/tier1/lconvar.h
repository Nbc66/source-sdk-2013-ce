//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $NoKeywords: $
//===========================================================================//

#ifndef LCONVAR_H
#define LCONVAR_H

#if _WIN32
#pragma once
#endif

/* type for ConCommand functions */
typedef ConCommand lua_ConCommand;


/* type for ConVar functions */
typedef ConVar lua_ConVar;



/*
** access functions (stack -> C)
*/

LUA_API lua_ConCommand     *(lua_toconcommand) (lua_State *L, int idx);
LUA_API lua_ConVar     *(lua_toconvar) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushconcommand) (lua_State *L, lua_ConCommand *pConCommand);
LUA_API void  (lua_pushconvar) (lua_State *L, lua_ConVar *pConVar);



LUALIB_API lua_ConCommand *(luaL_checkconcommand) (lua_State *L, int narg);
LUALIB_API lua_ConVar *(luaL_checkconvar) (lua_State *L, int narg);


#ifdef CLIENT_DLL
void ResetGameUIConCommandDatabase( void );
#endif
void ResetConCommandDatabase( void );
void ResetConVarDatabase( void );

#endif // LCONVAR_H
