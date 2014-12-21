// Scene_CLI.h

#pragma once

#include <FK/Scene.h>
#include "Base_CLI.h"
#include "Model_CLI.h"
#include "Projection_CLI.h"

using namespace std;
using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace FK_CLI
{
	public enum class fk_StereoChannel
	{
		STEREO_LEFT,
		STEREO_RIGHT
	};

	public enum class fk_FogMode
	{
		LINEAR_FOG,
		EXP_FOG,
		EXP2_FOG,
		NONE_FOG
	};

	public enum class fk_FogOption
	{
		FASTEST_FOG,
		NICEST_FOG,
		NOOPTION_FOG
	};

	::fk_StereoChannel GetStereo(FK_CLI::fk_StereoChannel);
	
	public ref class fk_Scene : fk_BaseObject
	{
	internal:
		List<fk_Model^>^	modelList;
		List<fk_Model^>^	overlayList;
		fk_Model^			defCamera;
		fk_Model^		   	camera;
		fk_Model^			leftCamera;
		fk_Model^			rightCamera;
		
		::fk_Scene * GetP(void)
		{
			return reinterpret_cast<::fk_Scene *>(this->pBase);
		}

	public:
		fk_Scene::fk_Scene(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				::fk_Scene *p = new ::fk_Scene();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
				modelList = gcnew List<fk_Model^>();
				overlayList = gcnew List<fk_Model^>();
				defCamera = gcnew fk_Model();
				p->entryCamera(defCamera->GetP());
				camera = defCamera;
			}
		}

		fk_Scene::fk_Scene() : fk_BaseObject(false)
		{
			Console::WriteLine("OK0");
			::fk_Scene *p = new ::fk_Scene();
			Console::WriteLine("OK1");
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			modelList = gcnew List<fk_Model^>();
			overlayList = gcnew List<fk_Model^>();
			defCamera = gcnew fk_Model();
			p->entryCamera(defCamera->GetP());
			camera = defCamera;
			Console::WriteLine("OK2");
		}

		fk_Scene::~fk_Scene()
		{
			this->!fk_Scene();
		}

		fk_Scene::!fk_Scene()
		{
			delete this->pBase;
			this->pBase = NULL;
		}

		// from fk_DisplayLink

		void clearDisplay(void)
		{
			GetP()->clearDisplay();
			modelList->Clear();
			overlayList->Clear();
			camera = defCamera;
		}

		void entryModel(fk_Model ^argM)
		{
			removeModel(argM);
			modelList->Add(argM);
			GetP()->entryModel(argM->GetP());
		}			

		void removeModel(fk_Model ^argM)
		{
			while(modelList->Contains(argM) == true) {
				modelList->Remove(argM);
			}
			GetP()->removeModel(argM->GetP());
		}

		void clearModel(void)
		{
			modelList->Clear();
			GetP()->clearModel();
		}

		void entryOverlayModel(fk_Model ^argM)
		{
			removeOverlayModel(argM);
			overlayList->Add(argM);
			GetP()->entryOverlayModel(argM->GetP());
		}
		
		void removeOverlayModel(fk_Model^ argM)
		{
			while(overlayList->Contains(argM) == true) {
				overlayList->Remove(argM);
			}
			GetP()->removeOverlayModel(argM->GetP());
		}
			
		void clearOverlayModel(void)
		{
			overlayList->Clear();
			GetP()->clearOverlayModel();
		}

		void entryCamera(fk_Model ^argM)
		{
			camera = argM;
			GetP()->entryCamera(argM->GetP());
		}

		fk_Model^ getCamera(void)
		{
			return camera;
		}
				
		void setProjection(fk_ProjectBase ^argP)
		{
			GetP()->setProjection(argP->GetP());
		}

		void entryStereoCamera(fk_StereoChannel argChannel, fk_Model^ argM)
		{
			GetP()->entryStereoCamera(GetStereo(argChannel), argM->GetP());
		}

		void setStereoProjection(fk_StereoChannel argChannel, fk_ProjectBase ^argP)
		{
			GetP()->setStereoProjection(GetStereo(argChannel), argP->GetP());
		}

		void clearStereo(void)
		{
			GetP()->clearStereo();
		}

		void setStereoOverlayMode(bool argMode)
		{
			GetP()->setStereoOverlayMode(argMode);
		}

		bool getStereoOverlayMode(void)
		{
			return GetP()->getStereoOverlayMode();
		}

		// from fk_Fog

		void setFogMode(fk_FogMode argMode)
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
			   
		void setFogOption(fk_FogOption argOpt)
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

		void setFogDensity(double argD)
		{
			GetP()->setFogDensity(argD);
		}

		void setFogLinearMap(double argS, double argE)
		{
			GetP()->setFogLinearMap(argS, argE);
		}

		void setFogColor(fk_Color^ argCol)
		{
			GetP()->setFogColor(*argCol->GetP());
		}

		void setFogColor(float argR, float argG, float argB, float argA)
		{
			GetP()->setFogColor(argR, argG, argB, argA);
		}
									
		void setFogColor(double argR, double argG, double argB, double argA)
		{
			GetP()->setFogColor(argR, argG, argB, argA);
		}

		fk_FogMode getFogMode(void)
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
		
		fk_FogOption getFogOption(void)
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

		double getFogDensity(void)
		{
			return GetP()->getFogDensity();
		}

		double getFogLinearStart(void)
		{
			return GetP()->getFogLinearStart();
		}
		
		double getFogLinearEnd(void)
		{
			return GetP()->getFogLinearEnd();
		}
		
		fk_Color^ getFogColor(void)
		{
			fk_Color^ C = gcnew fk_Color();
			::fk_Color tmpC = GetP()->getFogColor();
			C->set(tmpC.getR(), tmpC.getG(), tmpC.getB(), tmpC.getA());
			return C;
		}

		// from fk_Scene
		void setBGColor(fk_Color^ argCol)
		{
			GetP()->setBGColor(*argCol->GetP());
		}

		void setBGColor(float argR, float argG, float argB)
		{
			GetP()->setBGColor(argR, argG, argB);
		}

		fk_Color^ getBGColor(void)
		{
			fk_Color^ C = gcnew fk_Color();
			::fk_Color tmpC = GetP()->getBGColor();
			C->set(tmpC.getR(), tmpC.getG(), tmpC.getB(), tmpC.getA());
			return C;
		}

		void setBlendStatus(bool argMode)
		{
			GetP()->setBlendStatus(argMode);
		}

		bool getBlendStatus(void)
		{
			return GetP()->getBlendStatus();
		}
	};
}
