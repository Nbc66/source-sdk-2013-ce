//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Basic button control
//
// $NoKeywords: $
//=============================================================================//

#include <cbase.h>

#include <vgui_int.h>
#include <luamanager.h>
#include <vgui_controls/lPanel.h>
#include <lColor.h>

#include <scripted_controls/lButton.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
LButton::LButton(Panel *parent, const char *panelName, const char *text, Panel *pActionSignalTarget, const char *pCmd, lua_State *L ) : Button(parent, panelName, text, pActionSignalTarget, pCmd)
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
LButton::~LButton()
{
#if defined( LUA_SDK )
	lua_unref( m_lua_State, m_nTableReference );
#endif // LUA_SDK
}

/*
** access functions (stack -> C)
*/


LUA_API lua_Button *lua_tobutton (lua_State *L, int idx) {
  PHandle *phPanel = dynamic_cast<PHandle *>((PHandle *)lua_touserdata(L, idx));
  if (phPanel == NULL)
    return NULL;
  return dynamic_cast<lua_Button *>(phPanel->Get());
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushbutton (lua_State *L, Button *pButton) {
  LButton *plButton = dynamic_cast<LButton *>(pButton);
  if (plButton)
    ++plButton->m_nRefCount;
  PHandle *phPanel = (PHandle *)lua_newuserdata(L, sizeof(PHandle));
  phPanel->Set(pButton);
  luaL_getmetatable(L, "Button");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_Button *luaL_checkbutton (lua_State *L, int narg) {
  lua_Button *d = lua_tobutton(L, narg);
  if (d == NULL)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "Button expected, got INVALID_PANEL");
  return d;
}


static int Button_CanBeDefaultButton (lua_State *L) {
  lua_pushboolean(L, luaL_checkbutton(L, 1)->CanBeDefaultButton());
  return 1;
}

static int Button_ChainToAnimationMap (lua_State *L) {
  luaL_checkbutton(L, 1)->ChainToAnimationMap();
  return 0;
}

static int Button_ChainToMap (lua_State *L) {
  luaL_checkbutton(L, 1)->ChainToMap();
  return 0;
}

static int Button_DoClick (lua_State *L) {
  luaL_checkbutton(L, 1)->DoClick();
  return 0;
}

static int Button_DrawFocusBox (lua_State *L) {
  luaL_checkbutton(L, 1)->DrawFocusBox(luaL_checkboolean(L, 2));
  return 0;
}

static int Button_FireActionSignal (lua_State *L) {
  luaL_checkbutton(L, 1)->FireActionSignal();
  return 0;
}

static int Button_ForceDepressed (lua_State *L) {
  luaL_checkbutton(L, 1)->ForceDepressed(luaL_checkboolean(L, 2));
  return 0;
}

static int Button_GetButtonBgColor (lua_State *L) {
  lua_pushcolor(L, luaL_checkbutton(L, 1)->GetButtonBgColor());
  return 1;
}

static int Button_GetButtonFgColor (lua_State *L) {
  lua_pushcolor(L, luaL_checkbutton(L, 1)->GetButtonFgColor());
  return 1;
}

static int Button_GetPanelBaseClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkbutton(L, 1)->GetPanelBaseClassName());
  return 1;
}

static int Button_GetPanelClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkbutton(L, 1)->GetPanelClassName());
  return 1;
}

static int Button_GetRefTable (lua_State *L) {
  LButton *plButton = dynamic_cast<LButton *>(luaL_checkbutton(L, 1));
  if (plButton) {
    if (plButton->m_nTableReference == LUA_NOREF) {
      lua_newtable(L);
      plButton->m_nTableReference = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_getref(L, plButton->m_nTableReference);
  }
  else
    lua_pushnil(L);
  return 1;
}

static int Button_IsArmed (lua_State *L) {
  lua_pushboolean(L, luaL_checkbutton(L, 1)->IsArmed());
  return 1;
}

static int Button_IsBlinking (lua_State *L) {
  lua_pushboolean(L, luaL_checkbutton(L, 1)->IsBlinking());
  return 1;
}

static int Button_IsDepressed (lua_State *L) {
  lua_pushboolean(L, luaL_checkbutton(L, 1)->IsDepressed());
  return 1;
}

static int Button_IsDrawingFocusBox (lua_State *L) {
  lua_pushboolean(L, luaL_checkbutton(L, 1)->IsDrawingFocusBox());
  return 1;
}

static int Button_IsMouseClickEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkbutton(L, 1)->IsMouseClickEnabled((MouseCode)luaL_checkint(L, 2)));
  return 1;
}

static int Button_IsSelected (lua_State *L) {
  lua_pushboolean(L, luaL_checkbutton(L, 1)->IsSelected());
  return 1;
}

static int Button_IsUseCaptureMouseEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkbutton(L, 1)->IsUseCaptureMouseEnabled());
  return 1;
}

static int Button_KB_AddBoundKey (lua_State *L) {
  luaL_checkbutton(L, 1)->KB_AddBoundKey(luaL_checkstring(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int Button_KB_ChainToMap (lua_State *L) {
  luaL_checkbutton(L, 1)->KB_ChainToMap();
  return 0;
}

static int Button_OnCursorEntered (lua_State *L) {
  luaL_checkbutton(L, 1)->OnCursorEntered();
  return 0;
}

static int Button_OnCursorExited (lua_State *L) {
  luaL_checkbutton(L, 1)->OnCursorExited();
  return 0;
}

static int Button_OnHotkey (lua_State *L) {
  luaL_checkbutton(L, 1)->OnHotkey();
  return 0;
}

static int Button_OnKillFocus (lua_State *L) {
  luaL_checkbutton(L, 1)->OnKillFocus();
  return 0;
}

static int Button_OnSetFocus (lua_State *L) {
  luaL_checkbutton(L, 1)->OnSetFocus();
  return 0;
}

static int Button_PerformLayout (lua_State *L) {
  luaL_checkbutton(L, 1)->PerformLayout();
  return 0;
}

static int Button_RecalculateDepressedState (lua_State *L) {
  luaL_checkbutton(L, 1)->RecalculateDepressedState();
  return 0;
}

static int Button_SetArmed (lua_State *L) {
  luaL_checkbutton(L, 1)->SetArmed(luaL_checkboolean(L, 2));
  return 0;
}

static int Button_SetArmedColor (lua_State *L) {
  luaL_checkbutton(L, 1)->SetArmedColor(luaL_checkcolor(L, 2), luaL_checkcolor(L, 3));
  return 0;
}

static int Button_SetArmedSound (lua_State *L) {
  luaL_checkbutton(L, 1)->SetArmedSound(luaL_checkstring(L, 2));
  return 0;
}

static int Button_SetAsCurrentDefaultButton (lua_State *L) {
  luaL_checkbutton(L, 1)->SetAsCurrentDefaultButton(luaL_checkint(L, 2));
  return 0;
}

static int Button_SetAsDefaultButton (lua_State *L) {
  luaL_checkbutton(L, 1)->SetAsDefaultButton(luaL_checkint(L, 2));
  return 0;
}

static int Button_SetBlink (lua_State *L) {
  luaL_checkbutton(L, 1)->SetBlink(luaL_checkboolean(L, 2));
  return 0;
}

static int Button_SetBlinkColor (lua_State *L) {
  luaL_checkbutton(L, 1)->SetBlinkColor(luaL_checkcolor(L, 2));
  return 0;
}

static int Button_SetButtonActivationType (lua_State *L) {
  luaL_checkbutton(L, 1)->SetButtonActivationType((Button::ActivationType_t)luaL_checkint(L, 2));
  return 0;
}

static int Button_SetButtonBorderEnabled (lua_State *L) {
  luaL_checkbutton(L, 1)->SetButtonBorderEnabled(luaL_checkboolean(L, 2));
  return 0;
}

static int Button_SetDefaultColor (lua_State *L) {
  luaL_checkbutton(L, 1)->SetDefaultColor(luaL_checkcolor(L, 2), luaL_checkcolor(L, 3));
  return 0;
}

static int Button_SetDepressedColor (lua_State *L) {
  luaL_checkbutton(L, 1)->SetDepressedColor(luaL_checkcolor(L, 2), luaL_checkcolor(L, 3));
  return 0;
}

static int Button_SetDepressedSound (lua_State *L) {
  luaL_checkbutton(L, 1)->SetDepressedSound(luaL_checkstring(L, 2));
  return 0;
}

static int Button_SetMouseClickEnabled (lua_State *L) {
  luaL_checkbutton(L, 1)->SetMouseClickEnabled((MouseCode)luaL_checkint(L, 2), luaL_checkboolean(L, 3));
  return 0;
}

static int Button_SetReleasedSound (lua_State *L) {
  luaL_checkbutton(L, 1)->SetReleasedSound(luaL_checkstring(L, 2));
  return 0;
}

static int Button_SetSelected (lua_State *L) {
  luaL_checkbutton(L, 1)->SetSelected(luaL_checkboolean(L, 2));
  return 0;
}

static int Button_SetShouldPaint (lua_State *L) {
  luaL_checkbutton(L, 1)->SetShouldPaint(luaL_checkboolean(L, 2));
  return 0;
}

static int Button_SetUseCaptureMouse (lua_State *L) {
  luaL_checkbutton(L, 1)->SetUseCaptureMouse(luaL_checkboolean(L, 2));
  return 0;
}

static int Button_ShouldPaint (lua_State *L) {
  lua_pushboolean(L, luaL_checkbutton(L, 1)->ShouldPaint());
  return 1;
}

static int Button_SizeToContents (lua_State *L) {
  luaL_checkbutton(L, 1)->SizeToContents();
  return 0;
}

static int Button___index (lua_State *L) {
  Button *pButton = lua_tobutton(L, 1);
  if (pButton == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
	lua_pushfstring(L, "%s:%d: attempt to index an INVALID_PANEL", ar2.short_src, ar1.currentline);
	return lua_error(L);
  }
  LButton *plButton = dynamic_cast<LButton *>(pButton);
  if (plButton && plButton->m_nTableReference != LUA_NOREF) {
    lua_getref(L, plButton->m_nTableReference);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 2);
      lua_getmetatable(L, 1);
      lua_pushvalue(L, 2);
      lua_gettable(L, -2);
      if (lua_isnil(L, -1)) {
        lua_pop(L, 2);
        luaL_getmetatable(L, "Panel");
        lua_pushvalue(L, 2);
        lua_gettable(L, -2);
      }
    }
  } else {
    lua_getmetatable(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 2);
      luaL_getmetatable(L, "Panel");
      lua_pushvalue(L, 2);
      lua_gettable(L, -2);
    }
  }
  return 1;
}

static int Button___newindex (lua_State *L) {
  Button *pButton = lua_tobutton(L, 1);
  if (pButton == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
    lua_pushfstring(L, "%s:%d: attempt to index an INVALID_PANEL", ar2.short_src, ar1.currentline);
    return lua_error(L);
  }
  LButton *plButton = dynamic_cast<LButton *>(pButton);
  if (plButton) {
    if (plButton->m_nTableReference == LUA_NOREF) {
      lua_newtable(L);
      plButton->m_nTableReference = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_getref(L, plButton->m_nTableReference);
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

static int Button___gc (lua_State *L) {
  LButton *plButton = dynamic_cast<LButton *>(lua_tobutton(L, 1));
  if (plButton) {
    --plButton->m_nRefCount;
	if (plButton->m_nRefCount <= 0) {
      delete plButton;
    }
  }
  return 0;
}

static int Button___eq (lua_State *L) {
  lua_pushboolean(L, lua_tobutton(L, 1) == lua_tobutton(L, 2));
  return 1;
}

static int Button___tostring (lua_State *L) {
  Button *pButton = lua_tobutton(L, 1);
  if (pButton == NULL)
    lua_pushstring(L, "INVALID_PANEL");
  else {
    const char *pName = pButton->GetName();
    if (Q_strcmp(pName, "") == 0)
      pName = "(no name)";
    lua_pushfstring(L, "Button: \"%s\"", pName);
  }
  return 1;
}


static const luaL_Reg Buttonmeta[] = {
  {"CanBeDefaultButton", Button_CanBeDefaultButton},
  {"ChainToAnimationMap", Button_ChainToAnimationMap},
  {"ChainToMap", Button_ChainToMap},
  {"DoClick", Button_DoClick},
  {"DrawFocusBox", Button_DrawFocusBox},
  {"FireActionSignal", Button_FireActionSignal},
  {"ForceDepressed", Button_ForceDepressed},
  {"GetButtonBgColor", Button_GetButtonBgColor},
  {"GetButtonFgColor", Button_GetButtonFgColor},
  {"GetPanelBaseClassName", Button_GetPanelBaseClassName},
  {"GetPanelClassName", Button_GetPanelClassName},
  {"GetRefTable", Button_GetRefTable},
  {"IsArmed", Button_IsArmed},
  {"IsBlinking", Button_IsBlinking},
  {"IsDepressed", Button_IsDepressed},
  {"IsDrawingFocusBox", Button_IsDrawingFocusBox},
  {"IsMouseClickEnabled", Button_IsMouseClickEnabled},
  {"IsSelected", Button_IsSelected},
  {"IsUseCaptureMouseEnabled", Button_IsUseCaptureMouseEnabled},
  {"KB_AddBoundKey", Button_KB_AddBoundKey},
  {"KB_ChainToMap", Button_KB_ChainToMap},
  {"OnCursorEntered", Button_OnCursorEntered},
  {"OnCursorExited", Button_OnCursorExited},
  {"OnHotkey", Button_OnHotkey},
  {"OnKillFocus", Button_OnKillFocus},
  {"OnSetFocus", Button_OnSetFocus},
  {"PerformLayout", Button_PerformLayout},
  {"RecalculateDepressedState", Button_RecalculateDepressedState},
  {"SetArmed", Button_SetArmed},
  {"SetArmedColor", Button_SetArmedColor},
  {"SetArmedSound", Button_SetArmedSound},
  {"SetAsCurrentDefaultButton", Button_SetAsCurrentDefaultButton},
  {"SetAsDefaultButton", Button_SetAsDefaultButton},
  {"SetBlink", Button_SetBlink},
  {"SetBlinkColor", Button_SetBlinkColor},
  {"SetButtonActivationType", Button_SetButtonActivationType},
  {"SetButtonBorderEnabled", Button_SetButtonBorderEnabled},
  {"SetDefaultColor", Button_SetDefaultColor},
  {"SetDepressedColor", Button_SetDepressedColor},
  {"SetDepressedSound", Button_SetDepressedSound},
  {"SetMouseClickEnabled", Button_SetMouseClickEnabled},
  {"SetReleasedSound", Button_SetReleasedSound},
  {"SetSelected", Button_SetSelected},
  {"SetShouldPaint", Button_SetShouldPaint},
  {"SetUseCaptureMouse", Button_SetUseCaptureMouse},
  {"ShouldPaint", Button_ShouldPaint},
  {"SizeToContents", Button_SizeToContents},
  {"__index", Button___index},
  {"__newindex", Button___newindex},
  {"__gc", Button___gc},
  {"__eq", Button___eq},
  {"__tostring", Button___tostring},
  {NULL, NULL}
};


static int luasrc_Button (lua_State *L) {
  Button *pButton = new LButton(luaL_optpanel(L, 1, VGui_GetClientLuaRootPanel()), luaL_checkstring(L, 2), luaL_checkstring(L, 3), luaL_optpanel(L, 4, 0), luaL_optstring(L, 5, 0), L);
  lua_pushbutton(L, pButton);
  return 1;
}


static const luaL_Reg Button_funcs[] = {
  {"Button", luasrc_Button},
  {NULL, NULL}
};


/*
** Open Button object
*/
LUALIB_API int luaopen_vgui_Button(lua_State *L) {
  luaL_newmetatable(L, "Button");
  luaL_register(L, NULL, Buttonmeta);
  lua_pushstring(L, "panel");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "panel" */
  luaL_register(L, "vgui", Button_funcs);
  lua_pop(L, 2);
  return 1;
}

