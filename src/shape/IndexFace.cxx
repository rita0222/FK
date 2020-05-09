#define FK_DEF_SIZETYPE
#include <algorithm>
#include <FK/IndexFace.h>
#include <FK/EdgePair.H>
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

constexpr static double vParam[8][3] = {
	{0.5, 0.5, 0.5},
	{-0.5, 0.5, 0.5},
	{0.5, -0.5, 0.5},
	{-0.5, -0.5, 0.5},
	{0.5, 0.5, -0.5},
	{-0.5, 0.5, -0.5},
	{0.5, -0.5, -0.5},
	{-0.5, -0.5, -0.5}
};

constexpr static int vertexTable[6][4] = {
	{0, 1, 3, 2}, {4, 6 ,7, 5},
	{2, 6, 4, 0}, {1, 5, 7, 3},
	{0, 4, 5, 1}, {2, 3, 7, 6}
};

fk_IndexFaceSet::Member::Member(void) :
	cloneFlg(false), orgIFS(nullptr), edgeIBO(0), faceIBO(0)
{
	return;
}

fk_IndexFaceSet::fk_IndexFaceSet(void) : _m(make_unique<Member>())
{
	SetObjectType(fk_Type::INDEXFACESET);
	realType = fk_RealShapeType::IFS;

	Init();

	setShaderAttribute(vertexName, 3, _m->vertexPosition.getP());
	setShaderAttribute(normalName, 3, _m->vertexNormal.getP());

	return;
}

fk_IndexFaceSet::~fk_IndexFaceSet()
{
	if(_m->cloneFlg == true) {
		_m->orgIFS->_m->cloneList.remove(this);
	}

	DeleteCloneLink(this);
	if(_m->edgeIBO != 0) DeleteBuffer(_m->edgeIBO);
	if(_m->faceIBO != 0) DeleteBuffer(_m->faceIBO);
	return;
}

void fk_IndexFaceSet::DeleteCloneLink(fk_IndexFaceSet *argIFS)
{
	argIFS->_m->anim.reset();
	argIFS->_m->cloneFlg = false;
	argIFS->_m->orgIFS = nullptr;

	for(auto ifset : argIFS->_m->cloneList) {
		DeleteCloneLink(ifset);
	}
	argIFS->_m->cloneList.clear();
	return;
}

void fk_IndexFaceSet::Init(void)
{
	// 各データを一旦解放
	_m->vertexPosition.clear();
	_m->vertexNormal.clear();
	_m->faceNormal.clear();
	_m->faceIndex.clear();
	_m->edgeIndex.clear();
	_m->loopStack.clear();
	_m->vertexNormFlg.clear();
	_m->faceNormFlg.clear();
	_m->modifyList.clear();
	_m->cloneList.clear();

	_m->edgeIndexFlg = true;
	_m->faceIndexFlg = true;

	_m->smoothMode = true;

	return;
}

bool fk_IndexFaceSet::MakeMesh(vector<fk_Vector> *vData,
							   vector< vector<int> > *lIndex, bool)
{
	_st i, j;

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
		_m->vertexPosition.push(vData->at(i));
		//vertexNormFlg.push_back(char(true));
	}

	// 面データのコピー
	for(i = 0; i < lIndex->size(); ++i) {
		if((*lIndex)[i].size() == 3) {
			for(j = 0; j < 3; ++j) {
				_m->faceIndex.push_back(GLuint((*lIndex)[i][j]));
			}
		} else {
			_m->faceIndex.push_back(GLuint((*lIndex)[i][0]));
			_m->faceIndex.push_back(GLuint((*lIndex)[i][1]));
			_m->faceIndex.push_back(GLuint((*lIndex)[i][2]));
			_m->faceIndex.push_back(GLuint((*lIndex)[i][2]));
			_m->faceIndex.push_back(GLuint((*lIndex)[i][3]));
			_m->faceIndex.push_back(GLuint((*lIndex)[i][0]));
		}
	}

	MakeEdgeSet(lIndex);
	ModifyVertexNorm();

	_m->faceIndexFlg = true;

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
	vector<vector<int>> tmpIFS;
	vector<int> tmpLoop;
	vector<vector<int>> *ifsP;

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

	_m->faceNormal.resize(int(_m->faceIndex.size())/3);
	_m->faceNormFlg.resize(_m->faceIndex.size()/3);

	fill(_m->faceNormFlg.begin(), _m->faceNormFlg.end(), char(true));

	for(i = 0; i < _m->faceNormal.getSize(); ++i) {
		MakeFaceNorm(i);
	}

	ResetFaceFlg();
	return;
}

void fk_IndexFaceSet::ModifyFaceNorm(void)
{
	// 形状が定義されていない場合
	if(_m->faceIndex.empty() == true) return;

	// まだ面法線配列が生成されていない場合
	if(_m->faceNormal.getSize() == 0) {
		InitFaceNorm();
	}

	// 頂点の面接続テーブルが生成されていない場合, テーブルを生成する。
	if(_m->loopStack.empty() == true) {
		MakeLoopTable();
	}

	// modifyList に従って処理
	for(_st i = 0; i < _m->modifyList.size(); ++i) {
		_st vID = _st(_m->modifyList[i]);
		for(_st j = 0; j < _m->loopStack[vID].size(); ++j) {
			MakeFaceNorm(_m->loopStack[vID][j]);
		}
	}

	ResetFaceFlg();
	_m->modifyList.clear();

	return;
}

void fk_IndexFaceSet::MakeFaceNorm(int argID)
{
	_st id = _st(argID);

	if(_m->faceNormFlg[id] == char(false)) return;

	fk_FVector v = CalcTriNorm(&_m->faceIndex[id*3]);
	_m->faceNormal.set(argID, v);
	_m->faceNormFlg[id] = char(false);

	if(_m->vertexNormal.getSize() != 0) {
		for(_st j = id*3; j < id*3 + 3; ++j) {
			_m->vertexNormFlg[_m->faceIndex[j]] = char(true);
		}
	}
	
	return;
}

void fk_IndexFaceSet::ResetFaceFlg(void)
{
	fill(_m->faceNormFlg.begin(), _m->faceNormFlg.end(), char(true));
	return;
}

void fk_IndexFaceSet::InitVertexNorm(void)
{
	if(_m->faceNormal.getSize() == 0) InitFaceNorm();

	_m->vertexNormal.resize(_m->vertexPosition.getSize());
	_m->vertexNormFlg.resize(_st(_m->vertexPosition.getSize()));
	fill(_m->vertexNormFlg.begin(), _m->vertexNormFlg.end(), char(true));
	return;
}

void fk_IndexFaceSet::ModifyVertexNorm(void)
{
	// 形状が定義されていない場合
	if(_m->faceIndex.empty()) return;

	// まだ頂点法線配列が生成されていない場合
	if(_m->vertexNormal.getSize() == 0) {
		InitVertexNorm();
	}

	// 面法線情報を再計算
	ModifyFaceNorm();

	fk_Vector norm;
	for(_st i = 0; i < _st(_m->vertexPosition.getSize()); ++i) {
		if(_m->vertexNormFlg[i] == char(true)) {
			norm.init();
			for(_st j = 0; j < _m->loopStack[i].size(); ++j) {
				norm += _m->faceNormal.getV(_m->loopStack[i][j]);
			}
			norm.normalize();
			_m->vertexNormal.set(int(i), norm);
			_m->vertexNormFlg[i] = char(false);
		}
	}

	return;
}

fk_FVector fk_IndexFaceSet::CalcTriNorm(GLuint *argIF)
{
	_st i;
	fk_Vector retNorm;
	fk_Vector triV[3];

	for(i = 0; i < 3; ++i) {
		triV[i] = _m->vertexPosition.getV(int(argIF[i]));
	}

	retNorm = (triV[1] - triV[0]) ^ (triV[2] - triV[1]);
	retNorm.normalize();
	return retNorm;
}

fk_FVector fk_IndexFaceSet::CalcPolyNorm(int argNum, int *argIF)
{
	vector<fk_Vector> posArray, normArray;
	_st i;
	fk_Vector tmpVec, sumNorm;

	posArray.clear();
	normArray.clear();

	if(argNum < 4) return sumNorm;
	for(i = 0; i < _st(argNum); ++i) {
		tmpVec = _m->vertexPosition.getV(argIF[i]);
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
	_st i, j, vID;

	_m->loopStack.clear();
	_m->loopStack.resize(_st(_m->vertexPosition.getSize()));

	for(i = 0; i < _m->faceIndex.size()/3; ++i) {
		for(j = 0; j < 3; ++j) {
			vID = _m->faceIndex[i*3 + j];
			_m->loopStack[vID].push_back(int(i));
		}
	}

	return;
}

void fk_IndexFaceSet::MakeEdgeSet(vector< vector<int> > *argLoop)
{
	fk_HeapBase<fk_EdgePair> edgeHeap;
	vector<fk_EdgePair> edgeArray;
	_st i, j;
	int id1, id2;
	vector<char> edgeFlg;

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
	
	_m->edgeIndex.clear();
	for(i = 0; i < edgeArray.size(); ++i) {
		if(edgeFlg[i] == char(true)) {
			_m->edgeIndex.push_back(GLuint(edgeArray[i].id[0]));
			_m->edgeIndex.push_back(GLuint(edgeArray[i].id[1]));
		}
	}
	_m->edgeIndexFlg = true;

	return;
}


int fk_IndexFaceSet::getPosSize(void)
{
	return _m->vertexPosition.getSize();
}

int fk_IndexFaceSet::getEdgeSize(void)
{
	return int(_m->edgeIndex.size()/2);
}

int fk_IndexFaceSet::getFaceSize(void)
{
	return int(_m->faceIndex.size()/3);
}

fk_Vector fk_IndexFaceSet::getPosVec(int argID)
{
	fk_Vector retVec(0.0, 0.0, 0.0);

	if(argID < 0 || argID >= _m->vertexPosition.getSize()) return retVec;
	return _m->vertexPosition.getV(argID);
}

vector<int> fk_IndexFaceSet::getFaceData(int argID)
{
	vector<int> retIF;

	if(argID < 0 || argID >= int(_m->faceIndex.size()/3)) return retIF;

	_st id = _st(argID)*3;

	retIF.push_back(int(_m->faceIndex[id]));
	retIF.push_back(int(_m->faceIndex[id+1]));
	retIF.push_back(int(_m->faceIndex[id+2]));

	return retIF;
}

int fk_IndexFaceSet::getFaceData(int argFID, int argVID)
{
	if(argFID < 0 || argFID >= int(_m->faceIndex.size()/3)) return -1;
	if(argVID < 0 || argVID >= 3) return -1;

	return int(_m->faceIndex[_st(argFID) * 3 + _st(argVID)]);
}

bool fk_IndexFaceSet::moveVPosition(int argID,
									const fk_Vector &argPos, int argOrder)
{
	int trueID = argID - argOrder;

	if(trueID < 0 || trueID >= _m->vertexPosition.getSize()) return false;

	_m->vertexPosition.set(trueID, argPos);
	_m->modifyList.push_back(trueID);
	modifyAttribute(vertexName);
	modifyAttribute(normalName);

	return true;
}

bool fk_IndexFaceSet::moveVPosition(int argID,
									double argX, double argY, double argZ,
									int argOrder)
{
	int trueID = argID - argOrder;

	if(trueID < 0 || trueID >= _m->vertexPosition.getSize()) return false;

	_m->vertexPosition.set(trueID, argX, argY, argZ);
	_m->modifyList.push_back(trueID);
	modifyAttribute(vertexName);
	modifyAttribute(normalName);

	return true;
}

bool fk_IndexFaceSet::moveVPosition(int argID, double *argPos, int argOrder)
{
	int trueID = argID - argOrder;

	if(trueID < 0 || trueID >= _m->vertexPosition.getSize()) return false;

	_m->vertexPosition.set(trueID, argPos[0], argPos[1], argPos[2]);
	_m->modifyList.push_back(trueID);
	modifyAttribute(vertexName);
	modifyAttribute(normalName);

	return true;
}

fk_Vector fk_IndexFaceSet::getFaceNorm(int argPID, int argOrder)
{
	int trueID = argPID - argOrder;

	if(trueID < 0 || trueID >= _m->faceNormal.getSize()) {
		return fk_Vector(0.0, 0.0, 0.0);
	}

	return _m->faceNormal.getV(trueID);
}

fk_Vector fk_IndexFaceSet::getPNorm(int argPID, int argOrder)
{
	return getFaceNorm(argPID, argOrder);
}

bool fk_IndexFaceSet::setFaceNorm(int argPID, const fk_Vector &argVec, int argOrder)
{
	int trueID = argPID - argOrder;

	if(trueID < 0 || trueID >= _m->faceNormal.getSize()) return false;
	_m->faceNormal.set(trueID, argVec);
	modifyAttribute(normalName);
	return true;
}

bool fk_IndexFaceSet::setPNorm(int argPID, const fk_Vector &argVec, int argOrder)
{
	return setFaceNorm(argPID, argVec, argOrder);
}

fk_Vector fk_IndexFaceSet::getVertexNorm(int argVID, int argOrder)
{
	int trueID = argVID - argOrder;

	if(trueID < 0 || trueID >= _m->vertexNormal.getSize()) {
		return fk_Vector(0.0, 0.0, 0.0);
	}

	return _m->vertexNormal.getV(trueID);
}

fk_Vector fk_IndexFaceSet::getVNorm(int argVID, int argOrder)
{
	return getVertexNorm(argVID, argOrder);
}

bool fk_IndexFaceSet::setVertexNorm(int argVID, const fk_Vector &argVec, int argOrder)
{
	int trueID = argVID - argOrder;

	if(trueID < 0 || trueID >= _m->vertexNormal.getSize()) return false;
	_m->vertexNormal.set(trueID, argVec);
	modifyAttribute(normalName);

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
	unique_ptr<fk_SMFParser> smfParser(new fk_SMFParser());

	smfParser->SetMeshData(this);
	return smfParser->ReadSMFFile(argFileName);
}

bool fk_IndexFaceSet::readSTLFile(string argFileName,
								  bool argSolidFlag, double argEPS)
{
	unique_ptr<fk_STLParser> stlParser(new fk_STLParser());

	stlParser->SetMeshData(this);
	return stlParser->ReadSTLFile(argFileName, argSolidFlag, argEPS);
}

bool fk_IndexFaceSet::readHRCFile(string argFileName)
{
	unique_ptr<fk_HRCParser> hrcParser(new fk_HRCParser());

	hrcParser->SetMeshData(this);
	return hrcParser->ReadHRCFile(argFileName);
}

bool fk_IndexFaceSet::readRDSFile(string argFileName, bool argSolidFlg)
{
	unique_ptr<fk_RDSParser> rdsParser(new fk_RDSParser());

	rdsParser->SetMeshData(this);
	return rdsParser->ReadRDSFile(argFileName, argSolidFlg);
}

bool fk_IndexFaceSet::readDXFFile(string argFileName, bool argSolidFlg)
{
	unique_ptr<fk_DXFParser> dxfParser(new fk_DXFParser());

	dxfParser->SetMeshData(this);
	return dxfParser->ReadDXFFile(argFileName, argSolidFlg);
}

bool fk_IndexFaceSet::readVRMLFile(string argFileName,
								   bool argMaterialFlag, bool argSolidFlag)
{
	unique_ptr<fk_VRMLParser> vrmlParser(new fk_VRMLParser());

	vrmlParser->SetMeshData(this);
	return vrmlParser->ReadVRMLFile(argFileName, argMaterialFlag, argSolidFlag);
}


bool fk_IndexFaceSet::readMQOFile(string argFileName,
								  string argObjName,
								  bool argSolidFlg,
								  bool argContFlg,
								  bool argMatFlg)
{
	return readMQOFile(argFileName, argObjName, -1, argSolidFlg, argContFlg, argMatFlg);
}

bool fk_IndexFaceSet::readMQOFile(string argFileName,
								  string argObjName,
								  int argMateID,
								  bool argSolidFlg,
								  bool argContFlg,
								  bool argMatFlg)
{
	unique_ptr<fk_MQOParser> mqoParser(new fk_MQOParser());
	mqoParser->SetMeshData(this);
	mqoParser->SetContMode(argContFlg);
	mqoParser->SetMaterialMode(argMatFlg);
	return mqoParser->ReadMQOFile(argFileName, argObjName, argMateID, argSolidFlg);
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
	unique_ptr<fk_MQOParser> mqoParser(new fk_MQOParser());

	mqoParser->SetMeshData(this);
	mqoParser->SetContMode(argContFlg);
	mqoParser->SetMaterialMode(argMatFlg);
	return mqoParser->ReadMQOData(argBuffer, argObjName, argMateID, argSolidFlg);
}

bool fk_IndexFaceSet::readD3DXFile(string argFileName, string argObjName,
								   bool argSolidFlg)
{
	return readD3DXFile(argFileName, argObjName, -1, argSolidFlg);
}

bool fk_IndexFaceSet::readD3DXFile(string argFileName, string argObjName,
								   int argTexID, bool argSolidFlg)
{
	unique_ptr<fk_D3DXParser> d3dxParser(new fk_D3DXParser());
	bool retFlg, animFlg;

	if(_m->anim == nullptr || _m->cloneFlg == true) {
		_m->anim = make_shared<fk_D3DXAnimation>();
	}
	d3dxParser->SetMeshData(this);
	d3dxParser->SetAnimation(_m->anim.get());
	retFlg = d3dxParser->ReadD3DXFile(argFileName, argObjName,
									  argTexID, argSolidFlg, &animFlg);
	if(animFlg == true) setAnimationTime(-1.0);
	return retFlg;
}

bool fk_IndexFaceSet::writeVRMLFile(string argFileName,
									fk_Material *argMaterial, bool triFlag)
{
	unique_ptr<fk_VRMLOut> vrmlOut(new fk_VRMLOut(this));
	return vrmlOut->WriteVRMLFile(argFileName, argMaterial, triFlag);
}

bool fk_IndexFaceSet::writeVRMLFile(string argFileName,
									vector<double> *argTime,
									vector<fk_Vector> *argPos,
									fk_Material *argMaterial,
									bool argTriFlg)
{
	unique_ptr<fk_VRMLOut> vrmlOut(new fk_VRMLOut(this));
	return vrmlOut->WriteVRMLFile(argFileName, argTime, argPos, argMaterial, argTriFlg);
}

bool fk_IndexFaceSet::writeSTLFile(string argFileName)
{
	unique_ptr<fk_STLOut> stlOut(new fk_STLOut(this));
	return stlOut->WriteSTLFile(argFileName);
}

bool fk_IndexFaceSet::writeDXFFile(string argFileName, bool argTriFlg)
{
	unique_ptr<fk_DXFOut> dxfOut(new fk_DXFOut(this));
	return dxfOut->WriteDXFFile(argFileName, argTriFlg);
}

bool fk_IndexFaceSet::writeMQOFile(string argFileName)
{
	unique_ptr<fk_MQOOut> mqoOut(new fk_MQOOut(this));
	return mqoOut->WriteMQOFile(argFileName);
}

void fk_IndexFaceSet::makePolygon(vector<fk_Vector> *argArray)
{
	if(argArray == nullptr) return;

	fk_Vector center;
	vector<int> loop;
	vector<vector<int>> ifs;
	vector<fk_Vector> array = *argArray;

	_st vSize = argArray->size();

	for(auto &v : array) center += v;
	center /= double(vSize);
	array.push_back(center);

	for(int i = 0; i < int(vSize); i++) {
		int id0 = i;
		int id1 = (i == int(vSize - 1)) ? 0 : i+1;
		loop.clear();
		loop.push_back(int(vSize));
		loop.push_back(id0);
		loop.push_back(id1);
		ifs.push_back(loop);
	}
	MakeMesh(&array, &ifs);
}

void fk_IndexFaceSet::makePolygon(int argNum, fk_Vector *argArray)
{
	fk_Vector center;
	vector<int> loop;
	vector< vector<int> > ifs;
	vector<fk_Vector> array;

	for(int i = 0; i < argNum; ++i) array.push_back(argArray[i]);
	_st vSize = array.size();

	for(auto &v : array) center += v;
	center /= double(vSize);
	array.push_back(center);

	for(int i = 0; i < int(vSize); i++) {
		int id0 = i;
		int id1 = (i == int(vSize - 1)) ? 0 : i+1;
		loop.clear();
		loop.push_back(int(vSize));
		loop.push_back(id0);
		loop.push_back(id1);
		ifs.push_back(loop);
	}
	MakeMesh(&array, &ifs);
}


void fk_IndexFaceSet::makeBlock(double argX, double argY, double argZ)
{
	vector<fk_Vector> pos;
	vector<int> loop;
	vector<vector<int>> ifs;

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
	fk_Vector pos;

	for(int i = 0; i < 6; ++i) {
		for (int j = 0; j < 4; j++) {
			pos.x = vParam[vertexTable[i][j]][0] * argX;
			pos.y = vParam[vertexTable[i][j]][1] * argY;
			pos.z = vParam[vertexTable[i][j]][2] * argZ;
			moveVPosition(i*4+j, pos);
		}
	}

	return;
}

void fk_IndexFaceSet::setBlockSize(double argSize, fk_Axis argAxis)
{
	fk_Vector pos = _m->vertexPosition.getV(0);
	pos.x = fabs(pos.x) * 2.0;
	pos.y = fabs(pos.y) * 2.0;
	pos.z = fabs(pos.z) * 2.0;
	switch(argAxis) {
	  case fk_Axis::X:
		pos.x = argSize;
		break;
		
	  case fk_Axis::Y:
		pos.y = argSize;
		break;
		
	  case fk_Axis::Z:
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
	fk_Vector pos = _m->vertexPosition.getV(0);
	pos.x = fabs(pos.x) * 2.0;
	pos.y = fabs(pos.y) * 2.0;
	pos.z = fabs(pos.z) * 2.0;
	switch(argAxis) {
	  case fk_Axis::X:
		pos.x *= argScale;
		break;
		
	  case fk_Axis::Y:
		pos.y *= argScale;
		break;
		
	  case fk_Axis::Z:
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
	fk_Vector pos = _m->vertexPosition.getV(0);
	pos.x = fabs(pos.x) * 2.0 * argX;
	pos.y = fabs(pos.y) * 2.0 * argY;
	pos.z = fabs(pos.z) * 2.0 * argZ;
	setBlockSize(pos.x, pos.y, pos.z);
	return;
}

void fk_IndexFaceSet::makeCircle(int argDiv, double argRadius)
{
	vector<fk_Vector> vecArray;
	vector<int> IDArray;
	vector<vector<int>> IFArray;
	double theta;

	vecArray.resize(_st(argDiv)*4 + 1);
	vecArray[_st(argDiv)*4].set(0.0, 0.0, 0.0);

	for(int i = 0; i < 4 * argDiv; ++i) {
		theta = (double(i) * fk_Math::PI)/(double(argDiv) * 2.0);
		vecArray[_st(i)].set(cos(theta) * argRadius,
							 sin(theta) * argRadius, 0.0);
	}

	IFArray.clear();

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
	makeCircle(argDiv, _m->vertexPosition.getV(0).x);

	return;
}

void fk_IndexFaceSet::setCircleRadius(double argRadius)
{
	double scale;
	fk_Vector V;

	scale = argRadius/_m->vertexPosition.getV(0).x;

	for(int i = 0; i < _m->vertexPosition.getSize()-1; ++i) {
		V = _m->vertexPosition.getV(i);
		moveVPosition(i, V.x*scale, V.y*scale, 0.0);
	}

	return;
}

void fk_IndexFaceSet::setCircleScale(double argScale)
{
	fk_Vector V;

	for(int i = 0; i < _m->vertexPosition.getSize()-1; ++i) {
		V = _m->vertexPosition.getV(i);
		moveVPosition(i, V.x * argScale, V.y * argScale, 0.0);
	}

	return;
}

void fk_IndexFaceSet::makeSphere(int argDiv, double argRadius)
{
	vector<fk_Vector> vecArray;
	vector<int> IDArray;
	vector<vector<int>> IFArray;
	_st i, j, index, div;
	int ii, jj;
	int iindex1, iindex2, iindex3, iindex4;
	vector<double> xz_radius;
	double theta1, theta2;

	div = _st(argDiv);
	vecArray.resize(div*4 * (div*2 - 1) + 2);
	xz_radius.resize(div*2 - 1);

	for(i = 0; i < div*2 - 1; ++i) {
		xz_radius[i] = argRadius*sin(double(i+1)*fk_Math::PI/double(div*2));
	}

	vecArray.front().set(0.0, argRadius, 0.0);
	vecArray.back().set(0.0, -argRadius, 0.0);

	for(i = 0; i < div*2 - 1; ++i) {
		for(j = 0; j < div*4; ++j) {
			index = i*div*4 + j + 1;
			theta1 = double(j)*fk_Math::PI/double(div*2);
			theta2 = double(i+1)*fk_Math::PI/double(div*2);
			vecArray[index].set(xz_radius[i] * cos(theta1),
								argRadius * cos(theta2),
								xz_radius[i] * sin(theta1));
		}
	}

	IFArray.clear();

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
	makeSphere(argDiv, _m->vertexPosition.getV(0).y);
	return;
}

void fk_IndexFaceSet::setSphereRadius(double argRadius)
{
	double scale = argRadius/_m->vertexPosition.getV(0).y;

	for(int i = 0; i < _m->vertexPosition.getSize(); ++i) {
		moveVPosition(i, _m->vertexPosition.getV(i) * scale);
	}

	return;
}

void fk_IndexFaceSet::setSphereScale(double argScale)
{
	for(int i = 0; i < _m->vertexPosition.getSize(); ++i) {
		moveVPosition(i, _m->vertexPosition.getV(i) * argScale);
	}

	return;
}

void fk_IndexFaceSet::makePrism(int argDiv, double argTop, double argBottom,
								double argHeight, bool argSmoothMode)
{
	fk_IFSetHandle IFSet;
	vector<fk_Vector> vecArray;
	vector<int> IDArray;
	vector<vector<int>> IFArray;

	_m->smoothMode = argSmoothMode;
	_st div = _st(argDiv);
	_st vSize = (_m->smoothMode == true) ? 4 * div + 2 : 6 * div + 2;
	vecArray.resize(vSize);

	// 底面中心
	vecArray[vSize - 2].set(0.0, 0.0, 0.0);

	// 上面中心
	vecArray[vSize - 1].set(0.0, 0.0, -argHeight);

	for(_st j = 0; j < div; ++j) {
		double theta = (double(j*2) * fk_Math::PI)/double(div);

		// 底面
		vecArray[j].set(cos(theta) * argBottom,
						sin(theta) * argBottom, 0.0);

		// 上面
		vecArray[div+j].set(cos(theta) * argTop,
							sin(theta) * argTop, -argHeight);

		// 側面底側
		vecArray[2*div+j] = vecArray[j];
		if(_m->smoothMode == false) vecArray[4*div+j] = vecArray[j];

		// 側面上側
		vecArray[3*div+j] = vecArray[div+j];
		if(_m->smoothMode == false) vecArray[5*div+j] = vecArray[div+j];
	}

	IFArray.clear();

	int margin = (_m->smoothMode == true) ? 0 : argDiv * 2;
	for(_st j = 0; j < div; ++j) {
		int i = int(j);
		// 底面
		IDArray.clear();
		IDArray.push_back(int(vSize - 2));
		IDArray.push_back(i);
		if(i == argDiv - 1) {
			IDArray.push_back(0);
		} else {
			IDArray.push_back(i+1);
		}
		IFArray.push_back(IDArray);

		// 上面
		IDArray.clear();
		IDArray.push_back(int(vSize - 1));
		if(i == argDiv-1) {
			IDArray.push_back(argDiv);
		} else {
			IDArray.push_back(argDiv+i+1);
		}
		IDArray.push_back(argDiv+i);
		IFArray.push_back(IDArray);

		// 側面
		int id_d_0, id_d_1, id_u_0, id_u_1;

		id_d_0 = 2*argDiv + i;
		id_d_1 = 2*argDiv + i + 1 + margin;
		id_u_0 = 3*argDiv + i;
		id_u_1 = 3*argDiv + i + 1 + margin;
		if(i == argDiv - 1) {
			id_d_1 -= argDiv;
			id_u_1 -= argDiv;
		}
		
		IDArray.clear();
		IDArray.push_back(id_d_0);
		IDArray.push_back(id_u_0);
		IDArray.push_back(id_u_1);
		IDArray.push_back(id_d_1);
		IFArray.push_back(IDArray);
	}
	MakeMesh(&vecArray, &IFArray);

	return;
}

void fk_IndexFaceSet::setPrismDivide(int argDiv)
{
	int div;
	double top, bottom, height;

	if((div = (_m->vertexPosition.getSize() - 2)/4) < 3) return;

	top = _m->vertexPosition.getV(2*div).x;
	bottom = _m->vertexPosition.getV(0).x;
	height = -_m->vertexPosition.getV(2*div).z;

	makePrism(argDiv, top, bottom, height, _m->smoothMode);
	return;
}

void fk_IndexFaceSet::setPrismTopRadius(double argTop)
{
	int div;
	int i;
	double theta, z;
	fk_Vector vec;

	int vSize = _m->vertexPosition.getSize();
	div = (_m->smoothMode == true) ? (vSize - 2)/4 : (vSize - 2)/6;
	z = _m->vertexPosition.getV(vSize-1).z;
	for(i = 0; i < div; ++i) {
		theta = double(i) * 2.0 * fk_Math::PI/double(div);
		vec.set(cos(theta) * argTop, sin(theta) * argTop, z);
		moveVPosition(div+i, vec);
		moveVPosition(3*div+i, vec);
		if(_m->smoothMode == false) moveVPosition(5*div+i, vec);
	}

	return;
}

void fk_IndexFaceSet::setPrismBottomRadius(double argBottom)
{
	int div;
	int i;
	double theta;
	fk_Vector vec;

	int vSize = _m->vertexPosition.getSize();
	div = (_m->smoothMode == true) ? (vSize - 2)/4 : (vSize - 2)/6;
	for(i = 0; i < div; ++i) {
		theta = double(i) * 2.0 * fk_Math::PI/double(div);
		vec.set(cos(theta) * argBottom, sin(theta) * argBottom, 0.0);
		moveVPosition(i, vec);
		moveVPosition(2*div+i, vec);
		if(_m->smoothMode == false) moveVPosition(4*div+i, vec);
	}

	return;
}

void fk_IndexFaceSet::setPrismHeight(double argHeight)
{
	int i, div;
	fk_Vector vec;

	int vSize = _m->vertexPosition.getSize();
	div = (_m->smoothMode == true) ? (vSize - 2)/4 : (vSize - 2)/6;
	for(i = 0; i < div; ++i) {
		vec = _m->vertexPosition.getV(div+i);
		vec.z = -argHeight;
		moveVPosition(div+i, vec);
		moveVPosition(3*div+i, vec);
		if(_m->smoothMode == false) moveVPosition(5*div+i, vec);
	}
	vec.set(0.0, 0.0, -argHeight);
	moveVPosition(vSize-1, vec);

	return;
}

void fk_IndexFaceSet::makeCone(int argDiv, double argRadius, double argHeight, bool argSmoothMode)
{
	vector<fk_Vector> vecArray;
	vector<int> IDArray;
	vector<vector<int>> IFArray;
	_st div = _st(argDiv);
	int topID, leftID, rightID, margin;

	_m->smoothMode = argSmoothMode;
	_st centerID = (_m->smoothMode) ? 3*div : 4*div;
	vecArray.resize(centerID+1);
	vecArray[centerID].set(0.0, 0.0, 0.0);

	for(_st i = 0; i < div; ++i) {
		double theta = (double(i*2) * fk_Math::PI)/double(div);
		vecArray[i].set(cos(theta) * argRadius, sin(theta) * argRadius, 0.0);
		vecArray[div+i] = vecArray[i];
		if(_m->smoothMode == true) {
			vecArray[2*div+i].set(0.0, 0.0, -argHeight);
		} else {
			vecArray[2*div+i] = vecArray[i];
			vecArray[3*div+i].set(0.0, 0.0, -argHeight);
		}
	}

	IFArray.clear();

	margin = (_m->smoothMode == true) ? 0 : argDiv;

	for(int i = 0; i < argDiv; ++i) {
		// 底面
		IDArray.clear();
		IDArray.push_back(int(centerID));
		IDArray.push_back(i);
		if(i == argDiv - 1) {
			IDArray.push_back(0);
		} else {
			IDArray.push_back(i+1);
		}
		IFArray.push_back(IDArray);

		// 側面
		topID = 2*argDiv + i + margin;
		leftID = (i == argDiv - 1) ? argDiv + margin : argDiv + i + 1 + margin;
		rightID = argDiv + i;

		IDArray.clear();
		IDArray.push_back(topID);
		IDArray.push_back(leftID);
		IDArray.push_back(rightID);
		IFArray.push_back(IDArray);
	}
	
	MakeMesh(&vecArray, &IFArray);

	return;
}

void fk_IndexFaceSet::setConeDivide(int argDiv)
{
	double rad, height;
	int id = _m->vertexPosition.getSize() - 2;

	rad = _m->vertexPosition.getV(0).x;
	height = -_m->vertexPosition.getV(id).z;

	makeCone(argDiv, rad, height, _m->smoothMode);
}

void fk_IndexFaceSet::setConeRadius(double argRadius)
{
	fk_Vector vec;

	int vSize = _m->vertexPosition.getSize();
	int div = (_m->smoothMode == true) ? (vSize - 1)/3 : (vSize - 1)/4;
	for(int i = 0; i < div; ++i) {
		double theta = double(i) * 2.0 * fk_Math::PI/double(div);
		vec.set(cos(theta) * argRadius, sin(theta) * argRadius, 0.0);
		moveVPosition(i, vec);
		moveVPosition(div+i, vec);
		if(_m->smoothMode == false) moveVPosition(2*div+i, vec);
	}

	return;
}

void fk_IndexFaceSet::setConeHeight(double argHeight)
{
	fk_Vector vec(0.0, 0.0, -argHeight);

	int vSize = _m->vertexPosition.getSize();
	int div = (_m->smoothMode == true) ? (vSize - 1)/3 : (vSize - 1)/4;
	int start = (_m->smoothMode == true) ? 2*div : 3*div;
	int end = (_m->smoothMode == true) ? 3*div : 4*div;

	for(int i = start; i < end; ++i) moveVPosition(i, vec);

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
		xy_radius[i] = argRad*sin(double(i+1)*fk_Math::PI/double(div*2));
		xy_radius[(2*div-1) - i] = xy_radius[i];
	}

	argVec->front().set(0.0, 0.0, argRad+len);
	argVec->back().set(0.0, 0.0, -(argRad+len));

	for(i = 0; i < div; ++i) {
		for(j = 0; j < div*4; ++j) {
			index1 = i*div*4 + j + 1;
			theta1 = double(j)*fk_Math::PI/double(div*2);
			theta2 = double(i+1)*fk_Math::PI/double(div*2);
			argVec->at(index1).set(xy_radius[i] * cos(theta1),
								   xy_radius[i] * sin(theta1),
								   argRad * cos(theta2) + len);

		}
	}

	for(i = div; i < div*2; ++i) {
		for(j = 0; j < div*4; ++j) {
			index1 = i*div*4 + j + 1;
			theta1 = double(j)*fk_Math::PI/double(div*2);
			theta2 = double(i)*fk_Math::PI/double(div*2);
			argVec->at(index1).set(xy_radius[i] * cos(theta1),
								   xy_radius[i] * sin(theta1),
								   argRad * cos(theta2) - len);
		}
	}
	return;
}

void fk_IndexFaceSet::MakeCapsuleIFSet(vector< vector<int> > *argIF, int argDiv)
{
	vector<int> IDArray;
	int i, j, index1, index2;

	argIF->clear();

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
	vector<fk_Vector> vecArray;
	vector<vector<int>> IFArray;

	if(argLen < 0.0) return;

	MakeCapsuleVec(&vecArray, argDiv, argLen, argRad);
	MakeCapsuleIFSet(&IFArray, argDiv);
	MakeMesh(&vecArray, &IFArray);
}

void fk_IndexFaceSet::setCapsuleSize(double argLen, double argRad)
{
	vector<fk_Vector> vecArray;
	int div;
	_st i;

	div = int(sqrt(double(_m->vertexPosition.getSize())/8.0));
	MakeCapsuleVec(&vecArray, div, argLen, argRad);
	for(i = 0; i < _st(_m->vertexPosition.getSize()); ++i) {
		moveVPosition(int(i), vecArray[i]);
	}

	return;
}

void fk_IndexFaceSet::putSolid(fk_Solid *argSolid)
{
	vector<fk_Vector> vArray;
	vector<int> tmpIDArray;

	if(argSolid == nullptr) return;

	vArray.resize(_st(_m->vertexPosition.getSize()));
	for(_st i = 0; i < _st(_m->vertexPosition.getSize()); ++i) {
		vArray[i] = _m->vertexPosition.getV(int(i));
	}

	tmpIDArray.resize(_m->faceIndex.size());
	for(_st i = 0; i < _m->faceIndex.size(); ++i) tmpIDArray[i] = int(_m->faceIndex[i]);

	argSolid->makeIFSet(int(_m->faceIndex.size())/3, 3, &tmpIDArray[0],
						_m->vertexPosition.getSize(), &vArray[0]);

	return;
}

fk_D3DXAnimation * fk_IndexFaceSet::GetAnimation(void)
{
	if(_m->anim == nullptr) _m->anim = make_shared<fk_D3DXAnimation>();
	return _m->anim.get();
}

void fk_IndexFaceSet::setAnimationTime(double argTime)
{
	if(_m->anim == nullptr) return;

	if(_m->vertexPosition.getSize() != _m->timeOrgPosition.getSize()) {
		_m->timeOrgPosition = _m->vertexPosition;
	}

	_m->anim->SetTime(argTime);

	for(int i = 0; i < _m->vertexPosition.getSize(); ++i) {
		moveVPosition(i, _m->anim->GetMovePos(i, _m->timeOrgPosition.getV(i)));
	}

	return;
}

void fk_IndexFaceSet::setBVHMotion(fk_BVHBase *argBVH)
{
	if(_m->anim == nullptr || _m->cloneFlg == true) {
		_m->anim = make_shared<fk_D3DXAnimation>();
		_m->cloneFlg = false;
	}
	_m->anim->SetBVHMotion(argBVH);
	return;
}

void fk_IndexFaceSet::cloneShape(fk_IndexFaceSet *argIFS)
{
	if(this == argIFS) return;
	if(argIFS == nullptr) return;

	//localPalette = argIFS->localPalette;
	_m->vertexPosition = argIFS->_m->vertexPosition;
	_m->timeOrgPosition = argIFS->_m->timeOrgPosition;
	_m->vertexNormal = argIFS->_m->vertexNormal;
	_m->faceNormal = argIFS->_m->faceNormal;
	_m->faceIndex = argIFS->_m->faceIndex;
	_m->edgeIndex = argIFS->_m->edgeIndex;
	_m->loopStack = argIFS->_m->loopStack;
	_m->vertexNormFlg = argIFS->_m->vertexNormFlg;
	_m->faceNormFlg = argIFS->_m->faceNormFlg;
	_m->modifyList = argIFS->_m->modifyList;

	_m->anim = argIFS->_m->anim;
	_m->orgIFS = argIFS;
	_m->cloneFlg = true;

	argIFS->_m->cloneList.push_back(this);


	return;
}

/////////////////////////////////////////////////////////////////////////////

void fk_IndexFaceSet::EdgeIBOSetup(void)
{
	if(_m->edgeIBO == 0) {
		_m->edgeIBO = GenBuffer();
		_m->edgeIndexFlg = true;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _m->edgeIBO);
	if(_m->edgeIndexFlg == true) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 GLsizei(_m->edgeIndex.size()*sizeof(GLuint)),
					 _m->edgeIndex.data(), GL_STATIC_DRAW);
		_m->edgeIndexFlg = false;
	}
}

void fk_IndexFaceSet::FaceIBOSetup(void)
{
	if(_m->faceIBO == 0) {
		_m->faceIBO = GenBuffer();
		_m->faceIndexFlg = true;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _m->faceIBO);
	if(_m->faceIndexFlg == true) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 GLsizei(_m->faceIndex.size()*sizeof(GLuint)),
					 _m->faceIndex.data(), GL_STATIC_DRAW);
		_m->faceIndexFlg = false;
	}
}

void fk_IndexFaceSet::ForceUpdateAttr(void)
{
	fk_Shape::ForceUpdateAttr();
	_m->edgeIndexFlg = true;
	_m->faceIndexFlg = true;
}

void fk_IndexFaceSet::updateAttr(void)
{
	if(_m->vertexPosition.isModify() == true) {
		modifyAttribute(vertexName);
		_m->vertexPosition.reset();
	}

	if(_m->vertexNormal.isModify() == true) {
		modifyAttribute(normalName);
		_m->vertexNormal.reset();
	}
}

vector<float> * fk_IndexFaceSet::GetVertexP(void)
{
	return _m->vertexPosition.getP();
}

vector<float> * fk_IndexFaceSet::GetNormP(void)
{
	return _m->vertexNormal.getP();
}

/////////////////////////////////////////////////////////////////////////////

void fk_IndexFaceSet::DataPrint(void)
{
	stringstream ss;
	fk_Vector p, n;
	
	for(int i = 0; i < _m->vertexPosition.getSize(); ++i) {
		p = _m->vertexPosition.getV(i);
		n = _m->vertexNormal.getV(i);
		ss.clear();
		ss << "(p, n)[" << i << "] = (";
		ss << p.x << ", " << p.y << ", " << p.z << "), (";
		ss << n.x << ", " << n.y << ", " << n.z << ")" << endl;
	}

	for(_st i = 0; i < _m->faceIndex.size()/3; ++i) {
		ss.clear();
		ss << "ifs[" << i << "] = {";
		ss << _m->faceIndex[i*3] << ", ";
		ss << _m->faceIndex[i*3+1] << ", ";
		ss << _m->faceIndex[i*3+2] << "}" << endl;
	}

	for(_st i = 0; i < _m->edgeIndex.size()/2; ++i) {
		ss.clear();
		ss << "edge[" << i << "] = {";
		ss << _m->edgeIndex[2*i] << ", ";
		ss << _m->edgeIndex[2*i+1] << "}" << endl;
	}
	Error::Put(ss.str());

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
