//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//
#if !defined( VGUI_INT_H )
#define VGUI_INT_H
#ifdef _WIN32
#pragma once
#endif

#include "interface.h"

#include <vgui/VGUI.h>

namespace vgui
{
	class Panel;
}

bool VGui_Startup( CreateInterfaceFn appSystemFactory );
void VGui_Shutdown( void );
void VGui_CreateGlobalPanels( void );
vgui::VPANEL VGui_GetClientDLLRootPanel( void );
#ifdef LUA_SDK
vgui::Panel* VGui_GetGameUIPanel(void);
vgui::Panel* VGui_GetClientLuaRootPanel(void);
void VGUI_CreateGameUIRootPanel(void);
void VGUI_DestroyGameUIRootPanel(void);
#endif
void VGUI_CreateClientDLLRootPanel( void );
void VGUI_DestroyClientDLLRootPanel( void );
void VGui_PreRender();
void VGui_PostRender();

#endif // VGUI_INT_H