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

	fk_GraphEdge *e = new fk_GraphEdge(newID, argV1, argV2);
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

	V1 = *(argV1->getPosition());
	V2 = *(argV2->getPosition());

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

void fk_Graph::setCostMode(fk_CostType argType, bool argBackMode, unsigned int argCostID)
{
	setCostMode(0, argType, argBackMode, argCostID);
}

void fk_Graph::setCostMode(unsigned int argTableID, fk_CostType argType,
						   bool argBackMode, unsigned int argCostID)
{
	if(argTableID >= tableArray.size()) tableArray.resize(argTableID + 1);
	tableArray[argTableID].type = argType;
	tableArray[argTableID].costID = argCostID;
	tableArray[argTableID].backMode = argBackMode;
}

void fk_Graph::setStart(fk_GraphNode *argNode)
{
	setStart(0, argNode);
}

void fk_Graph::setStart(unsigned int argTableID, fk_GraphNode *argNode)
{
	if(argNode == nullptr) return;
	if(argNode->IsBase(this) == false) return;
	if(argTableID >= tableArray.size()) tableArray.resize(argTableID + 1);
	tableArray[argTableID].start = argNode;
}

void fk_Graph::addGoal(fk_GraphNode *argNode)
{
	addGoal(0, argNode);
}

void fk_Graph::addGoal(unsigned int argTableID, fk_GraphNode *argNode)
{
	if(argNode == nullptr) return;
	if(argNode->IsBase(this) == false) return;
	if(argTableID >= tableArray.size()) tableArray.resize(argTableID + 1);
	tableArray[argTableID].goal.push_back(argNode);
}

void fk_Graph::TablePrint(void)
{
	for(_st i = 0; i < tableArray.size(); ++i) {
		fk_Window::printf("Table[%d] : ", i);
		fk_Window::putString(tableArray[i].print());
	}
}		

fk_Graph::fk_GraphCostTable::fk_GraphCostTable(void)
{
	start = nullptr;
	goal.clear();
	type = fk_CostType::LENGTH;
	costID = 0;
	queueList.clear();
}

fk_Graph::fk_GraphCostTable::~fk_GraphCostTable()
{
}

bool fk_Graph::initCostTable(unsigned int argID)
{
	if(tableArray.size() <= argID) return false;
	fk_GraphCostTable *tbl = &tableArray[argID];
	if(tbl->start == nullptr) return false;
	if(tbl->backMode == true && tbl->goal.empty() == true) return false;

	list<fk_GraphNode *> *queue = &tbl->queueList;
	queue->clear();

	if(tbl->type == fk_CostType::INT) {
		for(auto node : nodeArray) node->clearIntCost(argID);
		if(tbl->backMode == true) {
			for(auto node : tbl->goal) {
				node->setIntCost(argID, 0);
				queue->push_back(node);
			}
		} else {
			tbl->start->setIntCost(argID, 0);
			queue->push_back(tbl->start);
		}
	} else {
		for(auto node : nodeArray) node->clearDoubleCost(argID);
		if(tbl->backMode == true) {
			for(auto node : tbl->goal) {
				node->setDoubleCost(argID, 0.0);
				queue->push_back(node);
			}
		} else {
			tbl->start->setDoubleCost(argID, 0.0);
			queue->push_back(tbl->start);
		}
	}

	return true;
}

fk_GraphCostStatus fk_Graph::updateCostTable(unsigned int argID)
{
	if(tableArray.size() <= argID) return fk_GraphCostStatus::ERROR;
	fk_GraphCostTable *tbl = &tableArray[argID];
	if(tbl->start == nullptr) return fk_GraphCostStatus::ERROR;
	if(tbl->backMode == true && tbl->goal.empty() == true) return fk_GraphCostStatus::ERROR;

	list<fk_GraphNode *> *queue = &tbl->queueList;

	if(queue->empty()) return fk_GraphCostStatus::FINISH;

	fk_GraphNode *cur = queue->front();
	queue->pop_front();

	list<fk_GraphEdge *> edgeList;
	if(tbl->backMode == true) {
		cur->getEndEdge(&edgeList);
	} else {
		cur->getStartEdge(&edgeList);
	}
		
	if(tbl->type == fk_CostType::INT) {
		for(fk_GraphEdge *edge : edgeList) IntUpdate(argID, tbl, edge, cur);
	} else {
		for(fk_GraphEdge *edge : edgeList) DoubleUpdate(argID, tbl, edge, cur);
	}
	if(queue->empty()) return fk_GraphCostStatus::FINISH;
	return fk_GraphCostStatus::CONTINUE;
}

void fk_Graph::IntUpdate(unsigned int argID,
						 fk_GraphCostTable *argTable,
						 fk_GraphEdge *argEdge,
						 fk_GraphNode *argNode)
{
	list<fk_GraphNode *> *queue = &argTable->queueList;

	fk_GraphNode *next = (argEdge->getNode(true) == argNode) ?
		argEdge->getNode(false) : argEdge->getNode(true);

	int cost = argNode->getIntCost(argID) + argEdge->getIntCost(argTable->costID);

	if(cost < next->getIntCost(argID) || next->isDoneIntCost(argID) == false) {
		next->setIntCost(argID, cost);
		auto p = queue->begin();
		if(p != queue->end()) {
			while(p != queue->end() && (*p)->getIntCost(argID) < cost) ++p;
			queue->insert(p, next);
		} else {
			queue->push_back(next);
		}
	}
}

void fk_Graph::DoubleUpdate(unsigned int argID,
							fk_GraphCostTable *argTable,
							fk_GraphEdge *argEdge,
							fk_GraphNode *argNode)
{
	list<fk_GraphNode *> *queue = &argTable->queueList;

	fk_GraphNode *next = (argEdge->getNode(true) == argNode) ?
		argEdge->getNode(false) : argEdge->getNode(true);

	double cost = (argTable->type == fk_CostType::DOUBLE) ?
		argNode->getDoubleCost(argID) + argEdge->getDoubleCost(argTable->costID) :
		argNode->getDoubleCost(argID) + argEdge->getLength();

	if(cost < next->getDoubleCost(argID) || next->isDoneDoubleCost(argID) == false) {
		next->setDoubleCost(argID, cost);
		auto p = queue->begin();
		if(p != queue->end()) {
			while(p != queue->end() && (*p)->getDoubleCost(argID) < cost) ++p;
			queue->insert(p, next);
		} else {
			queue->push_back(next);
		}
	}
}

	



void fk_Graph::CostPrint(fk_CostType argType, unsigned int argID)
{
	for(auto node : nodeArray) {
		if(argType == fk_CostType::INT) {
			fk_Window::printf("Node[%d] = %f", node->getID(), node->getIntCost(argID));
		} else {
			fk_Window::printf("Node[%d] = %f", node->getID(), node->getDoubleCost(argID));
		}
	}
}

string fk_Graph::fk_GraphCostTable::print(void)
{
	string outStr;

	outStr += "S = ";
	outStr += (start == nullptr) ? "NULL" : to_string(start->getID());
	outStr += + ",\n";
	outStr += "G =";
	for(auto n : goal) {
		outStr += " " + to_string(n->getID()) + ",";
	}
	outStr += "\n";
	outStr += "Type = ";
	switch(type)
	{
	  case fk_CostType::INT:
		outStr += "INT";
		break;

	  case fk_CostType::DOUBLE:
		outStr += "DOUBLE";
		break;

	  case fk_CostType::LENGTH:
		outStr += "LENGTH";
		break;

	  default:
		outStr += "NONE";
		break;
	}
	outStr += ",\n";
	outStr += "C = " + to_string(costID) + "\n";

	return outStr;
}
