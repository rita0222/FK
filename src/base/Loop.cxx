/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#include <FK/Loop.h>
#include <FK/Half.h>
#include <FK/Vertex.h>
#include <FK/Math.h>
#include <FK/Error.H>
#include <list>
#include <algorithm>

using namespace std;

const double TESS_DELTA = 0.0001;

static bool IsInner(const fk_Vector &a, const fk_Vector &b,
					const fk_Vector &c, const fk_Vector &n)
{
	fk_Vector		tmpVec1, tmpVec2, tmpVec3;
	
	tmpVec1 = a ^ b;
	tmpVec2 = a ^ c;
	tmpVec3 = b ^ c;

	if(tmpVec1 * n > 0.0) {
		if(tmpVec2 * n > 0.0 && tmpVec3 * n > 0.0) return true;
	} else {
		if(tmpVec2 * n > 0.0 || tmpVec3 * n > 0.0) return true;
	}
	return false;
}

static bool IsCrossLine(const fk_Vector &argA, const fk_Vector &argB,
						const fk_Vector &argC, const fk_Vector &argD)
{
	if(fk_Math::isCrossLineSegment(argA, argB, argC, argD, false) == true) {
		return true;
	}

	if(fk_Math::isOnLineSegment(argA, argB, argC, false) == true) {
		return true;
	}

	if(fk_Math::isOnLineSegment(argA, argB, argD, false) == true) {
		return true;
	}

	if(fk_Math::isOnLineSegment(argC, argD, argA, false) == true) {
		return true;
	}

	if(fk_Math::isOnLineSegment(argC, argD, argB, false) == true) {
		return true;
	}

	return false;
}

static bool IsCrossPolygon(vector<fk_Vertex *> *argVer, list<int> *argID,
						   const fk_Vector &argV1, const fk_Vector &argV2)
{
	int						id1, id2;
	list<int>::iterator		ite;
	fk_Vector				tmpVec1, tmpVec2;

	id1 = id2 = -1;
	for(ite = argID->begin(); ite != argID->end(); ++ite) {
		id2 = id1;
		id1 = (*ite);
		if(id2 != -1) {
			tmpVec1 = argVer->at(static_cast<_st>(id1))->getPosition();
			tmpVec2 = argVer->at(static_cast<_st>(id2))->getPosition();

			if(IsCrossLine(tmpVec1, tmpVec2, argV1, argV2) == true) {
				return true;
			}
		}
	}

	tmpVec1 = argVer->at(static_cast<_st>(argID->back()))->getPosition();
	tmpVec2 = argVer->at(static_cast<_st>(argID->front()))->getPosition();

	return(IsCrossLine(tmpVec1, tmpVec2, argV1, argV2));
}

static int GetPrevID(list<int> *argList, int argID)
{
	list<int>::iterator		ite;

	ite = find(argList->begin(), argList->end(), argID);
	if(ite == argList->end()) return -1;

	if(ite == argList->begin()) return argList->back();
	--ite;
	return (*ite);
}

static int GetNextID(list<int> *argList, int argID)
{
	list<int>::iterator		ite;

	ite = find(argList->begin(), argList->end(), argID);
	if(ite == argList->end()) return -1;

	++ite;
	if(ite == argList->end()) return argList->front();
	return (*ite);
}

fk_Loop::fk_Loop(int argID)
{
	Init(argID);

	return;
}

fk_Loop::~fk_Loop()
{
	return;
}

void fk_Loop::Init(int argID)
{
	InitTopology(argID, FK_LOOP_TYPE);
	oneHalf = NULL;
	norm.set(0.0, 0.0, 0.0);
	normFlag = errorFlag = tesselateFlag = false;
	tesselateMode = true;
	surf = NULL;
	tesselateIndex.clear();
	tesselateVertex.clear();
	ifsID = -1;

	return;
}

fk_Half * fk_Loop::getOneHalf(void) const
{
	return oneHalf;
}

fk_Half * fk_Loop::SetOneHalf(fk_Half *argHf)
{
	fk_Half *retHf = oneHalf;

	oneHalf = argHf;
	return retHf;
}

bool fk_Loop::SetNormal(void)
{
	fk_Half				*curH;
	vector<fk_Vector>	posArray, normArray;
	_st					i;
	fk_Vector			sumNorm;

	posArray.clear();
	normArray.clear();
	if(oneHalf == NULL) return false;
	curH = oneHalf;
	
	do {
		if(curH == NULL) {
			posArray.clear();
			return false;
		}

		posArray.push_back(curH->getVertex()->getPosition());
		curH = curH->getNextHalf();
	} while(curH != oneHalf);

	posArray.push_back(posArray[0]);
	posArray.push_back(posArray[1]);

	sumNorm.init();
	for(i = 0; i < posArray.size() - 2; i++) {
		normArray.push_back((posArray[i+1] - posArray[i]) ^
							(posArray[i+2] - posArray[i+1]));
		sumNorm += normArray[i];
	}

	for(i = 0; i < normArray.size(); i++) {
		if(sumNorm * normArray[i] < 0.0) normArray[i] = -normArray[i];
	}

	sumNorm.init();
	for(i = 0; i < normArray.size(); i++) {
		sumNorm += normArray[i];
	}

	if(sumNorm.normalize() == false) {
		fk_PutError("fk_Loop", "SetNormal", 1,
					"Normal Undefined Error");
		return false;
	}

	norm = sumNorm;
	return true;
}

fk_Vector * fk_Loop::getNormal(void)
{
	if(errorFlag == true) return NULL;

	if(normFlag == false) {
		if(SetNormal() == false) {
			fk_PutError("fk_Loop", "getNormal", 1,
						"Normal Vector Error.");
			errorFlag = true;
			return NULL;
		}
	}

	normFlag = true;
	return &norm;
}

int fk_Loop::getVNum(void) const
{
	int			retNum = 1;
	fk_Half		*countH = NULL;

	if(errorFlag == true) return -1;
	if(oneHalf == NULL) return -1;

	for(countH = oneHalf->getNextHalf();
		countH != oneHalf;
		countH = countH->getNextHalf()) {
		retNum++;
	}

	return retNum;
}

void fk_Loop::ModifyLoop(void)
{
	normFlag = false;
	tesselateFlag = false;
	return;
}


void fk_Loop::Print(void) const
{
	fk_Printf("Loop[%d] = {", getID());

	if(oneHalf != NULL) {
		fk_Printf("\t1H = %d", oneHalf->getID());
	} else {
		fk_Printf("\t1H = NULL");
	}

	fk_PutError("}");

	return;
}

bool fk_Loop::Check(void) const
{
	fk_Half	*curH, *prevH;
	string	outStr;


	if(oneHalf->getParentLoop() != this) {
		outStr = fk_StrPrintf("Loop[%d] ... Half[%d] ERROR",
							  getID(), oneHalf->getID());
		fk_PutError("fk_Loop", "Check", 1, outStr);
		return false;
	}

	curH = oneHalf->getNextHalf();
	prevH = oneHalf;

	if(curH->getPrevHalf() != prevH) {
		outStr = fk_StrPrintf("Loop[%d] ... Half[%d] ERROR",
							  getID(), curH->getID());
		fk_PutError("fk_Loop", "Check", 2, outStr);
		return false;
	}

	while(curH != oneHalf) {

		if(curH->getParentLoop() != this) {
			outStr = fk_StrPrintf("Loop[%d] ... Half[%d] ERROR",
								  getID(), curH->getID());
			fk_PutError("fk_Loop", "Check", 3, outStr);
			return false;
		}

		prevH = curH;
		curH = curH->getNextHalf();

		if(curH->getPrevHalf() != prevH) {
			outStr = fk_StrPrintf("Loop[%d] ... Half[%d] ERROR",
								  getID(), curH->getID());
			fk_PutError("fk_Loop", "Check", 4, outStr);
			return false;
		}
	}

	return true;
}

bool fk_Loop::Compare(fk_Loop *argL) const
{
	if(argL == NULL) return false;
	if(argL == this) return true;
	if(getID() != argL->getID()) return false;
	if(getID() == FK_UNDEFINED) return true;

	if(oneHalf == NULL && argL->oneHalf == NULL) {
		return true;
	} else if(oneHalf == NULL || argL->oneHalf == NULL) {
		return false;
	}

	if(oneHalf->getID() == argL->oneHalf->getID()) return true;
	return false;
}

void fk_Loop::setSurfGeometry(fk_Surface *argSurf)
{
	surf = argSurf;
	return;
}

fk_Surface * fk_Loop::getSurfGeometry(void)
{
	return surf;
}

bool fk_Loop::isTesselated(void)
{
	if(tesselateMode == false) return false;
	if(tesselateFlag == false) {
		MakeTesselateData();
	}

	if(tesselateVertex.empty() == true) return false;
	return true;
}

void fk_Loop::setTesselateMode(bool argMode)
{
	tesselateMode = argMode;
	return;
}

bool fk_Loop::getTesselateMode(void)
{
	return tesselateMode;
}

void fk_Loop::MakeTesselateData(void)
{
	fk_Half				*curH;
	int					i;
	int					curID, prevID, nextID, prev2ID;
	list<int>			loopVID;
	int					loopCount;
	fk_Vector			tmpVec[5], tmpPos[2], curV, prevV, prev2V, nextV;

	if(tesselateMode == false) return;
	if(getNormal() == NULL) return;

	tesselateIndex.clear();
	tesselateVertex.clear();

	if(oneHalf == NULL) return;
	curH = oneHalf;
	do {
		if(curH == NULL) {
			tesselateIndex.clear();
			tesselateVertex.clear();
			return;
		}

		tesselateVertex.push_back(curH->getVertex());
		curH = curH->getNextHalf();
	} while(curH != oneHalf);

	if(tesselateVertex.size() <= 2) {
		tesselateIndex.clear();
		tesselateVertex.clear();
		return;
	}

	for(i = 0; i < static_cast<int>(tesselateVertex.size()); i++) {
		loopVID.push_back(i);
	}

	loopCount = 0;

	curID = 0;
	while(loopVID.size() > 3) {
		loopCount++;
		prevID = GetPrevID(&loopVID, curID);
		nextID = GetNextID(&loopVID, curID);
		prev2ID = GetPrevID(&loopVID, prevID);

		curV = tesselateVertex[static_cast<_st>(curID)]->getPosition();
		prevV = tesselateVertex[static_cast<_st>(prevID)]->getPosition();
		prev2V = tesselateVertex[static_cast<_st>(prev2ID)]->getPosition();
		nextV = tesselateVertex[static_cast<_st>(nextID)]->getPosition();

		tmpVec[0] = curV - prevV;
		tmpVec[1] = nextV - curV;
		tmpVec[2] = prevV - prev2V;
		tmpVec[3] = nextV - prevV;
		tmpVec[4] = tmpVec[0] ^ tmpVec[1];

		if(norm * tmpVec[4] > FK_EPS) {
			tmpPos[0] = prevV + tmpVec[3] * TESS_DELTA;
			tmpPos[1] = nextV - tmpVec[3] * TESS_DELTA;

			if(IsCrossPolygon(&tesselateVertex, &loopVID,
							  tmpPos[0], tmpPos[1]) == false) {
				if(IsInner(tmpVec[2], tmpVec[0], tmpVec[3], norm) == true) {
					tesselateIndex.push_back(prevID);
					tesselateIndex.push_back(curID);
					tesselateIndex.push_back(nextID);
					loopVID.erase(find(loopVID.begin(), loopVID.end(), curID));
					loopCount = 0;
				}
			}
		}

		if(loopCount >= static_cast<int>(loopVID.size())) {
			fk_PutError("fk_Loop", "MakeTesselateData", 1,
						"Tesselate Error");
			tesselateMode = false;
			tesselateIndex.clear();
			tesselateVertex.clear();
			return;
		}

		curID = nextID;
	}

	prevID = GetPrevID(&loopVID, curID);
	nextID = GetNextID(&loopVID, curID);
	tesselateIndex.push_back(prevID);
	tesselateIndex.push_back(curID);
	tesselateIndex.push_back(nextID);

	tesselateFlag = true;
	return;
}

vector<fk_Vertex *> * fk_Loop::GetTesselateVertex(void)
{
	return &tesselateVertex;
}

vector<int> * fk_Loop::GetTesselateIndex(void)
{
	return &tesselateIndex;
}

void fk_Loop::SetIFSID(int argID)
{
	ifsID = argID;
	return;
}

int fk_Loop::GetIFSID(void)
{
	return ifsID;
}

fk_LoopCrossStatus fk_Loop::IsCross(const fk_Vector &argS,
									const fk_Vector &argE,
									fk_Vector *retR)
{
	fk_Vector		V[3], R;
	fk_Half			*curH;


	if(getVNum() != 3) return FK_LOOP_ERROR_CROSS;
	curH = oneHalf;
	for(int i = 0; i < 3; i++) {
		if(curH == NULL) return FK_LOOP_ERROR_CROSS;
		V[i] = curH->getVertex()->getPosition();
		curH = curH->getNextHalf();
	}

	if(fk_Math::calcCrossLineAndTri(argS, argE,
									V[0], V[1], V[2], &R) == false) {
		return FK_LOOP_NO_CROSS;
	}

	if(retR != NULL) retR->set(R.x, R.y, R.z);

	if(R.x <= FK_EPS) return FK_LOOP_ONEDGE_CROSS;
	if(R.y <= FK_EPS) return FK_LOOP_ONEDGE_CROSS;
	if(R.x + R.y >= 1.0 - FK_EPS) return FK_LOOP_ONEDGE_CROSS;
	if(R.z <= FK_EPS || R.z >= 1.0 - FK_EPS) return FK_LOOP_ONFACE_CROSS;

	if(*getNormal() * (argE - argS) < 0.0) return FK_LOOP_FRONT_CROSS;
	return FK_LOOP_BACK_CROSS;
}
