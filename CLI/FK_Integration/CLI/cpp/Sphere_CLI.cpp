#include "Sphere_CLI.h"

namespace FK_CLI {

	::fk_Sphere * fk_Sphere::GetP(void)
	{
		return (::fk_Sphere *)(pBase);
	}

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
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_Sphere::SetDivide(int argDiv)
	{
		GetP()->setDivide(argDiv);
	}

	void fk_Sphere::SetRadius(double argRad)
	{
		GetP()->setRadius(argRad);
	}

	void fk_Sphere::SetScale(double argScale)
	{
		GetP()->setScale(argScale);
	}
}
