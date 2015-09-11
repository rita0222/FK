#include "Scene_CLI.h"

namespace FK_CLI {

	::fk_Scene * fk_Scene::GetP(void)
	{
		return (::fk_Scene *)(pBase);
	}

	fk_Scene::fk_Scene(bool argNewFlg) : fk_Fog(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_Scene();
			CameraUpdate();
		}
	}

	fk_Scene::fk_Scene() : fk_Fog(false)
	{
		pBase = new ::fk_Scene();
		CameraUpdate();
	}

	fk_Scene::~fk_Scene()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_Scene::!fk_Scene()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) {
			GetP()->SetFinalizeMode();
			delete GetP();
		}
		pBase = nullptr;
	}

	void fk_Scene::BGColor::set(fk_Color^ argCol)
	{
		GetP()->setBGColor(*argCol->GetP());
	}

	fk_Color^ fk_Scene::BGColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		::fk_Color tmpC = GetP()->getBGColor();
		C->Set(tmpC.getR(), tmpC.getG(), tmpC.getB(), tmpC.getA());
		return C;
	}

	void fk_Scene::BlendStatus::set(bool argMode)
	{
		GetP()->setBlendStatus(argMode);
	}

	bool fk_Scene::BlendStatus::get(void)
	{
		return GetP()->getBlendStatus();
	}
}
