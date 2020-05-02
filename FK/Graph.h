#ifndef __FK_GRAPH_HEADER__
#define __FK_GRAPH_HEADER__

#include <FK/CostTable.H>
#include <FK/IDAdmin.H>

namespace FK {

	//! グラフのコスト算出状況を表す列挙型
	enum class fk_CostStatus {
		CONTINUE,	//!<	途中段階状態
		FINISH,		//!<	完了状態
		ERROR		//!<	エラー
	};

	//! グラフ構造を制御するクラス
	/*!
	 *	このクラスは、グラフ構造を制御する機能を提供します。
	 *	グラフ構造には多くの応用用途がありますが、
	 *	本クラスではその中でも経路探索を念頭に置いた機能を多く提供しています。
	 *
	 *	グラフ構造は、「ノード」と「辺」の2種類の要素によって構成されます。
	 *	ノードは任意の位置を持つ頂点集合であり、
	 *	辺は任意の2点を接続する線分です。
	 *	辺は無向線分としても有向線分としても考えることができ、
	 *	経路としてとらえると無向線分は両通行経路、有向線分は一方通行経路となります。
	 *
	 *	ノードを表すクラスは fk_GraphNode, 辺を表すクラスは fk_GraphEdge であり、
	 *	これらのクラスの機能も合わせて利用します。
	 *
	 *	fk_Graph のノードと辺は、「コスト」を格納することができます。
	 *	グラフ内の全要素のコストをまとめて「コストテーブル」と呼びます。
	 *	コストテーブルは、経路探索アルゴリズムで重要なデータであり、
	 *	fk_Graph はコストを扱うために有用な機能を多く提供しています。
	 *
	 *	コストテーブルは、int 型と double 型のいずれかを選択でき、
	 *	かつ両方の型それぞれで複数のコストテーブルを格納することができます。
	 *	各コストテーブルは ID により管理します。
	 *
	 *	\sa fk_GraphNode, fk_GraphEdge
	 */
	class fk_Graph : public fk_Shape {

	public:

		//! コンストラクタ
		/*!
		 *	初期値として、ノード数を設定します。
		 *	fk_Graph ではノード数は固定であるため、
		 *	利用する際に十分な数のノードを確保しておく必要があります。
		 *
		 *	\param[in]	num		ノード数
		 */
		fk_Graph(unsigned int num);

		//! デストラクタ
		~fk_Graph();

		//! \name 情報参照関数
		///@{

		//! ノード数取得関数
		/*!
		 *	グラフ内に存在するノード数を取得します。
		 *
		 *	\return		ノード数
		 */
		unsigned int getNodeSize(void);

		//! 辺ID最大値取得関数
		/*!
		 *	現在存在する辺の ID の最大値を取得します。
		 *
		 *	\return		最大ID
		 */
		unsigned int getMaxEdgeID(void);

		//! ノード取得関数
		/*!
		 *	ノードを表すインスタンスを ID より取得します。
		 *
		 *	\param[in]	ID		ノード ID
		 *
		 *	\return		ノード
		 */
		fk_GraphNode * getNode(unsigned int ID);

		//! 辺情報取得関数
		/*!
		 *	辺を表すインスタンスを ID より取得します。
		 *
		 *	\param[in]	ID		辺 ID
		 *
		 *	\return		辺情報
		 */
		fk_GraphEdge * getEdge(unsigned int ID);

		//! 辺存在確認関数
		/*!
		 *	2つのノードの間に辺が存在するかどうかを判定します。
		 *	なお、ノード間の辺は複数存在する場合もあり、2本以上存在する場合も true を返します。
		 *
		 *	\param[in]	v1		辺の端点となるノード。
		 *	\param[in]	v2		辺の端点となるノード。
		 *
		 *	\return		辺が存在する場合 true を、存在しない場合 false を返します。
		 */
		bool isConnect(fk_GraphNode *v1, fk_GraphNode *v2);

		///@}

		//! \name 接続変更関数
		///@{

		//!	辺生成関数
		/*!
		 *	2点のノード間に辺を作成します。
		 *	なお、既に2点間に辺が存在する場合でも、エラーとならずに新たに辺を追加生成します。
		 *
		 *	\param[in]	mode	true の場合有向、false の場合無向となります。
		 *						辺が経路を表す場合は、有向辺は一方通行を表します。
		 *	\param[in]	v1		辺の始点となるノード。
		 *	\param[in]	v2		辺の終点となるノード。
		 *
		 *	\return
		 *			接続した辺のインスタンスを返します。
		 *			作成に失敗した場合は nullptr を返します。
		 */
		fk_GraphEdge * makeEdge(bool mode, fk_GraphNode *v1, fk_GraphNode *v2);

		//! 辺削除関数
		/*!
		 *	辺を削除します。
		 *
		 *	\param[in]	e		削除する辺のインスタンス
		 *
		 *	\return		削除に成功した場合 true を、失敗した場合 false を返します。
		 */
		bool deleteEdge(fk_GraphEdge *e);

		///@}

		//! \name 経路コスト制御関数
		///@{

		//! コストテーブル生成関数
		/*!
		 *	コストテーブルを作成します。作成の際には ID を指定します。
		 *	指定した ID で既に作成済であった場合は false を返し、初期化は行いません。
		 *
		 *	\param[in]	tableID		コストテーブル ID
		 *
		 *	\param[in]	type		コスト値のタイプを設定します。
		 *							- fk_CostType::INT \n
		 *								コストが int 型となります。
		 *							- fk_CostType::DOUBLE \n
		 *								コストが double 型となります。
		 *							- fk_CostType::LENGTH \n
		 *								コストは辺の長さとなり、
		 *								内部では double 型として扱われます。
		 *							.
		 *
		 *	\return		作成に成功すれば true を、失敗すれば false を返します。
		 */
		bool makeCostTable(unsigned int tableID, fk_CostType type);

		//! コスト算出方向指定関数
		/*!
		 *	コストの算出方向を指定します。
		 *
		 *	\param[in]	tableID		コストテーブルID
		 *
		 *	\param[in]	direction	コストを出発ノード側から算出する場合は
		 *							fk_CostDirection::FORWARD を指定します。
		 *							コストを目標ノード側から算出する場合は
		 *							fk_CostDirection::BACK を指定します。
		 *
		 *	\return		設定に成功すれば true を、失敗すれば false を返します。
		 */
		bool setCostDirection(unsigned int tableID, fk_CostDirection direction);

		//! 辺コストID対応指定関数
		/*!
		 *	コストテーブルに対し、コスト値算出に利用する辺のコストIDを指定します。
		 *
		 *	\param[in]	tableID		コストテーブルID
		 *
		 *	\param[in]	edgeCostID 	利用する辺のコスト値 ID を指定します。
		 *							makeCostTable() の第2引数に
		 *							fk_CostType::LENGTH を指定していた場合、
		 *							この値は無視されます。
		 */
		bool setEdgeCostID(unsigned int tableID, unsigned int edgeCostID);

		//! ノード内コストID参照関数
		/*!
		 *	コストテーブルに対応するノード内コストIDを参照します。
		 *
		 *	\param[in]	tableID		コストテーブルID
		 *
		 *	\return		ノード内コストID
		 */
		unsigned int getNodeCostID(unsigned int tableID);

		//! 出発ノード設定関数
		/*!
		 *	経路探索における出発ノードを指定します。
		 *	既に別の出発ノードが設定されていた場合は、新たに設定したノードに更新されます。
		 *
		 *	\param[in]	tableID		コストテーブルID
		 *	\param[in]	node		ノードインスタンス
		 */
		void setStart(unsigned int tableID, fk_GraphNode *node);

		//! 目標ノード追加関数
		/*!
		 *	経路探索における目標ノードを追加します。
		 *	目標ノードは一つのコストテーブルに対し複数設定することができます。
		 *
		 *	\param[in]	tableID		コストテーブルID
		 *	\param[in]	node		目標ノードインスタンス
		 */
		void addGoal(unsigned int tableID, fk_GraphNode *node);

		//! コストテーブル初期化関数
		/*!
		 *	コストテーブルを初期化します。
		 *
		 *	\param[in]	tableID		コストテーブルID
		 *
		 *	\return		初期化に成功したら true を、失敗したら false を返します。
		 *				setCostMode() による設定が行われていないコストテーブルだった場合は
		 *				false を返します。
		 */
		bool initCostTable(unsigned int tableID);

		//! コストテーブル更新関数
		/*!
		 *	各ノードに対し、コスト算出を一段階進めます。
		 *	全てのノードのコスト値を完全にするには、
		 *	fk_CostStatus::FINISH が返されるまで繰り返し本関数を呼び出す必要があります。
		 *
		 *	\param[in]	tableID		コストテーブルID
		 *
		 *	\return		現在のコスト算出状況を返します。
		 *				- fk_CostStatus::CONTINUE \n
		 *					コスト算出がまだ途中段階であることを意味します。
		 *				- fk_CostStatus::FINISH \n
		 *					コスト算出が完了したことを意味します。
		 *				- fk_CostStatus::ERROR \n
		 *					グラフ内のコスト算出に関する情報が不完全であることを意味します。
		 */
		fk_CostStatus updateCostTable(unsigned int tableID);

		//! コストテーブル状態取得関数
		/*!
		 *	現在のコストテーブルにおける更新情報を取得します。
		 *	updateCostTable() では実際にコストテーブルの更新処理を行いますが、
		 *	本関数は更新処理は行わず状態のみを取得します。
		 *
		 *	\param[in]	tableID		コストテーブルID
		 *
		 *	\return		現在のコスト算出状況を返します。
		 *				- fk_CostStatus::CONTINUE \n
		 *					コスト算出がまだ途中段階であることを意味します。
		 *				- fk_CostStatus::FINISH \n
		 *					コスト算出が完了したことを意味します。
		 *				- fk_CostStatus::ERROR \n
		 *					グラフ内のコスト算出に関する情報が不完全であることを意味します。
		 */
		fk_CostStatus getCostStatus(unsigned int tableID);

		//! 最短経路取得関数1
		/*!
		 *	コストテーブルに基づいた、出発ノードから目標ノードまでの最短経路を取得します。
		 *	本関数を用いる際には、事前にコストテーブルの更新が完了し、
		 *	getCostStatus() による結果が fk_CostStatus::FINISH となる状況でなければなりません。
		 *
		 *	最短経路が複数存在するような場合、任意の1種類のみを取得します。
		 *	現状では全ての最短経路を取得する機能は提供していません。
		 *
		 *	目標ノードが複数ある場合、そのうち出発ノードからもっとも経路が短いものが抽出されます。
		 *
		 *	本関数は STL コンテナを直接返すため、
		 *	経路情報が大きい場合はコピーの演算コストが増大します。
		 *	速度を重視する場合は getOnePath(unsigned int, std::list<fk_GraphNode *> *)
		 *	の利用を推奨します。
		 *
		 *	\param[in]	tableID		経路探索に用いる コストテーブルの ID
		 *
		 *	\return		最短経路の経由地となるノードを経路順に格納したリストを返します。
		 */
		std::list<fk_GraphNode *> getOnePath(unsigned int tableID);

		//! 最短経路取得関数2
		/*!
		 *	コストテーブルに基づいた、出発ノードから目標ノードまでの最短経路を取得します。
		 *	本関数を用いる際には、事前にコストテーブルの更新が完了し、
		 *	getCostStatus() による結果が fk_CostStatus::FINISH となる状況でなければなりません。
		 *
		 *	最短経路が複数存在するような場合、任意の1種類のみを取得します。
		 *	現状では全ての最短経路を取得する機能は提供していません。
		 *
		 *	目標ノードが複数ある場合、そのうち出発ノードからもっとも経路が短いものが抽出されます。
		 *
		 *	\param[in]	tableID		経路探索に用いる コストテーブルの ID
		 *	\param[out]	nodeList	最短経路の経由地となるノードを、経路順に格納します。
		 */
		void getOnePath(unsigned int tableID, std::list<fk_GraphNode *> *nodeList);

		///@}
		
#ifndef FK_DOXYGEN_USER_PROCESS
		fk_Point * GetVertexShape(void);
		fk_Line * GetEdgeShape(void);
		void TablePrint(void);
		void CostPrint(unsigned int);
		void CostPrint(fk_CostType, unsigned int);
#endif

	private:
		std::unique_ptr<fk_Point> nodeShape;
		std::unique_ptr<fk_Line> edgeShape;
		std::unique_ptr<fk_IDAdmin> edgeAdmin;

		std::vector<std::unique_ptr<fk_GraphNode>> nodeArray;
		std::vector<std::unique_ptr<fk_GraphEdge>> edgeArray;
		std::vector<std::unique_ptr<fk_CostTable>> tableArray;

		unsigned int intCostMax, doubleCostMax;

		void NodeResize(unsigned int);
		bool TableReady(unsigned int);
		void DoubleUpdate(fk_CostTable *, fk_GraphEdge *, fk_GraphNode *);
		void IntUpdate(fk_CostTable *, fk_GraphEdge *, fk_GraphNode *);

		void GetIntForwardPath(unsigned int, fk_GraphNode *,
							   std::list<fk_GraphNode *> *, std::list<fk_GraphNode *> *);
		void GetIntBackPath(unsigned int, fk_GraphNode *,
							std::list<fk_GraphNode *> *, std::list<fk_GraphNode *> *);
		void GetDoubleForwardPath(unsigned int, fk_GraphNode *,
								  std::list<fk_GraphNode *> *, std::list<fk_GraphNode *> *);
		void GetDoubleBackPath(unsigned int, fk_GraphNode *,
							   std::list<fk_GraphNode *> *, std::list<fk_GraphNode *> *);
		fk_GraphNode * GetTrueGoal(fk_CostType, unsigned int, std::list<fk_GraphNode *> *);

	};
}


#endif

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
