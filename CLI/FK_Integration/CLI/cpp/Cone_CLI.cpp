#include "Cone_CLI.h"

namespace FK_CLI {

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
