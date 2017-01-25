﻿#ifndef __FK_GREGORY_HEADER__
#define __FK_GREGORY_HEADER__

#include <FK/BezSurface.h>

namespace FK {
	//! Gregory 曲面を生成、管理するクラス
	/*!
	 *	このクラスは、形状として Gregory 曲面を制御する機能を提供します。
	 *	次数は u,v 両方で 3 次式で固定となります。
	 *	制御点を直接指定する方法の他に、
	 *	他の Gregory 曲面と G1 連続性を保証する接続を行う機能が提供されています。
	 */

	class fk_Gregory : public fk_Surface {

	public:

		//! コンストラクタ
		fk_Gregory(void);

		//! デストラクタ
		virtual ~fk_Gregory();

		//! 初期化用関数
		/*!
		 *	この関数は、曲線を初期状態(3次式、全ての制御点が原点にある状態)にします。
		 */
		void	init(void);

		//! 境界上制御点設定関数
		/*!
		 *	Gregory 曲面の境界線の制御点位置ベクトルを設定します。
		 *	なお、Gregory 曲面の四隅にあたる制御点は、
		 *	u 方向側からも v 方向側も指定が可能です。
		 *
		 *	\param[in] uv	境界線のIDを指定します。
		 *					0 が u側でv始点側、1 がu側でv終点側、
		 *					2 が v側でu始点側、3 がv側でu終点側です。
		 *					この部分は、 fk_SurfDirection 型で指定することも可能です。
		 *	\param[in] ID	境界線制御点のIDを指定します。
		 *					曲線の始点は0で、
		 *					続く制御点のIDが 1,2,3 となります。
		 *	\param[in] pos	制御点位置ベクトル
		 *
		 *	\return 設定に成功した場合 true、失敗した場合 false を返します。
		 *
		 *	\sa setCtrl(), getBoundary(), fk_SurfDirection
		 */
		bool	setBoundary(int uv, int ID, const fk_Vector &pos);

		//! 内部制御点設定関数
		/*!
		 *	Gregory 曲面の内部制御点の位置ベクトルを設定します。
		 *	ID は、隣接する境界線の制御点 ID と一致します。
		 *
		 *	\param[in] uv	指定する制御点に隣接する境界曲線のIDを指定します。
		 *					0 が u側でv始点側、1 がu側でv終点側、
		 *					2 が v側でu始点側、3 がv側でu終点側です。
		 *					この部分は、 fk_SurfDirection 型で指定することも可能です。
		 *	\param[in] ID	境界線制御点のIDを指定します。
		 *					1 か 2 のいずれかしか指定できません。
		 *	\param[in] pos	制御点位置ベクトル
		 *
		 *	\return 設定に成功した場合 true、失敗した場合 false を返します。
		 *
		 *	\sa setBoudary(), getCtrl(), fk_SurfDirection
		 */
		bool	setCtrl(int uv, int ID, const fk_Vector &pos);

		//! 境界上制御点参照関数
		/*!
		 *	Gregory 曲面の境界線の制御点位置ベクトルを参照します。
		 *
		 *	\param[in] uv	境界線のIDを指定します。
		 *					0 が u側でv始点側、1 がu側でv終点側、
		 *					2 が v側でu始点側、3 がv側でu終点側です。
		 *					この部分は、 fk_SurfDirection 型で指定することも可能です。
		 *	\param[in] ID	境界線制御点のIDを指定します。
		 *					曲線の始点は0で、
		 *					続く制御点のIDが 1,2,3 となります。
		 *
		 *	\return 制御点位置ベクトル。IDが不正だった場合、零ベクトルを返します。
		 *
		 *	\sa setBoundary(), fk_SurfDirection
		 */
		fk_Vector	getBoundary(int uv, int ID);

		//! 内部制御点参照関数
		/*!
		 *	Gregory 曲面の内部制御点の位置ベクトルを参照します。
		 *
		 *	\param[in] uv	指定する制御点に隣接する境界曲線のIDを指定します。
		 *					0 が u側でv始点側、1 がu側でv終点側、
		 *					2 が v側でu始点側、3 がv側でu終点側です。
		 *					この部分は、 fk_SurfDirection 型で指定することも可能です。
		 *	\param[in] ID	境界線制御点のIDを指定します。
		 *					1 か 2 のいずれかしか指定できません。
		 *
		 *	\return 制御点位置ベクトル。IDが不正だった場合、零ベクトルを返します。
		 *
		 *	\sa setCtrl(), fk_SurfDirection
		 */
		fk_Vector	getCtrl(int uv, int ID);

		//! 曲面点算出関数
		/*!
		 *	パラメータに対応する曲面上の点の位置ベクトルを返します。
		 *
		 *	\param[in]	u	曲面の u パラメータ
		 *	\param[in]	v	曲面の v パラメータ
		 *
		 *	\return 曲面上の点の位置ベクトル
		 */
		fk_Vector		pos(double u, double v);

		//! 曲面 u 方向偏微分ベクトル算出関数
		/*!
		 *	曲面上の u 方向偏微分ベクトルを算出する関数です。
		 *
		 *	\param[in]	u	u パラメータ
		 *	\param[in]	v	v パラメータ
		 *
		 *	\return		曲面上の u 方向偏微分ベクトル
		 */
		fk_Vector		uDeriv(double u, double v);

		//! 曲面 v 方向偏微分ベクトル算出関数
		/*!
		 *	曲面上の v 方向偏微分ベクトルを算出する関数です。
		 *
		 *	\param[in]	u	u パラメータ
		 *	\param[in]	v	v パラメータ
		 *
		 *	\return		曲面上の v 方向偏微分ベクトル
		 */
		fk_Vector		vDeriv(double u, double v);

	private:
		fk_BezSurface	bez;
		fk_Vector		ctrl[20];

		int		MapID(bool, int, int);
		void	BezSet(double, double);
	};
}

#endif	// __FK_GREGORY_HEADER__

/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
