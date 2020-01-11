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
#define FK_DEF_SIZETYPE
#include <FK/LineDraw.H>
#include <FK/OpenGL.H>
#include <FK/Model.h>
#include <FK/Curve.h>
#include <FK/Surface.h>
#include <FK/Solid.h>
#include <FK/IndexFace.h>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_LineDraw::fk_LineDraw(void)
	: lineShader(nullptr), vsModelID(0), vsElemID(0), vsIFSID(0), fsLineID(0), fsIFSID(0)
{
	return;
}

fk_LineDraw::~fk_LineDraw()
{
	delete lineShader;
	return;
}


void fk_LineDraw::DrawShapeLine(fk_Model *argModel, fk_Shape *argShape)
{
	fk_Shape * shape = (argShape == nullptr) ? argModel->getShape() : argShape;
	auto shapeType = shape->getRealShapeType();
	auto col = &(argModel->getLineColor()->col);
	auto modelShader = (argShape == nullptr) ? argModel->getShader() : nullptr;

	if(modelShader != nullptr) {
		shader = modelShader;
		if(shader->IsSetup() == false) {
			ParamInit(shader->getProgram(), shader->getParameter());
		}
	} else {
		if(lineShader == nullptr) ShaderSetup();
		else shader = lineShader;
	}
	
	auto parameter = shader->getParameter();

	SetParameter(parameter);
	parameter->setRegister(fk_Shape::lineModelColorName, col, fk_Shape::lineModelColorName);
	shader->ProcPreShader();

	if(shader == lineShader) SubroutineSetup(argModel);
	
	glEnable(GL_LINE_SMOOTH);

	switch(shapeType) {
	  case fk_RealShapeType::LINE:
		Draw_Line(dynamic_cast<fk_LineBase *>(shape), parameter);
		break;

	  case fk_RealShapeType::IFS:
		Draw_IFS(dynamic_cast<fk_IndexFaceSet *>(shape), parameter);
		break;

	  default:
		break;
	}

	shader->ProcPostShader();
	return;
}

void fk_LineDraw::ShaderSetup(void)
{
	lineShader = new fk_ShaderBinder();
	shader = lineShader;
	auto prog = shader->getProgram();
	auto param = shader->getParameter();

	prog->vertexShaderSource =
		#include "GLSL/Line_VS.out"
		;

	prog->fragmentShaderSource =
		#include "GLSL/Line_FS.out"
		;

	if(prog->validate() == false) {
		fk_PutError("fk_LineDraw", "ShaderSetup", 1, "Shader Compile Error");
		fk_PutError(prog->getLastError());
	}

	ParamInit(prog, param);

	auto progID = prog->getProgramID();
	
	vsModelID = glGetSubroutineIndex(progID, GL_VERTEX_SHADER, "LineModelVS");
	vsElemID = glGetSubroutineIndex(progID, GL_VERTEX_SHADER, "LineElemVS");
	vsIFSID = glGetSubroutineIndex(progID, GL_VERTEX_SHADER, "LineIFSVS");
	fsLineID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "LineLineFS");
	fsIFSID = glGetSubroutineIndex(progID, GL_FRAGMENT_SHADER, "LineIFSFS");

	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &vsModelID);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &fsLineID);

	return;
}

void fk_LineDraw::ParamInit(fk_ShaderProgram *argProg, fk_ShaderParameter *argParam)
{
	argParam->reserveAttribute(fk_Line::vertexName);
	argParam->reserveAttribute(fk_Line::lineElementColorName);
	argParam->reserveAttribute(fk_Line::lineElementAliveName);
	
	glBindFragDataLocation(argProg->getProgramID(), 0, fragmentName.c_str());
	argProg->link();
}

GLuint fk_LineDraw::VAOSetup(fk_Shape *argShape)
{
	GLuint 			vao;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	argShape->SetLineVAO(vao);
	argShape->DefineVBO();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return vao;
}

void fk_LineDraw::Draw_Line(fk_LineBase *argLine, fk_ShaderParameter *argParam)
{
	GLuint vao = argLine->GetLineVAO();

	if(vao == 0) {
		vao = VAOSetup(argLine);
	}
	glBindVertexArray(vao);
	argLine->BindShaderBuffer(argParam->getAttrTable());
	glEnable(GL_LINE_SMOOTH);
	glDrawArrays(GL_LINES, 0, argLine->Size()*2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return;
}

void fk_LineDraw::Draw_IFS(fk_IndexFaceSet *argIFS, fk_ShaderParameter *argParam)
{
	GLuint vao = argIFS->GetLineVAO();

	if(vao == 0) {
		vao = VAOSetup(argIFS);
	}
	glBindVertexArray(vao);
	argIFS->BindShaderBuffer(argParam->getAttrTable());
	argIFS->EdgeIBOSetup();
	glEnable(GL_LINE_SMOOTH);
	glDrawElements(GL_LINES, GLint(argIFS->getEdgeSize()*2), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return;
}

void fk_LineDraw::SubroutineSetup(fk_Model *argModel)
{
	auto shape = argModel->getShape();
	auto mode = argModel->getElementMode();

	switch(shape->getRealShapeType()) {
	  case fk_RealShapeType::LINE:
	  case fk_RealShapeType::CURVE:
	  case fk_RealShapeType::SURFACE:
	  case fk_RealShapeType::GRAPH:

		switch(mode) {
		  case fk_ElementMode::MODEL:
			glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &vsModelID);
			break;

		  case fk_ElementMode::ELEMENT:
			glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &vsElemID);
			break;

		  default:
			return;
		}
		
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &fsLineID);
		return;

	  case fk_RealShapeType::IFS:
		glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &vsIFSID);
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &fsIFSID);
		return;

	  default:
		break;
	}

	return;
}
