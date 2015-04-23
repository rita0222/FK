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
		ALL_GUIDE = AXIS_X | AXIS_Y | AXIS_Z | GRID_XZ | GRID_XY | GRID_YZ
	};
		
	public ref class fk_GuideObject {
	internal:
		bool dFlg;
		::fk_GuideObject *pGuide;
		::fk_GuideObject * GetP(void);
		
	public:
		fk_GuideObject();
		fk_GuideObject(bool argNewFlg);
		~fk_GuideObject();
		!fk_GuideObject();

		property double AxisWidth {
			void set(double);
		}

		property double GridWidth {
			void set(double);
		}

		property double Scale {
			void set(double);
		}

		property int Num {
			void set(int);
		}

		void EntryScene(fk_Scene^ scene, fk_GuideMode mode);
		void RemoveScene(fk_Scene^ scene);
	};
}
