// Circle_CLI.h

#pragma once

#include <FK/Circle.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	public ref class fk_Circle : fk_IndexFaceSet {
	internal:
		::fk_Circle * GetP(void)
		{
			return (::fk_Circle *)(pBase);
		}

	public:
		fk_Circle::fk_Circle() : fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Circle();
		}

		fk_Circle::fk_Circle(bool argNewFlg) : fk_IndexFaceSet(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_Circle();
			}
				
		}

		fk_Circle::fk_Circle(int argDiv, double argRad) : fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Circle(argDiv, argRad);
		}

		fk_Circle::~fk_Circle()
		{
			this->!fk_Circle();
		}

		fk_Circle::!fk_Circle()
		{
			if(pBase == nullptr) return;
			if(dFlg == true) delete GetP();
			pBase = nullptr;
		}

		void SetDivide(int div);
		void SetRadius(double radius);
		void SetScale(double scale);
	};
}
