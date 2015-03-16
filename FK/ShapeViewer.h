/****************************************************************************
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
#ifndef __FK_SHAPE_VIEWER_HEADER__
#define __FK_SHAPE_VIEWER_HEADER__

#include <FK/Window.h>
#include <FK/MatExample.h>
#include <FK/Line.h>
#include <FK/Texture.h>
#include <FK/Model.h>
#include <FK/Light.h>
#include <FK/Scene.h>
//#include <map>
#include <unordered_map>

#ifndef FK_DOXYGEN_USER_PROCESS

enum fk_ShapeGUIMenuItem {
	FK_SV_GUI_NONE,
	FK_SV_GUI_WRLOPEN,
	FK_SV_GUI_STLOPEN,
	FK_SV_GUI_DXFOPEN,
	FK_SV_GUI_WRLSAVE,
	FK_SV_GUI_STLSAVE,
	FK_SV_GUI_IMAGESNAP,
	FK_SV_GUI_QUIT,
	FK_SV_GUI_POLYDRAW,
	FK_SV_GUI_EDGEDRAW,
	FK_SV_GUI_VERTEXDRAW,
	FK_SV_GUI_LIGHTROTATE,
	FK_SV_GUI_AXISDRAW,
	FK_SV_GUI_AMBIENT,
	FK_SV_GUI_DIFFUSE,
	FK_SV_GUI_SPECULAR,
	FK_SV_GUI_EMISSION,
	FK_SV_GUI_SHININESS,
	FK_SV_GUI_VERTEXCOLOR,
	FK_SV_GUI_EDGECOLOR
};

class fk_GUI_;

#endif

//! 簡易形状表示システム用クラス
/*!
 *	このクラスは、簡易形状表示システムを制御する機能を提供します。
 *
 *	FK システムにおいて、形状を表示するためには形状用インスタンスの他にモデル、
 *	シーン、ウィンドウを準備する必要があります。
 *	また、様々な角度から形状を閲覧したい場合には、
 *	さらにカメラ操作のプログラムを追加しなければなりません。
 *	fk_ShapeViewer を用いると、モデル、シーン、ウィンドウを準備する必要はなく、
 *	閲覧するための機能が最初から備わっています。
 *
 *	fk_ShapeViewer が備えている標準機能は、以下のようなものがあります。
 *	- VRML、STL、DXF 各フォーマットファイル入力機能と、VRML ファイル出力機能。
 *	- 表示されている画像をファイルに保存する機能。
 *	- 面表示、稜線表示、頂点表示の各 ON/OFF および座標軸表示の ON/OFF。
 *	- 光源回転有無の制御。
 *	- 面のマテリアルおよび稜線、頂点の表示色設定。
 *	- GUI による姿勢制御および表示倍率、座標軸サイズの制御。
 *	- 左右矢印キーによるヘディング角制御。
 *	- スペースキーによる表示倍率制御。スペースキー単体で拡大、
 *		シフトキーとスペースキーを同時に押すことで縮小が行えます。
 *	- マウスドラッグ操作による形状の平行移動。
 *	.
 *	上記の操作は全てメニューなどの GUI から操作が可能で、
 *	プログラムとして記述する必要がありません。
 *	また、以下に述べるような各種メンバ関数を利用することで、
 *	プログラムから細かく制御することもできます。
 *	例えば、複数の形状を別々に動作させるといった制御も可能となります。
 *	特に ID を指定しなかった場合や、メニューから形状データを読み込んだ場合は、
 *	形状 ID が 0 となります。
 *
 *	変形アニメーションの様子を表示することも可能です。
 *	これは、 draw() を変形する度に呼び出すことで実現できます。
 *
 *	\sa fk_Window
 */

class fk_ShapeViewer : public fk_BaseObject {
 private:

	fk_Dimension		fkWinSize;
	fk_Dimension		allWinSize;
	fk_Dimension		groupPos;
	fk_Dimension		mousePos;

	int					mouseX, mouseY;

	// Window
	Fl_Window			*mainWindow;
	fk_Window			*viewWin;

	// GUI
	fk_GUI_				*gui;

	// flag
	bool				changeFlag;
	bool				lightFlag;
	bool				materialFlag;
	bool				moveFlag;
	bool				oldMoveFlag;
	fk_DrawMode			drawMode;
	bool				axisFlag;

	// FK Object
	fk_Model						parentModel;
	std::vector<fk_Model *>			modelArray;
	std::unordered_map<int, int>	IDMap;
	fk_Model						lightModel[2], camera, axisModel;
	fk_Solid						localSolid;
	fk_Line							axisLine;
	fk_Light						light;
	fk_Scene						scene;
	std::vector<fk_Material *>		polyMaterial;
	std::vector<fk_Color *>			edgeColor;
	std::vector<fk_Color *>			vertexColor;

	void				InitValue(void);
	void				InitFlag(void);
	void				InitWindow(void);
	void				InitGUI(void);
	void				LightInit(void);
	void				AxisInit(void);
	void				ViewInit(void);
	void				ModelInit(int, fk_Shape *);
	void				RotateLight(double);
	bool				MenuSelect(void);
	void				SetOrientation(double, double, double, double);
	void				SetAxisLine(double);
	void				MovePosition(double, double, double);
	void				DragShape(void);
	void				KeyHandle(void);
	std::string			CommonFileChooser(std::string, int, std::string);
	void				SetAllMaterial(void);
	void				SetSceneFlg(fk_ShapeGUIMenuItem);

	void				GetMaterial(int, fk_ShapeGUIMenuItem,
									double *, double *, double *);
	void				SetMaterial(int, fk_ShapeGUIMenuItem,
									double, double, double);
	void				SetDrawMode(void);

 public:
	//! コンストラクタ
	/*!
	 *	描画領域の大きさを指定することができます。単位はピクセルとなります。
	 *	ウィンドウ全体の大きさではないことに注意して下さい。
	 *
	 *	\param[in]	w	描画領域横幅
	 *	\param[in]	h	描画領域縦幅
	 */
	fk_ShapeViewer(int w = 300, int h = 360);

	//! デストラクタ
	virtual ~fk_ShapeViewer();

	//! \name 描画処理・描画領域制御関数
	//@{

	//! 描画更新関数
	/*!
	 *	形状の描画を行います。
	 *	GUI ならびにメンバ関数によって操作を行っても、
	 *	この関数を呼ばなければ画面は更新されません。
	 *
	 *	通常は、以下のようなコードを記述することになります。
	 *
	 *		fk_ShapeViewer	viewer;
	 *
	 *		while(viewer.draw() == true) {
	 *			// (もし必要なら)形状の変形処理を記述
	 *		}
	 *
	 *	\return
	 *		描画が正常に行えた場合、true を返します。
	 *		そうでない場合に false を返します。
	 *		これは例えば、ウィンドウが閉じられた場合などがそれに当たります。
	 */
	bool	draw(void);

	//! 描画領域サイズ変更関数
	/*!
	 *	描画領域のサイズを変更します。単位はピクセルとなります。
	 *
	 *	\param[in]	w	描画領域横幅
	 *	\param[in]	h	描画領域縦幅
	 */
	void	setWindowSize(int w, int h);

	//! OpenGL 頂点配列処理制御関数
	/*!
	 *	この関数は、OpenGL 環境における頂点配列の使用を制御します。
	 *	OpenGL には「頂点配列」と呼ばれる仕組みがあり、
	 *	一般的にはこの機能を用いると描画処理が高速になります。
	 *	しかし、実行する環境によってはかえって低速になったり、
	 *	描画に不具合が生じることもあります。
	 *	そのような場合、この関数を用いて頂点配列を利用しないように、
	 *	内部処理を切り替えることが可能です。
	 *	デフォルトでは「有効」となっています。
	 *
	 *	\note
	 *		この関数による設定は、OpenGL 環境においてのみ有効です。
	 *		Direct3D 版においては設定は意味をなしません。
	 *
	 *	\param[in]	mode	
	 *		true の場合、頂点配列処理を有効とします。
	 *		false の場合は無効とします。
	 */
	void	setOGLPointerMode(bool mode);

	//! OpenGL 頂点配列処理参照関数
	/*!
	 *	現在の OpenGL 頂点配列処理が有効であるかどうかを参照します。
	 *	頂点配列についての詳細は setOGLPointerMode() の解説を参照して下さい。
	 *
	 *	\return
	 *		頂点配列処理が有効である場合 true を、
	 *		無効である場合 false を返します。
	 *
	 *	\sa setOGLPointerMode()
	 */
	bool	getOGLPointerMode(void);

	//@}

	//! \name 形状制御関数
	//@{
	//! 単独形状設定関数
	/*!
	 *	形状を描画対象として設定します。
	 *	fk_Shape の派生クラスであれば、
	 *	(テクスチャ系も含めて)全てのクラスを描画対象として設定できます。
	 *	なお、この関数は ID を 0 番として
	 *	setShape(int, fk_Shape *) を用いた場合と同義になります。
	 *
	 *	\param[in]	shape	形状インスタンス
	 */
	void		setShape(fk_Shape *shape);

	//! ID付き形状設定関数
	/*!
	 *	形状を描画対象として設定します。
	 *	setShape(fk_Shape *) との違いは、
	 *	指定の際に ID を付けることです。
	 *	複数の形状を同時に描画したい場合は、
	 *	異なる ID をそれぞれの形状に付けることで実現できます。
	 *
	 *	\param[in]	ID		形状 ID
	 *	\param[in]	shape	形状インスタンス
	 */
	void		setShape(int ID, fk_Shape *shape);

	//! 形状参照関数
	/*!
	 *	指定した ID で設定されている形状インスタンスを返します。
	 *
	 *	\param[in]	ID	形状 ID
	 *
	 *	\return
	 *		形状インスタンスを返します。
	 *		指定した ID の形状インスタンスが存在しない場合は、NULL を返します。
	 */
	fk_Shape *	getShape(int ID = 0);

	//! 形状設定数参照関数
	/*!
	 *	現在設定されている形状の個数を返します。
	 *
	 *	\return		形状個数
	 */
	int		getModelNum(void);

	//! 形状設定初期化関数
	/*!
	 *	現在設定されている全ての形状情報を消去します。
	 */
	void	clearModel(void);

	//! 形状設定時処理関数
	/*!
	 *	この関数は、 setShape() やファイルからの形状入力が行われた際に、
	 *	自動的に呼び出されます。
	 *	呼び出された際に、引数には形状インスタンスが入ります。
	 *	このクラスは仮想関数となっており、
	 *	fk_ShapeViewer の派生クラスにおいてこの関数を再定義することにより、
	 *	形状設定やファイル入力時に形状に対して修正や分析などを行うことが可能となります。
	 *
	 *	\param[in]	shape	形状インスタンス
	 *
	 *	\return
	 *		現バージョンでは特に意味はありません。
	 */
	virtual bool	shapeProcess(fk_Solid *shape);
	//@}

	//! \name 全体描画属性制御関数
	//@{

	//! 描画モード設定関数
	/*!
	 *	登録されている全ての形状の描画モードを設定します。
	 *	描画モードとは、
	 *	面、稜線、頂点のそれぞれを描画するかどうかを制御するものです。
	 *	描画モードには以下のようなものがあります。
	 *	- FK_NONEMODE:				何も描画しません。
	 *	- FK_POINTMODE:				頂点を描画します。
	 *	- FK_LINEMODE:				稜線を描画します。
	 *	- FK_POLYMODE:				面の表を描画します。
	 *	- FK_BACK_POLYMODE:			面の裏を描画します。
	 *	- FK_FRONTBACK_POLYMODE:	面の表と裏を描画します。
	 *	.
	 *	これらの描画モードは、
	 *	ビット論理和を用いて複数のものを同時に指定することが可能です。
	 *	以下のコードは、頂点、稜線、面の表をすべて描画するように設定します。
	 *
	 *		fk_ShapeViewer	viewer;
	 *
	 *		viewer.setDrawMode(FK_POINTMODE | FK_LINEMODE | FK_POLYMODE);
	 *
	 *	個別の形状に対して別々の描画モードを設定する場合は、
	 *	setDrawMode(int, fk_DrawMode) を利用して下さい。
	 *
	 *	\param[in]	mode	描画モード
	 *
	 *	\sa setDrawMode(int, fk_DrawMode), fk_Model::setDrawMode()
	 */
	void	setDrawMode(fk_DrawMode mode);

	//! 描画モード参照関数
	/*!
	 *	現在の描画モードを参照します。
	 *
	 *	\return		描画モード
	 *
	 *	\sa setDrawMode(fk_DrawMode)
	 */
	fk_DrawMode		getDrawMode(void);

	//! 透過処理設定関数
	/*!
	 *	描画の際、透過処理を有効とするかどうかを設定します。
	 *	機能的には fk_Scene::setBlendStatus() と同様です。
	 *	詳細は、 fk_Scene::setBlendStatus() のマニュアルを参照して下さい。
	 *
	 *	\param[in]	mode	true であれば有効、false であれば無効とします。
	 *
	 *	\sa fk_Scene::setBlendStatus(), getBlendStatus()
	 */
	void			setBlendStatus(bool mode);

	//! 透過処理参照関数
	/*!
	 *	現在の透過処理状態を取得します。
	 *
	 *	\return		有効であれば true を、無効であれば false を返します。
	 *
	 *	\sa setBlendStatus()
	 */
	bool			getBlendStatus(void);

	//! 背景色設定関数1
	/*!
	 *	描画領域の背景色を設定します。
	 *
	 *	\param[in]	col		背景色
	 *
	 *	\sa setBGColor(float, float, float), fk_Color, getBGColor()
	 */
	void	setBGColor(fk_Color col);

	//! 背景色設定関数2
	/*!
	 *	描画領域の背景色を設定します。
	 *	各色要素は 0 から 1 までの値を取ります。
	 *	それ以外の値が与えられた場合、0 以下なら 0 に、1 以上なら 1 に丸められます。
	 *
	 *	\param[in]	r		背景色の赤要素
	 *	\param[in]	g		背景色の緑要素
	 *	\param[in]	b		背景色の青要素
	 *
	 *	\sa setBGColor(fk_Color), getBGColor()
	 */
	void	setBGColor(float r, float g, float b);

	//! 背景色参照関数
	/*!
	 *	描画領域の背景色を取得します。
	 *
	 *	\return		背景色
	 *
	 *	\sa fk_Color, setBGColor(fk_Color) setBGColor(float, float, float)
	 */
	fk_Color		getBGColor(void);

	//! 座標軸描画設定関数
	/*!
	 *	座標軸の表示の有無を設定します。
	 *
	 *	\param[in]	mode	true であれば描画有効、false であれば無効とします。
	 *
	 *	\sa setAxisScale(), getAxisMode()
	 */
	void			setAxisMode(bool mode);

	//! 座標軸描画参照関数
	/*!
	 *	座標軸の表示状態を取得します。
	 *
	 *	\return		描画有効であれば true を、無効であれば false を返します。
	 *
	 *	\sa setAxisMode()
	 */
	bool			getAxisMode(void);

	//! 座標軸大きさ設定関数
	/*!
	 *	座標軸の大きさを設定します。ここでいう大きさとは、
	 *	各軸の長さのことです。
	 *
	 *	\param[in]	scale	大きさ
	 */
	void	setAxisScale(double scale);

	//! 座標軸大きさ参照関数
	/*!
	 *	座標軸の大きさを取得します。
	 *
	 *	\return		大きさ
	 *
	 *	\sa setAxisScale()
	 */
	double	getAxisScale(void);



	//! 描画領域中心座標参照関数
	/*!
	 *	現在の描画領域で中心(注視点)となっている位置の位置ベクトルを返します。
	 *
	 *	\return		中心の位置ベクトル
	 */
	fk_Vector	getCenter(void);
	//@}

	//! \name 形状個別描画属性・マテリアル設定関数
	//@{

	//! 個別形状描画モード設定関数
	/*!
	 *	個別の形状に対して描画モードを設定します。
	 *	描画モードとは、
	 *	面、稜線、頂点のそれぞれを描画するかどうかを制御するものです。
	 *	描画モードには以下のようなものがあります。
	 *	- FK_NONEMODE:				何も描画しません。
	 *	- FK_POINTMODE:				頂点を描画します。
	 *	- FK_LINEMODE:				稜線を描画します。
	 *	- FK_POLYMODE:				面の表を描画します。
	 *	- FK_BACK_POLYMODE:			面の裏を描画します。
	 *	- FK_FRONTBACK_POLYMODE:	面の表と裏を描画します。
	 *	.
	 *	これらの描画モードは、
	 *	ビット論理和を用いて複数のものを同時に指定することが可能です。
	 *	以下のコードは、頂点、稜線、面の表をすべて描画するように設定します。
	 *
	 *		fk_ShapeViewer	viewer;
	 *
	 *		viewer.setDrawMode(0, FK_POINTMODE | FK_LINEMODE | FK_POLYMODE);
	 *
	 *	全ての形状に対しての描画モードを設定する場合は、
	 *	setDrawMode(fk_DrawMode) を利用して下さい。
	 *
	 *	\param[in]	ID		形状 ID
	 *	\param[in]	mode	描画モード
	 *
	 *	\sa setDrawMode(fk_DrawMode), fk_Model::setDrawMode()
	 */
	void	setDrawMode(int ID, fk_DrawMode mode);

	//! 個別形状描画モード参照関数
	/*!
	 *	現在の形状個別の描画モードを参照します。
	 *
	 *	\param[in]	ID		形状ID
	 *
	 *	\return		描画モード
	 *
	 *	\sa setDrawMode(int, fk_DrawMode)
	 */
	fk_DrawMode		getDrawMode(int ID);

	//! 形状稜線描画幅設定関数
	/*!
	 *	形状に対し、稜線の描画幅を設定します。
	 *	単位はピクセルです。整数以外も設定可能です。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	width	描画幅
	 */
	void	setLineWidth(int ID, double width);

	//! 形状稜線描画幅参照関数
	/*!
	 *	形状の稜線描画幅を取得します。
	 *	単位はピクセルです。
	 *
	 *	\param[in]	ID		形状ID
	 *
	 *	\return		描画幅
	 *
	 *	\sa setLineWidth()
	 */
	double	getLineWidth(int ID);

	//! 形状頂点描画サイズ設定関数
	/*!
	 *	形状に対し、頂点描画サイズを設定します。
	 *	単位はピクセルです。整数以外も設定可能です。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	size	描画サイズ
	 */
	void	setPointSize(int ID, double size);

	//! 形状頂点描画サイズ参照関数
	/*!
	 *	形状の頂点描画サイズを取得します。
	 *	単位はピクセルです。
	 *
	 *	\param[in]	ID		形状ID
	 *
	 *	\return		描画サイズ
	 *
	 *	\sa setPointSize()
	 */
	double	getPointSize(int ID);

	//! 形状マテリアル設定関数
	/*!
	 *	形状に対し、面のマテリアルを設定します。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	mat		マテリアル
	 *
	 *	\sa setEdgeColor(), setVertexColor(), fk_Material
	 */
	void	setMaterial(int ID, fk_Material mat);

	//! 形状稜線描画色設定関数
	/*!
	 *	形状に対し、稜線の描画色を設定します。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	col		稜線色
	 *
	 *	\sa setMaterial(), setVertexColor(), fk_Color
	 */
	void	setEdgeColor(int ID, fk_Color col);

	//! 形状頂点描画色設定関数
	/*!
	 *	形状に対し、頂点の描画色を設定します。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	col		頂点色
	 *
	 *	\sa setMaterial(), setEdgeColor(), fk_Color
	 */
	void	setVertexColor(int ID, fk_Color col);

	//@}

	//! \name カメラ角度・倍率制御関数
	//@{

	//! カメラヘッド角設定関数
	/*!
	 *	カメラのヘッド角を設定します。
	 *	ヘッド角についての詳細は、 fk_Angle の解説を参照して下さい。
	 *	引数の単位は弧度法(ラジアン)となります。
	 *
	 *	\param[in]	angle		ヘッド角の角度
	 *
	 *	\sa setPitch(), setBank(), setScale(), fk_Angle
	 */
	void	setHead(double angle);

	//! カメラヘッド角参照関数
	/*!
	 *	現在のカメラのヘッド角を取得します。
	 *
	 *	\return		ヘッド角の角度
	 *
	 *	\sa setHead()
	 */
	double	getHead(void);

	//! カメラピッチ角設定関数
	/*!
	 *	カメラのピッチ角を設定します。
	 *	ピッチ角についての詳細は、 fk_Angle の解説を参照して下さい。
	 *	引数の単位は弧度法(ラジアン)となります。
	 *
	 *	\param[in]	angle		ピッチ角の角度
	 *
	 *	\sa setHead(), setBank(), setScale(), fk_Angle
	 */
	void	setPitch(double angle);

	//! カメラピッチ角参照関数
	/*!
	 *	現在のカメラのピッチ角を取得します。
	 *
	 *	\return		ピッチ角の角度
	 *
	 *	\sa setPitch()
	 */
	double	getPitch(void);

	//! カメラバンク角設定関数
	/*!
	 *	カメラのバンク角を設定します。
	 *	バンク角についての詳細は、 fk_Angle の解説を参照して下さい。
	 *	引数の単位は弧度法(ラジアン)となります。
	 *
	 *	\param[in]	angle		バンク角の角度
	 *
	 *	\sa setHead(), setPitch(), setScale(), fk_Angle
	 */
	void	setBank(double angle);

	//! カメラバンク角参照関数
	/*!
	 *	現在のカメラのバンク角を取得します。
	 *
	 *	\return		バンク角の角度
	 *
	 *	\sa setBank()
	 */
	double	getBank(void);

	//! カメラ倍率設定関数
	/*!
	 *	カメラの表示倍率を設定します。
	 *
	 *	\param[in]	scale	表示倍率
	 *
	 *	\sa setHead(), setPicth(), setBank()
	 */
	void	setScale(double scale);

	//! カメラ倍率参照関数
	/*!
	 *	カメラの表示倍率を取得します。
	 *
	 *	\return		表示倍率
	 *
	 *	\sa setScale()
	 */
	double	getScale(void);

	//@}

	//! \name 形状位置・姿勢制御関数
	//@{

	//! 形状位置設定関数1
	/*!
	 *	形状の位置を設定します。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	pos		形状位置ベクトル
	 *
	 *	\sa	setPosition(int, double, double, double),
	 *		setAngle(int, fk_Angle), setVec(int, fk_Vector),
	 *		setUpvec(int, fk_Vector)
	 */
	void	setPosition(int ID, fk_Vector pos);

	//! 形状位置設定関数2
	/*!
	 *	形状の位置を設定します。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	x		形状位置ベクトルのx成分
	 *	\param[in]	y		形状位置ベクトルのy成分
	 *	\param[in]	z		形状位置ベクトルのz成分
	 *
	 *	\sa setPosition(int, fk_Vector),
	 *		setAngle(int, fk_Angle), setVec(int, fk_Vector),
	 *		setUpvec(int, fk_Vector)
	 */
	void	setPosition(int ID, double x, double y, double z);

	//! 形状姿勢設定関数1
	/*!
	 *	形状の姿勢をオイラー角で設定します。
	 *	オイラー角については、 fk_Angle の解説を参照して下さい。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	angle	姿勢を表すオイラー角
	 *
	 *	\sa setAngle(int, double, double, double),
	 *		setPosition(int, fk_Vector), setVec(int, fk_Vector),
	 *		setUpvec(int, fk_Vector)
	 */
	void	setAngle(int ID, fk_Angle angle);

	//! 形状姿勢設定関数2
	/*!
	 *	形状の姿勢をオイラー角で設定します。
	 *	オイラー角については、 fk_Angle の解説を参照して下さい。
	 *	なお、角度の単位は弧度法(ラジアン)となります。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	h		姿勢を表すオイラー角のヘッド角度
	 *	\param[in]	p		姿勢を表すオイラー角のピッチ角度
	 *	\param[in]	b		姿勢を表すオイラー角のバンク角度
	 *
	 *	\sa setAngle(int, fk_Angle),
	 *		setPosition(int, fk_Vector), setVec(int, fk_Vector),
	 *		setUpvec(int, fk_Vector)
	 */
	void	setAngle(int ID, double h, double p, double b);

	//! 形状方向ベクトル設定関数1
	/*!
	 *	形状の方向ベクトルを設定します。
	 *	方向ベクトルは正規化してある必要はありません。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	vec		方向ベクトル
	 *
	 *	\sa setVec(int, double, double, double),
	 *		setPosition(int, fk_Vector), setAngle(int, fk_Angle),
	 *		setUpvec(int, fk_Vector)
	 */
	void	setVec(int ID, fk_Vector vec);

	//! 形状方向ベクトル設定関数2
	/*!
	 *	形状の方向ベクトルを設定します。
	 *	方向ベクトルは正規化してある必要はありません。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	x		方向ベクトルのx成分
	 *	\param[in]	y		方向ベクトルのy成分
	 *	\param[in]	z		方向ベクトルのz成分
	 *
	 *	\sa setVec(int, fk_Vector),
	 *		setPosition(int, fk_Vector), setAngle(int, fk_Angle),
	 *		setUpvec(int, fk_Vector)
	 */
	void	setVec(int ID, double x, double y, double z);

	//! 形状アップベクトル設定関数1
	/*!
	 *	形状のアップベクトルを設定します。
	 *	アップベクトルは正規化してある必要はありません。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	vec		アップベクトル
	 *
	 *	\sa setUpvec(int, double, double, double),
	 *		setPosition(int, fk_Vector), setAngle(int, fk_Angle),
	 *		setVec(int, fk_Vector)
	 */
	void	setUpvec(int ID, fk_Vector vec);

	//! 形状アップベクトル設定関数2
	/*!
	 *	形状のアップベクトルを設定します。
	 *	アップベクトルは正規化してある必要はありません。
	 *
	 *	\param[in]	ID		形状ID
	 *	\param[in]	x		アップベクトルのx成分
	 *	\param[in]	y		アップベクトルのy成分
	 *	\param[in]	z		アップベクトルのz成分
	 *
	 *	\sa setUpvec(int, fk_Vector),
	 *		setPosition(int, fk_Vector), setAngle(int, fk_Angle),
	 *		setVec(int, fk_Vector)
	 */
	void	setUpvec(int ID, double x, double y, double z);
	//@}

	//! \name フレームレート制御関数
	//@{

	//! フレームレート制御方法指定関数
	/*!
	 *	この関数は、フレームレートを制御するためのモードを指定します。
	 *	「フレームレート」とは、1秒間あたりの画面更新回数のことです。
	 *	フレームレートの制御には、以下の2種類があります。
	 *	- フレームレートが高すぎる場合に、一定のフレームレート以上が出ないようにする。
	 *		この制御を「ウェイトモード」と言います。
	 *	- フレームレートが低すぎる場合に、画面更新をスキップする。
	 *		この制御を「スキップモード」と言います。
	 *	.
	 *	モードには、以下の3種類が指定できます。
	 *	- FK_DEFAULT_FRAME: 制御を行いません。
	 *	- FK_WAIT_FRAME: ウェイトモードを有効にします。
	 *	- FK_SKIP_FRAME: スキップモードを有効にします。
	 *	.
	 *	なお、FK_WAIT_FRAME と FK_SKIP_FRAME は同時に指定することが可能です。
	 *	その場合は、以下のようにビット論理和演算子を利用します。
	 *
	 *		fk_ShapeViewer	viewer;
	 *	
	 *		viewer.setFrameMode(FK_WAIT_FRAME | FK_SKIP_FRAME);
	 *
	 *	\param[in]	mode		制御モード
	 *	
	 *	\sa setFrameInterval(), getSkipFrame(), fk_Window::setFrameMode()
	 */
	void	setFrameMode(fk_FrameMode mode);

	//! フレームレート制御方法参照関数
	/*!
	 *	現在のフレームレート制御方法を取得します。
	 *
	 *	\return		制御モードを返します。
	 *
	 *	\sa setFrameMode()
	 */
	fk_FrameMode	getFrameMode(void);

	//! フレーム間時間設定関数
	/*!
	 *	この関数は、フレームレート制御の「ウェイトモード」および
	 *	「スキップモード」における、
	 *	フレーム間時間の設定を行います。
	 *	「フレーム間時間」とは、
	 *	あるフレームが表示されてから次のフレームが表示されるまでの時間のことです。
	 *	例えば秒間60フレームとしたい場合は、
	 *	フレーム間時間は \f$\frac{1}{60} = 0.01666\cdots\f$ となります。
	 *	なお、本関数では指定はミリ秒(1000分の1秒)単位で行い、
	 *	型は int 型となります。従って、前述した秒間60フレームの場合は
	 *	「16」または「17」を指定することになります。
	 *
	 *	\param[in]	ms		フレーム間時間。単位はミリ秒です。
	 *
	 *	\sa setFrameMode() getSkipFrame(), fk_Window::setFrameInterval()
	 */
	void	setFrameInterval(int ms);

	//! フレーム間時間参照関数
	/*!
	 *	現在設定されているフレーム間時間を参照します。
	 *
	 *	\return		フレーム間時間を返します。単位はミリ秒です。
	 *
	 *	\sa setFrameInterval()
	 */
	int		getFrameInterval(void);

	//! スキップフレーム数参照関数
	/*!
	 *	フレーム制御で「スキップモード」を用いている場合に、
	 *	現在表示されているフレームとその前のフレームの間に、
	 *	何枚分のフレームが描画スキップされたかを参照します。
	 *
	 *	\return		スキップされたフレーム枚数
	 *
	 *	\sa setFrameMode(), setFrameInterval(), fk_Window::getSkipFrame()
	 */
	int		getSkipFrame(void);
	//@}

	//! \name 描画画像取り込み関数
	//@{


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
	 *
	 *	\sa fk_Window::snapImage(std::string, fk_ImageType, fk_SnapProcMode)
	 */
	bool	snapImage(std::string fileName,
					  fk_ImageType format = FK_IMAGE_BMP,
					  fk_SnapProcMode mode = FK_SNAP_GL_FRONT);

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
	 *
	 *	\sa fk_Window::snapImage(fk_Image *, fk_SnapProcMode)
	 */

	bool	snapImage(fk_Image *image,
					  fk_SnapProcMode mode = FK_SNAP_GL_FRONT);
	//@}

	//! \name メッセージ出力制御関数
	//@{

	//! メッセージ出力モード設定関数
	/*!
	 *	実質的に、 fk_Window::setPutStrMode() とまったく同じ動作となります。
	 *	そちらの解説を参照して下さい。
	 *
	 *	\sa fk_Window::setPutStrMode()
	 */
	void	setPutStrMode(const fk_PutStrMode mode);

	//! メッセージ出力モード参照関数
	/*!
	 *	実質的に、 fk_Window::getPutStrMode() とまったく同じ動作となります。
	 *	そちらの解説を参照して下さい。
	 *
	 *	\sa fk_Window::getPutStrMode()
	 */
	fk_PutStrMode	getPutStrMode(void);

	//! メッセージ出力用ファイル設定関数
	/*!
	 *	実質的に、 fk_Window::setPutFile() とまったく同じ動作となります。
	 *	そちらの解説を参照して下さい。
	 *
	 *	\sa fk_Window::setPutFile()
	 */
	bool	setPutFile(const std::string &str);

	//! メッセージ出力文字列設定関数
	/*!
	 *	実質的に、 fk_Window::putString() とまったく同じ動作となります。
	 *	そちらの解説を参照して下さい。
	 *
	 *	\sa fk_Window::putString()
	 */
	void	putString(const std::string &str);

#ifndef FK_CLI_CODE
	//! メッセージ出力書式付き設定関数
	/*!
	 *	実質的に、 fk_Window::printf() とまったく同じ動作となります。
	 *	そちらの解説を参照して下さい。
	 *
	 *	\sa fk_Window::printf()
	 */
	void	printf(const char *format, ...);
#endif

	//! メッセージ出力用ブラウザ初期化関数
	/*!
	 *	実質的に、 fk_Window::clearBrowser() とまったく同じ動作となります。
	 *	そちらの解説を参照して下さい。
	 *
	 *	\sa fk_Window::clearBrowser()
	 */
	void	clearBrowser(void);
	//@}

#ifndef FK_DOXYGEN_USER_PROCESS
	void	SetFinalizeMode(void);
#endif
};

#endif // !__FK_SHAPE_VIEWER_HEADER__
