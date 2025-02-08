//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LPROPERTYDIALOG_H
#define LPROPERTYDIALOG_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/PropertyDialog.h>

namespace vgui
{

//-----------------------------------------------------------------------------
// Purpose: Lua wrapper for a simple frame that holds a property sheet
//-----------------------------------------------------------------------------
class LPropertyDialog : public PropertyDialog
{
	DECLARE_CLASS_SIMPLE( LPropertyDialog, PropertyDialog );

public:
	LPropertyDialog(Panel *parent, const char *panelName, lua_State *L);
	~LPropertyDialog();

protected:
	// Called when the OK button is pressed.  Simply closes the dialog.
	virtual bool OnOK(bool applyOnly);

	// called when the Cancel button is pressed
	virtual void OnCancel();

	// vgui overrides
	virtual void PerformLayout();
	virtual void OnCommand(const char *command);
	virtual void OnKeyCodeTyped(KeyCode code);

public:
	void EnableApplyButton(bool bEnable);

public:
#if defined( LUA_SDK )
	lua_State *m_lua_State;
	int m_nTableReference;
	int m_nRefCount;
#endif
};

}; // vgui

#define BEGIN_LUA_CALL_PROPERTYDIALOG_METHOD(functionName) \
  if (m_nTableReference >= 0) { \
    lua_getref(m_lua_State, m_nTableReference); \
    lua_getfield(m_lua_State, -1, functionName); \
    lua_remove(m_lua_State, -2); \
    if (lua_isfunction(m_lua_State, -1)) { \
      int args = 0; \
	  lua_pushpropertydialog(m_lua_State, this); \
	  ++args;

/* type for PropertyDialog functions */
typedef vgui::PropertyDialog lua_PropertyDialog;



/*
** access functions (stack -> C)
*/

LUA_API lua_PropertyDialog     *(lua_topropertydialog) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushpropertydialog) (lua_State *L, lua_PropertyDialog *pDialog);



LUALIB_API lua_PropertyDialog *(luaL_checkpropertydialog) (lua_State *L, int narg);


#endif // LPROPERTYDIALOG_H
