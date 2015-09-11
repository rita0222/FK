// Matrix_CLI.h

#pragma once

#include <FK/Matrix.h>
#include "Vector_CLI.h"

namespace FK_CLI {

	//! オイラー角を表すクラス
	/*!
	 *	オイラー角は、3次元での姿勢を表す方法の一つで、
	 *	空間中の全ての姿勢を表現することが可能です。
	 *	FK におけるオイラー角は Z-X-Y 座標系を意味します。
	 *	ヘディング角を h、ピッチ角を p、バンク角を b としたとき、
	 *	このオイラー角は以下の回転変換と同意です。
	 *	\f[
	 *		R_y(-h) \cdot R_x(p) \cdot R_z(-b)
	 *	\f]
	 *	角度の単位はすべて弧度法(ラジアン)です。
	 */

	public ref class fk_Angle {
	internal:
		double h_, p_, b_;

		static operator ::fk_Angle (fk_Angle^);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Angle(::fk_Angle);
#endif

		//! コンストラクタ1
		/*!
		 *	ヘディング角、ピッチ角、バンク角全て 0 のオイラー角を生成します。
		 */
		fk_Angle();

		//! コンストラクタ2
		/*!
		 *	引数としてヘディング角、ピッチ角、バンク角を入力します。
		 *	単位は弧度法(ラジアン)です。
		 *
		 *	\param[in]	h	ヘディング角
		 *	\param[in]	p	ピッチ角
		 *	\param[in]	b	バンク角
		 */
		fk_Angle(double h, double p, double b);

		//! コンストラクタ3
		/*!
		 *	引数として別のオイラー角を入力し、その値をコピーします。
		 *
		 *	\param[in]	angle	オイラー角インスタンス
		 */
		fk_Angle(fk_Angle^ angle);

		//! デストラクタ
		~fk_Angle();

		//! ファイナライザ
		!fk_Angle();

		//! ヘディング角プロパティ
		property double h {
			double get();
			void set(double value);
		}

		//! ピッチ角プロパティ
		property double p {
			double get();
			void set(double value);
		}

		//! バンク角プロパティ
		property double b {
			double get();
			void set(double value);
		}

		//! 設定用関数
		/*!
		 *	\param[in]	h	ヘディング角
		 *	\param[in]	p	ピッチ角
		 *	\param[in]	b	バンク角
		 */
		void Set(double h, double p, double b);
	};

	//! 4元正方行列を管理するクラス
	/*!
	 *	このクラスは、4元正方行列に関する様々な機能を提供します。
	 *	行列同士の演算の他、ベクトルとの積演算(一次変換)も
	 *	fk_Vector や fk_HVector クラスを用いて行えます。
	 *
	 *	FKでは行列は MV 行列系を採用しています。
	 *	従って、行列とベクトルの積演算においては行列が左側、ベクトルは右側となり、
	 *	ベクトルは列ベクトルとして扱われます。
	 *	また、行列積による合成変換を生成した場合、
	 *	変換は右側の行列から行われることになります。
	 *
	 *	行列とベクトルの積に fk_Vector 型を用いた場合、
	 *	同次座標が 1 である fk_HVector 型として扱われます。
	 *
	 *	任意元の正方行列を扱う場合は fk_GenMatrix を利用して下さい。
	 *
	 *	\sa fk_GenMatrix, fk_Vector, fk_HVector
	 */
	public ref class fk_Matrix {
	internal:
		::fk_Matrix *pMatrix;
	public:

		//! コンストラクタ
		/*!
		 *	単位行列を生成します。
		 */
		fk_Matrix();

		//! コピーコンストラクタ
		fk_Matrix(fk_Matrix^);

		//! デストラクタ
		~fk_Matrix();

		//! ファイナライザ
		!fk_Matrix();

		//! 成分プロパティ
		/*!
		 *	各成分の設定や参照を行います。
		 *	1番目の引数が行番号、2番目の引数が列番号です。
		 *
		 *		M[1,2] = 5.0;
		 */
 		property double default[int, int] {
			double get(int, int);
			void set(int, int, double);
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
		bool Equals(fk_Matrix^ M);

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

		//! ベクトル変換二項演算子
		/*!
		 *	4次元ベクトル V1 の、行列 M による変換ベクトル V2 を求めるには、
		 *	以下のように記述します。
		 *	V1, V2 は共に fk_HVector 型の変数で、M は fk_Matrix 型の変数です。
		 *
		 *		V2 = M * V1;
		 *
		 *	FK では行列体系として MV 系を採用しており、
		 *	行列のベクトル変換の際には行列が左側、ベクトルが右側である必要があります。
		 */
		static fk_HVector^ operator*(fk_Matrix^ M, fk_HVector^ V1);

		//! 行列積二項演算子
		/*!
		 *	行列 M1, M2 の行列積 M3 を求めるには、
		 *	以下のように記述します。
		 *	M1, M2, M3 はいずれも fk_Matrix 型の変数です。
		 *
		 *		M3 = M1 * M2;
		 *
		 *	\note
		 *		行列積は交換法則が成り立たないため、
		 *		\f$ \mathbf{M}_1\mathbf{M}_2 \f$ と
		 *		\f$ \mathbf{M}_2\mathbf{M}_1 \f$ は一般的に結果が異なります。
		 */
		static fk_Matrix^ operator*(fk_Matrix^ M1, fk_Matrix^ M2);

		//! 行列実数倍二項演算子1
		/*!
		 *	行列 M1 のスカラー倍行列をエルには、以下のように記述します。
		 *	M1, M2 はいずれも fk_Matrix 型の変数で、d は double 型の変数です。
		 *
		 *		M2 = d * M1;
		 *
		 *	なお、行列と実数の順番は逆でも構いません。
		 */
		static fk_Matrix^ operator*(double d, fk_Matrix^ M1);

		//! 行列実数倍二項演算子2
		/*!
		 *	行列 M1 のスカラー倍行列をエルには、以下のように記述します。
		 *	M1, M2 はいずれも fk_Matrix 型の変数で、d は double 型の変数です。
		 *
		 *		M2 = M1 * d;
		 *
		 *	なお、行列と実数の順番は逆でも構いません。
		 */
		static fk_Matrix^ operator*(fk_Matrix^ M1, double d);

		//! 行列差二項演算子
		/*!
		 *	行列 M1, M2 の行列差 M3 を求めるには、
		 *	以下のように記述します。
		 *	M1, M2, M3 はいずれも fk_Matrix 型です。
		 *
		 *		M3 = M1 - M2;
		 *
		 *	\note
		 *		行列差は交換法則が成り立ちません。
		 */
		static fk_Matrix^ operator-(fk_Matrix^ M1, fk_Matrix^ M2);

		//! 行列和二項演算子
		/*!
		 *	行列 M1, M2 の行列和 M3 を求めるには、
		 *	以下のように記述します。
		 *	M1, M2, M3 はいずれも fk_Matrix 型です。
		 *
		 *		M3 = M1 + M2;
		 *
		 *	\note
		 *		行列和は交換法則が成り立ちます。
		 */
		static fk_Matrix^ operator+(fk_Matrix^ M1, fk_Matrix^ M2);

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
		 */
		static void operator +=(fk_Matrix^ M1, fk_Matrix^ M2);

		//! 行列差代入演算子1
		/*!
		 *	以下のコードは、M1 と M2 の行列差を
		 *	前の M1 の値は破棄して改めて M1 に設定します。
		 *
		 *		M1 -= M2;
		 *
		 *	これは、以下のコードと同義です。
		 *
		 *		M1 = M1 - M2;
		 */
		static void operator -=(fk_Matrix^ M1, fk_Matrix^ M2);

		//! 行列積代入演算子1
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
		 *		行列積は交換法則が成り立たないため、
		 *		\f$ \mathbf{M}_2\mathbf{M}_1 \f$ を
		 *		\f$ \mathbf{M}_1 \f$ に代入したいときには、この演算子は利用できません。
		 */
		static void operator *=(fk_Matrix^ M1, fk_Matrix^ M2);

		//! \name 成分参照・取得系関数
		//@{

		//! 単位行列化関数
		/*!
		 *	行列を単位行列に初期化します。
		 */
		void Init();

		//! 成分設定関数
		/*!
		 *	行番号 row、列番号 col に対応する成分を value に設定します。
		 *	row, col はそれぞれ最初が 0、最後が 3 になります。
		 *
		 *	次のコード
		 *
		 *		M.Set(1, 2, 0.5);
		 *
		 *	は、以下のコードと同義になります。
		 *
		 *		M[1, 2] = 0.5;
		 *
		 *	\param[in]	row		行番号
		 *	\param[in]	col		列番号
		 *	\param[in]	value	設定する成分の値
		 */
		void Set(int row, int col, double value);

		
		//! 行ベクトル成分設定関数1
		/*!
		 *	行列中の、行番号が row である行ベクトルを vec に設定します。
		 *	row は最初が 0、最後が 3 となります。この関数の場合、
		 *	行ベクトルの最後の成分については値は変更しません。
		 *
		 * 	次のコード
		 *
		 *		M.SetRow(row, vec);
		 *
		 *	は、以下のコードと同義になります。
		 *
		 *		M[row, 0] = vec.x;
		 *		M[row, 1] = vec.y;
		 *		M[row, 2] = vec.z;
		 *
		 *	\param[in]	row		行番号
		 *	\param[in]	V		設定ベクトル
		 */
		void SetRow(int row, fk_Vector^ V);

		//! 行ベクトル成分設定関数2
		/*!
		 *	行列中の、行番号が row である行ベクトルを V に設定します。
		 *	row は最初が 0、最後が 3 となります。
		 *
		 * 	次のコード
		 *
		 *		M.setRow(row, vec);
		 *		
		 *	は、以下のコードと同義になります。
		 *
		 *		M[row, 0] = vec.x;
		 *		M[row, 1] = vec.y;
		 *		M[row, 2] = vec.z;
		 *		M[row, 3] = vec.w;
		 *
		 *	\param[in]	row		行番号
		 *	\param[in]	V		設定ベクトル
		 */
		void SetRow(int row, fk_HVector^ V);

		//! 列ベクトル成分設定関数1
		/*!
		 *	行列中の、列番号が col である列ベクトルを vec に設定します。
		 *	col は最初が 0、最後が 3 となります。この関数の場合、
		 *	列ベクトルの最後の成分については値は変更しません。
		 *
		 * 	次のコード
		 *
		 *		M.SetCol(col, vec);
		 *
		 *	は、以下のコードと同義になります。
		 *		
		 *		M[0, col] = vec.x;
		 *		M[1, col] = vec.y;
		 *		M[2, col] = vec.z;
		 *
		 *	\param[in]	col		列番号
		 *	\param[in]	V		設定ベクトル
		 */
		void SetCol(int col, fk_Vector^ V);

		//! 列ベクトル成分設定関数1
		/*!
		 *	行列中の、列番号が col である列ベクトルを vec に設定します。
		 *	col は最初が 0、最後が 3 となります。
		 *
		 * 	次のコード
		 *
		 *		M.SetCol(col, vec);
		 *
		 *	は、以下のコードと同義になります。
		 *		
		 *		M[0, col] = vec.x;
		 *		M[1, col] = vec.y;
		 *		M[2, col] = vec.z;
		 *		M[3, col] = vec.w;
		 *
		 *	\param[in]	col		列番号
		 *	\param[in]	V		設定ベクトル
		 */
		void SetCol(int col, fk_HVector^ V);


		//! 行ベクトル成分取得関数
		/*!
		 *	行列中の、行番号が row である行ベクトルを返します。
		 *	row は最初が 0、最後が 3 となります。
		 *
		 *	\param[in]	row		行番号
		 *
		 *	\return 行ベクトル
		 */
		fk_HVector^ GetRow(int row);

		//! 列ベクトル成分取得関数
		/*!
		 *	行列中の、列番号が col である列ベクトルを返します。
		 *	col は最初が 0、最後が 3 となります。
		 *
		 *	\param[in]	col		列番号
		 *
		 *	\return 列ベクトル
		 */
		fk_HVector^ GetCol(int col);

		//@}

		//! \name 逆行列・転置系関数
		//@{

		//! 逆行列化関数
		/*!
		 *	現在設定されている行列に対し、自身を逆行列化します。
		 *	行列が特異行列(非正則行列)である場合は失敗となり、
		 *	自身の変化を行いません。
		 *
		 *	\return
		 *		成功すれば true を、失敗すれば false を返します。
		 *
		 *	\note
		 *		直交行列の場合、この関数は Negate() でもまったく同様に動作します。
		 *
		 *	\sa GetInverse(), Negate(), IsRegular(), IsSingular()
		 */
		bool Inverse();

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
		fk_Matrix^ GetInverse();

		//! 転置化関数
		/*!
		 *	現在設定されている行列に対し、自身を転置化します。
		 *
		 *	\sa Inverse()
		 */
		void Negate();

		//! 正則判定関数
		/*!
		 *	行列が正則であるかどうかを判定します。
		 *	正則行列とは、逆行列が存在する行列のことです。
		 *
		 *	\return 正則であれば true を、そうでなければ false を返します。
		 *
		 *	\sa Inverse(), GetInverse(), IsSingular()
		 */
		bool IsRegular();

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
		bool IsSingular();

		//@}

		//! \name 変換行列生成系関数
		//@{


		//! 座標軸回転行列生成関数
		/*!
		 *	座標軸回転変換を表す行列を生成します。
		 *
		 *	\param[in]	rad		回転角。単位は弧度法(ラジアン)です。
		 *	\param[in]	axis
		 *		座標軸。 fk_Axis.X, fk_Axis.Y, fk_Axis.Z のいずれかになります。
		 */
		void MakeRot(double rad, fk_Axis axis);

		//! 平行移動行列生成関数1
		/*!
		 *	平行移動変換を表す行列を生成します。
		 *
		 *	\param[in]	V	移動ベクトル
		 */
		void MakeTrans(fk_Vector^ V);

		//! オイラー角回転行列生成関数1
		/*!
		 *	オイラー角による合成回転変換を表す行列を生成します。
		 *	オイラー角については、 fk_Angle を参照して下さい。
		 *
		 *	\param[in]	h	ヘディング角
		 *	\param[in]	p	ピッチ角
		 *	\param[in]	b	バンク角
		 */
		void MakeEuler(double h, double p, double b);

		//! オイラー角回転行列生成関数2
		/*!
		 *	オイラー角による合成回転変換を表す行列を生成します。
		 *	オイラー角については、 fk_Angle を参照して下さい。
		 *
		 *	\param[in]	angle	オイラー角
		 */
		void MakeEuler(fk_Angle^ angle);

		//! 拡大縮小行列生成関数
		/*!
		 *	各座標軸方向への拡大縮小率を個別に設定した行列を生成します。
		 *
		 *	\param[in]	x	x方向の拡大縮小率
		 *	\param[in]	y	y方向の拡大縮小率
		 *	\param[in]	z	z方向の拡大縮小率
		 */
		void MakeScale(double x, double y, double z);

		//! 拡大縮小行列生成関数2
		/*!
		 *	各座標軸方向への拡大縮小率を個別に設定した行列を生成します。
		 *	引数のベクトルの各成分が、軸方向の拡大縮小率と対応します。
		 *
		 *	\param[in]	V	拡大縮小率ベクトル
		 */
		void MakeScale(fk_Vector^ V);
	};
}
