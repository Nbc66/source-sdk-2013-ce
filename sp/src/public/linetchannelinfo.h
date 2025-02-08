//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//
#if !defined( LINETCHANNELINFO_H )
#define LINETCHANNELINFO_H
#ifdef _WIN32
#pragma once
#endif

#pragma warning( disable: 4189 )


/* type for INetChannelInfo functions */
typedef INetChannelInfo lua_INetChannelInfo;



/*
** access functions (stack -> C)
*/

LUA_API lua_INetChannelInfo     *(lua_tonetchannel) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushnetchannel) (lua_State *L, lua_INetChannelInfo *netchannel);



LUALIB_API lua_INetChannelInfo *(luaL_checknetchannel) (lua_State *L, int narg);


#endif // LINETCHANNELINFO_H