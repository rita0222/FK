#include "Model_CLI.h"

namespace FK_CLI {

	::fk_Model * fk_Model::GetP(void)
	{
		return (::fk_Model *)(pBase);
	}

	fk_Model::fk_Model(): fk_Boundary(false), shape(nullptr)
	{
		pBase = new ::fk_Model();
		modelList->Add(this);
	}

	fk_Model::fk_Model(bool argNewFlg): fk_Boundary(false), shape(nullptr)
	{
		if(argNewFlg == true) pBase = new ::fk_Model();
		modelList->Add(this);
	}

	fk_Model::~fk_Model()
	{
		shape = nullptr;
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
		modelList->Remove(this);
	}

	fk_Model::!fk_Model()
	{
		shape = nullptr;
		if(pBase == nullptr) return;
		if(dFlg == true) {
			GetP()->SetTreeDelMode(false);
			delete GetP();
		}
		pBase = nullptr;
		modelList->Remove(this);
	}

	//////////////////////////////////////////////////////////////////////////

	unsigned int fk_Model::ID::get(void)
	{
		return GetP()->getID();
	}

	void fk_Model::Shape::set(fk_Shape^ argShape)
	{
		shape = argShape;
		if(!argShape) return;
		::fk_Shape *pS = (::fk_Shape *)(argShape->pBase);
		GetP()->setShape(pS);
	}

	fk_Shape^ fk_Model::Shape::get(void)
	{
		return shape;
	}

	void fk_Model::Material::set(fk_Material^ argM)
	{
		if(!argM) return;
		GetP()->setMaterial(*argM->pMat);
	}

	fk_Material^ fk_Model::Material::get(void)
	{
		fk_Material^ M = gcnew fk_Material();
		*M->pMat = *GetP()->getMaterial();
		return M;
	}

	fk_Material^ fk_Model::InhMaterial::get(void)
	{
		fk_Material^ M = gcnew fk_Material();
		*M->pMat = *GetP()->getInhMaterial();
		return M;
	}

	fk_Color^ fk_Model::PointColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getPointColor();
		return C;
	}

	void fk_Model::PointColor::set(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setPointColor(argC->pCol);
	}

	fk_Color^ fk_Model::InhPointColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getInhPointColor();
		return C;
	}

	void fk_Model::LineColor::set(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setLineColor(argC->pCol);
	}

	fk_Color^ fk_Model::LineColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getLineColor();
		return C;
	}
	
	fk_Color^ fk_Model::InhLineColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getInhLineColor();
		return C;
	}

	void fk_Model::PointSize::set(double argSize)
	{
		GetP()->setSize(argSize);
	}

	double fk_Model::PointSize::get(void)
	{
		return GetP()->getSize();
	}
	
	void fk_Model::LineWidth::set(double argWidth)
	{
		GetP()->setWidth(argWidth);
	}

	double fk_Model::LineWidth::get(void)
	{
		return GetP()->getWidth();
	}

	void fk_Model::DrawMode::set(fk_DrawMode argMode)
	{
		unsigned int mode = static_cast<unsigned int>(argMode);
		GetP()->setDrawMode(mode);
	}

	fk_DrawMode fk_Model::DrawMode::get(void)
	{
		return static_cast<fk_DrawMode>(GetP()->getDrawMode());
	}

	void fk_Model::MaterialMode::set(fk_MaterialMode argMode)
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

	fk_MaterialMode fk_Model::MaterialMode::get(void)
	{
		switch(GetP()->getMaterialMode()) {
			case FK_PARENT_MODE:
				return fk_MaterialMode::PARENT;

			case FK_CHILD_MODE:
				return fk_MaterialMode::CHILD;
		}
		return fk_MaterialMode::NONE;
	}

	void fk_Model::PickMode::set(bool argMode)
	{
		GetP()->setPickMode(argMode);
	}

	bool fk_Model::PickMode::get(void)
	{
		return GetP()->getPickMode();
	}

	void fk_Model::SmoothMode::set(bool argMode)
	{
		GetP()->setSmoothMode(argMode);
	}

	bool fk_Model::SmoothMode::get(void)
	{
		return GetP()->getSmoothMode();
	}

	void fk_Model::ReverseDrawMode::set(bool argMode)
	{
		GetP()->setReverseDrawMode(argMode);
	}

	bool fk_Model::ReverseDrawMode::get(void)
	{
		return GetP()->getReverseDrawMode();
	}

	fk_Matrix^ fk_Model::InhMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhMatrix();
		return M;
	}

	fk_Matrix^ fk_Model::InhInvMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhInvMatrix();
		return M;
	}
	fk_Matrix^ fk_Model::InhBaseMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhBaseMatrix();
		return M;
	}

	fk_Matrix^ fk_Model::InhInvBaseMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhInvBaseMatrix();
		return M;
	}

	fk_Vector^ fk_Model::InhPosition::get(void)
	{
		return gcnew fk_Vector(GetP()->getInhPosition());
	}

	fk_Vector^ fk_Model::InhVec::get(void)
	{
		return gcnew fk_Vector(GetP()->getInhVec());
	}

	fk_Vector^ fk_Model::InhUpvec::get(void)
	{
		return gcnew fk_Vector(GetP()->getInhUpvec());
	}

	fk_Angle^ fk_Model::InhAngle::get(void)
	{
		fk_Angle^ A = gcnew fk_Angle();
		*A->pAngle = GetP()->getInhAngle();
		return A;
	}

	double fk_Model::InhScale::get(void)
	{
		return GetP()->getInhScale();
	}

	void fk_Model::Parent::set(fk_Model^ argM)
	{
		SetParent(argM, false);
	}

	fk_Model^ fk_Model::Parent::get(void)
	{
		if(GetP()->getParent() == nullptr) return nullptr;
		fk_Model^ M = gcnew fk_Model(false);
		M->pBase = GetP()->getParent();
		return M;
	}

	void fk_Model::InterMode::set(bool argMode)
	{
		GetP()->setInterMode(argMode);
	}

	bool fk_Model::InterMode::get(void)
	{
		return GetP()->getInterMode();
	}

	bool fk_Model::InterStatus::get(void)
	{
		return GetP()->getInterStatus();
	}

	void fk_Model::InterStopMode::set(bool argMode)
	{
		GetP()->setInterStopMode(argMode);
	}

	bool fk_Model::InterStopMode::get(void)
	{
		return GetP()->getInterStopMode();
	}

	////////////////////////////////////////////////////////////////////////////////

	void fk_Model::DeleteMaterial(void)
	{
		GetP()->deleteMaterial();
	}

	void fk_Model::DeletePointColor(void)
	{
		GetP()->deletePointColor();
	}

	void fk_Model::DeleteLineColor(void)
	{
		GetP()->deleteLineColor();
	}

	bool fk_Model::SetParent(fk_Model^ argM, bool argMode)
	{
		if(!argM) return false;

		return GetP()->setParent(argM->GetP(), argMode);
	}

	bool fk_Model::SetParent(fk_Model^ argM)
	{
		return SetParent(argM, false);
	}

	void fk_Model::DeleteParent(bool argMode)
	{
		GetP()->deleteParent(argMode);
	}

	void fk_Model::DeleteParent(void)
	{
		DeleteParent(false);
	}

	bool fk_Model::EntryChild(fk_Model^ argModel, bool argMode)
	{
		if(!argModel) return false;
		return GetP()->entryChild(argModel->GetP(), argMode);
	}

	bool fk_Model::EntryChild(fk_Model^ argModel)
	{
		return EntryChild(argModel, false);
	}

	bool fk_Model::DeleteChild(fk_Model^ argModel, bool argMode)
	{
		if(!argModel) return false;
		return GetP()->deleteChild(argModel->GetP(), argMode);
	}

	bool fk_Model::DeleteChild(fk_Model^ argModel)
	{
		return DeleteChild(argModel, false);
	}

	void fk_Model::DeleteChildren(bool argMode)
	{
		GetP()->deleteChildren(argMode);
	}

	void fk_Model::DeleteChildren(void)
	{
		DeleteChildren(false);
	}

	void fk_Model::SnapShot(void)
	{
		GetP()->snapShot();
	}

	bool fk_Model::Restore(void)
	{
		return GetP()->restore();
	}

	bool fk_Model::Restore(double argT)
	{
		return GetP()->restore(argT);
	}

	void fk_Model::AdjustSphere(void)
	{
		GetP()->adjustSphere();
	}

	void fk_Model::AdjustAABB(void)
	{
		GetP()->adjustAABB();
	}

	void fk_Model::AdjustOBB(void)
	{
		GetP()->adjustOBB();
	}

	void fk_Model::AdjustCapsule(fk_Vector^ argS, fk_Vector^ argE)
	{
		if(!argS || !argE) return;
		GetP()->adjustCapsule(::fk_Vector(argS->x_, argS->y_, argS->z_),
							  ::fk_Vector(argE->x_, argE->y_, argE->z_));
	}

	bool fk_Model::IsInter(fk_Model^ argModel)
	{
		if(!argModel) return false;
		return GetP()->isInter(argModel->GetP());
	}

	bool fk_Model::IsCollision(fk_Model^ argModel, double %argTime)
	{
		double tmpT;
		bool retVal = GetP()->isCollision(argModel->GetP(), &tmpT);
		argTime = tmpT;
		return retVal;
	}

	void fk_Model::ResetInter(void)
	{
		GetP()->resetInter();
	}

	void fk_Model::EntryInterModel(fk_Model^ argModel)
	{
		GetP()->entryInterModel(argModel->GetP());
	}

	void fk_Model::DeleteInterModel(fk_Model^ argModel)
	{
		GetP()->deleteInterModel(argModel->GetP());
	}

	void fk_Model::ClearInterModel(void)
	{
		GetP()->clearInterModel();
	}

	////////////////////////////////////////////////////////////////////////////////
	
	bool fk_Model::GlRotate(fk_Vector^ argO, fk_Axis argAxis, double argTheta)
	{
		if(!argO) return false;
		return GetP()->glRotate(argO->x_, argO->y_, argO->z_, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::GlRotate(double argX, double argY, double argZ, fk_Axis argAxis, double argTheta)
	{
		return GetP()->glRotate(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::GlRotate(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->glRotate(argA->x_, argA->y_, argA->z_,
								argB->x_, argB->y_, argB->z_, argTheta);
	}

	bool fk_Model::GlRotate(double argAx, double argAy, double argAz,
							double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->glRotate(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::LoRotate(fk_Vector^ argO, fk_Axis argAxis, double argTheta)
	{
		if(!argO) return false;
		return GetP()->loRotate(argO->x_, argO->y_, argO->z_, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::LoRotate(double argX, double argY, double argZ, fk_Axis argAxis, double argTheta)
	{
		return GetP()->loRotate(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::LoRotate(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->loRotate(argA->x_, argA->y_, argA->z_,
								argB->x_, argB->y_, argB->z_, argTheta);
	}

	bool fk_Model::LoRotate(double argAx, double argAy, double argAz,
							double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->loRotate(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::GlRotateWithVec(fk_Vector^ argO, fk_Axis argAxis, double argTheta)
	{
		if(!argO) return false;
		return GetP()->glRotateWithVec(argO->x_, argO->y_, argO->z_, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::GlRotateWithVec(double argX, double argY, double argZ,
								   fk_Axis argAxis, double argTheta)
	{
		return GetP()->glRotateWithVec(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::GlRotateWithVec(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->glRotateWithVec(argA->x_, argA->y_, argA->z_,
									   argB->x_, argB->y_, argB->z_, argTheta);
	}

	bool fk_Model::GlRotateWithVec(double argAx, double argAy, double argAz,
								   double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->glRotateWithVec(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::LoRotateWithVec(fk_Vector^ argO, fk_Axis argAxis, double argTheta)
	{
		if(!argO) return false;
		return GetP()->loRotateWithVec(argO->x_, argO->y_, argO->z_, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::LoRotateWithVec(double argX, double argY, double argZ,
								   fk_Axis argAxis, double argTheta)
	{
		return GetP()->loRotateWithVec(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::LoRotateWithVec(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->loRotateWithVec(argA->x_, argA->y_, argA->z_,
									   argB->x_, argB->y_, argB->z_, argTheta);
	}

	bool fk_Model::LoRotateWithVec(double argAx, double argAy, double argAz,
								   double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->loRotateWithVec(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::GlTranslate(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glTranslate(argV->x_, argV->y_, argV->z_);
	}

	bool fk_Model::GlTranslate(double argX, double argY, double argZ)
	{
		return GetP()->glTranslate(argX, argY, argZ);
	}

	bool fk_Model::LoTranslate(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->loTranslate(argV->x_, argV->y_, argV->z_);
	}

	bool fk_Model::LoTranslate(double argX, double argY, double argZ)
	{
		return GetP()->loTranslate(argX, argY, argZ);
	}

	bool fk_Model::GlMoveTo(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glMoveTo(argV->x_, argV->y_, argV->z_);
	}

	bool fk_Model::GlMoveTo(double argX, double argY, double argZ)
	{
		return GetP()->glMoveTo(argX, argY, argZ);
	}
}
