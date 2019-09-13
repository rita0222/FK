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


#ifndef __FK_GREGORY_HEADER__
#define __FK_GREGORY_HEADER__

#include <FK/Surface.h>

namespace FK {
	//! Gregory 曲面を生成、管理するクラス
	/*!
	 *	このクラスは、形状として Gregory 曲面を制御する機能を提供します。
	 *	u,v 両方向で 3 次式のみに対応しています。
	 *
	 *	Gregory 曲面の境界線や制御点は以下の図のような構成を持っています。
	 *	\image html Gregory.png "Gregory曲面の構成"
	 *
	 *	以降、この図に基づいて各要素を解説していきます。
	 *
	 *	Gregory 曲面の境界は以下のような 4 本の 3 次 Bezier 曲線により構成されています。
	 *	- fk_SurfDirection::U_S: u 方向 v 始点側曲線
	 *	- fk_SurfDirection::U_E: u 方向 v 終点側曲線
	 *	- fk_SurfDirection::V_S: v 方向 u 終点側曲線
	 *	- fk_SurfDirection::V_E: v 方向 u 終点側曲線
	 *	.
	 *	これらの境界線を構成する制御点を「境界制御点」と呼び、
	 *	図中の「C」で構成されている制御点にあたります。
	 *	これらの点位置は setCurveCtrl() で設定が可能で、
	 *	「曲線名」と「ID」によって指定します。
	 *	図中の境界制御点の一番目が曲線名、二番目が ID にあたります。
	 *	4隅の制御点については指定方法が 2 種類あります。
	 *	例えば、図の左上の制御点は
	 *	setCurveCtrl(fk_SurfDirection::U_E, 0, V) と
	 *	setCurveCtrl(fk_SurfDirection::V_S, 3, V) の両方の指定方法があります。
	 *
	 *	Gregory 曲面は境界制御点の他に、流れベクトルを制御する
	 *	「流れベクトル制御点」があり、図中の「D」で構成されている点にあたります。
	 *	これらの制御点の位置を変更しても境界線は変化しませんが、
	 *	曲面境界部分の流れベクトル(偏微分ベクトル)が変化します。
	 *	流れベクトルを適切に設定すると、
	 *	隣り合う曲面が境界部分で折れ曲がらず滑らかに接続することができます。
	 */

	class fk_Gregory : public fk_Surface {

	public:

		//! コンストラクタ
		fk_Gregory(void);

		//! デストラクタ
		virtual ~fk_Gregory();

		//! 初期化用関数
		/*!
		 *	この関数は、曲面を初期状態(全ての制御点が原点にある状態)にします。
		 */
		void			init(void);

		//! 境界制御点設定関数
		/*!
		 *	境界線の制御点位置ベクトルを設定します。
		 *
		 *	\param[in] cID	設定を行う境界線の種類
		 *	\param[in] vID	制御点 ID。先頭は 0 になります。
		 *	\param[in] pos	制御点位置ベクトル
		 *
		 *	\return 設定に成功した場合 true、失敗した場合 false を返します。
		 */
		bool setCurveCtrl(fk_SurfDirection cID, int vID, const fk_Vector &pos);

		//! 偏微分制御点設定関数
		/*!
		 *	境界偏微分制御点位置ベクトルを設定します。
		 *
		 *	\param[in] cID	設定を行う境界線の種類
		 *	\param[in] vID	制御点 ID。1, 2 のいずれかになります。
		 *	\param[in] pos	制御点位置ベクトル
		 *
		 *	\return 設定に成功した場合 true、失敗した場合 false を返します。
		 */
		bool setDerivCtrl(fk_SurfDirection cID, int vID, const fk_Vector &pos);

		//! 境界制御点参照関数
		/*!
		 *	曲面の境界制御点位置ベクトルを参照します。
		 *
		 *	\param[in] cID	境界線種類
		 *	\param[in] vID	制御点のv方向ID
		 *
		 *	\return 制御点位置ベクトル。IDが不正だった場合、零ベクトルを返します。
		 */
		fk_Vector getCurveCtrl(fk_SurfDirection cID, int vID);

		//! 流れベクトル制御点参照関数
		/*!
		 *	曲面の流れベクトル制御点位置ベクトルを参照します。
		 *
		 *	\param[in] cID	境界線種類
		 *	\param[in] vID	制御点のv方向ID
		 *
		 *	\return 制御点位置ベクトル。IDが不正だった場合、零ベクトルを返します。
		 */
		fk_Vector getDerivCtrl(fk_SurfDirection cID, int vID);

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
		static std::vector< std::vector< std::tuple<int, int, bool> >	> CLinePos;
		
		int GetCID(fk_SurfDirection, int);
		int GetDID(fk_SurfDirection, int);
		void SetCLine(fk_SurfDirection, int, const fk_Vector &);
		void SetDLine(fk_SurfDirection, int, const fk_Vector &);
		fk_Vector GetIntC(double, double, int, int);
		void MakeBezier(fk_Vector [4][4], double, double);

		void MakeCLinePos(void);
	};
}

#endif	// __FK_BEZSURFACE_HEADER__
