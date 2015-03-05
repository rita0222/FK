#include "GuideObject_CLI.h"

namespace FK_CLI {

	::fk_GuideObject * fk_GuideObject::GetP(void)
	{
		return pGuide;
	}

	fk_GuideObject::fk_GuideObject()
	{
		pGuide = new ::fk_GuideObject();
		dFlg = true;
	}

	fk_GuideObject::fk_GuideObject(bool argNewFlg)
	{
		if(argNewFlg == true) pGuide = new ::fk_GuideObject();
		dFlg = argNewFlg;
	}

	fk_GuideObject::~fk_GuideObject()
	{
		if(pGuide == nullptr) return;
		if(dFlg == true) delete pGuide;
		pGuide = nullptr;
	}

	fk_GuideObject::!fk_GuideObject()
	{
		if(pGuide == nullptr) return;
		if(dFlg == true) {
			pGuide->SetFinalizeMode();
			delete pGuide;
		}
		pGuide = nullptr;
	}

	void fk_GuideObject::AxisWidth::set(double argWidth)
	{
		GetP()->setAxisWidth(argWidth);
	}

	void fk_GuideObject::GridWidth::set(double argWidth)
	{
		GetP()->setGridWidth(argWidth);
	}

	void fk_GuideObject::Scale::set(double argScale)
	{
		GetP()->setScale(argScale);
	}

	void fk_GuideObject::Num::set(int argNum)
	{
		GetP()->setNum(argNum);
	}
		
	void fk_GuideObject::EntryScene(fk_Scene ^argS, fk_GuideMode argMode)
	{
		GetP()->entryScene(argS->GetP(), int(argMode));
	}
		
	void fk_GuideObject::RemoveScene(fk_Scene ^argS)
	{	
		GetP()->removeScene(argS->GetP());
	}
}

