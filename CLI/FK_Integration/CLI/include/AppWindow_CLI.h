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

		property fk_Dimension^ Size {
			void set(fk_Dimension^);
		}

		property fk_Rect^ InnerSize {
			void set(fk_Rect^);
		}

		property fk_Color^ BGColor {
			void set(fk_Color^);
		}

		property int FPS {
			void set(int);
		}

		property double AxisWidth {
			void set(double);
		}

		property double GridWidth {
			void set(double);
		}

		property double GuideScale {
			void set(double);
		}

		property int GuideNum {
			void set(int);
		}

		property fk_Vector^ CameraPos {
			void set(fk_Vector^);
			fk_Vector^ get();
		}

		property fk_Vector^ CameraFocus {
			void set(fk_Vector^);
		}

		property fk_Model^ CameraModel {
			void set(fk_Model^);
			fk_Model^ get();
		}
		
		property fk_Scene^ Scene {
			void set(fk_Scene^);
			fk_Scene^ get();
		}

		property fk_Vector^ MousePosition {
			fk_Vector^ get();
		}

		property bool TrackBallMode {
			void set(bool);
		}
		
		void SetScene(fk_Scene^ scene, bool defCameraAndLight);
		void SetCameraDefault(void);

		void Open(void);
		void Close(void);
		bool Update(bool forceFlg);
		bool Update(void);
		void SetSceneDefault(void);
		void ShowGuide(void);
		void ShowGuide(fk_GuideMode mode);
		void HideGuide(void);

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
		void SetCursorState(bool visible, bool center);
		bool IsModelPicked(fk_Model^ model, int pixel, int mouseX, int mouseY);
		bool IsModelPicked(fk_Model^ model, int pixel);
		bool IsModelPicked(fk_Model^ model);
		void ProcMouseView(fk_Model^ camera, double x, double y, bool lockSW);
	};
}
