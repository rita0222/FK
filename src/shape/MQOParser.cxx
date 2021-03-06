﻿#define FK_DEF_SIZETYPE
#include <FK/MQOParser.H>
#include <FK/MeshTexture.h>
#include <FK/IFSTexture.h>
#include <FK/Tree.h>

using namespace std;
using namespace FK;

class _fk_MQOPropertyList : public fk_TreeBaseObject {
public:
	string property;
	string data;
};

_fk_MQO_IDSet::_fk_MQO_IDSet(void)
{
	id = -1;
	coord.set(0.0, 0.0);
	return;
}

bool _fk_MQO_IDSet::operator ==(const _fk_MQO_IDSet &i) const
{
	if(id == i.id && coord == i.coord) return true;
	return false;
}

fk_MQOParser::Member::Member(void) :
	tree(make_unique<fk_Tree>()),
	meshTexture(nullptr), ifsTexture(nullptr), contFlg(true), matFlg(false)
{
	tree->clear("_MQOParser_root");
}
	

fk_MQOParser::fk_MQOParser(void) : _m(make_unique<Member>())
{
	IFSListUpdate = [](fk_IFSTexture *, fk_MQOListSet *) {};
	return;
}

fk_MQOParser::~fk_MQOParser()
{
	return;
}

bool fk_MQOParser::ReadMQOFile(const string &argFileName,
							   const string &argObjName,
							   int argMateID, bool argSolidFlg)
{
	if(meshData == nullptr && _m->meshTexture == nullptr) {
		return false;
	}

	if(CheckFile(argFileName) == false) return false;

	return MakeData(argFileName, nullptr, argObjName,
					argMateID, argSolidFlg);
}

bool fk_MQOParser::ReadMQOData(unsigned char *argBuffer,
							   const string &argObjName,
							   int argMateID, bool argSolidFlg)
{
	if(meshData == nullptr && _m->meshTexture == nullptr) {
		return false;
	}

	if(CheckData(argBuffer) == false) return false;
	return MakeData("", argBuffer, argObjName,
					argMateID, argSolidFlg);
}

void fk_MQOParser::SetMeshTexture(fk_MeshTexture *argTexture)
{
	_m->meshTexture = argTexture;
	meshData = nullptr;
	_m->ifsTexture = nullptr;
	return;
}

void fk_MQOParser::SetIFSTexture(fk_IFSTexture *argTexture, fk_IndexFaceSet *argMesh)
{
	_m->ifsTexture = argTexture;
	SetMeshData(argMesh);
	_m->meshTexture = nullptr;
	return;
}

fk_TreeData * fk_MQOParser::GetProperty(fk_TreeData *argParent,
										string *argLine)
{
	string					keys, objName;
	fk_TreeData				*newData;
	shared_ptr<_fk_MQOPropertyList> propList(new _fk_MQOPropertyList());

	keys = argLine->substr(0, argLine->find("{"));
	TrimString(&keys);
	newData = _m->tree->addNewChild(argParent, keys);
	propList->property = PopWord(&keys);

	if(propList->property == "Object") {
		string::size_type		start, end;

		start = keys.find("\"");
		if(start != string::npos) {
			end = keys.find_first_of("\"", start+1);
			propList->data = keys.substr(start, end - start);
		} else {	
			propList->data = PopWord(&keys);
		}
	} else {
		propList->data = PopWord(&keys);
	}

	ReplaceString(&(propList->data), "\"", "");
	newData->setObject(propList);
	return newData;
}

bool fk_MQOParser::CheckFile(const string &argFileName)
{
	ifstream	ifs(argFileName);
	string		str, line, word;
	int			i;

	if(ifs.fail()) return false;

	for(i = 0; i < 2; i++) {
		if(!getline(ifs, line)) {
			ifs.close();
			return false;
		}
		str += line + "\n";
	}

	ifs.close();
	if(PopWord(&str) != "Metasequoia") return false;
	if(PopWord(&str) != "Document") return false;
	if(PopWord(&str) != "Format") return false;
	if(PopWord(&str) != "Text") return false;
	if(PopWord(&str) != "Ver") return false;
	word = PopWord(&str);
	if(word != "1.0" && word != "1.1") return false;

	return true;
}


bool fk_MQOParser::CheckData(unsigned char *)
{
	return true;
}

bool fk_MQOParser::MakeData(const string &argFileName,
							unsigned char *argBuffer,
							const string &argObjName,
							int argMateID, bool argSolidFlg)
{
	string line;
	ifstream ifs(argFileName), *ifsP;
	bool oMode, vMode, fMode, mMode;
	int vNum, fNum;
	unsigned int bufTag;
	fk_TreeData *data;
	_fk_MQOPropertyList *propList;

	if(_m->meshTexture != nullptr && _m->ifsTexture != nullptr) return false;

	if(argBuffer == nullptr) {
		if(ifs.fail()) {
			return false;
		} else {
			ifsP = &ifs;
		}
	} else {
		ifsP = nullptr;
	}

	data = _m->tree->getRoot();
	oMode = false;
	vMode = false;
	fMode = false;
	mMode = false;
	vNum = -1;

	bufTag = 0;

	while(ReadLine(ifsP, argBuffer, &bufTag, &line) == true) {

		if(line.find("{") != string::npos) {
			data = GetProperty(data, &line);
			propList = static_cast<_fk_MQOPropertyList *>(data->getObject());
			if(propList->property == "Object") {
				if(propList->data == argObjName) {
					oMode = true;
					continue;
				}
			} else if(propList->property == "Material") {
				mMode = true;
				continue;
			}  else if(oMode == true) {
				if(propList->property == "vertex") {
					vMode = true;
					vNum = Str2Int(propList->data);
					if(vNum < 0) {
						return false;
					}
					continue;
				} else if(propList->property == "face") {
					fMode = true;
					fNum = Str2Int(propList->data);
					if(fNum < 0) {
						return false;
					}
					continue;
				}
			}

		} else if(line.find("}") != string::npos) {
			propList = static_cast<_fk_MQOPropertyList *>(data->getObject());
			if(propList->property == "Object" && oMode == true) {
				oMode = false;
				continue;
			} else if(propList->property == "vertex" && vMode == true) {
				if(vNum != int(_m->vData.size())) {
					return false;
				}
				vMode = false;
			} else if(propList->property == "face" && fMode == true) {
				fMode = false;
			} else if(propList->property == "Material" && mMode == true) {
				mMode = false;
			}

			data = data->getParent();
			continue;
		}

		if(vMode == true) {
			if(PushVertexData(&line) == false) {
				if(argBuffer == nullptr) ifs.close();
				return false;
			}
		}

		if(fMode == true) {
			if(PushFaceData(&line, argMateID) == false) {
				if(argBuffer == nullptr) ifs.close();
				return false;
			}
		}

		if(mMode == true) {
			if(PushMaterialData(&line) == false) {
				if(argBuffer == nullptr) ifs.close();
				return false;
			}
		}
	}

	if(argBuffer == nullptr) ifs.close();

	if(CheckIFData(vNum) == false) {
		return false;
	}

	if(meshData != nullptr) {
		meshData->clearMaterial();
		for(unsigned int i = 0; i < _m->mData.size(); i++) {
			meshData->pushPalette(_m->mData[i]);
		}

		meshData->Init();
		/*
		if(meshData->MakeMesh(&optVData, &fData,
							  &cIDData, argSolidFlg) == false) {
		*/
		if(meshData->MakeMesh(&_m->optVData, &_m->fData, argSolidFlg) == false) {
			return false;
		}

		if(_m->matFlg == true) {
			if(meshData->getPaletteSize() == 0) {
				meshData->setMaterialMode(fk_MaterialMode::NONE);
			} else {
				meshData->setMaterialMode(fk_MaterialMode::PARENT);
			}
		} else {
			meshData->setMaterialMode(fk_MaterialMode::CHILD);
		}
	}

	if(_m->meshTexture != nullptr) {
		SetMeshTexCoord();
	}

	if(_m->ifsTexture != nullptr) {
		SetIFSTexCoord();
	}

	return true;
}

bool fk_MQOParser::ReadLine(ifstream *argIFS,
							unsigned char *argBuffer,
							unsigned int *argBufTag,
							string *argOutStr)
{
	bool	startFlg, lineFlg;

	startFlg = false;
	lineFlg = false;
	if(argBuffer == nullptr) {
		if(!getline(*argIFS, *argOutStr)) {
			return false;
		}
		*argOutStr += "\n";
	} else {
		argOutStr->clear();
		while(true) {
			if(argBuffer[*argBufTag] == '\0') return false;
			if(argBuffer[*argBufTag] == '\n' ||
			   argBuffer[*argBufTag] == '\r') {
				lineFlg = false;
			} else {
				lineFlg = true;
			}

			if(startFlg == false && lineFlg == true) {
				startFlg = true;
			}

			if(startFlg == true && lineFlg == false) {
				break;
			}

			if(startFlg == true) {
				argOutStr->push_back(char(argBuffer[(*argBufTag)]));
			}
			(*argBufTag)++;
		}
	}

	return true;
}

bool fk_MQOParser::PushVertexData(string *argLine)

{
	fk_Vector		pos;
	string			words[3];
	int				i;

	for(i = 0; i < 3; i++) {
		words[i] = PopWord(argLine);
		if(IsNumeric(words[i]) == false) return false;
	}

	pos.x = Str2Double(words[0]);
	pos.y = Str2Double(words[1]);
	pos.z = Str2Double(words[2]);

	_m->vData.push_back(pos);
	return true;
}

bool fk_MQOParser::PushFaceData(string *argLine, int argMateID)
{
	string					word, sep;
	int						tmpID, mateID;
	int						i, vNum;
	vector<int>				vIDArray;
	vector<fk_TexCoord>		texArray;
	fk_TexCoord				tmpCoord;
	double					tmpX, tmpY;

	sep = "()[]{}";
	word = PopWord(argLine, sep);
	if(IsInteger(word) == false) return false;
	vNum = Str2Int(word);
	if(vNum != 3 && vNum != 4) return false;

	vIDArray.clear();
	texArray.clear();
	mateID = FK_UNDEFINED;
	while((word = PopWord(argLine, sep)) != "") {
		if(word == "V") {
			if(PopWord(argLine, sep) != "(") return false;
			for(i = 0; i < vNum; i++) {
				word = PopWord(argLine, sep);
				if(IsInteger(word) == false) return false;
				//vIDArray.push_back(Str2Int(word) + 1);
				vIDArray.push_back(Str2Int(word));
			}

			tmpID = vIDArray[0];
			vIDArray[0] = vIDArray[2];
			vIDArray[2] = tmpID;

			if(PopWord(argLine, sep) != ")") return false;

		} else if(word == "M") {
			if(PopWord(argLine, sep) != "(") return false;
			word = PopWord(argLine, sep);
			if(IsInteger(word) == false) return false;
			mateID = Str2Int(word);

			if(PopWord(argLine, sep) != ")") return false;

		} else if(word == "UV") {
			if(PopWord(argLine, sep) != "(") return false;
			for(i = 0; i < vNum; i++) {
				word = PopWord(argLine, sep);
				if(IsNumeric(word) == false) return false;
				tmpX = Str2Double(word);
				word = PopWord(argLine, sep);
				if(IsNumeric(word) == false) return false;
				tmpY = 1.0 - Str2Double(word);

				while(tmpX < 0.0) tmpX += 1.0;
				while(tmpX > 1.0) tmpX -= 1.0;
				while(tmpY < 0.0) tmpY += 1.0;
				while(tmpY > 1.0) tmpY -= 1.0;
				tmpCoord.x = static_cast<float>(tmpX);
				tmpCoord.y = static_cast<float>(tmpY);
				texArray.push_back(tmpCoord);
			}
			tmpCoord = texArray[0];
			texArray[0] = texArray[2];
			texArray[2] = tmpCoord;

			if(PopWord(argLine, sep) != ")") return false;
		}
	}

	if(argMateID >= 0 && mateID != argMateID) return true;

	_m->cIDData.push_back(mateID);
	if(vIDArray.size() == 3) {
		_m->fData.push_back(vIDArray);
		_m->tData.push_back(texArray);
	} else {
		SetQuadFace(&_m->fData, &_m->tData, &vIDArray, &texArray);
		_m->cIDData.push_back(mateID);
	}

	return true;
}

bool fk_MQOParser::PushMaterialData(string *argLine)
{
	string				word, sep;
	fk_Color			col;
	float				dif, amb, emi, spec, shin;
	fk_Material			mat;

	dif = amb = emi = spec = shin = 0.0f;

	sep = "()[]{}";
	word = PopWord(argLine, sep);

	while((word = PopWord(argLine, sep)) != "") {
		if(word == "col") {
			if(PopWord(argLine, sep) != "(") return false;
			for(_st i = 0; i < 4; i++) {
				word = PopWord(argLine, sep);
				if(IsNumeric(word) == false) return false;
				col.col[i] = Str2Float(word);
			}
			if(PopWord(argLine, sep) != ")") return false;
		}

		if(word == "dif") {
			if(PopWord(argLine, sep) != "(") return false;
			word = PopWord(argLine, sep);
			if(IsNumeric(word) == false) return false;
			dif = Str2Float(word);
			if(PopWord(argLine, sep) != ")") return false;
		}

		if(word == "amb") {
			if(PopWord(argLine, sep) != "(") return false;
			word = PopWord(argLine, sep);
			if(IsNumeric(word) == false) return false;
			amb = Str2Float(word);
			if(PopWord(argLine, sep) != ")") return false;
		}

		if(word == "emi") {
			if(PopWord(argLine, sep) != "(") return false;
			word = PopWord(argLine, sep);
			if(IsNumeric(word) == false) return false;
			emi = Str2Float(word);
			if(PopWord(argLine, sep) != ")") return false;
		}

		if(word == "spc") {
			if(PopWord(argLine, sep) != "(") return false;
			word = PopWord(argLine, sep);
			if(IsNumeric(word) == false) return false;
			spec = Str2Float(word);
			if(PopWord(argLine, sep) != ")") return false;
		}

		if(word == "power") {
			if(PopWord(argLine, sep) != "(") return false;
			word = PopWord(argLine, sep);
			if(IsNumeric(word) == false) return false;
			shin = Str2Float(word);
			if(PopWord(argLine, sep) != ")") return false;
		}

	}

	mat.setAlpha(col.col[3]);
	mat.setAmbient(col.col[0] * amb,
				   col.col[1] * amb,
				   col.col[2] * amb);
	mat.setDiffuse(col.col[0] * dif,
				   col.col[1] * dif,
				   col.col[2] * dif);
	mat.setEmission(col.col[0] * emi,
					col.col[1] * emi,
					col.col[2] * emi);
	mat.setSpecular(col.col[0] * spec,
					col.col[1] * spec,
					col.col[2] * spec);
	mat.setShininess(shin);

	_m->mData.push_back(mat);

	return true;
}

void fk_MQOParser::SetQuadFace(vector< vector<int> > *argIF,
							   vector< vector<fk_TexCoord> > *argIFST,
							   vector<int> *argID,
							   vector<fk_TexCoord> *argFaceTexCoord)
{
	vector<int>			tmpIDArray1, tmpIDArray2;
	vector<fk_TexCoord>	tmpCoordArray1, tmpCoordArray2;

	tmpIDArray1.push_back((*argID)[0]);
	tmpIDArray1.push_back((*argID)[1]);
	tmpIDArray1.push_back((*argID)[2]);

	tmpIDArray2.push_back((*argID)[0]);
	tmpIDArray2.push_back((*argID)[2]);
	tmpIDArray2.push_back((*argID)[3]);

	argIF->push_back(tmpIDArray1);
	argIF->push_back(tmpIDArray2);

	if(argFaceTexCoord->size() == 4) {
		tmpCoordArray1.push_back((*argFaceTexCoord)[0]);
		tmpCoordArray1.push_back((*argFaceTexCoord)[1]);
		tmpCoordArray1.push_back((*argFaceTexCoord)[2]);

		tmpCoordArray2.push_back((*argFaceTexCoord)[0]);
		tmpCoordArray2.push_back((*argFaceTexCoord)[2]);
		tmpCoordArray2.push_back((*argFaceTexCoord)[3]);
	}

	argIFST->push_back(tmpCoordArray1);
	argIFST->push_back(tmpCoordArray2);

	return;
}

bool fk_MQOParser::CheckIFData(int argVNum)
{
	_st		fNum = 0;
	_st		i, j, size;
	int		id;

	for(i = 0; i < _m->fData.size(); i++) {
		size = _m->fData[i].size();
		if(size < 3 || size > 4) {
			return false;
		}
		fNum += (size - 2);

		for(j = 0; j < _m->fData[i].size(); j++) {
			id = _m->fData[i][j];
			//if(id <= 0 || id > argVNum) {
			if(id < 0 || id >= argVNum) {
				return false;
			}
		}
	}

	OptimizeData();

	if(_m->contFlg == true) MakeUniqueVertex4Texture();

	if(_m->meshTexture != nullptr) {
		_m->meshTexture->setTriNum(int(fNum));
	}

	return true;
}

void fk_MQOParser::OptimizeData(void)
{
	_st				i, j;
	vector<char>	tmpArray;
	vector<int>		mapArray;
	int				index, count;

	tmpArray.resize(_m->vData.size());
	for(i = 0; i < tmpArray.size(); i++) tmpArray[i] = char(false);

	for(i = 0; i < _m->fData.size(); i++) {
		for(j = 0; j < _m->fData[i].size(); j++) {
			//index = _m->fData[i][j]-1;
			index = _m->fData[i][j];
			if(index < 0 || index >= int(tmpArray.size())) return;
			tmpArray[_st(index)] = char(true);
		}
	}

	//count = 1;
	count = 0;
	mapArray.resize(tmpArray.size());
	for(i = 0; i < tmpArray.size(); i++) {
		if(tmpArray[i] == char(true)) {
			mapArray[i] = count;
			_m->optVData.push_back(_m->vData[i]);
			count++;
		} else {
			mapArray[i] = -1;
		}
	}

	for(i = 0; i < _m->fData.size(); i++) {
		for(j = 0; j < _m->fData[i].size(); j++) {
			//index = _m->fData[i][j]-1;
			index = _m->fData[i][j];
			_m->fData[i][j] = mapArray[_st(index)];
		}
	}

	return;
}

void fk_MQOParser::MakeUniqueVertex4Texture(void)
{
	fk_MQOListSet						listSet;
	fk_TexCoord							coord;
	_st									i, j, k, index;
	_fk_MQO_IDSet						idset;
	int									newID;

	listSet.resize(_m->optVData.size());
	newID = int(_m->optVData.size());

	for(i = 0; i < _m->fData.size(); i++) {
		if(_m->fData[i].size() != _m->tData[i].size()) continue;

		for(j = 0; j < _m->fData[i].size(); j++) {
			//index = _st(_m->fData[i][j] - 1);
			index = _st(_m->fData[i][j]);
			idset.id = int(index);

			coord = _m->tData[i][j];
			idset.coord = coord;

			if(listSet[index].size() == 0) {
				listSet[index].push_back(idset);
			} else {
				for(k = 0; k < listSet[index].size(); k++) {
					if(idset.coord == listSet[index][k].coord) {
						//_m->fData[i][j] = listSet[index][k].id + 1;
						_m->fData[i][j] = listSet[index][k].id;
						break;
					}
				}
				if(k == listSet[index].size()) {
					idset.id = newID;
					listSet[index].push_back(idset);
					_m->optVData.push_back(_m->optVData[index]);
					//newID++;
					_m->fData[i][j] = newID;
					newID++;
				}
			}
		}
	}

	if(_m->ifsTexture != nullptr) IFSListUpdate(_m->ifsTexture, &listSet);
		
	/*
	if(_m->ifsTexture != nullptr) {
		commonList = &(_m->ifsTexture->commonList);
		commonList->resize(listSet.size());
		for(i = 0; i < listSet.size(); i++) {
			for(j = 1; j < listSet[i].size(); j++) {
				commonList->at(i).push_back(listSet[i][j].id);
			}
		}
	}
	*/
	return;
}

void fk_MQOParser::SetMeshTexCoord(void)
{
	_st			i, j;
	fk_Vector	triPos[3];
	fk_TexCoord	triCoord[3];

	if(_m->meshTexture == nullptr) return;
	for(i = 0; i < _m->fData.size(); i++) {
		for(j = 0; j < 3; j++) {
			//triPos[j] = _m->optVData[_st(_m->fData[i][j]-1)];
			triPos[j] = _m->optVData[_st(_m->fData[i][j])];
			triCoord[j] = _m->tData[i][j];
		}
		_m->meshTexture->setTriPos(int(i), triPos);
		_m->meshTexture->setTriTextureCoord(int(i), triCoord);
	}
	return;
}

void fk_MQOParser::SetIFSTexCoord(void)
{
	_st			i, j;

	for(i = 0; i < _m->tData.size(); i++) {
		for(j = 0; j < _m->tData[i].size(); j++) {
			_m->ifsTexture->setTextureCoord(int(i), int(j), _m->tData[i][j]);
		}
	}
	return;
}

void fk_MQOParser::SetContMode(bool argFlg)
{
	_m->contFlg = argFlg;
	return;
}

void fk_MQOParser::SetMaterialMode(bool argFlg)
{
	_m->matFlg = argFlg;
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
