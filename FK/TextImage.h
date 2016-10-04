#ifndef __FK_TEXTIMAGE_HEADER__
#define __FK_TEXTIMAGE_HEADER__

#include <FK/Image.h>
#include <FK/UniCode.h>
#include <FK/Material.h>

#include <string>
#include <vector>

class fk_FTGlyph;
class fk_FTFace;

//! 文字列板の文字列配置を表す列挙型
enum fk_TextAlign {
	FK_ALIGN_LEFT,		//!< 左寄せ
	FK_ALIGN_CENTER,	//!< 中寄せ
	FK_ALIGN_RIGHT		//!< 右寄せ
};

//! 文字列板の文字送りモードを表す列挙型
enum fk_TextSendingMode {
	FK_SENDING_ALL,		//!< 全体一括
	FK_SENDING_CHAR,	//!< 文字単位
	FK_SENDING_LINE		//!< 行単位
};


//! 文字列板を管理するクラス
/*!
 *	このクラスは、文字列板を制御する機能を提供します。
 *
 *  本クラスは fk_Image の派生クラスであり、本質的には画像を意味します。
 *	通常の画像に対し、文字列を表示することに特化したクラスです。
 *	このクラスを用いて作成した文字列を矩形テクスチャとすることで、
 *	シーン上にメッセージを表示することができます。
 *	実質的には通常の矩形テクスチャとなりますので、
 *	単純に画面に文字を表示するだけではなく、
 *	3次元空間中に自由に配置することができます。
 *
 *	文字列画像生成に際しては、複数行を一枚の画像中に表示することができます。
 *	その際、左寄り、中寄り、右寄りといったアライメントや、
 *	画像端からのマージンなども細かく設定することができます。
 *
 *	また、本クラスの特徴的な機能として「文字送り」があります。
 *	これは、初期状態として全ての文字が表示されていない状態にしておき、
 *	一文字ずつ、あるいは一行ずつ順番に表示していくという機能です。
 *
 *	本クラスを用いる場合、以下の順番で処理を進める必要があります。
 *		-# フォント情報の入力 (initFont())
 *		-# 描画色、配置などの各種設定
 *		-# 文字列の入力
 *		.
 *	これは、実際の画像生成を文字列データ入力の段階で行うため、
 *	それ以外の設定を事前にしておかなければならないためです。
 *	詳細はユーザーズマニュアルの「文字列板」の項目を参照して下さい。
 *
 *	なお、文字列板はその性質上、常に画面上で最前面に表示しておきたい場合が多くあります。
 *	これは、シーン登録においてオーバーレイモデルとして登録することで容易に実現できます。
 *	詳細は fk_DisplayLink::entryOverlayModel() の解説を参照して下さい。
 *
 *	\sa fk_Image, fk_UniStr, fk_RectTexture, fk_Scene, fk_SpriteModel
 */

#ifndef FK_DOXYGEN_USER_PROCESS
typedef std::vector<unsigned char>	fk_GlyphBuffer;
#endif

class fk_TextImage : public fk_Image {
 private:

	fk_FTFace				*face;
	int						dpi, ptsize;
	int						boldStrength;
	int						lineSkip, charSkip, spaceLineSkip;
	int						maxHeight, maxWidth;
	std::vector<fk_Rect>	lineArray;
	std::vector<fk_Rect>	charArray;
	std::vector<int>		lineMap;
	int						minWidth;
	int						upOffset, downOffset, leftOffset, rightOffset;
	bool					smoothFlg;
	fk_Color				fgColor, bgColor, shadowColor;
	fk_TextAlign			alignMode;
	std::vector<fk_Image *>	charImages;
	fk_TextSendingMode		sendingMode;
	int						sendPos;
	bool					shadowMode;
	fk_Dimension			shadowOffset;
	fk_UniStr				strData;
	bool					monospaceMode;
	int						monospaceSize;
	
	int						LayoutGlyphs(std::vector<fk_FTGlyph *> *);
	void					DumpRasterMap(int, int *, int *,
										  std::vector<fk_FTGlyph *> *);
	void					FreeGlyph(std::vector<fk_FTGlyph *> *);

	void					CalcTextOffset(void);
	void					ReCalcCharOffset(void);
	void					InitTextImage(void);
	void					CopyCharImage(int);
	void					ClearCharImages(void);
	void					MakeColorScale(const fk_Color &, const fk_Color &, int *);
	int						GetPixel(fk_GlyphBuffer *, int, int, int, int);
	
 public:
	//! コンストラクタ
	fk_TextImage(void);

	//! デストラクタ
	virtual ~fk_TextImage();


	//! \name フォント関連関数
	//@{

	//! フォント情報入力関数
	/*!
	 *	フォントの入力を行います。
	 *	ここで指定するものは TrueType 形式のフォントファイルとなります。
	 *	通常は「ttf」あるいは「ttc」という拡張子のファイルとなっています。
	 *
	 *	なお、この関数は loadUniStr() や loadStrFile()
	 *	などの文字列入力よりも先に行っておく必要があります。
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
	bool	initFont(const std::string fontFileName);

	//! フォント解像度設定関数
	/*!
	 *	フォントの解像度を設定します。
	 *	解像度を高くするほど高精細な画像となりますが、
	 *	画像サイズが大きくなるため描画時の負担が高くなっていきます。
	 *	デフォルトでは 48 に設定されています。
	 *
	 *	\note
	 *		機能的には setPTSize() とほとんど同義になりますが、
	 *		フォントによっては解像度が高い場合とサイズが大きい場合では
	 *		異なった描画結果となることがあります。
	 *
	 *	\param[in]	dpi		解像度
	 *
	 *	\sa setPTSize()
	 */
	void	setDPI(int dpi);

	//! フォント解像度参照関数
	/*!
	 *	現在設定されているフォントの解像度を取得します。
	 *
	 *	\return		解像度
	 *
	 *	\sa setDPI()
	 */
	int		getDPI(void) const;

	//! フォントサイズ設定関数
	/*!
	 *	フォントのサイズを設定します。
	 *	サイズを大きくするほど高精細な画像となりますが、
	 *	画像サイズが大きくなるため描画時の負担が高くなっていきます。
	 *	デフォルトでは 48 に設定されています。
	 *
	 *	\note
	 *		機能的には setDPI() とほとんど同義になりますが、
	 *		フォントによっては解像度が高い場合とサイズが大きい場合では
	 *		異なった描画結果となることがあります。
	 *
	 *	\param[in]	size	フォントの大きさ
	 *
	 *	\sa setDPI()
	 */
	void	setPTSize(int size);

	//! フォントサイズ参照関数
	/*!
	 *	現在設定されているフォントサイズを取得します。
	 *
	 *	\return		フォントサイズ
	 *
	 *	\sa setPTSize()
	 */
	int		getPTSize(void) const;

	//! 太さ値設定関数
	/*!
	 *	文字の太さを数値に応じて太くします。
	 *	高い値であるほど、線が太くなっていきます。
	 *	デフォルトは 1 となっています。
	 *	太さの度合いについては、解像度やフォントサイズに依存するので、
	 *	それぞれと合わせて調整する必要があります。
	 *
	 *	\param[in]	str		太さ値
	 *
	 *	\sa setDPI(), setPTSize()
	 */
	void	setBoldStrength(int str);

	//! 太さ値参照関数
	/*!
	 *	現在設定されている太さ値を取得します。
	 *
	 *	\return		太さ値
	 *
	 *	\sa setBoldStrength()
	 */
	int		getBoldStrength(void) const;

	//! 影付け効果設定関数
	/*!
	 *	表示文字に対し、影付け効果を有無を設定します。
	 *	デフォルトでは無効となっています。
	 *
	 *	\param[in]	mode
	 *		true の場合有効、false の場合無効となります。
	 *
	 *	\sa setShadowOffset(), setShadowColor(fk_Color)
	 */
	void	setShadowMode(bool mode);

	//! 影付け効果参照関数
	/*!
	 *	影付け効果の有無を取得します。
	 *
	 *	\return		有効である場合 true を、無効である場合 false を返します。
	 *
	 *	\sa setShadowMode()
	 */
	bool	getShadowMode(void) const;

	//! 影付けずらし幅設定関数
	/*!
	 *	影付け効果の際、影のずらし幅を設定します。
	 *
	 *	\param[in]	x
	 *		横方向のずれを設定します。単位はピクセルです。
	 *		正の値で右方向、負の値で左方向にずらします。
	 *	\param[in]	y
	 *		縦方向のずれを設定します。単位はピクセルです。
	 *		正の値で下方向、負の値で上方向にずらします。
	 *
	 *	\sa setShadowMode(), setShadowColor(fk_Color)
	 */
	void	setShadowOffset(int x, int y);

	//! 影付けずらし幅参照関数
	/*!
	 *	影付け効果の際の、影のずらし幅を取得します。
	 *
	 *	\return		ずらし幅
	 *
	 *	\sa setShadowOffset(), fk_Dimension
	 */
	fk_Dimension	getShadowOffset(void) const;

	//! 影付け色設定関数1
	/*!
	 *	影付け効果の際の、影の色を設定します。透過色設定も有効となります。
	 *
	 *	\param[in]	col		影色
	 *
	 *	\sa setShadowMode(), setShadowOffset(), fk_Color
	 */
	void	setShadowColor(fk_Color col);

	//! 影付け色設定関数2
	/*!
	 *	影付け効果の際の、影の色を設定します。透過色設定も有効となります。
	 *	各要素値については fk_Color に準じます。
	 *
	 *	\param[in]	r		影色の R 値(赤)要素値
	 *	\param[in]	g		影色の G 値(緑)要素値
	 *	\param[in]	b		影色の B 値(青)要素値
	 *	\param[in]	a		影色の A 値(透過)要素値
	 *
	 *	\sa setShadowMode(), setShadowOffset(), fk_Color
	 */
	void	setShadowColor(float r, float g, float b, float a);

	//! 影付け色設定関数3
	/*!
	 *	影付け効果の際の、影の色を設定します。透過色設定も有効となります。
	 *	各要素値については fk_Color に準じます。
	 *
	 *	\param[in]	r		影色の R 値(赤)要素値
	 *	\param[in]	g		影色の G 値(緑)要素値
	 *	\param[in]	b		影色の B 値(青)要素値
	 *	\param[in]	a		影色の A 値(透過)要素値
	 *
	 *	\sa setShadowMode(), setShadowOffset(), fk_Color
	 */
	void	setShadowColor(double r, double g, double b, double a);

	//! 影付け色参照関数
	/*!
	 *	影付け効果の際の、影の色を取得します。
	 *
	 *	\return		影色
	 *
	 *	\sa setShadowColor(fk_Color), fk_Color
	 */
	fk_Color	getShadowColor(void) const;
	//@}

	//! \name 描画属性関連関数
	//@{

	//! 文字色設定関数1
	/*!
	 *	文字色を設定します。透過色設定も有効となります。
	 *
	 *	\param[in]	col		文字色
	 *
	 *	\sa setBackColor(fk_Color), setSmoothMode()
	 */
	void	setForeColor(fk_Color col);

	//! 文字色設定関数2
	/*!
	 *	文字色を設定します。透過色設定も有効となります。
	 *	各要素値については fk_Color に準じます。
	 *
	 *	\param[in]	r		文字色の R 値(赤)要素値
	 *	\param[in]	g		文字色の G 値(緑)要素値
	 *	\param[in]	b		文字色の B 値(青)要素値
	 *	\param[in]	a		文字色の A 値(透過)要素値
	 *
	 *	\sa setBackColor(float, float, float, float),
	 *		setSmoothMode(), fk_Color
	 */
	void	setForeColor(float r, float g, float b, float a);

	//! 文字色設定関数3
	/*!
	 *	文字色を設定します。透過色設定も有効となります。
	 *	各要素値については fk_Color に準じます。
	 *
	 *	\param[in]	r		文字色の R 値(赤)要素値
	 *	\param[in]	g		文字色の G 値(緑)要素値
	 *	\param[in]	b		文字色の B 値(青)要素値
	 *	\param[in]	a		文字色の A 値(透過)要素値
	 *
	 *	\sa setBackColor(double, double, double, double),
	 *		setSmoothMode(), fk_Color
	 */
	void	setForeColor(double r, double g, double b, double a);

	//! 文字色参照関数
	/*!
	 *	文字色を取得します。
	 *
	 *	\return		文字色
	 *
	 *	\sa setForeColor(fk_Color), fk_Color
	 */
	fk_Color	getForeColor(void) const;

	//! 背景色設定関数1
	/*!
	 *	背景色を設定します。透過色設定も有効となります。
	 *
	 *	\param[in]	col		背景色
	 *
	 *	\sa setForeColor(fk_Color), setSmoothMode()
	 */
	void	setBackColor(fk_Color col);

	//! 背景色設定関数2
	/*!
	 *	背景色を設定します。透過色設定も有効となります。
	 *	各要素値については fk_Color に準じます。
	 *
	 *	\param[in]	r		背景色の R 値(赤)要素値
	 *	\param[in]	g		背景色の G 値(緑)要素値
	 *	\param[in]	b		背景色の B 値(青)要素値
	 *	\param[in]	a		背景色の A 値(透過)要素値
	 *
	 *	\sa setForeColor(float, float, float, float),
	 *		setSmoothMode(), fk_Color
	 */
	void	setBackColor(float r, float g, float b, float a);

	//! 背景色設定関数3
	/*!
	 *	背景色を設定します。透過色設定も有効となります。
	 *	各要素値については fk_Color に準じます。
	 *
	 *	\param[in]	r		背景色の R 値(赤)要素値
	 *	\param[in]	g		背景色の G 値(緑)要素値
	 *	\param[in]	b		背景色の B 値(青)要素値
	 *	\param[in]	a		背景色の A 値(透過)要素値
	 *
	 *	\sa setForeColor(double, double, double, double),
	 *		setSmoothMode(), fk_Color
	 */
	void	setBackColor(double r, double g, double b, double a);

	//! 背景色参照関数
	/*!
	 *	背景色を取得します。
	 *
	 *	\return		背景色
	 *
	 *	\sa setBackColor(fk_Color), fk_Color
	 */
	fk_Color	getBackColor(void) const;

	//! アンチエイリアシング効果設定関数
	/*!
	 *	表示文字に対し、アンチエイリアシング効果の有無を設定します。
	 *	この設定を有効とした場合、
	 *	表示の際に文字色と背景色の中間色も描画に利用されるようになります。
	 *	逆に無効とした場合、描画の際には文字色と背景色以外は利用されなくなります。
	 *	デフォルトでは有効となっています。
	 *
	 *	\param[in]	mode
	 *		true の場合有効、false の場合無効となります。
	 *
	 *	\sa setForeColor(fk_Color), setBackColor(fk_Color)
	 */
	void	setSmoothMode(bool mode);

	//! アンチエイリアシング効果参照関数
	/*!
	 *	アンチエイリアシング効果の有無を取得します。
	 *
	 *	\return		有効である場合 true を、無効である場合 false を返します。
	 *
	 *	\sa setSmoothMode()
	 */
	bool	getSmoothMode(void) const;

#ifndef FK_DOXYGEN_USER_PROCESS
	void	setSmoothFlg(bool);
	bool	getSmoothFlg(void) const;
#endif

	
	//@}

	//! \name 文字配置事前設定関連関数

	//@{
	//! 等幅表示設定関数
	/*!
	 * 	文字の等幅表示設定を行います。
	 *	設定を有効とした場合、半角全角問わず全ての文字を等幅で表示します。
	 *	デフォルトでは無効となっています。
	 *	なお、 setCharSkip() によって設定する文字間幅は等幅においても有効となります。
	 *
	 *	\param[in]	mode
	 *		true の場合有効、false の場合無効となります。
	 *
	 *	\note
	 *		setMonospaceSize() によって文字幅を設定しないと、
	 *		文字幅が 0 として表示されてしまうため、何も表示されていない状況となります。
	 *
	 *	\sa getMonospaceMode(), setMonospaceSize(), setCharSkip()
	 */
	void	setMonospaceMode(bool mode);

	//! 等幅表示設定参照関数
	/*!
	 *	等幅表示設定の有無を取得します。
	 *
	 *	\return		有効である場合 true を、無効である場合 false を返します。
	 *
	 *	\sa setMonospaceMode()
	 */
	bool	getMonospaceMode(void) const;

	//! 等幅表示文字幅設定関数
	/*!
	 *	等幅表示の際の文字幅を設定します。単位はピクセルとなります。
	 *	デフォルトでは 0 が設定されています。
	 *
	 *	\param[in]	size	文字幅
	 *
	 *	\note
	 *		等幅表示は、 setMonospaceMode()
	 *		で設定を有効としなければ等幅表示とはなりません。
	 *
	 *	\sa setMonospaceMode(), getMonospaceSize(), setCharSkip()
	 */
	void	setMonospaceSize(int size);

	//! 等幅表示文字幅参照関数
	/*!
	 *	等幅表示の際の文字幅を参照します。単位はピクセルとなります。
	 *
	 *	\return		文字幅
	 *
	 *	\sa setMonospaceSize(), getCharSkip()
	 */
	int		getMonospaceSize(void) const;

	//! 文字間幅設定関数
	/*!
	 *	文字同士の横方向の空白幅を設定します。
	 *	単位はピクセルとなります。
	 *	デフォルトは 0 に設定されています。
	 *
	 *	文字との対比については、解像度やフォントサイズに応じて変わってきます。
	 *	つまり、解像度やフォントサイズが大きい場合、
	 *	空白を作るには大きな値が必要となります。
	 *	従って、解像度やフォントサイズを変更した場合には、
	 *	この値も再度調整する必要があります。
	 *
	 *	\param[in]	skip		空白幅
	 *
	 *	\sa setLineSkip(), setSpaceLineSkip(), setOffset(),
	 *		setDPI(), setPTSize(), setMonospaceMode(), setMonospaceSize()
	 */
	void	setCharSkip(int skip);

	//! 文字間幅参照関数
	/*!
	 *	文字同士の横方向の空白幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\return		空白幅
	 *
	 *	\sa setCharSkip()
	 */
	int		getCharSkip(void) const;

	//! 行間幅設定関数
	/*!
	 * 	行同士の縦方向の空白幅を取得します。
	 *	単位はピクセルとなります。
	 *	デフォルトは 0 に設定されています。
	 *
	 *	文字との対比については、解像度やフォントサイズに応じて変わってきます。
	 *	つまり、解像度やフォントサイズが大きい場合、
	 *	空白を作るには大きな値が必要となります。
	 *	従って、解像度やフォントサイズを変更した場合には、
	 *	この値も再度調整する必要があります。
	 *
	 *	\param[in]	skip		空白幅
	 *
	 *	\sa setCharSkip(), setSpaceLineSkip(), setOffset(),
	 *		setDPI(), setPTSize()
	 */
	void	setLineSkip(int skip);

	//! 行間幅参照関数
	/*!
	 *	行同士の縦方向の空白幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\return		空白幅
	 *
	 *	\sa setLineSkip()
	 */
	int		getLineSkip(void) const;

	//! 空行縦幅設定関数
	/*!
	 *	文字列中に空行が入っていた場合の、その縦幅を設定します。
	 *	単位はピクセルとなります。
	 *	この値が 0 である場合、空行は結果的に省略されることになります。
	 *
	 *	文字との対比については、解像度やフォントサイズに応じて変わってきます。
	 *	つまり、解像度やフォントサイズが大きい場合、
	 *	空白を作るには大きな値が必要となります。
	 *	従って、解像度やフォントサイズを変更した場合には、
	 *	この値も再度調整する必要があります。
	 *
	 *	\param[in]	skip	縦幅
	 *
	 *	\sa setCharSkip(), setLineSkip(), setOffset(),
	 *		setDPI(), setPTSize()
	 */
	void	setSpaceLineSkip(int skip);

	//! 空行縦幅参照関数
	/*!
	 *	文字列中に空行が入っていた場合の、その縦幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\return		縦幅
	 *
	 *	\sa setSpaceLineSkip()
	 */
	int		getSpaceLineSkip(void) const;

	//! オフセット設定関数
	/*!
	 *	文字が実際に表示されている部分と、画面の縁までの幅を設定します。
	 *	単位はピクセルとなります。
	 *	デフォルトでは、全て 0 に設定されています。
	 *
	 *	文字との対比については、解像度やフォントサイズに応じて変わってきます。
	 *	つまり、解像度やフォントサイズが大きい場合、
	 *	空白を作るには大きな値が必要となります。
	 *	従って、解像度やフォントサイズを変更した場合には、
	 *	この値も再度調整する必要があります。
	 *
	 *	\param[in]	up		上幅
	 *	\param[in]	down	下幅
	 *	\param[in]	left	左幅
	 *	\param[in]	right	右幅
	 *
	 *	\sa setCharSkip(), setLineSkip(), setSpaceLineSkip(),
	 *		setDPI(), setPTSize()
	 */
	void	setOffset(int up, int down, int left, int right);

	//! オフセット上幅参照関数
	/*!
	 *	文字が実際に表示されている部分のうち、上側の縁までの幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\return		上幅
	 *
	 *	\sa setOffset()
	 */
	int		getUpOffset(void) const;

	//! オフセット下幅参照関数
	/*!
	 *	文字が実際に表示されている部分のうち、下側の縁までの幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\return		下幅
	 *
	 *	\sa setOffset()
	 */
	int		getDownOffset(void) const;

	//! オフセット左幅参照関数
	/*!
	 *	文字が実際に表示されている部分のうち、左側の縁までの幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\return		左幅
	 *
	 *	\sa setOffset()
	 */
	int		getLeftOffset(void) const;

	//! オフセット右幅参照関数
	/*!
	 *	文字が実際に表示されている部分のうち、右側の縁までの幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\return		右幅
	 *
	 *	\sa setOffset()
	 */
	int		getRightOffset(void) const;

	//! 文字列寄せ方向(アライメント)設定関数
	/*!
	 *	文字列を表示する際の、文字寄せ方向(アライメント)を設定します。
	 *
	 *	複数行に渡る文字列の場合で、各行の横幅が異なる場合や、
	 *	setMinLineWidth() によって画像の横幅をあらかじめ設定した場合などは、
	 *	行の横幅が画像の横幅に満たない状況が生じます。
	 *	このような行に対し、本関数でどちら側に寄るのかを設定します。
	 *	デフォルトは FK_ALIGN_LEFT 、つまり左寄せとなっています。
	 *
	 *	\param[in]	align		アライメント
	 *
	 *	\sa fk_TextAlign, setMinLineWidth()
	 */
	void	setAlign(fk_TextAlign align);

	//! 文字列寄せ方向(アライメント)参照関数
	/*!
	 *	文字列を表示する際の、文字寄せ方向(アライメント)を取得します。
	 *
	 *	\return		アライメント
	 *
	 *	\sa setAlign()
	 */
	fk_TextAlign		getAlign(void) const;

	//! 画像最小横幅設定関数
	/*!
	 *	生成される文字列板画像の横幅の最小値を設定します。
	 *	単位はピクセルとなります。
	 *	デフォルトは 0 に設定されています。
	 *
	 *	通常、文字列板として生成される画像の横幅は、
	 *	入力した文字列に依存します。
	 *	行の文字数が多ければ幅は広がり、逆に少ない場合は狭まります。
	 *	このような異なる画像を同じテクスチャ画像として連続に表示した場合、
	 *	一文字の横幅が画像によって変動してしまうという現象が生じます。
	 *	これは、あまり見栄えが良いとは言えません。
	 * 	そのような場合、本関数を用いて十分な横幅を予め確保しておきます。
	 *	そうすることで、文字列はアライメントに従って適切に配置され、
	 *	文字の幅も画像によって変わることはありません。
	 *
	 *	ただし、ここで設定した横幅を超える幅を持つ行が発生した場合、
	 *	画像の幅はその行による幅に設定されることになります。
	 *
	 *	\param[in]	width		画像最小横幅
	 *
	 *	\sa setAlign()
	 */
	void	setMinLineWidth(int width);

	//! 画像最小横幅参照関数
	/*!
	 *	生成される文字列板画像の横幅の最小値を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\return		画像最小横幅
	 *
	 *	\sa setMinLineWidth()
	 */
	int		getMinLineWidth(void) const;

	//@}

	//! \name 文字列入力関数
	//@{

	//! 文字列データ入力関数
	/*!
	 *	fk_UniStr 型のインスタンスに格納されている文字列を入力します。
	 *
	 *	文字列板画像は、
	 *	この関数かまたは loadStrFile() が呼ばれた時点で生成されます。
	 *	従って、色や配置などの設定は本関数を呼ぶ前に行わなければなりません。
	 *
	 *	既に本関数を実行したインスタンスに対し、改めて本関数を実行することは可能です。
	 *	その場合は、新たな文字列と設定に基づき、文字列板画像を再構築します。
	 *
	 *	\param[in]	str		文字列が格納されているインスタンス
	 *
	 *	\return		文字列板生成に成功すれば true を、失敗すれば false を返します。
	 *
	 *	\sa loadStrFile()
	 */
	bool	loadUniStr(fk_UniStr *str);

	//! 文字列データファイル入力関数
	/*!
	 *	テキストファイルに入っている文字列を入力します。
	 *
	 *	文字列板画像は、
	 *	この関数かまたは loadUniStr() が呼ばれた時点で生成されます。
	 *	従って、色や配置などの設定は本関数を呼ぶ前に行わなければなりません。
	 *
	 *	既に本関数を実行したインスタンスに対し、改めて本関数を実行することは可能です。
	 *	その場合は、新たな文字列と設定に基づき、文字列板画像を再構築します。
	 *
	 *	\param[in]	fileName		ファイル名
	 *
	 *	\param[in]	code
	 *		入力する文字列の想定日本語コード。
	 *		サポートしているのは JISコード、SJISコード、EUC、UTF-16 です。
	 *		具体的な指定値は fk_StringCode のリストを参照して下さい。
	 *
	 *	\return		文字列板生成に成功すれば true を、失敗すれば false を返します。
	 */
	bool	loadStrFile(const std::string fileName,
						fk_StringCode code = FK_STR_UTF16);
	//@}

	//! \name 文字列入力後情報参照関数
	//@{

	//! 行数参照関数
	/*!
	 *	入力した文字列の行数を取得します。
	 *
	 *	\return		行数
	 *
	 *	\sa loadUniStr(), loadStrFile()
	 */
	int		getLineNum(void) const;

	//! 行中文字数参照関数
	/*!
	 *	入力した文字列中の、指定した行の文字数を取得します。
	 *
	 *	\param[in]	num		行番号。最初の行は 0 となります。
	 *
	 *	\return		文字数
	 *
	 *	\sa getLineNum(), getAllCharNum(), loadUniStr(), loadStrFile()
	 */
	int		getLineCharNum(int num) const;

	//! 文字数参照関数
	/*!
	 *	入力した文字列の文字数を取得します。
	 *
	 *	\return		文字数
	 *
	 *	\sa getLineNum(), getLineCharNum(), loadUniStr(), loadStrFile()
	 */
	int		getAllCharNum(void) const;

	//! 最大横幅参照関数
	/*!
	 *	入力した文字列のうち、最も横幅が広い行の横幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	画像の横幅を直接取得するには、
	 *	fk_Image::getWidth() を利用して下さい。
	 *
	 *	\return		最大縦幅
	 *
	 *	\sa getMaxLineHeight(), getLineWidth(), setMinLineWidth()
	 */
	int		getMaxLineWidth(void) const;

	//! 最大縦幅参照関数
	/*!
	 *	入力した文字列のうち、最も縦幅が広い行の縦幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	画像全体の縦幅を取得するには、
	 *	fk_Image::getHeight() を利用して下さい。
	 *
	 *	\note
	 *		TrueType 形式のフォント、特に半角英数字については、
	 *		横幅、縦幅共に文字によって異なります。
	 *		結果として、行の縦幅も構成される文字によって異なってくることになります。
	 *
	 *	\return		最大縦幅
	 *
	 *	\sa getMaxLineWidth(), getLineHeight()
	 */
	int		getMaxLineHeight(void) const;

	//! 行横幅参照関数
	/*!
	 *	入力した文字列中の、指定した行の横幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\param[in]	num		行番号。最初の行は 0 となります。
	 *
	 *	\return		横幅
	 *
	 *	\sa getLineHeight(), getMaxLineWidth()
	 */
	int		getLineWidth(int num) const;

	//! 行縦幅参照関数
	/*!
	 *	入力した文字列中の、指定した行の縦幅を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\note
	 *		TrueType 形式のフォント、特に半角英数字については、
	 *		横幅、縦幅共に文字によって異なります。
	 *		結果として、行の縦幅も構成される文字によって異なってくることになります。
	 *
	 *	\param[in]	num		行番号。最初の行は 0 となります。
	 *
	 *	\return		縦幅
	 *
	 *	\sa getLineWidth(), getMaxLineHeight()
	 */
	int		getLineHeight(int num) const;

	//! 行開始位置 x 成分取得関数
	/*!
	 *	入力した文字列中の、
	 *	指定した行の開始位置(文字列左下部分)の x 成分を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\param[in]	num		行番号。最初の行は 0 となります。
	 *
	 *	\return		行左下部分の x 成分
	 *
	 *	\sa getLineStartYPos()
	 */
	int		getLineStartXPos(int num) const;

	//! 行開始位置 y 成分取得関数
	/*!
	 *	入力した文字列中の、
	 *	指定した行の開始位置(文字列左下部分)の y 成分を取得します。
	 *	単位はピクセルとなります。
	 *
	 *	\param[in]	num		行番号。最初の行は 0 となります。
	 *
	 *	\return		行左下部分の y 成分
	 *
	 *	\sa getLineStartXPos()
	 */
	int		getLineStartYPos(int num) const;

	//@}

	//! \name 文字送り関連関数
	//@{
	
	//! 文字送りモード設定関数
	/*!
	 *	この関数は、文字送りのモードを設定します。
	 *
	 *	「文字送り」とは、読み込んだ文字列を最初は表示せず、
	 *	一文字ずつ、あるいは一行ずつ徐々に表示していく機能のことです。
	 *	文字送りを有効とした場合、
	 *	send() を呼び出すごとに一文字ずつ、あるいは一行ずつが表示されていきます。
	 *	一度表示した文字列については、
	 *	clear() を呼び出すことで初期状態
	 *	(文字が表示されていない状態)に戻すことができます。
	 *
	 *	本関数は、文字列を loadUniStr() や
	 *	loadStrFile() で入力する前に設定しておくことが可能です。
	 *	また、入力後に動的に変更することも可能です。
	 *
	 *	\param[in]	mode
	 *		文字送りモード。以下の値が設定できます。
	 *		- FK_SENDING_CHAR: 一文字ずつ送るモード。
	 *		- FK_SENDING_LINE: 一行ずつ送るモード。
	 *		- FK_SENDING_ALL: 文字送りを無効とするモード。
	 *
	 *	\sa send(), finish(), clear()
	 */
	void	setSendingMode(fk_TextSendingMode mode);

	//! 文字送りモード参照関数
	/*!
	 *	現在の文字送りモードを取得します。
	 *
	 *	\return		文字送りモード
	 *
	 *	\sa setSendingMode()
	 */
	fk_TextSendingMode	getSendingMode(void) const;

	//! 文字送り実行関数
	/*!
	 *	setSendingMode() で指定したモードに従い、
	 *	文字送りを行います。
	 *
	 *	\return
	 *		文字送りが行われたら true を返します。
	 *		既に全ての文字が表示されていた状態で本関数を呼び出した場合は、
	 *		false を返します。
	 *
	 *	\sa setSendingMode(), finish(), clear()
	 */
	bool	send(void);

	//! 文字送り完了関数
	/*!
	 *	文字送りが有効である場合に、
	 *	まだ表示されていない文字を全て表示させます。
	 *
	 *	\return
	 *		本関数を呼び出した時点で、まだ表示されていない文字があり、
	 *		新たに表示された文字が存在した場合には true を返します。
	 *		呼び出した時点で既に全ての文字が表示されており、
	 *		新たに表示された文字が存在しなかった場合には false を返します。
	 *
	 *	\sa setSendingMode(), send(), clear()
	 */
	bool	finish(void);

	//! 文字送り初期化関数
	/*!
	 *	文字送りが有効である場合に、
	 *	全ての文字を初期状態、つまり非表示の状態に戻します。
	 *
	 *	\return
	 *		本関数を呼び出した時点で、既に表示されていた文字があり、
	 *		なんらかの文字が消去された場合には true を返します。
	 *		呼び出した時点で文字が表示されておらず、
	 *		結果的に非表示となった文字が存在しなかった場合には false を返します。
	 *
	 *	\sa setSendingMode(), send(), finish()
	 */
	bool	clear(void);

	//@}

	//! \name キャッシュ関連関数
	//@{
	//! キャッシュ機能制御関数
	/*!
	 *	この関数は、フォントデータのキャッシュの制御を行います。
	 *	デフォルトでは無効となっています。
	 *
	 *	文字列の画像を生成する際には、
	 *	入力されたフォントデータからビットマップとしての
	 *	画像情報に変換するという処理がなされます。
	 *	同じ文字に対してこの処理を行うことは、計算時間の点で無駄となります。
	 *	そこで、 fk_TextImage には一度得た画像情報を保存しておき、
	 *	同じ文字が登場した際には再利用するという機能があります。
	 *	これが「キャッシュ機能」です。
	 *	特に数字やアルファベット、平仮名などは再利用する頻度が高いため、
	 *	本機能を有効とすることで処理が高速となる利点があります。
	 *
	 *	一方、キャッシュ機能はメモリの利用量が増えることを意味します。
	 *	高い解像度やフォントサイズを用いている場合は、
	 *	キャッシュのメモリ利用量も膨大となっていきますので、
	 *	場合によっては処理速度がむしろ低下することもありえます。
	 *
	 *	ここで利用されるキャッシュデータは、
	 *	インスタンス毎ではなくシステム全体で共有されます。
	 *	従って、異なるインスタンスで読み込んだ文字に関しても
	 *	キャッシュ効果が働くことになります。
	 *
	 *	\param[in]	mode
	 *		true であれば有効、false であれば無効とします。
	 *
	 *	\sa clearCache()
	 */
	static void		setCacheMode(bool mode);

	//! キャッシュ機能有無効参照関数
	/*!
	 * フォントデータのキャッシュ機能の有無効を取得します。
	 *
	 *	\return
	 *		有効であれば true を、無効であれば false を返します。
	 *
	 *	\sa setCacheMode()
	 */
	static bool		getCacheMode(void);

	//! キャッシュ初期化関数
	/*!
	 *	キャッシュ機能が有効である場合に、
	 *	これまでのキャッシュデータをすべて消去します。
	 *
	 *	\sa setCacheMode()
	 */
	static void		clearCache(void);
	//@}
};

#endif // !__FK_TEXTIMAGE_HEADER__

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
