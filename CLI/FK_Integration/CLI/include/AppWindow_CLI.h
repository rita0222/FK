// AppWindow_CLI.h

#pragma once

#include <FK/SimpleWindow.h>
#include "GuideObject_CLI.h"
#include "SpriteModel_CLI.h"
#include "Performer_CLI.h"

namespace FK_CLI
{
	public enum class fk_SpecialKey {
		SHIFT_R,	//!< 右シフトキー
		SHIFT_L,	//!< 左シフトキー
		CTRL_R,		//!< 右コントロールキー
		CTRL_L,		//!< 左コントロールキー
		ALT_R,		//!< 右オルトキー
		ALT_L,		//!< 左オルトキー
		ENTER,		//!< エンター(改行、リターン)キー
		BACKSPACE,	//!< バックスペース(後退)キー
		DELETEKEY,	//!< デリート(削除)キー
		CAPS_LOCK,	//!< キャップスロックキー
		TAB,		//!< タブキー
		PAGE_UP,	//!< ページアップキー
		PAGE_DOWN,	//!< ページダウンキー
		HOME,		//!< ホームキー
		END,		//!< エンドキー
		INSERT,		//!< インサートキー
		LEFT,		//!< 左矢印キー
		RIGHT,		//!< 右矢印キー
		UP,			//!< 上矢印キー
		DOWN,		//!< 下矢印キー
		F1,			//!< F1 ファンクションキー
		F2,			//!< F2 ファンクションキー
		F3,			//!< F3 ファンクションキー
		F4,			//!< F4 ファンクションキー
		F5,			//!< F5 ファンクションキー
		F6,			//!< F6 ファンクションキー
		F7,			//!< F7 ファンクションキー
		F8,			//!< F8 ファンクションキー
		F9,			//!< F9 ファンクションキー
		F10,		//!< F10 ファンクションキー
		F11,		//!< F11 ファンクションキー
		F12			//!< F12 ファンクションキー
	};

	//! マウスボタンを表す列挙型
	public enum class fk_MouseButton {
		MOUSE1,		//!< マウス左クリック(第1ボタン)
		MOUSE2,		//!< マウス中クリック、あるいはホイールクリック(第2ボタン)
		MOUSE3		//!< マウス右クリック(第3ボタン)
	};

	//! ボタン系デバイス状態を表す列挙型
	 public enum class fk_SwitchStatus {
		RELEASE,	//!< 離しっぱなしの状態
		UP,			//!< 離した瞬間
		DOWN,		//!< 押した瞬間
		PRESS		//!< 押しっぱなしの状態
	};

	//! アプリケーションウィンドウクラス
	/*!
	 *	このクラスは、
	 *	3D シーンを表示するウィンドウを簡易に作成する機能を提供します。
	 *	シーン・カメラ・ライトを内包しているので、
	 *	とりあえず形状を表示させるだけなら、
	 *	非常に短いコード量で済みます。
	 *	もちろんゲームアプリを完成させることも可能です。
	 *	入力に関するユーティリティ機能も含みます。
	 *	Fl_Window、 fk_Window 、 fk_Scene を複合したクラスですので、
	 *	既存の FK ユーザが利用する場合はその旨を念頭に置いてください。
	 */
	public ref class fk_AppWindow {
	internal:
		::fk_AppWindow *pWin;
		fk_Scene^ scene;

		::fk_AppWindow * GetP(void);
		::fk_SpecialKey GetSK(fk_SpecialKey);
		::fk_SwitchStatus GetSS(fk_SwitchStatus);

	public:
		//! コンストラクタ
		fk_AppWindow();

		//! デストラクタ
		~fk_AppWindow();

		//! ファイナライザ
		!fk_AppWindow();

		//! ウィンドウタイトルプロパティ
		/*!
		 *	ウィンドウタイトルに出力する文字列を設定します。
		 *
		 *		Window.WindowName = "FK Window";
		 */
		property String^ WindowName {
			void set(String^);
		}

		//!	ウィンドウサイズプロパティ
		/*!
		 *	ウィンドウサイズを変更します。単位はピクセルです。
		 *	3DCG描画領域も同じサイズに変更します。
		 *	デフォルトは512x512です。
		 *
		 *		Window.Size.w = 800;
		 *		Window.Size.h = 600;
		 */
		property fk_Dimension^ Size {
			void set(fk_Dimension^);
		}

		//! 描画領域サイズ設定プロパティ
		/*!
		 *	ウィンドウの内部に持つ3DCGの描画領域の位置とサイズを変更します。
		 *	マルチウィンドウを実現する際の調整用関数なので、上級者向けです。
		 *
		 *		Window.InnerSize.x = 10;	// 描画領域左上位置 x 座標
		 *		Window.InnerSize.y = 10;	// 描画領域左上位置 y 座標
		 *		Window.InnerSize.w = 100;	// 描画領域横幅
		 *		Window.InnerSize.h = 100;	// 描画領域縦幅
		 */
		property fk_Rect^ InnerSize {
			void set(fk_Rect^);
		}

		//! 背景色設定プロパティ
		/*!
		 *	3DCG描画領域の背景色を設定します。
		 *
		 *		// RGB要素を一つずつ設定
		 *		Window.BGColor.r = 0.2;
		 *		Window.BGColor.g = 0.3;
		 *		Window.BGColor.b = 0.4;
		 *
		 *		// fk_Colorで一括設定
		 *		Window.BGColor = new fk_Color(0.2, 0.3, 0.4);
		 */
		property fk_Color^ BGColor {
			void set(fk_Color^);
		}

		//! FPS設定プロパティ
		/*!
		 *	Update()をコールした際に調整するFPSを指定します。
		 *	FPS(Frame Per Second)とは、1秒間中で画面更新が行われる回数の単位です。
		 *	この値を 0 に設定した場合は、FPS制御を行いません。
		 *	デフォルトは60です。
		 *
		 *		Window.FPS = 0;
		 */
		property int FPS {
			void set(int);
		}

		//! 軸線幅設定プロパティ
		/*!
		 *	ShowGuide() で表示する軸の太さを指定します。
		 *	デフォルトは4.0です。
		 *
		 *		Window.AxisWidth = 1.0;
		 *
		 *	\sa ShowGuide(), GridWidth, GuideNum
		 */
		property double AxisWidth {
			void set(double);
		}

		//! グリッド線幅設定プロパティ
		/*!
		 *	ShowGuide() で表示するグリッドの太さを指定します。
		 *	デフォルトは1.0です。
		 *
		 *		Window.GridWidth = 0.5;
		 *
		 *	\sa ShowGuide(), AxisWidth, GuideNum
		 */
		property double GridWidth {
			void set(double);
		}

		//! グリッド幅設定プロパティ
		/*!
		 *	ShowGuide()で表示するグリッドや軸の1辺の長さを指定します。
		 *	デフォルトは5.0です。
		 *
		 *		Window.GuideScale = 10.0;
		 *
		 *	\sa ShowGuide(), GridWidth, GuideNum
		 */
		property double GuideScale {
			void set(double);
		}

		//! グリッド数設定プロパティ
		/*!
		 *	ShowGuide()で表示するグリッドの軸方向あたりの個数を指定します。
		 *	デフォルトは20です。
		 *
		 *		Window.GuideNum = 50;
		 *
		 *	\sa ShowGuide(), GridWidth, GuideScale
		 */
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
