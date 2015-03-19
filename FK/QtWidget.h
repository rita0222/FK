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
#ifndef __FK_QT_WIDGET_HEADER__
#define __FK_QT_WIDGET_HEADER__

#include <QGLWidget>
#include <QTimer>

#include <FK/Engine.H>

//! Qt 用ウィジェット生成クラス
/*!
 *	このクラスは、FK によるシーンを
 *	Qt 用ウィジェットとして作成、制御するための機能を提供します。
 *
 *	fk_QtWidget クラスは、Qt の QGLWidget の派生クラスとなっています。
 *	通常の QGLWidget インスタンスに対し、
 *	FK のシーン描画機能が追加されているものと言えます。
 *
 *	本クラスの使用方法の概略は以下のようになります。
 *	-# fk_QtWidget の派生クラスを作成し、
 *		メンバとして FK の各種インスタンスを用意する。
 *	-# fk_Scene インスタンスを setScene() で登録する。
 *	-# beforeLoop() 関数に、描画ループの前処理を記述する。
 *	-# loop() 関数に、描画ループ内の処理を記述する。
 *	-# (必要であれば) afterLoop() 関数に、描画ループの後処理を記述する。
 *	.
 *	あとは、通常の Qt ウィジェットとしてウィンドウに登録しておくことで、
 *	自動的に画面が更新されていきます。
 *	(更新は QTimer によるタイマーイベントによって行っています。)
 *
 *	\attention
 *		対応する Qt のバージョンは 4.5 以降となります。
 *
 *	\sa fk_Window
 */

class fk_QtWidget : public QGLWidget
{
	Q_OBJECT

 private:

	QColor				bgColor;
	QTimer				*qtTimer;
	bool				firstFlg;
	int					interval;
	QSize				widgetSize;

	fk_GraphicsEngine	engine;

 private slots:
	void			_updateShape(void);
	void			_quit(void);

 protected:

#ifndef FK_DOXYGEN_USER_PROCESS
	void			initializeGL(void);
	void			paintGL(void);
	void			resizeGL(int, int);
#endif

	//! ループ前処理記述関数
	/*!
	 *	この関数は、ウィジェットの生成時にシステム内部から自動的に呼び出される関数です。
	 *	fk_QtWidget クラスの派生クラスを作成し、
	 *	そのクラスにおいて本関数を再定義することによって、
	 *	描画ループの前処理を記述することが可能です。
	 *
	 *	\sa loop(), afterLoop()
	 */
	virtual void	beforeLoop(void) {}

	//! 毎ループ処理記述関数
	/*!
	 *	この関数は、画面更新の度にシステム内部から自動的に呼び出される関数です。
	 *	fk_QtWidget クラスの派生クラスを作成し、
	 *	そのクラスにおいて本関数を再定義することによって、
	 *	描画ループの内部処理を記述することが可能です。
	 *
	 *	\sa beforeLoop(), afterLoop()
	 */
	virtual bool	loop(void) { return true; }

	//! ループ後処理記述関数
	/*!
	 *	この関数は、ウィジェット消去時にシステム内部から自動的に呼び出される関数です。
	 *	fk_QtWidget クラスの派生クラスを作成し、
	 *	そのクラスにおいて本関数を再定義することによって、
	 *	描画ループの後処理を記述することが可能です。
	 *
	 *	\sa beforeLoop(), loop()
	 */
	virtual void	afterLoop(void) {}

 public:
	//! コンストラクタ
	/*!
	 *	\param[in]	w		ウィジェットの横幅。ピクセル値で指定します。
	 *	\param[in]	h		ウィジェットの縦幅。ピクセル値で指定します。
	 *	\param[in]	parent
	 *		本ウィジェットの親ウィジェットインスタンスを指定します。
	 *		親ウィジェットを指定しない場合は nullptr を代入します。
	 */
	fk_QtWidget(int w, int h, QWidget *parent = nullptr);

	//! デストラクタ
	virtual ~fk_QtWidget();

	//! \name シーン制御関数
	//@{

	//! シーン設定関数
	/*!
	 *	シーンをウィジェットに設定します。
	 *
	 *	\param[in]	scene		シーンのインスタンス
	 */
	void	setScene(fk_Scene *scene);
	//@}


	//! \name 投影座標・空間座標変換関数
	//@{

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
	 *	\param[in]	plane
	 *		射影先の平面。平面情報の設定については fk_Plane の解説を参照して下さい。
	 *	\param[out]	pos		算出した点の位置ベクトル
	 *
	 *	\return		算出に成功すれば true を、失敗すれば false を返します。
	 *
	 *	\sa getProjectPosition(double, double, double, fk_Vector *),
	 *		getWindowPosition(), fk_Plane
	 */
	bool	getProjectPosition(double x, double y,
							   fk_Plane *plane, fk_Vector *pos);

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
	 *	\param[out]	pos		算出した点の位置ベクトル
	 *
	 *	\return		算出に成功すれば true を、失敗すれば false を返します。
	 */
	bool	getProjectPosition(double x, double y,
							   double dist, fk_Vector *pos);

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
	 *	\param[out]	pos_2D		射影点となる投影座標の位置ベクトル
	 *
	 *	\sa getProjectPosition(double, double, fk_Plane *, fk_Vector *),
	 *		getProjectPosition(double, double, double, fk_Vector *),
	 *		fk_Perspective, fk_Ortho, fk_Frustum
	 */
	bool	getWindowPosition(fk_Vector pos_3D, fk_Vector *pos_2D);
	//@}

	//! \name グラフィックス処理制御関数
	//@{
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

	//! テクスチャメモリ解放関数
	/*!
	 *	この関数は、現在確保されているテクスチャメモリの解放を行います。
	 *
	 *	アプリケーションの中でテクスチャマッピングを行う際、
	 *	各テクスチャ画像のキャッシングを行っています。
	 *	これは、一般的にテクスチャマッピングにおいては同じ画像を再利用する割合が高いため、
	 *	キャッシングの効率が良いためです。
	 *	しかし、それは同時にテクスチャの格納によるメモリ使用量増大を意味します。
	 *	本関数は、確保したメモリを全て解放します。
	 *	これによりメモリ使用量は減少しますが、
	 *	テクスチャ画像入力のための処理時間が増加する可能性があります。
	 */
	void	clearTextureMemory(void);

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
	//@}

	//! \name フレームレート制御関数
	//@{
	//! フレーム間時間設定関数
	/*!
	 *	この関数は、フレーム間時間を設定します。
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
	 *	\sa getInterval()
	 */
	void	setInterval(int ms);

	//! フレーム間時間参照関数
	/*!
	 *	現在設定されているフレーム間時間を参照します。
	 *
	 *	\return		フレーム間時間を返します。単位はミリ秒です。
	 *
	 *	\sa setInterval()
	 */
	int		getInterval(void);
	//@}

	//! \name 描画更新制御関数
	//@{
	//! 更新開始関数
	/*!
	 *	この関数は、描画ループを開始します。
	 *	具体的には、 setInterval() によって設定した時間ごとに、
	 *	loop() を呼び出し続けます。
	 *	更新を停止するには stop() を用います。
	 *
	 *	\sa setInterval(), stop()
	 */
	void			start(void);

	//! 更新停止関数
	/*!
	 *	この関数は、描画ループを停止します。
	 *	例えば、実行中にダイアログなどを開いているときに、
	 *	QtWidget による更新を止めたい場合などに利用します。
	 *	再び更新を開始するには start() を用います。
	 *
	 *	\sa start()
	 */
	void			stop(void);
	//@}

#ifndef FK_DOXYGEN_USER_PROCESS
	virtual QSize	minimumSizeHint(void) const;
	virtual QSize	sizeHint(void) const;
#endif

};

#endif
