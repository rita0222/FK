#include "Cone_CLI.h"

namespace FK_CLI {

	void fk_Cone::setDivide(int argDiv)
	{
		GetP()->setDivide(argDiv);
	}

	void fk_Cone::setRadius(double argRad)
	{
		GetP()->setRadius(argRad);
	}

	void fk_Cone::setHeight(double argHeight)
	{
		GetP()->setHeight(argHeight);
	}
}
