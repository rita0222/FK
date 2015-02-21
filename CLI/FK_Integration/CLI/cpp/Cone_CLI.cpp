#include "Cone_CLI.h"

namespace FK_CLI {

	::fk_Cone * fk_Cone::GetP(void)
	{
		return (::fk_Cone *)(pBase);
	}

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
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_Cone::SetDivide(int argDiv)
	{
		GetP()->setDivide(argDiv);
	}

	void fk_Cone::SetRadius(double argRad)
	{
		GetP()->setRadius(argRad);
	}

	void fk_Cone::SetHeight(double argHeight)
	{
		GetP()->setHeight(argHeight);
	}
}
