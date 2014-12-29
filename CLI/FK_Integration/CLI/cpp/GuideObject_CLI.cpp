#include "GuideObject_CLI.h"

namespace FK_CLI {

	void fk_GuideObject::setAxisWidth(double argWidth)
	{
		GetP()->setAxisWidth(argWidth);
	}

	void fk_GuideObject::setGridWidth(double argWidth)
	{
		GetP()->setGridWidth(argWidth);
	}

	void fk_GuideObject::setScale(double argScale)
	{
		GetP()->setScale(argScale);
	}

	void fk_GuideObject::setNum(int argNum)
	{
		GetP()->setNum(argNum);
	}
		
	void fk_GuideObject::entryScene(fk_Scene ^argS, fk_GuideMode argMode)
	{
		GetP()->entryScene(argS->GetP(), int(argMode));
	}
		
	void fk_GuideObject::removeScene(fk_Scene ^argS)
	{	
		GetP()->removeScene(argS->GetP());
	}
}

