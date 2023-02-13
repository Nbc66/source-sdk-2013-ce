#ifndef GAMEPADUI_LOADING_H
#define GAMEPADUI_LOADING_H
#ifdef _WIN32
#pragma once
#endif

#include "gamepadui_interface.h"
#include "vgui_controls/Panel.h"
#include "GameUI/IGameUI.h"

class GamepadUILoading : public vgui::Panel
{
	DECLARE_CLASS_SIMPLE( GamepadUILoading, vgui::Panel );
public:
	GamepadUILoading( vgui::VPANEL parent );

	virtual void	ApplySchemeSettings( vgui::IScheme *pScheme );
	virtual void	PerformLayout();
	virtual void	Paint();
	MESSAGE_FUNC( OnActivate, "activate" );
	MESSAGE_FUNC( OnDeactivate, "deactivate" );

private:
	void	SolveEnginePanel();

private:

	int			m_iBarX;
	int			m_iBarY;
	int			m_iBarW;
	int			m_iBarH;
	bool		m_bResolved;
	int			m_SpinnerFrame;
	double		m_prevFrameTime;

	vgui::Frame *m_pDialog;
	vgui::ProgressBar *m_pProgress;
	
	vgui::ImagePanel *m_pBGImage;
	vgui::ProgressBar *m_pProgressMirror;
	vgui::ImagePanel *m_pSpinnerImage;
	vgui::ImagePanel *m_pLogoImage;
};

extern GamepadUILoading *g_pGamepadUILoading;

#endif
