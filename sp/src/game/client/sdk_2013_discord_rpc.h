//=============================================================================
//
// Purpose: Discord Rich Presence support.
//
//=============================================================================

#ifdef _WIN32
#pragma once
#endif

#include "GameEventListener.h"
#include "hl2orange.spa.h"
#include "discord-rpc/discord_rpc.h"
#include "const.h"

#define DISCORD_FIELD_SIZE 128

class CTFDiscordRPC : public CGameEventListener
{
public:
	CTFDiscordRPC();
	~CTFDiscordRPC();
	void RunFrame();
	void Init();
	void LevelInit(const char* szMapname);
	void Reset();
	void Shutdown();

	static void OnReady(const DiscordUser* user);
	static void OnDiscordError(int errorCode, const char* szMessage);

	// IGameEventListener interface:
	virtual void FireGameEvent(IGameEvent* event);

private:
	void InitializeDiscord();
	bool NeedToUpdate();

	void UpdateRichPresence();
	void SetLogo();

	//localization only
	const char* LocalizeDiscordString(const char* LocalizedString);

	const char* GetRPCAppId();
	const char* GetRPCMapImage(char m_szLatchedMapname[MAX_MAP_NAME], const char* pMapIcon);



	bool m_bErrored;
	bool m_bInitializeRequested;
	float m_flLastUpdatedTime;
	DiscordRichPresence m_sDiscordRichPresence;

	// scratch buffers to send in api struct. they need to persist
	// for a short duration after api call it seemed, it must be async
	// using a stack allocated would occassionally corrupt
	char m_szServerInfo[DISCORD_FIELD_SIZE];
	char m_szDetails[DISCORD_FIELD_SIZE];
	char m_szLatchedHostname[255];
	char m_szLatchedMapname[MAX_MAP_NAME];
	char szStateBuffer[256];
	//HINSTANCE m_hDiscordDLL;
};

extern CTFDiscordRPC g_discordrpc;