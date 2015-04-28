#include "Fog_CLI.h"

namespace FK_CLI {

	::fk_Fog * fk_Fog::GetP(void)
	{
		return (::fk_Fog *)(pBase);
	}

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

	void fk_Fog::FogMode::set(fk_FogMode argMode)
	{
		switch(argMode) {
		  case fk_FogMode::LINEAR_FOG:
			GetP()->setFogMode(FK_LINEAR_FOG);
			break;
				
		  case fk_FogMode::EXP_FOG:
			GetP()->setFogMode(FK_EXP_FOG);
			break;
				
		  case fk_FogMode::EXP2_FOG:
			GetP()->setFogMode(FK_EXP2_FOG);
			break;

		  default:
			GetP()->setFogMode(FK_NONE_FOG);
			break;
		}
	}

	fk_FogMode fk_Fog::FogMode::get(void)
	{
		switch(GetP()->getFogMode()) {
		  case FK_LINEAR_FOG:
			return fk_FogMode::LINEAR_FOG;

		  case FK_EXP_FOG:
			return fk_FogMode::EXP_FOG;

		  case FK_EXP2_FOG:
			return fk_FogMode::EXP2_FOG;

		  default:
			break;
		}
		return fk_FogMode::NONE_FOG;
	}
			   
	void fk_Fog::FogOption::set(fk_FogOption argOpt)
	{
		switch(argOpt) {
		  case fk_FogOption::FASTEST_FOG:
			GetP()->setFogOption(FK_FASTEST_FOG);
			break;

		  case fk_FogOption::NICEST_FOG:
			GetP()->setFogOption(FK_NICEST_FOG);
			break;

		  default:
			GetP()->setFogOption(FK_NOOPTION_FOG);
			break;
		}
	}

	fk_FogOption fk_Fog::FogOption::get(void)
	{
		switch(GetP()->getFogOption()) {
		  case FK_FASTEST_FOG:
			return fk_FogOption::FASTEST_FOG;
				
		  case FK_NICEST_FOG:
			return fk_FogOption::NICEST_FOG;

		  default:
			break;
		}
		return fk_FogOption::NOOPTION_FOG;
	}

	void fk_Fog::FogDensity::set(double argD)
	{
		GetP()->setFogDensity(argD);
	}

	double fk_Fog::FogDensity::get(void)
	{
		return GetP()->getFogDensity();
	}

	void fk_Fog::FogLinearStart::set(double argS)
	{
		GetP()->setFogLinearMap(argS, GetP()->getFogLinearEnd());
	}

	double fk_Fog::FogLinearStart::get(void)
	{
		return GetP()->getFogLinearStart();
	}

	void fk_Fog::FogLinearEnd::set(double argE)
	{
		GetP()->setFogLinearMap(GetP()->getFogLinearStart(), argE);
	}
		
	double fk_Fog::FogLinearEnd::get(void)
	{
		return GetP()->getFogLinearEnd();
	}

	void fk_Fog::FogColor::set(fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setFogColor(*argCol->GetP());
	}

	fk_Color^ fk_Fog::FogColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		::fk_Color tmpC = GetP()->getFogColor();
		C->Set(tmpC.getR(), tmpC.getG(), tmpC.getB(), tmpC.getA());
		return C;
	}
}
