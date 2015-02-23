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
		fk_Renderer::fk_Renderer(void);
		fk_Renderer::~fk_Renderer();
		fk_Renderer::!fk_Renderer();

		bool Initialize(System::IntPtr pWnd, int w, int h);
		void Shutdown(void);
		void Resize(int w, int h);
		void SetScene(fk_Scene^ scene);
		void Draw(void);
	};
}
