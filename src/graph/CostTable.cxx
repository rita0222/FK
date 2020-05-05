#define FK_DEF_SIZETYPE
#include <FK/CostTable.H>
#include <FK/Window.h>

using namespace std;
using namespace FK;

fk_CostTable::Member::Member(void) :
	start(nullptr), type(fk_CostType::LENGTH),
	edgeCostID(0), nodeCostID(0), direction(fk_CostDirection::BACK)
{
	return;
}

fk_CostTable::fk_CostTable(void) : _m(make_unique<Member>())
{
	return;
}

fk_CostTable::~fk_CostTable()
{
	return;
}

void fk_CostTable::setType(fk_CostType argType)
{
	_m->type = argType;
}

void fk_CostTable::setDirection(fk_CostDirection argD)
{
	_m->direction = argD;
}

void fk_CostTable::setNodeCostID(unsigned int argID)
{
	_m->nodeCostID = argID;
}

void fk_CostTable::setEdgeCostID(unsigned int argID)
{
	_m->edgeCostID = argID;
}


fk_CostType fk_CostTable::getType(void)
{
	return _m->type;
}

fk_CostDirection fk_CostTable::getDirection(void)
{
	return _m->direction;
}

unsigned int fk_CostTable::getNodeCostID(void)
{
	return _m->nodeCostID;
}

unsigned int fk_CostTable::getEdgeCostID(void)
{
	return _m->edgeCostID;
}

void fk_CostTable::setStart(fk_GraphNode *argStart)
{
	_m->start = argStart;
}

fk_GraphNode * fk_CostTable::getStart(void)
{
	return _m->start;
}

void fk_CostTable::addGoal(fk_GraphNode *argGoal)
{
	_m->goal.push_back(argGoal);
}

void fk_CostTable::clearGoal(void)
{
	_m->goal.clear();
}

list<fk_GraphNode *> * fk_CostTable::getGoal(void)
{
	return &(_m->goal);
}

void fk_CostTable::queueClear(void)
{
	_m->queueList.clear();
}

void fk_CostTable::addQueue(fk_GraphNode *argNode)
{
	_m->queueList.push_back(argNode);
}

bool fk_CostTable::isQueueEmpty(void)
{
	return _m->queueList.empty();
}

fk_GraphNode * fk_CostTable::queuePopFront(void)
{
	if(_m->queueList.empty()) return nullptr;
	fk_GraphNode *ret = _m->queueList.front();
	_m->queueList.pop_front();
	return ret;
}

void fk_CostTable::insertIntQueue(fk_GraphNode *argNode, unsigned int argID, int argCost)
{
	argNode->setIntCost(argID, argCost);
	auto p = _m->queueList.begin();
	if(p != _m->queueList.end()) {
		while(p != _m->queueList.end() && (*p)->getIntCost(argID) < argCost) ++p;
		_m->queueList.insert(p, argNode);
	} else {
		_m->queueList.push_back(argNode);
	}
}

void fk_CostTable::insertDoubleQueue(fk_GraphNode *argNode, unsigned int argID, double argCost)
{
	argNode->setDoubleCost(argID, argCost);
	auto p = _m->queueList.begin();
	if(p != _m->queueList.end()) {
		while(p != _m->queueList.end() && (*p)->getDoubleCost(argID) < argCost) ++p;
		_m->queueList.insert(p, argNode);
	} else {
		_m->queueList.push_back(argNode);
	}
}

string fk_CostTable::print(void)
{
	string outStr;

	outStr += "S = ";
	outStr += (_m->start == nullptr) ? "NULL" : to_string(_m->start->getID());
	outStr += + ",\n";
	outStr += "G =";
	for(auto n : _m->goal) {
		outStr += " " + to_string(n->getID()) + ",";
	}
	outStr += "\n";
	outStr += "Type = ";
	switch(_m->type)
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
	outStr += "(nodeCost, edgeCost) = (";
	outStr += to_string(_m->nodeCostID) + ", " + to_string(_m->edgeCostID) + ")\n";

	return outStr;
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
