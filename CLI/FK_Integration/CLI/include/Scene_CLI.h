// Scene_CLI.h

#pragma once

#include <FK/Scene.h>
#include "Fog_CLI.h"

namespace FK_CLI
{
	public ref class fk_Scene : fk_Fog {
	internal:

		::fk_Scene * GetP(void);

	public:
		fk_Scene::fk_Scene(bool argNewFlg);
		fk_Scene::fk_Scene();
		fk_Scene::~fk_Scene();
		fk_Scene::!fk_Scene();

		property fk_Color^ BGColor {
			void set(fk_Color^);
			fk_Color^ get();
		}

		property bool BlendStatus {
			void set(bool);
			bool get();
		}
	};
}
