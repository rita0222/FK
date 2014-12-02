/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#include <FK/D3D/Engine.h>
#include <FK/Scene.h>
#include <FK/Light.h>
#include <FK/Plane.h>
#include <FK/PickData.h>
#include <FK/Projection.h>
#include <FK/D3D/PointDraw.h>
#include <FK/D3D/LineDraw.h>
#include <FK/D3D/FaceDraw.h>
#include <FK/D3D/TextureDraw.h>

#include <FK/Error.H>

using namespace std;

// ★★★★★ Direct3D オブジェクト
static LPDIRECT3D9			g_lpD3D = NULL;
static LPDIRECT3DDEVICE9	g_lpD3DDEV = NULL;

// OpenGL コンテキスト
static HGLRC				g_hRC = NULL;

static unsigned int			generalID = 1;
static unsigned int			g_lostSC = 0;

LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_lpD3DDEV;
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Direct3D の初期化
//-----------------------------------------------------------------------------
HRESULT fk_GraphicsEngine::InitD3D(HWND hWnd, bool argErrRep)
{
	// スワップチェインの有無で初期化済みかを判定
	if(m_lpD3DSC != NULL && g_lpD3DDEV != NULL) return S_OK;

	m_hWnd = hWnd;

	// D3D9 オブジェクトはグローバルでひとつだけ
	if(g_lpD3D == NULL) {
		if(NULL == (g_lpD3D = Direct3DCreate9(D3D_SDK_VERSION))) {
			if(argErrRep) MessageBox(m_hWnd, "Direct3D の作成に失敗しました。", "FK_D3D", MB_OK | MB_ICONSTOP);
			return E_FAIL;
		}
	}

	// 現在の画面モードを取得
    D3DDISPLAYMODE d3ddm;
    if(FAILED(g_lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) return E_FAIL;

	// Direct3D 初期化パラメータの設定
	ZeroMemory(&m_d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	// ウィンドウモードとしてパラメータをセット
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.Windowed = TRUE;
	m_d3dpp.BackBufferWidth = 0;
	m_d3dpp.BackBufferHeight = 0;
	// 現在の画面モードを使用
	m_d3dpp.BackBufferFormat = d3ddm.Format;
	m_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
	m_d3dpp.hDeviceWindow = m_hWnd;
	// Z バッファの自動作成
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	// 垂直同期は待たない
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// デバイスの作成は一度だけ、2回目以降は追加スワップチェインを作成
	if(g_lpD3DDEV == NULL) {
		bool retryFlag = true;
retry:
		// デバイスの作成 - T&L HAL
		if(FAILED(g_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &g_lpD3DDEV))) {
			// cout << "T&L HAL failed." << endl;
			// 失敗したので HAL で試行
			if(FAILED(g_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dpp, &g_lpD3DDEV))) {
				// cout << "HAL failed." << endl;
				// 失敗したので REF で試行
				if(FAILED(g_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dpp, &g_lpD3DDEV))) {
					// cout << "REF failed." << endl;
					// 結局失敗した
					if(argErrRep) MessageBox(m_hWnd, "Direct3D の初期化に失敗しました。", "FK_D3D", MB_OK | MB_ICONSTOP);
					return E_FAIL;
				} else if(retryFlag) {
					retryFlag = false;
					goto retry;
				}
			}
		}
		// デバイスオブジェクトへの参照をコピー
		ref_lpD3DDEV = g_lpD3DDEV;
		// スワップチェインの取得
		ref_lpD3DDEV->GetSwapChain(0, &m_lpD3DSC);
	} else {
		// デバイスオブジェクトへの参照をコピー
		ref_lpD3DDEV = g_lpD3DDEV;
		// 追加スワップチェインの作成
		ref_lpD3DDEV->CreateAdditionalSwapChain(&m_d3dpp, &m_lpD3DSC);

		CheckDepthBufferSize();
	}

	// 描画クラスにデバイスを渡してやる。仕方ないから。
	faceDraw->setD3DDevice(ref_lpD3DDEV);
	lineDraw->setD3DDevice(ref_lpD3DDEV);
	pointDraw->setD3DDevice(ref_lpD3DDEV);
	textureDraw->setD3DDevice(ref_lpD3DDEV);

	// 行列スタックの生成
	D3DXCreateMatrixStack(0, &modelStack);
	D3DXCreateMatrixStack(0, &viewStack);
	D3DXCreateMatrixStack(0, &projStack);

	InitGL4Pick();

	// cout << "InitD3D() passed." << endl;

    return S_OK;
}

// デプスバッファのサイズチェック(一番でかいサイズのウィンドウにあわせる必要がある)
void fk_GraphicsEngine::CheckDepthBufferSize(void)
{
	LPDIRECT3DSURFACE9	pCurrentDepthStencil, pNewDepthStencil;
	D3DSURFACE_DESC		desc;

	// 現在の深度ステンシルを得る。
	ref_lpD3DDEV->GetDepthStencilSurface(&pCurrentDepthStencil);

	if(pCurrentDepthStencil == NULL) return;

	// 深度ステンシルのサイズを得る。
	pCurrentDepthStencil->GetDesc(&desc);

	// 作成したスワップチェインと、深度ステンシルのサイズを比較。
	if(desc.Width < m_d3dpp.BackBufferWidth || desc.Height < m_d3dpp.BackBufferHeight) {
		// 深度ステンシルを作り直す。
		ref_lpD3DDEV->CreateDepthStencilSurface(m_d3dpp.BackBufferWidth, m_d3dpp.BackBufferHeight,
			D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &pNewDepthStencil, NULL);

		// デバイスに深度ステンシルを設定する。
		ref_lpD3DDEV->SetDepthStencilSurface(pNewDepthStencil);

		RELEASE(pCurrentDepthStencil);
	}

	return;
}

bool fk_GraphicsEngine::InitGL4Pick(void)
{
	if(g_hRC != NULL) return true;

	// OpenGL の初期化
	GLuint PixelFormat;

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
	
	HDC hDC = GetDC(m_hWnd);
	PixelFormat = ChoosePixelFormat(hDC, &pfd);
	if(SetPixelFormat(hDC, PixelFormat, &pfd) == FALSE) {
		ReleaseDC(m_hWnd, hDC);
		return false;
	}
	g_hRC = wglCreateContext(hDC);
	if(g_hRC == NULL) {
		ReleaseDC(m_hWnd, hDC);
		return false;
	}

	wglMakeCurrent(hDC, g_hRC);
	// cout << "->wglMakeCurrent():" << glGetError() << endl;
	ReleaseDC(m_hWnd, hDC);

	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPolygonMode(GL_FRONT, GL_FILL);
	// cout << "init state:" << glGetError() << endl;

	return true;
}

fk_GraphicsEngine::fk_GraphicsEngine(void)
{
	ref_lpD3DDEV = NULL;
	m_lpD3DSC = NULL;
	m_hWnd = NULL;

	pointDraw = new fk_PointDraw;
	lineDraw = new fk_LineDraw;
	faceDraw = new fk_FaceDraw;
	textureDraw = new fk_TextureDraw;

	winID = 0;
	curDLink = NULL;
	dLinkStatus = 0;
	dLinkID = 0;
	wSize = 0;
	hSize = 0;
	arrayState = false;
	resizeFlag = false;
	textureMode = false;

	return;
}

fk_GraphicsEngine::~fk_GraphicsEngine()
{
	generalID--;

	delete pointDraw;
	delete lineDraw;
	delete faceDraw;
	delete textureDraw;

	RELEASE(projStack);
	RELEASE(viewStack);
	RELEASE(modelStack);

	if(generalID == 1) {
		// 最後の一個ならデバイスを解放
		RELEASE(g_lpD3DDEV);
		RELEASE(g_lpD3D);
		// コンテキストの破棄
		if(g_hRC != NULL) {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(g_hRC);
			g_hRC = NULL;
		}
	} else {
		// そうでなければスワップチェインだけを解放
		RELEASE(m_lpD3DSC);
	}

	return;
}

void fk_GraphicsEngine::Init(int argW, int argH)
{
	winID = generalID;
	generalID++;
	curDLink = (fk_DisplayLink *)NULL;
	dLinkStatus = FK_UNDEFINED;
	dLinkID = FK_UNDEFINED;
	wSize = argW;
	hSize = argH;
	resizeFlag = false;
	arrayState = true;
	textureMode = false;

	pointDraw->setArrayState(arrayState);
	lineDraw->setArrayState(arrayState);
	faceDraw->setArrayState(arrayState);
	textureDraw->setArrayState(arrayState);

	textureDraw->setBindMode(true);

	return;
}

void fk_GraphicsEngine::ResizeWindow(int argW, int argH)
{
	if(argW == wSize && argH == hSize) return;

	wSize = argW;
	hSize = argH;
	resizeFlag = true;

	ClearTextureMemory();
	RELEASE(m_lpD3DSC);
	if(g_lostSC == 0) {
		RELEASE(g_lpD3DDEV);
		g_lostSC = generalID-1;
	}

	while(true) {
		if(InitD3D(m_hWnd, false) == S_OK) break;
	}
	D3DStateInit();
	g_lostSC--;

	return;
}

void fk_GraphicsEngine::ClearTextureMemory(void)
{
	textureDraw->clearTextureMemory();
	return;
}

unsigned long fk_GraphicsEngine::GetUsingTextureMemory(void)
{
	return textureDraw->getUsingTextureMemory();
}

void fk_GraphicsEngine::SetViewPort(void)
{
	const  D3DXVECTOR3	vEye(0.0f, 0.0f, 0.0f), vAt(0.0f, 0.0f, -1.0f), vUp(0.0, 1.0, 0.0);
	static D3DVIEWPORT9	vpInfo;
	static D3DXMATRIX	workMat;

	static LPDIRECT3DSURFACE9	pBackBuffer;

	vpInfo.X = 0;			vpInfo.Y = 0;
	vpInfo.Width = wSize;	vpInfo.Height = hSize;
	vpInfo.MinZ = 0.0f;		vpInfo.MaxZ = 1.0f;
	ref_lpD3DDEV->SetViewport(&vpInfo);

	// 右手系射影行列をセット
	if(curDLink == (fk_DisplayLink *)NULL) {
		SetDefaultProjection();
	} else {
		SetProjection(curDLink->getProjection());
	}

	// View 行列をロード
	D3DXMatrixLookAtRH(&workMat, &vEye, &vAt, &vUp);
	viewStack->LoadMatrix(&workMat);
	ref_lpD3DDEV->SetTransform(D3DTS_VIEW, viewStack->GetTop());

	// Model 行列は単位行列のまま
	modelStack->LoadIdentity();
	ref_lpD3DDEV->SetTransform(D3DTS_WORLD, modelStack->GetTop());

	// レンダリング先をこのインスタンスが持つスワップチェインに設定
	m_lpD3DSC->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	ref_lpD3DDEV->SetRenderTarget(0, pBackBuffer);

	return;
}

void fk_GraphicsEngine::SetDefaultPickProjection(void)
{
	double			aspect;

	aspect = GLfloat(wSize)/GLfloat(hSize);
	gluPerspective(40.0, aspect, 1.0, 6000.0);
}


void fk_GraphicsEngine::SetPickProjection(const fk_ProjectBase *argProj)
{
	fk_ProjectBase	*proj;
	fk_Perspective	*pers;
	fk_Frustum		*frus;
	fk_Ortho		*orth;

	proj = const_cast<fk_ProjectBase *>(argProj);

	switch(argProj->getMode()) {
	  case FK_PERSPECTIVE_MODE:
		pers = static_cast<fk_Perspective *>(proj);
		gluPerspective((180.0 * pers->getFovy())/FK_PI,
					   GLfloat(wSize)/GLfloat(hSize),
					   pers->getNear(), pers->getFar());
		break;

	  case FK_FRUSTUM_MODE:
		frus = static_cast<fk_Frustum *>(proj);
		glFrustum(frus->getLeft(), frus->getRight(),
				  frus->getBottom(), frus->getTop(),
				  frus->getNear(), frus->getFar());
		break;

	  case FK_ORTHO_MODE:
		orth = static_cast<fk_Ortho *>(proj);
		glOrtho(orth->getLeft(), orth->getRight(),
				orth->getBottom(), orth->getTop(),
				orth->getNear(), orth->getFar());
		break;

	  default:
		break;
	}

	return;
}

void fk_GraphicsEngine::SetPickViewPort(int argPixSize, int argX, int argY)
{
	GLint	ViewPort[4];

	if(g_hRC == NULL) return;

	glViewport(0, 0, wSize, hSize);

	glGetIntegerv(GL_VIEWPORT, &ViewPort[0]);
	glSelectBuffer(FK_PICKDATAMAX*5, selectBuf);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix((GLdouble)argX, (GLdouble)(hSize - argY),
				  (GLdouble)argPixSize, (GLdouble)argPixSize, ViewPort);

	if(curDLink == (fk_DisplayLink *)NULL) {
		SetDefaultPickProjection();
	} else {
		SetPickProjection(curDLink->getProjection());
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	return;
}

void fk_GraphicsEngine::SetDefaultProjection(void)
{
	static D3DXMATRIX	workMat;

	D3DXMatrixPerspectiveFovRH(&workMat, (float)(40.0f*FK_PI/180.0f), (float)wSize/(float)hSize, 1.0f, 6000.0f);
	projStack->LoadMatrix(&workMat);
	ref_lpD3DDEV->SetTransform(D3DTS_PROJECTION, projStack->GetTop());

	return;
}

void fk_GraphicsEngine::SetProjection(const fk_ProjectBase *argProj)
{
	fk_ProjectBase	*proj;
	fk_Perspective	*pers;
	fk_Frustum		*frus;
	fk_Ortho		*orth;
	D3DXMATRIX		workMat;

	proj = const_cast<fk_ProjectBase *>(argProj);

	switch(argProj->getMode()) {
	  case FK_PERSPECTIVE_MODE:
		pers = static_cast<fk_Perspective *>(proj);
		D3DXMatrixPerspectiveFovRH(&workMat, (float)(pers->getFovy()),
			(float)wSize/(float)hSize, (float)pers->getNear(), (float)pers->getFar());
		break;

	  case FK_FRUSTUM_MODE:
		frus = static_cast<fk_Frustum *>(proj);
		D3DXMatrixPerspectiveOffCenterRH(&workMat,
			(float)frus->getLeft(), (float)frus->getRight(),
			(float)frus->getBottom(), (float)frus->getTop(),
			(float)frus->getNear(), (float)frus->getFar());
		break;

	  case FK_ORTHO_MODE:
		orth = static_cast<fk_Ortho *>(proj);
		D3DXMatrixOrthoOffCenterRH(&workMat,
			(float)orth->getLeft(), (float)orth->getRight(),
			(float)orth->getBottom(), (float)orth->getTop(),
			(float)orth->getNear(), (float)orth->getFar());
		break;

	  default:
		break;
	}
    
	projStack->LoadMatrix(&workMat);
	ref_lpD3DDEV->SetTransform(D3DTS_PROJECTION, projStack->GetTop());

	return;
}

void fk_GraphicsEngine::D3DStateInit(void)
{
    ref_lpD3DDEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	ref_lpD3DDEV->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	ref_lpD3DDEV->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
	ref_lpD3DDEV->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	ref_lpD3DDEV->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	ref_lpD3DDEV->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    ref_lpD3DDEV->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    ref_lpD3DDEV->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	// ポイントのスムース化が見あたらない(ポイントスプライト使わないと無理め)
	// 変わりに固定サイズのポイント描画を設定
	ref_lpD3DDEV->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
    ref_lpD3DDEV->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
	ref_lpD3DDEV->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    ref_lpD3DDEV->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	ref_lpD3DDEV->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	ref_lpD3DDEV->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	ref_lpD3DDEV->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
	ref_lpD3DDEV->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
	ref_lpD3DDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	ref_lpD3DDEV->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	// ピクセルフォーマットはデバイス生成時に設定済み
    ref_lpD3DDEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    ref_lpD3DDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    ref_lpD3DDEV->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
    ref_lpD3DDEV->SetRenderState(D3DRS_ALPHAREF, 0x01);

	return;
}

void fk_GraphicsEngine::ApplySceneParameter(bool argVPFlg)
{
	// bool			fogStatus = false;
	fk_Scene		*scene;
	fk_Color		bgColor(0.0f, 0.0f, 0.0f);

	scene = (fk_Scene *)NULL;

	if(curDLink != (fk_DisplayLink *)NULL) {
		if(dLinkID != curDLink->GetID() ||
		   dLinkStatus != curDLink->GetProjChangeStatus()) {
			dLinkID = curDLink->GetID();
			dLinkStatus = curDLink->GetProjChangeStatus();
			if(argVPFlg == true) {
				SetViewPort();
			}
			if(curDLink->getObjectType() == FK_SCENE) {
				scene = (fk_Scene *)curDLink;
				scene->GetFogChangeStatus();
				// fogStatus = true;
			}
		} else {
			if(curDLink->getObjectType() == FK_SCENE) {
				scene = (fk_Scene *)curDLink;
				// fogStatus = scene->GetFogChangeStatus();
			}
		}
	}

	if(scene != (fk_Scene *)NULL) {
		if(scene->getBlendStatus() == true) {
		    ref_lpD3DDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		    ref_lpD3DDEV->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
		} else {
		    ref_lpD3DDEV->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		    ref_lpD3DDEV->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
		}
		/*
		if(fogStatus == true) {
			InitFogStatus(scene);
		}
		*/
		InitFogStatus(scene);	// D3D では常時設定しないとだめっぽい
		bgColor = scene->getBGColor();
	}
	// バックバッファと Z バッファをクリア
	ref_lpD3DDEV->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), GetPackedColor(&bgColor), 1.0f, 0);

	return;
}

void fk_GraphicsEngine::Draw(bool argPickFlg)
{
	// リサイズ時に加えて、マルチウィンドウ時もビューポートを再設定(by rita)
	if(resizeFlag == true || generalID > 2) {
		SetViewPort();
		resizeFlag = false;
	}

	ApplySceneParameter(true);

	viewStack->Push();
	RecalcModelView();

	// シーン開始
	ref_lpD3DDEV->BeginScene();
	DrawObjs(argPickFlg);
	// シーン終了
	ref_lpD3DDEV->EndScene();

	viewStack->Pop();

	return;
}

void fk_GraphicsEngine::Flip(void)
{
	// スワップチェイン経由でバックバッファをプライマリバッファにコピー
	if(FAILED(m_lpD3DSC->Present(NULL, NULL, m_hWnd, NULL, 0))) {
		resizeFlag = true;

		ClearTextureMemory();
		RELEASE(m_lpD3DSC);
		if(g_lostSC == 0) {
			RELEASE(g_lpD3DDEV);
			g_lostSC = generalID-1;
		}

		while(true) {
			if(InitD3D(m_hWnd, false) == S_OK) break;
		}
		D3DStateInit();
		g_lostSC--;
	}

	return;
}

void fk_GraphicsEngine::SetScene(fk_Scene *argScene)
{
	curDLink = argScene;
	return;
}

void fk_GraphicsEngine::RecalcModelView(bool argPickFlg)
{
	if(curDLink != (fk_DisplayLink *)NULL) {
		RecalcInhModelView(curDLink->getCamera(), argPickFlg);
	}

	if(argPickFlg == false) {
		ref_lpD3DDEV->SetTransform(D3DTS_VIEW, viewStack->GetTop());
	}

	return;
}

void fk_GraphicsEngine::RecalcInhModelView(const fk_Model *argModel, bool argPickFlg)
{
	static fk_Angle		MAngle(0.0, 0.0, 0.0);
	static fk_Vector	MPos(0.0, 0.0, 0.0);
	const D3DXVECTOR3	axisX(1.0f, 0.0f, 0.0f), axisY(0.0f, 1.0f, 0.0f), axisZ(0.0f, 0.0f, 1.0f);

	if(argModel == NULL) return;

	MAngle = argModel->getAngle();
	MPos = argModel->getPosition();

	if(argPickFlg == true) {
		glRotated(180.0*MAngle.b/FK_PI, 0.0, 0.0, 1.0);
		glRotated(-180.0*MAngle.p/FK_PI, 1.0, 0.0, 0.0);
		glRotated(180.0*MAngle.h/FK_PI, 0.0, 1.0, 0.0);
		glTranslated(-MPos.x, -MPos.y, -MPos.z);
	} else {
		viewStack->RotateAxisLocal(&axisZ, (float) MAngle.b);
		viewStack->RotateAxisLocal(&axisX, (float)-MAngle.p);
		viewStack->RotateAxisLocal(&axisY, (float) MAngle.h);
		viewStack->TranslateLocal((float)-MPos.x, (float)-MPos.y, (float)-MPos.z);
	}

	if(argModel->getParent() != (fk_Model *)NULL) {
		RecalcInhModelView(argModel->getParent(), argPickFlg);
	}

	return;
}

void fk_GraphicsEngine::DrawObjs(bool argPickFlg)
{
	list<fk_Model *>::iterator	modelP, modelPEnd;
	list<fk_Model *>			*overlayList;
	bool						lightFlag;

	if(curDLink == (fk_DisplayLink *)NULL) return;
	
	lightFlag = DefineLight();

	if(argPickFlg == true) {
		modelArray.clear();
	}

	textureDraw->startUp();

	modelPEnd = curDLink->GetModelList()->end();
	for(modelP = curDLink->GetModelList()->begin();
		modelP != modelPEnd; ++modelP) {
		DrawModel(*modelP, lightFlag, argPickFlg);
	}

	overlayList = curDLink->GetOverlayList();
	if(overlayList->empty() == true) return;

	if(argPickFlg == true) {
		glDisable(GL_DEPTH_TEST);
	} else {
		ref_lpD3DDEV->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	}

	modelPEnd = overlayList->end();
	for(modelP = overlayList->begin(); modelP != modelPEnd; ++modelP) {
		DrawModel(*modelP, lightFlag, argPickFlg);
	}

	if(argPickFlg == true) {
		glEnable(GL_DEPTH_TEST);
	} else {
		ref_lpD3DDEV->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}

	return;
}

void fk_GraphicsEngine::DrawModel(fk_Model *argModel,
								  bool argLightFlg,
								  bool argPickFlg)
{
	fk_Shape		*modelShape;
	fk_ObjectType	objType;

	if(argPickFlg == true) {
		if(argModel->getPickMode() == false) return;
		glLoadName(static_cast<GLuint>(modelArray.size()));
		modelArray.push_back(argModel);
	}

	modelShape = argModel->getShape();
	if(modelShape == NULL) return;

	if(argPickFlg == true) {
		glPushMatrix();
		LoadModelMatrix(argModel, true);
	} else {
		modelStack->Push();
		LoadModelMatrix(argModel);
		ref_lpD3DDEV->SetTransform(D3DTS_WORLD, modelStack->GetTop());
	}
		
	argModel->preShader();
	objType = modelShape->getObjectType();
	switch(objType) {
	  case FK_RECTTEXTURE:
	  case FK_TRITEXTURE:
	  case FK_MESHTEXTURE:
	  case FK_IFSTEXTURE:
		textureDraw->drawTextureObj(argModel, argLightFlg, argPickFlg);
		textureMode = true;
		break;

	  default:
		DrawShapeObj(argModel, argLightFlg, argPickFlg);
		break;
	}
	argModel->postShader();
		
	if(argPickFlg == true) {
		glPopMatrix();
	} else {
		modelStack->Pop();
	}

	return;
}

bool fk_GraphicsEngine::DefineLight(void)
{
	const int					MaxLNum = 8;
	int							LightID;
	list<fk_Model *>::iterator	LightP, LightPEnd;
	bool						lightFlag;
	fk_Material					*LightMate;
	fk_Light					*LightShape;
	fk_Vector					LightPos, LightDirection;

	D3DLIGHT9					lightInfo;

	if(curDLink->GetLightList()->size() == 0) {
		lightFlag = false;
	} else {
		lightFlag = true;
	}

	for(LightID = 0; LightID < MaxLNum; LightID++) {
		ref_lpD3DDEV->LightEnable(LightID, FALSE);
	}

	if(lightFlag == true) {
		LightP = curDLink->GetLightList()->begin();
		LightPEnd = curDLink->GetLightList()->end();

		for(LightID = 0;
			LightP != LightPEnd && LightID < MaxLNum;
			++LightP, ++LightID) {

			ZeroMemory(&lightInfo, sizeof(D3DLIGHT9));

			LightMate = (*LightP)->getInhMaterial();

			memcpy(&(lightInfo.Ambient), LightMate->getAmbient()->col, sizeof(D3DCOLORVALUE));
			memcpy(&(lightInfo.Diffuse), LightMate->getDiffuse()->col, sizeof(D3DCOLORVALUE));
			memcpy(&(lightInfo.Specular), LightMate->getSpecular()->col, sizeof(D3DCOLORVALUE));

			LightShape = (fk_Light *)(*LightP)->getShape();

			switch(LightShape->getLightType()) {
			  case FK_PARALLEL_LIGHT:
				lightInfo.Type = D3DLIGHT_DIRECTIONAL;
				LightDirection = (*LightP)->getInhVec();

				lightInfo.Direction.x = (float)LightDirection.x;
				lightInfo.Direction.y = (float)LightDirection.y;
				lightInfo.Direction.z = (float)LightDirection.z;

				break;

			  case FK_POINT_LIGHT:
				lightInfo.Type = D3DLIGHT_POINT;
				LightPos = (*LightP)->getInhPosition();

				lightInfo.Position.x = (float)LightPos.x;
				lightInfo.Position.y = (float)LightPos.y;
				lightInfo.Position.z = (float)LightPos.z;

				lightInfo.Attenuation0 = 1.0f;
				lightInfo.Attenuation1 = float(LightShape->getAttenuation(0));
				lightInfo.Attenuation2 = float(LightShape->getAttenuation(1));
				lightInfo.Range = 6000.0f;

				break;

			  case FK_SPOT_LIGHT:
				lightInfo.Type = D3DLIGHT_SPOT;
				LightPos = (*LightP)->getInhPosition();
				LightDirection = (*LightP)->getInhVec();

				lightInfo.Position.x = (float)LightPos.x;
				lightInfo.Position.y = (float)LightPos.y;
				lightInfo.Position.z = (float)LightPos.z;

				lightInfo.Direction.x = (float)LightDirection.x;
				lightInfo.Direction.y = (float)LightDirection.y;
				lightInfo.Direction.z = (float)LightDirection.z;

				lightInfo.Attenuation0 = 1.0f;
				lightInfo.Attenuation1 = float(LightShape->getAttenuation(0));
				lightInfo.Attenuation2 = float(LightShape->getAttenuation(1));
				lightInfo.Theta = float(LightShape->getSpotCutOff())*2.0f;
				lightInfo.Phi = float(LightShape->getSpotCutOff()+LightShape->getSpotExponent())*2.0f;
				lightInfo.Falloff = 1.0f;
				lightInfo.Range = 6000.0f;

			  default:
				break;
			}

			ref_lpD3DDEV->SetLight(LightID, &lightInfo);
			ref_lpD3DDEV->LightEnable(LightID, TRUE);
		}
	}	

	return lightFlag;
}

void fk_GraphicsEngine::DrawShapeObj(fk_Model *argObj,
									 bool argLightFlag, bool argPickFlg)
{
	fk_DrawMode		DrawMode;

	DrawMode = argObj->getDrawMode();

	if(DrawMode == FK_NONEMODE) return;

	if(textureMode == true) {
		ref_lpD3DDEV->SetTexture(0, NULL);
		textureMode = false;
	}

	if((DrawMode & FK_POLYMODE) != FK_NONEMODE) {
		faceDraw->drawShapeFace(argObj, argLightFlag, DrawMode, argPickFlg);
	}

	if((DrawMode & FK_POINTMODE) != FK_NONEMODE) {
		pointDraw->drawShapePoint(argObj, argPickFlg);
	}

	if((DrawMode & FK_LINEMODE) != FK_NONEMODE) {
		lineDraw->drawShapeLine(argObj, argPickFlg);
	}

	if(argLightFlag == true) {
	    ref_lpD3DDEV->SetRenderState(D3DRS_LIGHTING, TRUE);
	} else {
	    ref_lpD3DDEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	return;
}

void fk_GraphicsEngine::LoadModelMatrix(fk_Model *argModel, bool argPickFlg)
{
	fk_Angle			MAngle;
	fk_Vector			MPos;
	double				Scale;
	const D3DXVECTOR3	axisX(1.0f, 0.0f, 0.0f), axisY(0.0f, 1.0f, 0.0f), axisZ(0.0f, 0.0f, 1.0f);

	// 絶望した！精度劣悪の float ベースで行列演算をさせる Direct3D に絶望した！！
	MAngle = argModel->getAngle();
	MPos = argModel->getPosition();

	if(argModel->getParent() != (fk_Model *)NULL) {
		LoadModelMatrix(argModel->getParent(), argPickFlg);
	}

	// ピック用 OpenGL 処理
	if(argPickFlg == true) {
		glTranslated(MPos.x, MPos.y, MPos.z);
		glRotated(-180.0*MAngle.h/FK_PI, 0.0, 1.0, 0.0);
		glRotated(180.0*MAngle.p/FK_PI, 1.0, 0.0, 0.0);
		glRotated(-180.0*MAngle.b/FK_PI, 0.0, 0.0, 1.0);

		if(argModel->getScaleMode() == true) {
			Scale = argModel->getScale();
			glScaled(Scale * argModel->getScale(fk_X),
					Scale * argModel->getScale(fk_Y),
					Scale * argModel->getScale(fk_Z));
		}
	// 通常描画用 Direct3D 処理
	} else {
		modelStack->TranslateLocal((float)MPos.x, (float)MPos.y, (float)MPos.z);
		modelStack->RotateAxisLocal(&axisY, (float)-MAngle.h);
		modelStack->RotateAxisLocal(&axisX, (float) MAngle.p);
		modelStack->RotateAxisLocal(&axisZ, (float)-MAngle.b);

		if(argModel->getScaleMode() == true) {
			Scale = argModel->getScale();

			modelStack->ScaleLocal((float)(Scale * argModel->getScale(fk_X)),
								(float)(Scale * argModel->getScale(fk_Y)),
								(float)(Scale * argModel->getScale(fk_Z)));
		}
	}

	return;
}

void fk_GraphicsEngine::InitFogStatus(fk_Scene *argScene)
{
	fk_FogMode		fogMode = argScene->getFogMode();
	fk_Color		fogColor = argScene->getFogColor();
	float			tmpArg;

	if(fogMode == FK_NONE_FOG) {
		ref_lpD3DDEV->SetRenderState(D3DRS_FOGENABLE, FALSE);
		return;
	}

	ref_lpD3DDEV->SetRenderState(D3DRS_FOGENABLE, TRUE);
	ref_lpD3DDEV->SetRenderState(D3DRS_FOGCOLOR, GetPackedColor(&fogColor));

	switch(fogMode) {
	  case FK_EXP_FOG:
		ref_lpD3DDEV->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);
		tmpArg = float(argScene->getFogDensity());
		ref_lpD3DDEV->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&tmpArg));
		break;
	
	  case FK_EXP2_FOG:
		ref_lpD3DDEV->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP2);
		tmpArg = float(argScene->getFogDensity());
		ref_lpD3DDEV->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&tmpArg));
		break;

	  case FK_LINEAR_FOG:
		ref_lpD3DDEV->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
		tmpArg = float(argScene->getFogLinearStart());
		ref_lpD3DDEV->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&tmpArg));
		tmpArg = float(argScene->getFogLinearEnd());
		ref_lpD3DDEV->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&tmpArg));
		break;

	  default:
		break;
	}

	// D3D にフォグの品質なんてものは存在しないらしい
	/*
	switch(argScene->getFogOption()) {
	  case FK_FASTEST_FOG:
		glHint(GL_FOG_HINT, GL_FASTEST);
		break;

	  case FK_NICEST_FOG:
		glHint(GL_FOG_HINT, GL_NICEST);
		break;

	  case FK_NOOPTION_FOG:
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		break;

	  default:
		break;
	}
	*/

	return;
}

void fk_GraphicsEngine::ViewMatCalc(fk_Matrix *argMat)
{
	D3DXMATRIX		tmpModel, tmpView, tmpProj;
	D3DVIEWPORT9	tmpVP;
	fk_Matrix		modelMat, ViewMat, projMat;
	int				ii, ij;

	viewStack->Push();
	RecalcModelView();

	ref_lpD3DDEV->GetViewport(&tmpVP);
	viewArray[0] = tmpVP.X;		viewArray[1] = tmpVP.Y;
	viewArray[2] = tmpVP.Width;	viewArray[3] = tmpVP.Height;
	ref_lpD3DDEV->GetTransform(D3DTS_PROJECTION, &tmpProj);
	ref_lpD3DDEV->GetTransform(D3DTS_VIEW, &tmpView);

	viewStack->Pop();

	for(ii = 0; ii < 4; ii++) {
		for(ij = 0; ij < 4; ij++) {
			projMat[ii][ij] = tmpProj[ii+ij*4];
			viewMat[ii][ij] = tmpView[ii+ij*4];
		}
	}

	*argMat = projMat * viewMat;
	return;
}

bool fk_GraphicsEngine::GetViewLinePos(double argX, double argY,
									   fk_Vector *retS, fk_Vector *retE)
{
	fk_HVector		inVec, outVec;
	fk_Matrix		mat;
	double			tmpY;

	ViewMatCalc(&mat);
	mat.inverse();

	tmpY = double(hSize) - argY - 1.0;
	inVec.x = (argX - double(viewArray[0]))*2.0/double(viewArray[2]) - 1.0;
	inVec.y = (tmpY - double(viewArray[1]))*2.0/double(viewArray[3]) - 1.0;
	inVec.w = 1.0;

	inVec.z = -1.0;
	outVec = mat * inVec;
	if(fabs(outVec.w) < FK_EPS) return false;
	retS->set(outVec.x/outVec.w, outVec.y/outVec.w, outVec.z/outVec.w);

	inVec.z = 1.0;
	outVec = mat * inVec;
	if(fabs(outVec.w) < FK_EPS) return false;
	retE->set(outVec.x/outVec.w, outVec.y/outVec.w, outVec.z/outVec.w);

	return true;
}

bool fk_GraphicsEngine::GetProjectPosition(double argX, double argY,
										   fk_Plane *argPlane,
										   fk_Vector *retPos)
{
	fk_Vector		sVec, eVec;

	if(curDLink == (fk_DisplayLink *)NULL) return false;

	if(generalID > 2) SetViewPort();

	GetViewLinePos(argX, argY, &sVec, &eVec);
	return argPlane->calcCrossPos(sVec, eVec, retPos);
}

bool fk_GraphicsEngine::GetProjectPosition(double argX, double argY,
										   double argDist, fk_Vector *retPos)
{
	fk_Vector		sVec, eVec, eyeVec, cameraPos;
	const fk_Model	*tmpCamera = curDLink->getCamera();

	if(curDLink == (fk_DisplayLink *)NULL) return false;

	if(generalID > 2) SetViewPort();

	GetViewLinePos(argX, argY, &sVec, &eVec);
	eyeVec = eVec - sVec;
	eyeVec.normalize();
	if(tmpCamera == NULL) {
		cameraPos.set(0.0, 0.0, 0.0);
	} else {
		cameraPos = tmpCamera->getInhPosition();
	}

	*retPos = cameraPos + eyeVec * argDist;
	return true;
}

bool fk_GraphicsEngine::GetWindowPosition(fk_Vector argPos, fk_Vector *retPos)
{
	fk_HVector		inVec, outVec;
	fk_Matrix		mat;

	inVec = argPos;
	inVec.w = 1.0;

	if(generalID > 2) SetViewPort();

	ViewMatCalc(&mat);
	outVec = mat * inVec;
	if(fabs(outVec.w) < FK_EPS) return false;
	outVec /= outVec.w;
	retPos->set(double(viewArray[0]) +
				double(viewArray[2])*(outVec.x + 1.0)/2.0,
				double(viewArray[1]) + double(hSize) - 1.0 -
				double(viewArray[3])*(outVec.y + 1.0)/2.0,
				(1.0 + outVec.z)/2.0);
	return true;
}

/*
void fk_GraphicsEngine::SetOGLPointerMode(bool argFlg)
{
	arrayState = argFlg;
	pointDraw->setArrayState(arrayState);
	lineDraw->setArrayState(arrayState);
	faceDraw->setArrayState(arrayState);
	textureDraw->setArrayState(arrayState);
	return;
}

bool fk_GraphicsEngine::GetOGLPointerMode(void)
{
	return arrayState;
}

void fk_GraphicsEngine::SetOGLTextureBindMode(bool argFlg)
{
	textureDraw->setBindMode(argFlg);
	return;
}

bool fk_GraphicsEngine::GetOGLTextureBindMode(void)
{
	return textureDraw->getBindMode();
}

bool fk_GraphicsEngine::SnapImage(string argFName, fk_ImageType argType, fk_SnapProcMode argMode)
{
	fk_Image	tmpImage;

	if(SnapImage(&tmpImage, argMode) == false) return false;

	switch(argType) {
	  case FK_IMAGE_PNG:
		return tmpImage.writePNG(argFName, false);
	  case FK_IMAGE_JPG:
		return tmpImage.writeJPG(argFName);
	  case FK_IMAGE_BMP:
	  default:
		break;
	}
	return tmpImage.writeBMP(argFName);
}
*/

bool fk_GraphicsEngine::SnapImage(fk_Image *argImage, fk_SnapProcMode argMode)
{
	LPDIRECT3DSURFACE9	pSurface = NULL;
	LPD3DXBUFFER		pBuffer = NULL;

	if(argImage == (fk_Image *)NULL) return false;

	// バックバッファを取得
	if(D3D_OK != m_lpD3DSC->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pSurface)) {
		return false;
	}

	// オンメモリBMPファイルとして書き出し
	if(D3D_OK != D3DXSaveSurfaceToFileInMemory(&pBuffer, D3DXIFF_BMP, pSurface, NULL, NULL)) {
		return false;
	}

	// オンメモリBMPからfk_Imageへ取り込み
	if(!argImage->readBMPData((fk_ImType *)pBuffer->GetBufferPointer())) {
		pBuffer->Release();
		return false;
	}

	pBuffer->Release();
	return true;
}

void fk_GraphicsEngine::GetPickData(fk_PickData *argPickData,
									int argPixSize,
									int argMouseX, int argMouseY)
{
	GLint			hits;
	unsigned int	ii;
	int				elemID;
	fk_ObjectType	elemType = FK_BASEOBJECT;
	double			farDepth, nearDepth;

	if(argPickData == (fk_PickData *)NULL) return;

	SetPickViewPort(argPixSize, argMouseX, argMouseY);
	RecalcModelView(true);
	DrawObjs(true);

	hits = glRenderMode(GL_RENDER);

	argPickData->ClearData();

	for(ii = 0; ii < (unsigned int)hits; ii++) {
		switch(selectBuf[ii*5 + 4] % 3) {
		  case 0:
			elemType = FK_LOOP;
			break;

		  case 1:
			elemType = FK_EDGE;
			break;

		  case 2:
			elemType = FK_VERTEX;
			break;

		  default:
			break;
		}

		elemID = selectBuf[ii*5 + 4]/3;
		farDepth = (double)selectBuf[ii*5 + 1]/0xffffffff;
		nearDepth = (double)selectBuf[ii*5 + 2]/0xffffffff;

		argPickData->PushData(modelArray[selectBuf[ii*5 + 3]],
							  elemID, elemType, farDepth, nearDepth);
	}

	SetViewPort();

	return;
}
