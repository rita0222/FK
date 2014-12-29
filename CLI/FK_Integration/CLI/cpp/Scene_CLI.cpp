#include "Scene_CLI.h"

namespace FK_CLI {
	::fk_StereoChannel fk_Scene::GetStereo(FK_CLI::fk_StereoChannel argC)
	{
		if(argC == fk_StereoChannel::STEREO_LEFT) {
			return FK_STEREO_LEFT;
		}
		return FK_STEREO_RIGHT;
	}

	void fk_Scene::clearDisplay(void)
	{
		GetP()->clearDisplay();
	}

	void fk_Scene::entryModel(fk_Model ^argM)
	{
		GetP()->entryModel(argM->GetP());
	}			

	void fk_Scene::removeModel(fk_Model ^argM)
	{
		GetP()->removeModel(argM->GetP());
	}

	void fk_Scene::clearModel(void)
	{
		GetP()->clearModel();
	}

	void fk_Scene::entryOverlayModel(fk_Model ^argM)
	{
		GetP()->entryOverlayModel(argM->GetP());
	}
		
	void fk_Scene::removeOverlayModel(fk_Model^ argM)
	{
		GetP()->removeOverlayModel(argM->GetP());
	}
			
	void fk_Scene::clearOverlayModel(void)
	{
		GetP()->clearOverlayModel();
	}

	void fk_Scene::entryCamera(fk_Model ^argM)
	{
		GetP()->entryCamera(argM->GetP());
	}

	fk_Model^ fk_Scene::getCamera(void)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pModel = const_cast<::fk_Model *>(GetP()->getCamera());
		M->dFlg = false;
		return M;
	}
				
	void fk_Scene::setProjection(fk_ProjectBase ^argP)
	{
		GetP()->setProjection(argP->GetP());
	}

	void fk_Scene::entryStereoCamera(fk_StereoChannel argChannel, fk_Model^ argM)
	{
		GetP()->entryStereoCamera(GetStereo(argChannel), argM->GetP());
	}

	void fk_Scene::setStereoProjection(fk_StereoChannel argChannel, fk_ProjectBase ^argP)
	{
		GetP()->setStereoProjection(GetStereo(argChannel), argP->GetP());
	}

	void fk_Scene::clearStereo(void)
	{
		GetP()->clearStereo();
	}

	void fk_Scene::setStereoOverlayMode(bool argMode)
	{
		GetP()->setStereoOverlayMode(argMode);
	}

	bool fk_Scene::getStereoOverlayMode(void)
	{
		return GetP()->getStereoOverlayMode();
	}

	// from fk_Fog

	void fk_Scene::setFogMode(fk_FogMode argMode)
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
			   
	void fk_Scene::setFogOption(fk_FogOption argOpt)
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

	void fk_Scene::setFogDensity(double argD)
	{
		GetP()->setFogDensity(argD);
	}

	void fk_Scene::setFogLinearMap(double argS, double argE)
	{
		GetP()->setFogLinearMap(argS, argE);
	}

	void fk_Scene::setFogColor(fk_Color^ argCol)
	{
		GetP()->setFogColor(*argCol->GetP());
	}

	void fk_Scene::setFogColor(float argR, float argG, float argB, float argA)
	{
		GetP()->setFogColor(argR, argG, argB, argA);
	}
									
	void fk_Scene::setFogColor(double argR, double argG, double argB, double argA)
	{
		GetP()->setFogColor(argR, argG, argB, argA);
	}

	fk_FogMode fk_Scene::getFogMode(void)
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
		
	fk_FogOption fk_Scene::getFogOption(void)
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

	double fk_Scene::getFogDensity(void)
	{
		return GetP()->getFogDensity();
	}

	double fk_Scene::getFogLinearStart(void)
	{
		return GetP()->getFogLinearStart();
	}
		
	double fk_Scene::getFogLinearEnd(void)
	{
		return GetP()->getFogLinearEnd();
	}
		
	fk_Color^ fk_Scene::getFogColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		::fk_Color tmpC = GetP()->getFogColor();
		C->set(tmpC.getR(), tmpC.getG(), tmpC.getB(), tmpC.getA());
		return C;
	}

	// from fk_Scene
	void fk_Scene::setBGColor(fk_Color^ argCol)
	{
		GetP()->setBGColor(*argCol->GetP());
	}

	void fk_Scene::setBGColor(float argR, float argG, float argB)
	{
		GetP()->setBGColor(argR, argG, argB);
	}

	fk_Color^ fk_Scene::getBGColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		::fk_Color tmpC = GetP()->getBGColor();
		C->set(tmpC.getR(), tmpC.getG(), tmpC.getB(), tmpC.getA());
		return C;
	}

	void fk_Scene::setBlendStatus(bool argMode)
	{
		GetP()->setBlendStatus(argMode);
	}

	bool fk_Scene::getBlendStatus(void)
	{
		return GetP()->getBlendStatus();
	}
}
