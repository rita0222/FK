#pragma once

#include <FK/Material.h>
#include <FK/MatExample.h>
#include "Color_CLI.h"

namespace FK_CLI
{
	//! マテリアル(質感)を管理するクラス
	/*!
	 *	このクラスは、マテリアル(質感)を管理、制御する機能を提供します。
	 *	FKにおけるマテリアルは、以下の要素によって成り立っています。
	 *
	 *	- 環境反射係数 (Ambient)
	 *	- 拡散反射係数 (Diffuse)
	 *	- 鏡面反射係数 (Specular)
	 *	- 放射光係数 (Emission)
	 *	- 鏡面反射ハイライト (Shininess)
	 *	- 透明度 (alpha)
	 *	.
	 *	これらのうち、前者4つは fk_Color による RGBA 色表現であり、
	 *	後者2つは float 型によるスカラー値となっています。
	 *	各要素についての詳細はユーザーズマニュアルやCGの解説文献を参照して下さい。
	 *
	 *	マテリアルには、最初から定義されているグローバル変数があります。
	 *	これらのリストはユーザーズマニュアルの付録Aに記されています。
	 *	利用するには、 InitDefault() メソッドを呼ぶ必要があります。
	 *
	 *	インスタンス生成時の初期状態は以下のような値となります。
	 *
	 *	- 環境反射係数: (0.3, 0.3, 0.3)
	 *	- 拡散反射係数: (0.0, 0.0, 0.0)
	 *	- 鏡面反射係数: (0.2, 0.2, 0.2)
	 *	- 放射光係数: (0.0, 0.0, 0.0)
	 *	- 鏡面反射ハイライト: 17.0
	 *	- 透明度: 1.0
	 *	.
	 *	なお、透過色を設定した場合でも、
	 *	シーンで透過処理設定を有効としなければ、透過処理が行われません。
	 *	詳細は fk_Scene::BlendStatus の説明を参照して下さい。
	 *
	 *	\sa fk_Color, fk_Palette, fk_Scene
	 */
	 public ref class fk_Material {
	 internal:
		 bool dFlg;
		 ::FK::fk_Material *pMat;

		 ::FK::fk_Material * GetP(void);

	 public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		 fk_Material(bool argNewFlg);
#endif
		 //! コンストラクタ1
		 /*!
		  *	概要に述べた初期値に従ってインスタンスの生成を行います。
		  */
		 fk_Material();
		 
		 //! コンストラクタ2
		 /*!
		  *	他の fk_Material 型インスタンスより値をコピーしてインスンタスを生成します。
		  *
		  *	\param[in]	mat	別の fk_Material 型インスタンス
		  */
		 fk_Material(fk_Material^ mat);

		 //! デストラクタ
		 ~fk_Material();

		 //! ファイナライザ
		 !fk_Material();

		 //! 同値比較メソッド1
		 /*!
		  *	二つのマテリアル値が同値かどうかを判定します。
		  *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		  *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		  *
		  *	\param[in]	M	同値かどうかを判定するマテリアル値
		  *
		  *	\return		同値であれば true を、そうでなければ false を返します。
		  */
		 bool Equals(fk_Material^ M);

		 //! 同値比較メソッド2
		 /*!
		  *	二つのマテリアル値が同値かどうかを判定します。
		  *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		  *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		  *
		  *	\param[in]	M	同値かどうかを判定するマテリアル値
		  *
		  *	\return		同値であれば true を、そうでなければ false を返します。
		  */
		 virtual bool Equals(Object^ M) override;

		 //! 透明度プロパティ
		 /*!
		  *	透明度の設定・参照を行います。引数は float 型です。
		  *	設定できる値は 0 から 1 までで、
		  *	範囲外の数値については上下限に丸められます。
		  *
		  *	\note
		  *		透過色を設定した場合でも、
		  *		シーンで透過処理設定を有効としなければ、透過処理が行われません。
		  *		詳細は fk_Scene::BlendStatus の説明を参照して下さい。
		  *
		  *	\sa fk_Scene::BlendStatus
		  */
		 property float Alpha {
			 float get();
			 void set(float argF);
		 }

		 //! 環境反射係数プロパティ
		 /*!
		  *	環境反射係数の設定・参照を行います。
		  *	プロパティは fk_Color 型です。
		  */
		 property fk_Color^ Ambient {
			 fk_Color^ get();
			 void set(fk_Color^ argC);
		 }

		 //! 拡散反射係数プロパティ
		 /*!
		  *	拡散反射係数の設定・参照を行います。
		  *	プロパティは fk_Color 型です。
		  */
		 property fk_Color^ Diffuse {
			 fk_Color^ get();
			 void set(fk_Color^ argC);
		 }

		 //! 鏡面反射係数プロパティ
		 /*!
		  *	鏡面反射係数の設定・参照を行います。
		  *	プロパティは fk_Color 型です。
		  */
		 property fk_Color^ Specular {
			 fk_Color^ get();
			 void set(fk_Color^ argC);
		 }

		 //! 放射光反射係数プロパティ
		 /*!
		  *	放射光反射係数の設定・参照を行います。
		  *	プロパティは fk_Color 型です。
		  */
		 property fk_Color^ Emission {
			 fk_Color^ get();
			 void set(fk_Color^ argC);
		 }

		 //! 鏡面反射ハイライトプロパティ
		 /*!
		  *	鏡面反射ハイライトを設定します。引数は float 型です。
		  */
		 property float Shininess {
			 float get();
			 void set(float s);
		 };

		 //! 初期化メソッド
		 /*!
		  *	変数を初期状態に戻します。
		  */
		 void Init(void);

		 //! デフォルトマテリアル初期化メソッド
		 /*!
		  *	このメソッドを呼ぶと、
		  *	ユーザーズマニュアルに掲載しているマテリアル変数の値を、
		  *	マニュアルに記載してある値に初期化します。
		  *	このメソッドを呼んだ後、該当マテリアル変数を
		  *	別のマテリアル値に設定することが可能です。
		  *
		  *	このメソッドは static 宣言されているため、
		  *	クラスのインスタンスを生成しなくても呼ぶことができます。
		  */
		 static void InitDefault(void);

		 /*!
		  * (0.2, 0.2, 0.2), (0.4, 0.4, 0.4), (0.01, 0.01, 0.01), (10.0)
		  */
		 static fk_Material^ AshGray;

		 /*!
		  * (0.15, 0.28, 0.23), (0.23, 0.47, 0.19), (0.37, 0.68, 0.28), (20.0)
		  */
		 static fk_Material^ BambooGreen;

		 /*!
		  * (0.0, 0.0, 0.0), (0.0, 0.0, 0.7), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Blue;

		 /*!
		  * (0.2, 0.1, 0.0), (0.35, 0.15, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Brown;

		 /*!
		  * (0.1, 0.07, 0.07), (0.44, 0.17, 0.1), (0.6, 0.39, 0.1), (16.0)
		  */
		 static fk_Material^ BurntTitan;

		 /*!
		  * (0.5, 0.3, 0.4), (0.9, 0.5, 0.7), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Coral;

		 /*!
		  * (0.0, 0.0, 0.0), (0.8, 0.7, 0.6), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Cream;

		 /*!
		  * (0.0, 0.0, 0.0), (0.0, 0.6, 0.6), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Cyan;

		 /*!
		  * (0.1, 0.1, 0.4), (0.0, 0.0, 0.25), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ DarkBlue;

		 /*!
		  * (0.1, 0.4, 0.1), (0.0, 0.2, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ DarkGreen;

		 /*!
		  * (0.3, 0.1, 0.3), (0.3, 0.0, 0.3), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ DarkPurple;

		 /*!
		  * (0.2, 0.0, 0.0), (0.4, 0.0, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ DarkRed;

		 /*!
		  * (0.0, 0.0, 0.0), (0.4, 0.3, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ DarkYellow;

		 /*!
		  * (0.18, 0.14, 0.0), (0.84, 0.86, 0.07), (0.92, 0.82, 0.49), (0.0)
		  */
		 static fk_Material^ DimYellow;

		 /*!
		  * (0.0, 0.0, 0.0), (0.8, 0.6, 0.4), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Flesh;

		 /*!
		  * (0.0, 0.0, 0.0), (0.04, 0.04, 0.04), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ GlossBlack;

		 /*!
		  * (0.0, 0.1, 0.0), (0.0, 0.7, 0.0), (0.47, 0.98, 0.49), (0.0)
		  */
		 static fk_Material^ GrassGreen;

		 /*!
		  * (0.0, 0.0, 0.0), (0.6, 0.6, 0.6), (0.1, 0.1, 0.1), (0.0)
		  */
		 static fk_Material^ Gray1;

		 /*!
		  * (0.0, 0.0, 0.0), (0.2, 0.2, 0.2), (0.1, 0.1, 0.1), (0.0)
		  */
		 static fk_Material^ Gray2;

		 /*!
		  * (0.0, 0.0, 0.0), (0.0, 0.5, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Green;

		 /*!
		  * (0.01, 0.22, 0.4), (0.2, 0.66, 0.92), (0.47, 0.74, 0.74), (0.0)
		  */
		 static fk_Material^ HolidaySkyBlue;

		 /*!
		  * (0.04, 0.11, 0.07), (0.09, 0.39, 0.18), (0.08, 0.67, 0.1), (14.0)
		  */
		 static fk_Material^ IridescentGreen;

		 /*!
		  * (0.36, 0.28, 0.18), (0.56, 0.52, 0.29), (0.72, 0.45, 0.4), (33.0)
		  */
		 static fk_Material^ Ivory;

		 /*!
		  * (0.14, 0.0, 0.0), (0.62, 0.0, 0.0), (1.0, 0.46, 0.46), (18.0)
		  */
		 static fk_Material^ LavaRed;

		 /*!
		  * (0.0, 0.0, 0.0), (0.4, 0.4, 0.9), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ LightBlue;

		 /*!
		  * (0.1, 0.2, 0.2), (0.0, 0.5, 0.5), (0.2, 0.2, 0.2), (60.0)
		  */
		 static fk_Material^ LightCyan;

		 /*!
		  * (0.0, 0.0, 0.0), (0.5, 0.7, 0.3), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ LightGreen;

		 /*!
		  * (0.0, 0.0, 0.0), (0.5, 0.4, 0.9), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ LightViolet;

		 /*!
		  * (0.21, 0.09, 0.23), (0.64, 0.54, 0.6), (0.4, 0.26, 0.37), (15.0)
		  */
		 static fk_Material^ Lilac;

		 /*!
		  * (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ MatBlack;

		 /*!
		  * (0.0, 0.0, 0.0), (0.8, 0.3, 0.0), (0.2, 0.2, 0.2), (0.0)
		  */
		 static fk_Material^ Orange;

		 /*!
		  * (0.0, 0.0, 0.0), (0.5, 0.7, 0.7), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ PaleBlue;

		 /*!
		  * (0.32, 0.29, 0.18), (0.64, 0.61, 0.5), (0.4, 0.29, 0.17), (15.0)
		  */
		 static fk_Material^ PearWhite;

		 /*!
		  * (0.6, 0.2, 0.3), (0.9, 0.55, 0.55), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Pink;

		 /*!
		  * (0.0, 0.0, 0.0), (0.7, 0.0, 0.7), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Purple;

		 /*!
		  * (0.0, 0.0, 0.0), (0.7, 0.0, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Red;

		 /*!
		  * (1.0, 1.0, 1.0), (1.0, 1.0, 1.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ TrueWhite;

		 /*!
		  * (0.01, 0.03, 0.21), (0.07, 0.12, 0.49), (0.53, 0.52, 0.91), (11.0)
		  */
		 static fk_Material^ UltraMarine;

		 /*!
		  * (0.0, 0.0, 0.0), (0.4, 0.0, 0.8), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Violet;

		 /*!
		  * (0.0, 0.0, 0.0), (0.8, 0.8, 0.8), (0.1, 0.1, 0.1), (0.0)
		  */
		 static fk_Material^ White;

		 /*!
		  * (0.0, 0.0, 0.0), (0.8, 0.6, 0.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Yellow;

		 /*!
		  * (0.0, 0.0, 0.0), (1.0, 1.0, 1.0), (1.0, 1.0, 1.0), (0.0)
		  */
		 static fk_Material^ WhiteLight;

		 /*!
		  * (1.0, 1.0, 1.0), (1.0, 1.0, 1.0), (0.0, 0.0, 0.0), (0.0)
		  */
		 static fk_Material^ Raw;
	};
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
