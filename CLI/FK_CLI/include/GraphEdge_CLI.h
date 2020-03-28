#pragma once

#include <FK/GraphEdge.h>
#include "Color_CLI.h"

namespace FK_CLI
{
    using namespace System::Collections::Generic;

    ref class fk_GraphNode;

    //! グラフ内コスト値の型を表す列挙型
						  public enum class fk_CostType {
							  INT,		//!<	整数型
							  DOUBLE,		//!<	実数型
							  LENGTH		//!<	辺長
						  };

	//! グラフ内コスト算出方向を表す列挙型
						   public enum class fk_CostDirection {
							   FORWARD,	//!< 出発ノードから開始
							   BACK		//!< 目標ノードから開始
						   };

	//! グラフ構造の辺を制御するクラス
	/*!
	 *	このクラスは、グラフ構造における辺を制御する機能を提供します。
	 *
	 *	グラフ構造の詳細および利用方法についての詳細は、
	 *	fk_Graph のマニュアルを参照して下さい。
	 *	ここでは、グラフの辺に関する情報に特化して解説します。
	 *
	 *	本クラスのインスタンスは fk_Graph::MakeEdge() で自動的に生成されるものであり、
	 *	FK 利用者が直接インスタンスを生成することはありません。
	 *
	 *	\sa fk_Graph, fk_GraphNode
	 */

	public ref class fk_GraphEdge : fk_BaseObject {
	internal:
		::FK::fk_GraphEdge * GetP(void);
		static ::FK::fk_CostType getCT(fk_CostType);
		static ::FK::fk_CostDirection getCD(fk_CostDirection);

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_GraphEdge(::FK::fk_GraphEdge *);
		~fk_GraphEdge();
		!fk_GraphEdge();
#endif

		//! ID 取得プロパティ
		/*!
		 *	稜線の ID を取得します。
		 *
		 *	\return		ID
		 */
		property unsigned int ID {
			unsigned int get();
		}

		//! 辺長利用モードプロパティ
		/*!
		 *	辺長利用モードを設定・参照します。
		 *	辺長利用モードを有効とした場合、辺長が辺のコストとして設定されます。
		 *	この場合、コストの型は double 型として扱われます。
		 *	両端のいずれかのノードが移動するなどして辺の長さが変更となった場合、
		 *	辺のコストは自動的に更新されます。
		 *	
		 *	true の場合辺長利用モードを有効とします。
		 *	false の場合無効とします。
		 *
		 *	\sa Length
		 */
		property bool LengthMode {
			bool get();
			void set(bool);
		}

		//! 辺長参照プロパティ
		/*!
		 *	現在の辺長を参照します。
		 *	なお、本関数は「辺長利用モード」の状態が有効、無効のいずれであっても利用可能です。
		 *
		 *	\sa LengthMode
		 */
		property double Length {
			double get();
		}
		
		//! 色指定プロパティ
		/*!
		 *	辺の色を指定します。
		 */
		property fk_Color^ Color {
			void set(fk_Color^);
		}

		//! ノード取得メソッド
		/*!
		 *	稜線の端点にあたるノードを取得します。
		 *
		 *	\param[in]	mode	true の場合始点を、false の場合終点を返します。
		 *
		 *	\return		端点ノード
		 */
		fk_GraphNode^ GetNode(bool mode);

		//! 整数型コスト設定メソッド
		/*!
		 *	辺の整数型コストを設定します。
		 *
		 *	\param[in]	ID		コスト ID
		 *	\param[in]	cost	コスト値
		 *
		 *	\sa GetIntCost(), SetDoubleCost()
		 */
		void SetIntCost(unsigned int ID, int cost);

		//! 実数型コスト設定メソッド
		/*!
		 *	辺の実数型コストを設定します。
		 *
		 *	\param[in]	ID		コスト ID
		 *	\param[in]	cost	コスト値
		 *
		 *	\sa GetDoubleCost(), SetDoubleCost(), SetIntCost()
		 */
		void SetDoubleCost(unsigned int ID, double cost);

		//! 整数型コスト参照メソッド
		/*!
		 *	辺の整数型コストを参照します。
		 *
		 *	\param[in]	ID		コスト ID
		 *
		 *	\return		辺コスト
		 *
		 *	\sa GetIntCost(), SetIntCost(), GetDoubleCost()
		 */
		int GetIntCost(unsigned int ID);

		//! 実数型コスト参照メソッド
		/*!
		 *	辺の実数型コストを参照します。
		 *
		 *	\param[in]	ID		コスト ID
		 *
		 *	\return		辺コスト
		 *
		 *	\sa GetDoubleCost(), SetDoubleCost(), GetIntCost()
		 */
		double GetDoubleCost(unsigned int ID);
	};
}

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
