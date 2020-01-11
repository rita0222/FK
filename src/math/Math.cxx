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
#include <FK/Math.h>
#include <FK/Matrix.h>
#include <random>

using namespace FK;
using namespace std;

static random_device *rd = nullptr;
static mt19937 *mt = nullptr;

static void randInit(void)
{
	if(rd == nullptr) rd = new random_device();
	if(mt == nullptr) mt = new mt19937((*rd)());
}

bool fk_Math::isOnLine(const fk_Vector &argA,
					   const fk_Vector &argB,
					   const fk_Vector &argP)
{
	fk_Vector	tmpVec;

	tmpVec = (argP - argA) ^ (argP - argB);

	if(tmpVec.dist2() < EPS) return true;
	return false;
}

bool fk_Math::isOnLineSegment(const fk_Vector &argA,
							  const fk_Vector &argB,
							  const fk_Vector &argP,
							  bool argOpenFlg)
{
	fk_Vector		vec1, vec2;

	if(argA == argP || argB == argP) {
		return argOpenFlg;
	}

	vec1 = argP - argA;
	vec2 = argP - argB;

	vec1.normalize();
	vec2.normalize();

	if(vec1 * vec2 < -1.0 + EPS) return true;
	return false;
}

bool fk_Math::isCrossLine(const fk_Vector &argA, 
						  const fk_Vector &argB,
						  const fk_Vector &argC,
						  const fk_Vector &argD)
{
	fk_Matrix		mat;

	mat[0][0] = argB.x - argA.x;
	mat[0][1] = argC.x - argD.x;
	mat[0][2] = 1.0;

	mat[1][0] = argB.y - argA.y;
	mat[1][1] = argC.y - argD.y;
	mat[1][2] = 1.0;

	mat[2][0] = argB.z - argA.z;
	mat[2][1] = argC.z - argD.z;
	mat[2][2] = 1.0;

	if(mat.inverse() == true) return true;

	return isOnLine(argA, argB, argC);
}	

bool fk_Math::isCrossLineSegment(const fk_Vector &argA,
								 const fk_Vector &argB,
								 const fk_Vector &argC,
								 const fk_Vector &argD,
								 bool argOpenFlg)
{
	fk_Vector		tmpVec0, tmpVec1;
	fk_Matrix		mat;
	double			inner;

	if(argOpenFlg == true) {
		if(argA == argC || argA == argD || argB == argC || argB == argD) {
			return true;
		}
	}

	mat[0][0] = argB.x - argA.x;
	mat[0][1] = argC.x - argD.x;
	mat[0][2] = 1.0;

	mat[1][0] = argB.y - argA.y;
	mat[1][1] = argC.y - argD.y;
	mat[1][2] = 1.0;

	mat[2][0] = argB.z - argA.z;
	mat[2][1] = argC.z - argD.z;
	mat[2][2] = 1.0;

	tmpVec0.set(argC.x - argA.x, argC.y - argA.y, argC.z - argA.z);

	if(mat.inverse() == true) {
		tmpVec1 = mat * tmpVec0;
		if(fabs(tmpVec1.z) > EPS) return false;

		if(argOpenFlg == true) {
			if(tmpVec1.x > -EPS && tmpVec1.x < 1.0 + EPS &&
			   tmpVec1.y > -EPS && tmpVec1.y < 1.0 + EPS) return true;
		} else {
			if(tmpVec1.x > EPS && tmpVec1.x < 1.0 - EPS &&
			   tmpVec1.y > EPS && tmpVec1.y < 1.0 - EPS) return true;
		}

		return false;
	}

	tmpVec0 = argA - argC;
	tmpVec1 = argB - argC;
	tmpVec0.normalize();
	tmpVec1.normalize();

	inner = tmpVec0 * tmpVec1;
	if(inner < -1.0 + EPS) return true;
	if(inner < 1.0 - EPS) return false;

	tmpVec0 = argA - argD;
	tmpVec1 = argB - argD;
	tmpVec0.normalize();
	tmpVec1.normalize();

	if(tmpVec0 * tmpVec1 < -1.0 + EPS) return true;

	return false;
}

double fk_Math::calcCosine(fk_Vector pos1, fk_Vector pos2)
{
	if(pos1.normalize() == false || pos2.normalize() == false) return 0.0;
	return(pos1*pos2);
}

fk_Vector fk_Math::divideVec(const fk_Vector &orgVec,
							const fk_Vector &vec1,
							const fk_Vector &vec2,
							const fk_Vector &vec3)
{
	fk_Matrix		mat;
	fk_Vector		retVec(0.0, 0.0, 0.0);

	mat[0][0] = vec1.x; mat[0][1] = vec2.x; mat[0][2] = vec3.x;
	mat[1][0] = vec1.y; mat[1][1] = vec2.y; mat[1][2] = vec3.y;
	mat[2][0] = vec1.z; mat[2][1] = vec2.z; mat[2][2] = vec3.z;

	if(mat.inverse() == false) {
		return retVec;
	}

	retVec = mat * orgVec;
	return retVec;
}


fk_Quaternion fk_Math::quatInterLinear(const fk_Quaternion &argQ1,
									   const fk_Quaternion &argQ2,
									   double argT)
{
	fk_Quaternion q;

	q = (1.0 - argT) * argQ1 + argT * argQ2;
	q.normalize();
	return q;
}

fk_Quaternion fk_Math::quatInterSphere(const fk_Quaternion &argQ1,
									   const fk_Quaternion &argQ2,
									   double argT)
{
	fk_Quaternion	q1, q2, q3;
	double			theta, sinTheta, prod;

	q1 = argQ1;

	if((argQ1 == argQ2) || (argQ1 == -argQ2)) return q1;

	if((argQ1 ^ argQ2) >= 0.0) {
		q2 = argQ2;
	} else {
		q2 = -argQ2;
	}

	q1.normalize();
	q2.normalize();

	prod = q1 ^ q2;
	if(prod > 1.0) prod = 1.0;
	if(prod < -1.0) prod = -1.0;

	theta = acos(prod);
	sinTheta = sin(theta);
	if(fabs(sinTheta) < fk_Vector::VECTOREPS) {
		q3 = quatInterLinear(argQ1, argQ2, argT);
	} else {
		q3 = (sin(theta * (1.0 - argT))/sinTheta) * q1
			+ (sin(theta*argT)/sinTheta) * q2;
	}

	return q3;
}

double fk_Math::clamp(double n, double min, double max)
{
	if(n < min) return min;
	if(n > max) return max;
	return n;
}

tuple<double, double, double, fk_Vector, fk_Vector>
fk_Math::calcClosestPtSegToSeg(const fk_Vector &p1, const fk_Vector &q1,
							   const fk_Vector &p2, const fk_Vector &q2)
{
	double s, t;
	fk_Vector C1, C2;

	fk_Vector d1 = q1 - p1;
	fk_Vector d2 = q2 - p2;
	fk_Vector r = p1 - p2;
	double a = d1*d1;
	double e = d2*d2;
	double f = d2*r;
	if(a < EPS && e < EPS) {
		s = t = 0.0;
		C1 = p1;
		C2 = p2;
	} else if(a < EPS) {
		s = 0.0;
		t = f/e;
		t = clamp(t, 0.0, 1.0);
	} else {
		double c = d1*r;
		if(e < EPS) {
			t = 0.0;
			s = clamp(-c/a, 0.0, 1.0);
		} else {
			double b = d1*d2;
			double denom = a*e - b*b;
			if(denom != 0.0) {
				s = clamp((b*f - c*e)/denom, 0.0, 1.0);
			} else {
				s = 0.0;
			}
			t = (b*s + f)/e;
			if(t < 0.0) {
				t = 0.0;
				s = clamp(-c/a, 0.0, 1.0);
			} else if(t > 1.0) {
				t = 1.0;
				s = clamp((b - c)/a, 0.0, 1.0);
			}
		}
	}
	C1 = p1 + d1*s;
	C2 = p2 + d2*t;
	
	return make_tuple((C1-C2).dist(), s, t, C1, C2);
}

#ifndef FK_OLD_NONSUPPORT
double fk_Math::calcClosestPtSegToSeg(const fk_Vector &p1, const fk_Vector &q1,
									  const fk_Vector &p2, const fk_Vector &q2,
									  double *s, double *t, fk_Vector *c1, fk_Vector *c2)
{
	double dist;

	tie(dist, *s, *t, *c1, *c2) = calcClosestPtSegToSeg(p1, q1, p2, q2);
	return dist;
}
#endif

tuple<double, fk_Vector>
fk_Math::calcClosestPtPtToSeg(const fk_Vector &c, const fk_Vector &a, const fk_Vector &b)
{
	fk_Vector ab = b - a;
	double t = clamp((c - a)*ab / (ab*ab), 0.0, 1.0);
	return {t, a + t*ab};
}

#ifndef FK_OLD_NONSUPPORT
void fk_Math::calcClosestPtPtToSeg(const fk_Vector &c, const fk_Vector &a, const fk_Vector &b,
									double *t, fk_Vector *D)
{
	tie(*t, *D) = calcClosestPtPtToSeg(c, a, b);
	return;
}
#endif

tuple<bool, double, double, double>
fk_Math::calcCrossLineAndTri(const fk_Vector &argP, const fk_Vector &argQ,
							 const fk_Vector &argA, const fk_Vector &argB,
							 const fk_Vector &argC)
{
	fk_Matrix M;

	M.setCol(0, argB - argA);
	M.setCol(1, argC - argA);
	M.setCol(2, argP - argQ);
	if(M.inverse() == false) return {false, 0.0, 0.0, 0.0};
	
	fk_Vector R = M * (argP - argA);

	if(R.x <= -EPS || R.y <= -EPS || R.x + R.y >= 1.0 + EPS ||
	   R.z <= -EPS || R.z >= 1.0 + EPS) {
		return {false, 0.0, 0.0, 0.0};
	}

	return {true, R.x, R.y, R.z};
}

#ifndef FK_OLD_NONSUPPORT
bool fk_Math::calcCrossLineAndTri(const fk_Vector &argP,
								  const fk_Vector &argQ,
								  const fk_Vector &argA,
								  const fk_Vector &argB,
								  const fk_Vector &argC,
								  fk_Vector *argR)
{
	auto [status, u, v, t] = calcCrossLineAndTri(argP, argQ, argA, argB, argC);
	if(argR != nullptr) argR->set(u, v, t);
	return status;
}
#endif

unsigned int fk_Math::rand(void)
{
	randInit();

	return (unsigned int)((*mt)());
}

int fk_Math::rand(int argMin, int argMax)
{
	randInit();

	if(argMin >= argMax) return argMin;
	uniform_int_distribution<> dist(argMin, argMax-1);
	return dist((*mt));
}

double fk_Math::drand(void)
{
	randInit();

	uniform_real_distribution<> dist(0.0, 1.0);
	return dist((*mt));
}

double fk_Math::drand(double argMin, double argMax)
{
	randInit();

	if(argMin >= argMax) return argMin;
	uniform_real_distribution<> dist(argMin, argMax);
	return dist((*mt));
}

   
