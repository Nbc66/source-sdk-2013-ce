//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "KeyValues.h"
#include "filesystem.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "LKeyValues.h"
#include "lColor.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

/*
** access functions (stack -> C)
*/


LUA_API lua_KeyValues *lua_tokeyvalues (lua_State *L, int idx) {
  lua_KeyValues *kv = *(lua_KeyValues **)lua_touserdata(L, idx);
  return kv;
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushkeyvalues (lua_State *L, lua_KeyValues *pKV) {
  lua_KeyValues **ppKV = (lua_KeyValues **)lua_newuserdata(L, sizeof(lua_KeyValues *));
  *ppKV = pKV;
  luaL_getmetatable(L, "KeyValues");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_KeyValues *luaL_checkkeyvalues (lua_State *L, int narg) {
  lua_KeyValues **d = (lua_KeyValues **)luaL_checkudata(L, narg, "KeyValues");
  if (*d == 0)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "KeyValues expected, got NULL keyvalues");
  return *d;
}


LUALIB_API lua_KeyValues *luaL_optkeyvalues (lua_State *L, int narg,
                                                           KeyValues *def) {
  return luaL_opt(L, luaL_checkkeyvalues, narg, def);
}


static int KeyValues_AddSubKey (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->AddSubKey(luaL_checkkeyvalues(L, 2));
  return 0;
}

static int KeyValues_ChainKeyValue (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->ChainKeyValue(luaL_checkkeyvalues(L, 2));
  return 0;
}

static int KeyValues_Clear (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->Clear();
  return 0;
}

static int KeyValues_CopySubkeys (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->CopySubkeys(luaL_checkkeyvalues(L, 2));
  return 0;
}

static int KeyValues_CreateNewKey (lua_State *L) {
  lua_pushkeyvalues(L, luaL_checkkeyvalues(L, 1)->CreateNewKey());
  return 1;
}

static int KeyValues_deleteThis (lua_State *L) {
  KeyValues *pKV = luaL_checkkeyvalues(L, 1);
  pKV->deleteThis();
  // Andrew; this isn't standard behavior or usage, but we do this for the sake
  // of things being safe in Lua
  *(void **)lua_touserdata(L, 1) = (void **)NULL;
  return 0;
}

static int KeyValues_FindKey (lua_State *L) {
  switch(lua_type(L, 2)) {
	case LUA_TNUMBER:
	  lua_pushkeyvalues(L, luaL_checkkeyvalues(L, 1)->FindKey(luaL_checkint(L, 2)));
	  break;
	case LUA_TSTRING:
	default:
	  lua_pushkeyvalues(L, luaL_checkkeyvalues(L, 1)->FindKey(luaL_checkstring(L, 2), luaL_optboolean(L, 3, false)));
	  break;
  }
  return 1;
}

static int KeyValues_GetColor (lua_State *L) {
  switch(lua_type(L, 2)) {
	case LUA_TNUMBER:
	  lua_pushcolor(L, luaL_checkkeyvalues(L, 1)->GetColor(luaL_checkint(L, 2)));
	  break;
	case LUA_TNONE:
	case LUA_TSTRING:
	default:
	  lua_pushcolor(L, luaL_checkkeyvalues(L, 1)->GetColor(luaL_optstring(L, 2, 0)));
	  break;
  }
  return 1;
}

static int KeyValues_GetDataType (lua_State *L) {
  lua_pushinteger(L, luaL_checkkeyvalues(L, 1)->GetDataType(luaL_optstring(L, 2, 0)));
  return 1;
}

static int KeyValues_GetFirstSubKey (lua_State *L) {
  lua_pushkeyvalues(L, luaL_checkkeyvalues(L, 1)->GetFirstSubKey());
  return 1;
}

static int KeyValues_GetFirstTrueSubKey (lua_State *L) {
  lua_pushkeyvalues(L, luaL_checkkeyvalues(L, 1)->GetFirstTrueSubKey());
  return 1;
}

static int KeyValues_GetFirstValue (lua_State *L) {
  lua_pushkeyvalues(L, luaL_checkkeyvalues(L, 1)->GetFirstValue());
  return 1;
}

static int KeyValues_GetFloat (lua_State *L) {
  switch(lua_type(L, 2)) {
	case LUA_TNUMBER:
	  lua_pushnumber(L, luaL_checkkeyvalues(L, 1)->GetFloat(luaL_checkint(L, 2), luaL_optnumber(L, 3, 0.0f)));
	  break;
	case LUA_TNONE:
	case LUA_TSTRING:
	default:
	  lua_pushnumber(L, luaL_checkkeyvalues(L, 1)->GetFloat(luaL_optstring(L, 2, 0), luaL_optnumber(L, 3, 0.0f)));
	  break;
  }
  return 1;
}

static int KeyValues_GetInt (lua_State *L) {
  switch(lua_type(L, 2)) {
	case LUA_TNUMBER:
	  lua_pushinteger(L, luaL_checkkeyvalues(L, 1)->GetInt(luaL_checkint(L, 2), luaL_optint(L, 3, 0)));
	  break;
	case LUA_TNONE:
	case LUA_TSTRING:
	default:
	  lua_pushinteger(L, luaL_checkkeyvalues(L, 1)->GetInt(luaL_optstring(L, 2, 0), luaL_optint(L, 3, 0)));
	  break;
  }
  return 1;
}

static int KeyValues_GetName (lua_State *L) {
  lua_pushstring(L, luaL_checkkeyvalues(L, 1)->GetName());
  return 1;
}

static int KeyValues_GetNameSymbol (lua_State *L) {
  lua_pushinteger(L, luaL_checkkeyvalues(L, 1)->GetNameSymbol());
  return 1;
}

static int KeyValues_GetNextKey (lua_State *L) {
  lua_pushkeyvalues(L, luaL_checkkeyvalues(L, 1)->GetNextKey());
  return 1;
}

static int KeyValues_GetNextTrueSubKey (lua_State *L) {
  lua_pushkeyvalues(L, luaL_checkkeyvalues(L, 1)->GetNextTrueSubKey());
  return 1;
}

static int KeyValues_GetNextValue (lua_State *L) {
  lua_pushkeyvalues(L, luaL_checkkeyvalues(L, 1)->GetNextValue());
  return 1;
}

static int KeyValues_GetString (lua_State *L) {
  switch(lua_type(L, 2)) {
	case LUA_TNUMBER:
	  lua_pushstring(L, luaL_checkkeyvalues(L, 1)->GetString(luaL_checkint(L, 2), luaL_optstring(L, 3, "")));
	  break;
	case LUA_TNONE:
	case LUA_TSTRING:
	default:
	  lua_pushstring(L, luaL_checkkeyvalues(L, 1)->GetString(luaL_optstring(L, 2, 0), luaL_optstring(L, 3, "")));
	  break;
  }
  return 1;
}

static int KeyValues_IsEmpty (lua_State *L) {
  switch(lua_type(L, 2)) {
	case LUA_TNUMBER:
	  lua_pushboolean(L, luaL_checkkeyvalues(L, 1)->IsEmpty(luaL_checkint(L, 2)));
	  break;
	case LUA_TNONE:
	case LUA_TSTRING:
	default:
	  lua_pushboolean(L, luaL_checkkeyvalues(L, 1)->IsEmpty(luaL_optstring(L, 2, 0)));
	  break;
  }
  return 1;
}

static int KeyValues_LoadFromFile (lua_State *L) {
  lua_pushboolean(L, luaL_checkkeyvalues(L, 1)->LoadFromFile(filesystem, luaL_checkstring(L, 2), luaL_optstring(L, 3, 0)));
  return 1;
}

static int KeyValues_MakeCopy (lua_State *L) {
  lua_pushkeyvalues(L, luaL_checkkeyvalues(L, 1)->MakeCopy());
  return 1;
}

static int KeyValues_ProcessResolutionKeys (lua_State *L) {
  lua_pushboolean(L, luaL_checkkeyvalues(L, 1)->ProcessResolutionKeys(luaL_checkstring(L, 2)));
  return 1;
}

static int KeyValues_RemoveSubKey (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->RemoveSubKey(luaL_checkkeyvalues(L, 2));
  return 0;
}

static int KeyValues_SaveToFile (lua_State *L) {
  lua_pushboolean(L, luaL_checkkeyvalues(L, 1)->SaveToFile(filesystem, luaL_checkstring(L, 2), luaL_optstring(L, 3, 0)));
  return 1;
}

static int KeyValues_SetColor (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->SetColor(luaL_checkstring(L, 2), luaL_checkcolor(L, 3));
  return 0;
}

static int KeyValues_SetFloat (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->SetFloat(luaL_checkstring(L, 2), luaL_checknumber(L, 3));
  return 0;
}

static int KeyValues_SetInt (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->SetInt(luaL_checkstring(L, 2), luaL_checkint(L, 3));
  return 0;
}

static int KeyValues_SetName (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->SetName(luaL_checkstring(L, 2));
  return 0;
}

static int KeyValues_SetNextKey (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->SetNextKey(luaL_checkkeyvalues(L, 2));
  return 0;
}

static int KeyValues_SetString (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->SetString(luaL_checkstring(L, 2), luaL_checkstring(L, 3));
  return 0;
}

static int KeyValues_SetStringValue (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->SetStringValue(luaL_checkstring(L, 2));
  return 0;
}

static int KeyValues_UsesEscapeSequences (lua_State *L) {
  luaL_checkkeyvalues(L, 1)->UsesEscapeSequences(luaL_checkboolean(L, 2));
  return 0;
}

static int KeyValues___eq (lua_State *L) {
  lua_pushboolean(L, lua_tokeyvalues(L, 1) == lua_tokeyvalues(L, 2));
  return 1;
}

static int KeyValues___tostring (lua_State *L) {
  KeyValues *pKV = lua_tokeyvalues(L, 1);
  if (pKV == NULL)
    lua_pushstring(L, "NULL_KEYVALUES");
  else
    lua_pushfstring(L, "KeyValues: %p", pKV);
  return 1;
}


static const luaL_Reg KeyValuesmeta[] = {
  {"AddSubKey", KeyValues_AddSubKey},
  {"ChainKeyValue", KeyValues_ChainKeyValue},
  {"Clear", KeyValues_Clear},
  {"CopySubkeys", KeyValues_CopySubkeys},
  {"CreateNewKey", KeyValues_CreateNewKey},
  {"deleteThis", KeyValues_deleteThis},
  {"FindKey", KeyValues_FindKey},
  {"GetColor", KeyValues_GetColor},
  {"GetDataType", KeyValues_GetDataType},
  {"GetFirstSubKey", KeyValues_GetFirstSubKey},
  {"GetFirstTrueSubKey", KeyValues_GetFirstTrueSubKey},
  {"GetFirstValue", KeyValues_GetFirstValue},
  {"GetFloat", KeyValues_GetFloat},
  {"GetInt", KeyValues_GetInt},
  {"GetName", KeyValues_GetName},
  {"GetNameSymbol", KeyValues_GetNameSymbol},
  {"GetNextKey", KeyValues_GetNextKey},
  {"GetNextTrueSubKey", KeyValues_GetNextTrueSubKey},
  {"GetNextValue", KeyValues_GetNextValue},
  {"GetString", KeyValues_GetString},
  {"IsEmpty", KeyValues_IsEmpty},
  {"LoadFromFile", KeyValues_LoadFromFile},
  {"MakeCopy", KeyValues_MakeCopy},
  {"ProcessResolutionKeys", KeyValues_ProcessResolutionKeys},
  {"RemoveSubKey", KeyValues_RemoveSubKey},
  {"SaveToFile", KeyValues_SaveToFile},
  {"SetColor", KeyValues_SetColor},
  {"SetFloat", KeyValues_SetFloat},
  {"SetInt", KeyValues_SetInt},
  {"SetName", KeyValues_SetName},
  {"SetNextKey", KeyValues_SetNextKey},
  {"SetString", KeyValues_SetString},
  {"SetStringValue", KeyValues_SetStringValue},
  {"UsesEscapeSequences", KeyValues_UsesEscapeSequences},
  {"__eq", KeyValues___eq},
  {"__tostring", KeyValues___tostring},
  {NULL, NULL}
};


static int luasrc_KeyValues (lua_State *L) {
  KeyValues *pKV = NULL;
  if (lua_gettop(L) <= 1)
	pKV = new KeyValues(luaL_checkstring(L, 1));
  else if (lua_gettop(L) <= 3) {
    switch(lua_type(L, 3)) {
      case LUA_TNUMBER:
	    pKV = new KeyValues(luaL_checkstring(L, 1), luaL_checkstring(L, 2), luaL_checkint(L, 3));
        break;
      case LUA_TSTRING:
	    pKV = new KeyValues(luaL_checkstring(L, 1), luaL_checkstring(L, 2), luaL_checkstring(L, 3));
        break;
      default:
        luaL_typerror(L, 3, "string or number");
        break;
    }
  }
  else if (lua_gettop(L) <= 5) {
    switch(lua_type(L, 3)) {
      case LUA_TNUMBER:
	    pKV = new KeyValues(luaL_checkstring(L, 1), luaL_checkstring(L, 2), luaL_checkint(L, 3), luaL_checkstring(L, 4), luaL_checkint(L, 5));
        break;
      case LUA_TSTRING:
	    pKV = new KeyValues(luaL_checkstring(L, 1), luaL_checkstring(L, 2), luaL_checkstring(L, 3), luaL_checkstring(L, 4), luaL_checkstring(L, 5));
        break;
      default:
        luaL_typerror(L, 3, "string or number");
        break;
    }
  }
  lua_pushkeyvalues(L, pKV);
  return 1;
}


static const luaL_Reg KeyValues_funcs[] = {
  {"KeyValues", luasrc_KeyValues},
  {NULL, NULL}
};


/*
** Open KeyValues object
*/
LUALIB_API int luaopen_KeyValues (lua_State *L) {
  luaL_newmetatable(L, LUA_KEYVALUESLIBNAME);
  luaL_register(L, NULL, KeyValuesmeta);
  lua_pushvalue(L, -1);  /* push metatable */
  lua_setfield(L, -2, "__index");  /* metatable.__index = metatable */
  lua_pushstring(L, "keyvalues");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "keyvalues" */
  luaL_register(L, "_G", KeyValues_funcs);
  lua_pop(L, 1);
  // Andrew; This is nasty, but we can't really repurpose the NULL global
  // entity.
  lua_pushkeyvalues(L, NULL);
  lua_setglobal(L, "NULL_KEYVALUES");  /* set global NULL_KEYVALUES */
  return 1;
}
