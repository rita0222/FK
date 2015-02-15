#include "AppWindow_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;
	
	::fk_SpecialKey fk_AppWindow::GetSK(fk_SpecialKey argK)
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

	::fk_SwitchStatus fk_AppWindow::GetSS(fk_SwitchStatus argSS)
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

	void fk_AppWindow::SetWindowName(String^ argName)
	{
		GetP()->setWindowName(marshal_as<string>(argName));
	}

	void fk_AppWindow::SetSize(int argW, int argH)
	{
		GetP()->setSize(argW, argH);
	}

	void fk_AppWindow::SetInnerSize(int argX, int argY, int argW, int argH)
	{
		GetP()->setInnerSize(argX, argY, argW, argH);
	}

	void fk_AppWindow::SetBGColor(double argR, double argG, double argB)
	{
		GetP()->setBGColor(argR, argG, argB);
	}

	void fk_AppWindow::SetBGColor(fk_Color^ argC)
	{
		GetP()->setBGColor(*argC->GetP());
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
		
	void fk_AppWindow::SetFPS(int argFPS)
	{
		GetP()->setFPS(argFPS);
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

	void fk_AppWindow::SetGuideAxisWidth(double argWidth)
	{
		GetP()->setGuideAxisWidth(argWidth);
	}

	void fk_AppWindow::SetGuideGridWidth(double argWidth)
	{
		GetP()->setGuideGridWidth(argWidth);
	}

	void fk_AppWindow::SetGuideScale(double argScale)
	{
		GetP()->setGuideScale(argScale);
	}

	void fk_AppWindow::SetGuideNum(int argNum)
	{
		GetP()->setGuideNum(argNum);
	}

	void fk_AppWindow::SetCameraPos(double argX, double argY, double argZ)
	{
		GetP()->setCameraPos(argX, argY, argZ);
	}

	void fk_AppWindow::SetCameraPos(fk_Vector^ argV)
	{
		GetP()->setCameraPos(*argV->pVec);
	}

	void fk_AppWindow::SetCameraFocus(double argX, double argY, double argZ)
	{
		GetP()->setCameraFocus(argX, argY, argZ);
	}

	void fk_AppWindow::SetCameraFocus(fk_Vector^ argV)
	{
		GetP()->setCameraFocus(*argV->pVec);
	}

	void fk_AppWindow::SetCameraModel(fk_Model^ argM)
	{
		GetP()->setCameraModel(argM->GetP());
	}
			
	fk_Model^ fk_AppWindow::GetCameraModel(void)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = (::fk_Model *)(GetP()->getCameraModel());
		M->dFlg = false;
		return M;
	}

	void fk_AppWindow::SetCameraDefault(void)
	{
		GetP()->setCameraDefault();
	}

	void fk_AppWindow::SetScene(fk_Scene^ argScene, bool argCL)
	{
		GetP()->setScene(argScene->GetP(), argCL);
	}
		
	void fk_AppWindow::SetScene(fk_Scene^ argScene)
	{
		if(!argScene) return;
		GetP()->setScene(argScene->GetP(), false);
		scene = argScene;
	}
			
	fk_Scene^ fk_AppWindow::GetScene(void)
	{
		return scene;
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
		::fk_MouseButton	b;
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
				
	fk_Vector^ fk_AppWindow::GetMousePosition(void)
	{
		return gcnew fk_Vector(GetP()->getMousePosition());
	}
				
	void fk_AppWindow::SetCursorState(bool argVisible, bool argCenter)
	{
		GetP()->setCursorState(argVisible, argCenter);
	}

	void fk_AppWindow::SetTrackBallMode(bool argMode)
	{
		GetP()->setTrackBallMode(argMode);
	}

	bool fk_AppWindow::IsModelPicked(fk_Model^ argM, int argP, int argX, int argY)
	{
		return GetP()->isModelPicked(argM->GetP(), argP, argX, argY);
	}

	bool fk_AppWindow::IsModelPicked(fk_Model^ argM, int argP)
	{
		return GetP()->isModelPicked(argM->GetP(), argP);
	}

	bool fk_AppWindow::IsModelPicked(fk_Model^ argM)
	{
		return GetP()->isModelPicked(argM->GetP());
	}

	void fk_AppWindow::ProcMouseView(fk_Model^ argCamera, double argX, double argY, bool argLockSW)
	{
		GetP()->procMouseView(argCamera->GetP(), argX, argY, argLockSW);
	}
}

