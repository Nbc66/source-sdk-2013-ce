//========================================================================//
//
// Purpose: Discord Rich Presence support.
//
//=============================================================================//

#ifdef _WIN32
#pragma once
#endif

#include "GameEventListener.h"
#include "hl2orange.spa.h"
#include "discord-rpc/discord_rpc.h"
#include "const.h"

#define DISCORD_FIELD_SIZE 128

class CDiscordRPC : public CGameEventListener
{
public:
	CDiscordRPC();
	~CDiscordRPC();

	void		RunFrame();
	void		Init();
	void		LevelInit( const char *pszMapname );
	void		Reset();
	void		Shutdown();

	// Discord callbacks
	static void HandleDiscordReady( const DiscordUser *connectedUser );
	static void HandleDiscordError( int errorCode, const char *message );

	// IGameEventListener interface:
	virtual void FireGameEvent( IGameEvent *event );

private:
	void		InitializeDiscord();
	bool		NeedToUpdate();

	void		UpdateRichPresence();
	void		SetLogo();

	// Localization only
	const char *LocalizeDiscordString( const char *pszLocalizedString );

	const char *GetRPCAppId();
	bool IsRPCUsed();
	const char *GetRPCMapImage( char szLatchedMapname[MAX_MAP_NAME], const char *pszMapIcon );

private:
	bool		m_bErrored;
	bool		m_bInitializeRequested;
	float		m_flLastUpdatedTime;

	DiscordRichPresence m_sDiscordRichPresence;

	// Scratch buffers to send in api struct. they need to persist
	// for a short duration after api call it seemed, it must be async
	// using a stack allocated would occassionally corrupt
	char		m_szServerInfo[DISCORD_FIELD_SIZE];
	char		m_szDetails[DISCORD_FIELD_SIZE];
	char		m_szLatchedHostname[255];
	char		m_szLatchedMapname[MAX_MAP_NAME];
	char		m_szStateBuffer[256];
	//HINSTANCE m_hDiscordDLL;
};

extern CDiscordRPC g_DiscordRPC;
