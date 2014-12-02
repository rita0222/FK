/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#include <FK/Half.h>
#include <FK/Vertex.h>
#include <FK/Edge.h>
#include <FK/Loop.h>
#include <FK/Error.H>

using namespace std;

fk_Half::fk_Half(int argID)
{
	Init(argID);
}

fk_Half::~fk_Half()
{
	return;
}

fk_Half::fk_Half(const fk_Half &argHf)
	: fk_Topology()
{
	vertex = argHf.vertex;
	nextHalf = argHf.nextHalf;
	prevHalf = argHf.prevHalf;
	parentEdge = argHf.parentEdge;
	parentLoop = argHf.parentLoop;
}

void fk_Half::Init(int argID)
{
	InitTopology(argID, FK_HALF_TYPE);
	vertex = NULL;
	parentEdge = NULL;
	nextHalf = NULL;
	prevHalf = NULL;
	parentLoop = NULL;

	return;
}

fk_Vertex *fk_Half::getVertex(void) const
{
	return vertex;
}

fk_Half *fk_Half::getNextHalf(void) const
{
	return nextHalf;
}

fk_Half *fk_Half::getPrevHalf(void) const
{
	return prevHalf;
}

fk_Edge *fk_Half::getParentEdge(void) const
{
	return parentEdge;
}

fk_Loop *fk_Half::getParentLoop(void) const
{
	return parentLoop;
}

bool fk_Half::isLeft(void) const
{
	if(parentEdge != NULL) {
		if(parentEdge->getLeftHalf() == this) {
			return true;
		}
	}

	return false;
}

bool fk_Half::isRight(void) const
{
	if(parentEdge != NULL) {
		if(parentEdge->getRightHalf() == this) {
			return true;
		}
	}

	return false;
}

fk_Vertex *fk_Half::SetVertex(fk_Vertex *argVx)
{
	fk_Vertex *retVx = vertex;

	vertex = argVx;
	return retVx;
}

fk_Half *fk_Half::SetNextHalf(fk_Half *argHf)
{
	fk_Half *retHf = nextHalf;

	nextHalf = argHf;
	return retHf;
}

fk_Half *fk_Half::SetPrevHalf(fk_Half *argHf)
{
	fk_Half *retHf = prevHalf;

	prevHalf = argHf;
	return retHf;
}

fk_Edge *fk_Half::SetParentEdge(fk_Edge *argEd)
{
	fk_Edge *retEd = parentEdge;

	parentEdge = argEd;
	return retEd;
}

fk_Loop *fk_Half::SetParentLoop(fk_Loop *argLp)
{
	fk_Loop *retLp = parentLoop;

	parentLoop = argLp;
	return retLp;
}

void fk_Half::Print(void) const
{
	fk_Printf("Half[%d] = {", getID());
	fk_Printf("\tv = %d", vertex->getID());

	if(nextHalf == NULL) {
		fk_Printf("\tnH = NULL");
	} else {
		fk_Printf("\tnH = %d", nextHalf->getID());
	}

	if(prevHalf == NULL) {
		fk_Printf("\tpH = NULL");
	} else {
		fk_Printf("\tpH = %d", prevHalf->getID());
	}

	fk_Printf("\tpE = %d", parentEdge->getID());

	if(parentLoop == NULL) {
		fk_Printf("\tpL = NULL");
	} else {
		fk_Printf("\tpL = %d", parentLoop->getID());
	}

	fk_PutError("}");

	return;
}

bool fk_Half::Check(void) const
{
	bool	retBool = true;
	string	outStr;

	if(nextHalf != NULL) {
		if(nextHalf->getPrevHalf() != this) {
			outStr = fk_StrPrintf("Half[%d] ... next[%d] ERROR!!",
								  getID(), nextHalf->getID());
			fk_PutError("fk_Half", "Check", 1, outStr);
			retBool = false;
		}
	}

	if(prevHalf != NULL) {
		if(prevHalf->getNextHalf() != this) {
			outStr = fk_StrPrintf("Half[%d] ... prev[%d] ERROR!!",
								  getID(), prevHalf->getID());
			fk_PutError("fk_Half", "Check", 2, outStr);
			retBool = false;
		}
	}

	return retBool;
}

bool fk_Half::Compare(fk_Half *argH) const
{
	if(argH == NULL) return false;
	if(argH == this) return true;
	if(getID() != argH->getID()) return false;
	if(getID() == FK_UNDEFINED) return true;

	if(vertex->getID() != argH->vertex->getID()) return false;
	if(nextHalf->getID() != argH->nextHalf->getID()) return false;
	if(prevHalf->getID() != argH->prevHalf->getID()) return false;
	if(parentEdge->getID() != argH->parentEdge->getID()) return false;

	if(parentLoop == NULL && argH->parentLoop == NULL) {
		return true;
	} else if(parentLoop == NULL || argH->parentLoop == NULL) {
		return false;
	}
	if(parentLoop->getID() == argH->parentLoop->getID()) return true;
	return false;
}
