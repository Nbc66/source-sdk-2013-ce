//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#ifndef LCONTROLS_H
#define LCONTROLS_H

#ifdef _WIN32
#pragma once
#endif


// predeclare all the vgui control class names
LUALIB_API int luaopen_vgui_AnalogBar(lua_State *L);
LUALIB_API int luaopen_vgui_AnimatingImagePanel(lua_State *L);
LUALIB_API int luaopen_vgui_AnimationController(lua_State *L);
LUALIB_API int luaopen_vgui_BuildModeDialog(lua_State *L);
LUALIB_API int luaopen_vgui_Button(lua_State *L);
LUALIB_API int luaopen_vgui_CheckButton(lua_State *L);
LUALIB_API int luaopen_vgui_CheckButtonList(lua_State *L);
LUALIB_API int luaopen_vgui_ComboBox(lua_State *L);
LUALIB_API int luaopen_vgui_DirectorySelectDialog(lua_State *L);
LUALIB_API int luaopen_vgui_Divider(lua_State *L);
LUALIB_API int luaopen_vgui_EditablePanel(lua_State *L);
LUALIB_API int luaopen_vgui_FileOpenDialog(lua_State *L);
LUALIB_API int luaopen_vgui_Frame(lua_State *L);
LUALIB_API int luaopen_vgui_GraphPanel(lua_State *L);
LUALIB_API int luaopen_vgui_HTML(lua_State *L);
LUALIB_API int luaopen_vgui_ImagePanel(lua_State *L);
LUALIB_API int luaopen_vgui_Label(lua_State *L);
LUALIB_API int luaopen_vgui_ListPanel(lua_State *L);
LUALIB_API int luaopen_vgui_ListViewPanel(lua_State *L);
LUALIB_API int luaopen_vgui_Menu(lua_State *L);
LUALIB_API int luaopen_vgui_MenuBar(lua_State *L);
LUALIB_API int luaopen_vgui_MenuButton(lua_State *L);
LUALIB_API int luaopen_vgui_MenuItem(lua_State *L);
LUALIB_API int luaopen_vgui_MessageBox(lua_State *L);
LUALIB_API int luaopen_vgui_Panel(lua_State *L);
LUALIB_API int luaopen_vgui_PanelListPanel(lua_State *L);
LUALIB_API int luaopen_vgui_ProgressBar(lua_State *L);
LUALIB_API int luaopen_vgui_ProgressBox(lua_State *L);
LUALIB_API int luaopen_vgui_PropertyDialog(lua_State *L);
LUALIB_API int luaopen_vgui_PropertyPage(lua_State *L);
LUALIB_API int luaopen_vgui_PropertySheet(lua_State *L);
LUALIB_API int luaopen_vgui_QueryBox(lua_State *L);
LUALIB_API int luaopen_vgui_RadioButton(lua_State *L);
LUALIB_API int luaopen_vgui_RichText(lua_State *L);
LUALIB_API int luaopen_vgui_ScalableImagePanel(lua_State *L);
LUALIB_API int luaopen_vgui_ScrollBar(lua_State *L);
LUALIB_API int luaopen_vgui_ScrollBarSlider(lua_State *L);
LUALIB_API int luaopen_vgui_SectionedListPanel(lua_State *L);
LUALIB_API int luaopen_vgui_Slider(lua_State *L);
LUALIB_API int luaopen_vgui_Splitter(lua_State *L);
LUALIB_API int luaopen_vgui_TextEntry(lua_State *L);
LUALIB_API int luaopen_vgui_ToggleButton(lua_State *L);
LUALIB_API int luaopen_vgui_Tooltip(lua_State *L);
LUALIB_API int luaopen_vgui_TreeView(lua_State *L);
LUALIB_API int luaopen_vgui_CTreeViewListControl(lua_State *L);
LUALIB_API int luaopen_vgui_URLLabel(lua_State *L);
LUALIB_API int luaopen_vgui_WizardPanel(lua_State *L);
LUALIB_API int luaopen_vgui_WizardSubPanel(lua_State *L);

#endif // LCONTROLS_H
