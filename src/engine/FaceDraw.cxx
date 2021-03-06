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

fk_FaceDraw::Member::Member(void) :	faceShader(SHADING_NUM * SHADOW_NUM * FOG_NUM)
{
	return;
}

fk_FaceDraw::fk_FaceDraw(void) : _m(make_unique<Member>())
{
	return;
}

fk_FaceDraw::~fk_FaceDraw()
{
	return;
}

bool fk_FaceDraw::AllTest(void)
{
	bool retFlg = true;
	for(int i = 0; i < SHADING_NUM; ++i) {
		for(int j = 0; j < SHADOW_NUM; ++j) {
			for(int k = 0; k < FOG_NUM; ++k) {
				if(ShaderInit(fk_ShadingMode(i), fk_ShadowMode(j), fk_FogMode(k)) == false) {
					retFlg = false;
				}
			}
		}
	}
	return retFlg;
}
	
fk_ShaderBinder *fk_FaceDraw::GetShader(
	fk_ShadingMode argShadingMode,
	fk_ShadowMode argShadowMode,
	fk_FogMode argFogMode)
{
	_st index = _st(argShadingMode) * SHADOW_NUM * FOG_NUM +
		_st(argShadowMode) * FOG_NUM + _st(argFogMode);

	return _m->faceShader[index].get();
}

fk_ShaderBinder * fk_FaceDraw::MakeShader(
	fk_ShadingMode argShadingMode,
	fk_ShadowMode argShadowMode,
	fk_FogMode argFogMode)
{
	_st index = _st(argShadingMode) * SHADOW_NUM * FOG_NUM +
		_st(argShadowMode) * FOG_NUM + _st(argFogMode);

	_m->faceShader[index] = make_unique<fk_ShaderBinder>();
	return _m->faceShader[index].get();
}

void fk_FaceDraw::DrawShapeFace(fk_Model *argModel, fk_ShadowMode argShadowMode,
								bool argShadowSwitch, fk_FogMode argFogMode)
{
	auto shapeType = argModel->getShape()->getRealShapeType();
	auto drawMode = argModel->getDrawMode();
	auto modelShader = argModel->getShader();

	if(modelShader != nullptr) {
		drawShader = modelShader;
		defaultShaderFlag = false;
		if(drawShader->IsSetup() == false) {
			ParamInit(drawShader->getProgram(), drawShader->getParameter());
			drawShader->SetupDone(true);
		}
	} else {
		DefaultShaderSetup(argModel, argShadowMode, argFogMode);
	}

	fk_ShaderParameter *parameter;
	if(argShadowSwitch == true && defaultShaderFlag == true) {
		ShadowSetup();
		parameter = shadowShader->getParameter();
	} else {
		parameter = drawShader->getParameter();
	}

	SetParameter(parameter);
	PolygonModeSet(drawMode);

	if(shapeType == fk_RealShapeType::IFS) Draw_IFS(argModel, parameter, argShadowSwitch);

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

void fk_FaceDraw::ShadowSetup(void)
{
	if(_m->faceShadowShader == nullptr) ShadowInit();
	shadowShader = _m->faceShadowShader.get();
}

void fk_FaceDraw::ShadowInit(void)
{
	_m->faceShadowShader = make_unique<fk_ShaderBinder>();
	auto shader = _m->faceShadowShader.get();
	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Common/VS_Shadow.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Common/FS_Shadow.out"
		;

	if(prog->validate() == false) {
		Error::Put("fk_FaceDraw", "ShadowInit", 1, "Shader Compile Error");
		Error::Put(prog->getLastError());
	}

	ParamInit(prog, param);
	shader->SetupDone(true);

	return;
}

void fk_FaceDraw::DefaultShaderSetup(fk_Model *argModel,
									 fk_ShadowMode argShadowMode,
									 fk_FogMode argFogMode)
{
	fk_ShadingMode shadingMode = argModel->getShadingMode();
	fk_ShadowMode shadowMode = (argModel->getShadowDraw()) ? argShadowMode : fk_ShadowMode::OFF;

	drawShader = GetShader(shadingMode, shadowMode, argFogMode);
	if(drawShader == nullptr) {
		ShaderInit(shadingMode, shadowMode, argFogMode);
		drawShader = GetShader(shadingMode, shadowMode, argFogMode);
	}
	defaultShaderFlag = true;
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

void fk_FaceDraw::Draw_IFS(fk_Model *argModel, fk_ShaderParameter *argParam, bool argShadowSwitch)
{
	fk_IndexFaceSet *ifs = dynamic_cast<fk_IndexFaceSet *>(argModel->getShape());
	GLuint vao = ifs->GetFaceVAO();
	fk_ShaderBinder *shader = (argShadowSwitch) ? shadowShader : drawShader;

	if(vao == 0) {
		vao = VAOSetup(ifs);
	}
	
	glBindVertexArray(vao);
	ifs->FaceIBOSetup();
	ifs->BindShaderBuffer(argParam->getAttrTable());
	shader->ProcPreShader();
	if(argShadowSwitch == false || argModel->getShadowEffect() == true) {
		glDrawElements(GL_TRIANGLES, GLint(ifs->getFaceSize()*3), GL_UNSIGNED_INT, 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	shader->ProcPostShader();

	return;
}

bool fk_FaceDraw::ShaderInit(fk_ShadingMode argShadingMode,
							 fk_ShadowMode argShadowMode,
							 fk_FogMode argFogMode)
{
	fk_ShaderBinder *shader = MakeShader(argShadingMode, argShadowMode, argFogMode);
	aliveShader.push_back(shader);

	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	// Vertex Shader
	FaceVertexInit(prog, argShadingMode, argShadowMode);
		
	// Fragment Shader
	FaceFragmentInit(prog, argShadingMode, argShadowMode, argFogMode);

	if(prog->validate() == false) {
		Error::Put("fk_FaceDraw", "ShaderInit", 1, "Shader Compile Error");
		string outStr = "Mode Code (";
		outStr += to_string(int(argShadingMode)) + ", ";
		outStr += to_string(int(argShadowMode)) + ", ";
		outStr += to_string(int(argFogMode)) + ")";
		Error::Put(outStr);
		Error::Put(prog->getLastError());
		return false;
	}

	ParamInit(prog, param);
	shader->SetupDone(true);
	return true;
}

void fk_FaceDraw::FaceVertexInit(fk_ShaderProgram *argProg,
								   fk_ShadingMode argShadingMode,
								   fk_ShadowMode argShadowMode)
{
	switch(argShadingMode) {
	  case fk_ShadingMode::PHONG:
		argProg->vertexShaderSource =
			#include "GLSL/Face/VS_Phong.out"
			;
		break;

	  case fk_ShadingMode::GOURAUD:
		argProg->vertexShaderSource =
			#include "GLSL/Face/VS_Gouraud_Common.out"
			;

		switch(argShadowMode) {
		  case fk_ShadowMode::HARD:
			argProg->vertexShaderSource +=
				#include "GLSL/Face/VS_Gouraud_Hard.out"
				;
			break;

		  case fk_ShadowMode::SOFT_FAST:
			argProg->vertexShaderSource +=
				#include "GLSL/Face/VS_Gouraud_SoftFast.out"
				;
			break;

		  case fk_ShadowMode::SOFT_NICE:
			argProg->vertexShaderSource +=
				#include "GLSL/Face/VS_Gouraud_SoftNice.out"
				;
			break;

		  case fk_ShadowMode::OFF:
			argProg->vertexShaderSource +=
				#include "GLSL/Face/VS_Gouraud_Off.out"
				;
			break;

		  default:
			break;
		}
		break;

	  default:
		break;
	}
}
void fk_FaceDraw::FaceFragmentInit(fk_ShaderProgram *argProg,
								   fk_ShadingMode argShadingMode,
								   fk_ShadowMode argShadowMode,
								   fk_FogMode argFogMode)
{
	// Fragment Shader
	switch(argShadingMode) {
	  case fk_ShadingMode::PHONG:
		argProg->fragmentShaderSource =
			#include "GLSL/Face/FS_Phong_Common.out"
			;

		switch(argShadowMode) {
		  case fk_ShadowMode::HARD:
			argProg->fragmentShaderSource +=
				#include "GLSL/Face/FS_Phong_Hard.out"
				;
			break;

		  case fk_ShadowMode::SOFT_FAST:
			argProg->fragmentShaderSource +=
				#include "GLSL/Face/FS_Phong_SoftFast.out"
				;
			break;

		  case fk_ShadowMode::SOFT_NICE:
			argProg->fragmentShaderSource +=
				#include "GLSL/Face/FS_Phong_SoftNice.out"
				;
			break;

		  case fk_ShadowMode::OFF:
			argProg->fragmentShaderSource +=
				#include "GLSL/Face/FS_Phong_Off.out"
				;
			break;

		  default:
			break;
		}
		break;
		
	  case fk_ShadingMode::GOURAUD:
		argProg->fragmentShaderSource =
			#include "GLSL/Face/FS_Gouraud.out"
			;
		break;

	  default:
		argProg->fragmentShaderSource =
			#include "GLSL/Common/FS_Discard.out"
			;
		break;
	}

	FragmentFogInit(argProg, argFogMode);

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
