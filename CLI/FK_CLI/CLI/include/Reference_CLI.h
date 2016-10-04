// Reference_CLI.h

#pragma once

#include <FK/Reference.h>
#include "Shape_CLI.h"
#include "Vertex_CLI.h"
#include "Half_CLI.h"
#include "Edge_CLI.h"
#include "Loop_CLI.h"

namespace FK_CLI
{
	//! 位相状態参照用クラス
	/*!
	 *	このクラスでは、 fk_Solid クラスのインスタンスにおいて、
	 *	様々な位相状態を参照する機能を提供します。
	 *	fk_Solid の位相についての詳細は、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」という章を参照して下さい。
	 *
	 *	\sa fk_DataAccess, fk_Operation, fk_Modify, fk_Solid
	 */

	public ref class fk_Reference : fk_Shape {
	internal:
		::fk_ReferenceL3 * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Reference::fk_Reference(bool argNewFlg);
		fk_Reference::~fk_Reference();
#endif
		
		//! \name 頂点に関連する関数
		//@{

		//! 頂点接続半稜線参照関数
		/*!
		 *	頂点 V に接続する半稜線のうちの1つを返します。
		 *	V が独立頂点であった場合は null を返します。
		 *
		 *	\param[in]	V		頂点位相
		 *
		 *	\return		接続半稜線のうちの1つ。ない場合は null を返します。
		 */
		fk_Half^			GetOneHOnV(fk_Vertex^ V);

		//! 頂点接続稜線参照関数
		/*!
		 *	頂点 V に接続する稜線のうちの1つを返します。
		 *	V が独立頂点であった場合は null を返します。
		 *
		 *	\param[in]	V		頂点位相
		 *
		 *	\return		接続稜線のうちの1つ。ない場合は null を返します。
		 */
		fk_Edge^			GetOneEOnV(fk_Vertex^ V);

		//! 隣接頂点参照関数
		/*!
		 *	頂点 V に隣接している頂点のうちの1つを返します。
		 *	V が独立頂点であった場合は null を返します。
		 *
		 *	\param[in]	V		頂点位相
		 *
		 *	\return		隣接頂点のうちの1つ。ない場合は null を返します。
		 */
		fk_Vertex^			GetOneNeighborVOnV(fk_Vertex^ V);

		//! 頂点接続全半稜線参照関数
		/*!
		 *	頂点 V を元頂点(開始点)としている全ての半稜線を配列として返します。
		 *
		 *	\param[in]	V		頂点位相
		 *
		 *	\return		V を元頂点とする半稜線の配列
		 */
		cli::array<fk_Half^>^	GetAllHOnV(fk_Vertex^ V);

		//! 頂点接続全稜線参照関数
		/*!
		 *	頂点 V に接続している全ての稜線を配列として返します。
		 *
		 *	\param[in]	V		頂点位相
		 *
		 *	\return		V に接続する稜線の配列
		 */
		cli::array<fk_Edge^>^	GetAllEOnV(fk_Vertex^ V);

		//! 頂点接続全ループ参照関数
		/*!
		 *	頂点 V に接続している全てのループを配列として返します。
		 *
		 *	\param[in]	V		頂点位相
		 *
		 *	\return		V に接続するループの配列
		 */
		cli::array<fk_Loop^>^	GetAllLOnV(fk_Vertex^ V);

		//! 頂点接続稜線数参照関数
		/*!
		 *	頂点 V に接続している稜線の本数を返します。
		 *
		 *	\param[in]	V		頂点位相
		 *
		 *	\return		V に接続する稜線本数
		 */
		int					GetENumOnV(fk_Vertex^ V);

		//! 全隣接頂点参照関数
		/*!
		 *	頂点 V に隣接している全ての頂点を配列として返します。
		 *
		 *	\param[in]	V		頂点位相
		 *
		 *	\return		V に隣接する頂点の配列
		 */
		cli::array<fk_Vertex^>^	GetAllNeighborVOnV(fk_Vertex^ V);

		//! 頂点間稜線参照関数
		/*!
		 *	頂点 V1 と V2 の両方に接続している全ての稜線を配列で返します。
		 *
		 *	\param[in]	V1		頂点位相1
		 *	\param[in]	V2		頂点位相2
		 *
		 *	\return		V1とV2に接続する稜線の配列
		 */
		cli::array<fk_Edge^>^	GetEOnVV(fk_Vertex^ V1, fk_Vertex^ V2);

		//! 頂点接続ループ参照関数
		/*!
		 *	頂点 V に接続しているループのうちの1つを返します。
		 *	V に接続するループが存在しない場合は、null を返します。
		 *
		 *	\param[in]	V		頂点位相
		 *
		 *	\return		接続ループのうちの1つ。ない場合は null を返します。
		 */
		fk_Loop^			GetOneLOnV(fk_Vertex^ V);

		//@}

		//! \name 半稜線に関連する関数
		//@{

		//! 半稜線接続頂点参照関数
		/*!
		 *	半稜線 H の元頂点(出発点)を返します。
		 *
		 *	\param[in]	H		半稜線位相
		 *
		 *	\return		元頂点
		 */
		fk_Vertex^			GetVOnH(fk_Half^ H);

		//! 対半稜線参照関数
		/*!
		 *	半稜線 H と同じ稜線を共有する、反対側の半稜線を返します。
		 *
		 *	\param[in]	H		半稜線位相
		 *
		 *	\return		対の半稜線
		 */
		fk_Half^			GetMateHOnH(fk_Half^ H);

		//! 親稜線参照関数
		/*!
		 *	半稜線 H が所属している稜線を返します。
		 *
		 *	\param[in]	H		半稜線位相
		 *
		 *	\return		親稜線
		 */
		fk_Edge^			GetParentEOnH(fk_Half^ H);

		//! 親ループ参照関数
		/*!
		 *	半稜線 H が所属しているループを返します。
		 *	もし H がどのループにも所属していない場合は null を返します。
		 *
		 *	\param[in]	H		半稜線位相
		 *
		 *	\return		親ループ。ない場合は null を返します。
		 */
		fk_Loop^			GetParentLOnH(fk_Half^ H);

		//@}
	
		//! \name 稜線に関連する関数
		//@{

		//! 右側頂点参照関数
		/*!
		 *	稜線 E において、右側の半稜線の元頂点(出発点)を返します。
		 *
		 *	\param[in]	E		稜線位相
		 *
		 *	\return		右側半稜線の元頂点
		 */
		fk_Vertex^			GetRightVOnE(fk_Edge^ E);

		//! 左側頂点参照関数
		/*!
		 *	稜線 E において、左側の半稜線の元頂点(出発点)を返します。
		 *
		 *	\param[in]	E		稜線位相
		 *
		 *	\return		左側半稜線の元頂点
		 */
		fk_Vertex^			GetLeftVOnE(fk_Edge^ E);

		//! 右側半稜線参照関数
		/*!
		 *	稜線 E において、右側の半稜線を返します。
		 *
		 *	\param[in]	E		稜線位相
		 *
		 *	\return		右側半稜線
		 */
		fk_Half^			GetRightHOnE(fk_Edge^ E);

		//! 左側半稜線参照関数
		/*!
		 *	稜線 E において、左側の半稜線を返します。
		 *
		 *	\param[in]	E		稜線位相
		 *
		 *	\return		左側半稜線
		 */
		fk_Half^			GetLeftHOnE(fk_Edge^ E);

		//! 右側ループ参照関数
		/*!
		 *	稜線 E において、右側にあるループを返します。
		 *	もし右側にループがなければ null を返します。
		 *
		 *	\param[in]	E		稜線位相
		 *
		 *	\return		右側ループ。ない場合は null を返します。
		 */
		fk_Loop^			GetRightLOnE(fk_Edge^ E);

		//! 左側ループ参照関数
		/*!
		 *	稜線 E において、左側にあるループを返します。
		 *	もし左側にループがなければ null を返します。
		 *
		 *	\param[in]	E		稜線位相
		 *
		 *	\return		左側ループ。ない場合は null を返します。
		 */
		fk_Loop^			GetLeftLOnE(fk_Edge^ E);

		//! 稜線位相状態参照関数
		/*!
		 *	稜線 E の位相状態を返します。
		 *	位相状態には、以下のものがあります。
		 *
		 *	- fk_EdgeStatus.UNDEF_EDGE: 未定義稜線。左右両側のループが存在しません。
		 *	- fk_EdgeStatus.HALFDEF_EDGE: 半定義稜線。左右いずれか一方のループが存在します。
		 *	- fk_EdgeStatus.BOTHDEF_EDGE: 両定義稜線。左右両側のループが存在します。
		 *	- fk_EdgeStatus.NONE_EDGE: 位相不整合。位相構造が正常状態ではありません。
		 *
		 *	\param[in]	E		稜線位相
		 *
		 *	\return		位相状態を返します。
		 */
		fk_EdgeStatus		GetEdgeStatus(fk_Edge^ E);

		//@}
	
		//! \name ループに関連する関数
		//@{

		//! ループ所属頂点参照関数
		/*!
		 *	ループ L に属している頂点のうちの1つを返します。
		 *
		 *	\param[in]	L		ループ位相
		 *
		 *	\return		所属頂点
		 */
		fk_Vertex^			GetOneVOnL(fk_Loop^ L);

		//! ループ所属半稜線参照関数
		/*!
		 *	ループ L に属している半稜線のうちの1つを返します。
		 *
		 *	\param[in]	L		ループ位相
		 *
		 *	\return		所属半稜線
		 */
		fk_Half^			GetOneHOnL(fk_Loop^ L);

		//! ループ所属稜線参照関数
		/*!
		 *	ループ L に属している稜線のうちの1つを返します。
		 *
		 *	\param[in]	L		ループ位相
		 *
		 *	\return		所属稜線
		 */
		fk_Edge^			GetOneEOnL(fk_Loop^ L);

		//! ループ所属全頂点参照関数
		/*!
		 *	ループ L に所属している全ての頂点を配列として返します。
		 *
		 *	\param[in]	L		ループ位相
		 *
		 *	\return		L に所属する頂点の配列
		 */
		cli::array<fk_Vertex^>^	GetAllVOnL(fk_Loop^ L);

		//! ループ所属全半稜線参照関数
		/*!
		 *	ループ L に所属している全ての半稜線を配列として返します。
		 *
		 *	\param[in]	L		ループ位相
		 *
		 *	\return		L に所属する半稜線の配列
		 */
		cli::array<fk_Half^>^	GetAllHOnL(fk_Loop^ L);

		//! ループ所属全稜線参照関数
		/*!
		 *	ループ L に所属している全ての稜線を配列として返します。
		 *
		 *	\param[in]	L		ループ位相
		 *
		 *	\return		L に所属する稜線の配列
		 */
		cli::array<fk_Edge^>^	GetAllEOnL(fk_Loop^ L);

		//! 隣接ループ参照関数
		/*!
		 *	ループ L と隣接しているループのうちの1つを返します。
		 *	隣接するループが存在しないときは null を返します。
		 *
		 *	\param[in]	L		ループ位相
		 *
		 *	\return		隣接ループのうちの1つ。ない場合は null を返します。
		 */
		fk_Loop^			GetOneNeighborLOnL(fk_Loop^ L);

		//! 半稜線条件付き隣接ループ参照関数
		/*!
		 *	ループ L と隣接しているループのうち、
		 *	半稜線 H の親稜線を共有しているループを返します。
		 *	この共有関係が成り立たないような状態の場合
		 *	(H が L 上にない、H の反対側にループが存在しないなど)
		 *	は、null を返します。
		 *
		 *	\param[in]	L		ループ位相
		 *	\param[in]	H		半稜線位相
		 *
		 *	\return		H を挟んだ隣接ループ。存在しない場合は null を返します。
		 */
		fk_Loop^			GetNeighborLOnLH(fk_Loop^ L, fk_Half^ H);

		//! ループ上頂点数参照関数
		/*!
		 *	ループ L に所属している頂点の個数を返します。
		 *
		 *	\param[in]	L		ループ位相
		 *
		 *	\return		L に所属する頂点個数
		 */
		int					GetVNumOnL(fk_Loop^ L);

		//! 稜線条件付き隣接ループ参照関数
		/*!
		 *	ループ L と隣接しているループのうち、
		 *	稜線 E を共有しているループを返します。
		 *	この共有関係が成り立たない状態の場合
		 *	(E が L 上にない、E の反対側にループが存在しないなど)
		 *	は、null を返します。
		 *
		 *	\param[in]	L		ループ位相
		 *	\param[in]	E		稜線位相
		 *
		 *	\return		E を挟んだ隣接ループ。存在しない場合は null を返します。
		 */
		fk_Loop^			GetNeighborLOnLE(fk_Loop^ L, fk_Edge^ E);

		//! 全隣接ループ参照関数
		/*!
		 *	ループ L に隣接している全てのループを配列として返します。
		 *
		 *	\param[in]	L		ループ位相
		 *
		 *	\return		L に隣接するループの配列
		 */
		cli::array<fk_Loop^>^	GetAllNeighborLOnL(fk_Loop^ L);
		//@}
	};
}

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
