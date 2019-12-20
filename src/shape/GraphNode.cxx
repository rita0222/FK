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
#include <FK/GraphNode.h>
#include <FK/Graph.h>

using namespace std;
using namespace FK;

fk_GraphNode::fk_GraphNode(int argID, fk_Graph *argGraph)
{
	ID = argID;
	baseGraph = argGraph;
	return;
}

fk_GraphNode::~fk_GraphNode()
{
	return;
}

int fk_GraphNode::getID(void)
{
	return ID;
}

void fk_GraphNode::setPosition(fk_Vector *argPos)
{
	position = *argPos;
	baseGraph->GetVertexShape()->setVertex(ID, position);

	auto edgeShape = baseGraph->GetEdgeShape();
	for(auto e : edgeAll) {
		if(e->getNode(true) == ID) {
			edgeShape->setVertex(e->getID(), 0, position);
		} else {
			edgeShape->setVertex(e->getID(), 1, position);
		}
	}
}

fk_Vector * fk_GraphNode::getPosition(void)
{
	return &position;
}

void fk_GraphNode::ConnectEdge(bool argMode, fk_GraphEdge *argEdge)
{
	edgeAll.push_back(argEdge);

	if(argMode == true) {
		edgeB.push_back(argEdge);
	} else {
		if(argEdge->getNode(true) == ID) {
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

bool fk_GraphNode::isConnect(bool argMode, int argID)
{
	for(auto e : edgeB) {
		if(e->getNode(true) == argID || e->getNode(false) == argID) return true;
	}

	if(argMode == true) {
		for(auto e : edgeS) {
			if(e->getNode(true) == argID || e->getNode(false) == argID) return true;
		}
	} else {
		for(auto e : edgeE) {
			if(e->getNode(true) == argID || e->getNode(false) == argID) return true;
		}
	}

	return false;
}

bool fk_GraphNode::isConnect(int argID)
{
	for(auto e : edgeAll) {
		if(e->getNode(true) == argID || e->getNode(false) == argID) return true;
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

	ret.splice(ret.end(), edgeE);
	ret.splice(ret.end(), edgeB);
	return ret;
}

void fk_GraphNode::getEndEdge(list<fk_GraphEdge *> *argList)
{
	if(argList == nullptr) return;
	argList->clear();
	copy(edgeE.begin(), edgeE.end(), back_inserter(*argList));
	copy(edgeB.begin(), edgeB.end(), back_inserter(*argList));
}

string fk_GraphNode::print(void)
{
	string outStr;

	for(auto e : edgeB) {
		outStr += "B = (" + to_string(e->getID()) + ", ";
		outStr += to_string(e->getNode(true)) + ", ";
		outStr += to_string(e->getNode(false)) + ")\n";
	}
	
	for(auto e : edgeS) {
		outStr += "S = (" + to_string(e->getID()) + ", ";
		outStr += to_string(e->getNode(true)) + ", ";
		outStr += to_string(e->getNode(false)) + ")\n";
	}
	
	for(auto e : edgeE) {
		outStr += "E = (" + to_string(e->getID()) + ", ";
		outStr += to_string(e->getNode(true)) + ", ";
		outStr += to_string(e->getNode(false)) + ")\n";
	}
	
	return outStr;
}
