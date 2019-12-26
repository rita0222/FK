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

#ifndef __FK_GRAPH_HEADER__
#define __FK_GRAPH_HEADER__

#include <FK/GraphNode.h>
#include <FK/EdgePair.H>
#include <FK/IDAdmin.H>

namespace FK {

	//! グラフ構造を制御するクラス
	/*!
	 *	このクラスは、グラフ構造を制御する機能を提供します。
	 */

	class fk_Graph : public fk_Shape {

	public:

		//! コンストラクタ
		/*!
		 *	\param[in]	num		ノード数
		 */
		fk_Graph(unsigned int num);

		//! デストラクタ
		~fk_Graph();

		//! ノード数取得関数
		/*!
		 *	\return		ノード数
		 */
		unsigned int getNodeSize(void);

		//! 辺ID最大値取得関数
		/*!
		 *	\return		最大ID
		 */
		unsigned int getMaxEdgeID(void);

		//! ノード取得関数
		/*!
		 *	\param[in]	ID		ノード ID
		 *
		 *	\return		ノード
		 */
		fk_GraphNode * getNode(unsigned int ID);

		//! 辺情報取得関数
		/*!
		 *	\param[in]	ID		辺 ID
		 *
		 *	\return		辺情報
		 */
		fk_GraphEdge * getEdge(unsigned int ID);

		//!	辺生成関数
		/*!
		 *	\param[in]	mode	true の場合有向、false の場合無向となります。
		 *						辺が経路を表す場合は、有向辺は一方通行を表します。
		 *	\param[in]	v1		辺の始点となるノード。
		 *	\param[in]	v2		辺の終点となるノード。
		 */
		fk_GraphEdge * makeEdge(bool mode, fk_GraphNode *v1, fk_GraphNode *v2);

		//! 辺削除関数
		/*!
		 *
		 */
		bool deleteEdge(fk_GraphEdge *e);

		//! 辺存在確認関数
		/*!
		 *	\param[in]	v1		辺の頂点となるノード。
		 *	\param[in]	v2		辺の頂点となるノード。
		 *
		 *	\return		辺が存在する場合 true を、存在しない場合 false を返します。
		 */
		bool isConnect(fk_GraphNode *v1, fk_GraphNode *v2);

		void setCostMode(fk_CostType type, unsigned int costID = 0);
		void setCostMode(unsigned int tableID, fk_CostType type, unsigned int costID = 0);

		void setStart(fk_GraphNode *node);
		void setStart(unsigned int tableID, fk_GraphNode *node);

		void addGoal(fk_GraphNode *node);
		void addGoal(unsigned int tableID, fk_GraphNode *node);

		void makeCostTable(unsigned int tableID);
		
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Point * GetVertexShape(void);
		fk_Line * GetEdgeShape(void);
		void TablePrint(void);
		void CostPrint(fk_CostType, unsigned int);
#endif

	private:
		class fk_GraphCostTable {
		public:
			fk_GraphCostTable(void);
			~fk_GraphCostTable();
			
			fk_GraphNode *start;
			std::list<fk_GraphNode *> goal;
			fk_CostType type;
			unsigned int costID;
			std::list<fk_GraphNode *> waitList;

			std::string print(void);
		};

		fk_Point *nodeShape;
		fk_Line *edgeShape;
		fk_IDAdmin *edgeAdmin;

		std::vector<fk_GraphNode *>	node;
		std::vector<fk_GraphEdge *>	edge;

		std::vector<fk_GraphCostTable> table;
		void NodeResize(unsigned int);
	};
}


#endif
