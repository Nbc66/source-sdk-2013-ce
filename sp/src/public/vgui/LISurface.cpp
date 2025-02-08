//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#define LISurface_cpp

#include "cbase.h"
#include "vgui/isurface.h"
#include "vgui/ILocalize.h"
#include "vgui_controls/Controls.h"
#include "luamanager.h"
#include "luasrclib.h"
#include "vgui/lvgui.h"
#include "vgui_controls/lPanel.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

using namespace vgui;



static int surface_AddBitmapFontFile (lua_State *L) {
  lua_pushboolean(L, surface()->AddBitmapFontFile(luaL_checkstring(L, 1)));
  return 1;
}

static int surface_AddCustomFontFile (lua_State *L) {
  lua_pushboolean(L, surface()->AddCustomFontFile(luaL_checkstring(L, 1), luaL_checkstring(L, 2)));
  return 1;
}

static int surface_AddPanel (lua_State *L) {
  surface()->AddPanel(luaL_checkvpanel(L, 1));
  return 0;
}

static int surface_ApplyChanges (lua_State *L) {
  surface()->ApplyChanges();
  return 0;
}

static int surface_BringToFront (lua_State *L) {
  surface()->BringToFront(luaL_checkvpanel(L, 1));
  return 0;
}

static int surface_CalculateMouseVisible (lua_State *L) {
  surface()->CalculateMouseVisible();
  return 0;
}

static int surface_ClearTemporaryFontCache (lua_State *L) {
  surface()->ClearTemporaryFontCache();
  return 0;
}

static int surface_CreateFont (lua_State *L) {
  lua_pushfont(L, surface()->CreateFont());
  return 1;
}

static int surface_CreateNewTextureID (lua_State *L) {
  lua_pushinteger(L, surface()->CreateNewTextureID(luaL_optboolean(L, 1, false)));
  return 1;
}

static int surface_CreatePopup (lua_State *L) {
  surface()->CreatePopup(luaL_checkvpanel(L, 1), luaL_checkboolean(L, 2), luaL_optboolean(L, 3, true), luaL_optboolean(L, 4, false), luaL_optboolean(L, 5, true), luaL_optboolean(L, 6, true));
  return 0;
}

static int surface_DrawFilledRect (lua_State *L) {
  surface()->DrawFilledRect(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int surface_DrawFilledRectFade (lua_State *L) {
  surface()->DrawFilledRectFade(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkint(L, 6), luaL_checkboolean(L, 7));
  return 0;
}

static int surface_DrawFlushText (lua_State *L) {
  surface()->DrawFlushText();
  return 0;
}

static int surface_DrawGetAlphaMultiplier (lua_State *L) {
  lua_pushnumber(L, surface()->DrawGetAlphaMultiplier());
  return 1;
}

static int surface_DrawGetTextPos (lua_State *L) {
  int x, y;
  surface()->DrawGetTextPos(x, y);
  lua_pushinteger(L, x);
  lua_pushinteger(L, y);
  return 2;
}

static int surface_DrawGetTextureFile (lua_State *L) {
  char * filename = "";
  lua_pushboolean(L, surface()->DrawGetTextureFile(luaL_checkint(L, 1), filename, luaL_checkint(L, 2)));
  lua_pushstring(L, filename);
  return 2;
}

static int surface_DrawGetTextureId (lua_State *L) {
  lua_pushinteger(L, surface()->DrawGetTextureId(luaL_checkstring(L, 1)));
  return 1;
}

static int surface_DrawGetTextureSize (lua_State *L) {
  int wide, tall;
  surface()->DrawGetTextureSize(luaL_checkint(L, 1), wide, tall);
  lua_pushinteger(L, wide);
  lua_pushinteger(L, tall);
  return 2;
}

static int surface_DrawLine (lua_State *L) {
  surface()->DrawLine(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int surface_DrawOutlinedCircle (lua_State *L) {
  surface()->DrawOutlinedCircle(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int surface_DrawOutlinedRect (lua_State *L) {
  surface()->DrawOutlinedRect(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int surface_DrawPrintText (lua_State *L) {
  const char *sz = luaL_checkstring(L, 1);
  int bufSize = (strlen( sz ) + 1 ) * sizeof(wchar_t);
  wchar_t *wbuf = static_cast<wchar_t *>( _alloca( bufSize ) );
  if ( wbuf )
  {
	  g_pVGuiLocalize->ConvertANSIToUnicode( sz, wbuf, bufSize);
	  surface()->DrawPrintText( wbuf, wcslen( wbuf ), (FontDrawType_t)luaL_optint(L, 3, FONT_DRAW_DEFAULT));
  }
  return 0;
}

static int surface_DrawSetAlphaMultiplier (lua_State *L) {
  surface()->DrawSetAlphaMultiplier(luaL_checknumber(L, 1));
  return 0;
}

static int surface_DrawSetColor (lua_State *L) {
  surface()->DrawSetColor(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int surface_DrawSetTextColor (lua_State *L) {
  surface()->DrawSetTextColor(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int surface_DrawSetTextFont (lua_State *L) {
  surface()->DrawSetTextFont(luaL_checkfont(L, 1));
  return 0;
}

static int surface_DrawSetTextPos (lua_State *L) {
  surface()->DrawSetTextPos(luaL_checkint(L, 1), luaL_checkint(L, 2));
  return 0;
}

static int surface_DrawSetTextScale (lua_State *L) {
  surface()->DrawSetTextScale(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
  return 0;
}

static int surface_DrawSetTexture (lua_State *L) {
  surface()->DrawSetTexture(luaL_checkint(L, 1));
  return 0;
}

static int surface_DrawSetTextureFile (lua_State *L) {
  surface()->DrawSetTextureFile(luaL_checkint(L, 1), luaL_checkstring(L, 2), luaL_checkint(L, 3), luaL_checkboolean(L, 4));
  return 0;
}

static int surface_DrawTexturedRect (lua_State *L) {
  surface()->DrawTexturedRect(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int surface_DrawTexturedSubRect (lua_State *L) {
  surface()->DrawTexturedSubRect(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checknumber(L, 5), luaL_checknumber(L, 6), luaL_checknumber(L, 7), luaL_checknumber(L, 8));
  return 0;
}

static int surface_EnableMouseCapture (lua_State *L) {
  surface()->EnableMouseCapture(luaL_checkvpanel(L, 1), luaL_checkboolean(L, 2));
  return 0;
}

static int surface_FlashWindow (lua_State *L) {
  surface()->FlashWindow(luaL_checkvpanel(L, 1), luaL_checkboolean(L, 2));
  return 0;
}

static int surface_GetAbsoluteWindowBounds (lua_State *L) {
  int x, y, wide, tall;
  surface()->GetAbsoluteWindowBounds(x, y, wide, tall);
  lua_pushinteger(L, x);
  lua_pushinteger(L, y);
  lua_pushinteger(L, wide);
  lua_pushinteger(L, tall);
  return 4;
}

static int surface_GetBitmapFontName (lua_State *L) {
  lua_pushstring(L, surface()->GetBitmapFontName(luaL_checkstring(L, 1)));
  return 1;
}

static int surface_GetCharABCwide (lua_State *L) {
  int a, b, c;
  surface()->GetCharABCwide(luaL_checkfont(L, 1), luaL_checkint(L, 2), a, b, c);
  lua_pushinteger(L, a);
  lua_pushinteger(L, b);
  lua_pushinteger(L, c);
  return 3;
}

static int surface_GetCharacterWidth (lua_State *L) {
  lua_pushinteger(L, surface()->GetCharacterWidth(luaL_checkfont(L, 1), luaL_checkint(L, 2)));
  return 1;
}

static int surface_GetEmbeddedPanel (lua_State *L) {
  lua_pushpanel(L, surface()->GetEmbeddedPanel());
  return 1;
}

static int surface_GetFontAscent (lua_State *L) {
  wchar_t wch[1];
  g_pVGuiLocalize->ConvertANSIToUnicode(luaL_checkstring(L, 2), wch, sizeof(wch));
  lua_pushinteger(L, surface()->GetFontAscent(luaL_checkfont(L, 1), wch[1]));
  return 1;
}

static int surface_GetFontTall (lua_State *L) {
  lua_pushinteger(L, surface()->GetFontTall(luaL_checkfont(L, 1)));
  return 1;
}

static int surface_GetModalPanel (lua_State *L) {
  lua_pushpanel(L, surface()->GetModalPanel());
  return 1;
}

static int surface_GetNotifyPanel (lua_State *L) {
  lua_pushpanel(L, surface()->GetNotifyPanel());
  return 1;
}

static int surface_GetPopup (lua_State *L) {
  lua_pushpanel(L, surface()->GetPopup(luaL_checkint(L, 1)));
  return 1;
}

static int surface_GetPopupCount (lua_State *L) {
  lua_pushinteger(L, surface()->GetPopupCount());
  return 1;
}

static int surface_GetProportionalBase (lua_State *L) {
  int width, height;
  surface()->GetProportionalBase(width, height);
  lua_pushinteger(L, width);
  lua_pushinteger(L, height);
  return 2;
}

static int surface_GetResolutionKey (lua_State *L) {
  lua_pushstring(L, surface()->GetResolutionKey());
  return 1;
}

static int surface_GetScreenSize (lua_State *L) {
  int wide, tall;
  surface()->GetScreenSize(wide, tall);
  lua_pushinteger(L, wide);
  lua_pushinteger(L, tall);
  return 2;
}

static int surface_GetTextSize (lua_State *L) {
  const char *sz = luaL_checkstring(L, 2);
  int wide = 0;
  int tall = 0;
  int bufSize = (strlen( sz ) + 1 ) * sizeof(wchar_t);
  wchar_t *wbuf = static_cast<wchar_t *>( _alloca( bufSize ) );
  if ( wbuf )
  {
	  surface()->GetTextSize(luaL_checkfont(L, 1), wbuf, wide, tall);
  }
  lua_pushinteger(L, wide);
  lua_pushinteger(L, tall);
  return 2;
}

static int surface_GetTitle (lua_State *L) {
  char szTitle[256];
  const wchar_t *wszTitle = surface()->GetTitle(luaL_checkvpanel(L, 1));
  g_pVGuiLocalize->ConvertUnicodeToANSI( wszTitle, szTitle, sizeof( szTitle ) );
  lua_pushstring(L, szTitle);
  return 1;
}

static int surface_GetTopmostPopup (lua_State *L) {
  lua_pushpanel(L, surface()->GetTopmostPopup());
  return 1;
}

static int surface_GetWorkspaceBounds (lua_State *L) {
  int x, y, wide, tall;
  surface()->GetWorkspaceBounds(x, y, wide, tall);
  lua_pushinteger(L, x);
  lua_pushinteger(L, y);
  lua_pushinteger(L, wide);
  lua_pushinteger(L, tall);
  return 4;
}

static int surface_GetZPos (lua_State *L) {
  lua_pushnumber(L, surface()->GetZPos());
  return 1;
}

static int surface_HasCursorPosFunctions (lua_State *L) {
  lua_pushboolean(L, surface()->HasCursorPosFunctions());
  return 1;
}

static int surface_HasFocus (lua_State *L) {
  lua_pushboolean(L, surface()->HasFocus());
  return 1;
}

static int surface_Invalidate (lua_State *L) {
  surface()->Invalidate(luaL_checkvpanel(L, 1));
  return 0;
}

static int surface_IsCursorLocked (lua_State *L) {
  lua_pushboolean(L, surface()->IsCursorLocked());
  return 1;
}

static int surface_IsCursorVisible (lua_State *L) {
  lua_pushboolean(L, surface()->IsCursorVisible());
  return 1;
}

static int surface_IsFontAdditive (lua_State *L) {
  lua_pushboolean(L, surface()->IsFontAdditive(luaL_checkfont(L, 1)));
  return 1;
}

static int surface_IsMinimized (lua_State *L) {
  lua_pushboolean(L, surface()->IsMinimized(luaL_checkvpanel(L, 1)));
  return 1;
}

static int surface_IsTextureIDValid (lua_State *L) {
  lua_pushboolean(L, surface()->IsTextureIDValid(luaL_checkint(L, 1)));
  return 1;
}

static int surface_IsWithin (lua_State *L) {
  lua_pushboolean(L, surface()->IsWithin(luaL_checkint(L, 1), luaL_checkint(L, 2)));
  return 1;
}

static int surface_LockCursor (lua_State *L) {
  surface()->LockCursor();
  return 0;
}

static int surface_MovePopupToBack (lua_State *L) {
  surface()->MovePopupToBack(luaL_checkvpanel(L, 1));
  return 0;
}

static int surface_MovePopupToFront (lua_State *L) {
  surface()->MovePopupToFront(luaL_checkvpanel(L, 1));
  return 0;
}

static int surface_NeedKBInput (lua_State *L) {
  lua_pushboolean(L, surface()->NeedKBInput());
  return 1;
}

static int surface_OnScreenSizeChanged (lua_State *L) {
  surface()->OnScreenSizeChanged(luaL_checkint(L, 1), luaL_checkint(L, 2));
  return 0;
}

static int surface_PaintTraverse (lua_State *L) {
  surface()->PaintTraverse(luaL_checkvpanel(L, 1));
  return 0;
}

static int surface_PaintTraverseEx (lua_State *L) {
  surface()->PaintTraverseEx(luaL_checkvpanel(L, 1), luaL_optboolean(L, 2, false));
  return 0;
}

static int surface_PlaySound (lua_State *L) {
  surface()->PlaySound(luaL_checkstring(L, 1));
  return 0;
}

static int surface_PopMakeCurrent (lua_State *L) {
  surface()->PopMakeCurrent(luaL_checkvpanel(L, 1));
  return 0;
}

static int surface_RunFrame (lua_State *L) {
  surface()->RunFrame();
  return 0;
}

static int surface_SetAllowHTMLJavaScript (lua_State *L) {
  surface()->SetAllowHTMLJavaScript(luaL_checkboolean(L, 1));
  return 0;
}

static int surface_SetBitmapFontName (lua_State *L) {
  surface()->SetBitmapFontName(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
  return 0;
}

static int surface_SetEmbeddedPanel (lua_State *L) {
  surface()->SetEmbeddedPanel(luaL_checkvpanel(L, 1));
  return 0;
}

static int surface_SetFontGlyphSet (lua_State *L) {
  lua_pushboolean(L, surface()->SetFontGlyphSet(luaL_checkfont(L, 1), luaL_checkstring(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkint(L, 5), luaL_checkint(L, 6), luaL_checkint(L, 7), luaL_optint(L, 8, 0), luaL_optint(L, 9, 0)));
  return 1;
}

static int surface_SetTranslateExtendedKeys (lua_State *L) {
  surface()->SetTranslateExtendedKeys(luaL_checkboolean(L, 1));
  return 0;
}

static int surface_SetWorkspaceInsets (lua_State *L) {
  surface()->SetWorkspaceInsets(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
  return 0;
}

static int surface_SupportsFeature (lua_State *L) {
  surface()->SupportsFeature((ISurface::SurfaceFeature_e)luaL_checkint(L, 1));
  return 0;
}

static int surface_SurfaceGetCursorPos (lua_State *L) {
  int x, y;
  surface()->SurfaceGetCursorPos(x, y);
  lua_pushinteger(L, x);
  lua_pushinteger(L, y);
  return 2;
}

static int surface_SurfaceSetCursorPos (lua_State *L) {
  surface()->SurfaceSetCursorPos(luaL_checkint(L, 1), luaL_checkint(L, 2));
  return 0;
}

static int surface_UnlockCursor (lua_State *L) {
  surface()->UnlockCursor();
  return 0;
}


static const luaL_Reg surfacelib[] = {
  {"AddBitmapFontFile",   surface_AddBitmapFontFile},
  {"AddCustomFontFile",   surface_AddCustomFontFile},
  {"AddPanel",   surface_AddPanel},
  {"ApplyChanges",   surface_ApplyChanges},
  {"BringToFront",   surface_BringToFront},
  {"CalculateMouseVisible",   surface_CalculateMouseVisible},
  {"ClearTemporaryFontCache",   surface_ClearTemporaryFontCache},
  {"CreateFont",   surface_CreateFont},
  {"CreateNewTextureID",   surface_CreateNewTextureID},
  {"CreatePopup",   surface_CreatePopup},
  {"DrawFilledRect",   surface_DrawFilledRect},
  {"DrawFilledRectFade",   surface_DrawFilledRectFade},
  {"DrawFlushText",   surface_DrawFlushText},
  {"DrawGetAlphaMultiplier",   surface_DrawGetAlphaMultiplier},
  {"DrawGetTextPos",   surface_DrawGetTextPos},
  {"DrawGetTextureFile",   surface_DrawGetTextureFile},
  {"DrawGetTextureId",   surface_DrawGetTextureId},
  {"DrawGetTextureSize",   surface_DrawGetTextureSize},
  {"DrawLine",   surface_DrawLine},
  {"DrawOutlinedCircle",   surface_DrawOutlinedCircle},
  {"DrawOutlinedRect",   surface_DrawOutlinedRect},
  {"DrawPrintText",   surface_DrawPrintText},
  {"DrawSetAlphaMultiplier",   surface_DrawSetAlphaMultiplier},
  {"DrawSetColor",   surface_DrawSetColor},
  {"DrawSetTextColor",   surface_DrawSetTextColor},
  {"DrawSetTextFont",   surface_DrawSetTextFont},
  {"DrawSetTextPos",   surface_DrawSetTextPos},
  {"DrawSetTextScale",   surface_DrawSetTextScale},
  {"DrawSetTexture",   surface_DrawSetTexture},
  {"DrawSetTextureFile",   surface_DrawSetTextureFile},
  {"DrawTexturedRect",   surface_DrawTexturedRect},
  {"DrawTexturedSubRect",   surface_DrawTexturedSubRect},
  {"EnableMouseCapture",   surface_EnableMouseCapture},
  {"FlashWindow",   surface_FlashWindow},
  {"GetAbsoluteWindowBounds",   surface_GetAbsoluteWindowBounds},
  {"GetBitmapFontName",   surface_GetBitmapFontName},
  {"GetCharABCwide",   surface_GetCharABCwide},
  {"GetCharacterWidth",   surface_GetCharacterWidth},
  {"GetEmbeddedPanel",   surface_GetEmbeddedPanel},
  {"GetFontAscent",   surface_GetFontAscent},
  {"GetFontTall",   surface_GetFontTall},
  {"GetModalPanel",   surface_GetModalPanel},
  {"GetNotifyPanel",   surface_GetNotifyPanel},
  {"GetPopup",   surface_GetPopup},
  {"GetPopupCount",   surface_GetPopupCount},
  {"GetProportionalBase",   surface_GetProportionalBase},
  {"GetResolutionKey",   surface_GetResolutionKey},
  {"GetScreenSize",   surface_GetScreenSize},
  {"GetTextSize",   surface_GetTextSize},
  {"GetTitle",   surface_GetTitle},
  {"GetTopmostPopup",   surface_GetTopmostPopup},
  {"GetWorkspaceBounds",   surface_GetWorkspaceBounds},
  {"GetZPos",   surface_GetZPos},
  {"HasCursorPosFunctions",   surface_HasCursorPosFunctions},
  {"HasFocus",   surface_HasFocus},
  {"Invalidate",   surface_Invalidate},
  {"IsCursorLocked",   surface_IsCursorLocked},
  {"IsCursorVisible",   surface_IsCursorVisible},
  {"IsFontAdditive",   surface_IsFontAdditive},
  {"IsMinimized",   surface_IsMinimized},
  {"IsTextureIDValid",   surface_IsTextureIDValid},
  {"IsWithin",   surface_IsWithin},
  {"LockCursor",   surface_LockCursor},
  {"MovePopupToBack",   surface_MovePopupToBack},
  {"MovePopupToFront",   surface_MovePopupToFront},
  {"NeedKBInput",   surface_NeedKBInput},
  {"OnScreenSizeChanged",   surface_OnScreenSizeChanged},
  {"PaintTraverse",   surface_PaintTraverse},
  {"PaintTraverseEx",   surface_PaintTraverseEx},
  {"PlaySound",   surface_PlaySound},
  {"PopMakeCurrent",   surface_PopMakeCurrent},
  {"RunFrame",   surface_RunFrame},
  {"SetAllowHTMLJavaScript",   surface_SetAllowHTMLJavaScript},
  {"SetBitmapFontName",   surface_SetBitmapFontName},
  {"SetEmbeddedPanel",   surface_SetEmbeddedPanel},
  {"SetFontGlyphSet",   surface_SetFontGlyphSet},
  {"SetTranslateExtendedKeys",   surface_SetTranslateExtendedKeys},
  {"SetWorkspaceInsets",   surface_SetWorkspaceInsets},
  {"SupportsFeature",   surface_SupportsFeature},
  {"SurfaceGetCursorPos",   surface_SurfaceGetCursorPos},
  {"SurfaceSetCursorPos",   surface_SurfaceSetCursorPos},
  {"UnlockCursor",   surface_UnlockCursor},
  {NULL, NULL}
};


/*
** Open surface library
*/
LUALIB_API int luaopen_surface (lua_State *L) {
  luaL_register(L, LUA_SURFACELIBNAME, surfacelib);
  return 1;
}


/*
** Open FONTFLAG library
*/
LUALIB_API int luaopen_FONTFLAG (lua_State *L) {
  BEGIN_LUA_SET_ENUM_LIB(L, LUA_FONTFLAGLIBNAME);
    lua_pushenum(L, vgui::ISurface::FONTFLAG_NONE, "NONE");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_ITALIC, "ITALIC");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_UNDERLINE, "UNDERLINE");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_STRIKEOUT, "STRIKEOUT");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_SYMBOL, "SYMBOL");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_ANTIALIAS, "ANTIALIAS");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_GAUSSIANBLUR, "GAUSSIANBLUR");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_ROTARY, "ROTARY");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_DROPSHADOW, "DROPSHADOW");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_ADDITIVE, "ADDITIVE");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_OUTLINE, "OUTLINE");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_CUSTOM, "CUSTOM");
    lua_pushenum(L, vgui::ISurface::FONTFLAG_BITMAP, "BITMAP");
  END_LUA_SET_ENUM_LIB(L);
  return 0;
}

