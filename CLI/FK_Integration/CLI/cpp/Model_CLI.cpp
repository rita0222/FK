#include "Model_CLI.h"

namespace FK_CLI {

	bool fk_Model::glRotate(fk_Vector^ argOrigin, fk_Axis argAxis, double argTheta)
	{
		if(!argOrigin) return false;
		return GetP()->glRotate(*argOrigin->pVec, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::glRotate(double argX, double argY, double argZ, fk_Axis argAxis, double argTheta)
	{
		return GetP()->glRotate(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::glRotate(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->glRotate(*argA->pVec, *argB->pVec, argTheta);
	}

	bool fk_Model::glRotate(double argAx, double argAy, double argAz,
							double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->glRotate(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::loRotate(fk_Vector^ argOrigin, fk_Axis argAxis, double argTheta)
	{
		if(!argOrigin) return false;
		return GetP()->loRotate(*argOrigin->pVec, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::loRotate(double argX, double argY, double argZ, fk_Axis argAxis, double argTheta)
	{
		return GetP()->loRotate(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::loRotate(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->loRotate(*argA->pVec, *argB->pVec, argTheta);
	}

	bool fk_Model::loRotate(double argAx, double argAy, double argAz,
							double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->loRotate(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::glRotateWithVec(fk_Vector^ argOrigin, fk_Axis argAxis, double argTheta)
	{
		if(!argOrigin) return false;
		return GetP()->glRotateWithVec(*argOrigin->pVec, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::glRotateWithVec(double argX, double argY, double argZ,
								   fk_Axis argAxis, double argTheta)
	{
		return GetP()->glRotateWithVec(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::glRotateWithVec(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->glRotateWithVec(*argA->pVec, *argB->pVec, argTheta);
	}

	bool fk_Model::glRotateWithVec(double argAx, double argAy, double argAz,
								   double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->glRotateWithVec(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::loRotateWithVec(fk_Vector^ argOrigin, fk_Axis argAxis, double argTheta)
	{
		if(!argOrigin) return false;
		return GetP()->loRotateWithVec(*argOrigin->pVec, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::loRotateWithVec(double argX, double argY, double argZ,
								   fk_Axis argAxis, double argTheta)
	{
		return GetP()->loRotateWithVec(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::loRotateWithVec(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->loRotateWithVec(*argA->pVec, *argB->pVec, argTheta);
	}

	bool fk_Model::loRotateWithVec(double argAx, double argAy, double argAz,
								   double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->loRotateWithVec(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::glTranslate(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glTranslate(*argV->pVec);
	}

	bool fk_Model::glTranslate(double argX, double argY, double argZ)
	{
		return GetP()->glTranslate(argX, argY, argZ);
	}

	bool fk_Model::loTranslate(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->loTranslate(*argV->pVec);
	}

	bool fk_Model::loTranslate(double argX, double argY, double argZ)
	{
		return GetP()->loTranslate(argX, argY, argZ);
	}

	bool fk_Model::glMoveTo(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glMoveTo(*argV->pVec);
	}

	bool fk_Model::glMoveTo(double argX, double argY, double argZ)
	{
		return GetP()->glMoveTo(argX, argY, argZ);
	}

	unsigned int fk_Model::getID(void)
	{
		return GetP()->getID();
	}

	void fk_Model::setShape(fk_Shape^ argShape)
	{
		if(!argShape) return;
		::fk_Shape *pS = (::fk_Shape *)(argShape->pBase);
		GetP()->setShape(pS);
	}

	fk_Shape^ fk_Model::getShape(void)
	{
		if(GetP()->getShape() == NULL) return nullptr;
		fk_Shape^ shape = gcnew fk_Shape(false);
		shape->pBase = GetP()->getShape();
		return shape;
	}

	void fk_Model::setMaterial(fk_Material^ argM)
	{
		if(!argM) return;
		GetP()->setMaterial(*argM->pMat);
	}

	void fk_Model::setPointColor(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setPointColor(argC->pCol);
	}

	void fk_Model::setPointColor(float argR, float argG, float argB)
	{
		GetP()->setPointColor(argR, argG, argB);
	}

	void fk_Model::setPointColor(double argR, double argG, double argB)
	{
		GetP()->setPointColor(float(argR), float(argG), float(argB));
	}

	void fk_Model::setLineColor(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setLineColor(argC->pCol);
	}

	void fk_Model::setLineColor(float argR, float argG, float argB)
	{
		GetP()->setLineColor(argR, argG, argB);
	}

	void fk_Model::setLineColor(double argR, double argG, double argB)
	{
		GetP()->setLineColor(float(argR), float(argG), float(argB));
	}

	void fk_Model::deleteMaterial(void)
	{
		GetP()->deleteMaterial();
	}

	void fk_Model::deletePointColor(void)
	{
		GetP()->deletePointColor();
	}

	void fk_Model::deleteLineColor(void)
	{
		GetP()->deleteLineColor();
	}

	fk_Material^ fk_Model::getMaterial(void)
	{
		fk_Material^ M = gcnew fk_Material();
		*M->pMat = *GetP()->getMaterial();
		return M;
	}

	fk_Material^ fk_Model::getInhMaterial(void)
	{
		fk_Material^ M = gcnew fk_Material();
		*M->pMat = *GetP()->getInhMaterial();
		return M;
	}

	fk_Color^ fk_Model::getPointColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getPointColor();
		return C;
	}

	fk_Color^ fk_Model::getInhPointColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getInhPointColor();
		return C;
	}


	fk_Color^ fk_Model::getLineColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getLineColor();
		return C;
	}

	fk_Color^ fk_Model::getInhLineColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getInhLineColor();
		return C;
	}

	void fk_Model::setSize(double argSize)
	{
		GetP()->setSize(argSize);
	}

	void fk_Model::setWidth(double argWidth)
	{
		GetP()->setWidth(argWidth);
	}

	double fk_Model::getSize(void)
	{
		return GetP()->getSize();
	}

	double fk_Model::getWidth(void)
	{
		return GetP()->getWidth();
	}

	void fk_Model::setDrawMode(fk_DrawMode argMode)
	{
		unsigned int mode = static_cast<unsigned int>(argMode);
		GetP()->setDrawMode(mode);
	}

	fk_DrawMode fk_Model::getDrawMode(void)
	{
		return static_cast<fk_DrawMode>(GetP()->getDrawMode());
	}

	void fk_Model::setMaterialMode(fk_MaterialMode argMode)
	{
		switch(argMode) {
			case fk_MaterialMode::PARENT:
				GetP()->setMaterialMode(FK_PARENT_MODE);
				break;

			case fk_MaterialMode::CHILD:
				GetP()->setMaterialMode(FK_CHILD_MODE);
				break;

			default:
				GetP()->setMaterialMode(FK_NONE_MODE);
				break;
		}
	}

	fk_MaterialMode fk_Model::getMaterialMode(void)
	{
		switch(GetP()->getMaterialMode()) {
			case FK_PARENT_MODE:
				return fk_MaterialMode::PARENT;

			case FK_CHILD_MODE:
				return fk_MaterialMode::CHILD;
		}
		return fk_MaterialMode::NONE;
	}

	void fk_Model::setPickMode(bool argMode)
	{
		GetP()->setPickMode(argMode);
	}

	bool fk_Model::getPickMode(void)
	{
		return GetP()->getPickMode();
	}

	void fk_Model::setSmoothMode(bool argMode)
	{
		GetP()->setSmoothMode(argMode);
	}

	bool fk_Model::getSmoothMode(void)
	{
		return GetP()->getSmoothMode();
	}

	void fk_Model::setReverseDrawMode(bool argMode)
	{
		GetP()->setReverseDrawMode(argMode);
	}

	bool fk_Model::getReverseDrawMode(void)
	{
		return GetP()->getReverseDrawMode();
	}

	fk_Matrix^ fk_Model::getInhMatrix(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhMatrix();
		return M;
	}

	fk_Matrix^ fk_Model::getInhInvMatrix(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhInvMatrix();
		return M;
	}
	fk_Matrix^ fk_Model::getInhBaseMatrix(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhBaseMatrix();
		return M;
	}

	fk_Matrix^ fk_Model::getInhInvBaseMatrix(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhInvBaseMatrix();
		return M;
	}

	fk_Vector^ fk_Model::getInhPosition(void)
	{
		return gcnew fk_Vector(GetP()->getInhPosition());
	}

	fk_Vector^ fk_Model::getInhVec(void)
	{
		return gcnew fk_Vector(GetP()->getInhVec());
	}

	fk_Vector^ fk_Model::getInhUpvec(void)
	{
		return gcnew fk_Vector(GetP()->getInhUpvec());
	}

	fk_Angle^ fk_Model::getInhAngle(void)
	{
		fk_Angle^ A = gcnew fk_Angle();
		*A->pAngle = GetP()->getInhAngle();
		return A;
	}

	double fk_Model::getInhScale(void)
	{
		return GetP()->getInhScale();
	}

	bool fk_Model::setParent(fk_Model^ argM, bool argMode)
	{
		if(!argM) return false;

		return GetP()->setParent(argM->GetP(), argMode);
	}

	bool fk_Model::setParent(fk_Model^ argM)
	{
		return setParent(argM, false);
	}

	void fk_Model::deleteParent(bool argMode)
	{
		GetP()->deleteParent(argMode);
	}

	void fk_Model::deleteParent(void)
	{
		deleteParent(false);
	}

	fk_Model^ fk_Model::getParent(void)
	{
		if(GetP()->getParent() == NULL) return nullptr;
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = GetP()->getParent();
		return M;
	}

	bool fk_Model::entryChild(fk_Model^ argModel, bool argMode)
	{
		if(!argModel) return false;
		return GetP()->entryChild(argModel->GetP(), argMode);
	}

	bool fk_Model::entryChild(fk_Model^ argModel)
	{
		return entryChild(argModel, false);
	}

	bool fk_Model::deleteChild(fk_Model^ argModel, bool argMode)
	{
		if(!argModel) return false;
		return GetP()->deleteChild(argModel->GetP(), argMode);
	}

	bool fk_Model::deleteChild(fk_Model^ argModel)
	{
		return deleteChild(argModel, false);
	}

	void fk_Model::deleteChildren(bool argMode)
	{
		GetP()->deleteChildren(argMode);
	}

	void fk_Model::deleteChildren(void)
	{
		deleteChildren(false);
	}

	void fk_Model::snapShot(void)
	{
		GetP()->snapShot();
	}

	bool fk_Model::restore(void)
	{
		return GetP()->restore();
	}

	bool fk_Model::restore(double argT)
	{
		return GetP()->restore(argT);
	}

	void fk_Model::adjustSphere(void)
	{
		GetP()->adjustSphere();
	}

	void fk_Model::adjustAABB(void)
	{
		GetP()->adjustAABB();
	}

	void fk_Model::adjustOBB(void)
	{
		GetP()->adjustOBB();
	}

	void fk_Model::adjustCapsule(fk_Vector^ argS, fk_Vector^ argE)
	{
		if(!argS || !argE) return;
		GetP()->adjustCapsule(*argS->pVec, *argE->pVec);
	}

	bool fk_Model::isInter(fk_Model^ argModel)
	{
		if(!argModel) return false;
		return GetP()->isInter(argModel->GetP());
	}

	bool fk_Model::isCollision(fk_Model^ argModel, double %argTime)
	{
		double tmpT;
		bool retVal = GetP()->isCollision(argModel->GetP(), &tmpT);
		argTime = tmpT;
		return retVal;
	}

	void fk_Model::setInterMode(bool argMode)
	{
		GetP()->setInterMode(argMode);
	}

	bool fk_Model::getInterMode(void)
	{
		return GetP()->getInterMode();
	}

	bool fk_Model::getInterStatus(void)
	{
		return GetP()->getInterStatus();
	}

	void fk_Model::resetInter(void)
	{
		GetP()->resetInter();
	}

	void fk_Model::setInterStopMode(bool argMode)
	{
		GetP()->setInterStopMode(argMode);
	}

	bool fk_Model::getInterStopMode(void)
	{
		return GetP()->getInterStopMode();
	}

	void fk_Model::entryInterModel(fk_Model^ argModel)
	{
		GetP()->entryInterModel(argModel->GetP());
	}

	void fk_Model::deleteInterModel(fk_Model^ argModel)
	{
		GetP()->deleteInterModel(argModel->GetP());
	}

	void fk_Model::clearInterModel(void)
	{
		GetP()->clearInterModel();
	}
}
