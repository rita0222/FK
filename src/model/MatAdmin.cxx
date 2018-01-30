/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
#include <FK/MatAdmin.h>
#include <FK/Quaternion.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

// static fk_HVector fk_dummy_vec;

inline bool AlmostZero(double x)
{
	if(x < FK_MATRIX_EPS && x > -FK_MATRIX_EPS) return true;
	return false;
}

inline bool AlmostEqual(double x, double y)
{
	return(AlmostZero(x - y));
}

fk_MatrixAdmin::fk_MatrixAdmin(fk_ObjectType argType)
	: fk_BaseObject(argType)
{
	Position.set(0.0, 0.0, 0.0);
	Position.ispos();
	Vec.set(0.0, 0.0, -1.0);
	Vec.isvec();
	UpVec.set(0.0, 1.0, 0.0);
	UpVec.isvec();
	xScale = yScale = zScale = Scale = 1.0;
	ScaleMode = false;

	UpdateMatrix(true);
}

fk_MatrixAdmin::~fk_MatrixAdmin()
{
	return;
}

void fk_MatrixAdmin::UpdateMatrix(bool argAngFlag)
{
	static fk_OrthoMatrix	tmp1, tmp2;
	fk_HVector				Y;

	if(argAngFlag == true) {
		AdjustVecToAngle();
	}

	tmp1.makeTrans(Position.x, Position.y, Position.z);
	tmp2.makeEuler(Angle.h, Angle.p, Angle.b);

	OrthoMatrix = tmp1*tmp2;
	Y.set(0.0, 1.0, 0.0, 0.0);
	UpVec = OrthoMatrix * Y;

	return;
}

fk_OrthoMatrix fk_MatrixAdmin::OrthonormalMatrix(const fk_Vector &argOrg,
												const fk_Vector &argTop,
												const double argAngle) const
{
	fk_Vector		axis;
	fk_Angle		ang;
	fk_OrthoMatrix	Trans, TransInv, Rot, RotInv;

	axis = argTop - argOrg;
	Trans.makeTrans(-argOrg);
	TransInv.makeTrans(argOrg);
	VectorToHeadPitch(&ang, &axis);
	RotInv.makeEuler(ang.h, ang.p, 0.0);
	RotInv.inverse();
	ang.b = argAngle;
	Rot.makeEuler(ang.h, ang.p, ang.b);
	return(TransInv * Rot * RotInv * Trans);
}

void fk_MatrixAdmin::SetScaleMode(void)
{
	if(AlmostEqual(Scale, 1.0) == false ||
	   AlmostEqual(xScale, 1.0) == false ||
	   AlmostEqual(yScale, 1.0) == false ||
	   AlmostEqual(zScale, 1.0) == false) {
		ScaleMode = true;
	} else {
		ScaleMode = false;
	}

	return;
}


void fk_MatrixAdmin::AddAngle(fk_Angle *argBaseAng,
							  const fk_Angle *argAddAng) const
{
	argBaseAng->h += argAddAng->h;
	if(argBaseAng->h < -FK_PI) argBaseAng->h += FK_PI;
	else if(argBaseAng->h > FK_PI) argBaseAng->h -= FK_PI;

	argBaseAng->p += argAddAng->p;
	if(argBaseAng->p < -FK_PI) argBaseAng->p += FK_PI;
	else if(argBaseAng->p > FK_PI) argBaseAng->p -= FK_PI;

	argBaseAng->b += argAddAng->b;
	if(argBaseAng->b < -FK_PI) argBaseAng->b += FK_PI;
	else if(argBaseAng->b > FK_PI) argBaseAng->b -= FK_PI;

	return;
}


fk_Vector fk_MatrixAdmin::getPosition(void) const
{
	return Position;
}

fk_Vector fk_MatrixAdmin::getVec(void) const
{
	return Vec;
}

fk_Vector fk_MatrixAdmin::getUpvec(void) const
{
	return UpVec;
}

fk_Vector fk_MatrixAdmin::getUpVec(void) const
{
	return getUpvec();
}

fk_Angle fk_MatrixAdmin::getAngle(void) const
{
	return Angle;
}

fk_Matrix fk_MatrixAdmin::getMatrix(void) const
{
	fk_Matrix	scaleMat, affineMat;

	if(ScaleMode == true) {
		scaleMat.makeScale(Scale*xScale, Scale*yScale, Scale*zScale);
		affineMat = OrthoMatrix * scaleMat;
	} else {
		affineMat = OrthoMatrix;
	}

	return affineMat;
}

fk_Matrix fk_MatrixAdmin::getInvMatrix(void) const
{
	return (!getMatrix());
}

fk_OrthoMatrix fk_MatrixAdmin::getBaseMatrix(void) const
{
	return OrthoMatrix;
}

fk_OrthoMatrix fk_MatrixAdmin::getInvBaseMatrix(void) const
{
	return !OrthoMatrix;
}

bool fk_MatrixAdmin::setScale(const double argScale)
{
	if(fabs(argScale) < FK_EPS) {
		fk_PutError("fk_MatrixAdmin", "setScale", 1,
					"Zero Scale Error.");
		return false;
	}

	Scale = argScale;
	SetScaleMode();

	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::setScale(const double argScale, const fk_Axis argAxis)
{
	if(fabs(argScale) < FK_EPS) {
		fk_PutError("fk_MatrixAdmin", "setScale", 2,
					"Zero Scale Error.");
		return false;
	}

	switch(argAxis) {
	  case fk_X:
		xScale = argScale;
		break;
	  case fk_Y:
		yScale = argScale;
		break;
	  case fk_Z:
		zScale = argScale;
		break;
	  default:
		break;
	}

	SetScaleMode();
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::setScale(const double argX, const double argY,
							  const double argZ)
{
	if(fabs(argX) < FK_EPS || fabs(argY) < FK_EPS || fabs(argZ) < FK_EPS) {
		fk_PutError("fk_MatrixAdmin", "setScale", 3,
					"Zero Scale Error.");
		return false;
	}

	xScale = argX;
	yScale = argY;
	zScale = argZ;
	SetScaleMode();
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::prdScale(const double argScale)
{
	if(fabs(argScale * Scale) < FK_EPS) {
		fk_PutError("fk_MatrixAdmin", "prdScale", 1,
					"Zero Scale Error.");
		return false;
	}

	Scale *= argScale;
	SetScaleMode();
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::prdScale(const double argScale, const fk_Axis argAxis)
{
	switch(argAxis) {
	  case fk_X:
		if(fabs(xScale * argScale) < FK_EPS) {
			fk_PutError("fk_MatrixAdmin", "prdScale", 2,
						"Zero Scale Error.");
			return false;
		}

		xScale *= argScale;
		break;
	  case fk_Y:
		if(fabs(yScale * argScale) < FK_EPS) {
			fk_PutError("fk_MatrixAdmin", "prdScale", 2,
						"Zero Scale Error.");
			return false;
		}

		yScale *= argScale;
		break;
	  case fk_Z:
		if(fabs(zScale * argScale) < FK_EPS) {
			fk_PutError("fk_MatrixAdmin", "prdScale", 2,
						"Zero Scale Error.");
			return false;
		}

		zScale *= argScale;
		break;
	  default:
		break;
	}

	SetScaleMode();
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::prdScale(const double argX, const double argY,
							  const double argZ)
{
	if(fabs(xScale * argX) < FK_EPS ||
	   fabs(yScale * argY) < FK_EPS ||
	   fabs(zScale * argZ) < FK_EPS) {
		fk_PutError("fk_MatrixAdmin", "prdScale", 3,
					"Zero Scale Error.");
		return false;
	}

	xScale *= argX;
	yScale *= argY;
	zScale *= argZ;
	SetScaleMode();
	UpdateMatrix(false);

	return true;
}


double fk_MatrixAdmin::getScale(void) const
{
	return Scale;
}

double fk_MatrixAdmin::getScale(const fk_Axis argAxis) const
{
	switch(argAxis) {
	  case fk_X:
		return xScale;
	  case fk_Y:
		return yScale;
	  case fk_Z:
		return zScale;
	}
	return 0.0;
}

bool fk_MatrixAdmin::getScaleMode(void) const
{
	return ScaleMode;
}

bool fk_MatrixAdmin::glRotate_(fk_Vector &argOrg, fk_Axis argAxis, double argAngle)
{
	fk_Matrix Trans, TransInv, Rot;

	Trans.makeTrans(-argOrg);
	TransInv.makeTrans(argOrg);
	Rot.makeRot(argAngle, argAxis);

	Position.ispos();
	Position *= TransInv * Rot * Trans;
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::glRotate_(double argX, double argY, double argZ,
							   fk_Axis argAxis, double argAngle)
{
	fk_Vector org(argX, argY, argZ);
	glRotate_(org, argAxis, argAngle);

	return true;
}

void fk_MatrixAdmin::GlRotate_(const fk_Vector &argOrg, const fk_Vector &argTop, double argAngle)
{
	fk_OrthoMatrix rotMat = OrthonormalMatrix(argOrg, argTop, argAngle);

	Position.ispos();
	Position *= rotMat;

	UpdateMatrix(false);

	return;
}

bool fk_MatrixAdmin::glRotate_(fk_Vector &argOrg, fk_Vector &argTop, double argAngle)
{
	if(argOrg == argTop) {
		fk_PutError("fk_MatrixAdmin", "glRotate", 1,
					"Zero-Vector Defined.");
		return false;
	}

	GlRotate_(argOrg, argTop, argAngle);

	return true;
}

bool fk_MatrixAdmin::glRotate_(double argOX, double argOY, double argOZ,
							   double argTX, double argTY, double argTZ, double argAngle)
{
	fk_Vector org, top;

	org.set(argOX, argOY, argOZ);
	top.set(argTX, argTY, argTZ);
	if(org == top) {
		fk_PutError("fk_MatrixAdmin", "glRotate", 2,
					"Zero-Vector Defined.");
		return false;
	}

	GlRotate_(org, top, argAngle);
	return true;
}

bool fk_MatrixAdmin::loRotate_(fk_Vector &argOrg, fk_Axis argAxis, double argAngle)
{
	fk_Matrix SelfInv, affineMat, scaleMat;
	fk_Matrix Rot, Trans, TransInv;

	if(ScaleMode == true) {
		scaleMat.makeScale(Scale*xScale, Scale*yScale, Scale*zScale);
		affineMat = OrthoMatrix * scaleMat;
	} else {
		affineMat = OrthoMatrix;
	}

	SelfInv = !affineMat;
	Trans.makeTrans(-argOrg);
	TransInv.makeTrans(argOrg);
	Rot.makeRot(argAngle, argAxis);

	Position.ispos();
	Position *= affineMat * TransInv * Rot * Trans * SelfInv;
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::loRotate_(double argX, double argY, double argZ,
							   fk_Axis argAxis, double argAngle)
{
	fk_Vector org;

	org.set(argX, argY, argZ);
	loRotate_(org, argAxis, argAngle);

	return true;
}

void fk_MatrixAdmin::LoRotate_(const fk_Vector &argOrg, const fk_Vector &argTop, double argAngle)
{
	fk_OrthoMatrix	SelfInv;
	fk_OrthoMatrix	rotMat;
	fk_Matrix		scaleMat, affineMat;

	if(ScaleMode == true) {
		scaleMat.makeScale(Scale*xScale, Scale*yScale, Scale*zScale);
		affineMat = OrthoMatrix * scaleMat;
	} else {
		affineMat = OrthoMatrix;
	}

	SelfInv = !OrthoMatrix;
	rotMat = OrthonormalMatrix(argOrg, argTop, argAngle);
	Position.ispos();
	Position *= affineMat * rotMat * SelfInv;

	UpdateMatrix(false);
	return;
}

bool fk_MatrixAdmin::loRotate_(fk_Vector &argOrg, fk_Vector &argTop, double argAngle)
{
	if(argOrg == argTop) {
		fk_PutError("fk_MatrixAdmin", "loRotate", 1,
					"Zero-Vector Defined.");
		return false;
	}

	LoRotate_(argOrg, argTop, argAngle);
	return true;
}

bool fk_MatrixAdmin::loRotate_(double argOX, double argOY, double argOZ,
							   double argTX, double argTY, double argTZ, double argAngle)
{
	fk_Vector org, top;

	org.set(argOX, argOY, argOZ);
	top.set(argTX, argTY, argTZ);

	if(org == top) {
		fk_PutError("fk_MatrixAdmin", "loRotate", 2,
					"Zero-Vector Defined.");
		return false;
	}

	LoRotate_(org, top, argAngle);
	return true;
}

bool fk_MatrixAdmin::glRotateWithVec_(fk_Vector &argOrg, fk_Axis argAxis, double argAngle)
{
	fk_Matrix Rot, Trans, TransInv;

	Trans.makeTrans(-argOrg);
	TransInv.makeTrans(argOrg);

	Rot.makeRot(argAngle, argAxis);

	Position.ispos();
	Position *= TransInv * Rot * Trans;

	Vec.isvec();
	Vec *= Rot;
	UpVec.isvec();
	UpVec *= Rot;

	UpdateMatrix(true);
	return true;
}

bool fk_MatrixAdmin::glRotateWithVec_(double argX, double argY, double argZ,
									  fk_Axis argAxis, double argAngle)
{
	fk_Vector org;

	org.set(argX, argY, argZ);
	glRotateWithVec_(org, argAxis, argAngle);
	return true;
}

void fk_MatrixAdmin::GlRotateWithVec_(const fk_Vector &argOrg,
									  const fk_Vector &argTop, double argAngle)
{
	fk_Matrix rotMat;

	rotMat = OrthonormalMatrix(argOrg, argTop, argAngle);

	Position.ispos();
	Position *= rotMat;

	Vec.isvec();
	Vec *= rotMat;

	UpVec.isvec();
	UpVec *= rotMat;

	UpdateMatrix(true);
	return;
}

bool fk_MatrixAdmin::glRotateWithVec_(fk_Vector &argOrg, fk_Vector &argTop, double argAngle)
{
	if(argOrg == argTop) {
		fk_PutError("fk_MatrixAdmin", "glRotateWithVec", 1,
					"Zero-Vector Defined.");
		return false;
	}

	GlRotateWithVec_(argOrg, argTop, argAngle);
	return true;
}

bool fk_MatrixAdmin::glRotateWithVec_(double argOX, double argOY, double argOZ,
									  double argTX, double argTY, double argTZ, double argAngle)
{
	fk_Vector org, top;

	org.set(argOX, argOY, argOZ);
	top.set(argTX, argTY, argTZ);

	if(org == top) {
		fk_PutError("fk_MatrixAdmin", "glRotateWithVec", 2,
					"Zero-Vector Defined.");
		return false;
	}

	GlRotateWithVec_(org, top, argAngle);
	return true;
}

bool fk_MatrixAdmin::loRotateWithVec_(fk_Vector &argOrg, fk_Axis argAxis, double argAngle)
{
	fk_OrthoMatrix SelfInv;
	fk_OrthoMatrix Rot, Trans, TransInv, New;

	SelfInv = !OrthoMatrix;
	Trans.makeTrans(-argOrg);
	TransInv.makeTrans(argOrg);

	Rot.makeRot(argAngle, argAxis);

	New = OrthoMatrix * TransInv * Rot * Trans * SelfInv;
	Position.ispos();
	Position *= New;

	Vec.isvec();
	Vec *= New;

	UpVec.isvec();
	UpVec *= New;

	UpdateMatrix(true);

	return true;
}

bool fk_MatrixAdmin::loRotateWithVec_(double argX, double argY, double argZ,
									  fk_Axis argAxis, double argAngle)
{
	fk_Vector org;

	org.set(argX, argY, argZ);
	loRotateWithVec_(org, argAxis, argAngle);

	return true;
}

void fk_MatrixAdmin::LoRotateWithVec_(const fk_Vector &argOrg,
									  const fk_Vector &argTop, double argAngle)
{
	fk_OrthoMatrix rotMat;
	fk_OrthoMatrix SelfInv;
	fk_OrthoMatrix New;

	rotMat = OrthonormalMatrix(argOrg, argTop, argAngle);
	SelfInv = !OrthoMatrix;
	New = OrthoMatrix * rotMat * SelfInv;	

	Position.ispos();
	Position *= New;

	Vec.isvec();
	Vec *= New;

	UpVec.isvec();
	UpVec *= New;

	UpdateMatrix(true);
}

bool fk_MatrixAdmin::loRotateWithVec_(fk_Vector &argOrg, fk_Vector &argTop, double argAngle)
{
	if(argOrg == argTop) {
		fk_PutError("fk_MatrixAdmin", "loRotateWithVec", 1,
					"Zero-Vector Defined.");
		return false;
	}

	LoRotateWithVec_(argOrg, argTop, argAngle);
	return true;
}

bool fk_MatrixAdmin::loRotateWithVec_(double argOX, double argOY, double argOZ,
									  double argTX, double argTY, double argTZ, double argAngle)
{
	fk_Vector org, top;

	org.set(argOX, argOY, argOZ);
	top.set(argTX, argTY, argTZ);
	if(org == top) {
		fk_PutError("fk_MatrixAdmin", "loRotateWithVec", 2,
					"Zero-Vector Defined.");
		return false;
	}

	LoRotateWithVec_(org, top, argAngle);
	return true;
}

bool fk_MatrixAdmin::glFocus(fk_Vector argObj)
{
	fk_Vector focusVec;

	// Find out Heading & Pitching
	focusVec = argObj - Position;
	if(focusVec.isZero() == true) {
		fk_PutError("fk_MatrixAdmin", "glFocus", 1,
					"Zero-Vector Defined.");
		return false;
	}

	VectorToHeadPitch(&Angle, &focusVec);
	AdjustAngleToVec();
	UpdateMatrix(true);
	return true;
}

bool fk_MatrixAdmin::glFocus(double argX, double argY, double argZ)
{
	fk_Vector tmp(argX, argY, argZ);
	return glFocus(tmp);
}

bool fk_MatrixAdmin::loFocus(fk_Vector argObj)
{
	fk_Vector glo;

	if(argObj.isZero() == true) {
		fk_PutError("fk_MatrixAdmin", "loFocus", 1,
					"Zero-Vector Defined.");
		return false;
	}

	// Make Objective Vector in Global Axis
	RotateLtoG(&glo, &argObj, &Angle);
	if(glo.normalize() == false) {
		fk_PutError("fk_MatrixAdmin", "loFocus", 2, "Vector Undefined Error.");
		return false;
	}

	// Find out Heading & Pitching
	VectorToHeadPitch(&Angle, &glo);

	AdjustAngleToVec();
	UpdateMatrix(true);

	return true;
}

bool fk_MatrixAdmin::loFocus(double argX, double argY, double argZ)
{
	fk_Vector tmp(argX, argY, argZ);
	return loFocus(tmp);
}

bool fk_MatrixAdmin::glVec(fk_Vector argVec)
{
	if(argVec.normalize() == false) {
		fk_PutError("fk_MatrixAdmin", "glVec", 1, "Zero-Vector Defined.");
		return false;
	}
	Vec = argVec;
	UpdateMatrix(true);

	return true;
}

bool fk_MatrixAdmin::glVec(double argX, double argY, double argZ)
{
	fk_Vector	tmpVec(argX, argY, argZ);

	return glVec(tmpVec);
}

bool fk_MatrixAdmin::glUpvec(fk_Vector argUpv)
{
	if(argUpv.normalize() == false) {
		fk_PutError("fk_MatrixAdmin", "glUpvec", 1, "Zero-Vector Defined.");
		return false;
	}

	if(fabs(argUpv * fk_Vector(Vec)) <= 1.0 - FK_EPS) {
		UpVec = argUpv;
		UpdateMatrix(true);
	} else {
		fk_PutError("fk_MatrixAdmin", "glUpvec", 2,
					"Up Vector Parallel Error.");
		return false;
	}

	return true;
}

bool fk_MatrixAdmin::glUpvec(double argX, double argY, double argZ)
{
	fk_Vector tmp(argX, argY, argZ);
	return glUpvec(tmp);
}

bool fk_MatrixAdmin::loUpvec(fk_Vector argUpv)
{
	fk_Vector tmp;

	RotateLtoG(&tmp, &argUpv, &Angle);
	if(tmp.normalize() == false) {
		fk_PutError("fk_MatrixAdmin", "loUpvec", 1,
					"UpVector Undefined Error.");
		return false;
	}

	if(fabs(tmp * fk_Vector(Vec)) <= 1.0 - FK_EPS) {
		UpVec = tmp;
	} else {
		fk_PutError("fk_MatrixAdmin", "loUpvec", 2,
					"Up Vector Parallel Error.");
		return false;
	}
	UpdateMatrix(true);
	return true;
}

bool fk_MatrixAdmin::loUpvec(double argX, double argY, double argZ)
{
	fk_Vector tmp;

	tmp.set(argX, argY, argZ);
	return loUpvec(tmp);
}

bool fk_MatrixAdmin::glAngle(fk_Angle argAng)
{
	Angle = argAng;
	AdjustAngleToVec();
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::glAngle(double argH, double argP, double argB)
{
	fk_Angle tmp;
	tmp.h = argH;
	tmp.p = argP;
	tmp.b = argB;

	return glAngle(tmp);
}
	
bool fk_MatrixAdmin::loAngle(fk_Angle argAng) // Pitching & Yawing
{
	fk_Vector tmpVec, tmpUpv;

	// Find out Eye Vector & Up Vector in Global Axis

	AngleToVector(&tmpVec, &tmpUpv, &argAng);
	RotateLtoG(&Vec, &tmpVec, &Angle);
	RotateLtoG(&UpVec, &tmpUpv, &Angle);

	UpdateMatrix(true);
	return true;
}

bool fk_MatrixAdmin::loAngle(double argH, double argP, double argB)
{
	fk_Angle tmp;
	tmp.h = argH;
	tmp.p = argP;
	tmp.b = argB;

	return loAngle(tmp);
}

bool fk_MatrixAdmin::glTranslate_(fk_Vector &argVec)
{
	Position += argVec;
	UpdateMatrix(false);
	return true;
}

bool fk_MatrixAdmin::glTranslate_(double argX, double argY, double argZ)
{
	fk_Vector tmp(argX, argY, argZ);
	return glTranslate_(tmp);
}

bool fk_MatrixAdmin::glMoveTo_(fk_Vector &argVec)
{
	Position = argVec;
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::glMoveTo_(double argX, double argY, double argZ)
{
	fk_Vector tmp(argX, argY, argZ);
	return glMoveTo_(tmp);
}

bool fk_MatrixAdmin::loTranslate_(fk_Vector &argVec)
{
	fk_Vector tmp;

	RotateLtoG(&tmp, &argVec, &Angle);
	Position += tmp;
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::loTranslate_(double argX, double argY, double argZ)
{
	fk_Vector tmp(argX, argY, argZ);
	return loTranslate_(tmp);
}

void fk_MatrixAdmin::RotateLtoG(fk_Vector *retVec, const fk_Vector *argVec,
								const fk_Angle *argAngle) const
{
	fk_Matrix	M;

	M.makeEuler(argAngle->h, argAngle->p, argAngle->b);
	*retVec = M * (*argVec);

	return;
}

void fk_MatrixAdmin::AngleToVector(fk_Vector *argDirecVec,
								   fk_Vector *argUpVec,
								   const fk_Angle *argAng) const
{
	fk_Vector	tmpDirecVec(0.0, 0.0, -1.0);
	fk_Vector	tmpUpVec(0.0, 1.0, 0.0);
	fk_Matrix	tmpMat;

	tmpMat.makeEuler(argAng->h, argAng->p, argAng->b);
	*argDirecVec = tmpMat * tmpDirecVec;
	*argUpVec = tmpMat * tmpUpVec;

	return;
}

void fk_MatrixAdmin::VectorToHeadPitch(fk_Angle *retAngle,
									   const fk_Vector *argVec) const
{
	fk_Vector	tmpVec;

	tmpVec = *argVec;
	if(tmpVec.normalize() == false) {
		fk_PutError("fk_MatrixAdmin", "VectorToHeadPitch", 1,
					"Zero Vector Error.");
		return;
	}

	retAngle->p = asin(tmpVec.y);

	if(fabs(tmpVec.z) < FK_EPS) {
		if(fabs(tmpVec.x) < FK_EPS) {
			retAngle->h = 0.0;
		} else if(tmpVec.x > 0.0) {
			retAngle->h = FK_PI/2.0;
		} else {
			retAngle->h = -FK_PI/2.0;
		}
	} else {
		retAngle->h = atan2(tmpVec.x, -tmpVec.z);
	}

	return;
}

void fk_MatrixAdmin::VectorToAngle(fk_Angle *retAngle,
								   const fk_Vector *argDirecVec,
								   const fk_Vector *argUpVec) const
{
	fk_Vector	tmpUpVec;
	fk_Matrix	Mx, My;

	VectorToHeadPitch(retAngle, argDirecVec);

	Mx.makeRot(-retAngle->p, fk_X);
	My.makeRot(retAngle->h, fk_Y);
	
	tmpUpVec = Mx * My * (*argUpVec);

	if(fabs(tmpUpVec.y) < FK_EPS) {
		if(fabs(tmpUpVec.x) < FK_EPS) {
			retAngle->b = 0.0;
		} else if(tmpUpVec.x > 0.0) {
			retAngle->b = FK_PI/2.0;
		} else {
			retAngle->b = -FK_PI/2.0;
		}
	} else {
		retAngle->b = atan2(tmpUpVec.x, tmpUpVec.y);
	}

	if(retAngle->b < -FK_PI) {
		retAngle->b += FK_PI;
	} else if(retAngle->b > FK_PI) {
		retAngle->b -= FK_PI;
	}

	return;
}

void fk_MatrixAdmin::AdjustAngleToVec(void)
{
	AngleToVector(&Vec, &UpVec, &Angle);
	return;
}

void fk_MatrixAdmin::AdjustVecToAngle(void)
{
	VectorToAngle(&Angle, &Vec, &UpVec);
	return;
}
