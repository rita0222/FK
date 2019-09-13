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
#ifndef __FK_SURFACE_HEADER__
#define __FK_SURFACE_HEADER__

#include <FK/Vector.h>
#include <FK/FVecArray.h>
#include <FK/Line.h>
#include <FK/Point.h>

namespace FK {

	//! 曲面の uv 方向を表す列挙型
	enum class fk_SurfDirection : int {
		U_S = 0,	//!< u側(v始点側)
		U_E = 1,	//!< u側(v終点側)
		V_S = 2,	//!< v側(u始点側)
		V_E = 3		//!< v側(u終点側)
	};
	
	//! 曲面用純粋仮想クラス
	/*!
	 *	このクラスは、自由曲面用の純粋仮想クラスです。
	 *	このクラスを継承することによって、
	 *	ユーザは任意の自由曲面形式を四辺形となる fk_Loop に追加することができます。
	 *	自由曲面は、以下の条件を満たす必要があります。
	 *	- パラメータ空間が 2 次元である。(以降、これを「u方向」「v方向」とします。)
	 *	- パラメータ空間中のあらゆるパラメータで曲面上の点を算出できる。
	 *	- パラメータ空間中のあらゆるパラメータで、
	 *		u 方向 と v 方向共に偏微分ベクトルが算出できる。
	 *	- 曲面のパラメータ端点、
	 *		つまり (0, 0), (0, 1), (1, 0), (1, 1) となる 4 点の位置ベクトルが、
	 *		ループの 4 頂点の位置ベクトルと一致している。
	 *
	 *	\sa fk_Loop, fk_Curve
	 */ 

	class fk_Surface : public fk_Shape {

	public:

		//! コンストラクタ
		fk_Surface(void);

		//! デストラクタ
		virtual ~fk_Surface();

		//! 曲面点位置ベクトル算出関数
		/*!
		 *	曲面上の点の位置ベクトルを算出する純粋仮想関数です。
		 *	派生クラスにおいて実際に実装する必要があります。
		 *
		 *	\param[in]	u	u パラメータ
		 *	\param[in]	v	v パラメータ
		 *
		 *	\return		曲面上の位置ベクトル
		 */
		virtual fk_Vector	pos(double u, double v) = 0;

		//! 曲面 u 方向偏微分ベクトル算出関数
		/*!
		 *	曲面上の u 方向偏微分ベクトルを算出する純粋仮想関数です。
		 *	派生クラスにおいて実際に実装する必要があります。
		 *
		 *	\param[in]	u	u パラメータ
		 *	\param[in]	v	v パラメータ
		 *
		 *	\return		曲面上の u 方向偏微分ベクトル
		 */
		virtual fk_Vector	uDeriv(double u, double v) = 0;

		//! 曲面 v 方向偏微分ベクトル算出関数
		/*!
		 *	曲面上の v 方向偏微分ベクトルを算出する純粋仮想関数です。
		 *	派生クラスにおいて実際に実装する必要があります。
		 *
		 *	\param[in]	u	u パラメータ
		 *	\param[in]	v	v パラメータ
		 *
		 *	\return		曲面上の v 方向偏微分ベクトル
		 */
		virtual fk_Vector	vDeriv(double u, double v) = 0;

		// 曲面法線ベクトル算出関数
		/*!
		 *	曲面上の法線ベクトルを算出します。
		 *	本関数は、派生クラスにおいて再定義する必要はありません。
		 *
		 *	\param[in]	u	u パラメータ
		 *	\param[in]	v	v パラメータ
		 *
		 *	\return		曲面上の法線ベクトル
		 */
		fk_Vector	norm(double u, double v);

		//! 曲面分割数設定関数
		/*!
		 *	描画する際の曲面の分割数を設定します。
		 *	本関数は、派生クラスにおいて再定義する必要はありません。
		 *
		 *	\param[in]	div		分割数。
		 */
		void	setDiv(int div);
	
		//! 曲面分割数参照関数
		/*!
		 *	描画する際の曲面の分割数を参照します。
		 *	本関数は、派生クラスにおいて再定義する必要はありません。
		 *
		 *	\return		分割数
		 */
		int		getDiv(void);


		//! 制御点数取得関数
		/*!
		 *	曲面の制御点数を取得します。
		 *
		 *	\return	制御点数
		 */
		int	getCtrlSize(void);

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Line * GetLine(void);
		fk_Point * GetPoint(void);
#endif

	protected:
		fk_FVecArray	ctrlPos;
		fk_Line			ctrlLine;

		//! 制御点設定関数1
		/*!
		 *	曲面の制御点位置ベクトルを設定します。
		 *	通常はこの関数ではなく、
		 *	各派生クラスで定義されている制御点設定関数を用います。
		 *
		 *	\param[in]	ID	設定する制御点の ID。先頭は 0 になります。
		 *	\param[in]	pos	制御点位置ベクトル
		 *
		 *	\return	設定に成功した場合 true、失敗した場合 false を返します。
		 */
		bool setCtrl(int ID, fk_Vector *pos);

		//! 制御点設定関数2
		/*!
		 *	曲面の制御点位置ベクトルを設定します。
		 *	通常はこの関数ではなく、
		 *	各派生クラスで定義されている制御点設定関数を用います。
		 *
		 *	\param[in]	ID	設定する制御点の ID。先頭は 0 になります。
		 *	\param[in]	pos	制御点位置ベクトル
		 *
		 *	\return	設定に成功した場合 true、失敗した場合 false を返します。
		 */
		bool setCtrl(int ID, fk_Vector pos);

		//! 制御点取得関数
		/*!
		 *	曲面の制御点位置ベクトルを取得します。
		 *	通常はこの関数ではなく、
		 *	各派生クラスで定義されている制御点取得関数を用います。
		 *
		 *	\param[in]	ID	設定する制御点の ID。先頭は 0 になります。
		 *
		 *	\return	指定した制御点の位置ベクトル。
		 *		指定した制御点が存在しない場合は零ベクトルを返します。
		 */
		fk_Vector getCtrl(int ID);

		//! 制御点最大サイズ設定関数
		/*!
		 *	曲面の制御点最大サイズを設定します。負数が指定された場合は無視します。
		 *	通常はこの関数ではなく、
		 *	各派生クラスで定義されている次数設定関数を用います。
		 *
		 *	\param[in]	num	制御点数
		 */
		void setCtrlSize(int num);

		//! 制御点数設定関数
		/*!
		 *	曲面の制御点数を設定します。負数が指定された場合は無視します。
		 *	通常はこの関数ではなく、
		 *	各派生クラスで定義されている次数設定関数を用います。
		 *
		 *	\param[in]	num	制御点数
		 */
		void setCtrlNum(int num);

#ifndef FK_DOXYGEN_USER_PROCESS
		double	Bezier(int, int, double);
#endif

	private:
		int	div;
		int size;

		fk_Point		ctrlPoint;
	};
}

#endif	// __FK_SURFACE_HEADER__
