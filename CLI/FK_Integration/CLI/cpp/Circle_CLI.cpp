#include "Circle_CLI.h"

namespace FK_CLI {

	::fk_Circle * fk_Circle::GetP(void)
	{
		return (::fk_Circle *)(pBase);
	}

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

	void fk_Circle::SetDivide(int argDiv)
	{
		GetP()->setDivide(argDiv);
	}

	void fk_Circle::SetRadius(double argRad)
	{
		GetP()->setRadius(argRad);
	}

	void fk_Circle::SetScale(double argScale)
	{
		GetP()->setScale(argScale);
	}
}

