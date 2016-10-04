// Image_CLI.h

#pragma once

#include <FK/Image.h>
#include "Base_CLI.h"
#include "Material_CLI.h"

namespace FK_CLI
{
	//! 画像フォーマットを表す列挙型
	public enum class fk_ImageType {
		BMP,	//!< Windows Bitmap (BMP) 形式
		PNG,	//!< PNG 形式
		JPG		//!< JPEG 形式
	};

	//! 画像サイズを表すクラス
	/*!
	 *	このクラスは、画像サイズの設定や取得に利用します。
	 *
	 *	\sa fk_Rect, fk_Image
	 */
	public ref class fk_Dimension {
	internal:
		::fk_Dimension	*pDim;

		::fk_Dimension * GetP(void);

	public:
		//! コンストラクタ1
		/*!
		 *	(0, 0) となるサイズを生成します。
		 */
		fk_Dimension();

		//! コンストラクタ2
		/*!
		 *	\param[in] W 画像の横幅
		 *	\param[in] H 画像の縦幅
		 */
		fk_Dimension(int W, int H);

		//! デストラクタ
		~fk_Dimension();

		//! ファイナライザ
		!fk_Dimension();

		//! 横幅プロパティ
		property int w {
			int get();
			void set(int value);
		}

		//! 縦幅プロパティ
		property int h {
			int get();
			void set(int value);
		}

		//! 横方向プロパティ
		/*!
		 *	w プロパティの別名です。
		 */
		property int x {
			int get();
			void set(int value);
		}

		//! 縦方向プロパティ
		/*!
		 *	h プロパティの別名です。
		 */
		property int y {
			int get();
			void set(int value);
		}

		//! 文字列変換関数
		/*!
		 *	座標を文字列に変換します。
		 *
		 *	\return	変換文字列
		 */
		String^	ToString() override;

		//! 画像サイズ設定関数
		/*!
		 *	\param[in] W 画像の横幅
		 *	\param[in] H 画像の縦幅
		 */
		void Set(int W, int H);
	};

	//! 画像中の矩形領域を表すクラス
	/*!
	 *	このクラスは、画像中の矩形領域を表します。
	 *	このクラスの座標系は、画像の左上を原点とし、
	 *	x の正方向は右、y の正方向は下となります。
	 *
	 *	\sa fk_Dimension, fk_Image
	 */
	public ref class fk_Rect {
	internal:
		::fk_Rect	*pRect;

		::fk_Rect * GetP(void);

	public:

		//! コンストラクタ1
		/*!
		 *	x, y, w, h が全て 0 である初期値を生成します。
		 */
		fk_Rect();

		//! コンストラクタ2
		/*!
		 *	\param[in] X 領域左上の x 座標
		 *	\param[in] Y 領域左上の y 座標
		 *	\param[in] W 領域の横幅
		 *	\param[in] H 領域の縦幅
		 */
		fk_Rect(int X, int Y, int W, int H);

		//! デストラクタ
		~fk_Rect();

		//! ファイナライザ
		!fk_Rect();

		//! 領域左上 x 座標プロパティ
		property int x {
			int get();
			void set(int value);
		}

		//! 領域左上 y 座標プロパティ
		property int y {
			int get();
			void set(int value);
		}

		//! 領域横幅プロパティ
		property int w {
			int get();
			void set(int value);
		}

		//! 領域縦幅プロパティ
		property int h {
			int get();
			void set(int value);
		}

		//! 文字列変換関数
		/*!
		 *	座標を文字列に変換します。
		 *
		 *	\return	変換文字列
		 */
		String^	ToString() override;
		
		//! 領域設定関数
		/*!
		 *	\param[in] X 領域左上の x 座標
		 *	\param[in] Y 領域左上の y 座標
		 *	\param[in] W 領域の横幅
		 *	\param[in] H 領域の縦幅
		 */	
		void Set(int X, int Y, int W, int H);

		//! 領域位置設定関数
		/*!
		 *	\param[in] X 領域左上の x 座標
		 *	\param[in] Y 領域左上の y 座標
		 */
		void SetPos(int X, int Y);

		//! 領域サイズ設定関数
		/*!
		 *	\param[in] W 領域の横幅
		 *	\param[in] H 領域の縦幅
		 */	
		void SetSize(int W, int H);

		//! 領域サイズ参照関数
		/*!
		 *	\return 領域サイズ
		 */
		fk_Dimension^ GetSize(void);
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
	 *	BufferSize プロパティの覚え書きを参照して下さい。
	 *
	 *	\sa fk_Rect, fk_Dimension, fk_Texture
	 */
	public ref class fk_Image : fk_BaseObject {
	internal:
		::fk_Image * GetP(void);

	public:

#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Image(bool argNewFlg);
#endif

		//! コンストラクタ1
		/*!
		 *	空画像を生成します。
		 */
		fk_Image();

		//! コンストラクタ
		/*!
		 *	\param[in] W	画像の横幅
		 *	\param[in] H	画像の縦幅
		 */
		fk_Image(int W, int H);

		//! デストラクタ
		~fk_Image();

		//! ファイナライザ
		!fk_Image();

		//!	画素プロパティ
		/*!
		 *	各画素色値の設定や参照を行います。
		 *
		 *		image[100, 100] = new fk_Color(0.3, 0.4, 0.5);
		 */
		property fk_Color^ default[int, int] {
			fk_Color^ get(int, int);
			void set(int, int, fk_Color^);
		}

		//! 画像サイズプロパティ
		/*!
		 *	画像サイズの参照を行います。
		 */
		property fk_Dimension^ Size {
			fk_Dimension^ get();
		}

		//! 画像バッファサイズプロパティ
		/*!
		 *	fk_Image では、本来の画像サイズに対し、
		 *	格納するデータ領域はより大きなものとなっています。
		 *	このプロパティは、実際に確保しているデータ領域の大きさを
		 *	fk_Dimension 型で取得するものです。
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
		 */
		property fk_Dimension^ BufferSize {
			fk_Dimension^ get();
		}

#ifndef FK_DOXYGEN_USER_PROCESS
		property void* Buffer {
			void* get();
		}
#endif

		//! 初期化関数
		/*!
		 *	画像データを初期化します。
		 *	画像サイズも (0, 0) となります。
		 */
		void Init(void);

		
		//! 画像領域生成関数1
		/*!
		 *	画像データを与えられたサイズに従って生成します。
		 *
		 *	\param[in] w	画像の横幅
		 *	\param[in] h	画像の縦幅
		 *	\param[in] initFlg
		 *		true の場合は、
		 *		データ全体を色値 (0, 0, 0, 0) で初期化します。
		 *		false の場合は初期化を行いませんが、
		 *		その場合でも横幅が変更されたときは
		 *		各ピクセルの縦横関係が崩れてしまう可能性があります。
		 */
		void NewImage(int w, int h, bool initFlg);

		//! 画像領域生成関数2
		/*!
		 *	画像データを与えられたサイズに従って生成します。
		 *	データ全体の色値は (0, 0, 0, 0) で初期化します。
		 *
		 *	\param[in] w	画像の横幅
		 *	\param[in] h	画像の縦幅
		 */
		void NewImage(int w, int h);

		//! 画像データコピー関数1
		/*!
		 *	画像データを別インスタンスからコピーします。
		 *	この引数形式の場合、画像サイズは元画像データと同一となります。
		 *
		 *	\param[in] image	元画像インスタンス
		 */
		void CopyImage(fk_Image^ image);
		
		//! 画像データコピー関数2
		/*!
		 *	画像データの部分矩形領域を、別インスタンスの画像データ内容に書き換えます。
		 *	この引数形式では、画像中の一部分となる任意領域を書き換えることが可能ですが、
		 *	コピー元となる画像全体がコピー先の中に完全に収まるような配置である必要があります。
		 * 	この条件を満たさなかった場合は、データの書き換えを行いません。
		 *	配置の際の座標系は fk_Rect の座標系に従います。
		 *
		 *	\param[in] image	元画像インスタンス
		 *	\param[in] x		書き換え領域左上の x 座標
		 *	\param[in] y		書き換え領域左上の y 座標
		 */
		void CopyImage(fk_Image^ image, int x, int y);
		
		//! 画像データ部分抽出関数
		/*!
		 *	別インスタンス中にある画像データの部分矩形領域をコピーします。
		 *	指定した矩形領域は全て元画像内に収まっている必要があります。
		 *	領域の座標系は fk_Rect の座標系に従います。
		 *
		 *	\param[in] image	元画像インスタンス
		 *	\param[in] x		抽出矩形領域左上の x 座標
		 *	\param[in] y		抽出矩形領域左上の y 座標
		 *	\param[in] w		抽出矩形領域の横幅
		 *	\param[in] h		抽出矩形領域の縦幅
		 */
		bool SubImage(fk_Image^ image, int x, int y, int w, int h);

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
		int	GetR(int x, int y);

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
		int GetG(int x, int y);

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
		int GetB(int x, int y);

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
		int GetA(int x, int y);

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
		bool SetRGBA(int x, int y, int r, int g, int b, int a);

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
		bool SetRGB(int x, int y, int r, int g, int b);

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
		 *	\return
		 *		更新に成功した場合 true を、失敗した場合 false を返します。
		 *		値の丸めが入った場合については、失敗とはみなしません。
		 */
		bool SetR(int x, int y, int r);

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
		 *	\return
		 *		更新に成功した場合 true を、失敗した場合 false を返します。
		 *		値の丸めが入った場合については、失敗とはみなしません。
		 */
		bool SetG(int x, int y, int g);

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
		 *	\return
		 *		更新に成功した場合 true を、失敗した場合 false を返します。
		 *		値の丸めが入った場合については、失敗とはみなしません。
		 */
		bool SetB(int x, int y, int b);

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
		 *	\return
		 *		更新に成功した場合 true を、失敗した場合 false を返します。
		 *		値の丸めが入った場合については、失敗とはみなしません。
		 */
		bool SetA(int x, int y, int a);

		//! バッファ全体初期化関数1
		/*!
		 *	画像データ内の全てのピクセルを同一色で初期化します。
		 *	初期化の際には、実際の表示領域ではない部分についても更新を行います。
		 *	格納データについては BufferSize プロパティの覚え書きを参照して下さい。
		 *
		 *	\param[in] color	色要素値
		 */
		void FillColor(fk_Color^ color);

		//! バッファ全体初期化関数2
		/*!
		 *	画像データ内の全てのピクセルを同一色で初期化します。
		 *	初期化の際には、実際の表示領域ではない部分についても更新を行います。
		 *	格納データについては BufferSize プロパティの覚え書きを参照して下さい。
		 *
		 *	\param[in] r	R(赤)要素値
		 *	\param[in] g	G(赤)要素値
		 *	\param[in] b	B(赤)要素値
		 *	\param[in] a	A(赤)要素値
		 */
		void FillColor(int r, int g, int b, int a);

		//! バッファ全体初期化関数3
		/*!
		 *	画像データ内の全てのピクセルを同一色で初期化します。
		 *	初期化の際には、実際の表示領域ではない部分についても更新を行います。
		 *	透過値は 0 に設定します。
		 *	格納データについては BufferSize の覚え書きを参照して下さい。
		 *	
		 *	\param[in] r	R(赤)要素値
		 *	\param[in] g	G(赤)要素値
		 *	\param[in] b	B(赤)要素値
		 */
		void FillColor(int r, int g, int b);

		//! BMP ファイル入力関数
		/*!
		 *	BMP (Windows Bitmap) 形式のファイルからデータを読み込みます。
		 *
		 *	\param[in] fileName	ファイル名
		 *
		 *	\return 入力に成功すれば true、失敗すれば false を返します。
		 */
		bool ReadBMP(String^ fileName);

		//! PNG ファイル入力関数
		/*!
		 *	PNG 形式のファイルからデータを読み込みます。
		 *
		 *	\param[in] fileName	ファイル名
		 *
		 *	\return 入力に成功すれば true、失敗すれば false を返します。
		 */
		bool ReadPNG(String^ fileName);

		//! JPEG ファイル入力関数
		/*!
		 *	JPEG 形式のファイルからデータを読み込みます。
		 *
		 *	\param[in] fileName	ファイル名
		 *
		 *	\return 入力に成功すれば true、失敗すれば false を返します。
		 */
		bool ReadJPG(String^ fileName);

		//! BMP ファイル出力関数1
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
		bool WriteBMP(String^ fileName, bool transFlg);

		//! BMP ファイル出力関数2
		/*!
		 *	画像データを BMP (Windows Bitmap) 形式でファイルに保存します。
		 *
		 *	\param[in] fileName	ファイル名
		 *
		 *	\return 書き出しに成功すれば true、失敗すれば false を返します。
		 */
		bool WriteBMP(String^ fileName);

		//! PNG ファイル出力関数1
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
		bool WritePNG(String^ fileName, bool transFlg);

		//! PNG ファイル出力関数2
		/*!
		 *	画像データを PNG 形式でファイルに保存します。
		 *
		 *	\param[in] fileName	ファイル名
		 *
		 *	\return 書き出しに成功すれば true、失敗すれば false を返します。
		 */
		bool WritePNG(String^ fileName);

		//! JPEG ファイル出力関数1
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
		bool WriteJPG(String^ fileName, int quality);

		//! JPEG ファイル出力関数2
		/*!
		 *	画像データを JPEG 形式でファイルに保存します。
		 *	なお、JPEG 形式は透過がサポートされていないので、
		 *	画像中に透過色データを出力することはできません。
		 *	本関数は WriteJPG(String^, int) において、
		 *	品質値を 80 に設定した場合と同一の挙動となります。
		 *
		 *	\param[in] fileName	ファイル名
		 *
		 *	\return 書き出しに成功すれば true、失敗すれば false を返します。
		 */
		bool WriteJPG(String^ fileName);
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
