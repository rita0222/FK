#include "Capsule_CLI.h"

namespace FK_CLI {

	void fk_Capsule::setDivide(int argDiv)
	{
		GetP()->setDivide(argDiv);
	}

	void fk_Capsule::setLength(double argLen)
	{
		GetP()->setLength(argLen);
	}

	void fk_Capsule::setRadius(double argRad)
	{
		GetP()->setRadius(argRad);
	}

	void fk_Capsule::setScale(double argScale)
	{
		GetP()->setScale(argScale);
	}
}
