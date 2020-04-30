#include <FK/ShaderBinder.h>
#include <FK/DrawBase.H>

using namespace std;
using namespace FK;

const string fk_ShaderBinder::colorBufName = "fk_ColorBuf";
const string fk_ShaderBinder::depthBufName = "fk_DepthBuf";
const string fk_ShaderBinder::shadowBufName = "fk_ShadowBuf";
const string fk_ShaderBinder::fboTexCoordName = "fk_FBOTexCoord";
const string fk_ShaderBinder::fboSizeName = "fk_FBOSize";

bool fk_ShaderBinder::isExtensionInitialized = false;
string fk_ShaderBinder::fboVertexCode;
string fk_ShaderBinder::fboGeometryCode;

//static const GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};
//static const GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };

bool fk_ShaderBinder::Initialize()
{
#ifdef WIN32
	if (!isExtensionInitialized) {
		isExtensionInitialized = (glewInit() == GLEW_OK);
	}
#else
	isExtensionInitialized = true;
#endif

	if(fboVertexCode.empty() == true) {
		fboVertexCode +=
			#include "GLSL/FBO_Vertex.out"
			;
	}

	if(fboGeometryCode.empty() == true) {
		fboGeometryCode +=
			#include "GLSL/FBO_Geom.out"
			;
	}

	return isExtensionInitialized;
}

bool fk_ShaderBinder::IsInitialized(void)
{
    return isExtensionInitialized;
}

fk_ShaderBinder::fk_ShaderBinder()
	: program(&innerProgram), parameter(&innerParameter),
	  usingProgram(false), setupFlg(false),
	  bufW(0), bufH(0)
{
	isExtensionInitialized = false;
	Initialize();
	program->SetParameter(parameter);
	parameter->SetProgram(program);
}

fk_ShaderBinder::~fk_ShaderBinder()
{
}

fk_ShaderProgram * fk_ShaderBinder::getProgram(void)
{
	return program;
}

fk_ShaderParameter * fk_ShaderBinder::getParameter(void)
{
	return parameter;
}

void fk_ShaderBinder::bindModel(fk_Model *argModel)
{
	argModel->setShader(this);
}

void fk_ShaderBinder::unbindModel(fk_Model *argModel)
{
	argModel->setShader(nullptr);
}

void fk_ShaderBinder::LoadFBOShader(void)
{
	program->vertexShaderSource = fboVertexCode;
	program->geometryShaderSource = fboGeometryCode;
	program->SetFBOMode(true);
}

void fk_ShaderBinder::initializeFrameBufferObject(int width, int height)
{
	bufW = width;
	bufH = height;
	LoadFBOShader();
	fboSize.clear();
	fboSize.push_back(float(bufW));
	fboSize.push_back(float(bufH));
}

void fk_ShaderBinder::initializeFrameBufferObject(fk_Dimension argDim)
{
	initializeFrameBufferObject(argDim.w, argDim.h);
}

void fk_ShaderBinder::bindWindow(fk_Window *argWin)
{
	if(argWin == nullptr || bufW <= 0 || bufH <= 0) return;
	if(IsInitialized() == false) Initialize();
	
	argWin->GetEngine()->BindWindow(this);

	GLuint id = program->getProgramID();

	glBindAttribLocation(id, 0, fk_Shape::vertexName.c_str());
	glBindFragDataLocation(id, 0, fk_DrawBase::fragmentName.c_str());
	program->link();
	
	int maxUnit;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxUnit);

	parameter->setRegister(colorBufName, maxUnit-1);
	parameter->setRegister(depthBufName, maxUnit-2);
	parameter->setRegister(fboSizeName, &fboSize);
}

void fk_ShaderBinder::bindWindow(fk_AppWindow *argWin)
{
	if(argWin == nullptr) return;
	bindWindow(argWin->GetDrawWin());
}

void fk_ShaderBinder::unbindWindow(fk_Window *argWin)
{
	if(argWin == nullptr) return;
	argWin->GetEngine()->BindWindow(nullptr);
}

void fk_ShaderBinder::unbindWindow(fk_AppWindow *argWin)
{
	if(argWin == nullptr) return;
	unbindWindow(argWin->GetDrawWin());
}

void fk_ShaderBinder::ProcPreShader(void)
{
	GLuint id = program->getProgramID();
	if (id != 0) {
		glUseProgram(id);
		parameter->Apply(id);
		usingProgram = true;
	}
}

void fk_ShaderBinder::ProcPostShader(void)
{
	if (usingProgram == true) {
		glUseProgram(0);
		usingProgram = false;
	}
}

void fk_ShaderBinder::SetupDone(bool argFlg)
{
	setupFlg = argFlg;
}

bool fk_ShaderBinder::IsSetup(void)
{
	return setupFlg;
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
