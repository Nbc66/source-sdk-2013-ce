//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef SCRIPTEDHUDVIEWPORT_H
#define SCRIPTEDHUDVIEWPORT_H

#include <vgui_controls/Frame.h>

using namespace vgui;

//==============================================================================
class CScriptedHudViewport : public vgui::EditablePanel
{
	DECLARE_CLASS_SIMPLE( CScriptedHudViewport, vgui::EditablePanel );

public: 
	CScriptedHudViewport();

	virtual void SetParent(vgui::VPANEL parent);

protected:

	virtual void Paint();

};


#endif
