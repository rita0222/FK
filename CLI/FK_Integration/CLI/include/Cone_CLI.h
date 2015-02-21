// Cone_CLI.h

#pragma once

#include <FK/Cone.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	public ref class fk_Cone : fk_IndexFaceSet {
	internal:
		::fk_Cone * GetP(void);

	public:
		fk_Cone();
		fk_Cone(bool argNewFlg);
		fk_Cone(int argDiv, double argRad, double argHeight);
		~fk_Cone();
		!fk_Cone();

		void SetDivide(int dniv);
		void SetRadius(double radius);
		void SetHeight(double height);
	};
}
