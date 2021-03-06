﻿#include <FK/Model.h>
#include <FK/Material.h>
#include <FK/Shape.h>
#include <FK/Tree.h>
#include <FK/Quaternion.h>
#include <FK/BoundaryElem.H>
#include <FK/Math.h>
#include <algorithm>

using namespace std;
using namespace FK;

using mi = list<fk_Model *>::iterator;

unsigned int fk_Model::globalModelID = 1;

namespace FK {
	fk_DepthMode operator | (fk_DepthMode argL, fk_DepthMode argR) {
		return static_cast<fk_DepthMode>(static_cast<unsigned int>(argL) |
										static_cast<unsigned int>(argR));
	}

	fk_DepthMode operator & (fk_DepthMode argL, fk_DepthMode argR) {
		return static_cast<fk_DepthMode>(static_cast<unsigned int>(argL) &
										static_cast<unsigned int>(argR));
	}

	fk_DepthMode operator ^ (fk_DepthMode argL, fk_DepthMode argR) {
		return static_cast<fk_DepthMode>(static_cast<unsigned int>(argL) ^
										static_cast<unsigned int>(argR));
	}
}

fk_Model::Member::Member(void) :
	shape(nullptr), parentModel(nullptr),
	treeData(nullptr), drawMode(fk_Draw::NONE), elemMode(fk_ElementMode::MODEL),
	depthMode(fk_DepthMode::READ_AND_WRITE), pointSize(1.0),
	smoothFlag(false), reverseFlag(false),
	treeFlag(false), modelID(globalModelID), treeDelMode(true),
	texMode(fk_TexMode::NONE), shadingMode(fk_ShadingMode::PHONG),
	snapFlag(false), interMode(false), interStatus(false), interStopMode(false),
	shader(nullptr), shadowEffectMode(true), shadowDrawMode(true), fogMode(true)
{
	return;
}

fk_Model::fk_Model(fk_Shape *argShape) :
	fk_Boundary(fk_Type::MODEL), _m(make_unique<Member>())
{
	setBlendMode(fk_BlendMode::ALPHA);
	setShape(argShape);

	return;
}

fk_Model::~fk_Model()
{
	DeleteTree();

	return;
}

void fk_Model::setShape(fk_Shape *argShape)
{
	bool	drawModeFlag;

	if(argShape == nullptr) {
		_m->shape = nullptr;
		return;
	}

	if(_m->shape == nullptr) {
		drawModeFlag = true;
	} else if(_m->shape->getObjectType() != argShape->getObjectType()) {
		drawModeFlag = true;
	} else {
		drawModeFlag = false;
	}

	fk_Type type = argShape->getObjectType();
	if(drawModeFlag == true) {
		switch(type) {
		  case fk_Type::POINT:
		  case fk_Type::PARTICLESET:
			_m->drawMode = fk_Draw::POINT;
			break;

		  case fk_Type::LINE:
		  case fk_Type::POLYLINE:
		  case fk_Type::CLOSEDLINE:
			_m->drawMode = fk_Draw::LINE;
			break;
			 
		  case fk_Type::POLYGON:
		  case fk_Type::BLOCK:
		  case fk_Type::CIRCLE:
		  case fk_Type::SPHERE:
		  case fk_Type::PRISM:
		  case fk_Type::CONE:
		  case fk_Type::CAPSULE:
		  case fk_Type::SOLID:
		  case fk_Type::INDEXFACESET:
			_m->drawMode = fk_Draw::FACE;
			break;

		  case fk_Type::RECTTEXTURE:
		  case fk_Type::TRITEXTURE:
		  case fk_Type::MESHTEXTURE:
		  case fk_Type::IFSTEXTURE:
		  case fk_Type::ARTEXTURE:
			_m->drawMode = fk_Draw::TEXTURE;
			break;

		  default:
			_m->drawMode = fk_Draw::NONE;
			break;
		}
	}
	_m->shape = argShape;

	return;
}

void fk_Model::setMaterial(const fk_Material &argMate)
{
	_m->material = argMate;
	return;
}

void fk_Model::setPointColor(fk_Color *argColor)
{
	if(argColor == nullptr) return;
	setPointColor(argColor->getR(), argColor->getG(), argColor->getB());
	return;
}

void fk_Model::setPointColor(float argR, float argG, float argB)
{
	_m->pointColor.set(argR, argG, argB);
	return;
}

void fk_Model::setLineColor(fk_Color *argColor)
{
	if(argColor == nullptr) return;
	setLineColor(argColor->getR(), argColor->getG(), argColor->getB());
	return;
}

void fk_Model::setLineColor(float argR, float argG, float argB)
{
	_m->lineColor.set(argR, argG, argB);
	return;
}

void fk_Model::setCurveColor(fk_Color *argColor)
{
	if(argColor == nullptr) return;
	setCurveColor(argColor->getR(), argColor->getG(), argColor->getB());
	return;
}
void fk_Model::setCurveColor(float argR, float argG, float argB)
{
	_m->curveColor.set(argR, argG, argB);
	return;
}

fk_Shape * fk_Model::getShape(void) const
{
	return _m->shape;
}

fk_Material * fk_Model::getMaterial(void)
{
	return &(_m->material);
}

fk_Color * fk_Model::getPointColor(void)
{
	return &(_m->pointColor);
}

fk_Color * fk_Model::getLineColor(void)
{
	return &(_m->lineColor);
}

fk_Color * fk_Model::getCurveColor(void)
{
	return &(_m->curveColor);
}

void fk_Model::setDrawMode(const fk_Draw argMode)
{
	if(_m->drawMode == argMode) return;
	_m->drawMode = argMode;
	if(_m->shape != nullptr) {
		_m->shape->ForceUpdateAttr();
	}
	return;
}

fk_Draw fk_Model::getDrawMode(void) const
{
	return _m->drawMode;
}

void fk_Model::setElementMode(const fk_ElementMode argMode)
{
	_m->elemMode = argMode;
}

fk_ElementMode fk_Model::getElementMode(void) const
{
	return _m->elemMode;
}

void fk_Model::setMaterialMode(const fk_MaterialMode) {}
fk_MaterialMode fk_Model::getMaterialMode(void) const { return fk_MaterialMode::PARENT; }

void fk_Model::setBlendMode(const fk_BlendMode argMode,
							const fk_BlendFactor argSrcFactor,
							const fk_BlendFactor argDstFactor)
{
	switch(argMode) {
	  case fk_BlendMode::ALPHA:
		_m->srcFactor = fk_BlendFactor::SRC_ALPHA;
		_m->dstFactor = fk_BlendFactor::ONE_MINUS_SRC_ALPHA;
		break;

	  case fk_BlendMode::NEGATIVE:
		_m->srcFactor = fk_BlendFactor::ONE_MINUS_DST_COLOR;
		_m->dstFactor = fk_BlendFactor::ZERO;
		break;

	  case fk_BlendMode::ADDITION:
		_m->srcFactor = fk_BlendFactor::ONE;
		_m->dstFactor = fk_BlendFactor::ONE;
		break;

	  case fk_BlendMode::SCREEN:
		_m->srcFactor = fk_BlendFactor::SRC_ALPHA;
		_m->dstFactor = fk_BlendFactor::ONE;
		break;

	  case fk_BlendMode::LIGHTEN:
		_m->srcFactor = fk_BlendFactor::ONE_MINUS_DST_COLOR;
		_m->dstFactor = fk_BlendFactor::ONE;
		break;

	  case fk_BlendMode::MULTIPLY:
		_m->srcFactor = fk_BlendFactor::ZERO;
		_m->dstFactor = fk_BlendFactor::SRC_COLOR;
		break;

	  case fk_BlendMode::NONE:
		_m->srcFactor = fk_BlendFactor::ONE;
		_m->dstFactor = fk_BlendFactor::ZERO;
		break;

	  case fk_BlendMode::CUSTOM:
		_m->srcFactor = argSrcFactor;
		_m->dstFactor = argDstFactor;
		break;

	  default:
		return;
	}

	_m->blendMode = argMode;
	return;
}

fk_BlendMode fk_Model::getBlendMode(fk_BlendFactor *argOutSrc, fk_BlendFactor *argOutDst) const
{
	if (argOutSrc != nullptr) *argOutSrc = _m->srcFactor;
	if (argOutDst != nullptr) *argOutDst = _m->dstFactor;
	return _m->blendMode;
}

void fk_Model::setDepthMode(const fk_DepthMode argMode)
{
	_m->depthMode = argMode;
}

fk_DepthMode fk_Model::getDepthMode(void) const
{
	return _m->depthMode;
}

fk_Matrix fk_Model::getInhMatrix(void) const
{
	if(_m->parentModel == nullptr) return getMatrix();
	return (_m->parentModel->getInhMatrix() * getMatrix());
}

fk_Matrix fk_Model::getInhInvMatrix(void) const
{
	if(_m->parentModel == nullptr) return getInvMatrix();
	return (getInvMatrix() * _m->parentModel->getInhInvMatrix());
}

fk_OrthoMatrix fk_Model::getInhBaseMatrix(void) const
{
	if(_m->parentModel == nullptr) return _m_MatAdmin->M;
	return (_m->parentModel->getInhBaseMatrix() * _m_MatAdmin->M);
}

fk_OrthoMatrix fk_Model::getInhInvBaseMatrix(void) const
{
	fk_OrthoMatrix RetMat = _m_MatAdmin->M;
	RetMat.inverse();
	if(_m->parentModel == nullptr) return RetMat;
	return (_m->parentModel->getInhInvBaseMatrix() * RetMat);
}

fk_Vector fk_Model::getInhPosition(void) const
{
	fk_Vector retVec;

	if(_m->parentModel == nullptr) {
		retVec = _m_MatAdmin->pos;
	} else {
		retVec = _m->parentModel->getInhMatrix() * _m_MatAdmin->pos;
	}
	return retVec;
}

fk_Vector fk_Model::getInhVec(void) const
{
	fk_HVector hvec(_m_MatAdmin->vec);

	if(_m->parentModel == nullptr) return _m_MatAdmin->vec;

	hvec.isvec();
	return (_m->parentModel->getInhMatrix() * hvec);
}
	
fk_Vector fk_Model::getInhUpvec(void) const
{
	fk_HVector hvec(_m_MatAdmin->uvec);

	if(_m->parentModel == nullptr) return _m_MatAdmin->uvec;
	
	hvec.isvec();
	return (_m->parentModel->getInhMatrix() * hvec);
}

fk_Vector fk_Model::getInhUpVec(void) const
{
	return getInhUpvec();
}

fk_Angle fk_Model::getInhAngle(void) const
{
	fk_Angle retAngle;
	fk_Vector vec, upvec;

	if(_m->parentModel == nullptr) return _m_MatAdmin->angle;
	vec = getInhVec();
	upvec = getInhUpVec();
	VectorToAngle(&retAngle, &vec, &upvec);
	return retAngle;
}

double fk_Model::getInhScale(void) const
{
	if(_m->parentModel == nullptr) {
		return _m_MatAdmin->scale;
	}
	return (_m->parentModel->getInhScale() * _m_MatAdmin->scale);
}

void fk_Model::setPointSize(const double argSize)
{
	if(argSize <= fk_Math::EPS) return;
	_m->pointSize = argSize;
	return;
}

void fk_Model::setSize(const double argSize)
{
	setPointSize(argSize);
}

void fk_Model::setWidth(const double)
{
	return;
}

double fk_Model::getPointSize(void) const
{
	return _m->pointSize;
}

double fk_Model::getSize(void) const
{
	return getPointSize();
}

double fk_Model::getWidth(void) const
{
	return 0.0;
}

#ifndef _FREEBSD_

void fk_Model::setSmoothMode(const bool argFlg)
{
	_m->smoothFlag = argFlg;
	return;
}

#else

void fk_Model::setSmoothMode(const bool)
{
	return;
}

#endif

bool fk_Model::getSmoothMode(void) const
{
	return _m->smoothFlag;
}

void fk_Model::setReverseDrawMode(const bool argFlg)
{
	_m->reverseFlag = argFlg;
	return;
}

bool fk_Model::getReverseDrawMode(void) const
{
	return _m->reverseFlag;
}

void fk_Model::setTextureMode(fk_TexMode argMode)
{
	_m->texMode = argMode;
}

fk_TexMode fk_Model::getTextureMode(void)
{
	return _m->texMode;
}

void fk_Model::setShadingMode(fk_ShadingMode argMode)
{
	_m->shadingMode = argMode;
}

fk_ShadingMode fk_Model::getShadingMode(void) const
{
	return _m->shadingMode;
}

unsigned int fk_Model::getID(void) const
{
	return _m->modelID;
}

void fk_Model::snapShot(void)
{
	if(_m->snapPos == nullptr) _m->snapPos = make_unique<fk_HVector>();
	*(_m->snapPos) = _m_MatAdmin->pos;

	if(_m->snapInhPos == nullptr) _m->snapInhPos = make_unique<fk_HVector>();
	*(_m->snapInhPos) = getInhPosition();

	if(_m->snapAngle == nullptr) _m->snapAngle = make_unique<fk_Angle>();
	*(_m->snapAngle) = _m_MatAdmin->angle;

	_m->snapFlag = true;
	return;
}

bool fk_Model::restore(void)
{
	if(_m->snapFlag == false) return false;

	_m_MatAdmin->angle = *(_m->snapAngle);
	_m_MatAdmin->pos = *(_m->snapPos);
	AdjustAngleToVec();
	UpdateMatrix(false);

	return true;
}

bool fk_Model::restore(double argT)
{
	fk_Quaternion qOrg, qNew, qRet;

	if(_m->snapFlag == false) return false;
	if(argT < fk_Math::EPS || argT > 1.0 + fk_Math::EPS) return false;

	qOrg.makeEuler(*(_m->snapAngle));
	qNew.makeEuler(_m_MatAdmin->angle);
	qRet = fk_Q_Inter_Sphere(qOrg, qNew, argT);
	_m_MatAdmin->angle = qRet.getEuler();

	_m_MatAdmin->pos = (1.0 - argT) * (*(_m->snapPos)) + argT * _m_MatAdmin->pos;
	AdjustAngleToVec();
	UpdateMatrix(false);

	return true;
}

void fk_Model::adjustSphere(void)
{
	if(_m->shape == nullptr) return;
	setSphere(fk_SphereBoundary::getAdjustRadius(_m->shape));
	return;
}

void fk_Model::adjustAABB(void)
{
	if(_m->shape == nullptr) return;
	setAABBSize(fk_AABBBoundary::getAdjustSize(_m->shape, getInhInvMatrix()));
	return;
}

void fk_Model::adjustOBB(void)
{
	if(_m->shape == nullptr) return;
	setOBBSize(fk_OBBBoundary::getAdjustSize(_m->shape));
	return;
}

void fk_Model::adjustCapsule(fk_Vector argS, fk_Vector argE)
{
	if(_m->shape == nullptr) return;
	setCapsule(argS, argE, fk_CapsuleBoundary::getAdjustRadius(_m->shape, argS, argE));
}

bool fk_Model::isInter(fk_Model *argModel)
{
	bool retStatus = false;

	if(argModel == nullptr) return false;

	switch(getBMode()) {
	  case fk_BoundaryMode::SPHERE:
		retStatus = IsBSInter(argModel);
		break;

	  case fk_BoundaryMode::AABB:
		retStatus = IsAABBInter(argModel);
		break;

	  case fk_BoundaryMode::OBB:
		retStatus = IsOBBInter(argModel);
		break;

	  case fk_BoundaryMode::CAPSULE:
		retStatus = IsCapsuleInter(argModel);
		break;

	  case fk_BoundaryMode::NONE:
	  default:
		break;
	}
	if(retStatus == true) _m->interStatus = true;
	return retStatus;
}

bool fk_Model::IsBSInter(fk_Model *argModel)
{
	fk_Vector p1, p2;

	p1 = getInhPosition();
	p2 = argModel->getInhPosition();

	return fk_SphereBoundary::isInter(p1, getSphere() * _m_MatAdmin->scale,
									  p2, argModel->getSphere() * argModel->_m_MatAdmin->scale);
}


bool fk_Model::IsAABBInter(fk_Model *argModel)
{
	fk_Vector p1, p2;

	p1 = getInhPosition();
	p2 = argModel->getInhPosition();

	return fk_AABBBoundary::isInter(p1, getAABBSize() * _m_MatAdmin->scale,
									p2, argModel->getAABBSize() * argModel->_m_MatAdmin->scale);
}

bool fk_Model::IsOBBInter(fk_Model *argModel)
{
	fk_Vector A[3], B[3], obb_A, obb_B, P;
	double a[3], b[3];

	P = argModel->getInhPosition() - getInhPosition();

	A[1] = getInhUpVec();
	A[2] = -getInhVec();
	A[0] = A[1] ^ A[2];

	B[1] = argModel->getInhUpVec();
	B[2] = -(argModel->getInhVec());
	B[0] = B[1] ^ B[2];

	obb_A = getOBBSize();
	a[0] = _m_MatAdmin->scale * obb_A.x/2.0;
	a[1] = _m_MatAdmin->scale * obb_A.y/2.0;
	a[2] = _m_MatAdmin->scale * obb_A.z/2.0;

	obb_B = argModel->getOBBSize();
	b[0] = argModel->_m_MatAdmin->scale * obb_B.x/2.0;
	b[1] = argModel->_m_MatAdmin->scale * obb_B.y/2.0;
	b[2] = argModel->_m_MatAdmin->scale * obb_B.z/2.0;

	return fk_OBBBoundary::isInter(A, B, a, b, P);
}

bool fk_Model::IsCapsuleInter(fk_Model *argModel)
{
	fk_Vector s1, e1, s2, e2;
	fk_Matrix m1, m2;

	m1 = getInhMatrix();
	s1 = m1 * getCapsuleStartPos();
	e1 = m1 * getCapsuleEndPos();

	m2 = argModel->getInhMatrix();
	s2 = m2 * argModel->getCapsuleStartPos();
	e2 = m2 * argModel->getCapsuleEndPos();

	return (fk_CapsuleBoundary::isInter(s1, e1, _m_MatAdmin->scale * getCapsuleRadius(), s2, e2,
										argModel->_m_MatAdmin->scale * argModel->getCapsuleRadius()));
}

tuple<bool, double> fk_Model::isCollision(fk_Model *argModel)
{
	if(argModel == nullptr) return {false, 0.0};
	if(_m->snapFlag == false || argModel->_m->snapFlag == false) return {false, 0.0};
	if(_m->snapInhPos == nullptr) return {false, 0.0};
	if(argModel->_m->snapInhPos == nullptr) return {false, 0.0};

	return fk_SphereBoundary::isCollision(*(_m->snapInhPos),
										  getInhPosition(),
										  getSphere() * _m_MatAdmin->scale,
										  *(argModel->_m->snapInhPos),
										  argModel->getInhPosition(),
										  argModel->getSphere() *argModel->_m_MatAdmin->scale);
}

#ifndef FK_OLD_NONSUPPORT
bool fk_Model::isCollision(fk_Model *argModel, double *argTime)
{
	bool status;
	tie(status, *argTime) = isCollision(argModel);
	return status;
}
#endif

void fk_Model::setInterMode(bool argMode)
{
	_m->interMode = argMode;
	_m->interStatus = false;
}

bool fk_Model::getInterMode(void)
{
	return _m->interMode;
}

bool fk_Model::getInterStatus(void)
{
	return _m->interStatus;
}

void fk_Model::resetInter(void)
{
	_m->interStatus = false;
}

void fk_Model::entryInterModel(fk_Model *argModel)
{
	if(find(_m->interList.begin(), _m->interList.end(), argModel) ==
	   _m->interList.end()) {
		_m->interList.push_back(argModel);
	}
	return;
}

void fk_Model::deleteInterModel(fk_Model *argModel)
{
	_m->interList.remove(argModel);
	return;
}

void fk_Model::clearInterModel(void)
{
	_m->interList.clear();
	return;
}

void fk_Model::setInterStopMode(bool argMode)
{
	_m->interStopMode = argMode;
}

bool fk_Model::getInterStopMode(void)
{
	return _m->interStopMode;
}

void fk_Model::PreMove(void)
{
	if(_m->interStopMode == true && _m->interList.empty() == false) snapShot();
}

void fk_Model::PostMove(void)
{
	for(mi ite = _m->interList.begin(); ite != _m->interList.end(); ++ite) {
		if(isInter(*ite) == true) {
			restore();
			return;
		}
	}
}

bool fk_Model::glRotate(fk_Vector argOrg, fk_Axis argAxis, double argAngle)
{
	bool ret;

	PreMove();
	ret = glRotate_(argOrg, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotate(double argX, double argY, double argZ, fk_Axis argAxis, double argAngle)
{
	bool ret;

	PreMove();
	ret = glRotate_(argX, argY, argZ, argAxis, argAngle);
	PostMove();
	return ret;
}


bool fk_Model::glRotate(fk_Vector argOrg, fk_Vector argTop, double argAngle)
{
	bool ret;

	PreMove();
	ret = glRotate_(argOrg, argTop, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotate(double argOX, double argOY, double argOZ,
						double argTX, double argTY, double argTZ, double argAngle)
{
	bool ret;

	PreMove();
	ret = glRotate_(argOX, argOY, argOZ, argTX, argTY, argTZ, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotate(fk_Vector argOrg, fk_Axis argAxis, double argAngle)
{
	bool ret;

	PreMove();
	ret = loRotate_(argOrg, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotate(double argX, double argY, double argZ,
						fk_Axis argAxis, double argAngle)
{
	bool ret;

	PreMove();
	ret = loRotate_(argX, argY, argZ, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotate(fk_Vector argOrg, fk_Vector argTop, double argAngle)
{
	bool ret;

	PreMove();
	ret = loRotate_(argOrg, argTop, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotate(double argOX, double argOY, double argOZ,
						double argTX, double argTY, double argTZ, double argAngle)
{
	bool ret;

	PreMove();
	ret = loRotate_(argOX, argOY, argOZ, argTX, argTY, argTZ, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotateWithVec(fk_Vector argOrg, fk_Axis argAxis, double argAngle)
{
	bool ret;

	PreMove();
	ret = glRotateWithVec_(argOrg, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotateWithVec(double argX, double argY, double argZ,
							   fk_Axis argAxis, double argAngle)
{
	bool ret;

	PreMove();
	ret = glRotateWithVec_(argX, argY, argZ, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotateWithVec(fk_Vector argOrg, fk_Vector argTop, double argAngle)
{
	bool ret;

	PreMove();
	ret = glRotateWithVec_(argOrg, argTop, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotateWithVec(double argOX, double argOY, double argOZ,
							   double argTX, double argTY, double argTZ, double argAngle)
{
	bool ret;

	PreMove();
	ret = glRotateWithVec_(argOX, argOY, argOZ, argTX, argTY, argTZ, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotateWithVec(fk_Vector argOrg, fk_Axis argAxis, double argAngle)
{
	bool ret;

	PreMove();
	ret = loRotateWithVec_(argOrg, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotateWithVec(double argX, double argY, double argZ,
							   fk_Axis argAxis, double argAngle)
{
	bool ret;

	PreMove();
	ret = loRotateWithVec_(argX, argY, argZ, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotateWithVec(fk_Vector argOrg, fk_Vector argTop, double argAngle)
{
	bool ret;

	PreMove();
	ret = loRotateWithVec_(argOrg, argTop, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotateWithVec(double argOX, double argOY, double argOZ,
							   double argTX, double argTY, double argTZ, double argAngle)
{
	bool ret;

	PreMove();
	ret = loRotateWithVec_(argOX, argOY, argOZ, argTX, argTY, argTZ, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glTranslate(fk_Vector argV)
{
	bool ret;

	PreMove();
	ret = glTranslate_(argV);
	PostMove();
	return ret;
}

bool fk_Model::glTranslate(double argX, double argY, double argZ)
{
	bool ret;

	PreMove();
	ret = glTranslate_(argX, argY, argZ);
	PostMove();
	return ret;
}

bool fk_Model::loTranslate(fk_Vector argV)
{
	bool ret;

	PreMove();
	ret = loTranslate_(argV);
	PostMove();
	return ret;
}

bool fk_Model::loTranslate(double argX, double argY, double argZ)
{
	bool ret;

	PreMove();
	ret = loTranslate_(argX, argY, argZ);
	PostMove();
	return ret;
}


bool fk_Model::glMoveTo(fk_Vector argP)
{
	bool ret;

	PreMove();
	ret = glMoveTo_(argP);
	PostMove();
	return ret;
}

bool fk_Model::glMoveTo(double argX, double argY, double argZ)
{
	bool ret;

	PreMove();
	ret = glMoveTo_(argX, argY, argZ);
	PostMove();
	return ret;
}

void fk_Model::setShader(fk_ShaderBinder *argShader)
{
	_m->shader = argShader;
}

fk_ShaderBinder * fk_Model::getShader(void)
{
	return _m->shader;
}

void fk_Model::setPickMode(const bool) {}
bool fk_Model::getPickMode(void) const { return true; }

void fk_Model::setShadowEffect(bool argMode)
{
	_m->shadowEffectMode = argMode;
}

bool fk_Model::getShadowEffect(void)
{
	return _m->shadowEffectMode;
}

void fk_Model::setShadowDraw(bool argMode)
{
	_m->shadowDrawMode = argMode;
}

bool fk_Model::getShadowDraw(void)
{
	return _m->shadowDrawMode;
}

void fk_Model::setFogMode(bool argMode)
{
	_m->fogMode = argMode;
}

bool fk_Model::getFogMode(void)
{
	return _m->fogMode;
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
