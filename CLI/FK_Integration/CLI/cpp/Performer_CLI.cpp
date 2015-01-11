#include "Performer_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	bool fk_Performer::cloneCharactor(fk_Performer^ argP)
	{
		if(!argP) return false;
		return GetP()->cloneCharactor(argP->GetP());
	}

	bool fk_Performer::loadObjectData(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->loadObjectData(marshal_as<string>(argFileName));
	}

	bool fk_Performer::loadJointData(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->loadJointData(marshal_as<string>(argFileName));
	}

	bool fk_Performer::loadMotionData(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->loadMotionData(marshal_as<string>(argFileName));
	}

	void fk_Performer::entryScene(fk_Scene^ argScene)
	{
		if(!argScene) return;
		GetP()->entryScene(argScene->GetP());
	}

	void fk_Performer::removeScene(fk_Scene^ argScene)
	{
		if(!argScene) return;
		GetP()->removeScene(argScene->GetP());
	}

	int fk_Performer::getObjectNum(void)
	{
		return GetP()->getObjectNum();
	}

	fk_Model^ fk_Performer::getBaseModel(void)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = GetP()->getBaseModel();
		M->dFlg = false;
		return M;
	}

	fk_Model^ fk_Performer::getObjectModel(int argID)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = GetP()->getObjectModel(argID);
		M->dFlg = false;
		return M;
	}

	fk_Model^ fk_Performer::getJointModel(int argID)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = GetP()->getJointModel(argID);
		M->dFlg = false;
		return M;

	}
	int fk_Performer::getNowFrame(int argID)
	{
		return GetP()->getNowFrame(argID);
	}

	int fk_Performer::getTotalFrame(int argID)
	{
		return GetP()->getTotalFrame(argID);
	}

	bool fk_Performer::playMotion(int argID)
	{
		return GetP()->playMotion(argID);
	}

	void fk_Performer::stillMotion(int argMotionID, int argFrameID)
	{
		GetP()->stillMotion(argMotionID, argFrameID);
	}

	void fk_Performer::setNowFrame(int argMotionID, int argFrameID)
	{
		GetP()->setNowFrame(argMotionID, argFrameID);
	}

	bool fk_Performer::isMotionFinished(int argID)
	{
		return GetP()->isMotionFinished(argID);
	}

	int fk_Performer::getLoopCount(void)
	{
		return GetP()->getLoopCount();
	}
}
