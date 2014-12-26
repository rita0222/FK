// Light_CLI.h

#pragma once

#include <FK/Light.h>
#include "Shape_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;
	using namespace msclr::interop;

	public enum class fk_LightType
	{
		PARALLEL,
		POINT,
		SPOT
	};

	public ref class fk_Light : FK_CLI::fk_Shape {
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

		void setLightType(fk_LightType argType)
		{
			switch(argType) {
			  case fk_LightType::PARALLEL:
				GetP()->setLightType(::fk_LightType::FK_PARALLEL_LIGHT);
				break;
				
			  case fk_LightType::POINT:
				GetP()->setLightType(::fk_LightType::FK_POINT_LIGHT);
				break;

			  case fk_LightType::SPOT:
				GetP()->setLightType(::fk_LightType::FK_SPOT_LIGHT);
				break;
			}
		}

		fk_LightType getLightType(void)
		{
			switch(GetP()->getLightType()) {
			  case ::fk_LightType::FK_PARALLEL_LIGHT:
				return fk_LightType::PARALLEL;
				
			  case ::fk_LightType::FK_POINT_LIGHT:
				return fk_LightType::POINT;
				
			  case ::fk_LightType::FK_SPOT_LIGHT:
				return fk_LightType::SPOT;
			}
			return fk_LightType::PARALLEL;
		}

		void setAttenuation(double arg_kl, double arg_kq, double arg_kc)
		{
			GetP()->setAttenuation(arg_kl, arg_kq, arg_kc);
		}

		void setAttenuation(double arg_kl, double arg_kq)
		{
			GetP()->setAttenuation(arg_kl, arg_kq, 1.0);
		}

		void setSpotCutOff(double argTheta)
		{
			GetP()->setSpotCutOff(argTheta);
		}

		void setSpotExponent(double argAlpha)
		{
			GetP()->setSpotExponent(argAlpha);
		}

		double getAttenuation(int argNum)
		{
			return GetP()->getAttenuation(argNum);
		}

		double getSpotCutOff(void)
		{
			return GetP()->getSpotCutOff();
		}

		double getSpotExponent(void)
		{
			return GetP()->getSpotExponent();
		}
	};
}
