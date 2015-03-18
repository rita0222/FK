// Vector_CLI.h

#pragma once

#include <FK/Vector.h>

namespace FK_CLI
{
	using namespace System;

	public enum	class fk_Axis {
		X,
		Y,
		Z
	};
	
	//! 3次元ベクトルを管理するクラス
	/*!
	 *	このクラスは、3次元ベクトルの様々な機能を提供します。
	 *	成分は double 型によって格納されています。
	 *	このクラスでは、内積値や外積ベクトル、ノルム算出などの
	 *	ベクトルに関する基本的な演算が利用できます。
	 *	また、 fk_Matrix との組み合わせによる行列演算も可能です。
	 *
	 *	fk_Vector にはもう一つ、
	 *	多くの3次元ベクトル情報のやりとりに利用されるという重要な側面があります。
	 *	そのため、形状操作やモデル操作など多岐に渡って利用する機会があります。
	 *
	 *	4次元のベクトルを扱う場合は fk_HVector を参照して下さい。
	 *	成分を float 型として格納する場合は fk_FVector を参照して下さい。
	 *	任意次元のベクトルを扱う場合は fk_GenVector を参照して下さい。
	 *	\sa fk_Matrix, fk_HVector, fk_FVector, fk_GenVector
	 */
	public ref class fk_Vector {

#ifndef FK_DOXYGEN_USER_PROCESS		
	internal:
		//::fk_Vector *pVec;
		double	x_, y_, z_;

		static ::fk_Axis GetAxis(fk_Axis);
#endif

	public:

		//! コンストラクタ1
		/*!
		 *	初期値として \f$ (0, 0, 0) \f$ が代入されます。
		 */
		fk_Vector::fk_Vector();

		//! コンストラクタ2
		/*!
		 *	\param[in]	x	x成分
		 *	\param[in]	y	y成分
		 *	\param[in]	z	z成分
		 */
		fk_Vector::fk_Vector(double x, double y, double z);

		//! コンストラクタ3
		/*!
		 *	引数で与えられたベクトルの値をコピーし、新たにインスタンスを生成します。
		 *
		 *	\param[in]	V	別のインスタンス。
		 */
		fk_Vector::fk_Vector(fk_Vector^ V);

#ifndef FK_DOXYGEN_USER_PROCESS		
		fk_Vector::fk_Vector(::fk_Vector *);
		fk_Vector::fk_Vector(::fk_Vector);
		
		// デストラクタ
		fk_Vector::~fk_Vector();
		// ファイナライザ
		fk_Vector::!fk_Vector();
#endif
		
		//! ベクトルのx成分
		/*!
		 *	x成分を表すプロパティです。以下のようなコードで利用できます。
		 *
		 *		V.x = 0.0;
		 */
		property double	x {
			double get();
			void set(double);
		}

		//! ベクトルのy成分
		/*!
		 *	z成分を表すプロパティです。以下のようなコードで利用できます。
		 *
		 *		V.y = 0.0;
		 */
		property double y {
			double get();
			void set(double);
		}

		//! ベクトルのz成分
		/*!
		 *	z成分を表すプロパティです。以下のようなコードで利用できます。
		 *
		 *		V.z = 0.0;
		 */
		property double z {
			double get();
			void set(double);
		}

		//! \name 単項演算子
		//@{

		//! 単項マイナス演算子 
		/*!
		 *	fk_Vector では、以下のように記述することで、v2 に -v1 を代入できます。
		 *
		 *		v2 = -v1;
		 */
		static fk_Vector^ operator-(fk_Vector^);

		//@}

		//! 内積二項演算子
		/*!
		 *	3次元ベクトル \f$ \mathbf{P} \f$ と \f$ \mathbf{Q} \f$
		 *	の内積値(スカラー積)は、以下のように定義されます。
		 *
		 *	\f[
		 *		\mathbf{P}\cdot\mathbf{Q} = P_xQ_x + P_yQ_y + P_zQ_z
		 *	\f]
		 *
		 *	これを得るには、以下のように記述します。
		 *	P, Q はともに fk_Vector 型の変数で、d は double 型の変数です。
		 *
		 *		d = P * Q;
		 *
		 *	なお、内積は交換法則が成り立ちます。
		 */
		static double operator*(fk_Vector^, fk_Vector^);

		//! ベクトル和二項演算子
		/*!
		 *	ベクトル V1 と V2 の和を得るには、以下のように記述します。
		 *	V1, V2, V3 はいずれも fk_Vector 型の変数です。
		 *
		 *		V3 = V1 + V2;
		 *
		 *	なお、和演算は交換法則が成り立ちます。
		 */
		static fk_Vector^ operator+(fk_Vector^, fk_Vector^);

		//! ベクトル差二項演算子
		/*!
		 *	ベクトル V1 と V2 の差を得るには、以下のように記述します。
		 *	V1, V2, V3 はいずれも fk_Vector 型の変数です。
		 *
		 *		V3 = V1 - V2;
		 *
		 *	なお、差演算は交換法則が成り立ちません。
		 */
		static fk_Vector^ operator-(fk_Vector^, fk_Vector^);

		//! 実数倍二項演算子1
		/*!
		 *	ベクトル V1 のスカラー倍ベクトルを得るには、以下のように記述します。
		 *	V1, V2 は共に fk_Vector 型の変数で、d は double 型の変数です。
		 *
		 *		V2 = V1 * d;
		 *
		 *	なお、ベクトルと実数の順番は逆でも構いません。
		 */
		static fk_Vector^ operator*(fk_Vector^, double);

		//! 実数倍二項演算子2
		/*!
		 *	ベクトル V1 のスカラー倍ベクトルを得るには、以下のように記述します。
		 *	V1, V2 は共に fk_Vector 型の変数で、d は double 型の変数です。
		 *
		 *		V2 = d * V1;
		 *
		 *	なお、ベクトルと実数の順番は逆でも構いません。
		 */
		static fk_Vector^ operator*(double, fk_Vector^);

		//! 実数商二項演算子
		/*!
		 *	ベクトル V1 のスカラー商ベクトルを得るには、以下のように記述します。
		 *	V1, V2 は共に fk_Vector 型の変数で、d は double 型の変数です。
		 *
		 *		V2 = V1/d;
		 */
		static fk_Vector^ operator/(fk_Vector^, double);

		//! 外積二項演算子
		/*!
		 *	3次元ベクトル \f$ \mathbf{P} \f$ と \f$ \mathbf{Q} \f$
		 *	の外積ベクトル(ベクトル積)は、以下のように定義されます。
		 *
		 *	\f[
		 *		\mathbf{P} \times \mathbf{Q} =
		 *		(P_yQ_z - P_zQ_y, \; P_zQ_x - P_xQ_z, \; P_xQ_y - P_yQ_x)
		 *	\f]
		 *
		 *	これを得るには、以下のように記述します。
		 *	P,Q,R はいずれも fk_Vector 型の変数です。
		 *
		 *		R = P ^ Q;
		 *
		 *	なお、外積は以下のような法則があります。
		 *	- \f$\mathbf{P}\f$, \f$\mathbf{Q}\f$ が平行でない場合、
		 *		上記の \f$\mathbf{R}\f$ は、
		 *		\f$\mathbf{P}\f$, \f$\mathbf{Q}\f$ の双方と垂直である。
		 *	- \f$\mathbf{P}\f$, \f$\mathbf{Q}\f$ が平行な場合、
		 *		\f$\mathbf{R}\f$ は零ベクトルとなる。
		 *	- \f$ (\mathbf{P} \times \mathbf{Q}) = -(\mathbf{Q} \times \mathbf{P}) \f$
		 *		である。
		 *	\note
		 *	ここで演算子として採用されている「^」は、
		 *	C++ の仕様上あまり演算子としての優先度が高くありません。
		 *	そのため、括弧を適切に使用しないと本来の意図と異なる結果を生じるおそれがあります。
		 */
		static fk_Vector^ operator^(fk_Vector^, fk_Vector^);

		//! \name 代入演算子 
		//@{

		//! 実数積代入演算子
		/*!
		 *	以下のコードは、V を d 倍します。
		 *	V は fk_Vector 型の変数、d は double 型の変数です。
		 *
		 *		V *= d;
		 *
		 *	d は変数でなく数値でも構いません。
		 *
		 *		V *= 2.0;
		 */
		static void operator *= (fk_Vector^, double);

		//! 実数商代入演算子
		/*!
		 *	以下のコードは、V を 1/d 倍します。
		 *	V は fk_Vector 型の変数、d は double 型の変数です。
		 *
		 *		V /= d;
		 *
		 *	d は変数でなく数値でも構いません。
		 *
		 *		V /= 2.0;
		 *
		 *	なお、d が 0 であった場合は V の値を変更しません。
		 */
		static void operator /= (fk_Vector^, double);

		//! 単項和代入演算子
		/*!
		 *	以下のコードは、V1 に V2 を追加します。
		 *	V1、V2 はいずれも fk_Vector 型の変数です。
		 *
		 *		V1 += V2;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		V1 = V1 + V2;
		 */
		static void operator += (fk_Vector^, fk_Vector^);

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
		 */
		static void operator -= (fk_Vector^, fk_Vector^);

		//@}

		//! \name 同値比較関数
		//@{

		//! 同値比較関数1
		/*!
		 *	二つのベクトルの値が同値かどうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	V	同値かどうかを判定するベクトル
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		bool Equals(fk_Vector^ V);

		//! 同値比較関数2
		/*!
		 *	二つのベクトルの値が同値かどうかを判定します。
		 *	単純に == 演算子を用いた場合はインスタンスが同一であるかどうかの判定となるため、
		 *	異なるインスタンスで同値かどうかを判定する場合はこのメソッドを利用して下さい。
		 *
		 *	\param[in]	V	同値かどうかを判定するベクトル
		 *
		 *	\return		同値であれば true を、そうでなければ false を返します。
		 */
		virtual bool Equals(Object^ V) override;

		//@}

		//! \name メンバ関数
		//@{

		//! 文字列出力関数
		/*!
		 *	現在のベクトル成分値を文字列として出力します。
		 *
		 *	\return		成分値の文字列
		 */
		String^	fk_Vector::ToString() override;

		//! 成分設定関数1
		/*!
		 *	各成分を設定します。
		 *	\param[in]	x	x成分の値
		 *	\param[in]	y	y成分の値
		 *	\param[in]	z	z成分の値
		 */
		void Set(double x, double y, double z);

		//! 成分設定関数2
		/*!
		 *	各成分を設定します。z 成分には自動的に 0 が代入されます。
		 *	\param[in]	x	x成分の値
		 *	\param[in]	y	y成分の値
		 */
		void Set(double x, double y);

		//! ベクトル長さ算出関数
		/*!
		 *	ベクトルの長さ(ノルム)を返します。
		 *	ベクトル \f$ \mathbf{V} \f$ の長さは以下の式で算出されます。
		 *	\f[
		 *		|\mathbf{V}| = \sqrt{{V_x}^2 + {V_y}^2 + {V_z}^2}
		 *	\f]
		 *
		 *	\return	ベクトルの長さ
		 */
		double Dist();

		//! ベクトル長さ平方算出関数
		/*!
		 *	ベクトルの長さ(ノルム)の2乗の値を返します。
		 *	\f$ \mathbf{V} \f$ の長さの2乗は以下の式で算出されます。
		 *	\f[
		 *		|\mathbf{V}|^2 = {V_x}^2 + {V_y}^2 + {V_z}^2
		 *	\f]
		 *
		 *	平方根演算がない分、 dist() と比べて若干高速です。
		 *	\return ベクトルの長さの平方
		 */
		double Dist2();

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
		 *	「失敗」は、元のベクトルが零ベクトルである場合に限ります。
		 *
		 *	\sa Dist()
		 */
		bool Normalize();

		//! 零ベクトル判定関数
		/*!
		 *	\return 零ベクトルである場合 true を、そうでない場合 false を返します。
		 */
		bool IsZero();

		//! 射影ベクトル算出関数
		/*!
		 *	この関数は、元ベクトルから引数ベクトルに対する射影ベクトルを算出します。
		 *	元ベクトルを \f$ \mathbf{P} \f$, 引数ベクトルを \f$ \mathbf{Q} \f$,
		 *	射影ベクトルを \f$ \mathbf{P}' \f$ とすると、
		 *	以下の式で算出されます。
		 *	\f[
		 *		\mathbf{P}' = \frac{\mathbf{P}\cdot\mathbf{Q}}
		 *		{|\mathbf{Q}|^2} \mathbf{Q}
		 *	\f]
		 *
		 *	図による解説は、ユーザーズマニュアルの「ベクトルの射影」項目を参照して下さい。
		 *	\param[in]	Q	射影基準ベクトル
		 *	\return			射影ベクトル
		 *	\sa Perp(), Dist(), Dist2()
		 */
		fk_Vector^ Proj(fk_Vector^ Q);


		//! 射影垂直成分ベクトル算出関数
		/*!
		 *	この関数は、元ベクトルから引数ベクトルに対する射影の垂直成分ベクトルを算出します。
		 *	これは、元ベクトルと proj() で求められる射影ベクトルの差分ベクトルと同義です。
		 *	図による解説は、ユーザーズマニュアルの「ベクトルの射影」項目を参照して下さい。
		 *
		 *	\param[in]	Q	射影基準ベクトル
		 *	\return			射影垂直成分ベクトル
		 *
		 *	\sa Proj()
		 */
		fk_Vector^ Perp(fk_Vector^ Q);

		//@}
	};

	public ref class fk_HVector {
	internal:
		::fk_HVector *pHVec;

	public:
		// コンストラクタ
		fk_HVector();
		fk_HVector(fk_Vector^);
		fk_HVector(fk_Vector^, double);
		fk_HVector(fk_HVector^);

		// デストラクタ
		~fk_HVector();

		// ファイナライザ
		!fk_HVector();

		// プロパティ一覧
		property double x {
			double get();
			void set(double);
		}

		property double y {
			double get();
			void set(double);
		}

		property double z {
			double get();
			void set(double);
		}

		property double w {
			double get();
			void set(double);
		}

		static double operator* (fk_HVector^, fk_HVector^);

		// fk_Vectorとの変換
		static operator fk_HVector^ (fk_Vector^);
		static operator fk_Vector^ (fk_HVector^);

		//////////////////// 比較演算子		
		bool Equals(fk_HVector^);
		virtual bool Equals(Object^) override;
		String^ ToString() override;

		void Set(fk_Vector^, double);
		void Set(double, double, double, double);
		void Set(double, double, double);
		void Set(double, double);
		void Set(fk_Vector^);
		fk_Vector^ GetV(void);
		void IsPos(void);
		void IsVec(void);
		void Init(void);
	};

	public ref class fk_FVector {
	internal:
		::fk_FVector *pFVec;
	public:
		fk_FVector();
		fk_FVector(fk_FVector^);
		~fk_FVector();
		!fk_FVector();

		static operator fk_Vector^(fk_FVector^);
		static operator fk_FVector ^ (fk_Vector^);
		String^ ToString() override;

  		property float x {
			float get();
			void set(float);
		}

		property float y {
			float get();
			void set(float);
		}

		property float z {
			float get();
			void set(float);
		}
	};
}
