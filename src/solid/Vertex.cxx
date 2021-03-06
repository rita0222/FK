﻿#define FK_DEF_SIZETYPE
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Loop.h>
#include <FK/Edge.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;
using namespace FK;

static const fk_Vector fk_VInitPos(0.0, 0.0, 0.0);

fk_Vertex::Member::Member(void) :
	normCalcFlag(false), normFailFlag(false), oneHalf(FK_UNDEFINED), size(-1.0)
{
	return;
}

fk_Vertex::fk_Vertex(int argID) : _m(make_shared<Member>())
{
	DB = nullptr;
	SetID(argID);

	return;
}

fk_Vertex::~fk_Vertex()
{
	return;
}

void fk_Vertex::Init(fk_DataBase *argDB, int argID)
{
	InitTopology(argDB, argID, fk_TopologyType::VERTEX);
	_m->oneHalf = FK_UNDEFINED;
	UndefNormal();
	_m->size = -1.0;

	return;
}

fk_Vector fk_Vertex::getPosition(void) const
{
	return _m->position;
}

fk_Vector * fk_Vertex::GetPositionP(void)
{
	return &_m->position;
}

void fk_Vertex::SetPosition(fk_Vector argPos)
{
	_m->position = argPos;

	return;
}

fk_Half * fk_Vertex::getOneHalf(void) const
{
	if(DB == nullptr) return nullptr;
	return DB->GetHData(_m->oneHalf);
}

void fk_Vertex::SetOneHalf(int argHalf)
{
	_m->oneHalf = argHalf;
}

void fk_Vertex::CalcNormal(void)
{
	fk_Vector tmpVec(0.0, 0.0, 1.0), tmpNormal(0.0, 0.0, 0.0);
	fk_Vector *tmpVector;
	fk_Half *startH, *curH, *mateH;
	fk_Edge *curE;
	vector<fk_Vector> VecArray;
	_st i;

	if(DB == nullptr) return;
	if(_m->normCalcFlag == true) return;
	if(_m->normFailFlag == true) return;

	if(_m->oneHalf == FK_UNDEFINED) {
		_m->normFailFlag = true;
		_m->normal.set(0.0, 0.0, 1.0);
		return;
	}

	curH = startH = DB->GetHData(_m->oneHalf);
	VecArray.clear();
	do {
		if(curH->getParentLoop() != nullptr) {
			tmpVector = curH->getParentLoop()->getNormal();
			if(tmpVector == nullptr) {
				_m->normFailFlag = true;
				_m->normal.set(0.0, 0.0, 1.0);
				return;
			}
			VecArray.push_back(*tmpVector);
		}
		curE = curH->getParentEdge();
		mateH = (curE->getRightHalf() == curH) ? curE->getLeftHalf() : curE->getRightHalf();

		if(mateH->getNextHalf() == nullptr) {
			_m->normFailFlag = true;
			tmpNormal = tmpVec;
			return;
		} else {
			curH = mateH->getNextHalf();
		}
	} while(curH != startH);

	if(VecArray.empty() == true) {
		_m->normFailFlag = true;
		_m->normal.set(0.0, 0.0, 1.0);
		return;
	}

	for(i = 0; i < VecArray.size(); i++) {
		tmpNormal += VecArray[i];
	}

	if(tmpNormal.normalize() == true) {
		_m->normCalcFlag = true;
		_m->normFailFlag = false;
		_m->normal = tmpNormal;

	} else {
		_m->normCalcFlag = false;
		_m->normFailFlag = true;
	}

	return;
}

fk_Vector fk_Vertex::getNormal(void)
{
	CalcNormal();
	return _m->normal;
}	 

fk_Vector * fk_Vertex::GetNormalP(void)
{
	CalcNormal();
	return &_m->normal;
}

void fk_Vertex::UndefNormal(void)
{
	_m->normCalcFlag = false;
	_m->normFailFlag = false;
	return;
}

void fk_Vertex::SetNormal(const fk_Vector &argVec)
{
	UndefNormal();
	_m->normal = argVec;
	if(_m->normal.normalize() == false) {
		_m->normFailFlag = true;
	} else {
		_m->normCalcFlag = true;
	}
	return;
}

double fk_Vertex::getDrawSize(void) const
{
	return _m->size;
}

void fk_Vertex::setDrawSize(double argSize)
{
	if(argSize < 0.0) {
		_m->size = -1.0;
	} else {
		_m->size = argSize;
	}
	return;
}

void fk_Vertex::Print(void) const
{
	stringstream	ss;

	ss << "Vertex[" << getID() << "] = {";
	ss << "\tpos = ";
	ss << "(" << _m->position.x << ", " << _m->position.y << ", " << _m->position.z << ")";
	
	if(_m->normCalcFlag == true) {
		ss << "\tnorm = (";
		ss << _m->normal.x << ", " << _m->normal.y << ", " << _m->normal.z << ")";
	} else {
		ss << "\tnorm = (nullptr)";
	}

	if(_m->oneHalf == FK_UNDEFINED) {
		ss << "\toneH = UNDEF";
	} else {
		ss << "\tpH = " << _m->oneHalf;
	}
	ss << "}";
	Error::Put(ss.str());

	return;
}

bool fk_Vertex::Check(void) const
{
	stringstream	ss;

	if(DB == nullptr) return false;
	if(_m->oneHalf != FK_UNDEFINED) {
		if(DB->GetHData(_m->oneHalf)->getVertex() != this) {
			ss << "Vertex[" << getID();
			ss << "] ... Half[" << _m->oneHalf;
			ss << "] ERROR";
			Error::Put("fk_Vertex", "Check", 1, ss.str());
			return false;
		}
	}

	return true;
}

bool fk_Vertex::Compare(fk_Vertex *argV) const
{
	if(argV == nullptr) return false;
	if(argV == this) return true;
	if(getID() != argV->getID()) return false;
	if(getID() == FK_UNDEFINED) return true;

	if(_m->position != argV->_m->position) return false;
	if(_m->oneHalf == FK_UNDEFINED && argV->_m->oneHalf == FK_UNDEFINED) {
		return true;
	} else if(_m->oneHalf == FK_UNDEFINED || argV->_m->oneHalf == FK_UNDEFINED) {
		return false;
	}

	if(_m->oneHalf == argV->_m->oneHalf) return true;
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
