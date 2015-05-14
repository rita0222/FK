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
		::fk_GenMatrix *pGMat;
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
 		property double default[int,int] {
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

		//! 同値比較関数1
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

		//! 同値比較関数2
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

		//! 文字列出力関数
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

		//! 初期化関数1
		/*!
		 *	行列を、引数の値に従って初期化を行います。
		 *	次元数は変化しません。
		 *
		 *	\param[in]	initFlg
		 *		true の場合、単位行列として初期化します。
		 *		false の場合、零行列として初期化します。
		 */
		void Init(bool initFlg);

		//! 初期化関数2
		/*!
		 *	行列を単位行列として初期化します。
		 *	次元数は変化しません。
		 */
		void Init(void);

		//! 逆行列化関数
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

		//! 転置化関数
		/*!
		 *	現在設定されている行列に対し、自身を転置化します。
		 *
		 *	\sa Inverse()
		 */
		void Negate(void);

		//! 正則判定関数
		/*!
		 *	行列が正則であるかどうかを判定します。
		 *	正則行列とは、逆行列が存在する行列のことです。
		 *
		 *	\return 正則であれば true を、そうでなければ false を返します。
		 *
		 *	\sa Inverse(), GetInverse(), IsSingular()
		 */
		bool IsRegular(void);

		//! 特異判定関数
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
