/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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

#define FK_DEF_SIZETYPE
#include <FK/Modify.h>
#include <FK/IFSetHandle.H>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Edge.h>
#include <FK/Loop.h>
#include <FK/SubDivision.H>
#include <FK/Error.H>

using namespace std;

fk_Modify::fk_Modify(fk_DataBase *argDB)
	: fk_Operation(argDB)
{
	return;
}

fk_Modify::~fk_Modify()
{
	return;
}

fk_Loop * fk_Modify::removeVertexInLoop(fk_Vertex *argVx)
{
	vector<fk_Edge *>	connectE;
	vector<fk_Loop *>	connectL;
	vector<fk_Vertex *>	neighborV;
	_st					i;
	fk_Half				*remainH;
	fk_Loop				*retL;

	if(checkDB() == false) return nullptr;
	if(existVertex(argVx) == false) return nullptr;

	neighborV = getAllNeighborVOnV(argVx);
	for(i = 0; i < neighborV.size(); i++) {
		if(getENumOnV(neighborV[i]) < 3) return nullptr;
	}

	connectE = getAllEOnV(argVx);
	connectL = getAllLOnV(argVx);
	remainH = argVx->getOneHalf()->getNextHalf();

	for(i = 0; i < connectL.size(); i++) {
		if(deleteLoop(connectL[i]) == false) {
			return nullptr;
		}
	}

	for(i = 0; i < connectE.size(); i++) {
		if(deleteEdge(connectE[i]) == false) return nullptr;
	}

	if(deleteVertex(argVx) == false) return nullptr;

	retL = makeLoop(remainH);
	return retL;
}

bool fk_Modify::contractEdge(fk_Edge *argEd, bool rightFlg)
{
	fk_Vector		newPos;
	fk_Vertex		*rV, *lV;

	// データベースが存在しない 
	if(checkDB() == false) return false;

	// 稜線データがデータベース中に存在しない 
	if(existEdge(argEd) == false) return false;

	rV = getRightVOnE(argEd);
	lV = getLeftVOnE(argEd);

	newPos = (rV->getPosition() + lV->getPosition())/2.0;

	return contractEdge(argEd, newPos, rightFlg);
}

bool fk_Modify::contractEdge(fk_Edge *argEd, fk_Vector argPos, bool rightFlg)
{
	fk_Vertex				*remainV, *deleteV;
	fk_Vertex				*NeighborV[2];
	fk_Half					*newArgFirstH, *curH;
	fk_Half					*newArgH1 = nullptr;
	fk_Half					*newArgH2 = nullptr;
	fk_Loop					*remainL;
	fk_Edge					*newE = nullptr;
	vector<fk_Vertex *>		OldConnectV;
	vector<fk_Half *>		NewConnectH;
	_st						i;


	// データベースが存在しない 
	if(checkDB() == false) return false;

	// 稜線データがデータベース中に存在しない 
	if(existEdge(argEd) == false) return false;

	// 稜線が定義稜線でない 
	if(argEd->getRightHalf()->getParentLoop() == nullptr ||
	   argEd->getLeftHalf()->getParentLoop() == nullptr) {
		return false;
	}

	// 稜線が削除できる状態にない 
	if(checkContract(argEd) == false) return false;

	if(rightFlg == true) {
		// remainV に残す頂点を, deleteV に削除する頂点を代入 
		remainV = getRightVOnE(argEd);
		deleteV = getLeftVOnE(argEd);

		// 頂点の移動先を計算 
		newArgFirstH = getLeftHOnE(argEd)->getNextHalf();

		// argEd の対になる頂点の取得 
		NeighborV[0] = newArgFirstH->getNextHalf()->getVertex();
		NeighborV[1] = getRightHOnE(argEd)->getPrevHalf()->getVertex();
	} else {
		// remainV に残す頂点を, deleteV に削除する頂点を代入 
		remainV = getLeftVOnE(argEd);
		deleteV = getRightVOnE(argEd);

		// 頂点の移動先を計算 
		newArgFirstH = getRightHOnE(argEd)->getNextHalf();

		// argEd の対になる頂点の取得 
		NeighborV[0] = newArgFirstH->getNextHalf()->getVertex();
		NeighborV[1] = getLeftHOnE(argEd)->getPrevHalf()->getVertex();
	}

	// argEd を削除 
	if(uniteLoop(argEd) == false) return false;

	// 削除する頂点と隣接している頂点群を OldConnectV に格納 
	OldConnectV = getAllNeighborVOnV(deleteV);

	// deleteV を削除 
	remainL = removeVertexInLoop(deleteV);
	if(remainL != newArgFirstH->getParentLoop()) {
		fk_PutError("fk_Modify", "ContractEdge", 1,
					"Illegal Loop Error.");
		return false;
	}

	// deleteV に接続していた半稜線群の抽出 
	curH = newArgFirstH->getNextHalf();
	while(curH != newArgFirstH) {
		for(i = 0; i < OldConnectV.size(); i++) {
			if(curH->getVertex() == OldConnectV[i]) {
				if(OldConnectV[i] != NeighborV[0] &&
				   OldConnectV[i] != NeighborV[1]) {
					NewConnectH.push_back(curH->getPrevHalf());
				}
				break;
			}
		}
		curH = curH->getNextHalf();
	}

	// 抽出した半稜線を元に, remainV と再接続 
	for(i = 0; i < NewConnectH.size(); i++) {
		newArgH1 = NewConnectH[i];
		if(i == 0) {
			newArgH2 = newArgFirstH;
		} else {
			newArgH2 = (getRightVOnE(newE) == remainV) ?
				getRightHOnE(newE) : getLeftHOnE(newE);
		}
		newE = separateLoop(newArgH1, newArgH2);
		if(newE == nullptr) return false;
	}

	// remainV を移動 
	moveVertex(remainV, argPos);

	return true;
}

bool fk_Modify::checkContract(fk_Edge *argEd)
{
	fk_Loop		*rL, *lL;
	fk_Half		*rH, *lH;
	fk_Vertex	*rV, *lV;

	if(argEd == nullptr) return false;
	rH = argEd->getRightHalf();
	lH = argEd->getLeftHalf();

	rL = rH->getParentLoop();
	lL = lH->getParentLoop();

	rV = rH->getVertex();
	lV = lH->getVertex();

	if(rL != nullptr) {
		if(CheckLoop4Cont(rH) == false) return false;
	}

	if(lL != nullptr) {
		if(CheckLoop4Cont(lH) == false) return false;
	}

	if(getENumOnV(rV) <= 2 || getENumOnV(lV) <= 2) {
		return false;
	}

	return true;
}

bool fk_Modify::CheckLoop4Cont(fk_Half *argHf)
{
	fk_Half	*nextH, *prevH;
	fk_Half	*nMateH, *pMateH;

	// argHf が nullptr の場合 
	if(argHf == nullptr) return false;

	nextH = argHf->getNextHalf();
	prevH = argHf->getPrevHalf();

	// nextH と prevH が同一の場合 (argH が接続されていない場合) 
	if(nextH == prevH) return false;

	nMateH = getMateHOnH(nextH)->getPrevHalf();
	pMateH = getMateHOnH(prevH)->getNextHalf();

	if(nMateH->getParentEdge() == pMateH->getParentEdge()) {
		// nextH の向かい側の面と prevH の向かい側の面が隣り合っている場合 
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////


fk_Loop * fk_Modify::makePolygon(vector<fk_Vector> *argVec,
							bool argOpenFlg, bool argClearFlg)
{
	_st						i;
	fk_Vertex				*curV;
	vector<fk_Vertex *>		VertexArray;
	fk_Edge					*prevE;
	fk_Half					*nextH, *prevH, *lH, *rH, *nextH2, *prevH2;
	fk_Loop					*retL = nullptr;

	if(argVec == nullptr) return retL;
	if(argVec->size() < 3) return retL;
	VertexArray.clear();

	if(checkDB() == false) return retL;

	if(argClearFlg == true) {
		AllClear_();
	}

	for(i = 0; i < argVec->size(); i++) {
		curV = makeVertex((*argVec)[i]);
		VertexArray.push_back(curV);
	}

	if((prevE = makeEdge(VertexArray[1], VertexArray[0])) == nullptr) {
		fk_PutError("fk_Modify", "makePolygon", 1, "Make Edge Error.");
		AllClear_();
		return retL;
	}

	for(i = 2; i < VertexArray.size(); i++) {
		lH = prevE->getLeftHalf();
		rH = prevE->getRightHalf();
		if(lH->getVertex() == VertexArray[i-1]) {
			prevH = rH;
			nextH = lH;
		} else {
			prevH = lH;
			nextH = rH;
		}

		if((prevE = makeEdge(VertexArray[i-1], VertexArray[i],
							 prevH, nextH)) == nullptr) {
			fk_PutError("fk_Modify", "makePolygon", 2, "Make Edge Error.");
			AllClear_();
			return retL;
		}
	}

	if(argOpenFlg == false) {
		nextH = getOneHOnV(VertexArray.back());
		prevH = getMateHOnH(nextH);

		nextH2 = getOneHOnV(VertexArray[0]);
		prevH2 = getMateHOnH(nextH2);

		if(makeEdge(VertexArray.back(), VertexArray[0],
					prevH, nextH, prevH2, nextH2) == nullptr) {
			fk_PutError("fk_Modify", "makePolygon", 3, "Make Edge Error.");
			AllClear_();
			return retL;
		}
		if((retL = makeLoop(prevH)) == nullptr) {
			fk_PutError("fk_Modify", "makePolygon", 4, "Make Loop Error.");
			AllClear_();
			return retL;
		}
	}

	return retL;
}

fk_Loop * fk_Modify::makePolygon(int argNum, fk_Vector *argVec,
							bool argOpenFlg, bool argClearFlg)
{
	vector<fk_Vector>	VecArray;
	_st					i, num;
	num = static_cast<_st>(argNum);

	VecArray.resize(num);
	for(i = 0; i < num; i++) VecArray[i] = argVec[i];

	return makePolygon(&VecArray, argOpenFlg, argClearFlg);
}

void fk_Modify::pushPolygonVertex(fk_Vector argVec, bool argOpenFlg)
{
	fk_Vertex			*startV, *curV;
	fk_Edge				*lastE;
	vector<fk_Vector>	VecArray;
	fk_Half				*nextH, *prevH;

	if(checkDB() == false) return;

	switch(getVNum()) {
	  case 0:
		makeVertex(argVec);
		break;

	  case 1:
		startV = getNextV(nullptr);
		curV = makeVertex(argVec);
		makeEdge(curV, startV);
		break;

	  default:
		if(argOpenFlg == true) {
			lastE = getLastE();
			startV = getLastV();
			if(getENumOnV(startV) != 1) return;
			nextH = (lastE->getRightHalf()->getVertex() == startV) ?
				lastE->getRightHalf() : lastE->getLeftHalf();
			prevH = getMateHOnH(nextH);
			curV = makeVertex(argVec);
			makeEdge(startV, curV, prevH, nextH);
		} else {

			curV = getNextV(nullptr);
			while(curV != nullptr) {
				VecArray.push_back(curV->getPosition());
				curV = getNextV(curV);
			}

			VecArray.push_back(argVec);
			AllClear_();
			makePolygon(&VecArray, false);
		}

		break;
	}

	return;
}

fk_Loop * fk_Modify::pushPolygon(vector<fk_Vector> *argVec, bool argOpenFlg)
{
	return makePolygon(argVec, argOpenFlg, false);
}

fk_Loop * fk_Modify::pushPolygon(int argNum,
								 fk_Vector *argVec, bool argOpenFlg)
{
	vector<fk_Vector>	VecArray;
	_st					i, num;

	num = static_cast<_st>(argNum);

	VecArray.resize(num);
	for(i = 0; i < num; i++) VecArray[i] = argVec[i];

	return makePolygon(&VecArray, argOpenFlg, false);
}

void fk_Modify::makePoint(vector<fk_Vector> *argVec)
{
	_st		i;

	if(argVec == nullptr) return;
	if(checkDB() == false) return;
	AllClear_();

	for(i = 0; i < argVec->size(); i++) {
		makeVertex((*argVec)[i]);
	}

	return;
}

void fk_Modify::makePoint(int argNum, fk_Vector *argVec)
{
	int			i;

	if(checkDB() == false) return;
	AllClear_();

	for(i = 0; i < argNum; i++) {
		makeVertex(argVec[i]);
	}

	return;
}

fk_Vertex * fk_Modify::pushPointVertex(fk_Vector argVec)
{
	return makeVertex(argVec);
}

void fk_Modify::makeLines(vector<fk_Vector> *argVec)
{
	_st			i;
	fk_Vertex	*v1, *v2;

	if(argVec == nullptr) return;
	if(checkDB() == false) return;
	AllClear_();

	for(i = 0; i < argVec->size()/2; i++) {
		v1 = makeVertex((*argVec)[2*i]);
		v2 = makeVertex((*argVec)[2*i+1]);
		makeEdge(v1, v2);
	}

	return;
}

void fk_Modify::makeLines(int argNum, fk_Vector *argVec)
{
	int			i;
	fk_Vertex		*v1, *v2;

	if(argVec == nullptr) return;
	if(checkDB() == false) return;
	AllClear_();

	for(i = 0; i < argNum; i++) {
		v1 = makeVertex(argVec[2*i]);
		v2 = makeVertex(argVec[2*i+1]);
		makeEdge(v1, v2);
	}

	return;
}

fk_Edge * fk_Modify::pushLines(fk_Vector argVec1, fk_Vector argVec2)
{
	fk_Vertex		*v1, *v2;
	
	if(checkDB() == false) return nullptr;
	v1 = makeVertex(argVec1);
	v2 = makeVertex(argVec2);
	return makeEdge(v1, v2);
}

bool fk_Modify::changeLine(int argID, fk_Vector argPos1, fk_Vector argPos2)
{
	fk_Vertex		*v1, *v2;

	if(checkDB() == false) return false;

	if((v1 = getVData(2*argID + 1)) == nullptr ||
	   (v2 = getVData(2*argID + 2)) == nullptr) {
		return false;
	}

	moveVertex(v1, argPos1);
	moveVertex(v2, argPos2);
	return true;
}

bool fk_Modify::setLinePos(int argEID, int argVID, fk_Vector argPos)
{
	fk_Vertex		*tmpV;

	if(checkDB() == false) return false;

	if((tmpV = getVData(2*argEID + argVID + 1)) == nullptr) {
		return false;
	}

	moveVertex(tmpV, argPos);
	return true;
}


bool fk_Modify::setLinePos(int argID, fk_Vector argPos)
{
	if(argID != 0 && argID != 1) return false;
	return setLinePos(0, argID, argPos);
}

void fk_Modify::makeBlock(double argX, double argY, double argZ)
{
	int						i, j;
	fk_Vector				tmpVec;
	vector<fk_Vector>		VecArray;
	vector<int>				LSet;
	vector< vector<int> >	LIndexSet;
	fk_IFSetHandle			IFSet;

	const static double VParam[8][3] = {
		{0.5, 0.5, 0.5},
		{-0.5, 0.5, 0.5},
		{0.5, -0.5, 0.5},
		{-0.5, -0.5, 0.5},
		{0.5, 0.5, -0.5},
		{-0.5, 0.5, -0.5},
		{0.5, -0.5, -0.5},
		{-0.5, -0.5, -0.5}
	};

	const static int VertexTable[6][4] = {
		{1, 2, 4, 3}, {5, 7 ,8, 6},
		{3, 7, 5, 1}, {2, 6, 8, 4},
		{1, 5, 6, 2}, {3, 4, 8, 7}
	};

	if(checkDB() == false) return;

	AllClear_();
	IFSet.SetDataBase(GetDB());

	VecArray.clear();

	for(i = 0; i < 8; i++) {
		tmpVec.set(argX * VParam[i][0],
				   argY * VParam[i][1], argZ * VParam[i][2]);
		VecArray.push_back(tmpVec);
	}

	LIndexSet.clear();
	for(i = 0; i < 6; i++) {
		LSet.clear();
		for(j = 0; j < 4; j++) LSet.push_back(VertexTable[i][j]);
		LIndexSet.push_back(LSet);
	}

	IFSet.SetIndexFaceSet(&VecArray, &LIndexSet, true);
	AllCacheMake();

	return;
}

void fk_Modify::setBlockSize(double argX, double argY, double argZ)
{
	fk_Vector		basePos, curPos, newPos;
	fk_Vertex		*curV;
	double			scaleX, scaleY, scaleZ;

	if(checkDB() == false) return;
	if(getVNum() != 8 || getLNum() != 6) return;

	curV = getNextV(nullptr);
	basePos = curV->getPosition();
	scaleX = argX/(basePos.x * 2.0);
	scaleY = argY/(basePos.y * 2.0);
	scaleZ = argZ/(basePos.z * 2.0);

	while(curV != nullptr) {
		curPos = curV->getPosition();
		newPos.set(curPos.x*scaleX, curPos.y*scaleY, curPos.z*scaleZ);
		moveVertex(curV, newPos);
		curV = getNextV(curV);
	}

	return;
}

void fk_Modify::setBlockSize(double argSize, fk_Axis argAxis)
{
	double			scaleX, scaleY, scaleZ;
	fk_Vertex		*curV;
	fk_Vector		basePos, curPos, newPos;

	if(checkDB() == false) return;

	if(getVNum() != 8 || getLNum() != 6) return;
	
	curV = getNextV(nullptr);
	basePos = curV->getPosition();
	scaleX = scaleY = scaleZ = 1.0;

	switch(argAxis) {
	  case fk_X:
		scaleX = argSize/(basePos.x * 2.0);
		break;
	  case fk_Y:
		scaleY = argSize/(basePos.y * 2.0);
		break;
	  case fk_Z:
		scaleZ = argSize/(basePos.z * 2.0);
		break;
	  default:
		break;
	}

	while(curV != nullptr) {
		curPos = curV->getPosition();
		newPos.set(curPos.x*scaleX, curPos.y*scaleY, curPos.z*scaleZ);
		moveVertex(curV, newPos);
		curV = getNextV(curV);
	}

	return;
}

void fk_Modify::setBlockScale(double argScale)
{
	setBlockScale(argScale, argScale, argScale);
}

void fk_Modify::setBlockScale(double argScale, fk_Axis argAxis)
{
	fk_Vertex		*curV;
	fk_Vector		curPos, newPos;
	double			scaleX, scaleY, scaleZ;

	if(checkDB() == false) return;

	if(getVNum() != 8 || getLNum() != 6) return;
	
	curV = getNextV(nullptr);

	scaleX = scaleY = scaleZ = 1.0;

	switch(argAxis) {
	  case fk_X:
		scaleX = argScale;
		break;
	  case fk_Y:
		scaleY = argScale;
		break;
	  case fk_Z:
		scaleZ = argScale;
		break;
	  default:
		break;
	}

	while(curV != nullptr) {
		curPos = curV->getPosition();
		newPos.set(curPos.x*scaleX, curPos.y*scaleY, curPos.z*scaleZ);
		moveVertex(curV, newPos);
		curV = getNextV(curV);
	}

	return;
}

void fk_Modify::setBlockScale(double argX, double argY, double argZ)
{
	fk_Vector		curPos, newPos;
	fk_Vertex		*curV;

	if(checkDB() == false) return;

	if(getVNum() != 8 || getLNum() != 6) return;

	curV = getNextV(nullptr);

	while(curV != nullptr) {
		curPos = curV->getPosition();
		newPos.set(curPos.x*argX, curPos.y*argY, curPos.z*argZ);
		moveVertex(curV, newPos);
		curV = getNextV(curV);
	}

	return;
}

void fk_Modify::makeCircle(int argDiv, double argRadius)
{
	fk_IFSetHandle			IFSet;
	vector<fk_Vector>		VecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	_st						i, div;
	double					theta;

	if(checkDB() == false) return;
	AllClear_();

	IFSet.SetDataBase(GetDB());

	div = static_cast<_st>(argDiv);
	VecArray.resize(div * 4 + 1);
	VecArray[0].set(0.0, 0.0, 0.0);

	for(i = 0; i < 4 * div; i++) {
		theta = (static_cast<double>(i) * FK_PI)/(static_cast<double>(div*2));
		VecArray[i+1].set(cos(theta) * argRadius, sin(theta) * argRadius, 0.0);
	}

	IFArray.clear();
	for(i = 0; i < div*4; i++) {
		IDArray.clear();
		IDArray.push_back(1);
		IDArray.push_back(int(i+2));
		if(i == div * 4 - 1) {
			IDArray.push_back(2);
		} else {
			IDArray.push_back(int(i+3));
		}
		IFArray.push_back(IDArray);
	}

	IFSet.SetIndexFaceSet(&VecArray, &IFArray, true);
	AllCacheMake();

	return;
}

void fk_Modify::setCircleDivide(int argDiv)
{
	fk_Vertex		*curV;

	if(checkDB() == false) return;
	if(getLNum() == argDiv * 4) return;

	if((curV = getNextV(getNextV(nullptr))) == nullptr) {
		return;
	}

	makeCircle(argDiv, curV->getPosition().x);

	return;
}

void fk_Modify::setCircleRadius(double argRadius)
{
	fk_Vector		basePos, curPos;
	double			scale;
	fk_Vertex		*curV;

	if(checkDB() == false) return;

	curV = getNextV(nullptr);
	curV = getNextV(curV);
	if(curV == nullptr) return;

	basePos = curV->getPosition();
	scale = argRadius/basePos.x;

	while(curV != nullptr) {
		basePos = curV->getPosition();
		curPos.set(basePos.x * scale, basePos.y * scale, 0.0);
		moveVertex(curV, curPos);
		curV = getNextV(curV);
	}

	return;
}

void fk_Modify::setCircleScale(double argScale)
{
	fk_Vector		basePos, curPos;
	fk_Vertex		*curV;

	if(checkDB() == false) return;

	if((curV = getNextV(getNextV(nullptr))) == nullptr) {
		return;
	}

	while(curV != nullptr) {
		basePos = curV->getPosition();
		curPos.set(basePos.x * argScale, basePos.y * argScale, 0.0);
		moveVertex(curV, curPos);
		curV = getNextV(curV);
	}

	return;
}

void fk_Modify::makeSphere(int argDiv, double argRadius)
{
	fk_IFSetHandle			IFSet;
	vector<fk_Vector>		VecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	int						i, j, index, index2;
	_st						ii, jj;
	vector<double>			xz_radius;
	double					theta1, theta2;

	if(checkDB() == false) return;

	AllClear_();
	IFSet.SetDataBase(GetDB());

	VecArray.resize(static_cast<_st>(argDiv*4 * (argDiv*2 - 1) + 2));
	xz_radius.resize(static_cast<_st>(argDiv*2 - 1));

	for(i = 0; i < argDiv*2 - 1; i++) {
		ii = static_cast<_st>(i);
		xz_radius[ii] = argRadius*sin(static_cast<double>(i+1)*FK_PI/(argDiv*2.0));
	}

	VecArray.front().set(0.0, argRadius, 0.0);
	VecArray.back().set(0.0, -argRadius, 0.0);
	
	for(i = 0; i < argDiv*2 - 1; i++) {
		for(j = 0; j < argDiv*4; j++) {
			index = i*argDiv*4 + j + 1;
			ii = static_cast<_st>(i);
			jj = static_cast<_st>(index);

			theta1 = static_cast<double>(j)*FK_PI/(argDiv*2.0);
			theta2 = static_cast<double>(i+1)*FK_PI/(argDiv*2.0);
			VecArray[jj].set(xz_radius[ii] * cos(theta1),
							 argRadius * cos(theta2),
							 xz_radius[ii] * sin(theta1));
		}
	}

	IFArray.clear();

	// TOP
	for(i = 0; i < argDiv*4; i++) {
		IDArray.clear();
		IDArray.push_back(1);
		if(i == argDiv*4 - 1) {
			IDArray.push_back(2);
		} else {
			IDArray.push_back(i+3);
		}
		IDArray.push_back(i+2);
		IFArray.push_back(IDArray);
	}

	// BOTTOM
	index = (argDiv*4)*(argDiv*2 - 2) + 2;
	for(i = 0; i < argDiv*4; i++) {
		IDArray.clear();
		IDArray.push_back(index + (argDiv*4));
		IDArray.push_back(index + i);
		if(i == argDiv*4 - 1) {
			IDArray.push_back(index);
		} else {
			IDArray.push_back(index + i + 1);
		}
		IFArray.push_back(IDArray);
	}

	// SIDE
	for(i = 0; i < argDiv*2 - 2; i++) {
		for(j = 0; j < argDiv*4; j++) {
			IDArray.clear();
			index = i*argDiv*4 + j + 2;
			index2 = (j == argDiv*4 - 1) ? i*argDiv*4 + 2 : index + 1;

			IDArray.push_back(index);
			IDArray.push_back(index2);
			IDArray.push_back(index2 + argDiv*4);
			IDArray.push_back(index + argDiv*4);
			IFArray.push_back(IDArray);
		}
	}

	IFSet.SetIndexFaceSet(&VecArray, &IFArray, true);
	AllCacheMake();

	return;
}

void fk_Modify::setSphereDivide(int argDiv)
{
	fk_Vertex		*curV;

	if(checkDB() == false) return;

	if((curV = getNextV(nullptr)) == nullptr) {
		return;
	}
	makeSphere(argDiv, curV->getPosition().y);
	return;
}

void fk_Modify::setSphereRadius(double argRadius)
{
	fk_Vector		basePos, curPos;
	double			scale;
	fk_Vertex		*curV;

	if(checkDB() == false) return;

	curV = getNextV(nullptr);
	if(curV == nullptr) return;

	basePos = curV->getPosition();
	scale = argRadius/basePos.y;

	while(curV != nullptr) {
		basePos = curV->getPosition();
		curPos.set(basePos.x * scale, basePos.y * scale, basePos.z * scale);
		moveVertex(curV, curPos);
		curV = getNextV(curV);
	}

	return;
}

void fk_Modify::setSphereScale(double argScale)
{
	fk_Vector		basePos, curPos;
	fk_Vertex		*curV;

	if(checkDB() == false) return;

	curV = getNextV(nullptr);
	if(curV == nullptr) return;

	while(curV != nullptr) {
		basePos = curV->getPosition();
		curPos.set(basePos.x * argScale,
				   basePos.y * argScale, basePos.z * argScale);
		moveVertex(curV, curPos);
		curV = getNextV(curV);
	}

	return;
}

void fk_Modify::makePrism(int argDiv, double argTop, double argBottom,
						  double argHeight)
{
	fk_IFSetHandle			IFSet;
	vector<fk_Vector>		VecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	int						i, v[4];
	double					theta;

	if(checkDB() == false) return;
	AllClear_();

	IFSet.SetDataBase(GetDB());

	VecArray.resize(static_cast<_st>(argDiv*2+2));
	VecArray[0].set(0.0, 0.0, 0.0);
	VecArray[static_cast<_st>(argDiv + 1)].set(0.0, 0.0, -argHeight);

	for(i = 0; i < argDiv; i++) {
		theta = (static_cast<double>(i*2) * FK_PI)/static_cast<double>(argDiv);
		VecArray[static_cast<_st>(i+1)].set(cos(theta) * argBottom,
						  sin(theta) * argBottom, 0.0);
		VecArray[static_cast<_st>(argDiv+i+2)].set(cos(theta) * argTop, 
												   sin(theta) * argTop, -argHeight);
	}

	IFArray.clear();

	for(i = 0; i < argDiv; i++) {

		// 底面 
		IDArray.clear();
		IDArray.push_back(1);
		IDArray.push_back(i+2);
		if(i == argDiv - 1) {
			IDArray.push_back(2);
		} else {
			IDArray.push_back(i+3);
		}
		IFArray.push_back(IDArray);


		// 上面 
		IDArray.clear();
		IDArray.push_back(argDiv+2);
		if(i == argDiv-1) {
			IDArray.push_back(argDiv+3);
		} else {
			IDArray.push_back(argDiv+i+4);
		}
		IDArray.push_back(argDiv+i+3);

		IFArray.push_back(IDArray);

		// 側面 
		v[0] = i + 2;
		v[1] = argDiv + i + 3;
		if(i == argDiv-1) {
			v[2] = 2;
			v[3] = argDiv + 3;
		} else {
			v[2] = i + 3;
			v[3] = argDiv + i + 4;
		}
		IDArray.clear();
		IDArray.push_back(v[0]);
		IDArray.push_back(v[1]);
		IDArray.push_back(v[2]);
		IFArray.push_back(IDArray);

		IDArray.clear();
		IDArray.push_back(v[1]);
		IDArray.push_back(v[3]);
		IDArray.push_back(v[2]);
		IFArray.push_back(IDArray);
	}

	IFSet.SetIndexFaceSet(&VecArray, &IFArray, true);
	AllCacheMake();

	return;
}

void fk_Modify::setPrismDivide(int argDiv)
{
	int			div;
	double		top, bottom, height;

	if(checkDB() == false) return;
	if((div = getVNum()/2 - 1) < 3) return;

	top = getVData(div+3)->getPosition().x;
	bottom = getVData(2)->getPosition().x;
	height = -(getVData(div+2)->getPosition().z);

	makePrism(argDiv, top, bottom, height);
	return;
}

void fk_Modify::setPrismTopRadius(double argTop)
{
	int			div;
	int			i;
	fk_Vertex	*v;
	double		theta, z;
	fk_Vector	pos;

	div = getVNum()/2 - 1;
	z = getVData(div+3)->getPosition().z;
	for(i = 0; i < div; i++) {
		v = getVData(div+i+3);
		theta = (static_cast<double>(i*2) * FK_PI)/static_cast<double>(div);
		pos.set(cos(theta) * argTop, sin(theta) * argTop, z);
		moveVertex(v, pos);
	}

	return;
}

void fk_Modify::setPrismBottomRadius(double argBottom)
{
	int			div;
	int			i;
	fk_Vertex	*v;
	double		theta;
	fk_Vector	pos;

	div = getVNum()/2 - 1;
	for(i = 0; i < div; i++) {
		v = getVData(i+2);
		theta = (static_cast<double>(i*2) * FK_PI)/static_cast<double>(div);
		pos.set(cos(theta) * argBottom, sin(theta) * argBottom, 0.0);
		moveVertex(v, pos);
	}

	return;
}

void fk_Modify::setPrismHeight(double argHeight)
{
	int			div;
	int			i;
	fk_Vertex	*v;
	fk_Vector	pos;

	div = getVNum()/2 - 1;
	for(i = 0; i <= div; i++) {
		v = getVData(div+i+2);
		pos.set(v->getPosition().x, v->getPosition().y, -argHeight);
		moveVertex(v, pos);
	}

	return;
}

void fk_Modify::makeCone(int argDiv, double argRadius, double argHeight)
{
	fk_IFSetHandle			IFSet;
	vector<fk_Vector>		VecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	int						i;
	double					theta;

	if(checkDB() == false) return;
	AllClear_();

	IFSet.SetDataBase(GetDB());
	
	VecArray.resize(static_cast<_st>(argDiv+2));
	VecArray[0].set(0.0, 0.0, 0.0);
	VecArray[1].set(0.0, 0.0, -argHeight);

	for(i = 0; i < argDiv; i++) {
		theta = (static_cast<double>(i*2) * FK_PI)/static_cast<double>(argDiv);
		VecArray[static_cast<_st>(i+2)].set(cos(theta) * argRadius, sin(theta) * argRadius, 0.0);
	}

	IFArray.clear();

	for(i = 0; i < argDiv; i++) {
		// 底面 
		IDArray.clear();
		IDArray.push_back(1);
		IDArray.push_back(i+3);
		if(i == argDiv - 1) {
			IDArray.push_back(3);
		} else {
			IDArray.push_back(i+4);
		}
		IFArray.push_back(IDArray);

		// 側面 
		IDArray.clear();
		IDArray.push_back(2);
		if(i == argDiv - 1) {
			IDArray.push_back(3);
		} else {
			IDArray.push_back(i+4);
		}
		IDArray.push_back(i+3);
		IFArray.push_back(IDArray);
	}	

	IFSet.SetIndexFaceSet(&VecArray, &IFArray, true);
	AllCacheMake();

	return;
}

void fk_Modify::setConeDivide(int argDiv)
{
	double	rad, height;

	if(checkDB() == false) return;
	if(getVNum() < 5) return;

	rad = getVData(3)->getPosition().x;
	height = -(getVData(2)->getPosition().z);

	makeCone(argDiv, rad, height);
}

void fk_Modify::setConeRadius(double argRadius)
{
	int			div;
	int			i;
	fk_Vertex	*v;
	double		theta;
	fk_Vector	pos;

	div = getVNum()-2;
	for(i = 0; i < div; i++) {
		v = getVData(i+3);
		theta = (static_cast<double>(i*2) * FK_PI)/static_cast<double>(div);
		pos.set(cos(theta) * argRadius, sin(theta) * argRadius, 0.0);
		moveVertex(v, pos);
	}

	return;
}

void fk_Modify::setConeHeight(double argHeight)
{
	fk_Vector		pos(0.0, 0.0, -argHeight);

	moveVertex(getVData(2), pos);

	return;
}

bool fk_Modify::moveVPosition(int argID, fk_Vector argPos, int argOrder)
{
	if(checkDB() == false) return false;

	return moveVertex(getVData(argID+1-argOrder), argPos);
}

bool fk_Modify::moveVPosition(int argID, double argX, double argY, double argZ,
							  int argOrder)
{
	fk_Vector		pos(argX, argY, argZ);

	if(checkDB() == false) return false;

	return moveVertex(getVData(argID+1-argOrder), pos);
}

bool fk_Modify::moveVPosition(int argID, double *argPos, int argOrder)
{
	fk_Vector		pos(argPos[0], argPos[1], argPos[2]);

	if(checkDB() == false) return false;

	return moveVertex(getVData(argID+1-argOrder), pos);
}

void fk_Modify::subdivShape(int argCount)
{
	fk_SubDivision		sb;

	sb.calcCatmull(argCount, this);
	return;
}
