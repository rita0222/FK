// Modify_CLI.h

#pragma once

#include <FK/SolidBase.h>
#include "Modify_CLI.h"

namespace FK_CLI
{
	public ref class fk_SolidBase : fk_Modify {
	internal:
		::fk_SolidBase * GetP(void)
		{
			return (::fk_SolidBase *)(pBase);
		}

	public:
		fk_SolidBase::fk_SolidBase(bool argNewFlg) : fk_Modify(false)
		{
		}

		fk_SolidBase::~fk_SolidBase()
		{
			this->!fk_SolidBase();
		}

		fk_SolidBase::!fk_SolidBase()
		{
		}

		void makeIFSet(int faceNum, int polyNum, array<int>^ IFSet,
					   int vertexNum, array<fk_Vector^>^ posArray, int order);
		void makeIFSet(int faceNum, int polyNum, array<int>^ IFSet,
					   int vertexNum, array<fk_Vector^>^ posArray);

		void makeIFSet(array< array<int>^ >^ faceArray,
					   array<fk_Vector^>^ posArray, int order);
		void makeIFSet(array< array<int>^ >^ faceArray,
					   array<fk_Vector^>^ posArray);
	};
}
