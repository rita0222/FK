// SpriteModel_CLI.h

#pragma once

#include <FK/SpriteModel.h>
#include "Model_CLI.h"
#include "Texture_CLI.h"
#include "TextImage_CLI.h"

namespace FK_CLI
{
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
	public ref class fk_SpriteModel : fk_Model {
	internal:
		::fk_SpriteModel * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_SpriteModel(bool argNewFlg);
#endif

		//! コンストラクタ
		fk_SpriteModel();

		//! デストラクタ
		~fk_SpriteModel();

		//! ファイナライザ
		!fk_SpriteModel();

		//! 文字列描画オブジェクトプロパティ
		/*!
		 *	drawText() 関数によって制御される fk_TextImage 型のプロパティです。
		 *	このプロパティに対して様々な操作を行うことができ、
		 *	フォントや表示色など多くの属性を制御できます。
		 *	詳細は、 fk_TextImage クラスのマニュアルを参照して下さい。
		 *	なお、このプロパティに対して別に生成した
		 *	fk_TextImage 型インスタンスを代入することはできません。
		 *
		 *	\sa fk_TextImage
		 */
		property fk_TextImage^ Text {
			fk_TextImage^ get();
		}

		//! 画像データプロパティ
		/*!
		 *	内部の画像データインスタンスの参照・設定を行います。
		 *	画像サイズを変更しない限りは、内部データを直接変更しても問題ありません。
		 *
		 *	\attention
		 *		本関数で得たインスタンスの画像サイズを変更した場合の挙動は保証されません。
		 */
		property fk_Image^ Image {
			fk_Image^ get();
			void set(fk_Image^);
		}

		//! 表示サイズプロパティ
		/*!
		 *	画像の表示サイズの参照・設定を行います。
		 *	通常は画像の設定時に自動調整を行っていますので、
		 *	敢えてそこからサイズを変更したい時に使います。
		 *	引数を省略すると、読み込んである画像と同じサイズに復元します。
		 *	数値 1 が 1 ピクセルに相当する値になります。
		 *	-1 を指定した場合、元画像の横幅・縦幅となります。
		 *
		 *	\sa SetPositionLT(), SetSpriteArea()
		 */
		property fk_TexCoord^ Size {
			fk_TexCoord^ get();
			void set(fk_TexCoord^);
		}

		//! 画像表示モードプロパティ
		/*!
		 *	画像を滑らかに表示するかどうかという状態の参照・設定を行います。
		 *	true であれば滑らかな表示に設定し、
		 *	false であれば滑らかな表示は行いません。
		 */
		property bool SmoothMode {
			bool get();
			void set(bool);
		}

		//! Windows Bitmap (BMP)画像読み込み関数
		/*!
		 *	Windows Bitmap 形式 (BMP形式) の画像を読み込みます。
		 *
		 *	\param[in]	filename		BMP形式ファイル名
		 *
		 *	\return
		 *		成功したら true を、失敗したら false を返します。
		 */
		bool			ReadBMP(String^ filename);

		//! PNG画像読み込み関数
		/*!
		 *	PNG形式の画像を読み込みます。アルファチャンネルによる透過に対応しています。
		 *
		 *	\param[in]	filename		PNG形式ファイル名
		 *
		 *	\return
		 *		成功したら true を、失敗したら false を返します。
		 */
		bool			ReadPNG(String^ filename);

		//! JPEG(JPG)画像読み込み関数
		/*!
		 *	JPEG形式の画像を読み込みます。
		 *
		 *	\param[in]	filename		PNG形式ファイル名
		 *
		 *	\return
		 *		成功したら true を、失敗したら false を返します。
		 */
		bool			ReadJPG(String^ filename);

		//! 画像位置指定関数
		/*!
		 *	指定した座標が左上になるように位置を変更します。
		 *	指定する数値は、画面中心を原点とする座標系で、
		 *	数値 1 が 1 ピクセルに相当する値になります。
		 *
		 *	画像の中心位置を指定したい場合は、
		 *	fk_Model::GlMoveTo() を利用して下さい。
		 *
		 *	\attention
		 *		本関数によって位置を指定した後に、
		 *		以下に述べるような操作を行った場合、
		 *		表示位置が不適切となる場合があります。
		 *			- fk_SpriteModel::Size プロパティによる大きさ変更。
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
		 *	\sa Size, fk_Model::GlMoveTo()
		 */
		void			SetPositionLT(double x, double y);

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
		 *	\sa Size
		 */
		void			SetSpriteArea(double x, double y, double w, double h);

		//! 文字列描画用フォント設定関数
		/*!
		 *	文字表示を行うための、フォントの設定を行います。
		 *	DrawText() による文字列表示を行いたい場合は、事前に本関数を実行する必要があります。
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
		bool			InitFont(String^ fontFileName);

		//! 文字列表示関数
		/*!
		 *	指定された文字列を表示する画像を設定します。
		 *	本関数を実行する前に、事前に InitFont() でフォント指定を行う必要があります。
		 *
		 *	\note
		 *		fk_SprinteModel::Text プロパティを制御して表示方法を変更したい場合は、
		 *		本関数を実行する前に行う必要があります。
		 *		事後に変更しても有効にならないので注意してください。
		 *
		 *	\param[in]	str
		 *		指定文字列。既に設定されていた文字列があった場合は、その末尾に付け足します。
		 *
		 *	\sa InitFont(), DrawText(String^, bool)
		 */
		void			DrawText(String^ str);

		//! 初期化設定付き文字列表示関数
		/*!
		 *	指定された文字列を表示する画像を設定します。
		 *	本関数を実行する前に、事前に InitFont() でフォント指定を行う必要があります。
		 *
		 *	\note
		 *		fk_SpriteModel::Text メンバを制御して表示方法を変更したい場合は、
		 *		本関数を実行する前に行う必要があります。
		 *		事後に変更しても有効にならないので注意してください。
		 *
		 *	\param[in]	str		指定文字列
		 *
		 *	\param[in]	mode
		 *		true を渡すとこれまでに入力した文字列を一旦消去し、
		 *		新たに文字列を生成します。
		 *		false を渡すと、 DrawText(String^) と同様に、
		 *		これまでに入力した文字列への付け足しを行います。
		 *
		 *	\sa initFont(), drawText(const std::string, fk_StringCode)
		 */
		void			DrawText(String^ str, bool mode);

		//! 文字列消去関数
		/*!
		 *	DrawText() 関数によって作成した文字列を消去します。
		 *
		 *	\sa DrawText(String^), DrawText(String^, bool)
		 */
		void			ClearText(void);
	};
}
