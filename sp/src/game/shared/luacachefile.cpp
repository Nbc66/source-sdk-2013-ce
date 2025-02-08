//========== Copyleft © 2011, Team Sandbox, Some rights reserved. ===========//
//
// Purpose: Handles the creation of Lua Cache Files for multiplayer.
//
//===========================================================================//

#include "cbase.h"
#include "filesystem.h"
#ifdef WIN32
#include "winlite.h"
#endif
#include "zip/XUnzip.h"
#include "utldict.h"
#include "luamanager.h"
#include "luacachefile.h"

#ifdef GAME_DLL
#include "networkstringtable_gamedll.h"
#else
#include "networkstringtable_clientdll.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static IZip *s_lcfFile = 0;

//-----------------------------------------------------------------------------
// Purpose: // Get a lcffile instance
// Output : IZip*
//-----------------------------------------------------------------------------
LUA_API IZip* luasrc_GetLcfFile( void )
{
	if ( !s_lcfFile )
	{
		s_lcfFile = IZip::CreateZip();
	}
	return s_lcfFile;
}

//-----------------------------------------------------------------------------
// Purpose: Add file from disk to .lcf
// Input  : *relativename - 
//			*fullpath - 
//-----------------------------------------------------------------------------
LUA_API void luasrc_AddFileToLcf( const char *relativename, const char *fullpath )
{
	s_lcfFile->AddFileToZip( relativename, fullpath );
}

#ifdef CLIENT_DLL

LUA_API void luasrc_ExtractLcf ()
{
	INetworkStringTable *downloadables = networkstringtable->FindTable( "downloadables" );
	const char *pFilename = NULL;
	for ( int i=0; i<downloadables->GetNumStrings(); i++ )
	{
		pFilename = downloadables->GetString( i );
		char ext[ 10 ];
		Q_ExtractFileExtension( pFilename, ext, sizeof( ext ) );

		if ( !Q_stricmp( ext, "lcf" ) )
		{
			char current[ 512 ] = { 0 };
			char cachePath[MAX_PATH];
			bool bGetCurrentDirectory = V_GetCurrentDirectory( current, sizeof( current ) );
			if ( bGetCurrentDirectory )
			{
#ifdef CLIENT_DLL
				const char *gamePath = engine->GetGameDirectory();
#else
				char gamePath[ 256 ];
				engine->GetGameDir( gamePath, 256 );
#endif
				Q_strncpy( cachePath, gamePath, sizeof( cachePath ) );
				Q_strncat( cachePath, "\\" LUA_PATH_CACHE, sizeof( cachePath ), COPY_ALL_CHARACTERS );
				V_SetCurrentDirectory( cachePath );
			}

			char fullpath[MAX_PATH];
			filesystem->RelativePathToFullPath( pFilename, "MOD", fullpath, sizeof( fullpath ) );
			HZIP hz = OpenZip( fullpath, 0, ZIP_FILENAME );
			ZIPENTRY ze;
			GetZipItem( hz, -1, &ze );
			int numitems = ze.index;
			for ( int i = 0; i < numitems; i++ )
			{
				GetZipItem( hz, i, &ze );
				// forget directories, we create hierarchies from file names
				if ((ze.attr & FILE_ATTRIBUTE_DIRECTORY) != 1)
				{
					char fullpath[MAX_PATH];
					char path[MAX_PATH];
					Q_snprintf( path, sizeof( path ), LUA_PATH_CACHE"\\%s", ze.name );
					Q_StripFilename( path );
					filesystem->CreateDirHierarchy( path, "MOD" );
					Q_snprintf( fullpath, sizeof( fullpath ), "%s%s", cachePath, path + Q_strlen( LUA_PATH_CACHE ) );
					// DevMsg( "LCF: setting current directory to %s...\n", fullpath );
					V_SetCurrentDirectory( fullpath );
					// DevMsg( "LCF: unpacking %s...\n", ze.name );
					UnzipItem( hz, i, (void *)V_UnqualifiedFileName( ze.name ), 0, ZIP_FILENAME );
				}
			}
			CloseZip( hz );

			if ( bGetCurrentDirectory )
				V_SetCurrentDirectory( current );

			break;
		}
	}
}

#else

static CUtlDict< char *, int > m_LcfDatabase;

static const char *UTIL_StripAddonName( char *addonName )
{
	char *pc = addonName;
	int i = 0;
	while ( *pc )
	{
		char c = *pc;

		if ( c == '/' || c == '\\' )
		{
			*pc = 0;
			++i;
			return addonName + i;
		}
		else
		{
			*pc = 0;
			++i;
		}
		++pc;
	}
	Assert( false );
	return addonName + i;
}

static int luasrc_sendfile (lua_State *L) {
  // Can only send files in multiplayer!!!
  if ( gpGlobals->maxClients == 1 )
  {
  	return 0;
  }
  lua_Debug ar1;
  lua_getstack(L, 1, &ar1);
  lua_getinfo(L, "f", &ar1);
  lua_Debug ar2;
  lua_getinfo(L, ">S", &ar2);
  int iLength = Q_strlen( ar2.source );
  char source[MAX_PATH];
  Q_StrRight( ar2.source, iLength-1, source, sizeof( source ) );
  Q_StripFilename( source );
  char filename[MAX_PATH];
  Q_snprintf( filename, sizeof( filename ), "%s\\%s", source, luaL_checkstring(L, 1) );
  char relativePath[MAX_PATH];
  if ( filesystem->FullPathToRelativePathEx( filename, "MOD", relativePath, MAX_PATH ) )
  {
	const char *zipPath = NULL;
	if ( Q_strnicmp( relativePath, "addons/", 7 ) )
	{
		char *substring = strstr( relativePath, "addons\\" );
		if ( substring )
		{
			*substring = 0;
			zipPath = UTIL_StripAddonName( relativePath + 7 );
		}
	}
	char gamePath[ 256 ];
	engine->GetGameDir( gamePath, 256 );
	// DevMsg( "LCF: adding %s to the Lua cache file...\n", zipPath );
	m_LcfDatabase.Insert( zipPath, strdup( filename ) );
  }
  else
  {
	DevMsg( "LCF: couldn't find relative path to %s!\n", filename );
  }
  return 0;
}


static const luaL_Reg lcf_funcs[] = {
  {"sendfile", luasrc_sendfile},
  {NULL, NULL}
};


#endif

extern void lcf_open (lua_State *L) {
#ifndef CLIENT_DLL
  /* open lib into global table */
  luaL_register(L, "_G", lcf_funcs);
  lua_pop(L, 1);
#else
  // force create this directory incase it doesn't exist
  filesystem->CreateDirHierarchy( LUA_PATH_CACHE, "MOD");
#endif
}

extern void lcf_recursivedeletefile( const char *current ) {
	FileFindHandle_t fh;

	char path[ 512 ];
	if ( current[ 0 ] )
	{
        Q_snprintf( path, sizeof( path ), "%s/*.*", current );
	}
	else
	{
		Q_snprintf( path, sizeof( path ), "*.*" );
	}

	Q_FixSlashes( path );

	char const *fn = g_pFullFileSystem->FindFirstEx( path, "MOD", &fh );
	while ( fn )
	{
		if ( fn[0] != '.' )
		{
			if ( g_pFullFileSystem->FindIsDirectory( fh ) )
			{
				char nextdir[ 512 ];
				if ( current[ 0 ] )
				{
					Q_snprintf( nextdir, sizeof( nextdir ), "%s/%s", current, fn );
				}
				else
				{
					Q_snprintf( nextdir, sizeof( nextdir ), "%s", fn );
				}

				lcf_recursivedeletefile( nextdir );
			}
			else
			{
				char relative[ 512 ];
				if ( current[ 0 ] )
				{
					Q_snprintf( relative, sizeof( relative ), "%s/%s", current, fn );
				}
				else
				{
					Q_snprintf( relative, sizeof( relative ), "%s", fn );
				}
				DevMsg( "Deleting '%s/%s'...\n", current, fn );

				Q_FixSlashes( relative );
				g_pFullFileSystem->SetFileWritable( relative, true, "MOD" );
				g_pFullFileSystem->RemoveFile( relative, "MOD" );
			}
		}

		fn = g_pFullFileSystem->FindNext( fh );
	}
	g_pFullFileSystem->FindClose( fh );
}

extern void lcf_close (lua_State *L) {
#ifndef CLIENT_DLL
	int c = m_LcfDatabase.Count(); 
	for ( int i = 0; i < c; ++i )
	{
		delete m_LcfDatabase[ i ];
	}
	m_LcfDatabase.RemoveAll();
#else
	lcf_recursivedeletefile( LUA_PATH_CACHE );
#endif
}

#ifndef CLIENT_DLL

extern void lcf_preparecachefile (void) {
	int c = m_LcfDatabase.Count();
	if ( c > 0 )
	{
		DevMsg( "Preparing Lua cache file...\n" );
	}
	else
	{
		return;
	}
	IZip *pZip = luasrc_GetLcfFile();
	for ( int i = 0; i < c; i++ )
	{
		pZip->AddFileToZip( m_LcfDatabase.GetElementName( i ), m_LcfDatabase[ i ] ); 
	}
	// force create this directory incase it doesn't exist
	filesystem->CreateDirHierarchy( "cache", "MOD");
	FileHandle_t fh = g_pFullFileSystem->Open( "cache\\cache_temp.lcf", "wb", "MOD" );
	if ( FILESYSTEM_INVALID_HANDLE != fh )
	{
		pZip->SaveToDisk( fh );
	}
	g_pFullFileSystem->Close( fh );

	byte *buffer;

	fh = g_pFullFileSystem->Open( "cache\\cache_temp.lcf", "rb", "MOD" );

	int size = g_pFullFileSystem->Size( fh );
	buffer = new byte[ size + 1 ];
	if ( !buffer )
	{
		Warning( "lcf_preparecachefile:  Couldn't allocate buffer of size %i\n", size + 1 );
		g_pFullFileSystem->Close( fh );
		return;
	}
	g_pFullFileSystem->Read( buffer, size, fh );
	g_pFullFileSystem->Close( fh );

	// Ensure null terminator
	// buffer[ size ] =0;

	CRC32_t crc;

	CRC32_Init( &crc );
	// CRC32_ProcessBuffer( &crc, buffer, sizeof( buffer ) );
	CRC32_ProcessBuffer( &crc, buffer, size );
	CRC32_Final( &crc );

	delete[] buffer;

	char filename[ MAX_PATH ];
	char hexname[ 16 ];
	Q_binarytohex( (const byte *)&crc, sizeof( crc ), hexname, sizeof( hexname ) );
	Q_snprintf( filename, sizeof( filename ), "cache\\%s.lcf", hexname );
	if ( g_pFullFileSystem->FileExists( filename, "MOD" ) )
	{
		g_pFullFileSystem->RemoveFile( "cache\\cache_temp.lcf", "MOD" );
	}
	else
	{
		g_pFullFileSystem->RenameFile( "cache\\cache_temp.lcf", filename, "MOD" );
	}

	INetworkStringTable *downloadables = networkstringtable->FindTable( "downloadables" );
	downloadables->AddString( true, filename, -1 );
	IZip::ReleaseZip( pZip );
	s_lcfFile = 0;
}

CON_COMMAND(dumpluacachefile, "Dump the contents of the Lua cache file database to the console.")
{
	int c = m_LcfDatabase.Count();
	for ( int i = 0; i < c; i++ )
	{
		Msg( "%s: %s\n", m_LcfDatabase.GetElementName( i ), m_LcfDatabase[ i ] );
	}
}

#endif
