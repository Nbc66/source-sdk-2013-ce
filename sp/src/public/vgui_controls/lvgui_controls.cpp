//====== Copyright © 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================
#define lvgui_controls_cpp

#include "cbase.h"
#include "lua.hpp"
#include "lControls.h"
#include "scripted_controls/lPanel.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


/*
** Open vgui library
*/
LUALIB_API int luaopen_vgui (lua_State *L) {
  luaopen_vgui_Button(L);
  luaopen_vgui_EditablePanel(L);
  luaopen_vgui_Panel(L);
  luaopen_vgui_CheckButton(L);
  luaopen_vgui_Frame(L);
  luaopen_vgui_PropertyDialog(L);
  luaopen_vgui_PropertyPage(L);
  return 0;
}

