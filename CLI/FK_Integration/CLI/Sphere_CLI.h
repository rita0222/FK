// IndexFace_CLI.h

#pragma once

#include <FK/Sphere.h>
#include "IndexFace_CLI.h"
#include "Vector_CLI.h"

using namespace std;
using namespace System;

namespace FK_CLI
{
	public ref class fk_Sphere : fk_IndexFaceSet {
	internal:
		::fk_Sphere * GetP(void)
		{
			return reinterpret_cast<::fk_Sphere *>(this->pBase);
		}

	public:
		fk_Sphere::fk_Sphere() : fk_IndexFaceSet(false)
		{
			::fk_Sphere *p = new ::fk_Sphere();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Sphere::fk_Sphere(bool argNewFlg) : fk_IndexFaceSet(false)
		{
			if(argNewFlg == true) {
				::fk_Sphere *p = new ::fk_Sphere();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_Sphere::fk_Sphere(int argDiv, double argRad) : fk_IndexFaceSet(false)
		{
			::fk_Sphere *p = new ::fk_Sphere(argDiv, argRad);
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Sphere::~fk_Sphere()
		{
			this->!fk_Sphere();
		}

		fk_Sphere::!fk_Sphere()
		{
			delete this->pBase;
			this->pBase = NULL;
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
