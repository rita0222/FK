#ifndef __FK_VECTOR_HEADER__
#define __FK_VECTOR_HEADER__

#include <FK/Base.h>
#include <string>
#include <vector>

#ifdef OPENGL4
#include <FK/OpenGL.H>
#else
using GLfloat = float;
#endif

namespace FK {
	//! 座標軸を表す列挙型
	enum class fk_Axis {
		X,	//!<	x軸
		Y,	//!<	y軸
		Z	//!<	z軸
	};

	class fk_OrthoMatrix;
	class fk_Matrix;
	class fk_FVector;

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
	 *
	 *	\sa fk_Matrix, fk_HVector, fk_FVector, fk_GenVector
	 */

	class fk_Vector {

	public:
		static constexpr double VECTOREPS = 1.0e-12;	//!< ベクトル演算誤差基準値
		static constexpr double MATRIXEPS = 1.0e-12;	//!< 行列演算用誤差1
		static constexpr double MATRIXEPS2 = 1.0e-16;	//!< 行列演算用誤差2

		double	x;	//!<	x成分
		double	y;	//!<	y成分
		double	z;	//!<	z成分

		//! コンストラクタ
		/*!
		 *	\param[in]	x	x成分
		 *	\param[in]	y	y成分
		 *	\param[in]	z	z成分
		 */
		explicit fk_Vector(double x = 0.0, double y = 0.0, double z = 0.0);

		//! コピーコンストラクタ
		fk_Vector(const fk_Vector &);
		fk_Vector(const fk_Vector &&);

		//! コピーコンストラクタ
		fk_Vector(const fk_FVector &);
		fk_Vector(const fk_FVector &&);

		//! デストラクタ
		virtual ~fk_Vector() {}

		//! \name 単項演算子
		///@{

		//! 単項マイナス演算子 
		/*!
		 *	fk_Vector では、以下のように記述することで、v2 に -v1 を代入できます。
		 *
		 *		v2 = -v1;
		 */
		fk_Vector & operator -(void) const;

		///@}

		//! \name 比較演算子
		///@{

		//! 同値比較演算子 
		/*!
		 *	fk_Vector では、以下のように記述することで、
		 *	v1 と v2 が等しいかどうかを判断できます。
		 *
		 *		if(v1 == v2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、ある程度の計算誤差を許容します。
		 */
		bool operator ==(const fk_Vector &) const;

		//! 異値比較演算子 
		/*!
		 *	fk_Vector では、以下のように記述することで、
		 *	v1 と v2 が等しくないかどうかを判断できます。
		 *
		 *		if(v1 != v2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、ある程度の計算誤差を許容します。
		 */
		bool operator !=(const fk_Vector &) const;

		//! 右不等号演算子 
		/*!
		 *	この演算子では、以下のように処理を行います。
		 *	-#	x成分において、左が大きい場合は真、右が大きい場合は偽とする。
		 *		x成分が fk_Vector::VECTOREPS による誤差許容の上で等しい場合、次の処理に移る。
		 *	-#	y成分において、左が大きい場合は真、右が大きい場合は偽とする。
		 *		y成分が fk_Vector::VECTOREPS による誤差許容の上で等しい場合、次の処理に移る。
		 *	-#	z成分において、左が大きい場合は真、右が大きい場合は偽とする。
		 *		z成分が fk_Vector::VECTOREPS による誤差許容の上で等しい場合、偽とする。
		 *	.
		 *	この演算子は数学的な意味はありませんが、整列化の際に有用となります。
		 */
		bool operator >(const fk_Vector &) const;

		//! 左不等号演算子 
		/*!
		 *	この演算子では、以下のように処理を行います。
		 *	-#	x成分において、右が大きい場合は真、左が大きい場合は偽とする。
		 *		x成分が fk_Vector::VECTOREPS による誤差許容の上で等しい場合、次の処理に移る。
		 *	-#	y成分において、右が大きい場合は真、左が大きい場合は偽とする。
		 *		y成分が fk_Vector::VECTOREPS による誤差許容の上で等しい場合、次の処理に移る。
		 *	-#	z成分において、右が大きい場合は真、左が大きい場合は偽とする。
		 *		z成分が fk_Vector::VECTOREPS による誤差許容の上で等しい場合、偽とする。
		 *	.
		 *	この演算子は数学的な意味はありませんが、整列化の際に有用となります。
		 */
		bool operator <(const fk_Vector &) const;

		//! 等価右不等号演算子
		/*!
		 *	右不等号演算子とほぼ同一ですが、全ての成分が等しい場合には真を返します。
		 */
		bool operator >=(const fk_Vector &) const;

		//! 等価左不等号演算子
		/*!
		 *	左不等号演算子とほぼ同一ですが、全ての成分が等しい場合には真を返します。
		 */
		bool operator <=(const fk_Vector &) const;

		///@}

		//! \name 代入演算子 
		///@{

		//! 単純代入演算子
		fk_Vector & operator =(const fk_Vector &);
		fk_Vector & operator =(const fk_Vector &&);

		//! fk_FVector 型からの単純代入演算子
		fk_Vector & operator =(const fk_FVector &);
		fk_Vector & operator =(const fk_FVector &&);

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
		fk_Vector & operator *=(double);

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
		fk_Vector & operator /=(double);

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
		fk_Vector & operator +=(const fk_Vector &);

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
		fk_Vector & operator -=(const fk_Vector &);

		//! 単項外積代入演算子
		/*!
		 *	以下のコードは、V1 と V2 の外積ベクトルを V1 に代入します。
		 *	V1、V2 はいずれも fk_Vector 型の変数です。
		 *
		 *		V1 ^= V2;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		V1 = V1 ^ V2;
		 */
		fk_Vector & operator ^=(const fk_Vector &);

		//! 行列変換代入演算子1
		/*!
		 *	以下のコードは、V を M によって変換した値を代入します。
		 *	V は fk_Vector 型の変数、M は fk_Matrix 型の変数です。
		 *
		 *		V *= M;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		V = M * V;
		 *
		 *	演算の際、fk_Vector は fk_HVector に変換されます。
		 *	変換の際の同次座標は 1 に設定されます。
		 */
		fk_Vector & operator *=(const fk_Matrix &);

		//! 行列変換代入演算子2
		/*!
		 *	以下のコードは、V を M によって変換した値を代入します。
		 *	V は fk_Vector 型の変数、M は fk_OrthoMatrix 型の変数です。
		 *
		 *		V *= M;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		V = M * V;
		 *
		 *	演算の際、fk_Vector は fk_HVector に変換されます。
		 *	変換の際の同次座標は 1 に設定されます。
		 */
		fk_Vector & operator *=(const fk_OrthoMatrix &);
		///@}

		//! \name メンバ関数
		///@{

		//! 成分設定関数1
		/*!
		 *	各成分を設定します。
		 *	\param[in]	x	x成分の値
		 *	\param[in]	y	y成分の値
		 *	\param[in]	z	z成分の値
		 */
		virtual void set(double x, double y, double z = 0.0);

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
		double dist(void) const;

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
		double dist2(void) const;

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
		 *	\sa dist()
		 */
		bool normalize(void);

		//! 初期化関数
		/*!
		 *	零ベクトルに初期化を行います。
		 */
		virtual void init(void);

		//! 零ベクトル判定関数
		/*!
		 *	\return 零ベクトルである場合 true を、そうでない場合 false を返します。
		 */
		bool isZero(void) const;

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
		 *	\sa perp(), dist(), dist2()
		 */
		fk_Vector proj(const fk_Vector &Q) const;
		fk_Vector proj(const fk_Vector &&Q) const;

		//! 射影垂直成分ベクトル算出関数
		/*!
		 *	この関数は、元ベクトルから引数ベクトルに対する射影の垂直成分ベクトルを算出します。
		 *	これは、元ベクトルと proj() で求められる射影ベクトルの差分ベクトルと同義です。
		 *	図による解説は、ユーザーズマニュアルの「ベクトルの射影」項目を参照して下さい。
		 *	\param[in]	Q	射影基準ベクトル
		 *	\return			射影垂直成分ベクトル
		 *	\sa proj()
		 */
		fk_Vector perp(const fk_Vector &Q) const;
		fk_Vector perp(const fk_Vector &&Q) const;

#ifndef FK_DOXYGEN_USER_PROCESS

		virtual std::string	OutStr(void) const;
		virtual void Print(void) const;
		virtual void Print(std::string) const;

#endif

		//! \name 二項演算子
		///@{

		friend double operator *(const fk_Vector &, const fk_Vector &);
		friend fk_Vector operator +(const fk_Vector &, const fk_Vector &);
		friend fk_Vector operator -(const fk_Vector &, const fk_Vector &);
		friend fk_Vector operator *(const fk_Vector &, double);
		friend fk_Vector operator *(double, const fk_Vector &);
		friend fk_Vector operator /(const fk_Vector &, double);
		friend fk_Vector operator ^(const fk_Vector &, const fk_Vector &);

		///@}
	};


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
	double operator *(const fk_Vector &, const fk_Vector &);

	//! ベクトル和二項演算子
	/*!
	 *	ベクトル V1 と V2 の和を得るには、以下のように記述します。
	 *	V1, V2, V3 はいずれも fk_Vector 型の変数です。
	 *
	 *		V3 = V1 + V2;
	 *
	 *	なお、和演算は交換法則が成り立ちます。
	 */
	fk_Vector operator +(const fk_Vector &, const fk_Vector &);

	//! ベクトル差二項演算子
	/*!
	 *	ベクトル V1 と V2 の差を得るには、以下のように記述します。
	 *	V1, V2, V3 はいずれも fk_Vector 型の変数です。
	 *
	 *		V3 = V1 - V2;
	 *
	 *	なお、差演算は交換法則が成り立ちません。
	 */
	fk_Vector operator -(const fk_Vector &, const fk_Vector &);

	//! 実数倍二項演算子1
	/*!
	 *	ベクトル V1 のスカラー倍ベクトルを得るには、以下のように記述します。
	 *	V1, V2 は共に fk_Vector 型の変数で、d は double 型の変数です。
	 *
	 *		V2 = V1 * d;
	 *
	 *	なお、ベクトルと実数の順番は逆でも構いません。
	 */
	fk_Vector operator *(const fk_Vector &, double);

	//! 実数倍二項演算子2
	/*!
	 *	ベクトル V1 のスカラー倍ベクトルを得るには、以下のように記述します。
	 *	V1, V2 は共に fk_Vector 型の変数で、d は double 型の変数です。
	 *
	 *		V2 = d * V1;
	 *
	 *	なお、ベクトルと実数の順番は逆でも構いません。
	 */
	fk_Vector operator *(double, const fk_Vector &);

	//! 実数商二項演算子
	/*!
	 *	ベクトル V1 のスカラー商ベクトルを得るには、以下のように記述します。
	 *	V1, V2 は共に fk_Vector 型の変数で、d は double 型の変数です。
	 *
	 *		V2 = V1/d;
	 */
	fk_Vector operator /(const fk_Vector &, double);

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
	fk_Vector operator ^(const fk_Vector &, const fk_Vector &);

	//! 4次元ベクトルを管理するクラス
	/*!
	 *	このクラスは、4次元ベクトルの様々な機能を提供します。
	 *	成分は double 型によって格納されています。
	 *	fk_HVector は fk_Vector クラスの派生クラスとなっており、
	 *	継承した成分である x, y, z については通常の3次元成分と同様です。
	 *	4つめの成分である w は、多くの場合は同次座標成分を表し、
	 *	4元正方行列との演算のために存在します。
	 *	\sa fk_Vector, fk_Matrix, fk_FVector, fk_GenVector
	 */

	class fk_HVector: public fk_Vector {
	public:
		double	w;	//!<	同次座標成分

		//! コンストラクタ1
		fk_HVector(void);

		//! コンストラクタ2
		/*!
		 *	\param[in]	v	x,y,z成分の入力となる3次元ベクトル
		 *	\param[in]	w	同次座標値
		 */
		fk_HVector(const fk_Vector &v, double w = 1.0);
		fk_HVector(const fk_Vector &&v, double w = 1.0);

		//! コンストラクタ3
		/*!
		 *	\param[in]	x	x成分
		 *	\param[in]	y	y成分
		 *	\param[in]	z	z成分
		 *	\param[in]	w	同次座標値
		 */
		fk_HVector(double x, double y, double z, double w = 1.0);

		//! デストラクタ
		virtual ~fk_HVector() {}

		//! コピーコンストラクタ
		fk_HVector(const fk_HVector &);
		fk_HVector(const fk_HVector &&);

		//! \name 比較演算子
		///@{

		//! 同値比較演算子 
		/*!
		 *	fk_HVector では、以下のように記述することで、
		 *	v1 と v2 が等しいかどうかを判断できます。
		 *
		 *		if(v1 == v2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、ある程度の計算誤差を許容します。
		 *	なお、同次座標成分の比較も含まれます。
		 */
		bool operator ==(const fk_HVector &) const;

		//! 異値比較演算子 
		/*!
		 *	fk_HVector では、以下のように記述することで、
		 *	v1 と v2 が等しくないかどうかを判断できます。
		 *
		 *		if(v1 != v2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、ある程度の計算誤差を許容します。
		 *	なお、同次座標成分の比較も含まれます。
		 */
		bool operator !=(const fk_HVector &) const;
		///@}

		//! \name 代入演算子 
		///@{

		//! 単純代入演算子
		fk_HVector & operator =(const fk_HVector &);
		fk_HVector & operator =(const fk_HVector &&);

		//! 単純代入演算子
		/*!
		 *	この代入演算子において、同次座標成分は 1 に設定されます。
		 */
		fk_HVector & operator =(const fk_Vector &);
		fk_HVector & operator =(const fk_Vector &&);

		//! 行列変換代入演算子1
		/*!
		 *	以下のコードは、V を M によって変換した値を代入します。
		 *	V は fk_HVector 型の変数、M は fk_Matrix 型の変数です。
		 *
		 *		V *= M;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		V = M * V;
		 */
		fk_HVector & operator *=(const fk_Matrix &);

		//! 行列変換代入演算子2
		/*!
		 *	以下のコードは、V を M によって変換した値を代入します。
		 *	V は fk_HVector 型の変数、M は fk_OrthoMatrix 型の変数です。
		 *
		 *		V *= M;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		V = M * V;
		 */
		fk_HVector & operator *=(const fk_OrthoMatrix &);

		///@}

		//! \name メンバ関数
		///@{

		//! fk_Vector による設定関数1
		/*!
		 *	fk_Vector 型の引数によって値を設定します。
		 *	x, y, z 成分については引数の値を代入し、
		 *	w 成分は 1 に設定します。
		 *	既に w 成分に 1 以外の値が入っていた場合でも、1 に設定されます。
		 *	\param[in]	v	3次元ベクトル
		 */
		void set(const fk_Vector &v);
		void set(const fk_Vector &&v);

		//! fk_Vector による設定関数2
		/*!
		 *	fk_Vector 型の引数によって値を設定します。
		 *	x, y, z 成分については引数 v の各成分の値を代入し、
		 *	w 成分は引数の w の値を設定します。
		 *	\param[in]	v	3次元ベクトル
		 *	\param[in]	w	同次座標値
		 */
		void set(const fk_Vector &v, double w);
		void set(const fk_Vector &&v, double w);

		//! 数値による設定関数1
		/*!
		 *	数値引数によって各成分の値を設定します。
		 *	w 成分は 1 に設定します。
		 *	既に w 成分に 1 以外の値が入っていた場合でも、1 に設定されます。
		 *	\param[in]	x	x成分値
		 *	\param[in]	y	y成分値
		 *	\param[in]	z	z成分値
		 */
		void set(double x, double y, double z = 0.0);

		//! 数値による設定関数2
		/*!
		 *	数値引数によって各成分の値を設定します。
		 *	\param[in]	x	x成分値
		 *	\param[in]	y	y成分値
		 *	\param[in]	z	z成分値
		 *	\param[in]	w	同次座標値
		 */
		void set(double x, double y, double z, double w);

		//! 同次座標設定関数
		/*!
		 *	同次座標成分を設定します。
		 *	その他の成分については値を変更しません。
		 *	\param[in]	w	同次座標値
		 */
		void setw(double w);

		//! 3次元ベクトル取得関数
		/*!
		 *	3次元ベクトル部を返します。
		 *	\return 3次元ベクトル
		 */
		fk_Vector getV(void) const;

		//! 同次座標値取得関数
		/*!
		 *	同次座標値を取得します。
		 *	\return 同次座標値
		 */
		double getw(void) const;

		//! 位置ベクトル設定関数
		/*!
		 *	このベクトルを、位置ベクトルとして扱えるようにします。
		 *	この関数は、同次座標に 1 を設定することと同義です。
		 */
		void ispos(void);

		//! 方向ベクトル設定関数
		/*!
		 *	このベクトルを、方向ベクトルとして扱えるようにします。
		 *	この関数は、同次座標に 0 を設定することと同義です。
		 */
		void isvec(void);

		//! 初期化関数
		/*!
		 *	4次元ベクトルを (0, 0, 0, 1) に設定します。
		 */
		void init(void);

#ifndef FK_DOXYGEN_USER_PROCESS

		std::string OutStr(void) const;
		void Print(void) const;
		void Print(std::string) const;

#endif

		//! \name 二項演算子
		///@{

		friend double operator *(const fk_HVector &, const fk_HVector &);
		friend fk_HVector operator *(const fk_Matrix &, const fk_HVector &);
		friend fk_HVector operator *(const fk_OrthoMatrix &, const fk_HVector &);

		///@}
	};


	//! 内積二項演算子
	/*!
	 *	fk_HVector 型のベクトル V1 と V2 について、
	 *	それぞれの3次元ベクトル部の内積値(スカラー積)を得るには、以下のように記述します。
	 *	V1, V2 はともに fk_HVector 型の変数で、d は double 型の変数です。
	 *
	 *		d = V1 * V2;
	 *
	 *	なお、内積は交換法則が成り立ちます。
	 *	同次座標成分については、内積値の算出には利用しません。
	 */
	double operator *(const fk_HVector &, const fk_HVector &);

	//! 行列変換二項演算子1
	/*!
	 *	以下のコードは、fk_HVector 型の変数 V_org を
	 *	fk_Matrix 型の変数 M によって変換した値を、
	 *	fk_HVector 型変数 V_new に代入します。
	 *
	 *		V_new = M * V_org;
	 *
	 *	FK では行列体系として MV 系を採用しており、
	 *	行列のベクトル変換の際には行列が左側、ベクトルが右側である必要があります。
	 */
	fk_HVector operator *(const fk_Matrix &, const fk_HVector &);

	//! 行列変換二項演算子2
	/*!
	 *	以下のコードは、fk_HVector 型の変数 V_org を
	 *	fk_OrthoMatrix 型の変数 M によって変換した値を、
	 *	fk_HVector 型変数 V_new に代入します。
	 *
	 *		V_new = M * V_org;
	 *
	 *	FK では行列体系として MV 系を採用しており、
	 *	行列のベクトル変換の際には行列が左側、ベクトルが右側である必要があります。
	 */
	fk_HVector operator *(const fk_OrthoMatrix &, const fk_HVector &);


	//! 単精度浮動小数点型3次元ベクトルを管理するクラス
	/*!
	 *	このクラスは、3次元ベクトルの各成分を float 型で格納するためのものです。
	 *	このクラス自体は、ベクトルに必要な様々な演算機能を保持していません。
	 *	ベクトル演算を使用するには fk_Vector を利用して下さい。
	 *
	 *	このクラスの存在意義は、記憶量の削減にあります。
	 *	3次元形状を扱う場合、3次元ベクトルの記憶量が膨大になることがあります。
	 *	そのような場合で、精度がそれほど高くなくても差し支えない場合は、
	 *	double を基本とするデータを float を基本とするデータにすることで、
	 *	記憶量を半分に削減することができます。
	 *	fk_FVector は、そのような場合に配列データとして格納しておくことを想定しています。
	 *	\sa fk_Vector, fk_HVector, fk_GenVector
	 */

	class fk_FVector {
	public:
		float x;	//!<	x成分
		float y;	//!<	y成分
		float z;	//!<	z成分

		//! コンストラクタ
		fk_FVector(void);

		//! コピーコンストラクタ1
		fk_FVector(const fk_FVector &);
		fk_FVector(const fk_FVector &&);

		//! コピーコンストラクタ2
		/*!
		 *	fk_Vector 型からの変換のため、
		 *	浮動小数点精度が double 相当から float 相当まで落ちます。
		 */
		fk_FVector(const fk_Vector &);
		fk_FVector(const fk_Vector &&);

		//! 代入演算子
		/*!
		 *	fk_Vector 型からの変換のため、
		 *	浮動小数点精度が double 相当から float 相当まで落ちます。
		 */
		fk_FVector & operator =(const fk_Vector &);
		fk_FVector & operator =(const fk_Vector &&);
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

	class fk_TexCoord {

	public:

		float x;	//!<	x成分
		float y;	//!<	y成分

		//! コンストラクタ
		/*!
		 *	\param[in]	x	x成分
		 *	\param[in]	y	y成分
		 */
		fk_TexCoord(double x = 0.0, double y = 0.0);

		//! コピーコンストラクタ
		fk_TexCoord(const fk_TexCoord &);

		//! 代入演算子
		fk_TexCoord & operator =(const fk_TexCoord &);

		//! 同値比較演算子
		/*!
		 *	fk_TexCoord では、以下のように記述することで、
		 *	c1 と c2 が等しいかどうかを判断できます。
		 *
		 *		if(c1 == c2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、ある程度の計算誤差を許容します。
		 */
		bool operator ==(const fk_TexCoord &) const;

		//! 異値比較演算子
		/*!
		 *	fk_TexCoord では、以下のように記述することで、
		 *	c1 と c2 が等しくないかどうかを判断できます。
		 *
		 *		if(c1 != c2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、ある程度の計算誤差を許容します。
		 */
		bool operator !=(const fk_TexCoord &) const;

		//! 成分設定関数
		/*!
		 *	各成分を設定します。
		 *
		 *	\param[in]	x	x成分の値
		 *	\param[in]	y	y成分の値
		 */
		void set(double x, double y);
	};
}

#endif /* !__FK_VECTOR_HEADER__ */

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
