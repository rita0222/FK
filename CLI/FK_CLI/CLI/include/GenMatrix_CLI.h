// GenMatrix_CLI.h

#pragma once

#include <FK/GenMatrix.h>
#include "GenVector_CLI.h"

namespace FK_CLI {

	//! 任意次元正方行列を管理するクラス
	/*!
	 *	このクラスは、任意次元の正方行列に関する様々な機能を提供します。
	 *	最も重要な機能は、
	 *	fk_GenVector クラスと合わせた行列演算による連立方程式の計算です。
	 *	4元以下の行列演算については、 fk_Matrix を利用した方が高速です。
	 *
	 *	\sa fk_GenVector, fk_Matrix, fk_Vector, fk_HVector
	 */
	public ref class fk_GenMatrix {
	internal:
		::FK::fk_GenMatrix *pGMat;
	public:

		//! コンストラクタ1
		/*!
		 *	空の行列を生成します。
		 */
		fk_GenMatrix();

		//! コンストラクタ2
		/*!
		 *	引数で与えられた次元数の単位正方行列を生成します。
		 *
		 *	\param[in]	deg		次元数
		 */
		fk_GenMatrix(int deg);

		//! デストラクタ
		~fk_GenMatrix();

		//! ファイナライザ
		!fk_GenMatrix();

		//! 成分プロパティ
		/*!
		 *	各成分の設定や参照を行います。
		 *	1番目の引数が行番号、2番目の引数が列番号です。
		 *
		 *		M[1,2] = 5.0;
		 */

 		property double default [int,int] {
			double get(int, int);
			void set(int, int, double);
		}

		//! 次元数プロパティ
		/*!
		 *	次元数の設定や参照を行います。
		 *
		 *		int deg = M.Degree;
		 *		M.Degree = 10;
		 */
		property int Degree {
			void set(int);
			int get();
		}

		//////////////////// 比較演算子		

		//! 同値比較メソッド1
		/*!
		 *	2つの行列が同値かどうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	M	同値かどうかを判定する行列
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		bool Equals(fk_GenMatrix^ M);

		//! 同値比較メソッド2
		/*!
		 *	2つの行列が同値かどうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	O	同値かどうかを判定する行列
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		virtual bool Equals(Object^ O) override;

		//! 文字列出力メソッド
		/*!
		 *	現在のベクトル成分値を文字列として出力します。
		 *
		 *	\return		成分値の文字列
		 */
		String^	ToString() override;

		// fk_GenVector との積演算
		//! ベクトル変換二項演算子
		/*!
		 *	任意次元ベクトル V1 の、行列 M による変換ベクトル V2 を求めるには、
		 *	以下のように記述します。
		 *	V1, V2 は共に fk_GenVector 型の変数で、M は fk_GenMatrix 型の変数です。
		 *
		 *		V2 = M * V1;
		 *
		 *	FK では行列体系として MV 系を採用しており、
		 *	行列のベクトル変換の際には行列が左側、ベクトルが右側である必要があります。
		 *	なお、この演算では M と V1 の次元数が同一である必要があります。
		 *	もし次元数が異なった場合は、次元が 0 のベクトルを返します。
		 */
		static fk_GenVector^ operator*(fk_GenMatrix^ M, fk_GenVector^ V1);

		//! 行列積二項演算子
		/*!
		 *	行列 M1, M2 の行列積 M3 を求めるには、
		 *	以下のように記述します。
		 *	M1, M2, M3 はいずれも fk_GenMatrix 型の変数です。
		 *
		 *		M3 = M1 * M2;
		 *
		 *	\note
		 *	行列積は交換法則が成り立たないため、
		 *	\f$ \mathbf{M}_1\mathbf{M}_2 \f$ と
		 *	\f$ \mathbf{M}_2\mathbf{M}_1 \f$ は一般的に結果が異なります。
		 *	なお、この演算では M1 と M2 の次元数が同一である必要があります。
		 *	もし次元数が異なった場合は、次元が 0 の行列を返します。
		 */
		static fk_GenMatrix^ operator*(fk_GenMatrix^ M1, fk_GenMatrix^ M2);

		// 差演算子
		//! 行列差二項演算子
		/*!
		 *	行列 M1, M2 の行列差 M3 を求めるには、
		 *	以下のように記述します。
		 *	M1, M2, M3 はいずれも fk_GenMatrix 型です。
		 *
		 *		M3 = M1 - M2;
		 *
		 *	\note
		 *	行列差は交換法則は成り立ちません。
		 *	なお、この演算では M1 と M2 の次元数が同一である必要があります。
		 *	もし次元数が異なった場合は、次元が 0 の行列を返します。
		 */
		static fk_GenMatrix^ operator-(fk_GenMatrix^ M1, fk_GenMatrix^ M2);

		//! 行列和二項演算子
		/*!
		 *	行列 M1, M2 の行列和 M3 を求めるには、
		 *	以下のように記述します。
		 *	M1, M2, M3 はいずれも fk_GenMatrix 型です。
		 *
		 *		M3 = M1 + M2;
		 *
		 *	\note
		 *	行列和は交換法則が成り立ちます。
		 *	なお、この演算では M1 と M2 の次元数が同一である必要があります。
		 *	もし次元数が異なった場合は、次元が 0 の行列を返します。
		 */
		static fk_GenMatrix^ operator+(fk_GenMatrix^ M1, fk_GenMatrix^ M2);

		//! 行列和代入演算子
		/*!
		 *	以下のコードは、M1 と M2 の行列和を
		 *	前の M1 の値は破棄して改めて M1 に設定します。
		 *
		 *		M1 += M2;
		 *
		 *	これは、以下のコードと同義です。
		 *
		 *		M1 = M1 + M2;
		 *
		 *	M1 と M2 の次元数が異なる場合は、M1 は変化しません。
		 */
		static void operator +=(fk_GenMatrix^ M1, fk_GenMatrix^ M2);
		
		//! 行列差代入演算子
		/*!
		 *	以下のコードは、M1 と M2 の行列差を
		 *	前の M1 の値は破棄して改めて M1 に設定します。
		 *
		 *		M1 -= M2;
		 *
		 *	これは、以下のコードと同義です。
		 *
		 *		M1 = M1 - M2;
		 *
		 *	M1 と M2 の次元数が異なる場合は、M1 は変化しません。
		 */
		static void operator -=(fk_GenMatrix^ M1, fk_GenMatrix^ M2);

		//! 行列積代入演算子
		/*!
		 *	以下のコードは、M1 と M2 の行列積を
		 *	前の M1 の値は破棄して改めて M1 に設定します。
		 *
		 *		M1 *= M2;
		 *
		 *	これは、以下のコードと同義です。
		 *
		 *		M1 = M1 * M2;
		 *
		 *	\note
		 *	行列積は交換法則が成り立たないため、
		 *	\f$ \mathbf{M}_2\mathbf{M}_1 \f$ を
		 *	\f$ \mathbf{M}_1 \f$ に代入したいときには、この演算子は利用できません。
		 *
		 *	M1 と M2 の次元数が異なる場合は、M1 は変化しません。
		 */
		static void operator *=(fk_GenMatrix^ M1, fk_GenMatrix^ M2);

		//! 行列変換代入演算子
		/*!
		 *	以下のコードは、ベクトル V を 行列 M によって変換した値を代入します。
		 *	V は fk_GenVector 型の変数、M は fk_GenMatrix 型の変数です。
		 *
		 *		V *= M;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		V = M * V;
		 *
		 *	もし V と M の次元数が異なる場合、V の値は変化しません。
		 */
		static void operator *=(fk_GenVector^ V, fk_GenMatrix^ M);

		//! 初期化メソッド1
		/*!
		 *	行列を、引数の値に従って初期化を行います。
		 *	次元数は変化しません。
		 *
		 *	\param[in]	initFlg
		 *		true の場合、単位行列として初期化します。
		 *		false の場合、零行列として初期化します。
		 */
		void Init(bool initFlg);

		//! 初期化メソッド2
		/*!
		 *	行列を単位行列として初期化します。
		 *	次元数は変化しません。
		 */
		void Init(void);

		//! 逆行列化メソッド
		/*!
		 *	現在設定されている行列に対し、正則行列であれば自身を逆行列化します。
		 *	特異(非正則)行列である場合は「失敗」とし、成分値を変更しません。
		 *
		 *	\return
		 *		行列が正則である場合、逆行列化して true を返します。
		 *		特異行列であった場合は、成分値を変更せずに false を返します。
		 *
		 *	\sa GetInverse(), IsRegular(), IsSingular()
		 */
		bool Inverse(void);


		//! 逆行列取得演算子
		/*!
		 *	現在設定されている行列の逆行列を求めます。
		 *	自身の値は変化しません。
		 *
		 *	\return
		 *		逆行列を返します。もし自身が特異行列であった場合は、自身と同値を返します。
		 *
		 *	\sa Inverse(), IsRegular(), IsSingular()
		 */
		fk_GenMatrix^ GetInverse(void);

		//! 転置化メソッド
		/*!
		 *	現在設定されている行列に対し、自身を転置化します。
		 *
		 *	\sa Inverse()
		 */
		void Negate(void);

		//! 正則判定メソッド
		/*!
		 *	行列が正則であるかどうかを判定します。
		 *	正則行列とは、逆行列が存在する行列のことです。
		 *
		 *	\return 正則であれば true を、そうでなければ false を返します。
		 *
		 *	\sa Inverse(), GetInverse(), IsSingular()
		 */
		bool IsRegular(void);

		//! 特異判定メソッド
		/*!
		 *	行列が特異であるかどうかを判定します。
		 *	特異行列とは、逆行列が存在しない行列のことです。
		 *	これは「非正則行列」と同義になります。
		 *
		 *	\return 特異であれば true を、そうでなければ false を返します。
		 *
		 *	\sa Inverse(), GetInverse(), IsRegular()
		 */
		bool IsSingular(void);
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
