#ifndef __FK_INPUT_HEADER__
#define __FK_INPUT_HEADER__

#if defined(WIN32) && !defined(_MINGW_)
#define DIRECTINPUT_VERSION		DIRECTINPUT_HEADER_VERSION

#include <DX/dinput.h>
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#else

#ifndef FK_DOXYGEN_USER_PROCESS
#ifndef _MINGW_

struct POINT
{
	long  x;
	long  y;
};
using DWORD = unsigned long;
using HRESULT = long;
using HINSTANCE = int*;
using HWND = int*;

#else

#include <Fl/x.h>

#endif // !_MINGW_
#endif // !FK_DOXYGEN_USER_PROCESS
#endif // WIN32 && !_MINGW_

#include <map>
#include <vector>
#include "Misc.h"

namespace FK {

	//! ゲームパッドの入力を受け取るための構造体
	/*!
	 *	fk_Input クラスのメンバ関数である
	 *	fk_Input::getJoyStick() や fk_Input::getInputStatus() により、
	 *	現在のゲーム用デバイスの状態を得るためのデータ用構造体です。
	 *
	 *	\sa fk_Input
	 */
	struct fk_InputInfo {
		//! 各ボタン押下状況配列
		/*!
		 *	配列内に各ボタンの押下状況を格納します。
		 *	押されている場合は true が、
		 *	押されていない場合は false が格納されています。
		 */
		bool	button[32];

		//! 左スティック上方向状況変数
		/*!
		 *	左スティック(または方向キー)のおいて、
		 *	現在どの方向に示されているかを格納します。
		 *	上下左右それぞれが up, down, left, right
		 *	の各変数に対応し、示されている場合は true が、
		 *	示されていない場合は false が格納されています。
		 */
		bool	up;

		//! 左スティック下方向状況変数
		/*!
		 *	up の解説を参照して下さい。
		 */
		bool	down;

		//! 左スティック左方向状況変数
		/*!
		 *	up の解説を参照して下さい。
		 */
		bool	left;

		//! 左スティック上方向状況変数
		/*!
		 *	up の解説を参照して下さい。
		 */
		bool	right;

		//! アナログスティック状況変数 (x 座標値)
		/*!
		 *	ジョイスティックやアナログスティックが現在示している座標を格納します。
		 *	通常は (x[0], y[0])が左スティック、
		 *	(x[1], y[1]) が右スティックのアナログ値を示します。
		 *	360コントローラの場合は、
		 *	(x[2], y[2]) が右スティックのアナログ値で、
		 *	x[1] が LT(+), RT(-) の押し込み値を示します。
		 */
		short	x[3];

		//! アナログスティック状況変数 (y 座標値)
		/*!
		 *	x の解説を参照して下さい。
		 */
		short	y[3];

		//! ハットスイッチ状況変数
		/*!
		 *	ハットスイッチ(POV)が現在示している数値を格納します。
		 *	未入力状態の場合は -1、真上の場合は 0 とし、
		 *	時計回りに度数法値に100を掛けた数値が格納されます。
		 *	たとえば右側を示す場合は 9000 が、左側であれば 27000 が入ります。
		 */
		int		pov;
	};

	//! ゲームデバイスでの仮想空間軸方向を表す列挙型
	enum fk_AxisDirection {
		FK_AXIS1_X = 1,	//!<	fk_InputInfo::x[0] に対応
		FK_AXIS1_Y,		//!<	fk_InputInfo::y[0] に対応
		FK_AXIS2_X,		//!<	fk_InputInfo::x[1] に対応
		FK_AXIS2_Y,		//!<	fk_InputInfo::y[1] に対応
		FK_AXIS3_X,		//!<	fk_InputInfo::x[2] に対応
		FK_AXIS3_Y		//!<	fk_InputInfo::y[2] に対応
	};

	//! ゲームデバイスでのスティックデバイス軸方向を表す列挙型
	enum fk_RawAxis {
		FK_AXIS_X_POS = 0,	//!<	左スティック x 軸正方向
		FK_AXIS_X_NEG,		//!<	左スティック x 軸逆方向
		FK_AXIS_Y_POS,		//!<	左スティック y 軸正方向
		FK_AXIS_Y_NEG,		//!<	左スティック y 軸逆方向
		FK_AXIS_Z_POS,		//!<	左スティック z 軸正方向
		FK_AXIS_Z_NEG,		//!<	左スティック z 軸逆方向
		FK_AXIS_RX_POS,		//!<	右スティック x 軸正方向
		FK_AXIS_RX_NEG,		//!<	右スティック x 軸逆方向
		FK_AXIS_RY_POS,		//!<	右スティック y 軸正方向
		FK_AXIS_RY_NEG,		//!<	右スティック y 軸逆方向
		FK_AXIS_RZ_POS,		//!<	右スティック z 軸正方向
		FK_AXIS_RZ_NEG		//!<	右スティック z 軸逆方向
	};

#ifdef FKUT_INPUT

#define AXIS1_X FK_AXIS1_X
#define AXIS1_Y FK_AXIS1_Y
#define AXIS2_X FK_AXIS2_X
#define AXIS2_Y FK_AXIS2_Y
#define AXIS3_X FK_AXIS3_X
#define AXIS3_Y FK_AXIS3_Y
#define AXIS_X_POS FK_AXIS_X_POS
#define AXIS_X_NEG FK_AXIS_X_NEG
#define AXIS_Y_POS FK_AXIS_Y_POS
#define AXIS_Y_NEG FK_AXIS_Y_NEG
#define AXIS_Z_POS FK_AXIS_Z_POS
#define AXIS_Z_NEG FK_AXIS_Z_NEG
#define AXIS_RX_POS FK_AXIS_RX_POS
#define AXIS_RX_NEG FK_AXIS_RX_NEG
#define AXIS_RY_POS FK_AXIS_RY_POS
#define AXIS_RY_NEG FK_AXIS_RY_NEG
#define AXIS_RZ_POS FK_AXIS_RZ_POS
#define AXIS_RZ_NEG FK_AXIS_RZ_NEG

#endif
}

#include <stdio.h>

namespace FK {

	//! ゲームパッド・ジョイスティック系デバイス制御クラス
	/*!
	 *	このクラスは、ゲームコントローラーやジョイスティックなどの、
	 *	ゲーム専用デバイスを制御するためのクラスです。
	 *	単にデバイスの状況を取得するだけでなく、
	 *	デバイス中のボタンやスティックなどをキーボードで代替するための機能も備えています。
	 *	なお、本クラスは標準ヘッダには追加されていないため、
	 *	利用の際にはプログラムの先頭部分で、
	 *	以下のように FK.h を include した後に Input.h も include します。
	 *
	 *		#include <FK/FK.h>
	 *		#include <FK/Input.h>
	 *
	 *	以降、本クラスの説明ではゲーム専用デバイスを単に「デバイス」と呼称します。
	 *
	 *	\sa fk_InputInfo
	 *
	 *	\attention
	 *		本クラスは、Windows プラットフォームでしか利用できません。
	 *		また、利用の際には事前に DirectX SDK をインストールする必要があります。
	 *		さらに、本クラスを用いて作成した実行ファイルを実行するには、
	 *		開発時で用いたものと同一バージョンの DirectX がインストールされている必要があります。
	 */
	class fk_Input : public Noncopyable {
	public:
		//! コンストラクタ
		fk_Input(void);
		//! デストラクタ
		~fk_Input(void);

#ifndef FK_DOXYGEN_USER_PROCESS
		// Obsolute Functions
		// マウス関連
		POINT&	GetMouseLocalPos(void);
		POINT&	GetMouseWorldPos(void);
		bool	GetMouseButton(DWORD keycode);
		bool	GetLastMouseButton(DWORD keycode);
		int		GetMouseWheel(void);
		// キー関連
		bool	GetKey(const DWORD keycode);

#endif
		//! \name	基本処理関数
		//@{

		//! 初期化関数
		/*!
		 *	デバイス処理の初期化を行います。
		 *	最初に必ず1回呼ぶ必要があります。
		 *	その際、 Fl_Window (またはその派生クラス)のインスタンスにおいて、
		 *	Fl_Window::show() を呼んだ後に呼ぶ必要があります。
		 *
		 *	\param[in]	hinst
		 *		ここは「fl_display」と入力して下さい。
		 *
		 *	\param[in]	hwnd
		 *		ここは、Fl_Window (またはその派生クラス)のインスタンスの変数名を win としたとき、
		 *		「fl_xid(&win)」と入力して下さい。
		 *
		 *	\return
		 *		初期化に成功した場合 S_OK を、失敗した場合はそれ以外の値が返ります。
		 */
		HRESULT init(HINSTANCE hinst, HWND hwnd);

		//! 完了処理関数
		/*!
		 *	デバイスの完了処理を行います。デストラクタで自動的に呼ばれるので、
		 *	通常はユーザが直接利用することはありません。
		 *
		 *	\return
		 *		完了処理に成功すれば S_OK を、失敗すれば別の値を返します。
		 */
		HRESULT uninit(void);

		//! 更新処理
		/*!
		 *	現在のデバイス情報を更新します。
		 *	通常は描画処理毎に呼ぶことを想定しています。
		 *
		 *	\return
		 *		取得に成功すれば S_OK を、失敗すれば別の値を返します。
		 */
		HRESULT update(void);
		//@}

		//! \name	情報取得関数
		//@{

		//!	デバイス個数取得関数
		/*!
		 *	init() した時点で認識したデバイスの個数を取得します。
		 *	init() されてから抜き差しがあっても関知できません。
		 *
		 *	\return
		 *		認識した個数を返します。
		 */
		DWORD	getJoyCount(void);

		//!	デバイス情報取得関数
		/*!
		 *	デバイスの現在の入力状況を取得します。
		 *	得られる情報は以下の通りです。
		 *		- 各ボタンの押下状況。
		 *		- 左スティックの方向。
		 *		- 各アナログスティックの座標値。
		 * 		- ハットスイッチ(POV)の数値。
		 *
		 *	詳細は fk_InputInfo を参照して下さい。
		 *	この関数は、(getInputStatus() と違い)返値がポインタであることに注意して下さい。
		 *
		 *	\param[in]	index
		 *		デバイスのID。1個目が「0」となります。
		 *
		 *	\return
		 *		デバイス状況が格納された fk_InputInfo 型のポインタ。
		 *		引数で無効なデバイス番号が指定された場合は nullptr を返します。
		 *
		 *	\note
		 *		setButtonSwap() や setAxisToButton() によってボタンや軸を入れ替えていた場合、
		 *		入れ替えを反映した情報を取得します。しかし、
		 *		setKeyAssign(), setAxisAssign(), setPOVAssign()
		 *		といったキーボードの代替操作については、本関数においては反映されません。
		 *		キーボードと処理を一本化したい場合は getInputStatus() を使用して下さい。
		 *
		 *	\sa fk_InputInfo, getInputStatus()
		 */
		fk_InputInfo*	getJoyStick(DWORD index);

		//!	キーボード考慮デバイス情報取得関数
		/*!
		 *	デバイスの現在の入力状況を取得します。
		 *	得られる情報は以下の通りです。
		 *		- 各ボタンの押下状況。
		 *		- 左スティックの方向。
		 *		- 各アナログスティックの座標値。
		 * 		- ハットスイッチ(POV)の数値。
		 *
		 *	詳細は fk_InputInfo を参照して下さい。
		 *	この関数は、(getJoyStick() と違い)返値がポインタではないことに注意して下さい。
		 *
		 *	本関数は getJoyStick() とは異なり、
		 *	setKeyAssign(), setAxisAssign(), setPOVAssign()
		 *	によるキーボード代替設定が有効となります。
		 *	引数に 0 を入力し、さらにデバイスが接続されていなかった場合、
		 *	キーボードによる代替操作の状況を取得します。
		 *	デバイスが接続されている場合はデバイスの状況を取得します。
		 *
		 *	\param[in]	index
		 *		デバイスのID。
		 *		0 を指定し、かつデバイスが接続されてない場合は、
		 *		キーボードの代替操作状況を取得します。
		 *
		 *	\return
		 *		現在のデバイス状況。
		 *
		 *	\note
		 *		setButtonSwap() や setAxisToButton() によってボタンや軸を入れ替えていた場合、
		 *		入れ替えを反映した情報を取得します。
		 *		また、デバイスが接続されていない場合で、
		 *		キーボードの代替操作を無視したい場合は getJoyStick() を利用して下さい。
		 *
		 *	\sa fk_InputInfo, getJoyStick()
		 */
		fk_InputInfo	getInputStatus(int index = 0);

		//@}

		//! アナログデバイス調整関数
		//@{

		//!	スティック閾値設定関数1
		/*!
		 *	この関数は、左スティックを十字キーの代わりに用いる場合に、
		 *	どの程度倒したらその方向への入力と見なすかを設定するものです。
		 *	値の範囲は最小値が 0、最大値が 1000 で、初期値は 500 となっています。
		 *
		 *	\param[in]	index	デバイスのID。
		 *	\param[in]	borderX	横方向の閾値。
		 *	\param[in]	borderY	縦方向の閾値。
		 *
		 *	\sa fk_InputInfo, setMinMax(int, int, int)
		 */
		void			setBorder(int index, int borderX, int borderY);

		//!	スティック閾値設定関数2
		/*!
		 *	この関数は、左アナログスティックを十字キーの代わりに用いる場合に、
		 *	どの程度倒したらその方向への入力と見なすかを設定するものです。
		 *	値の範囲は最小値が 0、最大値が 1000 で、初期値は 500 となっています。
		 *	本関数は ID が 0 であるデバイスの閾値を設定しますが、
		 *	任意のデバイスの閾値を設定したい場合は setBorder(int, int, int) を用いて下さい。
		 *
		 *	\param[in]	borderX	横方向の閾値。
		 *	\param[in]	borderY	縦方向の閾値。
		 *
		 *	\sa fk_InputInfo, setMinMax(int, int)
		 */
		void			setBorder(int borderX, int borderY);

		//!	スティッククリッピング設定関数1
		/*!
		 *	この関数は、アナログスティックの値がある一定以上であれば最大値とみなし、
		 *	ある一定未満である場合は 0 とみなすように設定するものです。
		 *
		 *	アナログスティックを用いた場合、その座標の最大絶対値は 1000 であり、
		 *	ニュートラルの状態は 0 となるのが理想です。
		 *	しかしながら、実際には最もスティックを倒した状態でも 1000 にならない場合や、
		 *	ニュートラルの状態が微妙に (0, 0) からずれることがしばしばあります。
		 *	本関数は、そのような場合を考慮し、ある一定の絶対値以上であれば 1000 とみなし、
		 *	ある一定の絶対値未満であれば 0 とみなす設定を行います。
		 *	初期値は最小値が 200、最大値が 900 となっています。
		 *
		 *	\param[in]	index	デバイス ID。
		 *
		 *	\param[in]	min
		 *		0 とみなす閾値。負の数が与えられた場合は本関数の命令を無視します。
		 *		最小値方向のみなし設定を無効としたい場合、0 を入力して下さい。
		 *
		 *	\param[in]	max
		 *		1000(理論最大値)とみなす閾値。
		 *		1000 を超える値が与えられた場合は本関数の命令を無視します。
		 *		最大値方向のみなし設定を無効としたい場合、1000 を入力して下さい。
		 *
		 *	\sa fk_InputInfo, setBorder(int, int, int)
		 */
		void			setMinMax(int index, int min, int max);

		//!	スティッククリッピング設定関数2
		/*!
		 *	この関数は、アナログスティックの値がある一定以上であれば最大値とみなし、
		 *	ある一定未満である場合は 0 とみなすように設定するものです。
		 *
		 *	アナログスティックを用いた場合、その座標の最大絶対値は 1000 であり、
		 *	ニュートラルの状態は 0 となるのが理想です。
		 *	しかしながら、実際には最もスティックを倒した状態でも 1000 にならない場合や、
		 *	ニュートラルの状態が微妙に (0, 0) からずれることがしばしばあります。
		 *	本関数は、そのような場合を考慮し、ある一定の絶対値以上であれば 1000 とみなし、
		 *	ある一定の絶対値未満であれば 0 とみなす設定を行います。
		 *	初期値は最小値が 200、最大値が 900 となっています。
		 *	本関数は ID が 0 であるデバイスの閾値を設定しますが、
		 *	任意のデバイスの閾値を設定したい場合は setMinMax(int, int, int) を用いて下さい。
		 *
		 *	\param[in]	min
		 *		0 とみなす閾値。負の数が与えられた場合は本関数の命令を無視します。
		 *		最小値方向のみなし設定を無効としたい場合、0 を入力して下さい。
		 *
		 *	\param[in]	max
		 *		1000(理論最大値)とみなす閾値。
		 *		1000 を超える値が与えられた場合は本関数の命令を無視します。
		 *		最大値方向のみなし設定を無効としたい場合、1000 を入力して下さい。
		 *
		 *	\sa fk_InputInfo, setBorder(int, int)
		 */
		void			setMinMax(int min, int max);

		//@}

		//! \name ボタン・軸入れ替え関数
		//@{

		//!	ボタン入れ替え設定関数
		/*!
		 *	デバイスのボタン番号を入れ替えます。
		 *	この関数でボタンの入れ替えを設定した場合、
		 *	その後の getJoyStick() や getInputStatus() で取得する情報は、
		 *	入れ替えた状態を反映したものとなります。
		 *	なお、ボタンIDは 0 から開始となります。
		 *
		 *	\param[in]	dev		デバイスID。
		 *	\param[in]	id		新たに割り振るボタンID。
		 *	\param[in]	raw		デバイスでの本来のボタンID。
		 */
		void			setButtonSwap(int dev, int id, int raw);


		//!	軸入れ替え設定関数
		/*!
		 *	この関数は、デバイス上のスティックの軸方向と、
		 * 	仮想空間内の軸方向の対応を設定するものです。
		 *	以下のコードは、左スティックの横方向(x 軸方向)を、
		 *	fk_InputInfo::x[1] の値に対応させるためのものです。
		 *
		 *		fk_Input		input;
		 *		input.setAxisSwap(0, FK_AXIS2_X, FK_AXIS_X_POS);
		 *
		 *	\param[in]	dev		デバイスのID。
		 *	\param[in]	id		仮想空間内の軸方向。
		 *	\param[in]	raw		デバイス上の軸方向。
		 *
		 *	\note
		 *		仮想空間上の軸とデバイス上の軸の対応は、
		 *		初期状態は以下の通りです。
		 *			- FK_AXIS1_X : FK_AXIS_X_POS
		 *			- FK_AXIS1_Y : FK_AXIS_Y_POS
		 *			- FK_AXIS2_X : FK_AXIS_Z_POS
		 *			- FK_AXIS2_Y : FK_AXIS_RZ_POS
		 *			- FK_AXIS3_X : FK_AXIS_RX_POS
		 *			- FK_AXIS3_Y : FK_AXIS_RY_POS
		 */
		void			setAxisSwap(int dev, fk_AxisDirection id, fk_RawAxis raw);

		//! 軸ボタン割り当て設定関数
		/*!
		 *	デバイス上のスティック軸方向をボタンとして扱うよう設定します。
		 *	実質的には XBox360 コントローラ向けの機能となります。
		 *	以下は ID0 に接続された XBox360 コントローラを、
		 *	PS系コントローラ互換の割り当てに変更するコード例です。
		 *	デフォルトでは FK_AXIS2_X が LT, RT に対応しますが、
		 *	右スティックを軸2にアサインする設定も含めて例示します。
		 *
		 *		// 軸2と3を入れ替え
		 *		setAxisSwap(0, FK_AXIS2_X, FK_AXIS_RX_POS);
		 *		setAxisSwap(0, FK_AXIS2_Y, FK_AXIS_RY_POS);
		 *		setAxisSwap(0, FK_AXIS3_X, FK_AXIS_Z_POS);
		 *		setAxisSwap(0, FK_AXIS3_Y, FK_AXIS_RZ_POS);
		 *
		 *		// 入れ替え後の軸3の X 方向を 6,7 番に割り当て
		 *		setAxisToButton(0, FK_AXIS3_X, 6, 7, 500);
		 *
		 *		// ボタン入れ替え
		 *		setButtonSwap(0,  8, 6);	// Back->Select
		 *		setButtonSwap(0,  9, 7);	// Start->Start
		 *		setButtonSwap(0, 10, 8);	// StickL->StickL
		 *		setButtonSwap(0, 11, 9);	// StickR->StickR
		 *
		 *	\param[in]	dev			デバイス ID。
		 *	\param[in]	axisID		仮想空間内の軸方向。
		 *	\param[in]	posBtn		+ 方向のボタン番号。
		 *	\param[in]	negBtn		- 方向のボタン番号。
		 *	\param[in]	border		ボタンを押したと判断する閾値。
		 *
		 *	\sa setAxisSwap(), setButtonSwap(), clearAxisToButton(),
		 *		fk_InputInfo, fk_AxisDirection
		 */
		void			setAxisToButton(int dev, fk_AxisDirection axisID,
										int posBtn, int negBtn, int border);

		//! 軸ボタン割り当て解除関数
		/*!
		 *	setAxisToButton() 関数によって割り当てた設定を解除します。
		 *
		 * 	\param[in]	dev		デバイスID。
		 *
		 *	\sa setAxisToButton()
		 */
		void			clearAxisToButton(int dev);

		//@}

		//! \name キーボード代替関数
		//@{

		//!	ボタン機能キーボード代替設定関数
		/*!
		 *	デバイス上のボタンの代替としてキーボード上のキーを設定します。
		 *	キーコードの指定は、dinput.h 内で定義されている
		 *	「DIK_」で始まる定数を使って行います。
		 *	この関数によるキーボード代替操作は、デバイスIDが 0 のものに対してのみ有効です。
		 *
		 *	\param[in]	id
		 *		デバイス上のボタン番号。この番号とは、
		 *		setButtonSwap() で設定した「入れ替えた後の番号」を指します。
		 *	\param[in]	keycode
		 *		代替するキーに対応するキーコード。
		 *
		 *	\note
		 *		本関数による代替設定は、 getInputStatus() での結果には反映されますが、
		 *		getJoyStick() には反映されません。
		 *
		 * 	\sa setAxisAssign(), setPOVAssign()
		 */
		void			setKeyAssign(int id, DWORD keycode);

		//!	スティック機能キーボード代替設定関数
		/*!
		 *	デバイス上のスティックの代わりに使用するキーを設定します。
		 *	キーコードの指定は、dinput.h 内で定義されている
		 *	「DIK_」で始まる定数を使って行います。
		 *	この関数によるキーボード代替操作は、デバイスIDが 0 のものに対してのみ有効です。
		 *
		 *	\param[in]	axis_id
		 *		0で左スティック(通常十字キーとして使われる方)を、
		 *		1で右スティックを、
		 *		2で3番目の軸を表します。
		 *
		 *	\param[in]	up	上方向に対応するキーコード。
		 *	\param[in]	dn	下方向に対応するキーコード。
		 *	\param[in]	lt	左方向に対応するキーコード。		
		 *	\param[in]	rt	右方向に対応するキーコード。
		 *
		 *	\note
		 *		本関数による代替設定は、 getInputStatus() での結果には反映されますが、
		 *		getJoyStick() には反映されません。
		 *
		 *	\sa setKeyAssign(), setPOVAssign()
		 */
		void			setAxisAssign(int axis_id, DWORD up, DWORD dn, DWORD lt, DWORD rt);

		//!	ハットスイッチ(POVボタン)機能キーボード代替設定関数
		/*!
		 *	デバイス上のハットスイッチ(POVボタン)の代替としてキーボード上のキーを設定します。
		 *	キーコードの指定は、dinput.h 内で定義されている
		 *	「DIK_」で始まる定数を使って行います。
		 *	この関数によるキーボード代替操作は、デバイスIDが 0 のものに対してのみ有効です。
		 *
		 *	\param[in]	ul	左上方向に対応するキーコード。
		 *	\param[in]	u	上方向に対応するキーコード。
		 *	\param[in]	ur	右上方向に対応するキーコード。
		 *	\param[in]	l	左方向に対応するキーコード。
		 *	\param[in]	r	右上方向に対応するキーコード。
		 *	\param[in]	dl	左下上方向に対応するキーコード。
		 *	\param[in]	d	下方向に対応するキーコード。
		 *	\param[in]	dr	右下方向に対応するキーコード。
		 *
		 *	\note
		 *		本関数による代替設定は、 getInputStatus() での結果には反映されますが、
		 *		getJoyStick() には反映されません。
		 *
		 *	\sa setKeyAssign(), setAxisAssign()
		 */
		void			setPOVAssign(DWORD ul, DWORD u, DWORD ur, DWORD l,
									 DWORD r, DWORD dl, DWORD d, DWORD dr);

		//@}

	private:

#if defined(WIN32) && !defined(_MINGW_)
		static const int BUTTON_NUM = 32;
		static const int DIMGR_BUFFER_SIZE = 256;
		static const int INPUT_DEVICE_NUM = 16;
		static const int MOUSE_BUTTON_MAX = 8;
		static const int KEY_NUM = 256;

		int				buttonSwap[INPUT_DEVICE_NUM][BUTTON_NUM], axisSwap[INPUT_DEVICE_NUM][2*3];
		unsigned long	axisMap[4*3], povMap[8], keyMap[BUTTON_NUM];

		struct AxisParam {
			int pos, neg, border;
		};
		std::map<int, AxisParam>	axisParams[INPUT_DEVICE_NUM];

		//キーボードのメンバー変数
		bool m_Key[KEY_NUM];

		//マウスのメンバー変数
		POINT	m_MouseWorldPos;	//マウスの絶対座標
		int		m_MouseWheel;
		POINT	m_MouseLocalPos;	//マウスのローカル座標
		bool	m_Button[MOUSE_BUTTON_MAX];
		bool	m_LastButton[MOUSE_BUTTON_MAX];

		//Joyのメンバー変数
		DWORD					m_JoyCount;
		DWORD					m_JoyMaxCount;
		fk_InputInfo*			m_JoyButton;

		//X座標の遊び	0〜1000の値です。低いほど敏感
		int						m_AllowX[INPUT_DEVICE_NUM];

		//Y座標の遊び	0〜1000の値です。低いほど敏感
		int						m_AllowY[INPUT_DEVICE_NUM];

		// アナログスティックの値で有効とする範囲を指定します
		int						m_AllowMin[INPUT_DEVICE_NUM];

		// アナログスティックの値で有効とする範囲を指定します
		int						m_AllowMax[INPUT_DEVICE_NUM];

		//デバイス関連のメンバー変数
		HWND					m_hwnd;
		LPDIRECTINPUT8			m_Input;
		LPDIRECTINPUTDEVICE8	m_KeyBoardDevice;
		LPDIRECTINPUTDEVICE8	m_MouseDevice;
		LPDIRECTINPUTDEVICE8	m_JoyStciDevice[INPUT_DEVICE_NUM];
		DIDEVCAPS				m_DevCaps;
		DIDEVICEOBJECTDATA		m_DeviceObject[DIMGR_BUFFER_SIZE];  // Receives buffered data

		//=====================
		//Update関連
		//=====================
		HRESULT UpdateJoy(void);
		HRESULT UpdateMouse(void);
		HRESULT UpdateKey(void);

		//===========================
		//Joyのコールバック関数
		//===========================
		static BOOL CALLBACK EnumSizesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpvRef);
		static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* lpddi, LPVOID lpContext);

		short	AdjustParam(int, short);
		void	SetAxisParam(int, int, short);

#endif // WIN32 && !_MINGW_

	};
}
#endif //!__FK_INPUT_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
