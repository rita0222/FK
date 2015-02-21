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

		::fk_AppWindow * GetP(void);
		::fk_SpecialKey GetSK(fk_SpecialKey);
		::fk_SwitchStatus GetSS(fk_SwitchStatus);

	public:
		fk_AppWindow();
		~fk_AppWindow();
		!fk_AppWindow();

		property String^ WindowName {
			void set(String^);
		}

		void SetSize(int w, int h);
		void SetInnerSize(int x, int y, int w, int h);
		void SetBGColor(double r, double g, double b);
		void SetBGColor(fk_Color^ color);
		void Open(void);
		void Close(void);
		bool Update(bool forceFlg);
		bool Update(void);
		void SetFPS(int FPS);
		void ShowGuide(void);
		void ShowGuide(fk_GuideMode mode);
		void HideGuide(void);
		void SetGuideAxisWidth(double width);
		void SetGuideGridWidth(double width);
		void SetGuideScale(double scale);
		void SetGuideNum(int num);
		void SetCameraPos(double x, double y, double z);
		void SetCameraPos(fk_Vector^ pos);
		void SetCameraFocus(double x, double y, double z);
		void SetCameraFocus(fk_Vector^ pos);
		void SetCameraModel(fk_Model^ model);
		fk_Model^ GetCameraModel(void);
		void SetCameraDefault(void);
		void SetScene(fk_Scene^ scene, bool defCameraAndLight);
		void SetScene(fk_Scene^ scene);
		fk_Scene^ GetScene(void);
		void SetSceneDefault(void);
		void Entry(fk_Model^ model);
		void Entry(fk_Model^ model, fk_GuideObject^ guide);
		void Entry(fk_SpriteModel^ model);
		void Entry(fk_Performer^ chara);
		void Remove(fk_Model^ model);
		void Remove(fk_Model^ model, fk_GuideObject^ guide);
		void Remove(fk_SpriteModel^ model);
		void Remove(fk_Performer^ chara);
		void ClearModel(bool defCameraAndLight);
		void ClearModel(void);
		bool GetKeyStatus(wchar_t key, fk_SwitchStatus status);
		bool GetKeyStatus(wchar_t key, fk_SwitchStatus status, bool insideFlg);
		bool GetSpecialKeyStatus(fk_SpecialKey keyCode,
								 fk_SwitchStatus status, bool insideFlg);
		bool GetSpecialKeyStatus(fk_SpecialKey keyCode, fk_SwitchStatus status);
		bool GetMouseStatus(fk_MouseButton buttonCode, fk_SwitchStatus status, bool insideFlg);
		fk_Vector^ GetMousePosition(void);
		void SetCursorState(bool visible, bool center);
		void SetTrackBallMode(bool mode);
		bool IsModelPicked(fk_Model^ model, int pixel, int mouseX, int mouseY);
		bool IsModelPicked(fk_Model^ model, int pixel);
		bool IsModelPicked(fk_Model^ model);
		void ProcMouseView(fk_Model^ camera, double x, double y, bool lockSW);
	};
}
