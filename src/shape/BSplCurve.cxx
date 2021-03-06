﻿#define FK_DEF_SIZETYPE
#include <FK/BSplCurve.h>
#include <FK/BSplBase.H>

using namespace std;
using namespace FK;
using namespace FK::BSplBase;

fk_BSplCurve::Member::Member(void) :
	ord(3), num(0)
{
	return;
}

fk_BSplCurve::fk_BSplCurve(void) : _m(make_unique<Member>())
{
	SetObjectType(fk_Type::BSPLCURVE);
	init();
	return;
}

fk_BSplCurve::~fk_BSplCurve()
{
	_m_ctrlPos->clear();
	return;
}

void fk_BSplCurve::init(void)
{
	_m_ctrlPos->clear();
	_m->knotVec.clear();
	setOrdinate(3);
	setNum(3);
	return;
}

bool fk_BSplCurve::setOrdinate(int argOrd)
{
	if(argOrd < 3 || argOrd > 5) {
		return false;
	}

	_m->ord = argOrd;
	_m_ctrlPos->clear();
	_m->num = 0;

	return true;
}

bool fk_BSplCurve::setNum(int argNum)
{
	if(argNum < _m->ord) return false;
	_m->num = argNum;
	setCtrlSize(_m->num);
	_m_ctrlPos->resize(_m->num);
	UpdateKnot(_m->ord, _m->num, _m->knotVec);

	return true;
}

int fk_BSplCurve::getOrdinate(void)
{
	return _m->ord;
}

int fk_BSplCurve::getNum(void)
{
	return _m->num;
}

fk_Vector fk_BSplCurve::pos(double t)
{
	fk_Vector retPos(0.0, 0.0, 0.0);

	if(_m->num == 0) return retPos;
	for(int i = 0; i < _m->num; i++) {
		retPos += PosBasis(i, _m->ord, t, _m->knotVec) * _m_ctrlPos->getV(i);
	}
	return retPos;
}

fk_Vector fk_BSplCurve::diff(double t)
{
	fk_Vector retVec(0.0, 0.0, 0.0);

	if(_m->num == 0) return retVec;
	if(IsSame(t, 0.0)) {
		retVec = double(_m->ord-1) * (_m_ctrlPos->getV(1) - _m_ctrlPos->getV(0));
	} else if(IsSame(t, 1.0)) {
		retVec = double(_m->ord-1) * (_m_ctrlPos->getV(_m->num-1) - _m_ctrlPos->getV(_m->num-2));
	} else {
		for(int i = 0; i < _m->num; i++) {
			retVec += DiffBasis(i, _m->ord, t, _m->knotVec) * _m_ctrlPos->getV(i);
		}
	}

	return retVec;
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
