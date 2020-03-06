/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_WINDOW_HEADER__
#define __FK_WINDOW_HEADER__

#ifndef FK_OLD_NONSUPPORT
//#define FK_OLD_NONSUPPORT
#endif

#include <stdarg.h>
#include <map>

// for Graphics Header.
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Multi_Browser.H>

// for FK Header.
#include <FK/Engine.H>
#include <FK/FrameController.h>

// for Graphics Routine

namespace FK {

	//! 特殊キーを表す列挙型
	enum class fk_Key {
		SHIFT_R,	//!< 右シフトキー
		SHIFT_L,	//!< 左シフトキー
		CTRL_R,		//!< 右コントロールキー
		CTRL_L,		//!< 左コントロールキー
		ALT_R,		//!< 右オルトキー
		ALT_L,		//!< 左オルトキー
		ENTER,		//!< エンター(改行、リターン)キー
		BACKSPACE,	//!< バックスペース(後退)キー
		DEL,		//!< デリート(削除)キー
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
	enum class fk_MouseButton {
		M1,		//!< マウス左クリック(第1ボタン)
		M2,		//!< マウス中クリック、あるいはホイールクリック(第2ボタン)
		M3		//!< マウス右クリック(第3ボタン)
	};

	//! メッセージ出力タイプを表す列挙型
	enum class fk_PutStrMode {
		NONE,			//!< 出力なし
		CONSOLE,		//!< コンソール標準出力
		ERR_CONSOLE,	//!< コンソールエラー出力
		BROWSER,		//!< 専用ブラウザ出力
		FILE			//!< ファイル出力
	};

	//! ボタン系デバイス状態を表す列挙型
	enum class fk_Switch {
		RELEASE,	//!< 離しっぱなしの状態
		UP,			//!< 離した瞬間
		DOWN,		//!< 押した瞬間
		PRESS		//!< 押しっぱなしの状態
	};

	//! FLTK 用シーン描画ウィジェットクラス
	/*!
	 *	このクラスは、FK によるシーンを
	 *	FLTK 用ウィジェットとして作成、制御するための機能を提供します。
	 *
	 *	fk_Window クラスは、FLTK の Fl_Gl_Window の派生クラスとなっています。
	 *	実際にアプリケーションとして表示を行うには、
	 *	Fl_Window によってウィンドウを生成し、
	 *	この fk_Window インスタンスを子ウィジェットとして登録する必要があります。
	 *	具体的な利用方法はユーザーズマニュアルのウィンドウに関する章や、
	 *	サンプルプログラムを参照して下さい。
	 *
	 *	fk_Window クラスが持つ機能は、以下のように多岐に渡ります。
	 *	- シーンの表示
	 *	- デバイスの情報取得やイベントハンドリング
	 *	- フレームレート制御
	 *	- 投影座標と空間座標の変換
	 *	- グラフィックス処理制御
	 *	- 表示画像のファイルへの出力
	 *	- メッセージ出力
	 *	.
	 *	しかし、シーンを表示するのに最低限必要な関数は
	 *	setScene(), drawWindow(), winOpenStatus() の 3 つ
	 *	(と、 Fl::wait() もしくは Fl::check()) のみです。
	 *	その他の関数は、必要に応じて参照して下さい。
	 *
	 *	本クラスの解説では、「投影座標」というものが多く登場します。
	 *	投影座標とは描画領域の左上を原点とし、
	 *	x 軸の正方向を右向き、y 軸の正方向を下向きとする平面座標系のことです。
	 *	数値はピクセル幅となります。
	 *	例えば、描画領域の大きさが (400, 500) であった場合、
	 *	その中心の投影座標は (200, 250)、右上端の投影座標は (400, 0) となります。
	 *
	 *	\sa fk_Scene
	 */

	class fk_Window : public Fl_Gl_Window {

	public:

		//! コンストラクタ
		/*!
		 *	\param[in]	x		描画領域左上位置 x 座標
		 *	\param[in]	y		描画領域左上位置 y 座標
		 *	\param[in]	w		描画領域横幅
		 *	\param[in]	h		描画領域縦幅
		 *	\param[in]	name	ウィジェット名称
		 */
		fk_Window(int x = 0, int y = 0,
				  int w = 300, int h = 300, std::string name = "FK Window");

		//! デストラクタ
		virtual ~fk_Window();


		//! \name シーン制御関数
		///@{

		//! シーン登録関数
		/*!
		 *	シーンを本ウィジェットの描画対象として登録します。
		 *
		 *	\param[in]	scene		シーンインスタンス
		 */
		void	setScene(fk_Scene *scene);
		///@}

		//! \name イベント・デバイス制御関数
		///@{

		//! 描画更新関数
		/*!
		 *	画面の描画を行います。
		 *	この関数を呼ばない限りは、シーン内のモデル状態に変更があっても、
		 *	画面には反映されません。
		 *
		 *	\param[in]	drawFlag
		 *		true の場合、正常に画面を更新します。
		 *		false の場合は、正常に画面更新が行えるかどうかだけの判定を行い、
		 *		実際の画面更新は行いません。
		 *
		 *	\return
		 *		正常に描画が行われた場合 true を、失敗した場合は false を返します。
		 *
		 *	\sa winOpenStatus()
		 */
		int					drawWindow(bool drawFlag = true);

		//! 描画状態取得関数
		/*!
		 *	drawWindow() を呼んだ後、実際に描画が適切に行われているかどうかを参照します。
		 *
		 *	\return
		 *		適切に描画が行われていた場合は true を、
		 *		行われなかった場合は false を返します。
		 *
		 *	\sa drawWindow()
		 */
		bool	winOpenStatus(void);

		//! 描画領域寸法変更関数
		/*!
		 *	描画領域の位置と大きさを変更します。
		 *
		 *	\param[in]	x		描画領域左上位置 x 座標
		 *	\param[in]	y		描画領域左上位置 y 座標
		 *	\param[in]	w		描画領域横幅
		 *	\param[in]	h		描画領域縦幅
		 */
		void	resizeWindow(int x, int y, int w, int h);

		//! 標準キー状態取得関数
		/*!
		 *	指定したキーの現在の押下状態を参照します。
		 *	例えば、「a」キーが押されているかどうかを調べる場合は、
		 *	以下のようなコードを記述します。
		 *
		 *		fk_Window		win;
		 *
		 *		if(win.getKeyStatus('a', fk_Switch::PRESS, true) == true) {
		 *			// 押されている場合の処理
		 *		}
		 *
		 *	特殊キーの状態については、 getSpecialKeyStatus() を用いてください。
		 *
		 *	\param[in]	key
		 *		キーを表す文字。ここには、スペース(' ') や数字 ('1') なども含みます。
		 *
		 *	\param[in]	status
		 *		取得したい状態を指定します。種類については fk_Switch を参照してください。
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
		 *		(特殊キーを含む)多くのキーが同時に押さえられている場合、
		 *		正確な情報を返さない場合があります。
		 *		キーの同時押下許容数は、ハードウェアや OS によって異なってきます。
		 *
		 *	\sa getSpecialKeyStatus()
		 */
		bool getKeyStatus(char key, fk_Switch status, bool insideFlag = true);
	
		//! 特殊キー状態取得関数
		/*!
		 *	指定した特殊キーの現在の押下状態を参照します。
		 *	例えば、右矢印キーが押されているかどうかを調べる場合は、
		 *	以下のようなコードを記述します。
		 *
		 *		fk_Window		win;
		 *
		 *		if(win.getSpecialKeyStatus(fk_Key::RIGHT, true) == true) {
		 *			// 押されている場合の処理
		 *		}
		 *
		 *	特殊キーの種類については、 ::fk_Key の項目を参照して下さい。
		 *
		 *	標準キーの状態については、 getKeyStatus() を用いてください。
		 *
		 *	\param[in]	key
		 *		キーを表す文字。
		 *
		 *	\param[in]	status
		 *		取得したい状態を指定します。種類については ::fk_Switch を参照してください。
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
		 *		(標準キーを含む)多くのキーが同時に押さえられている場合、
		 *		正確な情報を返さない場合があります。
		 *		キーの同時押下許容数は、ハードウェアや OS によって異なってきます。
		 *
		 *	\sa getKeyStatus()
		 */
		bool	getSpecialKeyStatus(fk_Key key,
									fk_Switch status, bool insideFlag = true);

#ifndef FK_DOXYGEN_USER_PROCESS
		bool	getKeyStatus(char key, bool insideFlag = true);
		bool	getSpecialKeyStatus(fk_Key key, bool insideFlag = true);
#endif

		//! 最終押下キー取得関数
		/*!
		 *	最後に押された標準キーを取得します。
		 *	ここで「押された」というのは、いわゆる「押し始めた瞬間」のことを指します。
		 *	例えば、以下のような順番でキー操作を行ったとします。
		 *	-#	「a」キーを押さえっぱなしにする。
		 *	-#	さらに「b」キーを押さえっぱなしにする。
		 *	-#	「b」キーを離す。
		 *	-#	「a」キーを離す。
		 *	.
		 *	この場合、最後まで押さえられていたのは「a」キーとなりますが、
		 *	「押し始めた瞬間」は「b」キーの方が後であるため、
		 *	getLastKey() は「b」を返すことになります。
		 *
		 *	\return
		 *		最後に押されたキーのアスキーコード。
		 *		アプリケーションが起動されてから、
		 *		一度もキーが押されていない場合は 0 を返します。
		 */
		char	getLastKey(void);

		//! マウスポインタ位置取得関数
		/*!
		 *	現在のマウスポインタの位置を与えられた引数ポインタに格納します。
		 *	コード例は以下の通りです。
		 *
		 *		fk_Window		win;
		 *
		 *		auto [x, y] = win.getMousePosition(true);
		 *
		 *	格納される値は投影座標となります。
		 *	投影座標の詳細は本クラスの概要を参照して下さい。
		 *
		 *	\param[in]		insideFlag
		 *		true の場合は、もしマウスポインタが描画領域の外側にあった場合は
		 *		x, y の両方に -1 を格納します。
		 *		false の場合は、描画領域の内外に関係なく、
		 *		投影座標に従って値を格納します。
		 *		この場合、マウスポインタが描画領域の左側や上側にあった場合は、
		 *		負の値が x や y に格納されることがありえることを意味しますので、
		 *		注意が必要です。
		 *
		 *	\return
		 *		マウスポインタの x, y 座標がそれぞれ第1,2要素に入ります。
		 *		型は int 型となります。
		 *
		 *	\sa getMouseStatus(), getMouseWheelStatus(),
		 */
		std::tuple<int, int> getMousePosition(bool insideFlag = true);

#ifndef FK_OLD_NONSUPPORT
#ifndef FK_DOXYGEN_USER_PROCESS
		void getMousePosition(int *, int *, bool = true);
#endif
#endif
		
		//! マウスボタン状態取得関数
		/*!
		 *	指定したマウスボタンの現在の押下状態を参照します。
		 *	例えば、左マウスボタンが押されているかどうかを調べる場合は、
		 *	以下のようなコードを記述します。
		 *
		 *		fk_Window		win;
		 *
		 *		if(win.getMouseStatus(fk_MouseButton::M1, fk_Switch::PRESS) == true) {
		 *			// 押されている場合の処理
		 *		}
		 *
		 *	マウスボタンの種類については、 ::fk_MouseButton の項目を参照して下さい。
		 *
		 *	\param[in]	button		マウスボタンの種類
		 *
		 *	\param[in]	status
		 *		取得したい状態を指定します。種類については ::fk_Switch を参照してください。
		 *
		 *	\param[in]	insideFlag
		 *		true だった場合、
		 *		マウスポインタが描画領域の外にあった場合は無条件に false を返します。
		 *		false だった場合は、マウスポインタの位置に関わらず押下状態を返します。
		 *
		 *	\return
		 *		キーが status で指定した状態を満たしていれば true を、
		 *		そうでなければ false を返します。
		 */
		bool	getMouseStatus(fk_MouseButton button, fk_Switch status,
							   bool insideFlag = true);

#ifndef FK_DOXYGEN_USER_PROCESS
		bool	getMouseStatus(fk_MouseButton button, bool insideFlag = true);
#endif

		//! マウスホイール回転量取得関数
		/*!
		 *	この関数は、ウスホイールの回転量を取得するときに使用します。
		 *	返り値は整数で、正の場合は手前側、負の場合は奥側に回転していることを意味します。
		 *	数値の単位は、テキストをスクロールさせた場合の「行数」に相当するものです。
		 *
		 *	この関数の回転量とは、この関数が以前に呼び出してからのホイール回転量を意味します。
		 *	従って、最初に呼び出したときは必ず 0 を返すことになります。
		 *	また、一度この関数で回転量を取得した後、
		 *	drawWindow() 関数を実行しない限りは常に 0 を返す仕様となっています。
		 *
		 *	\return		回転量
		 *
		 *	\sa getMousePosition(), getMouseStatus()
		 */
		int		getMouseWheelStatus(void);
		///@}

		//! \name フレームレート制御関数
		///@{

		/*!
		 *	drawWindow() をコールした際に調整する FPS を指定します。
		 *	FPS(Frame Per Second)とは、1秒間中で画面更新が行われる回数の単位です。
		 *	この値を 0 に設定した場合は、FPS制御を行いません。
		 *	デフォルトは 0 です。
		 *
		 *	\param[in]		fps		FPS値
		 */
		void	setFPS(int fps);

		///@}

		//! \name 投影座標・空間座標変換関数
		///@{

		//! 投影平面から任意平面への射影点算出関数
		/*!
		 *	この関数は、描画領域上の投影座標から、
		 *	任意の平面への射影変換を行い、射影点を求めます。
		 *	これは、投影面上の投影座標とカメラを結ぶ直線と、
		 *	引数として入力された平面の交点を求めるということと同義です。
		 *	投影座標の詳細は本クラスの概要を参照して下さい。
		 *
		 *	\param[in]	x		投影座標の x 成分
		 *	\param[in]	y		投影座標の y 成分
		 *	\param[in]	plane	射影先の平面。
		 *
		 *	\return
		 *		第1要素は、算出に成功すれば true が、失敗すれば false が入ります。
		 *		第2要素は算出した点の位置ベクトルが入ります。
		 *		失敗した場合の第2要素の値は未定義です。
		 *
		 *	\sa getProjectPosition(double, double, double),
		 *		getWindowPosition(), fk_Plane
		 */
		std::tuple<bool, fk_Vector> getProjectPosition(double x, double y, fk_Plane &plane);

#ifndef FK_OLD_NONSUPPORT
#ifndef FK_DOXYGEN_USER_PROCESS
		bool	getProjectPosition(double x, double y,
								   fk_Plane *plane, fk_Vector *pos);
#endif
#endif
		//! 投影平面から任意距離での射影点算出関数
		/*!
		 *	この関数は、描画領域上の投影座標に対し、
		 *	カメラから指定した距離となっている3D空間中の点を算出します。
		 *	これは、投影面上の投影座標とカメラを結ぶ直線と、
		 *	カメラを中心とし指定距離を半径とする球面の交点を求めることと同義です。
		 *	投影座標の詳細は本クラスの概要を参照して下さい。
		 *
		 *	\param[in]	x		投影座標の x 成分
		 *	\param[in]	y		投影座標の y 成分
		 *	\param[in]	dist	カメラからの空間中の距離
		 *
		 *	\return
		 *		第1要素は、算出に成功すれば true が、失敗すれば false が入ります。
		 *		第2要素は算出した点の位置ベクトルが入ります。
		 *		失敗した場合の第2要素の値は未定義です。
		 */
		std::tuple<bool, fk_Vector> getProjectPosition(double x, double y, double dist);

#ifndef FK_OLD_NONSUPPORT
#ifndef FK_DOXYGEN_USER_PROCESS
		bool	getProjectPosition(double x, double y,
								   double dist, fk_Vector *pos);
#endif
#endif
		//! 空間座標から投影座標への射影点算出関数
		/*!
		 *	この関数は、空間座標から投影座標への射影点を算出します。
		 *	これは、ある空間中の位置が画面上でどこに表示されるかを知ることと同義です。
		 *	投影座標の詳細は本クラスの概要を参照して下さい。
		 *
		 *	なお、射影点の z 成分は投影における Near 面上の場合 0、
		 *	Far 面上の場合 1 となり、その間は線形補間した値となります。
		 *	つまり、カメラに近いほど値が小さくなるということです。
		 *
		 *	\param[in]	pos_3D		空間座標位置ベクトル
		 *
		 *	\return
		 *		第1要素は、算出に成功すれば true が、失敗すれば false が入ります。
		 *		第2要素は算出した射影点の位置ベクトルが入ります。
		 *		失敗した場合の第2要素の値は未定義です。
		 *
		 *	\sa getProjectPosition(double, double, fk_Plane &),
		 *		getProjectPosition(double, double, double),
		 *		fk_Perspective, fk_Ortho, fk_Frustum
		 */
		std::tuple<bool, fk_Vector> getWindowPosition(fk_Vector &pos_3D);

#ifndef FK_OLD_NONSUPPORT
#ifndef FK_DOXYGEN_USER_PROCESS
		bool	getWindowPosition(fk_Vector, fk_Vector *);
#endif
#endif
		///@}

		//! \name シェーダー対応設定用関数
		///@{

		//! 初期化前処理関数
		/*!
		 *	この関数は、グラフィックスシステムの初期化処理において、
		 *	処理前に自動的にシステム内部から呼び出される関数です。
		 *	fk_Window クラスの派生クラスを作成し、
		 *	そのクラスにおいて本関数を再定義することによって、
		 *	グラフィックスシステム初期化時の処理を追加することが可能です。
		 *	代表的な用途として、特殊デバイスの初期化処理などがあります。
		 *
		 *	\sa postInit(), preDraw(), postDraw()
		 */
		virtual void	preInit(void) {}

		//! 初期化後処理関数
		/*!
		 *	この関数は、グラフィックスシステムの初期化処理において、
		 *	処理後に自動的にシステム内部から呼び出される関数です。
		 *	fk_Window クラスの派生クラスを作成し、
		 *	そのクラスにおいて本関数を再定義することによって、
		 *	グラフィックスシステム初期化時の処理を追加することが可能です。
		 *	代表的な用途として、特殊デバイスの初期化処理などがあります。
		 *
		 *	\sa preInit(), preDraw(), postDraw()
		 */
		virtual void	postInit(void) {}

		//! 描画前処理関数
		/*!
		 *	この関数は、グラフィックスシステムの描画処理において、
		 *	描画前に自動的にシステム内部から呼び出される関数です。
		 *	fk_Window クラスの派生クラスを作成し、
		 *	そのクラスにおいて本関数を再定義することによって、
		 *	グラフィックスシステム毎描画時の処理を追加することが可能です。
		 *	代表的な用途として、特殊デバイスの情報取得などがあります。
		 */
		virtual void	preDraw(void) {}

		//! 描画後処理関数
		/*!
		 *	この関数は、グラフィックスシステムの描画処理において、
		 *	描画後に自動的にシステム内部から呼び出される関数です。
		 *	fk_Window クラスの派生クラスを作成し、
		 *	そのクラスにおいて本関数を再定義することによって、
		 *	グラフィックスシステム毎描画時の処理を追加することが可能です。
		 *	代表的な用途として、特殊デバイスの情報取得などがあります。
		 */
		virtual void	postDraw(void) {}
		///@}

#ifndef FK_DOXYGEN_USER_PROCESS
		virtual void	preDrawLeft(void) {}
		virtual void	postDrawLeft(void) {}
		virtual void	preDrawRight(void) {}
		virtual void	postDrawRight(void) {}

		std::list<fk_funcSet>	preDrawList;
		std::list<fk_funcSet>	postDrawList;
#endif

		//! \name 描画画像取り込み関数
		///@{

		//! 描画画像ファイル出力関数
		/*!
		 *	この関数は、描画領域に表示されている画像を、画像ファイルとして出力します。
		 *
		 *	\param[in]	fileName	画像ファイル名
		 *	\param[in]	format
		 *		画像ファイルのフォーマット。
		 *		現在利用可能なフォーマットは、
		 *		fk_ImageType の解説を参照して下さい。
		 *	\param[in]	mode
		 *		画像の取込先となるグラフィックスデバイス名。
		 *		取り込みがうまく動作しない場合は、
		 *		この引数の値を変更してください。
		 *
		 *	\return
		 *		出力に成功すれば true を、失敗すれば false を返します。
		 */
		bool	snapImage(std::string fileName,
						  fk_ImageType format = fk_ImageType::BMP,
						  fk_SnapProcMode mode = fk_SnapProcMode::FRONT);

		//! 描画画像データ出力関数
		/*!
		 *	この関数は、描画領域に表示されている画像を、
		 *	fk_Image 型のインスタンスに出力します。
		 *
		 *	\param[in]	image		画像データ出力先インスタンス
		 *	\param[in]	mode
		 *		画像の取込先となるグラフィックスデバイス名。
		 *		取り込みがうまく動作しない場合は、
		 *		この引数の値を変更してください。
		 *
		 *	\return
		 *		出力に成功すれば true を、失敗すれば false を返します。
		 */
		bool	snapImage(fk_Image *image,
						  fk_SnapProcMode mode = fk_SnapProcMode::FRONT);
		///@}

		//! \name 時間参照関数
		///@{

		//! 現時点システム時間参照関数
		/*!
		 *	この関数は、呼んだ時点でのシステム時間を取得します。
		 *	システム時間の定義は実行プラットフォームによって意味が異なりますが、
		 *	どのプラットフォームでも単位はミリ秒です。
		 *
		 *	\note
		 *		本関数は static 関数なので、
		 *		以下のように記述することでインスタンスの生成なしに利用することができます。
		 *
		 *			unsigned long nowTime = fk_Window::getNow();
		 *
		 *	\return		現在のシステム時間
		 */
		static unsigned long	getNow(void);
		///@}

		//! \name メッセージ出力制御関数
		///@{

		//! メッセージ出力モード設定関数
		/*!
		 *	この関数は、メッセージ出力のモードを設定します。
		 *	モードには、以下のようなものがあります。
		 *	- fk_PutStrMode::BROWSER:
		 *		メッセージ出力用ブラウザに出力します。デフォルトはこの値となっています。
		 *	- fk_PutStrMode::CONSOLE:
		 *		コンソールの標準出力に出力します。
		 *	- fk_PutStrMode::ERR_CONSOLE:
		 *		コンソールのエラー出力に出力します。
		 *	- fk_PutStrMode::FILE: setPutFile() 関数で指定したファイルに出力します。
		 *	- fk_PutStrMode::NONE: 出力を行いません。
		 *
		 *	\note
		 *		本関数は static 関数なので、
		 *		以下のように記述することでインスタンスの生成なしに利用することができます。
		 *
		 *			fk_Window::setPutStrMode(fk_PutStrMode::CONSOLE);
		 *
		 *	\param[in]	mode	出力モード
		 *
		 *	\sa getPutStrMode(), setPutFile(), putString(),
		 *		printf(), clearBrowser()
		 */
		static void				setPutStrMode(const fk_PutStrMode mode);

		//! メッセージ出力モード参照関数
		/*!
		 *	この関数は、メッセージ出力のモードを取得します。
		 *
		 *	\return		出力モード
		 *
		 *	\sa setPutStrMode()
		 */
		static fk_PutStrMode	getPutStrMode(void);

		//! メッセージ出力用ファイル設定関数
		/*!
		 *	この関数は、メッセージ出力のモードにおいてファイル出力
		 *	(fk_PutStrMode::FILE) を指定したときの、出力ファイル名を設定するものです。
		 *
		 *	\note
		 *		本関数は static 関数なので、
		 *		以下のように記述することでインスタンスの生成なしに利用することができます。
		 *
		 *			fk_Window::setPutFile("sample.txt");
		 *
		 *	\param[in]	fileName		出力ファイル名
		 *
		 *	\return
		 *		設定に成功すれば true を、失敗すれば false を返します。
		 *
		 *	\sa setPutStrMode(), putString(), printf()
		 */
		static bool				setPutFile(const std::string &fileName);

		//! メッセージ出力文字列設定関数
		/*!
		 *	この関数は、与えられた文字列をメッセージとして出力を行います。
		 *	出力先は、 setPutStrMode() によって設定したものとなります。
		 *
		 *	\note
		 *		本関数は static 関数なので、
		 *		以下のように記述することでインスタンスの生成なしに利用することができます。
		 *
		 *			fk_Window::putString("sample");
		 *
		 *	\param[in]	str		出力文字列
		 *
		 *	\sa setPutStrMode(), setPutFile(), printf(), clearBrowser()
		 */
		static void				putString(const std::string &str);

#ifndef FK_CLI_CODE
		//! メッセージ出力書式付き設定関数
		/*!
		 *	この関数は、与えられたフォーマットに従ってメッセージとして出力します。
		 *	この関数の引数は、C や C++ における標準関数である printf に準じます。
		 *
		 *	\note
		 *		本関数は static 関数なので、
		 *		以下のように記述することでインスタンスの生成なしに利用することができます。
		 *
		 *			int		i = 10;
		 *
		 *			fk_Window::printf("i = %d", i);
		 *
		 *	\sa setPutStrMode(), setPutFile(), putString(), clearBrowser()
		 */
		static void				printf(const char *format, ...);
#endif

		//! メッセージ出力用ブラウザ初期化関数
		/*!
		 *	この関数は、メッセージ出力における出力用ブラウザに対し、
		 *	表示の初期化を行います。
		 *	この関数を呼ぶ前に表示されていた文字列は全て削除されます。
		 *
		 *	\note
		 *		本関数は static 関数なので、
		 *		以下のように記述することでインスタンスの生成なしに利用することができます。
		 *
		 *			fk_Window::clearBrowser()
		 *
		 *	\sa setPutStrMode(), putString(), printf()
		 */
		static void				clearBrowser(void);
		///@}

#ifndef FK_DOXYGEN_USER_PROCESS
		//! \name 立体視モード制御関数
		///@{

		//! 立体視モード設定関数
		/*!
		 *	ウィンドウに対して立体視モードを設定します。
		 *	デフォルトでは無効になっています。
		 *
		 *	\note
		 *		このシステムにおける立体視画像出力は、OpenGL の標準拡張機能を利用します。
		 *		Direct3D 版では利用できないので注意してください。
		 *		立体視を利用するには、Quad Buffer をサポートしているグラフィックカードが必須です。
		 *		本プロジェクトで動作を確認しているのは NVIDIA 社の Quadro シリーズのみです。
		 *		対応していない環境で立体視モードを有効にしようとした場合は、
		 *		モードを変更せずに関数の処理が終了します。
		 *		モード切替が成功したかどうかは、後述する関数 getOGLStereoMode()で判定してください。
		 *
		 *	\param[in]	mode
		 *		true だった場合、立体視モードを有効にします。
		 *		false だった場合、立体視モードを無効にします。
		 *		いずれの動作においても、OpenGL の動作モードの再設定が行われます。
		 *
		 *	\sa fk_DisplayLink, getOGLStereoMode()
		 */
		void	setOGLStereoMode(bool mode);

		//! 立体視モード取得関数
		/*!
		 *	ウィンドウの現在の立体視モードを取得します。
		 *
		 *	\note
		 *		この関数は OpenGL 環境においてのみ有効です。
		 *		Direct3D 版においては意味のある値を返しません。
		 *
		 *	\return
		 *		true だった場合、立体視モードが有効になっています。
		 *		false だった場合、立体視モードが無効になっています。
		 *
		 *	\sa fk_DisplayLink, setOGLStereoMode()
		 */
		bool	getOGLStereoMode(void);
		///@}
#endif

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_GraphicsEngine * GetEngine(void);
#endif
		
	private:

		fk_Image				snapBuffer;

		bool					winOpenFlag;
		int						GLWinWSize;
		int						GLWinHSize;
		int						GLWinXPosition;
		int						GLWinYPosition;
		char					lastKey;

		std::map<char, bool>			keyStatus;
		std::map<fk_Key, bool>	specialKeyStatus;
		std::map<fk_MouseButton, bool>	mouseStatus;
	
		double					frameTime, prevTime;
		double					frameInterval;
		int						skipCount;

		fk_FrameController		fps_admin;
		int						fps;

		bool					stereoMode;


		static Fl_Window		*putWin;
		static Fl_Multi_Browser	*browser;
		static fk_PutStrMode	putStrMode;
		static std::ofstream	putStrOFS;
		static int				winNum;

		static Fl_Window		*error_win;
		static Fl_Multi_Browser	*err_browser;

		bool					IsInsideWindow(void);
		Fl_Group *				GetInhParentWindow(void);
		void					PushPrevStatus(void);
	
		void					draw();	// virtual Function from Fl_Gl_Window class

		static void				PutBrowser(const std::string &);

#ifdef WIN32
		bool					SnapImageGDI(fk_Image *);
#endif
		static void				ErrorInit(void);

	protected:

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_GraphicsEngine		engine;

		void					drawScene(void);
		void					drawSceneLeft(void);
		void					drawSceneRight(void);
#endif

	};
}

#endif /* !__FK_WINDOW_HEADER__ */


