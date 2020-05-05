#define FK_DEF_SIZETYPE
#include <FK/Graph.h>

using namespace std;
using namespace FK;

fk_GraphEdge::Member::Member(unsigned int argEID, fk_Graph *argGraph) :
	edgeID(argEID), lengthMode(true), length(0.0), baseGraph(argGraph)
{
	return;
}

fk_GraphEdge::fk_GraphEdge(unsigned int argEID,
						   fk_GraphNode *argV1,
						   fk_GraphNode *argV2,
						   fk_Graph *argGraph) :
	fk_BaseObject(fk_Type::GRAPHEDGE), _m(make_unique<Member>(argEID, argGraph))
{
	_m->node[0] = argV1;
	_m->node[1] = argV2;

	_m->intCost.push_back(0);
	_m->doubleCost.push_back(0.0);
	_m->length = (_m->node[0]->getPosition() - _m->node[1]->getPosition()).dist();
	_m->generation[0] = _m->node[0]->getGeneration();
	_m->generation[1] = _m->node[1]->getGeneration();
}

fk_GraphEdge::~fk_GraphEdge()
{
	return;
}

unsigned int fk_GraphEdge::getID(void)
{
	return _m->edgeID;
}

fk_GraphNode * fk_GraphEdge::getNode(bool argMode)
{
	if(argMode == true) return _m->node[0];
	return _m->node[1];
}

void fk_GraphEdge::setLengthMode(bool argMode)
{
	_m->lengthMode = argMode;
}

bool fk_GraphEdge::getLengthMode(void)
{
	return _m->lengthMode;
}

void fk_GraphEdge::UpdateLength(void)
{
	if(_m->node[0]->getGeneration() != _m->generation[0] ||
	   _m->node[1]->getGeneration() != _m->generation[1]) {
		_m->length = (_m->node[0]->getPosition() - _m->node[1]->getPosition()).dist();
		_m->generation[0] = _m->node[0]->getGeneration();
		_m->generation[1] = _m->node[1]->getGeneration();
	}
}

double fk_GraphEdge::getLength(void)
{
	UpdateLength();
	return _m->length;
}

void fk_GraphEdge::setIntCost(unsigned int argID, int argCost)
{
	if(argID >= _m->intCost.size()) _m->intCost.resize(_st(argID)+1);
	_m->intCost[argID] = argCost;
}

void fk_GraphEdge::setDoubleCost(unsigned int argID, double argCost)
{
	if(argID >= _m->doubleCost.size()) _m->doubleCost.resize(_st(argID)+1);
	_m->doubleCost[argID] = argCost;
}

int fk_GraphEdge::getIntCost(unsigned int argID)
{
	if(argID >= _m->intCost.size()) return 0;
	return _m->intCost[argID];
}

double fk_GraphEdge::getDoubleCost(unsigned int argID)
{
	if(argID >= _m->doubleCost.size()) return 0.0;
	return _m->doubleCost[argID];
}

void fk_GraphEdge::setColor(fk_Color argC)
{
	_m->baseGraph->GetEdgeShape()->setColor(int(_m->edgeID), &argC);
}

void fk_GraphEdge::setColor(fk_Color *argC)
{
	if(argC == nullptr) return;
	_m->baseGraph->GetEdgeShape()->setColor(int(_m->edgeID), argC);
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
