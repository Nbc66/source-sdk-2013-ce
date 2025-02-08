//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef ICLASSMAP_H
#define ICLASSMAP_H
#ifdef _WIN32
#pragma once
#endif

class C_BaseEntity;
typedef C_BaseEntity* (*DISPATCHFUNCTION)( void );

abstract_class IClassMap
{
public:
	virtual					~IClassMap() {}
	#ifdef LUA_SDK
	virtual void			Add(const char* mapname, const char* classname, int size, DISPATCHFUNCTION factory = 0, bool scripted = false) = 0;
	virtual void			RemoveAllScripted(void) = 0;
#else
	virtual void			Add( const char *mapname, const char *classname, int size, DISPATCHFUNCTION factory = 0 ) = 0;
#endif
	virtual char const		*Lookup( const char *classname ) = 0;
#ifdef LUA_SDK
	virtual DISPATCHFUNCTION FindFactory(const char* classname) = 0;
#endif
	virtual C_BaseEntity	*CreateEntity( const char *mapname ) = 0;
	virtual int				GetClassSize( const char *classname ) = 0;
};

extern IClassMap& GetClassMap();


#endif // ICLASSMAP_H
