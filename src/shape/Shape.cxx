/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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

const int fk_Shape::ALIVE;
const int fk_Shape::DEAD;

fk_Shape::fk_Shape(fk_Type argObjType)
	: palette(&defaultPalette), materialMode(fk_MaterialMode::NONE),
	  pointVAO(0), lineVAO(0), faceVAO(0), vboInitFlg(false), realType(fk_RealShapeType::OTHER)
{
	SetObjectType(argObjType);


	FlushAttr = []() {};

	return;
}

fk_Shape::~fk_Shape()
{
	if (pointVAO != 0) DeleteBuffer(pointVAO);
	if (lineVAO != 0) DeleteBuffer(lineVAO);
	if (faceVAO != 0) DeleteBuffer(faceVAO);

	int tmpID = 0;

	for (auto p : attrMapI) {
		tmpID = get<0>(p.second);
		if (tmpID != -1) {
			DeleteBuffer(GLuint(tmpID));
		}
	}

	for (auto p : attrMapF) {
		tmpID = get<0>(p.second);
		if (tmpID != -1) {
			DeleteBuffer(GLuint(tmpID));
		}
	}

	for (auto p : intSelf) {
		delete p.second;
	}

	for (auto p : floatSelf) {
		delete p.second;
	}

	return;
}

void fk_Shape::SetPaletteData(fk_Palette *argPal)
{
	palette = argPal;
	return;
}

void fk_Shape::setPaletteData(fk_Palette *argPal)
{
	SetPaletteData(argPal);
	return;
}

fk_Palette * fk_Shape::getPaletteData(void)
{
	return palette;
}

void fk_Shape::clearMaterial(void)
{
	palette->clearMaterial();
	return;
}

void fk_Shape::setObjMaterialID(int argID)
{
	palette->setObjMaterialID(argID);
	materialMode = fk_MaterialMode::CHILD;
	return;
}

void fk_Shape::pushPalette(fk_Material &argMat)
{
	palette->pushPalette(&argMat);
	materialMode = fk_MaterialMode::PARENT;
	return;
}

void fk_Shape::setPalette(fk_Material &argMat, int argID)
{
	palette->setPalette(&argMat, argID);
	materialMode = fk_MaterialMode::PARENT;
	return;
}

void fk_Shape::setMaterialMode(fk_MaterialMode argMode)
{
	materialMode = argMode;
	return;
}

fk_MaterialMode fk_Shape::getMaterialMode(void)
{
	return materialMode;
}

int fk_Shape::getObjMaterialID(void)
{
	return palette->getObjMaterialID();
}

int fk_Shape::getPaletteSize(void)
{
	return palette->getPaletteSize();
}

fk_Material * fk_Shape::getMaterial(int argID)
{
	return palette->getMaterial(argID);
}

vector<fk_Material> * fk_Shape::getMaterialVector(void)
{
	return palette->getMaterialVector();
}

fk_RealShapeType fk_Shape::getRealShapeType(void)
{
	return realType;
}

void fk_Shape::SetPointVAO(GLuint argVAO)
{
	pointVAO = argVAO;
}

void fk_Shape::SetLineVAO(GLuint argVAO)
{
	lineVAO = argVAO;
}

void fk_Shape::SetFaceVAO(GLuint argVAO)
{
	faceVAO = argVAO;
}

GLuint fk_Shape::GetPointVAO(void)
{
	return pointVAO;
}

GLuint fk_Shape::GetLineVAO(void)
{
	return lineVAO;
}

GLuint fk_Shape::GetFaceVAO(void)
{
	return faceVAO;
}

void fk_Shape::DeleteMapI(string argName)
{
	if(attrMapI.find(argName) != attrMapI.end()) {
		int tmpID = get<0>(attrMapI[argName]);
		if(tmpID != -1) {
			DeleteBuffer(GLuint(tmpID));
		}
		attrMapI.erase(argName);
	}
}	

void fk_Shape::DeleteMapF(string argName)
{
	if(attrMapF.find(argName) != attrMapF.end()) {
		int tmpID = get<0>(attrMapF[argName]);
		if(tmpID != -1) {
			DeleteBuffer(GLuint(tmpID));
		}
		attrMapF.erase(argName);
	}
}	

void fk_Shape::setShaderAttribute(string argName, int argDim,
								  vector<int> *argValue, bool argSelf)
{
	if(argValue == nullptr || argDim < 1 || argDim > 4) return;
	int id = -1;

	DeleteMapF(argName);
	
	if(attrMapI.find(argName) != attrMapI.end()) id = get<0>(attrMapI[argName]);

	if(argSelf == true) {
		vector<int> *array;
		if(intSelf.find(argName) == intSelf.end()) {
			array = new vector<int>();
			intSelf[argName] = array;
		} else {
			array = intSelf[argName];
		}
		*array = *argValue;
		attrMapI[argName] = shapeAttrI(id, argDim, array);
	} else {
		attrMapI[argName] = shapeAttrI(id, argDim, argValue);
	}
	attrModify[argName] = true;
}

void fk_Shape::setShaderAttribute(string argName, int argDim,
								  vector<float> *argValue, bool argSelf)
{
	if(argValue == nullptr || argDim < 1 || argDim > 4) return;
	int id = -1;

	DeleteMapI(argName);

	if(attrMapF.find(argName) != attrMapF.end()) id = get<0>(attrMapF[argName]);

	if(argSelf == true) {
		vector<float> *array;
		if(floatSelf.find(argName) == floatSelf.end()) {
			array = new vector<float>();
			floatSelf[argName] = array;
		} else {
			array = floatSelf[argName];
		}
		
		*array = *argValue;
		attrMapF[argName] = shapeAttrF(id, argDim, array);
	} else {
		attrMapF[argName] = shapeAttrF(id, argDim, argValue);
	}
	
	attrModify[argName] = true;
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
	if(vboInitFlg == true) return;

	for(auto itr = attrMapI.begin(); itr != attrMapI.end(); ++itr) {
		if(get<0>(itr->second) == -1) {
			get<0>(itr->second) = int(GenBuffer());
		}
	}

	for(auto itr = attrMapF.begin(); itr != attrMapF.end(); ++itr) {
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
	int vbo, dim;
	vector<float> *fArray;
	vector<int> *iArray;

	for(auto itr = attrMapI.begin(); itr != attrMapI.end(); ++itr) {
		if(argTable->find(itr->first) == argTable->end()) continue;
		loc = GLuint(argTable->at(itr->first));
		vbo = get<0>(itr->second);
		glBindBuffer(GL_ARRAY_BUFFER, GLuint(vbo));
		dim = get<1>(itr->second);
		glVertexAttribIPointer(loc, dim, GL_INT, 0, 0);
		if(attrModify[itr->first] == true) {
			iArray = get<2>(itr->second);
			size = iArray->size();
			glBufferData(GL_ARRAY_BUFFER,
						 GLsizeiptr(sizeof(int) * size),
						 iArray->data(), GL_STATIC_DRAW);
			attrModify[itr->first] = false;
		}
		glEnableVertexAttribArray(loc);
	}

	for(auto itr = attrMapF.begin(); itr != attrMapF.end(); ++itr) {
		if(argTable->find(itr->first) == argTable->end()) continue;
		loc = GLuint(argTable->at(itr->first));
		vbo = get<0>(itr->second);
		glBindBuffer(GL_ARRAY_BUFFER, GLuint(vbo));
		dim = get<1>(itr->second);
		glVertexAttribPointer(loc, dim, GL_FLOAT, GL_FALSE, 0, 0);
		if(attrModify[itr->first] == true) {
			fArray = get<2>(itr->second);
			size = fArray->size();
			glBufferData(GL_ARRAY_BUFFER,
						 GLsizeiptr(sizeof(float) * size),
						 fArray->data(), GL_STATIC_DRAW);
			attrModify[itr->first] = false;
		}
		glEnableVertexAttribArray(loc);
	}

	return;
}

void fk_Shape::modifyAttribute(string argName)
{
	attrModify[argName] = true;
}

void fk_Shape::FinishSetVBO(void)
{
	vboInitFlg = true;
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
	for(auto itr = attrModify.begin(); itr != attrModify.end(); ++itr) {
		itr->second = true;
	}
	vboInitFlg = false;
}
