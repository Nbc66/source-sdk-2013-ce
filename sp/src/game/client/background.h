//========= Copyright Jorge "BSVino" Rodriguez, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef MENU_BACKGROUND_H
#define MENU_BACKGROUND_H
#ifdef _WIN32
#pragma once
#endif

#include <vguitextwindow.h>
#include "video/ivideoservices.h"
#include <materialsystem/MaterialSystemUtil.h>

class CMainMenu : public vgui::Panel
{
public:
	DECLARE_CLASS_SIMPLE( CMainMenu, vgui::Panel );

	CMainMenu( vgui::Panel *parent, const char *pElementName );
	~CMainMenu();

public:
	virtual void ApplySchemeSettings( vgui::IScheme *pScheme );

	bool IsVideoPlaying();
	void StartVideo();
	void StopVideo();

	void GetPanelPos( int &xpos, int &ypos );

	void Paint();
	bool BeginPlayback( const char *pFilename );
	void ReleaseVideo();
	void SetBlackBackground( bool bBlack );
	void DoModal();

	MESSAGE_FUNC( OnDisconnectFromGame, "DisconnectedFromGame" );

private:
	bool m_bLoaded;
	bool m_bToolsMode;
	bool m_bPaintVideo;

	CMaterialReference m_MainMenuRef;

protected:
	IVideoMaterial *m_VideoMaterial;
	IMaterial *m_pMaterial;

	int m_nPlaybackHeight; // Calculated to address ratio changes
	int m_nPlaybackWidth;
	char m_szExitCommand[MAX_PATH]; // This call is fired at the engine when the video finishes or is interrupted

	float m_flU; // UV ranges for video on its sheet
	float m_flV;

	bool m_bBlackBackground;
	bool m_bAllowAlternateMedia;
};

#endif // MENU_BACKGROUND_H