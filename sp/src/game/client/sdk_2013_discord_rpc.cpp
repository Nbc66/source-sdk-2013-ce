//=============================================================================
//
// Purpose: Discord Rich Presence support.
//
//=============================================================================


#include "cbase.h"
#include "sdk_2013_discord_rpc.h"
#include <ctime>
#include "strtools.h"
#include "Color.h"
#include "discord-rpc/discord_rpc.h"
#include "discord-rpc/discord_register.h"
#include "tier0/icommandline.h"
#include "ilocalize.h"
#include <stdlib.h>
#include "hl2_gamerules.h"
#include "c_playerresource.h"
#include <inetchannelinfo.h>
#include "c_hl2_playerlocaldata.h"
#include "c_baseplayer.h"
#include "filesystem.h"
#include "tier0/icommandline.h"
#include <vgui/ILocalize.h>
#include <vgui_controls/AnimationController.h>
#include <vgui/ISurface.h>
#include <stdlib.h>


//Strings are bad dont use them ever
//-Nbc66
#include <string>
#include <algorithm>


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// update once every 10 seconds. discord has an internal rate limiter of 15 seconds as well
#define DISCORD_UPDATE_RATE 10.0f



CTFDiscordRPC g_discordrpc;

CTFDiscordRPC::CTFDiscordRPC()
{
	Q_memset(m_szLatchedMapname, 0, MAX_MAP_NAME);
	m_bInitializeRequested = false;
}

CTFDiscordRPC::~CTFDiscordRPC()
{
}

//stolen from KaydemonLP
//-Nbc66
const char* CTFDiscordRPC::GetRPCMapImage(char m_szLatchedMapname[MAX_MAP_NAME], const char* pMapIcon)
{
	KeyValues* pDiscordRPC = new KeyValues("Discord");
	pDiscordRPC->LoadFromFile(filesystem, "scripts/discord_rpc.txt");
	if (pDiscordRPC)
	{
		KeyValues* pMaps = pDiscordRPC->FindKey("Maps");
		if (pMaps)
		{
			return pMaps->GetString(m_szLatchedMapname, pMapIcon);
		}
		pMaps->deleteThis();
		pDiscordRPC->deleteThis();
	}
	return "sdk2013ce";
}

const char* CTFDiscordRPC::GetRPCAppId(void)
{
	const char* ID = "746722719328108615";
	KeyValues* pDiscordRPCID = new KeyValues("GameInfo");
	pDiscordRPCID->LoadFromFile(filesystem, "gameinfo.txt");
	if (pDiscordRPCID)
	{
		KeyValues* pID = pDiscordRPCID->FindKey("Discord");
		if (pID)
		{
			return	ID = pID->GetString("Discord_app_id","746722719328108615");
		}
		pID->deleteThis();
		pDiscordRPCID->deleteThis();
	}
	return ID;
}

void CTFDiscordRPC::Shutdown()
{
	Discord_Shutdown();
}

void CTFDiscordRPC::InitializeDiscord()
{
	DiscordEventHandlers handlers;
	Q_memset(&handlers, 0, sizeof(handlers));
	handlers.ready = &CTFDiscordRPC::OnReady;
	handlers.errored = &CTFDiscordRPC::OnDiscordError;

	char command[512];
	V_snprintf(command, sizeof(command), "%s -game \"%s\" -novid -steam\n", CommandLine()->GetParm(0), CommandLine()->ParmValue("-game"));
	Discord_Register(GetRPCAppId(), command);
	Discord_Initialize(GetRPCAppId(), &handlers, false, "");
	Reset();
}


void CTFDiscordRPC::Init()
{
	InitializeDiscord();
	m_bInitializeRequested = true;

	// make sure to call this after game system initialized
	ListenForGameEvent("server_spawn");
}

void CTFDiscordRPC::RunFrame()
{
	if (m_bErrored)
		return;
	// NOTE: we want to run this even if they have use_discord off, so we can clear
	// any previous state that may have already been sent
	UpdateRichPresence();
	Discord_RunCallbacks();

	// always run this, otherwise we will chicken & egg waiting for ready
	//if (Discord_RunCallbacks)
	//	Discord_RunCallbacks();
}

void CTFDiscordRPC::OnReady(const DiscordUser* user)
{

	//Obtain coordinated universal time:
	//-Nbc66
	std::string str;
	time_t t = time(NULL);

	str = asctime(gmtime(&t));

	//Fuck ctime for adding a \n at the fucking end you fucking piece of shit
	//-Nbc66
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

	ConColorMsg(Color(114, 137, 218, 255), "[Rich Presence] Ready!\n");
	ConColorMsg(Color(114, 137, 218, 255), "[Rich Presence] User %s#%s - %s\n", user->username, user->discriminator, user->userId);

	//Yup this is literaly usless but hey it's a novelty lol
	//-Nbc66
	ConColorMsg(Color(0, 255, 30, 255), "This build was compiled on %s UTC\n", str);

	g_discordrpc.Reset();
}

void CTFDiscordRPC::OnDiscordError(int errorCode, const char* szMessage)
{
	g_discordrpc.m_bErrored = true;
	char buff[1024];
	Q_snprintf(buff, 1024, "[Rich Presence] Init failed. code %d - error: %s\n", errorCode, szMessage);
	Warning(buff);
}

void CTFDiscordRPC::FireGameEvent(IGameEvent* event)
{
	const char* type = event->GetName();

	if (Q_strcmp(type, "server_spawn") == 0)
	{
		Q_strncpy(m_szLatchedHostname, event->GetString("hostname"), 255);
	}
}

void CTFDiscordRPC::SetLogo(void)
{

	const char* pszGameType = "Community Made";
	const char* pszImageLarge = "sdk2013ce";
	const char* pMapIcon = "sdk2013ce";

	//string for setting the picture of the class
	//you should name the small picture affter the class itself ex: Scout.jpg, Soldier.jpg, Pyro.jpg ...
	//you get it
	//-Nbc66
	const char* pszImageSmall = "";
	const char* pszImageText = "";

	if (engine->IsConnected())
	{

		if (pszImageLarge != m_szLatchedMapname)
		{
			//stolen from KaydemonLP
			//-Nbc66
			pMapIcon = GetRPCMapImage(m_szLatchedMapname, pMapIcon);


			//old function that uses hard coded maps inside this cpp file
			//-Nbc66
			/*
					if (pszImageLarge != m_szLatchedMapname)
					{
						for (int i = 0; i < MAP_COUNT; i++)
						{
							if (V_strcmp(g_aMapList[i], m_szLatchedMapname) == 0)
							{
								pMapIcon = m_szLatchedMapname;
								break;
							}
						}
					}
			*/



			pszImageLarge = pMapIcon;

			m_sDiscordRichPresence.largeImageKey = pszImageLarge;
			m_sDiscordRichPresence.largeImageText = pszGameType;
			m_sDiscordRichPresence.smallImageKey = pszImageSmall;
			m_sDiscordRichPresence.smallImageText = pszImageText;

		}
	}
}

void CTFDiscordRPC::LevelInit(const char* szMapname)
{
	Reset();
	// we cant update our presence here, because if its the first map a client loaded,
	// discord api may not yet be loaded, so latch
	Q_strcpy(m_szLatchedMapname, szMapname);
	//V_snprintf(szStateBuffer, sizeof(szStateBuffer), "MAP: %s", m_szLatchedMapname);
	// important, clear last update time as well
	m_flLastUpdatedTime = max(0, gpGlobals->realtime - DISCORD_UPDATE_RATE);
}

void CTFDiscordRPC::UpdateRichPresence()
{
	//The elapsed timer function using <ctime>
	//this is for setting up the time when the player joins a server
	//-Nbc66
	time_t iSysTime;
	time(&iSysTime);
	struct tm* tStartTime = NULL;
	tStartTime = localtime(&iSysTime);
	tStartTime->tm_sec += 0 - gpGlobals->curtime;

	if (!NeedToUpdate())
		return;

	m_flLastUpdatedTime = gpGlobals->realtime;

	if (engine->IsConnected())
	{
		V_snprintf(szStateBuffer, sizeof(szStateBuffer), "%s : %s", LocalizeDiscordString("#Discord_Map"), m_szLatchedMapname);
		//starts the elapsed timer for discord rpc
		//-Nbc66
		m_sDiscordRichPresence.startTimestamp = mktime(tStartTime);
		//sets the map name
		m_sDiscordRichPresence.details = szStateBuffer;
	}

	//checks if the loading bar is being drawn
	//and sets the discord status to "Currently is loading..."
	//-Nbc66
	if (engine->IsDrawingLoadingImage() == true)
	{
		m_sDiscordRichPresence.state = "";
		m_sDiscordRichPresence.details = "Currently loading...";
	}

	SetLogo();

	Discord_UpdatePresence(&m_sDiscordRichPresence);
}

bool CTFDiscordRPC::NeedToUpdate()
{
	if (m_bErrored || m_szLatchedMapname[0] == '\0')
		return false;

	return gpGlobals->realtime >= m_flLastUpdatedTime + DISCORD_UPDATE_RATE;
}

void CTFDiscordRPC::Reset()
{
	Q_memset(&m_sDiscordRichPresence, 0, sizeof(m_sDiscordRichPresence));
	m_sDiscordRichPresence.details = LocalizeDiscordString("#Discord_State_Menu");
	const char* pszState = "";

	m_sDiscordRichPresence.state = pszState;

	m_sDiscordRichPresence.endTimestamp;

	SetLogo();
	Discord_UpdatePresence(&m_sDiscordRichPresence);
}

//Function to get the localized string and then localize it on runtime
//Use this to localize the rest of the strings
//
//-Nbc66
const char* CTFDiscordRPC::LocalizeDiscordString(const char* LocalizedString)
{

	const wchar_t* WcharLocalizedString = g_pVGuiLocalize->Find(LocalizedString);
	//we need to set the Char array to 256
	//since ascii has 256 charachters and we need to account
	//for every single one belive me. you dont want to change the array size
	//or you are going to have a bad time with this whole function
	//-Nbc66
	char CharLocalizedArray[256];
	g_pVGuiLocalize->ConvertUnicodeToANSI(WcharLocalizedString, CharLocalizedArray, sizeof(CharLocalizedArray));
	const char* FinalCharLocalizedString = CharLocalizedArray;

	return FinalCharLocalizedString;

	delete[] FinalCharLocalizedString;
}

