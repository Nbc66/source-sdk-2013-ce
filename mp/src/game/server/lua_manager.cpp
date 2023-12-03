///////////// Copyright © 2009 LodleNet. All rights reserved. /////////////
//
//   Project     : Server
//   File        : ge_luamanager.cpp
//   Description :
//      Updated for LUA 5.2
//
//   Created On: 3/5/2009 4:58:54 PM
//   Created By:  <mailto:admin@lodle.net>
//   Updated By:  <mailto:matt.shirleys@gmail.com>
////////////////////////////////////////////////////////////////////////////

#include "cbase.h"
#include "lua_manager.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


void RegisterLUAFuncs(lua_State* L);
void RegisterLUAGlobals(lua_State* L);

CGELUAManager gLuaMng;
CGELUAManager* GELua()
{
	return &gLuaMng;
}

void RegPublicFunctions(lua_State* L)
{
	//add global lua functions here
	//RegisterLUAFuncs(L);
}

void RegPublicGlobals(lua_State* L)
{
	//add global lua defines here
	//RegisterLUAGlobals(L);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////

LuaHandle* g_NLuaHandle = NULL;

LuaHandle* GetNLuaHandle()
{
	return g_NLuaHandle;
}
LuaHandle::LuaHandle()
{
	pL = NULL;
}

LuaHandle::~LuaHandle()
{
	GELua()->DeRegisterLuaHandle(this);
}

void LuaHandle::InitDll()
{
	//Create an instance; Load the core libs.
	pL = luaL_newstate();
	luaopen_base(pL);		/* opens the basic library */
	luaopen_table(pL);		/* opens the table library */
	luaopen_string(pL);		/* opens the string lib. */
	luaopen_math(pL);		/* opens the math lib. */
#ifdef _DEBUG
	luaopen_debug(pL);
#endif

	RegFunctions();
	RegGlobals();

	RegPublicFunctions(pL);
	RegPublicGlobals(pL);

	Init();
}

void LuaHandle::ShutdownDll()
{
	Shutdown();

	lua_close(pL);
}

void LuaHandle::Register()
{
	GELua()->RegisterLuaHandle(this);
}

////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////

CGELUAManager::CGELUAManager()
{
	m_bInit = false;
}

CGELUAManager::~CGELUAManager()
{

}

void CGELUAManager::InitDll()
{
	// Register our LUA Functions and Globals so we can call them
	// from .lua scripts
	for (size_t x = 0; x < m_vHandles.size(); x++)
	{
		if (m_vHandles[x])
			continue;

		m_vHandles[x]->InitDll();
	}

	m_bInit = true;
	//ZMSLuaGamePlay *p = GetGP();
	//p->m_bLuaLoaded = true;


}

void CGELUAManager::ShutdownDll()
{
	for (size_t x = 0; x < m_vHandles.size(); x++)
	{
		if (m_vHandles[x])
			continue;

		m_vHandles[x]->Shutdown();
	}

	m_vHandles.clear();
}


void CGELUAManager::DeRegisterLuaHandle(LuaHandle* handle)
{
	if (!handle)
		return;

	for (size_t x = 0; x < m_vHandles.size(); x++)
	{
		if (m_vHandles[x] == handle)
			m_vHandles.erase(m_vHandles.begin() + x);
	}
}

void CGELUAManager::RegisterLuaHandle(LuaHandle* handle)
{
	if (!handle)
		return;

	for (size_t x = 0; x < m_vHandles.size(); x++)
	{
		if (m_vHandles[x] == handle)
			return;
	}

	m_vHandles.push_back(handle);

	//if we are late to the game
	if (m_bInit)
		handle->InitDll();
}
void RegisterLUAFuncs(lua_State* L)
{

}
void RegisterLUAGlobals(lua_State* L)
{

}
