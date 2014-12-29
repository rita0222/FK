// Prism_CLI.h

#pragma once

#include <FK/Prism.h>
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

	public ref class fk_Prism : FK_CLI::fk_IndexFaceSet {
	internal:
		::fk_Prism * GetP(void)
		{
			return (::fk_Prism *)(pBase);
		}

	public:
		fk_Prism::fk_Prism() : fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Prism();
		}

		fk_Prism::fk_Prism(bool argNewFlg) : fk_IndexFaceSet(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_Prism();
			}
				
		}
		
		fk_Prism::fk_Prism(int argDiv, double argTop, double argBottom, double argHeight)
			: fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Prism(argDiv, argTop, argBottom, argHeight);
		}

		fk_Prism::~fk_Prism()
		{
			this->!fk_Prism();
		}

		fk_Prism::!fk_Prism()
		{
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void setDivide(int argDiv)
		{
			GetP()->setDivide(argDiv);
		}

		void setTopRadius(double argRad)
		{
			GetP()->setTopRadius(argRad);
		}

		void setBottomRadius(double argRad)
		{
			GetP()->setBottomRadius(argRad);
		}
		
		void setHeight(double argHeight)
		{
			GetP()->setHeight(argHeight);
		}			
	};
}
