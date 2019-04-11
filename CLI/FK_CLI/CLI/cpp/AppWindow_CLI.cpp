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
#include "AppWindow_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;
	using namespace FK;

	::FK::fk_AppWindow * fk_AppWindow::GetP(void)
	{
		return pWin;
	}
	
	::FK::fk_SpecialKey fk_AppWindow::GetSK(fk_SpecialKey argK)
	{
		switch(argK) {
		  case fk_SpecialKey::SHIFT_R:
			return FK_SHIFT_R;
				
		  case fk_SpecialKey::SHIFT_L:
			return FK_SHIFT_L;
				
		  case fk_SpecialKey::CTRL_R:
			return FK_CTRL_R;
				
		  case fk_SpecialKey::CTRL_L:
			return FK_CTRL_L;
				
		  case fk_SpecialKey::ALT_R:
			return FK_ALT_R;
				
		  case fk_SpecialKey::ALT_L:
			return FK_ALT_L;
				
		  case fk_SpecialKey::ENTER:
			return FK_ENTER;
				
		  case fk_SpecialKey::BACKSPACE:
			return FK_BACKSPACE;
				
		  case fk_SpecialKey::DELETEKEY:
			return FK_DELETE;
				
		  case fk_SpecialKey::CAPS_LOCK:
			return FK_CAPS_LOCK;
				
		  case fk_SpecialKey::TAB:
			return FK_TAB;
				
		  case fk_SpecialKey::PAGE_UP:
			return FK_PAGE_UP;
				
		  case fk_SpecialKey::PAGE_DOWN:
			return FK_PAGE_DOWN;
				
		  case fk_SpecialKey::HOME:
			return FK_HOME;
				
		  case fk_SpecialKey::END:
			return FK_END;
				
		  case fk_SpecialKey::INSERT:
			return FK_INSERT;
				
		  case fk_SpecialKey::LEFT:
			return FK_LEFT;
				
		  case fk_SpecialKey::RIGHT:
			return FK_RIGHT;
				
		  case fk_SpecialKey::UP:
			return FK_UP;
				
		  case fk_SpecialKey::DOWN:
			return FK_DOWN;
				
		  case fk_SpecialKey::F1:
			return FK_F1;
				
		  case fk_SpecialKey::F2:
			return FK_F2;
				
		  case fk_SpecialKey::F3:
			return FK_F3;
				
		  case fk_SpecialKey::F4:
			return FK_F4;
				
		  case fk_SpecialKey::F5:
			return FK_F5;
				
		  case fk_SpecialKey::F6:
			return FK_F6;
				
		  case fk_SpecialKey::F7:
			return FK_F7;
				
		  case fk_SpecialKey::F8:
			return FK_F8;
				
		  case fk_SpecialKey::F9:
			return FK_F9;
				
		  case fk_SpecialKey::F10:
			return FK_F10;
				
		  case fk_SpecialKey::F11:
			return FK_F11;
				
		  case fk_SpecialKey::F12:
			return FK_F12;
				
		  default:
			break;
		}
		return FK_ENTER;
	}

	::FK::fk_SwitchStatus fk_AppWindow::GetSS(fk_SwitchStatus argSS)
	{
		switch(argSS) {
		  case fk_SwitchStatus::RELEASE:
			return FK_SW_RELEASE;
				
		  case fk_SwitchStatus::UP:
			return FK_SW_UP;
				
		  case fk_SwitchStatus::DOWN:
			return FK_SW_DOWN;
				
		  case fk_SwitchStatus::PRESS:
			return FK_SW_PRESS;
				
		  default:
			break;
		}
		return FK_SW_RELEASE;
	}

	fk_AppWindow::fk_AppWindow()
	{
		preInit = gcnew ShaderCallback(this, &fk_AppWindow::OnPreInit);
		postInit = gcnew ShaderCallback(this, &fk_AppWindow::OnPostInit);
		preDraw = gcnew ShaderCallback(this, &fk_AppWindow::OnPreDraw);
		postDraw = gcnew ShaderCallback(this, &fk_AppWindow::OnPostDraw);
		preDrawLeft = gcnew ShaderCallback(this, &fk_AppWindow::OnPreDrawLeft);
		postDrawLeft = gcnew ShaderCallback(this, &fk_AppWindow::OnPostDrawLeft);
		preDrawRight = gcnew ShaderCallback(this, &fk_AppWindow::OnPreDrawRight);
		postDrawRight = gcnew ShaderCallback(this, &fk_AppWindow::OnPostDrawRight);
#ifdef _WIN64
		uint64_t callbacks[8];
		callbacks[0] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(preInit).ToInt64();
		callbacks[1] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(postInit).ToInt64();
		callbacks[2] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(preDraw).ToInt64();
		callbacks[3] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(postDraw).ToInt64();
		callbacks[4] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(preDrawLeft).ToInt64();
		callbacks[5] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(postDrawLeft).ToInt64();
		callbacks[6] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(preDrawRight).ToInt64();
		callbacks[7] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(postDrawRight).ToInt64();
#else
		uint32_t callbacks[8];
		callbacks[0] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(preInit).ToInt32();
		callbacks[1] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(postInit).ToInt32();
		callbacks[2] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(preDraw).ToInt32();
		callbacks[3] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(postDraw).ToInt32();
		callbacks[4] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(preDrawLeft).ToInt32();
		callbacks[5] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(postDrawLeft).ToInt32();
		callbacks[6] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(preDrawRight).ToInt32();
		callbacks[7] = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(postDrawRight).ToInt32();
#endif
		pWin = new ::FK::fk_AppWindow(callbacks);
		scene = gcnew fk_Scene(false);
		scene->pBase = GetP()->getScene();
		scene->dFlg = false;
		scene->CameraUpdate();
	}

	fk_AppWindow::~fk_AppWindow()
	{
		preInit = nullptr;
		postInit = nullptr;
		preDraw = nullptr;
		postDraw = nullptr;
		preDrawLeft = nullptr;
		postDrawLeft = nullptr;
		preDrawRight = nullptr;
		postDrawRight = nullptr;
		delete scene;
		scene = nullptr;
		this->!fk_AppWindow();
	}

	fk_AppWindow::!fk_AppWindow()
	{
		delete pWin;
		pWin = nullptr;
	}

	void fk_AppWindow::WindowName::set(String^ argName)
	{
		GetP()->setWindowName(marshal_as<string>(argName));
	}

	void fk_AppWindow::Size::set(fk_Dimension^ argD)
	{
		if(!argD) return;
		GetP()->setSize(argD->pDim->w, argD->pDim->h);
	}

	void fk_AppWindow::InnerSize::set(fk_Rect^ argR)
	{
		GetP()->setInnerSize(argR->pRect->x, argR->pRect->y,
							 argR->pRect->w, argR->pRect->h);
	}

	void fk_AppWindow::BGColor::set(fk_Color^ argC)
	{
		GetP()->setBGColor(*argC->GetP());
	}

	void fk_AppWindow::FPS::set(int argFPS)
	{
		GetP()->setFPS(argFPS);
	}

	void fk_AppWindow::AxisWidth::set(double argWidth)
	{
		GetP()->setGuideAxisWidth(argWidth);
	}

	void fk_AppWindow::GridWidth::set(double argWidth)
	{
		GetP()->setGuideGridWidth(argWidth);
	}

	void fk_AppWindow::GuideScale::set(double argScale)
	{
		GetP()->setGuideScale(argScale);
	}

	void fk_AppWindow::GuideNum::set(int argNum)
	{
		GetP()->setGuideNum(argNum);
	}

	void fk_AppWindow::CameraPos::set(fk_Vector^ argV)
	{
		GetP()->setCameraPos(argV->x_, argV->y_, argV->z_);
	}

	fk_Vector^ fk_AppWindow::CameraPos::get(void)
	{
		fk_Vector^ V = gcnew fk_Vector(GetP()->getCameraModel()->getPosition());
		return V;
	}

	void fk_AppWindow::CameraFocus::set(fk_Vector^ argV)
	{
		GetP()->setCameraFocus(argV->x_, argV->y_, argV->z_);
	}

	void fk_AppWindow::CameraModel::set(fk_Model^ argM)
	{
		GetP()->setCameraModel(argM->GetP());
	}
			
	fk_Model^ fk_AppWindow::CameraModel::get(void)
	{
		return gcnew fk_Model(GetP()->getCameraModel());
	}

	void fk_AppWindow::Scene::set(fk_Scene^ argScene)
	{
		if(!argScene) return;
		GetP()->setScene(argScene->GetP(), false);
		scene = argScene;
	}
			
	fk_Scene^ fk_AppWindow::Scene::get(void)
	{
		return scene;
	}

	void fk_AppWindow::TrackBallMode::set(bool argMode)
	{
		GetP()->setTrackBallMode(argMode);
	}

	fk_Vector^ fk_AppWindow::MousePosition::get(void)
	{
		return gcnew fk_Vector(GetP()->getMousePosition());
	}
				
	void fk_AppWindow::Open(void)
	{
		GetP()->open();
	}
		
	void fk_AppWindow::Close(void)
	{
		GetP()->close();
	}
		
	bool fk_AppWindow::Update(bool argForceFlg)
	{
		return GetP()->update(argForceFlg);
	}

	bool fk_AppWindow::Update(void)
	{
		return GetP()->update(false);
	}
		
	void fk_AppWindow::ShowGuide(void)
	{
		GetP()->showGuide(FK_AXIS_X | FK_AXIS_Y | FK_AXIS_Z | FK_GRID_XZ);
	}
		
	void fk_AppWindow::ShowGuide(fk_GuideMode argMode)
	{
		GetP()->showGuide(int(argMode));
	}

	void fk_AppWindow::HideGuide(void)
	{
		GetP()->hideGuide();
	}

	void fk_AppWindow::SetCameraDefault(void)
	{
		GetP()->setCameraDefault();
	}

	void fk_AppWindow::SetScene(fk_Scene^ argScene, bool argCL)
	{
		GetP()->setScene(argScene->GetP(), argCL);
	}
		
	void fk_AppWindow::SetSceneDefault(void)
	{
		GetP()->setSceneDefault();
	}
			
	void fk_AppWindow::Entry(fk_Model^ argModel)
	{
		GetP()->entry(argModel->GetP());
	}

	void fk_AppWindow::Entry(fk_Model^ argM, fk_GuideObject^ argGuide)
	{
		GetP()->entry(argM->GetP(), argGuide->GetP());
	}

	void fk_AppWindow::Entry(fk_SpriteModel^ argM)
	{
		GetP()->entry(argM->GetP());
	}

	void fk_AppWindow::Entry(fk_Performer^ argP)
	{
		GetP()->entry(argP->GetP());
	}

	void fk_AppWindow::Remove(fk_Model^ argM)
	{
		GetP()->remove(argM->GetP());
	}

	void fk_AppWindow::Remove(fk_Model^ argM, fk_GuideObject^ argGuide)
	{
		GetP()->remove(argM->GetP(), argGuide->GetP());
	}

	void fk_AppWindow::Remove(fk_SpriteModel^ argM)
	{
		GetP()->remove(argM->GetP());
	}

	void fk_AppWindow::Remove(fk_Performer^ argP)
	{
		GetP()->remove(argP->GetP());
	}

	void fk_AppWindow::ClearModel(bool argCL)
	{
		GetP()->clearModel(argCL);
	}

	void fk_AppWindow::ClearModel(void)
	{
		GetP()->clearModel(false);
	}

	bool fk_AppWindow::GetKeyStatus(wchar_t argK, fk_SwitchStatus argStatus)
	{
		wchar_t tmpWBuf[2];
		char tmpBuf[2];
		size_t ret;

		tmpWBuf[0] = argK;
		tmpWBuf[1] = 0;
		wcstombs_s(&ret, tmpBuf, 2, tmpWBuf, 1);
		return GetP()->getKeyStatus(tmpBuf[0], GetSS(argStatus));
	}

	bool fk_AppWindow::GetKeyStatus(wchar_t argK, fk_SwitchStatus argStatus, bool argInFlg)
	{
		wchar_t tmpWBuf[2];
		char tmpBuf[2];
		size_t ret;

		tmpWBuf[0] = argK;
		tmpWBuf[1] = 0;
		wcstombs_s(&ret, tmpBuf, 2, tmpWBuf, 1);
		return GetP()->getKeyStatus(tmpBuf[0], GetSS(argStatus), argInFlg);
	}

	bool fk_AppWindow::GetSpecialKeyStatus(fk_SpecialKey keyCode,
										   fk_SwitchStatus argStatus, bool argInFlg)
	{
		return GetP()->getSpecialKeyStatus(GetSK(keyCode), GetSS(argStatus), argInFlg);
	}
		
	bool fk_AppWindow::GetSpecialKeyStatus(fk_SpecialKey keyCode, fk_SwitchStatus argStatus)
	{
		return GetP()->getSpecialKeyStatus(GetSK(keyCode), GetSS(argStatus), false);
	}
			
	bool fk_AppWindow::GetMouseStatus(fk_MouseButton argB, fk_SwitchStatus argSS, bool argInFlg)
	{
		::FK::fk_MouseButton	b;
		switch(argB) {
		  case fk_MouseButton::MOUSE1:
			b = FK_MOUSE1;
			break;
				
		  case fk_MouseButton::MOUSE2:
			b = FK_MOUSE2;
			break;
				
		  case fk_MouseButton::MOUSE3:
			b = FK_MOUSE3;
			break;

		  default:
			return false;
		}

		return GetP()->getMouseStatus(b, GetSS(argSS), argInFlg);
	}
				
	void fk_AppWindow::SetCursorState(bool argVisible, bool argCenter)
	{
		GetP()->setCursorState(argVisible, argCenter);
	}

	void fk_AppWindow::ProcMouseView(fk_Model^ argCamera, double argX, double argY, bool argLockSW)
	{
		GetP()->procMouseView(argCamera->GetP(), argX, argY, argLockSW);
	}

	
	bool fk_AppWindow::GetProjectPosition(double argX, double argY,
										  fk_Plane^ argPlane, fk_Vector^ argPos)
	{
		if(!argPlane || !argPos) return false;
		::FK::fk_Vector	retPos;
		bool		ret;

		ret = GetP()->getProjectPosition(argX, argY, argPlane->pPlane, &retPos);
		argPos->Set(retPos.x, retPos.y, retPos.z);
		return ret;
	}

	bool fk_AppWindow::GetProjectPosition(double argX, double argY,
										  double argDist, fk_Vector^ argPos)
	{
		if(!argPos) return false;
		::FK::fk_Vector	retPos;
		bool		ret;

		ret = GetP()->getProjectPosition(argX, argY, argDist, &retPos);
		argPos->Set(retPos.x, retPos.y, retPos.z);
		return ret;
	}

	bool fk_AppWindow::GetWindowPosition(fk_Vector^ argPos_3D, fk_Vector^ argPos_2D)
	{
		if(!argPos_3D || !argPos_2D) return false;
		::FK::fk_Vector	retPos;
		::FK::fk_Vector pos3D(argPos_3D->x_, argPos_3D->y_, argPos_3D->z_);
		bool		ret;

		ret = GetP()->getWindowPosition(pos3D, &retPos);
		argPos_2D->Set(retPos.x, retPos.y, retPos.z);
		return ret;
	}
}


