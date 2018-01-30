/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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

#define _INPUTSRC_

#define FKUT_INPUT
#include <FK/Input.h>

#if defined(WIN32) && !defined(_MINGW_)

#include <windows.h>

#include <iostream>

#ifndef RELEASE
#define RELEASE(x)	{if(x){(x)->Release();(x)=nullptr;}}
#endif

#pragma warning(disable:4800)

using namespace std;
using namespace FK;

//==================================================
//			コンストラクタ
//==================================================
fk_Input::fk_Input()
{
	m_hwnd = nullptr;

	m_MouseWorldPos.x = 0;
	m_MouseWorldPos.y = 0;
	m_MouseLocalPos.x = 0;
	m_MouseLocalPos.y = 0;
	m_MouseWheel = 0;
	memset(m_Button, 0, sizeof(bool) * MOUSE_BUTTON_MAX);
	memset(m_LastButton, 0, sizeof(bool) * MOUSE_BUTTON_MAX);

	m_JoyCount = 0;
	m_Input = nullptr;
	m_KeyBoardDevice = nullptr;
	m_MouseDevice = nullptr;
	for(DWORD i = 0; i < INPUT_DEVICE_NUM; i++) {
		m_JoyStciDevice[i] = nullptr;
		
		for(int j = 0; j < BUTTON_NUM; j++) {
			buttonSwap[i][j] = j;
		}

		setBorder(i, 500, 500);
		setMinMax(i, 200, 900);

		setAxisSwap(i, AXIS1_X, AXIS_X_POS);
		setAxisSwap(i, AXIS1_Y, AXIS_Y_POS);
		setAxisSwap(i, AXIS2_X, AXIS_Z_POS);
		setAxisSwap(i, AXIS2_Y, AXIS_RZ_POS);
		setAxisSwap(i, AXIS3_X, AXIS_RX_POS);
		setAxisSwap(i, AXIS3_Y, AXIS_RY_POS);
	}
	m_JoyButton = nullptr;

	setAxisAssign(0, DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT);
	setAxisAssign(1, 0, 0, 0, 0);
	setAxisAssign(2, 0, 0, 0, 0);
	setPOVAssign(DIK_NUMPAD7, DIK_NUMPAD8, DIK_NUMPAD9, DIK_NUMPAD4, DIK_NUMPAD6, DIK_NUMPAD1, DIK_NUMPAD2, DIK_NUMPAD3);
	for(int i = 0; i < BUTTON_NUM; i++) {
		setKeyAssign(i, 0);
	}

	return;
}

//===================================================
//			デストラクタ
//===================================================
fk_Input::~fk_Input()
{
	uninit();
}

//===================================================
//	初期化
//===================================================
HRESULT fk_Input::init(HINSTANCE hinst, HWND hwnd)
{
	m_hwnd = hwnd;
	HRESULT hr;

	// DirectInput の作成
	hr = DirectInput8Create(hinst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_Input, nullptr);
	if(FAILED(hr)) return hr;

	//==============================
	//	キーボード
	//==============================
	// キーボードデバイスの作成
	hr = m_Input->CreateDevice(GUID_SysKeyboard, &m_KeyBoardDevice, nullptr); 
	if(FAILED(hr)) return hr;

	// 取得データフォーマットの設定
	hr = m_KeyBoardDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)) return hr;

	// 強調レベル設定
	hr = m_KeyBoardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(hr)) return hr;

	ZeroMemory(m_Key, sizeof(m_Key));

	// バッファサイズの指定
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	dipdw.dwData			= DIMGR_BUFFER_SIZE; // Arbitary buffer size

	if(FAILED(hr = m_KeyBoardDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph))) return hr;

	// アクセス権取得
	if(m_KeyBoardDevice) m_KeyBoardDevice->Acquire(); 

	//==============================
	//マウス
	//==============================
	hr = m_Input->CreateDevice(GUID_SysMouse, &m_MouseDevice, nullptr); 
	if(FAILED(hr)) return hr;
	
	// データ形式を設定
	hr = m_MouseDevice->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(hr)) return hr;

	//モードを設定（フォアグラウンド＆非排他モード）
	hr = m_MouseDevice->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if(FAILED(hr)) return hr;

	DIPROPDWORD dimouse;
	dimouse.diph.dwSize			= sizeof(dimouse); 
	dimouse.diph.dwHeaderSize	= sizeof(dimouse.diph); 
	dimouse.diph.dwObj			= 0;
	dimouse.diph.dwHow			= DIPH_DEVICE;
	dimouse.dwData				= DIPROPAXISMODE_REL;	
	//dimouse.dwData			= DIPROPAXISMODE_ABS;	// 絶対値モードの場合
	hr = m_MouseDevice->SetProperty(DIPROP_AXISMODE, &dimouse.diph);
	if(FAILED(hr)) return hr;

	// バッファリング・データを取得するため、バッファ・サイズを設定
	dimouse.dwData = DIMGR_BUFFER_SIZE;
	hr =m_MouseDevice->SetProperty(DIPROP_BUFFERSIZE, &dimouse.diph);
	if(FAILED(hr)) return hr;
	m_MouseDevice->Acquire();


	//=================================
	//ジョイスティック
	//=================================

	m_JoyMaxCount = ::joyGetNumDevs();
	
	hr = m_Input->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, (void*)this, DIEDFL_ATTACHEDONLY);
	if(FAILED(hr)) return hr;

	DIPROPDWORD diprop;
	diprop.diph.dwSize			= sizeof(diprop); 
	diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
	diprop.diph.dwObj			= 0;
	diprop.diph.dwHow			= DIPH_DEVICE;
	diprop.dwData				= DIPROPAXISMODE_ABS;

	m_JoyButton = new fk_InputInfo[m_JoyCount];
	
 	for(DWORD i = 0; i < m_JoyCount; i++) {
		hr = m_JoyStciDevice[i]->SetDataFormat(&c_dfDIJoystick);
		if(FAILED(hr)) {
			m_JoyCount--;
			return hr;
		}

		hr = m_JoyStciDevice[i]->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if(FAILED(hr)) {
			m_JoyCount--;
			return hr;
		}

		hr = m_JoyStciDevice[i]->EnumObjects(EnumSizesCallback, (void*)m_JoyStciDevice[i], DIDFT_AXIS);
		if(FAILED(hr)) {
			m_JoyCount--;
			return hr;
		}

		hr = m_JoyStciDevice[i]->SetProperty(DIPROP_AXISMODE, &diprop.diph);
		if(FAILED(hr)) {
			// 2つ目以降のデバイスではエラーを吐くらしい
			// 1つ目の場合はエラー扱いで強制停止、2つめ以降ではスルー
			if(i == 0) {
				m_JoyCount--;
				return hr;
			}
		}

		// バッファリング・データを取得するため、バッファ・サイズを設定
		diprop.dwData = DIMGR_BUFFER_SIZE;
		hr = m_JoyStciDevice[i]->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);
		if(FAILED(hr)) {
			m_JoyCount--;
			return hr;
		}

		m_JoyStciDevice[i]->Acquire();

		ZeroMemory(&m_JoyButton[i], sizeof(fk_InputInfo));
		m_JoyButton[i].pov = -1;
	}

	return S_OK;
}

void fk_Input::setBorder(int id, int inAllowX, int inAllowY)
{
	if(id < 0 || id >= INPUT_DEVICE_NUM) return;

	m_AllowX[id] = inAllowX;
	m_AllowY[id] = inAllowY;

	return;
}

void fk_Input::setBorder(int inAllowX, int inAllowY)
{
	setBorder(0, inAllowX, inAllowY);
}

void fk_Input::setMinMax(int id, int inMin, int inMax)
{
	if(id < 0 || id >= INPUT_DEVICE_NUM) return;
	if(inMin > inMax) return;

	m_AllowMin[id] = inMin;
	m_AllowMax[id] = inMax;

	return;
}

void fk_Input::setMinMax(int inMin, int inMax)
{
	setMinMax(0, inMin, inMax);
}

//-----------------------------------------------------------
//	終了
//-----------------------------------------------------------
HRESULT fk_Input::uninit()
{	
	//============================
	//キーボード
	//============================
	if(m_KeyBoardDevice != nullptr) {
		m_KeyBoardDevice->Unacquire();
		RELEASE(m_KeyBoardDevice);
	}

	//============================
	//マウス
	//============================
	if(m_MouseDevice != nullptr) {
		m_MouseDevice->Unacquire();
		RELEASE(m_MouseDevice);
	}

	//==============================
	//　ジョイスティック
	//==============================
	for(DWORD i = 0; i < m_JoyCount; i++) {
		if(m_JoyStciDevice[i]) {
			m_JoyStciDevice[i]->Unacquire(); 
			RELEASE(m_JoyStciDevice[i]);
		}
	}
	
	if(m_JoyButton != nullptr) {
		delete []m_JoyButton;
		m_JoyButton = nullptr;
	}

	//================================
	//最後にDirectInput
	//================================
	RELEASE(m_Input);

	return S_OK;
}

//===============================================
//キーを取得します。
//===============================================
bool fk_Input::GetKey(const DWORD keycode)
{
	return m_Key[keycode];
}


//==================================
//全てのデバイスをアップデートします。
//==================================
HRESULT fk_Input::update()
{
	bool A = UpdateMouse() == S_OK;
	bool B = UpdateKey() == S_OK;
	bool C = UpdateJoy() == S_OK;
	if(A && B && C) {
		return S_OK;
	}
	return E_FAIL;
}



//==================================================
//キーをアップデートします。
//==================================================
HRESULT fk_Input::UpdateKey()
{
	DWORD	elements;
	HRESULT	hr;

    if(nullptr == m_KeyBoardDevice) {
        return S_OK;
	}
    elements = DIMGR_BUFFER_SIZE;
    hr = m_KeyBoardDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_DeviceObject, &elements, 0);
    if(hr != DI_OK) {
		if(m_KeyBoardDevice->Acquire() != DI_OK) {
			return E_FAIL;
		}
		m_KeyBoardDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_DeviceObject, &elements, 0);
	}

	for(DWORD i = 0; i < elements; i++) {
		m_Key[m_DeviceObject[i].dwOfs] = (bool)((m_DeviceObject[i].dwData & 0x80) >> 7);
	}

	return S_OK;
}

//====================================
//Mouseの更新
//====================================
HRESULT fk_Input::UpdateMouse()
{
	memcpy(m_LastButton, m_Button, sizeof(bool) * MOUSE_BUTTON_MAX);
	GetCursorPos(&m_MouseWorldPos);
	ScreenToClient(m_hwnd,&m_MouseWorldPos);

	m_MouseLocalPos.x = 0;
	m_MouseLocalPos.y = 0;
	m_MouseWheel = 0;
	DWORD dwItems = DIMGR_BUFFER_SIZE;

	if(nullptr == m_MouseDevice) {
        return S_OK;
	}
	
	HRESULT hr = m_MouseDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_DeviceObject, &dwItems, 0);
	if(hr != S_OK) {
		if(m_MouseDevice->Acquire() != DI_OK) {
			return E_FAIL;
		}
		m_MouseDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),m_DeviceObject,&dwItems, 0);
	}

	for(DWORD i = 0; i < dwItems; i++) {  
		switch(m_DeviceObject[i].dwOfs) {
		case DIMOFS_X:
			m_MouseLocalPos.x += m_DeviceObject[i].dwData;
			break;
		case DIMOFS_Y:
			m_MouseLocalPos.y += m_DeviceObject[i].dwData;
			break;
		case DIMOFS_Z:
			m_MouseWheel += m_DeviceObject[i].dwData;
			break;
		default:
			m_Button[m_DeviceObject[i].dwOfs - DIMOFS_BUTTON0] = (m_DeviceObject[i].dwData & 0x80) >> 7;
			break;
		}
	}

	//m_MouseWorldPos.x += m_MouseLocalPos.x;
	//m_MouseWorldPos.y += m_MouseLocalPos.y;

    return S_OK;
}

int fk_Input::GetMouseWheel()
{
	return m_MouseWheel;
}

short fk_Input::AdjustParam(int id, short argRawData)
{
	short	retVal;

	if(argRawData < 0) {
		retVal = argRawData + m_AllowMin[id];
		if(retVal > 0) retVal = 0;
	} else {
		retVal = argRawData - m_AllowMin[id];
		if(retVal < 0) retVal = 0;
	}

	retVal = short(double(retVal)*(1000.0/double(m_AllowMax[id]-m_AllowMin[id])));

	if(retVal > 1000) retVal = 1000;
	if(retVal < -1000) retVal = -1000;

	return retVal;
}

void fk_Input::SetAxisParam(int id, int rawAxis, short param)
{
	short value = param * abs(axisSwap[id][rawAxis])/axisSwap[id][rawAxis];

	switch(abs(axisSwap[id][rawAxis])) {
	case AXIS1_X:
		m_JoyButton[id].x[0] = value;
		break;
	case AXIS1_Y:
		m_JoyButton[id].y[0] = value;
		break;
	case AXIS2_X:
		m_JoyButton[id].x[1] = value;
		break;
	case AXIS2_Y:
		m_JoyButton[id].y[1] = value;
		break;
	case AXIS3_X:
		m_JoyButton[id].x[2] = value;
		break;
	case AXIS3_Y:
		m_JoyButton[id].y[2] = value;
		break;
	default:
		break;
	}

	return;
}

//====================================
//Joyの更新
//====================================
HRESULT fk_Input::UpdateJoy()
{
	if(nullptr == m_JoyStciDevice[0]) {
        return S_OK;
	}

	HRESULT		hr;
	DIJOYSTATE	dijs;

	for(DWORD i = 0; i < m_JoyCount; i++) {
		hr = m_JoyStciDevice[i]->Poll();
		if(FAILED(hr)) {
			if(m_JoyStciDevice[i]->Acquire() != DI_OK) {
				memset(&m_JoyButton[i], 0, sizeof(m_JoyButton[i]));
				m_JoyButton[i].pov = -1;
				return E_FAIL;
			}
			hr = m_JoyStciDevice[i]->Poll();
			if(FAILED(hr)) {
				memset(&m_JoyButton[i], 0, sizeof(m_JoyButton[i]));
				m_JoyButton[i].pov = -1;
				return E_FAIL;
			}
		}

		DWORD dwItems = DIMGR_BUFFER_SIZE;
		m_JoyStciDevice[i]->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),m_DeviceObject,&dwItems, 0);
		m_JoyStciDevice[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);
	

		if(m_JoyButton == nullptr) continue;
		//-------------------------------------------------------------------------
		//以降ボタンの更新
		//-------------------------------------------------------------------------
        fk_InputInfo &joyButton = m_JoyButton[i];

		for(DWORD j = 0; j < dwItems; j++) {  
			switch(m_DeviceObject[j].dwOfs) {
			case DIJOFS_X:
				//joyButton.x[0] = AdjustParam(i, (short)m_DeviceObject[j].dwData);
				SetAxisParam(i, 0, AdjustParam(i, (short)m_DeviceObject[j].dwData));
				break;
			case DIJOFS_Y:
				//joyButton.y[0] = AdjustParam(i, (short)m_DeviceObject[j].dwData);
				SetAxisParam(i, 1, AdjustParam(i, (short)m_DeviceObject[j].dwData));
				break;
			case DIJOFS_Z:
				//joyButton.x[1] = AdjustParam(i, (short)m_DeviceObject[j].dwData);
				SetAxisParam(i, 2, AdjustParam(i, (short)m_DeviceObject[j].dwData));
				break;
			case DIJOFS_RZ:
				//joyButton.y[1] = AdjustParam(i, (short)m_DeviceObject[j].dwData);
				SetAxisParam(i, 5, AdjustParam(i, (short)m_DeviceObject[j].dwData));
				break;
			case DIJOFS_RX:
				//joyButton.x[2] = AdjustParam(i, (short)m_DeviceObject[j].dwData);
				SetAxisParam(i, 3, AdjustParam(i, (short)m_DeviceObject[j].dwData));
				break;
			case DIJOFS_RY:
				//joyButton.y[2] = AdjustParam(i, (short)m_DeviceObject[j].dwData);
				SetAxisParam(i, 4, AdjustParam(i, (short)m_DeviceObject[j].dwData));
				break;
			default:
				// joyButton.button[m_DeviceObject[j].dwOfs - DIJOFS_BUTTON0] = (m_DeviceObject[j].dwData & 0x80) >> 7;
				break;
			}
		}

		//-------------------------------------------------------------------------
		//十字ボタンを更新
		//-------------------------------------------------------------------------
		if(joyButton.y[0] <= -m_AllowY[i]) {
			joyButton.up = true;
		} else {
			joyButton.up = false;
		}
		if(joyButton.y[0] >= m_AllowY[i]) {
			joyButton.down = true;
		} else {
			joyButton.down = false;
		}
		if(joyButton.x[0] >= m_AllowX[i]) {
			joyButton.right = true;
		} else {
			joyButton.right = false;
		}
		if(joyButton.x[0] <= -m_AllowX[i]) {
			joyButton.left = true;
		} else {
			joyButton.left = false;
		}

		joyButton.pov = (int)dijs.rgdwPOV[0];

		for(int j = 0; j < BUTTON_NUM; j++) {
			if(dijs.rgbButtons[j] & 0x80) {
				joyButton.button[buttonSwap[i][j]] = true;
			} else {
				joyButton.button[buttonSwap[i][j]] = false;
			}
		}

		for(auto it = axisParams[i].begin(); it != axisParams[i].end(); it++) {
			switch(it->first) {
			case AXIS1_X:
				if(joyButton.x[0] >= it->second.border) {
					joyButton.button[it->second.pos] = true;
				} else {
					joyButton.button[it->second.pos] = false;
				}
				if(joyButton.x[0] <= -(it->second.border)) {
					joyButton.button[it->second.neg] = true;
				} else {
					joyButton.button[it->second.neg] = false;
				}
				break;
			case AXIS1_Y:
				if(joyButton.y[0] >= it->second.border) {
					joyButton.button[it->second.pos] = true;
				} else {
					joyButton.button[it->second.pos] = false;
				}
				if(joyButton.y[0] <= -(it->second.border)) {
					joyButton.button[it->second.neg] = true;
				} else {
					joyButton.button[it->second.neg] = false;
				}
				break;
			case AXIS2_X:
				if(joyButton.x[1] >= it->second.border) {
					joyButton.button[it->second.pos] = true;
				} else {
					joyButton.button[it->second.pos] = false;
				}
				if(joyButton.x[1] <= -(it->second.border)) {
					joyButton.button[it->second.neg] = true;
				} else {
					joyButton.button[it->second.neg] = false;
				}
				break;
			case AXIS2_Y:
				if(joyButton.y[1] >= it->second.border) {
					joyButton.button[it->second.pos] = true;
				} else {
					joyButton.button[it->second.pos] = false;
				}
				if(joyButton.y[1] <= -(it->second.border)) {
					joyButton.button[it->second.neg] = true;
				} else {
					joyButton.button[it->second.neg] = false;
				}
				break;
			case AXIS3_X:
				if(joyButton.x[2] >= it->second.border) {
					joyButton.button[it->second.pos] = true;
				} else {
					joyButton.button[it->second.pos] = false;
				}
				if(joyButton.x[2] <= -(it->second.border)) {
					joyButton.button[it->second.neg] = true;
				} else {
					joyButton.button[it->second.neg] = false;
				}
				break;
			case AXIS3_Y:
				if(joyButton.y[2] >= it->second.border) {
					joyButton.button[it->second.pos] = true;
				} else {
					joyButton.button[it->second.pos] = false;
				}
				if(joyButton.y[2] <= -(it->second.border)) {
					joyButton.button[it->second.neg] = true;
				} else {
					joyButton.button[it->second.neg] = false;
				}
				break;
			default:
				break;
			}
		}
	}

	return S_OK;
}

BOOL CALLBACK fk_Input::EnumSizesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpvRef)
{
	//------------------------------------------------------------------------------
	//デバイスの設定
	//------------------------------------------------------------------------------
	DIPROPRANGE diprg;
	ZeroMemory(&diprg,sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg); 
	diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
	diprg.diph.dwObj = lpddoi->dwType;
	diprg.diph.dwHow = DIPH_BYID;
	diprg.lMin = -1000;
	diprg.lMax = +1000;

	//------------------------------------------------------------------------------
	//デバイスの設定
	//------------------------------------------------------------------------------
	LPDIRECTINPUTDEVICE8 lpJoy = (LPDIRECTINPUTDEVICE8)lpvRef;
	HRESULT hr;
	hr = lpJoy->SetProperty(DIPROP_RANGE, &diprg.diph);
	if(FAILED(hr)) {
		return DIENUM_STOP;
	}
	return DIENUM_CONTINUE;
}

//------------------------------------------------------------------------------
//ジョイスティックを列挙するコールバック関数
//------------------------------------------------------------------------------
BOOL CALLBACK fk_Input::EnumJoysticksCallback(const DIDEVICEINSTANCE* lpddi, LPVOID lpContext )
{
	//--------------------------------------------------------------------------
	//デバイスの割り当て
	//--------------------------------------------------------------------------
	fk_Input* joyStick = (fk_Input*)lpContext;	
	joyStick->m_DevCaps.dwSize = sizeof(DIDEVCAPS);
	joyStick->m_Input->CreateDevice(lpddi->guidInstance, &joyStick->m_JoyStciDevice[joyStick->m_JoyCount],nullptr);
	joyStick->m_JoyStciDevice[joyStick->getJoyCount()]->GetCapabilities(&joyStick->m_DevCaps);
	//--------------------------------------------------------------------------
	//ジョイスティック数が最大になってたら強制的にストップさせる
	//---------------------------------------------------------------------------
	if(++(joyStick->m_JoyCount) == joyStick->m_JoyMaxCount) {
		return DIENUM_STOP;
	}
	//--------------------------------------------------------------------------
	//最大になってなかったので列挙がまだ続く
	//--------------------------------------------------------------------------
	return DIENUM_CONTINUE;
}

//==================================
//Mouseボタンを取得
//==================================
bool fk_Input::GetMouseButton(DWORD key)
{
	if(key >= MOUSE_BUTTON_MAX) {
		return false;
	}
	return m_Button[key];
}

bool fk_Input::GetLastMouseButton(DWORD key)
{
	if(key >= MOUSE_BUTTON_MAX) {
		return false;
	}
	return m_LastButton[key];
}

//==================================
//JoyStickを取得
//==================================
fk_InputInfo* fk_Input::getJoyStick(DWORD dwNum)
{
	if(dwNum >= m_JoyCount) {
		return nullptr;
	}
	return &m_JoyButton[dwNum];
}

//==================================
//JoyStickの数を取得
//==================================
DWORD fk_Input::getJoyCount()
{
	return m_JoyCount;
}

//==================================
//Mouseのローカル座標を取得
//==================================
POINT& fk_Input::GetMouseLocalPos()
{
	return m_MouseLocalPos;
}

//==================================
//Mouseの絶対座標を取得
//==================================
POINT& fk_Input::GetMouseWorldPos()
{
	return m_MouseWorldPos;
}


void fk_Input::setButtonSwap(int joyIndex, int id, int raw)
{
	if(joyIndex >= INPUT_DEVICE_NUM) {
		return;
	}

	buttonSwap[joyIndex][raw] = id;

	return;
}

void fk_Input::setAxisSwap(int joyIndex, fk_AxisDirection id, fk_RawAxis raw)
{
	if(joyIndex >= INPUT_DEVICE_NUM) {
		return;
	}

	if(raw%2 == 1) {
		axisSwap[joyIndex][raw/2] = -id;
	} else {
		axisSwap[joyIndex][raw/2] =  id;
	}

	return;
}

void fk_Input::setAxisToButton(int joyIndex, fk_AxisDirection axisID, int posBtn, int negBtn, int border)
{
	AxisParam	param;

	param.pos = posBtn;
	param.neg = negBtn;
	param.border = border;

	axisParams[joyIndex][axisID] = param;

	return;
}

void fk_Input::clearAxisToButton(int joyIndex)
{
	axisParams[joyIndex].clear();

	return;
}

void fk_Input::setKeyAssign(int id, DWORD keycode)
{
	if(id >= 0 && id < BUTTON_NUM) {
		keyMap[id] = keycode;
	}

	return;
}

void fk_Input::setAxisAssign(int axis_id, DWORD up, DWORD dn, DWORD lt, DWORD rt)
{
	if(axis_id == 0 || axis_id == 1 || axis_id == 2) {
		axisMap[axis_id*4+0] = up;
		axisMap[axis_id*4+1] = dn;
		axisMap[axis_id*4+2] = lt;
		axisMap[axis_id*4+3] = rt;
	}

	return;
}

void fk_Input::setPOVAssign(DWORD ul, DWORD u, DWORD ur, DWORD l, DWORD r, DWORD dl, DWORD d, DWORD dr)
{
	povMap[0] = ul;
	povMap[1] = u;
	povMap[2] = ur;
	povMap[3] = l;
	povMap[4] = r;
	povMap[5] = dl;
	povMap[6] = d;
	povMap[7] = dr;

	return;
}

fk_InputInfo fk_Input::getInputStatus(int index)
{
	fk_InputInfo	retVal;

	memset(&retVal, 0, sizeof(fk_InputInfo));

	fk_InputInfo *joy_in = getJoyStick(index);

	if(joy_in != nullptr) {
		retVal = *joy_in;
	} else if(index == 0) {
		// 軸1
		retVal.x[0] = 0;	retVal.y[0] = 0;
		retVal.up    = GetKey(axisMap[0]);	retVal.y[0] += retVal.up    ? -1000 : 0;
		retVal.down	 = GetKey(axisMap[1]);	retVal.y[0] += retVal.down  ?  1000 : 0;
		retVal.left  = GetKey(axisMap[2]);	retVal.x[0] += retVal.left  ? -1000 : 0;
		retVal.right = GetKey(axisMap[3]);	retVal.x[0] += retVal.right ?  1000 : 0;

		// 軸2
		retVal.x[1] = 0;	retVal.y[1] = 0;
		retVal.y[1] += GetKey(axisMap[4]) ? -1000 : 0;
		retVal.y[1] += GetKey(axisMap[5]) ?  1000 : 0;
		retVal.x[1] += GetKey(axisMap[6]) ? -1000 : 0;
		retVal.x[1] += GetKey(axisMap[7]) ?  1000 : 0;

		// 軸3
		retVal.x[2] = 0;	retVal.y[2] = 0;
		retVal.y[2] += GetKey(axisMap[8])  ? -1000 : 0;
		retVal.y[2] += GetKey(axisMap[9])  ?  1000 : 0;
		retVal.x[2] += GetKey(axisMap[10]) ? -1000 : 0;
		retVal.x[2] += GetKey(axisMap[11]) ?  1000 : 0;

		// POV
		retVal.pov = -1;
		if(GetKey(povMap[0])) retVal.pov = 31500;
		if(GetKey(povMap[1])) retVal.pov = 0;
		if(GetKey(povMap[2])) retVal.pov = 4500;
		if(GetKey(povMap[3])) retVal.pov = 27000;
		if(GetKey(povMap[4])) retVal.pov = 9000;
		if(GetKey(povMap[5])) retVal.pov = 22500;
		if(GetKey(povMap[6])) retVal.pov = 18000;
		if(GetKey(povMap[7])) retVal.pov = 13500;

		// ボタン
		for(int i = 0; i < BUTTON_NUM; i++) {
			retVal.button[i] = GetKey(keyMap[i]);
		}
	}

	return retVal;
}

#else // WIN32

using namespace FK;

fk_Input::fk_Input(void) {}
fk_Input::~fk_Input(void) {}

POINT&	fk_Input::GetMouseLocalPos(void)
{
	static POINT p;
	return p;
}

POINT&	fk_Input::GetMouseWorldPos(void)
{
	static POINT p;
	return p;
}

bool	fk_Input::GetMouseButton(DWORD)
{
	return false;
}

bool	fk_Input::GetLastMouseButton(DWORD)
{
	return false;
}

int		fk_Input::GetMouseWheel(void)
{
	return 0;
}

bool	fk_Input::GetKey(const DWORD)
{
	return false;
}

HRESULT fk_Input::init(HINSTANCE, HWND)
{
	return 0;
}

HRESULT fk_Input::uninit(void)
{
	return 0;
}

HRESULT fk_Input::update(void)
{
	return 0;
}

DWORD fk_Input::getJoyCount(void)
{
	return 0;
}

fk_InputInfo*	fk_Input::getJoyStick(DWORD)
{
	return nullptr;
}

void			fk_Input::setBorder(int, int, int) {}
void			fk_Input::setBorder(int, int) {}
void			fk_Input::setMinMax(int, int, int) {}
void			fk_Input::setMinMax(int, int) {}
void			fk_Input::setButtonSwap(int, int, int) {}
void			fk_Input::setAxisSwap(int, fk_AxisDirection, fk_RawAxis) {}
void			fk_Input::setAxisToButton(int, fk_AxisDirection, int, int, int) {}
void			fk_Input::clearAxisToButton(int) {}
void			fk_Input::setKeyAssign(int, DWORD) {}
void			fk_Input::setAxisAssign(int, DWORD, DWORD, DWORD, DWORD) {}
void			fk_Input::setPOVAssign(DWORD, DWORD, DWORD, DWORD,
									   DWORD, DWORD, DWORD, DWORD) {}

fk_InputInfo	fk_Input::getInputStatus(int)
{
	return fk_InputInfo();
}

#endif
