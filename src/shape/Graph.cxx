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

using namespace std;
using namespace FK;

fk_Graph::fk_Graph(void)
{
	realType = fk_RealShapeType::GRAPH;
	SetObjectType(fk_Type::GRAPH);
	vertexShape = new fk_Point();
	edgeShape = new fk_Line();
	edgeAdmin = new fk_IDAdmin(0);
	return;
}

fk_Graph::~fk_Graph()
{
	delete vertexShape;
	delete edgeShape;
	delete edgeAdmin;

	return;
}

void fk_Graph::setNodeSize(int argSize)
{
	if(argSize < 0) return;

	if(argSize == 0) {
		node.clear();
		conS.clear();
		conE.clear();
	} else {
		node.resize(_st(argSize));
		conS.resize(_st(argSize));
		conE.resize(_st(argSize));
	}

	fk_Vector origin;

	while(argSize > vertexShape->getSize()) vertexShape->pushVertex(origin);
	for(int i = argSize; i < vertexShape->getSize(); ++i) vertexShape->removeVertex(i);

	return;
}

int fk_Graph::getNodeSize(void)
{
	return int(node.size());
}

void fk_Graph::setNodePosition(int argID, fk_Vector argPos)
{
	if(argID < 0 || argID >= getNodeSize()) return;
	node[_st(argID)] = argPos;
	vertexShape->setVertex(argID, argPos);

	for(auto &e : conS[_st(argID)]) edgeShape->setVertex(e.id[1], 0, argPos);
	for(auto &e : conE[_st(argID)]) edgeShape->setVertex(e.id[1], 1, argPos);
}

fk_Vector fk_Graph::getNodePosition(int argID)
{
	if(argID < 0 || argID >= getNodeSize()) return fk_Vector();
	return node[_st(argID)];
}

bool fk_Graph::isConnect(int argID1, int argID2)
{
	if(argID1 < 0 || argID1 >= getNodeSize() ||
	   argID2 < 0 || argID2 >= getNodeSize()) return false;

	for(fk_EdgePair e : conS[_st(argID1)]) {
		if(e.id[0] == argID2) return true;
	}

	for(fk_EdgePair e : conE[_st(argID1)]) {
		if(e.id[0] == argID2) return true;
	}

	return false;
}

int fk_Graph::makeEdge(int argID1, int argID2)
{
	if(argID1 < 0 || argID1 >= getNodeSize() ||
	   argID2 < 0 || argID2 >= getNodeSize()) return -2;

	if(isConnect(argID1, argID2)) return -1;
	
	int newID = edgeAdmin->CreateID();
	if(newID == int(edge.size())) edge.resize(_st(newID+1));
	edge[_st(newID)].set(argID1, argID2);

	conS[_st(argID1)].push_back(fk_EdgePair(argID2, newID));
	conE[_st(argID2)].push_back(fk_EdgePair(argID1, newID));

	edgeShape->pushLine(node[_st(argID1)], node[_st(argID2)]);

	return 0;
}

fk_EdgePair fk_Graph::getEdge(int argID)
{
	if(argID < 0 || argID >= int(edge.size())) {
		return fk_EdgePair();
	}

	return edge[_st(argID)];
}

fk_Point * fk_Graph::GetVertexShape(void)
{
	return vertexShape;
}

fk_Line * fk_Graph::GetEdgeShape(void)
{
	return edgeShape;
}
