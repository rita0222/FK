// Color_CLI.h

#pragma once

#include <FK/Color.h>
#include "Base_CLI.h"

namespace FK_CLI
{
	//! RGB色を管理するクラス
	/*!
	 *	このクラスは、RGBA法による色を管理、制御する機能を提供します。
	 *	「RGBA」のRが赤、Gが緑、Bが青、Aが透過度を意味します。
	 *	各要素は float 型によって表現し、値域は 0 から 1 までです。
	 *	透過色要素は 0 が完全な透明、1 が完全な不透明となります。
	 *
	 *	なお、透過色を設定した場合でも、
	 *	シーンで透過処理設定を有効としなければ、透過処理が行われません。
	 *	詳細は fk_Scene::BlendStatus の説明を参照して下さい。
	 *
	 *	\sa fk_Material, fk_Scene
	 */
	public ref class fk_Color {
	internal:
		bool dFlg;
		::FK::fk_Color *pCol;
		::FK::fk_Color * GetP(void);
		static operator ::FK::fk_Color(fk_Color^);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Color(bool argNewFlg);
		fk_Color(::FK::fk_Color);
#endif		

		//! コンストラクタ1
		/*!
		 *	RGB値がすべて 0.2, 透過色 1 (完全不透明) であるデフォルト値で色を生成します。
		 */
		fk_Color();

		//! コンストラクタ2
		/*!
		 *	R,G,Bの各色を引数で指定します。透過色要素は初期値では 1 になります。
		 *
		 *	\param[in] R R要素の値
		 *	\param[in] G G要素の値
		 *	\param[in] B B要素の値
		 */
		fk_Color(double R, double G, double B);
		
		//! コンストラクタ3
		/*!
		 *	R,G,B,A(透過色)の各色を引数で指定します。
		 *
		 *	\param[in] R R要素の値
		 *	\param[in] G G要素の値
		 *	\param[in] B B要素の値
		 *	\param[in] A A要素の値
		 */
		fk_Color(double R, double G, double B, double A);

		//! コンストラクタ4
		/*!
		 *	R,G,Bの各色を引数で指定します。透過色要素は初期値では 1 になります。
		 *
		 *	\param[in] R R要素の値
		 *	\param[in] G G要素の値
		 *	\param[in] B B要素の値
		 */
		fk_Color(float R, float G, float B);

		//! コンストラクタ5
		/*!
		 *	R,G,B,A(透過色)の各色を引数で指定します。
		 *
		 *	\param[in] R R要素の値
		 *	\param[in] G G要素の値
		 *	\param[in] B B要素の値
		 *	\param[in] A A要素の値
		 */
		fk_Color(float R, float G, float B, float A);

		//! デストラクタ
		~fk_Color();

		//! ファイナライザ
		!fk_Color();

		//! 色要素配列プロパティ
		/*!
		 *	各色要素を float の配列によってアクセスできるプロパティです。
		 *	メソッドを介さずに直接参照、操作しても問題ありません。
		 */
		property float col[int] {
			float get(int argI);
			void set(int argI, float argC);
		}

		//! R(赤)要素プロパティ
		/*!
		 *	R(赤)要素の参照・設定を行います。0から1の値となります。
		 */
		property float r {
			float get();
			void set(float argF);
		}

		//! G(緑)要素プロパティ
		/*!
		 *	G(緑)要素の参照・設定を行います。0から1の値となります。
		 */
		property float g {
			float get();
			void set(float argF);
		}

		//! B(青)要素プロパティ
		/*!
		 *	B(青)要素の参照・設定を行います。0から1の値となります。
		 */
		property float b {
			float get();
			void set(float argF);
		}

		//! A(透過色)要素プロパティ
		/*!
		 *	A(透過色)要素の参照・設定を行います。
		 *	0から1の値となり、0 が完全な透明、1 が完全な不透明となります。
		 */
		property float a {
			float get();
			void set(float argF);
		}

		//! \name 二項演算子
		//@{

		//! 色要素和二項演算子
		/*!
		 *	色値 C1 と C2 の和を得るには、以下のように記述します。
		 *	C1, C2, C3 はいずれも fk_Color 型の変数です。
		 *
		 *		C3 = C1 + C2;
		 *
		 *	なお演算の結果、成分値が 1 を超える場合はその成分を 1 とします。
		 */
		static fk_Color^ operator+(fk_Color^, fk_Color^);

		//! 色要素差二項演算子
		/*!
		 *	色値 C1 と C2 の差を得るには、以下のように記述します。
		 *	C1, C2, C3 はいずれも fk_Color 型の変数です。
		 *
		 *		C3 = C1 - C2;
		 *
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 にします。
		 */
		static fk_Color^ operator-(fk_Color^, fk_Color^);

		//! 実数倍二項演算子1
		/*!
		 *	ベクトル C1 のスカラー倍色値を得るには、以下のように記述します。
		 *	C1, C2 は共に fk_Color 型の変数で、d は double 型の変数です。
		 *
		 *		C2 = C1 * d;
		 *
		 *	色値と実数の順番は逆でも構いません。
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 に、
		 *	1 を超える場合はその成分を 1 とします。
		 */
		static fk_Color^ operator*(fk_Color^, double);

		//! 実数倍二項演算子2
		/*!
		 *	ベクトル C1 のスカラー倍色値を得るには、以下のように記述します。
		 *	C1, C2 は共に fk_Color 型の変数で、d は double 型の変数です。
		 *
		 *		C2 = d * C1;
		 *
		 *	色値と実数の順番は逆でも構いません。
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 に、
		 *	1 を超える場合はその成分を 1 とします。
		 */
		static fk_Color^ operator*(double, fk_Color^);

		//! 実数商二項演算子
		/*!
		 *	ベクトル C1 のスカラー商色値を得るには、以下のように記述します。
		 *	C1, C2 は共に fk_Color 型の変数で、d は double 型の変数です。
		 *
		 *		C2 = C1/d;
		 *
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 に、
		 *	1 を超える場合はその成分を 1 とします。
		 */
		static fk_Color^ operator/(fk_Color^, double);

		//@}

		//! \name 代入演算子
		//@{
		
		//! 実数積代入演算子
		/*!
		 *	以下のコードは、C の各成分を d 倍します。
		 *	C は fk_Color 型の変数、d は double 型の変数です。
		 *
		 *		C *= d;
		 *
		 *	d は変数でなく数値でも構いません。
		 *
		 *		C *= 2.0;
		 *
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 に、
		 *	1 を超える場合はその成分を 1 とします。
		 */
		static void operator *= (fk_Color^, double);

		//! 実数商代入演算子
		/*!
		 *	以下のコードは、C の各成分を 1/d 倍します。
		 *	C は fk_Color 型の変数、d は double 型の変数です。
		 *
		 *		C /= d;
		 *
		 *	d は変数でなく数値でも構いません。
		 *
		 *		C /= 2.0;
		 *
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 に、
		 *	1 を超える場合はその成分を 1 とします。
		 *	また、d が 0 であった場合は C の値を変更しません。
		 */
		static void operator /= (fk_Color^, double);

		//! 単項和代入演算子
		/*!
		 *	以下のコードは、C1 に C2 を追加します。
		 *	C1、C2 はいずれも fk_Color 型の変数です。
		 *
		 *		C1 += C2;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		C1 = C1 + C2;
		 *
		 *	なお演算の結果、成分値が 1 を超える場合はその成分を 1 とします。
		 */
		static void operator += (fk_Color^, fk_Color^);

		//! 単項差代入演算子
		/*!
		 *	以下のコードは、C1 から C2 を引きます。
		 *	C1、C2 はいずれも fk_Color 型の変数です。
		 *
		 *		C1 -= C2;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		C1 = C1 - C2;
		 *
		 *	なお演算の結果、成分値が 0 未満となる場合はその成分を 0 にします。
		 */
		static void operator -= (fk_Color^, fk_Color^);

		//@}
		
		//! 同値比較メソッド1
		/*!
		 *	二つの色値が同値かどうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	C	同値かどうかを判定する色値
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		bool Equals(fk_Color^ C);

		//! 同値比較メソッド2
		/*!
		 *	二つの色値の値が同値かどうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	C	同値かどうかを判定する色値
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		virtual bool Equals(Object^ C) override;

		//! 文字列出力メソッド
		/*!
		 *	現在の色成分値を文字列として出力します。
		 *
		 *	\return		成分値の文字列
		 */
		String^ ToString() override;

		//! 初期化メソッド1
		/*!
		 *	(R, G, B, A) = (0, 0, 0, 1) で初期化を行います。
		 */
		void Init(void);

		//! 初期化メソッド2
		/*!
		 *	色要素の設定を行います。
		 *	Set(float, float, float) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 */
		void Init(float R, float G, float B);

		//! 初期化メソッド3
		/*!
		 *	色要素の設定を行います。
		 *	同一引数型を持つ Set(float, float, float, float) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 *	\param[in] A A要素値
		 */
		void Init(float R, float G, float B, float A);

		//! 初期化メソッド4
		/*!
		 *	色要素の設定を行います。
		 *	Set(double, double, double) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 */
		void Init(double R, double G, double B);

		//! 初期化メソッド5
		/*!
		 *	色要素の設定を行います。
		 *	同一引数型を持つ Set(double, double, double, double) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 *	\param[in] A A要素値
		 */
		void Init(double R, double G, double B, double A);

		//! 設定メソッド1
		/*!
		 *	色要素の設定を行います。
		 *	Init(float, float, float) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 */
		void Set(float R, float G, float B);

		//! 設定メソッド2
		/*!
		 *	色要素の設定を行います。
		 *	Init(float, float, float, float) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 *	\param[in] A A要素値
		 */
		void Set(float R, float G, float B, float A);

		//! 設定メソッド3
		/*!
		 *	色要素の設定を行います。
		 *	Init(double, double, double) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 */
		void Set(double R, double G, double B);

		//! 設定メソッド4
		/*!
		 *	色要素の設定を行います。
		 *	Init(double, double, double, double) と同様に動作します。
		 *
		 *	\param[in] R R要素値
		 *	\param[in] G G要素値
		 *	\param[in] B B要素値
		 *	\param[in] A A要素値
		 */
		void Set(double R, double G, double B, double A);

		//! HSV変換メソッド
		/*!
		 *	HSV色からの変換を行い、その結果を格納します。
		 *	透明度は 1.0 (完全な不透明) となります。
		 *	
		 *
		 *	\param[in] H 色相要素値。単位は弧度法(ラジアン)です。
		 *	\param[in] S 彩度要素値。最小値は0、最大値は1です。
		 *	\param[in] V 明度要素値。最小値は0、最大値は1です。
		 */
		void SetHSV(double H, double S, double V);
	};
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
