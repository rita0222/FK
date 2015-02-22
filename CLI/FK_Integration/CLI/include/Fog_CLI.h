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
		::fk_Fog * GetP(void);

	public:
		fk_Fog(bool argNewFlg);
		~fk_Fog();
		!fk_Fog();

		property fk_FogMode FogMode {
			void set(fk_FogMode);
			fk_FogMode get();
		}

		property fk_FogOption FogOption {
			void set(fk_FogOption);
			fk_FogOption get();
		}

		property double FogDensity {
			void set(double);
			double get(void);
		}

		property double FogLinearStart {
			void set(double);
			double get(void);
		}

		property double FogLinearEnd {
			void set(double);
			double get(void);
		}

		property fk_Color^ FogColor {
			void set(fk_Color^);
			fk_Color^ get();
		}

		void setFogColor(float r, float g, float b, float a);
		void setFogColor(double r, double g, double b, double a);
	};
}
