// IndexFace_CLI.h

#pragma once

#include <FK/Sphere.h>
#include "IndexFace_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	public ref class fk_Sphere : fk_IndexFaceSet {
	internal:
		::fk_Sphere * GetP(void);

	public:
		fk_Sphere();
		fk_Sphere(bool argNewFlg);
		fk_Sphere(int argDiv, double argRad);
		~fk_Sphere();
		!fk_Sphere();

		void SetDivide(int div);
		void SetRadius(double radius);
		void SetScale(double scale);
	};
}
