//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Public interfaces to vphysics DLL
//
// $NoKeywords: $
//=============================================================================//

#ifndef LVPHYSICS_INTERFACE_H
#define LVPHYSICS_INTERFACE_H
#ifdef _WIN32
#pragma once
#endif

#pragma warning (disable : 4238)


/* type for IPhysicsObject functions */
typedef IPhysicsObject lua_IPhysicsObject;
typedef surfacephysicsparams_t lua_surfacephysicsparams_t;
typedef surfaceaudioparams_t lua_surfaceaudioparams_t;
typedef surfacesoundnames_t lua_surfacesoundnames_t;
typedef surfacesoundhandles_t lua_surfacesoundhandles_t;
typedef surfacegameprops_t lua_surfacegameprops_t;
typedef surfacedata_t lua_surfacedata_t;
typedef IPhysicsSurfaceProps lua_IPhysicsSurfaceProps;



/*
** access functions (stack -> C)
*/

LUA_API lua_IPhysicsObject             *(lua_tophysicsobject) (lua_State *L, int idx);
LUA_API lua_surfacephysicsparams_t     (lua_tosurfacephysicsparams) (lua_State *L, int idx);
LUA_API lua_surfaceaudioparams_t       (lua_tosurfaceaudioparams) (lua_State *L, int idx);
LUA_API lua_surfacesoundnames_t        (lua_tosurfacesoundnames) (lua_State *L, int idx);
LUA_API lua_surfacesoundhandles_t      (lua_tosurfacesoundhandles) (lua_State *L, int idx);
LUA_API lua_surfacegameprops_t         (lua_tosurfacegameprops) (lua_State *L, int idx);
LUA_API lua_surfacedata_t              (lua_tosurfacedata) (lua_State *L, int idx);
LUA_API lua_IPhysicsSurfaceProps       *(lua_tophysicssurfaceprops) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushphysicsobject) (lua_State *L, lua_IPhysicsObject *pPhysicsObject);
LUA_API void  (lua_pushsurfacephysicsparams) (lua_State *L, lua_surfacephysicsparams_t *pphysics);
LUA_API void  (lua_pushsurfaceaudioparams) (lua_State *L, lua_surfaceaudioparams_t *paudio);
LUA_API void  (lua_pushsurfacesoundnames) (lua_State *L, lua_surfacesoundnames_t *psounds);
LUA_API void  (lua_pushsurfacesoundhandles) (lua_State *L, lua_surfacesoundhandles_t *psoundhandles);
LUA_API void  (lua_pushsurfacegameprops) (lua_State *L, lua_surfacegameprops_t *pgame);
LUA_API void  (lua_pushsurfacedata) (lua_State *L, lua_surfacedata_t *psurface);
LUA_API void  (lua_pushphysicssurfaceprops) (lua_State *L, lua_IPhysicsSurfaceProps *pProps);



LUALIB_API lua_IPhysicsObject *(luaL_checkphysicsobject) (lua_State *L, int narg);
LUALIB_API lua_IPhysicsSurfaceProps *(luaL_checkphysicssurfaceprops) (lua_State *L, int narg);


#endif // LVPHYSICS_INTERFACE_H
