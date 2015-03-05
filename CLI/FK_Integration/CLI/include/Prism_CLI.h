// Prism_CLI.h

#pragma once

#include <FK/Prism.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	public ref class fk_Prism : fk_IndexFaceSet {
	internal:
		::fk_Prism * GetP(void);

	public:
		fk_Prism();
		fk_Prism(bool argNewFlg);
		fk_Prism(int argDiv, double argTop, double argBottom, double argHeight);
		~fk_Prism();
		!fk_Prism();

		void SetDivide(int div);
		void SetTopRadius(double radius);
		void SetBottomRadius(double radius);
		void SetHeight(double height);
	};
}
