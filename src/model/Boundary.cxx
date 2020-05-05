#include <FK/Model.h>

using namespace FK;
using namespace std;

fk_Boundary::Member::Member(void) :
	bMode(fk_BoundaryMode::NONE), bDrawToggle(false),
	bLineWidth(1.0), bSphereRad(0.0), bCapRad(0.0)
{
	return;
}

fk_Boundary::fk_Boundary(fk_Type argType)
	: fk_MatrixAdmin(argType), _m(make_unique<Member>())
{
	return;
}

fk_Boundary::~fk_Boundary()
{
	return;
}

void fk_Boundary::setSphere(double argRadius)
{
	if(argRadius <= 0.0) {
		_m->bSphereRad = 0.0;
	} else {
		_m->bSphereRad = argRadius;
	}

	if(_m->bSphere == nullptr) {
		_m->bSphere = make_unique<fk_IndexFaceSet>();
		_m->bSphere->makeSphere(4, _m->bSphereRad);
	} else {
		_m->bSphere->setSphereRadius(_m->bSphereRad);
	}

	return;
}

double fk_Boundary::getSphere(void)
{
	return _m->bSphereRad;
}

void fk_Boundary::setAABBSize(double argX, double argY, double argZ)
{
	if(_m->bAABBSize == nullptr) {
		_m->bAABBSize = make_unique<fk_Vector>(argX, argY, argZ);
	} else {
		_m->bAABBSize->set(argX, argY, argZ);
	}

	if(_m->bAABB == nullptr) {
		_m->bAABB = make_unique<fk_IndexFaceSet>();
		_m->bAABB->makeBlock(argX, argY, argZ);
	} else {
		_m->bAABB->setBlockSize(argX, argY, argZ);
	}

	return;
}

void fk_Boundary::setAABBSize(fk_Vector argV)
{
	setAABBSize(argV.x, argV.y, argV.z);
	return;
}

fk_Vector fk_Boundary::getAABBSize(void)
{
	if(_m->bAABBSize == nullptr) return fk_Vector(0.0, 0.0, 0.0);
	return (*(_m->bAABBSize));
}

void fk_Boundary::setOBBSize(double argX, double argY, double argZ)
{
	if(_m->bOBBSize == nullptr) {
		_m->bOBBSize = make_unique<fk_Vector>(argX, argY, argZ);
	} else {
		_m->bOBBSize->set(argX, argY, argZ);
	}

	if(_m->bOBB == nullptr) {
		_m->bOBB = make_unique<fk_IndexFaceSet>();
		_m->bOBB->makeBlock(argX, argY, argZ);
	} else {
		_m->bOBB->setBlockSize(argX, argY, argZ);
	}

	return;
}

void fk_Boundary::setOBBSize(fk_Vector argV)
{
	setOBBSize(argV.x, argV.y, argV.z);
	return;
}

fk_Vector fk_Boundary::getOBBSize(void)
{
	if(_m->bOBBSize == nullptr) return fk_Vector(0.0, 0.0, 0.0);
	return (*(_m->bOBBSize));
}

void fk_Boundary::setCapsule(fk_Vector argS, fk_Vector argE, double argRad)
{
	fk_Vector	vec;
	
	if(_m->bCapSPos == nullptr) _m->bCapSPos = make_unique<fk_Vector>();
	if(_m->bCapEPos == nullptr) _m->bCapEPos = make_unique<fk_Vector>();
	if(argRad < 0.0) return;
	if(argS == argE) return;
	*(_m->bCapSPos) = argS;
	*(_m->bCapEPos) = argE;
	_m->bCapRad = argRad;

	vec = argE - argS;
//	bModel->glVec(vec);
/*
	pos = (argS + argE)/2.0;
	bModel->glMoveTo(pos);
*/

	if(_m->bCapsule == nullptr) {
		_m->bCapsule = make_unique<fk_IndexFaceSet>();
		_m->bCapsule->makeCapsule(4, vec.dist(), _m->bCapRad);
	} else {
		_m->bCapsule->setCapsuleSize(vec.dist(), _m->bCapRad);
	}
}

double fk_Boundary::getCapsuleRadius(void)
{
	return _m->bCapRad;
}

double fk_Boundary::getCapsuleLength(void)
{
	if(_m->bCapSPos == nullptr || _m->bCapEPos == nullptr) return 0.0;
	return (*(_m->bCapSPos) - *(_m->bCapEPos)).dist();
}

fk_Vector fk_Boundary::getCapsuleStartPos(void)
{
	if(_m->bCapSPos == nullptr) return fk_Vector(0.0, 0.0, 0.0);
	return *(_m->bCapSPos);
}

fk_Vector fk_Boundary::getCapsuleEndPos(void)
{
	if(_m->bCapEPos == nullptr) return fk_Vector(0.0, 0.0, 0.0);
	return *(_m->bCapEPos);
}

void fk_Boundary::setBMode(fk_BoundaryMode argMode)
{
	_m->bMode = argMode;
}

fk_BoundaryMode fk_Boundary::getBMode(void)
{
	return _m->bMode;
}

void fk_Boundary::setBDrawToggle(bool argToggle)
{
	_m->bDrawToggle = argToggle;
}

bool fk_Boundary::getBDrawToggle(void)
{
	return _m->bDrawToggle;
}

void fk_Boundary::setBLineColor(fk_Color argCol)
{
	if(_m->bLineColor == nullptr) _m->bLineColor = make_unique<fk_Color>();
	*(_m->bLineColor) = argCol;
}

fk_Color * fk_Boundary::getBLineColor(void)
{
	if(_m->bLineColor == nullptr) _m->bLineColor = make_unique<fk_Color>();
	return _m->bLineColor.get();
}

void fk_Boundary::setBIntLineColor(fk_Color argCol)
{
	if(_m->bIntLineColor == nullptr) _m->bIntLineColor = make_unique<fk_Color>();
	*(_m->bIntLineColor) = argCol;
}

fk_Color * fk_Boundary::getBIntLineColor(void)
{
	if(_m->bIntLineColor == nullptr) _m->bIntLineColor = make_unique<fk_Color>();
	return _m->bIntLineColor.get();
}

void fk_Boundary::setBLineWidth(double argWidth)
{
	_m->bLineWidth = argWidth;
}

double fk_Boundary::getBLineWidth(void)
{
	return _m->bLineWidth;
}

fk_IndexFaceSet * fk_Boundary::GetBShape(void)
{
	switch(_m->bMode) {
	  case fk_BoundaryMode::SPHERE:
		return _m->bSphere.get();

	  case fk_BoundaryMode::AABB:
		return _m->bAABB.get();

	  case fk_BoundaryMode::OBB:
		return _m->bOBB.get();

	  case fk_BoundaryMode::CAPSULE:
		return _m->bCapsule.get();

	  case fk_BoundaryMode::NONE:
	  default:
		break;
	}
	return nullptr;
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
