#define FK_DEF_SIZETYPE
#include <FK/SurfaceDraw.H>
#include <FK/FaceDraw.H>
#include <FK/OpenGL.H>
#include <FK/Model.h>
#include <FK/BezSurface.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_SurfaceDraw::fk_SurfaceDraw(fk_SurfaceDrawMode argMode) :
	surfShader(_st(fk_SurfaceDrawMode::NUM) * S_DRAW_NUM * FOG_NUM * SHADOW_NUM, nullptr),
	surfShadowShader(SHADOW_NUM, nullptr), mode(argMode)
{
	return;
}

fk_SurfaceDraw::~fk_SurfaceDraw()
{
	for (auto s : surfShader) delete s;
	for (auto s : surfShadowShader) delete s;
	return;
}

fk_ShaderBinder *fk_SurfaceDraw::GetDrawShader(
	fk_SurfaceDrawMode argMode,
	fk_SurfaceDrawType argType,
	fk_FogMode argFog,
	fk_ShadowMode argShadow)
{
	_st index =
		_st(argMode) * S_DRAW_NUM * FOG_NUM * SHADOW_NUM +
		_st(argType) * FOG_NUM * SHADOW_NUM +
		_st(argFog) * SHADOW_NUM + _st(argShadow);
	return surfShader[index];
}

fk_ShaderBinder * fk_SurfaceDraw::MakeDrawShader(
	fk_SurfaceDrawMode argMode,
	fk_SurfaceDrawType argType,
	fk_FogMode argFog,
	fk_ShadowMode argShadow)
{
	_st index =
		_st(argMode) * S_DRAW_NUM * FOG_NUM * SHADOW_NUM +
		_st(argType) * FOG_NUM * SHADOW_NUM +
		_st(argFog) * SHADOW_NUM + _st(argShadow);

	delete surfShader[index];
	surfShader[index] = new fk_ShaderBinder();
	return surfShader[index];
}

fk_ShaderBinder *fk_SurfaceDraw::GetShadowShader(fk_SurfaceDrawType argType)
{
	return surfShadowShader[_st(argType)];
}

fk_ShaderBinder *fk_SurfaceDraw::MakeShadowShader(fk_SurfaceDrawType argType)
{
	delete surfShadowShader[_st(argType)];
	surfShadowShader[_st(argType)] = new fk_ShaderBinder();
	return surfShadowShader[_st(argType)];
}

bool fk_SurfaceDraw::AllTest(void)
{
	bool retFlg = true;

	for(int i = 0; i < S_DRAW_NUM; ++i) {
		for(int j = 0; j < FOG_NUM; ++j) {
			for(int k = 0; k < SHADOW_NUM; ++k) {
				if(FaceShaderInit(fk_SurfaceDrawType(i),
								  fk_FogMode(j),
								  fk_ShadowMode(k)) == false) {
					retFlg = false;
				}
			}
			if(LineShaderInit(fk_SurfaceDrawType(i), fk_FogMode(j)) == false) retFlg = false;
			if(PointShaderInit(fk_SurfaceDrawType(i), fk_FogMode(j)) == false) retFlg = false;
		}
		if(ShadowInit(fk_SurfaceDrawType(i)) == false) retFlg = false;
	}
	return retFlg;
}

void fk_SurfaceDraw::DrawShapeSurface(fk_Model *argModel, fk_ShadowMode argShadowMode,
									  bool argShadowSwitch, fk_FogMode argFogMode)
{
	auto col = &(argModel->getCurveColor()->col);
	auto modelShader = argModel->getShader();
	int degree = 3;
	int div = 0;

	if(modelShader != nullptr) {
		drawShader = modelShader;
		defaultShaderFlag = false;
		if(drawShader->IsSetup() == false) {
			ParamInit(drawShader->getProgram(), drawShader->getParameter());
			drawShader->SetupDone(true);
		}
	} else {
		DefaultShaderSetup(argModel, argFogMode, argShadowMode);
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

	if(argModel->getShape()->getObjectType() == fk_Type::BEZSURFACE) {
		fk_BezSurface *bezSurf = dynamic_cast<fk_BezSurface *>(argModel->getShape());
		degree = bezSurf->getDegree();
		div = bezSurf->getDiv();
	} else {
		// Gregory Surface
		degree = 3;
		div = dynamic_cast<fk_Surface *>(argModel->getShape())->getDiv();
	}

	SetParameter(parameter);
	parameter->setRegister(fk_Shape::curveModelColorName, col, fk_Shape::curveModelColorName);
	parameter->setRegister(fk_Shape::degreeName, degree, fk_Shape::degreeName);
	parameter->setRegister(fk_Shape::geomDivName, div, fk_Shape::geomDivName);

	Draw_Surface(argModel, argShadowSwitch);
	return;
}

fk_SurfaceDrawType fk_SurfaceDraw::GetSurfType(fk_Model *argModel)
{
	if(argModel->getShape()->getObjectType() == fk_Type::BEZSURFACE) {
		return fk_SurfaceDrawType::BEZIER;
	}
	return fk_SurfaceDrawType::GREGORY;
}	

void fk_SurfaceDraw::DefaultShaderSetup(fk_Model *argModel,
										fk_FogMode argFogMode,
										fk_ShadowMode argShadowMode)
{
	fk_SurfaceDrawType type = GetSurfType(argModel);
	fk_ShadowMode shadowMode = (argModel->getShadowDraw()) ? argShadowMode : fk_ShadowMode::OFF;

	switch(mode) {
	  case fk_SurfaceDrawMode::LINE:
		  drawShader = GetDrawShader(fk_SurfaceDrawMode::LINE, type, argFogMode);
		  if (drawShader == nullptr) {
			  LineShaderInit(type, argFogMode);
			  drawShader = GetDrawShader(fk_SurfaceDrawMode::LINE, type, argFogMode);
		  }
		  break;

	  case fk_SurfaceDrawMode::POINT:
		  drawShader = GetDrawShader(fk_SurfaceDrawMode::POINT, type, argFogMode);
		  if (drawShader == nullptr) {
			  PointShaderInit(type, argFogMode);
			  drawShader = GetDrawShader(fk_SurfaceDrawMode::POINT, type, argFogMode);
		  }
		  break;

	  case fk_SurfaceDrawMode::FACE:
		  drawShader = GetDrawShader(fk_SurfaceDrawMode::FACE, type, argFogMode, shadowMode);
		  if (drawShader == nullptr) {
			  FaceShaderInit(type, argFogMode, shadowMode);
			  drawShader = GetDrawShader(fk_SurfaceDrawMode::FACE, type, argFogMode, shadowMode);
		  }
		  break;

	  default:
		  break;
	}
	defaultShaderFlag = true;
}

bool fk_SurfaceDraw::LineShaderInit(fk_SurfaceDrawType argType, fk_FogMode argFogMode)
{
	fk_ShaderBinder *shader = MakeDrawShader(
		fk_SurfaceDrawMode::LINE, argType, argFogMode);

	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Surface/VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Surface/FS_Line.out"
		;

	FragmentFogInit(prog, argFogMode);

	prog->tessEvalShaderSource =
		#include "GLSL/Surface/TE_Line.out"
		;

	TessEvalAdd(prog, argType);

	prog->geometryShaderSource =
		#include "GLSL/Surface/GS_Line.out"
		;

	if(prog->validate() == false) {
		Error::Put("fk_SurfaceDraw", "LineShaderInit", 1, "Shader Compile Error");
		string outStr = "Mode Code (";
		outStr += to_string(int(argType)) + ", ";
		outStr += to_string(int(argFogMode)) + ")";
		Error::Put(outStr);
		Error::Put(prog->getLastError());
		return false;
	}

	ParamInit(prog, param);
	shader->SetupDone(true);
	return true;
}

bool fk_SurfaceDraw::PointShaderInit(fk_SurfaceDrawType argType, fk_FogMode argFogMode)
{
	fk_ShaderBinder *shader = MakeDrawShader(
		fk_SurfaceDrawMode::POINT, argType, argFogMode);

	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Surface/VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Surface/FS_Line.out"
		;

	FragmentFogInit(prog, argFogMode);

	prog->tessEvalShaderSource =
		#include "GLSL/Surface/TE_Point.out"
		;

	TessEvalAdd(prog, argType);

	if(prog->validate() == false) {
		Error::Put("fk_SurfaceDraw", "PointShaderInit", 1, "Shader Compile Error");
		string outStr = "Mode Code (";
		outStr += to_string(int(argType)) + ", ";
		outStr += to_string(int(argFogMode)) + ")";
		Error::Put(outStr);
		Error::Put(prog->getLastError());
		return false;
	}

	ParamInit(prog, param);
	shader->SetupDone(true);
	return true;
}

bool fk_SurfaceDraw::FaceShaderInit(fk_SurfaceDrawType argType,
									fk_FogMode argFogMode,
									fk_ShadowMode argShadowMode)
{
	fk_ShaderBinder *shader = MakeDrawShader(
		fk_SurfaceDrawMode::FACE, argType, argFogMode, argShadowMode);

	aliveShader.push_back(shader);

	auto prog = shader->getProgram();
	auto param = shader->getParameter();
	
	// Vertex Shader
	prog->vertexShaderSource =
		#include "GLSL/Surface/VS.out"
		;

	// Tess Eval Shader
	prog->tessEvalShaderSource =
		#include "GLSL/Surface/TE_Face.out"
		;

	TessEvalAdd(prog, argType);

	fk_FaceDraw::FaceFragmentInit(prog, fk_ShadingMode::PHONG, argShadowMode, argFogMode);

	if(prog->validate() == false) {
		Error::Put("fk_SurfaceDraw", "FaceShaderInit", 1, "Shader Compile Error");
		string outStr = "Mode Code (";
		outStr += to_string(int(argType)) + ", ";
		outStr += to_string(int(argFogMode)) + ", ";
		outStr += to_string(int(argShadowMode)) + ")";
		Error::Put(outStr);
		Error::Put(prog->getLastError());
		return false;
	}

	ParamInit(prog, param);
	shader->SetupDone(true);
	return true;
}

void fk_SurfaceDraw::TessEvalAdd(fk_ShaderProgram *argProgram, fk_SurfaceDrawType argType)
{
	if(argType == fk_SurfaceDrawType::BEZIER) {
		argProgram->tessEvalShaderSource +=
			#include "GLSL/Surface/TE_Bez.out"
			;
	} else {
		argProgram->tessEvalShaderSource +=
			#include "GLSL/Surface/TE_Greg.out"
			;
	}
}

void fk_SurfaceDraw::ShadowSetup(fk_Model *argModel)
{
	fk_SurfaceDrawType type = GetSurfType(argModel);
	shadowShader = GetShadowShader(type);
	if (shadowShader == nullptr) {
		ShadowInit(type);
		shadowShader = GetShadowShader(type);
	}
}

bool fk_SurfaceDraw::ShadowInit(fk_SurfaceDrawType argType)
{
	fk_ShaderBinder *shader = MakeShadowShader(argType);

	auto prog = shader->getProgram();
	auto param = shader->getParameter();
	
	prog->vertexShaderSource =
		#include "GLSL/Surface/VS.out"
		;

	prog->tessEvalShaderSource =
		#include "GLSL/Surface/TE_Point.out"
		;

	TessEvalAdd(prog, argType);

	prog->fragmentShaderSource =
		#include "GLSL/Common/FS_Shadow.out"
		;

	if(prog->validate() == false) {
		Error::Put("fk_FaceDraw", "ShadowInit", 1, "Shader Compile Error");
		Error::Put(prog->getLastError());
		return false;
	}

	ParamInit(prog, param);
	shader->SetupDone(true);
	return true;
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

	if(argShadowSwitch == false ||
	   (mode == fk_SurfaceDrawMode::FACE &&
		argModel->getShadowEffect() == true)) {
		glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, tessOut);
		glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, tessIn);
		glPatchParameteri(GL_PATCH_VERTICES, surf->getCtrlSize());
		glDrawArrays(GL_PATCHES, 0, surf->getCtrlSize());
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader->ProcPostShader();
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
