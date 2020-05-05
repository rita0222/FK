#include <FK/MatAdmin.h>
#include <FK/Quaternion.h>
#include <FK/Math.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

inline bool AlmostZero(double x)
{
	if(x < fk_Vector::MATRIXEPS2 && x > -fk_Vector::MATRIXEPS2) return true;
	return false;
}

inline bool AlmostEqual(double x, double y)
{
	return(AlmostZero(x - y));
}

fk_MatrixAdmin::Member::Member(void) :
	pos(0.0, 0.0, 0.0), vec(0.0, 0.0, -1.0), uvec(0.0, 1.0, 0.0),
	scale(1.0), xScale(1.0), yScale(1.0), zScale(1.0), mode(false)
{
	pos.ispos();
	vec.isvec();
	uvec.isvec();
}

fk_MatrixAdmin::fk_MatrixAdmin(fk_Type argType)
	: fk_BaseObject(argType), _m_MatAdmin(make_unique<Member>())
{
	UpdateMatrix(true);
}

fk_MatrixAdmin::~fk_MatrixAdmin()
{
	return;
}

void fk_MatrixAdmin::UpdateMatrix(bool argAngFlag)
{
	static fk_OrthoMatrix tmp1, tmp2;
	fk_HVector Y;

	if(argAngFlag == true) {
		AdjustVecToAngle();
	}

	tmp1.makeTrans(_m_MatAdmin->pos.x, _m_MatAdmin->pos.y, _m_MatAdmin->pos.z);
	tmp2.makeEuler(_m_MatAdmin->angle.h, _m_MatAdmin->angle.p, _m_MatAdmin->angle.b);

	_m_MatAdmin->M = tmp1*tmp2;
	Y.set(0.0, 1.0, 0.0, 0.0);
	_m_MatAdmin->uvec = _m_MatAdmin->M * Y;

	return;
}

fk_OrthoMatrix fk_MatrixAdmin::OrthonormalMatrix(const fk_Vector &argOrg,
												const fk_Vector &argTop,
												const double argAngle) const
{
	fk_Vector axis;
	fk_Angle ang;
	fk_OrthoMatrix Trans, TransInv, Rot, RotInv;

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
	if(AlmostEqual(_m_MatAdmin->scale, 1.0) == false ||
	   AlmostEqual(_m_MatAdmin->xScale, 1.0) == false ||
	   AlmostEqual(_m_MatAdmin->yScale, 1.0) == false ||
	   AlmostEqual(_m_MatAdmin->zScale, 1.0) == false) {
		_m_MatAdmin->mode = true;
	} else {
		_m_MatAdmin->mode = false;
	}

	return;
}


void fk_MatrixAdmin::AddAngle(fk_Angle *argBaseAng,
							  const fk_Angle *argAddAng) const
{
	argBaseAng->h += argAddAng->h;
	if(argBaseAng->h < -fk_Math::PI) argBaseAng->h += fk_Math::PI;
	else if(argBaseAng->h > fk_Math::PI) argBaseAng->h -= fk_Math::PI;

	argBaseAng->p += argAddAng->p;
	if(argBaseAng->p < -fk_Math::PI) argBaseAng->p += fk_Math::PI;
	else if(argBaseAng->p > fk_Math::PI) argBaseAng->p -= fk_Math::PI;

	argBaseAng->b += argAddAng->b;
	if(argBaseAng->b < -fk_Math::PI) argBaseAng->b += fk_Math::PI;
	else if(argBaseAng->b > fk_Math::PI) argBaseAng->b -= fk_Math::PI;

	return;
}


fk_Vector fk_MatrixAdmin::getPosition(void) const
{
	return _m_MatAdmin->pos;
}

fk_Vector fk_MatrixAdmin::getVec(void) const
{
	return _m_MatAdmin->vec;
}

fk_Vector fk_MatrixAdmin::getUpvec(void) const
{
	return _m_MatAdmin->uvec;
}

fk_Vector fk_MatrixAdmin::getUpVec(void) const
{
	return getUpvec();
}

fk_Angle fk_MatrixAdmin::getAngle(void) const
{
	return _m_MatAdmin->angle;
}

fk_Matrix fk_MatrixAdmin::getMatrix(void) const
{
	fk_Matrix scaleMat, affineMat;

	if(_m_MatAdmin->mode == true) {
		scaleMat.makeScale(_m_MatAdmin->scale * _m_MatAdmin->xScale,
						   _m_MatAdmin->scale * _m_MatAdmin->yScale,
						   _m_MatAdmin->scale * _m_MatAdmin->zScale);
		affineMat = _m_MatAdmin->M * scaleMat;
	} else {
		affineMat = _m_MatAdmin->M;
	}

	return affineMat;
}

fk_Matrix fk_MatrixAdmin::getInvMatrix(void) const
{
	return (!getMatrix());
}

fk_OrthoMatrix fk_MatrixAdmin::getBaseMatrix(void) const
{
	return _m_MatAdmin->M;
}

fk_OrthoMatrix fk_MatrixAdmin::getInvBaseMatrix(void) const
{
	return !_m_MatAdmin->M;
}

bool fk_MatrixAdmin::setScale(const double argScale)
{
	if(fabs(argScale) < fk_Math::EPS) {
		Error::Put("fk_MatrixAdmin", "setScale", 1, "Zero Scale Error.");
		return false;
	}

	_m_MatAdmin->scale = argScale;
	SetScaleMode();

	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::setScale(const double argScale, const fk_Axis argAxis)
{
	if(fabs(argScale) < fk_Math::EPS) {
		Error::Put("fk_MatrixAdmin", "setScale", 2, "Zero Scale Error.");
		return false;
	}

	switch(argAxis) {
	  case fk_Axis::X:
		_m_MatAdmin->xScale = argScale;
		break;
	  case fk_Axis::Y:
		_m_MatAdmin->yScale = argScale;
		break;
	  case fk_Axis::Z:
		_m_MatAdmin->zScale = argScale;
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
	if(fabs(argX) < fk_Math::EPS || fabs(argY) < fk_Math::EPS || fabs(argZ) < fk_Math::EPS) {
		Error::Put("fk_MatrixAdmin", "setScale", 3, "Zero Scale Error.");
		return false;
	}

	_m_MatAdmin->xScale = argX;
	_m_MatAdmin->yScale = argY;
	_m_MatAdmin->zScale = argZ;
	SetScaleMode();
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::prdScale(const double argScale)
{
	if(fabs(argScale * _m_MatAdmin->scale) < fk_Math::EPS) {
		Error::Put("fk_MatrixAdmin", "prdScale", 1, "Zero Scale Error.");
		return false;
	}

	_m_MatAdmin->scale *= argScale;
	SetScaleMode();
	UpdateMatrix(false);

	return true;
}

bool fk_MatrixAdmin::prdScale(const double argScale, const fk_Axis argAxis)
{
	switch(argAxis) {
	  case fk_Axis::X:
		if(fabs(_m_MatAdmin->xScale * argScale) < fk_Math::EPS) {
			Error::Put("fk_MatrixAdmin", "prdScale", 2, "Zero Scale Error.");
			return false;
		}

		_m_MatAdmin->xScale *= argScale;
		break;
	  case fk_Axis::Y:
		if(fabs(_m_MatAdmin->yScale * argScale) < fk_Math::EPS) {
			Error::Put("fk_MatrixAdmin", "prdScale", 2, "Zero Scale Error.");
			return false;
		}

		_m_MatAdmin->yScale *= argScale;
		break;
	  case fk_Axis::Z:
		if(fabs(_m_MatAdmin->zScale * argScale) < fk_Math::EPS) {
			Error::Put("fk_MatrixAdmin", "prdScale", 2, "Zero Scale Error.");
			return false;
		}

		_m_MatAdmin->zScale *= argScale;
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
	if(fabs(_m_MatAdmin->xScale * argX) < fk_Math::EPS ||
	   fabs(_m_MatAdmin->yScale * argY) < fk_Math::EPS ||
	   fabs(_m_MatAdmin->zScale * argZ) < fk_Math::EPS) {
		Error::Put("fk_MatrixAdmin", "prdScale", 3, "Zero Scale Error.");
		return false;
	}

	_m_MatAdmin->xScale *= argX;
	_m_MatAdmin->yScale *= argY;
	_m_MatAdmin->zScale *= argZ;
	SetScaleMode();
	UpdateMatrix(false);

	return true;
}


double fk_MatrixAdmin::getScale(void) const
{
	return _m_MatAdmin->scale;
}

double fk_MatrixAdmin::getScale(const fk_Axis argAxis) const
{
	switch(argAxis) {
	  case fk_Axis::X:
		return _m_MatAdmin->xScale;
	  case fk_Axis::Y:
		return _m_MatAdmin->yScale;
	  case fk_Axis::Z:
		return _m_MatAdmin->zScale;
	}
	return 0.0;
}

bool fk_MatrixAdmin::getScaleMode(void) const
{
	return _m_MatAdmin->mode;
}

bool fk_MatrixAdmin::glRotate_(fk_Vector &argOrg, fk_Axis argAxis, double argAngle)
{
	fk_Matrix Trans, TransInv, Rot;

	Trans.makeTrans(-argOrg);
	TransInv.makeTrans(argOrg);
	Rot.makeRot(argAngle, argAxis);

	_m_MatAdmin->pos.ispos();
	_m_MatAdmin->pos *= TransInv * Rot * Trans;
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

	_m_MatAdmin->pos.ispos();
	_m_MatAdmin->pos *= rotMat;

	UpdateMatrix(false);

	return;
}

bool fk_MatrixAdmin::glRotate_(fk_Vector &argOrg, fk_Vector &argTop, double argAngle)
{
	if(argOrg == argTop) {
		Error::Put("fk_MatrixAdmin", "glRotate", 1, "Zero-Vector Defined.");
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
		Error::Put("fk_MatrixAdmin", "glRotate", 2, "Zero-Vector Defined.");
		return false;
	}

	GlRotate_(org, top, argAngle);
	return true;
}

bool fk_MatrixAdmin::loRotate_(fk_Vector &argOrg, fk_Axis argAxis, double argAngle)
{
	fk_Matrix SelfInv, affineMat, scaleMat;
	fk_Matrix Rot, Trans, TransInv;

	if(_m_MatAdmin->mode == true) {
		scaleMat.makeScale(_m_MatAdmin->scale * _m_MatAdmin->xScale,
						   _m_MatAdmin->scale * _m_MatAdmin->yScale,
						   _m_MatAdmin->scale * _m_MatAdmin->zScale);
		affineMat = _m_MatAdmin->M * scaleMat;
	} else {
		affineMat = _m_MatAdmin->M;
	}

	SelfInv = !affineMat;
	Trans.makeTrans(-argOrg);
	TransInv.makeTrans(argOrg);
	Rot.makeRot(argAngle, argAxis);

	_m_MatAdmin->pos.ispos();
	_m_MatAdmin->pos *= affineMat * TransInv * Rot * Trans * SelfInv;
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

	if(_m_MatAdmin->mode == true) {
		scaleMat.makeScale(_m_MatAdmin->scale * _m_MatAdmin->xScale,
						   _m_MatAdmin->scale * _m_MatAdmin->yScale,
						   _m_MatAdmin->scale * _m_MatAdmin->zScale);
		affineMat = _m_MatAdmin->M * scaleMat;
	} else {
		affineMat = _m_MatAdmin->M;
	}

	SelfInv = !_m_MatAdmin->M;
	rotMat = OrthonormalMatrix(argOrg, argTop, argAngle);
	_m_MatAdmin->pos.ispos();
	_m_MatAdmin->pos *= affineMat * rotMat * SelfInv;

	UpdateMatrix(false);
	return;
}

bool fk_MatrixAdmin::loRotate_(fk_Vector &argOrg, fk_Vector &argTop, double argAngle)
{
	if(argOrg == argTop) {
		Error::Put("fk_MatrixAdmin", "loRotate", 1, "Zero-Vector Defined.");
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
		Error::Put("fk_MatrixAdmin", "loRotate", 2, "Zero-Vector Defined.");
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

	_m_MatAdmin->pos.ispos();
	_m_MatAdmin->pos *= TransInv * Rot * Trans;

	_m_MatAdmin->vec.isvec();
	_m_MatAdmin->vec *= Rot;
	_m_MatAdmin->uvec.isvec();
	_m_MatAdmin->uvec *= Rot;

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

	_m_MatAdmin->pos.ispos();
	_m_MatAdmin->pos *= rotMat;

	_m_MatAdmin->vec.isvec();
	_m_MatAdmin->vec *= rotMat;

	_m_MatAdmin->uvec.isvec();
	_m_MatAdmin->uvec *= rotMat;

	UpdateMatrix(true);
	return;
}

bool fk_MatrixAdmin::glRotateWithVec_(fk_Vector &argOrg, fk_Vector &argTop, double argAngle)
{
	if(argOrg == argTop) {
		Error::Put("fk_MatrixAdmin", "glRotateWithVec", 1, "Zero-Vector Defined.");
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
		Error::Put("fk_MatrixAdmin", "glRotateWithVec", 2, "Zero-Vector Defined.");
		return false;
	}

	GlRotateWithVec_(org, top, argAngle);
	return true;
}

bool fk_MatrixAdmin::loRotateWithVec_(fk_Vector &argOrg, fk_Axis argAxis, double argAngle)
{
	fk_OrthoMatrix SelfInv;
	fk_OrthoMatrix Rot, Trans, TransInv, New;

	SelfInv = !_m_MatAdmin->M;
	Trans.makeTrans(-argOrg);
	TransInv.makeTrans(argOrg);

	Rot.makeRot(argAngle, argAxis);

	New = _m_MatAdmin->M * TransInv * Rot * Trans * SelfInv;
	_m_MatAdmin->pos.ispos();
	_m_MatAdmin->pos *= New;

	_m_MatAdmin->vec.isvec();
	_m_MatAdmin->vec *= New;

	_m_MatAdmin->uvec.isvec();
	_m_MatAdmin->uvec *= New;

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
	SelfInv = !_m_MatAdmin->M;
	New = _m_MatAdmin->M * rotMat * SelfInv;	

	_m_MatAdmin->pos.ispos();
	_m_MatAdmin->pos *= New;

	_m_MatAdmin->vec.isvec();
	_m_MatAdmin->vec *= New;

	_m_MatAdmin->uvec.isvec();
	_m_MatAdmin->uvec *= New;

	UpdateMatrix(true);
}

bool fk_MatrixAdmin::loRotateWithVec_(fk_Vector &argOrg, fk_Vector &argTop, double argAngle)
{
	if(argOrg == argTop) {
		Error::Put("fk_MatrixAdmin", "loRotateWithVec", 1, "Zero-Vector Defined.");
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
		Error::Put("fk_MatrixAdmin", "loRotateWithVec", 2, "Zero-Vector Defined.");
		return false;
	}

	LoRotateWithVec_(org, top, argAngle);
	return true;
}

bool fk_MatrixAdmin::glFocus(fk_Vector argObj)
{
	fk_Vector focusVec;

	// Find out Heading & Pitching
	focusVec = argObj - _m_MatAdmin->pos;
	if(focusVec.isZero() == true) {
		Error::Put("fk_MatrixAdmin", "glFocus", 1, "Zero-Vector Defined.");
		return false;
	}

	VectorToHeadPitch(&_m_MatAdmin->angle, &focusVec);
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
		Error::Put("fk_MatrixAdmin", "loFocus", 1, "Zero-Vector Defined.");
		return false;
	}

	// Make Objective Vector in Global Axis
	RotateLtoG(&glo, &argObj, &_m_MatAdmin->angle);
	if(glo.normalize() == false) {
		Error::Put("fk_MatrixAdmin", "loFocus", 2, "Vector Undefined Error.");
		return false;
	}

	// Find out Heading & Pitching
	VectorToHeadPitch(&_m_MatAdmin->angle, &glo);

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
		Error::Put("fk_MatrixAdmin", "glVec", 1, "Zero-Vector Defined.");
		return false;
	}
	_m_MatAdmin->vec = argVec;
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
		Error::Put("fk_MatrixAdmin", "glUpvec", 1, "Zero-Vector Defined.");
		return false;
	}

	if(fabs(argUpv * fk_Vector(_m_MatAdmin->vec)) <= 1.0 - fk_Vector::MATRIXEPS2) {
		_m_MatAdmin->uvec = argUpv;
		UpdateMatrix(true);
	} else {
		Error::Put("fk_MatrixAdmin", "glUpvec", 2, "Up Vector Parallel Error.");
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

	RotateLtoG(&tmp, &argUpv, &_m_MatAdmin->angle);
	if(tmp.normalize() == false) {
		Error::Put("fk_MatrixAdmin", "loUpvec", 1, "UpVector Undefined Error.");
		return false;
	}

	if(fabs(tmp * fk_Vector(_m_MatAdmin->vec)) <= 1.0 - fk_Vector::MATRIXEPS2) {
		_m_MatAdmin->uvec = tmp;
	} else {
		Error::Put("fk_MatrixAdmin", "loUpvec", 2, "Up Vector Parallel Error.");
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
	_m_MatAdmin->angle = argAng;
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
	RotateLtoG(&_m_MatAdmin->vec, &tmpVec, &_m_MatAdmin->angle);
	RotateLtoG(&_m_MatAdmin->uvec, &tmpUpv, &_m_MatAdmin->angle);

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
	_m_MatAdmin->pos += argVec;
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
	_m_MatAdmin->pos = argVec;
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

	RotateLtoG(&tmp, &argVec, &_m_MatAdmin->angle);
	_m_MatAdmin->pos += tmp;
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
	fk_Matrix M;

	M.makeEuler(argAngle->h, argAngle->p, argAngle->b);
	*retVec = M * (*argVec);

	return;
}

void fk_MatrixAdmin::AngleToVector(fk_Vector *argDirecVec,
								   fk_Vector *argUpVec,
								   const fk_Angle *argAng) const
{
	fk_Vector tmpDirecVec(0.0, 0.0, -1.0);
	fk_Vector tmpUpVec(0.0, 1.0, 0.0);
	fk_Matrix tmpMat;

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
		Error::Put("fk_MatrixAdmin", "VectorToHeadPitch", 1, "Zero Vector Error.");
		return;
	}

	retAngle->p = asin(tmpVec.y);

	if(fabs(tmpVec.z) < fk_Vector::MATRIXEPS) {
		if(fabs(tmpVec.x) < fk_Vector::MATRIXEPS) {
			retAngle->h = 0.0;
		} else if(tmpVec.x > 0.0) {
			retAngle->h = fk_Math::PI/2.0;
		} else {
			retAngle->h = -fk_Math::PI/2.0;
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

	Mx.makeRot(-retAngle->p, fk_Axis::X);
	My.makeRot(retAngle->h, fk_Axis::Y);
	
	tmpUpVec = Mx * My * (*argUpVec);

	if(fabs(tmpUpVec.y) < fk_Vector::MATRIXEPS) {
		if(fabs(tmpUpVec.x) < fk_Vector::MATRIXEPS) {
			retAngle->b = 0.0;
		} else if(tmpUpVec.x > 0.0) {
			retAngle->b = fk_Math::PI/2.0;
		} else {
			retAngle->b = -fk_Math::PI/2.0;
		}
	} else {
		retAngle->b = atan2(tmpUpVec.x, tmpUpVec.y);
	}

	if(retAngle->b < -fk_Math::PI) {
		retAngle->b += fk_Math::PI;
	} else if(retAngle->b > fk_Math::PI) {
		retAngle->b -= fk_Math::PI;
	}

	return;
}

void fk_MatrixAdmin::AdjustAngleToVec(void)
{
	AngleToVector(&_m_MatAdmin->vec, &_m_MatAdmin->uvec, &_m_MatAdmin->angle);
	return;
}

void fk_MatrixAdmin::AdjustVecToAngle(void)
{
	VectorToAngle(&_m_MatAdmin->angle, &_m_MatAdmin->vec, &_m_MatAdmin->uvec);
	return;
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
