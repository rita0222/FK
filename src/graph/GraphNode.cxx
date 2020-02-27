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

using namespace std;
using namespace FK;

fk_GraphNode::fk_GraphNode(unsigned int argID, fk_Graph *argGraph)
	: fk_BaseObject(fk_Type::GRAPHNODE), ID(argID), generation(0), baseGraph(argGraph)
{
	clearIntCost(0);
	clearDoubleCost(0);
	
	return;
}

fk_GraphNode::~fk_GraphNode()
{
	return;
}

unsigned int fk_GraphNode::getID(void)
{
	return ID;
}

void fk_GraphNode::setPosition(fk_Vector *argPos)
{
	setPosition(*argPos);
}

void fk_GraphNode::setPosition(fk_Vector argPos)
{
	baseGraph->GetVertexShape()->setVertex(int(ID), argPos);

	auto edgeShape = baseGraph->GetEdgeShape();
	for(auto e : edgeAll) {
		if(e->getNode(true) == this) {
			edgeShape->setVertex(int(e->getID()), 0, argPos);
		} else {
			edgeShape->setVertex(int(e->getID()), 1, argPos);
		}
	}
	++generation;
}


fk_Vector & fk_GraphNode::getPosition(void)
{
	return position;
}

unsigned int fk_GraphNode::getGeneration(void)
{
	return generation;
}

void fk_GraphNode::ConnectEdge(bool argMode, fk_GraphEdge *argEdge)
{
	edgeAll.push_back(argEdge);

	if(argMode == true) {
		edgeB.push_back(argEdge);
	} else {
		if(argEdge->getNode(true) == this) {
			edgeS.push_back(argEdge);
		} else {
			edgeE.push_back(argEdge);
		}
	}
	return;
}

void fk_GraphNode::DeleteEdge(fk_GraphEdge *argEdge)
{
	edgeAll.remove(argEdge);
	edgeB.remove(argEdge);
	edgeS.remove(argEdge);
	edgeE.remove(argEdge);
}

bool fk_GraphNode::isConnect(bool argMode, fk_GraphNode *argV)
{
	if(argV == nullptr) return false;
	if(this->baseGraph != argV->baseGraph) return false;

	for(auto e : edgeB) {
		if(e->getNode(true) == argV || e->getNode(false) == argV) return true;
	}

	if(argMode == true) {
		for(auto e : edgeS) {
			if(e->getNode(true) == argV || e->getNode(false) == argV) return true;
		}
	} else {
		for(auto e : edgeE) {
			if(e->getNode(true) == argV || e->getNode(false) == argV) return true;
		}
	}

	return false;
}

bool fk_GraphNode::isConnect(fk_GraphNode *argV)
{
	if(argV == nullptr) return false;
	if(this->baseGraph != argV->baseGraph) return false;

	for(auto e : edgeAll) {
		if(e->getNode(true) == argV || e->getNode(false) == argV) return true;
	}

	return false;
}

list<fk_GraphEdge *> fk_GraphNode::getAllEdge(void)
{
	return edgeAll;
}

void fk_GraphNode::getAllEdge(list<fk_GraphEdge *> *argList)
{
	if(argList == nullptr) return;
	argList->clear();
	copy(edgeAll.begin(), edgeAll.end(), back_inserter(*argList));
}

list<fk_GraphEdge *> fk_GraphNode::getStartEdge(void)
{
	list<fk_GraphEdge *> ret;

	copy(edgeS.begin(), edgeS.end(), back_inserter(ret));
	copy(edgeB.begin(), edgeB.end(), back_inserter(ret));
	return ret;
}

void fk_GraphNode::getStartEdge(list<fk_GraphEdge *> *argList)
{
	if(argList == nullptr) return;
	argList->clear();
	copy(edgeS.begin(), edgeS.end(), back_inserter(*argList));
	copy(edgeB.begin(), edgeB.end(), back_inserter(*argList));
}

list<fk_GraphEdge *> fk_GraphNode::getEndEdge(void)
{
	list<fk_GraphEdge *> ret;

	copy(edgeE.begin(), edgeE.end(), back_inserter(ret));
	copy(edgeB.begin(), edgeB.end(), back_inserter(ret));
	return ret;
}

void fk_GraphNode::getEndEdge(list<fk_GraphEdge *> *argList)
{
	if(argList == nullptr) return;
	argList->clear();
	copy(edgeE.begin(), edgeE.end(), back_inserter(*argList));
	copy(edgeB.begin(), edgeB.end(), back_inserter(*argList));
}

list<fk_GraphNode *> fk_GraphNode::getNextNode(void)
{
	list<fk_GraphNode *> ret;
	getNextNode(&ret);
	return ret;
}

void fk_GraphNode::getNextNode(list<fk_GraphNode *> *argList)
{
	if(argList == nullptr) return;
	argList->clear();

	for(auto e : edgeS) {
		argList->push_back(e->getNode(false));
	}

	for(auto e : edgeB) {
		if(e->getNode(true) == this) {
			argList->push_back(e->getNode(false));
		} else {
			argList->push_back(e->getNode(true));
		}
	}
}

list<fk_GraphNode *> fk_GraphNode::getPrevNode(void)
{
	list<fk_GraphNode *> ret;
	getPrevNode(&ret);
	return ret;
}

void fk_GraphNode::getPrevNode(list<fk_GraphNode *> *argList)
{
	if(argList == nullptr) return;
	argList->clear();

	for(auto e : edgeE) {
		argList->push_back(e->getNode(true));
	}

	for(auto e : edgeB) {
		if(e->getNode(true) == this) {
			argList->push_back(e->getNode(false));
		} else {
			argList->push_back(e->getNode(true));
		}
	}
}


void fk_GraphNode::clearIntCost(void)
{
	clearIntCost(0);
}

void fk_GraphNode::clearIntCost(unsigned int argID)
{
	if(intCost.size() <= argID) {
		_st cur = intCost.size();
		intCost.resize(_st(argID)+1);
		for(_st i = cur; i < intCost.size() - 1; ++i) {
			intCost[i] = {false, 0};
		}
	}
	intCost[argID] = {false, 0};
}

void fk_GraphNode::clearDoubleCost(void)
{
	clearDoubleCost(0);
}

void fk_GraphNode::clearDoubleCost(unsigned int argID)
{
	if(doubleCost.size() <= argID) {
		_st cur = doubleCost.size();
		doubleCost.resize(_st(argID)+1);
		for(_st i = cur; i < doubleCost.size() - 1; ++i) {
			doubleCost[i] = {false, 0.0};
		}
	}
	doubleCost[argID] = {false, 0.0};
}

bool fk_GraphNode::isDoneIntCost(void)
{
	return isDoneIntCost(0);
}

bool fk_GraphNode::isDoneIntCost(unsigned int argID)
{
	if(intCost.size() <= argID) clearIntCost(argID);
	return get<0>(intCost[argID]);
}

bool fk_GraphNode::isDoneDoubleCost(void)
{
	return isDoneDoubleCost(0);
}

bool fk_GraphNode::isDoneDoubleCost(unsigned int argID)
{
	if(doubleCost.size() <= argID) clearDoubleCost(argID);
	return get<0>(doubleCost[argID]);
}

void fk_GraphNode::setIntCost(unsigned int argID, int argValue)
{
	if(intCost.size() <= argID) clearIntCost(argID);
	intCost[argID] = {true, argValue};
}

void fk_GraphNode::setDoubleCost(unsigned int argID, double argValue)
{
	if(doubleCost.size() <= argID) clearDoubleCost(argID);
	doubleCost[argID] = {true, argValue};
}

int fk_GraphNode::getIntCost(unsigned int argID)
{
	if(intCost.size() <= argID) return 0;
	return get<1>(intCost[argID]);
}

double fk_GraphNode::getDoubleCost(unsigned int argID)
{
	if(doubleCost.size() <= argID) return 0.0;
	return get<1>(doubleCost[argID]);
}

bool fk_GraphNode::IsBase(fk_Graph *argBase)
{
	return (argBase == baseGraph);
}

void fk_GraphNode::setColor(fk_Color argC)
{
	baseGraph->GetVertexShape()->setColor(int(ID), argC);
}

void fk_GraphNode::setColor(fk_Color *argC)
{
	baseGraph->GetVertexShape()->setColor(int(ID), *argC);
}

string fk_GraphNode::print(void)
{
	string outStr;

	for(auto e : edgeB) {
		outStr += "B = (" + to_string(e->getID()) + ", ";
		outStr += to_string(e->getNode(true)->getID()) + ", ";
		outStr += to_string(e->getNode(false)->getID()) + ")\n";
	}
	
	for(auto e : edgeS) {
		outStr += "S = (" + to_string(e->getID()) + ", ";
		outStr += to_string(e->getNode(true)->getID()) + ", ";
		outStr += to_string(e->getNode(false)->getID()) + ")\n";
	}
	
	for(auto e : edgeE) {
		outStr += "E = (" + to_string(e->getID()) + ", ";
		outStr += to_string(e->getNode(true)->getID()) + ", ";
		outStr += to_string(e->getNode(false)->getID()) + ")\n";
	}
	
	return outStr;
}

