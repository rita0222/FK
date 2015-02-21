// Circle_CLI.h

#pragma once

#include <FK/Circle.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	public ref class fk_Circle : fk_IndexFaceSet {
	internal:
		::fk_Circle * GetP(void);

	public:
		fk_Circle();
		fk_Circle(bool argNewFlg);
		fk_Circle(int argDiv, double argRad);
		~fk_Circle();
		!fk_Circle();

		void SetDivide(int div);
		void SetRadius(double radius);
		void SetScale(double scale);
	};
}
