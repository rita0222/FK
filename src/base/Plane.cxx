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
#include <FK/Plane.h>
#include <FK/Matrix.h>

fk_Plane::fk_Plane(void)
	: fk_BaseObject(FK_PLANE)
{
	base.set(0.0, 0.0, 0.0);
	uVec.set(1.0, 0.0, 0.0);
	vVec.set(0.0, 1.0, 0.0);
	norm.set(0.0, 0.0, 1.0);
	dist = 0.0;
	distFlag = false;

	return;
}

fk_Plane::~fk_Plane()
{
	return;
}

bool fk_Plane::setPosNormal(const fk_Vector &argBase,
							const fk_Vector &argNorm)
{
	fk_Vector		tmp;

	if(argNorm.isZero() == true) {
		return false;
	}

	base = argBase;
	norm = argNorm;
	norm.normalize();
	if(fabs(norm.z) > 1.0 - FK_EPS) {
		// 法線ベクトルが z 軸に平行

		uVec.set(1.0, 0.0, 0.0);
		if(norm.z > 0.0) {
			vVec.set(0.0, 1.0, 0.0);
			norm.set(0.0, 0.0, 1.0);
		} else {
			vVec.set(0.0, -1.0, 0.0);
			norm.set(0.0, 0.0, -1.0);
		}
	} else {
		// z 軸に平行じゃない場合

		tmp.set(norm.x, norm.y, norm.z + 1.0);
		uVec = norm ^ tmp;
		uVec.normalize();
		vVec = norm ^ uVec;
		vVec.normalize();
	}
	distFlag = false;
	return true;
}

bool fk_Plane::set3Pos(const fk_Vector &argPos1,
					   const fk_Vector &argPos2,
					   const fk_Vector &argPos3)
{
	fk_Vector	tmpU, tmpV;

	tmpU = argPos2 - argPos1;
	tmpV = argPos3 - argPos1;

	if((tmpU ^ tmpV).dist2() < FK_EPS) return false;
	tmpU.normalize();
	tmpV.normalize();
	base = argPos1;
	uVec = tmpU;
	vVec = tmpV;
	norm = uVec ^ vVec;
	distFlag = false;

	return true;
}

bool fk_Plane::setPosUVVec(const fk_Vector &argBase,
						   const fk_Vector &argUVec,
						   const fk_Vector &argVVec)
{
	if((argUVec ^ argVVec).dist2() < FK_EPS) return false;
	base = argBase;
	uVec = argUVec;
	uVec.normalize();
	vVec = argVVec.perp(uVec);
	vVec.normalize();
	norm = uVec ^ vVec;
	distFlag = false;

	return true;
}

fk_Vector fk_Plane::getBasePos(void)
{
	return base;
}

fk_Vector fk_Plane::getUVec(void)
{
	return uVec;
}

fk_Vector fk_Plane::getVVec(void)
{
	return vVec;
}

fk_Vector fk_Plane::getNormal(void)
{
	return norm;
}

double fk_Plane::getDist(void)
{
	if(distFlag == false) {
		CalcDist();
	}

	return fabs(dist);
}

void fk_Plane::CalcDist(void)
{
	dist = base * norm;
	distFlag = true;
	return;
}

double fk_Plane::getDist(const fk_Vector &argPos)
{
	return (fabs((argPos - base) * norm));
}

fk_Vector fk_Plane::getPos(double argU, double argV)
{
	return (base + argU*uVec + argV*vVec);
}

bool fk_Plane::isParallel(const fk_Vector &argVec)
{
	if(fabs(norm * argVec) < FK_EPS) return true;
	return false;
}

bool fk_Plane::isParallel(const fk_Plane &argPlane)
{
	return isVertical(argPlane.norm);
}

bool fk_Plane::isVertical(const fk_Vector &argVec)
{
	if((norm ^ argVec).dist2() < FK_EPS) return true;
	return false;
}

bool fk_Plane::isVertical(const fk_Plane &argPlane)
{
	return isParallel(argPlane.norm);
}

bool fk_Plane::calcCrossLineParam(const fk_Vector &argStart,
								  const fk_Vector &argEnd,
								  double *retT)
{
	fk_Vector		lineVec;

	lineVec = argEnd - argStart;

	if(isParallel(lineVec) == true) return false;

	if(distFlag == false) CalcDist();
	*retT = (dist - (norm * argStart))/(norm * lineVec);
	return true;
}

bool fk_Plane::calcCrossPos(const fk_Vector &argStart,
							const fk_Vector &argEnd,
							fk_Vector *retPos)
{
	double			param;

	if(calcCrossLineParam(argStart, argEnd, &param) == false) {
		return false;
	}

	*retPos = (1.0 - param)*argStart + param*argEnd;
	return true;
}

bool fk_Plane::calcCrossAll(const fk_Vector &argStart,
							const fk_Vector &argEnd,
							fk_Vector *retPos, double *retT,
							double *retU, double *retV)
{
	fk_Matrix		mat;
	fk_HVector		lineVec, tmpVec, paramVec;

	lineVec = argStart - argEnd;
	if(isParallel(lineVec) == true) {
		return false;
	}

	tmpVec = argStart - base;

	mat[0][0] = uVec.x;	mat[0][1] = vVec.x;	mat[0][2] = lineVec.x;
	mat[1][0] = uVec.y;	mat[1][1] = vVec.y;	mat[1][2] = lineVec.y;
	mat[2][0] = uVec.z;	mat[2][1] = vVec.z;	mat[2][2] = lineVec.z;

	mat.inverse();
	paramVec = mat * tmpVec;

	*retU = paramVec.x;
	*retV = paramVec.y;
	*retT = paramVec.z;

	*retPos = (1.0 - *retT)*argStart + (*retT)*argEnd;
	return true;
}

bool fk_Plane::calcCrossPlaneParam(const fk_Vector &argStart,
								   const fk_Vector &argEnd,
								   double *retU, double *retV)
{
	fk_Vector	dummy;
	double		t;

	return calcCrossAll(argStart, argEnd, &dummy, &t, retU, retV);
}
