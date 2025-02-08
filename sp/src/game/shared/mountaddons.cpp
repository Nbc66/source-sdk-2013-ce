//========== Copyleft © 2011, Team Sandbox, Some rights reserved. ===========//
//
// Purpose:
//
//===========================================================================//

#include "cbase.h"
#include "filesystem.h"
#include "luamanager.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

void MountAddons()
{
	// Andrew; mount the Lua cache directory first. We consider this a temporary
	// addon used across servers
	char fullpath[ 512 ] = { 0 };
	bool bGetCurrentDirectory = V_GetCurrentDirectory( fullpath, sizeof( fullpath ) );
	if ( bGetCurrentDirectory )
	{
#ifdef CLIENT_DLL
		const char *gamePath = engine->GetGameDirectory();
#else
		char gamePath[ 256 ];
		engine->GetGameDir( gamePath, 256 );
#endif
		V_SetCurrentDirectory( gamePath );
	}
	filesystem->AddSearchPath( LUA_PATH_CACHE, "MOD", PATH_ADD_TO_TAIL );
	if ( bGetCurrentDirectory )
		V_SetCurrentDirectory( fullpath );

	FileFindHandle_t fh;

	char relativepath[ MAX_PATH ] = { 0 };
	char addonName[ 255 ] = { 0 };

	char const *fn = g_pFullFileSystem->FindFirstEx( LUA_PATH_ADDONS "\\*", "MOD", &fh );
	while ( fn )
	{
		Q_strcpy( addonName, fn );
		if ( fn[0] != '.' )
		{
			if ( g_pFullFileSystem->FindIsDirectory( fh ) )
			{
#ifdef GAME_DLL
				Msg( "Mounting addon \"%s\"...\n", addonName );
#endif

				Q_snprintf( relativepath, sizeof( relativepath ), LUA_PATH_ADDONS "\\%s", addonName );
				char fullpath[ 512 ] = { 0 };
				bool bGetCurrentDirectory = V_GetCurrentDirectory( fullpath, sizeof( fullpath ) );
				if ( bGetCurrentDirectory )
				{
#ifdef CLIENT_DLL
					const char *gamePath = engine->GetGameDirectory();
#else
					char gamePath[ 256 ];
					engine->GetGameDir( gamePath, 256 );
#endif
					V_SetCurrentDirectory( gamePath );
				}
				filesystem->AddSearchPath( relativepath, "MOD", PATH_ADD_TO_TAIL );
				if ( bGetCurrentDirectory )
					V_SetCurrentDirectory( fullpath );
			}
		}

		fn = g_pFullFileSystem->FindNext( fh );
	}
	g_pFullFileSystem->FindClose( fh );
}
