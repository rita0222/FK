#ifndef	__FK_TEXTURE_HEADER__
#define	__FK_TEXTURE_HEADER__

#include <FK/Shape.h>
#include <FK/Image.h>
#include <FK/IndexFace.h>

class fk_MQOParser;
class fk_IndexFaceSet;

//! テクスチャモードを表す列挙型
enum fk_TexMode {
	FK_TEX_MODULATE,	//!< 積算モード
	FK_TEX_REPLACE,		//!< 画像モード
	FK_TEX_DECAL		//!< 線形補間モード
};

//! テクスチャ描画品質を表す列挙型
enum fk_TexRendMode {
	FK_TEX_REND_NORMAL,	//!< 標準品質
	FK_TEX_REND_SMOOTH	//!< 高品質
};

//! テクスチャ座標を管理するクラス
/*!
 *	このクラスは、テクスチャ座標に関する基本的な機能を提供します。
 *
 *	テクスチャ座標系とは、画像のピクセルサイズにかかわらず左下を (0, 0)、
 *	右上端を (1, 1) として、画像の任意の位置をパラメータとして表す座標系のことです。
 *	例えば、画像の中心は (0.5, 0,5) として表されます。
 *	テクスチャ座標系では、横方向が x 成分、縦方向が y 成分となります。
 *
 *	\sa fk_TriTexture, fk_MeshTexture, fk_IFSTexture
 */

class fk_TexCoord {

 public:

	float	x;	//!<	x成分
	float	y;	//!<	y成分

	//! コンストラクタ
	/*!
	 *	\param[in]	x	x成分
	 *	\param[in]	y	y成分
	 */
	fk_TexCoord(double x = 0.0, double y = 0.0);

	//! コピーコンストラクタ
	fk_TexCoord(const fk_TexCoord &);

	//! 代入演算子
	fk_TexCoord & operator =(const fk_TexCoord &);

	//! 等号比較演算子
	/*!
	 *	fk_TexCoord では、以下のように記述することで、
	 *	c1 と c2 が等しいかどうかを判断できます。
	 *
	 *		if(c1 == c2) {
	 *			:
	 *			:
	 *		}
	 *
	 *	ここでの比較は、ある程度の計算誤差を許容します。
	 */
	bool	operator ==(const fk_TexCoord &) const;

	//! 成分設定関数
	/*!
	 *	各成分を設定します。
	 *
	 *	\param[in]	x	x成分の値
	 *	\param[in]	y	y成分の値
	 */
	void	set(double x, double y);
};

//! テクスチャ用基底クラス
/*!
 *	このクラスは、テクスチャを表すクラスの基底クラスです。
 *	様々なテクスチャクラスの共通機能を提供します。
 *	クラス自体の主な機能はテクスチャ画像の生成や入力です。
 *
 *	\sa fk_Image, fk_RectTexture, fk_TriTexture, fk_MeshTexture, fk_IFSTexture, fk_Dimension
 */

class fk_Texture: public fk_Shape {
	friend class		fk_TextureDraw;

 private:
	fk_Image			*image;
	fk_Image			localImage;
	fk_TexMode			texMode;
	fk_TexRendMode		texRendMode;
	fk_Palette			localPal;

	bool				GetInitFlag(void);
	void				SetInitFlag(bool);
	fk_TexID			GetTexID(void);
	void				SetTexID(const fk_TexID);

	static void			ClearTexState(fk_Image *);

 protected:

#ifndef FK_DOXYGEN_USER_PROCESS

	void				BaseInit(void);
	bool				IsLocalImage(void);
	void				SetLocalImage(void);

#endif

 public:

#ifndef FK_DOXYGEN_USER_PROCESS

	fk_Texture(fk_Image * = nullptr);
	virtual ~fk_Texture();
	virtual void			init(void) = 0;

#endif

	//! 画像データ設定関数
	/*!
	 *	画像データを設定します。
	 *
	 *	\note
	 *		fk_Texture (およびその派生クラス) では、
	 *		最初から自前の画像データ領域を保持しています。
	 *		この関数はあくまで外部で用意した画像データを
	 *		テクスチャとして利用したい場合に使用するためのものであり、
	 *		必ず設定しなければならないというわけではありません。
	 *
	 *	\param[in]		image		画像データ
	 */
	void					setImage(fk_Image *image);

	//! 画像データ取得関数
	/*!
	 *	現在設定されている画像データを取得します。
	 *
	 *	\return		画像データ
	 */
	fk_Image *				getImage(void);

	//! BMP ファイル入力関数
	/*!
	 *	BMP (Windows Bitmap) 形式のファイルからデータを読み込み、
	 *	テクスチャ画像として設定します。
	 *
	 *	\param[in]	fileName	ファイル名
	 *
	 *	\return	入力に成功すれば true、失敗すれば false を返します。
	 */
	bool					readBMP(std::string fileName);

	//! BMP バッファ入力関数
	/*!
	 *	BMP (Windows Bitmap) 形式のバッファからデータを読み込み、
	 *	テクスチャ画像として設定します。
	 *	fk_ImType 型は、OpenGL をサポートしている環境においては GLubyte、
	 *	サポートしていない環境では unsigned char 型として定義されています。
	 *
	 *	\param[in]	buf		データバッファ
	 *
	 *	\return 入力に成功すれば true、失敗すれば false を返します。
	 */
	bool					readBMPData(fk_ImType *buf);

	//! PNG ファイル入力関数
	/*!
	 *	PNG 形式のファイルからデータを読み込み、
	 *	テクスチャ画像として設定します。
	 *
	 *	\param[in]	fileName	ファイル名
	 *
	 *	\return	入力に成功すれば true、失敗すれば false を返します。
	 */
	bool					readPNG(std::string fileName);

	//! PNG バッファ入力関数
	/*!
	 * 	PNG 形式のバッファからデータを読み込み、
	 *	テクスチャ画像として設定します。
	 *	fk_ImType 型は、OpenGL をサポートしている環境においては GLubyte、
	 *	サポートしていない環境では unsigned char 型として定義されています。
	 *
	 *	\param[in]	buf		データバッファ
	 *
	 *	\return 入力に成功すれば true、失敗すれば false を返します。
	 */
	bool					readPNGData(fk_ImType *buf);

	//! JPEG ファイル入力関数
	/*!
	 *	JPEG 形式のファイルからデータを読み込み、
	 *	テクスチャ画像として設定します。
	 *
	 *	\param[in]	fileName	ファイル名
	 *
	 *	\return	入力に成功すれば true、失敗すれば false を返します。
	 */
	bool					readJPG(std::string fileName);

	//! 画像サイズ取得関数
	/*!
	 *	画像サイズを fk_Dimension 型で取得します。
	 *
	 *	\return		画像サイズ
	 *
	 *	\sa getBufferSize()
	 */
	const fk_Dimension *	getImageSize(void);

	//! 画像バッファサイズ取得関数
	/*!
	 *	実際に画像用データバッファとして確保されているサイズを、
	 *	fk_Dimension 型で返します。
	 *
	 *	\note
	 *		実画像サイズとデータバッファサイズの違いについては、
	 *		fk_Image::getBufferSize() の覚え書きを参照して下さい。
	 *
	 *	\return		データサイズ
	 *
	 *	\sa getImageSize(), fk_Image::getBufferSize()
	 */
	const fk_Dimension *	getBufferSize(void);

	//! テクスチャモード設定関数
	/*!
	 *	テクスチャの描画時における描画色処理モードを設定します。
	 *	これは、ポリゴンに設定されているマテリアルによる発色と、
	 *	テクスチャ画像の色をどのように混成するかを制御するものです。
	 *	それぞれのモードの概要と厳密な計算式を以下に記載します。
	 *	なお、数式中の \f$ C_f \f$ はポリゴン色、
	 *	\f$ C_\alpha \f$ ポリゴンの透明度、
	 *	\f$ T_f \f$ はテクスチャピクセル色、
	 *	\f$ T_\alpha \f$ はテクスチャの透明度を表します。
	 *
	 *	- FK_TEX_MODULATE \n
	 *		この設定では、ポリゴンの色とテクスチャの色を積算します。
	 *		そのため、光源による陰影効果が生じます。
	 *		透明度に関しても積算となります。
	 *		数式として表すと、色と透明度はそれぞれ
	 *		\f[
	 *			(C_f T_f, \; C_\alpha T_\alpha)
	 *		\f]
	 *		となります。
	 *
	 *	- FK_TEX_REPLACE \n
	 *		この設定では、ポリゴンの色は完全に無視され、
	 *		テクスチャのピクセル色がそのまま表示されます。
	 *		そのため、光源による陰影効果が生じません。
	 *		また、テクスチャ画像の透明度はそのまま描画に反映されます。
	 *		数式として表すと、色と透明度はそれぞれ
	 *		\f[
	 *			(T_f, \; T_\alpha)
	 *		\f]
	 *		となります。
	 *
	 *	- FK_TEX_DECAL \n
	 *		この設定では、各ピクセルの透明度に応じて、
	 *		ポリゴン色とピクセル色の混合が行われます。
	 *		光源による陰影効果は、ピクセルの透明度が低い場合に強くなります。
	 *		透明度は、ポリゴンの透明度がそのまま適用されます。
	 *		これを数式として表すと、色と透明度はそれぞれ
	 *		\f[
	 *			(C_f (1-T_\alpha) + T_f T_\alpha, \; C_\alpha)
	 *		\f]
	 *		となります。
	 *	.
	 *	なお、デフォルトでは FK_TEX_MODULATE が設定されています。
	 *
	 *	\param[in]		mode	モード
	 */
	void					setTextureMode(fk_TexMode mode);

	//! テクスチャモード取得関数
	/*!
	 *	現在のテクスチャモードを取得します。
	 *
	 *	\return		テクスチャモード
	 *
	 *	\sa setTextureMode()
	 */
	fk_TexMode				getTextureMode(void);

	//! テクスチャ描画品質設定関数
	/*!
	 *	テクスチャの描画品質を設定します。
	 *	設定可能なモードは以下の通りです。
	 *	- FK_TEX_REND_NORMAL: 標準品質。描画速度を優先します。
	 *	- FK_TEX_REND_SMOOTH: 高品質。画質を優先します。
	 *	.
	 *	なお、デフォルトでは FK_TEX_REND_NORMAL が設定されています。
	 *
	 *	\param[in]	mode	品質モード
	 */
	void					setTexRendMode(fk_TexRendMode mode);

	//! テクスチャ描画品質取得関数
	/*!
	 *	現在設定されているテクスチャ描画品質モードを取得します。
	 *
	 *	\return		品質モード
	 *
	 *	\sa setTexRendMode()
	 */
	fk_TexRendMode			getTexRendMode(void);

	//! 一様色初期化関数1
	/*!
	 *	内部の画像ピクセルを、すべて同じ色で初期化します。
	 *
	 *	\param[in]	color		初期化色
	 *
	 *	\sa fk_Color
	 */
	void					fillColor(const fk_Color &color);

	//! 一様色初期化関数2
	/*!
	 *	内部の画像ピクセルを、すべて同じ色で初期化します。
	 *	色要素は、最小値が 0, 最大値が 255 として解釈します。
	 *
	 *	\param[in]	r		初期化色の赤要素
	 *	\param[in]	g		初期化色の緑要素
	 *	\param[in]	b		初期化色の青要素
	 *	\param[in]	a		初期化色の透明度要素
	 */
	void					fillColor(int r, int g, int b, int a = 0);

	//! 画像データ配列先頭アドレス取得関数	
	/*!
	 *	画像データを実際に格納しているデータ配列の先頭アドレスを参照します。
	 *
	 *	\warning
	 *		この関数は fk_Image の内部構造に強く依存します。
	 *		内部構造は今後の更新で変更される可能性があるため、
	 *		本関数を用いた場合は後方互換性が保証できません。
	 *		また、この関数を用いて得た内部データを更新した場合、
	 *		システム全体の整合性が維持できなくなる可能性があります。
	 *		上記の2点の理由から、この関数の利用は推奨しません。
	 *
	 *	\return
	 *		画像データ配列の先頭アドレス。
	 *		テクスチャ画像が生成、設定されていない場合は nullptr を返します。
	 *
	 *	\sa fk_Image::getBufPointer()
	 */
	const fk_ImType *		getImageBuf(void);
};

//! 矩形テクスチャを生成、管理するクラス
/*!
 *	このクラスは、矩形型のテクスチャを制御する機能を提供します。
 *	テクスチャを表示する方法としては、最も簡単なクラスとなります。
 *
 *	テクスチャ画像を表示する最低限の手順は、以下の通りです。
 *	-# 画像を入力する。
 *	-# setTextureSize() 関数で大きさを設定する。
 *	-# fk_Model に登録する。
 *	.
 *	あとは、他の形状クラスと同様です。
 *
 *	矩形の配置は、モデルの方向ベクトルに垂直となり、
 *	画像の中心とモデルの中心が一致するように配置されます。
 *	また、画像の表側はモデルの後方
 *	(初期状態では +z 方向) 側から見た場合に見えるという点に注意して下さい。
 *
 *	\sa fk_Texture, fk_TriTexture, fk_MeshTexture, fk_IFSTexture
 */

class fk_RectTexture : public fk_Texture {

	friend class		fk_TextureDraw;

 private:

	fk_TexCoord			texSize;
	bool				repeatFlag;
	fk_TexCoord			repeatParam;
	fk_TexCoord			texCoord[2];

 public:

	//! コンストラクタ
	/*!
	 *	\param[in]	image
	 *		テクスチャ画像。省略するか nullptr を代入した場合は、
	 *	   	テクスチャ画像を初期状態では生成しません。
	 */
	fk_RectTexture(fk_Image *image = nullptr);

	//! デストラクタ
	virtual ~fk_RectTexture();

	//! 初期化関数
	/*!
	 *	現在設定されているテクスチャ画像を廃棄し、全ての設定を初期状態に戻します。
	 */
	void				init(void);

	//! テクスチャサイズ設定関数
	/*!
	 *	矩形テクスチャの大きさを設定します。
	 *
	 *	\param[in]	w		横幅
	 *	\param[in]	h		縦幅
	 *
	 *	\return
	 *		横幅、縦幅のいずれかで 0 以下の値が入力されていた場合、
	 *		false を返します。設定に成功した場合は true を返します。
	 */
	bool				setTextureSize(double w, double h);

	//! テクスチャサイズ参照関数
	/*!
	 *	矩形テクスチャの大きさを取得します。
	 *
	 *	\return		矩形テクスチャの大きさ
	 */
	fk_TexCoord			getTextureSize(void);

	//! リピートモード設定関数
	/*!
	 *	リピートモードの設定を行います。
	 *	リピートモードを有効にすると、画像が縦横に行列上に並んでいる状態になります。
	 *	並ぶ枚数については、 setRepeatParam() 関数で設定します。
	 *
	 *	リピートモードを利用する場合、画像の横幅、縦幅いずれも
	 *	\f$ 2^n \f$ (n は整数) で表される数値でなければならないという条件があります。
	 *	(横幅と縦幅は一致している必要はありません。)
	 *	この条件を満たさなかった場合の動作は保証されません。
	 *	また、リピートモードを有効とした場合、 setTextureCoord() による
	 *	画像の切り出しも無効となります。
	 *
	 *	\param[in]	mode
	 *		true であればリピートモードを有効とし、
	 *		false であれば無効とします。
	 *
	 *	\sa setRepeatParam()
	 */
	void				setRepeatMode(bool mode);

	//! リピートモード参照関数
	/*!
	 *	現在のリピートモードの状態を取得します。
	 *
	 *	\return
	 *		true であればリピートモードが有効であることを意味します。
	 *		false であれば無効であることを意味します。
	 *
	 *	\sa setRepeatMode()
	 */
	bool				getRepeatMode(void);

	//! リピートモード枚数設定関数
	/*!
	 *	リピートモードでの、縦方向と横方向に並べる枚数を設定します。
	 *	リピートモードについては setRepeatMode() の説明を参照して下さい。
	 *
	 *	なお、枚数は正であれば整数である必要はありません。
	 *	その場合は、右端と上端の画像が途中で切れます。
	 *
	 *	\param[in]	wNum		横方法の枚数
	 *	\param[in]	hNum		縦方向の枚数
	 *
	 *	\sa setRepeatMode()
	 */
	void				setRepeatParam(double wNum, double hNum);

	//! リピートモード枚数参照関数
	/*!
	 *	リピートモードの、各方向の枚数を取得します。
	 *
	 *	\return		各方向の枚数
	 *
	 *	\sa setRepeatParam()
	 */
	fk_TexCoord			getRepeatParam(void);

	//! 部分抽出設定関数1
	/*!
	 *	画像の部分矩形領域を切り出し、その部分をテクスチャ画像とします。
	 *	領域指定はテクスチャ座標系を用います。
	 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
	 *	なお、 setRepeatMode() でリピートモードを有効とした場合、
	 *	この部分抽出の設定は無効となります。
	 *
	 *	\param[in]	sX	抽出左下部分の x 成分
	 *	\param[in]	sY	抽出左下部分の y 成分
	 *	\param[in]	eX	抽出右上部分の x 成分
	 *	\param[in]	eY	抽出右上部分の y 成分
	 */
	void				setTextureCoord(double sX, double sY,
										double eX, double eY);

	//! 部分抽出設定関数2
	/*!
	 *	画像の部分矩形領域を切り出し、その部分をテクスチャ画像とします。
	 *	領域指定はテクスチャ座標系を用います。
	 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
	 *	なお、 setRepeatMode() でリピートモードを有効とした場合、
	 *	この部分抽出の設定は無効となります。
	 *
	 *	\param[in]	S	抽出左下部分のテクスチャ座標
	 *	\param[in]	E	抽出右上部分のテクスチャ座標
	 */
	void				setTextureCoord(const fk_TexCoord &S,
										const fk_TexCoord &E);

	//! 部分抽出参照関数
	/*!
	 *	setTextureCoord() 関数によって部分抽出領域を設定した場合、
	 *	その領域のテクスチャ座標を取得します。
	 *
	 *	\param[in]	ID
	 *		0 であれば左下部のテクスチャ座標を、
	 *		1 であれば右上部のテクスチャ座標を返します。
	 *		それ以外の値を入力した場合は、常に (0, 0) を返します。
	 *
	 *	\return		左上部、または右上部のテクスチャ座標
	 *
	 *	\sa setTextureCoord()
	 */
	fk_TexCoord			getTextureCoord(int ID);
};

//! 3角形テクスチャを生成、管理するクラス
/*!
 *	このクラスは、3角形のテクスチャを制御する機能を提供します。
 *
 *	3角形テクスチャを生成する大まかな手順は以下のようになります。
 *	-# 画像を入力する。
 *	-# 各頂点のテクスチャ座標を設定する。
 *	-# 各頂点の3次元空間内の位置ベクトルを設定する。
 *	.
 *	空間上に各頂点を配置する際、頂点の順番が反時計回りになっている側が表面となります。
 *	テクスチャ座標系の方は必ずしも反時計回りになっている必要はありませんが、
 *	それが時計回りである場合は表示される画像が結果的に裏返ります。
 *
 *	本クラスでは、1つのインスタンスで制御できる3角形は1枚のみです。
 *	複数枚の3角形を1つのインスタンスで制御したい場合は、
 *	fk_MeshTexture クラスを用いた方がメモリ使用量や描画速度の効率が良くなります。
 *	また、3角形ではなく矩形を扱いたい場合は fk_RectTexture クラスを利用して下さい。
 *
 *	\sa fk_Texture, fk_RectTexture, fk_MeshTexture, fk_IFSTexture
 */

class fk_TriTexture : public fk_Texture {

	friend class		fk_TextureDraw;

 private:
	fk_Vector			pos[3];
	fk_TexCoord			texCoord[3];

	fk_Vector *			getPos(void);
	fk_TexCoord *		getCoord(void);

 public:

	//! コンストラクタ
	/*!
	 *	\param[in]	image
	 *		テクスチャ画像。省略するか nullptr を代入した場合は、
	 *	   	テクスチャ画像を初期状態では生成しません。
	 */
	fk_TriTexture(fk_Image *image = nullptr);

	//! デストラクタ
	virtual ~fk_TriTexture();

	//! 初期化関数
	/*!
	 *	現在設定されているテクスチャ画像を廃棄し、全ての設定を初期状態に戻します。
	 */
	void				init(void);

	//! テクスチャ座標設定関数1
	/*!
	 *	頂点のテクスチャ座標を設定します。
	 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
	 *	テクスチャ座標は、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	ID
	 *		頂点ID。0, 1, 2 のいずれかになります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\param[in]	x
	 *		テクスチャ座標の x 成分。0 以上 1 以下である必要があります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\param[in]	y
	 *		テクスチャ座標の y 成分。0 以上 1 以下である必要があります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool				setTextureCoord(int ID, double x, double y);

	//! テクスチャ座標設定関数2
	/*!
	 *	頂点のテクスチャ座標を設定します。
	 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
	 *	テクスチャ座標は、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	ID
	 *		頂点ID。0, 1, 2 のいずれかになります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\param[in]	coord
	 *		テクスチャ座標。各成文は 0 以上 1 以下である必要があります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool				setTextureCoord(int ID, fk_TexCoord coord);

	//! テクスチャ座標取得関数
	/*!
	 *	setTextureCoord() で設定したテクスチャ座標を取得します。
	 *
	 *	\param[in]	ID		頂点ID。
	 *		0, 1, 2 のいずれか以外を指定した場合は、
	 *		常に (0, 0) を返します。
	 *
	 *	\return		IDに対応する頂点のテクスチャ座標
	 */
	fk_TexCoord			getTextureCoord(int ID);

	//! 頂点位置ベクトル設定関数1
	/*!
	 *	頂点の空間中での位置ベクトルを設定します。
	 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	ID
	 *		頂点ID。0, 1, 2 のいずれかになります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\param[in]	x	頂点位置ベクトルの x 成分
	 *	\param[in]	y	頂点位置ベクトルの y 成分
	 *	\param[in]	z	頂点位置ベクトルの z 成分
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool				setVertexPos(int ID, double x, double y, double z);

	//! 頂点位置ベクトル設定関数2
	/*!
	 *	頂点の空間中での位置ベクトルを設定します。
	 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	ID
	 *		頂点ID。0, 1, 2 のいずれかになります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\param[in]	pos		頂点位置ベクトル
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool				setVertexPos(int ID, fk_Vector pos);

	//! 頂点位置ベクトル取得関数
	/*!
	 *	setTexturePos() で設定したテクスチャ座標を取得します。
	 *
	 *	\param[in]	ID		頂点ID。
	 *		0, 1, 2 のいずれか以外を指定した場合は、
	 *		常に (0, 0, 0) を返します。
	 *
	 *	\return		IDに対応する頂点の位置ベクトル
	 */
	fk_Vector			getVertexPos(int ID);
};

//! メッシュテクスチャを生成、管理するクラス
/*!
 *	このクラスは、複数の3角形テクスチャを制御する機能を提供します。
 *
 *	メッシュテクスチャを生成するおおまかな手順は以下のようになります。
 *	-# 画像を入力する。
 *	-# 各頂点のテクスチャ座標を設定する。
 *	-# 各頂点の3次元空間内の位置ベクトルを設定する。
 *	.
 *	空間上に各頂点を配置する際、頂点の順番が反時計回りになっている側が表面となります。
 *	テクスチャ座標系の方は必ずしも反時計回りになっている必要はありませんが、
 *	それが時計回りである場合は表示される画像が結果的に裏返ります。
 *
 *	本クラスでは、1つのインスタンスで複数枚の3角形テクスチャを扱うことができます。
 *	(その分、 fk_TriTexture よりも利用方法はやや複雑になっています。)
 *	同様の機能を持つクラスとして、 fk_IFSTexture があります。
 *	fk_IFSTexture クラスと比較した、
 *	本クラスの長所と短所をまとめると以下のようになります。
 *	- 長所
 *		- 3角形テクスチャの動的生成が可能である。
 *	- 短所
 *		- 描画速度は若干劣る。
 *		- D3DXファイルの入力に対応していない。
 *	.
 *	総じて、3角形テクスチャの動的生成を想定する場合は fk_MeshTexture が有用です。
 *	それ以外の用途では、 fk_IFSTexture の利用を検討する価値があると言えます。
 *
 *	\sa fk_Texture, fk_RectTexture, fk_TriTexture, fk_IFSTexture
 */

class fk_MeshTexture : public fk_Texture {

	friend class			fk_TextureDraw;

 private:

	int							triNum;
	std::vector<fk_Vector>		posArray;
	std::vector<fk_TexCoord>	coordArray;

	std::vector<fk_Vector> *	getPos(void);
	std::vector<fk_TexCoord> *	getCoord(void);

 public:

	//! コンストラクタ
	/*!
	 *	\param[in]	image
	 *		テクスチャ画像。省略するか nullptr を代入した場合は、
	 *	   	テクスチャ画像を初期状態では生成しません。
	 */
	fk_MeshTexture(fk_Image *image = nullptr);

	//! デストラクタ
	virtual ~fk_MeshTexture();

	//! 初期化関数
	/*!
	 *	現在設定されているテクスチャ画像を廃棄し、全ての設定を初期状態に戻します。
	 */
	void			init(void);

	//! 3角形面数設定関数
	/*!
	 *	3角形テクスチャ面の枚数を設定します。
	 *	枚数を変更しても、前に設定した面データは可能な限り保持します。
	 *
	 *	\param[in]	num		枚数
	 *
	 *	\return		設定に成功すれば true を、失敗すれば false を返します。
	 */
	bool			setTriNum(int num);

	//! 3角形面数参照関数
	/*!
	 *	3角形テクスチャ面の枚数を取得します。
	 *
	 *	\return		枚数
	 *
	 *	\sa setTriNum()
	 */
	int				getTriNum(void);

	//! テクスチャ座標設定関数1
	/*!
	 *	頂点のテクスチャ座標を設定します。
	 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
	 *	テクスチャ座標は、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	tID
	 *		3角形面の ID を入力します。
	 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
	 *
	 *	\param[in]	vID
	 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\param[in]	x
	 *		テクスチャ座標の x 成分。0 以上 1 以下である必要があります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\param[in]	y
	 *		テクスチャ座標の y 成分。0 以上 1 以下である必要があります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool			setTextureCoord(int tID, int vID,
									double x, double y);

	//! テクスチャ座標設定関数2
	/*!
	 *	頂点のテクスチャ座標を設定します。
	 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
	 *	テクスチャ座標は、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	tID
	 *		3角形面の ID を入力します。
	 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
	 *
	 *	\param[in]	vID
	 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\param[in]	coord
	 *		テクスチャ座標。各成文は 0 以上 1 以下である必要があります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool			setTextureCoord(int tID, int vID, fk_TexCoord coord);

	//! テクスチャ座標配列設定関数1
	/*!
	 *	各3角形テクスチャのテクスチャ座標を、配列によって設定します。
	 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
	 *	テクスチャ座標は、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	tID
	 *		3角形面の ID を入力します。
	 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
	 *
	 *	\param[in]	array
	 *		テクスチャ座標を表す配列へのポインタです。
	 *		配列の先頭3個分のデータが利用されます。
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool			setTriTextureCoord(int tID,
									   std::vector<fk_TexCoord> *array);

	//! テクスチャ座標配列設定関数2
	/*!
	 *	各3角形テクスチャのテクスチャ座標を、配列によって設定します。
	 *	テクスチャ座標系については fk_TexCoord の説明を参照して下さい。
	 *	テクスチャ座標は、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	tID
	 *		3角形面の ID を入力します。
	 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
	 *
	 *	\param[in]	array
	 *		テクスチャ座標を表す配列へのポインタです。
	 *		配列の先頭3個分のデータが利用されます。
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool			setTriTextureCoord(int tID,
									   fk_TexCoord *array);
	//! テクスチャ座標参照関数
	/*!
	 *	設定されているテクスチャ座標を取得します。
	 *
	 *	\param[in]	tID
	 *		3角形面の ID を入力します。
	 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
	 *
	 *	\param[in]	vID
	 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
	 *
	 *	\return		テクスチャ座標。取得に失敗した場合は常に (0, 0) を返します。
	 *
	 *	\sa setTextureCoord(), setTriTextureCoord()
	 */
	fk_TexCoord		getTextureCoord(int tID, int vID);

	//! 頂点位置ベクトル設定関数1
	/*!
	 *	頂点の空間中での位置ベクトルを設定します。
	 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	tID
	 *		3角形面の ID を入力します。
	 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
	 *
	 *	\param[in]	vID
	 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\param[in]	x	頂点位置ベクトルの x 成分
	 *	\param[in]	y	頂点位置ベクトルの y 成分
	 *	\param[in]	z	頂点位置ベクトルの z 成分
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool			setVertexPos(int tID, int vID,
								 double x, double y, double z);

	//! 頂点位置ベクトル設定関数2
	/*!
	 *	頂点の空間中での位置ベクトルを設定します。
	 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	tID
	 *		3角形面の ID を入力します。
	 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
	 *
	 *	\param[in]	vID
	 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
	 *		それ以外の値を入力した場合はエラーとなり、false を返します。
	 *
	 *	\param[in]	pos		頂点位置ベクトル
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool			setVertexPos(int tID, int vID, fk_Vector pos);

	//! 頂点位置ベクトル配列設定関数1
	/*!
	 *	各3角形テクスチャの頂点位置ベクトルを、配列によって設定します。
	 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	tID
	 *		3角形面の ID を入力します。
	 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
	 *
	 *	\param[in]	array
	 *		頂点の位置ベクトルを表す配列へのポインタです。
	 *		配列の先頭3個分のデータが利用されます。
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool			setTriPos(int tID, std::vector<fk_Vector> *array);

	//! 頂点位置ベクトル配列設定関数2
	/*!
	 *	各3角形テクスチャの頂点位置ベクトルを、配列によって設定します。
	 *	位置ベクトルは、一度設定した後でも動的に変更することが可能です。
	 *
	 *	\param[in]	tID
	 *		3角形面の ID を入力します。
	 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
	 *
	 *	\param[in]	array
	 *		頂点の位置ベクトルを表す配列へのポインタです。
	 *		配列の先頭3個分のデータが利用されます。
	 *
	 *	\return		設定に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool			setTriPos(int tID, fk_Vector *array);

	//! 頂点位置ベクトル参照関数
	/*!
	 *	設定されている頂点位置ベクトルを取得します。
	 *
	 *	\param[in]	tID
	 *		3角形面の ID を入力します。
	 *		ID は 0 から始まる整数値で、最大が枚数から1を引いたものとなります。
	 *
	 *	\param[in]	vID
	 *		頂点IDを入力します。0, 1, 2 のいずれかになります。
	 *
	 *	\return		頂点位置ベクトル。取得に失敗した場合は常に (0, 0, 0) を返します。
	 *
	 *	\sa setTexturePos(), setTriTexturePos()
	 */
	fk_Vector		getVertexPos(int tID, int vID);

	//! fk_IndexFaceSet インスタンスコピー関数
	/*!
	 *	現在の形状データを、
	 *	fk_IndexFaceSet 型のインスタンスにコピーします。
	 *
	 *	\param[in]	ifs		fk_IndexFaceSet 型インスタンスのアドレス。
	 */
	void			putIndexFaceSet(fk_IndexFaceSet *ifs);

	//! MQOファイル入力関数
	/*!
	 *	MQO 形式のファイルからデータを入力します。
	 *	本関数が入力を行うのは形状データとテクスチャ座標であり、
	 *	画像データの入力は行いません。
	 *	画像データ入力は fk_Texture のメンバ関数等を用いて別途行ってください。
	 *
	 *	MQOデータには「オブジェクト」という概念があり、
	 *	1つの形状データが複数のオブジェクトによって構成されていることがあります。
	 *	この関数では、ファイル名とともにオブジェクト名を指定する必要があります。
	 *
	 *	\param[in]	fileName	ファイル名
	 *
	 *	\param[in]	objName		オブジェクト名
	 *
	 *	\param[in]	contFlg
	 *		テクスチャ断絶の設定を指定します。これは、テクスチャ座標が不連続な箇所に対し、
	 *		形状の位相を断絶する操作を行うためのものです。
	 *		これを true にした場合は断裂操作が行われ、
	 *		テクスチャ座標が不連続な箇所が幾何的にも不連続となるように表示されます。
	 *		ほとんどの場合は、断裂操作を行った方が良好な描画結果となります。
	 *		ただし、断裂操作を行う際に新たな位相要素を生成するため、
	 *		本来のデータよりも頂点、稜線、面が若干増加する場合があります。
	 *		false にした場合は、断裂操作を行わずに通常のデータ通り読み込みます。
	 *
	 *	\return ファイルの入力に成功した場合 true を、失敗した場合 false を返します。
	 *
	 *	\sa fk_IFSTexture::readMQOFile()
	 */
	bool			readMQOFile(std::string fileName,
								std::string objName,
								bool contFlg = true);
};

#endif	// !__FK_TEXTURE_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
