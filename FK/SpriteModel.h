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
#ifndef __FK_SPRITE_MODEL_HEADER__
#define __FK_SPRITE_MODEL_HEADER__

#include <FK/UniCode.h>
#include <FK/Model.h>
#include <FK/TextImage.h>
#include <FK/Texture.h>
#include <FK/Scene.h>
#include <FK/Window.h>

//! 2D スプライトモデルクラス
/*!
 *	このクラスは、画像や文字列をディスプレイ座標系に従って配置する機能を提供します。
 *	
 *	リアルタイム 3DCG において (3次元空間の投影によらず)
 *	ディスプレイ上に直接画像やメッセージ等のビットマップ画像を表示する処理を
 *	「スプライト表示」と呼びます。
 *	スプライト表示を行うための方法はプラットフォームによって異なるため、
 *	FK では直接スプライト表示を行う機能は提供しませんが、
 *	本クラスはディスプレイ座標系での指定に従って、
 *	適切にテクスチャ画像の配置を行うことによって(擬似的に)スプライト表示を実現します。
 *	
 *	\attention
 *		本クラスは fk_Model クラスを継承しており、
 *		fk_Model のメンバ関数が使用可能です。
 *		ただし、3次元的な挙動を指示した場合には意図しない動作になることがあります。
 *		また、表示するウィンドウごとに内部計算が必要なため、
 *		マルチウィンドウ利用時はインスタンスを使い回すことができません。
 *		ウィンドウごとに別々のインスタンスを使用して下さい。
 *
 *	\sa fk_Model, fk_TextImage, fk_Image
 */

class fk_SpriteModel : public fk_Model {
private:
	friend class fk_AppWindow;

	fk_RectTexture	texShape;
	fk_Material		absMate;
	fk_Model		pixelBase;

	fk_UniStr		textStr;
	bool			fontReady;

	static double	distPut;

public:
	//! 文字列描画設定用オブジェクト
	/*!
	 *	drawText() 関数によって制御される fk_TextImage 型インスタンスです。
	 *	このメンバを直接操作することにより、フォントや表示色など多くの属性を制御できます。
	 *	詳細は、 fk_TextImage クラスのマニュアルを参照して下さい。
	 *
	 *	\sa fk_TextImage
	 */
	fk_TextImage	text;

	//! コンストラクタ
	fk_SpriteModel(void);
	//! デストラクタ
	~fk_SpriteModel(void);

	//! fk_Scene へのエントリー関数
	/*!
	 *	スプライトのサイズやレイアウトを、カメラ・シーン・ウィンドウに合わせて設定します。
	 *	fk_Scene へ最初にエントリーする時は、こちらの関数を使ってください。
	 *	シーンにはカメラがセット済みである必要があります。
	 *	ウィンドウサイズ・カメラ・射影を変更した場合はもう一度呼ばないとサイズがおかしくなります。
	 *
	 *	\note
	 *		fk_AppWindow を利用している場合は、本関数を利用する必要はありません。
	 *
	 *	\param[in]	win		表示対象となる fk_Window 型のインスタンスへのポインタ。
	 *	\param[in]	scene	表示対象となる fk_Scene 型のインスタンスへのポインタ。
	 *	\param[in]	camera	表示対象となるカメラインスタンスへのポインタ。
	 *
	 *	\sa fk_Window, fk_Scene, fk_Model
	 */
	bool		entryFirst(fk_Window *win, fk_Scene *scene, fk_Model *camera = NULL);

	//! Windows Bitmap (BMP)画像読み込み関数
	/*!
	 *	Windows Bitmap 形式 (BMP形式) の画像を読み込みます。
	 *
	 *	\param[in]	filename		BMP形式ファイル名
	 *
	 *	\return
	 *		成功したら true を、失敗したら false を返します。
	 */
	bool		readBMP(const std::string filename);

	//! PNG画像読み込み関数
	/*!
	 *	PNG形式の画像を読み込みます。アルファチャンネルによる透過に対応しています。
	 *
	 *	\param[in]	filename		PNG形式ファイル名
	 *
	 *	\return
	 *		成功したら true を、失敗したら false を返します。
	 */
	bool		readPNG(const std::string filename);

	//! JPEG(JPG)画像読み込み関数
	/*!
	 *	JPEG形式の画像を読み込みます。
	 *
	 *	\param[in]	filename		PNG形式ファイル名
	 *
	 *	\return
	 *		成功したら true を、失敗したら false を返します。
	 */
	bool		readJPG(const std::string filename);

	//! 画像データセット関数
	/*!
	 *	fk_Image 型の画像データを読み込みます。
	 *
	 *	既に画像を読み込み済みの fk_Image をセットします。
	 */
	void		setImage(fk_Image &image);

	//! 画像データ参照関数
	/*!
	 *	内部の画像データインスタンスを参照します。
	 *	画像サイズを変更しない限りは、内部データを直接変更しても問題ありません。
	 *
	 *	\attention
	 *		本関数で得たインスタンスの画像サイズを変更した場合の挙動は保証されません。
	 *
	 *	\return
	 *		画像データインスタンスのポインタ
	 */
	fk_Image *	getImage(void);

	//! 画像位置指定関数
	/*!
	 *	指定した座標が左上になるように位置を変更します。
	 *	指定する数値は、画面中心を原点とする座標系で、
	 *	数値 1 が 1 ピクセルに相当する値になります。
	 *
	 *	画像の中心位置を指定したい場合は、
	 *	fk_Model::glMoveTo() を利用して下さい。
	 *
	 *	\attention
	 *		本関数によって位置を指定した後に、
	 *		以下に述べるような操作を行った場合、
	 *		表示位置が不適切となる場合があります。
	 *			- setSpriteSize() による大きさ変更。
	 *			- 画像データの再入力。
	 *			- 投影変換の変更。
	 *			- ウィンドウサイズの変更。
	 *			.
	 *		このような操作を行った場合、
	 *		再度本関数によって適切な位置に指定を行う必要があります。
	 *
	 *	\param[in]	x	画像左上の x 座標値。
	 *	\param[in]	y	画像左上の y 座標値。
	 *
	 *	\sa setSpriteSize(), getSpriteSize(), fk_Model::glMoveTo()
	 */
	void		setPositionLT(double x, double y);

	//! 画像表示領域指定関数
	/*!
	 *	画像の一部分だけを表示領域として切り出します。
	 *	本関数での座標系は、画像のピクセル数が横幅 \f$ W \f$, 縦幅 \f$ H \f$ としたとき、
	 *	画像の左上が \f$ (0, 0) \f$ であり、右下が \f$ (W-1, H-1) \f$ となります。
	 *
	 *	\param[in]	x	表示領域左上の x 座標値。
	 *	\param[in]	y	表示領域左上の y 座標値。
	 *	\param[in]	w	表示領域の横幅ピクセル数。
	 *	\param[in]	h	表示領域の縦幅ピクセル数。
	 *
	 *	\sa getSpriteSize()
	 */
	void		setSpriteArea(double x, double y, double w, double h);

	//! 表示サイズ設定関数
	/*!
	 *	画像の表示サイズを設定します。
	 *	通常は画像の設定時に自動調整を行っていますので、
	 *	敢えてそこからサイズを変更したい時に使います。
	 *	引数を省略すると、読み込んである画像と同じサイズに復元します。
	 *	数値 1 が 1 ピクセルに相当する値になります。
	 *
	 *	\param[in]	width		表示サイズの横幅。-1 を指定した場合、元画像の横幅となります。
	 *	\param[in]	height		表示サイズの縦幅。-1 を指定した場合、元画像の縦幅となります。
	 *
	 *	\sa getSpriteSize(), setPositionLT(), setSpriteArea()
	 */
	void		setSpriteSize(double width = -1.0, double height = -1.0);

	//! 表示サイズ取得関数
	/*!
	 *	画像の表示サイズを取得します。
	 *	数値 1 が 1 ピクセルに相当する値になります。
	 *
	 *	\return
	 *		u 成分と v 成分にそれぞれ幅と高さが入ります。
	 *
	 *	\sa setSpriteSize()
	 */
	fk_TexCoord	getSpriteSize(void);

	//! 画像表示モード設定関数
	/*!
	 *	画像を滑らかに表示するかどうかを制御します。
	 *	デフォルトでは滑らかに表示する設定になっています。
	 *
	 *	\param[in]	mode
	 *		true であれば滑らかな表示に設定し、
	 *		false であれば滑らかな表示は行いません。
	 *
	 *	\sa getSpriteSmoothMode()
	 */
	void		setSpriteSmoothMode(bool mode);

	//! 画像表示モード取得関数
	/*!
	 *	画像を滑らかに表示するかどうかの状態を取得します。
	 *
	 *	\return
	 *		滑らかに表示する設定であれば true を、そうでなければ false を返します。
	 *
	 *	\sa setSpriteSmoothMode()
	 */
	bool		getSpriteSmoothMode(void);

	//! 文字列描画用フォント設定関数
	/*!
	 *	文字表示を行うための、フォントの設定を行います。
	 *	drawText() による文字列表示を行いたい場合は、事前に本関数を実行する必要があります。
	 *	ここで指定するものは TrueType 形式のフォントファイルとなります。
	 *	通常は「ttf」あるいは「ttc」という拡張子のファイルとなっています。
	 *
	 *	\param[in]	fontFileName	フォントファイル名
	 *
	 *	\return
	 *		フォントの設定に成功すれば true を、失敗すれば false を返します。
	 *
	 *	\attention
	 *		各種 OS に付属しているフォントファイルや、
	 *		商用のフォントファイルの中には、
	 *		ライセンス上再配布が禁止されているものがあります。
	 *		プログラムの配布時には必ずライセンスの確認を行ってください。
	 */
	bool		initFont(const std::string fontFileName);

	//! 文字列表示関数
	/*!
	 *	指定された文字列を表示する画像を設定します。
	 *	本関数を実行する前に、事前に initFont() でフォント指定を行う必要があります。
	 *
	 *	\note
	 *		fk_SprinteModel::text メンバを制御して表示方法を変更したい場合は、
	 *		本関数を実行する前に行う必要があります。
	 *		事後に変更しても有効にならないので注意してください。
	 *
	 *	\param[in]	str
	 *		指定文字列。既に設定されていた文字列があった場合は、その末尾に付け足します。
	 *
	 *	\param[in]	code	文字コード
	 *
	 *	\sa initFont(), drawText(const std::string, bool, fk_StringCode)
	 */
	void		drawText(const std::string str, fk_StringCode code = FK_STR_SJIS);

	//! 初期化設定付き文字列表示関数
	/*!
	 *	指定された文字列を表示する画像を設定します。
	 *	本関数を実行する前に、事前に initFont() でフォント指定を行う必要があります。
	 *
	 *	\note
	 *		fk_SpriteModel::text メンバを制御して表示方法を変更したい場合は、
	 *		本関数を実行する前に行う必要があります。
	 *		事後に変更しても有効にならないので注意してください。
	 *
	 *	\param[in]	str		指定文字列
	 *
	 *	\param[in]	mode
	 *		true を渡すとこれまでに入力した文字列を一旦消去し、
	 *		新たに文字列を生成します。
	 *		false を渡すと、 drawText(const std::string, fk_StringCode) と同様に、
	 *		これまでに入力した文字列への付け足しを行います。
	 *
	 *	\param[in]	code	文字コード
	 *
	 *	\sa initFont(), drawText(const std::string, fk_StringCode)
	 */
	void		drawText(const std::string str, bool mode, fk_StringCode code = FK_STR_SJIS);

	//! 文字列消去関数
	/*!
	 *	drawText() 関数によって作成した文字列を消去します。
	 *
	 *	\sa drawText(const std::string, fk_StringCode),
	 *		drawText(const std::string, bool, fk_StringCode)
	 */
	void		clearText(void);

#ifndef FK_DOXYGEN_USER_PROCESS
	void		MakePixelBase(fk_Window *argWin, fk_Scene *argScn);
	void		SetFinalizeMode(void);
#endif

};

#endif
