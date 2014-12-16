﻿/****************************************************************************
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
#include <algorithm>
#include <FK/IndexFace.h>
#include <FK/Solid.h>
#include <FK/D3DXAnimation.H>
#include <FK/D3DXParser.H>
#include <FK/SMFParser.H>
#include <FK/STLParser.H>
#include <FK/HRCParser.H>
#include <FK/RDSParser.H>
#include <FK/DXFParser.H>
#include <FK/VRMLParser.H>
#include <FK/MQOParser.H>
#include <FK/VRMLOut.H>
#include <FK/STLOut.H>
#include <FK/DXFOut.H>
#include <FK/MQOOut.H>
#include <FK/IFSetHandle.H>
#include <FK/Error.H>
#include <sstream>

using namespace std;

fk_IndexFaceSet::fk_IndexFaceSet(void)
{
	SetObjectType(FK_INDEXFACESET);
	SetPaletteData(&localPalette);

	posSize = -1;
	faceSize = -1;
	type = FK_IF_NONE;
	modifyFlg = true;
	colorFlg = false;
	anim = NULL;
	cloneFlg = false;
	orgIFS = NULL;

	pos.clear();
	timeOrgPos.clear();
	vNorm.clear();
	pNorm.clear();
	ifs.clear();
	edgeSet.clear();
	loopStack.clear();
	vNormFlg.clear();
	pNormFlg.clear();
	modifyList.clear();
	colorID.clear();
	cloneList.clear();

	return;
}

fk_IndexFaceSet::~fk_IndexFaceSet()
{
	if(cloneFlg == true) {
		orgIFS->cloneList.remove(this);
	} else {
		delete anim;
	}

	DeleteCloneLink(this);
	return;
}

void fk_IndexFaceSet::DeleteCloneLink(fk_IndexFaceSet *argIFS)
{
	list<fk_IndexFaceSet *>::iterator	ite;

	argIFS->anim = NULL;
	argIFS->cloneFlg = false;
	argIFS->orgIFS = NULL;

	for(ite = argIFS->cloneList.begin();
		ite != argIFS->cloneList.end(); ++ite) {

		DeleteCloneLink(*ite);
	}
	argIFS->cloneList.clear();
	return;
}

void fk_IndexFaceSet::Init(void)
{
	return;
}

bool fk_IndexFaceSet::Init(int argTNum, int argPNum, int argVNum)
{
	_st		i;

	// 面数が不適切
	if(argTNum < 1) return false;

	// 角数が不適切
	if(argPNum != 3 && argPNum != 4) return false;

	// 頂点数が不適切
	if(argVNum < 3) return false;

	// 各データを一旦解放
	pos.clear();
	vNorm.clear();
	pNorm.clear();
	ifs.clear();
	edgeSet.clear();

	loopStack.clear();
	vNormFlg.clear();
	pNormFlg.clear();
	colorID.clear();

	pos.resize(static_cast<_st>(argVNum));
	ifs.resize(static_cast<_st>(argTNum*argPNum));

	// メッシュタイプの設定
	switch(argPNum) {
	  case 3:
		type = FK_IF_TRIANGLES;
		break;
	  case 4:
		type = FK_IF_QUADS;
		break;
	  default:
		return false;
	}

	posSize = argVNum;
	faceSize = argTNum;
	colorID.resize(static_cast<_st>(faceSize));
	for(i = 0; i < static_cast<_st>(faceSize); i++) {
		colorID[i] = FK_UNDEFINED;
	}

	colorFlg = false;

	return true;
}

bool fk_IndexFaceSet::MakeMesh(vector<fk_Vector> *vData,
							   vector< vector<int> > *lIndex,
							   vector<int> *mateIDSet, bool)
{
	_st				i, j, pNum;
	vector<int>		tmpP;

	if(vData == NULL || lIndex == NULL) {
		return false;
	}

	if(lIndex->size() == 0) return true;

	pNum = (*lIndex)[0].size();

	// 三角形か四角形でない場合はエラー
	if(pNum != 3 && pNum != 4) return false;

	// 全ての面が同角数でなければエラー
	for(i = 1; i < lIndex->size(); i++) {
		if((*lIndex)[i].size() != pNum) {
			return false;
		}
	}

	// データ領域の確保
	if(Init(static_cast<int>(lIndex->size()), static_cast<int>(pNum),
			static_cast<int>(vData->size())) == false) return false;

	// 頂点データのコピー
	for(i = 0; i < vData->size(); i++) {
		pos[i] = (*vData)[i];
	}

	// 面データのコピー
	for(i = 0; i < lIndex->size(); i++) {
		tmpP = (*lIndex)[i];
		for(j = 0; j < pNum; j++) {
			ifs[i*pNum+j] = tmpP[j] - 1;
		}
	}

	MakeEdgeSet();
	ModifyVNorm();

	if(mateIDSet == NULL) return true;
	if(mateIDSet->size() != lIndex->size()) return true;

	for(i = 0; i < mateIDSet->size(); i++) {
		colorID[i] = (*mateIDSet)[i];
	}
	colorFlg = true;

	return true;
}

void fk_IndexFaceSet::makeIFSet(int argTNum, int argPNum, int *argIF,
								int argVNum, fk_Vector *argPos, int argOrder)
{
	_st			i;

	if(Init(argTNum, argPNum, argVNum) == false) return;

	// 頂点データのコピー
	for(i = 0; i < static_cast<_st>(argVNum); i++) {
		pos[i] = argPos[i];
	}

	// 面データのコピー
	for(i = 0; i < static_cast<_st>(argPNum*argTNum); i++) {
		ifs[i] = argIF[i] - argOrder;
	}

	MakeEdgeSet();

	return;
}

void fk_IndexFaceSet::InitPNorm(void)
{
	int			i;

	if(faceSize < 0) return;

	pNorm.resize(static_cast<_st>(faceSize));
	pNormFlg.resize(static_cast<_st>(faceSize));
	ClearPFlg();

	for(i = 0; i < faceSize; i++) {
		MakePNorm(i);
	}

	modifyFlg = false;
	return;
}

void fk_IndexFaceSet::ModifyPNorm(void)
{
	_st		i, j, vID;

	// 形状が定義されていない場合
	if(faceSize < 0) return;

	// まだ面法線配列が生成されていない場合
	if(pNorm.empty() == true) {
		InitPNorm();
		return;
	}

	// 変形がなかった場合は終了
	if(modifyFlg == false) return;

	// 頂点の面接続テーブルが生成されていない場合, テーブルを生成する。
	if(loopStack.empty() == true) {
		MakeLoopTable();
	}

	// modifyList に従って処理
	for(i = 0; i < modifyList.size(); i++) {
		vID = static_cast<_st>(modifyList[i]);
		for(j = 0; j < loopStack[vID].size(); j++) {
			MakePNorm(loopStack[vID][j]);
		}
	}

	ClearPFlg();
	modifyList.clear();
	modifyFlg = false;
	return;
}

void fk_IndexFaceSet::MakePNorm(int argID)
{
	_st		id = static_cast<_st>(argID);
	_st		j;

	if(pNormFlg[id] == static_cast<char>(false)) return;

	switch(type) {
	  case FK_IF_TRIANGLES:
		pNorm[id] = CalcTriNorm(&ifs[id*3]);
		pNormFlg[id] = static_cast<char>(false);

		if(vNorm.empty() == false) {
			for(j = id*3; j < id*3 + 3; j++) {
				vNormFlg[static_cast<_st>(ifs[j])] = static_cast<char>(true);
			}
		}
		break;

	  case FK_IF_QUADS:
		pNorm[id] = CalcPolyNorm(4, &ifs[id*4]);
		pNormFlg[id] = static_cast<char>(false);

		if(vNorm.empty() == false) {
			for(j = id*4; j < id*4 + 4; j++) {
				vNormFlg[static_cast<_st>(ifs[j])] = static_cast<char>(true);
			}
		}
		break;

	  default:
		break;
	}

	return;
}

void fk_IndexFaceSet::ClearPFlg(void)
{
	_st		i;

	for(i = 0; i < static_cast<_st>(faceSize); i++) {
		pNormFlg[i] = static_cast<char>(true);
	}
	return;
}

void fk_IndexFaceSet::InitVNorm(void)
{
	vector<fk_Vector>	normArray;
	fk_Vector			tmpVec;
	_st					vNum;
	_st					i, j;

	// 形状が定義されていない場合
	if(faceSize < 0) return;

	switch(type) {
	  case FK_IF_TRIANGLES:
		vNum = 3;
		break;
	  case FK_IF_QUADS:
		vNum = 4;
		break;
	  default:
		return;
	}

	if(pNorm.empty() == true) InitPNorm();

	vNorm.resize(static_cast<_st>(posSize));
	vNormFlg.resize(static_cast<_st>(posSize));

	normArray.resize(static_cast<_st>(posSize));
	for(i = 0; i < static_cast<_st>(posSize); i++) normArray[i].init();

	for(i = 0; i < static_cast<_st>(faceSize); i++) {
		for(j = 0; j < vNum; j++) {
			tmpVec = pNorm[i];
			normArray[static_cast<_st>(ifs[i*vNum+j])] += tmpVec;
		}
	}

	for(i = 0; i < static_cast<_st>(posSize); i++) {
		normArray[i].normalize();
		vNorm[i] = normArray[i];
	}

	ClearVFlg();
	return;
}

void fk_IndexFaceSet::ModifyVNorm(void)
{
	fk_Vector		norm, tmpV;
	_st				i, j, loopID;

	// 形状が定義されていない場合
	if(faceSize < 0) return;

	// まだ頂点法線配列が生成されていない場合
	if(vNorm.empty() == true) {
		InitVNorm();
		return;
	}

	// 変形がなかった場合は終了
	if(modifyFlg == false) return;

	// 面法線情報を再計算
	ModifyPNorm();

	switch(type) {
	  case FK_IF_TRIANGLES:
		break;
	  case FK_IF_QUADS:
		break;
	  default:
		return;
	}

	for(i = 0; i < static_cast<_st>(posSize); i++) {
		if(vNormFlg[i] == static_cast<char>(true)) {
			norm.init();
			for(j = 0; j < loopStack[i].size(); j++) {
				loopID = static_cast<_st>(loopStack[i][j]);
				tmpV = pNorm[loopID];
				norm += tmpV;
			}
			norm.normalize();
			vNorm[i] = norm;
			vNormFlg[i] = static_cast<char>(false);
		}
	}

	return;
}

void fk_IndexFaceSet::ClearVFlg(void)
{
	_st		i;

	for(i = 0; i < static_cast<_st>(posSize); i++) {
		vNormFlg[i] = static_cast<char>(false);
	}
	return;
}

fk_Vector fk_IndexFaceSet::CalcTriNorm(int *argIF)
{
	_st			i;
	fk_Vector	retNorm;
	fk_Vector	triV[3];

	for(i = 0; i < 3; i++) {
		triV[i] = pos[static_cast<_st>(argIF[i])];
	}

	retNorm = (triV[1] - triV[0]) ^ (triV[2] - triV[1]);
	retNorm.normalize();

	return retNorm;
}

fk_Vector fk_IndexFaceSet::CalcPolyNorm(int argNum, int *argIF)
{
	vector<fk_Vector>	posArray, normArray;
	_st					i;
	fk_Vector			tmpVec, sumNorm;

	posArray.clear();
	normArray.clear();

	if(argNum < 4) return sumNorm;
	for(i = 0; i < static_cast<_st>(argNum); i++) {
		tmpVec = pos[static_cast<_st>(argIF[i])];
		posArray.push_back(tmpVec);
	}

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

	sumNorm.normalize();
	return sumNorm;
}

void fk_IndexFaceSet::MakeLoopTable(void)
{
	_st		i, j, vNum, vID;

	switch(type) {
	  case FK_IF_TRIANGLES:
		vNum = 3;
		break;
	  case FK_IF_QUADS:
		vNum = 4;
		break;
	  default:
		return;
	}

	loopStack.clear();
	loopStack.resize(static_cast<_st>(posSize));

	for(i = 0; i < static_cast<_st>(faceSize); i++) {
		for(j = 0; j < vNum; j++) {
			vID = static_cast<_st>(ifs[i*vNum + j]);
			loopStack[vID].push_back(static_cast<int>(i));
		}
	}

	return;
}

void fk_IndexFaceSet::MakeEdgeSet(void)
{
	vector< vector<int> >	edgeTable;
	_st						i, j, pSize;
	_st						tmpV1, tmpV2, v1, v2;

	switch(type) {
	  case FK_IF_TRIANGLES:
		pSize = 3;
		break;
	  case FK_IF_QUADS:
		pSize = 4;
		break;
	  default:
		return;
	}

	for(i = 0; i < static_cast<_st>(faceSize); i++) {
		for(j = 0; j < pSize; j++) {
			tmpV1 = static_cast<_st>(ifs[i*pSize+j]);
			if(j == pSize-1) {
				tmpV2 = static_cast<_st>(ifs[i*pSize]);
			} else {
				tmpV2 = static_cast<_st>(ifs[i*pSize+j+1]);
			}

			if(tmpV1 < tmpV2) {
				v1 = tmpV1; v2 = tmpV2;
			} else {
				v1 = tmpV2; v2 = tmpV1;
			}

			if(edgeTable.size() <= v1) edgeTable.resize(v1+1);

			if(find(edgeTable[v1].begin(),
					edgeTable[v1].end(), v2) == edgeTable[v1].end()) {
				edgeTable[v1].push_back(static_cast<int>(v2));
			}
		}
	}

	for(i = 0; i < edgeTable.size(); i++) {
		for(j = 0; j < edgeTable[i].size(); j++) {
			edgeSet.push_back(static_cast<int>(i));
			edgeSet.push_back(edgeTable[i][j]);
		}
	}

	return;
}



int fk_IndexFaceSet::getPosSize(void)
{
	if(posSize < 0) return 0;
	return posSize;
}

int fk_IndexFaceSet::getFaceSize(void)
{
	if(faceSize < 0) return 0;
	return faceSize;
}

fk_Vector fk_IndexFaceSet::getPosVec(int argID)
{
	fk_Vector		retVec(0.0, 0.0, 0.0);

	if(argID < 0 || argID >= posSize) return retVec;
	retVec = pos[static_cast<_st>(argID)];
	return retVec;
}

vector<int> fk_IndexFaceSet::getFaceData(int argID)
{
	vector<int>		retIF;
	_st				pNum, i, id;

	if(argID < 0 || argID >= faceSize) return retIF;
	id = static_cast<_st>(argID);

	switch(type) {
	  case FK_IF_TRIANGLES:
		pNum = 3;
		break;
	  case FK_IF_QUADS:
		pNum = 4;
		break;
	  default:
		return retIF;
	}

	for(i = id*pNum; i < (id+1)*pNum; i++) {
		retIF.push_back(ifs[i]);
	}

	return retIF;
}

int fk_IndexFaceSet::getFaceData(int argFID, int argVID)
{
	int			pNum;

	if(argFID < 0 || argFID >= faceSize) return -1;

	switch(type) {
	  case FK_IF_TRIANGLES:
		pNum = 3;
		break;
	  case FK_IF_QUADS:
		pNum = 4;
		break;
	  default:
		return -1;
	}

	if(argVID < 0 || argVID >= pNum) return -1;

	return ifs[static_cast<_st>(argFID * pNum + argVID)];
}


fk_IFType fk_IndexFaceSet::getFaceType(void)
{
	return type;
}

bool fk_IndexFaceSet::moveVPosition(int argID,
									const fk_Vector &argPos, int argOrder)
{
	int		trueID = argID - argOrder;

	if(trueID < 0 || trueID >= posSize) return false;

	pos[static_cast<_st>(trueID)] = argPos;

	modifyFlg = true;

	if(find(modifyList.begin(),
			modifyList.end(), trueID) == modifyList.end()) {
		modifyList.push_back(trueID);
	}

	return true;
}

bool fk_IndexFaceSet::moveVPosition(int argID,
									double argX, double argY, double argZ,
									int argOrder)
{
	int		trueID = argID - argOrder;
	_st		id;

	if(trueID < 0 || trueID >= posSize) return false;
	id = static_cast<_st>(trueID);

	pos[id].x = float(argX);
	pos[id].y = float(argY);
	pos[id].z = float(argZ);
	modifyFlg = true;
	if(find(modifyList.begin(),
			modifyList.end(), trueID) == modifyList.end()) {
		modifyList.push_back(trueID);
	}

	return true;
}

bool fk_IndexFaceSet::moveVPosition(int argID, double *argPos, int argOrder)
{
	int		trueID = argID - argOrder;
	_st		id;

	if(trueID < 0 || trueID >= posSize) return false;
	id = static_cast<_st>(trueID);

	pos[id].x = float(argPos[0]);
	pos[id].y = float(argPos[1]);
	pos[id].z = float(argPos[2]);

	modifyFlg = true;
	modifyList.push_back(trueID);

	if(find(modifyList.begin(),
			modifyList.end(), trueID) == modifyList.end()) {
		modifyList.push_back(trueID);
	}

	return true;
}

fk_Vector fk_IndexFaceSet::getPNorm(int argPID, int argOrder)
{
	int			trueID = argPID - argOrder;

	if(trueID < 0 || trueID >= static_cast<int>(pNorm.size())) {
		return fk_Vector(0.0, 0.0, 0.0);
	}

	return fk_Vector(pNorm[static_cast<_st>(trueID)]);
}

bool fk_IndexFaceSet::setPNorm(int argPID,
							   const fk_Vector &argVec, int argOrder)
{
	int			trueID = argPID - argOrder;

	if(trueID < 0 || trueID >= static_cast<int>(pNorm.size())) return false;
	pNorm[static_cast<_st>(trueID)] = argVec;
	return true;
}

fk_Vector fk_IndexFaceSet::getVNorm(int argVID, int argOrder)
{
	int			trueID = argVID - argOrder;

	if(trueID < 0 || trueID >= int(vNorm.size())) {
		return fk_Vector(0.0, 0.0, 0.0);
	}
	return fk_Vector(vNorm[static_cast<_st>(trueID)]);
}

bool fk_IndexFaceSet::setVNorm(int argVID,
							   const fk_Vector &argVec, int argOrder)
{
	int			trueID = argVID - argOrder;

	if(trueID < 0 || trueID >= static_cast<int>(vNorm.size())) return false;
	vNorm[static_cast<_st>(trueID)] = argVec;
	return true;
}

bool fk_IndexFaceSet::setElemMaterialID(int argIndex, int argColor)
{
	_st		index = static_cast<_st>(argIndex);

	if(argIndex < 0 || index >= colorID.size()) {
		return false;
	}

	colorID[index] = argColor;
	colorFlg = true;

	return true;
}

int fk_IndexFaceSet::getElemMaterialID(int argIndex)
{
	_st		index = static_cast<_st>(argIndex);

	if(argIndex < 0 || index >= colorID.size()) {
		return -1;
	}

	return colorID[index];
}

void fk_IndexFaceSet::flush(void)
{
	if(pNorm.empty() == true) {
		ModifyPNorm();
	} else {
		ModifyVNorm();
	}
	return;
}

bool fk_IndexFaceSet::readSMFFile(string argFileName)
{
	fk_SMFParser	*smfParser = new fk_SMFParser();
	bool			retFlg;

	smfParser->SetMeshData(this);
	retFlg = smfParser->ReadSMFFile(argFileName);
	delete smfParser;
	return retFlg;
}

bool fk_IndexFaceSet::readSTLFile(string argFileName,
								  bool argSolidFlag, double argEPS)
{
	fk_STLParser	*stlParser = new fk_STLParser();
	bool			retFlg;

	stlParser->SetMeshData(this);
	retFlg = stlParser->ReadSTLFile(argFileName, argSolidFlag, argEPS);
	delete stlParser;
	return retFlg;
}

bool fk_IndexFaceSet::readHRCFile(string argFileName)
{
	fk_HRCParser	*hrcParser = new fk_HRCParser();
	bool			retFlg;

	hrcParser->SetMeshData(this);
	retFlg = hrcParser->ReadHRCFile(argFileName);
	delete hrcParser;
	return retFlg;
}

bool fk_IndexFaceSet::readRDSFile(string argFileName, bool argSolidFlg)
{
	fk_RDSParser	*rdsParser = new fk_RDSParser();
	bool			retFlg;

	rdsParser->SetMeshData(this);
	retFlg = rdsParser->ReadRDSFile(argFileName, argSolidFlg);
	delete rdsParser;
	return retFlg;
}

bool fk_IndexFaceSet::readDXFFile(string argFileName, bool argSolidFlg)
{
	fk_DXFParser	*dxfParser = new fk_DXFParser();
	bool			retFlg;

	dxfParser->SetMeshData(this);
	retFlg = dxfParser->ReadDXFFile(argFileName, argSolidFlg);
	delete dxfParser;
	return retFlg;
}

bool fk_IndexFaceSet::readVRMLFile(string argFileName,
								   bool argMaterialFlag, bool argSolidFlag)
{
	fk_VRMLParser	*vrmlParser = new fk_VRMLParser();
	bool			retFlg;

	vrmlParser->SetMeshData(this);
	retFlg = vrmlParser->ReadVRMLFile(argFileName, argMaterialFlag,
									  argSolidFlag);
	delete vrmlParser;
	return retFlg;
}


bool fk_IndexFaceSet::readMQOFile(string argFileName,
								  string argObjName,
								  bool argSolidFlg,
								  bool argContFlg,
								  bool argMatFlg)
{
	return readMQOFile(argFileName, argObjName, -1, argSolidFlg,
					   argContFlg, argMatFlg);
}

bool fk_IndexFaceSet::readMQOFile(string argFileName,
								  string argObjName,
								  int argMateID,
								  bool argSolidFlg,
								  bool argContFlg,
								  bool argMatFlg)
{
	fk_MQOParser	*mqoParser = new fk_MQOParser();
	bool			retFlg;

	mqoParser->SetMeshData(this);
	mqoParser->SetContMode(argContFlg);
	mqoParser->SetMaterialMode(argMatFlg);
	retFlg = mqoParser->ReadMQOFile(argFileName, argObjName,
									argMateID, argSolidFlg);
	delete mqoParser;
	return retFlg;
}

bool fk_IndexFaceSet::readMQOData(unsigned char *argBuffer,
								  string argObjName,
								  bool argSolidFlg,
								  bool argContFlg,
								  bool argMatFlg)
{
	return readMQOData(argBuffer, argObjName, -1, argSolidFlg,
					   argContFlg, argMatFlg);
}

bool fk_IndexFaceSet::readMQOData(unsigned char *argBuffer,
								  string argObjName,
								  int argMateID,
								  bool argSolidFlg,
								  bool argContFlg,
								  bool argMatFlg)
{
	fk_MQOParser	*mqoParser = new fk_MQOParser();
	bool			retFlg;

	mqoParser->SetMeshData(this);
	mqoParser->SetContMode(argContFlg);
	mqoParser->SetMaterialMode(argMatFlg);
	retFlg = mqoParser->ReadMQOData(argBuffer, argObjName,
									argMateID, argSolidFlg);
	delete mqoParser;
	return retFlg;
}

bool fk_IndexFaceSet::readD3DXFile(string argFileName, string argObjName,
								   bool argSolidFlg)
{
	return readD3DXFile(argFileName, argObjName, -1, argSolidFlg);
}

bool fk_IndexFaceSet::readD3DXFile(string argFileName, string argObjName,
								   int argTexID, bool argSolidFlg)
{
	fk_D3DXParser	*d3dxParser = new fk_D3DXParser();
	bool			retFlg, animFlg;

	if(anim == NULL || cloneFlg == true) {
		anim = new fk_D3DXAnimation;
	}
	d3dxParser->SetMeshData(this);
	d3dxParser->SetAnimation(anim);
	retFlg = d3dxParser->ReadD3DXFile(argFileName, argObjName,
									  argTexID, argSolidFlg, &animFlg);
	if(animFlg == true) setAnimationTime(-1.0);
	delete d3dxParser;
	return retFlg;
}

bool fk_IndexFaceSet::writeVRMLFile(string argFileName,
									fk_Material *argMaterial, bool triFlag)
{
	fk_VRMLOut		*vrmlOut = new fk_VRMLOut(this);
	bool			retFlg;

	retFlg = vrmlOut->WriteVRMLFile(argFileName, argMaterial, triFlag);
	delete vrmlOut;
	return retFlg;
}

bool fk_IndexFaceSet::writeVRMLFile(string argFileName,
									vector<double> *argTime,
									vector<fk_Vector> *argPos,
									fk_Material *argMaterial,
									bool argTriFlg)
{
	fk_VRMLOut		*vrmlOut = new fk_VRMLOut(this);
	bool			retFlg;

	retFlg = vrmlOut->WriteVRMLFile(argFileName, argTime, argPos,
									argMaterial, argTriFlg);
	delete vrmlOut;
	return retFlg;
}

bool fk_IndexFaceSet::writeSTLFile(string argFileName)
{
	fk_STLOut		*stlOut = new fk_STLOut(this);
	bool			retFlg;

	retFlg = stlOut->WriteSTLFile(argFileName);
	delete stlOut;
	return retFlg;
}

bool fk_IndexFaceSet::writeDXFFile(string argFileName, bool argTriFlg)
{
	fk_DXFOut		*dxfOut = new fk_DXFOut(this);
	bool			retFlg;

	retFlg = dxfOut->WriteDXFFile(argFileName, argTriFlg);
	delete dxfOut;
	return retFlg;
}

bool fk_IndexFaceSet::writeMQOFile(string argFileName)
{
	fk_MQOOut		*mqoOut = new fk_MQOOut(this);
	bool			retFlg;

	retFlg = mqoOut->WriteMQOFile(argFileName);
	delete mqoOut;
	return retFlg;
}

void fk_IndexFaceSet::makeBlock(double argX, double argY, double argZ)
{
	_st			i;
	fk_Vector	tmpVec[8];

	const static double vParam[8][3] = {
		{0.5, 0.5, 0.5},
		{-0.5, 0.5, 0.5},
		{0.5, -0.5, 0.5},
		{-0.5, -0.5, 0.5},
		{0.5, 0.5, -0.5},
		{-0.5, 0.5, -0.5},
		{0.5, -0.5, -0.5},
		{-0.5, -0.5, -0.5}
	};

	static int vertexTable[6][4] = {
		{1, 2, 4, 3}, {5, 7 ,8, 6},
		{3, 7, 5, 1}, {2, 6, 8, 4},
		{1, 5, 6, 2}, {3, 4, 8, 7}
	};

	for(i = 0; i < 8; i++) {
		tmpVec[i].set(argX * vParam[i][0],
					  argY * vParam[i][1], argZ * vParam[i][2]);
	}

	makeIFSet(6, 4, &vertexTable[0][0], 8, tmpVec, 1);
	return;
}

void fk_IndexFaceSet::setBlockSize(double argX, double argY, double argZ)

{
	int			i;

	const static double vParam[8][3] = {
		{0.5, 0.5, 0.5},
		{-0.5, 0.5, 0.5},
		{0.5, -0.5, 0.5},
		{-0.5, -0.5, 0.5},
		{0.5, 0.5, -0.5},
		{-0.5, 0.5, -0.5},
		{0.5, -0.5, -0.5},
		{-0.5, -0.5, -0.5}
	};

	if(posSize != 8 || faceSize != 6) return;

	for(i = 0; i < 8; i++) {
		moveVPosition(i, argX * vParam[i][0],
					  argY * vParam[i][1], argZ * vParam[i][2]);
	}

	return;
}

void fk_IndexFaceSet::setBlockSize(double argSize, fk_Axis argAxis)
{
	fk_Vector			newPos;
	int					i;
	const static double vParam[8][3] = {
		{0.5, 0.5, 0.5},
		{-0.5, 0.5, 0.5},
		{0.5, -0.5, 0.5},
		{-0.5, -0.5, 0.5},
		{0.5, 0.5, -0.5},
		{-0.5, 0.5, -0.5},
		{0.5, -0.5, -0.5},
		{-0.5, -0.5, -0.5}
	};

	if(posSize != 8 || faceSize != 6) return;

	newPos = pos[0];
	newPos *= 2.0;

	switch(argAxis) {
	  case fk_X:
		newPos.x = argSize;
		break;
	  case fk_Y:
		newPos.y = argSize;
		break;
	  case fk_Z:
		newPos.z = argSize;
		break;
	  default:
		break;
	}

	for(i = 0; i < 8; i++) {
		moveVPosition(i, newPos.x * vParam[i][0],
					  newPos.y * vParam[i][1], newPos.z * vParam[i][2]);
	}

	return;
}

void fk_IndexFaceSet::setBlockScale(double argScale)
{
	setBlockScale(argScale, argScale, argScale);
}

void fk_IndexFaceSet::setBlockScale(double argScale, fk_Axis argAxis)
{
	fk_Vector		newPos;
	int				i;
	const static double vParam[8][3] = {
		{0.5, 0.5, 0.5},
		{-0.5, 0.5, 0.5},
		{0.5, -0.5, 0.5},
		{-0.5, -0.5, 0.5},
		{0.5, 0.5, -0.5},
		{-0.5, 0.5, -0.5},
		{0.5, -0.5, -0.5},
		{-0.5, -0.5, -0.5}
	};

	if(posSize != 8 || faceSize != 6) return;
	newPos = pos[0];
	newPos *= 2.0;

	switch(argAxis) {
	  case fk_X:
		newPos.x *= argScale;
		break;
	  case fk_Y:
		newPos.y *= argScale;
		break;
	  case fk_Z:
		newPos.z *= argScale;
		break;
	  default:
		break;
	}

	for(i = 0; i < 8; i++) {
		moveVPosition(i, newPos.x * vParam[i][0],
					  newPos.y * vParam[i][1], newPos.z * vParam[i][2]);
	}

	return;
}

void fk_IndexFaceSet::setBlockScale(double argX, double argY, double argZ)
{
	fk_Vector		newPos;
	int				i;
	const static double vParam[8][3] = {
		{0.5, 0.5, 0.5},
		{-0.5, 0.5, 0.5},
		{0.5, -0.5, 0.5},
		{-0.5, -0.5, 0.5},
		{0.5, 0.5, -0.5},
		{-0.5, 0.5, -0.5},
		{0.5, -0.5, -0.5},
		{-0.5, -0.5, -0.5}
	};

	if(posSize != 8 || faceSize != 6) return;
	newPos.set(static_cast<double>(pos[0].x)*2.0*argX,
			   static_cast<double>(pos[0].y)*2.0*argY,
			   static_cast<double>(pos[0].z)*2.0*argZ);

	for(i = 0; i < 8; i++) {
		moveVPosition(i, newPos.x * vParam[i][0],
					  newPos.y * vParam[i][1], newPos.z * vParam[i][2]);
	}

	return;
}

void fk_IndexFaceSet::makeCircle(int argDiv, double argRadius)
{
	vector<fk_Vector>		vecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	int						i;
	double					theta;

	vecArray.resize(static_cast<_st>(argDiv * 4 + 1));
	vecArray[0].set(0.0, 0.0, 0.0);

	for(i = 0; i < 4 * argDiv; i++) {
		theta = (static_cast<double>(i) * FK_PI)/(double(argDiv*2));
		vecArray[static_cast<_st>(i+1)].set(cos(theta) * argRadius,
											sin(theta) * argRadius, 0.0);
	}

	IFArray.clear();
	for(i = 0; i < argDiv*4; i++) {
		IDArray.clear();
		IDArray.push_back(1);
		IDArray.push_back(i + 2);
		if(i == argDiv * 4 - 1) {
			IDArray.push_back(2);
		} else {
			IDArray.push_back(i + 3);
		}
		IFArray.push_back(IDArray);
	}

	MakeMesh(&vecArray, &IFArray);

	return;
}

void fk_IndexFaceSet::setCircleDivide(int argDiv)
{
	makeCircle(argDiv, static_cast<double>(pos[1].x));

	return;
}

void fk_IndexFaceSet::setCircleRadius(double argRadius)
{
	double		scale;
	_st			i;

	scale = argRadius/static_cast<double>(pos[1].x);

	for(i = 1; i < static_cast<_st>(posSize); i++) {
		moveVPosition(static_cast<int>(i), static_cast<double>(pos[i].x)*scale,
					  static_cast<double>(pos[i].y)*scale, 0.0);
	}

	return;
}

void fk_IndexFaceSet::setCircleScale(double argScale)
{
	_st		i;

	for(i = 1; i < static_cast<_st>(posSize); i++) {
		moveVPosition(static_cast<int>(i), static_cast<double>(pos[i].x)*argScale,
					  static_cast<double>(pos[i].y)*argScale, 0.0);
	}

	return;
}

void fk_IndexFaceSet::makeSphere(int argDiv, double argRadius)
{
	vector<fk_Vector>		vecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	_st						i, j, index, div;
	int						ii, jj, iindex, iindex2;
	vector<double>			xz_radius;
	double					theta1, theta2;

	div = static_cast<_st>(argDiv);
	vecArray.resize(div*4 * (div*2 - 1) + 2);
	xz_radius.resize(div*2 - 1);

	for(i = 0; i < div*2 - 1; i++) {
		xz_radius[i] = argRadius*sin(static_cast<double>(i+1)*FK_PI/static_cast<double>(div*2));
	}

	vecArray.front().set(0.0, argRadius, 0.0);
	vecArray.back().set(0.0, -argRadius, 0.0);

	for(i = 0; i < div*2 - 1; i++) {
		for(j = 0; j < div*4; j++) {
			index = i*div*4 + j + 1;
			theta1 = static_cast<double>(j)*FK_PI/static_cast<double>(div*2);
			theta2 = static_cast<double>(i+1)*FK_PI/static_cast<double>(div*2);
			vecArray[index].set(xz_radius[i] * cos(theta1),
								argRadius * cos(theta2),
								xz_radius[i] * sin(theta1));
		}
	}

	IFArray.clear();

	// TOP
	for(ii = 0; ii < argDiv*4; ii++) {
		IDArray.clear();
		IDArray.push_back(1);
		if(ii == argDiv*4 - 1) {
			IDArray.push_back(2);
		} else {
			IDArray.push_back(ii+3);
		}
		IDArray.push_back(ii+2);
		IFArray.push_back(IDArray);
	}

	// BOTTOM
	iindex = (argDiv*4)*(argDiv*2 - 2) + 2;
	for(ii = 0; ii < argDiv*4; ii++) {
		IDArray.clear();
		IDArray.push_back(iindex + (argDiv*4));
		IDArray.push_back(iindex + ii);
		if(ii == argDiv*4 - 1) {
			IDArray.push_back(iindex);
		} else {
			IDArray.push_back(iindex + ii + 1);
		}
		IFArray.push_back(IDArray);
	}

	// SIDE
	for(ii = 0; ii < argDiv*2 - 2; ii++) {
		for(jj = 0; jj < argDiv*4; jj++) {
			IDArray.clear();
			iindex = ii*argDiv*4 + jj + 2;
			iindex2 = (jj == argDiv*4 - 1) ? ii*argDiv*4 + 2 : iindex + 1;

			IDArray.push_back(iindex);
			IDArray.push_back(iindex2);
			IDArray.push_back(iindex2 + argDiv*4);
			IFArray.push_back(IDArray);

			IDArray.clear();
			IDArray.push_back(iindex);
			IDArray.push_back(iindex2 + argDiv*4);
			IDArray.push_back(iindex + argDiv*4);
			IFArray.push_back(IDArray);
		}
	}

	MakeMesh(&vecArray, &IFArray);

	return;
}

void fk_IndexFaceSet::setSphereDivide(int argDiv)
{
	makeSphere(argDiv, static_cast<double>(pos[0].y));
	return;
}

void fk_IndexFaceSet::setSphereRadius(double argRadius)
{
	double		scale;
	_st			i;

	scale = argRadius/static_cast<double>(pos[0].y);

	for(i = 0; i < static_cast<_st>(posSize); i++) {
		moveVPosition(static_cast<int>(i),
					  static_cast<double>(pos[i].x)*scale,
					  static_cast<double>(pos[i].y)*scale,
					  static_cast<double>(pos[i].z)*scale);
	}

	return;
}

void fk_IndexFaceSet::setSphereScale(double argScale)
{
	_st		i;

	for(i = 0; i < static_cast<_st>(posSize); i++) {
		moveVPosition(static_cast<int>(i),
					  static_cast<double>(pos[i].x)*argScale,
					  static_cast<double>(pos[i].y)*argScale,
					  static_cast<double>(pos[i].z)*argScale);
	}

	return;
}

void fk_IndexFaceSet::makePrism(int argDiv, double argTop, double argBottom,
								double argHeight)
{
	fk_IFSetHandle			IFSet;
	vector<fk_Vector>		vecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	int						v[4], i;
	_st						j, div;
	double					theta;

	div = static_cast<_st>(argDiv);
	vecArray.resize(div*2+2);
	vecArray[0].set(0.0, 0.0, 0.0);
	vecArray[div + 1].set(0.0, 0.0, -argHeight);

	for(j = 0; j < div; j++) {
		theta = (static_cast<double>(j*2) * FK_PI)/static_cast<double>(div);
		vecArray[j+1].set(cos(theta) * argBottom,
						  sin(theta) * argBottom, 0.0);
		vecArray[div+j+2].set(cos(theta) * argTop,
							  sin(theta) * argTop, -argHeight);
	}

	IFArray.clear();

	for(j = 0; j < div; j++) {
		i = static_cast<int>(j);
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

	MakeMesh(&vecArray, &IFArray);

	return;
}

void fk_IndexFaceSet::setPrismDivide(int argDiv)
{
	_st			div;
	double		top, bottom, height;

	if((div = static_cast<_st>(posSize/2 - 1)) < 3) return;

	top = static_cast<double>(pos[div+2].x);
	bottom = static_cast<double>(pos[1].x);
	height = static_cast<double>(-pos[div+1].z);

	makePrism(argDiv, top, bottom, height);
	return;
}

void fk_IndexFaceSet::setPrismTopRadius(double argTop)
{
	int			div;
	int			i;
	double		theta, z;
	fk_Vector	vec;

	div = posSize/2 - 1;
	z = static_cast<double>(pos[static_cast<_st>(div+2)].z);
	for(i = 0; i < div; i++) {
		theta = (static_cast<double>(i*2) * FK_PI)/static_cast<double>(div);
		vec.set(cos(theta) * argTop, sin(theta) * argTop, z);
		moveVPosition(div+i+2, vec);
	}

	return;
}

void fk_IndexFaceSet::setPrismBottomRadius(double argBottom)
{
	int			div;
	int			i;
	double		theta;
	fk_Vector	vec;

	div = posSize/2 - 1;
	for(i = 0; i < div; i++) {
		theta = (static_cast<double>(i*2) * FK_PI)/static_cast<double>(div);
		vec.set(cos(theta) * argBottom, sin(theta) * argBottom, 0.0);
		moveVPosition(i+1, vec);
	}

	return;
}

void fk_IndexFaceSet::setPrismHeight(double argHeight)
{
	_st			i, div;
	fk_Vector	vec;

	div = static_cast<_st>(posSize/2 - 1);
	for(i = 0; i <= div; i++) {
		vec.set(static_cast<double>(pos[div+i+1].x),
				static_cast<double>(pos[div+i+1].y),
				-argHeight);
		moveVPosition(static_cast<int>(div+i+1), vec);
	}

	return;
}

void fk_IndexFaceSet::makeCone(int argDiv, double argRadius, double argHeight)
{
	vector<fk_Vector>		vecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	_st						j, div;
	int						i;
	double					theta;

	div = static_cast<_st>(argDiv);
	vecArray.resize(div+2);
	vecArray[0].set(0.0, 0.0, 0.0);
	vecArray[1].set(0.0, 0.0, -argHeight);

	for(j = 0; j < div; j++) {
		theta = (static_cast<double>(j*2) * FK_PI)/static_cast<double>(div);
		vecArray[j+2].set(cos(theta) * argRadius, sin(theta) * argRadius, 0.0);
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

	MakeMesh(&vecArray, &IFArray);

	return;
}

void fk_IndexFaceSet::setConeDivide(int argDiv)
{
	double	rad, height;

	rad = static_cast<double>(pos[2].x);
	height = static_cast<double>(-pos[1].z);

	makeCone(argDiv, rad, height);
}

void fk_IndexFaceSet::setConeRadius(double argRadius)
{
	int			div;
	int			i;
	double		theta;
	fk_Vector	vec;

	div = posSize - 2;
	for(i = 0; i < div; i++) {
		theta = (static_cast<double>(i*2) * FK_PI)/static_cast<double>(div);
		vec.set(cos(theta) * argRadius, sin(theta) * argRadius, 0.0);
		moveVPosition(i+2, vec);
	}

	return;
}

void fk_IndexFaceSet::setConeHeight(double argHeight)
{
	fk_Vector		vec(0.0, 0.0, -argHeight);

	moveVPosition(1, vec);

	return;
}

void fk_IndexFaceSet::MakeCapsuleVec(vector<fk_Vector> *argVec, int argDiv, 
									 double argLen, double argRad)
{
	_st					div = static_cast<_st>(argDiv);
	_st					i, j, index1;
	vector<double>		xy_radius;
	double				theta1, theta2;
	double				len = argLen/2.0;

	argVec->resize(div*div * 8 + 2);
	xy_radius.resize(div*2);

	for(i = 0; i < div; i++) {
		xy_radius[i] = argRad*sin(static_cast<double>(i+1)*FK_PI/static_cast<double>(div*2));
		xy_radius[(2*div-1) - i] = xy_radius[i];
	}

	argVec->front().set(0.0, 0.0, argRad+len);
	argVec->back().set(0.0, 0.0, -(argRad+len));

	for(i = 0; i < div; i++) {
		for(j = 0; j < div*4; j++) {
			index1 = i*div*4 + j + 1;
			theta1 = static_cast<double>(j)*FK_PI/static_cast<double>(div*2);
			theta2 = static_cast<double>(i+1)*FK_PI/static_cast<double>(div*2);
			argVec->at(index1).set(xy_radius[i] * cos(theta1),
								   xy_radius[i] * sin(theta1),
								   argRad * cos(theta2) + len);

		}
	}

	for(i = div; i < div*2; i++) {
		for(j = 0; j < div*4; j++) {
			index1 = i*div*4 + j + 1;
			theta1 = static_cast<double>(j)*FK_PI/static_cast<double>(div*2);
			theta2 = static_cast<double>(i)*FK_PI/static_cast<double>(div*2);
			argVec->at(index1).set(xy_radius[i] * cos(theta1),
								   xy_radius[i] * sin(theta1),
								   argRad * cos(theta2) - len);
		}
	}
	return;
}

void fk_IndexFaceSet::MakeCapsuleIFSet(vector< vector<int> > *argIF, int argDiv)
{
	vector<int>		IDArray;
	int				i, j, index1, index2;

	argIF->clear();

	// TOP
	for(i = 0; i < argDiv*4; i++) {
		IDArray.clear();
		IDArray.push_back(1);
		IDArray.push_back(i+2);
		if(i == argDiv*4 - 1) {
			IDArray.push_back(2);
		} else {
			IDArray.push_back(i+3);
		}
		argIF->push_back(IDArray);
	}

	// BOTTOM
	index1 = (argDiv*4)*(argDiv*2 - 1) + 2;
	for(i = 0; i < argDiv*4; i++) {
		IDArray.clear();
		IDArray.push_back(index1 + (argDiv*4));
		if(i == argDiv*4 - 1) {
			IDArray.push_back(index1);
		} else {
			IDArray.push_back(index1 + i + 1);
		}
		IDArray.push_back(index1 + i);
		argIF->push_back(IDArray);
	}

	// SIDE
	for(i = 0; i < argDiv*2 - 1; i++) {
		for(j = 0; j < argDiv*4; j++) {
			IDArray.clear();
			index1 = i*argDiv*4 + j + 2;
			index2 = (j == argDiv*4 - 1) ? i*argDiv*4 + 2 : index1 + 1;

			IDArray.push_back(index1);
			IDArray.push_back(index2 + argDiv*4);
			IDArray.push_back(index2);
			argIF->push_back(IDArray);

			IDArray.clear();
			IDArray.push_back(index1);
			IDArray.push_back(index1 + argDiv*4);
			IDArray.push_back(index2 + argDiv*4);
			argIF->push_back(IDArray);
		}
	}
	return;
}

void fk_IndexFaceSet::makeCapsule(int argDiv, double argLen, double argRad)
{
	vector<fk_Vector>		vecArray;
	vector< vector<int> >	IFArray;

	if(argLen < 0.0) return;

	MakeCapsuleVec(&vecArray, argDiv, argLen, argRad);
	MakeCapsuleIFSet(&IFArray, argDiv);
	MakeMesh(&vecArray, &IFArray);
}

void fk_IndexFaceSet::setCapsuleSize(double argLen, double argRad)
{
	vector<fk_Vector>	vecArray;
	int					div;
	_st					i;

	div = static_cast<int>(sqrt(static_cast<double>(posSize)/8.0));
	MakeCapsuleVec(&vecArray, div, argLen, argRad);
	for(i = 0; i < static_cast<_st>(posSize); i++) {
		moveVPosition(static_cast<int>(i), vecArray[i]);
	}

	return;
}

void fk_IndexFaceSet::putSolid(fk_Solid *argSolid)
{
	fk_Vector	*vArray;
	int			tmpPNum = 0;

	if(argSolid == NULL) return;

	switch(type) {
	  case FK_IF_TRIANGLES:
		tmpPNum = 3;
		break;

	  case FK_IF_QUADS:
		tmpPNum = 4;
		break;

	  default:
		return;
	}

	vArray = new fk_Vector [static_cast<size_t>(posSize)];
	for(_st i = 0; i < static_cast<_st>(posSize); i++) vArray[i] = pos[i];

	argSolid->makeIFSet(faceSize, tmpPNum, &ifs[0], posSize, vArray);
	delete [] vArray;

	return;
}

fk_D3DXAnimation * fk_IndexFaceSet::GetAnimation(void)
{
	if(anim == NULL) anim = new fk_D3DXAnimation;
	return anim;
}

void fk_IndexFaceSet::setAnimationTime(double argTime)
{
	_st		i;
	int		j;

	if(anim == NULL) return;

	if(pos.size() != timeOrgPos.size()) {
		timeOrgPos = pos;
	}

	anim->SetTime(argTime);

	for(i = 0; i < pos.size(); i++) {
		j = static_cast<int>(i);
		moveVPosition(j, anim->GetMovePos(j, timeOrgPos[i]));
	}

	return;
}

void fk_IndexFaceSet::setBVHMotion(fk_BVHMotion *argBVH)
{
	if(anim == NULL || cloneFlg == true) {
		anim = new fk_D3DXAnimation;
		cloneFlg = false;
	}
	anim->SetBVHMotion(argBVH);
	return;
}

void fk_IndexFaceSet::cloneShape(fk_IndexFaceSet *argIFS)
{
	if(this == argIFS) return;
	if(argIFS == NULL) return;

	localPalette = argIFS->localPalette;
	pos = argIFS->pos;
	timeOrgPos = argIFS->timeOrgPos;
	vNorm = argIFS->vNorm;
	pNorm = argIFS->pNorm;
	ifs = argIFS->ifs;
	edgeSet = argIFS->edgeSet;
	loopStack = argIFS->loopStack;
	modifyFlg = argIFS->modifyFlg;
	vNormFlg = argIFS->vNormFlg;
	pNormFlg = argIFS->pNormFlg;
	modifyList = argIFS->modifyList;
	colorID = argIFS->colorID;
	colorFlg = argIFS->colorFlg;
	posSize = argIFS->posSize;
	faceSize = argIFS->faceSize;
	type = argIFS->type;

	anim = argIFS->anim;
	orgIFS = argIFS;
	cloneFlg = true;

	argIFS->cloneList.push_back(this);


	return;
}

void fk_IndexFaceSet::PosPrint(string argStr)
{
	_st				i;
	stringstream	ss;
	
	for(i = 0; i < pos.size(); i++) {
		ss.clear();
		ss << argStr << "[" << i << "] = (";
		ss << pos[i].x << ", " << pos[i].y << ", " << pos[i].z << ")";
		fk_PutError(ss.str());
	}
	return;
}

