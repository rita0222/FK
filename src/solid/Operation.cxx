#define __FK_OPERATION_CODE__
#define FK_DEF_SIZETYPE
#include <FK/Operation.h>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Edge.h>
#include <FK/Loop.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_Operation::Member::Member(void) : historyMode(false), tesselateMode(false)
{
	return;
}

fk_Operation::fk_Operation(fk_DataBase *argDB) : _m(make_unique<Member>())
{
	SetDataBase(argDB);
	_m->history.Init();
	setHistoryMode(false);
	setTesselateMode(false);
	return;
}

fk_Operation::~fk_Operation()
{
	_m->history.Init();
	return;
}


void fk_Operation::UndefVNorm(fk_Vertex *argV)
{
	_st i, j;
	vector<fk_Loop *> LoopArray;
	vector<fk_Vertex *> VertexArray;


	if(argV == nullptr) return;
	LoopArray = getAllLOnV(argV);

	for(i = 0; i < LoopArray.size(); i++) {
		VertexArray = getAllVOnL(LoopArray[i]);
		for(j = 0; j < VertexArray.size(); j++) {
			VertexArray[j]->UndefNormal();
		}
	}

	return;
}

fk_Loop * fk_Operation::SetLoop(fk_Half *argH, bool nullFlg,
								fk_Loop *argL, int argLID)
{
	fk_Loop *newL;
	fk_Half *loopH, *nextH, *mateH;
	vector<fk_Half *> halfStack;
	vector<fk_Loop *> loopStack;
	unsigned int i;


	if(checkDB() == false) return nullptr;

	if(nullFlg == true && argH->getParentLoop() != nullptr) {
		Error::Put("fk_Operation", "SetLoop", 1, "Loop Definition Error.");
		return nullptr;
	}

	loopH = argH->getNextHalf();
	if(nullFlg == false && argL != nullptr) {
		newL = argL;
	} else {
		newL = (argLID == FK_UNDEFINED) ?
			GetNewLoopObj() : GetNewLoopObj(argLID);
	}

	halfStack.clear();
	while(loopH != argH) {
		mateH = getMateHOnH(loopH);
		if(nullFlg == true &&
		   loopH->getParentLoop() != nullptr) {
			for(i = 0; i < halfStack.size(); i++) {
				halfStack[i]->SetParentLoop(loopStack[i]->getID());
			}
			DeleteLoopObj(newL);
			Error::Put("fk_Operation", "SetLoop", 2, "Loop Definition Error.");
			return nullptr;
		}

		if(mateH->getParentLoop() == newL) {
			for(i = 0; i < halfStack.size(); i++) {
				halfStack[i]->SetParentLoop(loopStack[i]->getID());
			}
			if(nullFlg == true) {
				DeleteLoopObj(newL);
			}
			return nullptr;
		}

		loopStack.push_back(loopH->getParentLoop());
		loopH->SetParentLoop(newL->getID());
		halfStack.push_back(loopH);
		nextH = loopH->getNextHalf();
		if(nextH->getPrevHalf() != loopH) {
			for(i = 0; i < halfStack.size(); i++) {
				halfStack[i]->SetParentLoop(loopStack[i]->getID());
			}
			if(nullFlg == true) {
				DeleteLoopObj(newL);
			}
			Error::Put("fk_Operation", "SetLoop", 3, "Half Edge Connection Error.");
			return nullptr;
		}
		loopH = nextH;
	}

	argH->SetParentLoop(newL->getID());

	newL->SetOneHalf(argH->getID());
	newL->ModifyLoop();

	return newL;
}

fk_Vertex * fk_Operation::makeVertex(const fk_Vector argPos)
{
	return MakeVertex(argPos, FK_UNDEFINED);
}

fk_Vertex * fk_Operation::MakeVertex(const fk_Vector argPos, int argID)
{
	fk_Vertex *newV;

	if(checkDB() == false) return nullptr;

	if(argID == FK_UNDEFINED) {
		newV = GetNewVertexObj();
	} else {
		newV = GetNewVertexObj(argID);
	}

	if(newV == nullptr) return nullptr;

	newV->SetPosition(argPos);

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::MAKEV));
		_m->history.PushInt(newV->getID());
		_m->history.PushVec(argPos);
		_m->history.Close();
	}

	return newV;
}

bool fk_Operation::deleteVertex(fk_Vertex *argV)
{
	return DeleteVertex(argV);
}

bool fk_Operation::DeleteVertex(fk_Vertex *argV)
{
	int id;
	fk_Vector pos;

	if(checkDB() == false) return false;
	if(argV == nullptr) return false;
	if(argV->getOneHalf() != nullptr) {
		Error::Put("fk_Operation", "DeleteVertex", 1, "Vertex Connection Error.");
		return false;
	}

	id = argV->getID();

	if(_m->historyMode == true) {
		pos = argV->getPosition();
	}

	if(DeleteVertexObj(argV) == false) return false;

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::DELV));
		_m->history.PushInt(id);
		_m->history.PushVec(pos);
		_m->history.Close();
	}

	return true;
}

bool fk_Operation::moveVertex(fk_Vertex *argV, fk_Vector argVec)
{
	return MoveVertex(argV, argVec);
}

bool fk_Operation::MoveVertex(fk_Vertex *argV, fk_Vector argVec)
{
	vector<fk_Loop *> LoopSet;
	vector<fk_Loop *>::iterator lIterator;
	fk_Vector orgPos;

	if(argV == nullptr) return false;

	if(_m->historyMode == true) {
		orgPos = argV->getPosition();
	}

	argV->SetPosition(argVec);
	LoopSet = getAllLOnV(argV);

	for(lIterator = LoopSet.begin();
		lIterator != LoopSet.end(); ++lIterator) {
		(*lIterator)->ModifyLoop();
	}
	UndefVNorm(argV);

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::MOVEV));
		_m->history.PushInt(argV->getID());
		_m->history.PushVec(orgPos);
		_m->history.PushVec(argVec);
		_m->history.Close();
	}

	return true;
}

fk_Edge * fk_Operation::makeEdge(fk_Vertex *argV1, fk_Vertex *argV2,
								 fk_Half *argH1_1, fk_Half *argH1_2,
								 fk_Half *argH2_1, fk_Half *argH2_2)
{
	fk_Edge *newE;

	newE = nullptr;
	if(checkDB() == false) return nullptr;

	if(argV1 == nullptr || argV2 == nullptr) {
		return nullptr;
	}

	if(argH1_1 == nullptr && argH1_2 == nullptr &&
	   argH2_1 == nullptr && argH2_2 == nullptr) {
		newE = MakeEdge1(argV1, argV2);

	} else if(argH2_1 == nullptr && argH2_2 == nullptr) {
		newE = MakeEdge2(argV1, argV2, argH1_1, argH1_2, true, false);
	} else {
		newE = MakeEdge3(argV1, argV2, argH1_1, argH1_2, argH2_1, argH2_2,
						 false, false);
	}

	return newE;
}
	   
fk_Edge * fk_Operation::MakeEdge1(fk_Vertex *argV1, fk_Vertex *argV2,
								  int argEID, int argH1ID, int argH2ID)
{
	fk_Edge *newE;
	fk_Half *newH1, *newH2;

	// 両方が独立頂点かどうかのチェック 
	if(argV1->getOneHalf() != nullptr || argV2->getOneHalf() != nullptr) {
		Error::Put("fk_Operation", "MakeEdge1", 1, "Vertex Topology Error.");
		return nullptr;
	}

	// 新要素の生成 
	newE = (argEID == FK_UNDEFINED) ?
		GetNewEdgeObj() : GetNewEdgeObj(argEID);
	newH1 = (argH1ID == FK_UNDEFINED) ?
		GetNewHalfObj() : GetNewHalfObj(argH1ID);
	newH2 = (argH2ID == FK_UNDEFINED) ?
		GetNewHalfObj() : GetNewHalfObj(argH2ID);

	// 新稜線の半稜線設定 
	newE->SetLeftHalf(newH1->getID());
	newE->SetRightHalf(newH2->getID());

	// 以下、新半稜線の属性設定 
	newH1->SetVertex(argV1->getID());
	newH1->SetParentEdge(newE->getID());
	newH1->SetPrevHalf(newH2->getID());
	newH1->SetNextHalf(newH2->getID());
	argV1->SetOneHalf(newH1->getID());

	newH2->SetVertex(argV2->getID());
	newH2->SetParentEdge(newE->getID());
	newH2->SetPrevHalf(newH1->getID());
	newH2->SetNextHalf(newH1->getID());
	argV2->SetOneHalf(newH2->getID());

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::MAKEE1));
		_m->history.PushInt(argV1->getID());
		_m->history.PushInt(argV2->getID());
		_m->history.PushInt(newE->getID());
		_m->history.PushInt(newH1->getID());
		_m->history.PushInt(newH2->getID());
		_m->history.Close();
	}

	return newE;
}

fk_Edge * fk_Operation::MakeEdge2(fk_Vertex *argV1, fk_Vertex *argV2,
								  fk_Half *argH1, fk_Half *argH2,
								  bool lrFlag, bool v1ParentFlag,
								  int argEID, int argH1ID, int argH2ID)
{
	fk_Edge *newE;
	fk_Half *newH1, *newH2;

	// v1 が接続頂点、v2 が独立頂点になっているかどうかのチェック 
	if(argV1->getOneHalf() == nullptr || argV2->getOneHalf() != nullptr) {
		Error::Put("fk_Operation", "MakeEdge2", 1, "Vertex Topology Error.");
		return nullptr;
	}

	// 半稜線の nullptr ポインタチェック 
	if(argH1 == nullptr || argH2 == nullptr) {
		Error::Put("fk_Operation", "MakeEdge2", 2, "Half Edge Null Pointer Error.");
		return nullptr;
	}

	// v1, h1, h2 の接続関係のチェック 
	if(argH1->getNextHalf() != argH2 || argH2->getPrevHalf() != argH1 ||
	   argH2->getVertex() != argV1) {
		Error::Put("fk_Operation", "MakeEdge2", 3, "Half Edge Topology Error.");
		return nullptr;
	}

	// h1, h2 が未定義半稜線かどうかのチェック 
	if(argH1->getParentLoop() != nullptr ||
	   argH2->getParentLoop() != nullptr) {
		Error::Put("fk_Operation", "MakeEdge2", 4, "Half Edge Has Loop Error.");
		return nullptr;
	}

	// 新要素の生成 
	newE = (argEID == FK_UNDEFINED) ?
		GetNewEdgeObj() : GetNewEdgeObj(argEID);
	newH1 = (argH1ID == FK_UNDEFINED) ?
		GetNewHalfObj() : GetNewHalfObj(argH1ID);
	newH2 = (argH2ID == FK_UNDEFINED) ?
		GetNewHalfObj() : GetNewHalfObj(argH2ID);

	// 新稜線の半稜線設定 
	newE->SetLeftHalf(newH1->getID());
	newE->SetRightHalf(newH2->getID());

	// v1 まわり設定 
	newH1->SetVertex(argV1->getID());
	newH1->SetParentEdge(newE->getID());
	newH1->SetPrevHalf(argH1->getID());
	newH1->SetNextHalf(newH2->getID());
	argH1->SetNextHalf(newH1->getID());

	// v2 まわり設定 
	newH2->SetVertex(argV2->getID());
	newH2->SetParentEdge(newE->getID());
	newH2->SetPrevHalf(newH1->getID());
	newH2->SetNextHalf(argH2->getID());
	argH2->SetPrevHalf(newH2->getID());
	argV2->SetOneHalf(newH2->getID());

	if(lrFlag == false) {
		// V1 → V2 の半稜線が右側の場合 

		newE->SwapHalf();
	}

	if(v1ParentFlag == true) {
		// V1 の親半稜線が newH1 の場合 

		argV1->SetOneHalf(newH1->getID());
	}

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::MAKEE2));
		_m->history.PushInt(argV2->getID());
		_m->history.PushInt(argH1->getID());
		_m->history.PushInt(newE->getID());
		_m->history.PushInt(newH1->getID());
		_m->history.PushInt(newH2->getID());
		_m->history.PushBool(lrFlag);
		_m->history.PushBool(v1ParentFlag);
		_m->history.Close();
	}

	return newE;
}

fk_Edge * fk_Operation::MakeEdge3(fk_Vertex *argV1, fk_Vertex *argV2,
								  fk_Half *argH1_1, fk_Half *argH1_2,
								  fk_Half *argH2_1, fk_Half *argH2_2,
								  bool v1PFlag, bool v2PFlag,
								  int argEID, int argH1ID, int argH2ID)
{
	fk_Edge *newE;
	fk_Half *newH1, *newH2;

	// v1, v2 が接続頂点かどうかのチェック 
	if(argV1->getOneHalf() == nullptr || argV2->getOneHalf() == nullptr) {
		Error::Put("fk_Operation", "MakeEdge3", 1, "Vertex Topology Error.");
		return nullptr;
	}

	// 半稜線の nullptr ポインタチェック 
	if(argH1_1 == nullptr || argH1_2 == nullptr ||
	   argH2_1 == nullptr || argH2_2 == nullptr) {
		Error::Put("fk_Operation", "MakeEdge3", 2, "Half Edge Null Pointer Error.");
		return nullptr;
	}

	// v1,v2 まわりの位相チェック 
	if(argH1_1->getNextHalf() != argH1_2 ||
	   argH1_2->getPrevHalf() != argH1_1 ||
	   argH1_2->getVertex() != argV1 ||
	   argH2_1->getNextHalf() != argH2_2 ||
	   argH2_2->getPrevHalf() != argH2_1 ||
	   argH2_2->getVertex() != argV2) {
		Error::Put("fk_Operation", "MakeEdge3", 3, "Half Edge Topology Error.");
		return nullptr;
	}

	// 全半稜線が未定義半稜線かどうかのチェック 
	if(argH1_1->getParentLoop() != nullptr ||
	   argH1_2->getParentLoop() != nullptr ||
	   argH2_1->getParentLoop() != nullptr ||
	   argH2_2->getParentLoop() != nullptr) {
		Error::Put("fk_Operation", "MakeEdge3", 4, "Half Edge Has Loop Error.");
		return nullptr;
	}

	// 新要素の生成 
	newE = (argEID == FK_UNDEFINED) ?
		GetNewEdgeObj() : GetNewEdgeObj(argEID);
	newH1 = (argH1ID == FK_UNDEFINED) ?
		GetNewHalfObj() : GetNewHalfObj(argH1ID);
	newH2 = (argH2ID == FK_UNDEFINED) ?
		GetNewHalfObj() : GetNewHalfObj(argH2ID);

	// 新稜線の半稜線設定 
	newE->SetLeftHalf(newH1->getID());
	newE->SetRightHalf(newH2->getID());

	// v1 まわり設定 
	newH1->SetVertex(argV1->getID());
	newH1->SetParentEdge(newE->getID());
	newH1->SetPrevHalf(argH1_1->getID());
	newH1->SetNextHalf(argH2_2->getID());
	argH1_1->SetNextHalf(newH1->getID());
	argH2_2->SetPrevHalf(newH1->getID());

	// v2 まわり設定 
	newH2->SetVertex(argV2->getID());
	newH2->SetParentEdge(newE->getID());
	newH2->SetPrevHalf(argH2_1->getID());
	newH2->SetNextHalf(argH1_2->getID());
	argH2_1->SetNextHalf(newH2->getID());
	argH1_2->SetPrevHalf(newH2->getID());

	if(v1PFlag == true) {
		// V1 の半親稜線を newH1 にするとき 
		argV1->SetOneHalf(newH1->getID());
	}

	if(v2PFlag == true) {
		// V2 の半親稜線を newH2 にするとき 
		argV2->SetOneHalf(newH2->getID());
	}

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::MAKEE3));
		_m->history.PushInt(argH1_1->getID());
		_m->history.PushInt(argH2_1->getID());
		_m->history.PushInt(newE->getID());
		_m->history.PushInt(newH1->getID());
		_m->history.PushInt(newH2->getID());
		_m->history.PushBool(v1PFlag);
		_m->history.PushBool(v2PFlag);
		_m->history.Close();
	}

	return newE;
}

bool fk_Operation::deleteEdge(fk_Edge *argE)
{
	fk_Half *lHalf, *rHalf;

	if(checkDB() == false) return false;
	if(getEdgeStatus(argE) != fk_EdgeStatus::UNDEF) {
		Error::Put("fk_Operation", "deleteEdge", 1, "No UndefEdge Error.");
		return false;
	}

	lHalf = argE->getLeftHalf();
	rHalf = argE->getRightHalf();

	if(rHalf->getNextHalf() == lHalf && rHalf->getPrevHalf() == lHalf) {
		return DeleteEdge1(argE);
	}

	if(lHalf->getNextHalf() == rHalf) {
		return DeleteEdge2(lHalf);
	}

	if(rHalf->getNextHalf() == lHalf) {
		return DeleteEdge2(rHalf);
	}

	return DeleteEdge3(argE);
}

bool fk_Operation::DeleteEdge1(fk_Edge *argE)
{
	fk_Vertex *lV, *rV;
	fk_Half *lH, *rH;
	int eID, lHID, rHID;

	lH = argE->getLeftHalf();
	rH = argE->getRightHalf();
	lV = lH->getVertex();
	rV = rH->getVertex();

	lV->SetOneHalf(FK_UNDEFINED);
	rV->SetOneHalf(FK_UNDEFINED);

	eID = argE->getID();
	lHID = lH->getID();
	rHID = rH->getID();

	if(DeleteEdgeObj(argE) == false ||
	   DeleteHalfObj(lH) == false ||
	   DeleteHalfObj(rH) == false) {
		Error::Put("fk_Operation", "DeleteEdge1", 1, "DataBase Error.");
		return false;
	}

	if(_m->historyMode == true) {
		int lVID = lV->getID();
		int rVID = rV->getID();

		_m->history.Open(int(Code::DELE1));
		_m->history.PushInt(lVID);
		_m->history.PushInt(rVID);
		_m->history.PushInt(eID);
		_m->history.PushInt(lHID);
		_m->history.PushInt(rHID);
		_m->history.Close();
	}

	return true;
}

bool fk_Operation::DeleteEdge2(fk_Half *argH)
{
	fk_Edge *delE;
	fk_Half *mateH, *prevH, *nextH;
	fk_Vertex *conV, *aloneV;
	int eID, argHID, mateHID;
	bool lrFlag, v1ParentFlag;

	delE = argH->getParentEdge();
	mateH = getMateHOnH(argH);
	prevH = argH->getPrevHalf();
	nextH = mateH->getNextHalf();
	conV = argH->getVertex();
	aloneV = mateH->getVertex();

	if(delE->getLeftHalf() == argH) {
		lrFlag = true;
	} else {
		lrFlag = false;
	}

	aloneV->SetOneHalf(FK_UNDEFINED);
	prevH->SetNextHalf(nextH->getID());
	nextH->SetPrevHalf(prevH->getID());
	if(conV->getOneHalf() == argH) {
		conV->SetOneHalf(nextH->getID());
		v1ParentFlag = true;
	} else {
		v1ParentFlag = false;
	}

	eID = delE->getID();
	argHID = argH->getID();
	mateHID = mateH->getID();

	if(DeleteEdgeObj(delE) == false ||
	   DeleteHalfObj(argH) == false ||
	   DeleteHalfObj(mateH) == false) {
		Error::Put("fk_Operation", "DeleteEdge2", 1, "DataBase Error.");
		return false;
	}

	if(_m->historyMode == true) {
		int prevHID = prevH->getID();
		int aloneVID = aloneV->getID();

		_m->history.Open(int(Code::DELE2));
		_m->history.PushInt(aloneVID);
		_m->history.PushInt(prevHID);
		_m->history.PushInt(eID);
		_m->history.PushInt(argHID);
		_m->history.PushInt(mateHID);
		_m->history.PushBool(lrFlag);
		_m->history.PushBool(v1ParentFlag);
		_m->history.Close();
	}

	return true;
}

bool fk_Operation::DeleteEdge3(fk_Edge *argE)
{
	fk_Vertex *lV, *rV;
	fk_Half *lH, *rH, *lPrevH, *lNextH, *rPrevH, *rNextH;
	int eID, lHID, rHID, lPHID, rPHID;
	bool lVParentFlag, rVParentFlag;

	lH = argE->getLeftHalf();
	rH = argE->getRightHalf();
	lV = lH->getVertex();
	rV = rH->getVertex();
	lPrevH = lH->getPrevHalf();
	lNextH = rH->getNextHalf();
	rPrevH = rH->getPrevHalf();
	rNextH = lH->getNextHalf();

	eID = argE->getID();
	lHID = lH->getID();
	rHID = rH->getID();
	lPHID = lPrevH->getID();
	rPHID = rPrevH->getID();

	// lV まわり設定 
	lPrevH->SetNextHalf(lNextH->getID());
	lNextH->SetPrevHalf(lPrevH->getID());
	if(lV->getOneHalf() == lH) {
		lV->SetOneHalf(lNextH->getID());
		lVParentFlag = true;
	} else {
		lVParentFlag = false;
	}

	// rV まわり設定 
	rPrevH->SetNextHalf(rNextH->getID());
	rNextH->SetPrevHalf(rPrevH->getID());
	if(rV->getOneHalf() == rH) {
		rV->SetOneHalf(rNextH->getID());
		rVParentFlag = true;
	} else {
		rVParentFlag = false;
	}

	// 各要素削除 
	if(DeleteEdgeObj(argE) == false ||
	   DeleteHalfObj(lH) == false ||
	   DeleteHalfObj(rH) == false) {
		Error::Put("fk_Operation", "DeleteEdge3", 1, "DataBase Error.");
		return false;
	}

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::DELE3));
		_m->history.PushInt(lPHID);
		_m->history.PushInt(rPHID);
		_m->history.PushInt(eID);
		_m->history.PushInt(lHID);
		_m->history.PushInt(rHID);
		_m->history.PushBool(lVParentFlag);
		_m->history.PushBool(rVParentFlag);
		_m->history.Close();
	}

	return true;
}

fk_Loop * fk_Operation::makeLoop(fk_Half *argH)
{
	return MakeLoop(argH, FK_UNDEFINED);
}

fk_Loop * fk_Operation::MakeLoop(fk_Half *argH, int argLID)
{
	fk_Loop *newL;
	fk_Half *loopH;

	if((newL = SetLoop(argH, true, nullptr, argLID)) == nullptr) {
		return nullptr;
	}

	loopH = argH;
	do {
		loopH->getVertex()->UndefNormal();
		loopH = loopH->getNextHalf();
	} while(loopH != argH);

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::MAKEL));
		_m->history.PushInt(newL->getID());
		_m->history.PushInt(argH->getID());
		_m->history.Close();
	}

	return newL;
}

bool fk_Operation::deleteLoop(fk_Loop *argL)
{
	return DeleteLoop(argL);
}

bool fk_Operation::DeleteLoop(fk_Loop *argL)
{
	fk_Half *loopH, *oneH;
	int loopID;

	if(checkDB() == false) return false;

	oneH = argL->getOneHalf();
	loopH = oneH->getNextHalf();

	while(loopH != oneH) {
		if(loopH->getParentLoop() != argL) {
			Error::Put("fk_Operation", "deleteLoop", 1, "Parent Loop Error.");
			return false;
		}

		loopH->SetParentLoop(FK_UNDEFINED);
		loopH->getVertex()->UndefNormal();
		loopH = loopH->getNextHalf();
	}

	if(oneH->getParentLoop() != argL) {
		Error::Put("fk_Operation", "deleteLoop", 2, "Parent Loop Error.");
		return false;
	} else {
		oneH->SetParentLoop(FK_UNDEFINED);
	}

	loopID = argL->getID();
	if(DeleteLoopObj(argL) == false) {
		Error::Put("fk_Operation", "deleteLoop", 3, "Delete Loop Error.");
		return false;
	}

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::DELL));
		_m->history.PushInt(loopID);
		_m->history.PushInt(oneH->getID());
		_m->history.Close();
	}

	return true;
}

fk_Edge * fk_Operation::separateLoop(fk_Half *argPrevH, fk_Half *argNextH)
{
	return SeparateLoop(argPrevH, argNextH, nullptr, nullptr,
						false, false);
}

fk_Edge * fk_Operation::SeparateLoop(fk_Half *argPrevH, fk_Half *argNextH,
									 fk_Half *lLOneH, fk_Half *rLOneH,
									 bool lVPFlag, bool rVPFlag,
									 int argEID, int argLHID,
									 int argRHID, int argLID)
{
	fk_Loop *curL, *newL;
	fk_Half *newLH, *newRH;
	fk_Edge *newE;
	fk_Half *oldNextH, *oldPrevH;
	fk_Vertex *lV, *rV;
	int uniRLOneHID;

	if(checkDB() == false) return nullptr;

	curL = argPrevH->getParentLoop();

	// argPrevH と argNextH が異なるループに属す場合のエラー処理 
	if(curL == nullptr || curL != argNextH->getParentLoop()) {
		Error::Put("fk_Operation", "separateLoop", 1, "Illegal Loop Error.");
		return nullptr;
	}

	// argPrevH の次の半稜線が argNextH だった場合のエラー処理 
	if(argPrevH->getNextHalf() == argNextH) {
		Error::Put("fk_Operation", "separateLoop", 2, "Illegal Connection Error.");
		return nullptr;
	}

	oldNextH = argPrevH->getNextHalf();
	oldPrevH = argNextH->getPrevHalf();

	lV = oldNextH->getVertex();
	rV = argNextH->getVertex();

	// 新たな位相要素の生成 
	newE = (argEID == FK_UNDEFINED) ?
		GetNewEdgeObj() : GetNewEdgeObj(argEID);
	newLH = (argLHID == FK_UNDEFINED) ?
		GetNewHalfObj() : GetNewHalfObj(argLHID);
	newRH = (argRHID == FK_UNDEFINED) ?
		GetNewHalfObj() : GetNewHalfObj(argRHID);

	// 新稜線の属性設定 
	newE->SetLeftHalf(newLH->getID());
	newE->SetRightHalf(newRH->getID());

	// 新半稜線の属性設定 (ループ以外) 
	newLH->SetVertex(lV->getID());
	newLH->SetNextHalf(argNextH->getID());
	newLH->SetPrevHalf(argPrevH->getID());
	newLH->SetParentEdge(newE->getID());

	newRH->SetVertex(rV->getID());
	newRH->SetNextHalf(oldNextH->getID());
	newRH->SetPrevHalf(oldPrevH->getID());
	newRH->SetParentEdge(newE->getID());
	newRH->SetParentLoop(curL->getID());

	// 旧半稜線の属性再設定 (ループ以外) 
	argPrevH->SetNextHalf(newLH->getID());
	argNextH->SetPrevHalf(newLH->getID());
	oldPrevH->SetNextHalf(newRH->getID());
	oldNextH->SetPrevHalf(newRH->getID());
	
	if(lVPFlag == true) {
		lV->SetOneHalf(newLH->getID());
	}

	if(rVPFlag == true) {
		rV->SetOneHalf(newRH->getID());
	}

	// 旧ループが保持する半稜線情報を再設定 
	uniRLOneHID = curL->getOneHalf()->getID();
	if(rLOneH == nullptr) {
		curL->SetOneHalf(newRH->getID());
	} else {
		curL->SetOneHalf(rLOneH->getID());
	}

	curL->ModifyLoop();

	// 新ループ側の半稜線へ、ループ情報を設定 
	if((newL = SetLoop(newLH, false, nullptr, argLID)) == nullptr) {
		Error::Put("fk_Operation", "separateLoop", 3, "Set Loop Error.");
		return nullptr;
	}

	if(lLOneH != nullptr) {
		newL->SetOneHalf(lLOneH->getID());
	}

	UndefVNorm(lV);
	UndefVNorm(rV);

	if(_m->historyMode == true) {
		int pHID = argPrevH->getID();
		int nHID = argNextH->getID();
		int newLID = newL->getID();
		int newEID = newE->getID();
		int newLHID = newLH->getID();
		int newRHID = newRH->getID();
		int lLOneHID = (lLOneH != nullptr) ? lLOneH->getID() : FK_UNDEFINED;
		int rLOneHID = (rLOneH != nullptr) ? rLOneH->getID() : FK_UNDEFINED;

		_m->history.Open(int(Code::SEPL));
		_m->history.PushInt(pHID);
		_m->history.PushInt(nHID);
		_m->history.PushInt(newEID);
		_m->history.PushInt(newLHID);
		_m->history.PushInt(newRHID);
		_m->history.PushInt(newLID);
		_m->history.PushInt(lLOneHID);
		_m->history.PushInt(rLOneHID);
		_m->history.PushInt(uniRLOneHID);
		_m->history.PushBool(lVPFlag);
		_m->history.PushBool(rVPFlag);
		_m->history.Close();
	}

	return newE;
}


bool fk_Operation::uniteLoop(fk_Edge *argE)
{
	return UniteLoop(argE, nullptr);
}

bool fk_Operation::UniteLoop(fk_Edge *argE, fk_Half *argNewRL1H)
{
	fk_Loop *lL, *rL;
	fk_Half *lH, *rH, *lLOneH, *rLOneH;
	fk_Half *lNextH, *lPrevH, *rNextH, *rPrevH;
	fk_Vertex *lV, *rV;
	int eID, pHID, nHID, loopID, lHID, rHID, lLOneHID, rLOneHID;
	int uniRLOneHID;
	bool lVPFlag, rVPFlag;

	if(checkDB() == false) return false;

	lH = argE->getLeftHalf();
	rH = argE->getRightHalf();
	lL = lH->getParentLoop();
	rL = rH->getParentLoop();

	if(lL == nullptr || rL == nullptr) {
		Error::Put("fk_Operation", "uniteLoop", 1, "No BothDefEdge Error.");
		return false;
	}

	if(lL == rL) {
		Error::Put("fk_Operation", "uniteLoop", 2, "Half Edge Connection Error.");
		return false;
	}

	lV = lH->getVertex();
	rV = rH->getVertex();

	lNextH = rH->getNextHalf();
	lPrevH = lH->getPrevHalf();
	rNextH = lH->getNextHalf();
	rPrevH = rH->getPrevHalf();

	lLOneH = lL->getOneHalf();
	rLOneH = rL->getOneHalf();

	eID = argE->getID();
	lHID = lH->getID();
	rHID = rH->getID();
	loopID = lL->getID();
	pHID = lPrevH->getID();
	nHID = rNextH->getID();

	lPrevH->SetNextHalf(lNextH->getID());
	lNextH->SetPrevHalf(lPrevH->getID());
	rPrevH->SetNextHalf(rNextH->getID());
	rNextH->SetPrevHalf(rPrevH->getID());

	if(lV->getOneHalf() == lH) {
		lV->SetOneHalf(lNextH->getID());
		lVPFlag = true;
	} else {
		lVPFlag = false;
	}

	if(rV->getOneHalf() == rH) {
		rV->SetOneHalf(rNextH->getID());
		rVPFlag = true;
	} else {
		rVPFlag = false;
	}

	if(lLOneH == lH) {
		lLOneHID = FK_UNDEFINED;
	} else {
		lLOneHID = lLOneH->getID();
	}

	if(rLOneH == rH) {
		rLOneHID = FK_UNDEFINED;
		SetLoop(lNextH, false, rL);
	} else {
		rLOneHID = rLOneH->getID();
		SetLoop(rL->getOneHalf(), false, rL);
	}

	if(argNewRL1H != nullptr) {
		uniRLOneHID = argNewRL1H->getID();
		rL->SetOneHalf(uniRLOneHID);
	} else {
		uniRLOneHID = rL->getOneHalf()->getID();
	}

	if(DeleteEdgeObj(argE) == false || DeleteHalfObj(lH) == false ||
	   DeleteHalfObj(rH) == false || DeleteLoopObj(lL) == false) {
		Error::Put("fk_Operation", "uniteLoop", 3, "Delete Elements Error.");
		return false;
	}

	UndefVNorm(lV);
	UndefVNorm(rV);

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::UNITL));
		_m->history.PushInt(pHID);
		_m->history.PushInt(nHID);
		_m->history.PushInt(eID);
		_m->history.PushInt(lHID);
		_m->history.PushInt(rHID);
		_m->history.PushInt(loopID);
		_m->history.PushInt(lLOneHID);
		_m->history.PushInt(rLOneHID);
		_m->history.PushInt(uniRLOneHID);
		_m->history.PushBool(lVPFlag);
		_m->history.PushBool(rVPFlag);
		_m->history.Close();
	}

	return true;
}

fk_Vertex * fk_Operation::separateEdge(fk_Edge *argE)
{
	return SeparateEdge(argE, false, false, false, false, nullptr);
}

fk_Vertex * fk_Operation::SeparateEdge(fk_Edge *argE, bool argOrgEFlag,
									   bool argNewEFlag,
									   bool argL1PFlag, bool argL2PFlag,
									   fk_Vector *argPos,
									   int argVID, int argEID,
									   int argH1ID, int argH2ID)
{
	fk_Edge *newE;					// 新稜線 
	fk_Half *newH1, *newH2;			// 新半稜線 
	fk_Half *orgH1, *orgH2;			// argE の半稜線 
	fk_Half *orgPrevH, *orgNextH;	// curRH の前半稜線と、curLH の次半稜線 
	fk_Vertex *v1, *v2, *newV;		// argE の両端点と新頂点 
	fk_Loop *l1, *l2;				// argE の属するループ 

	if(checkDB() == false) return nullptr;

	// 各データの取得 
	if(argOrgEFlag == true) {
		orgH1 = argE->getLeftHalf();
		orgH2 = argE->getRightHalf();
	} else {
		orgH1 = argE->getRightHalf();
		orgH2 = argE->getLeftHalf();
	}

	v1 = orgH1->getVertex();
	v2 = orgH2->getVertex();
	l1 = orgH1->getParentLoop();
	l2 = orgH2->getParentLoop();
	orgPrevH = orgH1->getPrevHalf();
	orgNextH = orgH2->getNextHalf();

	// 新位相要素の生成 
	newV = (argVID == FK_UNDEFINED) ?
		GetNewVertexObj() : GetNewVertexObj(argVID);
	newE = (argEID == FK_UNDEFINED) ?
		GetNewEdgeObj() : GetNewEdgeObj(argEID);
	newH1 = (argH1ID == FK_UNDEFINED) ?
		GetNewHalfObj() : GetNewHalfObj(argH1ID);
	newH2 = (argH2ID == FK_UNDEFINED) ?
		GetNewHalfObj() : GetNewHalfObj(argH2ID);

	// 稜線情報の設定 
	if(argNewEFlag == true) {
		newE->SetLeftHalf(newH1->getID());
		newE->SetRightHalf(newH2->getID());
	} else {
		newE->SetLeftHalf(newH2->getID());
		newE->SetRightHalf(newH1->getID());
	}

	// 新半稜線情報の設定 
	newH1->SetVertex(v1->getID());
	newH2->SetVertex(newV->getID());

	newH1->SetParentEdge(newE->getID());
	newH2->SetParentEdge(newE->getID());

	newH1->SetParentLoop(l1->getID());
	newH2->SetParentLoop(l2->getID());

	newH1->SetNextHalf(orgH1->getID());
	newH1->SetPrevHalf(orgPrevH->getID());
	newH2->SetNextHalf(orgNextH->getID());
	newH2->SetPrevHalf(orgH2->getID());

	// その他の半稜線の接続関係設定 

	orgH1->SetPrevHalf(newH1->getID());
	orgH2->SetNextHalf(newH2->getID());
	orgPrevH->SetNextHalf(newH1->getID());
	orgNextH->SetPrevHalf(newH2->getID());
	orgH1->SetVertex(newV->getID());

	// 新頂点情報の設定 
	if(argPos != nullptr) {
		newV->SetPosition(*argPos);
	} else {
		newV->SetPosition((v1->getPosition() + v2->getPosition())/2.0);
	}
	newV->SetOneHalf(orgH1->getID());

	if(v1->getOneHalf() == orgH1) v1->SetOneHalf(newH1->getID());

	v1->UndefNormal();
	v2->UndefNormal();

	if(argL1PFlag == true && l1 != nullptr) {
		l1->SetOneHalf(newH1->getID());
	}

	if(argL2PFlag == true && l2 != nullptr) {
		l2->SetOneHalf(newH2->getID());
	}

	if(l1 != nullptr) l1->ModifyLoop();
	if(l2 != nullptr) l2->ModifyLoop();

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::SEPE));
		_m->history.PushInt(argE->getID());
		_m->history.PushInt(newV->getID());
		_m->history.PushInt(newE->getID());
		_m->history.PushInt(newH1->getID());
		_m->history.PushInt(newH2->getID());
		_m->history.PushBool(argOrgEFlag);
		_m->history.PushBool(argNewEFlag);
		_m->history.PushBool(argL1PFlag);
		_m->history.PushBool(argL2PFlag);
		_m->history.PushVec(newV->getPosition());
		_m->history.Close();
	}

	return newV;
}


bool fk_Operation::uniteEdge(fk_Vertex *argV)
{
	return UniteEdge(argV);
}

bool fk_Operation::UniteEdge(fk_Vertex *argV)
{
	fk_Half *delH, *delMateH;
	fk_Half *remainH, *remainMateH;
	fk_Half *nextH, *prevH;
	fk_Edge *remainE, *delE;
	fk_Vertex *v1;
	fk_Vector pos;
	fk_Loop *l1, *l2;
	bool remEFlag, delEFlag, l1PFlag, l2PFlag;
	int delVID, delEID, delHID, delMateHID;
	
	if(checkDB() == false) return false;

	if(getENumOnV(argV) != 2) {
		Error::Put("fk_Operation", "uniteEdge", 1, "Connect Edge Number Error.");
		return false;
	}

	remainH = argV->getOneHalf();
	remainMateH = getMateHOnH(remainH);
	delH = remainH->getPrevHalf();
	delMateH = remainMateH->getNextHalf();

	remainE = remainH->getParentEdge();
	delE = delH->getParentEdge();

	nextH = delMateH->getNextHalf();
	prevH = delH->getPrevHalf();
	v1 = delH->getVertex();
	pos = v1->getPosition();

	l1 = remainH->getParentLoop();
	l2 = remainMateH->getParentLoop();

	if(getVNumOnL(l1) <= 3 || getVNumOnL(l2) <= 3) {
		Error::Put("fk_Operation", "uniteEdge", 2, "Polygon Size Error.");
		return false;
	}

	remEFlag = (remainH == remainE->getLeftHalf()) ? true : false;
	delEFlag = (delH == delE->getLeftHalf()) ? true : false;

	if(delH == l1->getOneHalf()) {
		l1PFlag = true;
		l1->SetOneHalf(remainH->getID());
	} else {
		l1PFlag = false;
	}

	if(delMateH == l2->getOneHalf()) {
		l2PFlag = true;
		l2->SetOneHalf(remainMateH->getID());
	} else {
		l2PFlag = false;
	}

	remainH->SetPrevHalf(prevH->getID());
	prevH->SetNextHalf(remainH->getID());
	remainMateH->SetNextHalf(nextH->getID());
	nextH->SetPrevHalf(remainMateH->getID());
	remainH->SetVertex(v1->getID());

	if(v1->getOneHalf() == delH) v1->SetOneHalf(remainH->getID());

	delVID = argV->getID();
	delEID = delE->getID();
	delHID = delH->getID();
	delMateHID = delMateH->getID();

	if(DeleteEdgeObj(delE) == false ||
	   DeleteHalfObj(delH) == false ||
	   DeleteHalfObj(delMateH) == false ||
	   DeleteVertexObj(argV) == false) {
		Error::Put("fk_Operation", "uniteEdge", 3, "Delete Elements Error.");
		return false;
	}

	UndefVNorm(remainH->getVertex());
	UndefVNorm(remainMateH->getVertex());

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::UNITE));
		_m->history.PushInt(remainE->getID());
		_m->history.PushInt(delVID);
		_m->history.PushInt(delEID);
		_m->history.PushInt(delHID);
		_m->history.PushInt(delMateHID);
		_m->history.PushBool(remEFlag);
		_m->history.PushBool(delEFlag);
		_m->history.PushBool(l1PFlag);
		_m->history.PushBool(l2PFlag);
		_m->history.PushVec(pos);
		_m->history.Close();
	}

	return true;
}

void fk_Operation::negateBody(void)
{
	NegateBody();
	return;
}

void fk_Operation::NegateBody(void)
{
	vector<fk_Half *> rNext, rPrev, lNext, lPrev;
	fk_Edge *curE;
	fk_Loop *curL;
	_st i;

	if(checkDB() == false) return;
	for(curE = getNextE(nullptr);
		curE != nullptr;
		curE = getNextE(curE)) {
		rNext.push_back(getMateHOnH(curE->getLeftHalf()->getPrevHalf()));
		rPrev.push_back(getMateHOnH(curE->getLeftHalf()->getNextHalf()));
		lNext.push_back(getMateHOnH(curE->getRightHalf()->getPrevHalf()));
		lPrev.push_back(getMateHOnH(curE->getRightHalf()->getNextHalf()));
	}

	i = 0;
	for(curE = getNextE(nullptr);
		curE != nullptr;
		curE = getNextE(curE)) {
		curE->getRightHalf()->SetNextHalf(rNext[i]->getID());
		curE->getRightHalf()->SetPrevHalf(rPrev[i]->getID());
		curE->getLeftHalf()->SetNextHalf(lNext[i]->getID());
		curE->getLeftHalf()->SetPrevHalf(lPrev[i]->getID());
		i++;
	}

	for(curL = getNextL(nullptr);
		curL != nullptr;
		curL = getNextL(curL)) {
		curL->SetOneHalf(getMateHOnH(curL->getOneHalf())->getID());
	}

	if(_m->historyMode == true) {
		_m->history.Open(int(Code::NEGATE));
		_m->history.Close();
	}

	return;
}

void fk_Operation::setHistoryMode(bool argFlg)
{
	if(argFlg == false) _m->history.Init();
	_m->historyMode = argFlg;
	return;
}

bool fk_Operation::getHistoryMode(void)
{
	return _m->historyMode;
}

void fk_Operation::setHistoryMark(void)
{
	_m->history.SetMark();
	return;
}

bool fk_Operation::undoHistory(void)
{
	fk_Command com;
	bool orgMode;

	if(_m->history.GetComIndex() == -1) return false;

	orgMode = _m->historyMode;
	_m->historyMode = false;
	com = _m->history.GetCom();
	do {
		UndoCom(&com);
		_m->history.Undo();
		if(_m->history.GetComIndex() == -1) break;
		com = _m->history.GetCom();
	} while(com.GetMarkStatus() == false);

	_m->historyMode = orgMode;
	return true;
}

bool fk_Operation::redoHistory(void)
{
	fk_Command com;
	bool orgMode;

	if(_m->history.Redo() == false) return false;

	orgMode = _m->historyMode;
	_m->historyMode = false;

	do {
		com = _m->history.GetCom();
		RedoCom(&com);
		if(com.GetMarkStatus() == true) break;
	} while(_m->history.Redo() == true);

	_m->historyMode = orgMode;
	return true;
}

void fk_Operation::UndoCom(fk_Command *argCom)
{
	unsigned int boolI, intI, vecI;
	fk_Vertex *tmpV1, *tmpV2;
	fk_Half *tmpH1, *tmpH2, *tmpH3, *tmpH4;
	fk_Vector tmpPos;

	boolI = argCom->GetBoolIndex();
	intI = argCom->GetIntIndex();
	vecI = argCom->GetVecIndex();

	switch(Code(argCom->GetCommandID())) {
	  case Code::MAKEV:
		DeleteVertex(getVData(_m->history.GetInt(intI)));
		break;

	  case Code::DELV:
		MakeVertex(_m->history.GetVec(vecI), _m->history.GetInt(intI));
		break;

	  case Code::MOVEV:
		MoveVertex(getVData(_m->history.GetInt(intI)), _m->history.GetVec(vecI));
		break;

	  case Code::MAKEE1:
		DeleteEdge1(getEData(_m->history.GetInt(intI+2)));
		break;

	  case Code::MAKEE2:
		DeleteEdge2(getHData(_m->history.GetInt(intI+3)));
		break;

	  case Code::MAKEE3:
		DeleteEdge3(getEData(_m->history.GetInt(intI+2)));
		break;

	  case Code::DELE1:
		MakeEdge1(getVData(_m->history.GetInt(intI)),
				  getVData(_m->history.GetInt(intI+1)),
				  _m->history.GetInt(intI+2),
				  _m->history.GetInt(intI+3),
				  _m->history.GetInt(intI+4));
		break;

	  case Code::DELE2:
		tmpV2 = getVData(_m->history.GetInt(intI));
		tmpH1 = getHData(_m->history.GetInt(intI+1));
		tmpH2 = tmpH1->getNextHalf();
		tmpV1 = tmpH2->getVertex();

		MakeEdge2(tmpV1, tmpV2, tmpH1, tmpH2,
				  _m->history.GetBool(boolI), _m->history.GetBool(boolI+1),
				  _m->history.GetInt(intI+2),
				  _m->history.GetInt(intI+3),
				  _m->history.GetInt(intI+4));
		break;

	  case Code::DELE3:
		tmpH1 = getHData(_m->history.GetInt(intI));
		tmpH2 = tmpH1->getNextHalf();
		tmpH3 = getHData(_m->history.GetInt(intI+1));
		tmpH4 = tmpH3->getNextHalf();
		tmpV1 = tmpH2->getVertex();
		tmpV2 = tmpH4->getVertex();

		MakeEdge3(tmpV1, tmpV2, tmpH1, tmpH2, tmpH3, tmpH4,
				  _m->history.GetBool(boolI),
				  _m->history.GetBool(boolI+1),
				  _m->history.GetInt(intI+2),
				  _m->history.GetInt(intI+3),
				  _m->history.GetInt(intI+4));
		break;

	  case Code::MAKEL:
		DeleteLoop(getLData(_m->history.GetInt(intI)));
		break;

	  case Code::DELL:
		MakeLoop(getHData(_m->history.GetInt(intI+1)), _m->history.GetInt(intI));
		break;

	  case Code::SEPL:
		UniteLoop(getEData(_m->history.GetInt(intI+2)),
				  getHData(_m->history.GetInt(intI+8)));
		break;

	  case Code::UNITL:
		tmpH1 = getHData(_m->history.GetInt(intI));
		tmpH2 = getHData(_m->history.GetInt(intI+1));
		tmpH3 = (_m->history.GetInt(intI+6) != FK_UNDEFINED) ?
			getHData(_m->history.GetInt(intI+6)) : nullptr;
		tmpH4 = (_m->history.GetInt(intI+7) != FK_UNDEFINED) ?
			getHData(_m->history.GetInt(intI+7)) : nullptr;

		SeparateLoop(tmpH1, tmpH2, tmpH3, tmpH4,
					 _m->history.GetBool(boolI),
					 _m->history.GetBool(boolI+1),
					 _m->history.GetInt(intI+2),
					 _m->history.GetInt(intI+3),
					 _m->history.GetInt(intI+4),
					 _m->history.GetInt(intI+5));
		break;

	  case Code::SEPE:
		UniteEdge(getVData(_m->history.GetInt(intI+1)));
		break;

	  case Code::UNITE:
		tmpPos = _m->history.GetVec(vecI),
		SeparateEdge(getEData(_m->history.GetInt(intI)),
					 _m->history.GetBool(boolI),
					 _m->history.GetBool(boolI+1),
					 _m->history.GetBool(boolI+2),
					 _m->history.GetBool(boolI+3),
					 &tmpPos,
					 _m->history.GetInt(intI+1),
					 _m->history.GetInt(intI+2),
					 _m->history.GetInt(intI+3),
					 _m->history.GetInt(intI+4));
		break;

	  case Code::NEGATE:
		NegateBody();
		break;

	  default:
		break;
	}

	return;
}

void fk_Operation::RedoCom(fk_Command *argCom)
{
	unsigned int boolI, intI, vecI;
	fk_Vertex *tmpV1, *tmpV2;
	fk_Half *tmpH1, *tmpH2, *tmpH3, *tmpH4;
	fk_Vector tmpPos;

	boolI = argCom->GetBoolIndex();
	intI = argCom->GetIntIndex();
	vecI = argCom->GetVecIndex();

	switch(Code(argCom->GetCommandID())) {
	  case Code::MAKEV:
		MakeVertex(_m->history.GetVec(vecI), _m->history.GetInt(intI));
		break;

	  case Code::DELV:
		DeleteVertex(getVData(_m->history.GetInt(intI)));
		break;

	  case Code::MOVEV:
		MoveVertex(getVData(_m->history.GetInt(intI)), _m->history.GetVec(vecI+1));
		break;

	  case Code::MAKEE1:
		MakeEdge1(getVData(_m->history.GetInt(intI)),
				  getVData(_m->history.GetInt(intI+1)),
				  _m->history.GetInt(intI+2),
				  _m->history.GetInt(intI+3),
				  _m->history.GetInt(intI+4));
		break;

	  case Code::MAKEE2:
		tmpV2 = getVData(_m->history.GetInt(intI));
		tmpH1 = getHData(_m->history.GetInt(intI+1));
		tmpH2 = tmpH1->getNextHalf();
		tmpV1 = tmpH2->getVertex();
						 
		MakeEdge2(tmpV1, tmpV2, tmpH1, tmpH2,
				  _m->history.GetBool(boolI), _m->history.GetBool(boolI+1),
				  _m->history.GetInt(intI+2),
				  _m->history.GetInt(intI+3),
				  _m->history.GetInt(intI+4));
		break;

	  case Code::MAKEE3:
		tmpH1 = getHData(_m->history.GetInt(intI));
		tmpH2 = tmpH1->getNextHalf();
		tmpH3 = getHData(_m->history.GetInt(intI+1));
		tmpH4 = tmpH3->getNextHalf();
		tmpV1 = tmpH2->getVertex();
		tmpV2 = tmpH4->getVertex();

		MakeEdge3(tmpV1, tmpV2, tmpH1, tmpH2, tmpH3, tmpH4,
				  _m->history.GetBool(boolI),
				  _m->history.GetBool(boolI+1),
				  _m->history.GetInt(intI+2),
				  _m->history.GetInt(intI+3),
				  _m->history.GetInt(intI+4));
		break;

	  case Code::DELE1:
		DeleteEdge1(getEData(_m->history.GetInt(intI+2)));
		break;

	  case Code::DELE2:
		DeleteEdge2(getHData(_m->history.GetInt(intI+3)));
		break;

	  case Code::DELE3:
		DeleteEdge3(getEData(_m->history.GetInt(intI+2)));
		break;

	  case Code::MAKEL:
		MakeLoop(getHData(_m->history.GetInt(intI+1)), _m->history.GetInt(intI));
		break;

	  case Code::DELL:
		DeleteLoop(getLData(_m->history.GetInt(intI)));
		break;

	  case Code::SEPL:
		tmpH1 = getHData(_m->history.GetInt(intI));
		tmpH2 = getHData(_m->history.GetInt(intI+1));
		tmpH3 = (_m->history.GetInt(intI+6) != FK_UNDEFINED) ?
			getHData(_m->history.GetInt(intI+6)) : nullptr;
		tmpH4 = (_m->history.GetInt(intI+7) != FK_UNDEFINED) ?
			getHData(_m->history.GetInt(intI+7)) : nullptr;

		SeparateLoop(tmpH1, tmpH2, tmpH3, tmpH4,
					 _m->history.GetBool(boolI),
					 _m->history.GetBool(boolI+1),
					 _m->history.GetInt(intI+2),
					 _m->history.GetInt(intI+3),
					 _m->history.GetInt(intI+4),
					 _m->history.GetInt(intI+5));
		break;

	  case Code::UNITL:
		UniteLoop(getEData(_m->history.GetInt(intI+2)),
				  getHData(_m->history.GetInt(intI+8)));
		break;

	  case Code::SEPE:
		tmpPos = _m->history.GetVec(vecI);

		SeparateEdge(getEData(_m->history.GetInt(intI)),
					 _m->history.GetBool(boolI),
					 _m->history.GetBool(boolI+1),
					 _m->history.GetBool(boolI+2),
					 _m->history.GetBool(boolI+3),
					 &tmpPos,
					 _m->history.GetInt(intI+1),
					 _m->history.GetInt(intI+2),
					 _m->history.GetInt(intI+3),
					 _m->history.GetInt(intI+4));
		break;

	  case Code::UNITE:
		UniteEdge(getVData(_m->history.GetInt(intI+1)));
		break;

	  case Code::NEGATE:
		NegateBody();
		break;

	  default:
		break;
	}

	return;
}

void fk_Operation::PrintHistorySize(void)
{
	_m->history.PrintSize();
	return;
}

void fk_Operation::setTesselateMode(bool argMode)
{
	fk_Loop *curL;

	_m->tesselateMode = argMode;

	if(_m->tesselateMode == true) {
		for(curL = getNextL(nullptr); curL != nullptr; curL = getNextL(curL)) {
			curL->setTesselateMode(true);
			curL->isTesselated();
		}
	} else {
		DeleteAllTesselateData();
	}

	return;
}

bool fk_Operation::getTesselateMode(void)
{
	return _m->tesselateMode;
}

void fk_Operation::DeleteAllTesselateData(void)
{
	fk_Loop *curL;

	for(curL = getNextL(nullptr); curL != nullptr; curL = getNextL(curL)) {
		curL->setTesselateMode(false);
	}
	return;
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
