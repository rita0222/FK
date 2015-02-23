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

		::fk_Performer * GetP(void);

	public:
		fk_Performer();
		fk_Performer(bool argNewFlg);
		~fk_Performer();
		!fk_Performer();

		property int ObjectNum {
			int get();
		}

		property int LoopCount {
			int get();
		}

		property fk_Scene^ Scene {
			void set(fk_Scene^);
		}
		
		bool CloneCharactor(fk_Performer^ perf);
		bool LoadObjectData(String^ filename);
		bool LoadJointData(String^ filename);
		bool LoadMotionData(String^ filename);
		void RemoveScene(fk_Scene^ scene);
		fk_Model^ GetBaseModel(void);
		fk_Model^ GetObjectModel(int id);
		fk_Model^ GetJointModel(int id);
		int GetNowFrame(int id);
		int GetTotalFrame(int id);
	
		bool PlayMotion(int id);
		void StillMotion(int motionID, int frameID);
		void SetNowFrame(int motionID, int frameID);
		bool IsMotionFinished(int id);
	};
}
