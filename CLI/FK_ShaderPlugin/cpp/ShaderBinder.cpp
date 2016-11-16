#include "ShaderBinder.h"
#include "GL/glew.h"
#include <string>
#include <vcclr.h>

// レンダーターゲットのリスト
static const GLenum bufs[] = {
	GL_COLOR_ATTACHMENT0,	// カラーバッファ
	GL_DEPTH_ATTACHMENT,	// デプステクスチャ
};

namespace FK_ShaderPlugin
{
	bool fk_ShaderBinder::Initialize()
	{
		if (!isExtensionInitialized)
		{
			isExtensionInitialized = glewInit() == GLEW_OK;
		}

		return isExtensionInitialized;
	}

	fk_ShaderBinder::fk_ShaderBinder()
	{
		Initialize();

		Program = innerProgram = gcnew fk_ShaderProgram();
		Parameter = innerParameter = gcnew fk_ShaderParameter();
	}

	fk_ShaderBinder::fk_ShaderBinder(fk_ShaderProgram^ prog, fk_ShaderParameter^ param)
	{
		Initialize();

		if (prog != nullptr) Program = prog;
		else Program = innerProgram = gcnew fk_ShaderProgram();

		if (param != nullptr) Parameter = param;
		else Parameter = innerParameter = gcnew fk_ShaderParameter();
	}

	fk_ShaderBinder::~fk_ShaderBinder()
	{
		if (innerProgram != nullptr) delete innerProgram;
		if (innerParameter != nullptr) delete innerParameter;
		Program = innerProgram = nullptr;
		Parameter = innerParameter = nullptr;
	}

	void fk_ShaderBinder::BindModel(fk_Model ^ model)
	{
		model->PreShader +=
			gcnew fk_DrawCallback(this, &fk_ShaderBinder::ProcPreShader);
		model->PostShader +=
			gcnew fk_DrawCallback(this, &fk_ShaderBinder::ProcPostShader);
	}

	void fk_ShaderBinder::UnbindModel(fk_Model ^ model)
	{
		model->PreShader -=
			gcnew fk_DrawCallback(this, &fk_ShaderBinder::ProcPreShader);
		model->PostShader -=
			gcnew fk_DrawCallback(this, &fk_ShaderBinder::ProcPostShader);
	}

	void fk_ShaderBinder::InitializeFrameBufferObject(int width, int height)
	{
		bufW = width;
		bufH = height;

		// カラーバッファ用のテクスチャを用意する
		GLuint tmpID;
		glGenTextures(1, &tmpID);
		texID = tmpID;
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufW, bufH, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		// デプステクスチャ用のテクスチャを用意する
		glGenTextures(1, &tmpID);
		depthTexID = tmpID;
		glBindTexture(GL_TEXTURE_2D, depthTexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, bufW, bufH, 0,
			GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		// フレームバッファオブジェクトを作成する
		glGenFramebuffers(1, &tmpID);
		fboID = tmpID;
		glBindFramebuffer(GL_FRAMEBUFFER, fboID);

		// フレームバッファオブジェクトにカラーバッファとしてテクスチャを結合する
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D, texID, 0);
		// フレームバッファオブジェクトにデプステクスチャを結合する
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D, depthTexID, 0);

		// フレームバッファオブジェクトの結合を解除する
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void fk_ShaderBinder::InitializeFrameBufferObject(fk_Dimension^ argDim)
	{
		InitializeFrameBufferObject(argDim->w, argDim->h);
	}

	void fk_ShaderBinder::FinalizeFrameBufferObject()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GLuint tmpID;
		tmpID = fboID;
		glDeleteFramebuffers(1, &tmpID);
		tmpID = texID;
		glDeleteTextures(1, &tmpID);
		tmpID = depthTexID;
		glDeleteTextures(1, &tmpID);
	}

	void fk_ShaderBinder::BindWindow(fk_IBindableDrawer^ window)
	{
		window->PreDraw +=
			gcnew fk_DrawCallback(this, &fk_ShaderBinder::ProcPreDraw);
		window->PostDraw +=
			gcnew fk_DrawCallback(this, &fk_ShaderBinder::ProcPostDraw);
	}

	void fk_ShaderBinder::UnbindWindow(fk_IBindableDrawer^ window)
	{
		window->PreDraw -=
			gcnew fk_DrawCallback(this, &fk_ShaderBinder::ProcPreDraw);
		window->PostDraw -=
			gcnew fk_DrawCallback(this, &fk_ShaderBinder::ProcPostDraw);
	}

	void fk_ShaderBinder::ProcPreShader(void)
	{
		UInt32 id = Program->ProgramId;
		if (id != 0)
		{
			glUseProgram(id);
			Parameter->Apply(id);
			usingProgram = true;
		}
	}

	void fk_ShaderBinder::ProcPostShader(void)
	{
		if (usingProgram)
		{
			glUseProgram(0);
			usingProgram = false;
		}
	}

	void fk_ShaderBinder::ProcPreDraw(void)
	{
		// フレームバッファオブジェクトを結合する
		glBindFramebuffer(GL_FRAMEBUFFER, fboID);
		// レンダーターゲットを指定する
		glDrawBuffers(sizeof bufs / sizeof bufs[0], bufs);
		// これでFKでの描画内容はFBOにスイッチする
	}

	void fk_ShaderBinder::ProcPostDraw(void)
	{
		// レンダーターゲットを元に戻す
		glDrawBuffer(GL_BACK);
		// フレームバッファオブジェクトを結合を解除する
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// 透視変換行列を単位行列にする
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		// モデルビュー変換行列を単位行列にする
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// テクスチャマッピングを有効にする
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthTexID);

		ProcPreShader();

		// 正方形を描く
		glColor3d(1.0, 1.0, 1.0);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2d(0.0, 0.0);
		glVertex2d(-1.0, -1.0);
		glTexCoord2d(1.0, 0.0);
		glVertex2d(1.0, -1.0);
		glTexCoord2d(1.0, 1.0);
		glVertex2d(1.0, 1.0);
		glTexCoord2d(0.0, 1.0);
		glVertex2d(-1.0, 1.0);
		glEnd();

		ProcPostShader();

		// テクスチャマッピングを無効にする
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glFlush();
	}
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
