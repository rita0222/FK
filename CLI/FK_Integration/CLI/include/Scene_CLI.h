// Scene_CLI.h

#pragma once

#include <FK/Scene.h>
#include "Base_CLI.h"
#include "Model_CLI.h"
#include "Projection_CLI.h"

namespace FK_CLI
{
	public enum class fk_StereoChannel {
		STEREO_LEFT,
		STEREO_RIGHT
	};

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

	public ref class fk_Scene {
	internal:
		bool dFlg;
		::fk_Scene *pScene;

		::fk_Scene * GetP(void)
		{
			return pScene;
		}

		::fk_StereoChannel GetStereo(FK_CLI::fk_StereoChannel);
	
	public:
		fk_Scene::fk_Scene(bool argNewFlg) : dFlg(argNewFlg)
		{
			if(argNewFlg == true) pScene = new ::fk_Scene();
		}

		fk_Scene::fk_Scene() : dFlg(true)
		{
			pScene = new ::fk_Scene();
		}

		fk_Scene::~fk_Scene()
		{
			this->!fk_Scene();
		}

		fk_Scene::!fk_Scene()
		{
			if(dFlg == true) delete pScene;
			pScene = NULL;
		}

		// from fk_DisplayLink
		void clearDisplay(void);
		void entryModel(fk_Model ^model);
		void removeModel(fk_Model ^model);
		void clearModel(void);
		void entryOverlayModel(fk_Model ^model);
		void removeOverlayModel(fk_Model^ model);
		void clearOverlayModel(void);
		void entryCamera(fk_Model ^model);
		fk_Model^ getCamera(void);
		void setProjection(fk_ProjectBase ^argP);
		void entryStereoCamera(fk_StereoChannel channel, fk_Model^ model);
		void setStereoProjection(fk_StereoChannel channel, fk_ProjectBase ^projection);
		void clearStereo(void);
		void setStereoOverlayMode(bool mode);
		bool getStereoOverlayMode(void);

		// from fk_Fog
		void setFogMode(fk_FogMode mode);
		void setFogOption(fk_FogOption opt);
		void setFogDensity(double density);
		void setFogLinearMap(double start, double end);
		void setFogColor(fk_Color^ color);
		void setFogColor(float r, float g, float b, float a);
		void setFogColor(double r, double g, double b, double a);
		fk_FogMode getFogMode(void);
		fk_FogOption getFogOption(void);
		double getFogDensity(void);
		double getFogLinearStart(void);
		double getFogLinearEnd(void);
		fk_Color^ getFogColor(void);

		// from fk_Scene
		void setBGColor(fk_Color^ color);
		void setBGColor(float r, float g, float b);
		fk_Color^ getBGColor(void);
		void setBlendStatus(bool mode);
		bool getBlendStatus(void);
	};
}
