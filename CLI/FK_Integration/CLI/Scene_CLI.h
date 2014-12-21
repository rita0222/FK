// Scene_CLI.h

#pragma once

#include <FK/Scene.h>
#include "Base_CLI.h"
#include "Model_CLI.h"

using namespace std;
using namespace System;

namespace FK_CLI
{
	public enum class fk_StereoChannel
	{
		FK_STEREO_LEFT,
		FK_STEREO_RIGHT
	};

	public enum class fk_FogMode
	{
		FK_LINEAR_FOG,
		FK_EXP_FOG,
		FK_EXP2_FOG,
		FK_NONE_FOG
	};

	public enum class fk_FogOption
	{
		FK_FASTEST_FOG,
		FK_NICEST_FOG,
		FK_NOOPTION_FOG
	};

	public ref class fk_Scene : fk_BaseObject
	{
	internal:
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
			}
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

		/*
		// from fk_DisplayLink

		void					clearDisplay(void);
		void					entryModel(fk_Model *model);
		void					removeModel(fk_Model *model);
		void					clearModel(void);
		void					entryOverlayModel(fk_Model *model);
		void					removeOverlayModel(fk_Model *model);
		void					clearOverlayModel(void);
		void					entryCamera(fk_Model *model);
		const fk_Model *		getCamera(void) const;
		void					setProjection(fk_ProjectBase *proj);
		const fk_ProjectBase *	getProjection(void) const;
		void					entryStereoCamera(fk_StereoChannel channel, fk_Model *model);
		void					setStereoProjection(fk_StereoChannel channel, fk_ProjectBase *proj);
		const fk_Model *		getStereoCamera(fk_StereoChannel channel);
		const fk_ProjectBase *	getStereoProjection(fk_StereoChannel channel);
		void					clearStereo(void);
		void	setStereoOverlayMode(bool mode);
		bool	getStereoOverlayMode(void);

		// from fk_Fog
		void			setFogMode(const fk_FogMode mode);
		void			setFogOption(const fk_FogOption opt);
		void			setFogDensity(const double d);
		void			setFogLinearMap(const double S, const double E);
		void			setFogColor(const fk_Color col);
		void			setFogColor(const float r, const float g,
									const float b, const float a);
		void			setFogColor(const double r, const double g,
									const double b, const double a);
		fk_FogMode		getFogMode(void) const;
		fk_FogOption	getFogOption(void) const;
		double			getFogDensity(void) const;
		double			getFogLinearStart(void) const;
		double			getFogLinearEnd(void) const;
		fk_Color		getFogColor(void) const;

		// from fk_Scene
		void			setBGColor(fk_Color col);
		void			setBGColor(float r, float g, float b);
		fk_Color		getBGColor(void);
		void			setBlendStatus(bool mode);
		bool			getBlendStatus(void);
		*/
	};
}
