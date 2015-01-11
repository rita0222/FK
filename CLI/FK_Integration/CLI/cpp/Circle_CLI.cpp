#include "Circle_CLI.h"

namespace FK_CLI {

	void fk_Circle::setDivide(int argDiv)
	{
		GetP()->setDivide(argDiv);
	}

	void fk_Circle::setRadius(double argRad)
	{
		GetP()->setRadius(argRad);
	}

	void fk_Circle::setScale(double argScale)
	{
		GetP()->setScale(argScale);
	}
}

