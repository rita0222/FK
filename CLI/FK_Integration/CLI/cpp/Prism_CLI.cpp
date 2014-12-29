#include "Prism_CLI.h"

namespace FK_CLI {
	void fk_Prism::setDivide(int argDiv)
	{
		GetP()->setDivide(argDiv);
	}

	void fk_Prism::setTopRadius(double argRad)
	{
		GetP()->setTopRadius(argRad);
	}

	void fk_Prism::setBottomRadius(double argRad)
	{
		GetP()->setBottomRadius(argRad);
	}
		
	void fk_Prism::setHeight(double argHeight)
	{
		GetP()->setHeight(argHeight);
	}			
}
