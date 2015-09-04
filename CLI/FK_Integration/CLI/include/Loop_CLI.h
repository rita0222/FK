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

﻿// Half_CLI.h

#pragma once

#include <FK/Loop.h>
#include "Topology_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	ref class fk_Half;
	
	//! ソリッドモデルのループ位相を管理するクラス
	/*!
	 *	このクラスは、 fk_Solid によるソリッドモデルにおいて、
	 *	ループ位相に関する制御機能を提供します。
	 *	FK におけるソリッドモデルの構造については、
	 *	ユーザーズマニュアルの「形状に対する高度な操作」の章を参照して下さい。
	 *
	 *	派生クラスのうち、ID 管理については fk_Topology,
	 *	個別マテリアル設定については fk_TopologyMaterial,
	 *	属性設定については fk_Attribute を参照して下さい。
	 *
	 *	ループに対して、幾何形状として曲面データを設定することができます。
	 *	詳細は fk_Surface を参照して下さい。
	 *	\sa fk_Solid, fk_Vertex, fk_Half, fk_Edge, fk_Topology,
	 *		fk_TopologyMaterial, fk_Attribute, fk_Surface
	 */

	public ref class fk_Loop : fk_TopologyMaterial {
	internal:
		::fk_Loop * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Loop(bool argNewFlg);
		~fk_Loop();
		!fk_Loop();
#endif

		//! 接続半稜線プロパティ
		/*!
		 *	このループを構成する半稜線のうちの1つを参照します。
		 *	条件を満たす全ての半稜線を得たい場合は、
		 *	fk_Reference::GetAllHOnL() 関数を用いて下さい。
		 *
		 *	\return このループを構成する半稜線を表す fk_Half 型インスタンスのアドレス。
		 */
		property fk_Half^ OneHalf {
			fk_Half^ get();
		}

		//! 法線ベクトルプロパティ
		/*!
		 *	適切な法線ベクトルを参照します。
		 *	ループが曲面である場合は、面全体の平均法線ベクトルとなります。
		 *	null となるケースがありえることに注意して下さい。
		 *
		 *	\return 法線ベクトルのアドレス。算出できなかった場合は null を返します。
		 */
		property fk_Vector^ Normal {
			fk_Vector^ get();
		}

		//! 頂点数プロパティ
		/*!
		 *	このループを構成する頂点数を参照します。
		 *
		 *	\return	ループを構成する頂点数。もしエラーが生じた場合は -1 となります。
		 *
		 *	\sa fk_Reference::GetVNumOnL()
		 */
		property int VertexNum {
			int get();
		}

		//! テセレーション設定プロパティ
		/*!
		 *	true の場合、4角以上のループに対してテセレーション処理を施すようになります。
		 *	false の場合はテセレーション処理を行いません。
		 *
		 *	「テセレーション」とは、4角以上の多角形に対し、
		 *	内部を複数の3角形に分割する処理のことです。
		 *	一般的に、非凸多角形や非平面多角形である場合、
		 *	描画処理が適切に行えないことがあります。
		 *	そのようなループに対しては、
		 *	テセレーションを施すことによって正常に描画されることが期待できます。
		 *
		 *	形状中の全てのループに対して、テセレーションの有無効を設定するには、
		 *	fk_Operation::TesselateMode を利用して下さい。
		 *
		 *	\sa fk_Operation::TesselateMode
		 */
		property bool TesselateMode {
			bool get();
			void set(bool);
		}

		//! テセレーション状態参照関数
		/*!
		 *	テセレーションが有効になっていても、ループが 3 角形であった場合など、
		 *	内部ではテセレーション処理を行っていない可能性があります。
		 *	実際にテセレーション処理を行ったかどうかを知るには、
		 *	この関数を用いる必要があります。
		 *
		 *	\return
		 *		true であれば、ループに対しテセレーション処理が行われています。
		 *		false であれば行われていません。
		 *
		 *	\sa TesselateMode
		 */
		bool IsTesselated(void);
	};
}
