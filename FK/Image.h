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

//! \file Image.h

#ifndef	__FK_IMAGE_HEADER__
#define	__FK_IMAGE_HEADER__

#include <FK/Base.h>
#include <FK/Material.h>
#include <vector>
#include <string>

#ifndef FK_DOXYGEN_USER_PROCESS

#ifdef	NO_GL_LIBRARY
typedef	unsigned char	fk_ImType;
typedef unsigned int	fk_TexID;
#else
#include <FK/OpenGL.H>
typedef GLubyte			fk_ImType;
typedef GLuint			fk_TexID;
#endif


enum fk_ImageStatus {
	FK_IMAGE_OK,
	FK_IMAGE_OPENERROR,
	FK_IMAGE_DATAERROR,
	FK_IMAGE_READERROR
};

enum fk_ImageFix {
	FK_FIX_LARGE,
	FK_FIX_SMALL,
	FK_FIX_64,
	FK_FIX_128,
	FK_FIX_256,
	FK_FIX_512,
	FK_FIX_1024,
	FK_FIX_2048,
	FK_FIX_4096,
	FK_FIX_8192,
	FK_FIX_16384,
	FK_FIX_32768,
	FK_FIX_65536
};

#endif

//! 画像フォーマットを表す列挙型
enum fk_ImageType {
	FK_IMAGE_BMP,		//!< Windows Bitmap (BMP) 形式
	FK_IMAGE_PNG,		//!< PNG 形式
	FK_IMAGE_JPG		//!< JPEG 形式
};

//! 画像取り込み方法を表す列挙型
enum fk_SnapProcMode {
	FK_SNAP_GL_FRONT,	//!< OpenGL フロントバッファ
	FK_SNAP_GL_BACK,	//!< OpenGL バックバッファ
	FK_SNAP_WIN32_GDI,	//!< Win32 GDI (Windows プラットフォームのみ対応)
	FK_SNAP_D3D_WINDOW,	//!< Direct3D ウィンドウバッファ (Direct3D版のみ対応)
	FK_SNAP_D3D_FULL	//!< Direct3D フルスクリーンバッファ (Direct3D版のみ対応)
};

//! 画像サイズを表すクラス
/*!
 *	このクラスは、画像サイズの設定や取得に利用します。
 *	\sa fk_Rect, fk_Image
 */
class fk_Dimension {
 public:
	int		w; //!< 画像の横幅
	int		h; //!< 画像の縦幅

	//! コンストラクタ
	/*!
	 *	\param[in] w 画像の横幅
	 *	\param[in] h 画像の縦幅
	 */
	fk_Dimension(int w = 0, int h = 0);

	//! コピーコンストラクタ
	fk_Dimension(const fk_Dimension &);

	//! 画像サイズ設定関数
	/*!
	 *	\param[in] w 画像の横幅
	 *	\param[in] h 画像の縦幅
	 */
	void set(int w, int h);
};

//! 画像中の矩形領域を表すクラス
/*!
 *	このクラスは、画像中の矩形領域を表します。
 *	このクラスの座標系は、画像の左上を原点とし、
 *	x の正方向は右、y の正方向は下となります。
 *
 *	\sa fk_Dimension, fk_Image
 */
class fk_Rect {
 public:
	int		x;	//!< 領域左上の x 座標
	int		y;	//!< 領域左上の y 座標
	int		w;	//!< 領域の横幅
	int		h;	//!< 領域の縦幅

	//! コンストラクタ
	/*!
	 *	\param[in] x 領域左上の x 座標
	 *	\param[in] y 領域左上の y 座標
	 *	\param[in] w 領域の横幅
	 *	\param[in] h 領域の縦幅
	 */
	fk_Rect(int x = 0, int y = 0, int w = 0, int h = 0);

	//! コピーコンストラクタ
	fk_Rect(const fk_Rect &);

	//! 領域設定関数
	/*!
	 *	\param[in] x 領域左上の x 座標
	 *	\param[in] y 領域左上の y 座標
	 *	\param[in] w 領域の横幅
	 *	\param[in] h 領域の縦幅
	 */	
	void			set(int x, int y, int w, int h);

	//! 領域位置設定関数
	/*!
	 *	\param[in] x 領域左上の x 座標
	 *	\param[in] y 領域左上の y 座標
	 */
	void			setPos(int x, int y);

	//! 領域サイズ設定関数
	/*!
	 *	\param[in] w 領域の横幅
	 *	\param[in] h 領域の縦幅
	 */	
	void			setSize(int w, int h);

	//! 領域サイズ参照関数
	/*!
	 *	\return 領域サイズ
	 */
	fk_Dimension	getSize(void);
};

//! 画像を生成、管理するクラス
/*!
 *	このクラスは、画像データを制御する機能を提供します。
 *	主な利用用途はテクスチャ画像の管理ですが、
 *	画像処理のための基本的な機能を保持しています。
 *	画像データは RGBA 形式で保存されます。
 *	各要素は整数値で最小値は 0、最大値は 255 です。
 *	透過色要素は 0 が完全な透明、255 が完全な不透明を表します。
 *	現バージョンのピクセルサイズの最大値は縦幅横幅共に 65536 までです。
 *
 *	実際の画像サイズと、格納するデータについての関係は
 *	getBufferSize() 関数の覚え書きを参照して下さい。
 *
 *	\sa fk_Rect, fk_Dimension, fk_Texture
 */
class fk_Image : public fk_BaseObject {

	friend class	fk_Texture;

 private:

	fk_Dimension			imageSize, bufSize;
	std::vector<fk_ImType>	imageBuf;
	fk_ImType				*bufPointer;
	fk_TexID				texID;
	bool					initFlag;
	// テクスチャの部分更新用情報
	fk_Rect					updateRect;

	unsigned int		ChgUInt(fk_ImType *, int) const;
	unsigned int		ChgUShort(fk_ImType *, int) const;

	int					GetOffset(int, int) const;
	fk_ImType			RoundVal(int) const;
	fk_ImageStatus		CreateImg(const std::string);
	fk_ImageStatus		CreateImg(fk_ImType *);
	void				CreateBuffer(bool = true);
	void				CreateBuffer(int, int, bool = true);
	void				CreateBuffer(const fk_Dimension, bool = true);
	bool				IsPixelStatus(int, int) const;
	int					GetOneBufferSize(int, int);
	int					GetFixVal(fk_ImageFix, int) const;

	void				SetLong2Byte(long, fk_ImType *, int);
	void				SetInt2Byte(int, fk_ImType *, int);

	bool				GetInitFlag(void);
	void				SetInitFlag(bool);
	void				SetTexID(const fk_TexID);

	bool				IsBmpFile(const std::string) const;
	bool				IsBmpData(fk_ImType *) const;
	fk_ImageStatus		LoadBmpFile(const std::string);
	fk_ImageStatus		LoadBmpData(fk_ImType *);
	void				SetRGBA4Bmp(int, int, fk_ImType *,
									int, std::vector<fk_ImType> &);

	bool				GetBmpFileHeader(std::ifstream &, fk_ImType *);
	bool				GetBmpInfoHeader(std::ifstream &, fk_ImType *);
	fk_Dimension		GetBmpSize(fk_ImType *);

	fk_ImageStatus		SaveBmpFile(std::string, bool);
	void				MakeBmpFileHeader(int, int, int,
										  std::vector<fk_ImType> &);
	void				MakeBmpInfoHeader(int, int, int,
										  std::vector<fk_ImType> &);
	void				MakeBmpBuffer(int, int, bool, fk_ImType *);

	bool				IsPngFile(const std::string) const;
	bool				IsPngData(fk_ImType *) const;
	fk_ImageStatus		LoadPngFile(const std::string);
	fk_ImageStatus		LoadPngData(fk_ImType *);

 public:

	//! コンストラクタ
	/*!
	 *	\param[in] w 画像の横幅
	 *	\param[in] h 画像の縦幅
	 */
	fk_Image(int w = 0, int h = 0);

	//! デストラクタ
	virtual ~fk_Image();

	//! コピーコンストラクタ
	fk_Image(const fk_Image &);

	//! 初期化関数
	/*!
	 *	画像データを初期化します。
	 *	画像サイズも (0, 0) となります。
	 */
	void	init();

	//! BMP ファイル入力関数
	/*!
	 *	BMP (Windows Bitmap) 形式のファイルからデータを読み込みます。
	 *
	 *	\param[in] fileName	ファイル名
	 *
	 *	\return 入力に成功すれば true、失敗すれば false を返します。
	 */
	bool	readBMP(const std::string fileName);

	//! BMP バッファ入力関数
	/*!
	 *	BMP (Windows Bitmap) 形式のバッファからデータを読み込みます。
	 *	fk_ImType 型は、OpenGL をサポートしている環境においては GLubyte、
	 *	サポートしていない環境では unsigned char 型として定義されています。
	 *
	 *	\param[in] buf	データバッファ
	 *
	 *	\return 入力に成功すれば true、失敗すれば false を返します。
	 */
	bool	readBMPData(fk_ImType *buf);

	//! PNG ファイル入力関数
	/*!
	 *	PNG 形式のファイルからデータを読み込みます。
	 *
	 *	\param[in] fileName	ファイル名
	 *
	 *	\return 入力に成功すれば true、失敗すれば false を返します。
	 */
	bool	readPNG(const std::string fileName);

	//! PNG データ入力用関数
	/*!
	 *	PNG 形式のバッファからデータを読み込みます。
	 *	fk_ImType 型は、OpenGL をサポートしている環境においては GLubyte、
	 *	サポートしていない環境では unsigned char 型として定義されています。
	 *
	 *	\param[in] buf	データバッファ
	 *
	 *	\return 入力に成功すれば true、失敗すれば false を返します。
	 */
	bool	readPNGData(fk_ImType *buf);

	//! JPEG ファイル入力関数
	/*!
	 *	JPEG 形式のファイルからデータを読み込みます。
	 *
	 *	\param[in] fileName	ファイル名
	 *
	 *	\return 入力に成功すれば true、失敗すれば false を返します。
	 */
	bool	readJPG(const std::string fileName);

	//! BMP ファイル出力関数
	/*!
	 *	画像データを BMP (Windows Bitmap) 形式でファイルに保存します。
	 *
	 *	\param[in] fileName	ファイル名
	 *	\param[in] transFlg
	 *		true の場合、透過色要素をファイル中に書き出します。
	 *		透過色要素は本来 BMP 形式では標準でサポートされておらず、
	 *		FK によって利用する画像ファイルの独自拡張となっています。
	 *		ただし、透過色要素を埋め込んだ画像ファイルは一般のアプリケーションでも
	 *		(透過色が追加されていないデータとして)読み込むことは可能です。
	 *		false の場合は、データ中の透過色要素をファイルには出力しません。
	 *
	 *	\return 書き出しに成功すれば true、失敗すれば false を返します。
	 */
	bool	writeBMP(const std::string fileName, const bool transFlg = false);

	//! PNG ファイル出力関数
	/*!
	 *	画像データを PNG 形式でファイルに保存します。
	 *
	 *	\param[in] fileName	ファイル名
	 *	\param[in] transFlg
	 *		true の場合、透過色要素をファイル中に書き出します。
	 *		false の場合は、データ中の透過色要素をファイルには出力しません。
	 *
	 *	\return 書き出しに成功すれば true、失敗すれば false を返します。
	 */
	bool	writePNG(const std::string fileName, const bool transFlg = true);

	//! JPEG ファイル出力関数
	/*!
	 *	画像データを JPEG 形式でファイルに保存します。
	 *	なお、JPEG 形式は透過がサポートされていないので、
	 *	画像中に透過色データを出力することはできません。
	 *
	 *	\param[in] fileName	ファイル名
	 *	\param[in] quality
	 *		画像の品質を設定します。
	 *		品質が高いほどファイルのサイズは大きくなります。
	 *		100 が最高品質、0 が最低品質となります。範囲外の数値が入力された場合、
	 *		上下限に丸められます。
	 *
	 *	\return 書き出しに成功すれば true、失敗すれば false を返します。
	 */
	bool	writeJPG(const std::string fileName, int quality = 80);

	//! 画像領域生成関数
	/*!
	 *	画像データを与えられたサイズに従って生成します。
	 *
	 *	\param[in] w	画像の横幅
	 *	\param[in] h	画像の縦幅
	 *	\param[in] initFlg
	 *		true の場合は、データ全体を (0, 0, 0, 0) で初期化します。
	 *		false の場合は初期化を行いませんが、
	 *		その場合でも横幅が変更されたときは
	 *		各ピクセルの縦横関係が崩れてしまう可能性があります。
	 */
	void	newImage(int w, int h, bool initFlg = true);

	//! 画像データコピー関数1
	/*!
	 *	画像データを別インスタンスからコピーします。
	 *	この引数形式の場合、画像サイズは元画像データと同一となります。
	 *
	 *	\param[in] image	元画像データのアドレス
	 */
	void	copyImage(const fk_Image *image);

	//! 画像データコピー関数2
	/*!
	 *	画像データの部分矩形領域を、別インスタンスの画像データ内容に書き換えます。
	 *	この引数形式では、画像中の一部分となる任意領域を書き換えることが可能ですが、
	 *	コピー元となる画像全体がコピー先の中に完全に収まるような配置である必要があります。
	 * 	この条件を満たさなかった場合は、データの書き換えを行いません。
	 *	配置の際の座標系は fk_Rect の座標系に従います。
	 *
	 *	\param[in] image	元画像データのアドレス
	 *	\param[in] x		書き換え領域左上の x 座標
	 *	\param[in] y		書き換え領域左上の y 座標
	 */
	void	copyImage(const fk_Image *image, int x, int y);

	//! 画像データ部分抽出関数
	/*!
	 *	別インスタンス中にある画像データの部分矩形領域をコピーします。
	 *	指定した矩形領域は全て元画像内に収まっている必要があります。
	 *	領域の座標系は fk_Rect の座標系に従います。
	 *
	 *	\param[in] image	元画像データのアドレス
	 *	\param[in] x		抽出矩形領域左上の x 座標
	 *	\param[in] y		抽出矩形領域左上の y 座標
	 *	\param[in] w		抽出矩形領域の横幅
	 *	\param[in] h		抽出矩形領域の縦幅
	 */
	bool	subImage(const fk_Image *image, int x, int y, int w, int h);

	//! 画像横幅取得関数
	/*!
	 *	\return 横幅
	 */
	int		getWidth(void) const;

	//! 画像縦幅取得関数
	/*!
	 *	\return 縦幅
	 */
	int		getHeight(void) const;

	//! 画像サイズ取得関数
	/*!
	 *	\return 画像サイズのポインタ
	 */
	const fk_Dimension *	getImageSize(void);

	//! 画像バッファサイズ取得関数
	/*!
	 *	fk_Image では、本来の画像サイズに対し、
	 *	格納するデータ領域はより大きなものとなっています。
	 *	この関数は、実際に確保しているデータ領域の大きさを
	 *	fk_Dimension 型で返すものです。
	 *
	 *	\note
	 *		fk_Image のデータ格納がこのような仕様になっている理由は、
	 *		古い OpenGL の仕様に基づきます。
	 *		ver 2.0 以前の OpenGL では、
	 *		テクスチャ画像として与えられるデータ領域について、
	 *		横幅と縦幅は \f$ 2^n \f$ で表される
	 *		整数値でなければならないという制約がありました。
	 *		(縦幅と横幅は同一である必要はありません。)
	 *		また、OpenGL の 2.0 以降をサポートしたハードウェアであっても、
	 *		\f$ 2^n \f$ 以外の幅であった場合に
	 *		描画速度が著しく低下する場合があるという報告もあります。
	 *		このような理由から、
	 *		fk_Image では内部データで幅を \f$ 2^n \f$ となるように補正しています。
	 *
	 *	\return データサイズのポインタ
	 */
	const fk_Dimension *	getBufferSize(void);

	//! ピクセルR要素取得関数
	/*!
	 *	ピクセルのR(赤)要素値を取得します。
	 *	座標系は fk_Rect の座標系に従います。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *
	 *	\return
	 *		ピクセルのR(赤)要素値。
	 *		指定した座標が画像内にない場合は、-1 を返します。
	 */
	int		getR(int x, int y) const;

	//! ピクセルG要素取得関数
	/*!
	 *	ピクセルのG(緑)要素値を取得します。
	 *	座標系は fk_Rect の座標系に従います。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *
	 *	\return
	 *		ピクセルのG(緑)要素値。
	 *		指定した座標が画像内にない場合は、-1 を返します。
	 */
	int		getG(int x, int y) const;

	//! ピクセルB要素取得関数
	/*!
	 *	ピクセルのB(青)要素値を取得します。
	 *	座標系は fk_Rect の座標系に従います。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *
	 *	\return
	 *		ピクセルのB(青)要素値。
	 *		指定した座標が画像内にない場合は、-1 を返します。
	 */
	int		getB(int x, int y) const;

	//! ピクセルA要素取得関数
	/*!
	 *	ピクセルのA(透過度)要素値を取得します。
	 *	座標系は fk_Rect の座標系に従います。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *
	 *	\return
	 *		ピクセルのA(透過度)要素値。
	 *		指定した座標が画像内にない場合は、-1 を返します。
	 */
	int		getA(int x, int y) const;

	//! ピクセル色要素取得関数
	/*!
	 *	ピクセルの色要素値を fk_Color 型で取得します。
	 *	座標系は fk_Rect の座標系に従います。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *
	 *	\return
	 *		ピクセルの色要素値。
	 *		指定した座標が画像内にない場合は、(0, 0, 0, 1) の値を返します。
	 */
	fk_Color	getColor(int x, int y) const;

	//! ピクセル RGBA 値設定関数
	/*!
	 *	ピクセルの RGBA 各色要素を設定します。
	 *	座標系は fk_Rect の座標系に従います。
	 *	値が 0 から 255 の範囲内になかった場合は、
	 *	上下限それぞれに丸められます。
	 * 	座標が画像内になかった場合は、画像情報を変更しません。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *	\param[in] r	R(赤)要素値
	 *	\param[in] g	G(赤)要素値
	 *	\param[in] b	B(赤)要素値
	 *	\param[in] a	A(赤)要素値
	 *
	 *	\return
	 *		更新に成功した場合 true を、失敗した場合 false を返します。
	 *		値の丸めが入った場合については、失敗とはみなしません。
	 */
	bool	setRGBA(int x, int y, int r, int g, int b, int a);

	//! ピクセル RGB 値設定関数
	/*!
	 *	ピクセルの RGB 各色要素を設定します。
	 *	座標系は fk_Rect の座標系に従います。
	 *	値が 0 から 255 の範囲内になかった場合は、
	 *	上下限それぞれに丸められます。
	 * 	座標が画像内になかった場合は、画像情報を変更しません。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *	\param[in] r	R(赤)要素値
	 *	\param[in] g	G(赤)要素値
	 *	\param[in] b	B(赤)要素値
	 *
	 *	\return
	 *		更新に成功した場合 true を、失敗した場合 false を返します。
	 *		値の丸めが入った場合については、失敗とはみなしません。
	 */
	bool	setRGB(int x, int y, int r, int g, int b);

	//! ピクセル R 値設定関数
	/*!
	 *	ピクセルの R 色要素を設定します。
	 *	座標系は fk_Rect の座標系に従います。
	 *	値が 0 から 255 の範囲内になかった場合は、
	 *	上下限それぞれに丸められます。
	 * 	座標が画像内になかった場合は、画像情報を変更しません。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *	\param[in] r	R(赤)要素値
	 *
	 *	\return	更新に成功した場合 true を、失敗した場合 false を返します。
	 *	値の丸めが入った場合については、失敗とはみなしません。
	 */
	bool	setR(int x, int y, int r);

	//! ピクセル G 値設定関数
	/*!
	 *	ピクセルの G 色要素を設定します。
	 *	座標系は fk_Rect の座標系に従います。
	 *	値が 0 から 255 の範囲内になかった場合は、
	 *	上下限それぞれに丸められます。
	 * 	座標が画像内になかった場合は、画像情報を変更しません。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *	\param[in] g	G(緑)要素値
	 *
	 *	\return	更新に成功した場合 true を、失敗した場合 false を返します。
	 *	値の丸めが入った場合については、失敗とはみなしません。
	 */
	bool	setG(int x, int y, int g);

	//! ピクセル B 値設定関数
	/*!
	 *	ピクセルの B 色要素を設定します。
	 *	座標系は fk_Rect の座標系に従います。
	 *	値が 0 から 255 の範囲内になかった場合は、
	 *	上下限それぞれに丸められます。
	 * 	座標が画像内になかった場合は、画像情報を変更しません。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *	\param[in] b	B(青)要素値
	 *
	 *	\return	更新に成功した場合 true を、失敗した場合 false を返します。
	 *	値の丸めが入った場合については、失敗とはみなしません。
	 */
	bool	setB(int x, int y, int b);

	//! ピクセル A 値設定関数
	/*!
	 *	ピクセルの A 色要素を設定します。
	 *	座標系は fk_Rect の座標系に従います。
	 *	値が 0 から 255 の範囲内になかった場合は、
	 *	上下限それぞれに丸められます。
	 * 	座標が画像内になかった場合は、画像情報を変更しません。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *	\param[in] a	A(透過度)要素値
	 *
	 *	\return	更新に成功した場合 true を、失敗した場合 false を返します。
	 *	値の丸めが入った場合については、失敗とはみなしません。
	 */
	bool	setA(int x, int y, int a);

	//! ピクセル色値設定関数
	/*!
	 *	ピクセルの色要素を fk_Color 型で設定します。
	 *	座標系は fk_Rect の座標系に従います。
	 * 	座標が画像内になかった場合は、画像情報を変更しません。
	 *
	 *	\param[in] x	ピクセルの x 座標
	 *	\param[in] y	ピクセルの y 座標
	 *	\param[in] col	色要素値
	 *
	 *	\return	更新に成功した場合 true を、失敗した場合 false を返します。
	 */
	bool	setColor(int x, int y, const fk_Color &col);

	//! バッファ全体初期化関数1
	/*!
	 *	画像データ内の全てのピクセルを同一色で初期化します。
	 *	初期化の際には、実際の表示領域ではない部分についても更新を行います。
	 *	格納データについては getBufferSize() の覚え書きを参照して下さい。
	 *
	 *	\param[in] col	色要素値
	 */
	void	fillColor(const fk_Color &col);

	//! バッファ全体初期化関数2
	/*!
	 *	画像データ内の全てのピクセルを同一色で初期化します。
	 *	初期化の際には、実際の表示領域ではない部分についても更新を行います。
	 *	格納データについては getBufferSize() の覚え書きを参照して下さい。
	 *
	 *	\param[in] r	R(赤)要素値
	 *	\param[in] g	G(赤)要素値
	 *	\param[in] b	B(赤)要素値
	 *	\param[in] a	A(赤)要素値
	 */
	void	fillColor(int r, int g, int b, int a = 0);

	//! 画像データ配列先頭アドレス取得関数	
	/*!
	 *	画像データを実際に格納しているデータ配列の先頭アドレスを参照します。
	 *
	 *	\warning
	 *	この関数は fk_Image の内部構造に強く依存します。
	 *	内部構造は今後の更新で変更される可能性があるため、
	 *	本関数を用いた場合は後方互換性が保証できません。
	 *	また、この関数を用いて得た内部データを更新した場合、
	 *	システム全体の整合性が維持できなくなる可能性があります。
	 *	上記の2点の理由から、この関数の利用は推奨しません。
	 *
	 *	\return 画像データ配列の先頭アドレス
	 */
	const fk_ImType *		getBufPointer(void) const;

#ifndef FK_DOXYGEN_USER_PROCESS

	fk_TexID	GetTexID(void);
	void		ClearUpdateArea(void);
	void		SetUpdateArea(void);
	void		SetUpdateArea(int, int, int, int);
	fk_Rect		GetUpdateArea(void);

#endif

};

#endif	// __FK_IMAGE_HEADER__
