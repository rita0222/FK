// IndexFace_CLI.h

#pragma once

#include <FK/Sphere.h>
#include "IndexFace_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

	public ref class fk_Sphere : FK_CLI::fk_IndexFaceSet {
	internal:
		::fk_Sphere * GetP(void)
		{
			return (::fk_Sphere *)(pBase);
		}

	public:
		fk_Sphere::fk_Sphere() : fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Sphere();
		}

		fk_Sphere::fk_Sphere(bool argNewFlg) : fk_IndexFaceSet(false)
		{
			if(argNewFlg == true) pBase = new ::fk_Sphere();
		}

		fk_Sphere::fk_Sphere(int argDiv, double argRad) : fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Sphere(argDiv, argRad);
		}

		fk_Sphere::~fk_Sphere()
		{
			this->!fk_Sphere();
		}

		fk_Sphere::!fk_Sphere()
		{
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void setDivide(int argDiv)
		{
			GetP()->setDivide(argDiv);
		}

		void setRadius(double argRad)
		{
			GetP()->setRadius(argRad);
		}

		void setScale(double argScale)
		{
			GetP()->setScale(argScale);
		}
	};
}
