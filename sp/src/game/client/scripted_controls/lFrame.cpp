//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#include <cbase.h>
#include <vgui/IVGui.h>
#include <vgui_int.h>
#include <ienginevgui.h>
#include <luamanager.h>
#include <vgui_controls/lPanel.h>
#include <LKeyValues.h>

#include <scripted_controls/lFrame.h>

// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
LFrame::LFrame(Panel *parent, const char *panelName, bool showTaskbarIcon, lua_State *L) : Frame(parent, panelName, showTaskbarIcon)
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
LFrame::~LFrame()
{
#if defined( LUA_SDK )
	lua_unref( m_lua_State, m_nTableReference );
#endif // LUA_SDK
}

/*
** access functions (stack -> C)
*/


LUA_API lua_Frame *lua_toframe (lua_State *L, int idx) {
  PHandle *phPanel = dynamic_cast<PHandle *>((PHandle *)lua_touserdata(L, idx));
  if (phPanel == NULL)
    return NULL;
  return dynamic_cast<lua_Frame *>(phPanel->Get());
}



/*
** push functions (C -> stack)
*/


LUA_API void lua_pushframe (lua_State *L, Frame *pFrame) {
  LFrame *plFrame = dynamic_cast<LFrame *>(pFrame);
  if (plFrame)
    ++plFrame->m_nRefCount;
  PHandle *phPanel = (PHandle *)lua_newuserdata(L, sizeof(PHandle));
  phPanel->Set(pFrame);
  luaL_getmetatable(L, "Frame");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_Frame *luaL_checkframe (lua_State *L, int narg) {
  lua_Frame *d = lua_toframe(L, narg);
  if (d == NULL)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "Frame expected, got INVALID_PANEL");
  return d;
}


static int Frame_Activate (lua_State *L) {
  luaL_checkframe(L, 1)->Activate();
  return 0;
}

static int Frame_ActivateMinimized (lua_State *L) {
  luaL_checkframe(L, 1)->ActivateMinimized();
  return 0;
}

static int Frame_CanChainKeysToParent (lua_State *L) {
  lua_pushboolean(L, luaL_checkframe(L, 1)->CanChainKeysToParent());
  return 1;
}

static int Frame_CanStartDragging (lua_State *L) {
  lua_pushboolean(L, luaL_checkframe(L, 1)->CanStartDragging(luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5)));
  return 1;
}

static int Frame_ChainToAnimationMap (lua_State *L) {
  luaL_checkframe(L, 1)->ChainToAnimationMap();
  return 0;
}

static int Frame_ChainToMap (lua_State *L) {
  luaL_checkframe(L, 1)->ChainToMap();
  return 0;
}

static int Frame_Close (lua_State *L) {
  luaL_checkframe(L, 1)->Close();
  return 0;
}

static int Frame_CloseModal (lua_State *L) {
  luaL_checkframe(L, 1)->CloseModal();
  return 0;
}

static int Frame_DeletePanel (lua_State *L) {
  luaL_checkframe(L, 1)->DeletePanel();
  return 0;
}

static int Frame_DisableFadeEffect (lua_State *L) {
  luaL_checkframe(L, 1)->DisableFadeEffect();
  return 0;
}

static int Frame_DoModal (lua_State *L) {
  luaL_checkframe(L, 1)->DoModal();
  return 0;
}

static int Frame_FlashWindow (lua_State *L) {
  luaL_checkframe(L, 1)->FlashWindow();
  return 0;
}

static int Frame_FlashWindowStop (lua_State *L) {
  luaL_checkframe(L, 1)->FlashWindowStop();
  return 0;
}

static int Frame_GetBottomRightSize (lua_State *L) {
  lua_pushinteger(L, luaL_checkframe(L, 1)->GetBottomRightSize());
  return 1;
}

static int Frame_GetCaptionHeight (lua_State *L) {
  lua_pushinteger(L, luaL_checkframe(L, 1)->GetCaptionHeight());
  return 1;
}

static int Frame_GetClipToParent (lua_State *L) {
  lua_pushboolean(L, luaL_checkframe(L, 1)->GetClipToParent());
  return 1;
}

static int Frame_GetCornerSize (lua_State *L) {
  lua_pushinteger(L, luaL_checkframe(L, 1)->GetCornerSize());
  return 1;
}

static int Frame_GetDraggerSize (lua_State *L) {
  lua_pushinteger(L, luaL_checkframe(L, 1)->GetDraggerSize());
  return 1;
}

static int Frame_GetPanelBaseClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkframe(L, 1)->GetPanelBaseClassName());
  return 1;
}

static int Frame_GetPanelClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkframe(L, 1)->GetPanelClassName());
  return 1;
}

static int Frame_GetRefTable (lua_State *L) {
  LFrame *plFrame = dynamic_cast<LFrame *>(luaL_checkframe(L, 1));
  if (plFrame) {
    if (plFrame->m_nTableReference == LUA_NOREF) {
      lua_newtable(L);
      plFrame->m_nTableReference = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_getref(L, plFrame->m_nTableReference);
  }
  else
    lua_pushnil(L);
  return 1;
}

static int Frame_IsMinimized (lua_State *L) {
  lua_pushboolean(L, luaL_checkframe(L, 1)->IsMinimized());
  return 1;
}

static int Frame_IsMoveable (lua_State *L) {
  lua_pushboolean(L, luaL_checkframe(L, 1)->IsMoveable());
  return 1;
}

static int Frame_IsSizeable (lua_State *L) {
  lua_pushboolean(L, luaL_checkframe(L, 1)->IsSizeable());
  return 1;
}

static int Frame_IsSmallCaption (lua_State *L) {
  lua_pushboolean(L, luaL_checkframe(L, 1)->IsSmallCaption());
  return 1;
}

static int Frame_KB_AddBoundKey (lua_State *L) {
  luaL_checkframe(L, 1)->KB_AddBoundKey(luaL_checkstring(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int Frame_KB_ChainToMap (lua_State *L) {
  luaL_checkframe(L, 1)->KB_ChainToMap();
  return 0;
}

static int Frame_LoadControlSettings (lua_State *L) {
  luaL_checkframe(L, 1)->LoadControlSettings(luaL_checkstring(L, 2), luaL_optstring(L, 3, NULL), luaL_optkeyvalues(L, 4, NULL));
  return 0;
}

static int Frame_MoveToCenterOfScreen (lua_State *L) {
  luaL_checkframe(L, 1)->MoveToCenterOfScreen();
  return 0;
}

static int Frame_OnCommand (lua_State *L) {
  luaL_checkframe(L, 1)->OnCommand(luaL_checkstring(L, 2));
  return 0;
}

static int Frame_PlaceUnderCursor (lua_State *L) {
  luaL_checkframe(L, 1)->PlaceUnderCursor();
  return 0;
}

static int Frame_SetChainKeysToParent (lua_State *L) {
  luaL_checkframe(L, 1)->SetChainKeysToParent(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetClipToParent (lua_State *L) {
  luaL_checkframe(L, 1)->SetClipToParent(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetCloseButtonVisible (lua_State *L) {
  luaL_checkframe(L, 1)->SetCloseButtonVisible(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetDeleteSelfOnClose (lua_State *L) {
  luaL_checkframe(L, 1)->SetDeleteSelfOnClose(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetImages (lua_State *L) {
  luaL_checkframe(L, 1)->SetImages(luaL_checkstring(L, 2), luaL_optstring(L, 3, 0));
  return 0;
}

static int Frame_SetMaximizeButtonVisible (lua_State *L) {
  luaL_checkframe(L, 1)->SetMaximizeButtonVisible(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetMenuButtonResponsive (lua_State *L) {
  luaL_checkframe(L, 1)->SetMenuButtonResponsive(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetMenuButtonVisible (lua_State *L) {
  luaL_checkframe(L, 1)->SetMenuButtonVisible(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetMinimizeButtonVisible (lua_State *L) {
  luaL_checkframe(L, 1)->SetMinimizeButtonVisible(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetMinimizeToSysTrayButtonVisible (lua_State *L) {
  luaL_checkframe(L, 1)->SetMinimizeToSysTrayButtonVisible(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetMoveable (lua_State *L) {
  luaL_checkframe(L, 1)->SetMoveable(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetSizeable (lua_State *L) {
  luaL_checkframe(L, 1)->SetSizeable(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetSmallCaption (lua_State *L) {
  luaL_checkframe(L, 1)->SetSmallCaption(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame_SetTitle (lua_State *L) {
  luaL_checkframe(L, 1)->SetTitle(luaL_checkstring(L, 2), luaL_checkboolean(L, 3));
  return 0;
}

static int Frame_SetTitleBarVisible (lua_State *L) {
  luaL_checkframe(L, 1)->SetTitleBarVisible(luaL_checkboolean(L, 2));
  return 0;
}

static int Frame___index (lua_State *L) {
  Frame *pFrame = lua_toframe(L, 1);
  if (pFrame == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
	lua_pushfstring(L, "%s:%d: attempt to index an INVALID_PANEL", ar2.short_src, ar1.currentline);
	return lua_error(L);
  }
  LFrame *plFrame = dynamic_cast<LFrame *>(pFrame);
  if (plFrame && plFrame->m_nTableReference != LUA_NOREF) {
    lua_getref(L, plFrame->m_nTableReference);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 2);
      lua_getmetatable(L, 1);
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
  } else {
    lua_getmetatable(L, 1);
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
  return 1;
}

static int Frame___newindex (lua_State *L) {
  Frame *pFrame = lua_toframe(L, 1);
  if (pFrame == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
    lua_pushfstring(L, "%s:%d: attempt to index an INVALID_PANEL", ar2.short_src, ar1.currentline);
    return lua_error(L);
  }
  LFrame *plFrame = dynamic_cast<LFrame *>(pFrame);
  if (plFrame) {
    if (plFrame->m_nTableReference == LUA_NOREF) {
      lua_newtable(L);
      plFrame->m_nTableReference = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_getref(L, plFrame->m_nTableReference);
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

static int Frame___gc (lua_State *L) {
  LFrame *plFrame = dynamic_cast<LFrame *>(lua_toframe(L, 1));
  if (plFrame) {
    --plFrame->m_nRefCount;
	if (plFrame->m_nRefCount <= 0) {
      delete plFrame;
    }
  }
  return 0;
}

static int Frame___eq (lua_State *L) {
  lua_pushboolean(L, lua_toframe(L, 1) == lua_toframe(L, 2));
  return 1;
}

static int Frame___tostring (lua_State *L) {
  Frame *pFrame = lua_toframe(L, 1);
  if (pFrame == NULL)
    lua_pushstring(L, "INVALID_PANEL");
  else {
    const char *pName = pFrame->GetName();
    if (Q_strcmp(pName, "") == 0)
      pName = "(no name)";
    lua_pushfstring(L, "Frame: \"%s\"", pName);
  }
  return 1;
}


static const luaL_Reg Framemeta[] = {
  {"Activate", Frame_Activate},
  {"ActivateMinimized", Frame_ActivateMinimized},
  {"CanChainKeysToParent", Frame_CanChainKeysToParent},
  {"CanStartDragging", Frame_CanStartDragging},
  {"ChainToAnimationMap", Frame_ChainToAnimationMap},
  {"ChainToMap", Frame_ChainToMap},
  {"Close", Frame_Close},
  {"CloseModal", Frame_CloseModal},
  {"DeletePanel", Frame_DeletePanel},
  {"DisableFadeEffect", Frame_DisableFadeEffect},
  {"DoModal", Frame_DoModal},
  {"FlashWindow", Frame_FlashWindow},
  {"FlashWindowStop", Frame_FlashWindowStop},
  {"GetBottomRightSize", Frame_GetBottomRightSize},
  {"GetCaptionHeight", Frame_GetCaptionHeight},
  {"GetClipToParent", Frame_GetClipToParent},
  {"GetCornerSize", Frame_GetCornerSize},
  {"GetDraggerSize", Frame_GetDraggerSize},
  {"GetPanelBaseClassName", Frame_GetPanelBaseClassName},
  {"GetPanelClassName", Frame_GetPanelClassName},
  {"GetRefTable", Frame_GetRefTable},
  {"IsMinimized", Frame_IsMinimized},
  {"IsMoveable", Frame_IsMoveable},
  {"IsSizeable", Frame_IsSizeable},
  {"IsSmallCaption", Frame_IsSmallCaption},
  {"KB_AddBoundKey", Frame_KB_AddBoundKey},
  {"KB_ChainToMap", Frame_KB_ChainToMap},
  {"LoadControlSettings", Frame_LoadControlSettings},
  {"MoveToCenterOfScreen", Frame_MoveToCenterOfScreen},
  {"OnCommand", Frame_OnCommand},
  {"PlaceUnderCursor", Frame_PlaceUnderCursor},
  {"SetChainKeysToParent", Frame_SetChainKeysToParent},
  {"SetClipToParent", Frame_SetClipToParent},
  {"SetCloseButtonVisible", Frame_SetCloseButtonVisible},
  {"SetDeleteSelfOnClose", Frame_SetDeleteSelfOnClose},
  {"SetImages", Frame_SetImages},
  {"SetMaximizeButtonVisible", Frame_SetMaximizeButtonVisible},
  {"SetMenuButtonResponsive", Frame_SetMenuButtonResponsive},
  {"SetMenuButtonVisible", Frame_SetMenuButtonVisible},
  {"SetMinimizeButtonVisible", Frame_SetMinimizeButtonVisible},
  {"SetMinimizeToSysTrayButtonVisible", Frame_SetMinimizeToSysTrayButtonVisible},
  {"SetMoveable", Frame_SetMoveable},
  {"SetSizeable", Frame_SetSizeable},
  {"SetSmallCaption", Frame_SetSmallCaption},
  {"SetTitle", Frame_SetTitle},
  {"SetTitleBarVisible", Frame_SetTitleBarVisible},
  {"__index", Frame___index},
  {"__newindex", Frame___newindex},
  {"__gc", Frame___gc},
  {"__eq", Frame___eq},
  {"__tostring", Frame___tostring},
  {NULL, NULL}
};


static int luasrc_Frame (lua_State *L) {
  Frame *pFrame = new LFrame(luaL_optpanel(L, 1, VGui_GetClientLuaRootPanel()), luaL_optstring(L, 2, NULL), luaL_optboolean(L, 3, true), L);
  lua_pushframe(L, pFrame);
  return 1;
}


static const luaL_Reg Frame_funcs[] = {
  {"Frame", luasrc_Frame},
  {NULL, NULL}
};


/*
** Open Frame object
*/
LUALIB_API int luaopen_vgui_Frame(lua_State *L) {
  luaL_newmetatable(L, "Frame");
  luaL_register(L, NULL, Framemeta);
  lua_pushstring(L, "panel");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "panel" */
  luaL_register(L, "vgui", Frame_funcs);
  lua_pop(L, 2);
  return 1;
}