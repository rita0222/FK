#include "Renderer_CLI.h"
#include <msclr/marshal_cppstd.h>
#include <GL/gl.h>
#include <stdlib.h>

std::vector<HGLRC>* GetRcArray(void)
{
	static std::vector<HGLRC> rcArray;
	return &rcArray;
}

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

		std::vector<HGLRC> *rcArray = GetRcArray();
		rcArray->push_back(hRC);
		if (rcArray->size() > 1)
		{
			wglShareLists(rcArray->at(0), hRC);
		}

		wglMakeCurrent(hDC, hRC);
		pEngine->Init(argW, argH);
		pEngine->OpenGLInit();
		return true;
	}

	void fk_Renderer::Shutdown(void)
	{
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
}
