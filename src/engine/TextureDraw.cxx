﻿#define FK_DEF_SIZETYPE
#include <FK/TextureDraw.H>
#include <FK/IFSTexture.h>
#include <FK/Model.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_TextureDraw::fk_TextureDraw(void)
{
	for(int i = 0; i < int(fk_ShadingMode::NUM); ++i) {
		for(int j = 0; j < int(fk_ShadowMode::NUM); ++j) {
			for(int k = 0; k < 2; ++k) {
				textureShader[i][j][k] = nullptr;
			}
		}
	}

	replaceShader = nullptr;
	texShadowShader[0] = nullptr;
	texShadowShader[1] = nullptr;
	return;
}
		
fk_TextureDraw::~fk_TextureDraw()
{
	delete replaceShader;
	delete texShadowShader[0];
	delete texShadowShader[1];

	for(int i = 0; i < int(fk_ShadingMode::NUM); ++i) {
		for(int j = 0; j < int(fk_ShadowMode::NUM); ++j) {
			for(int k = 0; k < 2; ++k) {
				delete textureShader[i][j][k];
			}
		}
	}

	return;
}

void fk_TextureDraw::DrawShapeTexture(fk_Model *argModel,
									  fk_ShadowMode argShadowMode, bool argShadowSwitch)
{
	auto modelShader = argModel->getShader();

	if(modelShader != nullptr) {
		drawShader = modelShader;
		defaultShaderFlag = false;
		if(drawShader->IsSetup() == false) {
			ParamInit(drawShader->getProgram(), drawShader->getParameter());
			drawShader->SetupDone(true);
		}
	} else {
		DefaultShaderSetup(argModel, argShadowMode);
		defaultShaderFlag = true;
	}
	
	PolygonModeSet();

	fk_ShaderParameter *parameter;

	if(argShadowSwitch == true && defaultShaderFlag == true) {
		ShadowSetup(argModel);
		parameter = shadowShader->getParameter();
	} else {
		parameter = drawShader->getParameter();
	}

	SetParameter(parameter);
	Draw_Texture(argModel, parameter, argShadowSwitch);
	return;
}

void fk_TextureDraw::PolygonModeSet(void)
{
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
}

void fk_TextureDraw::ParamInit(fk_ShaderProgram *argProg, fk_ShaderParameter *argParam)
{
	argParam->reserveAttribute(fk_Shape::vertexName);
	argParam->reserveAttribute(fk_Shape::normalName);
	argParam->reserveAttribute(fk_Shape::texCoordName);
	
	glBindFragDataLocation(argProg->getProgramID(), 0, fragmentName.c_str());
	argProg->link();
}


GLuint fk_TextureDraw::VAOSetup(fk_Shape *argShape)
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

void fk_TextureDraw::Draw_Texture(fk_Model *argModel,
								  fk_ShaderParameter *argParam, bool argShadowSwitch)
{
	fk_Texture *texture = dynamic_cast<fk_Texture *>(argModel->getShape());
	GLuint vao = texture->GetFaceVAO();
	fk_ShaderBinder *shader = (argShadowSwitch) ? shadowShader : drawShader;

	if(vao == 0) {
		vao = VAOSetup(texture);
	}

	glBindVertexArray(vao);
	texture->FaceIBOSetup();
	texture->BindShaderBuffer(argParam->getAttrTable());

	texture->Replace();
	argParam->attachTexture(0, texture);
	for(int i = 0; i < 8; ++i) {
		argParam->setRegister(fk_Texture::texIDName + "[" + to_string(i) + "]", i+1);
	}

	shader->ProcPreShader();

	fk_TexMode texMode = argModel->getTextureMode();
	if(texMode == fk_TexMode::NONE) texMode = texture->getTextureMode();

	glDrawElements(GL_TRIANGLES, GLint(texture->GetFaceSize()*3), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	shader->ProcPostShader();
	return;
}

void fk_TextureDraw::DefaultShaderSetup(fk_Model *argModel, fk_ShadowMode argShadowMode)
{
	fk_Texture *texture = dynamic_cast<fk_Texture *>(argModel->getShape());
	fk_TexMode texMode = argModel->getTextureMode();
	if(texMode == fk_TexMode::NONE) texMode = texture->getTextureMode();
	fk_ShadingMode shadingMode = argModel->getShadingMode();
	fk_ShadowMode shadowMode = (argModel->getShadowDraw()) ? argShadowMode : fk_ShadowMode::OFF;

	switch(texMode) {
	  case fk_TexMode::NONE:
		break;
		
	  case fk_TexMode::REPLACE:
		if(replaceShader == nullptr) ReplaceShaderInit();
		drawShader = replaceShader;
		break;

	  default:
		if(textureShader[int(shadingMode)][int(shadowMode)][int(texMode)] == nullptr) {
			TextureShaderInit(shadingMode, shadowMode, texMode);
		}
		drawShader = textureShader[int(shadingMode)][int(shadowMode)][int(texMode)];
	}
	
	defaultShaderFlag = true;
}

void fk_TextureDraw::ReplaceShaderInit(void)
{
	replaceShader = new fk_ShaderBinder();

	auto prog = replaceShader->getProgram();
	auto param = replaceShader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Texture_VS_Replace.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Texture_FS_Replace.out"
		;
	
	if(prog->validate() == false) {
		fk_PutError("fk_TextureDraw", "ReplaceShaderInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);
}

void fk_TextureDraw::TextureShaderInit(fk_ShadingMode argShadingMode,
									   fk_ShadowMode argShadowMode,
									   fk_TexMode argTexMode)
{
	fk_ShaderBinder *shader = new fk_ShaderBinder();
	textureShader[int(argShadingMode)][int(argShadowMode)][int(argTexMode)] = shader;
	aliveShader.push_back(shader);

	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	// Vertex Shader
	switch(argShadingMode) {
	  case fk_ShadingMode::PHONG:
		prog->vertexShaderSource =
			#include "GLSL/Texture_VS_Phong.out"
			;
		break;
		
	  case fk_ShadingMode::GOURAUD:
		prog->vertexShaderSource =
			#include "GLSL/Texture_VS_Gouraud_Common.out"
			;
		break;

		switch(argShadowMode) {
		  case fk_ShadowMode::HARD:
			prog->vertexShaderSource +=
				#include "GLSL/Texture_VS_Gouraud_Hard.out"
				;
			break;

		  case fk_ShadowMode::SOFT_FAST:
			prog->vertexShaderSource +=
				#include "GLSL/Texture_VS_Gouraud_SoftFast.out"
				;
			break;

		  case fk_ShadowMode::SOFT_NICE:
			prog->vertexShaderSource +=
				#include "GLSL/Texture_VS_Gouraud_SoftNice.out"
				;
			break;

		  case fk_ShadowMode::OFF:
			prog->vertexShaderSource +=
				#include "GLSL/Texture_VS_Gouraud_Off.out"
				;
			break;

		  default:
			break;
		}
		break;

	  default:
		break;
	}

	// Fragment Shader
	switch(argShadingMode) {
	  case fk_ShadingMode::PHONG:
		prog->fragmentShaderSource =
			#include "GLSL/Texture_FS_Phong_Common.out"
			;

		switch(argShadowMode) {
		  case fk_ShadowMode::HARD:
			prog->fragmentShaderSource +=
				#include "GLSL/Texture_FS_Phong_Hard.out"
				;
			break;

		  case fk_ShadowMode::SOFT_FAST:
			prog->fragmentShaderSource +=
				#include "GLSL/Texture_FS_Phong_SoftFast.out"
				;
			break;

		  case fk_ShadowMode::SOFT_NICE:
			prog->fragmentShaderSource +=
				#include "GLSL/Texture_FS_Phong_SoftNice.out"
				;
			break;

		  case fk_ShadowMode::OFF:
			prog->fragmentShaderSource +=
				#include "GLSL/Texture_FS_Phong_Off.out"
				;
			break;

		  default:
			break;
		}

		switch(argTexMode) {
		  case fk_TexMode::MODULATE:
			prog->fragmentShaderSource +=
				#include "GLSL/Texture_FS_Phong_Mod.out"
				;
			break;
			
		  case fk_TexMode::DECAL:
			prog->fragmentShaderSource +=
				#include "GLSL/Texture_FS_Phong_Dec.out"
				;
			break;

		  default:
			break;
		}
		break;

	  case fk_ShadingMode::GOURAUD:
		switch(argTexMode) {
		  case fk_TexMode::MODULATE:
			prog->fragmentShaderSource =
				#include "GLSL/Texture_FS_Gouraud_Mod.out"
				;
			break;
			
		  case fk_TexMode::DECAL:
			prog->fragmentShaderSource +=
				#include "GLSL/Texture_FS_Gouraud_Dec.out"
				;
			break;

		  default:
			break;
		}
		break;

	  default:
		break;
	}

	if(prog->validate() == false) {
		fk_PutError("fk_FaceDraw", "TextureShaderInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
		//fk_PutError(prog->vertexShaderSource);
		//fk_PutError(prog->fragmentShaderSource);
	}

	ParamInit(prog, param);
	return;
}

void fk_TextureDraw::ShadowSetup(fk_Model *argModel)
{
	int ID = (argModel->getShadowEffect()) ? 0 : 1;
	if(texShadowShader[ID] == nullptr) ShadowInit(ID);
	shadowShader = texShadowShader[ID];
}

void fk_TextureDraw::ShadowInit(int argID)
{
	fk_ShaderBinder *shader = new fk_ShaderBinder();
	texShadowShader[argID] = shader;
	
	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Face_VS_Shadow.out"
		;

	if(argID == 0) {
		prog->fragmentShaderSource =
			#include "GLSL/Face_FS_Shadow.out"
			;
	} else {
		prog->fragmentShaderSource =
			#include "GLSL/FS_Discard.out"
			;
	}

	if(prog->validate() == false) {
		fk_PutError("fk_TextureDraw", "ShadowInit", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

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
