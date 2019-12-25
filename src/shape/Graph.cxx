﻿/****************************************************************************
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

fk_Graph::fk_Graph(int argNum)
{
	fk_Vector origin;

	realType = fk_RealShapeType::GRAPH;
	SetObjectType(fk_Type::GRAPH);
	nodeShape = new fk_Point();
	edgeShape = new fk_Line();
	edgeAdmin = new fk_IDAdmin(0);
	NodeResize(argNum);
	for(int i = 0; i < argNum; ++i) nodeShape->pushVertex(origin);
	return;
}

fk_Graph::~fk_Graph()
{
	delete nodeShape;
	delete edgeShape;
	delete edgeAdmin;

	for(auto v : node) delete v;
	for(auto e : edge) delete e;
	return;
}

int fk_Graph::getNodeSize(void)
{
	return int(node.size());
}

fk_GraphNode * fk_Graph::getNode(int argID)
{
	if(argID < 0 || argID >= getNodeSize()) return nullptr;
	return node[_st(argID)];
}

bool fk_Graph::isConnect(fk_GraphNode *argV1, fk_GraphNode *argV2)
{
	if(argV1 == nullptr || argV2 == nullptr) return false;

	int ID1 = argV1->getID();
	int ID2 = argV2->getID();

	if(ID1 < 0 || ID1 >= getNodeSize() || ID2 < 0 || ID2 >= getNodeSize()) return false;

	return argV1->isConnect(argV2);
}

fk_GraphEdge * fk_Graph::makeEdge(bool argMode, fk_GraphNode *argV1, fk_GraphNode *argV2)
{
	if(argV1 == nullptr || argV2 == nullptr) return nullptr;

	int ID1 = argV1->getID();
	int ID2 = argV2->getID();

	if(ID1 < 0 || ID1 >= getNodeSize() || ID2 < 0 || ID2 >= getNodeSize()) return nullptr;

	int newID = edgeAdmin->CreateID();

	fk_GraphEdge *e = new fk_GraphEdge(newID, argV1, argV2);
	fk_Vector V1, V2;

	if(newID == int(edge.size())) {
		edge.push_back(e);
		edgeShape->pushLine(V1, V2);
	} else {
		if(edge[_st(newID)] != nullptr) delete edge[_st(newID)];
		edge[_st(newID)] = e;
	}

	argV1->ConnectEdge(argMode, e);
	argV2->ConnectEdge(argMode, e);

	V1 = *(argV1->getPosition());
	V2 = *(argV2->getPosition());

	edgeShape->changeLine(newID, V1, V2);
	edgeShape->setDrawMode(newID, true);
	return e;
}

fk_GraphEdge * fk_Graph::getEdge(int argID)
{
	if(argID < 0 || argID >= int(edge.size())) return nullptr;
	return edge[_st(argID)];
}

fk_Point * fk_Graph::GetVertexShape(void)
{
	return nodeShape;
}

fk_Line * fk_Graph::GetEdgeShape(void)
{
	return edgeShape;
}

void fk_Graph::NodeResize(int argSize)
{
	int oldSize = int(node.size());
	
	for(_st i = _st(argSize); i < _st(oldSize); ++i) {
		delete node[i];
		node[i] = nullptr;
	}

	if(oldSize > argSize) node.resize(_st(argSize));

	for(int i = oldSize; i < argSize; ++i) {
		node.push_back(new fk_GraphNode(i, this));
	}
}

bool fk_Graph::deleteEdge(fk_GraphEdge *argE)
{
	if(argE == nullptr) return false;
	if(argE != edge[_st(argE->getID())]) return false;
	int ID = argE->getID();

	auto v1 = argE->getNode(true);
	auto v2 = argE->getNode(false);
	if(v1->isConnect(v2) == false || v2->isConnect(v1) == false) return false;
	v1->DeleteEdge(argE);
	v2->DeleteEdge(argE);
	edgeAdmin->EraseID(ID);
	delete argE;
	edge[_st(ID)] = nullptr;
	edgeShape->setDrawMode(ID, false);

	return true;
}
