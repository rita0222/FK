/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_GEN_VECTOR_HEADER__
#define __FK_GEN_VECTOR_HEADER__

#include <FK/Vector.h>

namespace FK {
	class fk_GenMatrix;

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

	class fk_GenVector {

		friend class		fk_GenMatrix;

	public:

		//! コンストラクタ1
		/*!
		 *	次元数のみを指定するコンストラクタです。
		 *	全ての成分に 0 が設定されます。
		 *	引数を省略した場合、
		 *	次元数が 0 である (つまり成分のない)ベクトルを生成します。
		 *	\param[in]	deg		次元数
		 */
		fk_GenVector(int deg = 0);
	
		//! コンストラクタ2
		/*!
		 *	このコンストラクタでは、
		 *	引数として STL の vector<double> 型配列を入力とします。
		 *	\param[in]	array	成分値配列
		 */
		fk_GenVector(std::vector<double> &array);
	
		//! コンストラクタ3
		/*!
		 *	このコンストラクタでは、
		 *	引数として次元数と double 型配列を入力とします。
		 *	\param[in]	deg		次元数
		 *	\param[in]	array	成分値配列
		 */
		fk_GenVector(int deg, double *array);
	
		//! コピーコンストラクタ
		fk_GenVector(const fk_GenVector &);
	
		//! fk_Vector からのコピーコンストラクタ
		fk_GenVector(const fk_Vector &);
	
		//! fk_HVector からのコピーコンストラクタ
		fk_GenVector(const fk_HVector &);

		//! \name 単項演算子
		///@{

		//! 単項マイナス演算子 
		/*!
		 *	fk_GenVector では、以下のように記述することで、v2 に -v1 を代入できます。
		 *	全ての成分の符号が反転します。
		 *	v2 の次元数は v1 と同じに設定されます。
		 *
		 *		v2 = -v1;
		 */
		fk_GenVector &	operator -(void) const;

		///@}

		//! \name 比較演算子
		///@{

		//! 同値比較演算子 
		/*!
		 *	fk_GenVector では、以下のように記述することで、
		 *	v1 と v2 が等しいかどうかを判断できます。
		 *
		 *		if(v1 == v2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、ある程度の計算誤差を許容します。
		 *	次元数が異なる場合は、成分値にかかわらず偽となります。
		 */
		bool			operator ==(const fk_GenVector &) const;

		//! 異値比較演算子
		/*!
		 *	fk_GenVector では、以下のように記述することで、
		 *	v1 と v2 が等しくないかどうかを判断できます。
		 *
		 *		if(v1 != v2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、ある程度の計算誤差を許容します。
		 *	次元数が異なる場合は、成分値にかかわらず真となります。
		 */
		bool			operator !=(const fk_GenVector &) const;

		///@}

		//! \name 代入演算子 
		///@{

		//! 単純代入演算子
		fk_GenVector &	operator =(const fk_GenVector &);

		//! fk_Vector 型からの単純代入演算子
		fk_GenVector &	operator =(const fk_Vector &);

		//! fk_HVector 型からの単純代入演算子
		fk_GenVector &	operator =(const fk_HVector &);

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
		fk_GenVector &	operator *=(double d);

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
		fk_GenVector &	operator /=(double);

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
		fk_GenVector &	operator +=(const fk_GenVector &);

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
		fk_GenVector &	operator -=(const fk_GenVector &);

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
		fk_GenVector &	operator *=(const fk_GenMatrix &);

		///@}
	
		//! \name メンバ関数
		///@{

		//! 次元数設定関数
		/*!
		 *	次元数を設定します。
		 *	各成分の値は可能な限り引き継がれます。
		 *	\param[in]	deg		次元数
		 */
		void			resize(int deg);

		// 成分値設定関数
		/*!
		 *	成分値を設定します。
		 *	id は最初の成分が 0 になります。
		 *	id が次元数に対して不正であった場合は失敗となります。
		 *	\param[in]	ID		成分のID
		 *	\param[in]	value	設定値
		 *	\return	成功すれば true を、失敗すれば false を返します。
		 */
		bool			set(int ID, double value);

		//! 次元数取得関数
		/*!
		 *	次元数を取得します。
		 *	\return	次元数
		 */
		int				size(void) const;

		//! 成分値取得関数
		/*!
		 *	引数に対応する成分を取得します。
		 *	最初の成分 ID は 0 です。
		 *	\param[in]	ID	成分のID
		 *	\return	対応する成分値。ID が不正であった場合は無条件に 0.0 を返します。
		 */
		double			get(int ID) const;					// 値取得

		//! ノルム取得関数
		/*!
		 *	ベクトルのノルムを取得します。
		 *	ノルムは、次元数 n のベクトル
		 *	\f$ \mathbf{V} = (V_0, \; V_1, \; \ldots, \; V_{n-1}) \f$
		 *	に対し、以下の式で算出します。
		 *	\f[
		 *		|\mathbf{V}| = \sqrt{\sum_{i=0}^{n-1} (V_i)^2}
		 *	\f]
		 *	\return	ノルム
		 *	\sa norm2(), normalize()
		 */
		double			norm(void) const;

		//! ノルム平方値取得関数
		/*!
		 *	ベクトルのノルムの平方値を取得します。
		 *	ノルムは、次元数 n のベクトル
		 *	\f$ \mathbf{V} = (V_0, \; V_1, \; \ldots, \; V_{n-1}) \f$
		 *	に対し、以下の式で算出します。
		 *	\f[
		 *		|\mathbf{V}|^2 = \sum_{i=0}^{n-1} (V_i)^2
		 *	\f]
		 *	\return	ノルム平方値
		 *	\sa norm(), normalize()
		 */
		double			norm2(void) const;

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
		 *	\sa dist()
		 */
		bool			normalize(void);

		//! 初期化関数
		/*!
		 *	ベクトルの初期化を行います。
		 *	\param[in]	degFlg	true の場合は、次元数を 0 に設定します。
		 *	false の場合は、次元数は変化せず、全ての成分を 0 にします。
		 */
		void			init(bool degFlg = false);

		//! 零ベクトル判定関数
		/*!
		 *	ベクトルが零ベクトルであるかどうかを判定します。
		 *	\return 零ベクトルである場合 true を、そうでない場合 false を返します。
		 *	次元数が 0 である場合は true を返します。
		 */
		bool			isZero(void) const;

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
		 *	\return 置換に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool			replace(int s, fk_GenVector &Q);

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
		 *	\return 置換に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool			replace(int s, fk_Vector &Q);

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
		 *	\return 置換に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool			replace(int s, fk_HVector &Q);

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
		 *	\return 加算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool			add(int s, fk_GenVector &Q);

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
		 *	\return 加算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool			add(int s, fk_Vector &Q);

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
		 *	\return 加算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool			add(int s, fk_HVector &Q);

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
		 *	\return 減算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool			sub(int s, fk_GenVector &Q);

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
		bool			sub(int s, fk_Vector &Q);

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
		 *	\return 減算に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool			sub(int s, fk_HVector &Q);

		//! 部分抽出関数
		/*!
		 *	ID が s から e までの成分値を持つ部分ベクトルを抽出します。
		 *	条件として、\f$ 0 \leq s < e < n \f$
		 *	である必要があります。n は元ベクトルの次元数です。
		 *	\param[in]	s	抽出開始成分 ID
		 *	\param[in]	e	抽出終了成分 ID
		 *	\return	部分ベクトル。引数が条件を満たさなかった場合は、
		 *	次元数が 0 のベクトルを返します。
		 */
		fk_GenVector	div(int s, int e);

#ifndef FK_DOXYGEN_USER_PROCESS

		void			Print(void) const;
		void			Print(std::string) const;

#endif

		//! \name 二項演算子
		///@{

		friend double		operator *(const fk_GenVector &, const fk_GenVector &);
		friend fk_GenVector	operator +(const fk_GenVector &, const fk_GenVector &);
		friend fk_GenVector	operator -(const fk_GenVector &, const fk_GenVector &);
		friend fk_GenVector	operator *(const fk_GenVector &, double);
		friend fk_GenVector	operator *(double, const fk_GenVector &);
		friend fk_GenVector	operator /(const fk_GenVector &, double);
		friend fk_GenVector	operator ^(const fk_GenVector &, const fk_GenVector &);

		///@}

	private:

		std::vector<double>		v;
	};

	//////// 二項演算子の外部関数宣言 
	
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
	double			operator *(const fk_GenVector &P, const fk_GenVector &Q);

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
	fk_GenVector	operator +(const fk_GenVector &P, const fk_GenVector &Q);

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
	fk_GenVector	operator -(const fk_GenVector &P, const fk_GenVector &Q);

	//! 実数倍二項演算子1
	/*!
	 *	ベクトル V1 のスカラー倍ベクトルを得るには、以下のように記述します。
	 *	V1, V2 は共に fk_GenVector 型の変数で、d は double 型の変数です。
	 *
	 *		V2 = V1 * d;
	 *
	 *	なお、ベクトルと実数の順番は逆でも構いません。
	 */
	fk_GenVector	operator *(const fk_GenVector &V, double d);

	//! 実数倍二項演算子2
	/*!
	 *	ベクトル V1 のスカラー倍ベクトルを得るには、以下のように記述します。
	 *	V1, V2 は共に fk_GenVector 型の変数で、d は double 型の変数です。
	 *
	 *		V2 = d * V1;
	 *
	 *	なお、ベクトルと実数の順番は逆でも構いません。
	 */
	fk_GenVector	operator *(double d, const fk_GenVector &V);

	//! 実数商二項演算子
	/*!
	 *	ベクトル V1 のスカラー商ベクトルを得るには、以下のように記述します。
	 *	V1, V2 は共に fk_GenVector 型の変数で、d は double 型の変数です。
	 *
	 *		V2 = V1/d;
	 */
	fk_GenVector	operator /(const fk_GenVector &V, double d);


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
	fk_GenVector	operator ^(const fk_GenVector &P, const fk_GenVector &Q);
}

#endif // !__FK_GEN_VECTOR_HEADER__


