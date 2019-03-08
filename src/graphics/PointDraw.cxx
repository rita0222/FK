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
#include <FK/PointDraw.H>
#include <FK/OpenGL.H>
#include <FK/Model.h>
#include <FK/Point.h>
#include <FK/Solid.h>
#include <FK/IndexFace.h>
#include <FK/Vertex.h>
#include <FK/Curve.h>
#include <FK/Surface.h>

using namespace std;
using namespace FK;

fk_PointDraw::fk_PointDraw(void)
{
	shader = nullptr;

	return;
}

fk_PointDraw::~fk_PointDraw()
{
	delete shader;
	return;
}
/*
void fk_PointDraw::PointModelShaderSetup(void)
{
	pointModelShader = new fk_ShaderBinder();
 	auto prog = pointModelShader->getProgram();
	auto param = pointModelShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Point_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Point_Point_FS.out"
		;

	if(prog->validate() == false) {
		fk_Window::printf("Shader Error");
		fk_Window::putString(prog->getLastError());
	}

	param->reserveAttribute(fk_Shape::vertexName);
	param->reserveAttribute(fk_Shape::pointElementAliveName);
	
	glBindFragDataLocation(prog->getProgramID(), 0, fragmentName.c_str());

	prog->link();
	return;
}

void fk_PointDraw::PointElemShaderSetup(void)
{
	pointElemShader = new fk_ShaderBinder();
 	auto prog = pointElemShader->getProgram();
	auto param = pointElemShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Point_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Point_Point_FS.out"
		;

	if(prog->validate() == false) {
		fk_Window::printf("Shader Error");
		fk_Window::putString(prog->getLastError());
	}

	param->reserveAttribute(fk_Shape::vertexName);
	param->reserveAttribute(fk_Shape::pointElementColorName);
	param->reserveAttribute(fk_Shape::pointElementAliveName);
	
	glBindFragDataLocation(prog->getProgramID(), 0, fragmentName.c_str());

	prog->link();

	return;
}

void fk_PointDraw::IFSShaderSetup(void)
{
	ifsShader = new fk_ShaderBinder();
 	auto prog = ifsShader->getProgram();
	auto param = ifsShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Point_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Point_IFS_FS.out"
		;

	if(prog->validate() == false) {
		fk_Window::printf("Shader Error");
		fk_Window::putString(prog->getLastError());
	}

	param->reserveAttribute(fk_Shape::vertexName);
	
	glBindFragDataLocation(prog->getProgramID(), 0, fragmentName.c_str());

	prog->link();
	return;
}
*/

void fk_PointDraw::ShaderSetup(void)
{
	shader = new fk_ShaderBinder();
 	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Point_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Point_FS.out"
		;

	if(prog->validate() == false) {
		fk_Window::printf("Shader Error");
		fk_Window::putString(prog->getLastError());
	}

	param->reserveAttribute(fk_Shape::vertexName);
	param->reserveAttribute(fk_Shape::pointElementColorName);
	param->reserveAttribute(fk_Shape::pointElementAliveName);

	auto progID = prog->getProgramID();

	glBindFragDataLocation(progID, 0, fragmentName.c_str());

	prog->link();

	vsModelID = glGetSubroutineIndex(progID, GL_VERTEX_SHADER, "PointModelVS");
	vsElemID = glGetSubroutineIndex(progID, GL_VERTEX_SHADER, "PointElemVS");
	vsIFSID = glGetSubroutineIndex(progID, GL_VERTEX_SHADER, "PointIFSVS");
	fsPointID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "PointPointFS");
	fsIFSID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "PointIFSFS");

	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &vsModelID);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &fsPointID);

	return;
}
	
GLuint fk_PointDraw::VAOSetup(fk_Shape *argShape)
{
	GLuint 			vao;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	argShape->SetPointVAO(vao);
	argShape->DefineVBO();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//fk_Window::printf("Point VAO = %d", vao);
	return vao;
}

void fk_PointDraw::DrawShapePoint(fk_Model *argModel)
{
	fk_Shape *shape = argModel->getShape();
	fk_RealShapeType shapeType = shape->getRealShapeType();
	fk_ElementMode mode = argModel->getElementMode();
	int pointSize;

	if(shader == nullptr) ShaderSetup();

	auto parameter = shader->getParameter();
	SetParameter(parameter);
	parameter->setRegister(fk_Shape::pointModelColorName, &(argModel->getPointColor()->col));

	shader->ProcPreShader();

	switch(shape->getRealShapeType()) {
	  case FK_SHAPE_POINT:
		switch(mode) {
		  case FK_ELEM_MODEL:
			glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &vsModelID);
			break;

		  case FK_ELEM_ELEMENT:
			glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &vsElemID);
			break;

		  default:
			return;
		}
		
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &fsPointID);
		pointSize = dynamic_cast<fk_Point *>(shape)->getSize();
		break;

	  case FK_SHAPE_IFS:
		glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &vsIFSID);
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &fsIFSID);
		pointSize = dynamic_cast<fk_IndexFaceSet *>(shape)->getPosSize();
		break;

	  default:
		return;
	}
	
	glPointSize((GLfloat)argModel->getPointSize());

	switch(shapeType) {
	  case FK_SHAPE_POINT:
	  case FK_SHAPE_IFS:
		Draw_Point(argModel, parameter, pointSize);
		break;

/*
	  case FK_SHAPE_SOLID:
		DrawSolidPointNormal(argModel, argFlag);
		break;

	  case FK_SHAPE_CURVE:
		DrawCurvePointNormal(argModel, argFlag);
		break;
		
	  case FK_SHAPE_SURFACE:
		DrawSurfacePointNormal(argModel, argFlag);
		break;
*/
	  default:
		break;
	}

	shader->ProcPostShader();

	return;
}

void fk_PointDraw::Draw_Point(fk_Model *argModel, fk_ShaderParameter *argParam, int argSize)
{
	fk_Shape	*shape = argModel->getShape();
	GLuint 		vao = shape->GetPointVAO();

	if(vao == 0) vao = VAOSetup(shape);
	glBindVertexArray(vao);
	shape->BindShaderBuffer(argParam->getAttrTable());
	glDrawArrays(GL_POINTS, 0, GLsizei(argSize));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return;
}

/*
void fk_PointDraw::DrawSolidPointModel(fk_Model *argObj)
{
	fk_Solid				*solidP;
	fk_Color				*ModelColor;
	double					orgSize;
	list<fk_Vertex *>		*vertexStack;
	bool					reverseFlag = argObj->getReverseDrawMode();

	list<fk_Vertex *>::iterator				ite;
	list<fk_Vertex *>::reverse_iterator		rite;


	solidP = static_cast<fk_Solid *>(argObj->getShape());
	if(solidP->checkDB() == false) return;
	if(solidP->getNextV(nullptr) == nullptr) return;

	if(solidP->GetVCacheStatus() == false) {
		solidP->MakeVCache();
	}

	vertexStack = solidP->GetVCache();

	if(argFlg == true) {
		ModelColor = argObj->getInhPointColor();
		if(ModelColor == nullptr) {
			ModelColor = argObj->getInhMaterial()->getAmbient();
		}
	} else {
		ModelColor = (*solidP->getMaterialVector())[0].getAmbient();
	}

#ifndef OPENGL4
	glColor4fv(&ModelColor->col[0]);
#endif
	orgSize = argObj->getSize();

	if(reverseFlag == false) {
		for(ite = vertexStack->begin(); ite != vertexStack->end(); ++ite) {
			DrawSolidPointNormalElem(*ite, orgSize);
		}
	} else {
		for(rite = vertexStack->rbegin(); rite != vertexStack->rend(); ++rite) {
			DrawSolidPointNormalElem(*rite, orgSize);
		}
	}

	return;
}

void fk_PointDraw::DrawSolidPointNormalElem(fk_Vertex *argV, double argOrgSize)
{
	double trueSize;

	trueSize = argV->getDrawSize();
	if(trueSize < 0.0) {
		glPointSize(static_cast<GLfloat>(argOrgSize));
	} else {
		glPointSize(static_cast<GLfloat>(trueSize));
	}

#ifndef OPENGL4	
	glBegin(GL_POINTS);
	glVertex3dv(static_cast<GLdouble *>(&(argV->GetPositionP()->x)));
	glEnd();
#endif
	return;
}


void fk_PointDraw::DrawIFSPointNormal(fk_Model *argObj, bool argFlag)
{
	fk_IndexFaceSet		*ifsetP;
	fk_Color			*modelColor;

	ifsetP = static_cast<fk_IndexFaceSet *>(argObj->getShape());

	if(argFlag == true) {
		modelColor = argObj->getInhPointColor();
		if(modelColor == nullptr) {
			modelColor = argObj->getInhMaterial()->getAmbient();
		}
	} else {
		modelColor = (*ifsetP->getMaterialVector())[0].getAmbient();
	}

#ifndef OPENGL4
	glColor4fv(&modelColor->col[0]);
	
	if(arrayState == true) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &ifsetP->pos[0]);
		glDrawArrays(GL_POINTS, 0, ifsetP->posSize);
	} else {
		glBegin(GL_POINTS);
		for(_st id = 0; id < static_cast<_st>(ifsetP->posSize); id++) {
			glVertex3fv(static_cast<GLfloat *>(&ifsetP->pos[id].x));
		}
		glEnd();
	}
#endif

	return;
}


void fk_PointDraw::DrawCurvePointNormal(fk_Model *argObj, bool argFlag)
{
	fk_Curve *curve = static_cast<fk_Curve *>(argObj->getShape());
	fk_Color *modelColor;

	if(argFlag == true) {
		modelColor = argObj->getInhPointColor();
		if(modelColor == nullptr) {
			modelColor = argObj->getInhMaterial()->getAmbient();
		}
	} else {
		modelColor = (*curve->getMaterialVector())[0].getAmbient();
	}

#ifndef OPENGL4	
	glColor4fv(&modelColor->col[0]);

	curve->makeCache();
	_st div = static_cast<_st>(curve->getDiv());
	auto vArray = curve->getPosCache();

	glBegin(GL_POINTS);
	for(_st i = 0; i < div; ++i) {
		auto vPos = &((*vArray)[i]);
		glVertex3dv(static_cast<GLdouble *>(&(vPos->x)));
	}
	glEnd();
#endif
	
	return;
}

void fk_PointDraw::DrawSurfacePointNormal(fk_Model *argObj, bool argMode)
{
	fk_Surface	*surf = static_cast<fk_Surface *>(argObj->getShape());
	fk_Color	*modelColor;
	
	if(argMode == true) {
		modelColor = argObj->getInhPointColor();
		if(modelColor == nullptr) {
			modelColor = argObj->getInhMaterial()->getAmbient();
		}
	} else {
		modelColor = surf->getMaterial(0)->getAmbient();
	}

#ifndef OPENGL4
	glColor4fv(&modelColor->col[0]);

	surf->makeCache();
	_st div = static_cast<_st>(surf->getDiv());
	auto vArray = surf->getPosCache();

	glBegin(GL_POINTS);
	for(_st i = 0; i < (div+1)*(div+1); ++i) {
		auto vPos = &((*vArray)[i]);
		glVertex3dv(static_cast<GLdouble *>(&(vPos->x)));
	}
	glEnd();
#endif
	return;
}
*/
