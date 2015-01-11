// Renderer_CLI.h

#pragma once

#include <FK/Engine.H>
#include <msclr/marshal_cppstd.h>
#include "Scene_CLI.h"

namespace FK_CLI
{
	public ref class fk_Renderer {
	private:
		HWND	hWnd;
		HDC		hDC;
		HGLRC	hRC;

		::fk_GraphicsEngine *pEngine;

	public:
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

		bool Initialize(System::IntPtr pWnd, int w, int h);
		void Shutdown(void);
		void Resize(int w, int h);
		void SetScene(fk_Scene^ scene);
		void Draw(void);
	};
}
