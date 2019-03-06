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
#define GLEW_STATIC
#include <FK/ShaderBinder.h>

using namespace std;
using namespace FK;

bool fk_ShaderBinder::isExtensionInitialized = false;

bool fk_ShaderBinder::Initialize()
{
#ifdef WIN32
	if (!isExtensionInitialized) {
		isExtensionInitialized = (glewInit() == GLEW_OK);
	}
#else
	isExtensionInitialized = true;
#endif

	return isExtensionInitialized;
}

fk_ShaderBinder::fk_ShaderBinder()
	: program(&innerProgram), parameter(&innerParameter),  usingProgram(false),
	  bufW(0), bufH(0), rectVAO(0), fboHandle(0), colorBuf(0)
{
	isExtensionInitialized = false;
	Initialize();
	program->SetParameter(parameter);
}

fk_ShaderBinder::fk_ShaderBinder(fk_ShaderProgram *argProg, fk_ShaderParameter *argParam)
	: usingProgram(false),
	  bufW(0), bufH(0), rectVAO(0), fboHandle(0), colorBuf(0)
{
	isExtensionInitialized = false;
	Initialize();

	setProgram(argProg);
	setParameter(argParam);
}

fk_ShaderBinder::~fk_ShaderBinder()
{
}

void fk_ShaderBinder::setProgram(fk_ShaderProgram *argProg)
{
	program = (argProg != nullptr) ? argProg : &innerProgram;
	return;
}

fk_ShaderProgram * fk_ShaderBinder::getProgram(void)
{
	return program;
}

void fk_ShaderBinder::setParameter(fk_ShaderParameter *argParam)
{
	parameter = (argParam != nullptr) ? argParam : &innerParameter;
	if(program != nullptr) program->SetParameter(parameter);
	return;
}

fk_ShaderParameter * fk_ShaderBinder::getParameter(void)
{
	return parameter;
}

void fk_ShaderBinder::bindModel(fk_Model *argModel)
{
	argModel->preShader = [&](){ ProcPreShader(); };
	argModel->postShader = [&](){ ProcPostShader(); };
}

void fk_ShaderBinder::unbindModel(fk_Model *argModel)
{
	argModel->preShader = [](){};
	argModel->postShader = [](){};
}

void fk_ShaderBinder::initializeFrameBufferObject(int width, int height)
{
	bufW = width;
	bufH = height;

    static GLfloat verts[] = {
        -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f
    };
    static GLfloat tc[] = {
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

	SetupFBO();

	GLuint handle[2];
	glGenBuffers(2, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), tc, GL_STATIC_DRAW);

	glGenVertexArrays(1, &rectVAO);
	glBindVertexArray(rectVAO);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	auto prog = getProgram();
	auto id = prog->getProgramID();

	glBindFragDataLocation(id, 0, "fragment");

	prog->link();

	auto texLocation = glGetUniformLocation(id, "fk_ColorBuf");
	if(texLocation >= 0) glUniform1i(texLocation, 0);
}

void fk_ShaderBinder::SetupFBO(void)
{
	glGenFramebuffers(1, &fboHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

	glGenTextures(1, &colorBuf);
	glBindTexture(GL_TEXTURE_2D, colorBuf);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufW, bufH, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuf, 0);

	GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, drawBuffers);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void fk_ShaderBinder::initializeFrameBufferObject(fk_Dimension argDim)
{
	initializeFrameBufferObject(argDim.w, argDim.h);
}

void fk_ShaderBinder::finalizeFrameBufferObject(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fboHandle);
	glDeleteTextures(1, &colorBuf);
}

void fk_ShaderBinder::bindWindow(fk_Window *argWin)
{
	if(argWin == nullptr) return;

	GLuint		id = program->getProgramID();

	fk_funcSet	preD = fk_funcSet(id, [&](){ ProcPreDraw(); });
	fk_funcSet	postD = fk_funcSet(id, [&](){ ProcPostDraw(); });
	argWin->preDrawList.push_back(preD);
	argWin->postDrawList.push_back(postD);
}

void fk_ShaderBinder::bindWindow(fk_AppWindow *argWin)
{
	if(argWin == nullptr) return;
	bindWindow(argWin->drawWin);
}

void fk_ShaderBinder::unbindWindow(fk_Window *argWin)
{
	if(argWin == nullptr) return;

	GLuint id = program->getProgramID();

	for(auto it = argWin->preDrawList.begin(); it != argWin->preDrawList.end();) {
		if(get<0>(*it) == id) it = argWin->preDrawList.erase(it);
		else ++it;
	}

	for(auto it = argWin->postDrawList.begin(); it != argWin->postDrawList.end();) {
		if(get<0>(*it) == id) it = argWin->postDrawList.erase(it);
		else ++it;
	}
}

void fk_ShaderBinder::unbindWindow(fk_AppWindow *argWin)
{
	if(argWin == nullptr) return;
	unbindWindow(argWin->drawWin);
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
	if (usingProgram) {
		glUseProgram(0);
		usingProgram = false;
	}
}

void fk_ShaderBinder::ProcPreDraw(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void fk_ShaderBinder::ProcPostDraw(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	ProcPreShader();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorBuf);
	glBindVertexArray(rectVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	ProcPostShader();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
