#ifndef SHADERAPIHACK_H
#define SHADERAPIHACK_H
#ifdef _WIN32
#pragma once
#endif
#include "materialsystem/materialsystem_config.h"
class CMaterialConfigWrapper
{
public:
	CMaterialConfigWrapper()
	{
		m_pHardwareConfig = materials->GetHardwareConfig(MATERIALSYSTEM_HARDWARECONFIG_INTERFACE_VERSION, 0);
		m_VideoConfig = materials->GetCurrentConfigForVideoCard();
	}

	~CMaterialConfigWrapper()
	{
		m_VideoConfig.m_nReserved++;
		materials->OverrideConfig(m_VideoConfig, true);
	}

	int& GetNumPixelConstants() { return *(((int*)m_pHardwareConfig) + 331); }
	int& GetNumBooleanPixelConstants() { return *(((int*)m_pHardwareConfig) + 332); }
	int& GetNumIntegerBoolPixelConstants() { return *(((int*)m_pHardwareConfig) + 333); }

	void SetNumPixelConstants(int Num) { GetNumPixelConstants() = Num; }
	void SetNumBooleanPixelConstants(int Num) { GetNumBooleanPixelConstants() = Num; }
	void SetNumIntegerPixelConstants(int Num) { GetNumIntegerBoolPixelConstants() = Num; }

	void PrintPixelConstants()
	{
		Msg("\t%d pixel constants\n\t%d boolean pixel constants\n\t%d integer pixel constants\n",
			GetNumPixelConstants(), GetNumBooleanPixelConstants(), GetNumIntegerBoolPixelConstants());
	}

	IMaterialSystemHardwareConfig* m_pHardwareConfig;
	MaterialSystem_Config_t m_VideoConfig;
};
#endif