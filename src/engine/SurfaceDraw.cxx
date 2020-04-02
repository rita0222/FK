#define FK_DEF_SIZETYPE
#include <FK/SurfaceDraw.H>
#include <FK/OpenGL.H>
#include <FK/Model.h>
#include <FK/BezSurface.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_SurfaceDraw::fk_SurfaceDraw(fk_SurfaceDrawMode argMode)
{
	lineShader = nullptr;
	pointShader = nullptr;
	offShader = nullptr;
	hardShader = nullptr;
	softFastShader = nullptr;
	softNiceShader = nullptr;
	shadowDrawShader = nullptr;
	shadowDiscardShader = nullptr;

	mode = argMode;
	drawBezID = 0;
	drawGregID = 0;
	shadowBezID = 0;
	shadowGregID = 0;
	return;
}

fk_SurfaceDraw::~fk_SurfaceDraw()
{
	delete lineShader;
	delete pointShader;
	delete offShader;
	delete hardShader;
	delete softFastShader;
	delete softNiceShader;
	delete shadowDrawShader;
	delete shadowDiscardShader;

	return;
}


void fk_SurfaceDraw::DrawShapeSurface(fk_Model *argModel,
									  fk_ShadowMode argShadowMode, bool argShadowSwitch)
{
	auto col = &(argModel->getCurveColor()->col);
	auto modelShader = argModel->getShader();

	if(modelShader != nullptr) {
		drawShader = modelShader;
		defaultShaderFlag = false;
		if(drawShader->IsSetup() == false) {
			ParamInit(drawShader->getProgram(), drawShader->getParameter());
			drawShader->SetupDone(true);
		}
	} else {
		DefaultShaderSetup(argShadowMode);
	}

	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	fk_ShaderParameter *parameter;
	if(argShadowSwitch == true && defaultShaderFlag == true) {
		ShadowSetup(argModel);
		parameter = shadowShader->getParameter();
	} else {
		parameter = drawShader->getParameter();
	}

	SetParameter(parameter);
	parameter->setRegister(fk_Shape::curveModelColorName, col, fk_Shape::curveModelColorName);

	if(argModel->getShape()->getObjectType() == fk_Type::BEZSURFACE) {
		fk_BezSurface *bezSurf = dynamic_cast<fk_BezSurface *>(argModel->getShape());
		parameter->setRegister(fk_Shape::degreeName, bezSurf->getDegree(), fk_Shape::degreeName);
	} else {
		// Gregory Surface
		parameter->setRegister(fk_Shape::degreeName, 3, fk_Shape::degreeName);
	}

	Draw_Surface(argModel, argShadowSwitch);
	return;
}

void fk_SurfaceDraw::DefaultShaderSetup(fk_ShadowMode argShadowMode)
{
	switch(mode) {
	  case fk_SurfaceDrawMode::LINE:
		if(lineShader == nullptr) LineShaderInit();
		drawShader = lineShader;
		break;

	  case fk_SurfaceDrawMode::POINT:
		if(pointShader == nullptr) PointShaderInit();
		drawShader = pointShader;
		break;

	  case fk_SurfaceDrawMode::FACE:
		switch(argShadowMode) {
		  case fk_ShadowMode::HARD:
			if(hardShader == nullptr) HardShaderInit();
			drawShader = hardShader;
			break;

		  case fk_ShadowMode::SOFT_FAST:
			if(softFastShader == nullptr) SoftFastShaderInit();
			drawShader = softFastShader;
			break;

		  case fk_ShadowMode::SOFT_NICE:
			if(softNiceShader == nullptr) SoftNiceShaderInit();
			drawShader = softNiceShader;
			break;

		  default:
			if(offShader == nullptr) OffShaderInit();
			drawShader = offShader;
			break;
		}
		break;

	  default:
		break;
	}
	defaultShaderFlag = true;
}

void fk_SurfaceDraw::LineShaderInit(void)
{
	lineShader = new fk_ShaderBinder();

	auto prog = lineShader->getProgram();
	auto param = lineShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Surface_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Surface_FS_Line.out"
		;

	prog->tessEvalShaderSource =
		#include "GLSL/Surface_TE_Line.out"
		;

	prog->geometryShaderSource =
		#include "GLSL/Surface_GS_Line.out"
		;

	if(prog->validate() == false) {
		fk_PutError("fk_SurfaceDraw", "LineShaderInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();

	drawBezID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "BezSurf");
	drawGregID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "GregSurf");
	glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &drawBezID);

	return;
}

void fk_SurfaceDraw::PointShaderInit(void)
{
	pointShader = new fk_ShaderBinder();

	auto prog = pointShader->getProgram();
	auto param = pointShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Surface_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Surface_FS_Line.out"
		;

	prog->tessEvalShaderSource =
		#include "GLSL/Surface_TE_Point.out"
		;

	if(prog->validate() == false) {
		fk_PutError("fk_SurfaceDraw", "PointShaderInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();

	drawBezID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "BezSurf");
	drawGregID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "GregSurf");
	glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &drawBezID);

	return;
}

void fk_SurfaceDraw::OffShaderInit(void)
{
	offShader = new fk_ShaderBinder();

	auto prog = offShader->getProgram();
	auto param = offShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Surface_VS.out"
		;

	prog->tessEvalShaderSource =
		#include "GLSL/Surface_TE_Face.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Face_FS_Phong_Common.out"
		;

	prog->fragmentShaderSource +=
		#include "GLSL/Face_FS_Phong_Off.out"
		;


	if(prog->validate() == false) {
		fk_PutError("fk_SurfaceDraw", "OffShaderInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();

	drawBezID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "BezSurf");
	drawGregID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "GregSurf");
	glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &drawBezID);

	return;
}

void fk_SurfaceDraw::HardShaderInit(void)
{
	hardShader = new fk_ShaderBinder();

	auto prog = hardShader->getProgram();
	auto param = hardShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Surface_VS.out"
		;

	prog->tessEvalShaderSource =
		#include "GLSL/Surface_TE_Face.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Face_FS_Phong_Common.out"
		;

	prog->fragmentShaderSource +=
		#include "GLSL/Face_FS_Phong_Hard.out"
		;


	if(prog->validate() == false) {
		fk_PutError("fk_SurfaceDraw", "HardShaderInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();

	drawBezID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "BezSurf");
	drawGregID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "GregSurf");
	glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &drawBezID);

	return;
}

void fk_SurfaceDraw::SoftFastShaderInit(void)
{
	softFastShader = new fk_ShaderBinder();

	auto prog = softFastShader->getProgram();
	auto param = softFastShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Surface_VS.out"
		;

	prog->tessEvalShaderSource =
		#include "GLSL/Surface_TE_Face.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Face_FS_Phong_Common.out"
		;

	prog->fragmentShaderSource +=
		#include "GLSL/Face_FS_Phong_SoftFast.out"
		;


	if(prog->validate() == false) {
		fk_PutError("fk_SurfaceDraw", "SoftFastShaderInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();

	drawBezID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "BezSurf");
	drawGregID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "GregSurf");
	glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &drawBezID);

	return;
}

void fk_SurfaceDraw::SoftNiceShaderInit(void)
{
	softNiceShader = new fk_ShaderBinder();

	auto prog = softNiceShader->getProgram();
	auto param = softNiceShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Surface_VS.out"
		;

	prog->tessEvalShaderSource =
		#include "GLSL/Surface_TE_Face.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Face_FS_Phong_Common.out"
		;

	prog->fragmentShaderSource +=
		#include "GLSL/Face_FS_Phong_SoftNice.out"
		;


	if(prog->validate() == false) {
		fk_PutError("fk_SurfaceDraw", "SoftNiceShaderInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();

	drawBezID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "BezSurf");
	drawGregID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "GregSurf");
	glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &drawBezID);

	return;
}

void fk_SurfaceDraw::ShadowSetup(fk_Model *argModel)
{
	if(shadowDrawShader == nullptr) ShadowDrawInit();
	if(shadowDiscardShader == nullptr) ShadowDiscardInit();
	shadowShader = (argModel->getShadowEffect()) ? shadowDrawShader : shadowDiscardShader;
}
	
void fk_SurfaceDraw::ShadowDrawInit(void)
{
	if(shadowDrawShader == nullptr) shadowDrawShader = new fk_ShaderBinder();
	auto prog = shadowDrawShader->getProgram();
	auto param = shadowDrawShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Surface_VS.out"
		;

	prog->tessEvalShaderSource =
		#include "GLSL/Surface_TE_Shadow.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Surface_FS_Shadow.out"
		;

	if(prog->validate() == false) {
		fk_PutError("fk_FaceDraw", "ShadowDrawInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();

	shadowBezID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "BezSurf");
	shadowGregID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "GregSurf");

	glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &shadowBezID);
	return;
}

void fk_SurfaceDraw::ShadowDrawInit(void)
{
	if(shadowDrawShader == nullptr) shadowDrawShader = new fk_ShaderBinder();
	auto prog = shadowDrawShader->getProgram();
	auto param = shadowDrawShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Surface_VS.out"
		;

	prog->tessEvalShaderSource =
		#include "GLSL/Surface_TE_Shadow.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Surface_FS_Shadow.out"
		;

	if(prog->validate() == false) {
		fk_PutError("fk_FaceDraw", "ShadowDrawInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();

	shadowBezID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "BezSurf");
	shadowGregID = glGetSubroutineIndex(progID, GL_TESS_EVALUATION_SHADER, "GregSurf");

	glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &shadowBezID);
	return;
}

void fk_SurfaceDraw::ParamInit(fk_ShaderProgram *argProg, fk_ShaderParameter *argParam)
{
	argParam->reserveAttribute(fk_Shape::ctrlPosName);
	glBindFragDataLocation(argProg->getProgramID(), 0, fragmentName.c_str());
	argProg->link();
}

GLuint fk_SurfaceDraw::VAOSetup(fk_Shape *argShape)
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

void fk_SurfaceDraw::Draw_Surface(fk_Model *argModel, bool argShadowSwitch)
{
	fk_Surface	*surf = dynamic_cast<fk_Surface *>(argModel->getShape());
	GLuint		vao = surf->GetFaceVAO();
	GLfloat		div = float(surf->getDiv());
	GLfloat		tessOut[4] = {div, div, div, div};
	GLfloat		tessIn[2] = {div, div};
	fk_ShaderBinder *shader = (argShadowSwitch) ? shadowShader : drawShader;

	if(vao == 0) {
		vao = VAOSetup(surf);
	}
	
	glBindVertexArray(vao);
	surf->BindShaderBuffer(shader->getParameter()->getAttrTable());

	shader->ProcPreShader();
	if(defaultShaderFlag == true) SubroutineSetup(argModel, argShadowSwitch);

	glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, tessOut);
	glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, tessIn);
	glPatchParameteri(GL_PATCH_VERTICES, surf->getCtrlSize());
	glDrawArrays(GL_PATCHES, 0, surf->getCtrlSize());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader->ProcPostShader();
	return;
}

void fk_SurfaceDraw::SubroutineSetup(fk_Model *argModel, bool argShadowSwitch)
{
	GLuint ID = 0;

	switch(argModel->getShape()->getObjectType()) {
	  case fk_Type::BEZSURFACE:
		ID = (argShadowSwitch) ? shadowBezID : drawBezID;
		break;

	  case fk_Type::GREGORY:
		ID = (argShadowSwitch) ? shadowGregID : drawGregID;
		break;

	  default:
		break;
	}

	glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &ID);
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
