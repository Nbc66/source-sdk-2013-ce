//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include <cbase.h>
#include <vgui/KeyCode.h>
#include <vgui_int.h>
#include <luamanager.h>
#include <vgui_controls/lPanel.h>

#include <scripted_controls/lPropertyDialog.h>
#include <vgui_controls/PropertySheet.h>
#include <vgui_controls/Button.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
LPropertyDialog::LPropertyDialog(Panel *parent, const char *panelName, lua_State *L) : PropertyDialog(parent, panelName)
{
#if defined( LUA_SDK )
	m_lua_State = L;
	m_nTableReference = LUA_NOREF;
	m_nRefCount = 0;
#endif // LUA_SDK
}

//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
LPropertyDialog::~LPropertyDialog()
{
#if defined( LUA_SDK )
	lua_unref( m_lua_State, m_nTableReference );
#endif // LUA_SDK
}

//-----------------------------------------------------------------------------
// Purpose: Sets up the sheet
//-----------------------------------------------------------------------------
void LPropertyDialog::PerformLayout()
{
	BaseClass::PerformLayout();

#ifdef LUA_SDK
	BEGIN_LUA_CALL_PROPERTYDIALOG_METHOD( "PerformLayout" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Handles command text from the buttons
//-----------------------------------------------------------------------------
void LPropertyDialog::OnCommand(const char *command)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PROPERTYDIALOG_METHOD( "OnCommand" );
		lua_pushstring( m_lua_State, command );
	END_LUA_CALL_PANEL_METHOD( 1, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnCommand(command);
}

//-----------------------------------------------------------------------------
// Purpose: called when the Cancel button is pressed
//-----------------------------------------------------------------------------
void LPropertyDialog::OnCancel()
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PROPERTYDIALOG_METHOD( "OnCancel" );
	END_LUA_CALL_PANEL_METHOD( 0, 0 );
#endif
}


//-----------------------------------------------------------------------------
// Purpose: 
// Input  : code - 
//-----------------------------------------------------------------------------
void LPropertyDialog::OnKeyCodeTyped(KeyCode code)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PROPERTYDIALOG_METHOD( "OnKeyCodeTyped" );
		lua_pushinteger( m_lua_State, code );
	END_LUA_CALL_PANEL_METHOD( 1, 1 );

	RETURN_LUA_PANEL_NONE();
#endif

	BaseClass::OnKeyCodeTyped(code);
}


//-----------------------------------------------------------------------------
// Purpose: Command handler
//-----------------------------------------------------------------------------
bool LPropertyDialog::OnOK(bool applyOnly)
{
#ifdef LUA_SDK
	BEGIN_LUA_CALL_PROPERTYDIALOG_METHOD( "OnOK" );
		lua_pushboolean( m_lua_State, applyOnly );
	END_LUA_CALL_PANEL_METHOD( 1, 1 );

	RETURN_LUA_PANEL_BOOLEAN();
#endif

    // the sheet should have the pages apply changes before we tell the world
	_propertySheet->ApplyChanges();

    // this should tell anybody who's watching us that we're done
	PostActionSignal(new KeyValues("ApplyChanges"));

	// default to closing
	return true;
}

//-----------------------------------------------------------------------------
// Purpose: enable/disable the apply button
//-----------------------------------------------------------------------------
void LPropertyDialog::EnableApplyButton(bool bEnable)
{
	_applyButton->SetEnabled(bEnable);
	InvalidateLayout();
}

/*
** access functions (stack -> C)
*/


LUA_API lua_PropertyDialog *lua_topropertydialog (lua_State *L, int idx) {
  PHandle *phPanel = dynamic_cast<PHandle *>((PHandle *)lua_touserdata(L, idx));
  if (phPanel == NULL)
    return NULL;
  return dynamic_cast<lua_PropertyDialog *>(phPanel->Get());
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushpropertydialog (lua_State *L, PropertyDialog *pDialog) {
  LPropertyDialog *plDialog = dynamic_cast<LPropertyDialog *>(pDialog);
  if (plDialog)
    ++plDialog->m_nRefCount;
  PHandle *phPanel = (PHandle *)lua_newuserdata(L, sizeof(PHandle));
  phPanel->Set(pDialog);
  luaL_getmetatable(L, "PropertyDialog");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_PropertyDialog *luaL_checkpropertydialog (lua_State *L, int narg) {
  lua_PropertyDialog *d = lua_topropertydialog(L, narg);
  if (d == NULL)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "PropertyDialog expected, got INVALID_PANEL");
  return d;
}


static int PropertyDialog_AddPage (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->AddPage(luaL_checkpanel(L, 2), luaL_checkstring(L, 3));
  return 0;
}

static int PropertyDialog_ApplyChanges (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->ApplyChanges();
  return 0;
}

static int PropertyDialog_ChainToAnimationMap (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->ChainToAnimationMap();
  return 0;
}

static int PropertyDialog_ChainToMap (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->ChainToMap();
  return 0;
}

static int PropertyDialog_EnableApplyButton (lua_State *L) {
  LPropertyDialog *plDialog = dynamic_cast<LPropertyDialog *>(luaL_checkpropertydialog(L, 1));
  if (plDialog)
    plDialog->EnableApplyButton(luaL_checkboolean(L, 2));
  return 0;
}

static int PropertyDialog_GetActivePage (lua_State *L) {
  lua_pushpanel(L, luaL_checkpropertydialog(L, 1)->GetActivePage());
  return 1;
}

static int PropertyDialog_GetPanelBaseClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkpropertydialog(L, 1)->GetPanelBaseClassName());
  return 1;
}

static int PropertyDialog_GetPanelClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkpropertydialog(L, 1)->GetPanelClassName());
  return 1;
}

static int PropertyDialog_GetRefTable (lua_State *L) {
  LPropertyDialog *plDialog = dynamic_cast<LPropertyDialog *>(luaL_checkpropertydialog(L, 1));
  if (plDialog) {
    if (plDialog->m_nTableReference == LUA_NOREF) {
      lua_newtable(L);
      plDialog->m_nTableReference = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_getref(L, plDialog->m_nTableReference);
  }
  else
    lua_pushnil(L);
  return 1;
}

static int PropertyDialog_KB_AddBoundKey (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->KB_AddBoundKey(luaL_checkstring(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int PropertyDialog_KB_ChainToMap (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->KB_ChainToMap();
  return 0;
}

static int PropertyDialog_ResetAllData (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->ResetAllData();
  return 0;
}

static int PropertyDialog_SetApplyButtonText (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->SetApplyButtonText(luaL_checkstring(L, 2));
  return 0;
}

static int PropertyDialog_SetApplyButtonVisible (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->SetApplyButtonVisible(luaL_checkboolean(L, 2));
  return 0;
}

static int PropertyDialog_SetCancelButtonText (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->SetCancelButtonText(luaL_checkstring(L, 2));
  return 0;
}

static int PropertyDialog_SetCancelButtonVisible (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->SetCancelButtonVisible(luaL_checkboolean(L, 2));
  return 0;
}

static int PropertyDialog_SetOKButtonText (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->SetOKButtonText(luaL_checkstring(L, 2));
  return 0;
}

static int PropertyDialog_SetOKButtonVisible (lua_State *L) {
  luaL_checkpropertydialog(L, 1)->SetOKButtonVisible(luaL_checkboolean(L, 2));
  return 0;
}

static int PropertyDialog___index (lua_State *L) {
  PropertyDialog *pDialog = lua_topropertydialog(L, 1);
  if (pDialog == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
	lua_pushfstring(L, "%s:%d: attempt to index an INVALID_PANEL", ar2.short_src, ar1.currentline);
	return lua_error(L);
  }
  LPropertyDialog *plDialog = dynamic_cast<LPropertyDialog *>(pDialog);
  if (plDialog && plDialog->m_nTableReference != LUA_NOREF) {
    lua_getref(L, plDialog->m_nTableReference);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 2);
      lua_getmetatable(L, 1);
      lua_pushvalue(L, 2);
      lua_gettable(L, -2);
      if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        luaL_getmetatable(L, "Frame");
        lua_pushvalue(L, 2);
        lua_gettable(L, -2);
        if (lua_isnil(L, -1)) {
          lua_pop(L, 2);
          luaL_getmetatable(L, "EditablePanel");
          lua_pushvalue(L, 2);
          lua_gettable(L, -2);
          if (lua_isnil(L, -1)) {
            lua_pop(L, 2);
            luaL_getmetatable(L, "Panel");
            lua_pushvalue(L, 2);
            lua_gettable(L, -2);
          }
        }
      }
    }
  } else {
    lua_getmetatable(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 2);
      luaL_getmetatable(L, "Frame");
      lua_pushvalue(L, 2);
      lua_gettable(L, -2);
      if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        luaL_getmetatable(L, "EditablePanel");
        lua_pushvalue(L, 2);
        lua_gettable(L, -2);
        if (lua_isnil(L, -1)) {
          lua_pop(L, 2);
          luaL_getmetatable(L, "Panel");
          lua_pushvalue(L, 2);
          lua_gettable(L, -2);
        }
      }
    }
  }
  return 1;
}

static int PropertyDialog___newindex (lua_State *L) {
  PropertyDialog *pDialog = lua_topropertydialog(L, 1);
  if (pDialog == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
    lua_pushfstring(L, "%s:%d: attempt to index an INVALID_PANEL", ar2.short_src, ar1.currentline);
    return lua_error(L);
  }
  LPropertyDialog *plDialog = dynamic_cast<LPropertyDialog *>(pDialog);
  if (plDialog) {
    if (plDialog->m_nTableReference == LUA_NOREF) {
      lua_newtable(L);
      plDialog->m_nTableReference = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_getref(L, plDialog->m_nTableReference);
    lua_pushvalue(L, 3);
    lua_setfield(L, -2, luaL_checkstring(L, 2));
	lua_pop(L, 1);
    return 0;
  } else {
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
    lua_pushfstring(L, "%s:%d: attempt to index a non-scripted panel", ar2.short_src, ar1.currentline);
    return lua_error(L);
  }
}

static int PropertyDialog___gc (lua_State *L) {
  LPropertyDialog *plDialog = dynamic_cast<LPropertyDialog *>(lua_topropertydialog(L, 1));
  if (plDialog) {
    --plDialog->m_nRefCount;
	if (plDialog->m_nRefCount <= 0) {
      delete plDialog;
    }
  }
  return 0;
}

static int PropertyDialog___eq (lua_State *L) {
  lua_pushboolean(L, lua_topropertydialog(L, 1) == lua_topropertydialog(L, 2));
  return 1;
}

static int PropertyDialog___tostring (lua_State *L) {
  PropertyDialog *pDialog = lua_topropertydialog(L, 1);
  if (pDialog == NULL)
    lua_pushstring(L, "INVALID_PANEL");
  else {
    const char *pName = pDialog->GetName();
    if (Q_strcmp(pName, "") == 0)
      pName = "(no name)";
    lua_pushfstring(L, "PropertyDialog: \"%s\"", pName);
  }
  return 1;
}


static const luaL_Reg PropertyDialogmeta[] = {
  {"AddPage", PropertyDialog_AddPage},
  {"ApplyChanges", PropertyDialog_ApplyChanges},
  {"ChainToAnimationMap", PropertyDialog_ChainToAnimationMap},
  {"ChainToMap", PropertyDialog_ChainToMap},
  {"EnableApplyButton", PropertyDialog_EnableApplyButton},
  {"GetActivePage", PropertyDialog_GetActivePage},
  {"GetPanelBaseClassName", PropertyDialog_GetPanelBaseClassName},
  {"GetPanelClassName", PropertyDialog_GetPanelClassName},
  {"GetRefTable", PropertyDialog_GetRefTable},
  {"KB_AddBoundKey", PropertyDialog_KB_AddBoundKey},
  {"KB_ChainToMap", PropertyDialog_KB_ChainToMap},
  {"ResetAllData", PropertyDialog_ResetAllData},
  {"SetApplyButtonText", PropertyDialog_SetApplyButtonText},
  {"SetApplyButtonVisible", PropertyDialog_SetApplyButtonVisible},
  {"SetCancelButtonText", PropertyDialog_SetCancelButtonText},
  {"SetCancelButtonVisible", PropertyDialog_SetCancelButtonVisible},
  {"SetOKButtonText", PropertyDialog_SetOKButtonText},
  {"SetOKButtonVisible", PropertyDialog_SetOKButtonVisible},
  {"__index", PropertyDialog___index},
  {"__newindex", PropertyDialog___newindex},
  {"__gc", PropertyDialog___gc},
  {"__eq", PropertyDialog___eq},
  {"__tostring", PropertyDialog___tostring},
  {NULL, NULL}
};


static int luasrc_PropertyDialog (lua_State *L) {
  PropertyDialog *pDialog = new LPropertyDialog(luaL_optpanel(L, 1, VGui_GetClientLuaRootPanel()), luaL_checkstring(L, 2), L);
  lua_pushpropertydialog(L, pDialog);
  return 1;
}


static const luaL_Reg PropertyDialog_funcs[] = {
  {"PropertyDialog", luasrc_PropertyDialog},
  {NULL, NULL}
};


/*
** Open PropertyDialog object
*/
LUALIB_API int luaopen_vgui_PropertyDialog(lua_State *L) {
  luaL_newmetatable(L, "PropertyDialog");
  luaL_register(L, NULL, PropertyDialogmeta);
  lua_pushstring(L, "panel");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "panel" */
  luaL_register(L, "vgui", PropertyDialog_funcs);
  lua_pop(L, 2);
  return 1;
}
