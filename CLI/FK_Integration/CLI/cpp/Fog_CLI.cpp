#include "Fog_CLI.h"

namespace FK_CLI {

	void fk_Fog::setFogMode(fk_FogMode argMode)
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
			   
	void fk_Fog::setFogOption(fk_FogOption argOpt)
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

	void fk_Fog::setFogDensity(double argD)
	{
		GetP()->setFogDensity(argD);
	}

	void fk_Fog::setFogLinearMap(double argS, double argE)
	{
		GetP()->setFogLinearMap(argS, argE);
	}

	void fk_Fog::setFogColor(fk_Color^ argCol)
	{
		GetP()->setFogColor(*argCol->GetP());
	}

	void fk_Fog::setFogColor(float argR, float argG, float argB, float argA)
	{
		GetP()->setFogColor(argR, argG, argB, argA);
	}
									
	void fk_Fog::setFogColor(double argR, double argG, double argB, double argA)
	{
		GetP()->setFogColor(argR, argG, argB, argA);
	}

	fk_FogMode fk_Fog::getFogMode(void)
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
		
	fk_FogOption fk_Fog::getFogOption(void)
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

	double fk_Fog::getFogDensity(void)
	{
		return GetP()->getFogDensity();
	}

	double fk_Fog::getFogLinearStart(void)
	{
		return GetP()->getFogLinearStart();
	}
		
	double fk_Fog::getFogLinearEnd(void)
	{
		return GetP()->getFogLinearEnd();
	}
		
	fk_Color^ fk_Fog::getFogColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		::fk_Color tmpC = GetP()->getFogColor();
		C->set(tmpC.getR(), tmpC.getG(), tmpC.getB(), tmpC.getA());
		return C;
	}
}
