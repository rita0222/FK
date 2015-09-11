#include "Capsule_CLI.h"

namespace FK_CLI {

	::fk_Capsule * fk_Capsule::GetP(void)
	{
		return (::fk_Capsule *)(pBase);
	}

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
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_Capsule::SetDivide(int argDiv)
	{
		GetP()->setDivide(argDiv);
	}

	void fk_Capsule::SetLength(double argLen)
	{
		GetP()->setLength(argLen);
	}

	void fk_Capsule::SetRadius(double argRad)
	{
		GetP()->setRadius(argRad);
	}

	void fk_Capsule::SetScale(double argScale)
	{
		GetP()->setScale(argScale);
	}
}
