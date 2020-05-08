#include <FK/Half.h>
#include <FK/Vertex.h>
#include <FK/Edge.h>
#include <FK/Loop.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;
using namespace FK;

fk_Half::Member::Member(void) :
	vertex(FK_UNDEFINED),
	nextHalf(FK_UNDEFINED),
	prevHalf(FK_UNDEFINED),
	parentEdge(FK_UNDEFINED),
	parentLoop(FK_UNDEFINED)
{
	return;
}

fk_Half::fk_Half(int argID) : _m(make_unique<Member>())
{
	DB = nullptr;
	SetID(argID);
}

fk_Half::~fk_Half()
{
	return;
}

fk_Half::fk_Half(const fk_Half &argHf) : fk_Topology()
{
	_m->vertex = argHf._m->vertex;
	_m->nextHalf = argHf._m->nextHalf;
	_m->prevHalf = argHf._m->prevHalf;
	_m->parentEdge = argHf._m->parentEdge;
	_m->parentLoop = argHf._m->parentLoop;
}

void fk_Half::Init(fk_DataBase *argDB, int argID)
{
	InitTopology(argDB, argID, fk_TopologyType::HALF);
	_m->vertex = FK_UNDEFINED;
	_m->parentEdge = FK_UNDEFINED;
	_m->nextHalf = FK_UNDEFINED;
	_m->prevHalf = FK_UNDEFINED;
	_m->parentLoop = FK_UNDEFINED;

	return;
}

fk_Vertex * fk_Half::getVertex(void) const
{
	if(DB == nullptr) return nullptr;
	return DB->GetVData(_m->vertex);
}

fk_Half * fk_Half::getNextHalf(void) const
{
	if(DB == nullptr) return nullptr;
	return DB->GetHData(_m->nextHalf);
}

fk_Half * fk_Half::getPrevHalf(void) const
{
	if(DB == nullptr) return nullptr;
	return DB->GetHData(_m->prevHalf);
}

fk_Edge * fk_Half::getParentEdge(void) const
{
	if(DB == nullptr) return nullptr;
	return DB->GetEData(_m->parentEdge);
}

fk_Loop * fk_Half::getParentLoop(void) const
{
	if(DB == nullptr) return nullptr;
	return DB->GetLData(_m->parentLoop);
}

bool fk_Half::isLeft(void) const
{
	if(DB == nullptr) return false;
	if(_m->parentEdge != FK_UNDEFINED) {
		if(DB->GetEData(_m->parentEdge)->getLeftHalf() == this) {
			return true;
		}
	}

	return false;
}

bool fk_Half::isRight(void) const
{
	if(DB == nullptr) return false;
	if(_m->parentEdge != FK_UNDEFINED) {
		if(DB->GetEData(_m->parentEdge)->getRightHalf() == this) {
			return true;
		}
	}

	return false;
}

int fk_Half::SetVertex(int argVx)
{
	int retVx = _m->vertex;
	_m->vertex = argVx;
	return retVx;
}

int fk_Half::SetNextHalf(int argHf)
{
	int retHf = _m->nextHalf;
	_m->nextHalf = argHf;
	return retHf;
}

int fk_Half::SetPrevHalf(int argHf)
{
	int retHf = _m->prevHalf;
	_m->prevHalf = argHf;
	return retHf;
}

int fk_Half::SetParentEdge(int argEd)
{
	int retEd = _m->parentEdge;
	_m->parentEdge = argEd;
	return retEd;
}

int fk_Half::SetParentLoop(int argLp)
{
	int retLp = _m->parentLoop;
	_m->parentLoop = argLp;
	return retLp;
}

void fk_Half::Print(void) const
{
	stringstream	ss;


	ss << "Half[" << getID() << "] = {";
	Error::Put(ss.str());
	ss.clear();
	
	ss << "\tv = " << _m->vertex;
	Error::Put(ss.str());
	ss.clear();

	if(_m->nextHalf == FK_UNDEFINED) {
		ss << "\tnH = UNDEF";
	} else {
		ss << "\tnH = " << _m->nextHalf;
	}
	Error::Put(ss.str());
	ss.clear();

	if(_m->prevHalf == FK_UNDEFINED) {
		ss << "\tpH = UNDEF";
	} else {
		ss << "\tpH = " << _m->prevHalf;
	}
	Error::Put(ss.str());
	ss.clear();

	ss << "\tpE = " << _m->parentEdge;
	Error::Put(ss.str());
	ss.clear();

	if(_m->parentLoop == FK_UNDEFINED) {
		ss << "\tpL = UNDEF";
	} else {
		ss << "\tpL = " << _m->parentLoop;
	}
	Error::Put(ss.str());
	ss.clear();

	Error::Put("}");

	return;
}

bool fk_Half::Check(void) const
{
	bool retBool = true;
	stringstream ss;
	
	if(DB == nullptr) return false;

	if(_m->nextHalf != FK_UNDEFINED) {
		if(DB->GetHData(_m->nextHalf)->getPrevHalf() != this) {
			ss << "Half[" << getID() << "] ... next[";
			ss << _m->nextHalf << "] ERROR!!";
			Error::Put("fk_Half", "Check", 1, ss.str());
			retBool = false;
		}
	}

	if(_m->prevHalf != FK_UNDEFINED) {
		if(DB->GetHData(_m->prevHalf)->getNextHalf() != this) {
			ss << "Half[" << getID() << "] ... prev[";
			ss << _m->prevHalf << "] ERROR!!";
			Error::Put("fk_Half", "Check", 2, ss.str());
			retBool = false;
		}
	}

	return retBool;
}

bool fk_Half::Compare(fk_Half *argH) const
{
	if(DB == nullptr) return false;
	if(argH == nullptr) return false;
	if(argH == this) return true;
	if(getID() != argH->getID()) return false;
	if(getID() == FK_UNDEFINED) return true;

	if(_m->vertex != argH->_m->vertex) return false;
	if(_m->nextHalf != argH->_m->nextHalf) return false;
	if(_m->prevHalf != argH->_m->prevHalf) return false;
	if(_m->parentEdge != argH->_m->parentEdge) return false;

	if(_m->parentLoop == FK_UNDEFINED && argH->_m->parentLoop == FK_UNDEFINED) {
		return true;
	} else if(_m->parentLoop == FK_UNDEFINED || argH->_m->parentLoop == FK_UNDEFINED) {
		return false;
	}
	if(_m->parentLoop == argH->_m->parentLoop) return true;
	return false;
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
