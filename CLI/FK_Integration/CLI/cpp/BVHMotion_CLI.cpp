#include "BVHMotion_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;

	void fk_BVHMotion::init(void)
	{
		GetP()->init();
	}

	bool fk_BVHMotion::readBVHFile(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readBVHFile(marshal_as<string>(argFileName));
	}

	int fk_BVHMotion::getNodeNum(void)
	{
		return GetP()->getNodeNum();
	}

	String^ fk_BVHMotion::getNodeName(int argIndex)
	{
		String^ S = marshal_as<String^>(GetP()->getNodeName(argIndex));
		return S;
	}

	fk_Model^ fk_BVHMotion::getNodeModel(int argIndex)
	{
		::fk_Model *pM = GetP()->getNodeModel(argIndex);
		if(pM == NULL) return nullptr;

		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = pM;
		M->dFlg = false;
		return M;
	}

	fk_Model^ fk_BVHMotion::getNodeModel(String^ argNodeName)
	{
		if(!argNodeName) return nullptr;
		::fk_Model *pM = GetP()->getNodeModel(marshal_as<string>(argNodeName));
		if(pM == NULL) return nullptr;

		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = pM;
		M->dFlg = false;
		return M;
	}

	int fk_BVHMotion::nextFrame(void)
	{
		return GetP()->nextFrame();
	}

	void fk_BVHMotion::setFrameCount(int argFrame)
	{
		GetP()->setFrameCount(argFrame);
	}

	void fk_BVHMotion::setAnimationTime(double argT)
	{
		GetP()->setAnimationTime(argT);
	}

	int fk_BVHMotion::getNowFrameCount(void)
	{
		return GetP()->getNowFrameCount();
	}

	int fk_BVHMotion::getFrameLength(void)
	{
		return GetP()->getFrameLength();
	}
		
	double fk_BVHMotion::getOneFrameTime(void)
	{
		return GetP()->getOneFrameTime();
	}
}
	
