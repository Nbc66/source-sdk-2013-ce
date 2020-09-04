//========================================================================//
//
// Purpose: Discord Rich Presence support.
//
//=============================================================================//

#include "cbase.h"
#include "sdk2013ce_discord_rpc.h"
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

// Strings are bad dont use them ever -Nbc66
#include <string>
#include <algorithm>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// update once every 10 seconds. discord has an internal rate limiter of 15 seconds as well
#define DISCORD_UPDATE_RATE 10.0f

CDiscordRPC g_DiscordRPC;

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CDiscordRPC::CDiscordRPC()
{
	Q_memset( m_szLatchedMapname, 0, MAX_MAP_NAME );
	m_bInitializeRequested = false;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CDiscordRPC::~CDiscordRPC()
{
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::RunFrame()
{
	if (IsRPCUsed() == 0)
	{
		Shutdown();
	}

	if ( m_bErrored )
		return;

	// NOTE: We want to run this even if they have use_discord off, 
	// so we can clear any previous state that may have already been sent
	UpdateRichPresence();
	Discord_RunCallbacks();

	// Always run this, otherwise we will chicken & egg waiting for ready
	//if ( Discord_RunCallbacks )
	//	Discord_RunCallbacks();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::Init()
{
	if (IsRPCUsed() == 0)
	{
		Shutdown();
	}

	InitializeDiscord();
	m_bInitializeRequested = true;

	// Make sure to call this after game system initialized
	ListenForGameEvent( "server_spawn" );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::LevelInit( const char *pszMapname )
{
	Reset();
	
	// We can't update our presence here, because if its the first map a client loaded,
	// the Discord API may not yet be loaded, so latch
	Q_strcpy( m_szLatchedMapname, pszMapname );
	//V_snprintf(szStateBuffer, sizeof(szStateBuffer), "MAP: %s", m_szLatchedMapname);
	
	// Important, clear last update time as well
	m_flLastUpdatedTime = max(0, gpGlobals->realtime - DISCORD_UPDATE_RATE);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::Reset()
{
	Q_memset( &m_sDiscordRichPresence, 0, sizeof(m_sDiscordRichPresence) );
	m_sDiscordRichPresence.details = "Main Menu";
	
	const char *pszState = "";
	m_sDiscordRichPresence.state = pszState;

	m_sDiscordRichPresence.endTimestamp;

	SetLogo();
	Discord_UpdatePresence( &m_sDiscordRichPresence );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::Shutdown()
{
	Discord_Shutdown();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::HandleDiscordReady( const DiscordUser *connectedUser )
{
	// Obtain coordinated universal time -Nbc66
	std::string str;
	time_t t = time( NULL );

	str = asctime( gmtime(&t) );

	// Fuck ctime for adding a \n at the fucking end you fucking piece of shit -Nbc66
	str.erase( std::remove(str.begin(), str.end(), '\n'), str.end() );

	ConColorMsg( Color(114, 137, 218, 255), "[Rich Presence] Ready!\n" );
	ConColorMsg( Color(114, 137, 218, 255), "[Rich Presence] User %s#%s - %s\n", connectedUser->username, connectedUser->discriminator, connectedUser->userId );

	// Yup this is literaly usless but hey it's a novelty lol -Nbc66
	ConColorMsg( Color(0, 255, 30, 255), "This build was compiled on %s UTC\n", str );

	g_DiscordRPC.Reset();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::HandleDiscordError( int errorCode, const char *message )
{
	g_DiscordRPC.m_bErrored = true;

	char buff[1024];
	Q_snprintf( buff, 1024, "[Rich Presence] Init failed. code %d - error: %s\n", errorCode, message );
	Warning( buff );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::FireGameEvent( IGameEvent *event)
{
	const char *type = event->GetName();
	if ( Q_strcmp(type, "server_spawn") == 0 )
	{
		Q_strncpy( m_szLatchedHostname, event->GetString("hostname"), 255 );
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::InitializeDiscord()
{
	DiscordEventHandlers handlers;

	Q_memset( &handlers, 0, sizeof(handlers) );
	handlers.ready = &CDiscordRPC::HandleDiscordReady;
	handlers.errored = &CDiscordRPC::HandleDiscordError;

	char command[512];
	V_snprintf( command, sizeof(command), "%s -game \"%s\" -novid -steam\n", CommandLine()->GetParm(0), CommandLine()->ParmValue("-game") );
	Discord_Register( GetRPCAppId(), command );
	Discord_Initialize( GetRPCAppId(), &handlers, false, "" );
	Reset();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool CDiscordRPC::NeedToUpdate()
{
	if ( m_bErrored || m_szLatchedMapname[0] == '\0' )
		return false;

	return gpGlobals->realtime >= m_flLastUpdatedTime + DISCORD_UPDATE_RATE;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::UpdateRichPresence()
{
	// The elapsed timer function using <ctime>
	// This is for setting up the time when the player joins a server -Nbc66
	time_t iSysTime;
	time( &iSysTime );
	struct tm* tStartTime = NULL;
	tStartTime = localtime( &iSysTime );
	tStartTime->tm_sec += 0 - gpGlobals->curtime;

	if ( !NeedToUpdate() )
		return;

	m_flLastUpdatedTime = gpGlobals->realtime;

	if ( engine->IsConnected() )
	{
		V_snprintf( m_szStateBuffer, sizeof(m_szStateBuffer), "Map : %s",  m_szLatchedMapname );
		// Starts the elapsed timer for Discord RPC -Nbc66
		m_sDiscordRichPresence.startTimestamp = mktime(tStartTime);
		// Sets the map name
		m_sDiscordRichPresence.details = m_szStateBuffer;
	}

	// Checks if the loading bar is being drawn
	// and sets the discord status to "Currently is loading..." -Nbc66
	if ( engine->IsDrawingLoadingImage() )
	{
		m_sDiscordRichPresence.state = "";
		m_sDiscordRichPresence.details = "Currently loading...";
	}

	SetLogo();

	Discord_UpdatePresence( &m_sDiscordRichPresence );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDiscordRPC::SetLogo()
{
	const char *pszGameType = "Community Made";
	const char *pszImageLarge = "sdk2013ce";
	const char *pszMapIcon = "sdk2013ce";
	const char *pszImageSmall = "";
	const char *pszImageText = "";

	if ( engine->IsConnected() )
	{
		if ( pszImageLarge != m_szLatchedMapname )
		{
			pszMapIcon = GetRPCMapImage( m_szLatchedMapname, pszMapIcon );

			pszImageLarge = pszMapIcon;

			m_sDiscordRichPresence.largeImageKey = pszImageLarge;
			m_sDiscordRichPresence.largeImageText = pszGameType;
			m_sDiscordRichPresence.smallImageKey = pszImageSmall;
			m_sDiscordRichPresence.smallImageText = pszImageText;
		}
	}
}



//-----------------------------------------------------------------------------
// Purpose: Function to get the localized string and then localize it on runtime
//          Use this to localize the rest of the strings
//-----------------------------------------------------------------------------

//dont bother using this for sp since v_strdup only works on mp and is crucial for this function to work

/*const char *CDiscordRPC::LocalizeDiscordString( const char *pszLocalizedString )
{
	const wchar_t *pwszLocalizedString = g_pVGuiLocalize->Find( pszLocalizedString );

	// We need to set the Char array to 256
	// since ASCII has 256 characters and we need to account
	// for every single one, belive me. You dont want to change the array size
	// or you are going to have a bad time with this whole function -Nbc66
	char szLocalizedArray[256];
	g_pVGuiLocalize->ConvertUnicodeToANSI( pwszLocalizedString, szLocalizedArray, sizeof(szLocalizedArray) );
	const char *pszFinalLocalizedString = V_strdup(szLocalizedArray);

	ConLog("RPC Localization Result = $",pszFinalLocalizedString);

	return pszFinalLocalizedString;

	delete[] pszFinalLocalizedString, szLocalizedArray;
}*/

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
const char *CDiscordRPC::GetRPCAppId()
{
	const char *ID = "746722719328108615";
	KeyValues *pDiscordRPCID = new KeyValues( "GameInfo" );
	pDiscordRPCID->LoadFromFile( filesystem, "gameinfo.txt" );
	if ( pDiscordRPCID )
	{
		KeyValues *pID = pDiscordRPCID->FindKey( "Discord" );
		if (pID)
		{
			return ID = pID->GetString( "DiscordAppID", "746722719328108615" );
		}
		pID->deleteThis();
		pDiscordRPCID->deleteThis();
	}
	return ID;
}

//-----------------------------------------------------------------------------
// Purpose: function to check if we set up support for RPC in Gameinfo.txt and
//			are we going to use RPC in our mod -Nbc66
//-----------------------------------------------------------------------------
bool CDiscordRPC::IsRPCUsed()
{
	bool IsItOn = 0;
	KeyValues* pDiscordRPCIsUsed = new KeyValues( "GameInfo" );
	pDiscordRPCIsUsed->LoadFromFile( filesystem, "gameinfo.txt" );
	if (pDiscordRPCIsUsed)
	{
		KeyValues* IsUsedBool = pDiscordRPCIsUsed->FindKey( "Discord" );
		if (IsUsedBool)
		{
			return IsItOn = IsUsedBool->GetBool( "SupportsDiscordRPC",  1);
		}
		IsUsedBool->deleteThis();
		pDiscordRPCIsUsed->deleteThis();
	}
	return IsItOn;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
const char *CDiscordRPC::GetRPCMapImage( char szLatchedMapname[MAX_MAP_NAME], const char *pszMapIcon )
{
	KeyValues *pDiscordRPC = new KeyValues( "Discord" );
	pDiscordRPC->LoadFromFile( filesystem, "scripts/discord_rpc.txt" );
	if ( pDiscordRPC )
	{
		KeyValues *pMaps = pDiscordRPC->FindKey( "Maps" );
		if ( pMaps )
		{
			return pMaps->GetString( m_szLatchedMapname, pszMapIcon );
		}
		pMaps->deleteThis();
		pDiscordRPC->deleteThis();
	}
	return "sdk2013ce";
}
