﻿#define FK_DEF_SIZETYPE
#include <FK/Error.H>
#include <FK/FaceDraw.H>
#include <FK/OpenGL.H>
#include <FK/IndexFace.h>
#include <FK/Solid.h>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Loop.h>
#include <FK/Surface.h>

using namespace std;
using namespace FK;

typedef list<fk_Loop *>::iterator			loopIte;
typedef list<fk_Loop *>::reverse_iterator	loopRIte;

fk_FaceDraw::fk_FaceDraw(void)
	: phongShader(nullptr), gouraudShader(nullptr),
	  shadowBuf_p_ID(0), shadowON_p_ID(0), shadowOFF_p_ID(0), 
	  shadowBuf_g_ID(0), shadowON_g_ID(0), shadowOFF_g_ID(0)
{
	return;
}

fk_FaceDraw::~fk_FaceDraw()
{
	delete phongShader;
	delete gouraudShader;
	return;
}

void fk_FaceDraw::DrawShapeFace(fk_Model *argModel, bool argShadowMode, bool argShadowSwitch)
{
	auto	shapeType = argModel->getShape()->getRealShapeType();
	auto	drawMode = argModel->getDrawMode();
	auto	modelShader = argModel->getShader();

	if(modelShader != nullptr) {
		shader = modelShader;
		defaultShaderFlag = false;
		if(shader->IsSetup() == false) {
			ParamInit(shader->getProgram(), shader->getParameter());
			shader->SetupDone(true);
		}
	} else {
		if(phongShader == nullptr || gouraudShader == nullptr) ShaderSetup();
		switch(argModel->getShadingMode()) {
		  case fk_ShadingMode::PHONG:
			shader = phongShader;
			break;

		  case fk_ShadingMode::GOURAUD:
			shader = gouraudShader;
			break;

		  default:
			return;
		}
		defaultShaderFlag = true;
	}

	PolygonModeSet(drawMode);

	auto parameter = shader->getParameter();
	SetParameter(parameter);

	if(shapeType == fk_RealShapeType::IFS) {
		Draw_IFS(argModel, parameter, argShadowMode, argShadowSwitch);
	}

	return;
}

void fk_FaceDraw::PolygonModeSet(fk_Draw argDMode)
{
	if((argDMode & fk_Draw::FRONTBACK_FACE) == fk_Draw::FRONTBACK_FACE) {
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else if((argDMode & fk_Draw::BACK_FACE) == fk_Draw::BACK_FACE) {
		glCullFace(GL_FRONT);
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_BACK, GL_FILL);
	} else {
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}

void fk_FaceDraw::PhongSetup(void)
{
	if(phongShader == nullptr) phongShader = new fk_ShaderBinder();
	auto prog = phongShader->getProgram();
	auto param = phongShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Face_Phong_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Face_Phong_FS.out"
		;

	if(prog->validate() == false) {
		fk_PutError("fk_FaceDraw", "PhongSetup", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();

	shadowBuf_p_ID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "ShadowBufDraw");
	shadowON_p_ID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "ShadowONDraw");
	shadowOFF_p_ID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "ShadowOFFDraw");
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &shadowON_p_ID);
	
	return;
}

void fk_FaceDraw::GouraudSetup(void)
{
	if(gouraudShader == nullptr) gouraudShader = new fk_ShaderBinder();
	auto prog = gouraudShader->getProgram();
	auto param = gouraudShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Face_Gouraud_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Face_Gouraud_FS.out"
		;
	
	if(prog->validate() == false) {
		fk_PutError("fk_FaceDraw", "GouraudSetup", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();
	shadowBuf_g_ID = glGetSubroutineIndex(progID, GL_VERTEX_SHADER, "ShadowBufDraw");
	shadowON_g_ID = glGetSubroutineIndex(progID, GL_VERTEX_SHADER, "ShadowONDraw");
	shadowOFF_g_ID = glGetSubroutineIndex(progID, GL_VERTEX_SHADER, "ShadowOFFDraw");
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &shadowON_g_ID);
	return;
}

void fk_FaceDraw::ShaderSetup(void)
{
	PhongSetup();
	GouraudSetup();
}

void fk_FaceDraw::ParamInit(fk_ShaderProgram *argProg, fk_ShaderParameter *argParam)
{
	argParam->reserveAttribute(fk_Shape::vertexName);
	argParam->reserveAttribute(fk_Shape::normalName);
	glBindFragDataLocation(argProg->getProgramID(), 0, fragmentName.c_str());

	argProg->link();
}

GLuint fk_FaceDraw::VAOSetup(fk_Shape *argShape)
{
	GLuint 			vao;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	argShape->SetFaceVAO(vao);
	argShape->DefineVBO();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return vao;
}

void fk_FaceDraw::Draw_IFS(fk_Model *argModel, fk_ShaderParameter *argParam,
						   bool argShadowMode, bool argShadowSwitch)
{
	fk_IndexFaceSet *ifs = dynamic_cast<fk_IndexFaceSet *>(argModel->getShape());
	GLuint			vao = ifs->GetFaceVAO();

	if(vao == 0) {
		vao = VAOSetup(ifs);
	}
	
	glBindVertexArray(vao);
	ifs->FaceIBOSetup();
	ifs->BindShaderBuffer(argParam->getAttrTable());
	shader->ProcPreShader();

	if(defaultShaderFlag == true) SubroutineSetup(argModel, argShadowMode, argShadowSwitch);
	
	glDrawElements(GL_TRIANGLES, GLint(ifs->getFaceSize()*3), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	shader->ProcPostShader();

	return;
}

void fk_FaceDraw::SubroutineSetup(fk_Model *argModel, bool argShadowMode, bool argShadowSwitch)
{
	FK_UNUSED(argShadowMode);

	GLuint ID = 0;

	switch(argModel->getShadingMode()) {
	  case fk_ShadingMode::PHONG:
		ID = (argShadowSwitch) ? shadowBuf_p_ID : ((argShadowMode) ? shadowON_p_ID : shadowOFF_p_ID);
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &ID);
		break;

	  case fk_ShadingMode::GOURAUD:
		ID = (argShadowSwitch) ? shadowBuf_g_ID : ((argShadowMode) ? shadowON_g_ID : shadowOFF_g_ID);
		glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &ID);
		break;

	  default:
		break;
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
