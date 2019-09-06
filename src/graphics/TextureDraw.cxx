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
#include <FK/TextureDraw.H>
#include <FK/IFSTexture.h>
#include <FK/Model.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_TextureDraw::fk_TextureDraw(void)
	: phongShader(nullptr), gouraudShader(nullptr),
	  modulate_p_ID(0), replace_p_ID(0), decal_p_ID(0),
	  modulate_g_ID(0), replace_g_ID(0), decal_g_ID(0)
{
	return;
}
		
fk_TextureDraw::~fk_TextureDraw()
{
	delete phongShader;
	delete gouraudShader;
	return;
}

void fk_TextureDraw::DrawShapeTexture(fk_Model *argModel)
{
	auto modelShader = argModel->getShader();

	if(modelShader != nullptr) {
		shader = modelShader;
		if(shader->IsSetup() == false) {
			ParamInit(shader->getProgram(), shader->getParameter());
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
	}
	
	PolygonModeSet();

	auto parameter = shader->getParameter();
	SetParameter(parameter);

	Draw_Texture(argModel, parameter);
	return;
}

void fk_TextureDraw::PolygonModeSet(void)
{
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
}

void fk_TextureDraw::PhongSetup(void)
{
	if(phongShader == nullptr) phongShader = new fk_ShaderBinder();
	shader = phongShader;
	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Texture_Phong_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Texture_Phong_FS.out"
		;
	
	if(prog->validate() == false) {
		fk_PutError("fk_TextureDraw", "PhongSetup", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();
	
	modulate_p_ID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "Modulate");
	replace_p_ID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "Replace");
	decal_p_ID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "Decal");

	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &modulate_p_ID);

	return;
}

void fk_TextureDraw::GouraudSetup(void)
{
	if(gouraudShader == nullptr) gouraudShader = new fk_ShaderBinder();
	shader = gouraudShader;
	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Texture_Gouraud_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Texture_Gouraud_FS.out"
		;
	
	if(prog->validate() == false) {
		fk_PutError("fk_TextureDraw", "GouraudSetup", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();
	
	modulate_g_ID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "Modulate");
	replace_g_ID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "Replace");
	decal_g_ID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "Decal");

	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &modulate_g_ID);

	return;
}

void fk_TextureDraw::ShaderSetup(void)
{
	PhongSetup();
	GouraudSetup();
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

void fk_TextureDraw::Draw_Texture(fk_Model *argModel, fk_ShaderParameter *argParam)
{
	fk_Texture		*texture = dynamic_cast<fk_Texture *>(argModel->getShape());
	GLuint			vao = texture->GetFaceVAO();

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

	if(shader == phongShader || shader == gouraudShader) {
		GLuint id = 0;

		switch(argModel->getShadingMode()) {
		  case fk_ShadingMode::PHONG:
			switch(texMode) {
			  case fk_TexMode::MODULATE:
				id = modulate_p_ID;
				break;

			  case fk_TexMode::REPLACE:
				id = replace_p_ID;
				break;

			  case fk_TexMode::DECAL:
				id = decal_p_ID;
				break;

			  default:
				break;
			}
			break;

		  case fk_ShadingMode::GOURAUD:
			switch(texMode) {
			  case fk_TexMode::MODULATE:
				id = modulate_g_ID;
				break;

			  case fk_TexMode::REPLACE:
				id = replace_g_ID;
				break;

			  case fk_TexMode::DECAL:
				id = decal_g_ID;
				break;

			  default:
				break;
			}
			break;

		  default:
			break;
		}

		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &id);
	}

	glDrawElements(GL_TRIANGLES, GLint(texture->GetFaceSize()*3), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	shader->ProcPostShader();
	return;
}
