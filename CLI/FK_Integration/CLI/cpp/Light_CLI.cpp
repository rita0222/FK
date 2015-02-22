#include "Light_CLI.h"

namespace FK_CLI {

	::fk_Light * fk_Light::GetP(void)
	{
		return (::fk_Light *)(this->pBase);
	}

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
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_Light::Type::set(fk_LightType argType)
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

	fk_LightType fk_Light::Type::get(void)
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


	void fk_Light::SpotCutOff::set(double argTheta)
	{
		GetP()->setSpotCutOff(argTheta);
	}

	double fk_Light::SpotCutOff::get(void)
	{
		return GetP()->getSpotCutOff();
	}

	void fk_Light::SpotExponent::set(double argAlpha)
	{
		GetP()->setSpotExponent(argAlpha);
	}

	double fk_Light::SpotExponent::get(void)
	{
		return GetP()->getSpotExponent();
	}

	void fk_Light::SetAttenuation(double arg_kl, double arg_kq, double arg_kc)
	{
		GetP()->setAttenuation(arg_kl, arg_kq, arg_kc);
	}

	void fk_Light::SetAttenuation(double arg_kl, double arg_kq)
	{
		GetP()->setAttenuation(arg_kl, arg_kq, 1.0);
	}

	double fk_Light::GetAttenuation(int argNum)
	{
		return GetP()->getAttenuation(argNum);
	}
}
