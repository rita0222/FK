#include "Prism_CLI.h"

namespace FK_CLI {
	::fk_Prism * fk_Prism::GetP(void)
	{
		return (::fk_Prism *)(pBase);
	}

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
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_Prism::SetDivide(int argDiv)
	{
		GetP()->setDivide(argDiv);
	}

	void fk_Prism::SetTopRadius(double argRad)
	{
		GetP()->setTopRadius(argRad);
	}

	void fk_Prism::SetBottomRadius(double argRad)
	{
		GetP()->setBottomRadius(argRad);
	}
		
	void fk_Prism::SetHeight(double argHeight)
	{
		GetP()->setHeight(argHeight);
	}			
}
