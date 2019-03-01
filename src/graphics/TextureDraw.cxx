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
	: shader(nullptr), modulateID(0), replaceID(0), decalID(0)
{
	return;
}
		
fk_TextureDraw::~fk_TextureDraw()
{
	delete shader;
	return;
}

void fk_TextureDraw::DrawShapeTexture(fk_Model *argModel)
{
	fk_DrawMode				drawMode = argModel->getDrawMode();

	if(shader == nullptr) ShaderSetup();
	PolygonModeSet();

	auto parameter = shader->getParameter();
	SetParameter(parameter);

	if((drawMode & FK_SHADERMODE) == FK_NONEMODE) shader->ProcPreShader();
	Draw_Texture(argModel, parameter);
	if((drawMode & FK_SHADERMODE) == FK_NONEMODE) shader->ProcPostShader();
	return;
}

void fk_TextureDraw::PolygonModeSet(void)
{
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
}

void fk_TextureDraw::ShaderSetup(void)
{
	shader = new fk_ShaderBinder();
	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Texture_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Texture_FS.out"
		;
	
	if(prog->validate() == false) {
		fk_Window::printf("Shader Error");
		fk_Window::putString(prog->getLastError());
	}

	param->reserveAttribute(fk_Shape::vertexName);
	param->reserveAttribute(fk_Shape::normalName);
	param->reserveAttribute(fk_Shape::texCoordName);
	
	glBindFragDataLocation(prog->getProgramID(), 0, fragmentName.c_str());

	prog->link();

	modulateID = glGetSubroutineIndex(prog->getProgramID(), GL_FRAGMENT_SHADER, "Modulate");
	replaceID = glGetSubroutineIndex(prog->getProgramID(), GL_FRAGMENT_SHADER, "Replace");
	decalID = glGetSubroutineIndex(prog->getProgramID(), GL_FRAGMENT_SHADER, "Decal");

	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &modulateID);

	return;
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

	argParam->attachTexture(1, texture);
	for(int i = 0; i < 8; ++i) {
		argParam->setRegister(fk_Texture::texIDName + "[" + to_string(i) + "]", i+1);
	}

	texture->Replace();
	
	glBindVertexArray(vao);
	texture->BindShaderBuffer(argParam->getAttrTable());
	texture->FaceIBOSetup();

	switch(texture->getTextureMode()) {
	  case FK_TEX_MODULATE:
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &modulateID);
		break;

	  case FK_TEX_REPLACE:
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &replaceID);
		break;

	  case FK_TEX_DECAL:
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &decalID);
		break;

	  default:
		break;
	}
	
	glDrawElements(GL_TRIANGLES, GLint(texture->GetFaceSize()*3), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return;
}
