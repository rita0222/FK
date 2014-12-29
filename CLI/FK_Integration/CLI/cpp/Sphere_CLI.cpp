#include "Sphere_CLI.h"

namespace FK_CLI {
	void fk_Sphere::setDivide(int argDiv)
	{
		GetP()->setDivide(argDiv);
	}

	void fk_Sphere::setRadius(double argRad)
	{
		GetP()->setRadius(argRad);
	}

	void fk_Sphere::setScale(double argScale)
	{
		GetP()->setScale(argScale);
	}
}
