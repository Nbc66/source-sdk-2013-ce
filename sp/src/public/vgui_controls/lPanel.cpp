//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#define lpanel_cpp

#include "cbase.h"
#include <vgui_controls/Panel.h>
#include "c_vguiscreen.h"
#include "iclientmode.h"
#include "ienginevgui.h"
#include <vgui/IVGui.h>
#include "panelmetaclassmgr.h"
#include <vgui_controls/PHandle.h>
#include "luamanager.h"
#include "vgui_int.h"
#include "lPanel.h"
#include <scripted_controls/lPanel.h>
#include "lColor.h"

using namespace vgui;


/*
** access functions (stack -> C)
*/


LUA_API lua_Panel *(lua_topanel) (lua_State *L, int idx) {
  PHandle *phPanel = dynamic_cast<PHandle *>((PHandle *)lua_touserdata(L, idx));
  if (phPanel == NULL)
    return NULL;
  return (lua_Panel *)phPanel->Get();
}



/*
** push functions (C -> stack)
*/


LUA_API void (lua_pushpanel) (lua_State *L, Panel *pPanel) {
  LPanel *plPanel = dynamic_cast<LPanel *>(pPanel);
  if (plPanel)
    ++plPanel->m_nRefCount;
  PHandle *phPanel = (PHandle *)lua_newuserdata(L, sizeof(PHandle));
  phPanel->Set(pPanel);
  luaL_getmetatable(L, "Panel");
  lua_setmetatable(L, -2);
}


LUA_API void (lua_pushpanel) (lua_State *L, VPANEL panel) {
  PHandle *phPanel = (PHandle *)lua_newuserdata(L, sizeof(PHandle));
  phPanel->Set(ivgui()->PanelToHandle(panel));
  luaL_getmetatable(L, "Panel");
  lua_setmetatable(L, -2);
}


LUALIB_API lua_Panel *(luaL_checkpanel) (lua_State *L, int narg) {
  lua_Panel *d = lua_topanel(L, narg);
  if (d == NULL)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "Panel expected, got INVALID_PANEL");
  return d;
}


LUALIB_API VPANEL (luaL_checkvpanel) (lua_State *L, int narg) {
  lua_Panel *d = lua_topanel(L, narg);
  if (d == NULL)  /* avoid extra test when d is not 0 */
    luaL_argerror(L, narg, "Panel expected, got INVALID_PANEL");
  PHandle hPanel;
  hPanel.Set(d);
  return ivgui()->HandleToPanel(hPanel.m_iPanelID);
}


LUALIB_API lua_Panel *(luaL_optpanel) (lua_State *L, int narg,
                                                   Panel *def) {
  return luaL_opt(L, luaL_checkpanel, narg, def);
}


static int Panel_AddKeyBinding (lua_State *L) {
  luaL_checkpanel(L, 1)->AddKeyBinding(luaL_checkstring(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int Panel_AddActionSignalTarget (lua_State *L) {
  luaL_checkpanel(L, 1)->AddActionSignalTarget(luaL_checkpanel(L, 2));
  return 0;
}

static int Panel_CanStartDragging (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->CanStartDragging(luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5)));
  return 1;
}

static int Panel_ChainToAnimationMap (lua_State *L) {
  luaL_checkpanel(L, 1)->ChainToAnimationMap();
  return 0;
}

static int Panel_ChainToMap (lua_State *L) {
  luaL_checkpanel(L, 1)->ChainToMap();
  return 0;
}

static int Panel_DeletePanel (lua_State *L) {
  luaL_checkpanel(L, 1)->DeletePanel();
  return 0;
}

static int Panel_DisableMouseInputForThisPanel (lua_State *L) {
  luaL_checkpanel(L, 1)->DisableMouseInputForThisPanel(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_DrawBox (lua_State *L) {
  luaL_checkpanel(L, 1)->DrawBox(luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkcolor(L, 6), luaL_checknumber(L, 7), luaL_optboolean(L, 8, 0));
  return 0;
}

static int Panel_DrawBoxFade (lua_State *L) {
  luaL_checkpanel(L, 1)->DrawBoxFade(luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkcolor(L, 6), luaL_checknumber(L, 7), luaL_checkint(L, 8), luaL_checkint(L, 9), luaL_checkboolean(L, 10), luaL_optboolean(L, 11, 0));
  return 0;
}

static int Panel_DrawHollowBox (lua_State *L) {
  luaL_checkpanel(L, 1)->DrawHollowBox(luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkcolor(L, 6), luaL_checknumber(L, 7));
  return 0;
}

static int Panel_DrawTexturedBox (lua_State *L) {
  luaL_checkpanel(L, 1)->DrawTexturedBox(luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkcolor(L, 6), luaL_checknumber(L, 7));
  return 0;
}

static int Panel_EditKeyBindings (lua_State *L) {
  luaL_checkpanel(L, 1)->EditKeyBindings();
  return 0;
}

static int Panel_FillRectSkippingPanel (lua_State *L) {
  luaL_checkpanel(L, 1)->FillRectSkippingPanel(luaL_checkcolor(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkint(L, 6), luaL_checkpanel(L, 7));
  return 0;
}

static int Panel_FindChildByName (lua_State *L) {
  lua_pushpanel(L, luaL_checkpanel(L, 1)->FindChildByName(luaL_checkstring(L, 2), luaL_optboolean(L, 3, 0)));
  return 1;
}

static int Panel_FindChildIndexByName (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->FindChildIndexByName(luaL_checkstring(L, 2)));
  return 1;
}

static int Panel_FindSiblingByName (lua_State *L) {
  lua_pushpanel(L, luaL_checkpanel(L, 1)->FindSiblingByName(luaL_checkstring(L, 2)));
  return 1;
}

static int Panel_GetAlpha (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->GetAlpha());
  return 1;
}

static int Panel_GetBgColor (lua_State *L) {
  lua_pushcolor(L, luaL_checkpanel(L, 1)->GetBgColor());
  return 1;
}

static int Panel_GetBounds (lua_State *L) {
  int x, y, wide, tall;
  luaL_checkpanel(L, 1)->GetBounds(x, y, wide, tall);
  lua_pushinteger(L, x);
  lua_pushinteger(L, y);
  lua_pushinteger(L, wide);
  lua_pushinteger(L, tall);
  return 4;
}

static int Panel_GetChild (lua_State *L) {
  lua_pushpanel(L, luaL_checkpanel(L, 1)->GetChild(luaL_checkint(L, 2)));
  return 1;
}

static int Panel_GetChildCount (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->GetChildCount());
  return 1;
}

static int Panel_GetClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkpanel(L, 1)->GetClassName());
  return 1;
}

static int Panel_GetClipRect (lua_State *L) {
  int x0, y0, x1, y1;
  luaL_checkpanel(L, 1)->GetClipRect(x0, y0, x1, y1);
  lua_pushinteger(L, x0);
  lua_pushinteger(L, y0);
  lua_pushinteger(L, x1);
  lua_pushinteger(L, y1);
  return 4;
}

static int Panel_GetCornerTextureSize (lua_State *L) {
  int w, h;
  luaL_checkpanel(L, 1)->GetCornerTextureSize(w, h);
  lua_pushinteger(L, w);
  lua_pushinteger(L, h);
  return 2;
}

static int Panel_GetDescription (lua_State *L) {
  lua_pushstring(L, luaL_checkpanel(L, 1)->GetDescription());
  return 1;
}

static int Panel_GetDragFrameColor (lua_State *L) {
  lua_pushcolor(L, luaL_checkpanel(L, 1)->GetDragFrameColor());
  return 1;
}

static int Panel_GetDragPanel (lua_State *L) {
  lua_pushpanel(L, luaL_checkpanel(L, 1)->GetDragPanel());
  return 1;
}

static int Panel_GetDragStartTolerance (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->GetDragStartTolerance());
  return 1;
}

static int Panel_GetDropFrameColor (lua_State *L) {
  lua_pushcolor(L, luaL_checkpanel(L, 1)->GetDropFrameColor());
  return 1;
}

static int Panel_GetFgColor (lua_State *L) {
  lua_pushcolor(L, luaL_checkpanel(L, 1)->GetFgColor());
  return 1;
}

static int Panel_GetInset (lua_State *L) {
  int left, top, right, bottom;
  luaL_checkpanel(L, 1)->GetInset(left, top, right, bottom);
  lua_pushinteger(L, left);
  lua_pushinteger(L, top);
  lua_pushinteger(L, right);
  lua_pushinteger(L, bottom);
  return 4;
}

static int Panel_GetKeyBindingsFile (lua_State *L) {
  lua_pushstring(L, luaL_checkpanel(L, 1)->GetKeyBindingsFile());
  return 1;
}

static int Panel_GetKeyBindingsFilePathID (lua_State *L) {
  lua_pushstring(L, luaL_checkpanel(L, 1)->GetKeyBindingsFilePathID());
  return 1;
}

static int Panel_GetKeyMappingCount (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->GetKeyMappingCount());
  return 1;
}

static int Panel_GetMinimumSize (lua_State *L) {
  int wide, tall;
  luaL_checkpanel(L, 1)->GetMinimumSize(wide, tall);
  lua_pushinteger(L, wide);
  lua_pushinteger(L, tall);
  return 2;
}

static int Panel_GetModuleName (lua_State *L) {
  lua_pushstring(L, luaL_checkpanel(L, 1)->GetModuleName());
  return 1;
}

static int Panel_GetName (lua_State *L) {
  lua_pushstring(L, luaL_checkpanel(L, 1)->GetName());
  return 1;
}

static int Panel_GetPaintBackgroundType (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->GetPaintBackgroundType());
  return 1;
}

static int Panel_GetPaintSize (lua_State *L) {
  int wide, tall;
  luaL_checkpanel(L, 1)->GetPaintSize(wide, tall);
  lua_pushinteger(L, wide);
  lua_pushinteger(L, tall);
  return 2;
}

static int Panel_GetPanelBaseClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkpanel(L, 1)->GetPanelBaseClassName());
  return 1;
}

static int Panel_GetPanelClassName (lua_State *L) {
  lua_pushstring(L, luaL_checkpanel(L, 1)->GetPanelClassName());
  return 1;
}

static int Panel_GetParent (lua_State *L) {
  lua_pushpanel(L, luaL_checkpanel(L, 1)->GetParent());
  return 1;
}

static int Panel_GetPinCorner (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->GetPinCorner());
  return 1;
}

static int Panel_GetPinOffset (lua_State *L) {
  int dx, dy;
  luaL_checkpanel(L, 1)->GetPinOffset(dx, dy);
  lua_pushinteger(L, dx);
  lua_pushinteger(L, dy);
  return 2;
}

static int Panel_GetPos (lua_State *L) {
  int x, y;
  luaL_checkpanel(L, 1)->GetPos(x, y);
  lua_pushinteger(L, x);
  lua_pushinteger(L, y);
  return 2;
}

static int Panel_GetRefTable (lua_State *L) {
  LPanel *plPanel = dynamic_cast<LPanel *>(luaL_checkpanel(L, 1));
  if (plPanel) {
    if (plPanel->m_nTableReference == LUA_NOREF) {
      lua_newtable(L);
      plPanel->m_nTableReference = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_getref(L, plPanel->m_nTableReference);
  }
  else
    lua_pushnil(L);
  return 1;
}

static int Panel_GetResizeOffset (lua_State *L) {
  int dx, dy;
  luaL_checkpanel(L, 1)->GetResizeOffset(dx, dy);
  lua_pushinteger(L, dx);
  lua_pushinteger(L, dy);
  return 2;
}

static int Panel_GetSize (lua_State *L) {
  int wide, tall;
  luaL_checkpanel(L, 1)->GetSize(wide, tall);
  lua_pushinteger(L, wide);
  lua_pushinteger(L, tall);
  return 2;
}

static int Panel_GetTabPosition (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->GetTabPosition());
  return 1;
}

static int Panel_GetTall (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->GetTall());
  return 1;
}

static int Panel_GetVPanel (lua_State *L) {
  lua_pushpanel(L, luaL_checkpanel(L, 1)->GetVPanel());
  return 1;
}

static int Panel_GetVParent (lua_State *L) {
  lua_pushpanel(L, luaL_checkpanel(L, 1)->GetVParent());
  return 1;
}

static int Panel_GetWide (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->GetWide());
  return 1;
}

static int Panel_GetZPos (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->GetZPos());
  return 1;
}

static int Panel_HasFocus (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->HasFocus());
  return 1;
}

static int Panel_HasUserConfigSettings (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->HasUserConfigSettings());
  return 1;
}

static int Panel_InitPropertyConverters (lua_State *L) {
  luaL_checkpanel(L, 1)->InitPropertyConverters();
  return 0;
}

static int Panel_InvalidateLayout (lua_State *L) {
  luaL_checkpanel(L, 1)->InvalidateLayout(luaL_optboolean(L, 2, 0), luaL_optboolean(L, 3, 0));
  return 0;
}

static int Panel_IsAutoDeleteSet (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsAutoDeleteSet());
  return 1;
}

static int Panel_IsBeingDragged (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsBeingDragged());
  return 1;
}

static int Panel_IsBlockingDragChaining (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsBlockingDragChaining());
  return 1;
}

static int Panel_IsBottomAligned (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsBottomAligned());
  return 1;
}

static int Panel_IsBuildGroupEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsBuildGroupEnabled());
  return 1;
}

static int Panel_IsBuildModeActive (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsBuildModeActive());
  return 1;
}

static int Panel_IsBuildModeDeletable (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsBuildModeDeletable());
  return 1;
}

static int Panel_IsBuildModeEditable (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsBuildModeEditable());
  return 1;
}

static int Panel_IsChildOfModalSubTree (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsChildOfModalSubTree());
  return 1;
}

static int Panel_IsChildOfSurfaceModalPanel (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsChildOfSurfaceModalPanel());
  return 1;
}

static int Panel_IsCursorNone (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsCursorNone());
  return 1;
}

static int Panel_IsCursorOver (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsCursorOver());
  return 1;
}

static int Panel_IsDragEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsDragEnabled());
  return 1;
}

static int Panel_IsDropEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsDropEnabled());
  return 1;
}

static int Panel_IsEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsEnabled());
  return 1;
}

static int Panel_IsKeyBindingChainToParentAllowed (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsKeyBindingChainToParentAllowed());
  return 1;
}

static int Panel_IsKeyBoardInputEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsKeyBoardInputEnabled());
  return 1;
}

static int Panel_IsKeyOverridden (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsKeyOverridden((KeyCode)luaL_checkint(L, 2), luaL_checkint(L, 3)));
  return 1;
}

static int Panel_IsKeyRebound (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsKeyRebound((KeyCode)luaL_checkint(L, 2), luaL_checkint(L, 3)));
  return 1;
}

static int Panel_IsLayoutInvalid (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsLayoutInvalid());
  return 1;
}

static int Panel_IsMouseInputDisabledForThisPanel (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsMouseInputDisabledForThisPanel());
  return 1;
}

static int Panel_IsMouseInputEnabled (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsMouseInputEnabled());
  return 1;
}

static int Panel_IsOpaque (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsOpaque());
  return 1;
}

static int Panel_IsPopup (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsPopup());
  return 1;
}

static int Panel_IsProportional (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsProportional());
  return 1;
}

static int Panel_IsRightAligned (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsRightAligned());
  return 1;
}

static int Panel_IsStartDragWhenMouseExitsPanel (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsStartDragWhenMouseExitsPanel());
  return 1;
}

static int Panel_IsTriplePressAllowed (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsTriplePressAllowed());
  return 1;
}

static int Panel_IsValidKeyBindingsContext (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsValidKeyBindingsContext());
  return 1;
}

static int Panel_IsVisible (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsVisible());
  return 1;
}

static int Panel_IsWithin (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsWithin(luaL_checkint(L, 2), luaL_checkint(L, 3)));
  return 1;
}

static int Panel_IsWithinTraverse (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->IsWithinTraverse(luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkboolean(L, 4)));
  return 1;
}

static int Panel_KB_AddBoundKey (lua_State *L) {
  luaL_checkpanel(L, 1)->KB_AddBoundKey(luaL_checkstring(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int Panel_KB_ChainToMap (lua_State *L) {
  luaL_checkpanel(L, 1)->KB_ChainToMap();
  return 0;
}

static int Panel_KeyCodeToString (lua_State *L) {
  lua_pushstring(L, luaL_checkpanel(L, 1)->KeyCodeToString((KeyCode)luaL_checkint(L, 2)));
  return 1;
}

static int Panel_LocalToScreen (lua_State *L) {
  int x, y;
  luaL_checkpanel(L, 1)->LocalToScreen(x, y);
  lua_pushinteger(L, x);
  lua_pushinteger(L, y);
  return 2;
}

static int Panel_MakePopup (lua_State *L) {
  luaL_checkpanel(L, 1)->MakePopup(luaL_optboolean(L, 2, 1), luaL_optboolean(L, 3, 0));
  return 0;
}

static int Panel_MakeReadyForUse (lua_State *L) {
  luaL_checkpanel(L, 1)->MakeReadyForUse();
  return 0;
}

static int Panel_MarkForDeletion (lua_State *L) {
  luaL_checkpanel(L, 1)->MarkForDeletion();
  return 0;
}

static int Panel_MoveToFront (lua_State *L) {
  luaL_checkpanel(L, 1)->MoveToFront();
  return 0;
}

static int Panel_OnCommand (lua_State *L) {
  luaL_checkpanel(L, 1)->OnCommand(luaL_checkstring(L, 2));
  return 0;
}

static int Panel_OnCursorEntered (lua_State *L) {
  luaL_checkpanel(L, 1)->OnCursorEntered();
  return 0;
}

static int Panel_OnCursorExited (lua_State *L) {
  luaL_checkpanel(L, 1)->OnCursorExited();
  return 0;
}

static int Panel_OnCursorMoved (lua_State *L) {
  luaL_checkpanel(L, 1)->OnCursorMoved(luaL_checkint(L, 2), luaL_checkint(L, 3));
  return 0;
}

static int Panel_OnDelete (lua_State *L) {
  luaL_checkpanel(L, 1)->OnDelete();
  return 0;
}

static int Panel_OnDraggablePanelPaint (lua_State *L) {
  luaL_checkpanel(L, 1)->OnDraggablePanelPaint();
  return 0;
}

static int Panel_OnKeyCodePressed (lua_State *L) {
  luaL_checkpanel(L, 1)->OnKeyCodePressed((KeyCode)luaL_checkint(L, 2));
  return 0;
}

static int Panel_OnKeyCodeTyped (lua_State *L) {
  luaL_checkpanel(L, 1)->OnKeyCodeTyped((KeyCode)luaL_checkint(L, 2));
  return 0;
}

static int Panel_OnKeyFocusTicked (lua_State *L) {
  luaL_checkpanel(L, 1)->OnKeyFocusTicked();
  return 0;
}

static int Panel_OnKillFocus (lua_State *L) {
  luaL_checkpanel(L, 1)->OnKillFocus();
  return 0;
}

static int Panel_OnMouseCaptureLost (lua_State *L) {
  luaL_checkpanel(L, 1)->OnMouseCaptureLost();
  return 0;
}

static int Panel_OnMouseDoublePressed (lua_State *L) {
  luaL_checkpanel(L, 1)->OnMouseDoublePressed((MouseCode)luaL_checkint(L, 2));
  return 0;
}

static int Panel_OnMouseFocusTicked (lua_State *L) {
  luaL_checkpanel(L, 1)->OnMouseFocusTicked();
  return 0;
}

static int Panel_OnMousePressed (lua_State *L) {
  luaL_checkpanel(L, 1)->OnMousePressed((MouseCode)luaL_checkint(L, 2));
  return 0;
}

static int Panel_OnMouseReleased (lua_State *L) {
  luaL_checkpanel(L, 1)->OnMouseReleased((MouseCode)luaL_checkint(L, 2));
  return 0;
}

static int Panel_OnMouseTriplePressed (lua_State *L) {
  luaL_checkpanel(L, 1)->OnMouseTriplePressed((MouseCode)luaL_checkint(L, 2));
  return 0;
}

static int Panel_OnMouseWheeled (lua_State *L) {
  luaL_checkpanel(L, 1)->OnMouseWheeled(luaL_checkint(L, 2));
  return 0;
}

static int Panel_OnMove (lua_State *L) {
  luaL_checkpanel(L, 1)->OnMove();
  return 0;
}

static int Panel_OnSetFocus (lua_State *L) {
  luaL_checkpanel(L, 1)->OnSetFocus();
  return 0;
}

static int Panel_OnSizeChanged (lua_State *L) {
  luaL_checkpanel(L, 1)->OnSizeChanged(luaL_checkint(L, 2), luaL_checkint(L, 3));
  return 0;
}

static int Panel_OnThink (lua_State *L) {
  luaL_checkpanel(L, 1)->OnThink();
  return 0;
}

static int Panel_OnTick (lua_State *L) {
  luaL_checkpanel(L, 1)->OnTick();
  return 0;
}

static int Panel_Paint (lua_State *L) {
  luaL_checkpanel(L, 1)->Paint();
  return 0;
}

static int Panel_PaintBackground (lua_State *L) {
  luaL_checkpanel(L, 1)->PaintBackground();
  return 0;
}

static int Panel_PaintBorder (lua_State *L) {
  luaL_checkpanel(L, 1)->PaintBorder();
  return 0;
}

static int Panel_PaintBuildOverlay (lua_State *L) {
  luaL_checkpanel(L, 1)->PaintBuildOverlay();
  return 0;
}

static int Panel_ParentLocalToScreen (lua_State *L) {
  int x, y;
  luaL_checkpanel(L, 1)->ParentLocalToScreen(x, y);
  lua_pushinteger(L, x);
  lua_pushinteger(L, y);
  return 2;
}

static int Panel_PerformLayout (lua_State *L) {
  luaL_checkpanel(L, 1)->PerformLayout();
  return 0;
}

static int Panel_PostChildPaint (lua_State *L) {
  luaL_checkpanel(L, 1)->PostChildPaint();
  return 0;
}

static int Panel_ReloadKeyBindings (lua_State *L) {
  luaL_checkpanel(L, 1)->ReloadKeyBindings();
  return 0;
}

static int Panel_RemoveActionSignalTarget (lua_State *L) {
  luaL_checkpanel(L, 1)->RemoveActionSignalTarget(luaL_checkpanel(L, 2));
  return 0;
}

static int Panel_RemoveAllKeyBindings (lua_State *L) {
  luaL_checkpanel(L, 1)->RemoveAllKeyBindings();
  return 0;
}

static int Panel_Repaint (lua_State *L) {
  luaL_checkpanel(L, 1)->Repaint();
  return 0;
}

static int Panel_RequestFocus (lua_State *L) {
  luaL_checkpanel(L, 1)->RequestFocus(luaL_optint(L, 2, 0));
  return 0;
}

static int Panel_RevertKeyBindingsToDefault (lua_State *L) {
  luaL_checkpanel(L, 1)->RevertKeyBindingsToDefault();
  return 0;
}

static int Panel_ScreenToLocal (lua_State *L) {
  int x, y;
  luaL_checkpanel(L, 1)->ScreenToLocal(x, y);
  lua_pushinteger(L, x);
  lua_pushinteger(L, y);
  return 2;
}

static int Panel_SetAllowKeyBindingChainToParent (lua_State *L) {
  luaL_checkpanel(L, 1)->SetAllowKeyBindingChainToParent(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetAlpha (lua_State *L) {
  luaL_checkpanel(L, 1)->SetAlpha(luaL_checkint(L, 2));
  return 0;
}

static int Panel_SetAutoDelete (lua_State *L) {
  luaL_checkpanel(L, 1)->SetAutoDelete(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetAutoResize (lua_State *L) {
  luaL_checkpanel(L, 1)->SetAutoResize((Panel::PinCorner_e)luaL_checkint(L, 2), (Panel::AutoResize_e)luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkint(L, 6), luaL_checkint(L, 7));
  return 0;
}

static int Panel_SetBgColor (lua_State *L) {
  luaL_checkpanel(L, 1)->SetBgColor(luaL_checkcolor(L, 2));
  return 0;
}

static int Panel_SetBlockDragChaining (lua_State *L) {
  luaL_checkpanel(L, 1)->SetBlockDragChaining(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetBounds (lua_State *L) {
  luaL_checkpanel(L, 1)->SetBounds(luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5));
  return 0;
}

static int Panel_SetBuildModeDeletable (lua_State *L) {
  luaL_checkpanel(L, 1)->SetBuildModeDeletable(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetBuildModeEditable (lua_State *L) {
  luaL_checkpanel(L, 1)->SetBuildModeEditable(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetDragEnabled (lua_State *L) {
  luaL_checkpanel(L, 1)->SetDragEnabled(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetDragSTartTolerance (lua_State *L) {
  luaL_checkpanel(L, 1)->SetDragSTartTolerance(luaL_checkint(L, 2));
  return 0;
}

static int Panel_SetDropEnabled (lua_State *L) {
  luaL_checkpanel(L, 1)->SetDropEnabled(luaL_checkboolean(L, 2), luaL_optnumber(L, 3, 0.0f));
  return 0;
}

static int Panel_SetEnabled (lua_State *L) {
  luaL_checkpanel(L, 1)->SetEnabled(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetFgColor (lua_State *L) {
  luaL_checkpanel(L, 1)->SetFgColor(luaL_checkcolor(L, 2));
  return 0;
}

static int Panel_SetKeyBoardInputEnabled (lua_State *L) {
  luaL_checkpanel(L, 1)->SetKeyBoardInputEnabled(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetMinimumSize (lua_State *L) {
  luaL_checkpanel(L, 1)->SetMinimumSize(luaL_checkint(L, 2), luaL_checkint(L, 3));
  return 0;
}

static int Panel_SetMouseInputEnabled (lua_State *L) {
  luaL_checkpanel(L, 1)->SetMouseInputEnabled(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetName (lua_State *L) {
  luaL_checkpanel(L, 1)->SetName(luaL_checkstring(L, 2));
  return 0;
}

static int Panel_SetPaintBackgroundEnabled (lua_State *L) {
  luaL_checkpanel(L, 1)->SetPaintBackgroundEnabled(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetPaintBackgroundType (lua_State *L) {
  luaL_checkpanel(L, 1)->SetPaintBackgroundType(luaL_checkint(L, 2));
  return 0;
}

static int Panel_SetPaintBorderEnabled (lua_State *L) {
  luaL_checkpanel(L, 1)->SetPaintBorderEnabled(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetPaintEnabled (lua_State *L) {
  luaL_checkpanel(L, 1)->SetPaintEnabled(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetParent (lua_State *L) {
  luaL_checkpanel(L, 1)->SetParent(luaL_checkpanel(L, 2));
  return 0;
}

static int Panel_SetPinCorner (lua_State *L) {
  luaL_checkpanel(L, 1)->SetPinCorner((Panel::PinCorner_e)luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int Panel_SetPos (lua_State *L) {
  luaL_checkpanel(L, 1)->SetPos(luaL_checkint(L, 2), luaL_checkint(L, 3));
  return 0;
}

static int Panel_SetPostChildPaintEnabled (lua_State *L) {
  luaL_checkpanel(L, 1)->SetPostChildPaintEnabled(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetProportional (lua_State *L) {
  luaL_checkpanel(L, 1)->SetProportional(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetScheme (lua_State *L) {
  luaL_checkpanel(L, 1)->SetScheme(luaL_checkstring(L, 2));
  return 0;
}

static int Panel_SetSilentMode (lua_State *L) {
  luaL_checkpanel(L, 1)->SetSilentMode(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetSize (lua_State *L) {
  luaL_checkpanel(L, 1)->SetSize(luaL_checkint(L, 2), luaL_checkint(L, 3));
  return 0;
}

static int Panel_SetSkipChildDuringPainting (lua_State *L) {
  luaL_checkpanel(L, 1)->SetSkipChildDuringPainting(luaL_checkpanel(L, 2));
  return 0;
}

static int Panel_SetStartDragWhenMouseExitsPanel (lua_State *L) {
  luaL_checkpanel(L, 1)->SetStartDragWhenMouseExitsPanel(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetTabPosition (lua_State *L) {
  luaL_checkpanel(L, 1)->SetTabPosition(luaL_checkint(L, 2));
  return 0;
}

static int Panel_SetTall (lua_State *L) {
  luaL_checkpanel(L, 1)->SetTall(luaL_checkint(L, 2));
  return 0;
}

static int Panel_SetTriplePressAllowed (lua_State *L) {
  luaL_checkpanel(L, 1)->SetTriplePressAllowed(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetVisible (lua_State *L) {
  luaL_checkpanel(L, 1)->SetVisible(luaL_checkboolean(L, 2));
  return 0;
}

static int Panel_SetWide (lua_State *L) {
  luaL_checkpanel(L, 1)->SetWide(luaL_checkint(L, 2));
  return 0;
}

static int Panel_SetZPos (lua_State *L) {
  luaL_checkpanel(L, 1)->SetZPos(luaL_checkint(L, 2));
  return 0;
}

static int Panel_ShouldHandleInputMessage (lua_State *L) {
  lua_pushboolean(L, luaL_checkpanel(L, 1)->ShouldHandleInputMessage());
  return 1;
}

static int Panel_StringToKeyCode (lua_State *L) {
  lua_pushinteger(L, luaL_checkpanel(L, 1)->StringToKeyCode(luaL_checkstring(L, 2)));
  return 1;
}

static int Panel___index (lua_State *L) {
  Panel *pPanel = lua_topanel(L, 1);
  if (pPanel == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
	lua_pushfstring(L, "%s:%d: attempt to index an INVALID_PANEL", ar2.short_src, ar1.currentline);
	return lua_error(L);
  }
  LPanel *plPanel = dynamic_cast<LPanel *>(pPanel);
  if (plPanel && plPanel->m_nTableReference != LUA_NOREF) {
    lua_getref(L, plPanel->m_nTableReference);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1)) {
      lua_pop(L, 2);
      lua_getmetatable(L, 1);
      lua_pushvalue(L, 2);
      lua_gettable(L, -2);
    }
  } else {
    lua_getmetatable(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
  }
  return 1;
}

static int Panel___newindex (lua_State *L) {
  Panel *pPanel = lua_topanel(L, 1);
  if (pPanel == NULL) {  /* avoid extra test when d is not 0 */
    lua_Debug ar1;
    lua_getstack(L, 1, &ar1);
    lua_getinfo(L, "fl", &ar1);
    lua_Debug ar2;
    lua_getinfo(L, ">S", &ar2);
    lua_pushfstring(L, "%s:%d: attempt to index an INVALID_PANEL", ar2.short_src, ar1.currentline);
    return lua_error(L);
  }
  LPanel *plPanel = dynamic_cast<LPanel *>(pPanel);
  if (plPanel) {
    if (plPanel->m_nTableReference == LUA_NOREF) {
      lua_newtable(L);
      plPanel->m_nTableReference = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_getref(L, plPanel->m_nTableReference);
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

static int Panel___gc (lua_State *L) {
  LPanel *plPanel = dynamic_cast<LPanel *>(lua_topanel(L, 1));
  if (plPanel) {
    --plPanel->m_nRefCount;
	if (plPanel->m_nRefCount <= 0) {
      delete plPanel;
    }
  }
  return 0;
}

static int Panel___eq (lua_State *L) {
  lua_pushboolean(L, lua_topanel(L, 1) == lua_topanel(L, 2));
  return 1;
}

static int Panel___tostring (lua_State *L) {
  Panel *pPanel = lua_topanel(L, 1);
  if (pPanel == NULL)
    lua_pushstring(L, "INVALID_PANEL");
  else {
    const char *pName = pPanel->GetName();
    if (Q_strcmp(pName, "") == 0)
      pName = "(no name)";
    lua_pushfstring(L, "Panel: \"%s\"", pName);
  }
  return 1;
}


static const luaL_Reg Panelmeta[] = {
  {"AddKeyBinding", Panel_AddKeyBinding},
  {"AddActionSignalTarget", Panel_AddActionSignalTarget},
  {"CanStartDragging", Panel_CanStartDragging},
  {"ChainToAnimationMap", Panel_ChainToAnimationMap},
  {"ChainToMap", Panel_ChainToMap},
  {"DeletePanel", Panel_DeletePanel},
  {"DisableMouseInputForThisPanel", Panel_DisableMouseInputForThisPanel},
  {"DrawBox", Panel_DrawBox},
  {"DrawBoxFade", Panel_DrawBoxFade},
  {"DrawHollowBox", Panel_DrawHollowBox},
  {"DrawTexturedBox", Panel_DrawTexturedBox},
  {"EditKeyBindings", Panel_EditKeyBindings},
  {"FillRectSkippingPanel", Panel_FillRectSkippingPanel},
  {"FindChildByName", Panel_FindChildByName},
  {"FindChildIndexByName", Panel_FindChildIndexByName},
  {"FindSiblingByName", Panel_FindSiblingByName},
  {"GetAlpha", Panel_GetAlpha},
  {"GetBgColor", Panel_GetBgColor},
  {"GetBounds", Panel_GetBounds},
  {"GetChild", Panel_GetChild},
  {"GetChildCount", Panel_GetChildCount},
  {"GetClassName", Panel_GetClassName},
  {"GetClipRect", Panel_GetClipRect},
  {"GetCornerTextureSize", Panel_GetCornerTextureSize},
  {"GetDescription", Panel_GetDescription},
  {"GetDragFrameColor", Panel_GetDragFrameColor},
  {"GetDragPanel", Panel_GetDragPanel},
  {"GetDragStartTolerance", Panel_GetDragStartTolerance},
  {"GetDropFrameColor", Panel_GetDropFrameColor},
  {"GetFgColor", Panel_GetFgColor},
  {"GetInset", Panel_GetInset},
  {"GetKeyBindingsFile", Panel_GetKeyBindingsFile},
  {"GetKeyBindingsFilePathID", Panel_GetKeyBindingsFilePathID},
  {"GetKeyMappingCount", Panel_GetKeyMappingCount},
  {"GetMinimumSize", Panel_GetMinimumSize},
  {"GetModuleName", Panel_GetModuleName},
  {"GetName", Panel_GetName},
  {"GetPaintBackgroundType", Panel_GetPaintBackgroundType},
  {"GetPaintSize", Panel_GetPaintSize},
  {"GetPanelBaseClassName", Panel_GetPanelBaseClassName},
  {"GetPanelClassName", Panel_GetPanelClassName},
  {"GetParent", Panel_GetParent},
  {"GetPinCorner", Panel_GetPinCorner},
  {"GetPinOffset", Panel_GetPinOffset},
  {"GetPos", Panel_GetPos},
  {"GetRefTable", Panel_GetRefTable},
  {"GetResizeOffset", Panel_GetResizeOffset},
  {"GetSize", Panel_GetSize},
  {"GetTabPosition", Panel_GetTabPosition},
  {"GetTall", Panel_GetTall},
  {"GetVPanel", Panel_GetVPanel},
  {"GetVParent", Panel_GetVParent},
  {"GetWide", Panel_GetWide},
  {"GetZPos", Panel_GetZPos},
  {"HasFocus", Panel_HasFocus},
  {"HasUserConfigSettings", Panel_HasUserConfigSettings},
  {"InitPropertyConverters", Panel_InitPropertyConverters},
  {"InvalidateLayout", Panel_InvalidateLayout},
  {"IsAutoDeleteSet", Panel_IsAutoDeleteSet},
  {"IsBeingDragged", Panel_IsBeingDragged},
  {"IsBlockingDragChaining", Panel_IsBlockingDragChaining},
  {"IsBottomAligned", Panel_IsBottomAligned},
  {"IsBuildGroupEnabled", Panel_IsBuildGroupEnabled},
  {"IsBuildModeActive", Panel_IsBuildModeActive},
  {"IsBuildModeDeletable", Panel_IsBuildModeDeletable},
  {"IsBuildModeEditable", Panel_IsBuildModeEditable},
  {"IsChildOfModalSubTree", Panel_IsChildOfModalSubTree},
  {"IsChildOfSurfaceModalPanel", Panel_IsChildOfSurfaceModalPanel},
  {"IsCursorNone", Panel_IsCursorNone},
  {"IsCursorOver", Panel_IsCursorOver},
  {"IsDragEnabled", Panel_IsDragEnabled},
  {"IsDropEnabled", Panel_IsDropEnabled},
  {"IsEnabled", Panel_IsEnabled},
  {"IsKeyBindingChainToParentAllowed", Panel_IsKeyBindingChainToParentAllowed},
  {"IsKeyBoardInputEnabled", Panel_IsKeyBoardInputEnabled},
  {"IsKeyOverridden", Panel_IsKeyOverridden},
  {"IsKeyRebound", Panel_IsKeyRebound},
  {"IsLayoutInvalid", Panel_IsLayoutInvalid},
  {"IsMouseInputDisabledForThisPanel", Panel_IsMouseInputDisabledForThisPanel},
  {"IsMouseInputEnabled", Panel_IsMouseInputEnabled},
  {"IsOpaque", Panel_IsOpaque},
  {"IsPopup", Panel_IsPopup},
  {"IsProportional", Panel_IsProportional},
  {"IsRightAligned", Panel_IsRightAligned},
  {"IsStartDragWhenMouseExitsPanel", Panel_IsStartDragWhenMouseExitsPanel},
  {"IsTriplePressAllowed", Panel_IsTriplePressAllowed},
  {"IsValidKeyBindingsContext", Panel_IsValidKeyBindingsContext},
  {"IsVisible", Panel_IsVisible},
  {"IsWithin", Panel_IsWithin},
  {"IsWithinTraverse", Panel_IsWithinTraverse},
  {"KB_AddBoundKey", Panel_KB_AddBoundKey},
  {"KB_ChainToMap", Panel_KB_ChainToMap},
  {"KeyCodeToString", Panel_KeyCodeToString},
  {"LocalToScreen", Panel_LocalToScreen},
  {"MakePopup", Panel_MakePopup},
  {"MakeReadyForUse", Panel_MakeReadyForUse},
  {"MarkForDeletion", Panel_MarkForDeletion},
  {"MoveToFront", Panel_MoveToFront},
  {"OnCommand", Panel_OnCommand},
  {"OnCursorEntered", Panel_OnCursorEntered},
  {"OnCursorExited", Panel_OnCursorExited},
  {"OnCursorMoved", Panel_OnCursorMoved},
  {"OnDelete", Panel_OnDelete},
  {"OnDraggablePanelPaint", Panel_OnDraggablePanelPaint},
  {"OnKeyCodePressed", Panel_OnKeyCodePressed},
  {"OnKeyCodeTyped", Panel_OnKeyCodeTyped},
  {"OnKeyFocusTicked", Panel_OnKeyFocusTicked},
  {"OnKillFocus", Panel_OnKillFocus},
  {"OnMouseCaptureLost", Panel_OnMouseCaptureLost},
  {"OnMouseDoublePressed", Panel_OnMouseDoublePressed},
  {"OnMouseFocusTicked", Panel_OnMouseFocusTicked},
  {"OnMousePressed", Panel_OnMousePressed},
  {"OnMouseReleased", Panel_OnMouseReleased},
  {"OnMouseTriplePressed", Panel_OnMouseTriplePressed},
  {"OnMouseWheeled", Panel_OnMouseWheeled},
  {"OnMove", Panel_OnMove},
  {"OnSetFocus", Panel_OnSetFocus},
  {"OnSizeChanged", Panel_OnSizeChanged},
  {"OnThink", Panel_OnThink},
  {"OnTick", Panel_OnTick},
  {"Paint", Panel_Paint},
  {"PaintBackground", Panel_PaintBackground},
  {"PaintBorder", Panel_PaintBorder},
  {"PaintBuildOverlay", Panel_PaintBuildOverlay},
  {"ParentLocalToScreen", Panel_ParentLocalToScreen},
  {"PerformLayout", Panel_PerformLayout},
  {"PostChildPaint", Panel_PostChildPaint},
  {"ReloadKeyBindings", Panel_ReloadKeyBindings},
  {"RemoveActionSignalTarget", Panel_RemoveActionSignalTarget},
  {"RemoveAllKeyBindings", Panel_RemoveAllKeyBindings},
  {"Repaint", Panel_Repaint},
  {"RequestFocus", Panel_RequestFocus},
  {"RevertKeyBindingsToDefault", Panel_RevertKeyBindingsToDefault},
  {"ScreenToLocal", Panel_ScreenToLocal},
  {"SetAllowKeyBindingChainToParent", Panel_SetAllowKeyBindingChainToParent},
  {"SetAlpha", Panel_SetAlpha},
  {"SetAutoDelete", Panel_SetAutoDelete},
  {"SetAutoResize", Panel_SetAutoResize},
  {"SetBgColor", Panel_SetBgColor},
  {"SetBlockDragChaining", Panel_SetBlockDragChaining},
  {"SetBounds", Panel_SetBounds},
  {"SetBuildModeDeletable", Panel_SetBuildModeDeletable},
  {"SetBuildModeEditable", Panel_SetBuildModeEditable},
  {"SetDragEnabled", Panel_SetDragEnabled},
  {"SetDragSTartTolerance", Panel_SetDragSTartTolerance},
  {"SetDropEnabled", Panel_SetDropEnabled},
  {"SetEnabled", Panel_SetEnabled},
  {"SetFgColor", Panel_SetFgColor},
  {"SetKeyBoardInputEnabled", Panel_SetKeyBoardInputEnabled},
  {"SetMinimumSize", Panel_SetMinimumSize},
  {"SetMouseInputEnabled", Panel_SetMouseInputEnabled},
  {"SetName", Panel_SetName},
  {"SetPaintBackgroundEnabled", Panel_SetPaintBackgroundEnabled},
  {"SetPaintBackgroundType", Panel_SetPaintBackgroundType},
  {"SetPaintBorderEnabled", Panel_SetPaintBorderEnabled},
  {"SetPaintEnabled", Panel_SetPaintEnabled},
  {"SetParent", Panel_SetParent},
  {"SetPinCorner", Panel_SetPinCorner},
  {"SetPos", Panel_SetPos},
  {"SetPostChildPaintEnabled", Panel_SetPostChildPaintEnabled},
  {"SetProportional", Panel_SetProportional},
  {"SetScheme", Panel_SetScheme},
  {"SetSilentMode", Panel_SetSilentMode},
  {"SetSize", Panel_SetSize},
  {"SetSkipChildDuringPainting", Panel_SetSkipChildDuringPainting},
  {"SetStartDragWhenMouseExitsPanel", Panel_SetStartDragWhenMouseExitsPanel},
  {"SetTabPosition", Panel_SetTabPosition},
  {"SetTall", Panel_SetTall},
  {"SetTriplePressAllowed", Panel_SetTriplePressAllowed},
  {"SetVisible", Panel_SetVisible},
  {"SetWide", Panel_SetWide},
  {"SetZPos", Panel_SetZPos},
  {"ShouldHandleInputMessage", Panel_ShouldHandleInputMessage},
  {"StringToKeyCode", Panel_StringToKeyCode},
  {"__index", Panel___index},
  {"__newindex", Panel___newindex},
  {"__gc", Panel___gc},
  {"__eq", Panel___eq},
  {"__tostring", Panel___tostring},
  {NULL, NULL}
};


static int luasrc_VGui_GetGameUIPanel (lua_State *L) {
  lua_pushpanel(L, VGui_GetGameUIPanel());
  return 1;
}

static int luasrc_VGui_GetClientLuaRootPanel (lua_State *L) {
  lua_pushpanel(L, VGui_GetClientLuaRootPanel());
  return 1;
}


static const luaL_Reg Panel_funcs[] = {
  {"VGui_GetGameUIPanel", luasrc_VGui_GetGameUIPanel},
  {"VGui_GetClientLuaRootPanel", luasrc_VGui_GetClientLuaRootPanel},
  {NULL, NULL}
};


/*
** Open Panel object
*/
LUALIB_API int luaopen_Panel (lua_State *L) {
  luaL_newmetatable(L, "Panel");
  luaL_register(L, NULL, Panelmeta);
  lua_pushstring(L, "panel");
  lua_setfield(L, -2, "__type");  /* metatable.__type = "panel" */
  luaL_register(L, "_G", Panel_funcs);
  lua_pop(L, 1);
  // Andrew; Don't be mislead, INVALID_PANEL is not NULL internally, but we
  // need a name other than NULL, because NULL has already been assigned as an
  // entity.
  lua_pushpanel(L, (Panel *)0);
  lua_setglobal(L, "INVALID_PANEL");  /* set global INVALID_PANEL */
  return 1;
}

