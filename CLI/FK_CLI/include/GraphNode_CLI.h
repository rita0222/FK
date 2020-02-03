/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
// GraphNode_CLI.h

#ifndef _FK_CLI_GRAPHNODE_
#define _FK_CLI_GRAPHNODE_


#include <FK/GraphNode.h>
#include "Base_CLI.h"
#include "Vector_CLI.h"
#include "Color_CLI.h"
#using <System.dll>

namespace FK_CLI
{
	using namespace System;
	using namespace System::Collections::Generic;

	ref class fk_GraphEdge;

	//! グラフ構造のノードを制御するクラス
	/*!
	 *	このクラスは、グラフ構造におけるノードを制御する機能を提供します。
	 */
	public ref class fk_GraphNode : fk_BaseObject {
	internal:
		::FK::fk_GraphNode * GetP(void);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_GraphNode(::FK::fk_GraphNode*);
		~fk_GraphNode();
		!fk_GraphNode();
#endif
		
		//! ID 取得関数
		/*!
		 *	\return		ID
		 */
		property unsigned int ID {
			unsigned int get();
		}

		//! 位置ベクトル設定関数
		/*!
		 *	ノードの位置ベクトルを設定します。
		 *
		 *	\param[in]	pos		位置ベクトル
		 */

		property fk_Vector^ Position {
			fk_Vector^ get();
			void set(fk_Vector^);
		}

		//! 位置変更回数取得関数
		/*!
		 *	これまでのノード位置変更回数を取得します。
		 *
		 *	\return		変更回数
		 */
		property unsigned int Generation {
			unsigned int get();
		}

		//! 接続ノード確認関数
		/*!
		 *	指定したノードとの間に辺が存在するかどうかを判定します。
		 *	辺の方向も考慮したい場合は IsConnect(bool, fk_GraphNode^) を使用して下さい。
		 *
		 *	\param[in]	node	接続を確認するノード
		 *
		 *	\return		辺が存在する場合 true を、存在しない場合 false を返します。
		 */
		bool IsConnect(fk_GraphNode^ node);

		//! 方向判定付き接続ノード確認関数
		/*!
		 *	指定したノードとの間に、指定した方向の辺が存在するかどうかを判定します。
		 *	IsConnect(fk_GraphNode^) の場合は何かしらの辺が存在すれば true を返しますが、
		 *	こちらの関数では辺の方向を指定することができます。
		 * 	mode が true のときは、this インスタンスから node への経路が存在する場合のみに
		 *	true を返します。そのため、辺が存在していたとしても、
		 *	node から this への一方通行辺だった場合は false を返します。
		 *	mode が false の場合は this インスタンスが終点側の場合に true を返します。
		 *  間の辺が双方向辺だった場合は、mode の値にかかわらず true を返します。
		 *
		 *	\param[in]	mode	辺の向きを指定します。
		 *	\param[in]	node	接続を確認するノード。
		 *
		 *	\return	指定した方向への辺が存在する場合 true を、存在しない場合 false を返します。
		 */
		bool IsConnect(bool mode, fk_GraphNode^ node);

		//! 全接続辺取得関数1
		/*!
		 *	現在ノードに接続している全ての辺を取得します。
		 *
		 *	\return		接続辺の list 集合。
		 */
		property List<fk_GraphEdge^>^ AllEdge {
			List<fk_GraphEdge^>^ get();
		}

		//! 始点接続辺取得関数1
		/*!
		 *	現在ノードに接続している辺のうち、以下の条件に当てはまる辺を取得します。
		 *	- 双方向辺。
		 *	- 一方通行辺のうち、このノードが始点となっている辺。
		 *	.
		 *
		 *	\return		接続辺の list 集合。
		 */
		property List<fk_GraphEdge^>^ StartEdge {
			List<fk_GraphEdge^>^ get();
		}

		//! 終点接続辺取得関数1
		/*!
		 *	現在ノードに接続している辺のうち、以下の条件に当てはまる辺を取得します。
		 *	- 双方向辺。
		 *	- 一方通行辺のうち、このノードが終点となっている辺。
		 *	.
		 *
		 *	\return		接続辺の list 集合。
		 */
		property List<fk_GraphEdge^>^ EndEdge {
			List<fk_GraphEdge^>^ get();
		}

		property List<fk_GraphNode^>^ NextNode {
			List<fk_GraphNode^>^ get();
		}
		
		property List<fk_GraphNode^>^ PrevNode {
			List<fk_GraphNode^>^ get();
		}

		void SetIntCost(unsigned int ID, int value);
		void SetDoubleCost(unsigned int ID, double value);
		int GetIntCost(unsigned int ID);
		double GetDoubleCost(unsigned int ID);

		void ClearIntCost(void);
		void ClearIntCost(unsigned int ID);
		void ClearDoubleCost(void);
		void ClearDoubleCost(unsigned int ID);

		bool IsDoneIntCost(void);
		bool IsDoneIntCost(unsigned int ID);
		bool IsDoneDoubleCost(void);
		bool IsDoneDoubleCost(unsigned int ID);

		property fk_Color^ Color {
			void set(fk_Color^);
		}
	};
}

#endif