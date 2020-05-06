#define FK_DEF_SIZETYPE
#include <FK/D3DXShapeParser.H>
#include <FK/D3DXData.H>
#include <FK/IFSTexture.h>
#include <FK/Error.H>
#include <deque>
#include <sstream>

using namespace std;
using namespace FK;

fk_D3DXShapeParser::Member::Member(void)
{
	return;
}

fk_D3DXShapeParser::fk_D3DXShapeParser(void) : _m(make_unique<Member>())
{
	return;
}

fk_D3DXShapeParser::~fk_D3DXShapeParser()
{
	return;
}

void fk_D3DXShapeParser::Clear(void)
{
	_m->vData.clear();
	_m->optVData.clear();
	_m->fData.clear();
	_m->optFData.clear();
	_m->tData.clear();
	_m->optTData.clear();
	_m->mData.clear();
	_m->vMapData.clear();

	return;
}

bool fk_D3DXShapeParser::ReadMeshData(fk_TreeData *argData, ifstream &argIFS)
{
	if(SetFrameMatrix(argData) == false) {
		Error::Put("fk_D3DXShapeParser", "ReadMeshData", 1);
		return false;
	}

	if(ReadVectorData(argIFS, fk_D3DX_VecMode::V_MODE) == false) {
		Error::Put("fk_D3DXShapeParser", "ReadMeshData", 2);
		return false;
	}

	if(ReadFaceData(argIFS) == false) {
		Error::Put("fk_D3DXShapeParser", "ReadMeshData", 3);
		return false;
	}

	return true;
}

bool fk_D3DXShapeParser::SetFrameMatrix(fk_TreeData *argData)
{
	fk_TreeData				*parent = argData->getParent();
	fk_D3DXPropertyList		*prop;

	if(parent == nullptr) {
		Error::Put("fk_D3DXShapeParser", "SetFrameMatrix", 1);
		return false;
	}

	prop = static_cast<fk_D3DXPropertyList *>(parent->getObject());
	if(prop != nullptr) {
		_m->frameMatrix = *(prop->GetFrameMatrix());
	}

	return true;
}

bool fk_D3DXShapeParser::ReadVectorData(ifstream &argIFS, fk_D3DX_VecMode argMode)
{
	string word, line;
	int i, vNum;
	fk_Vector tmpVec;
	fk_TexCoord tmpTex;

	word.clear();
	while(word.size() == 0) {
		if(!getline(argIFS, line)) return false;
		word = PopWord(&line);
	}

	word.erase(word.size()-1);
	if(IsInteger(word) == false) return false;
	vNum = Str2Int(word);

	if(argMode == fk_D3DX_VecMode::V_MODE) {
		for(i = 0; i < vNum; i++) {
			if(GetVector(argIFS, &line, &tmpVec) == false) return false;
			_m->vData.push_back(tmpVec);
		}
	} else {
		for(i = 0; i < vNum; i++) {
			if(GetTexCoord(argIFS, &line, &tmpTex) == false) return false;
			_m->tData.push_back(tmpTex);
		}
	}

	return true;
}

bool fk_D3DXShapeParser::GetVector(ifstream &argIFS,
								   string *argLine, fk_Vector *argVec)
{
	string word;
	fk_Vector vec;

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argVec->x = Str2Double(word);

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argVec->y = Str2Double(word);

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argVec->z = Str2Double(word);

	return true;
}

bool fk_D3DXShapeParser::GetTexCoord(ifstream &argIFS, string *argLine,
								fk_TexCoord *argTexCoord)
{
	string word;
	fk_TexCoord coord;

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argTexCoord->x = float(Str2Double(word));

	if(GetWord(argIFS, ";,", argLine, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	argTexCoord->y = float(1.0 - Str2Double(word));

	return true;
}

bool fk_D3DXShapeParser::ReadFaceData(ifstream &argIFS)
{
	int i, fNum, fCount, vNum;
	string word, line, lineList;
	vector<int> vIDArray;

	word.clear();
	while(word.size() == 0) {
		if(!getline(argIFS, line)) return false;
		word = PopWord(&line);
	}

	word.erase(word.size()-1);
	if(IsInteger(word) == false) return false;
	fNum = Str2Int(word);

	fCount = 0;
	lineList.clear();
	while(fCount < fNum) {
		word.clear();
		while(word.size() == 0) {
			if(AddLineList(argIFS, &lineList) == false) return false;
			word = PopWord(&lineList, ";,");
		}

		if(IsInteger(word) == false) return false;
		vNum = Str2Int(word);
		if(vNum != 3 && vNum != 4) return false;

		lineList.erase(0, 1);

		vIDArray.clear();
		for(i = 0; i < vNum; i++) {
			word = PopWord(&lineList, ";,");
			while(word.size() == 0) {
				if(AddLineList(argIFS, &lineList) == false) return false;
				word = PopWord(&lineList, ";,");
			}
			if(IsInteger(word) == false) return false;
			vIDArray.push_back(Str2Int(word)+1);
		}

		_m->fData.push_back(vIDArray);
		lineList.erase(0, 1);
		fCount++;
	}

	return true;
}

bool fk_D3DXShapeParser::ReadMaterialData(ifstream &argIFS)
{
	string word, lineList;
	int i, matMaxID, fNum, matID;

	if(GetWord(argIFS, ";,", &lineList, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	matMaxID = Str2Int(word) - 1;

	if(GetWord(argIFS, ";,", &lineList, &word) == false) return false;
	if(IsNumeric(word) == false) return false;
	fNum = Str2Int(word);

	_m->mData.clear();
	for(i = 0; i < fNum; i++) {
		if(GetWord(argIFS, ";,", &lineList, &word) == false) return false;
		if(IsNumeric(word) == false) return false;
		matID = Str2Int(word);
		if(matID < 0 || matID > matMaxID) return false;
		_m->mData.push_back(matID);
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////

void fk_D3DXShapeParser::SetQuadFace(int argIndex)
{
	vector<int> tmpIDArray1, tmpIDArray2;
	_st index = _st(argIndex);
	
	tmpIDArray1.push_back(_m->fData[index][0]);
	tmpIDArray1.push_back(_m->fData[index][1]);
	tmpIDArray1.push_back(_m->fData[index][2]);

	tmpIDArray2.push_back(_m->fData[index][0]);
	tmpIDArray2.push_back(_m->fData[index][2]);
	tmpIDArray2.push_back(_m->fData[index][3]);

	_m->optFData.push_back(tmpIDArray1);
	_m->optFData.push_back(tmpIDArray2);

	return;
}

void fk_D3DXShapeParser::SetIFSTexCoord(fk_IFSTexture *argIFST)
{
	_st i, j, index;

	for(i = 0; i < _m->optFData.size(); i++) {
		for(j = 0; j < 3; j++) {
			index = _st(_m->optFData[i][j]) - 1;
			argIFST->setTextureCoord(int(i), int(j), _m->optTData[index]);
		}
	}
	return;
}

void fk_D3DXShapeParser::OptimizeData(int argMateID)
{
	_st i, j;
	bool texDataFlg;
	deque<bool> tmpArray;
	int index, count;
	string outStr;

	_m->optVData.clear();
	_m->optFData.clear();
	_m->optTData.clear();

	count = 0;
	_m->vMapData.clear();

	if(_m->mData.size() == _m->fData.size()) texDataFlg = true;
	else texDataFlg = false;

	for(i = 0; i < _m->fData.size(); i++) {
		if(texDataFlg == true && argMateID >= 0) {
			if(_m->mData[i] != argMateID) continue;
		}

		if(_m->fData[i].size() == 3) {
			_m->optFData.push_back(_m->fData[i]);
		} else {
			SetQuadFace(static_cast<int>(i));
		}
	}

	tmpArray.resize(_m->vData.size());
	for(i = 0; i < tmpArray.size(); i++) tmpArray[i] = false;

	for(i = 0; i < _m->optFData.size(); i++) {
		for(j = 0; j < _m->optFData[i].size(); j++) {
			index = _m->optFData[i][j] - 1;
			if(index < 0 || index >= static_cast<int>(tmpArray.size())) return;
			tmpArray[static_cast<_st>(index)] = true;
		}
	}

	_m->vMapData.resize(tmpArray.size());
	for(i = 0; i < tmpArray.size(); i++) {
		if(tmpArray[i] == true) {
			_m->vMapData[i] = count;
			_m->optVData.push_back(_m->vData[i]);
			if(_m->tData.empty() == false) _m->optTData.push_back(_m->tData[i]);
			count++;
		} else {
			_m->vMapData[i] = -1;
		}
	}

	for(i = 0; i < _m->optFData.size(); i++) {
		for(j = 0; j < _m->optFData[i].size(); j++) {
			index = _m->optFData[i][j]-1;
			_m->optFData[i][j] = _m->vMapData[static_cast<_st>(index)]+1;
		}
	}

	return;
}

bool fk_D3DXShapeParser::MakeMesh(fk_ParserData *argMesh,
								  bool argSolidFlg)
{
	argMesh->Init();
	return argMesh->MakeMesh(&_m->optVData, &_m->optFData, argSolidFlg);
}

int fk_D3DXShapeParser::GetVMap(int argIndex)
{
	if(argIndex < 0 || argIndex >= static_cast<int>(_m->vMapData.size())) {
		return -1;
	}
	return _m->vMapData[static_cast<_st>(argIndex)];
}

int fk_D3DXShapeParser::GetOptVSize(void)
{
	return static_cast<int>(_m->optVData.size());
}

int fk_D3DXShapeParser::GetOrgVSize(void)
{
	return static_cast<int>(_m->vData.size());
}

void fk_D3DXShapeParser::Print(void)
{
	_st				i, j;
	stringstream	ss;

	ss << "vsize = " << _m->optVData.size();
	Error::Put(ss.str());
	ss.clear();
	
	for(i = 0; i < _m->optVData.size(); i++) {
		ss << "v[" << i << "]\t= " << _m->optVData[i].OutStr();
		Error::Put(ss.str());
		ss.clear();
	}

	ss << "fSize = " <<  _m->optFData.size();
	Error::Put(ss.str());
	ss.clear();
	
	for(i = 0; i < _m->optFData.size(); i++) {
		ss << "f[" << i << "]\t= (";
		for(j = 0; j < _m->optFData[i].size(); j++) {
			ss << _m->optFData[i][j];
			if(j == _m->optFData[i].size()-1) {
				ss << ")";
			} else {
				ss << ", ";
			}
		}
		Error::Put(ss.str());
		ss.clear();
	}

	ss << "tSize = " << _m->optTData.size();
	Error::Put(ss.str());
	ss.clear();

	for(i = 0; i < _m->optTData.size(); i++) {
		ss << "t[" << i << "]\t= (" << _m->optTData[i].x << ", " << _m->optTData[i].y << ")";
		Error::Put(ss.str());
		ss.clear();
	}

	ss << "mSize = " << _m->mData.size();
	Error::Put(ss.str());
	ss.clear();

	for(i = 0; i < _m->mData.size(); i++) {
		ss << "m[" << i << "]\t = " <<  _m->mData[i];
		Error::Put(ss.str());
		ss.clear();
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
