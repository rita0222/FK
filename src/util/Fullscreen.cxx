// fk_FullscreenControllerクラス
// WIN32APIを利用した完全なフルスクリーンモードを提供します。

#include <FK/Fullscreen.h>

using namespace FK;
using namespace std;

#if defined(WIN32) && !defined(_MINGW_) && !defined(FK_CLI_CODE)

/*
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
static LPDIRECT3D9			g_lpD3D = nullptr;
static LPDIRECT3DDEVICE9	g_lpD3DDEV = nullptr;
*/

// グローバル変数
static struct fk_FullscreenController::WindowState WindowState[fk_FullscreenController::MAX_WINDOWNUMBER];
static int iWindowNumber;					// 画面上のウインドウ数

// ウインドウ位置保存のコールバック関数
BOOL CALLBACK EnumWindowsSaveFunc(HWND hWnd, LPARAM lParam)
{
	char szWindowName[fk_FullscreenController::MAX_NAMELENGTH];
	char szClassName[fk_FullscreenController::MAX_NAMELENGTH];

	// ウインドウ名とクラス名の取得
	GetWindowText(hWnd, szWindowName, fk_FullscreenController::MAX_NAMELENGTH);
	GetClassName(hWnd, szClassName, fk_FullscreenController::MAX_NAMELENGTH);

	// 見えているウインドウだけをセレクト
	if(IsWindowVisible(hWnd) &&
		GetWindow(hWnd, GW_OWNER) == nullptr &&
		lstrlen(szWindowName) > 0 &&
		lstrcmp(szClassName, "Progman") != 0 ){

		// ウインドウ位置を保存
		if(iWindowNumber < fk_FullscreenController::MAX_WINDOWNUMBER){
			WindowState[iWindowNumber].WindowPlacement.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(hWnd, &WindowState[iWindowNumber].WindowPlacement);
			WindowState[iWindowNumber].hWnd = hWnd;

			++iWindowNumber;
		}
	}

	return TRUE;
}

// ウインドウ位置再現のコールバック関数
BOOL CALLBACK EnumWindowsLoadFunc(HWND hWnd, LPARAM lParam)
{
	char szWindowName[fk_FullscreenController::MAX_NAMELENGTH];
	int  i;

	// ウインドウ名の取得
	GetWindowText(hWnd, szWindowName, fk_FullscreenController::MAX_NAMELENGTH);

	// 保存されているウインドウを検索
	for(i = 0; i < iWindowNumber; i++){
		if(WindowState[i].hWnd == hWnd) break;
	}

	// 見つかったら元の場所に戻す
	if(i != iWindowNumber){
		SetWindowPlacement(hWnd, &WindowState[i].WindowPlacement);
	}

	return TRUE;
}

fk_FullscreenController::Member::Member(void) :
	pFlWnd(nullptr), pFkWnd(nullptr), hFlWnd(nullptr),
	nWndX(0), nWndY(0), nWndW(0), nWndH(0),
	fscW(0), fscH(0), mode(true)
{
	return;
}

// プライベートコンストラクタ
fk_FullscreenController::fk_FullscreenController() : _m(make_unique<Member>())
{
	return;
}
// プライベートデストラクタ
fk_FullscreenController::~fk_FullscreenController()
{
	return;
}

// ウインドウ位置保存
BOOL fk_FullscreenController::SaveWindowPosition()
{
	iWindowNumber = 0;
	if(EnumWindows(EnumWindowsSaveFunc, NULL) == 0)	return FALSE;

	return TRUE;
}

// ウインドウ位置再現
BOOL fk_FullscreenController::LoadWindowPosition()
{
	if(EnumWindows(EnumWindowsLoadFunc, NULL) == 0)	return FALSE;

	return TRUE;
}

// フルスクリーン化
BOOL fk_FullscreenController::ChangeScreen(HWND hWnd, int iFlag, int nWidth, int nHeight)
{
	DEVMODE DeviceMode;
	memset(&DeviceMode, 0, sizeof(DeviceMode));

	// フルスクリーンにするですよ
	if (iFlag == int(fk_FullscreenMode::SCMODE_FULLSCREEN)) {

		// 現在の色数を取得
		HDC hDC = GetDC(hWnd);
		int ScreenColors = GetDeviceCaps(hDC, BITSPIXEL);
		int ScreenWidth = GetDeviceCaps(hDC, HORZRES);
		int ScreenHeight = GetDeviceCaps(hDC, VERTRES);
		int ScreenRefresh = GetDeviceCaps(hDC, VREFRESH);
		ReleaseDC(hWnd, hDC);

		// 今のスクリーンサイズが一緒ならいじらない
		if(ScreenWidth != nWidth || ScreenHeight != nHeight) {
			// フルスクリーンモードを探す
			int	i = 0, just = -1, overlap = 0;
			while(true){
				if(!EnumDisplaySettings(nullptr, i, &DeviceMode)) break;
				if(DeviceMode.dmPelsWidth == (unsigned int)nWidth &&
					DeviceMode.dmPelsHeight	== (unsigned int)nHeight &&
					DeviceMode.dmBitsPerPel	== (DWORD)ScreenColors &&
					DeviceMode.dmDisplayFrequency == 60) {
						just = i;
						break;
				}
				if(DeviceMode.dmPelsWidth >= (unsigned int)nWidth &&
					DeviceMode.dmPelsHeight	>= (unsigned int)nHeight &&
					DeviceMode.dmBitsPerPel	== (DWORD)ScreenColors &&
					DeviceMode.dmDisplayFrequency == 60) {
						just = i;
						overlap = 1;
						break;
				}
				i++;
			}
			if(just == -1) return FALSE;
			EnumDisplaySettings(nullptr, just, &DeviceMode);
			fscW = DeviceMode.dmPelsWidth;
			fscH = DeviceMode.dmPelsHeight;
			DeviceMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

			// フルスクリーンに変更
			if(ChangeDisplaySettings(&DeviceMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
				fscW = fscH = 0;
				return FALSE;
			}
		} else {
			fscW = nWidth;
			fscH = nHeight;
		}
		// 常に最前面設定用
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0,
			SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE);
	}

	// 元の画面モードに戻すですよ
	if(iFlag == int(fk_FullscreenMode::SCMODE_WINDOW)) {
		ChangeDisplaySettings(nullptr, 0);
		// 常に最前面設定を解除
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,
			SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE);
		fscW = fscH = 0;
	}

	return TRUE;
}

// バインド初期化
void fk_FullscreenController::init(Fl_Window *p_main_win, fk_Window *p_draw_win)
{
	// ポインタ受け取り
	_m->pFlWnd = p_main_win;		// Fl_Window操作用にポインタを取得
	_m->hFlWnd = fl_xid(pFlWnd);	// 解像度変更用にウィンドウハンドルを取得
	_m->pFkWnd = p_draw_win;
	_m->mode = false;

	return;
}

/*
bool fk_FullscreenController::changeByD3D(bool argMode)
{
	// D3D9 オブジェクトはグローバルでひとつだけ
	if(g_lpD3D == nullptr) {
		if(nullptr == (g_lpD3D = Direct3DCreate9(D3D_SDK_VERSION))) {
			MessageBox(hFlWnd, "Direct3D の作成に失敗しました。", "FK_D3D", MB_OK | MB_ICONSTOP);
			return false;
		}
	}

	// 現在の画面モードを取得
    D3DDISPLAYMODE			d3ddm;
    if(FAILED(g_lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) return false;

	// Direct3D 初期化パラメータの設定
	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	// フルスクリーンモードとしてパラメータをセット
	d3dpp.BackBufferCount = 0;
	d3dpp.Windowed = FALSE;
	d3dpp.BackBufferWidth = nW;
	d3dpp.BackBufferHeight = nH;
	// 現在の画面モードを使用
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hFlWnd;
	// Zバッファとかはいらない
	d3dpp.EnableAutoDepthStencil = FALSE;
	// 垂直同期は待たない
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// デバイスの作成は一度だけ、2回目以降は追加スワップチェインを作成
	if(g_lpD3DDEV == nullptr  && argMode) {
		// デバイス作成は2回試行する
		for(int i = 0; i < 1; i++) {
			// デバイスの作成 - T&L HAL
			if(FAILED(g_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hFlWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_lpD3DDEV))) {
				// 失敗したので HAL で試行
				if(FAILED(g_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hFlWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_lpD3DDEV))) {
					// 失敗したので REF で試行
					if(FAILED(g_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hFlWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_lpD3DDEV))) {
						// 結局失敗した
						MessageBox(hFlWnd, "Direct3D の初期化に失敗しました。", "FK_D3D", MB_OK | MB_ICONSTOP);
						return false;
					}
				}
			}
		}
	} else if(g_lpD3DDEV != nullptr && !argMode) {
		g_lpD3DDEV->Release();
		g_lpD3DDEV = nullptr;
		g_lpD3D->Release();
		g_lpD3D = nullptr;
	}

	return true;
}
*/

// モードチェック
bool fk_FullscreenController::isFullscreen()
{
	return _m->mode;
}

// フルスクリーン化
bool fk_FullscreenController::changeToFullscreen()
{
	if(_m->mode == false) {
		// ウィンドウサイズ保存
		SaveWindowPosition();
		_m->nWndX = _m->pFlWnd->x();
		_m->nWndY = _m->pFlWnd->y();
		_m->nWndW = _m->pFkWnd->w();
		_m->nWndH = _m->pFkWnd->h();

		// 解像度変更
		_m->pFlWnd->fullscreen();	// Fl_Windowのフルスクリーン(ラベルバー消去)
		if(ChangeScreen(_m->hFlWnd, int(fk_FullscreenMode::SCMODE_FULLSCREEN),
						_m->nWndW, _m->nWndH) == TRUE) {
			_m->pFlWnd->resize(0, 0, fscW, fscH);	// リサイズ
			_m->pFlWnd->color(FL_BLACK);
			_m->pFkWnd->resizeWindow((_m->fscW - _m->nWndW)/2,
									 (_m->fscH - _m->nWndH)/2,
									 _m->nWndW, _m->nWndH);
			_m->mode = true;

			return true;
		} else {
			_m->pFlWnd->fullscreen_off(_m->nWndX, _m->nWndY, _m->nWndW, _m->nWndH);
			LoadWindowPosition();
			MessageBox(_m->hFlWnd, "FullScreen Failed", "FullScreen Failed", 0);
			return false;
		}
	} else {
		return true;
	}

}

// ウィンドウ化
void fk_FullscreenController::changeToWindow()
{
	if(mode == true) {
		pFlWnd->fullscreen_off(nWndX, nWndY, nWndW, nWndH);
		pFkWnd->resizeWindow(0, 0, nWndW, nWndH);
		ChangeScreen(hFlWnd, int(fk_FullscreenMode::SCMODE_WINDOW), nWndW, nWndH);
		LoadWindowPosition();

		mode = false;
	}

	return;
}

#else // !WIN32

fk_FullscreenController::fk_FullscreenController(void)
{
	return;
}

fk_FullscreenController::~fk_FullscreenController()
{
	return;
}

void fk_FullscreenController::init(Fl_Window *, fk_Window *)
{
	return;
}

bool fk_FullscreenController::isFullscreen(void)
{
	return false;
}

bool fk_FullscreenController::changeToFullscreen(void)
{
	return false;
}

void fk_FullscreenController::changeToWindow(void)
{
	return;
}

#endif

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
