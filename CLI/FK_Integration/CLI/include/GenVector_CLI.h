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

﻿// GenVector_CLI.h

#pragma once

#include <FK/GenVector.h>
#include "Matrix_CLI.h"

namespace FK_CLI {
	using namespace System;

	//! 任意次元ベクトルを管理するクラス
	/*!
	 * 	このクラスは、任意次元ベクトルの様々な機能を提供します。
	 *	このクラス単体でも、線形空間におけるベクトルの様々な演算を利用することができます。
	 *	最も重要な機能は、
	 *	fk_GenMatrix クラスと合わせた行列演算による連立方程式の計算です。
	 *	4元以下の行列演算については、 fk_Matrix を利用した方が高速です。
	 *
	 *	\sa fk_GenMatrix, fk_Vector, fk_HVector, fk_Matrix
	 */
	public ref class fk_GenVector {
	internal:
		::fk_GenVector *pGVec;

	public:

#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_GenVector(::fk_GenVector *argV);
#endif
		//! コンストラクタ1
		/*!
		 *	次元数が 0 である (つまり成分のない)ベクトルを生成します。
		 */
		fk_GenVector();

		//! コンストラクタ2
		/*!
		 *	次元数のみを指定するコンストラクタです。
		 *	全ての成分に 0 が設定されます。
		 *
		 *	\param[in]	deg		次元数
		 */
		fk_GenVector(int deg);

		//! コンストラクタ3
		/*!
		 *	このコンストラクタでは、
		 *	引数として double 型配列 (array) を入力とします。
		 *
		 *	\param[in]	array	成分値配列
		 */
		fk_GenVector(cli::array<double>^ array);

		//! fk_Vector からのコピーコンストラクタ
		fk_GenVector(fk_Vector^ V);

		//! fk_HVector からのコピーコンストラクタ
		fk_GenVector(fk_HVector^ H);

		//! コピーコンストラクタ
		fk_GenVector(fk_GenVector^ GV);

		//! デストラクタ
		~fk_GenVector();

		//! ファイナライザ
		!fk_GenVector();

		//////////////////// 比較演算子		

		//! 同値比較関数1
		/*!
		 *	2つのベクトルの値が同値かどうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	V	同値かどうかを判定するベクトル
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		bool Equals(fk_GenVector^ V);

		//! 同値比較関数2
		/*!
		 *	2つのベクトルの値が同値かどうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	O	同値かどうかを判定するベクトル
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		virtual bool Equals(Object^ O) override;

		//////////////////// 単項演算子

		//! 単項マイナス演算子 
		/*!
		 *	fk_GenVector では、以下のように記述することで、v2 に -v1 を代入できます。
		 *	全ての成分の符号が反転します。
		 *	v2 の次元数は v1 と同じに設定されます。
		 *
		 *		v2 = -v1;
		 */
		static fk_GenVector^ operator-(fk_GenVector^ argV);

		//! 内積二項演算子 
		/*!
		 *	fk_GenVector 型の n 次元ベクトル
		 *	\f$ \mathbf{P} \f$ と \f$ \mathbf{Q} \f$
		 *	の内積値(スカラー積)は、以下のように定義されます。
		 *
		 *	\f[
		 *		\mathbf{P}\cdot\mathbf{Q} = \sum_{i=0}^{n-1} P_iQ_i
		 *	\f]
		 *	
		 *	これを得るには、以下のように記述します。d は double 型の変数です。
		 *
		 *		d = P * Q;
		 *
		 *	P と Q の次元数が異なる場合は、無条件に 0.0 を返します。
		 *	なお、内積演算は交換法則が成り立ちます。
		 */
		static double operator*(fk_GenVector^ P, fk_GenVector^ Q);


		//! ベクトル和二項演算子
		/*!
		 *	ベクトル P と Q の和を得るには、以下のように記述します。
		 *	P, Q, R はいずれも fk_GenVector 型の変数です。
		 *
		 *		R = P + Q;
		 *
		 *	P と Q の次元数が異なる場合は、次元数 0 のベクトルを返します。
		 *	なお、和演算は交換法則が成り立ちます。
		 */
		static fk_GenVector^ operator+(fk_GenVector^ P, fk_GenVector^ Q);

		//! ベクトル差二項演算子
		/*!
		 *	ベクトル P と Q の差を得るには、以下のように記述します。
		 *	P, Q, R はいずれも fk_GenVector 型の変数です。
		 *
		 *		R = P - Q;
		 *
		 *	P と Q の次元数が異なる場合は、次元数 0 のベクトルを返します。
		 *	なお、差演算は交換法則は成り立ちません。
		 */
		static fk_GenVector^ operator-(fk_GenVector^ P, fk_GenVector^ Q);

		//! 実数倍二項演算子1
		/*!
		 *	ベクトル V1 のスカラー倍ベクトルを得るには、以下のように記述します。
		 *	V1, V2 は共に fk_GenVector 型の変数で、d は double 型の変数です。
		 *
		 *		V2 = V1 * d;
		 *
		 *	なお、ベクトルと実数の順番は逆でも構いません。
		 */
		static fk_GenVector^ operator*(fk_GenVector^ V1, double d);

		//! 実数倍二項演算子2
		/*!
		 *	ベクトル V1 のスカラー倍ベクトルを得るには、以下のように記述します。
		 *	V1, V2 は共に fk_GenVector 型の変数で、d は double 型の変数です。
		 *
		 *		V2 = d * V1;
		 *
		 *	なお、ベクトルと実数の順番は逆でも構いません。
		 */
		static fk_GenVector^ operator*(double d, fk_GenVector^ V1);

		//! 実数商二項演算子
		/*!
		 *	ベクトル V1 のスカラー商ベクトルを得るには、以下のように記述します。
		 *	V1, V2 は共に fk_GenVector 型の変数で、d は double 型の変数です。
		 *
		 *		V2 = V1/d;
		 */
		static fk_GenVector^ operator/(fk_GenVector^ V1, double d);

		//! 外積二項演算子
		/*!
		 *	n次元ベクトル \f$ \mathbf{P} \f$ と \f$ \mathbf{Q} \f$
		 *	の外積ベクトル(ベクトル積)は、以下のように定義されます。
		 *
		 *	\f[
		 *		\mathbf{P} \times \mathbf{Q} =
		 *		\left(P_1Q_2 - P_2Q_1, \; P_2Q_3 - P_3Q_2,
		 *		\ldots, \; P_{n-2}Q_{n-1} - P_{n-1}Q_{n-2}, \;
		 *		P_{n-1}Q_0 - P_0Q_{n-1}, \;
		 *		P_0Q_1 - P_1Q_0\right)
		 *	\f]
		 *
		 *	これを得るには、以下のように記述します。
		 *	P,Q,R はいずれも fk_Vector 型の変数です。
		 *
		 *		R = P ^ Q;
		 *
		 *	P と Q の次元数が異なる場合は、次元数 0 のベクトルを返します。
		 */
		static fk_GenVector^ operator ^(fk_GenVector^ P, fk_GenVector^ Q);

		//代入演算子

		//! 実数積演算子
		/*!
		 *	以下のコードは、ベクトル V の成分全てを d 倍します。
		 *	V は fk_GenVector 型の変数、d は double 型の変数です。
		 *
		 *		V *= d;
		 *
		 *	d は変数でなく数値でも構いません。
		 *
		 *		V *= 2.0;
		 */
		static void operator *=(fk_GenVector^ V, double d);

		//! 実数商代入演算子
		/*!
		 *	以下のコードは、ベクトル V の成分全てを 1/d 倍します。
		 *	V は fk_GenVector 型の変数、d は double 型の変数です。
		 *
		 *		V /= d;
		 *
		 *	d は変数でなく数値でも構いません。
		 *
		 *		V /= 2.0;
		 *
		 *	なお、d が 0 であった場合は V の値を変更しません。
		 */
		static void operator /=(fk_GenVector^ V, double d);

		//! 単項和代入演算子
		/*!
		 *	以下のコードは、V1 に V2 を追加します。
		 *	V1、V2 はいずれも fk_GenVector 型の変数です。
		 *
		 *		V1 += V2;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		V1 = V1 + V2;
		 *
		 *	V1 と V2 の次元数が異なる場合は、V1 の値は変化しません。
		 */
		static void operator +=(fk_GenVector^ V1, fk_GenVector^ V2);

		//! 単項差代入演算子
		/*!
		 *	以下のコードは、V1 から V2 を引きます。
		 *	V1、V2 はいずれも fk_Vector 型の変数です。
		 *
		 *		V1 -= V2;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		V1 = V1 - V2;
		 *
		 *	V1 と V2 の次元数が異なる場合は、V1 の値は変化しません。
		 */
		static void operator -=(fk_GenVector^ V1, fk_GenVector^ V2);

		//! 成分プロパティ
		/*!
		 *	各成分の設定や参照を行います。
		 *
		 *		V[0] = 5.0;
		 */
		property double default[int] {
			double get(int argID);
			void set(int argID, double argD);
		}

		//! 次元数プロパティ
		/*!
		 *	次元数 (成分の個数) の設定や参照を行います。
		 *
		 *		int deg = V.size;
		 *		V.size = 10;
		 */
		property int Size {
			void set(int);
			int get();
		}

		//! ノルムプロパティ
		/*!
		 *	現在のベクトルのノルム(長さ)を取得します。
		 *	これは、ベクトル
		 *	\f$ \mathbf{V} = \{V_0, V_1, \ldots, V_{n-1}\} \f$
		 *	に対し、
		 *	\f[
		 *		\sqrt{\sum_{i = 0}^{n-1} {V_i}^2}
		 *	\f]
		 *	の値となります。
		 *
		 *	\sa Normalize()
		 */
		property double Norm {
			double get();
		}

		//! ノルム2乗プロパティ
		/*!
		 *	現在のベクトルのノルム(長さ)の2乗を取得します。
		 *	これは、ベクトル
		 *	\f$ \mathbf{V} = \{V_0, V_1, \ldots, V_{n-1}\} \f$
		 *	に対し、
		 *	\f[
		 *		\sum_{i = 0}^{n-1} {V_i}^2
		 *	\f]
		 *	の値となります。
		 *
		 *	\sa Normalize()
		 */
		property double Norm2 {
			double get();
		}
		
		//! 文字列出力関数
		/*!
		 *	現在のベクトル成分値を文字列として出力します。
		 *
		 *	\return		成分値の文字列
		 */
		String^	ToString() override;

		//! 正規化関数
		/*!
		 *	ベクトルの正規化を行います。
		 *	正規化とは、ベクトル \f$ \mathbf{V} \f$ に対し、
		 *	以下の演算で \f$ \mathbf{V}' \f$ を求めることです。
		 *
		 *	\f[
		 *		\mathbf{V}' = \frac{\mathbf{V}}{|\mathbf{V}|}
		 *	\f]
		 *
		 *	\return	成功した場合 true を、失敗した場合 false を返します。
		 *	「失敗」は、元のベクトルが零ベクトルであるか、
		 *	次元数が 0 の場合に起こります。
		 *
		 *	\sa Norm, Norm2
		 */
		bool Normalize(void);

		//! 初期化関数1
		/*!
		 *	ベクトルの成分を全て 0 にします。
		 *
		 *	\param[in]	degFlg
		 *		true の場合は、次元数を 0 に設定します。
		 *		false の場合は、次元数は変化せず、全ての成分を 0 にします。
		 */
		void Init(bool degFlg);
		
		//! 初期化関数2
		/*!
		 *	ベクトルの成分を全て 0 にします。
		 *	次元数は変化しません。
		 */
		void Init(void);

		//! 零ベクトル判定関数
		/*!
		 *	ベクトルが零ベクトルであるかどうかを判定します。
		 *
		 *	\return
		 *		零ベクトルである場合 true を、そうでない場合 false を返します。
		 *		次元数が 0 である場合は true を返します。
		 */
		bool IsZero(void);

		//! 部分置換関数1
		/*!
		 *	現在の変数が表す n 次元のベクトル
		 *	\f[
		 *		\mathbf{P} = (P_0, \; P_1, \; \ldots, \; P_{n-1})
		 *	\f]
		 *	と、引数として与えられる m 次元ベクトル
		 *	\f[
		 *		\mathbf{Q} = (Q_0, \; Q_1, \; \ldots, \; Q_{m-1})
		 *	\f]
		 *	について、
		 *	\f$ \mathbf{P} \f$ の m 個の成分
		 *	\f[
		 *		P_{s}, \; P_{s+1}, \; \ldots, \; P_{s+m-1}
		 *	\f]
		 *	を \f$ \mathbf{Q} \f$ の各成分に置き換えます。
		 *	条件として、\f$ s \geq 0 \f$ かつ
		 *	\f$ n \geq s + m - 1 \f$ を満たしている必要があります。
		 *
		 *	\param[in]	s	置換する最初の成分 ID
		 *	\param[in]	Q	置換ベクトル
		 *
		 *	\return 置換に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool Replace(int s, fk_GenVector^ Q);

		//! 部分置換関数2
		/*!
		 *	現在の変数が表す n 次元のベクトル
		 *	\f[
		 *		\mathbf{P} = (P_0, \; P_1, \; \ldots, \; P_{n-1})
		 *	\f]
		 *	と、引数として与えられる 3 次元ベクトル
		 *	\f[
		 *		\mathbf{Q} = (Q_x, \; Q_y, \; Q_z)
		 *	\f]
		 *	について、
		 *	\f$ \mathbf{P} \f$ の 3 個の成分
		 *	\f[
		 *		P_s, \; P_{s+1}, \; P_{s+2}
		 *	\f]
		 *	を \f$ Q_x, Q_y, Q_z \f$ の各成分に置き換えます。
		 *	条件として、\f$ s \geq 0 \f$ かつ
		 *	\f$ n \geq s + 2 \f$ を満たしている必要があります。
		 *
		 *	\param[in]	s	置換する最初の成分 ID
		 *	\param[in]	Q	置換ベクトル
		 *
		 *	\return 置換に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool Replace(int s, fk_Vector^ Q);

		//! 部分置換関数3
		/*!
		 *	現在の変数が表す n 次元のベクトル
		 *	\f[
		 *		\mathbf{P} = (P_0, \; P_1, \; \ldots, \; P_{n-1})
		 *	\f]
		 *	と、引数として与えられる 4 次元ベクトル
		 *	\f[
		 *		\mathbf{Q} = (Q_x, \; Q_y, \; Q_z, \; Q_w)
		 *	\f]
		 *	について、
		 *	\f$ \mathbf{P} \f$ の 4 個の成分
		 *	\f[
		 *		P_s, \; P_{s+1}, \; P_{s+2}, \; P_{s+3}
		 *	\f]
		 *	を \f$ Q_x, Q_y, Q_z, Q_w \f$ の各成分に置き換えます。
		 *	条件として、\f$ s \geq 0 \f$ かつ
		 *	\f$ n \geq s + 3 \f$ を満たしている必要があります。
		 *
		 *	\param[in]	s	置換する最初の成分 ID
		 *	\param[in]	Q	置換ベクトル
		 *
		 *	\return 置換に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool Replace(int s, fk_HVector^ Q);

		//! 部分加算関数1
		/*!
		 *	現在の変数が表す n 次元のベクトル
		 *	\f[
		 *		\mathbf{P} = (P_0, \; P_1, \; \ldots, \; P_{n-1})
		 *	\f]
		 *	と、引数として与えられる m 次元ベクトル
		 *	\f[
		 *		\mathbf{Q} = (Q_0, \; Q_1, \; \ldots, \; Q_{m-1})
		 *	\f]
		 *	について、
		 *	\f$ \mathbf{P} \f$ の m 個の成分
		 *	\f[
		 *		P_{s}, \; P_{s+1}, \; \ldots, \; P_{s+m-1}
		 *	\f]
		 *	に対して \f$ \mathbf{Q} \f$ の各成分の値を加算します。
		 *	条件として、\f$ s \geq 0 \f$ かつ
		 *	\f$ n \geq s + m - 1 \f$ を満たしている必要があります。
		 *
		 *	\param[in]	s	加算する最初の成分 ID
		 *	\param[in]	Q	加算ベクトル
		 *
		 *	\return 加算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool Add(int s, fk_GenVector^ Q);

		//! 部分加算関数2
		/*!
		 *	現在の変数が表す n 次元のベクトル
		 *	\f[
		 *		\mathbf{P} = (P_0, \; P_1, \; \ldots, \; P_{n-1})
		 *	\f]
		 *	と、引数として与えられる 3 次元ベクトル
		 *	\f[
		 *		\mathbf{Q} = (Q_x, \; Q_y, \; Q_z)
		 *	\f]
		 *	について、
		 *	\f$ \mathbf{P} \f$ の 3 個の成分
		 *	\f[
		 *		P_s, \; P_{s+1}, \; P_{s+2}
		 *	\f]
		 *	に対して \f$ Q_x, Q_y, Q_z \f$ の各成分の値を加算します。
		 *	条件として、\f$ s \geq 0 \f$ かつ
		 *	\f$ n \geq s + 2 \f$ を満たしている必要があります。
		 *
		 *	\param[in]	s	加算する最初の成分 ID
		 *	\param[in]	Q	加算ベクトル
		 *
		 *	\return 加算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool Add(int s, fk_Vector^ Q);

		//! 部分加算関数3
		/*!
		 *	現在の変数が表す n 次元のベクトル
		 *	\f[
		 *		\mathbf{P} = (P_0, \; P_1, \; \ldots, \; P_{n-1})
		 *	\f]
		 *	と、引数として与えられる 4 次元ベクトル
		 *	\f[
		 *		\mathbf{Q} = (Q_x, \; Q_y, \; Q_z, \; Q_w)
		 *	\f]
		 *	について、
		 *	\f$ \mathbf{P} \f$ の 4 個の成分
		 *	\f[
		 *		P_s, \; P_{s+1}, \; P_{s+2}, \; P_{s+3}
		 *	\f]
		 *	に対して \f$ Q_x, Q_y, Q_z, Q_w \f$ の各成分の値を加算します。
		 *	条件として、\f$ s \geq 0 \f$ かつ
		 *	\f$ n \geq s + 3 \f$ を満たしている必要があります。
		 *
		 *	\param[in]	s	加算する最初の成分 ID
		 *	\param[in]	Q	加算ベクトル
		 *
		 *	\return 加算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool Add(int s, fk_HVector^ Q);

		//! 部分減算関数1
		/*!
		 *	現在の変数が表す n 次元のベクトル
		 *	\f[
		 *		\mathbf{P} = (P_0, \; P_1, \; \ldots, \; P_{n-1})
		 *	\f]
		 *	と、引数として与えられる m 次元ベクトル
		 *	\f[
		 *		\mathbf{Q} = (Q_0, \; Q_1, \; \ldots, \; Q_{m-1})
		 *	\f]
		 *	について、
		 *	\f$ \mathbf{P} \f$ の m 個の成分
		 *	\f[
		 *		P_{s}, \; P_{s+1}, \; \ldots, \; P_{s+m-1}
		 *	\f]
		 *	に対して \f$ \mathbf{Q} \f$ の各成分の値を減算します。
		 *	条件として、\f$ s \geq 0 \f$ かつ
		 *	\f$ n \geq s + m - 1 \f$ を満たしている必要があります。
		 *
		 *	\param[in]	s	減算する最初の成分 ID
		 *	\param[in]	Q	減算ベクトル
		 *
		 *	\return 減算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool Sub(int s, fk_GenVector^ Q);

		//! 部分減算関数2
		/*!
		 *	現在の変数が表す n 次元のベクトル
		 *	\f[
		 *		\mathbf{P} = (P_0, \; P_1, \; \ldots, \; P_{n-1})
		 *	\f]
		 *	と、引数として与えられる 3 次元ベクトル
		 *	\f[
		 *		\mathbf{Q} = (Q_x, \; Q_y, \; Q_z)
		 *	\f]
		 *	について、
		 *	\f$ \mathbf{P} \f$ の 3 個の成分
		 *	\f[
		 *		P_s, \; P_{s+1}, \; P_{s+2}
		 *	\f]
		 *	に対して \f$ Q_x, Q_y, Q_z \f$ の各成分の値を加算します。
		 *	条件として、\f$ s \geq 0 \f$ かつ
		 *	\f$ n \geq s + 2 \f$ を満たしている必要があります。
		 *
		 *	\param[in]	s	減算する最初の成分 ID
		 *	\param[in]	Q	減算ベクトル
		 *	\return 減算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool Sub(int s, fk_Vector^ Q);

		//! 部分減算関数3
		/*!
		 *	現在の変数が表す n 次元のベクトル
		 *	\f[
		 *		\mathbf{P} = (P_0, \; P_1, \; \ldots, \; P_{n-1})
		 *	\f]
		 *	と、引数として与えられる 4 次元ベクトル
		 *	\f[
		 *		\mathbf{Q} = (Q_x, \; Q_y, \; Q_z, \; Q_w)
		 *	\f]
		 *	について、
		 *	\f$ \mathbf{P} \f$ の 4 個の成分
		 *	\f[
		 *		P_s, \; P_{s+1}, \; P_{s+2}, \; P_{s+3}
		 *	\f]
		 *	に対して \f$ Q_x, Q_y, Q_z, Q_w \f$ の各成分の値を加算します。
		 *	条件として、\f$ s \geq 0 \f$ かつ
		 *	\f$ n \geq s + 3 \f$ を満たしている必要があります。
		 *
		 *	\param[in]	s	減算する最初の成分 ID
		 *	\param[in]	Q	減算ベクトル
		 *
		 *	\return 減算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool Sub(int s, fk_HVector^ Q);

		//! 部分抽出関数
		/*!
		 *	ID が s から e までの成分値を持つ部分ベクトルを抽出します。
		 *	条件として、\f$ 0 \leq s < e < n \f$
		 *	である必要があります。n は元ベクトルの次元数です。
		 *
		 *	\param[in]	s	抽出開始成分 ID
		 *	\param[in]	e	抽出終了成分 ID
		 *
		 *	\return
		 *		部分ベクトル。引数が条件を満たさなかった場合は、
		 *		次元数が 0 のベクトルを返します。
		 */
		fk_GenVector^ Div(int s, int e);
	};
}

