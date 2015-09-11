#include "Performer_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::fk_Performer * fk_Performer::GetP(void)
	{
		return pMotion;
		baseModel = GetBaseModel();
	}

	fk_Performer::fk_Performer()
	{
		pMotion = new ::fk_Performer();
	}

	fk_Performer::fk_Performer(bool argNewFlg)
	{
		if(argNewFlg == true) pMotion = new ::fk_Performer();
		baseModel = GetBaseModel();
	}

	fk_Performer::~fk_Performer()
	{
		if(pMotion == nullptr) return;
		if(dFlg == true) delete GetP();
		pMotion = nullptr;
	}

	fk_Performer::!fk_Performer()
	{
		if(pMotion == nullptr) return;
		if(dFlg == true) {
			GetP()->SetFinalizeMode();
			delete GetP();
		}
		pMotion = nullptr;
	}

	int fk_Performer::ObjectNum::get(void)
	{
		return GetP()->getObjectNum();
	}

	int fk_Performer::LoopCount::get(void)
	{
		return GetP()->getLoopCount();
	}

	void fk_Performer::Scene::set(fk_Scene^ argScene)
	{
		if(!argScene) return;
		GetP()->entryScene(argScene->GetP());
	}

	bool fk_Performer::CloneCharactor(fk_Performer^ argP)
	{
		if(!argP) return false;
		return GetP()->cloneCharactor(argP->GetP());
	}

	bool fk_Performer::LoadObjectData(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->loadObjectData(marshal_as<string>(argFileName));
	}

	bool fk_Performer::LoadJointData(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->loadJointData(marshal_as<string>(argFileName));
	}

	bool fk_Performer::LoadMotionData(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->loadMotionData(marshal_as<string>(argFileName));
	}

	void fk_Performer::RemoveScene(fk_Scene^ argScene)
	{
		if(!argScene) return;
		GetP()->removeScene(argScene->GetP());
	}

	fk_Model^ fk_Performer::GetBaseModel(void)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = GetP()->getBaseModel();
		M->dFlg = false;
		return M;
	}

	fk_Model^ fk_Performer::GetObjectModel(int argID)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = GetP()->getObjectModel(argID);
		M->dFlg = false;
		return M;
	}

	fk_Model^ fk_Performer::GetJointModel(int argID)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = GetP()->getJointModel(argID);
		M->dFlg = false;
		return M;

	}
	int fk_Performer::GetNowFrame(int argID)
	{
		return GetP()->getNowFrame(argID);
	}

	int fk_Performer::GetTotalFrame(int argID)
	{
		return GetP()->getTotalFrame(argID);
	}

	bool fk_Performer::PlayMotion(int argID)
	{
		return GetP()->playMotion(argID);
	}

	void fk_Performer::StillMotion(int argMotionID, int argFrameID)
	{
		GetP()->stillMotion(argMotionID, argFrameID);
	}

	void fk_Performer::SetNowFrame(int argMotionID, int argFrameID)
	{
		GetP()->setNowFrame(argMotionID, argFrameID);
	}

	bool fk_Performer::IsMotionFinished(int argID)
	{
		return GetP()->isMotionFinished(argID);
	}
}
