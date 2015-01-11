#include "Scene_CLI.h"

namespace FK_CLI {

	void fk_Scene::setBGColor(fk_Color^ argCol)
	{
		GetP()->setBGColor(*argCol->GetP());
	}

	void fk_Scene::setBGColor(float argR, float argG, float argB)
	{
		GetP()->setBGColor(argR, argG, argB);
	}

	fk_Color^ fk_Scene::getBGColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		::fk_Color tmpC = GetP()->getBGColor();
		C->set(tmpC.getR(), tmpC.getG(), tmpC.getB(), tmpC.getA());
		return C;
	}

	void fk_Scene::setBlendStatus(bool argMode)
	{
		GetP()->setBlendStatus(argMode);
	}

	bool fk_Scene::getBlendStatus(void)
	{
		return GetP()->getBlendStatus();
	}
}
