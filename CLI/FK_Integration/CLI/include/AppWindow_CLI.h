// AppWindow_CLI.h

#pragma once

#include <FK/SimpleWindow.h>
#include "GuideObject_CLI.h"
#include "SpriteModel_CLI.h"
#include "Performer_CLI.h"

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

	public ref class fk_AppWindow {
	internal:
		::fk_AppWindow *pWin;
		fk_Scene^ scene;

		::fk_AppWindow * GetP(void)
		{
			return pWin;
		}

		::fk_SpecialKey GetSK(fk_SpecialKey);
		::fk_SwitchStatus GetSS(fk_SwitchStatus);

	public:
		fk_AppWindow::fk_AppWindow()
		{
			pWin = new ::fk_AppWindow();
			scene = gcnew fk_Scene(false);
			scene->pBase = GetP()->getScene();
			scene->dFlg = false;
			scene->CameraUpdate();
		}

		fk_AppWindow::~fk_AppWindow()
		{
			delete pWin;
			pWin = NULL;
		}

		fk_AppWindow::!fk_AppWindow()
		{
			pWin->SetFinalizeMode();
			delete pWin;
			pWin = NULL;
		}

		void setWindowName(String^ name);
		void setSize(int w, int h);
		void setInnerSize(int x, int y, int w, int h);
		void setBGColor(double r, double g, double b);
		void setBGColor(fk_Color^ color);
		void open(void);
		void close(void);
		bool update(bool forceFlg);
		bool update(void);
		void setFPS(int FPS);
		void showGuide(void);
		void showGuide(fk_GuideMode mode);
		void hideGuide(void);
		void setGuideAxisWidth(double width);
		void setGuideGridWidth(double width);
		void setGuideScale(double scale);
		void setGuideNum(int num);
		void setCameraPos(double x, double y, double z);
		void setCameraPos(fk_Vector^ pos);
		void setCameraFocus(double x, double y, double z);
		void setCameraFocus(fk_Vector^ pos);
		void setCameraModel(fk_Model^ model);
		fk_Model^ getCameraModel(void);
		void setCameraDefault(void);
		void setScene(fk_Scene^ scene, bool defCameraAndLight);
		void setScene(fk_Scene^ scene);
		fk_Scene^ getScene(void);
		void setSceneDefault(void);
		void entry(fk_Model^ model);
		void entry(fk_Model^ model, fk_GuideObject^ guide);
		void entry(fk_SpriteModel^ model);
		void entry(fk_Performer^ chara);
		void remove(fk_Model^ model);
		void remove(fk_Model^ model, fk_GuideObject^ guide);
		void remove(fk_SpriteModel^ model);
		void remove(fk_Performer^ chara);
		void clearModel(bool defCameraAndLight);
		void clearModel(void);
		bool getKeyStatus(wchar_t key, fk_SwitchStatus status);
		bool getKeyStatus(wchar_t key, fk_SwitchStatus status, bool insideFlg);
		bool getSpecialKeyStatus(fk_SpecialKey keyCode,
								 fk_SwitchStatus status, bool insideFlg);
		bool getSpecialKeyStatus(fk_SpecialKey keyCode, fk_SwitchStatus status);
		bool getMouseStatus(fk_MouseButton buttonCode, fk_SwitchStatus status, bool insideFlg);
		fk_Vector^ getMousePosition(void);
		void setCursorState(bool visible, bool center);
		void setTrackBallMode(bool mode);
		bool isModelPicked(fk_Model^ model, int pixel, int mouseX, int mouseY);
		bool isModelPicked(fk_Model^ model, int pixel);
		bool isModelPicked(fk_Model^ model);
		void procMouseView(fk_Model^ camera, double x, double y, bool lockSW);
	};
}
