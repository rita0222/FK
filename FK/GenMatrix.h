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
#ifndef __FK_GEN_MATRIX_HEADER__
#define __FK_GEN_MATRIX_HEADER__

#include <FK/GenVector.h>
#include <FK/Matrix.h>

//! 任意次元正方行列を管理するクラス
/*!
 *	このクラスは、任意次元の正方行列に関する様々な機能を提供します。
 *	最も重要な機能は、
 *	fk_GenVector クラスと合わせた行列演算による連立方程式の計算です。
 *	4元以下の行列演算については、 fk_Matrix を利用した方が高速です。
 *
 *	\sa fk_GenVector, fk_Matrix, fk_Vector, fk_HVector
 */

class fk_GenMatrix {

	friend class		fk_GenVector;
	
  private:
	std::vector<double>					m;
	std::vector<double>::size_type		deg;

	void				MultVec(fk_GenVector &, const fk_GenVector &) const;
	void				MakeIdentMatrix(void);
	void				MakeZeroMatrix(void);
	bool				MatrixInverse(void);

 public:
	
	//! コンストラクタ
	/*!
	 *	引数で与えられた次元数の単位正方行列を生成します。
	 *
	 *	\param[in]	deg		次元数
	 */
	fk_GenMatrix(int deg = 0);

	//! コピーコンストラクタ
	fk_GenMatrix(const fk_GenMatrix &);

	//! \name 単項演算子
	//@{

	//! 逆行列取得演算子
	/*!
	 *	以下のコードは、M_org の逆行列を M_new に代入します。
	 *
	 *		M_new = !M_org;
	 *
	 *	このとき、M_org は変化しません。
	 *	もし M_org が特異行列であった場合は、M_new は M_org と同値となります。
	 */
	fk_GenMatrix	operator !(void) const;
	//@}

	//! \name 比較演算子
	//@{

	//! 同値比較演算子
	/*!
	 *	fk_GenMatrix では、以下のように記述することで、
	 *	M1 と M2 が等しいかどうかを判断できます。
	 *
	 *		if(M1 == M2) {
	 *			:
	 *			:
	 *		}
	 *
	 *	ここでの比較は、各成分の比較において
	 *	FK_MATRIX_EPS までの数値誤差を許容しています。
	 *	次元数が異なる場合は、無条件に偽となります。
	 */
	bool	operator ==(const fk_GenMatrix &) const;

	//! 異値比較演算子
	/*!
	 *	fk_GenMatrix では、以下のように記述することで、
	 *	M1 と M2 が等しくないかどうかを判断できます。
	 *
	 *		if(M1 != M2) {
	 *			:
	 *			:
	 *		}
	 *
	 *	ここでの比較は、各成分の比較において
	 *	FK_MATRIX_EPS までの数値誤差を許容しています。
	 *	次元数が異なる場合は、無条件に真となります。
	 */
	bool	operator !=(const fk_GenMatrix &) const;

	//@}

	//! \name 代入演算子
	//@{
	//! 単純代入演算子
	fk_GenMatrix &		operator =(const fk_GenMatrix &);

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
	fk_GenMatrix &		operator +=(const fk_GenMatrix &);

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
	fk_GenMatrix &		operator -=(const fk_GenMatrix &);

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
	 *		行列積は交換法則が成り立たないため、
	 *		\f$ \mathbf{M}_2\mathbf{M}_1 \f$ を
	 *		\f$ \mathbf{M}_1 \f$ に代入したいときには、この演算子は利用できません。
	 *
	 *		M1 と M2 の次元数が異なる場合は、M1 は変化しません。
	 */
	fk_GenMatrix &		operator *=(const fk_GenMatrix &);
	//@}

	//! \name メンバ関数
	//@{
	//! 初期化関数
	/*!
	 *	行列を、引数の値に従って初期化を行います。
	 *	次元数は変化しません。
	 *
	 *	\param[in]	initFlg
	 *		true の場合、単位行列として初期化します。
	 *		false の場合、零行列として初期化します。
	 */
	void			init(bool initFlg = true);

	// 次数設定 (直前の値は保持)
	//! 次元数設定関数
	/*!
	 *	行列の次元数を設定します。
	 *	各成分の値は可能な限り引き継がれます。
	 *
	 *	\param[in]	deg		次元数
	 */
	void			setDeg(int deg);

	//! 次元数取得関数
	/*!
	 *	次元数を取得します。
	 *
	 *	\return	次元数
	 */
	int				getDeg(void) const;

	//! 成分値設定関数
	/*!
	 *	引数に対応する成分の値を設定します。
	 *
	 *	\param[in]	row		行番号。0から始まります。
	 *	\param[in]	col		列番号。0から始まります。
	 *	\param[in]	value	設定値。
	 */
	void			set(int row, int col, double value);

	//! 成分値取得関数
	/*!
	 *	引数に対応する成分を取得します。
	 *
	 *	\param[in]	row		行番号。0から始まります。
	 *	\param[in]	col		列番号。0から始まります。
	 *	\return		成分値
	 */
	double			get(int row, int col) const;

	//! 逆行列化関数
	/*!
	 *	現在設定されている行列に対し、正則行列であれば自身を逆行列化します。
	 *	非正則行列(特異行列)である場合は「失敗」とし、成分値を変更しません。
	 *
	 *	\return
	 *		行列が正則である場合、逆行列化して true を返します。
	 *		非正則行列であった場合は、成分値を変更せずに false を返します。
	 *
	 *	\sa isRegular(), isSingular()
	 */
	bool			inverse(void);

	//! 転置化関数
	/*!
	 *	現在設定されている行列に対し、自身を転置化します。
	 */
	void			negate(void);


	//! 正則判定関数
	/*!
	 *	行列が正則であるかどうかを判定します。
	 *	正則行列とは、逆行列が存在する行列のことです。
	 *
	 *	\return 正則であれば true を、そうでなければ false を返します。
	 *
	 *	\sa inverse(), isSingular()
	 */
	bool			isRegular(void) const;

	//! 非正則(特異)判定関数
	/*!
	 *	行列が非正則(特異)であるかどうかを判定します。
	 *	非正則行列とは、逆行列が存在しない行列のことです。
	 *
	 *	\return 非正則であれば true を、そうでなければ false を返します。
	 *
	 *	\sa inverse(), isRegular()
	 */
	bool			isSingular(void) const;

#ifndef FK_DOXYGEN_USER_PROCESS

	void			Print(std::string = "") const;

#endif

	//! \name 二項演算子 
	//@{
	friend fk_GenVector	operator *(const fk_GenMatrix &, const fk_GenVector &);
	friend fk_GenMatrix	operator +(const fk_GenMatrix &, const fk_GenMatrix &);
	friend fk_GenMatrix	operator -(const fk_GenMatrix &, const fk_GenMatrix &);
	friend fk_GenMatrix	operator *(const fk_GenMatrix &, const fk_GenMatrix &);
	//@}
};	

//////// 二項演算子の外部関数宣言

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
fk_GenVector	operator *(const fk_GenMatrix &, const fk_GenVector &);

//! 行列和二項演算子
/*!
 *	行列 M1, M2 の行列和 M3 を求めるには、
 *	以下のように記述します。
 *	M1, M2, M3 はいずれも fk_GenMatrix 型です。
 *
 *		M3 = M1 + M2;
 *
 *	\note
 *		行列和は交換法則が成り立ちます。
 *		なお、この演算では M1 と M2 の次元数が同一である必要があります。
 *		もし次元数が異なった場合は、次元が 0 の行列を返します。
 */
fk_GenMatrix	operator +(const fk_GenMatrix &, const fk_GenMatrix &);

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
 *		行列差は交換法則は成り立ちません。
 *		なお、この演算では M1 と M2 の次元数が同一である必要があります。
 *		もし次元数が異なった場合は、次元が 0 の行列を返します。
 */
fk_GenMatrix	operator -(const fk_GenMatrix &, const fk_GenMatrix &);

//! 行列積二項演算子
/*!
 *	行列 M1, M2 の行列積 M3 を求めるには、
 *	以下のように記述します。
 *	M1, M2, M3 はいずれも fk_GenMatrix 型の変数です。
 *
 *		M3 = M1 * M2;
 *
 *	\note
 *		行列積は交換法則が成り立たないため、
 *		\f$ \mathbf{M}_1\mathbf{M}_2 \f$ と
 *		\f$ \mathbf{M}_2\mathbf{M}_1 \f$ は一般的に結果が異なります。
 *		なお、この演算では M1 と M2 の次元数が同一である必要があります。
 *		もし次元数が異なった場合は、次元が 0 の行列を返します。
 */
fk_GenMatrix	operator *(const fk_GenMatrix &, const fk_GenMatrix &);


#endif // !__FK_GEN_MATRIX_HEADER__
