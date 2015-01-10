// Scene_CLI.h

#pragma once

#include <FK/Scene.h>
#include "Fog_CLI.h"

namespace FK_CLI
{
	public ref class fk_Scene : fk_Fog {
	internal:

		::fk_Scene * GetP(void)
		{
			return (::fk_Scene *)(pBase);
		}

	public:
		fk_Scene::fk_Scene(bool argNewFlg) : fk_Fog(false)
		{
			if(argNewFlg == true) pBase = new ::fk_Scene();
		}

		fk_Scene::fk_Scene() : fk_Fog(false)
		{
			pBase = new ::fk_Scene();
		}

		fk_Scene::~fk_Scene()
		{
			if(pBase == NULL) return;
			if(dFlg == true) delete GetP();
			pBase = NULL;
		}

		fk_Scene::!fk_Scene()
		{
			if(pBase == NULL) return;
			if(dFlg == true) {
				GetP()->SetFinalizeMode();
				delete GetP();
			}
			pBase = NULL;
		}

		void setBGColor(fk_Color^ color);
		void setBGColor(float r, float g, float b);
		fk_Color^ getBGColor(void);
		void setBlendStatus(bool mode);
		bool getBlendStatus(void);
	};
}
