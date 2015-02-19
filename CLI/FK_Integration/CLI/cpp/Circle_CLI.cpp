#include "Circle_CLI.h"

namespace FK_CLI {

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

