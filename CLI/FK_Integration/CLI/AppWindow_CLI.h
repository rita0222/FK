// Scene_CLI.h

#pragma once

#include <FK/SimpleWindow.h>
#include "GuideObject_CLI.h"

using namespace std;
using namespace System;
using namespace msclr::interop;

namespace FK_CLI
{
	public enum class fk_SpecialKey {
		SHIFT_R,
		SHIFT_L,
		CTRL_R,
		CTRL_L,
		ALT_R,
		ALT_L,
		ENTER,
		BACKSPACE,
		DELETEKEY,
		CAPS_LOCK,
		TAB,
		PAGE_UP,
		PAGE_DOWN,
		HOME,
		END,
		INSERT,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12
	};

	public enum class fk_MouseButton {
		MOUSE1,
		MOUSE2,
		MOUSE3
	};

	public enum class fk_SwitchStatus {
		RELEASE,
		UP,
		DOWN,
		PRESS
	};

	public ref class fk_AppWindow : fk_BaseObject
	{
	internal:
		::fk_AppWindow * GetP(void)
		{
			return reinterpret_cast<::fk_AppWindow *>(this->pBase);
		}

		::fk_SpecialKey GetSK(fk_SpecialKey argK)
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

		::fk_SwitchStatus GetSS(fk_SwitchStatus argSS)
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
		
	public:
		fk_AppWindow::fk_AppWindow(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				::fk_AppWindow *p = new ::fk_AppWindow();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_AppWindow::fk_AppWindow() : fk_BaseObject(false)
		{
			::fk_AppWindow *p = new ::fk_AppWindow();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_AppWindow::~fk_AppWindow()
		{
			this->!fk_AppWindow();
		}

		fk_AppWindow::!fk_AppWindow()
		{
			if(dFlg == true) delete this->pBase;
			this->pBase = NULL;
		}

		void setWindowName(String^ argName)
		{
			GetP()->setWindowName(marshal_as<string>(argName));
		}

		void setSize(int argW, int argH)
		{
			GetP()->setSize(argW, argH);
		}

		void setInnerSize(int argX, int argY, int argW, int argH)
		{
			GetP()->setInnerSize(argX, argY, argW, argH);
		}

		void setBGColor(double argR, double argG, double argB)
		{
			GetP()->setBGColor(argR, argG, argB);
		}

		void setBGColor(fk_Color ^argC)
		{
			GetP()->setBGColor(*argC->GetP());
		}

		void open(void)
		{
			GetP()->open();
		}
		
		void close(void)
		{
			GetP()->close();
		}
		
		bool update(bool argForceFlg)
		{
			return GetP()->update(argForceFlg);
		}

		bool update(void)
		{
			return GetP()->update(false);
		}
		
		void setFPS(int argFPS)
		{
			GetP()->setFPS(argFPS);
		}

		void showGuide(void)
		{
			GetP()->showGuide(FK_AXIS_X | FK_AXIS_Y | FK_AXIS_Z | FK_GRID_XZ);
		}
		
		void showGuide(fk_GuideMode argMode)
		{
			GetP()->showGuide(int(argMode));
		}

		void hideGuide(void)
		{
			GetP()->hideGuide();
		}

		void setGuideAxisWidth(double argWidth)
		{
			GetP()->setGuideAxisWidth(argWidth);
		}

		void setGuideGridWidth(double argWidth)
		{
			GetP()->setGuideGridWidth(argWidth);
		}

		void setGuideScale(double argScale)
		{
			GetP()->setGuideScale(argScale);
		}

		void setGuideNum(int argNum)
		{
			GetP()->setGuideNum(argNum);
		}

		void setCameraPos(double argX, double argY, double argZ)
		{
			GetP()->setCameraPos(argX, argY, argZ);
		}

		void setCameraPos(fk_Vector ^argV)
		{
			GetP()->setCameraPos(*argV->pVec);
		}

		void setCameraFocus(double argX, double argY, double argZ)
		{
			GetP()->setCameraFocus(argX, argY, argZ);
		}

		void setCameraFocus(fk_Vector ^argV)
		{
			GetP()->setCameraFocus(*argV->pVec);
		}

		void setCameraModel(fk_Model ^argM)
		{
			GetP()->setCameraModel(argM->GetP());
		}
			
		fk_Model^ getCameraModel(void)
		{
			fk_Model^ M = gcnew fk_Model(false);
			M->pBase = reinterpret_cast<::fk_Model *>(GetP()->getCameraModel());
			M->dFlg = false;
			return M;
		}

		void setCameraDefault(void)
		{
			GetP()->setCameraDefault();
		}

		void setScene(fk_Scene^ argScene, bool argCL)
		{
			GetP()->setScene(argScene->GetP(), argCL);
		}
		
		void setScene(fk_Scene^ argScene)
		{
			GetP()->setScene(argScene->GetP(), false);
		}
			
		fk_Scene ^getScene(void)
		{
			fk_Scene ^S = gcnew fk_Scene(false);
			S->pBase = reinterpret_cast<::fk_BaseObject *>(GetP()->getScene());
			S->dFlg = false;
			return S;
		}
		
		void setSceneDefault(void)
		{
			GetP()->setSceneDefault();
		}
			
		void entry(fk_Model ^argModel)
		{
			GetP()->entry(argModel->GetP());
		}

		void entry(fk_Model ^argM, fk_GuideObject^ argGuide)
		{
			GetP()->entry(argM->GetP(), argGuide->GetP());
		}
			
		//void entry(fk_SpriteModel *model);
		//void entry(fk_SpriteModel &model);
		//void entry(fk_Performer *chara);
		//void entry(fk_Performer &chara);

		void remove(fk_Model ^argM)
		{
			GetP()->remove(argM->GetP());
		}

		void remove(fk_Model^ argM, fk_GuideObject^ argGuide)
		{
			GetP()->remove(argM->GetP(), argGuide->GetP());
		}

		//void remove(fk_SpriteModel *model);
		//void remove(fk_SpriteModel &model);
		//void remove(fk_Performer *chara);
		//void remove(fk_Performer &chara);

		void clearModel(bool argCL)
		{
			GetP()->clearModel(argCL);
		}

		void clearModel(void)
		{
			GetP()->clearModel(false);
		}

		bool getKeyStatus(char argK, fk_SwitchStatus argStatus)
		{
			return GetP()->getKeyStatus(argK, GetSS(argStatus), false);
		}
		bool getKeyStatus(char argK, fk_SwitchStatus argStatus, bool argInFlg)
		{
			return GetP()->getKeyStatus(argK, GetSS(argStatus), argInFlg);
		}

		bool getSpecialKeyStatus(fk_SpecialKey keyCode,
								 fk_SwitchStatus argStatus, bool argInFlg)
		{
			return GetP()->getSpecialKeyStatus(GetSK(keyCode), GetSS(argStatus), argInFlg);
		}
		
		bool getSpecialKeyStatus(fk_SpecialKey keyCode, fk_SwitchStatus argStatus)
		{
			return GetP()->getSpecialKeyStatus(GetSK(keyCode), GetSS(argStatus), false);
		}
			
		bool getMouseStatus(fk_MouseButton argB, fk_SwitchStatus argSS, bool argInFlg)
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
				
		fk_Vector^ getMousePosition(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getMousePosition();
			return V;
		}
				
		void setCursorState(bool argVisible, bool argCenter)
		{
			GetP()->setCursorState(argVisible, argCenter);
		}

		void setTrackBallMode(bool argMode)
		{
			GetP()->setTrackBallMode(argMode);
		}

		bool isModelPicked(fk_Model ^argM, int argP, int argX, int argY)
		{
			return GetP()->isModelPicked(argM->GetP(), argP, argX, argY);
		}

		bool isModelPicked(fk_Model ^argM, int argP)
		{
			return GetP()->isModelPicked(argM->GetP(), argP);
		}

		bool isModelPicked(fk_Model ^argM)
		{
			return GetP()->isModelPicked(argM->GetP());
		}

		void procMouseView(fk_Model^ argCamera, double argX, double argY, bool argLockSW)
		{
			GetP()->procMouseView(argCamera->GetP(), argX, argY, argLockSW);
		}
	};
}
