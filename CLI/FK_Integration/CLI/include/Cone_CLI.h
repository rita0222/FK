// Cone_CLI.h

#pragma once

#include <FK/Cone.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	public ref class fk_Cone : fk_IndexFaceSet {
	internal:
		::fk_Cone * GetP(void)
		{
			return (::fk_Cone *)(pBase);
		}

	public:
		fk_Cone::fk_Cone() : fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Cone();
		}

		fk_Cone::fk_Cone(bool argNewFlg) : fk_IndexFaceSet(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_Cone();
			}
				
		}

		fk_Cone::fk_Cone(int argDiv, double argRad, double argHeight)
			: fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Cone(argDiv, argRad, argHeight);
		}

		fk_Cone::~fk_Cone()
		{
			this->!fk_Cone();
		}

		fk_Cone::!fk_Cone()
		{
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void setDivide(int dniv);
		void setRadius(double radius);
		void setHeight(double height);
	};
}
