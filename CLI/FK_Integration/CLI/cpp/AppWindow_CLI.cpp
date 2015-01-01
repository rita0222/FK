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

	void fk_AppWindow::setWindowName(String^ argName)
	{
		GetP()->setWindowName(marshal_as<string>(argName));
	}

	void fk_AppWindow::setSize(int argW, int argH)
	{
		GetP()->setSize(argW, argH);
	}

	void fk_AppWindow::setInnerSize(int argX, int argY, int argW, int argH)
	{
		GetP()->setInnerSize(argX, argY, argW, argH);
	}

	void fk_AppWindow::setBGColor(double argR, double argG, double argB)
	{
		GetP()->setBGColor(argR, argG, argB);
	}

	void fk_AppWindow::setBGColor(fk_Color^ argC)
	{
		GetP()->setBGColor(*argC->GetP());
	}

	void fk_AppWindow::open(void)
	{
		GetP()->open();
	}
		
	void fk_AppWindow::close(void)
	{
		GetP()->close();
	}
		
	bool fk_AppWindow::update(bool argForceFlg)
	{
		return GetP()->update(argForceFlg);
	}

	bool fk_AppWindow::update(void)
	{
		return GetP()->update(false);
	}
		
	void fk_AppWindow::setFPS(int argFPS)
	{
		GetP()->setFPS(argFPS);
	}

	void fk_AppWindow::showGuide(void)
	{
		GetP()->showGuide(FK_AXIS_X | FK_AXIS_Y | FK_AXIS_Z | FK_GRID_XZ);
	}
		
	void fk_AppWindow::showGuide(fk_GuideMode argMode)
	{
		GetP()->showGuide(int(argMode));
	}

	void fk_AppWindow::hideGuide(void)
	{
		GetP()->hideGuide();
	}

	void fk_AppWindow::setGuideAxisWidth(double argWidth)
	{
		GetP()->setGuideAxisWidth(argWidth);
	}

	void fk_AppWindow::setGuideGridWidth(double argWidth)
	{
		GetP()->setGuideGridWidth(argWidth);
	}

	void fk_AppWindow::setGuideScale(double argScale)
	{
		GetP()->setGuideScale(argScale);
	}

	void fk_AppWindow::setGuideNum(int argNum)
	{
		GetP()->setGuideNum(argNum);
	}

	void fk_AppWindow::setCameraPos(double argX, double argY, double argZ)
	{
		GetP()->setCameraPos(argX, argY, argZ);
	}

	void fk_AppWindow::setCameraPos(fk_Vector^ argV)
	{
		GetP()->setCameraPos(*argV->pVec);
	}

	void fk_AppWindow::setCameraFocus(double argX, double argY, double argZ)
	{
		GetP()->setCameraFocus(argX, argY, argZ);
	}

	void fk_AppWindow::setCameraFocus(fk_Vector^ argV)
	{
		GetP()->setCameraFocus(*argV->pVec);
	}

	void fk_AppWindow::setCameraModel(fk_Model^ argM)
	{
		GetP()->setCameraModel(argM->GetP());
	}
			
	fk_Model^ fk_AppWindow::getCameraModel(void)
	{
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = (::fk_Model *)(GetP()->getCameraModel());
		M->dFlg = false;
		return M;
	}

	void fk_AppWindow::setCameraDefault(void)
	{
		GetP()->setCameraDefault();
	}

	void fk_AppWindow::setScene(fk_Scene^ argScene, bool argCL)
	{
		GetP()->setScene(argScene->GetP(), argCL);
	}
		
	void fk_AppWindow::setScene(fk_Scene^ argScene)
	{
		GetP()->setScene(argScene->GetP(), false);
	}
			
	fk_Scene^ fk_AppWindow::getScene(void)
	{
		fk_Scene^ S = gcnew fk_Scene(false);
		S->pBase = GetP()->getScene();
		S->dFlg = false;

		return S;
	}
		
	void fk_AppWindow::setSceneDefault(void)
	{
		GetP()->setSceneDefault();
	}
			
	void fk_AppWindow::entry(fk_Model^ argModel)
	{
		GetP()->entry(argModel->GetP());
	}

	void fk_AppWindow::entry(fk_Model^ argM, fk_GuideObject^ argGuide)
	{
		GetP()->entry(argM->GetP(), argGuide->GetP());
	}

	void fk_AppWindow::entry(fk_SpriteModel^ argM)
	{
		GetP()->entry(argM->GetP());
	}

	void fk_AppWindow::remove(fk_Model^ argM)
	{
		GetP()->remove(argM->GetP());
	}

	void fk_AppWindow::remove(fk_Model^ argM, fk_GuideObject^ argGuide)
	{
		GetP()->remove(argM->GetP(), argGuide->GetP());
	}

	void fk_AppWindow::remove(fk_SpriteModel^ argM)
	{
		GetP()->remove(argM->GetP());
	}

	void fk_AppWindow::clearModel(bool argCL)
	{
		GetP()->clearModel(argCL);
	}

	void fk_AppWindow::clearModel(void)
	{
		GetP()->clearModel(false);
	}

	bool fk_AppWindow::getKeyStatus(char argK, fk_SwitchStatus argStatus)
	{
		return GetP()->getKeyStatus(argK, GetSS(argStatus), false);
	}
	bool fk_AppWindow::getKeyStatus(char argK, fk_SwitchStatus argStatus, bool argInFlg)
	{
		return GetP()->getKeyStatus(argK, GetSS(argStatus), argInFlg);
	}

	bool fk_AppWindow::getSpecialKeyStatus(fk_SpecialKey keyCode,
										   fk_SwitchStatus argStatus, bool argInFlg)
	{
		return GetP()->getSpecialKeyStatus(GetSK(keyCode), GetSS(argStatus), argInFlg);
	}
		
	bool fk_AppWindow::getSpecialKeyStatus(fk_SpecialKey keyCode, fk_SwitchStatus argStatus)
	{
		return GetP()->getSpecialKeyStatus(GetSK(keyCode), GetSS(argStatus), false);
	}
			
	bool fk_AppWindow::getMouseStatus(fk_MouseButton argB, fk_SwitchStatus argSS, bool argInFlg)
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
				
	fk_Vector^ fk_AppWindow::getMousePosition(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getMousePosition();
		return V;
	}
				
	void fk_AppWindow::setCursorState(bool argVisible, bool argCenter)
	{
		GetP()->setCursorState(argVisible, argCenter);
	}

	void fk_AppWindow::setTrackBallMode(bool argMode)
	{
		GetP()->setTrackBallMode(argMode);
	}

	bool fk_AppWindow::isModelPicked(fk_Model^ argM, int argP, int argX, int argY)
	{
		return GetP()->isModelPicked(argM->GetP(), argP, argX, argY);
	}

	bool fk_AppWindow::isModelPicked(fk_Model^ argM, int argP)
	{
		return GetP()->isModelPicked(argM->GetP(), argP);
	}

	bool fk_AppWindow::isModelPicked(fk_Model^ argM)
	{
		return GetP()->isModelPicked(argM->GetP());
	}

	void fk_AppWindow::procMouseView(fk_Model^ argCamera, double argX, double argY, bool argLockSW)
	{
		GetP()->procMouseView(argCamera->GetP(), argX, argY, argLockSW);
	}
}

