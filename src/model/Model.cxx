#include <FK/Model.h>
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

fk_Model::fk_ModelData::fk_ModelData(void) :
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

fk_Model::fk_Model(fk_Shape *argShape) : fk_Boundary(fk_Type::MODEL)
{
	mData = make_unique<fk_ModelData>();
	
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
		mData->shape = nullptr;
		return;
	}

	if(mData->shape == nullptr) {
		drawModeFlag = true;
	} else if(mData->shape->getObjectType() != argShape->getObjectType()) {
		drawModeFlag = true;
	} else {
		drawModeFlag = false;
	}

	fk_Type type = argShape->getObjectType();
	if(drawModeFlag == true) {
		switch(type) {
		  case fk_Type::POINT:
		  case fk_Type::PARTICLESET:
			mData->drawMode = fk_Draw::POINT;
			break;

		  case fk_Type::LINE:
		  case fk_Type::POLYLINE:
		  case fk_Type::CLOSEDLINE:
			mData->drawMode = fk_Draw::LINE;
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
			mData->drawMode = fk_Draw::FACE;
			break;

		  case fk_Type::RECTTEXTURE:
		  case fk_Type::TRITEXTURE:
		  case fk_Type::MESHTEXTURE:
		  case fk_Type::IFSTEXTURE:
		  case fk_Type::ARTEXTURE:
			mData->drawMode = fk_Draw::TEXTURE;
			break;

		  default:
			mData->drawMode = fk_Draw::NONE;
			break;
		}
	}
	mData->shape = argShape;

	return;
}

void fk_Model::setMaterial(const fk_Material &argMate)
{
	mData->material = argMate;
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
	mData->pointColor.set(argR, argG, argB);
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
	mData->lineColor.set(argR, argG, argB);
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
	mData->curveColor.set(argR, argG, argB);
	return;
}

fk_Shape * fk_Model::getShape(void) const
{
	return mData->shape;
}

fk_Material * fk_Model::getMaterial(void)
{
	return &(mData->material);
}

fk_Color * fk_Model::getPointColor(void)
{
	return &(mData->pointColor);
}

fk_Color * fk_Model::getLineColor(void)
{
	return &(mData->lineColor);
}

fk_Color * fk_Model::getCurveColor(void)
{
	return &(mData->curveColor);
}

void fk_Model::setDrawMode(const fk_Draw argMode)
{
	if(mData->drawMode == argMode) return;
	mData->drawMode = argMode;
	if(mData->shape != nullptr) {
		mData->shape->ForceUpdateAttr();
	}
	return;
}

fk_Draw fk_Model::getDrawMode(void) const
{
	return mData->drawMode;
}

void fk_Model::setElementMode(const fk_ElementMode argMode)
{
	mData->elemMode = argMode;
}

fk_ElementMode fk_Model::getElementMode(void) const
{
	return mData->elemMode;
}

void fk_Model::setMaterialMode(const fk_MaterialMode) {}
fk_MaterialMode fk_Model::getMaterialMode(void) const { return fk_MaterialMode::PARENT; }

void fk_Model::setBlendMode(const fk_BlendMode argMode,
							const fk_BlendFactor argSrcFactor,
							const fk_BlendFactor argDstFactor)
{
	switch(argMode) {
	  case fk_BlendMode::ALPHA:
		mData->srcFactor = fk_BlendFactor::SRC_ALPHA;
		mData->dstFactor = fk_BlendFactor::ONE_MINUS_SRC_ALPHA;
		break;

	  case fk_BlendMode::NEGATIVE:
		mData->srcFactor = fk_BlendFactor::ONE_MINUS_DST_COLOR;
		mData->dstFactor = fk_BlendFactor::ZERO;
		break;

	  case fk_BlendMode::ADDITION:
		mData->srcFactor = fk_BlendFactor::ONE;
		mData->dstFactor = fk_BlendFactor::ONE;
		break;

	  case fk_BlendMode::SCREEN:
		mData->srcFactor = fk_BlendFactor::SRC_ALPHA;
		mData->dstFactor = fk_BlendFactor::ONE;
		break;

	  case fk_BlendMode::LIGHTEN:
		mData->srcFactor = fk_BlendFactor::ONE_MINUS_DST_COLOR;
		mData->dstFactor = fk_BlendFactor::ONE;
		break;

	  case fk_BlendMode::MULTIPLY:
		mData->srcFactor = fk_BlendFactor::ZERO;
		mData->dstFactor = fk_BlendFactor::SRC_COLOR;
		break;

	  case fk_BlendMode::NONE:
		mData->srcFactor = fk_BlendFactor::ONE;
		mData->dstFactor = fk_BlendFactor::ZERO;
		break;

	  case fk_BlendMode::CUSTOM:
		mData->srcFactor = argSrcFactor;
		mData->dstFactor = argDstFactor;
		break;

	  default:
		return;
	}

	mData->blendMode = argMode;
	return;
}

fk_BlendMode fk_Model::getBlendMode(fk_BlendFactor *argOutSrc, fk_BlendFactor *argOutDst) const
{
	if (argOutSrc != nullptr) *argOutSrc = mData->srcFactor;
	if (argOutDst != nullptr) *argOutDst = mData->dstFactor;
	return mData->blendMode;
}

void fk_Model::setDepthMode(const fk_DepthMode argMode)
{
	mData->depthMode = argMode;
}

fk_DepthMode fk_Model::getDepthMode(void) const
{
	return mData->depthMode;
}

fk_Matrix fk_Model::getInhMatrix(void) const
{
	if(mData->parentModel == nullptr) return getMatrix();
	return (mData->parentModel->getInhMatrix() * getMatrix());
}

fk_Matrix fk_Model::getInhInvMatrix(void) const
{
	if(mData->parentModel == nullptr) return getInvMatrix();
	return (getInvMatrix() * mData->parentModel->getInhInvMatrix());
}

fk_OrthoMatrix fk_Model::getInhBaseMatrix(void) const
{
	if(mData->parentModel == nullptr) return oData->M;
	return (mData->parentModel->getInhBaseMatrix() * oData->M);
}

fk_OrthoMatrix fk_Model::getInhInvBaseMatrix(void) const
{
	fk_OrthoMatrix	RetMat = oData->M;
	RetMat.inverse();
	if(mData->parentModel == nullptr) return RetMat;
	return (mData->parentModel->getInhInvBaseMatrix() * RetMat);
}

fk_Vector fk_Model::getInhPosition(void) const
{
	fk_Vector retVec;

	if(mData->parentModel == nullptr) {
		retVec = oData->pos;
	} else {
		retVec = mData->parentModel->getInhMatrix() * oData->pos;
	}
	return retVec;
}

fk_Vector fk_Model::getInhVec(void) const
{
	fk_HVector	hvec(oData->vec);

	if(mData->parentModel == nullptr) return oData->vec;

	hvec.isvec();
	return (mData->parentModel->getInhMatrix() * hvec);
}
	
fk_Vector fk_Model::getInhUpvec(void) const
{
	fk_HVector	hvec(oData->uvec);

	if(mData->parentModel == nullptr) return oData->uvec;
	
	hvec.isvec();
	return (mData->parentModel->getInhMatrix() * hvec);
}

fk_Vector fk_Model::getInhUpVec(void) const
{
	return getInhUpvec();
}

fk_Angle fk_Model::getInhAngle(void) const
{
	fk_Angle		retAngle;
	fk_Vector		vec, upvec;

	if(mData->parentModel == nullptr) return oData->angle;
	vec = getInhVec();
	upvec = getInhUpVec();
	VectorToAngle(&retAngle, &vec, &upvec);
	return retAngle;
}

double fk_Model::getInhScale(void) const
{
	if(mData->parentModel == nullptr) {
		return oData->scale;
	}
	return (mData->parentModel->getInhScale() * oData->scale);
}

void fk_Model::setPointSize(const double argSize)
{
	if(argSize <= fk_Math::EPS) return;
	mData->pointSize = argSize;
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
	return mData->pointSize;
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
	mData->smoothFlag = argFlg;

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
	return mData->smoothFlag;
}

void fk_Model::setReverseDrawMode(const bool argFlg)
{
	mData->reverseFlag = argFlg;
	return;
}

bool fk_Model::getReverseDrawMode(void) const
{
	return mData->reverseFlag;
}

void fk_Model::setTextureMode(fk_TexMode argMode)
{
	mData->texMode = argMode;
}

fk_TexMode fk_Model::getTextureMode(void)
{
	return mData->texMode;
}

void fk_Model::setShadingMode(fk_ShadingMode argMode)
{
	mData->shadingMode = argMode;
}

fk_ShadingMode fk_Model::getShadingMode(void) const
{
	return mData->shadingMode;
}

unsigned int fk_Model::getID(void) const
{
	return mData->modelID;
}

void fk_Model::snapShot(void)
{
	if(mData->snapPos == nullptr) mData->snapPos = make_unique<fk_HVector>();
	*(mData->snapPos) = oData->pos;

	if(mData->snapInhPos == nullptr) mData->snapInhPos = make_unique<fk_HVector>();
	*(mData->snapInhPos) = getInhPosition();

	if(mData->snapAngle == nullptr) mData->snapAngle = make_unique<fk_Angle>();
	*(mData->snapAngle) = oData->angle;

	mData->snapFlag = true;
	return;
}

bool fk_Model::restore(void)
{
	if(mData->snapFlag == false) return false;

	oData->angle = *(mData->snapAngle);
	oData->pos = *(mData->snapPos);
	AdjustAngleToVec();
	UpdateMatrix(false);

	return true;
}

bool fk_Model::restore(double argT)
{
	fk_Quaternion qOrg, qNew, qRet;

	if(mData->snapFlag == false) return false;
	if(argT < fk_Math::EPS || argT > 1.0 + fk_Math::EPS) return false;

	qOrg.makeEuler(*(mData->snapAngle));
	qNew.makeEuler(oData->angle);
	qRet = fk_Q_Inter_Sphere(qOrg, qNew, argT);
	oData->angle = qRet.getEuler();

	oData->pos = (1.0 - argT) * (*(mData->snapPos)) +  argT * oData->pos;
	AdjustAngleToVec();
	UpdateMatrix(false);

	return true;
}

void fk_Model::adjustSphere(void)
{
	if(mData->shape == nullptr) return;
	setSphere(fk_SphereBoundary::getAdjustRadius(mData->shape));
	return;
}

void fk_Model::adjustAABB(void)
{
	if(mData->shape == nullptr) return;
	setAABBSize(fk_AABBBoundary::getAdjustSize(mData->shape, getInhInvMatrix()));
	return;
}

void fk_Model::adjustOBB(void)
{
	if(mData->shape == nullptr) return;
	setOBBSize(fk_OBBBoundary::getAdjustSize(mData->shape));
	return;
}

void fk_Model::adjustCapsule(fk_Vector argS, fk_Vector argE)
{
	if(mData->shape == nullptr) return;
	setCapsule(argS, argE, fk_CapsuleBoundary::getAdjustRadius(mData->shape, argS, argE));
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
	if(retStatus == true) mData->interStatus = true;
	return retStatus;
}

bool fk_Model::IsBSInter(fk_Model *argModel)
{
	fk_Vector p1, p2;

	p1 = getInhPosition();
	p2 = argModel->getInhPosition();

	return fk_SphereBoundary::isInter(p1, getSphere() * oData->scale,
									  p2, argModel->getSphere() * argModel->oData->scale);
}


bool fk_Model::IsAABBInter(fk_Model *argModel)
{
	fk_Vector p1, p2;

	p1 = getInhPosition();
	p2 = argModel->getInhPosition();

	return fk_AABBBoundary::isInter(p1, getAABBSize() * oData->scale,
									p2, argModel->getAABBSize() * argModel->oData->scale);
}

bool fk_Model::IsOBBInter(fk_Model *argModel)
{
	fk_Vector	A[3], B[3], obb_A, obb_B, P;
	double		a[3], b[3];

	P = argModel->getInhPosition() - getInhPosition();

	A[1] = getInhUpVec();
	A[2] = -getInhVec();
	A[0] = A[1] ^ A[2];

	B[1] = argModel->getInhUpVec();
	B[2] = -(argModel->getInhVec());
	B[0] = B[1] ^ B[2];

	obb_A = getOBBSize();
	a[0] = oData->scale * obb_A.x/2.0;
	a[1] = oData->scale * obb_A.y/2.0;
	a[2] = oData->scale * obb_A.z/2.0;

	obb_B = argModel->getOBBSize();
	b[0] = argModel->oData->scale * obb_B.x/2.0;
	b[1] = argModel->oData->scale * obb_B.y/2.0;
	b[2] = argModel->oData->scale * obb_B.z/2.0;

	return fk_OBBBoundary::isInter(A, B, a, b, P);
}

bool fk_Model::IsCapsuleInter(fk_Model *argModel)
{
	fk_Vector		s1, e1, s2, e2;
	fk_Matrix		m1, m2;

	m1 = getInhMatrix();
	s1 = m1 * getCapsuleStartPos();
	e1 = m1 * getCapsuleEndPos();

	m2 = argModel->getInhMatrix();
	s2 = m2 * argModel->getCapsuleStartPos();
	e2 = m2 * argModel->getCapsuleEndPos();

	return (fk_CapsuleBoundary::isInter(s1, e1, oData->scale * getCapsuleRadius(), s2, e2,
										argModel->oData->scale * argModel->getCapsuleRadius()));
}

tuple<bool, double> fk_Model::isCollision(fk_Model *argModel)
{
	if(argModel == nullptr) return {false, 0.0};
	if(mData->snapFlag == false || argModel->mData->snapFlag == false) return {false, 0.0};
	if(mData->snapInhPos == nullptr) return {false, 0.0};
	if(argModel->mData->snapInhPos == nullptr) return {false, 0.0};

	return fk_SphereBoundary::isCollision(*(mData->snapInhPos),
										  getInhPosition(),
										  getSphere() * oData->scale,
										  *(argModel->mData->snapInhPos),
										  argModel->getInhPosition(),
										  argModel->getSphere() * argModel->oData->scale);
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
	mData->interMode = argMode;
	mData->interStatus = false;
}

bool fk_Model::getInterMode(void)
{
	return mData->interMode;
}

bool fk_Model::getInterStatus(void)
{
	return mData->interStatus;
}

void fk_Model::resetInter(void)
{
	mData->interStatus = false;
}

void fk_Model::entryInterModel(fk_Model *argModel)
{
	if(find(mData->interList.begin(), mData->interList.end(), argModel) ==
	   mData->interList.end()) {
		mData->interList.push_back(argModel);
	}
	return;
}

void fk_Model::deleteInterModel(fk_Model *argModel)
{
	mData->interList.remove(argModel);
	return;
}

void fk_Model::clearInterModel(void)
{
	mData->interList.clear();
	return;
}

void fk_Model::setInterStopMode(bool argMode)
{
	mData->interStopMode = argMode;
}

bool fk_Model::getInterStopMode(void)
{
	return mData->interStopMode;
}

void fk_Model::PreMove(void)
{
	if(mData->interStopMode == true && mData->interList.empty() == false) snapShot();
}

void fk_Model::PostMove(void)
{
	for(mi ite = mData->interList.begin(); ite != mData->interList.end(); ++ite) {
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
	mData->shader = argShader;
}

fk_ShaderBinder * fk_Model::getShader(void)
{
	return mData->shader;
}

void fk_Model::setPickMode(const bool) {}
bool fk_Model::getPickMode(void) const { return true; }

void fk_Model::setShadowEffect(bool argMode)
{
	mData->shadowEffectMode = argMode;
}

bool fk_Model::getShadowEffect(void)
{
	return mData->shadowEffectMode;
}

void fk_Model::setShadowDraw(bool argMode)
{
	mData->shadowDrawMode = argMode;
}

bool fk_Model::getShadowDraw(void)
{
	return mData->shadowDrawMode;
}

void fk_Model::setFogMode(bool argMode)
{
	mData->fogMode = argMode;
}

bool fk_Model::getFogMode(void)
{
	return mData->fogMode;
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
