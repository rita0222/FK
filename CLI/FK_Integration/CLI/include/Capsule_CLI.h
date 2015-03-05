// Block_CLI.h

#pragma once

#include <FK/Capsule.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	public ref class fk_Capsule : fk_IndexFaceSet {
	internal:
		::fk_Capsule * GetP(void);

	public:
		fk_Capsule();
		fk_Capsule(bool argNewFlg);
		fk_Capsule(int argDiv, double argLen, double argRad);
		~fk_Capsule();
		!fk_Capsule();

		void SetDivide(int div);
		void SetLength(double length);
		void SetRadius(double radius);
		void SetScale(double scale);
	};
}
