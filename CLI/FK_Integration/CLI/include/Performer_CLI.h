// Performer_CLI.h

#pragma once

#include <FK/MotionCharactor.h>
#include "Scene_CLI.h"

namespace FK_CLI
{
	public ref class fk_Performer {
	internal:
		::fk_Performer *pMotion;
		bool dFlg;
		fk_Model^ baseModel;

		::fk_Performer * GetP(void)
		{
			return pMotion;
			baseModel = getBaseModel();
		}

	public:
		fk_Performer::fk_Performer()
		{
			pMotion = new ::fk_Performer();
		}

		fk_Performer::fk_Performer(bool argNewFlg)
		{
			if(argNewFlg == true) pMotion = new ::fk_Performer();
			baseModel = getBaseModel();
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

		bool cloneCharactor(fk_Performer^ perf);
		bool loadObjectData(String^ filename);
		bool loadJointData(String^ filename);
		bool loadMotionData(String^ filename);
		void entryScene(fk_Scene^ scene);
		void removeScene(fk_Scene^ scene);
		int getObjectNum(void);
		fk_Model^ getBaseModel(void);
		fk_Model^ getObjectModel(int id);
		fk_Model^ getJointModel(int id);
		int getNowFrame(int id);
		int getTotalFrame(int id);
		bool playMotion(int id);
		void stillMotion(int motionID, int frameID);
		void setNowFrame(int motionID, int frameID);
		bool isMotionFinished(int id);
		int getLoopCount(void);
	};
}
