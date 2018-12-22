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

#include <FK/Shape.h>
#include <FK/Window.h>

using namespace std;
using namespace FK;

const string fk_Shape::vertexName = "fk_Vertex";
const string fk_Shape::normalName = "fk_Normal";
const string fk_Shape::pointModelColorName = "fk_PointModelColor";
const string fk_Shape::pointElementColorName = "fk_PointElementColor";
const string fk_Shape::pointElementAliveName = "fk_PointElementAlive";
const string fk_Shape::lineModelColorName = "fk_LineModelColor";
const string fk_Shape::lineElementColorName = "fk_LineElementColorName";

fk_Shape::fk_Shape(fk_ObjectType argObjType)
	: palette(&defaultPalette), materialMode(FK_NONE_MODE),
	  pointVAO(0), lineVAO(0), faceVAO(0), vboInitFlg(false)
{
	SetObjectType(argObjType);
	return;
}

fk_Shape::~fk_Shape()
{
	if(pointVAO != 0) glDeleteBuffers(1, &pointVAO);
	if(lineVAO != 0) glDeleteBuffers(1, &lineVAO);
	if(faceVAO != 0) glDeleteBuffers(1, &faceVAO);
		
	int tmpID1 = 0;
	GLuint tmpID2 = 0;

	for(auto p : attrMapI) {
		tmpID1 = get<0>(p.second);
		if(tmpID1 != -1) {
			tmpID2 = GLuint(tmpID1);
			glDeleteBuffers(1, &tmpID2);
		}
	}

	for(auto p : attrMapF) {
		tmpID1 = get<0>(p.second);
		if(tmpID1 != -1) {
			tmpID2 = GLuint(tmpID1);
			glDeleteBuffers(1, &tmpID2);
		}
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
	materialMode = FK_CHILD_MODE;
	return;
}

void fk_Shape::pushPalette(fk_Material &argMat)
{
	palette->pushPalette(&argMat);
	materialMode = FK_PARENT_MODE;
	return;
}

void fk_Shape::setPalette(fk_Material &argMat, int argID)
{
	palette->setPalette(&argMat, argID);
	materialMode = FK_PARENT_MODE;
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
	switch(getObjectType()) {
	  case FK_INDEXFACESET:
	  case FK_BLOCK:
	  case FK_CIRCLE:
	  case FK_SPHERE:
	  case FK_PRISM:
	  case FK_CONE:
	  case FK_CAPSULE:
		return FK_SHAPE_IFS;

	  case FK_SOLID:
	  case FK_POLYGON:
	  case FK_POLYLINE:
	  case FK_CLOSEDLINE:
		return FK_SHAPE_SOLID;

	  case FK_RECTTEXTURE:
	  case FK_TRITEXTURE:
	  case FK_MESHTEXTURE:
	  case FK_IFSTEXTURE:
	  case FK_ARTEXTURE:
		return FK_SHAPE_TEXTURE;

	  case FK_POINT:
	  case FK_PARTICLESET:
		return FK_SHAPE_POINT;

	  case FK_LINE:
		  return FK_SHAPE_LINE;
		  
	  case FK_CURVE:
	  case FK_BEZCURVE:
	  case FK_BSPLCURVE:
		return FK_SHAPE_CURVE;

	  case FK_SURFACE:
	  case FK_BEZSURFACE:
	  case FK_BSPLSURFACE:
	  case FK_GREGORY:
		return FK_SHAPE_SURFACE;
		
	  case FK_LIGHT:
		return FK_SHAPE_LIGHT;

	  default:
		break;
	}
	return FK_SHAPE_OTHER;
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
			GLuint tmpID2 = GLuint(tmpID);
			glDeleteBuffers(1, &tmpID2);
		}
		attrMapI.erase(argName);
	}
}	

void fk_Shape::DeleteMapF(string argName)
{
	if(attrMapF.find(argName) != attrMapF.end()) {
		int tmpID = get<0>(attrMapF[argName]);
		if(tmpID != -1) {
			GLuint tmpID2 = GLuint(tmpID);
			glDeleteBuffers(1, &tmpID2);
		}
		attrMapF.erase(argName);
	}
}	

void fk_Shape::setShaderAttribute(string argName, int argDim, vector<int> *argValue)
{
	int id = -1;

	DeleteMapF(argName);
	
	if(attrMapI.find(argName) != attrMapI.end()) id = get<0>(attrMapI[argName]);
	attrMapI[argName] = shapeAttrI(id, argDim, argValue);
	attrModify[argName] = true;
	vboInitFlg = false;
}

void fk_Shape::setShaderAttribute(string argName, int argDim, vector<float> *argValue)
{
	int id = -1;

	DeleteMapI(argName);

	if(attrMapF.find(argName) != attrMapF.end()) id = get<0>(attrMapF[argName]);
	attrMapF[argName] = shapeAttrF(id, argDim, argValue);
	attrModify[argName] = true;
	vboInitFlg = false;
}
	
void fk_Shape::DefineVBO(void)
{
	if(vboInitFlg == true) return;
	int tmpID = 0;
	GLuint tmpUID = 0;
	for(auto itr = attrMapI.begin(); itr != attrMapI.end(); ++itr) {
		tmpID = get<0>(itr->second);
		if(tmpID != -1) {
			tmpUID = GLuint(tmpID);
			glDeleteBuffers(1, &tmpUID);
		}
		glGenBuffers(1, &tmpUID);
		get<0>(itr->second) = int(tmpUID);
	}

	for(auto itr = attrMapF.begin(); itr != attrMapF.end(); ++itr) {
		tmpID = get<0>(itr->second);
		if(tmpID != -1) {
			tmpUID = GLuint(tmpID);
			glDeleteBuffers(1, &tmpUID);
		}
		glGenBuffers(1, &tmpUID);
		get<0>(itr->second) = int(tmpUID);
	}

	vboInitFlg = true;

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

		if(attrModify[itr->first] == true) {
			vbo = get<0>(itr->second);
			dim = get<1>(itr->second);

			glBindBuffer(GL_ARRAY_BUFFER, GLuint(vbo));
			glVertexAttribIPointer(loc, dim, GL_INT, 0, 0);
			iArray = get<2>(itr->second);
			size = iArray->size();
			glBufferData(GL_ARRAY_BUFFER,
						 GLsizeiptr(sizeof(int) * size),
						 &((*iArray)[0]), GL_STATIC_DRAW);
			attrModify[itr->first] = false;
		}
		glEnableVertexAttribArray(loc);
	}

	for(auto itr = attrMapF.begin(); itr != attrMapF.end(); ++itr) {
		if(argTable->find(itr->first) == argTable->end()) continue;
		loc = GLuint(argTable->at(itr->first));

		if(attrModify[itr->first] == true) {
			vbo = get<0>(itr->second);
			dim = get<1>(itr->second);

			glBindBuffer(GL_ARRAY_BUFFER, GLuint(vbo));
			glVertexAttribPointer(loc, dim, GL_FLOAT, GL_FALSE, 0, 0);
		
			fArray = get<2>(itr->second);
			size = fArray->size();
			glBufferData(GL_ARRAY_BUFFER,
						 GLsizeiptr(sizeof(float) * size),
						 &((*fArray)[0]), GL_STATIC_DRAW);
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

void fk_Shape::updateAttr(void)
{
	for(auto itr = attrModify.begin(); itr != attrModify.end(); ++itr) {
		itr->second = true;
	}
}
