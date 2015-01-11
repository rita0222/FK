// Fog_CLI.h

#pragma once

#include <FK/Fog.h>
#include "DList_CLI.h"

namespace FK_CLI
{
	public enum class fk_FogMode {
		LINEAR_FOG,
		EXP_FOG,
		EXP2_FOG,
		NONE_FOG
	};

	public enum class fk_FogOption {
		FASTEST_FOG,
		NICEST_FOG,
		NOOPTION_FOG
	};

	public ref class fk_Fog : fk_DisplayLink {
	internal:
		::fk_Fog * GetP(void)
		{
			return (::fk_Fog *)(pBase);
		}

	public:
		fk_Fog::fk_Fog(bool argNewFlg) : fk_DisplayLink(false)
		{
		}

		fk_Fog::~fk_Fog()
		{
			this->!fk_Fog();
		}

		fk_Fog::!fk_Fog()
		{
		}

		void setFogMode(fk_FogMode mode);
		void setFogOption(fk_FogOption opt);
		void setFogDensity(double density);
		void setFogLinearMap(double start, double end);
		void setFogColor(fk_Color^ color);
		void setFogColor(float r, float g, float b, float a);
		void setFogColor(double r, double g, double b, double a);
		fk_FogMode getFogMode(void);
		fk_FogOption getFogOption(void);
		double getFogDensity(void);
		double getFogLinearStart(void);
		double getFogLinearEnd(void);
		fk_Color^ getFogColor(void);
	};
}
