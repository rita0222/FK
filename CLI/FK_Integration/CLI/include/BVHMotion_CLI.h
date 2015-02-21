// BVHMotion_CLI.h

#pragma once

#include <FK/BVHMotion.h>
#include "Model_CLI.h"

namespace FK_CLI
{
	public ref class fk_BVHMotion {
	internal:
		::fk_BVHMotion *pMotion;

		::fk_BVHMotion * GetP(void);

	public:
		fk_BVHMotion();
		~fk_BVHMotion();
		!fk_BVHMotion();

		property int NowFrameCount {
			int get();
		}

		property int FrameLength {
			int get();
		}

		property double OneFrameTime {
			double get();
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
