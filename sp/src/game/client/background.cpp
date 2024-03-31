//========= Copyright Jorge "BSVino" Rodriguez, All rights reserved. ============//
//
// Purpose: 
//
//====================================================================================//

#include "cbase.h"
#include "menu_background.h"
#include <cdll_client_int.h>
#include <ienginevgui.h>
#include <KeyValues.h>
#include "iclientmode.h"

#include <vgui/IScheme.h>
#include <vgui/ILocalize.h>
#include <vgui/ISurface.h>
#include <vgui/IVGui.h>

#include "clienteffectprecachesystem.h"
#include "tier0/icommandline.h"

#include "baseviewport.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Basically this entire file was given to me by Tony Sergi from Project Valkyrie.

CLIENTEFFECT_REGISTER_BEGIN( PrecacheMainMenu )
	CLIENTEFFECT_MATERIAL( "console/mainmenu" )
CLIENTEFFECT_REGISTER_END()

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CMainMenu::CMainMenu( vgui::Panel *parent, const char *pElementName ) : vgui::Panel( NULL, "MainMenu" )
{
	vgui::VPANEL pParent = enginevgui->GetPanel( PANEL_GAMEUIDLL );
	SetParent( pParent );
	SetBuildModeEditable( false );
	SetVisible( false ); 
	SetPaintEnabled( false );
	SetProportional( true );
	SetKeyBoardInputEnabled( false );
	SetBlackBackground( false );
	SetPaintBorderEnabled( false );
	m_VideoMaterial = NULL;
	m_nPlaybackWidth = 0;
	m_nPlaybackHeight = 0;

	m_bToolsMode = false;
	m_bLoaded = false;

	m_MainMenuRef.Init( "console/mainmenu.vmt", TEXTURE_GROUP_OTHER );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CMainMenu::~CMainMenu()
{
	ReleaseVideo();
	MarkForDeletion();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CMainMenu::ApplySchemeSettings( IScheme *pScheme )
{
	SetPos( 0, 0 );
	SetSize( ScreenWidth(), ScreenHeight() );
	SetZPos( 500 );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool CMainMenu::IsVideoPlaying() 
{
	return m_bPaintVideo;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CMainMenu::StartVideo()
{
	m_bToolsMode = ( IsPC() && ( CommandLine()->CheckParm( "-tools" ) != NULL ) ) ? true : false;

	SetVisible( true ); 
	SetPaintEnabled( true );

	bool isWide = false;
	if ( (ScreenWidth() / 4) != (ScreenHeight() / 3) )
		isWide = true;

	m_bLoaded = false;
	if ( isWide )
	{
		//DevMsg( "Attempting to play widescreen video\n" );
		if ( BeginPlayback( "media/mainmenu_wide.bik" ) )
		{
			m_bLoaded = true;
		}
		else
		{
			if ( BeginPlayback( "media/mainmenu.bik" ) )
				m_bLoaded = true;
		}
	}
	else
	{
		if ( BeginPlayback( "media/mainmenu.bik" ) )
			m_bLoaded = true;
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CMainMenu::StopVideo()
{
	// NOTE(Tony): Release the video when stopping
	// NOTE(Tony): Modified, don't hide the panel anymore, because we draw the main menu logo thing for in-game
	//SetVisible( false ); 
	//SetPaintEnabled( false );
	ReleaseVideo();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CMainMenu::GetPanelPos( int &xpos, int &ypos )
{
	vgui::ipanel()->GetAbsPos( GetVPanel(), xpos, ypos );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CMainMenu::Paint( void )
{
	if ( m_bToolsMode )
		return;

	if ( engine->IsConnected() )
		return;

	if ( !m_bLoaded )
		return;

	if ( m_bPaintVideo )
	{
		// No video to play, so do nothing
		if ( m_VideoMaterial == NULL )
			return;

		// Update our frame
		if ( m_VideoMaterial->Update() == false )
			return;

		// Sit in the "center"
		int xpos, ypos;
		GetPanelPos( xpos, ypos );

		// Black out the background (we could omit drawing under the video surface, but this is straight-forward)
		if ( m_bBlackBackground )
		{
			vgui::surface()->DrawSetColor(  0, 0, 0, 255 );
			vgui::surface()->DrawFilledRect( 0, 0, GetWide(), GetTall() );
		}

		// Draw the polys to draw this out
		CMatRenderContextPtr pRenderContext( materials );

		pRenderContext->MatrixMode( MATERIAL_VIEW );
		pRenderContext->PushMatrix();
		pRenderContext->LoadIdentity();

		pRenderContext->MatrixMode( MATERIAL_PROJECTION );
		pRenderContext->PushMatrix();
		pRenderContext->LoadIdentity();

		pRenderContext->Bind( m_pMaterial, NULL );

		CMeshBuilder meshBuilder;
		IMesh *pMesh = pRenderContext->GetDynamicMesh( true );
		meshBuilder.Begin( pMesh, MATERIAL_QUADS, 1 );

		float flLeftX = xpos;
		float flRightX = xpos + ( m_nPlaybackWidth - 1 );

		float flTopY = ypos;
		float flBottomY = ypos + ( m_nPlaybackHeight - 1 );

		// Map our UVs to cut out just the portion of the video we're interested in
		float flLeftU = 0.0f;
		float flTopV = 0.0f;

		// We need to subtract off a pixel to make sure we don't bleed
		float flRightU = m_flU - ( 1.0f / (float)m_nPlaybackWidth );
		float flBottomV = m_flV - ( 1.0f / (float)m_nPlaybackHeight );

		// Get the current viewport size
		int vx, vy, vw, vh;
		pRenderContext->GetViewport( vx, vy, vw, vh );

		// Map from screen pixel coords to -1..1
		flRightX = FLerp( -1, 1, 0, vw, flRightX );
		flLeftX = FLerp( -1, 1, 0, vw, flLeftX );
		flTopY = FLerp( 1, -1, 0, vh , flTopY );
		flBottomY = FLerp( 1, -1, 0, vh, flBottomY );

		float alpha = ( (float)GetFgColor()[3] / 255.0f );

		for ( int corner = 0; corner < 4; corner++ )
		{
			bool bLeft = ( corner == 0 ) || ( corner == 3 );
			meshBuilder.Position3f( ( bLeft ) ? flLeftX : flRightX, ( corner & 2 ) ? flBottomY : flTopY, 0.0f );
			meshBuilder.Normal3f( 0.0f, 0.0f, 1.0f );
			meshBuilder.TexCoord2f( 0, ( bLeft ) ? flLeftU : flRightU, ( corner & 2 ) ? flBottomV : flTopV );
			meshBuilder.TangentS3f( 0.0f, 1.0f, 0.0f );
			meshBuilder.TangentT3f( 1.0f, 0.0f, 0.0f );
			meshBuilder.Color4f( 1.0f, 1.0f, 1.0f, alpha );
			meshBuilder.AdvanceVertex();
		}

		meshBuilder.End();
		pMesh->Draw();

		pRenderContext->MatrixMode( MATERIAL_VIEW );
		pRenderContext->PopMatrix();

		pRenderContext->MatrixMode( MATERIAL_PROJECTION );
		pRenderContext->PopMatrix();
	}
	
	// NOTE(Tony): now draw the mainmenu.vmt overtop!
	{
		CMatRenderContextPtr pRenderContext( materials );
		CMeshBuilder mb;
		IMesh *mesh;

		pRenderContext->Bind( m_MainMenuRef );
		mesh = pRenderContext->GetDynamicMesh( true );
		mb.Begin( mesh, MATERIAL_QUADS, 1 );

		mb.Color4ub( 255, 255, 255, 255 );
		mb.TexCoord2f( 0, 0, 0 );
		mb.Position3f( 0.0f, 0.0f, 0 );
		mb.AdvanceVertex();

		mb.Color4ub( 255, 255, 255, 255);
		mb.TexCoord2f( 0, 1, 0 );
		mb.Position3f( ScreenWidth(), 0.0f, 0 );
		mb.AdvanceVertex();

		mb.Color4ub( 255, 255, 255, 255);
		mb.TexCoord2f( 0, 1, 1 );
		mb.Position3f( ScreenWidth(), ScreenHeight(), 0 );
		mb.AdvanceVertex();

		mb.Color4ub( 255, 255, 255, 255);
		mb.TexCoord2f( 0, 0, 1 );
		mb.Position3f( 0.0f, ScreenHeight(), 0 );
		mb.AdvanceVertex();

		mb.End();
		mesh->Draw();
	}

}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool CMainMenu::BeginPlayback( const char *pFilename )
{
	// Need working video services
	if ( g_pVideo == NULL )
		return false;

	// Destroy any previously allocated video
	if ( m_VideoMaterial != NULL )
	{
		g_pVideo->DestroyVideoMaterial( m_VideoMaterial );
		m_VideoMaterial = NULL;
	}

	// Create new Video material
	m_VideoMaterial = g_pVideo->CreateVideoMaterial( "VideoMaterial", pFilename, "GAME",
										VideoPlaybackFlags::DEFAULT_MATERIAL_OPTIONS,
										VideoSystem::DETERMINE_FROM_FILE_EXTENSION, m_bAllowAlternateMedia );
	if ( m_VideoMaterial == NULL )
		return false;

	m_bPaintVideo = true;

	m_VideoMaterial->SetLooping( true );

	int nWidth, nHeight;
	m_VideoMaterial->GetVideoImageSize( &nWidth, &nHeight );
	m_VideoMaterial->GetVideoTexCoordRange( &m_flU, &m_flV );
	m_pMaterial = m_VideoMaterial->GetMaterial();

	m_nPlaybackWidth = ScreenWidth();
	m_nPlaybackHeight = ScreenHeight();

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CMainMenu::ReleaseVideo()
{
	m_bPaintVideo = false;

	// NOTE(Tony): Not touching the sound!!
	//enginesound->NotifyEndMoviePlayback();

	// Destroy any previously allocated video
	// Shut down this video, destroy the video material
	if ( g_pVideo != NULL && m_VideoMaterial != NULL )
	{
		g_pVideo->DestroyVideoMaterial( m_VideoMaterial );
		m_VideoMaterial = NULL;
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CMainMenu::SetBlackBackground( bool bBlack )
{
	m_bBlackBackground = bBlack;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CMainMenu::DoModal()
{
	vgui::surface()->RestrictPaintToSinglePanel( GetVPanel() );
}

//-----------------------------------------------------------------------------
// Purpose: If we get disconnected, load the menu
//-----------------------------------------------------------------------------
void CMainMenu::OnDisconnectFromGame()
{
	StartVideo();
}

//-----------------------------------------------------------------------------
// Purpose: Find the disconnect command, and rename it...
//-----------------------------------------------------------------------------
CON_COMMAND( __disconnect, "Disconnect game from server." )
{
	CBaseViewport *pViewPort = dynamic_cast<CBaseViewport *>( g_pClientMode->GetViewport() );
	if ( pViewPort )
		pViewPort->StartMainMenuVideo();

	engine->ClientCmd_Unrestricted( "__real_disconnect" );	
}

void SwapDisconnectCommand()
{
	//DevMsg("SwapDisconnectCommand\n");
	ConCommand *_realDisconnectCommand = dynamic_cast<ConCommand *>( g_pCVar->FindCommand( "disconnect" ) );
	ConCommand *_DisconnectCommand = dynamic_cast<ConCommand *>( g_pCVar->FindCommand( "__disconnect" ) );

	if ( !_realDisconnectCommand )
		return;

	if ( !_DisconnectCommand )
		return;

	_realDisconnectCommand->Shutdown();
	_realDisconnectCommand->Create( "__real_disconnect", "" );
	_realDisconnectCommand->Init();

	_DisconnectCommand->Shutdown();
	_DisconnectCommand->Create( "disconnect", "Disconnect game from server." );
	_DisconnectCommand->Init();
}