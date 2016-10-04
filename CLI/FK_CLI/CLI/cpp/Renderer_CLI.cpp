#include "Renderer_CLI.h"
#include <msclr/marshal_cppstd.h>
#include <GL/gl.h>
#include <stdlib.h>

static HGLRC firstRC = nullptr;

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	fk_Renderer::fk_Renderer(void) : hWnd(nullptr), hDC(nullptr), hRC(nullptr)
	{
		pEngine = new ::fk_GraphicsEngine();
	}

	fk_Renderer::~fk_Renderer()
	{
		if (pEngine != nullptr) Shutdown();
		delete pEngine;
		pEngine = nullptr;
	}

	fk_Renderer::!fk_Renderer()
	{
		if (pEngine != nullptr) Shutdown();
		delete pEngine;
		pEngine = nullptr;
	}

	bool fk_Renderer::Initialize(System::IntPtr argPwnd, int argW, int argH)
	{
		hWnd = (HWND)argPwnd.ToPointer();

		// OpenGL の初期化
		GLuint PixelFormat;

		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;

		hDC = GetDC(hWnd);
		PixelFormat = ChoosePixelFormat(hDC, &pfd);
		if (SetPixelFormat(hDC, PixelFormat, &pfd) == FALSE)
		{
			ReleaseDC(hWnd, hDC);
			hDC = nullptr;
			return false;
		}

		hRC = wglCreateContext(hDC);
		if (hRC == nullptr)
		{
			ReleaseDC(hWnd, hDC);
			hDC = nullptr;
			return false;
		}

		if (firstRC != nullptr)
		{
			wglShareLists(firstRC, hRC);
		}
		else
		{
			firstRC = hRC;
		}

		wglMakeCurrent(hDC, hRC);
		pEngine->Init(argW, argH);
		pEngine->OpenGLInit();

		return true;
	}

	void fk_Renderer::Shutdown(void)
	{
		if (firstRC != nullptr) firstRC = nullptr;

		if (hRC != nullptr)
		{
			if (wglGetCurrentContext() == hRC) wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(hRC);
			hRC = nullptr;
		}

		if (hDC != nullptr && hWnd != nullptr)
		{
			ReleaseDC(hWnd, hDC);
			hDC = nullptr;
			hWnd = nullptr;
		}
	}

	void fk_Renderer::Resize(int argW, int argH)
	{
		pEngine->ResizeWindow(argW, argH);
	}

	void fk_Renderer::SetScene(fk_Scene^ argScene)
	{
		pEngine->SetScene(argScene->GetP());
	}

	void fk_Renderer::Draw(void)
	{
		if (wglGetCurrentContext() != hRC)
		{
			wglMakeCurrent(hDC, hRC);
		}

		pEngine->Draw(false);

		SwapBuffers(hDC);
	}

	bool fk_Renderer::GetProjectPosition(double argX, double argY,
		fk_Plane^ argPlane, fk_Vector^ argPos)
	{
		if (!argPlane || !argPos) return false;
		::fk_Vector	retPos;
		bool		ret;

		ret = pEngine->GetProjectPosition(argX, argY, argPlane->pPlane, &retPos);
		argPos->Set(retPos.x, retPos.y, retPos.z);
		return ret;
	}

	bool fk_Renderer::GetProjectPosition(double argX, double argY,
		double argDist, fk_Vector^ argPos)
	{
		if (!argPos) return false;
		::fk_Vector	retPos;
		bool		ret;

		ret = pEngine->GetProjectPosition(argX, argY, argDist, &retPos);
		argPos->Set(retPos.x, retPos.y, retPos.z);
		return ret;
	}

	bool fk_Renderer::GetWindowPosition(fk_Vector^ argPos_3D, fk_Vector^ argPos_2D)
	{
		if (!argPos_3D || !argPos_2D) return false;
		::fk_Vector	retPos;
		bool		ret;

		ret = pEngine->GetWindowPosition(argPos_3D, &retPos);
		argPos_2D->Set(retPos.x, retPos.y, retPos.z);
		return ret;
	}

	cli::array<fk_PickData^>^ fk_Renderer::GetPickData(int argX, int argY, int argPixel)
	{
		::fk_PickData pick;
		pEngine->GetPickData(&pick, argPixel, argX, argY);
		int size = pick.getSize();
		cli::array<fk_PickData^>^ ret = gcnew cli::array<fk_PickData^>(size);
		for (int i = 0; i < size; ++i)
		{
			fk_Model^ pickedModel = gcnew fk_Model(pick.getModel(i));
			fk_PickedTopologyType^ pickedType;
			switch (pick.getType(i))
			{
			case FK_VERTEX:
				pickedType = fk_PickedTopologyType::VERTEX;
				break;
			case FK_EDGE:
				pickedType = fk_PickedTopologyType::EDGE;
				break;
			case FK_LOOP:
				pickedType = fk_PickedTopologyType::LOOP;
				break;
			default:
				pickedType = fk_PickedTopologyType::NONE;
				break;
			}

			ret[i] = gcnew fk_PickData(pickedModel, pickedType, pick.getID(i), pick.getFarDepth(i), pick.getNearDepth(i));
		}

		return ret;
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
