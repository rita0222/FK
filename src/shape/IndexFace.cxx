/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
#include <FK/Window.h>
#include <sstream>

using namespace std;
using namespace FK;

namespace FK {
	class fk_EdgePair {
	public:
		int id[2];

		fk_EdgePair();
		
		bool	operator ==(const fk_EdgePair &) const;
		bool	operator >(const fk_EdgePair &) const;
		bool	operator <(const fk_EdgePair &) const;

		void	set(int, int);
	};		
}

fk_EdgePair::fk_EdgePair()
{
	id[0] = id[1] = -1;
}

bool fk_EdgePair::operator ==(const fk_EdgePair &argE) const
{
	return (id[0] == argE.id[0] && id[1] == argE.id[1]);
}

bool fk_EdgePair::operator >(const fk_EdgePair &argE) const
{
	if(id[0] > argE.id[0]) return true;
	if(id[0] < argE.id[0]) return false;
	if(id[1] > argE.id[1]) return true;
	return false;
}

bool fk_EdgePair::operator <(const fk_EdgePair &argE) const
{
	if(id[0] < argE.id[0]) return true;
	if(id[0] > argE.id[0]) return false;
	if(id[1] < argE.id[1]) return true;
	return false;
}

void fk_EdgePair::set(int argID1, int argID2)
{
	if(argID1 < argID2) {
		id[0] = argID1;
		id[1] = argID2;
	} else {
		id[0] = argID2;
		id[1] = argID1;
	}
}

//////////////////////////////////////////////////////////////////////////////

fk_IndexFaceSet::fk_IndexFaceSet(void)
	: anim(nullptr), cloneFlg(false), orgIFS(nullptr),
	  edgeIndexFlg(true), faceIndexFlg(true),
	  edgeIBO(0), faceIBO(0)
{
	SetObjectType(FK_INDEXFACESET);
	//SetPaletteData(&localPalette);
	
	vertexPosition.clear();
	timeOrgPosition.clear();
	vertexNormal.clear();
	faceNormal.clear();
	edgeIndex.clear();
	faceIndex.clear();
	loopStack.clear();
	vertexNormFlg.clear();
	faceNormFlg.clear();
	modifyList.clear();
	cloneList.clear();

	setShaderAttribute(vertexName, 3, vertexPosition.getP());
	setShaderAttribute(normalName, 3, vertexNormal.getP());

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
	if(edgeIBO != 0) glDeleteBuffers(1, &edgeIBO);
	if(faceIBO != 0) glDeleteBuffers(1, &faceIBO);
	return;
}

void fk_IndexFaceSet::DeleteCloneLink(fk_IndexFaceSet *argIFS)
{
	list<fk_IndexFaceSet *>::iterator	ite;

	argIFS->anim = nullptr;
	argIFS->cloneFlg = false;
	argIFS->orgIFS = nullptr;

	for(ite = argIFS->cloneList.begin();
		ite != argIFS->cloneList.end(); ++ite) {

		DeleteCloneLink(*ite);
	}
	argIFS->cloneList.clear();
	return;
}

void fk_IndexFaceSet::Init(void)
{
	// 各データを一旦解放
	vertexPosition.clear();
	vertexNormal.clear();
	faceNormal.clear();
	faceIndex.clear();
	edgeIndex.clear();
	loopStack.clear();

	vertexNormFlg.clear();
	faceNormFlg.clear();

	edgeIndexFlg = true;
	faceIndexFlg = true;

	return;
}

bool fk_IndexFaceSet::MakeMesh(vector<fk_Vector> *vData,
							   vector< vector<int> > *lIndex, bool)
{
	_st				i, j;

	if(vData == nullptr || lIndex == nullptr) {
		return false;
	}

	if(lIndex->size() == 0) return true;

	// 3,4角形以外が入力されたらエラー
	for(i = 0; i < lIndex->size(); ++i) {
		_st pNum = lIndex->at(i).size();
		if(pNum < 3 || pNum > 4) return false;
	}

	// データ領域の確保
	Init();

	// 頂点データのコピー
	for(i = 0; i < vData->size(); ++i) {
		vertexPosition.push((*vData)[i]);
		//vertexNormFlg.push_back(char(true));
	}

	// 面データのコピー
	for(i = 0; i < lIndex->size(); ++i) {
		if((*lIndex)[i].size() == 3) {
			for(j = 0; j < 3; ++j) {
				faceIndex.push_back(GLuint((*lIndex)[i][j]));
			}
		} else {
			faceIndex.push_back(GLuint((*lIndex)[i][0]));
			faceIndex.push_back(GLuint((*lIndex)[i][1]));
			faceIndex.push_back(GLuint((*lIndex)[i][2]));
			faceIndex.push_back(GLuint((*lIndex)[i][2]));
			faceIndex.push_back(GLuint((*lIndex)[i][3]));
			faceIndex.push_back(GLuint((*lIndex)[i][0]));
		}
	}

	MakeEdgeSet(lIndex);
	ModifyVertexNorm();

	faceIndexFlg = true;

	return true;
}

void fk_IndexFaceSet::makeIFSet(int argTNum, int argPNum, int *argIF,
								int argVNum, fk_Vector *argPos, int argOrder)
{
	vector<fk_Vector> posArray;
	vector< vector<int> > loopArray;
	vector<int> loop;
	int id;

	Init();

	// 頂点データのコピー
	for(_st i = 0; i < _st(argVNum); ++i) posArray.push_back(argPos[i]);
	
	// 面データのコピー
	for(_st i = 0; i < _st(argTNum); ++i) {
		loop.clear();
		for(_st j = 0; j < _st(argPNum); ++j) {
			id = argIF[i*_st(argPNum) + j] - argOrder;
			loop.push_back(id);
		}
		loopArray.push_back(loop);
	}

	MakeMesh(&posArray, &loopArray);
	return;
}

void fk_IndexFaceSet::makeIFSet(vector< vector<int> > *argIFS,
								vector<fk_Vector> *argPos,
								int argOrder)
{
	vector< vector<int> >	tmpIFS;
	vector<int>				tmpLoop;
	vector< vector<int> >	*ifsP;

	if(argOrder != 0) {
		for(_st i = 0; i < argIFS->size(); ++i) {
			tmpLoop.clear();
			for(_st j = 0; j < (*argIFS)[i].size(); ++j) {
				tmpLoop.push_back((*argIFS)[i][j] - argOrder);
			}
			tmpIFS.push_back(tmpLoop);
		}
		ifsP = &tmpIFS;
	} else {
		ifsP = argIFS;
	}
	MakeMesh(argPos, ifsP);
	return;
}

void fk_IndexFaceSet::InitFaceNorm(void)
{
	int i;

	faceNormal.resize(int(faceIndex.size())/3);
	faceNormFlg.resize(faceIndex.size()/3);

	fill(faceNormFlg.begin(), faceNormFlg.end(), char(true));

	for(i = 0; i < faceNormal.getSize(); ++i) {
		MakeFaceNorm(i);
	}

	ResetFaceFlg();
	return;
}

void fk_IndexFaceSet::ModifyFaceNorm(void)
{
	_st		i, j, vID;

	// 形状が定義されていない場合
	if(faceIndex.empty() == true) return;

	// まだ面法線配列が生成されていない場合
	if(faceNormal.getSize() == 0) {
		InitFaceNorm();
	}

	// 頂点の面接続テーブルが生成されていない場合, テーブルを生成する。
	if(loopStack.empty() == true) {
		MakeLoopTable();
	}

	// modifyList に従って処理
	for(i = 0; i < modifyList.size(); ++i) {
		vID = _st(modifyList[i]);
		for(j = 0; j < loopStack[vID].size(); ++j) {
			MakeFaceNorm(loopStack[vID][j]);
		}
	}

	ResetFaceFlg();
	modifyList.clear();

	return;
}

void fk_IndexFaceSet::MakeFaceNorm(int argID)
{
	_st			id = _st(argID);
	_st			j;
	fk_FVector	v;

	if(faceNormFlg[id] == char(false)) return;

	v = CalcTriNorm(&faceIndex[id*3]);
	faceNormal.set(int(id), v);
	faceNormFlg[id] = char(false);

	if(vertexNormal.getSize() != 0) {
		for(j = id*3; j < id*3 + 3; ++j) {
			vertexNormFlg[faceIndex[j]] = char(true);
		}
	}
	
	return;
}

void fk_IndexFaceSet::ResetFaceFlg(void)
{
	fill(faceNormFlg.begin(), faceNormFlg.end(), char(true));
	return;
}

void fk_IndexFaceSet::InitVertexNorm(void)
{
	/*
	vector<fk_Vector>	normArray;
	fk_Vector			tmpVec;
	_st					i, j;
	*/

	if(faceNormal.getSize() == 0) InitFaceNorm();

	vertexNormal.resize(vertexPosition.getSize());
	vertexNormFlg.resize(_st(vertexPosition.getSize()));
	//normArray.resize(_st(vertexPosition.getSize()));

/*
	for(i = 0; i < normArray.size(); ++i) normArray[i].init();
	for(i = 0; i < faceIndex.size()/3; ++i) {
		tmpVec = faceNormal.getV(int(i));
		for(j = 0; j < 3; ++j) {
			normArray[faceIndex[i*3+j]] += tmpVec;
		}
	}

	for(i = 0; i < normArray.size(); ++i) {
		normArray[i].normalize();
		vertexNormal.set(int(i), normArray[i]);
	}
*/
	fill(vertexNormFlg.begin(), vertexNormFlg.end(), char(true));
	return;
}

void fk_IndexFaceSet::ModifyVertexNorm(void)
{
	fk_Vector		norm, tmpV;
	_st				i, j, loopID;

	// 形状が定義されていない場合
	if(faceIndex.empty()) return;

	// まだ頂点法線配列が生成されていない場合
	if(vertexNormal.getSize() == 0) {
		InitVertexNorm();
	}

	// 面法線情報を再計算
	ModifyFaceNorm();

	for(i = 0; i < _st(vertexPosition.getSize()); ++i) {
		if(vertexNormFlg[i] == char(true)) {
			norm.init();
			for(j = 0; j < loopStack[i].size(); ++j) {
				loopID = _st(loopStack[i][j]);
				tmpV = faceNormal.getV(int(loopID));
				norm += tmpV;
			}
			norm.normalize();
			vertexNormal.set(int(i), norm);
			vertexNormFlg[i] = char(false);
		}
	}

	return;
}

fk_FVector fk_IndexFaceSet::CalcTriNorm(GLuint *argIF)
{
	_st			i;
	fk_Vector	retNorm;
	fk_Vector	triV[3];

	for(i = 0; i < 3; ++i) {
		triV[i] = vertexPosition.getV(int(argIF[i]));
	}

	retNorm = (triV[1] - triV[0]) ^ (triV[2] - triV[1]);
	retNorm.normalize();

	return static_cast<fk_FVector>(retNorm);
}

fk_FVector fk_IndexFaceSet::CalcPolyNorm(int argNum, int *argIF)
{
	vector<fk_Vector>	posArray, normArray;
	_st					i;
	fk_Vector			tmpVec, sumNorm;

	posArray.clear();
	normArray.clear();

	if(argNum < 4) return sumNorm;
	for(i = 0; i < _st(argNum); ++i) {
		tmpVec = vertexPosition.getV(argIF[i]);
		posArray.push_back(tmpVec);
	}

	posArray.push_back(posArray[0]);
	posArray.push_back(posArray[1]);

	sumNorm.init();
	for(i = 0; i < posArray.size() - 2; ++i) {
		normArray.push_back((posArray[i+1] - posArray[i]) ^
							(posArray[i+2] - posArray[i+1]));
		sumNorm += normArray[i];
	}

	for(i = 0; i < normArray.size(); ++i) {
		if(sumNorm * normArray[i] < 0.0) normArray[i] = -normArray[i];
	}

	sumNorm.init();
	for(i = 0; i < normArray.size(); ++i) {
		sumNorm += normArray[i];
	}

	sumNorm.normalize();
	return static_cast<fk_FVector>(sumNorm);
}

void fk_IndexFaceSet::MakeLoopTable(void)
{
	_st		i, j, vID;

	loopStack.clear();
	loopStack.resize(_st(vertexPosition.getSize()));

	for(i = 0; i < faceIndex.size()/3; ++i) {
		for(j = 0; j < 3; ++j) {
			vID = faceIndex[i*3 + j];
			loopStack[vID].push_back(int(i));
		}
	}

	return;
}

void fk_IndexFaceSet::MakeEdgeSet(vector< vector<int> > *argLoop)
{
	fk_HeapBase<fk_EdgePair>	edgeHeap;
	vector<fk_EdgePair>			edgeArray;
	_st							i, j;
	int							id1, id2;
	vector<char>				edgeFlg;

	for(i = 0; i < argLoop->size(); ++i) {
		for(j = 1; j < (*argLoop)[i].size(); ++j) {
			id1 = (*argLoop)[i][j-1];
			id2 = (*argLoop)[i][j];
			edgeArray.resize(edgeArray.size()+1);
			edgeArray[edgeArray.size()-1].set(id1, id2);
		}
		id1 = (*argLoop)[i][(*argLoop)[i].size()-1];
		id2 = (*argLoop)[i][0];
		edgeArray.resize(edgeArray.size()+1);
		edgeArray[edgeArray.size()-1].set(id1, id2);
	}

	int maxID = -1;
	edgeFlg.resize(edgeArray.size());
	for(i = 0; i < edgeArray.size(); ++i) {
		int tmpID = edgeHeap.getID(&edgeArray[i]);
		if(maxID < tmpID) {
			edgeFlg[i] = char(true);
			maxID = tmpID;
		} else {
			edgeFlg[i] = char(false);
		}
	}
	
	edgeIndex.clear();
	for(i = 0; i < edgeArray.size(); ++i) {
		if(edgeFlg[i] == char(true)) {
			edgeIndex.push_back(GLuint(edgeArray[i].id[0]));
			edgeIndex.push_back(GLuint(edgeArray[i].id[1]));
		}
	}
	edgeIndexFlg = true;

	return;
}


int fk_IndexFaceSet::getPosSize(void)
{
	return vertexPosition.getSize();
}

int fk_IndexFaceSet::getEdgeSize(void)
{
	return int(edgeIndex.size()/2);
}

int fk_IndexFaceSet::getFaceSize(void)
{
	return int(faceIndex.size()/3);
}

fk_Vector fk_IndexFaceSet::getPosVec(int argID)
{
	fk_Vector		retVec(0.0, 0.0, 0.0);

	if(argID < 0 || argID >= vertexPosition.getSize()) return retVec;
	return vertexPosition.getV(argID);
}

vector<int> fk_IndexFaceSet::getFaceData(int argID)
{
	vector<int>		retIF;

	if(argID < 0 || argID >= int(faceIndex.size()/3)) return retIF;

	_st id = _st(argID*3);

	retIF.push_back(int(faceIndex[id]));
	retIF.push_back(int(faceIndex[id+1]));
	retIF.push_back(int(faceIndex[id+2]));

	return retIF;
}

int fk_IndexFaceSet::getFaceData(int argFID, int argVID)
{
	if(argFID < 0 || argFID >= int(faceIndex.size()/3)) return -1;
	if(argVID < 0 || argVID >= 3) return -1;

	return int(faceIndex[_st(argFID * 3 + argVID)]);
}

bool fk_IndexFaceSet::moveVPosition(int argID,
									const fk_Vector &argPos, int argOrder)
{
	int		trueID = argID - argOrder;

	if(trueID < 0 || trueID >= vertexPosition.getSize()) return false;

	vertexPosition.set(trueID, argPos);
	modifyList.push_back(trueID);

	return true;
}

bool fk_IndexFaceSet::moveVPosition(int argID,
									double argX, double argY, double argZ,
									int argOrder)
{
	int		trueID = argID - argOrder;

	if(trueID < 0 || trueID >= vertexPosition.getSize()) return false;

	vertexPosition.set(trueID, argX, argY, argZ);
	modifyList.push_back(trueID);

	return true;
}

bool fk_IndexFaceSet::moveVPosition(int argID, double *argPos, int argOrder)
{
	int		trueID = argID - argOrder;

	if(trueID < 0 || trueID >= vertexPosition.getSize()) return false;

	vertexPosition.set(trueID, argPos[0], argPos[1], argPos[2]);
	modifyList.push_back(trueID);

	return true;
}

fk_Vector fk_IndexFaceSet::getFaceNorm(int argPID, int argOrder)
{
	int			trueID = argPID - argOrder;

	if(trueID < 0 || trueID >= faceNormal.getSize()) {
		return fk_Vector(0.0, 0.0, 0.0);
	}

	return faceNormal.getV(trueID);
}

fk_Vector fk_IndexFaceSet::getPNorm(int argPID, int argOrder)
{
	return getFaceNorm(argPID, argOrder);
}

bool fk_IndexFaceSet::setFaceNorm(int argPID, const fk_Vector &argVec, int argOrder)
{
	int			trueID = argPID - argOrder;

	if(trueID < 0 || trueID >= faceNormal.getSize()) return false;
	faceNormal.set(trueID, argVec);
	return true;
}

bool fk_IndexFaceSet::setPNorm(int argPID, const fk_Vector &argVec, int argOrder)
{
	return setFaceNorm(argPID, argVec, argOrder);
}

fk_Vector fk_IndexFaceSet::getVertexNorm(int argVID, int argOrder)
{
	int			trueID = argVID - argOrder;

	if(trueID < 0 || trueID >= vertexNormal.getSize()) {
		return fk_Vector(0.0, 0.0, 0.0);
	}

	return vertexNormal.getV(trueID);
}

fk_Vector fk_IndexFaceSet::getVNorm(int argVID, int argOrder)
{
	return getVertexNorm(argVID, argOrder);
}

bool fk_IndexFaceSet::setVertexNorm(int argVID, const fk_Vector &argVec, int argOrder)
{
	int			trueID = argVID - argOrder;

	if(trueID < 0 || trueID >= vertexNormal.getSize()) return false;
	vertexNormal.set(trueID, argVec);

	return true;
}

bool fk_IndexFaceSet::setVNorm(int argVID, const fk_Vector &argVec, int argOrder)
{
	return setVertexNorm(argVID, argVec, argOrder);
}

bool fk_IndexFaceSet::setElemMaterialID(int, int)
{
	return true;
}

int fk_IndexFaceSet::getElemMaterialID(int)
{
	return -1;
}

void fk_IndexFaceSet::flush(void)
{
	ModifyVertexNorm();
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

	if(anim == nullptr || cloneFlg == true) {
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
	vector<fk_Vector>		pos;
	vector<int>				loop;
	vector< vector<int> >	ifs;

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
		{0, 1, 3, 2}, {4, 6 ,7, 5},
		{2, 6, 4, 0}, {1, 5, 7, 3},
		{0, 4, 5, 1}, {2, 3, 7, 6}
	};

	fk_Vector vec;
	for(int i = 0; i < 6; ++i) {
		loop.clear();
		for(int j = 0; j < 4; ++j) {
			vec.x = argX * vParam[vertexTable[i][j]][0];
			vec.y = argY * vParam[vertexTable[i][j]][1];
			vec.z = argZ * vParam[vertexTable[i][j]][2];
			pos.push_back(vec);
			loop.push_back(i*4+j);
		}
		ifs.push_back(loop);
	}
	MakeMesh(&pos, &ifs);
	return;
}

void fk_IndexFaceSet::setBlockSize(double argX, double argY, double argZ)

{
	for(int i = 0; i < vertexPosition.getSize(); ++i) {
		fk_Vector pos = vertexPosition.getV(i);
		pos.x = (pos.x > 0.0) ? argX * 0.5 : -argX * 0.5;
		pos.y = (pos.y > 0.0) ? argY * 0.5 : -argY * 0.5;
		pos.z = (pos.z > 0.0) ? argZ * 0.5 : -argZ * 0.5;
		moveVPosition(i, pos);
	}

	return;
}

void fk_IndexFaceSet::setBlockSize(double argSize, fk_Axis argAxis)
{
	fk_Vector pos = vertexPosition.getV(0);
	pos.x = fabs(pos.x) * 2.0;
	pos.y = fabs(pos.y) * 2.0;
	pos.z = fabs(pos.z) * 2.0;
	switch(argAxis) {
	  case fk_X:
		pos.x = argSize;
		break;
		
	  case fk_Y:
		pos.y = argSize;
		break;
		
	  case fk_Z:
		pos.z = argSize;
		break;

	  default:
		break;
	}
	setBlockSize(pos.x, pos.y, pos.z);
		   
	return;
}

void fk_IndexFaceSet::setBlockScale(double argScale)
{
	setBlockScale(argScale, argScale, argScale);
}

void fk_IndexFaceSet::setBlockScale(double argScale, fk_Axis argAxis)
{
	fk_Vector pos = vertexPosition.getV(0);
	pos.x = fabs(pos.x) * 2.0;
	pos.y = fabs(pos.y) * 2.0;
	pos.z = fabs(pos.z) * 2.0;
	switch(argAxis) {
	  case fk_X:
		pos.x *= argScale;
		break;
		
	  case fk_Y:
		pos.y *= argScale;
		break;
		
	  case fk_Z:
		pos.z *= argScale;
		break;

	  default:
		break;
	}
	setBlockSize(pos.x, pos.y, pos.z);

	return;
}

void fk_IndexFaceSet::setBlockScale(double argX, double argY, double argZ)
{
	fk_Vector pos = vertexPosition.getV(0);
	pos.x = fabs(pos.x) * 2.0 * argX;
	pos.y = fabs(pos.y) * 2.0 * argY;
	pos.z = fabs(pos.z) * 2.0 * argZ;
	setBlockSize(pos.x, pos.y, pos.z);
	return;
}

void fk_IndexFaceSet::makeCircle(int argDiv, double argRadius)
{
	vector<fk_Vector>		vecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	double					theta;

	vecArray.resize(_st(argDiv*4 + 1));
	vecArray[_st(argDiv*4)].set(0.0, 0.0, 0.0);

	for(int i = 0; i < 4 * argDiv; ++i) {
		theta = (double(i) * FK_PI)/(double(argDiv*2));
		vecArray[_st(i)].set(cos(theta) * argRadius,
							 sin(theta) * argRadius, 0.0);
	}

	IFArray.clear();

/*	
	for(i = 0; i < argDiv*4; ++i) {
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

	makeIFSet(&IFArray, &vecArray, 1);
*/
	for(int i = 0; i < argDiv*4; ++i) {
		IDArray.clear();
		IDArray.push_back(argDiv*4);
		IDArray.push_back(i);
		if(i == argDiv * 4 - 1) {
			IDArray.push_back(0);
		} else {
			IDArray.push_back(i+1);
		}
		IFArray.push_back(IDArray);
	}

	MakeMesh(&vecArray, &IFArray);
	
	return;
}

void fk_IndexFaceSet::setCircleDivide(int argDiv)
{
	makeCircle(argDiv, vertexPosition.getV(0).x);

	return;
}

void fk_IndexFaceSet::setCircleRadius(double argRadius)
{
	double		scale;
	fk_Vector	V;

	scale = argRadius/vertexPosition.getV(0).x;

	for(int i = 0; i < vertexPosition.getSize()-1; ++i) {
		V = vertexPosition.getV(i);
		moveVPosition(i, V.x*scale, V.y*scale, 0.0);
	}

	return;
}

void fk_IndexFaceSet::setCircleScale(double argScale)
{
	fk_Vector	V;

	for(int i = 0; i < vertexPosition.getSize()-1; ++i) {
		V = vertexPosition.getV(i);
		moveVPosition(i, V.x * argScale, V.y * argScale, 0.0);
	}

	return;
}

void fk_IndexFaceSet::makeSphere(int argDiv, double argRadius)
{
	vector<fk_Vector>		vecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	_st						i, j, index, div;
	int						ii, jj;
	int						iindex1, iindex2, iindex3, iindex4;
	vector<double>			xz_radius;
	double					theta1, theta2;

	div = _st(argDiv);
	vecArray.resize(div*4 * (div*2 - 1) + 2);
	xz_radius.resize(div*2 - 1);

	for(i = 0; i < div*2 - 1; ++i) {
		xz_radius[i] = argRadius*sin(double(i+1)*FK_PI/double(div*2));
	}

	vecArray.front().set(0.0, argRadius, 0.0);
	vecArray.back().set(0.0, -argRadius, 0.0);

	for(i = 0; i < div*2 - 1; ++i) {
		for(j = 0; j < div*4; ++j) {
			index = i*div*4 + j + 1;
			theta1 = double(j)*FK_PI/double(div*2);
			theta2 = double(i+1)*FK_PI/double(div*2);
			vecArray[index].set(xz_radius[i] * cos(theta1),
								argRadius * cos(theta2),
								xz_radius[i] * sin(theta1));
		}
	}

	IFArray.clear();
/*
	// TOP
	for(ii = 0; ii < argDiv*4; ++ii) {
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
	for(ii = 0; ii < argDiv*4; ++ii) {
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
	for(ii = 0; ii < argDiv*2 - 2; ++ii) {
		for(jj = 0; jj < argDiv*4; ++jj) {
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
*/
	// TOP
	for(ii = 0; ii < argDiv*4; ++ii) {
		IDArray.clear();
		IDArray.push_back(0);
		if(ii == argDiv*4 - 1) {
			IDArray.push_back(1);
		} else {
			IDArray.push_back(ii+2);
		}
		IDArray.push_back(ii+1);
		IFArray.push_back(IDArray);
	}

	// BOTTOM
	iindex1 = (argDiv*4)*(argDiv*2 - 2) + 1;
	for(ii = 0; ii < argDiv*4; ++ii) {
		IDArray.clear();
		IDArray.push_back(iindex1 + (argDiv*4));
		IDArray.push_back(iindex1 + ii);
		if(ii == argDiv*4 - 1) {
			IDArray.push_back(iindex1);
		} else {
			IDArray.push_back(iindex1 + ii + 1);
		}
		IFArray.push_back(IDArray);
	}

	// SIDE
	for(ii = 0; ii < argDiv*2 - 2; ++ii) {
		for(jj = 0; jj < argDiv*4; ++jj) {
			IDArray.clear();
			iindex1 = ii*argDiv*4 + jj + 1;
			iindex2 = (jj == argDiv*4 - 1) ? ii*argDiv*4 + 1 : iindex1 + 1;
			iindex3 = iindex1 + argDiv*4;
			iindex4 = iindex2 + argDiv*4;

			IDArray.clear();
			IDArray.push_back(iindex1);
			IDArray.push_back(iindex2);
			IDArray.push_back(iindex4);
			IDArray.push_back(iindex3);
			IFArray.push_back(IDArray);
		}
	}
	
	MakeMesh(&vecArray, &IFArray);

	return;
}

void fk_IndexFaceSet::setSphereDivide(int argDiv)
{
	makeSphere(argDiv, vertexPosition.getV(0).y);
	return;
}

void fk_IndexFaceSet::setSphereRadius(double argRadius)
{
	double		scale = argRadius/vertexPosition.getV(0).y;

	for(int i = 0; i < vertexPosition.getSize(); ++i) {
		moveVPosition(i, vertexPosition.getV(i) * scale);
	}

	return;
}

void fk_IndexFaceSet::setSphereScale(double argScale)
{
	for(int i = 0; i < vertexPosition.getSize(); ++i) {
		moveVPosition(i, vertexPosition.getV(i) * argScale);
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

	_st div = _st(argDiv);
	vecArray.resize(div*4+2);

	// 底面中心
	vecArray[4*div].set(0.0, 0.0, 0.0);

	// 上面中心
	vecArray[4*div+1].set(0.0, 0.0, -argHeight);

	for(_st j = 0; j < div; ++j) {
		double theta = (double(j*2) * FK_PI)/double(div);

		// 底面
		vecArray[j].set(cos(theta) * argBottom,
						sin(theta) * argBottom, 0.0);

		// 側面底側
		vecArray[div+j] = vecArray[j];

		// 側面上側
		vecArray[2*div+j].set(cos(theta) * argTop,
							  sin(theta) * argTop, -argHeight);
		// 上面
		vecArray[3*div+j] = vecArray[2*div+j];
	}

	IFArray.clear();

	for(_st j = 0; j < div; ++j) {
		int i = int(j);
		// 底面
		IDArray.clear();
		IDArray.push_back(argDiv*4);
		IDArray.push_back(i);
		if(i == argDiv - 1) {
			IDArray.push_back(0);
		} else {
			IDArray.push_back(i+1);
		}
		IFArray.push_back(IDArray);

		// 上面
		IDArray.clear();
		IDArray.push_back(4*argDiv+1);
		if(i == argDiv-1) {
			IDArray.push_back(3*argDiv);
		} else {
			IDArray.push_back(3*argDiv+i+1);
		}
		IDArray.push_back(3*argDiv+i);

		IFArray.push_back(IDArray);

		// 側面
		int id1, id2;
		if(i == argDiv - 1) {
			id1 = argDiv+1;
			id2 = 2*argDiv+1;
		} else {
			id1 = argDiv+i+1;
			id2 = 2*argDiv+i+1;
		}
		
		IDArray.clear();
		IDArray.push_back(id1);
		IDArray.push_back(argDiv+i);
		IDArray.push_back(2*argDiv+i);
		IDArray.push_back(id2);
		IFArray.push_back(IDArray);
	}
	MakeMesh(&vecArray, &IFArray);

	return;
}

void fk_IndexFaceSet::setPrismDivide(int argDiv)
{
	int		div;
	double	top, bottom, height;

	if((div = (vertexPosition.getSize() - 2)/4) < 3) return;

	top = vertexPosition.getV(2*div).x;
	bottom = vertexPosition.getV(0).x;
	height = -vertexPosition.getV(2*div).z;

	makePrism(argDiv, top, bottom, height);
	return;
}

void fk_IndexFaceSet::setPrismTopRadius(double argTop)
{
	int			div;
	int			i;
	double		theta, z;
	fk_Vector	vec;

	div = (vertexPosition.getSize()-2)/4;
	z = vertexPosition.getV(2*div).z;
	for(i = 0; i < div; ++i) {
		theta = (double(i*2) * FK_PI)/double(div);
		vec.set(cos(theta) * argTop, sin(theta) * argTop, z);
		moveVPosition(2*div+i, vec);
		moveVPosition(3*div+i, vec);
	}

	return;
}

void fk_IndexFaceSet::setPrismBottomRadius(double argBottom)
{
	int			div;
	int			i;
	double		theta;
	fk_Vector	vec;

	div = (vertexPosition.getSize()-2)/4;
	for(i = 0; i < div; ++i) {
		theta = (double(i*2) * FK_PI)/double(div);
		vec.set(cos(theta) * argBottom, sin(theta) * argBottom, 0.0);
		moveVPosition(i, vec);
		moveVPosition(div+i, vec);
	}

	return;
}

void fk_IndexFaceSet::setPrismHeight(double argHeight)
{
	int			i, div;
	fk_Vector	vec;

	div = (vertexPosition.getSize()-2)/4;
	for(i = 0; i < div; ++i) {
		vec = vertexPosition.getV(2*div+i);
		vec.z = -argHeight;
		moveVPosition(2*div+i, vec);
		moveVPosition(3*div+i, vec);
	}
	vec.set(0.0, 0.0, -argHeight);
	moveVPosition(4*div+1, vec);

	return;
}

void fk_IndexFaceSet::makeCone(int argDiv, double argRadius, double argHeight)
{
	vector<fk_Vector>		vecArray;
	vector<int>				IDArray;
	vector< vector<int> >	IFArray;
	_st						div = _st(argDiv);

	vecArray.resize(3*div+1);
	vecArray[3*div].set(0.0, 0.0, 0.0);

	for(_st j = 0; j < div; ++j) {
		double theta = (double(j*2) * FK_PI)/double(div);
		vecArray[j].set(cos(theta) * argRadius, sin(theta) * argRadius, 0.0);
		vecArray[div+j] = vecArray[j];
		vecArray[2*div+j].set(0.0, 0.0, -argHeight);
	}

	IFArray.clear();

	for(int i = 0; i < argDiv; ++i) {
		// 底面
		IDArray.clear();
		IDArray.push_back(3*argDiv);
		IDArray.push_back(i);
		if(i == argDiv - 1) {
			IDArray.push_back(0);
		} else {
			IDArray.push_back(i+1);
		}
		IFArray.push_back(IDArray);

		// 側面
		IDArray.clear();
		IDArray.push_back(2*argDiv+i);
		if(i == argDiv - 1) {
			IDArray.push_back(argDiv);
		} else {
			IDArray.push_back(argDiv+i+1);
		}
		IDArray.push_back(argDiv+i);
		IFArray.push_back(IDArray);
	}
	
	MakeMesh(&vecArray, &IFArray);

	return;
}

void fk_IndexFaceSet::setConeDivide(int argDiv)
{
	double	rad, height;
	int	    id = vertexPosition.getSize() - 2;

	rad = vertexPosition.getV(0).x;
	height = -vertexPosition.getV(id).z;

	makeCone(argDiv, rad, height);
}

void fk_IndexFaceSet::setConeRadius(double argRadius)
{
	int			div;
	double		theta;
	fk_Vector	vec;

	div = (vertexPosition.getSize()-1)/3;
	for(int i = 0; i < div; ++i) {
		theta = (double(i*2) * FK_PI)/double(div);
		vec.set(cos(theta) * argRadius, sin(theta) * argRadius, 0.0);
		moveVPosition(i, vec);
		moveVPosition(div+i, vec);
	}

	return;
}

void fk_IndexFaceSet::setConeHeight(double argHeight)
{
	fk_Vector	vec(0.0, 0.0, -argHeight);
	int 		div = (vertexPosition.getSize()-1)/3;

	for(int i = 2*div; i < 3*div; ++i) moveVPosition(i, vec);

	return;
}

void fk_IndexFaceSet::MakeCapsuleVec(vector<fk_Vector> *argVec, int argDiv, 
									 double argLen, double argRad)
{
	_st					div = _st(argDiv);
	_st					i, j, index1;
	vector<double>		xy_radius;
	double				theta1, theta2;
	double				len = argLen/2.0;

	argVec->resize(div*div * 8 + 2);
	xy_radius.resize(div*2);

	for(i = 0; i < div; ++i) {
		xy_radius[i] = argRad*sin(double(i+1)*FK_PI/double(div*2));
		xy_radius[(2*div-1) - i] = xy_radius[i];
	}

	argVec->front().set(0.0, 0.0, argRad+len);
	argVec->back().set(0.0, 0.0, -(argRad+len));

	for(i = 0; i < div; ++i) {
		for(j = 0; j < div*4; ++j) {
			index1 = i*div*4 + j + 1;
			theta1 = double(j)*FK_PI/double(div*2);
			theta2 = double(i+1)*FK_PI/double(div*2);
			argVec->at(index1).set(xy_radius[i] * cos(theta1),
								   xy_radius[i] * sin(theta1),
								   argRad * cos(theta2) + len);

		}
	}

	for(i = div; i < div*2; ++i) {
		for(j = 0; j < div*4; ++j) {
			index1 = i*div*4 + j + 1;
			theta1 = double(j)*FK_PI/double(div*2);
			theta2 = double(i)*FK_PI/double(div*2);
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
/*
	// TOP
	for(i = 0; i < argDiv*4; ++i) {
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
	for(i = 0; i < argDiv*4; ++i) {
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
	for(i = 0; i < argDiv*2 - 1; ++i) {
		for(j = 0; j < argDiv*4; ++j) {
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
*/
	// TOP
	for(i = 0; i < argDiv*4; ++i) {
		IDArray.clear();
		IDArray.push_back(0);
		IDArray.push_back(i+1);
		if(i == argDiv*4 - 1) {
			IDArray.push_back(1);
		} else {
			IDArray.push_back(i+2);
		}
		argIF->push_back(IDArray);
	}

	// BOTTOM
	index1 = (argDiv*4)*(argDiv*2 - 1) + 1;
	for(i = 0; i < argDiv*4; ++i) {
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
	for(i = 0; i < argDiv*2 - 1; ++i) {
		for(j = 0; j < argDiv*4; ++j) {
			IDArray.clear();
			index1 = i*argDiv*4 + j + 1;
			index2 = (j == argDiv*4 - 1) ? i*argDiv*4 + 1 : index1 + 1;
			int index3 = index1 + argDiv*4;
			int index4 = index2 + argDiv*4;

			IDArray.push_back(index1);
			IDArray.push_back(index3);
			IDArray.push_back(index4);
			IDArray.push_back(index2);
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

	div = int(sqrt(double(vertexPosition.getSize())/8.0));
	MakeCapsuleVec(&vecArray, div, argLen, argRad);
	for(i = 0; i < _st(vertexPosition.getSize()); ++i) {
		moveVPosition(int(i), vecArray[i]);
	}

	return;
}

void fk_IndexFaceSet::putSolid(fk_Solid *argSolid)
{
	vector<fk_Vector>	vArray;
	vector<int>			tmpIDArray;

	if(argSolid == nullptr) return;

	vArray.resize(_st(vertexPosition.getSize()));
	for(_st i = 0; i < _st(vertexPosition.getSize()); ++i) vArray[i] = vertexPosition.getV(int(i));

	tmpIDArray.resize(faceIndex.size());
	for(_st i = 0; i < faceIndex.size(); ++i) tmpIDArray[i] = int(faceIndex[i]);

	argSolid->makeIFSet(int(faceIndex.size())/3, 3, &tmpIDArray[0],
						vertexPosition.getSize(), &vArray[0]);

	return;
}

fk_D3DXAnimation * fk_IndexFaceSet::GetAnimation(void)
{
	if(anim == nullptr) anim = new fk_D3DXAnimation;
	return anim;
}

void fk_IndexFaceSet::setAnimationTime(double argTime)
{
	if(anim == nullptr) return;

	if(vertexPosition.getSize() != timeOrgPosition.getSize()) {
		timeOrgPosition = vertexPosition;
	}

	anim->SetTime(argTime);

	for(int i = 0; i < vertexPosition.getSize(); ++i) {
		moveVPosition(i, anim->GetMovePos(i, timeOrgPosition.getV(i)));
	}

	return;
}

void fk_IndexFaceSet::setBVHMotion(fk_BVHBase *argBVH)
{
	if(anim == nullptr || cloneFlg == true) {
		anim = new fk_D3DXAnimation;
		cloneFlg = false;
	}
	anim->SetBVHMotion(argBVH);
	return;
}

void fk_IndexFaceSet::cloneShape(fk_IndexFaceSet *argIFS)
{
	if(this == argIFS) return;
	if(argIFS == nullptr) return;

	//localPalette = argIFS->localPalette;
	vertexPosition = argIFS->vertexPosition;
	timeOrgPosition = argIFS->timeOrgPosition;
	vertexNormal = argIFS->vertexNormal;
	faceNormal = argIFS->faceNormal;
	faceIndex = argIFS->faceIndex;
	edgeIndex = argIFS->edgeIndex;
	loopStack = argIFS->loopStack;
	vertexNormFlg = argIFS->vertexNormFlg;
	faceNormFlg = argIFS->faceNormFlg;
	modifyList = argIFS->modifyList;

	anim = argIFS->anim;
	orgIFS = argIFS;
	cloneFlg = true;

	argIFS->cloneList.push_back(this);


	return;
}

/////////////////////////////////////////////////////////////////////////////

void fk_IndexFaceSet::EdgeIBOSetup(void)
{
	if(edgeIBO == 0) {
		glGenBuffers(1, &edgeIBO);
		edgeIndexFlg = true;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeIBO);
	if(edgeIndexFlg == true) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 GLsizei(edgeIndex.size()*sizeof(GLuint)),
					 &edgeIndex[0], GL_STATIC_DRAW);
		edgeIndexFlg = false;
	}
}

void fk_IndexFaceSet::FaceIBOSetup(void)
{
	if(faceIBO == 0) {
		glGenBuffers(1, &faceIBO);
		faceIndexFlg = true;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceIBO);
	if(faceIndexFlg == true) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 GLsizei(faceIndex.size()*sizeof(GLuint)),
					 &faceIndex[0], GL_STATIC_DRAW);
		faceIndexFlg = false;
	}
}

void fk_IndexFaceSet::forceUpdateAttr(void)
{
	fk_Shape::forceUpdateAttr();
	edgeIndexFlg = true;
	faceIndexFlg = true;
}

void fk_IndexFaceSet::updateAttr(void)
{
	if(vertexPosition.isModify() == true) {
		modifyAttribute(vertexName);
		vertexPosition.reset();
	}

	if(vertexNormal.isModify() == true) {
		modifyAttribute(normalName);
		vertexNormal.reset();
	}
}
/////////////////////////////////////////////////////////////////////////////

void fk_IndexFaceSet::DataPrint(void)
{
	stringstream	ss;
	fk_Vector		p, n;
	
	for(int i = 0; i < vertexPosition.getSize(); ++i) {
		p = vertexPosition.getV(i);
		n = vertexNormal.getV(i);
		ss.clear();
		ss << "(p, n)[" << i << "] = (";
		ss << p.x << ", " << p.y << ", " << p.z << "), (";
		ss << n.x << ", " << n.y << ", " << n.z << ")" << endl;
	}

	for(_st i = 0; i < faceIndex.size()/3; ++i) {
		ss.clear();
		ss << "ifs[" << i << "] = {";
		ss << faceIndex[i*3] << ", ";
		ss << faceIndex[i*3+1] << ", ";
		ss << faceIndex[i*3+2] << "}" << endl;
	}

	for(_st i = 0; i < edgeIndex.size()/2; ++i) {
		ss.clear();
		ss << "edge[" << i << "] = {";
		ss << edgeIndex[2*i] << ", ";
		ss << edgeIndex[2*i+1] << "}" << endl;
	}
	fk_PutError(ss.str());

	return;
}
