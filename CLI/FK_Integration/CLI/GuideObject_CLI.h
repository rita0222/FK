// Matrix_CLI.h

#pragma once

#include <FK/GuideObject.h>
#include "Base_CLI.h"
#include "Model_CLI.h"
#include "Scene_CLI.h"

namespace FK_CLI {
	using namespace std;
	using namespace System;

	public enum class fk_GuideMode : int {
		NO_GUIDE = 0x0000,
		AXIS_X   = 0x0001,
		AXIS_Y   = 0x0002,
		AXIS_Z   = 0x0004,
		GRID_XZ  = 0x0008,
		GRID_XY  = 0x0010,
		GRID_YZ  = 0x0020,
		ALL_GUIDE = FK_AXIS_X | FK_AXIS_Y | FK_AXIS_Z | FK_GRID_XZ | FK_GRID_XY | FK_GRID_YZ
	};
		
	public ref class fk_GuideObject : fk_BaseObject {
	internal:
		::fk_GuideObject * GetP(void)
		{
			return reinterpret_cast<::fk_GuideObject *>(this->pBase);
		}
		
	public:
		fk_GuideObject::fk_GuideObject() : fk_BaseObject(false)
		{
			::fk_GuideObject *p = new ::fk_GuideObject();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_GuideObject::fk_GuideObject(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				::fk_GuideObject *p = new ::fk_GuideObject();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_GuideObject::~fk_GuideObject()
		{
			this->!fk_GuideObject();
		}

		fk_GuideObject::!fk_GuideObject()
		{
			if(dFlg == true) delete this->pBase;
			this->pBase = NULL;
		}

		void setAxisWidth(double argWidth)
		{
			GetP()->setAxisWidth(argWidth);
		}

		void setGridWidth(double argWidth)
		{
			GetP()->setGridWidth(argWidth);
		}

		void setScale(double argScale)
		{
			GetP()->setScale(argScale);
		}

		void setNum(int argNum)
		{
			GetP()->setNum(argNum);
		}
		
		void entryScene(fk_Scene ^argS, fk_GuideMode argMode)
		{
			GetP()->entryScene(argS->GetP(), int(argMode));
		}
		
		void removeScene(fk_Scene ^argS)
		{	
			GetP()->removeScene(argS->GetP());
		}
	};
}
