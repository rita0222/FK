﻿#ifndef __FK_QUATERNION_HEADER__
#define __FK_QUATERNION_HEADER__

#include <FK/Vector.h>
#include <FK/Angle.h>
#include <FK/Matrix.h>

namespace FK {
	
	//! 四元数(クォータニオン)を管理するクラス
	/*!
	 *	このクラスは、四元数(クォータニオン)の様々な機能を提供します。
	 *	四元数とは、3種類の虚数単位 \f$ i, j, k \f$ と 4 個の実数
	 *	\f$ s, x, y, z \f$ を用いて
	 *	\f[
	 *		\mathbf{q} = s + xi + yj + zk
	 *	\f]
	 *	という形式で表現される数のことで、「ハミルトン数」とも呼ばれます。
	 *	3Dグラフィックス分野での主な利用用途は、3次元の姿勢補間です。
	 *	四元数の補間については fk_Math を参照して下さい。
	 *
	 *	上記定義式のうち、s を「スカラー部」、(x, y, z) を「ベクトル部」と呼びます。
	 *	fk_Quaternion クラスでは、スカラー部を double 型の「s」というメンバ、
	 *	ベクトル部を fk_Vector 型の「v」というメンバで保持します。
	 *	従って、変数名を q としたときの各成分は
	 *	q.s, q.v.x, q.v.y, q.v.z
	 *	となります。これらは、全て public メンバとなっているため、
	 *	直接代入や参照を行うことが可能です。
	 *
	 *	四元数は、数学的には任意軸回転変換を表現します。
	 *	一つの四元数 \f$ \mathbf{q} \f$ は3次元ベクトル \f$\mathbf{V}\f$ に対し、
	 *	\f[
	 *		\mathbf{V}' = \mathbf{q}\mathbf{V}\mathbf{q}^{-1}
	 *	\f]
	 *	という演算によって回転変換したベクトル \f$\mathbf{V}'\f$ を求めることができます。
	 *	また、四元数の積演算が合成変換を意味します。
	 *
	 *	その他の数学的性質については、各演算子やメンバ関数の項目で解説します。
	 *
	 *	\sa fk_Vector, fk_Angle, fk_Matrix, fk_Math
	 */


	class fk_Quaternion {
	public:
		double		s; //!< スカラー部
		fk_Vector	v; //!< ベクトル部

		//! コンストラクタ1
		/*!
		 *	引数なしの場合、全ての成分が 0 である四元数を生成します。
		 *	特に、スカラー部も 0 であることに注意して下さい。
		 */
		fk_Quaternion(void);

		//! コンストラクタ2
		/*!
		 *	4個の実数を引数とするコンストラクタによって、
		 *	各成分を個別に初期設定できます。
		 *
		 *	四元数の成分は、回転角や回転軸を直接表すものではありません。
		 *	回転角と回転軸を設定したい場合は、 setRotate() を使用して下さい。
		 *
		 *	\param[in]	s	スカラー部設定値
		 *	\param[in]	x	ベクトル部 x 成分設定値
		 *	\param[in]	y	ベクトル部 y 成分設定値
		 *	\param[in]	z	ベクトル部 z 成分設定値
		 *
		 *	\sa set(), setRotate()
		 */
		fk_Quaternion(double s, double x, double y, double z);

		//! コンストラクタ3
		/*!
		 *	1個の実数と1個の fk_Vector 型変数を引数とするコンストラクタによって、
		 *	スカラー部とベクトル部をそれぞれ初期設定できます。
		 *
		 *	四元数の成分は、回転角や回転軸を直接表すものではありません。
		 *	回転角と回転軸を設定したい場合は、 setRotate() を使用して下さい。
		 *
		 *	\param[in]	s	スカラー部設定値
		 *	\param[in]	v	ベクトル部設定値
		 *
		 *	\sa set(), setRotate()
		 */
		fk_Quaternion(const double s, const fk_Vector &v);

		//! コピーコンストラクタ
		fk_Quaternion(const fk_Quaternion &);

		//! \name 単項演算子
		///@{

		//! 単項マイナス演算子
		/*!
		 *	四元数 \f$\mathbf{q} = s + xi + yj + zk\f$ に対し、
		 *	\f[
		 *		-\mathbf{q} = -s-xi-yj-zk
		 *	\f]
		 *	として符号は定義されます。以下のコードは、q2 に -q1 を代入します。
		 *
		 *		q2 = -q1;
		 *
		 *	\note
		 *		回転変換を表す四元数 \f$\mathbf{q}\f$ において、
		 *		\f$-\mathbf{q}\f$ による変換もまったく同じ回転となります。
		 *		逆回転変換を行う四元数を求めたい場合は、共役を利用して下さい。
		 */
		fk_Quaternion & operator -(void) const;

		//! 単項共役演算子
		/*!
		 *	四元数 \f$\mathbf{q} = s + xi + yj + zk\f$ に対し、
		 *	\f[
		 *		\overline{\mathbf{q}} = s-xi-yj-zk
		 *	\f]
		 *	として共役 \f$\overline{\mathbf{q}}\f$は定義されます。
		 *	以下のコードは、q2 に q1 の共役を代入します。
		 *
		 *		q2 = ~q1;
		 *
		 *	正規化された四元数 \f$\mathbf{q}\f$ が回転を現すとき、
		 *	共役四元数 \f$\overline{\mathbf{q}}\f$ は
		 *	\f$\mathbf{q}\f$ の逆回転を表します。
		 *
		 *	\sa conj()
		 */
		fk_Quaternion & operator ~(void) const;

		//! 単項逆元演算子
		/*!
		 *	四元数 \f$\mathbf{q} = s + xi + yj + zk\f$ に対し、
		 *	\f[
		 *		\mathbf{q}^{-1} =
		 *		\frac{\overline{\mathbf{q}}}{|\mathbf{q}|^2}
		 *	\f]
		 *	として逆元 \f$\mathbf{q}^{-1}\f$ は定義されます。
		 *
		 *	四元数が正規である(つまり、ノルムが1である)場合、
		 *	四元数の逆元と共役は等しくなります。
		 *	また、四元数によるベクトル変換を考えたとき、逆元は逆変換を表します。
		 *
		 *	以下のコードは、変数 q1 の逆元を q2 に代入します。
		 *
		 *		q2 = !q1;
		 *
		 *	\sa norm(), inverse()
		 */
		fk_Quaternion & operator !(void) const;

		///@}

		//! \name 比較演算子
		///@{

		//! 同値比較演算子 
		/*!
		 *	fk_Quaternion では、以下のように記述することで、
		 *	q1 と q2 が等しいかどうかを判断できます。
		 *
		 *		if(q1 == q2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、ある程度の計算誤差を許容します。
		 */
		bool operator ==(const fk_Quaternion &) const;

		//! 異値比較演算子 
		/*!
		 *	fk_Quaternion では、以下のように記述することで、
		 *	q1 と q2 が等しくないかどうかを判断できます。
		 *
		 *		if(q1 != q2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、ある程度の計算誤差を許容します。
		 */
		bool operator !=(const fk_Quaternion &) const;

		///@}

		//! \name 代入演算子 
		///@{

		//! 単純代入演算子
		fk_Quaternion & operator =(const fk_Quaternion &);

		//! 積代入演算子
		/*!
		 *	以下のコードは、四元数 q1 および q2 の積を
		 *	前の q1 の値は破棄して改めて q1 に設定します。
		 *
		 *		q1 *= q2;
		 *
		 *	これは、以下のコードと同義です。
		 *
		 *		q1 = q1 * q2;
		 *
		 *	\note
		 *		四元数の積は交換法則が成り立たないため、
		 *		\f$ \mathbf{q}_2\mathbf{q}_1 \f$ を
		 *		\f$ \mathbf{q}_1 \f$ に代入したいときは、この演算子は利用できません。
		 */
		fk_Quaternion & operator *=(const fk_Quaternion &);

		//! スカラー倍代入演算子
		/*!
		 *	以下のコードは、四元数 q の全ての成分を d 倍します。
		 *	q は fk_Quaternion 型の変数、d は double 型の変数です。
		 *
		 *		q *= d;
		 *
		 *	d は変数でなく数値でも構いません。
		 *
		 *		q *= 2.0;
		 */
		fk_Quaternion & operator *=(double);

		//! スカラー商代入演算子
		/*!
		 *	以下のコードは、四元数 q の全ての成分を 1/d 倍します。
		 *	q は fk_Quaternion 型の変数、d は double 型の変数です。
		 *
		 *		q /= d;
		 *
		 *	d は変数でなく数値でも構いません。
		 *
		 *		q /= 2.0;
		 */
		fk_Quaternion & operator /=(double);

		//! 単項和代入演算子
		/*!
		 *	以下のコードは、q1 に q2 分を加算します。
		 *	q1, q2 はいずれも fk_Quaternion 型の変数です。
		 *
		 *		q1 += q2;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		q1 = q1 + q2;
		 */
		fk_Quaternion & operator +=(const fk_Quaternion &);

		//! 単項差代入演算子
		/*!
		 *	以下のコードは、q1 に q2 分を減算します。
		 *	q1, q2 はいずれも fk_Quaternion 型の変数です。
		 *
		 *		q1 -= q2;
		 *
		 *	上記コードは、以下のコードと同義です。
		 *
		 *		q1 = q1 - q2;
		 */
		fk_Quaternion & operator -=(const fk_Quaternion &);

		///@}

		//! \name メンバ関数
		///@{

		//! 初期化関数
		/*!
		 *	スカラー部を 1 に、ベクトル部を零ベクトルとして初期化します。
		 */
		void		init(void);

		//! 成分設定関数1
		/*!
		 *	各成分を個別に設定します。
		 *
		 *	ここで与えられるスカラー部とベクトル部は、
		 *	回転角や回転軸を表すわけではないことに注意して下さい。
		 *	回転変換における回転角と回転軸を設定する場合は、
		 *	setRotate() を用います。
		 *
		 *	\param[in]	s	スカラー部設定値
		 *	\param[in]	x	ベクトル部 x 成分設定値
		 *	\param[in]	y	ベクトル部 y 成分設定値
		 *	\param[in]	z	ベクトル部 z 成分設定値
		 *
		 *	\sa setRotate()
		 */
		void		set(double s, double x, double y, double z);

		//! 成分設定関数2
		/*!
		 *	1個の実数と1個の fk_Vector 型変数から、
		 *	スカラー部とベクトル部をそれぞれ設定します。
		 *
		 *	ここで与えられるスカラー部とベクトル部は、
		 *	回転角や回転軸を表すわけではないことに注意して下さい。
		 *	回転変換における回転角と回転軸を設定する場合は、
		 *	setRotate() を用います。
		 *
		 *	\param[in]	s	スカラー部設定値
		 *	\param[in]	v	ベクトル部設定値
		 *
		 *	\sa setRotate()
		 */
		void		set(double s, const fk_Vector &v);

		//! 回転変換設定関数1
		/*!
		 *	回転角を theta、回転軸を (x, y, z) とする回転変換を表す四元数を設定します。
		 *	回転軸は正規化されている必要はありません。
		 *
		 *	具体的に設定される成分値は、回転角を \f$\theta\f$ とし、
		 *	回転軸を表すベクトルを \f$\mathbf{V}\f$ としたとき、
		 *	スカラー部は \f$\cos\frac{\theta}{2}\f$ が、
		 *	ベクトル部は \f$\frac{\mathbf{V}}{|\mathbf{V}|}\sin\frac{\theta}{2}\f$
		 *	が設定されます。
		 *
		 *	ここで与えられた値と、設定される成分値は異なることに注意してください。
		 *	成分値を直接代入するには set() を用います。
		 *
		 *	\param[in]	theta	回転角
		 *	\param[in]	x		回転軸の x 成分
		 *	\param[in]	y		回転軸の y 成分
		 *	\param[in]	z		回転軸の z 成分
		 *
		 *	\sa set()
		 */
		void		setRotate(double theta, double x, double y, double z);

		//! 回転変換設定関数2
		/*!
		 *	回転角を theta、回転軸を V とする回転変換を表す四元数を設定します。
		 *	回転軸は正規化されている必要はありません。
		 *
		 *	具体的に設定される成分値は、回転角を \f$\theta\f$ とし、
		 *	回転軸を表すベクトルを \f$\mathbf{V}\f$ としたとき、
		 *	スカラー部は \f$\cos\frac{\theta}{2}\f$ が、
		 *	ベクトル部は \f$\frac{\mathbf{V}}{|\mathbf{V}|}\sin\frac{\theta}{2}\f$
		 *	が設定されます。
		 *
		 *	ここで与えられた値と、設定される成分値は異なることに注意してください。
		 *	成分値を直接代入するには set() を用います。
		 *
		 *	\param[in]	theta	回転角
		 *	\param[in]	V		回転軸ベクトル
		 *
		 *	\sa set()
		 */
		void		setRotate(double theta, const fk_Vector &V);

		//! オイラー角変換設定関数1
		/*!
		 *	原点を中心とする物体が、
		 *	オイラー角 (0, 0, 0) から
		 *	(h, p, b) の状態に回転する変換を表す四元数を設定します。
		 *	オイラー角についての解説は、 fk_Angle を参照して下さい。
		 *	\param[in]	h	ヘディング角
		 *	\param[in]	p	ピッチ角
		 *	\param[in]	b	バンク角
		 */
		void		makeEuler(double h, double p, double b);

		//! オイラー角変換設定関数1
		/*!
		 *	原点を中心とする物体が、
		 *	オイラー角 (0, 0, 0) から
		 *	angle が表すオイラー角の状態に回転する変換を表す四元数を設定します。
		 *	オイラー角についての解説は、 fk_Angle を参照して下さい。
		 *
		 *	\param[in]	angle	オイラー角
		 */
		void		makeEuler(const fk_Angle &angle);

		//! オイラー角取得関数
		/*!
		 *	四元数を回転変換として解釈したときに、
		 *	オイラー角 (0, 0, 0) の状態の物体が回転したときの
		 *	姿勢状態を示すオイラー角を返します。
		 *	オイラー角についての解説は、 fk_Angle を参照して下さい。
		 *
		 *	\return	オイラー角
		 */
		fk_Angle &	getEuler(void) const;

		//! ノルム取得関数
		/*!
		 *	四元数 \f$\mathbf{q}\f$ のノルム値 \f$|\mathbf{q}|^2\f$ を返します。
		 *	\f$\mathbf{q} = s + xi + yj + zk\f$ のノルム値は、
		 *	以下のように定義されます。
		 *	\f[
		 *		|\mathbf{q}|^2 = s^2 + x^2 + y^2 + z^2
		 *	\f]
		 *
		 *	\return	ノルム値
		 */
		double		norm(void) const;

		//! 絶対値取得関数
		/*!
		 *	四元数 \f$\mathbf{q}\f$ の絶対値 \f$|\mathbf{q}|\f$ を返します。
		 *	\f$\mathbf{q} = s + xi + yj + zk\f$ の絶対値は、
		 *	以下のように定義されます。
		 *	\f[
		 *		|\mathbf{q}| = \sqrt{s^2 + x^2 + y^2 + z^2}
		 *	\f]
		 *
		 *	\return	絶対値
		 */
		double		abs(void) const;

		//! 正規化関数
		/*!
		 *	四元数を正規化します。正規化とは、元の四元数の成分を絶対値で割ることで、
		 * 	絶対値が 1 である四元数を求めることです。
		 *	全ての成分が 0 である場合のみ、正規化できません。
		 *
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 */
		bool		normalize(void);

		//! 共役化関数
		/*!
		 *	現在設定されている四元数に対し、自身を共役化します。
		 *
		 *	四元数 \f$\mathbf{q} = s + xi + yj + zk\f$ に対し、
		 *	\f[
		 *		\overline{\mathbf{q}} = s-xi-yj-zk
		 *	\f]
		 *	として共役 \f$\overline{\mathbf{q}}\f$は定義されます。
		 *	正規化された四元数 \f$\mathbf{q}\f$ が回転を現すとき、
		 *	共役四元数 \f$\overline{\mathbf{q}}\f$ は
		 *	\f$\mathbf{q}\f$ の逆回転を表します。
		 */
		void		conj(void);				// 共役化

		//! 逆元化関数
		/*!
		 *	現在設定されている四元数に対し、自身を逆元化します。
		 *
		 *	四元数 \f$\mathbf{q} = s + xi + yj + zk\f$ に対し、
		 *	\f[
		 *		\mathbf{q}^{-1} =
		 *		\frac{\overline{\mathbf{q}}}{|\mathbf{q}|^2}
		 *	\f]
		 *	として逆元 \f$\mathbf{q}^{-1}\f$ は定義されます。
		 *
		 *	四元数が正規である(つまり、ノルムが1である)場合、
		 *	四元数の逆元と共役は等しくなります。
		 *	また、四元数によるベクトル変換を考えたとき、逆元は逆変換を表します。
		 *
		 *	\return
		 *		成功すれば true を返し、失敗すれば false を返します。
		 *		失敗は、全ての成分が 0 である場合に起こります。
		 *
		 *	\sa norm(), conj()
		 */
		bool		inverse(void);			// 逆元化

		//! 行列変換関数
		/*!
		 *	四元数を回転変換と考えたときの、同じ回転変換を意味する行列を返します。
		 *
		 *	\return 回転変換行列
		 */
		fk_Matrix &	conv(void) const;

		///@}

		//! \name 二項演算子
		///@{

		friend fk_Quaternion operator *(const fk_Quaternion &, const fk_Quaternion &);
		friend fk_Quaternion operator +(const fk_Quaternion &, const fk_Quaternion &);
		friend fk_Quaternion operator -(const fk_Quaternion &, const fk_Quaternion &);
		friend fk_Quaternion operator *(const fk_Quaternion &, double);
		friend fk_Quaternion operator *(double, const fk_Quaternion &);
		friend fk_Quaternion operator /(const fk_Quaternion &, double);
		friend fk_Vector operator *(const fk_Quaternion &, const fk_Vector &);
		friend double operator ^(const fk_Quaternion &, const fk_Quaternion &);

		///@}
	};

	//! 四元数積二項演算子
	/*!
	 *	2つの四元数 \f$\mathbf{q}_1, \mathbf{q}_2\f$ に対し、
	 *	それぞれのスカラー部とベクトル部を以下のように記述するとします。
	 *	\f[
	 *		\mathbf{q}_1 = s_1 + \mathbf{V}_1, \;
	 *		\mathbf{q}_2 = s_2 + \mathbf{V}_2
	 *	\f]
	 *	このとき、四元数の積は以下のように定義されます。
	 *
	 *	\f[
	 *		\mathbf{q}_1\mathbf{q}_2 =
	 *		\left(s_1s_2 - \mathbf{V}_1\cdot\mathbf{V}_2\right) +
	 *		\left(s_1\mathbf{V}_2+s_2\mathbf{V}_1 +
	 *		\mathbf{V}_1 \times \mathbf{V}_2\right)
	 *	\f]
	 *
	 *	これを得るには、以下のように記述します。
	 *	q1, q2, q はいずれも fk_Quaternion 型の変数です。
	 *
	 *		q = q1 * q2;
	 *
	 *	四元数の積は、四元数を回転変換として考えたとき、合成変換を生成することを意味します。
	 *	なお、四元数の積は交換法則は成り立ちません。
	 */
	fk_Quaternion operator *(const fk_Quaternion &, const fk_Quaternion &);

	//! 四元数和二項演算子
	/*!
	 *	四元数の和は、全ての成分同士を加算することで定義されます。
	 *	四元数 q1 と q2 の和を得るには、以下のように記述します。
	 *	q1, q2, q はいずれも fk_Quaternion 型の変数です。
	 *
	 *		q = q1 + q2;
	 */
	fk_Quaternion operator +(const fk_Quaternion &, const fk_Quaternion &);

	//! 四元数差二項演算子
	/*!
	 *	四元数の差は、全ての成分同士を減算することで定義されます。
	 *	四元数 q1 と q2 の差を得るには、以下のように記述します。
	 *	q1, q2, q はいずれも fk_Quaternion 型の変数です。
	 *
	 *		q = q1 - q2;
	 */
	fk_Quaternion operator -(const fk_Quaternion &, const fk_Quaternion &);

	//! 四元数スカラー倍二項演算子1
	/*!
	 *	四元数のスカラー倍は、全ての成分に与えられた実数を掛けることで定義されます。
	 *	これを得るには、以下のように記述します。
	 *	q1, q2 はいずれも fk_Quaternion 型の変数で、d は double 型の変数です。
	 *
	 *		q2 = q1 * d;
	 *
	 *	なお、四元数と実数の順番は逆でも構いません。
	 */
	fk_Quaternion operator *(const fk_Quaternion &, double);

	//! 四元数スカラー倍二項演算子2
	/*!
	 *	四元数のスカラー倍は、全ての成分に与えられた実数を掛けることで定義されます。
	 *	これを得るには、以下のように記述します。
	 *	q1, q2 はいずれも fk_Quaternion 型の変数で、d は double 型の変数です。
	 *
	 *		q2 = d * q1;
	 *
	 *	なお、四元数と実数の順番は逆でも構いません。
	 */
	fk_Quaternion operator *(double, const fk_Quaternion &);

	//! 四元数スカラー商二項演算子
	/*!
	 *	四元数のスカラー商は、全ての成分を与えられた実数で割ることで定義されます。
	 *	これを得るには、以下のように記述します。
	 *	q1, q2 はいずれも fk_Quaternion 型の変数で、d は double 型の変数です。
	 *
	 *		q2 = q1 / d;
	 */
	fk_Quaternion operator /(const fk_Quaternion &, double);

	//! 四元数ベクトル変換二項演算子
	/*!
	 *	四元数は、数学的には任意軸回転変換を表現します。
	 *	一つの四元数 \f$ \mathbf{q} \f$ は3次元ベクトル \f$\mathbf{V}\f$ に対し、
	 *	\f[
	 *		\mathbf{V}' = \mathbf{q}\mathbf{V}\mathbf{q}^{-1}
	 *	\f]
	 *	という演算によって回転変換したベクトル \f$\mathbf{V}'\f$ を求めることができます。
	 *
	 *	上記の変換ベクトルを得るには、以下のように記述します。
	 *	v1, v2 はともに fk_Vector 型の変数、q は fk_Quaternion 型の変数です。
	 *	v1 が元のベクトル、v2 が変換後のベクトルを意味します。
	 *
	 *		v2 = q * v1;
	 */
	fk_Vector operator *(const fk_Quaternion &, const fk_Vector &);

	//! 四元数内積二項演算子
	/*!
	 *	2つの四元数
	 *	\f$\mathbf{q}_1 = s_1 + x_1i + y_1j + z_1k, \;
	 *	\mathbf{q}_2 = s_2 + x_2i + y_2j + z_2k \f$
	 *	の内積(スカラー積)は、以下のように定義されます。
	 *	\f[
	 *		\mathbf{q}_1\cdot\mathbf{q}_2 =
	 *		s_1s_2 + x_1x_2 + y_1y_2 + z_1z_2
	 *	\f]
	 *
	 *	これを得るには、以下のように記述します。
	 *	q1, q2 は fk_Quaternion 型の変数、d は double 型の変数です。
	 *
	 *		d = q1 ^ q2;
	 *
	 *	なお、四元数の内積は交換法則が成り立ちます。
	 *
	 *	\note
	 *		ここで演算子として採用されている「^」は、
	 *		C++ の仕様上あまり演算子としての優先度が高くありません。
	 *		そのため、括弧を適切に使用しないと本来の意図と異なる結果を生じるおそれがあります。
	 */
	double operator ^(const fk_Quaternion &, const fk_Quaternion &);

#ifndef FK_DOXYGEN_USER_PROCESS
	fk_Quaternion fk_Q_Inter_Linear(const fk_Quaternion &,
									const fk_Quaternion &, double);

	fk_Quaternion fk_Q_Inter_Sphere(const fk_Quaternion &,
									const fk_Quaternion &, double);
#endif

}

#endif // !__FK_QUATERNION_HEADER__

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
