#ifndef __FK_MATRIX_HEADER__
#define __FK_MATRIX_HEADER__

#include <FK/Vector.h>
#include <FK/Angle.h>

namespace FK {

	const double FK_MATRIX_EPS = 1.0e-12;	//!< 行列演算用誤差1
	const double FK_MATRIX_EPS2 = 1.0e-16;	//!< 行列演算用誤差2

	//! 4元正方直交行列を管理するクラス
	/*!
	 *	このクラスは、4元正方直交行列に関する様々な機能を提供します。
	 *	直交行列とは、逆行列が存在し(正則)、逆行列と転置行列が等しい行列のことです。
	 *	M を直交行列として数式で記述すると以下のようになります。
	 *
	 *	\f[
	 *		\mathbf{M}^{-1} = \mathbf{M}^{\top}
	 *	\f]
	 *
	 *	代数的な定義は上記のとおりですが、直交行列を一次変換の見地で述べると、
	 *	回転変換、平行移動変換、すべての軸方向の拡大率が等しい拡大縮小変換の
	 *	合成変換を満たすことになります。
	 *	この変換の特徴は、変換した際に常に角度が保存されるという点です。
	 *
	 *	直交行列は、
	 * 	その性質上表現できる行列に制限がありますが、
	 *	逆行列を求める方法が転置するだけでよいということから、
	 *	一般的な行列よりも高速に逆行列を求められるという長所があります。
	 *	FK では、直交行列を一般行列から区別して扱うことで、
	 *	座標変換処理の高速化を実現しています。
	 *
	 *	数学的には、全ての軸方向に対して等しい倍率の拡大縮小を行う変換行列も
	 *	直交行列と言えますが、このクラスにおいては拡大縮小行列を想定していません。
	 *	そのような行列が設定された場合は、挙動に不具合を生じる可能性があります。
	 *
	 *	一般的な4元正方行列を扱う場合は fk_Matrix を利用して下さい。
	 *	さらに任意元の正方行列を扱う場合は fk_GenMatrix を利用して下さい。
	 *
	 *	\sa fk_Matrix, fk_GenMatrix, fk_Vector, fk_HVector, fk_Angle
	 */
	class fk_OrthoMatrix {
		friend class	fk_Matrix;
		friend class	fk_Vector;
		friend class	fk_HVector;

	public:

		//! コンストラクタ
		/*!
		 *	単位行列を生成します。
		 */
		fk_OrthoMatrix(void);

		//! コピーコンストラクタ
		fk_OrthoMatrix(const fk_OrthoMatrix &);


		//! デストラクタ
		~fk_OrthoMatrix();

		//! \name 単項演算子
		//@{

		//! 逆行列取得演算子
		/*!
		 *	以下のコードは、M_org の逆行列を M_new に代入します。
		 *
		 *		M_new = !M_org;
		 *
		 *	このとき、M_org は変化しません。
		 */
		fk_OrthoMatrix	operator !(void) const;

		//! 成分参照演算子
		/*!
		 *	行列中の各成分を直接参照する場合や、
		 *	直接代入する場合は配列演算子を用います。
		 *	以下のコードは、行列 \f$\mathbf{M}\f$ における成分
		 *	\f$ M_{12} \f$ に 1 を代入するものです。
		 *
		 *		M[1][2] = 1.0;
		 *
		 *	行列の成分は、配列演算子のうち左側が行番号、右側が列番号を指します。
		 *	配列は以下の通りです。
		 *
		 *	\f[
		 *		\left( \begin{array}{cccc}
		 *			\left[0\right]\left[0\right] &
		 *			\left[0\right]\left[1\right] &
		 *			\left[0\right]\left[2\right] &
		 *			\left[0\right]\left[3\right] \\
		 *			\left[1\right]\left[0\right] &
		 *			\left[1\right]\left[1\right] &
		 *			\left[1\right]\left[2\right] &
		 *			\left[1\right]\left[3\right] \\
		 *			\left[2\right]\left[0\right] &
		 *			\left[2\right]\left[1\right] &
		 *			\left[2\right]\left[2\right] &
		 *			\left[2\right]\left[3\right] \\
		 *			\left[3\right]\left[0\right] &
		 *			\left[3\right]\left[1\right] &
		 *			\left[3\right]\left[2\right] &
		 *			\left[3\right]\left[3\right] \\
		 *		\end{array} \right)
		 *	\f]
		 *
		 *	\note
		 *		厳密には、行全体が double 型の配列として存在しており、
		 *		例えば M[1] というのは上から 2 行目の配列ポインタを指します。
		 *		また、16個の成分要素全体がメモリとして全て整列していることは保証されています。
		 *
		 *	\warning
		 *		(この警告は、 fk_Matrix 型のインスタンスで利用する場合には関係ありません。)
		 *		fk_OrthoMatrix 型の変数では注意が必要です。
		 *		この機能を用いて成分を直接書き換えた場合、
		 *		数学的には行列が直交行列の条件を満たさなくなる設定も可能となります。
		 *		その場合の挙動は保証できません。
		 *		直交行列であることが保証できない操作を行う場合は、
		 *		fk_OrthoMatrix ではなく fk_Matrix を用いてください。
		 */
		double *		operator [](int);

		//@}

		//! \name 比較演算子 
		//@{

		//! 同値比較演算子
		/*!
		 *	fk_OrthoMatrix では、以下のように記述することで、
		 *	M1 と M2 が等しいかどうかを判断できます。
		 *
		 *		if(M1 == M2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、各成分の比較において
		 *	FK_MATRIX_EPS までの数値誤差を許容しています。
		 */
		bool	operator ==(const fk_OrthoMatrix &) const;

		//! 異値比較演算子
		/*!
		 *	fk_OrthoMatrix では、以下のように記述することで、
		 *	M1 と M2 が等しくないかどうかを判断できます。
		 *
		 *		if(M1 != M2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、各成分の比較において
		 *	FK_MATRIX_EPS までの数値誤差を許容しています。
		 */
		bool	operator !=(const fk_OrthoMatrix &) const;
		//@}

		//! \name 代入演算子 
		//@{

		//! 単純代入演算子
		fk_OrthoMatrix &		operator =(const fk_OrthoMatrix &);

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
		 */
		fk_OrthoMatrix &		operator *=(const fk_OrthoMatrix &);

		//@}

		//! \name メンバ関数
		//@{
		//! 単位行列化関数
		/*!
		 *	行列を単位行列に初期化します。
		 */
		void			init(void);

		//! 成分設定関数
		/*!
		 *	行番号 row、列番号 col に対応する成分を value に設定します。
		 *	row, col はそれぞれ最初が 0、最後が 3 になります。
		 *
		 *	\param[in]	row		行番号
		 *	\param[in]	col		列番号
		 *	\param[in]	value	設定する成分の値
		 *
		 *	\warning
		 *		(この警告は、 fk_Matrix 型のインスタンスで利用する場合には関係ありません。)
		 *		fk_OrthoMatrix 型の変数では注意が必要です。
		 *		この機能を用いて成分を直接書き換えた場合、
		 *		数学的には行列が直交行列の条件を満たさなくなる設定も可能となります。
		 *		その場合の挙動は保証できません。
		 *		直交行列であることが保証できない操作を行う場合は、
		 *		fk_OrthoMatrix ではなく fk_Matrix を用いてください。
		 */
		void			set(int row, int col, double value);

		//! 行ベクトル成分設定関数1
		/*!
		 *	行列中の、行番号が row である行ベクトルを設定します。
		 *	row は最初が 0、最後が 3 となります。この関数の場合、
		 *	行ベクトルの最後の成分については値は変更しません。
		 *
		 * 	次のコード
		 *
		 *		M.setRow(row, vec);
		 *
		 *	は、以下のコードと同義になります。
		 *
		 *		M[row][0] = vec.x;
		 *		M[row][1] = vec.y;
		 *		M[row][2] = vec.z;
		 *
		 *	\param[in]	row		行番号
		 *	\param[in]	V		行ベクトル
		 */
		void			setRow(int row, const fk_Vector &V);

		//! 行ベクトル成分設定関数2
		/*!
		 *	行列中の、行番号が row である行ベクトルを設定します。
		 *	row は最初が 0、最後が 3 となります。
		 *
		 * 	次のコード
		 *
		 *		M.setRow(row, vec);
		 *		
		 *	は、以下のコードと同義になります。
		 *
		 *		M[row][0] = vec.x;
		 *		M[row][1] = vec.y;
		 *		M[row][2] = vec.z;
		 *		M[row][3] = vec.w;
		 *
		 *	\param[in]	row		行番号
		 *	\param[in]	V		行ベクトル
		 */
		void			setRow(int row, const fk_HVector &V);

		//! 列ベクトル成分設定関数1
		/*!
		 *	行列中の、列番号が col である列ベクトルを設定します。
		 *	col は最初が 0、最後が 3 となります。この関数の場合、
		 *	列ベクトルの最後の成分については値は変更しません。
		 *
		 * 	次のコード
		 *
		 *		M.setCol(col, vec);
		 *
		 *	は、以下のコードと同義になります。
		 *		
		 *		M[0][col] = vec.x;
		 *		M[1][col] = vec.y;
		 *		M[2][col] = vec.z;
		 *
		 *	\param[in]	col		行番号
		 *	\param[in]	V		行ベクトル
		 */
		void			setCol(int col, const fk_Vector &V);
	
		//! 列ベクトル成分設定関数2
		/*!
		 *	行列中の、列番号が col である列ベクトルを設定します。
		 *	col は最初が 0、最後が 3 となります。
		 *
		 * 	次のコード
		 *
		 *		M.setCol(col, vec);
		 *
		 *	は、以下のコードと同義になります。
		 *
		 *		M[0][col] = vec.x;
		 *		M[1][col] = vec.y;
		 *		M[2][col] = vec.z;
		 *		M[3][col] = vec.w;
		 *
		 *	\param[in]	col		行番号
		 *	\param[in]	V		行ベクトル
		 */
		void			setCol(int col, const fk_HVector &V);

		//! 行ベクトル成分取得関数
		/*!
		 *	行列中の、行番号が row である行ベクトルを返します。
		 *	row は最初が 0、最後が 3 となります。
		 *
		 *	\param[in]	row		行番号
		 *
		 *	\return 行ベクトル
		 */
		fk_HVector		getRow(int row);

		//! 列ベクトル成分取得関数
		/*!
		 *	行列中の、列番号が col である列ベクトルを返します。
		 *	col は最初が 0、最後が 3 となります。
		 *
		 *	\param[in]	col		列番号
		 *
		 *	\return 列ベクトル
		 */
		fk_HVector		getCol(int col);

		//! 逆行列化関数
		/*!
		 *	現在設定されている行列に対し、自身を逆行列化します。
		 *
		 *	\return
		 *		成功すれば true を、失敗すれば false を返します。
		 *		通常、直交行列であれば結果は必ず成功となります。
		 *
		 *	\note
		 *		直交行列の場合、この関数は negate() でもまったく同様に動作します。
		 */
		bool			inverse(void);

		//! 転置化関数
		/*!
		 *	現在設定されている行列に対し、自身を転置化します。
		 *
		 *	\note
		 *		直交行列の場合、この関数は inverse() でもまったく同様に動作します。
		 */
		void			negate(void);

		//! 座標軸回転行列生成関数
		/*!
		 *	座標軸回転変換を表す行列を生成します。
		 *
		 *	\param[in]	rad		回転角。単位は弧度法(ラジアン)です。
		 *	\param[in]	axis	座標軸。 fk_X, fk_Y, fk_Z のいずれかになります。
		 */
		void			makeRot(double rad, fk_Axis axis);

		//! 平行移動行列生成関数1
		/*!
		 *	平行移動変換を表す行列を生成します。
		 *
		 *	\param[in]	x	移動ベクトルの x 成分
		 *	\param[in]	y	移動ベクトルの y 成分
		 *	\param[in]	z	移動ベクトルの z 成分
		 */
		void			makeTrans(double x, double y, double z);	

		//! 平行移動行列生成関数2
		/*!
		 *	平行移動変換を表す行列を生成します。
		 *
		 *	\param[in]	V	移動ベクトル
		 */
		void			makeTrans(const fk_Vector &V);

		//! オイラー角回転行列生成関数1
		/*!
		 *	オイラー角による合成回転変換を表す行列を生成します。
		 *	オイラー角については、 fk_Angle を参照して下さい。
		 *
		 *	\param[in]	h	ヘディング角
		 *	\param[in]	p	ピッチ角
		 *	\param[in]	b	バンク角
		 */
		void			makeEuler(double h, double p, double b);

		//! オイラー角回転行列生成関数2
		/*!
		 *	オイラー角による合成回転変換を表す行列を生成します。
		 *	オイラー角については、 fk_Angle を参照して下さい。
		 *
		 *	\param[in]	angle	オイラー角
		 */
		void			makeEuler(const fk_Angle &angle);
		//@}
	
#ifndef FK_DOXYGEN_USER_PROCESS

		float *			GetBuffer(void);
		void			Print(std::string = "") const;

#endif

		//! \name 二項演算子
		//@{
		friend fk_HVector		operator *(const fk_OrthoMatrix &,
										   const fk_HVector &);
		friend fk_OrthoMatrix	operator *(const fk_OrthoMatrix &,
										   const fk_OrthoMatrix &);
		friend fk_Matrix	operator *(const fk_Matrix &, const fk_OrthoMatrix &);
		friend fk_Matrix	operator *(const fk_OrthoMatrix &, const fk_Matrix &);
		friend fk_Matrix	operator +(const fk_Matrix &, const fk_OrthoMatrix &);
		friend fk_Matrix	operator +(const fk_OrthoMatrix &, const fk_Matrix &);
		friend fk_Matrix	operator -(const fk_Matrix &, const fk_OrthoMatrix &);
		friend fk_Matrix	operator -(const fk_OrthoMatrix &, const fk_Matrix &);
		//@}

	protected:

#ifndef FK_DOXYGEN_USER_PROCESS

		double	m[4][4];
		float	*buf;
		bool	updateStatus;
		void	MultVec(fk_HVector &, const fk_HVector &) const;

#endif
	};


	//! ベクトル変換二項演算子
	/*!
	 *	4次元ベクトル V1 の、直交行列 M による変換ベクトル V2 を求めるには、
	 *	以下のように記述します。
	 *	V1, V2 は共に fk_HVector 型の変数で、M は fk_OrthoMatrix 型の変数です。
	 *
	 *		V2 = M * V1;
	 *
	 *	FK では行列体系として MV 系を採用しており、
	 *	行列のベクトル変換の際には行列が左側、ベクトルが右側である必要があります。
	 */
	fk_HVector		operator *(const fk_OrthoMatrix &,
							   const fk_HVector &);
	//! 行列積二項演算子1
	/*!
	 *	直交行列 M1, M2 の行列積 M3 を求めるには、
	 *	以下のように記述します。
	 *	M1, M2, M3 はいずれも fk_OrthoMatrix 型の変数です。
	 *
	 *		M3 = M1 * M2;
	 *
	 *	\note
	 *	行列積は交換法則が成り立たないため、
	 *	\f$ \mathbf{M}_1\mathbf{M}_2 \f$ と
	 *	\f$ \mathbf{M}_2\mathbf{M}_1 \f$ は一般的に結果が異なります。
	 */
	fk_OrthoMatrix	operator *(const fk_OrthoMatrix &,
							   const fk_OrthoMatrix &);

	//! 行列積二項演算子2
	/*!
	 *	一般行列 M_ord と直交行列 M_ortho の行列積 M を求めるには、
	 *	以下のように記述します。
	 *	M_ord, M は fk_Matrix 型、M_ortho は fk_OrthoMatrix 型の変数です。
	 *
	 *		M = M_ord * M_ortho;
	 *
	 *	\note
	 *	行列積は交換法則が成り立たないため、
	 *	\f$ \mathbf{M}_1\mathbf{M}_2 \f$ と
	 *	\f$ \mathbf{M}_2\mathbf{M}_1 \f$ は一般的に結果が異なります。
	 */
	fk_Matrix	operator *(const fk_Matrix &, const fk_OrthoMatrix &);

	//! 行列積二項演算子3
	/*!
	 *	直交行列 M_ortho と一般行列 M_ord の行列積 M を求めるには、
	 *	以下のように記述します。
	 *	M_ord, M は fk_Matrix 型、M_ortho は fk_OrthoMatrix 型の変数です。
	 *
	 *		M = M_ortho * M_ord;
	 *
	 *	\note
	 *	行列積は交換法則が成り立たないため、
	 *	\f$ \mathbf{M}_1\mathbf{M}_2 \f$ と
	 *	\f$ \mathbf{M}_2\mathbf{M}_1 \f$ は一般的に結果が異なります。
	 */
	fk_Matrix	operator *(const fk_OrthoMatrix &, const fk_Matrix &);

	//! 行列和二項演算子1
	/*!
	 *	一般行列 M_ord と直交行列 M_ortho の行列和 M を求めるには、
	 *	以下のように記述します。
	 *	M_ord, M は fk_Matrix 型、M_ortho は fk_OrthoMatrix 型の変数です。
	 *
	 *		M = M_ord + M_ortho;
	 *
	 *	\note
	 *	行列和は交換法則が成り立ちます。
	 */
	fk_Matrix	operator +(const fk_Matrix &, const fk_OrthoMatrix &);

	//! 行列和二項演算子2
	/*!
	 *	直交行列 M_ortho と一般行列 M_ord の行列和 M を求めるには、
	 *	以下のように記述します。
	 *	M_ord, M は fk_Matrix 型、M_ortho は fk_OrthoMatrix 型の変数です。
	 *
	 *		M = M_ortho + M_ord;
	 *
	 *	\note
	 *	行列和は交換法則が成り立ちます。
	 */
	fk_Matrix	operator +(const fk_OrthoMatrix &, const fk_Matrix &);

	//! 行列差二項演算子1
	/*!
	 *	一般行列 M_ord と直交行列 M_ortho の行列差 M を求めるには、
	 *	以下のように記述します。
	 *	M_ord, M は fk_Matrix 型、M_ortho は fk_OrthoMatrix 型の変数です。
	 *
	 *		M = M_ord - M_ortho;
	 *
	 *	\note
	 *	行列差は交換法則が成り立ちません。
	 */
	fk_Matrix	operator -(const fk_Matrix &, const fk_OrthoMatrix &);

	//! 行列差二項演算子2
	/*!
	 *	直交行列 M_ortho と一般行列 M_ord の行列差 M を求めるには、
	 *	以下のように記述します。
	 *	M_ord, M は fk_Matrix 型、M_ortho は fk_OrthoMatrix 型の変数です。
	 *
	 *		M = M_ortho - M_ord;
	 *
	 *	\note
	 *	行列差は交換法則が成り立ちません。
	 */
	fk_Matrix	operator -(const fk_OrthoMatrix &, const fk_Matrix &);



	//! 一般4元正方行列を管理するクラス
	/*!
	 *	このクラスは、一般4元正方行列に関する様々な機能を提供します。
	 *	このクラスは、 fk_OrthoMatrix クラスから派生しており、
	 *	多くの重要な機能は fk_OrthoMatrix から継承していますので、
	 *	そちらの解説も合わせて参照して下さい。
	 *
	 *	行列同士の演算の他、ベクトルとの積演算(一次変換)も
	 *	fk_Vector や fk_HVector クラスを用いて行えます。
	 *	FKでは行列は MV 行列系を採用しています。
	 *	従って、行列とベクトルの積演算においては行列が左側、ベクトルは右側となり、
	 *	ベクトルは列ベクトルとして扱われます。
	 *	また、行列積による合成変換を生成した場合、
	 *	変換は右側の行列から行われることになります。
	 *
	 *	行列とベクトルの積に fk_Vector 型を用いた場合、
	 *	同次座標が 1 である fk_HVector 型として扱われます。
	 *
	 *	直交行列のみを扱う場合は fk_OrthoMatrix を利用して下さい。
	 *	任意元の正方行列を扱う場合は fk_GenMatrix を利用して下さい。
	 *
	 *	\sa fk_OrthoMatrix, fk_GenMatrix, fk_Vector, fk_HVector
	 */
	class fk_Matrix : public fk_OrthoMatrix {

		friend class	fk_Vector;
		friend class	fk_HVector;

	public:

		//! コンストラクタ
		/*!
		 *	単位行列を生成します。
		 */
		fk_Matrix(void);

		//! コピーコンストラクタ
		fk_Matrix(const fk_Matrix &);

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
		fk_Matrix		operator !(void) const;

		//@}

		//! \name 比較演算子 
		//@{
		//! 同値比較演算子
		/*!
		 *	fk_Matrix では、以下のように記述することで、
		 *	M1 と M2 が等しいかどうかを判断できます。
		 *
		 *		if(M1 == M2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、各成分の比較において
		 *	FK_MATRIX_EPS までの数値誤差を許容しています。
		 */
		bool	operator ==(const fk_Matrix &) const;

		//! 異値比較演算子
		/*!
		 *	fk_Matrix では、以下のように記述することで、
		 *	M1 と M2 が等しくないかどうかを判断できます。
		 *
		 *		if(M1 != M2) {
		 *			:
		 *			:
		 *		}
		 *
		 *	ここでの比較は、各成分の比較において
		 *	FK_MATRIX_EPS までの数値誤差を許容しています。
		 */
		bool	operator !=(const fk_Matrix &) const;

		//@}

		//! \name 代入演算子 
		//@{

		//! 単純代入演算子
		fk_Matrix &		operator =(const fk_Matrix &);

		//! fk_OrthoMatrix 型からの単純代入演算子
		fk_Matrix &		operator =(const fk_OrthoMatrix &);

		//! 行列和代入演算子1
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
		fk_Matrix &		operator +=(const fk_Matrix &);

		//! 行列和代入演算子2
		/*!
		 *	「行列和代入演算子1」と同義ですが、
		 *	右辺が fk_OrthoMatrix 型の場合に対応する演算子です。
		 */
		fk_Matrix &		operator +=(const fk_OrthoMatrix &);

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
		fk_Matrix &		operator -=(const fk_Matrix &);

		//! 行列差代入演算子2
		/*!
		 *	「行列差代入演算子1」と同義ですが、
		 *	右辺が fk_OrthoMatrix 型の場合に対応する演算子です。
		 */
		fk_Matrix &		operator -=(const fk_OrthoMatrix &);

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
		 *	行列積は交換法則が成り立たないため、
		 *	\f$ \mathbf{M}_2\mathbf{M}_1 \f$ を
		 *	\f$ \mathbf{M}_1 \f$ に代入したいときには、この演算子は利用できません。
		 */
		fk_Matrix &		operator *=(const fk_Matrix &);

		//! 行列積代入演算子2
		/*!
		 *	「行列積代入演算子1」と同義ですが、
		 *	右辺が fk_OrthoMatrix 型の場合に対応する演算子です。
		 */
		fk_Matrix &		operator *=(const fk_OrthoMatrix &);

		//@}

		//! \name メンバ関数
		//@{

		//! 正則判定関数
		/*!
		 *	行列が正則であるかどうかを判定します。
		 *	正則行列とは、逆行列が存在する行列のことです。
		 *	\return 正則であれば true を、そうでなければ false を返します。
		 *	\sa inverse(), isSingular()
		 */
		bool			isRegular(void) const;

		//! 特異判定関数
		/*!
		 *	行列が特異であるかどうかを判定します。
		 *	特異行列とは、逆行列が存在しない行列のことです。
		 *	これは「非正則行列」と同義になります。
		 *
		 *	\return 特異であれば true を、そうでなければ false を返します。
		 *
		 *	\sa inverse(), isRegular()
		 */
		bool			isSingular(void) const;

		//! 逆行列化関数
		/*!
		 *	現在設定されている行列に対し、正則行列であれば自身を逆行列化します。
		 *	特異(非正則)行列である場合は「失敗」とし、成分値を変更しません。
		 *
		 *	\return
		 *		行列が正則である場合、逆行列化して true を返します。
		 *		特異行列であった場合は、成分値を変更せずに false を返します。
		 *
		 *	\sa isRegular(), isSingular()
		 */
		bool			inverse(void);

		//! 拡大縮小行列生成関数1
		/*!
		 *	各座標軸方向への拡大縮小率を個別に設定した行列を生成します。
		 *
		 *	\param[in]	x	x方向の拡大縮小率
		 *	\param[in]	y	y方向の拡大縮小率
		 *	\param[in]	z	z方向の拡大縮小率
		 */
		void			makeScale(double x, double y, double z);

		//! 拡大縮小行列生成関数2
		/*!
		 *	各座標軸方向への拡大縮小率を個別に設定した行列を生成します。
		 *	引数のベクトルの各成分が、軸方向の拡大縮小率と対応します。
		 *
		 *	\param[in]	V	拡大縮小率ベクトル
		 */
		void			makeScale(const fk_Vector &V);

		//! 透視投影変換行列生成関数
		/*!
		 */
		void			makePerspective(double fovy, double aspect,
										double near, double far);

		void			makeFrustum(double left, double right,
									double bottom, double top,
									double near, double far);

		void			makeOrtho(double left, double right,
								  double bottom, double top,
								  double near, double far);
		//@}

		//! \name 二項演算子 
		//@{
		friend fk_HVector	operator *(const fk_Matrix &, const fk_HVector &);
		friend fk_Matrix	operator *(const fk_Matrix &, const fk_Matrix &);
		friend fk_Matrix	operator *(double, const fk_Matrix &);
		friend fk_Matrix	operator *(const fk_Matrix &, double);
		friend fk_Matrix	operator +(const fk_Matrix &, const fk_Matrix &);
		friend fk_Matrix	operator -(const fk_Matrix &, const fk_Matrix &);
		//@}
	};

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
	fk_HVector	operator *(const fk_Matrix &, const fk_HVector &);

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
	fk_Matrix	operator *(const fk_Matrix &, const fk_Matrix &);

	//! 行列実数倍二項演算子1
	/*!
	 *	行列 M1 のスカラー倍行列をエルには、以下のように記述します。
	 *	M1, M2 はいずれも fk_Matrix 型の変数で、d は double 型の変数です。
	 *
	 *		M2 = d * M1;
	 *
	 *	なお、行列と実数の順番は逆でも構いません。
	 */
	fk_Matrix	operator *(double, const fk_Matrix &);

	//! 行列実数倍二項演算子2
	/*!
	 *	行列 M1 のスカラー倍行列をエルには、以下のように記述します。
	 *	M1, M2 はいずれも fk_Matrix 型の変数で、d は double 型の変数です。
	 *
	 *		M2 = M1 * d;
	 *
	 *	なお、行列と実数の順番は逆でも構いません。
	 */
	fk_Matrix	operator *(const fk_Matrix &, double);

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
	fk_Matrix	operator +(const fk_Matrix &, const fk_Matrix &);

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
	fk_Matrix	operator -(const fk_Matrix &, const fk_Matrix &);
}

#endif	/* !__FK_MATRIX_HEADER__ */

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
