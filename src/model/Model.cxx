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
#include <FK/Model.h>
#include <FK/Material.h>
#include <FK/Shape.h>
#include <FK/Tree.h>
#include <FK/Quaternion.h>
#include <FK/BoundaryElem.H>
#include <algorithm>

using namespace std;
using namespace FK;

using mi = list<fk_Model *>::iterator;

static unsigned int		_globalModelID = 1;

fk_Model::fk_Model(fk_Shape *argShape)
	: fk_Boundary(FK_MODEL), shape(nullptr), parentModel(nullptr),
	  treeData(nullptr), snapPos(nullptr), snapInhPos(nullptr), snapAngle(nullptr)
{
	setDrawMode(FK_NONEMODE);
	setMaterialMode(FK_CHILD_MODE);
	setBlendMode(FK_BLEND_ALPHA_MODE);
	setDepthMode(FK_DEPTH_READ_AND_WRITE);

	setShape(argShape);
	setPointSize(1.0);
	setReverseDrawMode(false);
	elemMode = FK_ELEM_MODEL;

	_modelID = _globalModelID;
	_globalModelID++;

	treeFlag = false;
	treeDelMode = true;
	smoothFlag = false;

	snapFlag = false;

	interMode = false;
	interStatus = false;
	interStopMode = false;

	preShader = [](){};
	postShader = [](){};

	return;
}

fk_Model::~fk_Model()
{
	DeleteTree();

	delete snapPos;
	delete snapInhPos;
	delete snapAngle;

	return;
}

void fk_Model::setShape(fk_Shape *argShape)
{
	bool	drawModeFlag;

	if(argShape == nullptr) {
		shape = nullptr;
		return;
	}

	if(shape == nullptr) {
		drawModeFlag = true;
	} else if(shape->getObjectType() != argShape->getObjectType()) {
		drawModeFlag = true;
	} else {
		drawModeFlag = false;
	}

	fk_ObjectType type = argShape->getObjectType();
	if(drawModeFlag == true) {
		switch(type) {
		  case FK_POINT:
		  case FK_PARTICLESET:
			drawMode = FK_POINTMODE;
			break;

		  case FK_LINE:
		  case FK_POLYLINE:
		  case FK_CLOSEDLINE:
			drawMode = FK_LINEMODE;
			break;
			 
		  case FK_POLYGON:
		  case FK_BLOCK:
		  case FK_CIRCLE:
		  case FK_SPHERE:
		  case FK_PRISM:
		  case FK_CONE:
		  case FK_CAPSULE:
		  case FK_SOLID:
		  case FK_INDEXFACESET:
			drawMode = FK_POLYMODE;
			break;

		  case FK_RECTTEXTURE:
		  case FK_TRITEXTURE:
		  case FK_MESHTEXTURE:
		  case FK_IFSTEXTURE:
		  case FK_ARTEXTURE:
			drawMode = FK_TEXTUREMODE;
			break;

		  default:
			drawMode = FK_NONEMODE;
			break;
		}
	}
	shape = argShape;

	return;
}

void fk_Model::setMaterial(const fk_Material &argMate)
{
	material = argMate;
	return;
}

void fk_Model::setPointColor(fk_Color *argColor)
{
	setPointColor(argColor->getR(), argColor->getG(), argColor->getB());
	return;
}

void fk_Model::setPointColor(float argR, float argG, float argB)
{
	pointColor.set(argR, argG, argB);
	return;
}

void fk_Model::setLineColor(fk_Color *argColor)
{
	setLineColor(argColor->getR(), argColor->getG(), argColor->getB());
	return;
}

void fk_Model::setLineColor(float argR, float argG, float argB)
{
	lineColor.set(argR, argG, argB);
	return;
}

fk_Shape * fk_Model::getShape(void) const
{
	return shape;
}

fk_Material * fk_Model::getMaterial(void)
{
	return &material;
}

fk_Color * fk_Model::getPointColor(void)
{
	return &pointColor;
}

fk_Color * fk_Model::getLineColor(void)
{
	return &lineColor;
}

void fk_Model::setDrawMode(const fk_DrawMode argMode)
{
	if(drawMode == argMode) return;
	drawMode = argMode;
	if(shape != nullptr) {
		shape->forceUpdateAttr();
	}
	return;
}

fk_DrawMode fk_Model::getDrawMode(void) const
{
	return drawMode;
}

void fk_Model::setElementMode(const fk_ElementMode argMode)
{
	elemMode = argMode;
}

fk_ElementMode fk_Model::getElementMode(void) const
{
	return elemMode;
}

void fk_Model::setMaterialMode(const fk_MaterialMode) {}
fk_MaterialMode fk_Model::getMaterialMode(void) const { return FK_PARENT_MODE; }

void fk_Model::setBlendMode(const fk_BlendMode argMode,
							const fk_BlendFactor argSrcFactor,
							const fk_BlendFactor argDstFactor)
{
	switch(argMode) {
	  case FK_BLEND_ALPHA_MODE:
		srcFactor = FK_FACTOR_SRC_ALPHA;
		dstFactor = FK_FACTOR_ONE_MINUS_SRC_ALPHA;
		break;

	  case FK_BLEND_NEGATIVE_MODE:
		srcFactor = FK_FACTOR_ONE_MINUS_DST_COLOR;
		dstFactor = FK_FACTOR_ZERO;
		break;

	  case FK_BLEND_ADDITION_MODE:
		srcFactor = FK_FACTOR_ONE;
		dstFactor = FK_FACTOR_ONE;
		break;

	  case FK_BLEND_SCREEN_MODE:
		srcFactor = FK_FACTOR_SRC_ALPHA;
		dstFactor = FK_FACTOR_ONE;
		break;

	  case FK_BLEND_LIGHTEN_MODE:
		srcFactor = FK_FACTOR_ONE_MINUS_DST_COLOR;
		dstFactor = FK_FACTOR_ONE;
		break;

	  case FK_BLEND_MULTIPLY_MODE:
		srcFactor = FK_FACTOR_ZERO;
		dstFactor = FK_FACTOR_SRC_COLOR;
		break;

	  case FK_BLEND_NONE_MODE:
		srcFactor = FK_FACTOR_ONE;
		dstFactor = FK_FACTOR_ZERO;
		break;

	  case FK_BLEND_CUSTOM_MODE:
		srcFactor = argSrcFactor;
		dstFactor = argDstFactor;
		break;

	  default:
		return;
	}

	blendMode = argMode;
	return;
}

fk_BlendMode fk_Model::getBlendMode(fk_BlendFactor *outSrc, fk_BlendFactor *outDst) const
{
	if (outSrc != nullptr) *outSrc = srcFactor;
	if (outDst != nullptr) *outDst = dstFactor;
	return blendMode;
}

void fk_Model::setDepthMode(const fk_DepthMode argMode)
{
	depthMode = argMode;
}

fk_DepthMode fk_Model::getDepthMode(void) const
{
	return depthMode;
}

fk_Matrix fk_Model::getInhMatrix(void) const
{
	if(parentModel == nullptr) return getMatrix();
	return (parentModel->getInhMatrix() * getMatrix());
}

fk_Matrix fk_Model::getInhInvMatrix(void) const
{
	if(parentModel == nullptr) return getInvMatrix();
	return (getInvMatrix() * parentModel->getInhInvMatrix());
}

fk_OrthoMatrix fk_Model::getInhBaseMatrix(void) const
{
	if(parentModel == nullptr) return OrthoMatrix;
	return (parentModel->getInhBaseMatrix() * OrthoMatrix);
}

fk_OrthoMatrix fk_Model::getInhInvBaseMatrix(void) const
{
	fk_OrthoMatrix	RetMat = OrthoMatrix;
	RetMat.inverse();
	if(parentModel == nullptr) return RetMat;
	return (parentModel->getInhInvBaseMatrix() * RetMat);
}

fk_Vector fk_Model::getInhPosition(void) const
{
	fk_Vector retVec;

	if(parentModel == nullptr) {
		retVec = Position;
	} else {
		retVec = parentModel->getInhMatrix() * Position;
	}
	return retVec;
}

fk_Vector fk_Model::getInhVec(void) const
{
	fk_HVector	hvec(Vec);

	if(parentModel == nullptr) return Vec;

	hvec.isvec();
	return (parentModel->getInhMatrix() * hvec);
}
	
fk_Vector fk_Model::getInhUpvec(void) const
{
	fk_HVector	hvec(UpVec);

	if(parentModel == nullptr) return UpVec;
	
	hvec.isvec();
	return (parentModel->getInhMatrix() * hvec);
}

fk_Vector fk_Model::getInhUpVec(void) const
{
	return getInhUpvec();
}

fk_Angle fk_Model::getInhAngle(void) const
{
	fk_Angle		retAngle;
	fk_Vector		vec, upvec;

	if(parentModel == nullptr) return Angle;
	vec = getInhVec();
	upvec = getInhUpVec();
	VectorToAngle(&retAngle, &vec, &upvec);
	return retAngle;
}

double fk_Model::getInhScale(void) const
{
	if(parentModel == nullptr) {
		return Scale;
	}
	return (parentModel->getInhScale() * Scale);
}

void fk_Model::setPointSize(const double argSize)
{
	if(argSize <= FK_EPS) return;
	pointSize = argSize;
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
	return pointSize;
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
	smoothFlag = argFlg;

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
	return smoothFlag;
}

void fk_Model::setReverseDrawMode(const bool argFlg)
{
	reverseFlag = argFlg;
	return;
}

bool fk_Model::getReverseDrawMode(void) const
{
	return reverseFlag;
}

unsigned int fk_Model::getID(void) const
{
	return _modelID;
}

void fk_Model::snapShot(void)
{
	if(snapPos == nullptr) snapPos = new fk_HVector;
	*snapPos = Position;

	if(snapInhPos == nullptr) snapInhPos = new fk_HVector;
	*snapInhPos = getInhPosition();

	if(snapAngle == nullptr) snapAngle = new fk_Angle;
	*snapAngle = Angle;

	snapFlag = true;
	return;
}

bool fk_Model::restore(void)
{
	if(snapFlag == false) return false;

	Angle = *snapAngle;
	Position = *snapPos;
	AdjustAngleToVec();
	UpdateMatrix(false);

	return true;
}

bool fk_Model::restore(double argT)
{
	fk_Quaternion		qOrg, qNew, qRet;

	if(snapFlag == false) return false;
	if(argT < FK_EPS || argT > 1.0 + FK_EPS) return false;

	qOrg.makeEuler(*snapAngle);
	qNew.makeEuler(Angle);
	qRet = fk_Q_Inter_Sphere(qOrg, qNew, argT);
	Angle = qRet.getEuler();

	Position = (1.0 - argT)*(*snapPos) +  argT*Position;
	AdjustAngleToVec();
	UpdateMatrix(false);

	return true;
}

void fk_Model::adjustSphere(void)
{
	if(shape == nullptr) return;
	setSphere(fk_SphereBoundary::getAdjustRadius(shape));
	return;
}

void fk_Model::adjustAABB(void)
{
	if(shape == nullptr) return;
	setAABBSize(fk_AABBBoundary::getAdjustSize(shape, getInhInvMatrix()));
	return;
}

void fk_Model::adjustOBB(void)
{
	if(shape == nullptr) return;
	setOBBSize(fk_OBBBoundary::getAdjustSize(shape));
	return;
}

void fk_Model::adjustCapsule(fk_Vector argS, fk_Vector argE)
{
	if(shape == nullptr) return;
	setCapsule(argS, argE, fk_CapsuleBoundary::getAdjustRadius(shape, argS, argE));
}

bool fk_Model::isInter(fk_Model *argModel)
{
	bool		retStatus = false;

	if(argModel == nullptr) return false;

	switch(getBMode()) {
	  case FK_B_SPHERE:
		retStatus = IsBSInter(argModel);
		break;

	  case FK_B_AABB:
		retStatus = IsAABBInter(argModel);
		break;

	  case FK_B_OBB:
		retStatus = IsOBBInter(argModel);
		break;

	  case FK_B_CAPSULE:
		retStatus = IsCapsuleInter(argModel);
		break;

	  case FK_B_NONE:
	  default:
		break;
	}
	if(retStatus == true) interStatus = true;
	return retStatus;
}

bool fk_Model::IsBSInter(fk_Model *argModel)
{
	fk_Vector	p1, p2;

	p1 = getInhPosition();
	p2 = argModel->getInhPosition();

	return fk_SphereBoundary::isInter(p1, getSphere()*Scale,
									  p2, argModel->getSphere() * argModel->Scale);
}


bool fk_Model::IsAABBInter(fk_Model *argModel)
{
	fk_Vector	p1, p2;

	p1 = getInhPosition();
	p2 = argModel->getInhPosition();

	return fk_AABBBoundary::isInter(p1, getAABBSize() * Scale,
									p2, argModel->getAABBSize() * argModel->Scale);
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
	a[0] = Scale * obb_A.x/2.0;
	a[1] = Scale * obb_A.y/2.0;
	a[2] = Scale * obb_A.z/2.0;

	obb_B = argModel->getOBBSize();
	b[0] = argModel->Scale * obb_B.x/2.0;
	b[1] = argModel->Scale * obb_B.y/2.0;
	b[2] = argModel->Scale * obb_B.z/2.0;

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

	return (fk_CapsuleBoundary::isInter(s1, e1, Scale * getCapsuleRadius(), s2, e2,
										argModel->Scale * argModel->getCapsuleRadius()));
}

bool fk_Model::isCollision(fk_Model *argModel, double *argTime)
{
	if(argModel == nullptr) return false;
	if(snapFlag == false || argModel->snapFlag == false) return false;
	if(snapInhPos == nullptr) return false;
	if(argModel->snapInhPos == nullptr) return false;

	return fk_SphereBoundary::isCollision(*snapInhPos,
										  getInhPosition(),
										  getSphere() * Scale,
										  *(argModel->snapInhPos),
										  argModel->getInhPosition(),
										  argModel->getSphere() * argModel->Scale,
										  argTime);
	return true;
}

void fk_Model::setInterMode(bool argMode)
{
	interMode = argMode;
	interStatus = false;
}

bool fk_Model::getInterMode(void)
{
	return interMode;
}

bool fk_Model::getInterStatus(void)
{
	return interStatus;
}

void fk_Model::resetInter(void)
{
	interStatus = false;
}

void fk_Model::entryInterModel(fk_Model *argModel)
{
	if(find(interList.begin(), interList.end(), argModel) == interList.end()) {
		interList.push_back(argModel);
	}
	return;
}

void fk_Model::deleteInterModel(fk_Model *argModel)
{
	interList.remove(argModel);
	return;
}

void fk_Model::clearInterModel(void)
{
	interList.clear();
	return;
}

void fk_Model::setInterStopMode(bool argMode)
{
	interStopMode = argMode;
}

bool fk_Model::getInterStopMode(void)
{
	return interStopMode;
}

void fk_Model::PreMove(void)
{
	if(interStopMode == true && interList.empty() == false) snapShot();
}

void fk_Model::PostMove(void)
{
	for(mi ite = interList.begin(); ite != interList.end(); ++ite) {
		if(isInter(*ite) == true) {
			restore();
			return;
		}
	}
}

bool fk_Model::glRotate(fk_Vector argOrg, fk_Axis argAxis, double argAngle)
{
	bool	ret;

	PreMove();
	ret = glRotate_(argOrg, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotate(double argX, double argY, double argZ, fk_Axis argAxis, double argAngle)
{
	bool	ret;

	PreMove();
	ret = glRotate_(argX, argY, argZ, argAxis, argAngle);
	PostMove();
	return ret;
}


bool fk_Model::glRotate(fk_Vector argOrg, fk_Vector argTop, double argAngle)
{
	bool	ret;

	PreMove();
	ret = glRotate_(argOrg, argTop, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotate(double argOX, double argOY, double argOZ,
						double argTX, double argTY, double argTZ, double argAngle)
{
	bool	ret;

	PreMove();
	ret = glRotate_(argOX, argOY, argOZ, argTX, argTY, argTZ, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotate(fk_Vector argOrg, fk_Axis argAxis, double argAngle)
{
	bool	ret;

	PreMove();
	ret = loRotate_(argOrg, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotate(double argX, double argY, double argZ,
						fk_Axis argAxis, double argAngle)
{
	bool	ret;

	PreMove();
	ret = loRotate_(argX, argY, argZ, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotate(fk_Vector argOrg, fk_Vector argTop, double argAngle)
{
	bool	ret;

	PreMove();
	ret = loRotate_(argOrg, argTop, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotate(double argOX, double argOY, double argOZ,
						double argTX, double argTY, double argTZ, double argAngle)
{
	bool	ret;

	PreMove();
	ret = loRotate_(argOX, argOY, argOZ, argTX, argTY, argTZ, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotateWithVec(fk_Vector argOrg, fk_Axis argAxis, double argAngle)
{
	bool	ret;

	PreMove();
	ret = glRotateWithVec_(argOrg, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotateWithVec(double argX, double argY, double argZ,
							   fk_Axis argAxis, double argAngle)
{
	bool	ret;

	PreMove();
	ret = glRotateWithVec_(argX, argY, argZ, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotateWithVec(fk_Vector argOrg, fk_Vector argTop, double argAngle)
{
	bool	ret;

	PreMove();
	ret = glRotateWithVec_(argOrg, argTop, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glRotateWithVec(double argOX, double argOY, double argOZ,
							   double argTX, double argTY, double argTZ, double argAngle)
{
	bool	ret;

	PreMove();
	ret = glRotateWithVec_(argOX, argOY, argOZ, argTX, argTY, argTZ, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotateWithVec(fk_Vector argOrg, fk_Axis argAxis, double argAngle)
{
	bool	ret;

	PreMove();
	ret = loRotateWithVec_(argOrg, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotateWithVec(double argX, double argY, double argZ,
							   fk_Axis argAxis, double argAngle)
{
	bool	ret;

	PreMove();
	ret = loRotateWithVec_(argX, argY, argZ, argAxis, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotateWithVec(fk_Vector argOrg, fk_Vector argTop, double argAngle)
{
	bool	ret;

	PreMove();
	ret = loRotateWithVec_(argOrg, argTop, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::loRotateWithVec(double argOX, double argOY, double argOZ,
							   double argTX, double argTY, double argTZ, double argAngle)
{
	bool	ret;

	PreMove();
	ret = loRotateWithVec_(argOX, argOY, argOZ, argTX, argTY, argTZ, argAngle);
	PostMove();
	return ret;
}

bool fk_Model::glTranslate(fk_Vector argV)
{
	bool	ret;

	PreMove();
	ret = glTranslate_(argV);
	PostMove();
	return ret;
}

bool fk_Model::glTranslate(double argX, double argY, double argZ)
{
	bool	ret;

	PreMove();
	ret = glTranslate_(argX, argY, argZ);
	PostMove();
	return ret;
}

bool fk_Model::loTranslate(fk_Vector argV)
{
	bool	ret;

	PreMove();
	ret = loTranslate_(argV);
	PostMove();
	return ret;
}

bool fk_Model::loTranslate(double argX, double argY, double argZ)
{
	bool	ret;

	PreMove();
	ret = loTranslate_(argX, argY, argZ);
	PostMove();
	return ret;
}


bool fk_Model::glMoveTo(fk_Vector argP)
{
	bool	ret;

	PreMove();
	ret = glMoveTo_(argP);
	PostMove();
	return ret;
}

bool fk_Model::glMoveTo(double argX, double argY, double argZ)
{
	bool	ret;

	PreMove();
	ret = glMoveTo_(argX, argY, argZ);
	PostMove();
	return ret;
}

void fk_Model::setPickMode(const bool) {}
bool fk_Model::getPickMode(void) const { return true; }
