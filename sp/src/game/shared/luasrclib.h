//========== Copyleft © 2011, Team Sandbox, Some rights reserved. ===========//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//


#ifndef LUASRCLIB_H
#define LUASRCLIB_H
#ifdef _WIN32
#pragma once
#endif


#define LUA_BASEANIMATINGLIBNAME		"CBaseAnimating"
LUALIB_API int (luaopen_CBaseAnimating) (lua_State *L);

#define LUA_BASECOMBATWEAPONLIBNAME		"CBaseCombatWeapon"
LUALIB_API int (luaopen_CBaseCombatWeapon) (lua_State *L);

#define LUA_BASEENTITYLIBNAME			"CBaseEntity"
LUALIB_API int (luaopen_CBaseEntity) (lua_State *L);
LUALIB_API int (luaopen_CBaseEntity_shared) (lua_State *L);

#define LUA_BASEPLAYERLIBNAME			"CBasePlayer"
LUALIB_API int (luaopen_CBasePlayer) (lua_State *L);
LUALIB_API int (luaopen_CBasePlayer_shared) (lua_State *L);

#define LUA_EFFECTDATALIBNAME			"CEffectData"
LUALIB_API int (luaopen_CEffectData) (lua_State *L);

#define LUA_GAMETRACELIBNAME			"CGameTrace"
LUALIB_API int (luaopen_CGameTrace) (lua_State *L);

#define LUA_HL2MPPLAYERLIBNAME			"CHL2MP_Player"
LUALIB_API int (luaopen_CHL2MP_Player) (lua_State *L);
LUALIB_API int (luaopen_CHL2MP_Player_shared) (lua_State *L);

#define LUA_COLORLIBNAME				"Color"
LUALIB_API int (luaopen_Color) (lua_State *L);

#define LUA_CONCOMMANDLIBNAME			"ConCommand"
LUALIB_API int (luaopen_ConCommand) (lua_State *L);

#define LUA_CONTENTSLIBNAME				"CONTENTS"
LUALIB_API int (luaopen_CONTENTS) (lua_State *L);

#define LUA_CONVARLIBNAME				"ConVar"
LUALIB_API int (luaopen_ConVar) (lua_State *L);

#define LUA_PASFILTERLIBNAME			"CPASFilter"
LUALIB_API int (luaopen_CPASFilter) (lua_State *L);

#define LUA_RECIPIENTFILTERLIBNAME		"CRecipientFilter"
LUALIB_API int (luaopen_CRecipientFilter) (lua_State *L);

#define LUA_TAKEDAMAGEINFOLIBNAME		"CTakeDamageInfo"
LUALIB_API int (luaopen_CTakeDamageInfo) (lua_State *L);

#define LUA_CVARLIBNAME					"cvar"
LUALIB_API int (luaopen_cvar) (lua_State *L);

#define LUA_DBGLIBNAME					"dbg"
LUALIB_API int (luaopen_dbg) (lua_State *L);

#define LUA_DEBUGOVERLAYLIBNAME			"debugoverlay"
LUALIB_API int (luaopen_debugoverlay) (lua_State *L);

#define LUA_ENGINELIBNAME				"engine"
LUALIB_API int (luaopen_engine) (lua_State *L);

#define LUA_ENGINEVGUILIBNAME			"enginevgui"
LUALIB_API int (luaopen_enginevgui) (lua_State *L);

#define LUA_FCVARLIBNAME				"FCVAR"
LUALIB_API int (luaopen_FCVAR) (lua_State *L);

#define LUA_FILESYSTEMLIBNAME			"filesystem"
LUALIB_API int (luaopen_filesystem) (lua_State *L);

#define LUA_FONTFLAGLIBNAME				"FONTFLAG"
LUALIB_API int (luaopen_FONTFLAG) (lua_State *L);

#define LUA_ENTLISTLIBNAME				"gEntList"
LUALIB_API int (luaopen_gEntList) (lua_State *L);

#define LUA_GLOBALSLIBNAME				"gpGlobals"
LUALIB_API int (luaopen_gpGlobals) (lua_State *L);

#define LUA_CLIENTSHADOWMGRLIBNAME		"g_pClientShadowMgr"
LUALIB_API int (luaopen_g_pClientShadowMgr) (lua_State *L);

#define LUA_FONTLIBNAME					"HFont"
LUALIB_API int (luaopen_HFont) (lua_State *L);

#define LUA_HSCHEMELIBNAME				"HScheme"
LUALIB_API int (luaopen_HScheme) (lua_State *L);

#define LUA_MATERIALLIBNAME				"IMaterial"
LUALIB_API int (luaopen_IMaterial) (lua_State *L);

#define LUA_MOVEHELPERLIBNAME			"IMoveHelper"
LUALIB_API int (luaopen_IMoveHelper) (lua_State *L);

#define LUA_INLIBNAME					"IN"
LUALIB_API int (luaopen_IN) (lua_State *L);

#define LUA_NETCHANNELINFOLIBNAME		"INetChannelInfo"
LUALIB_API int (luaopen_INetChannelInfo) (lua_State *L);

#define LUA_INETWORKSTRINGTABLELIBNAME	"INetworkStringTable"
LUALIB_API int (luaopen_INetworkStringTable) (lua_State *L);

#define LUA_INPUTLIBNAME				"input"
LUALIB_API int (luaopen_input) (lua_State *L);

#define LUA_PHYSICSOBJECTLIBNAME		"IPhysicsObject"
LUALIB_API int (luaopen_IPhysicsObject) (lua_State *L);

#define LUA_PHYSICSSURFACEPROPSLIBNAME	"IPhysicsSurfaceProps"
LUALIB_API int (luaopen_IPhysicsSurfaceProps) (lua_State *L);

#define LUA_PREDICTIONSYSTEMLIBNAME		"IPredictionSystem"
LUALIB_API int (luaopen_IPredictionSystem) (lua_State *L);

#define LUA_ISCHEMELIBNAME				"IScheme"
LUALIB_API int (luaopen_IScheme) (lua_State *L);

#define LUA_STEAMFRIENDSLIBNAME			"ISteamFriends"
LUALIB_API int (luaopen_ISteamFriends) (lua_State *L);

#define LUA_KEYVALUESLIBNAME			"KeyValues"
LUALIB_API int (luaopen_KeyValues) (lua_State *L);

#define LUA_MASKLIBNAME					"MASK"
LUALIB_API int (luaopen_MASK) (lua_State *L);

#define LUA_MATHLIBLIBNAME				"mathlib"
LUALIB_API int (luaopen_mathlib) (lua_State *L);

#define LUA_MATRIXLIBNAME				"matrix3x4_t"
LUALIB_API int (luaopen_matrix3x4_t) (lua_State *L);

#define LUA_NETWORKSTRINGTABLELIBNAME	"networkstringtable"
LUALIB_API int (luaopen_networkstringtable) (lua_State *L);

#define LUA_PANELLIBNAME				"Panel"
LUALIB_API int (luaopen_Panel) (lua_State *L);

#define LUA_PHYSENVLIBNAME				"physenv"
LUALIB_API int (luaopen_physenv) (lua_State *L);

#define LUA_PREDICTIONLIBNAME			"prediction"
LUALIB_API int (luaopen_prediction) (lua_State *L);

#define LUA_QANGLELIBNAME				"QAngle"
LUALIB_API int (luaopen_QAngle) (lua_State *L);

#define LUA_RANDOMLIBNAME				"random"
LUALIB_API int (luaopen_random) (lua_State *L);

#define LUA_SCHEMELIBNAME				"scheme"
LUALIB_API int (luaopen_scheme) (lua_State *L);

#define LUA_STEAMAPICONTEXTLIBNAME		"steamapicontext"
LUALIB_API int (luaopen_steamapicontext) (lua_State *L);

#define LUA_SURFLIBNAME					"SURF"
LUALIB_API int (luaopen_SURF) (lua_State *L);

#define LUA_SURFACELIBNAME				"surface"
LUALIB_API int (luaopen_surface) (lua_State *L);

#define LUA_UTILLIBNAME					"UTIL"
LUALIB_API int (luaopen_UTIL) (lua_State *L);
LUALIB_API int (luaopen_UTIL_shared) (lua_State *L);

#define LUA_VECTORLIBNAME				"Vector"
LUALIB_API int (luaopen_Vector) (lua_State *L);

#define LUA_VGUILIBNAME					"vgui"
LUALIB_API int (luaopen_vgui) (lua_State *L);

#define LUA_VMATRIXLIBNAME				"vmatrix"
LUALIB_API int (luaopen_VMatrix) (lua_State *L);


/* open all Source Engine libraries */
LUALIB_API void (luasrc_openlibs) (lua_State *L); 



#endif // LUASRCLIB_H
