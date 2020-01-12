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

#define FK_DEF_SIZETYPE
#include <FK/Graph.h>
#include <FK/Window.h>

using namespace std;
using namespace FK;

fk_Graph::fk_Graph(unsigned int argNum)
{
	fk_Vector origin;

	realType = fk_RealShapeType::GRAPH;
	SetObjectType(fk_Type::GRAPH);
	nodeShape = new fk_Point();
	edgeShape = new fk_Line();
	edgeAdmin = new fk_IDAdmin(0);
	intCostMax = doubleCostMax = 0;
	NodeResize(argNum);
	for(unsigned int i = 0; i < argNum; ++i) nodeShape->pushVertex(origin);
	return;
}

fk_Graph::~fk_Graph()
{
	delete nodeShape;
	delete edgeShape;
	delete edgeAdmin;

	for(auto v : nodeArray) delete v;
	for(auto e : edgeArray) delete e;
	for(auto t : tableArray) delete t;
	return;
}

unsigned int fk_Graph::getNodeSize(void)
{
	return (unsigned int)nodeArray.size();
}

unsigned int fk_Graph::getMaxEdgeID(void)
{
	return (unsigned int)edgeAdmin->GetMaxID();
}
	
fk_GraphNode * fk_Graph::getNode(unsigned int argID)
{
	if(argID >= getNodeSize()) return nullptr;
	return nodeArray[argID];
}

bool fk_Graph::isConnect(fk_GraphNode *argV1, fk_GraphNode *argV2)
{
	if(argV1 == nullptr || argV2 == nullptr) return false;

	unsigned int ID1 = argV1->getID();
	unsigned int ID2 = argV2->getID();
	
	if(ID1 >= getNodeSize() || ID2 >= getNodeSize()) return false;

	return argV1->isConnect(argV2);
}

fk_GraphEdge * fk_Graph::makeEdge(bool argMode, fk_GraphNode *argV1, fk_GraphNode *argV2)
{
	if(argV1 == nullptr || argV2 == nullptr) return nullptr;

	unsigned int ID1 = argV1->getID();
	unsigned int ID2 = argV2->getID();

	if(ID1 >= getNodeSize() || ID2 >= getNodeSize()) return nullptr;

	unsigned int newID = (unsigned int)edgeAdmin->CreateID();

	fk_GraphEdge *e = new fk_GraphEdge(newID, argV1, argV2, this);
	fk_Vector V1, V2;

	if(newID == edgeArray.size()) {
		edgeArray.push_back(e);
		edgeShape->pushLine(V1, V2);
	} else {
		if(edgeArray[newID] != nullptr) delete edgeArray[newID];
		edgeArray[newID] = e;
	}

	argV1->ConnectEdge(argMode, e);
	argV2->ConnectEdge(argMode, e);

	V1 = argV1->getPosition();
	V2 = argV2->getPosition();

	edgeShape->changeLine(int(newID), V1, V2);
	edgeShape->setDrawMode(int(newID), true);
	return e;
}

fk_GraphEdge * fk_Graph::getEdge(unsigned int argID)
{
	if(argID >= edgeArray.size()) return nullptr;
	return edgeArray[argID];
}

fk_Point * fk_Graph::GetVertexShape(void)
{
	return nodeShape;
}

fk_Line * fk_Graph::GetEdgeShape(void)
{
	return edgeShape;
}

void fk_Graph::NodeResize(unsigned int argSize)
{
	unsigned int oldSize = (unsigned int)nodeArray.size();
	
	for(unsigned int i = argSize; i < oldSize; ++i) {
		delete nodeArray[i];
		nodeArray[i] = nullptr;
	}

	if(oldSize > argSize) nodeArray.resize(argSize);

	for(unsigned int i = oldSize; i < argSize; ++i) {
		nodeArray.push_back(new fk_GraphNode(i, this));
	}
}

bool fk_Graph::deleteEdge(fk_GraphEdge *argE)
{
	if(argE == nullptr) return false;
	if(argE != edgeArray[argE->getID()]) return false;
	unsigned int ID = argE->getID();

	auto v1 = argE->getNode(true);
	auto v2 = argE->getNode(false);
	if(v1->isConnect(v2) == false || v2->isConnect(v1) == false) return false;
	v1->DeleteEdge(argE);
	v2->DeleteEdge(argE);
	edgeAdmin->EraseID(int(ID));
	delete argE;
	edgeArray[ID] = nullptr;
	edgeShape->setDrawMode(int(ID), false);

	return true;
}

bool fk_Graph::TableReady(unsigned int argID)
{
	if(argID < tableArray.size()) {
		if(tableArray[argID] != nullptr) return false;
	}

	while(argID >= tableArray.size()) tableArray.push_back(nullptr);
	tableArray[argID] = new fk_CostTable();
	return true;
}

bool fk_Graph::makeCostTable(unsigned int argTableID, fk_CostType argType)
{
	if(TableReady(argTableID) == false) return false;
	fk_CostTable *table = tableArray[argTableID];

	table->setType(argType);
	if(argType == fk_CostType::INT) {
		table->setNodeCostID(intCostMax);
		++intCostMax;
	} else {
		table->setNodeCostID(doubleCostMax);
		++doubleCostMax;
	}
	return true;
}

bool fk_Graph::setCostDirection(unsigned int argTableID, fk_CostDirection argD)
{
	if(argTableID >= tableArray.size()) return false;
	if(tableArray[argTableID] == nullptr) return false;

	tableArray[argTableID]->setDirection(argD);
	return true;
}

bool fk_Graph::setEdgeCostID(unsigned int argTableID, unsigned int argEdgeID)
{
	if(argTableID >= tableArray.size()) return false;
	if(tableArray[argTableID] == nullptr) return false;

	tableArray[argTableID]->setEdgeCostID(argEdgeID);
	return true;
}

unsigned int fk_Graph::getNodeCostID(unsigned int argTableID)
{
	if(argTableID >= tableArray.size()) return 0;
	return tableArray[argTableID]->getNodeCostID();
}

void fk_Graph::setStart(unsigned int argTableID, fk_GraphNode *argNode)
{
	if(argNode == nullptr) return;
	if(argNode->IsBase(this) == false) return;
	TableReady(argTableID);
	tableArray[argTableID]->setStart(argNode);
}

void fk_Graph::addGoal(unsigned int argTableID, fk_GraphNode *argNode)
{
	if(argNode == nullptr) return;
	if(argNode->IsBase(this) == false) return;
	TableReady(argTableID);
	tableArray[argTableID]->addGoal(argNode);
}

void fk_Graph::TablePrint(void)
{
	for(_st i = 0; i < tableArray.size(); ++i) {
		if(tableArray[i] == nullptr) continue;
		fk_Window::putString("Table[" + to_string(i) + "] :");
		fk_Window::putString(tableArray[i]->print());
	}
}		

bool fk_Graph::initCostTable(unsigned int argID)
{
	if(tableArray.size() <= argID) return false;
	fk_CostTable *tbl = tableArray[argID];
	if(tbl == nullptr) return false;
	if(tbl->getStart() == nullptr) return false;
	if(tbl->getDirection() == fk_CostDirection::BACK && tbl->getGoal()->empty() == true) {
		return false;
	}

	tbl->queueClear();

	unsigned int costID = tbl->getNodeCostID();

	if(tbl->getType() == fk_CostType::INT) {
		for(auto node : nodeArray) node->clearIntCost(costID);
		if(tbl->getDirection() == fk_CostDirection::BACK) {
			for(auto node : *(tbl->getGoal())) {
				node->setIntCost(costID, 0);
				tbl->addQueue(node);
			}
		} else {
			tbl->getStart()->setIntCost(costID, 0);
			tbl->addQueue(tbl->getStart());
		}
	} else {
		for(auto node : nodeArray) node->clearDoubleCost(costID);
		if(tbl->getDirection() == fk_CostDirection::BACK) {
			for(auto node : *(tbl->getGoal())) {
				node->setDoubleCost(costID, 0.0);
				tbl->addQueue(node);
			}
		} else {
			tbl->getStart()->setDoubleCost(costID, 0.0);
			tbl->addQueue(tbl->getStart());
		}
	}

	return true;
}

fk_CostStatus fk_Graph::updateCostTable(unsigned int argID)
{
	fk_CostStatus status = getCostStatus(argID);
	if(status != fk_CostStatus::CONTINUE) return status;

	fk_CostTable *tbl = tableArray[argID];
	fk_GraphNode *cur = tbl->queuePopFront();

	list<fk_GraphEdge *> edgeList;
	if(tbl->getDirection() == fk_CostDirection::BACK) {
		cur->getEndEdge(&edgeList);
	} else {
		cur->getStartEdge(&edgeList);
	}
		
	if(tbl->getType() == fk_CostType::INT) {
		for(fk_GraphEdge *edge : edgeList) IntUpdate(tbl, edge, cur);
	} else {
		for(fk_GraphEdge *edge : edgeList) DoubleUpdate(tbl, edge, cur);
	}

	if(tbl->isQueueEmpty()) return fk_CostStatus::FINISH;

	return fk_CostStatus::CONTINUE;
}

void fk_Graph::IntUpdate(fk_CostTable *argTable,
						 fk_GraphEdge *argEdge, fk_GraphNode *argNode)
{
	unsigned int nodeID = argTable->getNodeCostID();
	unsigned int edgeID = argTable->getEdgeCostID();

	fk_GraphNode *next = (argEdge->getNode(true) == argNode) ?
		argEdge->getNode(false) : argEdge->getNode(true);

	int cost = argNode->getIntCost(nodeID) + argEdge->getIntCost(edgeID);

	if(cost < next->getIntCost(nodeID) || next->isDoneIntCost(nodeID) == false) {
		argTable->insertIntQueue(next, nodeID, cost);
	}
}

void fk_Graph::DoubleUpdate(fk_CostTable *argTable,
							fk_GraphEdge *argEdge, fk_GraphNode *argNode)
{
	unsigned int nodeID = argTable->getNodeCostID();
	unsigned int edgeID = argTable->getEdgeCostID();

	fk_GraphNode *next = (argEdge->getNode(true) == argNode) ?
		argEdge->getNode(false) : argEdge->getNode(true);

	double cost = (argTable->getType() == fk_CostType::DOUBLE) ?
		argNode->getDoubleCost(nodeID) + argEdge->getDoubleCost(edgeID) :
		argNode->getDoubleCost(nodeID) + argEdge->getLength();

	if(cost < next->getDoubleCost(nodeID) || next->isDoneDoubleCost(nodeID) == false) {
		argTable->insertDoubleQueue(next, nodeID, cost);
	}
}

list<fk_GraphNode *> fk_Graph::getOnePath(unsigned int argID)
{
	list<fk_GraphNode *> retList;

	retList.clear();
	getOnePath(argID, &retList);
	return retList;
}

void fk_Graph::getOnePath(unsigned int argID, list<fk_GraphNode *> *argList)
{
	if(argList == nullptr) return;
	if(getCostStatus(argID) != fk_CostStatus::FINISH) return;

	auto *tbl = tableArray[argID];
	auto nodeCostType = tbl->getType();
	auto nodeCostID = tbl->getNodeCostID();
	auto direction = tbl->getDirection();
	auto start = tbl->getStart();
	auto *goal = tbl->getGoal();

	if(start == nullptr) return;
	if(goal->empty()) return;

	switch(nodeCostType) {
	  case fk_CostType::INT:
		switch(direction) {
		  case fk_CostDirection::FORWARD:
			GetIntForwardPath(nodeCostID, start, goal, argList);
			break;

		  case fk_CostDirection::BACK:
			GetIntBackPath(nodeCostID, start, goal, argList);
			break;

		  default:
			break;
		}
		break;

	  case fk_CostType::DOUBLE:
	  case fk_CostType::LENGTH:
		switch(direction) {
		  case fk_CostDirection::FORWARD:
			GetDoubleForwardPath(nodeCostID, start, goal, argList);
			break;

		  case fk_CostDirection::BACK:
			GetDoubleBackPath(nodeCostID, start, goal, argList);
			break;

		  default:
			break;
		}
		break;
	}
	return;
}

void fk_Graph::GetDoubleForwardPath(unsigned int argCostID,
									fk_GraphNode *argStart,
									list<fk_GraphNode *> *argGoal,
									list<fk_GraphNode *> *argList)
{
	argList->clear();
	fk_GraphNode *trueGoal = GetTrueGoal(fk_CostType::DOUBLE, argCostID, argGoal);
	if(trueGoal == nullptr) return;

	fk_GraphNode *node = trueGoal;
	list<fk_GraphNode *> neighbor;

	while(node != nullptr) {
		argList->push_front(node);
		if(node == argStart) return;
		fk_GraphNode *nowNode = node;

		double curCost = node->getDoubleCost(argCostID);

		nowNode->getPrevNode(&neighbor);
		for(auto n : neighbor) {
			if(curCost > n->getDoubleCost(argCostID)) {
				node = n;
				curCost = n->getDoubleCost(argCostID);
			}
		}
		if(node == nowNode) return;
	}
	return;
}

void fk_Graph::GetDoubleBackPath(unsigned int argCostID,
								 fk_GraphNode *argStart,
								 list<fk_GraphNode *> *argGoal,
								 list<fk_GraphNode *> *argList)
{
	argList->clear();
	if(argStart->isDoneDoubleCost(argCostID) == false) return;

	fk_GraphNode *node = argStart;
	list<fk_GraphNode *> neighbor;

	while(node != nullptr) {
		argList->push_back(node);
		for(auto g : *argGoal) {
			if(node == g) return;
		}
		fk_GraphNode *nowNode = node;

		double curCost = node->getDoubleCost(argCostID);

		nowNode->getNextNode(&neighbor);
		for(auto n : neighbor) {
			if(curCost > n->getDoubleCost(argCostID)) {
				node = n;
				curCost = n->getDoubleCost(argCostID);
			}
		}
		if(node == nowNode) return;
	}
	return;
}

void fk_Graph::GetIntForwardPath(unsigned int argCostID,
								 fk_GraphNode *argStart,
								 list<fk_GraphNode *> *argGoal,
								 list<fk_GraphNode *> *argList)
{
	argList->clear();
	fk_GraphNode *trueGoal = GetTrueGoal(fk_CostType::INT, argCostID, argGoal);
	if(trueGoal == nullptr) return;

	fk_GraphNode *node = trueGoal;
	list<fk_GraphNode *> neighbor;

	while(node != nullptr) {
		argList->push_front(node);
		if(node == argStart) return;
		fk_GraphNode *nowNode = node;

		int curCost = node->getIntCost(argCostID);

		nowNode->getPrevNode(&neighbor);
		for(auto n : neighbor) {
			if(curCost > n->getIntCost(argCostID)) {
				node = n;
				curCost = n->getIntCost(argCostID);
			}
		}
		if(node == nowNode) return;
	}
	return;
}

void fk_Graph::GetIntBackPath(unsigned int argCostID,
							  fk_GraphNode *argStart,
							  list<fk_GraphNode *> *argGoal,
							  list<fk_GraphNode *> *argList)
{
	argList->clear();
	if(argStart->isDoneIntCost(argCostID) == false) return;

	fk_GraphNode *node = argStart;
	list<fk_GraphNode *> neighbor;

	while(node != nullptr) {
		argList->push_back(node);
		for(auto g : *argGoal) {
			if(node == g) return;
		}
		fk_GraphNode *nowNode = node;

		int curCost = node->getIntCost(argCostID);

		nowNode->getNextNode(&neighbor);
		for(auto n : neighbor) {
			if(curCost > n->getIntCost(argCostID)) {
				node = n;
				curCost = n->getIntCost(argCostID);
			}
		}
		if(node == nowNode) return;
	}
	return;
}

fk_GraphNode * fk_Graph::GetTrueGoal(fk_CostType argType,
									 unsigned int argID,
									 list<fk_GraphNode *> *argGoal)
{
	fk_GraphNode *trueGoal = nullptr;
	
	for(auto g : *argGoal) {
		switch(argType) {
		  case fk_CostType::INT:
			if(g->isDoneIntCost(argID) == false) continue;
			if(trueGoal == nullptr) {
				trueGoal = g;
			} else {
				if(trueGoal->getIntCost(argID) > g->getIntCost(argID)) {
					trueGoal = g;
				}
			}
			break;

		  case fk_CostType::DOUBLE:
		  case fk_CostType::LENGTH:
			if(g->isDoneDoubleCost(argID) == false) continue;
			if(trueGoal == nullptr) {
				trueGoal = g;
			} else {
				if(trueGoal->getDoubleCost(argID) > g->getDoubleCost(argID)) {
					trueGoal = g;
				}
			}
			break;

		  default:
			break;
		}
	}
	return trueGoal;
}

fk_CostStatus fk_Graph::getCostStatus(unsigned int argID)
{
	if(tableArray.size() <= argID) return fk_CostStatus::ERROR;
	fk_CostTable *tbl = tableArray[argID];
	if(tbl == nullptr) return fk_CostStatus::ERROR;
	if(tbl->getStart() == nullptr) return fk_CostStatus::ERROR;
	if(tbl->getDirection() == fk_CostDirection::BACK && tbl->getGoal()->empty() == true) {
		return fk_CostStatus::ERROR;
	}

	if(tbl->isQueueEmpty()) return fk_CostStatus::FINISH;
	return fk_CostStatus::CONTINUE;
}

void fk_Graph::CostPrint(unsigned int argID)
{
	if(argID >= tableArray.size()) return;
	if(tableArray[argID] == nullptr) return;

	fk_CostType type = tableArray[argID]->getType();
	unsigned int nodeID = tableArray[argID]->getNodeCostID();
	string str;
	
	for(auto node : nodeArray) {
		str = "Node[" + to_string(node->getID()) + "] = ";
		if(type == fk_CostType::INT) {
			str += to_string(node->getIntCost(nodeID));
		} else {
			str += to_string(node->getDoubleCost(nodeID));
		}
		fk_Window::putString(str);
	}
}

void fk_Graph::CostPrint(fk_CostType argType, unsigned int argID)
{
	string str;
	for(auto node : nodeArray) {
		str = "Node[" + to_string(node->getID()) + "] = ";
		if(argType == fk_CostType::INT) {
			str += to_string(node->getIntCost(argID));
		} else {
			str += to_string(node->getDoubleCost(argID));
		}
		fk_Window::putString(str);
	}
}
