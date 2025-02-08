//========== Copyleft © 2011, Team Sandbox, Some rights reserved. ===========//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#ifndef LUACACHEFILE_H
#define LUACACHEFILE_H
#ifdef _WIN32
#pragma once
#endif

#include "zip_utils.h"

// Embedded pack/pak file
IZip				*luasrc_GetLcfFile( void );
void				luasrc_AddFileToLcf( const char *pRelativeName, const char *fullpath );
#ifdef CLIENT_DLL
void				luasrc_ExtractLcf( void );
#endif

extern void lcf_recursivedeletefile( const char *current );
extern void lcf_open (lua_State *L);
extern void lcf_close (lua_State *L);

#ifndef CLIENT_DLL
extern void lcf_preparecachefile( void );
#endif

#endif // LUACACHEFILE_H
