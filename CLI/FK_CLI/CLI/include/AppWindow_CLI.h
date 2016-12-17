// AppWindow_CLI.h

#pragma once

#include <FK/AppWindow.h>
#include "GuideObject_CLI.h"
#include "SpriteModel_CLI.h"
#include "Performer_CLI.h"
#include "Plane_CLI.h"

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
	public ref class fk_AppWindow : public fk_IBindableDrawer {
	internal:
		::fk_AppWindow *pWin;
		fk_Scene^ scene;

		delegate void ShaderCallback(void);
		ShaderCallback^ preInit;
		ShaderCallback^ postInit;
		ShaderCallback^ preDraw;
		ShaderCallback^ postDraw;
		ShaderCallback^ preDrawLeft;
		ShaderCallback^ postDrawLeft;
		ShaderCallback^ preDrawRight;
		ShaderCallback^ postDrawRight;

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
		 *	マルチウィンドウを実現する際に使用します。
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
		 *	このメソッドでセットしたモデルを操作すれば、
		 *	fk_AppWindow のメソッドを介さずカメラ制御が可能です。
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
		 *	このメソッドでセットして切り替えることで、
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
		
		//! \name カメラ制御メソッド
		//@{

		//! カメラ初期化メソッド
		/*!
		 *	ウィンドウが制御するカメラを、
		 *	デフォルトで内部に保持している fk_Model のインスタンスに戻します。
		 *
		 *	\sa		CameraModel
		 */
		void SetCameraDefault(void);
		//@}

		//! \name シーン制御メソッド
		//@{
		//! シーン設定メソッド
		/*!
		 *	ウィンドウに対して、別の fk_Scene のオブジェクトをセットします。
		 *	アプリの画面ごとにモデルを登録した fk_Scene オブジェクトを、
		 *	このメソッドでセットして切り替えることで、
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

		//! シーン設定初期化メソッド
		/*!
		 *	ウィンドウが制御するシーンを、
		 *	デフォルトで内部に保持している fk_Scene のインスタンスに戻します。
		 *
		 *	\sa Scene, SetScene(fk_Scene^, bool), fk_Scene
		 */
		void SetSceneDefault(void);

		//! 通常モデル表示登録メソッド
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

		//! 座標軸付きモデル表示登録メソッド
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

		//! スプライトモデル登録メソッド
		/*!
		 *	ウィンドウに対してスプライトモデルを登録し、表示するようにします。
		 *
		 *	\param[in]		model		登録モデル
		 *
		 *	\sa Remove(fk_SpriteModel^), ClearModel(), fk_SpriteModel
		 */
		void Entry(fk_SpriteModel^ model);

		//! fk_Performer モデル登録メソッド
		/*!
		 *	ウィンドウに対して fk_Performer 型のモデルを登録し、
		 *	表示するようにします。
		 *
		 *	\param[in]		chara		登録モデル
		 *
		 *	\sa Remove(fk_Performer^), ClearModel(), fk_Performer
		 */
		void Entry(fk_Performer^ chara);

		//! 通常モデル表示解除メソッド
		/*!
		 *	ウィンドウからモデルの登録を解除し、表示されないようにします。
		 *	登録していないモデルを指定した場合は何も起きません。
		 *
		 *	\param[in]		model		登録解除モデル
		 *
		 *	\sa Entry(fk_Model^), ClearModel(), fk_Model
		 */
		void Remove(fk_Model^ model);

		//! 座標軸付きモデル表示解除メソッド
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

		//! スプライトモデル表示解除メソッド
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

		//! fk_Performer モデル表示解除メソッド
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

		//! 全モデル登録解除メソッド1
		/*!
		 *	現在のシーンから全てのモデルの表示登録を解除します。
		 *
		 *	\param[in]	defCameraAndLight
		 *		ウィンドウ内部で保持しているライトとカメラのモデルを残したい場合は、
		 *		true を指定します。
		 *		false を渡した場合は、完全なクリアとなります。
		 */
		void ClearModel(bool defCameraAndLight);

		//! 全モデル登録解除メソッド2
		/*!
		 *	現在のシーンから全てのモデルの表示登録を解除します。
		 *	ウィンドウ内部で保持しているライトとカメラのモデルは全てクリアとなります。
		 *
		 *	\sa ClearModel(bool)
		 */
		void ClearModel(void);
		//@}

		//! \name 描画制御メソッド
		//@{
		//! ウィンドウ生成メソッド
		/*!
		 *	ウィンドウを開いて表示します。
		 *
		 *	\sa Close(), Update()
		 */
		void Open(void);

		//! ウィンドウ破棄メソッド
		/*!
		 *	ウィンドウを閉じます。
		 *	ウィンドウが表示されている状態でプログラムが終了した場合は
		 *	自動的に閉じられるので、
		 *	本メソッドを明示的に呼ぶ必要はありません。
		 *	プログラム自体は動作し続けるが、ウィンドウを閉じたい場合や、
		 *	改めてウィンドウを再生成したい場合に本メソッドを利用して下さい。
		 *
		 *	\sa Open(), Update()
		 */
		void Close(void);

		//! シーン描画メソッド1
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
		 *		描画が行われるまではメソッドは終了しなくなります。
		 *		デフォルトは false です。
		 *
		 *	\sa Open(), Close(), FPS
		 */
		bool Update(bool forceFlg);

		//! シーン描画メソッド2
		/*!
		 *	シーン画面を描画し、さらに各種入力デバイスの状態を更新します。
		 *	基本的にメインループ内でコールすることになります。
		 *	その際、 FPS プロパティの数値基づいて時間調整が入ります。
		 *	本メソッドは、 Update(bool) において引数に false を与えた場合と同様の挙動となります。
		 *
		 *	\sa Open(), Close(), FPS
		 */
		bool Update(void);
		//@}

		//! \name グリッド・座標軸表示設定メソッド
		//@{

		//! グリッド・軸設定メソッド1
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

		//! グリッド・軸設定メソッド2
		/*!
		 *	画面内の座標系を表すグリッドと軸を指定します。
		 *	本メソッドでは、3次元座標軸と xz 平面のグリッドを表示します。
		 *	表示する座標軸およびグリッド面を細かく指定したい場合は、
		 *	ShowGuide(bool) を利用してください。
		 *
		 *	\sa HideGuide(), AxisWidth, GridWidth, GuideScale, GuideNum, fk_GuideMode
		 */
		void ShowGuide(void);

		//! グリッド・軸消去メソッド
		/*!
		 *	ShowGuide() で表示した軸とグリッドを消去します。
		 *	ShowGuide( fk_GuideMode.NO_GUIDE ) と等価です。
		 *
		 *	\sa ShowGuide()
		 */
		void HideGuide(void);
		//@}

		//! \name キーボード状態取得メソッド
		//@{

		//! 通常キー状態取得メソッド1
		/*!
		 *	通常キーの入力状態を検出します。
		 *	引数として、
		 *	検出したい文字をシングルクォーテーションで囲って指定します。
		 *	'A' や 'X' などとします。
		 *	入力できない特殊キーには getSpecialKeyStatus() を使います。
		 *
		 *	以下のコードは、「A」キーが押されているかどうかを検出します。
		 *
		 *		if(Window.GetKeyStatus('a', fk_SwitchStatus.PRESS, false) == true) {
		 *			// 押されている場合の処理
		 *		}
		 *
		 *	\param[in]	key
		 *		状態を取得したいキー文字。大文字や数字、各種記号キーを設定します。
		 *		スペースキーの状態を取得したい場合は「' '」と入力します。
		 *
		 *	\param[in]	status
		 *		取得したい状態を指定します。
		 *		種類については FK_CLI::fk_SwitchStatus を参照してください。
		 *
		 *	\param[in]	insideFlag
		 *		true だった場合、
		 *		マウスポインタが描画領域の外にあった場合は無条件に false を返します。
		 *		false だった場合は、マウスポインタの位置に関わらず押下状態を返します。
		 *
		 *	\return
		 *		キーが status で指定した状態を満たしていれば true を、
		 *		そうでなければ false を返します。
		 *
		 *	\sa GetSpecialKeyStatus(), Update()
		 */
		bool GetKeyStatus(wchar_t key, fk_SwitchStatus status, bool insideFlag);

		//! 通常キー状態取得メソッド2
		/*!
		 *	通常キーの入力状態を検出します。
		 *	引数として、
		 *	検出したい文字をシングルクォーテーションで囲って指定します。
		 *	'A' や 'X' などとします。
		 *	入力できない特殊キーには getSpecialKeyStatus() を使います。
		 *	なお、本メソッドは GetKeyStatus(wchar_t, fk_SwitchStatus, bool) にて
		 *	第三引数に false を入力した場合と挙動は同一です。
		 *
		 *	以下のコードは、「A」キーが押されているかどうかを検出します。
		 *
		 *		if(Window.GetKeyStatus('a', fk_SwitchStatus.PRESS) == true) {
		 *			// 押されている場合の処理
		 *		}
		 *
		 *	\param[in]	key
		 *		状態を取得したいキー文字。大文字や数字、各種記号キーを設定します。
		 *		スペースキーの状態を取得したい場合は「' '」と入力します。
		 *
		 *	\param[in]	status
		 *		取得したい状態を指定します。
		 *		種類については FK_CLI::fk_SwitchStatus を参照してください。
		 *
		 *	\return
		 *		キーが status で指定した状態を満たしていれば true を、
		 *		そうでなければ false を返します。
		 *
		 *	\sa GetSpecialKeyStatus(), Update()
		 */
		bool GetKeyStatus(wchar_t key, fk_SwitchStatus status);

		//! 特殊キー状態取得メソッド1
		/*!
		 *	特殊キーの入力状態を検出します。
		 *	引数として、検出したいキーに対応した FK_CLI::fk_SpecialKey 型の値を入力します。
		 *	例えば、上矢印キーの状態を取得したい場合には「fk_SpecialKey.UP」を入力します。
		 *	通常キーの状態取得は GetKeyStatus() を使います。
		 *
		 *	以下のコードは、「F1」キーが押されているかどうかを検出します。
		 *
		 *		if(Window.GetSpecialKeyStatus(fk_SpecialKey.F1, fk_SwitchStatus.PRESS, false) == true) {
		 *			// 押されている場合の処理
		 *		}
		 *
		 *	\param[in]	keyCode
		 *		状態を取得したいキーに対応した値。
		 *
		 *	\param[in]	status
		 *		取得したい状態を指定します。
		 *		種類については FK_CLI::fk_SwitchStatus を参照してください。
		 *
		 *	\param[in]	insideFlag
		 *		true だった場合、
		 *		マウスポインタが描画領域の外にあった場合は無条件に false を返します。
		 *		false だった場合は、マウスポインタの位置に関わらず押下状態を返します。
		 *
		 *	\return
		 *		キーが status で指定した状態を満たしていれば true を、
		 *		そうでなければ false を返します。
		 *
		 *	\note
		 *		スペースキーの状態取得は、本メソッドではなく GetKeyStatus() を用います。
		 *
		 *	\sa GetKeyStatus(), Update()
		 */
		bool GetSpecialKeyStatus(fk_SpecialKey keyCode,
								 fk_SwitchStatus status, bool insideFlag);
		
		//! 特殊キー状態取得メソッド2
		/*!
		 *	特殊キーの入力状態を検出します。
		 *	引数として、検出したいキーに対応した FK_CLI::fk_SpecialKey 型の値を入力します。
		 *	例えば、上矢印キーの状態を取得したい場合には「fk_SpecialKey.UP」を入力します。
		 *	通常キーの状態取得は GetKeyStatus() を使います。
		 *	なお、本メソッドは GetSpecialKeyStatus(fk_SpecialKey, fk_SwitchStatus, bool) にて
		 *	第三引数に false を入力した場合と挙動は同一です。
		 *
		 *	以下のコードは、「F1」キーが押されているかどうかを検出します。
		 *
		 *		if(Window.GetSpecialKeyStatus(fk_SpecialKey.F1, fk_SwitchStatus.PRESS) == true) {
		 *			// 押されている場合の処理
		 *		}
		 *
		 *	\param[in]	keyCode
		 *		状態を取得したいキーに対応した値。
		 *
		 *	\param[in]	status
		 *		取得したい状態を指定します。
		 *		種類については FK_CLI::fk_SwitchStatus を参照してください。
		 *
		 *	\return
		 *		キーが status で指定した状態を満たしていれば true を、
		 *		そうでなければ false を返します。
		 *
		 *	\note
		 *		スペースキーの状態取得は、本メソッドではなく GetKeyStatus() を用います。
		 *
		 *	\sa GetKeyStatus(), Update()
		 */
		bool GetSpecialKeyStatus(fk_SpecialKey keyCode, fk_SwitchStatus status);
		//@}

		//! \name マウス状態取得メソッド
		//@{

		//! マウスボタン状態取得メソッド
		/*!
		 *	マウスボタンのクリック状態を検出します。
		 *	マウスボタンの種類については、 FK_CLI::fk_MouseButton の項目を参照して下さい。
		 *
		 *	以下のコードは、マウス左ボタンが押されているかどうかを検出します。
		 *
		 *		if(Window.GetMouseStatus(fk_MouseButton.MOUSE1, fk_SwitchStatus.PRESS, false) == true) {
		 *			// 押されている場合の処理
		 *		}
		 *	\param[in]		buttonCode		マウスボタンの種類
		 *
		 *	\param[in]	status
		 *		取得したい状態を指定します。
		 *		種類については FK_CLI::fk_SwitchStatus を参照してください。
		 *
		 *	\param[in]	insideFlag
		 *		true だった場合、
		 *		マウスポインタが描画領域の外にあった場合は無条件に false を返します。
		 *		false だった場合は、マウスポインタの位置に関わらず押下状態を返します。
		 *
		 *	\return
		 *		ボタンが status で指定した状態を満たしていれば true を、
		 *		そうでなければ false を返します。
		 */
		bool GetMouseStatus(fk_MouseButton buttonCode, fk_SwitchStatus status, bool insideFlag);
		
		//! マウスカーソル表示制御メソッド
		/*!
		 *	マウスカーソルの表示・非表示と、
		 *	カーソルを画面の中心に移動するか否かを指定します。
		 *	初期状態では、マウスカーソルは表示し、中心移動は無効としています。
		 *
		 *	\param[in]		visible
		 *		true の場合、マウスカーソルを表示します。false の場合は消去します。
		 *
		 *	\param[in]		center
		 *		true の場合、マウスカーソルを画面中心に移動します。
		 *		false の場合は何も行いません。
		 */
		void SetCursorState(bool visible, bool center);


		//! モデルクリック判定メソッド1
		/*!
		 *	マウスでモデルをクリックしているかどうかを判定します。
		 *	引数には判定対象としたいモデルを渡します。1 つずつしか判定できません。
		 *	(モデル, 誤差を許容するピクセル数, X 座標, Y 座標)
		 *	の形式で引数を渡します。
		 *	カーソルがモデルに重なっている場合は true、
		 *	いない場合は false を返します。
		 *
		 *	\param[in]	model	判定対象モデル。
		 *
		 *	\param[in]	pixel	誤差許容ピクセル数。
		 *
		 *	\param[in]	mouseX
		 *		判定対象クリック位置のx座標。
		 *		-1 を指定した場合は、
		 *		現在のマウスポインタ位置の x 座標が対象となります。
		 *
		 *	\param[in]	mouseY
		 *		判定対象クリック位置のy座標。
		 *		-1 を指定した場合や省略した場合は、
		 *		現在のマウスポインタ位置の y 座標が対象となります。
		 *
		 *	\return
		 *		カーソルがモデルに重なっている場合は true、
		 *		いない場合は false を返します。
		 */
		bool IsModelPicked(fk_Model^ model, int pixel, int mouseX, int mouseY);

		//! モデルクリック判定メソッド2
		/*!
		 *	マウスでモデルをクリックしているかどうかを判定します。
		 *	引数には判定対象としたいモデルを渡します。1 つずつしか判定できません。
		 *	現在のカーソル位置を基準に判定します。
		 *	カーソルがモデルに重なっている場合は true、
		 *	いない場合は false を返します。
		 *
		 *	\param[in]	model	判定対象モデル。
		 *
		 *	\param[in]	pixel	誤差許容ピクセル数。
		 *
		 *	\return
		 *		カーソルがモデルに重なっている場合は true、
		 *		いない場合は false を返します。
		 */
		bool IsModelPicked(fk_Model^ model, int pixel);

		//! モデルクリック判定メソッド3
		/*!
		 *	マウスでモデルをクリックしているかどうかを判定します。
		 *	引数には判定対象としたいモデルを渡します。1 つずつしか判定できません。
		 *	現在のカーソル位置を基準に判定します。
		 *	カーソルがモデルに重なっている場合は true、
		 *	いない場合は false を返します。
		 *	本メソッドは、 IsModelPicked(fk_Model^, int) において
		 *	第二引数に 1 を指定した場合と同一の挙動となります。
		 *
		 *	\param[in]	model	判定対象モデル。
		 *
		 *	\return
		 *		カーソルがモデルに重なっている場合は true、
		 *		いない場合は false を返します。
		 */
		bool IsModelPicked(fk_Model^ model);
		
		//! FPS視点的カメラ制御メソッド
		/*!
		 *	FPS 視点のゲーム特有の、マウス移動による視点操作処理を行います。
		 *
		 *	\param[in]	camera		カメラモデル。
		 *	\param[in]	x			横方向の移動に対する回転角度。
		 *	\param[in]	y			縦方向の移動に対する回転角度。
		 *	\param[in]	lockSW
		 *		true の場合、カーソルの中心を固定します。
		 *		false の場合は固定しません。
		 */
		void ProcMouseView(fk_Model^ camera, double x, double y, bool lockSW);
		//@}

		//! \name 投影座標・空間座標変換メソッド
		//@{

		//! 投影平面から任意平面への射影点算出メソッド
		/*!
		 *	このメソッドは、描画領域上の投影座標から、
		 *	任意の平面への射影変換を行い、射影点を求めます。
		 *	これは、投影面上の投影座標とカメラを結ぶ直線と、
		 *	引数として入力された平面の交点を求めるということと同義です。
		 *
		 *	\param[in]	x		投影座標の x 成分
		 *	\param[in]	y		投影座標の y 成分
		 *	\param[in]	plane
		 *		射影先の平面。平面情報の設定については fk_Plane の解説を参照して下さい。
		 *	\param[out]	pos		算出した点の位置ベクトル
		 *
		 *	\return		算出に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa GetProjectPosition(double, double, double, fk_Vector^),
		 *		GetWindowPosition(), fk_Plane
		 */
		bool	GetProjectPosition(double x, double y,
								   fk_Plane^ plane, fk_Vector^ pos);

		//! 投影平面から任意距離での射影点算出メソッド
		/*!
		 *	このメソッドは、描画領域上の投影座標に対し、
		 *	カメラから指定した距離となっている3D空間中の点を算出します。
		 *	これは、投影面上の投影座標とカメラを結ぶ直線と、
		 *	カメラを中心とし指定距離を半径とする球面の交点を求めることと同義です。
		 *
		 *	\param[in]	x		投影座標の x 成分
		 *	\param[in]	y		投影座標の y 成分
		 *	\param[in]	dist	カメラからの空間中の距離
		 *	\param[out]	pos		算出した点の位置ベクトル
		 *
		 *	\return		算出に成功すれば true を、失敗すれば false を返します。
		 */
		bool	GetProjectPosition(double x, double y,
								   double dist, fk_Vector^ pos);

		//! 空間座標から投影座標への射影点算出メソッド
		/*!
		 *	このメソッドは、空間座標から投影座標への射影点を算出します。
		 *	これは、ある空間中の位置が画面上でどこに表示されるかを知ることと同義です。
		 *	投影座標の詳細は fk_Window の概要を参照して下さい。
		 *
		 *	なお、射影点の z 成分は投影における Near 面上の場合 0、
		 *	Far 面上の場合 1 となり、その間は線形補間した値となります。
		 *	つまり、カメラに近いほど値が小さくなるということです。
		 *
		 *	\param[in]	pos_3D		空間座標位置ベクトル
		 *	\param[out]	pos_2D		射影点となる投影座標の位置ベクトル
		 *
		 *	\sa GetProjectPosition(double, double, fk_Plane^, fk_Vector^),
		 *		GetProjectPosition(double, double, double, fk_Vector^),
		 *		fk_Perspective, fk_Ortho, fk_Frustum
		 */
		bool	GetWindowPosition(fk_Vector^ pos_3D, fk_Vector^ pos_2D);
		//@}

#ifndef FK_DOXYGEN_USER_PROCESS
		event fk_DrawCallback^ PreInit;
		event fk_DrawCallback^ PostInit;
		virtual event fk_DrawCallback^ PreDraw;
		virtual event fk_DrawCallback^ PostDraw;
		event fk_DrawCallback^ PreDrawLeft;
		event fk_DrawCallback^ PostDrawLeft;
		event fk_DrawCallback^ PreDrawRight;
		event fk_DrawCallback^ PostDrawRight;

		virtual void OnPreInit()
		{
			PreInit();
		};

		virtual void OnPostInit()
		{
			PostInit();
		};

		virtual void OnPreDraw()
		{
			PreDraw();
		};

		virtual void OnPostDraw()
		{
			PostDraw();
		};

		virtual void OnPreDrawLeft()
		{
			PreDrawLeft();
		};

		virtual void OnPostDrawLeft()
		{
			PostDrawLeft();
		};

		virtual void OnPreDrawRight()
		{
			PreDrawRight();
		};

		virtual void OnPostDrawRight()
		{
			PostDrawRight();
		};

#endif
	};
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
