//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LPROPERTYPAGE_H
#define LPROPERTYPAGE_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/PropertyPage.h>

namespace vgui
{

//-----------------------------------------------------------------------------
// Purpose: Lua wrapper for property page, as held by a set of property sheets
//-----------------------------------------------------------------------------
class LPropertyPage : public PropertyPage
{
	DECLARE_CLASS_SIMPLE( LPropertyPage, PropertyPage );

public:
	LPropertyPage(Panel *parent, const char *panelName, lua_State *L);
	~LPropertyPage();

	// Called when page is loaded.  Data should be reloaded from document into controls.
	MESSAGE_FUNC( OnResetData, "ResetData" );

	// Called when the OK / Apply button is pressed.  Changed data should be written into document.
	MESSAGE_FUNC( OnApplyChanges, "ApplyChanges" );

	// called when the page is shown/hidden
	MESSAGE_FUNC( OnPageShow, "PageShow" );
	MESSAGE_FUNC( OnPageHide, "PageHide" );

	virtual void OnKeyCodeTyped(KeyCode code);
	virtual bool HasUserConfigSettings() { return true; }

protected:
	// called to be notified of the tab button used to Activate this page
	// if overridden this must be chained back to
	MESSAGE_FUNC_PTR( OnPageTabActivated, "PageTabActivated", panel );

private:
	PHandle _pageTab;

#if defined( LUA_SDK )
public:
	lua_State *m_lua_State;
	int m_nTableReference;
	int m_nRefCount;
#endif
};

} // namespace vgui

#define BEGIN_LUA_CALL_PROPERTYPAGE_METHOD(functionName) \
  if (m_nTableReference >= 0) { \
    lua_getref(m_lua_State, m_nTableReference); \
    lua_getfield(m_lua_State, -1, functionName); \
    lua_remove(m_lua_State, -2); \
    if (lua_isfunction(m_lua_State, -1)) { \
      int args = 0; \
	  lua_pushpropertypage(m_lua_State, this); \
	  ++args;

/* type for PropertyPage functions */
typedef vgui::PropertyPage lua_PropertyPage;



/*
** access functions (stack -> C)
*/

LUA_API lua_PropertyPage     *(lua_topropertypage) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushpropertypage) (lua_State *L, lua_PropertyPage *pPage);



LUALIB_API lua_PropertyPage *(luaL_checkpropertypage) (lua_State *L, int narg);


#endif // LPROPERTYPAGE_H
