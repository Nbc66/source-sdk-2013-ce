//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#define lfilesystem_cpp

#include "cbase.h"
#include "filesystem.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "lfilesystem.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"



/*
** access functions (stack -> C)
*/


LUA_API lua_FileHandle_t &lua_tofilehandle (lua_State *L, int idx) {
  lua_FileHandle_t *phFile = (lua_FileHandle_t *)luaL_checkudata(L, idx, "FileHandle_t");
  return *phFile;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushfilehandle (lua_State *L, lua_FileHandle_t hFile) {
  lua_FileHandle_t *phFile = (lua_FileHandle_t *)lua_newuserdata(L, sizeof(lua_FileHandle_t));
  *phFile = hFile;
  luaL_getmetatable(L, "FileHandle_t");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_FileHandle_t &luaL_checkfilehandle (lua_State *L, int narg) {
  lua_FileHandle_t *d = (lua_FileHandle_t *)luaL_checkudata(L, narg, "FileHandle_t");
  if (*d == FILESYSTEM_INVALID_HANDLE)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "FileHandle_t expected, got FILESYSTEM_INVALID_HANDLE");
  return *d;
}


static int filesystem_AddPackFile (lua_State *L) {
  lua_pushboolean(L, filesystem->AddPackFile(luaL_checkstring(L, 1), luaL_checkstring(L, 2)));
  return 1;
}

static int filesystem_AddSearchPath (lua_State *L) {
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
  filesystem->AddSearchPath(luaL_checkstring(L, 1), luaL_checkstring(L, 2), (SearchPathAdd_t)luaL_optint(L, 3, PATH_ADD_TO_TAIL));
  if ( bGetCurrentDirectory )
	  V_SetCurrentDirectory( fullpath );
  return 0;
}

static int filesystem_BeginMapAccess (lua_State *L) {
  filesystem->BeginMapAccess();
  return 0;
}

static int filesystem_CancelWaitForResources (lua_State *L) {
  filesystem->CancelWaitForResources(luaL_checkint(L, 1));
  return 0;
}

static int filesystem_Close (lua_State *L) {
  filesystem->Close(luaL_checkfilehandle(L, 1));
  // Andrew; this isn't standard behavior or usage, but we do this for the sake
  // of things being safe in Lua
  luaL_checkfilehandle(L, 1) = FILESYSTEM_INVALID_HANDLE;
  return 0;
}

static int filesystem_CreateDirHierarchy (lua_State *L) {
  filesystem->CreateDirHierarchy(luaL_checkstring(L, 1), luaL_optstring(L, 2, 0));
  return 0;
}

static int filesystem_DiscardPreloadData (lua_State *L) {
  filesystem->DiscardPreloadData();
  return 0;
}

static int filesystem_Disconnect (lua_State *L) {
  filesystem->Disconnect();
  return 0;
}

/*static int filesystem_EnableWhitelistFileTracking(lua_State* L) {
  filesystem->EnableWhitelistFileTracking(luaL_checkboolean(L, 1));
  return 0;
}*/

static int filesystem_EndMapAccess (lua_State *L) {
  filesystem->EndMapAccess();
  return 0;
}

static int filesystem_EndOfFile (lua_State *L) {
  lua_pushboolean(L, filesystem->EndOfFile(luaL_checkfilehandle(L, 1)));
  return 1;
}

static int filesystem_FileExists (lua_State *L) {
  lua_pushboolean(L, filesystem->FileExists(luaL_checkstring(L, 1), luaL_optstring(L, 2, 0)));
  return 1;
}

static int filesystem_Flush (lua_State *L) {
  filesystem->Flush(luaL_checkfilehandle(L, 1));
  return 0;
}

static int filesystem_GetDVDMode (lua_State *L) {
  lua_pushinteger(L, filesystem->GetDVDMode());
  return 1;
}

static int filesystem_GetLocalCopy (lua_State *L) {
  filesystem->GetLocalCopy(luaL_checkstring(L, 1));
  return 0;
}

static int filesystem_GetWhitelistSpewFlags (lua_State *L) {
  lua_pushinteger(L, filesystem->GetWhitelistSpewFlags());
  return 1;
}

static int filesystem_HintResourceNeed (lua_State *L) {
  lua_pushinteger(L, filesystem->HintResourceNeed(luaL_checkstring(L, 1), luaL_checkint(L, 2)));
  return 1;
}

static int filesystem_IsDirectory (lua_State *L) {
  lua_pushboolean(L, filesystem->IsDirectory(luaL_checkstring(L, 1), luaL_optstring(L, 2, 0)));
  return 1;
}

static int filesystem_IsFileImmediatelyAvailable (lua_State *L) {
  lua_pushboolean(L, filesystem->IsFileImmediatelyAvailable(luaL_checkstring(L, 1)));
  return 1;
}

static int filesystem_IsFileWritable (lua_State *L) {
  lua_pushboolean(L, filesystem->IsFileWritable(luaL_checkstring(L, 1), luaL_optstring(L, 2, 0)));
  return 1;
}

static int filesystem_IsOk (lua_State *L) {
  lua_pushboolean(L, filesystem->IsOk(luaL_checkfilehandle(L, 1)));
  return 1;
}

static int filesystem_IsSteam (lua_State *L) {
  lua_pushboolean(L, filesystem->IsSteam());
  return 1;
}

static int filesystem_LoadCompiledKeyValues (lua_State *L) {
  filesystem->LoadCompiledKeyValues((IFileSystem::KeyValuesPreloadType_t)luaL_checkint(L, 1), luaL_checkstring(L, 2));
  return 0;
}

static int filesystem_MarkAllCRCsUnverified (lua_State *L) {
  filesystem->MarkAllCRCsUnverified();
  return 0;
}

static int filesystem_MarkPathIDByRequestOnly (lua_State *L) {
  filesystem->MarkPathIDByRequestOnly(luaL_checkstring(L, 1), luaL_checkboolean(L, 2));
  return 0;
}

static int filesystem_MountSteamContent (lua_State *L) {
  lua_pushinteger(L, filesystem->MountSteamContent(luaL_optint(L, 1, -1)));
  return 1;
}

static int filesystem_Open (lua_State *L) {
  lua_pushfilehandle(L, filesystem->Open(luaL_checkstring(L, 1), luaL_checkstring(L, 2), luaL_optstring(L, 3, 0)));
  return 1;
}

static int filesystem_Precache (lua_State *L) {
  lua_pushboolean(L, filesystem->Precache(luaL_checkstring(L, 1), luaL_optstring(L, 2, 0)));
  return 1;
}

static int filesystem_PrintOpenedFiles (lua_State *L) {
  filesystem->PrintOpenedFiles();
  return 0;
}

static int filesystem_PrintSearchPaths (lua_State *L) {
  filesystem->PrintSearchPaths();
  return 0;
}

static int filesystem_Read (lua_State *L) {
  byte *buffer;

  FileHandle_t file;
  file = luaL_checkfilehandle(L, 2);

  int size = luaL_checkint(L, 1);
  buffer = new byte[ size + 1 ];
  if ( !buffer )
  {
  	Warning( "filesystem.Read:  Couldn't allocate buffer of size %i for file\n", size + 1 );
  	lua_pushinteger(L, -1);
  	lua_pushstring(L, NULL);
  	return 2;
  }
  int bytesRead = filesystem->Read( buffer, size, file );

  if ( bytesRead )
  {
	  // Ensure null terminator
	  buffer[ bytesRead ] =0;
  }
  else
  {
	  *buffer = 0;
  }

  lua_pushinteger(L, size);
  lua_pushstring(L, (const char *)buffer);
  delete buffer;

  return 2;
}

static int filesystem_RemoveAllSearchPaths (lua_State *L) {
  filesystem->RemoveAllSearchPaths();
  return 0;
}

static int filesystem_RemoveFile (lua_State *L) {
  filesystem->RemoveFile(luaL_checkstring(L, 1), luaL_optstring(L, 2, 0));
  return 0;
}

static int filesystem_RemoveSearchPath (lua_State *L) {
  lua_pushboolean(L, filesystem->RemoveSearchPath(luaL_checkstring(L, 1), luaL_optstring(L, 2, 0)));
  return 1;
}

static int filesystem_RemoveSearchPaths (lua_State *L) {
  filesystem->RemoveSearchPaths(luaL_checkstring(L, 1));
  return 0;
}

static int filesystem_RenameFile (lua_State *L) {
  lua_pushboolean(L, filesystem->RenameFile(luaL_checkstring(L, 1), luaL_checkstring(L, 2), luaL_optstring(L, 3, 0)));
  return 1;
}

static int filesystem_SetFileWritable (lua_State *L) {
  lua_pushboolean(L, filesystem->SetFileWritable(luaL_checkstring(L, 1), luaL_checkboolean(L, 2), luaL_optstring(L, 3, 0)));
  return 1;
}

static int filesystem_SetupPreloadData (lua_State *L) {
  filesystem->SetupPreloadData();
  return 0;
}

static int filesystem_SetWarningLevel (lua_State *L) {
  filesystem->SetWarningLevel((FileWarningLevel_t)luaL_checkint(L, 1));
  return 0;
}

static int filesystem_SetWhitelistSpewFlags (lua_State *L) {
  filesystem->SetWhitelistSpewFlags(luaL_checkint(L, 1));
  return 0;
}

static int filesystem_Shutdown (lua_State *L) {
  filesystem->Shutdown();
  return 0;
}

static int filesystem_Size (lua_State *L) {
  switch(lua_type(L, 1)) {
    case LUA_TSTRING:
      lua_pushinteger(L, filesystem->Size(luaL_checkstring(L, 1), luaL_optstring(L, 2, 0)));
      break;
    case LUA_TUSERDATA:
    default:
      lua_pushinteger(L, filesystem->Size(luaL_checkfilehandle(L, 1)));
      break;
  }
  return 1;
}

static int filesystem_UnzipFile (lua_State *L) {
  lua_pushboolean(L, filesystem->UnzipFile(luaL_checkstring(L, 1), luaL_checkstring(L, 2), luaL_checkstring(L, 3)));
  return 1;
}

static int filesystem_WaitForResources (lua_State *L) {
  lua_pushinteger(L, filesystem->WaitForResources(luaL_checkstring(L, 1)));
  return 1;
}

static int filesystem_Write (lua_State *L) {
  size_t l;
  const char *pInput = luaL_checklstring(L, 1, &l);
  lua_pushinteger(L, filesystem->Write(pInput, l, luaL_checkfilehandle(L, 2)));
  return 1;
}


static const luaL_Reg filesystemlib[] = {
  {"AddPackFile",   filesystem_AddPackFile},
  {"AddSearchPath",   filesystem_AddSearchPath},
  {"BeginMapAccess",   filesystem_BeginMapAccess},
  {"CancelWaitForResources",   filesystem_CancelWaitForResources},
  {"Close",   filesystem_Close},
  {"CreateDirHierarchy",   filesystem_CreateDirHierarchy},
  {"DiscardPreloadData",   filesystem_DiscardPreloadData},
  {"Disconnect",   filesystem_Disconnect},
  //{"EnableWhitelistFileTracking",   filesystem_EnableWhitelistFileTracking},
  {"EndMapAccess",   filesystem_EndMapAccess},
  {"EndOfFile",   filesystem_EndOfFile},
  {"FileExists",   filesystem_FileExists},
  {"Flush",   filesystem_Flush},
  {"GetDVDMode",   filesystem_GetDVDMode},
  {"GetLocalCopy",   filesystem_GetLocalCopy},
  {"GetWhitelistSpewFlags",   filesystem_GetWhitelistSpewFlags},
  {"HintResourceNeed",   filesystem_HintResourceNeed},
  {"IsDirectory",   filesystem_IsDirectory},
  {"IsFileImmediatelyAvailable",   filesystem_IsFileImmediatelyAvailable},
  {"IsFileWritable",   filesystem_IsFileWritable},
  {"IsOk",   filesystem_IsOk},
  {"IsSteam",   filesystem_IsSteam},
  {"LoadCompiledKeyValues",   filesystem_LoadCompiledKeyValues},
  {"MarkAllCRCsUnverified",   filesystem_MarkAllCRCsUnverified},
  {"MarkPathIDByRequestOnly",   filesystem_MarkPathIDByRequestOnly},
  {"MountSteamContent",   filesystem_MountSteamContent},
  {"Open",   filesystem_Open},
  {"Precache",   filesystem_Precache},
  {"PrintOpenedFiles",   filesystem_PrintOpenedFiles},
  {"PrintSearchPaths",   filesystem_PrintSearchPaths},
  {"Read",   filesystem_Read},
  {"RemoveAllSearchPaths",   filesystem_RemoveAllSearchPaths},
  {"RemoveFile",   filesystem_RemoveFile},
  {"RemoveSearchPath",   filesystem_RemoveSearchPath},
  {"RemoveSearchPaths",   filesystem_RemoveSearchPaths},
  {"RenameFile",   filesystem_RenameFile},
  {"SetFileWritable",   filesystem_SetFileWritable},
  {"SetupPreloadData",   filesystem_SetupPreloadData},
  {"SetWarningLevel",   filesystem_SetWarningLevel},
  {"SetWhitelistSpewFlags",   filesystem_SetWhitelistSpewFlags},
  {"Size",   filesystem_Size},
  {"UnzipFile",   filesystem_UnzipFile},
  {"WaitForResources",   filesystem_WaitForResources},
  {"Write",   filesystem_Write},
  {NULL, NULL}
};


static int FileHandle_t___gc (lua_State *L) {
  FileHandle_t hFile = lua_tofilehandle(L, 1);
  if (hFile != FILESYSTEM_INVALID_HANDLE)
    filesystem->Close(hFile);
  return 0;
}

static int FileHandle_t___tostring (lua_State *L) {
  FileHandle_t hFile = lua_tofilehandle(L, 1);
  if (hFile == FILESYSTEM_INVALID_HANDLE)
    lua_pushstring(L, "FILESYSTEM_INVALID_HANDLE");
  else
    lua_pushfstring(L, "FileHandle_t: %p", lua_tofilehandle(L, 1));
  return 1;
}


static const luaL_Reg FileHandle_tmeta[] = {
  {"__gc", FileHandle_t___gc},
  {"__tostring", FileHandle_t___tostring},
  {NULL, NULL}
};


/*
** Open filesystem library
*/
LUALIB_API int luaopen_filesystem (lua_State *L) {
  luaL_newmetatable(L, "FileHandle_t");
  luaL_register(L, NULL, FileHandle_tmeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "filehandle");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "filehandle" */
  lua_pop(L, 1);
  lua_pushfilehandle(L, FILESYSTEM_INVALID_HANDLE);
  lua_setglobal(L, "FILESYSTEM_INVALID_HANDLE");
  luaL_register(L, LUA_FILESYSTEMLIBNAME, filesystemlib);
  return 1;
}

