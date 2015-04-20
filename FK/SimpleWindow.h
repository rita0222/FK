﻿/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_SIMPLE_WINDOW_HEADER__
#define __FK_SIMPLE_WINDOW_HEADER__

#include <FK/Window.h>
#include <FK/Light.h>
#include <FK/FrameController.H>
#include <FK/GuideObject.h>
#include <FK/TrackBall.h>
#include <FK/MotionCharactor.h>
#include <FK/SpriteModel.h>
#include <FK/Fullscreen.h>
#include <FK/Input.h>

enum fk_PadDirection {
	FK_PAD_UP = 32,
	FK_PAD_DOWN,
	FK_PAD_LEFT,
	FK_PAD_RIGHT
};

typedef fk_PadDirection fkut_PadDirection;

#define FKUT_PAD_UP		FK_PAD_UP
#define FKUT_PAD_DOWN	FK_PAD_DOWN
#define FKUT_PAD_LEFT	FK_PAD_LEFT
#define FKUT_PAD_RIGHT	FK_PAD_RIGHT

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

class fk_AppWindow {
private:
	friend class fk_CubicModel;
	friend class fk_SpriteModel;

	Fl_Window	*mainWin;
	fk_Window	*drawWin;

	fk_AppWindow		*ref_child;
	fk_FrameController	fps_admin;
	fk_GuideObject		guide;
	fk_TrackBall			*tb;
	fk_FullscreenController	fsc;

	fk_Scene	scene;
	fk_Scene	*ref_scene;

	fk_Light	lightShape;
	fk_Model	camera, light;
	fk_Model	*ref_camera;

	int		fps;
	bool	tbFlag, childMode;

	//static bool	prevKeySt[256], prevSPKeySt[32], prevMouseSt[3];

	fk_Input		input;
	fk_InputInfo	prevInput[16], nowInput[16];
	int				inputCount;

	void PushPrevStatus(void);
	void ToggleScreen(void);

public:

	//! コンストラクタ
	fk_AppWindow(void);
	//! 子ウィンドウ作成時用コンストラクタ
	fk_AppWindow(fk_AppWindow &parent);
	//! デストラクタ
	~fk_AppWindow(void);

	//! \name ウィンドウの各種設定関数
	//@{

	//! ウィンドウタイトル設定関数
	/*!
	 *	ウィンドウのタイトルバーに表示する文字列を変更します。
	 *	デフォルトは"FK APP Window"です。
	 *
	 *	\param[in]		name
	 *		タイトル文字列
	 */
	void setWindowName(const std::string &name);

	//! ウィンドウサイズ設定関数
	/*!
	 *	ウィンドウサイズを変更します。単位はピクセルです。
	 *	3DCG描画領域も同じサイズに変更します。
	 *	デフォルトは512x512です。
	 *
	 *	\param[in]		w
	 *		ウィンドウ横幅
	 *	\param[in]		h
	 *		ウィンドウ縦幅
	 */
	void setSize(int w, int h);

	//! 描画領域サイズ設定関数
	/*!
	 *	ウィンドウの内部に持つ3DCGの描画領域の位置とサイズを変更します。
	 *	マルチウィンドウを実現する際の調整用関数なので、上級者向けです。
	 *
	 *	\param[in]		x		描画領域左上位置 x 座標
	 *	\param[in]		y		描画領域左上位置 y 座標
	 *	\param[in]		w		描画領域横幅
	 *	\param[in]		h		描画領域縦幅
	 */
	void setInnerSize(int x, int y, int w, int h);

	//! 背景色設定関数1
	/*!
	 *	3DCG描画領域の背景色をRGBの色値ブレンドで指定します。
	 *	各成分は0.0～1.0の実数値です。
	 *	それ以外の値が与えられた場合、
	 *	0 以下なら 0 に、1 以上なら 1 に丸められます。
	 *	デフォルトは黒(0, 0, 0)です。
	 *
	 *	\param[in]		r		背景色の赤要素
	 *	\param[in]		g		背景色の緑要素
	 *	\param[in]		b		背景色の青要素
	 *
	 *	\sa setBGColor(const fk_Color &)
	 */
	void setBGColor(double r, double g, double b);


	//! 背景色設定関数2
	/*!
	 *	3DCG描画領域の背景色を設定します。
	 *
	 *	\param[in]		color		背景色
	 *
	 *	\sa setBGColor(double, double, double), fk_Color
	 */
	void setBGColor(const fk_Color &color);

	//! フルスクリーン化関数
	/*!
	 *	ウィンドウをフルスクリーン化します。
	 *	正しく表示するためには、
	 *	ウィンドウサイズがモニタ側で対応しているサイズと
	 *	一致している必要があります。
	 *	すでにフルスクリーン化されている時は何も起きません。
	 *	また、アプリ起動中に ALT+ENTER
	 *	キーでフルスクリーンとウィンドウを切り替えることができます。
	 *
	 *	\note
	 *		この関数は Windows 環境のみ対応しています。
	 *
	 *	\sa toWindow()
	 */
	void toFullscreen(void);

	//! ウィンドウ化関数
	/*!
	 *	フルスクリーン化しているウィンドウを元に戻します。
	 *	フルスクリーン化されていない時に呼んでも何も起きません。
	 *	また、アプリ起動中に ALT+ENTER
	 *	キーでフルスクリーンとウィンドウを切り替えることができます。
	 *
	 *	\note
	 *		この関数は Windows 環境のみ対応しています。
	 *
	 *	\sa toFullscreen()
	 */
	void toWindow(void);
	//@}

	//! \name 描画制御関数
	//@{

	//! ウィンドウ生成関数
	/*!
	 *	ウィンドウを開いて表示します。
	 *
	 *	\sa close(), update()
	 */
	void open(void);

	//! ウィンドウ破棄関数
	/*!
	 *	ウィンドウを閉じます。
	 *	ウィンドウが表示されている状態でプログラムが終了した場合は
	 *	自動的に閉じられるので、
	 *	本関数を明示的に呼ぶ必要はありません。
	 *	プログラム自体は動作し続けるが、ウィンドウを閉じたい場合や、
	 *	改めてウィンドウを再生成したい場合に本関数を利用して下さい。
	 *
	 *	\sa open(), update()
	 */
	void close(void);

	//! シーン描画関数
	/*!
	 *	シーン画面を描画し、さらに各種入力デバイスの状態を更新します。
	 *	基本的にメインループ内でコールすることになります。
	 *	その際、 setFPS() 関数によって設定した FPS
	 *	の制御状態に基づいて時間調整が入ります。
	 *	FPS制御を無視して強制的に描画処理を呼び出したい場合は引数に
	 *	true を渡します。
	 *
	 *	\param[in]	forceFlag
	 *		true の場合、FPS制御を無視して強制的に再描画を行います。
	 * 		false の場合は FPS制御により描画タイミングを制御し、
	 *		描画が行われるまでは関数は終了しなくなります。
	 *		デフォルトは false です。
	 *
	 *	\sa open(), close(), setFPS()
	 */
	bool update(bool forceFlag = false);

	//! FPS設定関数
	/*!
	 *	update()をコールした際に調整するFPSを指定します。
	 *	FPS(Frame Per Second)とは、1秒間中で画面更新が行われる回数の単位です。
	 *	この値を 0 に設定した場合は、FPS制御を行いません。
	 *	デフォルトは60です。
	 *
	 *	\param[in]		fps			FPS値
	 */
	void setFPS(int fps);
	//@}


	//! \name グリッド・座標軸表示設定関数
	//@{
	//! グリッド・軸設定関数
	/*!
	 *	画面内の座標系を表すグリッドと軸を指定します。
	 *	FK_AXIS_X, FK_AXIS_Y, FK_AXIS_Zがそれぞれの軸を、
	 *	FK_GRID_XZ, FK_GRID_XY, 
	 *	FK_GRID_YZがそれぞれの平面を表すグリッドに対応します。
	 *	複数の要素を指定したい場合は | (ビットOR演算子)で区切って指定できます。
	 *	FK_NO_GUIDEで全て非表示に、
	 *	FK_ALL_GUIDEで全ての軸・グリッドを表示します。
	 *	引数を省略した場合は、XYZの各軸とXZ平面のグリッドを表示します。
	 *	デフォルトでは全て非表示(FK_NO_GUIDE)です。
	 *
	 *	\param[in]		mode
	 *		表示するグリッド・軸の指定。複数を表示する場合は、
	 *		ビットOR演算を利用して並べて指定できます。
	 *
	 *	\sa hideGuide(), setGuideAxisWidth(), setGuideGridWidth(),
	 *		setGuideScale(), setGuideNum(), fk_GuideMode
	 */
	void showGuide(fk_GuideMode mode =
				   FK_AXIS_X | FK_AXIS_Y | FK_AXIS_Z | FK_GRID_XZ);

	//! グリッド・軸消去関数
	/*!
	 *	showGuide() で表示した軸とグリッドを消去します。
	 *	showGuide(FK_NO_GUIDE) と等価です。
	 *
	 *	\sa showGuide()
	 */
	void hideGuide(void);

	//! 軸線幅設定関数
	/*!
	 *	showGuide() で表示する軸の太さを指定します。
	 *	デフォルトは4.0です。
	 *
	 *	\param[in]		width		軸線の太さ
	 *
	 *	\sa showGuide(), setGuideGridWidth()
	 */
	void setGuideAxisWidth(double width);

	//! グリッド線幅設定関数
	/*!
	 *	showGuide() で表示するグリッドの太さを指定します。
	 *	デフォルトは1.0です。
	 *
	 *	\param[in]		width		グリッド線の太さ
	 *
	 *	\sa showGuide(), setGuideAxisWidth(), setGuideNum()
	 */
	void setGuideGridWidth(double width);

	//! グリッド幅設定関数
	/*!
	 *	showGuide()で表示するグリッドや軸の1辺の長さを指定します。
	 *	デフォルトは5.0です。
	 *
	 *	\param[in]		scale		グリッドの1辺の長さ
	 *
	 *	\sa showGuide(), setGuideGridWidth(), setGuideNum()
	 */
	void setGuideScale(double scale);

	//! グリッド数設定関数
	/*!
	 *	showGuide()で表示するグリッドの軸方向あたりの個数を指定します。
	 *	デフォルトは20です。
	 *
	 *	\param[in]		num		軸方向あたりのグリッド個数
	 *
	 *	\sa showGuide(), setGuideGridWidth(), setGuideScale()
	 */
	void setGuideNum(int num);
	//@}

	//! \name カメラ制御関数
	//@{

	//! カメラ位置設定関数1
	/*!
	 *	現在ウィンドウが制御しているカメラの位置を指定した位置座標に移動します。
	 *
	 *	\param[in]		x		カメラ位置のx成分
	 *	\param[in]		y		カメラ位置のy成分
	 *	\param[in]		z		カメラ位置のz成分
	 */
	void		setCameraPos(double x, double y, double z);

	//! カメラ位置設定関数2
	/*!
	 *	現在ウィンドウが制御しているカメラの位置を指定した位置座標に移動します。
	 *
	 *	\param[in]		pos		カメラ位置のベクトル
	 */
	void		setCameraPos(const fk_Vector &pos);

	//!	カメラ注視点設定関数1
	/*!
	 *	現在ウィンドウが制御しているカメラの向きを、
	 *	指定した座標に向くよう姿勢変更します。
	 *
	 *	\param[in]	   	x		注視点位置のx成分
	 *	\param[in]	   	y		注視点位置のy成分
	 *	\param[in]	   	z		注視点位置のz成分
	 */
	void		setCameraFocus(double x, double y, double z);

	//!	カメラ注視点設定関数2
	/*!
	 *	現在ウィンドウが制御しているカメラの向きを、
	 *	指定した座標に向くよう姿勢変更します。
	 *
	 *	\param[in]	   	pos		注視点の位置ベクトル
	 */
	void		setCameraFocus(const fk_Vector &pos);

	//! カメラモデル設定関数1
	/*!
	 *	ウィンドウに対して、
	 *	別のfk_Model(及びその派生クラス)のオブジェクトをカメラとして
	 *	セットします。
	 *	この関数でセットしたモデルを操作すれば、
	 *	fk_AppWindowのメンバ関数を介さずカメラ制御が可能です。
	 *
	 *	\param[in]		model	カメラモデル(のアドレス)
	 */
	void		setCameraModel(fk_Model *model);

	//! カメラモデル設定関数2
	/*!
	 *	ウィンドウに対して、
	 *	別のfk_Model(及びその派生クラス)のオブジェクトをカメラとして
	 *	セットします。
	 *	この関数でセットしたモデルを操作すれば、
	 *	fk_AppWindowのメンバ関数を介さずカメラ制御が可能です。
	 *
	 *	\param[in]		model	カメラモデル
	 */
	void		setCameraModel(fk_Model &model);

	//! カメラモデル取得関数
	/*!
	 *	現在ウィンドウで制御しているカメラモデルオブジェクトの
	 *	ポインタを取得します。
	 *
	 *	\return			カメラモデルのポインタ
	 *
	 *	\sa		setCameraModel(fk_Model *), setCameraModel(fk_Model &),
	 *			fk_Model
	 */
	fk_Model *	getCameraModel(void);


	//! カメラ初期化関数
	/*!
	 *	ウィンドウが制御するカメラを、
	 *	デフォルトで内部に保持している fk_Model のインスタンスに戻します。
	 *
	 *	\sa		setCameraModel(fk_Model *), setCameraModel(fk_Model &),
	 *			getCameraModel()
	 */
	void		setCameraDefault(void);
	//@}

	//! \name シーン制御関数
	//@{
	//! シーン設定関数1
	/*!
	 *	ウィンドウに対して、別の fk_Scene のオブジェクトをセットします。
	 *	アプリの画面ごとにモデルを登録した fk_Scene オブジェクトを、
	 *	この関数でセットして切り替えることで、
	 *	モデルを個別に登録や解除を行う手間が省けます。
	 *	ある程度以上の規模を持つアプリを開発する場合は便利です。
	 *	第 2 引数に true を設定すると、新たにセットするシーンに対して、
	 *	fk_AppWindow 内部のカメラとライトオブジェクトを
	 *	引き継いでセットすることができますが、
	 *	構造がややこしくなるのでできるだけ自前で用意することを推奨します。
	 *	省略した場合と false を設定した場合はシーンの切り替えのみを行います。
	 *
	 *	\param[in]		scene				シーンインスタンス(のポインタ)
	 *	\param[in]		defCameraAndLight
	 *		true である場合、
	 *		カメラ・光源設定についてシーン設定前のものを用います。
	 *		false である場合は第一引数の scene
	 *		に設定されている情報に切り替えます。
	 *
	 *	\sa getScene(), setSceneDefault()
	 */
	void		setScene(fk_Scene *scene, bool defCameraAndLight = false);

	//! シーン設定関数2
	/*!
	 *	ウィンドウに対して、別の fk_Scene のオブジェクトをセットします。
	 *	アプリの画面ごとにモデルを登録した fk_Scene オブジェクトを、
	 *	この関数でセットして切り替えることで、
	 *	モデルを個別にエントリー・リムーブする手間が省けます。
	 *	ある程度以上の規模を持つアプリを開発する場合は便利です。
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
	 *		false である場合は第一引数の scen
	 *		に設定されている情報に切り替えます。
	 *
	 *	\sa getScene(), setSceneDefault(), fk_Scene
	 */
	void		setScene(fk_Scene &scene, bool defCameraAndLight = false);

	//! シーン取得関数
	/*!
	 *	現在ウィンドウで制御しているシーンオブジェクトのポインタを取得します。
	 *
	 *	\return		現在設定されているシーンのポインタ
	 *
	 *	\sa setScene(fk_Scene *, bool), setScene(fk_Scene &, bool),
	 *		setSceneDefault(), fk_Scene
	 */
	fk_Scene *	getScene(void);

	//! シーン設定初期化関数
	/*!
	 *	ウィンドウが制御するシーンを、
	 *	デフォルトで内部に保持している fk_Scene のインスタンスに戻します。
	 *
	 *	\sa setScene(fk_Scene *, bool), setScene(fk_Scene &, bool),
	 *		getScene(), fk_Scene
	 */
	void		setSceneDefault(void);

	//! モデル表示登録関数1
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
	 *	\param[in]		model		登録モデル(のポインタ)
	 *
	 *	\sa entry(fk_Model &), remove(fk_Model *), clearModel()
	 */
	void entry(fk_Model *model);

	//! モデル表示登録関数2
	/*!
	 *	ウィンドウに対してモデルを登録し、表示するようにします。
	 *	既に登録済みのモデルに対して行った場合、登録順が最後尾となります。
	 *	半透明物体の描画については、 entry(fk_Model *) の説明を参照して下さい。
	 *
	 *	\param[in]		model		登録モデル
	 *
	 *	\sa entry(fk_Model *), remove(fk_Model &), clearModel()
	 */
	void entry(fk_Model &model);

	//! 座標軸付きモデル表示登録関数1
	/*!
	 *	ウィンドウに対してモデルを登録し、表示するようにします。
	 *	既に登録済みのモデルに対して行った場合、登録順が最後尾となります。
	 *	半透明物体の描画については、 entry(fk_Model *) の説明を参照して下さい。
	 *	登録の際、モデルのローカル座標系に基づく座標軸を同時に登録します。
	 *
	 *	\param[in]		model		登録モデル(のポインタ)
	 *	\param[in]		guide		座標軸(のポインタ)
	 *
	 *	\sa entry(fk_Model &, fk_GuideObject &),
	 *		remove(fk_Model *, fk_GuideObject *), clearModel()
	 */
	void entry(fk_Model *model, fk_GuideObject *guide);

	//! 座標軸付きモデル表示登録関数2
	/*!
	 *	ウィンドウに対してモデルを登録し、表示するようにします。
	 *	既に登録済みのモデルに対して行った場合、登録順が最後尾となります。
	 *	半透明物体の描画については、 entry(fk_Model *) の説明を参照して下さい。
	 *	登録の際、モデルのローカル座標系に基づく座標軸を同時に登録します。
	 *
	 *	\param[in]		model		登録モデル
	 *	\param[in]		guide		座標軸
	 *
	 *	\sa entry(fk_Model *, fk_GuideObject *),
	 *		remove(fk_Model &, fk_GuideObject &), clearModel()
	 */
	void entry(fk_Model &model, fk_GuideObject &guide);

	//! スプライトモデル登録関数1
	/*!
	 *	ウィンドウに対してスプライトモデルを登録し、表示するようにします。
	 *
	 *	\param[in]		model		登録モデル(のポインタ)
	 *
	 *	\sa entry(fk_SpriteModel &), remove(fk_SpriteModel *),
	 *		clearModel(), fk_SpriteModel
	 */
	void entry(fk_SpriteModel *model);

	//! スプライトモデル登録関数2
	/*!
	 *	ウィンドウに対してスプライトモデルを登録し、表示するようにします。
	 *
	 *	\param[in]		model		登録モデル
	 *
	 *	\sa entry(fk_SpriteModel *), remove(fk_SpriteModel &),
	 *		clearModel(), fk_SpriteModel
	 */
	void entry(fk_SpriteModel &model);

	//! fk_Performer モデル登録関数1
	/*!
	 *	ウィンドウに対して fk_Performer 型のモデルを登録し、
	 *	表示するようにします。
	 *
	 *	\param[in]		chara		登録モデル(のポインタ)
	 *
	 *	\sa entry(fk_Performer &), remove(fk_Performer *),
	 *		clearModel(), fk_Performer
	 */
	void entry(fk_Performer *chara);

	//! fk_Performer モデル登録関数2
	/*!
	 *	ウィンドウに対して fk_Performer 型のモデルを登録し、
	 *	表示するようにします。
	 *
	 *	\param[in]		chara		登録モデル
	 *
	 *	\sa entry(fk_Performer *), remove(fk_Performer &),
	 *		clearModel(), fk_Performer
	 */
	void entry(fk_Performer &chara);

	//! モデル表示解除関数1
	/*!
	 *	ウィンドウからモデルの登録を解除し、表示されないようにします。
	 *	登録していないモデルを指定した場合は何も起きません。
	 *
	 *	\param[in]		model		登録解除モデル(のポインタ)
	 *
	 *	\sa remove(fk_Model &), entry(fk_Model *), clearModel()
	 */
	void remove(fk_Model *model);

	//! モデル表示解除関数2
	/*!
	 *	ウィンドウからモデルの登録を解除し、表示されないようにします。
	 *	登録していないモデルを指定した場合は何も起きません。
	 *
	 *	\param[in]		model		登録解除モデル
	 *
	 *	\sa remove(fk_Model *), entry(fk_Model &), clearModel()
	 */
	void remove(fk_Model &model);

	//! 座標軸付きモデル表示解除関数1
	/*!
	 *	ウィンドウから、座標軸付きモデルの登録を解除し、
	 *	表示されないようにします。
	 *	登録していないモデルを指定した場合は何も起きません。
	 *
	 *	\param[in]		model		登録解除モデル(のポインタ)
	 *	\param[in]		guide		登録解除座標軸(のポインタ)
	 *
	 *	\sa remove(fk_Model &, fk_GuideObject &),
	 *		entry(fk_Model *, fk_GuideObject *),
	 *		clearModel()
	 */
	void remove(fk_Model *model, fk_GuideObject *guide);

	//! 座標軸付きモデル表示解除関数2
	/*!
	 *	ウィンドウから、座標軸付きモデルの登録を解除し、
	 *	表示されないようにします。
	 *	登録していないモデルを指定した場合は何も起きません。
	 *
	 *	\param[in]		model		登録解除モデル
	 *	\param[in]		guide		登録解除座標軸
	 *
	 *	\sa remove(fk_Model *, fk_GuideObject *),
	 *		entry(fk_Model &, fk_GuideObject &),
	 *		clearModel()
	 */
	void remove(fk_Model &model, fk_GuideObject &guide);

	//! スプライトモデル表示解除関数1
	/*!
	 *	ウィンドウから、スプライトモデルの登録を解除し、
	 *	表示されないようにします。
	 *	登録していないモデルを指定した場合は何も起きません。
	 *
	 *	\param[in]		model		登録解除モデル(のポインタ)
	 *
	 *	\sa remove(fk_SpriteModel &), entry(fk_SpriteModel *), clearModel()
	 */
	void remove(fk_SpriteModel *model);

	//! スプライトモデル表示解除関数2
	/*!
	 *	ウィンドウから、スプライトモデルの登録を解除し、
	 *	表示されないようにします。
	 *	登録していないモデルを指定した場合は何も起きません。
	 *
	 *	\param[in]		model		登録解除モデル
	 *
	 *	\sa remove(fk_SpriteModel *), entry(fk_SpriteModel &), clearModel()
	 */
	void remove(fk_SpriteModel &model);

	//! fk_Performer モデル表示解除関数1
	/*!
	 *	ウィンドウから、fk_Performer 型モデルの登録を解除し、
	 *	表示されないようにします。
	 *	登録していないモデルを指定した場合は何も起きません。
	 *
	 *	\param[in]		chara		登録解除モデル(のポインタ)
	 *
	 *	\sa remove(fk_Performer &), entry(fk_Performer *), clearModel()
	 */
	void remove(fk_Performer *chara);

	//! fk_Performer モデル表示解除関数2
	/*!
	 *	ウィンドウから、fk_Performer 型モデルの登録を解除し、
	 *	表示されないようにします。
	 *	登録していないモデルを指定した場合は何も起きません。
	 *
	 *	\param[in]		chara		登録解除モデル
	 *
	 *	\sa remove(fk_Performer *), entry(fk_Performer &), clearModel()
	 */
	void remove(fk_Performer &chara);

	//! 全モデル登録解除関数
	/*!
	 *	現在のシーンから全てのモデルの表示登録を解除します。
	 *
	 *	\param[in]	defCameraAndLight
	 *		ウィンドウ内部で保持しているライトとカメラのモデルを残したい場合は、
	 *		true を指定します。
	 *		省略あるいは false を渡した場合は、完全なクリアとなります。
	 */
	void clearModel(bool defCameraAndLight = false);
	//@}


	//! \name キーボード状態取得関数
	//@{

	//! 通常キー状態取得関数
	/*!
	 *	通常キーの入力状態を検出します。
	 *	引数として、
	 *	検出したい文字をシングルクォーテーションで囲って指定します。
	 *	'A' や 'X' などとします。
	 *	入力できない特殊キーには getSpecialKeyStatus() を使います。
	 *
	 *	\param[in]	keyChar
	 *		状態を取得したいキー文字。大文字や数字、各種記号キーを設定できます。
	 *		スペースキーの状態を取得したい場合は「' '」と入力します。
	 *
	 *	\return
	 *		キーの状態を返します。種類については
	 *		::fk_SwitchStatus を参照して下さい。
	 *		瞬間かどうかの判定は、
	 *		直前に update() を呼んだ時点とその前に update()
	 *		を呼んだ時点での入力状態によって決定しています。
	 *
	 *	\sa getSpecialKeyStatus(), update()
	 */
	fk_SwitchStatus		getKeyStatus(char keyChar);
	bool				getKeyStatus(char keyChar,
									 fk_SwitchStatus status, bool insideFlg = false);

	//! 特殊キー状態取得関数
	/*!
	 *	特殊キーの入力状態を検出します。
	 *	引数として、検出したいキーに対応した
	 *	::fk_SpecialKey 型の値を入力します。
	 *	例えば、上矢印キーの状態を取得したい場合には「FK_UP」を入力します。
	 *	通常キーの状態取得は getKeyStatus() を使います。
	 *
	 *	\param[in]	keyCode
	 *		状態を取得したいキーに対応した値。
	 *
	 *	\return
	 *		キーの状態を返します。種類については
	 *		::fk_SwitchStatus を参照して下さい。
	 *		瞬間かどうかの判定は、
	 *		直前に update() を呼んだ時点とその前に update()
	 *		を呼んだ時点での入力状態によって決定しています。
	 *
	 *	\note
	 *		スペースキーの状態取得は、本関数ではなく getKeyStatus() を用います。
	 *
	 *	\sa getKeyStatus(), update()
	 */
	fk_SwitchStatus	getSpecialKeyStatus(fk_SpecialKey keyCode);

	bool			getSpecialKeyStatus(fk_SpecialKey keyCode,
										fk_SwitchStatus status, bool insideFlg = false);

	//@}

	//! \name マウス状態取得関数
	//@{

	//! マウスボタン状態取得関数
	/*!
	 *	マウスボタンのクリック状態を検出します。
	 *	マウスボタンの種類については、 ::fk_MouseButton の項目を参照して下さい。
	 *
	 *	\param[in]		buttonCode		マウスボタンの種類
	 *
	 *	\return
	 *		ボタンの状態を返します。種類については
	 *		::fk_SwitchStatus を参照して下さい。
	 *		瞬間かどうかの判定は、直前に update() を呼んだ時点とその前に
	 *		update() を呼んだ時点での入力状態によって決定しています。
	 */
	fk_SwitchStatus		getMouseStatus(fk_MouseButton buttonCode);
	bool				getMouseStatus(fk_MouseButton buttonCode,
									   fk_SwitchStatus status, bool insideFlg);
	
	//! マウスポインタ位置取得関数
	/*!
	 *	マウスのカーソル位置を検出します。
	 *	返値として fk_Vector の値を返し、
	 *	x 成分と y 成分にそれぞれウィンドウ投影座標系の値が入ります。
	 *	ウィンドウの外にはみ出したかどうかは、
	 *	値がウィンドウサイズを超過しているか否かで判断できます。
	 *
	 *	\return
	 *		マウスポインタの位置座標
	 *
	 *	\sa getMouseStatus(), fk_Window::getMousePosition()
	 */
	fk_Vector			getMousePosition(void);

	//! マウスカーソル表示制御関数
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
	 *
	 *	\note
	 *		この関数は Windows 環境のみ対応しています。
	 */
	void				setCursorState(bool visible, bool center);
	//@}

	//! \name ゲームパッド状態制御関数
	//@{
	// ゲームパッド認識個数取得関数
	int					getPadCount(void);
	// ゲームパッドボタン状態取得関数
	fk_SwitchStatus	getPadButtonStatus(int padID, int buttonID);
	// ゲームパッド方向キー取得関数
	fk_Vector			getPadDirection(int padID, int axisID);
	// ゲームパッド管理オフジェクト取得関数
	fk_Input *			getPadManager(void);
	//@}

	//! \name マウス制御支援関数
	//@{

	//! トラックボールモード制御関数
	/*!
	 *	マウスの右ドラッグとホイール操作で、
	 *	カメラを自由に操作できるモードをON(true)/OFF(false)します。
	 *	デフォルトはOFF(false)です。
	 *
	 *	\param[in]		mode
	 *		true であれば有効、false であれば無効とします。
	 */
	void setTrackBallMode(bool mode);

	//! モデルクリック判定関数1
	/*!
	 *	マウスでモデルをクリックしているかどうかを判定します。
	 *	引数には判定対象としたいモデルを渡します。1 つずつしか判定できません。
	 *	そのままだと現在のカーソル位置を基準に判定しますが、
	 *	任意の座標を指定したい場合は、
	 *	(モデル, 誤差を許容するピクセル数, X 座標, Y 座標)
	 *	の形式で引数を渡します。
	 *	カーソルがモデルに重なっている場合は true、
	 *	いない場合は false を返します。
	 *
	 *	\param[in]	model	判定対象モデル。
	 *	\param[in]	pixel	誤差許容ピクセル数。
	 *	\param[in]	mouseX
	 *		判定対象クリック位置のx座標。
	 *		-1 を指定した場合や省略した場合は、
	 *		現在のマウスポインタ位置の x 座標が対象となります。
	 *	\param[in]	mouseY
	 *		判定対象クリック位置のy座標。
	 *		-1 を指定した場合や省略した場合は、
	 *		現在のマウスポインタ位置の y 座標が対象となります。
	 *
	 *	\return
	 *		カーソルがモデルに重なっている場合は true、
	 *		いない場合は false を返します。
	 */
	bool isModelPicked(fk_Model *model, int pixel = 1,
					   int mouseX = -1, int mouseY = -1);

	//! モデルクリック判定関数2
	/*!
	 *	マウスでモデルをクリックしているかどうかを判定します。
	 *	引数には判定対象としたいモデルを渡します。1 つずつしか判定できません。
	 *	そのままだと現在のカーソル位置を基準に判定しますが、
	 *	任意の座標を指定したい場合は、
	 *	(モデル, 誤差を許容するピクセル数, X 座標, Y 座標)
	 *	の形式で引数を渡します。
	 *	カーソルがモデルに重なっている場合は true、
	 *	いない場合は false を返します。
	 *
	 *	\param[in]	model	判定対象モデル。
	 *	\param[in]	pixel	誤差許容ピクセル数。
	 *	\param[in]	mouseX
	 *		判定対象クリック位置のx座標。
	 *		-1 を指定した場合や省略した場合は、
	 *		現在のマウスポインタ位置の x 座標が対象となります。
	 *	\param[in]	mouseY
	 *		判定対象クリック位置のy座標。
	 *		-1 を指定した場合や省略した場合は、
	 *		現在のマウスポインタ位置の y 座標が対象となります。
	 *
	 *	\return
	 *		カーソルがモデルに重なっている場合は true、
	 *		いない場合は false を返します。
	 */
	bool isModelPicked(fk_Model &model, int pixel = 1,
					   int mouseX = -1, int mouseY = -1);

	//! FPS視点的カメラ制御関数1
	/*!
	 *	FPS 視点のゲーム特有の、マウス移動による視点操作処理を行います。
	 *
	 *	\param[in]	camera		カメラモデル。
	 *	\param[in]	spinX		横方向の移動に対する回転角度。
	 *	\param[in]	spinY		縦方向の移動に対する回転角度。
	 *	\param[in]	lockSW
	 *		true の場合、カーソルの中心を固定します。
	 *		false の場合は固定しません。
	 */
	void procMouseView(fk_Model *camera, double spinX,
					   double spinY, bool lockSW);

	//! FPS視点的カメラ制御関数2
	/*!
	 *	FPS 視点のゲーム特有の、マウス移動による視点操作処理を行います。
	 *
	 *	\param[in]	camera		カメラモデル。
	 *	\param[in]	spinX		横方向の移動に対する回転角度。
	 *	\param[in]	spinY		縦方向の移動に対する回転角度。
	 *	\param[in]	lockSW
	 *		true の場合、カーソルの中心を固定します。
	 *		false の場合は固定しません。
	 */
	void procMouseView(fk_Model &camera, double spinX,
					   double spinY, bool lockSW);
	//@}

#ifndef FK_DOXYGEN_USER_PROCESS
	void		SetFinalizeMode(void);
#endif
};

typedef fk_AppWindow fkut_SimpleWindow;

#endif //!__FK_SIMPLE_WINDOW_HEADER__
