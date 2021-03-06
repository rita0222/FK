﻿#include <FK/Projection.h>
#include <FK/Error.H>

using namespace FK;
using namespace std;

fk_ProjectBase::fk_ProjectBase(fk_ProjectMode argMode)
{
	ProjM = make_unique<fk_Matrix>();
	SetMode(argMode);
	return;
}

fk_ProjectBase::~fk_ProjectBase()
{
	return;
}

void fk_ProjectBase::SetMode(fk_ProjectMode argMode)
{
	Mode = argMode;

	switch(Mode) {
	  case fk_ProjectMode::NONE:
		SetObjectType(fk_Type::PROJECTBASE);
		MakeMat = [&] { ProjM->init(); };
		break;

	  case fk_ProjectMode::PERSPECTIVE:
		SetObjectType(fk_Type::PERSPECTIVE);
		break;

	  case fk_ProjectMode::FRUSTUM:
		SetObjectType(fk_Type::FRUSTUM);
		break;

	  case fk_ProjectMode::ORTHO:
		SetObjectType(fk_Type::ORTHO);
		break;

	  default:
		break;
	}

	return;
}

fk_Matrix * fk_ProjectBase::GetMatrix()
{
	return ProjM.get();
}

fk_ProjectMode fk_ProjectBase::getMode(void) const
{
	return Mode;
}

fk_Perspective::Member::Member(void) :
	Fovy(0.0), Near(0.0), Far(0.0), Aspect(1.0), AutoMode(true)
{
	return;
}

void fk_Perspective::MakeInit(void)
{
	MakeMat = [&] {
		ProjM->makePerspective(_m->Fovy, _m->Near, _m->Far, _m->Aspect);
	};
}

fk_Perspective::fk_Perspective(double argFovy, double argNear, double argFar) :
	fk_ProjectBase(fk_ProjectMode::PERSPECTIVE), _m(make_unique<Member>())
{
	MakeInit();
	setAll(argFovy, argNear, argFar, 1.0);
	return;
}

fk_Perspective::fk_Perspective(const fk_Perspective &argPers)
	: fk_ProjectBase(fk_ProjectMode::PERSPECTIVE)
{
	MakeInit();
	setAll(argPers._m->Fovy, argPers._m->Near, argPers._m->Far, argPers._m->Aspect);
}

fk_Perspective::~fk_Perspective()
{
	return;
}

fk_Perspective & fk_Perspective::operator =(const fk_Perspective &argPers)
{
	SetMode(fk_ProjectMode::PERSPECTIVE);
	_m->AutoMode = argPers._m->AutoMode;
	setAll(argPers._m->Fovy, argPers._m->Near, argPers._m->Far, argPers._m->Aspect);

	return *this;
}

void fk_Perspective::setFovy(double argFovy)
{
	if(argFovy <= 0.0 || argFovy > fk_Math::PI) {
		Error::Put("fk_Perspective", "setFovy", 1, "Fovy Angle Error.");
		return;
	}

	_m->Fovy = argFovy;
	return;
}

void fk_Perspective::setNear(double argNear)
{
	if(argNear <= 0.0) {
		Error::Put("fk_Perspective", "setNear", 1, "Near Plane Distance Error.");
		return;
	}

	_m->Near = argNear;
	return;
}

void fk_Perspective::setFar(double argFar)
{
	if(argFar <= 0.0) {
		Error::Put("fk_Perspective", "setFar", 1, "Far Plane Distance Error.");
		return;
	}

	_m->Far = argFar;
	return;
}

void fk_Perspective::setAspect(double argAspect)
{
	_m->Aspect = argAspect;
	_m->AutoMode = false;
	return;
}

void fk_Perspective::setAll(double argFovy, double argNear, double argFar)
{
	setFovy(argFovy);
	setNear(argNear);
	setFar(argFar);
	_m->AutoMode = true;

	return;
}

void fk_Perspective::setAll(double argFovy, double argNear, double argFar, double argAspect)
{
	setFovy(argFovy);
	setNear(argNear);
	setFar(argFar);
	setAspect(argAspect);

	return;
}


double fk_Perspective::getFovy(void) const
{
	return _m->Fovy;
}

double fk_Perspective::getNear(void) const
{
	return _m->Near;
}

double fk_Perspective::getFar(void) const
{
	return _m->Far;
}

double fk_Perspective::getAspect(void) const
{
	return _m->Aspect;
}

fk_Frustum::Member::Member(void)
{
	return;
}

void fk_Frustum::MakeInit(void)
{
	MakeMat = [&] {
		ProjM->makeFrustum(_m->Left, _m->Right, _m->Bottom, _m->Top, _m->Near, _m->Far);
	};
}
	

fk_Frustum::fk_Frustum(double argLeft, double argRight,
					   double argBottom, double argTop,
					   double argNear, double argFar) :
	fk_ProjectBase(fk_ProjectMode::FRUSTUM), _m(make_unique<Member>())
{
	MakeInit();
	setAll(argLeft, argRight, argBottom, argTop, argNear, argFar);
	return;
}

fk_Frustum::fk_Frustum(const fk_Frustum &argFrustum) :
	fk_ProjectBase(fk_ProjectMode::FRUSTUM), _m(make_unique<Member>())
{
	MakeInit();
	setAll(argFrustum._m->Left, argFrustum._m->Right,
		   argFrustum._m->Bottom, argFrustum._m->Top,
		   argFrustum._m->Near, argFrustum._m->Far);
	return;
}

fk_Frustum::~fk_Frustum()
{
	return;
}

fk_Frustum & fk_Frustum::operator =(const fk_Frustum &argFrustum)
{
	SetMode(fk_ProjectMode::FRUSTUM);
	setAll(argFrustum._m->Left, argFrustum._m->Right,
		   argFrustum._m->Bottom, argFrustum._m->Top,
		   argFrustum._m->Near, argFrustum._m->Far);

	return *this;
}

void fk_Frustum::setLeft(double argLeft)
{
	_m->Left = argLeft;
	return;
}

void fk_Frustum::setRight(double argRight)
{
	_m->Right = argRight;
	return;
}

void fk_Frustum::setBottom(double argBottom)
{
	_m->Bottom = argBottom;
	return;
}

void fk_Frustum::setTop(double argTop)
{
	_m->Top = argTop;
	return;
}

void fk_Frustum::setNear(double argNear)
{
	_m->Near = argNear;
	return;
}

void fk_Frustum::setFar(double argFar)
{
	_m->Far = argFar;
	return;
}

void fk_Frustum::setAll(double argLeft, double argRight,
						double argBottom, double argTop,
						double argNear, double argFar)
{
	_m->Left = argLeft;
	_m->Right = argRight;
	_m->Bottom = argBottom;
	_m->Top = argTop;
	_m->Near = argNear;
	_m->Far = argFar;
	return;
}

double fk_Frustum::getLeft(void) const
{
	return _m->Left;
}

double fk_Frustum::getRight(void) const
{
	return _m->Right;
}

double fk_Frustum::getBottom(void) const
{
	return _m->Bottom;
}

double fk_Frustum::getTop(void) const
{
	return _m->Top;
}

double fk_Frustum::getNear(void) const
{
	return _m->Near;
}

double fk_Frustum::getFar(void) const
{
	return _m->Far;
}

fk_Ortho::Member::Member(void)
{
	return;
}

void fk_Ortho::MakeInit(void)
{
	MakeMat = [&] {
		ProjM->makeOrtho(_m->Left, _m->Right, _m->Bottom, _m->Top, _m->Near, _m->Far);
	};
}

fk_Ortho::fk_Ortho(double argLeft, double argRight,
				   double argBottom, double argTop,
				   double argNear, double argFar) :
	fk_ProjectBase(fk_ProjectMode::ORTHO), _m(make_unique<Member>())
{
	MakeInit();
	setAll(argLeft, argRight, argBottom, argTop, argNear, argFar);
	return;
}

fk_Ortho::fk_Ortho(const fk_Ortho &argOrtho)
	: fk_ProjectBase(fk_ProjectMode::ORTHO), _m(make_unique<Member>())
{
	MakeInit();
	setAll(argOrtho._m->Left, argOrtho._m->Right,
		   argOrtho._m->Bottom, argOrtho._m->Top,
		   argOrtho._m->Near, argOrtho._m->Far);
}

fk_Ortho::~fk_Ortho()
{
	return;
}

fk_Ortho & fk_Ortho::operator =(const fk_Ortho &argOrtho)
{
	SetMode(fk_ProjectMode::ORTHO);
	setAll(argOrtho._m->Left, argOrtho._m->Right,
		   argOrtho._m->Bottom, argOrtho._m->Top,
		   argOrtho._m->Near, argOrtho._m->Far);

	return *this;
}

void fk_Ortho::setLeft(double argLeft)
{
	_m->Left = argLeft;
	return;
}

void fk_Ortho::setRight(double argRight)
{
	_m->Right = argRight;
	return;
}

void fk_Ortho::setBottom(double argBottom)
{
	_m->Bottom = argBottom;
	return;
}

void fk_Ortho::setTop(double argTop)
{
	_m->Top = argTop;
	return;
}

void fk_Ortho::setNear(double argNear)
{
	_m->Near = argNear;
	return;
}

void fk_Ortho::setFar(double argFar)
{
	_m->Far = argFar;
	return;
}

void fk_Ortho::setAll(double argLeft, double argRight,
					  double argBottom, double argTop,
					  double argNear, double argFar)
{
	setLeft(argLeft);
	setRight(argRight);
	setBottom(argBottom);
	setTop(argTop);
	setNear(argNear);
	setFar(argFar);

	return;
}

double fk_Ortho::getLeft(void) const
{
	return _m->Left;
}

double fk_Ortho::getRight(void) const
{
	return _m->Right;
}

double fk_Ortho::getBottom(void) const
{
	return _m->Bottom;
}

double fk_Ortho::getTop(void) const
{
	return _m->Top;
}

double fk_Ortho::getNear(void) const
{
	return _m->Near;
}

double fk_Ortho::getFar(void) const
{
	return _m->Far;
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
