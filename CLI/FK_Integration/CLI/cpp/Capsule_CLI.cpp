#include "Capsule_CLI.h"

namespace FK_CLI {

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
