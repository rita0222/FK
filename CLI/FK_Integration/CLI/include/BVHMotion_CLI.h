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

		void init(void);
		bool readBVHFile(String^ fileName);
		int getNodeNum(void);
		String^ getNodeName(int index);
		fk_Model^ getNodeModel(int index);
		fk_Model^ getNodeModel(String^ nodeName);
		int nextFrame(void);
		void setFrameCount(int frame);
		void setAnimationTime(double t);
		int getNowFrameCount(void);
		int getFrameLength(void);
		double getOneFrameTime(void);
	};
}
