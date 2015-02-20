#include "BVHMotion_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;

	void fk_BVHMotion::Init(void)
	{
		GetP()->init();
	}

	bool fk_BVHMotion::ReadBVHFile(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readBVHFile(marshal_as<string>(argFileName));
	}

	int fk_BVHMotion::GetNodeNum(void)
	{
		return GetP()->getNodeNum();
	}

	String^ fk_BVHMotion::GetNodeName(int argIndex)
	{
		String^ S = marshal_as<String^>(GetP()->getNodeName(argIndex));
		return S;
	}

	fk_Model^ fk_BVHMotion::GetNodeModel(int argIndex)
	{
		::fk_Model *pM = GetP()->getNodeModel(argIndex);
		if(pM == nullptr) return nullptr;

		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = pM;
		M->dFlg = false;
		return M;
	}

	fk_Model^ fk_BVHMotion::GetNodeModel(String^ argNodeName)
	{
		if(!argNodeName) return nullptr;
		::fk_Model *pM = GetP()->getNodeModel(marshal_as<string>(argNodeName));
		if(pM == nullptr) return nullptr;

		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = pM;
		M->dFlg = false;
		return M;
	}

	int fk_BVHMotion::NextFrame(void)
	{
		return GetP()->nextFrame();
	}

	void fk_BVHMotion::SetFrameCount(int argFrame)
	{
		GetP()->setFrameCount(argFrame);
	}

	void fk_BVHMotion::SetAnimationTime(double argT)
	{
		GetP()->setAnimationTime(argT);
	}
}
