// BVHMotion_CLI.h

#pragma once

#include <FK/BVHMotion.h>
#include <msclr/marshal_cppstd.h>
#include "Model_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;
	using namespace msclr::interop;

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
			delete pMotion;
			pMotion = NULL;
		}

		void init(void)
		{
			GetP()->init();
		}

		bool readBVHFile(String^ argFileName)
		{
			if(!argFileName) return false;
			return GetP()->readBVHFile(marshal_as<string>(argFileName));
		}

		int getNodeNum(void)
		{
			return GetP()->getNodeNum();
		}

		String^ getNodeName(int argIndex)
		{
			String^ S = marshal_as<String^>(GetP()->getNodeName(argIndex));
			return S;
		}

		fk_Model^ getNodeModel(int argIndex)
		{
			::fk_Model *pM = GetP()->getNodeModel(argIndex);
			if(pM == NULL) return nullptr;

			fk_Model^ M = gcnew fk_Model(false);
			M->pModel = pM;
			M->dFlg = false;
			return M;
		}

		fk_Model^ getNodeModel(String^ argNodeName)
		{
			if(!argNodeName) return nullptr;
			::fk_Model *pM = GetP()->getNodeModel(marshal_as<string>(argNodeName));
			if(pM == NULL) return nullptr;

			fk_Model^ M = gcnew fk_Model(false);
			M->pModel = pM;
			M->dFlg = false;
			return M;
		}

		int nextFrame(void)
		{
			return GetP()->nextFrame();
		}

		void setFrameCount(int argFrame)
		{
			GetP()->setFrameCount(argFrame);
		}

		void setAnimationTime(double argT)
		{
			GetP()->setAnimationTime(argT);
		}

		int getNowFrameCount(void)
		{
			return GetP()->getNowFrameCount();
		}

		int getFrameLength(void)
		{
			return GetP()->getFrameLength();
		}
		
		double getOneFrameTime(void)
		{
			return GetP()->getOneFrameTime();
		}
	};
}
