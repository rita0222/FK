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

		//! カメラ位置設定・取得プロパティ
		/*!
		 *	現在ウィンドウが制御しているカメラの位置を設定できます。
		 *	また、このプロパティでは位置の取得も可能です。
		 *
		 *		Window.CameraPos = new fk_Vector(0.0, 0.0, 0.0);
		 *		fk_Vector pos = Window.CameraPos;
		 *
		 *	\sa CameraFocus, CameraModel
		 */
		property fk_Vector^ CameraPos {
			void set(fk_Vector^);
			fk_Vector^ get();
		}

		//!	カメラ注視点設定プロパティ
		/*!
		 *	現在ウィンドウが制御しているカメラの向きを、
		 *	指定した座標に向くよう姿勢変更します。
		 *
		 *		Window.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
		 *
		 *	\sa CameraPos, CameraModel
		 */
		property fk_Vector^ CameraFocus {
			void set(fk_Vector^);
		}

		//! カメラモデル設定プロパティ
		/*!
		 *	ウィンドウに対して、
		 *	別の fk_Model (及びその派生クラス)のオブジェクトをカメラとして
		 *	セットします。
		 *	この関数でセットしたモデルを操作すれば、
		 *	fk_AppWindow のメンバ関数を介さずカメラ制御が可能です。
		 *
		 *		fk_Model model = new fk_Model;
		 *		Window.CameraModel = model;
		 *
		 *	\sa CameraPos, CameraFocus, fk_Model
		 */
		property fk_Model^ CameraModel {
			void set(fk_Model^);
			fk_Model^ get();
		}
		
		//! シーン設定プロパティ
		/*!
		 *	ウィンドウに対して、別の fk_Scene のオブジェクトをセットします。
		 *	アプリの画面ごとにモデルを登録した fk_Scene オブジェクトを、
		 *	この関数でセットして切り替えることで、
		 *	モデルを個別に登録や解除を行う手間が省けます。
		 *	ある程度以上の規模を持つアプリを開発する場合は便利です。
		 *	また、現時点のシーンを取得することも可能です。
		 *
		 *		fk_Scene scene = new fk_Scene();
		 *		Window.Scene = scene;
		 *
		 *		fk_Scene s = Window.Scene;
		 *	
		 * \sa SetScene(), fk_Scene
		 */
		property fk_Scene^ Scene {
			void set(fk_Scene^);
			fk_Scene^ get();
		}

		//! マウスポインタ位置取得プロパティ
		/*!
		 *	マウスのカーソル位置を検出します。
		 *	本プロパティは fk_Vector 型であり、
		 *	x 成分と y 成分にそれぞれウィンドウ投影座標系の値が入ります。
		 *	ウィンドウの外にはみ出したかどうかは、
		 *	値がウィンドウサイズを超過しているか否かで判断できます。
		 *
		 *		fk_Vector mousePos = Window.MousePosition;
		 *
		 *	\sa GetMouseStatus()
		 */
		property fk_Vector^ MousePosition {
			fk_Vector^ get();
		}

		//! トラックボールモード制御プロパティ
		/*!
		 *	マウスの右ドラッグとホイール操作で、
		 *	カメラを自由に操作できるモードをON(true)/OFF(false)します。
		 *	デフォルトはOFF(false)です。
		 *
		 *		Window.TrackBallMode = true;
		 */
		property bool TrackBallMode {
			void set(bool);
		}
		
		//! \name カメラ制御関数
		//@{

		//! カメラ初期化関数
		/*!
		 *	ウィンドウが制御するカメラを、
		 *	デフォルトで内部に保持している fk_Model のインスタンスに戻します。
		 *
		 *	\sa		CameraModel
		 */
		void SetCameraDefault(void);
		//@}

		//! \name シーン制御関数
		//@{
		//! シーン設定関数
		/*!
		 *	ウィンドウに対して、別の fk_Scene のオブジェクトをセットします。
		 *	アプリの画面ごとにモデルを登録した fk_Scene オブジェクトを、
		 *	この関数でセットして切り替えることで、
		 *	モデルを個別に登録や解除を行う手間が省けます。
		 *	ある程度以上の規模を持つアプリを開発する場合は便利です。
		 *	Scene プロパティによる設定との違いは、第 2 引数にあります。
		 *	第 2 引数に true を設定すると、新たにセットするシーンに対して、
		 *	fk_AppWindow 内部のカメラとライトオブジェクトを
		 *	引き継いでセットすることができますが、
		 *	構造がややこしくなるのでできるだけ自前で用意することを推奨します。
		 *	省略した場合と false を設定した場合はシーンの切り替えのみを行います。
		 *
		 *	\param[in]		scene				シーンインスタンス
		 *	\param[in]		defCameraAndLight
		 *		true である場合、
		 *		カメラ・光源設定についてシーン設定前のものを用います。
		 *		false である場合は第一引数の scene
		 *		に設定されている情報に切り替えます。
		 *
		 *	\sa Scene, SetSceneDefault(), fk_Scene
		 */
		void SetScene(fk_Scene^ scene, bool defCameraAndLight);

		//! シーン設定初期化関数
		/*!
		 *	ウィンドウが制御するシーンを、
		 *	デフォルトで内部に保持している fk_Scene のインスタンスに戻します。
		 *
		 *	\sa Scene, SetScene(fk_Scene^, bool), fk_Scene
		 */
		void SetSceneDefault(void);

		//! 通常モデル表示登録関数
		/*!
		 *	ウィンドウに対してモデルを登録し、表示するようにします。
		 *	既に登録済みのモデルに対して行った場合、登録順が最後尾となります。
		 *
		 *	\note
		 *		FKでは、半透明な物体AとBがあり、
		 *		配置関係で「Aが前、Bが後」となっていた場合、
		 *		登録順が B, A の順番であれば適切に描画されますが、
		 *		A, B の登録順となっていた場合には A が半透明であっても
		 *		B が透けて見えなくなります。
		 *		このような場合、「前に配置される物体ほど後に登録する」
		 *		ように登録することで半透明描画が適切となります。
		 *
		 *	\param[in]		model		登録モデル
		 *
		 *	\sa Remove(fk_Model^), ClearModel()
		 */
		void Entry(fk_Model^ model);

		//! 座標軸付きモデル表示登録関数
		/*!
		 *	ウィンドウに対してモデルを登録し、表示するようにします。
		 *	既に登録済みのモデルに対して行った場合、登録順が最後尾となります。
		 *	半透明物体の描画については、 Entry(fk_Model^) の説明を参照して下さい。
		 *	登録の際、モデルのローカル座標系に基づく座標軸を同時に登録します。
		 *
		 *	\param[in]		model		登録モデル
		 *	\param[in]		guide		座標軸
		 *
		 *	\sa Remove(fk_Model^, fk_GuideObject^), ClearModel(), fk_GuideObject
		 */
		void Entry(fk_Model^ model, fk_GuideObject^ guide);

		//! スプライトモデル登録関数
		/*!
		 *	ウィンドウに対してスプライトモデルを登録し、表示するようにします。
		 *
		 *	\param[in]		model		登録モデル
		 *
		 *	\sa Remove(fk_SpriteModel^), ClearModel(), fk_SpriteModel
		 */
		void Entry(fk_SpriteModel^ model);

		//! fk_Performer モデル登録関数
		/*!
		 *	ウィンドウに対して fk_Performer 型のモデルを登録し、
		 *	表示するようにします。
		 *
		 *	\param[in]		chara		登録モデル
		 *
		 *	\sa Remove(fk_Performer^), ClearModel(), fk_Performer
		 */
		void Entry(fk_Performer^ chara);

		//! 通常モデル表示解除関数
		/*!
		 *	ウィンドウからモデルの登録を解除し、表示されないようにします。
		 *	登録していないモデルを指定した場合は何も起きません。
		 *
		 *	\param[in]		model		登録解除モデル
		 *
		 *	\sa Entry(fk_Model^), ClearModel(), fk_Model
		 */
		void Remove(fk_Model^ model);

		//! 座標軸付きモデル表示解除関数
		/*!
		 *	ウィンドウから、座標軸付きモデルの登録を解除し、
		 *	表示されないようにします。
		 *	登録していないモデルを指定した場合は何も起きません。
		 *
		 *	\param[in]		model		登録解除モデル
		 *	\param[in]		guide		登録解除座標軸
		 *
		 *	\sa Entry(fk_Model^, fk_GuideObject^), ClearModel()
		 */
		void Remove(fk_Model^ model, fk_GuideObject^ guide);

		//! スプライトモデル表示解除関数
		/*!
		 *	ウィンドウから、スプライトモデルの登録を解除し、
		 *	表示されないようにします。
		 *	登録していないモデルを指定した場合は何も起きません。
		 *
		 *	\param[in]		model		登録解除モデル
		 *
		 *	\sa Entry(fk_SpriteModel^), ClearModel()
		 */
		void Remove(fk_SpriteModel^ model);

		//! fk_Performer モデル表示解除関数
		/*!
		 *	ウィンドウから、fk_Performer 型モデルの登録を解除し、
		 *	表示されないようにします。
		 *	登録していないモデルを指定した場合は何も起きません。
		 *
		 *	\param[in]		chara		登録解除モデル
		 *
		 *	\sa Entry(fk_Performer^), ClearModel()
		 */
		void Remove(fk_Performer^ chara);

		//! 全モデル登録解除関数1
		/*!
		 *	現在のシーンから全てのモデルの表示登録を解除します。
		 *
		 *	\param[in]	defCameraAndLight
		 *		ウィンドウ内部で保持しているライトとカメラのモデルを残したい場合は、
		 *		true を指定します。
		 *		false を渡した場合は、完全なクリアとなります。
		 */
		void ClearModel(bool defCameraAndLight);

		//! 全モデル登録解除関数2
		/*!
		 *	現在のシーンから全てのモデルの表示登録を解除します。
		 *	ウィンドウ内部で保持しているライトとカメラのモデルは全てクリアとなります。
		 *
		 *	\sa ClearModel(bool)
		 */
		void ClearModel(void);
		//@}

		//! \name 描画制御関数
		//@{
		//! ウィンドウ生成関数
		/*!
		 *	ウィンドウを開いて表示します。
		 *
		 *	\sa Close(), Update()
		 */
		void Open(void);

		//! ウィンドウ破棄関数
		/*!
		 *	ウィンドウを閉じます。
		 *	ウィンドウが表示されている状態でプログラムが終了した場合は
		 *	自動的に閉じられるので、
		 *	本関数を明示的に呼ぶ必要はありません。
		 *	プログラム自体は動作し続けるが、ウィンドウを閉じたい場合や、
		 *	改めてウィンドウを再生成したい場合に本関数を利用して下さい。
		 *
		 *	\sa Open(), Update()
		 */
		void Close(void);

		//! シーン描画関数1
		/*!
		 *	シーン画面を描画し、さらに各種入力デバイスの状態を更新します。
		 *	基本的にメインループ内でコールすることになります。
		 *	その際、 FPS プロパティの数値基づいて時間調整が入ります。
		 *	FPS 制御を無視して強制的に描画処理を呼び出したい場合は引数に
		 *	true を渡します。
		 *
		 *	\param[in]	forceFlg
		 *		true の場合、FPS制御を無視して強制的に再描画を行います。
		 * 		false の場合は FPS制御により描画タイミングを制御し、
		 *		描画が行われるまでは関数は終了しなくなります。
		 *		デフォルトは false です。
		 *
		 *	\sa Open(), Close(), FPS
		 */
		bool Update(bool forceFlg);

		//! シーン描画関数2
		/*!
		 *	シーン画面を描画し、さらに各種入力デバイスの状態を更新します。
		 *	基本的にメインループ内でコールすることになります。
		 *	その際、 FPS プロパティの数値基づいて時間調整が入ります。
		 *	本関数は、 Update(bool) において引数に false を与えた場合と同様の挙動となります。
		 *
		 *	\sa Open(), Close(), FPS
		 */
		bool Update(void);
		//@}

		//! \name グリッド・座標軸表示設定関数
		//@{

		//! グリッド・軸設定関数1
		/*!
		 *	画面内の座標系を表すグリッドと軸を指定します。
		 *	引数は、 AXIS_X, AXIS_Y, AXIS_Z がそれぞれの軸を、
		 *	GRID_XZ, GRID_XY, GRID_YZ がそれぞれの平面を表すグリッドに対応します。
		 *	複数の要素を指定したい場合は | (ビットOR演算子)で区切って指定できます。
		 *	NO_GUIDE で全て非表示に、 ALL_GUIDE で全ての軸・グリッドを表示します。
		 *	引数を省略した場合は、xyz の各軸と xz 平面のグリッドを表示します。
		 *	デフォルトでは全て非表示(NO_GUIDE)です。
		 *
		 *	\param[in]		mode
		 *		表示するグリッド・軸の指定。複数を表示する場合は、
		 *		ビットOR演算を利用して並べて指定できます。
		 *
		 *	\sa HideGuide(), AxisWidth, GridWidth, GuideScale, GuideNum, fk_GuideMode
		 */
		void ShowGuide(fk_GuideMode mode);

		//! グリッド・軸設定関数2
		/*!
		 *	画面内の座標系を表すグリッドと軸を指定します。
		 *	本関数では、3次元座標軸と xz 平面のグリッドを表示します。
		 *	表示する座標軸およびグリッド面を細かく指定したい場合は、
		 *	ShowGuide(bool) を利用してください。
		 *
		 *	\sa HideGuide(), AxisWidth, GridWidth, GuideScale, GuideNum, fk_GuideMode
		 */
		void ShowGuide(void);

		//! グリッド・軸消去関数
		/*!
		 *	ShowGuide() で表示した軸とグリッドを消去します。
		 *	ShowGuide( fk_GuideMode.NO_GUIDE ) と等価です。
		 *
		 *	\sa ShowGuide()
		 */
		void HideGuide(void);

		//@}

		//! \name キーボード状態取得関数
		//@{
		bool GetKeyStatus(wchar_t key, fk_SwitchStatus status);
		bool GetKeyStatus(wchar_t key, fk_SwitchStatus status, bool insideFlg);
		bool GetSpecialKeyStatus(fk_SpecialKey keyCode,
								 fk_SwitchStatus status, bool insideFlg);
		bool GetSpecialKeyStatus(fk_SpecialKey keyCode, fk_SwitchStatus status);
		//@}

		//! \name マウス状態取得関数
		//@{
		bool GetMouseStatus(fk_MouseButton buttonCode, fk_SwitchStatus status, bool insideFlg);
		void SetCursorState(bool visible, bool center);
		bool IsModelPicked(fk_Model^ model, int pixel, int mouseX, int mouseY);
		bool IsModelPicked(fk_Model^ model, int pixel);
		bool IsModelPicked(fk_Model^ model);
		void ProcMouseView(fk_Model^ camera, double x, double y, bool lockSW);
		//@}
	};
}
