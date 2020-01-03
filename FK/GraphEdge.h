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

#ifndef __FK_GRAPH_EDGE_HEADER__
#define __FK_GRAPH_EDGE_HEADER__

#include <FK/Color.h>

namespace FK {

	class fk_GraphNode;
	class fk_Graph;

	enum class fk_CostType {
		INT,
		DOUBLE,
		LENGTH
	};

	enum class fk_CostDirection {
		FORWARD,
		BACK
	};

	//! グラフ構造の辺を制御するクラス
	/*!
	 *	このクラスは、グラフ構造における辺を制御する機能を提供します。
	 */
	class fk_GraphEdge {

	public:
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_GraphEdge(unsigned int, fk_GraphNode *, fk_GraphNode *, fk_Graph *);
		~fk_GraphEdge();
#endif

		//! ID 取得関数
		/*!
		 *	稜線の ID を取得します。
		 *
		 *	\return		ID
		 */
		unsigned int getID(void);

		//! ノード取得関数
		/*!
		 *	稜線の端点にあたるノードを取得します。
		 *
		 *	\param[in]	mode	true の場合始点を、false の場合終点を返します。
		 *
		 *	\return		端点ノード
		 */
		fk_GraphNode * getNode(bool mode);

		void setLengthMode(bool mode);
		bool getLengthMode(void);

		double getLength(void);
		
		//! 整数型コストID上限設定関数
		void setCostMaxID(fk_CostType type, unsigned int max);
		unsigned int getCostMaxID(fk_CostType type);

		//! 整数型コスト設定関数
		/*!
		 *
		 */
		void setIntCost(int cost);
		void setIntCost(unsigned int ID, int cost);

		void setDoubleCost(double cost);
		void setDoubleCost(unsigned int ID, double cost);

		int getIntCost(void);
		int getIntCost(unsigned int ID);

		double getDoubleCost(void);
		double getDoubleCost(unsigned int ID);

		void setColor(fk_Color col);
		void setColor(fk_Color *col);

	private:
		unsigned int edgeID;
		fk_GraphNode *node[2];
		unsigned int generation[2];

		bool lengthMode;
		double length;
		std::vector<int> intCost;
		std::vector<double> doubleCost;

		fk_Graph *baseGraph;

		void UpdateLength(void);
	};
}

#endif
