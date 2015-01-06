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
		::fk_Light * GetP(void)
		{
			return (::fk_Light *)(this->pBase);
		}

	public:
		fk_Light::fk_Light() : fk_Shape(false)
		{
			this->pBase = new ::fk_Light();
		}

		fk_Light::fk_Light(bool argNewFlg) : fk_Shape(false)
		{
			if(argNewFlg == true) this->pBase = new ::fk_Light();
		}

		fk_Light::~fk_Light()
		{
			this->!fk_Light();
		}

		fk_Light::!fk_Light()
		{
			if(dFlg == true) delete this->pBase;
			this->pBase = NULL;
		}

		void setLightType(fk_LightType type);
		fk_LightType getLightType(void);
		void setAttenuation(double k_l, double k_q, double k_c);
		void setAttenuation(double k_l, double k_q);
		void setSpotCutOff(double theta);
		void setSpotExponent(double alpha);
		double getAttenuation(int num);
		double getSpotCutOff(void);
		double getSpotExponent(void);
	};
}
