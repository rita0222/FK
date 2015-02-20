// BVHMotion_CLI.h

#pragma once

#include <FK/BVHMotion.h>
#include "Model_CLI.h"

namespace FK_CLI
{
	public ref class fk_BVHMotion {
	internal:
		::fk_BVHMotion *pMotion;

		::fk_BVHMotion * GetP(void)
		{
			return pMotion;
		}

	public:
		fk_BVHMotion::fk_BVHMotion()
		{
			pMotion = new ::fk_BVHMotion();
		}

		fk_BVHMotion::~fk_BVHMotion()
		{
			this->!fk_BVHMotion();
		}

		fk_BVHMotion::!fk_BVHMotion()
		{
			if(pMotion == nullptr) return;
			delete pMotion;
			pMotion = nullptr;
		}

		property int NowFrameCount {
			int get()
			{
				return GetP()->getNowFrameCount();
			}
		}

		property int FrameLength {
			int get()
			{
				return GetP()->getFrameLength();
			}
		}

		property double OneFrameTime {
			double get()
			{
				return GetP()->getOneFrameTime();
			}
		}

		void Init(void);
		bool ReadBVHFile(String^ fileName);
		int GetNodeNum(void);
		String^ GetNodeName(int index);
		fk_Model^ GetNodeModel(int index);
		fk_Model^ GetNodeModel(String^ nodeName);
		int NextFrame(void);
		void SetFrameCount(int frame);
		void SetAnimationTime(double t);
	};
}
