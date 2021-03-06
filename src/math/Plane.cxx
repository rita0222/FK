﻿#include <FK/Plane.h>
#include <FK/Matrix.h>
#include <FK/Math.h>

using namespace FK;
using namespace std;

fk_Plane::Member::Member(void) :
	base(0.0, 0.0, 0.0),
	uVec(1.0, 0.0, 0.0),
	vVec(0.0, 1.0, 0.0),
	norm(0.0, 0.0, 1.0),
	dist(0.0), distFlag(false)
{
	return;
}

fk_Plane::fk_Plane(void) :
	fk_BaseObject(fk_Type::PLANE), _m(make_unique<Member>())
{
	return;
}

fk_Plane::fk_Plane(const fk_Plane &argPlane) :
	fk_BaseObject(fk_Type::PLANE), _m(make_unique<Member>())
{
	_m->base = argPlane._m->base;
	_m->uVec = argPlane._m->uVec;
	_m->vVec = argPlane._m->vVec;
	_m->dist = argPlane._m->dist;
	_m->distFlag = argPlane._m->distFlag;

	return;
}

fk_Plane & fk_Plane::operator =(const fk_Plane &argPlane)
{
	_m->base = argPlane._m->base;
	_m->uVec = argPlane._m->uVec;
	_m->vVec = argPlane._m->vVec;
	_m->dist = argPlane._m->dist;
	_m->distFlag = argPlane._m->distFlag;

	return *this;
}

fk_Plane::~fk_Plane()
{
	return;
}

bool fk_Plane::setPosNormal(const fk_Vector &argBase,
							const fk_Vector &argNorm)
{
	fk_Vector tmp;

	if(argNorm.isZero() == true) {
		return false;
	}

	_m->base = argBase;
	_m->norm = argNorm;
	_m->norm.normalize();
	if(fabs(_m->norm.z) > 1.0 - fk_Math::EPS) {
		// 法線ベクトルが z 軸に平行

		_m->uVec.set(1.0, 0.0, 0.0);
		if(_m->norm.z > 0.0) {
			_m->vVec.set(0.0, 1.0, 0.0);
			_m->norm.set(0.0, 0.0, 1.0);
		} else {
			_m->vVec.set(0.0, -1.0, 0.0);
			_m->norm.set(0.0, 0.0, -1.0);
		}
	} else {
		// z 軸に平行じゃない場合

		tmp.set(_m->norm.x, _m->norm.y, _m->norm.z + 1.0);
		_m->uVec = _m->norm ^ tmp;
		_m->uVec.normalize();
		_m->vVec = _m->norm ^ _m->uVec;
		_m->vVec.normalize();
	}
	_m->distFlag = false;
	return true;
}

bool fk_Plane::set3Pos(const fk_Vector &argPos1,
					   const fk_Vector &argPos2,
					   const fk_Vector &argPos3)
{
	fk_Vector	tmpU, tmpV;

	tmpU = argPos2 - argPos1;
	tmpV = argPos3 - argPos1;

	if((tmpU ^ tmpV).dist2() < fk_Math::EPS) return false;
	tmpU.normalize();
	tmpV.normalize();
	_m->base = argPos1;
	_m->uVec = tmpU;
	_m->vVec = tmpV;
	_m->norm = _m->uVec ^ _m->vVec;
	_m->distFlag = false;

	return true;
}

bool fk_Plane::setPosUVVec(const fk_Vector &argBase,
						   const fk_Vector &argUVec,
						   const fk_Vector &argVVec)
{
	if((argUVec ^ argVVec).dist2() < fk_Math::EPS) return false;
	_m->base = argBase;
	_m->uVec = argUVec;
	_m->uVec.normalize();
	_m->vVec = argVVec.perp(_m->uVec);
	_m->vVec.normalize();
	_m->norm = _m->uVec ^ _m->vVec;
	_m->distFlag = false;

	return true;
}

fk_Vector fk_Plane::getBasePos(void)
{
	return _m->base;
}

fk_Vector fk_Plane::getUVec(void)
{
	return _m->uVec;
}

fk_Vector fk_Plane::getVVec(void)
{
	return _m->vVec;
}

fk_Vector fk_Plane::getNormal(void)
{
	return _m->norm;
}

double fk_Plane::getDist(void)
{
	if(_m->distFlag == false) {
		CalcDist();
	}

	return fabs(_m->dist);
}

void fk_Plane::CalcDist(void)
{
	_m->dist = _m->base * _m->norm;
	_m->distFlag = true;
	return;
}

double fk_Plane::getDist(const fk_Vector &argPos)
{
	return (fabs((argPos - _m->base) * _m->norm));
}

fk_Vector fk_Plane::getPos(double argU, double argV)
{
	return (_m->base + argU*_m->uVec + argV*_m->vVec);
}

bool fk_Plane::isParallel(const fk_Vector &argVec)
{
	if(fabs(_m->norm * argVec) < fk_Math::EPS) return true;
	return false;
}

bool fk_Plane::isParallel(const fk_Plane &argPlane)
{
	return isVertical(argPlane._m->norm);
}

bool fk_Plane::isVertical(const fk_Vector &argVec)
{
	if((_m->norm ^ argVec).dist2() < fk_Math::EPS) return true;
	return false;
}

bool fk_Plane::isVertical(const fk_Plane &argPlane)
{
	return isParallel(argPlane._m->norm);
}

tuple<bool, fk_Vector> fk_Plane::calcCrossPos(const fk_Vector &argStart, const fk_Vector &argEnd)
{
	auto [status, t] = calcCrossLineParam(argStart, argEnd);
	if(status == false) return {false, fk_Vector()};

	return {true, (1.0 - t)*argStart + t*argEnd};
}

#ifndef FK_OLD_NONSUPPORT
bool fk_Plane::calcCrossPos(const fk_Vector &argStart, const fk_Vector &argEnd, fk_Vector *retPos)
{
	bool status;
	tie(status, *retPos) = calcCrossPos(argStart, argEnd);
	return status;
}
#endif

tuple<bool, double> fk_Plane::calcCrossLineParam(const fk_Vector &argStart,
												 const fk_Vector &argEnd)
{
	fk_Vector lineVec(argEnd - argStart);

	if(isParallel(lineVec) == true) return {false, 0.0};
	if(_m->distFlag == false) CalcDist();
	return {true, (_m->dist - (_m->norm * argStart))/(_m->norm * lineVec)};
}

#ifndef FK_OLD_NONSUPPORT
bool fk_Plane::calcCrossLineParam(const fk_Vector &argStart, const fk_Vector &argEnd, double *retT)
{
	bool status;
	tie(status, *retT) = calcCrossLineParam(argStart, argEnd);
	return status;
}
#endif

tuple<bool, double, double> fk_Plane::calcCrossPlaneParam(const fk_Vector &argStart,
														  const fk_Vector &argEnd)
{
	bool status;
	double u, v;
	tie(status, ignore, ignore, u, v) = calcCrossAll(argStart, argEnd);
	return {status, u, v};
}

#ifndef FK_OLD_NONSUPPORT
bool fk_Plane::calcCrossPlaneParam(const fk_Vector &argStart,
								   const fk_Vector &argEnd,
								   double *retU, double *retV)
{
	bool status;
	tie(status, ignore, ignore, *retU, *retV) = calcCrossAll(argStart, argEnd);
	return status;
}
#endif

tuple<bool, fk_Vector, double, double, double> fk_Plane::calcCrossAll(const fk_Vector &argStart,
																	  const fk_Vector &argEnd)
{
	fk_Matrix mat;
	fk_HVector lineVec(argStart - argEnd);
	fk_HVector V;

	if(isParallel(lineVec) == true) {
		return {false, fk_Vector(), 0.0, 0.0, 0.0};
	}

	mat.setCol(0, _m->uVec);
	mat.setCol(1, _m->vVec);
	mat.setCol(2, lineVec);

	mat.inverse();
	V = mat * (argStart - _m->base);

	return {true, (1.0 - V.z) * argStart + V.z * argEnd, V.z, V.x, V.y};
}

#ifndef FK_OLD_NONSUPPORT
bool fk_Plane::calcCrossAll(const fk_Vector &argStart, const fk_Vector &argEnd,
							fk_Vector *retPos, double *retT, double *retU, double *retV)
{
	bool status;
	tie(status, *retPos, *retT, *retU, *retV) = calcCrossAll(argStart, argEnd);
	return status;
}
#endif

fk_Vector fk_Plane::proj(const fk_Vector &argP)
{
	return argP - ((argP - _m->base) * _m->norm) * _m->norm;
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
