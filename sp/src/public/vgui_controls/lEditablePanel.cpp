//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#define leditablepanel_cpp

#include "cbase.h"
#include <vgui_controls/PHandle.h>
#include "luamanager.h"
#include <vgui_controls/lEditablePanel.h>
#include <LKeyValues.h>
#include <vgui_controls/lPanel.h>

using namespace vgui;


/*
** access functions (stack -> C)
*/


LUA_API lua_EditablePanel *lua_toeditablepanel (lua_State *L, int idx) {
  PHandle *phPanel = dynamic_cast<PHandle *>((PHandle *)lua_touserdata(L, idx));
  if (phPanel == NULL)
    return NULL;
  return dynamic_cast<lua_EditablePanel *>(phPanel->Get());
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pusheditablepanel (lua_State *L, EditablePanel *pPanel) {
  PHandle *phPanel = (PHandle *)lua_newuserdata(L, sizeof(PHandle));
  phPanel->Set(pPanel);
  luaL_getmetatable(L, "EditablePanel");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_EditablePanel *luaL_checkeditablepanel (lua_State *L, int narg) {
  lua_EditablePanel *d = lua_toeditablepanel(L, narg);
  if (d == NULL)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "EditablePanel expected, got INVALID_PANEL");
  return d;
}


static int EditablePanel_ActivateBuildMode (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->ActivateBuildMode();
  return 0;
}

static int EditablePanel_ApplySettings (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->ApplySettings(luaL_checkkeyvalues(L, 2));
  return 0;
}

static int EditablePanel_ChainToAnimationMap (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->ChainToAnimationMap();
  return 0;
}

static int EditablePanel_ChainToMap (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->ChainToMap();
  return 0;
}

static int EditablePanel_CreateControlByName (lua_State *L) {
  lua_pushpanel(L, luaL_checkeditablepanel(L, 1)->CreateControlByName(luaL_checkstring(L, 2)));
  return 1;
}

static int EditablePanel_GetControlInt (lua_State *L) {
  lua_pushinteger(L, luaL_checkeditablepanel(L, 1)->GetControlInt(luaL_checkstring(L, 2), luaL_checkint(L, 3)));
  return 1;
}

static int EditablePanel_GetControlString (lua_State *L) {
  lua_pushstring(L, luaL_checkeditablepanel(L, 1)->GetControlString(luaL_checkstring(L, 2), luaL_optstring(L, 3, "")));
  return 1;
}

static int EditablePanel_GetCurrentKeyFocus (lua_State *L) {
  lua_pushpanel(L, luaL_checkeditablepanel(L, 1)->GetCurrentKeyFocus());
  return 1;
}

static int EditablePanel_GetDialogVariables (lua_State *L) {
  lua_pushkeyvalues(L, luaL_checkeditablepanel(L, 1)->GetDialogVariables());
  return 1;
}

static int EditablePanel_GetPanelBaseClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkeditablepanel(L, 1)->GetPanelBaseClassName());
  return 1;
}

static int EditablePanel_GetPanelClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkeditablepanel(L, 1)->GetPanelClassName());
  return 1;
}

static int EditablePanel_HasHotkey (lua_State *L) {
  size_t l;
  lua_pushpanel(L, luaL_checkeditablepanel(L, 1)->HasHotkey((wchar_t)luaL_checklstring(L, 2, &l)));
  return 1;
}

static int EditablePanel_KB_AddBoundKey (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->KB_AddBoundKey(luaL_checkstring(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 3));
  return 0;
}

static int EditablePanel_KB_ChainToMap (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->KB_ChainToMap();
  return 0;
}

static int EditablePanel_KeyCodeToString (lua_State *L) {
  lua_pushstring(L, luaL_checkeditablepanel(L, 1)->KeyCodeToString((KeyCode)luaL_checkint(L, 2)));
  return 1;
}

static int EditablePanel_LoadControlSettings (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->LoadControlSettings(luaL_checkstring(L, 2), luaL_optstring(L, 3, NULL), luaL_optkeyvalues(L, 4, NULL));
  return 0;
}

static int EditablePanel_LoadControlSettingsAndUserConfig (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->LoadControlSettingsAndUserConfig(luaL_checkstring(L, 2), luaL_optint(L, 3, 0));
  return 0;
}

static int EditablePanel_LoadUserConfig (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->LoadUserConfig(luaL_checkstring(L, 2), luaL_optint(L, 3, 0));
  return 0;
}

static int EditablePanel_OnKeyCodeTyped (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->OnKeyCodeTyped((KeyCode)luaL_checkint(L, 2));
  return 0;
}

static int EditablePanel_OnRequestFocus (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->OnRequestFocus(luaL_checkvpanel(L, 2), luaL_checkvpanel(L, 3));
  return 0;
}

static int EditablePanel_OnSetFocus (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->OnSetFocus();
  return 0;
}

static int EditablePanel_RegisterControlSettingsFile (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->RegisterControlSettingsFile(luaL_checkstring(L, 2), luaL_optstring(L, 3, NULL));
  return 0;
}

static int EditablePanel_RequestFocus (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->RequestFocus(luaL_optint(L, 2, 0));
  return 0;
}

static int EditablePanel_RequestFocusNext (lua_State *L) {
  lua_pushboolean(L, luaL_checkeditablepanel(L, 1)->RequestFocusNext(luaL_checkvpanel(L, 2)));
  return 1;
}

static int EditablePanel_RequestFocusPrev (lua_State *L) {
  lua_pushboolean(L, luaL_checkeditablepanel(L, 1)->RequestFocusPrev(luaL_checkvpanel(L, 2)));
  return 1;
}

static int EditablePanel_RequestInfo (lua_State *L) {
  lua_pushboolean(L, luaL_checkeditablepanel(L, 1)->RequestInfo(luaL_checkkeyvalues(L, 2)));
  return 1;
}

static int EditablePanel_RequestInfoFromChild (lua_State *L) {
  lua_pushboolean(L, luaL_checkeditablepanel(L, 1)->RequestInfoFromChild(luaL_checkstring(L, 2), luaL_checkkeyvalues(L, 3)));
  return 1;
}

static int EditablePanel_SaveUserConfig (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->SaveUserConfig();
  return 0;
}

static int EditablePanel_SetControlEnabled (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->SetControlEnabled(luaL_checkstring(L, 2), luaL_checkboolean(L, 3));
  return 0;
}

static int EditablePanel_SetControlInt (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->SetControlInt(luaL_checkstring(L, 2), luaL_checkint(L, 3));
  return 0;
}

static int EditablePanel_SetControlString (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->SetControlString(luaL_checkstring(L, 2), luaL_checkstring(L, 3));
  return 0;
}

static int EditablePanel_SetControlVisible (lua_State *L) {
  luaL_checkeditablepanel(L, 1)->SetControlVisible(luaL_checkstring(L, 2), luaL_checkboolean(L, 3));
  return 0;
}

static int EditablePanel_SetDialogVariable (lua_State *L) {
  switch(lua_type(L, 3)) {
	case LUA_TNUMBER:
	  luaL_checkeditablepanel(L, 1)->SetDialogVariable(luaL_checkstring(L, 2), (float)luaL_checknumber(L, 3));
	  break;
	case LUA_TSTRING:
	default:
	  luaL_checkeditablepanel(L, 1)->SetDialogVariable(luaL_checkstring(L, 2), luaL_checkstring(L, 3));
	  break;
  }
  return 0;
}

static int EditablePanel___index (lua_State *L) {
  EditablePanel *pPanel = lua_toeditablepanel(L, 1);
  if (pPanel == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
	lua_pushfstring(L, "%s:%d: attempt to index an INVALID_PANEL", ar2.short_src, ar1.currentline);
	return lua_error(L);
  }
  lua_getmetatable(L, 1);
  lua_pushvalue(L, 2);
  lua_gettable(L, -2);
  if (lua_isnil(L, -1)) {
    lua_pop(L, 2);
    luaL_getmetatable(L, "Panel");
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
  }
  return 1;
}

static int EditablePanel___eq (lua_State *L) {
  lua_pushboolean(L, lua_toeditablepanel(L, 1) == lua_toeditablepanel(L, 2));
  return 1;
}

static int EditablePanel___tostring (lua_State *L) {
  EditablePanel *pPanel = lua_toeditablepanel(L, 1);
  if (pPanel == NULL)
    lua_pushstring(L, "INVALID_PANEL");
  else {
    const char *pName = pPanel->GetName();
    if (Q_strcmp(pName, "") == 0)
      pName = "(no name)";
    lua_pushfstring(L, "EditablePanel: \"%s\"", pName);
  }
  return 1;
}


static const luaL_Reg EditablePanelmeta[] = {
  {"ActivateBuildMode", EditablePanel_ActivateBuildMode},
  {"ApplySettings", EditablePanel_ApplySettings},
  {"ChainToAnimationMap", EditablePanel_ChainToAnimationMap},
  {"ChainToMap", EditablePanel_ChainToMap},
  {"CreateControlByName", EditablePanel_CreateControlByName},
  {"GetControlInt", EditablePanel_GetControlInt},
  {"GetControlString", EditablePanel_GetControlString},
  {"GetCurrentKeyFocus", EditablePanel_GetCurrentKeyFocus},
  {"GetDialogVariables", EditablePanel_GetDialogVariables},
  {"GetPanelBaseClassName", EditablePanel_GetPanelBaseClassName},
  {"GetPanelClassName", EditablePanel_GetPanelClassName},
  {"HasHotkey", EditablePanel_HasHotkey},
  {"KB_AddBoundKey", EditablePanel_KB_AddBoundKey},
  {"KB_ChainToMap", EditablePanel_KB_ChainToMap},
  {"KeyCodeToString", EditablePanel_KeyCodeToString},
  {"LoadControlSettings", EditablePanel_LoadControlSettings},
  {"LoadControlSettingsAndUserConfig", EditablePanel_LoadControlSettingsAndUserConfig},
  {"LoadUserConfig", EditablePanel_LoadUserConfig},
  {"OnKeyCodeTyped", EditablePanel_OnKeyCodeTyped},
  {"OnRequestFocus", EditablePanel_OnRequestFocus},
  {"OnSetFocus", EditablePanel_OnSetFocus},
  {"RegisterControlSettingsFile", EditablePanel_RegisterControlSettingsFile},
  {"RequestFocus", EditablePanel_RequestFocus},
  {"RequestFocusNext", EditablePanel_RequestFocusNext},
  {"RequestFocusPrev", EditablePanel_RequestFocusPrev},
  {"RequestInfo", EditablePanel_RequestInfo},
  {"RequestInfoFromChild", EditablePanel_RequestInfoFromChild},
  {"SaveUserConfig", EditablePanel_SaveUserConfig},
  {"SetControlEnabled", EditablePanel_SetControlEnabled},
  {"SetControlInt", EditablePanel_SetControlInt},
  {"SetControlString", EditablePanel_SetControlString},
  {"SetControlVisible", EditablePanel_SetControlVisible},
  {"SetDialogVariable", EditablePanel_SetDialogVariable},
  {"__index", EditablePanel___index},
  {"__eq", EditablePanel___eq},
  {"__tostring", EditablePanel___tostring},
  {NULL, NULL}
};


/*
** Open EditablePanel object
*/
LUALIB_API int luaopen_vgui_EditablePanel (lua_State *L) {
  luaL_newmetatable(L, "EditablePanel");
  luaL_register(L, NULL, EditablePanelmeta);
  lua_pushstring(L, "panel");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "panel" */
  return 1;
}
