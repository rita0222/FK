#ifndef __FK_BSPLSURFACE_HEADER__
#define __FK_BSPLSURFACE_HEADER__

#include <FK/Surface.h>

namespace FK {

	//! B-Spline 曲面を生成、管理するクラス
	/*!
	 *	このクラスは、形状として B-Spline 曲面を制御する機能を提供します。
	 *	初期状態での位数はu,v方向ともに 3 で、制御点が全て原点にある状態となります。
	 *	現状では位数が 3,4,5 のいずれかのみしか生成できません。
	 *	また、このクラスの B-Spline 曲面は開一様 (Open Uniform)
	 *	であることを前提にしており、ノットベクトルを制御することはできません。
	 */

	class fk_BSplSurface : public fk_Surface {

	public:

		//! コンストラクタ
		fk_BSplSurface(void);

		//! デストラクタ
		virtual ~fk_BSplSurface();

		//! 初期化用関数
		/*!
		 *	この関数は、曲面を初期状態にします。
		 *	初期状態とは、以下のような条件で曲面を構築することです。
		 *		- u方向、v方向共に位数が 3。
		 *		- 制御点数が 3x3。
		 *		- すべての制御点の位置ベクトルが原点と一致。
		 *		.
		 */
		void	init(void);

		//! 位数設定関数
		/*!
		 *	曲面の位数を設定します。
		 *	現状では、3,4,5 のいずれかのみ以外は設定できません。
		 *	この関数を設定した後、制御点数は位数の2乗に固定され、
		 *	すべての制御点は原点に配置されます。
		 *
		 *	\param[in]	uO	u方向の位数
		 *	\param[in]	vO	v方向の位数
		 *
		 *	\return 位数設定に成功した場合 true、失敗した場合 false を返します。
		 */
		bool	setOrdinate(int uO, int vO);

		//! 制御点数設定関数
		/*!
		 *	曲面の制御点数を設定します。
		 *	制御点数は u 方向、v 方向で別々に指定し、
		 *	実際にはその積が制御点数となります。
		 *	制御点数は、それぞれの方向に設定されている位数以上である必要があります。
		 *	上限値はありません。
		 *
		 *	\param[in]	uN   	u方向の制御点数
		 *	\param[in]	vN		v方向の制御点数
		 *
		 *	\return 設定に成功した場合 true、失敗した場合 false を返します。
		 */
		bool	setNum(int uN, int vN);

		//! 制御点個別設定関数
		/*!
		 *	曲線の制御点位置ベクトルを設定します。
		 *
		 *	\param[in]	uID	設定する制御点の u 方向の ID。先頭は 0 になります。
		 *	\param[in]	vID	設定する制御点の v 方向の ID。先頭は 0 になります。
		 *	\param[in]	pos	制御点位置ベクトル
		 *
		 *	\return 設定に成功した場合 true、失敗した場合 false を返します。
		 */
		bool	setCtrl(int uID, int vID, const fk_Vector &pos);

		//! 制御点一斉設定関数
		/*!
		 *	曲面の制御点位置ベクトルを、vector 配列を用いて一斉に設定します。
		 *	設定の際、制御点数は setNum() によって設定しておく必要があり、
		 *	配列のサイズは上記の積と一致していなければなりません。
		 *
		 *	\param[in]	array	制御点の vector 配列のポインタ
		 *
		 *	\return 設定に成功した場合 true、失敗した場合 false を返します。
		 */
		bool	setCtrl(std::vector<fk_Vector> *array);	

		//! u方向位数参照関数
		/*!
		 *	曲面の u 方向の位数を参照します。
		 *
		 *	\return 位数
		 */
		int		getUOrdinate(void);	

		//! v方向位数参照関数
		/*!
		 *	曲面の v 方向の位数を参照します。
		 *
		 *	\return 位数
		 */
		int		getVOrdinate(void);	

		//! u方向制御点数参照関数
		/*!
		 *	曲面の u 方向の制御点数を参照します。
		 *
		 *	\return	u 方向の制御点数
		 */
		int		getUNum(void);

		//! v方向制御点数参照関数
		/*!
		 *	曲面の v 方向の制御点数を参照します。
		 *
		 *	\return	v 方向の制御点数
		 */
		int		getVNum(void);

		//! 制御点参照関数
		/*!
		 *	曲面の制御点位置ベクトルを参照します。
		 *
		 *	\param[in]	uID	u 方向の制御点 ID
		 *	\param[in]	vID	v 方向の制御点 ID
		 *
		 *	\return 制御点位置ベクトル。IDが不正だった場合、零ベクトルを返します。
		 */
		fk_Vector	getCtrl(int uID, int vID);

		//! 曲面算出関数
		/*!
		 *	パラメータに対応する曲面上の点の位置ベクトルを返します。
		 *
		 *	\param[in]	u	曲面上の u パラメータ
		 *	\param[in]	v	曲面上の v パラメータ
		 *
		 *	\return 曲面上の点の位置ベクトル
		 */
		fk_Vector	pos(double u, double v);

		//! 曲線 u 方向1階偏微分ベクトル算出関数
		/*!
		 *	パラメータに対応する曲面上の u 方向1階偏微分ベクトルを返します。
		 *
		 *	\param[in]	u	曲面上の u パラメータ
		 *	\param[in]	v	曲面上の v パラメータ
		 *
		 *	\return 曲面上の u 方向1階偏微分ベクトル
		 */
		fk_Vector	uDeriv(double u, double v);

		//! 曲線 v 方向1階偏微分ベクトル算出関数
		/*!
		 *	パラメータに対応する曲面上の v 方向1階偏微分ベクトルを返します。
		 *
		 *	\param[in]	u	曲面上の u パラメータ
		 *	\param[in]	v	曲面上の v パラメータ
		 *
		 *	\return 曲面上の v 方向1階偏微分ベクトル
		 */
		fk_Vector	vDeriv(double u, double v);

	private:
		int						uOrd, vOrd;
		int						uNum, vNum;
		std::vector<fk_Vector>	ctrlPos;
		std::vector<double>		uKnot, vKnot;
		std::vector<double>		tmpU, tmpV;
	};
}

#endif	// __FK_BSPLSURFACE_HEADER__

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
