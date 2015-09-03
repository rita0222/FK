/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
#include <FK/Error.H>

static fk_Angle & VectorToHeadPitch(const fk_Vector &argVec)
{
	fk_Vector			tmpVec;
	static fk_Angle		retAngle;

	tmpVec = argVec;
	if(tmpVec.normalize() == false) {
		fk_PutError("fk_Quaternion", "VectorToHeadPitch", 1,
					"Zero Vector Error.");
		retAngle.h = retAngle.p = retAngle.b = 0.0;
		return retAngle;
	}

	retAngle.p = asin(tmpVec.y);

	if(fabs(tmpVec.z) < FK_EPS) {
		if(fabs(tmpVec.x) < FK_EPS) {
			retAngle.h = 0.0;
		} else if(tmpVec.x > 0.0) {
			retAngle.h = FK_PI/2.0;
		} else {
			retAngle.h = -FK_PI/2.0;
		}
	} else {
		retAngle.h = atan2(tmpVec.x, -tmpVec.z);
	}

	return retAngle;
}

static fk_Angle & VectorToAngle(const fk_Vector &argDirecVec,
								const fk_Vector &argUpVec)
{
	static fk_Angle	retAngle;
	const fk_Vector	axisX(1.0, 0.0, 0.0);
	const fk_Vector	axisY(0.0, 1.0, 0.0);
	fk_Vector		tmpUpVec;
	fk_Quaternion	Qx, Qy;

	retAngle = VectorToHeadPitch(argDirecVec);

	Qx.setRotate(-retAngle.p, axisX);
	Qy.setRotate(retAngle.h, axisY);
	
	tmpUpVec = Qx * Qy * argUpVec;

	if(fabs(tmpUpVec.y) < FK_VECTOREPS) {
		if(fabs(tmpUpVec.x) < FK_VECTOREPS) {
			retAngle.b = 0.0;
		} else if(tmpUpVec.x > 0.0) {
			retAngle.b = FK_PI/2.0;
		} else {
			retAngle.b = -FK_PI/2.0;
		}
	} else {
		retAngle.b = atan2(tmpUpVec.x, tmpUpVec.y);
	}

	if(retAngle.b < -FK_PI) {
		retAngle.b += FK_PI;
	} else if(retAngle.b > FK_PI) {
		retAngle.b -= FK_PI;
	}

	return retAngle;
}

fk_Quaternion::fk_Quaternion(void)
{
	set(0.0, 0.0, 0.0, 0.0);
}

fk_Quaternion::fk_Quaternion(double argS, double argX, double argY, double argZ)
{
	set(argS, argX, argY, argZ);
	return;
}

fk_Quaternion::fk_Quaternion(const double argTheta, const fk_Vector &argV)
{
	set(argTheta, argV);
	return;
}

fk_Quaternion::fk_Quaternion(const fk_Quaternion &argQ)
{
	set(argQ.s, argQ.v.x, argQ.v.y, argQ.v.z);
	return;
}

void fk_Quaternion::init(void)
{
	set(1.0, 0.0, 0.0, 0.0);
	return;
}

void fk_Quaternion::set(double argS, double argX, double argY, double argZ)
{
	s = argS;
	v.x = argX;
	v.y = argY;
	v.z = argZ;
	return;
}

void fk_Quaternion::set(double argS, const fk_Vector &argV)
{
	s = argS;
	v = argV;
	return;
}

void fk_Quaternion::setRotate(double argTheta,
							  double argX, double argY, double argZ)
{
	const fk_Vector tmpV(argX, argY, argZ);
	setRotate(argTheta, tmpV);
	return;
}

void fk_Quaternion::setRotate(double argTheta, const fk_Vector &argV)
{
	double		dist = argV.dist();

	if(dist < FK_VECTOREPS) return;

	s = cos(argTheta/2.0);
	v = argV * sin(argTheta/2.0)/dist;
	return;
}

void fk_Quaternion::makeEuler(double argH, double argP, double argB)
{
	fk_Quaternion		qH, qP, qB;
	const fk_Vector		axisX(1.0, 0.0, 0.0);
	const fk_Vector		axisY(0.0, 1.0, 0.0);
	const fk_Vector		axisZ(0.0, 0.0, 1.0);

	qH.setRotate(-argH, axisY);
	qP.setRotate(argP, axisX);
	qB.setRotate(-argB, axisZ);

	*this = qH * qP * qB;
	return;
}

void fk_Quaternion::makeEuler(const fk_Angle &argAngle)
{
	makeEuler(argAngle.h, argAngle.p, argAngle.b);
	return;
}

fk_Angle & fk_Quaternion::getEuler(void) const
{
	fk_Quaternion		tmpQ = *this;
	const fk_Vector		vec(0.0, 0.0, -1.0);
	const fk_Vector		up(0.0, 1.0, 0.0);
	fk_Vector			rotVec, rotUp;
	static fk_Angle		retAngle;

	tmpQ.normalize();
	rotVec = tmpQ * vec;
	rotUp = tmpQ * up;
	retAngle = VectorToAngle(rotVec, rotUp);
	return retAngle;
}

double fk_Quaternion::norm(void) const
{
	return s*s + v.dist2();
}

double fk_Quaternion::abs(void) const
{
	return sqrt(norm());
}

bool fk_Quaternion::normalize(void)
{
	double	tmp_abs;
	double	tmp_norm = norm();
	if(tmp_norm < FK_VECTOREPS) return false;
	tmp_abs = sqrt(tmp_norm);
	s /= tmp_abs;
	v /= tmp_abs;
	return true;
}

void fk_Quaternion::conj(void)
{
	v = -v;
	return;
}

bool fk_Quaternion::inverse(void)
{
	double	tmp_norm = norm();
	if(tmp_norm < FK_VECTOREPS) return false;
	conj();
	*this /= tmp_norm;
	return true;
}

fk_Matrix & fk_Quaternion::conv(void) const
{
	static fk_Matrix	mat;
	fk_Quaternion		q = *this;

	q.normalize();

	mat.makeEuler(q.getEuler());
	return mat;
}

fk_Quaternion & fk_Quaternion::operator !(void) const
{
	static fk_Quaternion tmpQ;
	double	tmp_norm = norm();

	if(tmp_norm < FK_VECTOREPS) {
		tmpQ = *this;
	} else {
		tmpQ.s = s/tmp_norm;
		tmpQ.v = -v/tmp_norm;
	}

	return tmpQ;
}

fk_Quaternion & fk_Quaternion::operator ~(void) const
{
	static fk_Quaternion tmpQ;

	tmpQ.s = s;
	tmpQ.v = -v;
	return tmpQ;
}

fk_Quaternion & fk_Quaternion::operator -(void) const
{
	static fk_Quaternion tmpQ;

	tmpQ.s = -s;
	tmpQ.v = -v;
	return tmpQ;
}

fk_Quaternion & fk_Quaternion::operator =(const fk_Quaternion &argQ)
{
	s = argQ.s;
	v = argQ.v;

	return *this;
}

fk_Quaternion & fk_Quaternion::operator *=(double argD)
{
	s *= argD;
	v *= argD;

	return *this;
}

fk_Quaternion & fk_Quaternion::operator /=(double argD)
{
	s /= argD;
	v /= argD;

	return *this;
}

fk_Quaternion & fk_Quaternion::operator *=(const fk_Quaternion &argQ)
{
	*this = *this * argQ;

	return *this;
}

fk_Quaternion & fk_Quaternion::operator +=(const fk_Quaternion &argQ)
{
	s += argQ.s;
	v += argQ.v;

	return *this;
}

fk_Quaternion & fk_Quaternion::operator -=(const fk_Quaternion &argQ)
{
	s -= argQ.s;
	v -= argQ.v;

	return *this;
}

bool fk_Quaternion::operator ==(const fk_Quaternion &argQ) const
{
	if(fabs(s - argQ.s) < FK_VECTOREPS && v == argQ.v) return true;
	return false;
}

bool fk_Quaternion::operator !=(const fk_Quaternion &argQ) const
{
	if(fabs(s - argQ.s) < FK_VECTOREPS && v == argQ.v) return false;
	return true;
}

// friend 宣言による外部関数化した二項演算子

fk_Quaternion operator *(const fk_Quaternion &argQ1,
						 const fk_Quaternion &argQ2)
{
	fk_Quaternion	q;

	q.s = (argQ1.s * argQ2.s) - (argQ1.v * argQ2.v);
	q.v = (argQ1.s * argQ2.v) + (argQ2.s * argQ1.v) + (argQ1.v ^ argQ2.v);

	return q;
}

fk_Quaternion operator +(const fk_Quaternion &argQ1,
						 const fk_Quaternion &argQ2)
{
	fk_Quaternion q;

	q.s = argQ1.s + argQ2.s;
	q.v = argQ1.v + argQ2.v;

	return q;
}

fk_Quaternion operator -(const fk_Quaternion &argQ1,
						 const fk_Quaternion &argQ2)
{
	fk_Quaternion q;

	q.s = argQ1.s - argQ2.s;
	q.v = argQ1.v - argQ2.v;

	return q;
}

fk_Quaternion operator *(const fk_Quaternion &argQ, double argD)
{
	fk_Quaternion q;

	q.s = argQ.s * argD;
	q.v = argQ.v * argD;
	return q;
}

fk_Quaternion operator *(double argD, const fk_Quaternion &argQ)
{
	fk_Quaternion q;

	q.s = argQ.s * argD;
	q.v = argQ.v * argD;
	return q;
}

fk_Quaternion operator /(const fk_Quaternion &argQ, double argD)
{
	fk_Quaternion q;

	q.s = argQ.s / argD;
	q.v = argQ.v / argD;
	return q;
}

fk_Vector operator *(const fk_Quaternion &argQ, const fk_Vector &argV)
{
	fk_Vector v, tmpV1, tmpV2, tmpV3;

	tmpV1 = ((argQ.s*argQ.s) - argQ.v.dist2()) * argV;
	tmpV2 = 2.0 * argQ.s * (argQ.v ^ argV);
	tmpV3 = 2.0 * (argQ.v * argV) * argQ.v;
	v = tmpV1 + tmpV2 + tmpV3;
	return v;
}

double operator ^(const fk_Quaternion &argQ1, const fk_Quaternion &argQ2)
{
	return (argQ1.s * argQ2.s + argQ1.v * argQ2.v);
}

fk_Quaternion fk_Q_Inter_Linear(const fk_Quaternion &argQ1,
								const fk_Quaternion &argQ2, double argT)
{
	return fk_Math::quatInterLinear(argQ1, argQ2, argT);
}

fk_Quaternion fk_Q_Inter_Sphere(const fk_Quaternion &argQ1,
								const fk_Quaternion &argQ2, double argT)
{
	return fk_Math::quatInterSphere(argQ1, argQ2, argT);
}
