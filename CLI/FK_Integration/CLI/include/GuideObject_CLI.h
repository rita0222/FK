// Matrix_CLI.h

#pragma once

#include <FK/GuideObject.h>
#include "Base_CLI.h"
#include "Model_CLI.h"
#include "Scene_CLI.h"

namespace FK_CLI {
	public enum class fk_GuideMode : int {
		NO_GUIDE = 0x0000,
		AXIS_X   = 0x0001,
		AXIS_Y   = 0x0002,
		AXIS_Z   = 0x0004,
		GRID_XZ  = 0x0008,
		GRID_XY  = 0x0010,
		GRID_YZ  = 0x0020,
		ALL_GUIDE = FK_AXIS_X | FK_AXIS_Y | FK_AXIS_Z |
					FK_GRID_XZ | FK_GRID_XY | FK_GRID_YZ
	};
		
	public ref class fk_GuideObject {
	internal:
		bool dFlg;
		::fk_GuideObject *pGuide;

		::fk_GuideObject * GetP(void)
		{
			return pGuide;
		}
		
	public:
		fk_GuideObject::fk_GuideObject()
		{
			pGuide = new ::fk_GuideObject();
			dFlg = true;
		}

		fk_GuideObject::fk_GuideObject(bool argNewFlg)
		{
			if(argNewFlg == true) pGuide = new ::fk_GuideObject();
			dFlg = argNewFlg;
		}

		fk_GuideObject::~fk_GuideObject()
		{
			if(pGuide == nullptr) return;
			if(dFlg == true) delete pGuide;
			pGuide = nullptr;
		}

		fk_GuideObject::!fk_GuideObject()
		{
			if(pGuide == nullptr) return;
			if(dFlg == true) {
				pGuide->SetFinalizeMode();
				delete pGuide;
			}
			pGuide = nullptr;
		}

		void setAxisWidth(double width);
		void setGridWidth(double width);
		void setScale(double scale);
		void setNum(int num);
		void entryScene(fk_Scene^ scene, fk_GuideMode mode);
		void removeScene(fk_Scene^ scene);
	};
}
