// Block_CLI.h

#pragma once

#include <FK/Capsule.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	public ref class fk_Capsule : FK_CLI::fk_IndexFaceSet {
	internal:
		::fk_Capsule * GetP(void)
		{
			return (::fk_Capsule *)(pBase);
		}

	public:
		fk_Capsule::fk_Capsule() : fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Capsule();
		}

		fk_Capsule::fk_Capsule(bool argNewFlg) : fk_IndexFaceSet(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_Capsule();
			}
				
		}

		fk_Capsule::fk_Capsule(int argDiv, double argLen, double argRad)
			: fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Capsule(argDiv, argLen, argRad);
		}

		fk_Capsule::~fk_Capsule()
		{
			this->!fk_Capsule();
		}

		fk_Capsule::!fk_Capsule()
		{
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void setDivide(int div);
		void setLength(double length);
		void setRadius(double radius);
		void setScale(double scale);
	};
}
