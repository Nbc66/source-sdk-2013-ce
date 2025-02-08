//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#ifndef LISOUNDEMITTERSYSTEMBASE_H
#define LISOUNDEMITTERSYSTEMBASE_H
#ifdef _WIN32
#pragma once
#endif


/* type for CSoundParameters in Lua */
typedef CSoundParameters lua_CSoundParameters;



/*
** access functions (stack -> C)
*/

LUA_API lua_CSoundParameters      (lua_tosoundparameters) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushsoundparameters) (lua_State *L, lua_CSoundParameters &params);

#endif // LISOUNDEMITTERSYSTEMBASE_H
