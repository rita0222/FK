﻿#define FK_DEF_SIZETYPE

#include <FK/Shape.h>
//#include <FK/Window.h>

using namespace std;
using namespace FK;

const string fk_Shape::vertexName = "fk_Vertex";
const string fk_Shape::normalName = "fk_Normal";
const string fk_Shape::pointModelColorName = "fk_PointModelColor";
const string fk_Shape::pointElementColorName = "fk_PointElementColor";
const string fk_Shape::pointElementAliveName = "fk_PointElementAlive";
const string fk_Shape::lineModelColorName = "fk_LineModelColor";
const string fk_Shape::lineElementColorName = "fk_LineElementColor";
const string fk_Shape::lineElementAliveName = "fk_LineElementAlive";
const string fk_Shape::curveModelColorName = "fk_CurveModelColor";
const string fk_Shape::texCoordName = "fk_TexCoord";
const string fk_Shape::ctrlPosName = "fk_CtrlPos";
const string fk_Shape::degreeName = "fk_Degree";
const string fk_Shape::geomDivName = "fk_GeomDiv";

//int fk_Shape::ALIVE;
//int fk_Shape::DEAD;

fk_Shape::Member::Member(void) :
	pointVAO(0), lineVAO(0), faceVAO(0), vboInitFlg(false)
{
	return;
}

fk_Shape::fk_Shape(fk_Type argObjType) : _m(make_unique<Member>())
{
	SetObjectType(argObjType);
	realType = fk_RealShapeType::OTHER;
	FlushAttr = []() {};
	return;
}

fk_Shape::~fk_Shape()
{
	if (_m->pointVAO != 0) DeleteBuffer(_m->pointVAO);
	if (_m->lineVAO != 0) DeleteBuffer(_m->lineVAO);
	if (_m->faceVAO != 0) DeleteBuffer(_m->faceVAO);

	int tmpID = 0;

	for (auto p : _m->attrMapI) {
		tmpID = get<0>(p.second);
		if (tmpID != -1) {
			DeleteBuffer(GLuint(tmpID));
		}
	}

	for (auto p : _m->attrMapF) {
		tmpID = get<0>(p.second);
		if (tmpID != -1) {
			DeleteBuffer(GLuint(tmpID));
		}
	}
	
	return;
}

void fk_Shape::SetPaletteData(fk_Palette *argPal)
{
	FK_UNUSED(argPal);
	//palette = argPal;
	return;
}

void fk_Shape::setPaletteData(fk_Palette *argPal)
{
	FK_UNUSED(argPal);
	//SetPaletteData(argPal);
	return;
}

fk_Palette * fk_Shape::getPaletteData(void)
{
	//return palette;
	return nullptr;
}

void fk_Shape::clearMaterial(void)
{
	//palette->clearMaterial();
	return;
}

void fk_Shape::setObjMaterialID(int argID)
{
	FK_UNUSED(argID);
	//palette->setObjMaterialID(argID);
	//materialMode = fk_MaterialMode::CHILD;
	return;
}

void fk_Shape::pushPalette(fk_Material &argMat)
{
	FK_UNUSED(argMat);
	//palette->pushPalette(&argMat);
	//materialMode = fk_MaterialMode::PARENT;
	return;
}

void fk_Shape::setPalette(fk_Material &argMat, int argID)
{
	FK_UNUSED(argMat);
	FK_UNUSED(argID);
	//palette->setPalette(&argMat, argID);
	//materialMode = fk_MaterialMode::PARENT;
	return;
}

void fk_Shape::setMaterialMode(fk_MaterialMode argMode)
{
	FK_UNUSED(argMode);
	//materialMode = argMode;
	return;
}

fk_MaterialMode fk_Shape::getMaterialMode(void)
{
	//return materialMode;
	return fk_MaterialMode::NONE;
}

int fk_Shape::getObjMaterialID(void)
{
	//return palette->getObjMaterialID();
	return 0;
}

int fk_Shape::getPaletteSize(void)
{
	//return palette->getPaletteSize();
	return 0;
}

fk_Material * fk_Shape::getMaterial(int argID)
{
	FK_UNUSED(argID);
	//return palette->getMaterial(argID);
	return nullptr;
}

vector<fk_Material> * fk_Shape::getMaterialVector(void)
{
	//return palette->getMaterialVector();
	return nullptr;
}

fk_RealShapeType fk_Shape::getRealShapeType(void)
{
	return realType;
}

void fk_Shape::SetPointVAO(GLuint argVAO)
{
	_m->pointVAO = argVAO;
}

void fk_Shape::SetLineVAO(GLuint argVAO)
{
	_m->lineVAO = argVAO;
}

void fk_Shape::SetFaceVAO(GLuint argVAO)
{
	_m->faceVAO = argVAO;
}

GLuint fk_Shape::GetPointVAO(void)
{
	return _m->pointVAO;
}

GLuint fk_Shape::GetLineVAO(void)
{
	return _m->lineVAO;
}

GLuint fk_Shape::GetFaceVAO(void)
{
	return _m->faceVAO;
}

void fk_Shape::DeleteMapI(string argName)
{
	if(_m->attrMapI.find(argName) != _m->attrMapI.end()) {
		int tmpID = get<0>(_m->attrMapI[argName]);
		if(tmpID != -1) {
			DeleteBuffer(GLuint(tmpID));
		}
		_m->attrMapI.erase(argName);
	}
}	

void fk_Shape::DeleteMapF(string argName)
{
	if(_m->attrMapF.find(argName) != _m->attrMapF.end()) {
		int tmpID = get<0>(_m->attrMapF[argName]);
		if(tmpID != -1) {
			DeleteBuffer(GLuint(tmpID));
		}
		_m->attrMapF.erase(argName);
	}
}	

void fk_Shape::setShaderAttribute(string argName, int argDim,
								  vector<int> *argValue, bool argSelf)
{
	if(argValue == nullptr || argDim < 1 || argDim > 4) return;
	int id = -1;

	DeleteMapF(argName);
	
	if(_m->attrMapI.find(argName) != _m->attrMapI.end()) id = get<0>(_m->attrMapI[argName]);

	if(argSelf == true) {
		if(_m->intSelf.find(argName) == _m->intSelf.end()) {
			_m->intSelf.emplace(argName, make_unique<vector<int>>());
		}
		vector<int> *array = _m->intSelf[argName].get();
		array->resize(argValue->size());
		copy(argValue->begin(), argValue->end(), array->begin());
		_m->attrMapI[argName] = shapeAttrI(id, argDim, array);
	} else {
		_m->attrMapI[argName] = shapeAttrI(id, argDim, argValue);
	}
	_m->attrModify[argName] = true;
}

void fk_Shape::setShaderAttribute(string argName, int argDim,
								  vector<float> *argValue, bool argSelf)
{
	if(argValue == nullptr || argDim < 1 || argDim > 4) return;
	int id = -1;

	DeleteMapI(argName);

	if(_m->attrMapF.find(argName) != _m->attrMapF.end()) id = get<0>(_m->attrMapF[argName]);

	if(argSelf == true) {
		if(_m->floatSelf.find(argName) == _m->floatSelf.end()) {
			_m->floatSelf.emplace(argName, make_unique<vector<float>>());
		}
		vector<float> *array = _m->floatSelf[argName].get();
		array->resize(argValue->size());
		copy(argValue->begin(), argValue->end(), array->begin());
		_m->attrMapF[argName] = shapeAttrF(id, argDim, array);
	} else {
		_m->attrMapF[argName] = shapeAttrF(id, argDim, argValue);
	}
	
	_m->attrModify[argName] = true;
}
	
void fk_Shape::setShaderAttribute(string argName, int argDim,
								  vector<fk_Vector> *argValue)
{
	if(argValue == nullptr || argDim < 1 || argDim > 4) return;
	vector<float> array;

	for(_st i = 0; i < argValue->size(); ++i) {
		array.push_back(float(argValue->at(i).x));
		if(argDim == 1) continue;
		array.push_back(float(argValue->at(i).y));
		if(argDim == 2) continue;
		array.push_back(float(argValue->at(i).z));
		if(argDim == 4) array.push_back(0.0f);
	}

	setShaderAttribute(argName, argDim, &array, true);
}
	
void fk_Shape::setShaderAttribute(string argName, int argDim,
								  vector<fk_TexCoord> *argValue)
{
	if(argValue == nullptr || argDim < 1 || argDim > 4) return;
	vector<float> array;

	for(_st i = 0; i < argValue->size(); ++i) {
		array.push_back(float(argValue->at(i).x));
		if(argDim == 1) continue;
		array.push_back(float(argValue->at(i).y));
		if(argDim == 2) continue;
		array.push_back(0.0f);
		if(argDim == 4) array.push_back(0.0f);
	}

	setShaderAttribute(argName, argDim, &array, true);
}

void fk_Shape::setShaderAttribute(string argName, int argDim,
								  vector<fk_HVector> *argValue)
{
	if(argValue == nullptr || argDim < 1 || argDim > 4) return;
	vector<float> array;

	for(_st i = 0; i < argValue->size(); ++i) {
		array.push_back(float(argValue->at(i).x));
		if(argDim == 1) continue;
		array.push_back(float(argValue->at(i).y));
		if(argDim == 2) continue;
		array.push_back(float(argValue->at(i).z));
		if(argDim == 4) array.push_back(float(argValue->at(i).w));
	}

	setShaderAttribute(argName, argDim, &array, true);
}
	

void fk_Shape::DefineVBO(void)
{
	if(_m->vboInitFlg == true) return;

	for(auto itr = _m->attrMapI.begin(); itr != _m->attrMapI.end(); ++itr) {
		if(get<0>(itr->second) == -1) {
			get<0>(itr->second) = int(GenBuffer());
		}
	}

	for(auto itr = _m->attrMapF.begin(); itr != _m->attrMapF.end(); ++itr) {
		if(get<0>(itr->second) == -1) {
			get<0>(itr->second) = int(GenBuffer());
		}
	}
	return;
}

void fk_Shape::BindShaderBuffer(map<string, int> *argTable)
{
	GLuint loc;
	_st size;

	for(auto itr = _m->attrMapI.begin(); itr != _m->attrMapI.end(); ++itr) {
		if(argTable->find(itr->first) == argTable->end()) continue;
		auto [vbo, dim, iArray] = itr->second;
		loc = GLuint(argTable->at(itr->first));
		glBindBuffer(GL_ARRAY_BUFFER, GLuint(vbo));
		glVertexAttribIPointer(loc, dim, GL_INT, 0, 0);
		if(_m->attrModify[itr->first] == true) {
			size = iArray->size();
			glBufferData(GL_ARRAY_BUFFER,
						 GLsizeiptr(sizeof(int) * size),
						 iArray->data(), GL_STATIC_DRAW);
			_m->attrModify[itr->first] = false;
		}
		glEnableVertexAttribArray(loc);
	}

	for(auto itr = _m->attrMapF.begin(); itr != _m->attrMapF.end(); ++itr) {
		if(argTable->find(itr->first) == argTable->end()) continue;
		auto [vbo, dim, fArray] = itr->second;
		loc = GLuint(argTable->at(itr->first));
		glBindBuffer(GL_ARRAY_BUFFER, GLuint(vbo));
		glVertexAttribPointer(loc, dim, GL_FLOAT, GL_FALSE, 0, 0);
		if(_m->attrModify[itr->first] == true) {
			size = fArray->size();
			glBufferData(GL_ARRAY_BUFFER,
						 GLsizeiptr(sizeof(float) * size),
						 fArray->data(), GL_STATIC_DRAW);
			_m->attrModify[itr->first] = false;
		}
		glEnableVertexAttribArray(loc);
	}

	return;
}

void fk_Shape::modifyAttribute(string argName)
{
	_m->attrModify[argName] = true;
}

void fk_Shape::FinishSetVBO(void)
{
	_m->vboInitFlg = true;
}

GLuint fk_Shape::GenBuffer(void)
{
	GLuint	id;

	glGenBuffers(1, &id);
	return id;
}

void fk_Shape::DeleteBuffer(GLuint argID)
{
#ifndef FK_CLI_CODE
	glDeleteBuffers(1, &argID);
#endif
}

void fk_Shape::ForceUpdateAttr(void)
{
	for(auto itr = _m->attrModify.begin(); itr != _m->attrModify.end(); ++itr) {
		itr->second = true;
	}
	_m->vboInitFlg = false;
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
