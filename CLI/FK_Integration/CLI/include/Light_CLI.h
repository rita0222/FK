// Light_CLI.h

#pragma once

#include <FK/Light.h>
#include "Shape_CLI.h"

namespace FK_CLI
{
	public enum class fk_LightType {
		PARALLEL,
		POINT,
		SPOT
	};

	public ref class fk_Light : fk_Shape {
	internal:
		::fk_Light * GetP(void);

	public:
		fk_Light();
		fk_Light(bool argNewFlg);
		~fk_Light();
		!fk_Light();

		property fk_LightType Type {
			void set(fk_LightType);
			fk_LightType get();
		}

		property double SpotCutOff {
			void set(double);
			double get();
		}
		
		property double SpotExponent {
			void set(double);
			double get();
		}

		void SetAttenuation(double k_l, double k_q, double k_c);
		void SetAttenuation(double k_l, double k_q);
		double GetAttenuation(int num);
	};
}
