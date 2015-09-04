// Texture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Shape_CLI.h"
#include "Image_CLI.h"
#include <string>

namespace FK_CLI
{
	//! テクスチャモードを表す列挙型
	public enum class fk_TexMode {
		MODULATE,	//!<	積算モード
		REPLACE,	//!<	画像モード
		DECAL		//!<	線形補間モード
	};

	//! テクスチャ描画品質を表す列挙型
	public enum class fk_TexRendMode {
		NORMAL,		//!<	標準品質
		SMOOTH		//!<	高品質
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
	public ref class fk_TexCoord {
	internal:
		double x_, y_;
		static operator ::fk_TexCoord (fk_TexCoord^);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_TexCoord(::fk_TexCoord);
#endif

		//! コンストラクタ1
		/*!
		 *	(0, 0) として生成します。
		 */
		fk_TexCoord();

		//! コンストラクタ2
		/*!
		 *	引数で成分を設定します。
		 *
		 *	\param[in]	x	x成分
		 *	\param[in]	y	y成分
		 */
		fk_TexCoord(double x, double y);

		//! デストラクタ
		~fk_TexCoord();

		//! ファイナライザ
		!fk_TexCoord();

		//! x 成分プロパティ
		property double x {
			double get();
			void set(double v);
		}
		
		//! y 成分プロパティ
		property double y {
			double get();
			void set(double v);
		}

		//////////////////// 比較演算子		

		//! 同値比較関数1
		/*!
		 *	2つのテクスチャ座標か同値どうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	T	同値かどうかを判定するテクスチャ座標
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		bool Equals(fk_TexCoord^ T);

		//! 同値比較関数2
		/*!
		 *	2つのテクスチャ座標か同値どうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	O	同値かどうかを判定するテクスチャ座標
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		virtual bool Equals(Object^ O) override;

		//! 成分設定関数
		/*!
		 *	各成分を設定します。
		 *
		 *	\param[in]	x	x成分の値
		 *	\param[in]	y	y成分の値
		 */
		void Set(double x, double y);

		//! 文字列出力関数
		/*!
		 *	現在のテクスチャ座標成分値を文字列として出力します。
		 *
		 *	\return		成分値の文字列
		 */
		String^ fk_TexCoord::ToString() override;
	};

	//! テクスチャ用基底クラス
	/*!
	 *	このクラスは、テクスチャを表すクラスの基底クラスです。
	 *	様々なテクスチャクラスの共通機能を提供します。
	 *	クラス自体の主な機能はテクスチャ画像の生成や入力です。
	 *
	 *	\sa fk_Image, fk_RectTexture, fk_TriTexture, fk_MeshTexture, fk_IFSTexture, fk_Dimension
	 */
	public ref class fk_Texture : fk_Shape {
	internal:
		::fk_Texture * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Texture(bool argNewFlg);
		~fk_Texture();
		!fk_Texture();
#endif

		//! 画像データプロパティ
		/*!
		 *	画像データの参照・設定を行います。
		 *
		 *	\note
		 *		fk_Texture (およびその派生クラス) では、
		 *		最初から自前の画像データ領域を保持しています。
		 *		このプロパティでの設定は、あくまで外部で用意した画像データを
		 *		テクスチャとして利用したい場合に使用するためのものであり、
		 *		必ず設定しなければならないというわけではありません。
		 */
		property fk_Image^ Image {
			fk_Image^ get();
			void set(fk_Image^);
		}

		//! 画像サイズプロパティ
		/*!
		 *	画像サイズを fk_Dimension 型で参照します。
		 *
		 *	\sa BufferSize
		 */
		property fk_Dimension^ ImageSize {
			fk_Dimension^ get();
		}

		//! 画像バッファサイズプロパティ
		/*!
		 *	実際に画像用データバッファとして確保されているサイズを、
		 *	fk_Dimension 型で参照します。
		 *
		 *	\note
		 *		実画像サイズとデータバッファサイズの違いについては、
		 *		fk_Image::BufferSize の覚え書きを参照して下さい。
		 *
		 *	\sa ImageSize, fk_Image::BufferSize
		 */
		property fk_Dimension^ BufferSize {
			fk_Dimension^ get();
		}

		//! テクスチャモードプロパティ
		/*!
		 *	テクスチャの描画時における描画色処理モードの参照・設定を行います。
		 *	これは、ポリゴンに設定されているマテリアルによる発色と、
		 *	テクスチャ画像の色をどのように混成するかを制御するものです。
		 *	それぞれのモードの概要と厳密な計算式を以下に記載します。
		 *	なお、数式中の \f$ C_f \f$ はポリゴン色、
		 *	\f$ C_\alpha \f$ ポリゴンの透明度、
		 *	\f$ T_f \f$ はテクスチャピクセル色、
		 *	\f$ T_\alpha \f$ はテクスチャの透明度を表します。
		 *
		 *	- fk_TexMode.MODULATE \n
		 *		この設定では、ポリゴンの色とテクスチャの色を積算します。
		 *		そのため、光源による陰影効果が生じます。
		 *		透明度に関しても積算となります。
		 *		数式として表すと、色と透明度はそれぞれ
		 *		\f[
		 *			(C_f T_f, \; C_\alpha T_\alpha)
		 *		\f]
		 *		となります。
		 *
		 *	- fk_TexMode.REPLACE \n
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
		 *	- fk_TexMode.DECAL \n
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
		 *	なお、デフォルトでは fk_TexMode.MODULATE が設定されています。
		 */
		property fk_TexMode TextureMode {
			fk_TexMode get();
			void set(fk_TexMode);
		}

		//! テクスチャ描画品質プロパティ
		/*!
		 *	テクスチャの描画品質の参照・設定を行います。
		 *	設定可能なモードは以下の通りです。
		 *	- fk_TexRendMode.NORMAL: 標準品質。描画速度を優先します。
		 *	- fk_TexRendMode.SMOOTH: 高品質。画質を優先します。
		 *	.
		 *	なお、デフォルトでは fk_TexRendMode.NORMAL が設定されています。
		 *
		 *	\param[in]	mode	品質モード
		 */
		property fk_TexRendMode RendMode {
			fk_TexRendMode get();
			void set(fk_TexRendMode);
		}
		
		//! BMP ファイル入力関数
		/*!
		 *	BMP (Windows Bitmap) 形式のファイルからデータを読み込み、
		 *	テクスチャ画像として設定します。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\return	入力に成功すれば true、失敗すれば false を返します。
		 */
		bool	ReadBMP(String^ fileName);

		//! PNG ファイル入力関数
		/*!
		 *	PNG 形式のファイルからデータを読み込み、
		 *	テクスチャ画像として設定します。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\return	入力に成功すれば true、失敗すれば false を返します。
		 */
		bool	ReadPNG(String^ fileName);

		//! JPEG ファイル入力関数
		/*!
		 *	JPEG 形式のファイルからデータを読み込み、
		 *	テクスチャ画像として設定します。
		 *
		 *	\param[in]	fileName	ファイル名
		 *
		 *	\return	入力に成功すれば true、失敗すれば false を返します。
		 */
		bool	ReadJPG(String^ fileName);

		//! 一様色初期化関数1
		/*!
		 *	内部の画像ピクセルを、すべて同じ色で初期化します。
		 *
		 *	\param[in]	color		初期化色
		 *
		 *	\sa fk_Color
		 */
		void	FillColor(fk_Color^ color);
	};
}

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
