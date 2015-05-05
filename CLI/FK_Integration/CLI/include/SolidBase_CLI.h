// Modify_CLI.h

#pragma once

#include <FK/SolidBase.h>
#include "Modify_CLI.h"

namespace FK_CLI
{
	public ref class fk_SolidBase : fk_Modify {
	internal:
		::fk_SolidBase * GetP(void);

	public:
		fk_SolidBase(bool argNewFlg);
		~fk_SolidBase();
		!fk_SolidBase();

		void MakeIFSet(int faceNum, int polyNum, array<int>^ IFSet,
					   int vertexNum, array<fk_Vector^>^ posArray, int order);
		void MakeIFSet(int faceNum, int polyNum, array<int>^ IFSet,
					   int vertexNum, array<fk_Vector^>^ posArray);

		void MakeIFSet(array< array<int>^ >^ faceArray,
					   array<fk_Vector^>^ posArray, int order);
		void MakeIFSet(array< array<int>^ >^ faceArray,
					   array<fk_Vector^>^ posArray);
	};
}
