#include "Light_CLI.h"

namespace FK_CLI {
	void fk_Light::setLightType(fk_LightType argType)
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

	fk_LightType fk_Light::getLightType(void)
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

	void fk_Light::setAttenuation(double arg_kl, double arg_kq, double arg_kc)
	{
		GetP()->setAttenuation(arg_kl, arg_kq, arg_kc);
	}

	void fk_Light::setAttenuation(double arg_kl, double arg_kq)
	{
		GetP()->setAttenuation(arg_kl, arg_kq, 1.0);
	}

	void fk_Light::setSpotCutOff(double argTheta)
	{
		GetP()->setSpotCutOff(argTheta);
	}

	void fk_Light::setSpotExponent(double argAlpha)
	{
		GetP()->setSpotExponent(argAlpha);
	}

	double fk_Light::getAttenuation(int argNum)
	{
		return GetP()->getAttenuation(argNum);
	}

	double fk_Light::getSpotCutOff(void)
	{
		return GetP()->getSpotCutOff();
	}

	double fk_Light::getSpotExponent(void)
	{
		return GetP()->getSpotExponent();
	}
}
