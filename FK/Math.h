/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_MATH_HEADER__
#define __FK_MATH_HEADER__

#include <FK/Quaternion.h>

//! 数学処理関数集合クラス
/*!
 *	このクラスは、様々な数学的処理関数を static 関数群としてまとめたものです。
 *
 *	全ての関数は static 宣言されているため、
 *	本クラスの関数を用いる際に fk_Math 型のインスタンスを生成する必要はありません。
 *	例えば、以下のようにしてコードを記述します。
 *
 *		fk_Vector	vec1, vec2;
 *		double		theta;
 *		
 *		theta = fk_Math::calcCosine(vec1, vec2);
 */

class fk_Math {
 public:

	//! \name 基本数値演算関数
	//@{

	//! 数値範囲制限関数
	/*!
	 *	数値を、指定した範囲内に収まるように補正します。
	 *
	 *	\param[in]	a		対象とする値。
	 *	\param[in]	min		収めたい範囲の最小値。
	 *	\param[in]	max		収めたい範囲の最大値。
	 *
	 *	\return
	 *		\f$ min \leq a \leq max\f$ である場合は a そのままの値を、
	 *		\f$a < min\f$ である場合は min を、
	 *		\f$a > max\f$ である場合は max を返します。
	 */
	static double clamp(double a, double min, double max);
	//@}

	//! \name 幾何的演算関数
	//@{
	//! 直線上判定関数
	/*!
	 *	頂点 \f$\mathbf{P}\f$ が、
	 *	\f$\mathbf{A}, \mathbf{B}\f$ を通る直線上にあるかどうかを判定します。
	 *	厳密には、直線と \f$\mathbf{P}\f$ の距離が FK_EPS 内である場合は、
	 *	直線上にあると解釈します。
	 *
	 *	\param[in]	A		直線上の一点。B とは異なる位置でなければなりません。
	 *	\param[in]	B		直線上の一点。A とは異なる位置でなければなりません。
	 *	\param[in]	P		判定対象位置ベクトル
	 *
	 *	\return
	 *		直線上にあると判定されれば true を、
	 *		ないと判定されれば false を返します。
	 *		A と B が非常に近い(あるいは同じ位置にある)場合、
	 *		判定結果が異常となる場合があります。
	 *
	 *	\sa isOnLineSegment()
	 */
	static bool isOnLine(const fk_Vector &A,
						 const fk_Vector &B,
						 const fk_Vector &P);

	//! 線分上判定関数
	/*!
	 *	頂点 \f$\mathbf{P}\f$ が、
	 *	\f$\mathbf{A}, \mathbf{B}\f$ を端点とする線分上にあるかどうかを判定します。
	 *	厳密には、線分と \f$\mathbf{P}\f$ の距離が FK_EPS 内である場合は、
	 *	線分上にあると解釈します。
	 *
	 *	\param[in]	A		線分の始点。B とは異なる位置でなければなりません。
	 *	\param[in]	B		線分の終点。A とは異なる位置でなければなりません。
	 *	\param[in]	P		判定対象位置ベクトル
	 *	\param[in]	openFlg
	 *		true の場合は、線分を閉区間として解釈します。
	 *		つまり、両端点そのものも線分の一部とみまします。
	 *		false の場合は線分を開区間として解釈します。
	 *		この場合は、両端点は線分には含まれないので、
	 *		もし P が A や B と一致していた場合は false を返すことになります。
	 *
	 *	\return
	 *		線分上にあると判定されれば true を、
	 *		ないと判定されれば false を返します。
	 *		A と B が非常に近い(あるいは同じ位置にある)場合、
	 *		判定結果が異常となる場合があります。
	 *
	 *	\sa isOnLine()
	 */
	static bool isOnLineSegment(const fk_Vector &A,
								const fk_Vector &B,
								const fk_Vector &P,
								bool openFlg = true);

	//! 直線交差判定関数
	/*!
	 * 	点A,B を通る直線と、点C,D を通る直線が、空間上で交差するかどうかを判定します。
	 *	厳密には、両直線の距離が FK_EPS 内である場合は、交差すると解釈します。
	 *
	 *	もし直線 AB と直線 CD が平行であった場合、
	 *	両直線が一致していれば true を、一致していない場合は false を返します。
	 *
	 *	\param[in]	A	1本目の直線上の一点。B とは異なる位置でなければなりません。
	 *	\param[in]	B	1本目の直線上の一点。A とは異なる位置でなければなりません。
	 *	\param[in]	C	2本目の直線上の一点。D とは異なる位置でなければなりません。
	 *	\param[in]	D	2本目の直線上の一点。C とは異なる位置でなければなりません。
	 *
	 *	\return
	 *		交差している場合 true を、していない場合 false を返します。
	 *
	 *	\sa isCrossLineSegment()
	 */
	static bool isCrossLine(const fk_Vector &A, const fk_Vector &B,
							const fk_Vector &C, const fk_Vector &D);

	//! 線分交差判定関数
	/*!
	 *	点A,Bを端点とする線分と、点C,Dを端点とする線分が、
	 *	空間上で交差するかどうかを判定します。
	 *	厳密には、両線分の距離が FK_EPS 内である場合は、交差すると解釈します。
	 *
	 *	もし線分 AB と線分 CD が平行であった場合、
	 *	共有部分が存在すれば true を、なければ false を返します。
	 *
	 *	\param[in]	A	1本目の線分の始点。B とは異なる位置でなければなりません。
	 *	\param[in]	B	1本目の線分の終点。A とは異なる位置でなければなりません。
	 *	\param[in]	C	2本目の線分の始点。D とは異なる位置でなければなりません。
	 *	\param[in]	D	2本目の線分の終点。C とは異なる位置でなければなりません。
	 *
	 *	\param[in]	openFlg
	 *		true の場合は、線分を閉区間として解釈します。
	 *		つまり、両端点そのものも線分の一部とみまします。
	 *		false の場合は線分を開区間として解釈します。
	 *		この場合は、両端点は線分には含まれないので、
	 *		端点と線分が交差しているような場合は false を返すことになります。
	 *
	 *	\return
	 *		線分が交差すると判定されれば true を、
	 *		しないと判定されれば false を返します。
	 *		両線分の端点が非常に近い(あるいは同じ位置にある)場合、
	 *		判定結果が異常となる場合があります。
	 *
	 *	\sa isCrossLine()
	 */
	static bool isCrossLineSegment(const fk_Vector &A, const fk_Vector &B,
								   const fk_Vector &C, const fk_Vector &D,
								   bool openFlg = true);

	//! 線分対線分・最近接点算出関数
	/*!
	 *	点A,Bを端点とする線分と、点C,Dを端点とする線分における最近接点を算出します。
	 *	線分の交差のみを判定するのであればisCrossLineSegment()で十分ですが、
	 *	この関数は線分間の距離と、それぞれの線分における最近接点を指すパラメータを
	 *	同時に算出することができます。
	 *
	 *	\param[in]	A	1本目の線分の始点。B とは異なる位置でなければなりません。
	 *	\param[in]	B	1本目の線分の終点。A とは異なる位置でなければなりません。
	 *	\param[in]	C	2本目の線分の始点。D とは異なる位置でなければなりません。
	 *	\param[in]	D	2本目の線分の終点。C とは異なる位置でなければなりません。
	 *	\param[out]	s	1本目の線分上の最近接点を示すパラメータが代入されます。
	 *	\param[out]	t	2本目の線分上の最近接点を示すパラメータが代入されます。
	 *	\param[out]	P	1本目の線分上の最近接点座標が代入されます。
	 *	\param[out]	Q	2本目の線分上の最近接点座標が代入されます。
	 *
	 *	\return
	 *		線分間の距離を返します。線分が交差してる場合はこの値は 0 になります。
	 *
	 *	\sa isCrossLine(), isCrossLineSegment()
	 */
	static double calcClosestPtSegToSeg(const fk_Vector &A, const fk_Vector &B,
										const fk_Vector &C, const fk_Vector &D,
										double *s, double *t, fk_Vector *P, fk_Vector *Q);


	//! 点対線分・最近接点算出関数
	/*!
	 *	点Cに対する、点A,Bを端点とする線分上の最近接点を算出します。
	 *	最近接点を指すパラメータと座標値を同時に返します。
	 *
	 *	\param[in]	C	点の座標。
	 *	\param[in]	A	線分の始点。B とは異なる位置でなければなりません。
	 *	\param[in]	B	線分の終点。A とは異なる位置でなければなりません。
	 *	\param[out]	t	線分上の最近接点を示すパラメータが代入されます。
	 *	\param[out]	P	線分上の最近接点座標が代入されます。
	 */
	static void calcClosestPtPtToSeg(const fk_Vector &C, const fk_Vector &A, const fk_Vector &B,
									 double *t, fk_Vector *P);


	//! 三角形対線分交差判定関数
	/*!
	 *	線分 PQ と、三角形 ABC が交差しているかどうかを判定します。
	 *	この関数では、三角形の境界と線分が接している場合や、
	 *	線分の端点が三角形面上にあるような場合でも、交差していると判断します。
	 *	以下の条件を満たす場合は、常に false を返します。
	 *		- 線分 PQ の両端点が同じ場所にある場合。
	 *		- 三角形 ABC の 3 点のうち、少なくとも 2 点が同じ場所にある場合。
	 *		- 三角形 ABC の 3 点が同一直線上にある場合。
	 *		- 線分 PQ と 三角形 ABC が平行だった場合。
	 *	.
	 *	\param[in]	P		有向線分の始点。
	 *	\param[in]	Q		有向線分の終点。
	 *	\param[in]	A		三角形の頂点。
	 *	\param[in]	B		三角形の頂点。
	 *	\param[in]	C		三角形の頂点。
	 *	\param[out]	R
	 *		交差の有無にかかわらず、
	 *		PQを通る直線とABCを通る平面の交点のパラメータが代入されます。
	 *		以下の式は、ABC平面上の点 T をパラメータ表現したものです。
	 *		\f[
	 *			\mathbf{T} = \mathbf{A} + u (\mathbf{B} - \mathbf{A})
	 *			+ v (\mathbf{C} - \mathbf{A})
	 *		\f]
	 *		また、以下の式は直線 PQ 上の点 L をパラメータ表現したものです。
	 *		\f[
	 *			\mathbf{L} = (1 - t)\mathbf{P} + t\mathbf{Q}
	 *		\f]
	 *		これらの式のうち、平面パラメータ\f$ u, v \f$ が
	 *		R の x 成分と y 成分、
	 *		直線パラメータ \f$ t \f$ が R の z 成分に代入されます。
	 *		なお、パラメータ出力を必要としない場合は、
	 *		本引数を省略するか NULL を代入しても構いません。
	 *
	 *	\return		交差していれば true を、していなければ false を返します。
	 */
	static bool calcCrossLineAndTri(const fk_Vector &P,
									const fk_Vector &Q,
									const fk_Vector &A,
									const fk_Vector &B,
									const fk_Vector &C,
									fk_Vector *R = NULL);

	//! 余弦値算出関数
	/*!
	 *	方向ベクトル \f$ \mathbf{A}, \mathbf{B} \f$
	 *	のなす角を \f$ \theta \f$ としたとき、
	 *	\f$ \cos\theta \f$ を返します。
	 *	\f$ \mathbf{A}, \mathbf{B} \f$ は正規化してある必要はありません。
	 *	なお、\f$ \mathbf{A}, \mathbf{B} \f$ のいずれかが
	 *	零ベクトルである場合は 0 を返します。
	 *
	 *	\param[in]	A	方向ベクトル
	 *	\param[in]	B	方向ベクトル
	 *	\return			余弦値。
	 */
	static double calcCosine(fk_Vector A, fk_Vector B);

	//! ベクトル分離係数算出関数
	/*!
	 *	任意のベクトル \f$\mathbf{V}\f$ と、
	 *	それぞれが一次独立であるベクトル
	 *	\f$\mathbf{A}, \mathbf{B}, \mathbf{C}\f$ について、
	 *	\f[
	 *		\mathbf{V} =
	 *			\alpha\mathbf{A} +
	 *			\beta\mathbf{B} +
	 *			\gamma\mathbf{C}
	 *	\f]
	 *	を満たすような実数列 \f$(\alpha, \beta, \gamma)\f$ を求めます。
	 *	\f$\mathbf{A}, \mathbf{B}, \mathbf{C}\f$ が一次独立でなかった場合、
	 *	\f$(\alpha, \beta, \gamma)\f$ はすべて 0 として出力します。
	 *
	 *	\param[in]	V		分離対象ベクトル
	 *	\param[in]	A		分離要素ベクトル
	 *	\param[in]	B		分離要素ベクトル
	 *	\param[in]	C		分離要素ベクトル
	 *
	 *	\return
	 *		\f$(\alpha, \beta, \gamma)\f$ をそれぞれ
	 *		x 成分、y 成分、z 成分とする fk_Vector 型の変数を返します。
	 */

	static fk_Vector divideVec(const fk_Vector &V,
							   const fk_Vector &A,
							   const fk_Vector &B,
							   const fk_Vector &C);

	//@}

	//! \name 四元数補間関数
	//@{

	//! 四元数単純線形補間関数
	/*!
	 *	2つの四元数 \f$ \mathbf{q}_1, \mathbf{q}_2 \f$ に対し、
	 *	パラメータ \f$ t \f$ で単純線形補間した四元数を返します。
	 *	補間式は以下のとおりです。
	 *	\f[
	 *		\mathbf{q}(t) =
	 *		\frac{(1-t)\mathbf{q}_1 + t\mathbf{q}_2}
	 *		{|(1-t)\mathbf{q}_1 + t\mathbf{q}_2|}
	 *	\f]
	 *
	 *	単純線形補間は、
	 *	quatInterSphere() による球面線形補間と比べて高速です。
	 *	しかし、回転速度が一定でない、
	 *	正反対に近い姿勢の補間で誤差が生じやすいといった問題が生じることがあります。
	 *	速度面がそれほど切実でないのであれば、
	 *	quatInterSphere() による球面線形補間を推奨します。
	 *
	 *	\param[in]	q1		補間の始点となる四元数
	 *	\param[in]	q2		補間の終点となる四元数
	 *	\param[in]	t
	 *		補間パラメータ。0 で始点、1 で終点となります。
	 *		通常の補間域は \f$ 0 \leq t \leq 1 \f$ となりますが、
	 *		範囲外も算出は可能です。
	 *
	 *	\return
	 *		補間四元数。常に正規化されています。
	 *
	 *	\sa fk_Quaternion, quatInterSphere()
	 */
	static fk_Quaternion quatInterLinear(const fk_Quaternion &q1,
										 const fk_Quaternion &q2,
										 double t);

	//! 四元数球面線形補間関数
	/*!
	 *	2つの四元数 \f$ \mathbf{q}_1, \mathbf{q}_2 \f$ に対し、
	 *	パラメータ \f$ t \f$ で球面線形補間した四元数を返します。
	 *	補間式は以下のとおりです。
	 *	\f[
	 *		\mathbf{q}(t) =
	 *			\frac{\sin((1-t)\theta)}{\sin\theta}\mathbf{q}_1 +
	 *			\frac{\sin(t\theta)}{\sin\theta}\mathbf{q}_2
	 *			\qquad (\theta = \cos^{-1}(\mathbf{q}_1\cdot\mathbf{q}_2))
	 *	\f]
	 *
	 *	球面線形補間は、
	 *	quatInterLinear() による単純線形補間と比べて計算速度はやや劣りますが、
	 *	回転速度が一定であることや、
	 *	正反対に近い姿勢の補間で誤差が生じにくいといった長所があります。
	 *	速度面がそれほど切実でないのであれば、
	 *	quatInterLinear() による単純線形補間よりも
	 *	本関数による球面線形補間を推奨します。
	 *
	 *	\param[in]	q1		補間の始点となる四元数
	 *	\param[in]	q2		補間の終点となる四元数
	 *	\param[in]	t
	 *		補間パラメータ。0 で始点、1 で終点となります。
	 *		通常の補間域は \f$ 0 \leq t \leq 1 \f$ となりますが、
	 *		範囲外も算出は可能です。
	 *
	 *	\return
	 *		補間四元数。常に正規化されています。
	 *
	 *	\sa fk_Quaternion, quatInterLinear()
	 */

	static fk_Quaternion quatInterSphere(const fk_Quaternion &q1,
										 const fk_Quaternion &q2,
										 double t);

	//@}
};


#endif // !__FK_MATH_HEADER__
