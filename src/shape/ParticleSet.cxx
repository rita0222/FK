﻿#define FK_DEF_SIZETYPE
#include <FK/ParticleSet.h>
#include <FK/IDAdmin.H>
#include <FK/Point.h>

using namespace std;
using namespace FK;

fk_ParticleSet::Member::Member(unsigned int argMax) :
	pAdmin(make_unique<fk_IDAdmin>()), point(make_unique<fk_Point>()),
	count(0), allMode(false), indivMode(false), maxNum(argMax)
{
	return;
}

fk_ParticleSet::fk_ParticleSet(unsigned int argMax) :
	_m(make_unique<Member>(argMax))
{
	SetObjectType(fk_Type::PARTICLESET);
	_m->pAdmin->Init(0);

	genMethod = [](fk_Particle *){};
	allMethod = [](){};
	indivMethod = [](fk_Particle *){};

	return;
}

fk_ParticleSet::~fk_ParticleSet()
{
	return;
}

fk_Particle * fk_ParticleSet::newParticle(void)
{
	return newParticle(0.0, 0.0, 0.0);
}

fk_Particle * fk_ParticleSet::newParticle(double argX, double argY, double argZ)
{
	return newParticle(fk_Vector(argX, argY, argZ));
}

fk_Particle * fk_ParticleSet::newParticle(const fk_Vector &argPos)
{
	if(_m->maxNum <= (unsigned int)(_m->pAdmin->GetIDNum())) {
		return nullptr;
	}

	_st pID = _st(_m->pAdmin->CreateID());
	if(_m->pSet.size() == pID) {
		fk_Point *pShape = _m->point.get();
		_m->pSet.push_back(make_unique<fk_Particle>(pShape, pShape->pushVertex(argPos)));
	} else {
		_m->pSet[pID].get()->init();
	}

	genMethod(_m->pSet[pID].get());
	return _m->pSet[pID].get();
}

bool fk_ParticleSet::removeParticle(fk_Particle *argP)
{
	if(argP == nullptr) return false;
	return removeParticle(argP->getID());
}

bool fk_ParticleSet::removeParticle(int argID)
{
	if(_m->pAdmin->EraseID(argID) == false) return false;
	_m->pSet[_st(argID)]->setDrawMode(false);
	return true;
}

unsigned int fk_ParticleSet::getCount(void) const
{
	return _m->count;
}

fk_Particle * fk_ParticleSet::getParticle(int argID) const
{
	if(_m->pAdmin->ExistID(argID) == false) {
		return nullptr;
	}

	return _m->pSet[_st(argID)].get();
}

fk_Particle * fk_ParticleSet::getNextParticle(fk_Particle *argP) const
{
	if(argP == nullptr) {
		return getParticle(_m->pAdmin->GetNext(-1));
	}
	return getParticle(_m->pAdmin->GetNext(argP->getID()));
}

unsigned int fk_ParticleSet::getParticleNum(void) const
{
	return static_cast<unsigned int>(_m->pAdmin->GetIDNum());
}

void fk_ParticleSet::setMaxSize(unsigned int argSize)
{
	_m->maxNum = argSize;
	return;
}

unsigned int fk_ParticleSet::getMaxSize(void) const
{
	return _m->maxNum;
}

void fk_ParticleSet::setAllMode(bool argMode)
{
	_m->allMode = argMode;
	return;
}

bool fk_ParticleSet::getAllMode(void) const
{
	return _m->allMode;
}

void fk_ParticleSet::setIndivMode(bool argMode)
{
	_m->indivMode = argMode;
	return;
}

bool fk_ParticleSet::getIndivMode(void) const
{
	return _m->indivMode;
}

void fk_ParticleSet::handle(void)
{
	fk_Particle *p;

	if(_m->allMode == true) {
		allMethod();
	}

	if(_m->indivMode == true) {
		for(p = getNextParticle(nullptr); p != nullptr; p = getNextParticle(p)) {
			indivMethod(p);
		}
	}

	for(p = getNextParticle(nullptr); p != nullptr; p = getNextParticle(p)) {
		p->handle();
	}

	_m->count++;
	return;
}

fk_Shape * fk_ParticleSet::getShape(void) const
{
	return static_cast<fk_Shape *>(_m->point.get());
}

int fk_Particle::getColorID(void) const { return 0; }
void fk_Particle::setColorID(int) { return; }
void fk_ParticleSet::setColorPalette(int, const fk_Color &) { return; }
void fk_ParticleSet::setColorPalette(int, float, float, float) { return; }
void fk_ParticleSet::setColorPalette(int, double, double, double) { return; }

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
