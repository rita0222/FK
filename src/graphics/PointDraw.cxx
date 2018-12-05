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
#ifdef FK_D3D
#include "PointDraw_D3D.cxx"
#else

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
	SetArrayState(false);
	shader = nullptr;
}

fk_PointDraw::~fk_PointDraw()
{
	if(shader != nullptr) delete shader;
	return;
}

void fk_PointDraw::SetArrayState(bool argState)
{
	arrayState = argState;
	return;
}

void fk_PointDraw::SetProjectMatrix(fk_Matrix *argM)
{
	projM = argM;
	return;
}

void fk_PointDraw::SetCamera(fk_Model *argCamera)
{
	cameraM = argCamera->getInhInvMatrix();
	return;
}

void fk_PointDraw::ShaderSetup(fk_Model *argM)
{
	shader = new fk_ShaderBinder();
 	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	FK_UNUSED(param);

	prog->vertexShaderSource = "#version 410 core\n";
	prog->vertexShaderSource += "uniform mat4 modelview;\n";
	prog->vertexShaderSource += "uniform mat4 projection;\n";
	prog->vertexShaderSource += "uniform vec4 color;\n";
	prog->vertexShaderSource += "in vec4 position;\n";
	prog->vertexShaderSource += "in int drawmode;\n";
	prog->vertexShaderSource += "flat out vec4 f_color;\n";
	prog->vertexShaderSource += "void main()\n";
	prog->vertexShaderSource += "{\n";
	prog->vertexShaderSource += "    gl_Position = projection * modelview * position;\n";
	prog->vertexShaderSource += "    f_color = color;\n";
	prog->vertexShaderSource += "    if(drawmode == 2) {\n";
	prog->vertexShaderSource += "    	f_color = vec4(1.0, 0.0, 0.0, 1.0);\n";
	//prog->vertexShaderSource += "    } else {\n";
	//prog->vertexShaderSource += "    	f_color = vec4(0.0, 0.0, 1.0, 1.0);\n";
	prog->vertexShaderSource += "    }\n";
	prog->vertexShaderSource += "}\n";

	prog->fragmentShaderSource = "#version 410 core\n";
	prog->fragmentShaderSource += "flat in vec4 f_color;\n";
	prog->fragmentShaderSource += "out vec4 fragment;\n";
	prog->fragmentShaderSource += "void main()\n";
	prog->fragmentShaderSource += "{\n";
	prog->fragmentShaderSource += "    fragment = f_color;\n";
	prog->fragmentShaderSource += "}\n";

	if(prog->validate() == false) {
		fk_Window::printf("Shader Error");
		fk_Window::putString(prog->getLastError());
	}
	shader->bindModel(argM);

	glBindAttribLocation(prog->getProgramID(), 1, "position");
	glBindAttribLocation(prog->getProgramID(), 2, "drawmode");
	glBindFragDataLocation(prog->getProgramID(), 0, "fragment");

	GLuint pID = prog->getProgramID();
	fk_Window::printf("A: pid = %d, (%d, %d)", pID,
					  glGetAttribLocation(pID, "position"),
					  glGetAttribLocation(pID, "drawmode"));

	prog->link();


	fk_Window::printf("B: pid = %d, (%d, %d)", pID,
					  glGetAttribLocation(pID, "position"),
					  glGetAttribLocation(pID, "drawmode"));

	return;
}

void fk_PointDraw::ParticleVAOSetup(fk_Point *argPoint)
{
	GLuint 			vao;
	GLuint			*vbo;
	float			*pos = &(argPoint->posArray[0]);
	int				*drawmode = &(argPoint->aliveArray[0]);
	int				size = int(argPoint->aliveArray.size());
	auto 			prog = shader->getProgram();

	FK_UNUSED(prog);


	GLuint pID = prog->getProgramID();
	fk_Window::printf("C: pid = %d, (%d, %d)", pID,
					  glGetAttribLocation(pID, "position"),
					  glGetAttribLocation(pID, "drawmode"));

	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	argPoint->SetPointVAO(vao);

	vbo = argPoint->GetVBO();

	glGenBuffers(2, &vbo[0]);

	
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBufferData(GL_ARRAY_BUFFER,
				 GLsizeiptr(sizeof(float) * 3) * GLsizeiptr(size),
				 pos, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, 0, 0);
	glBufferData(GL_ARRAY_BUFFER,
				 GLsizeiptr(sizeof(int)) * GLsizeiptr(size),
				 drawmode, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void fk_PointDraw::DrawShapePoint(fk_Model *argObj)
{
	if(shader == nullptr) {
		shader = new fk_ShaderBinder();
		ShaderSetup(argObj);
	}

	if(argObj->preShaderList.empty() == true &&
	   argObj->postShaderList.empty() == true) {
		shader->bindModel(argObj);
	}

	glPointSize((GLfloat)argObj->getSize());

	fk_Matrix modelViewM = cameraM * argObj->getInhMatrix();

	auto parameter = shader->getParameter();
	parameter->setRegister("projection", projM);
	parameter->setRegister("modelview", &modelViewM);
	parameter->setRegister("color", &(argObj->getPointColor()->col));
	DrawShapePointModel(argObj);

	return;
}

void fk_PointDraw::DrawShapePointModel(fk_Model *argObj)
{
	switch(argObj->getShape()->getRealShapeType()) {
	  case FK_SHAPE_POINT:
		DrawParticlePointModel(argObj);
		break;
/*
	  case FK_SHAPE_IFS:
		DrawIFSPointNormal(argObj, argFlag);
		break;

	  case FK_SHAPE_SOLID:
		DrawSolidPointNormal(argObj, argFlag);
		break;

	  case FK_SHAPE_CURVE:
		DrawCurvePointNormal(argObj, argFlag);
		break;
		
	  case FK_SHAPE_SURFACE:
		DrawSurfacePointNormal(argObj, argFlag);
		break;
*/
	  default:
		break;
	}
	return;
}

void fk_PointDraw::DrawParticlePointModel(fk_Model *argObj)
{
	fk_Point		*point = static_cast<fk_Point *>(argObj->getShape());
	float			*pos = &(point->posArray[0]);
	int				*drawmode = &(point->aliveArray[0]);
	int				size = int(point->aliveArray.size());

	GLuint 		vao = point->GetPointVAO();

	if(vao == 0) {
		ParticleVAOSetup(point);
		vao = point->GetPointVAO();
	}

	GLuint *	vbo = point->GetVBO();

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, GLsizeiptr(sizeof(fk_FVector)) * GLsizeiptr(size), pos);
	glBufferData(GL_ARRAY_BUFFER,
				 GLsizeiptr(sizeof(float) * 3) * GLsizeiptr(size),
				 pos, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, 0, 0);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, GLsizeiptr(sizeof(int)) * GLsizeiptr(size), drawmode);
	glBufferData(GL_ARRAY_BUFFER,
				 GLsizeiptr(sizeof(int)) * GLsizeiptr(size),
				 drawmode, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glDrawArrays(GL_POINTS, 0, size);
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

#endif
