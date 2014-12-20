// Model_CLI.h

#pragma once

#include <FK/Model.h>
#include <list>
#include "Shape_CLI.h"
#include "Vector_CLI.h"
#include "Matrix_CLI.h"
#include "Material_CLI.h"

using namespace std;
using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace FK_CLI
{
	public enum class fk_BoundaryMode
	{
		SPHERE,
		AABB,
		OBB,
		CAPSULE,
		NONE
	};

	public enum class fk_DrawMode : unsigned int
	{
		NONEMODE			= 0x0000,
		POINTMODE			= 0x0001,
		LINEMODE			= 0x0002,
		POLYMODE			= 0x0004,
		BACK_POLYMODE		= (0x0008 | FK_POLYMODE),
		FRONTBACK_POLYMODE	= (0x0010 | FK_POLYMODE),
		TEXTUREMODE			= 0x0020
	};

	public ref class fk_Model : fk_BaseObject {
	internal:
		fk_Shape^					shape;
		fk_Model^					parent;
		List<fk_Model^>^			childList;
		
		::fk_Model * GetP(void)
		{
			return (reinterpret_cast<::fk_Model *>(this->pBase));
		}

	public:
		fk_Model::fk_Model()
			: fk_BaseObject(false), shape(nullptr), parent(nullptr)
		{
			::fk_Model *p = new ::fk_Model();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			childList = gcnew List<fk_Model^>();
		}

		fk_Model::fk_Model(bool argNewFlg)
			: fk_BaseObject(false), shape(nullptr), parent(nullptr)
		{
			if(argNewFlg == true) {
				::fk_Model *p = new ::fk_Model();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
			childList = gcnew List<fk_Model^>();
		}

		fk_Model::~fk_Model()
		{
			this->!fk_Model();
		}

		fk_Model::!fk_Model()
		{
			delete this->pBase;
			this->pBase = NULL;
		}

		fk_Vector^ getPosition(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getPosition();
			return V;
		}

		fk_Vector^ getVec(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getVec();
			return V;
		}

		fk_Vector^ getUpvec(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getUpvec();
			return V;
		}

		fk_Angle^ getAngle(void)
		{
			fk_Angle^ A = gcnew fk_Angle();
			*A->pAngle = GetP()->getAngle();
			return A;
		}

		fk_Matrix^ getMatrix(void)
		{
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = GetP()->getMatrix();
			return M;
		}
			
		fk_Matrix^ getInvMatrix(void)
		{
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = GetP()->getInvMatrix();
			return M;
		}

		fk_Matrix^ getBaseMatrix(void)
		{
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = GetP()->getBaseMatrix();
			return M;
		}

		fk_Matrix^ getInvBaseMatrix(void)
		{
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = GetP()->getInvBaseMatrix();
			return M;
		}

		bool setScale(double argScale)
		{
			return GetP()->setScale(argScale);
		}

		bool setScale(double argScale, fk_Axis argAxis)
		{
			return GetP()->setScale(argScale, GetAxis(argAxis));
		}

		bool setScale(double argX, double argY, double argZ)
		{
			return GetP()->setScale(argX, argY, argZ);
		}
		bool prdScale(double argScale)
		{
			return GetP()->prdScale(argScale);
		}

		bool prdScale(double argScale, fk_Axis argAxis)
		{
			return GetP()->prdScale(argScale, GetAxis(argAxis));
		}

		bool prdScale(double argX, double argY, double argZ)
		{
			return GetP()->prdScale(argX, argY, argZ);
		}

		double getScale(void)
		{
			return GetP()->getScale();
		}

		double getScale(fk_Axis argAxis)
		{
			return GetP()->getScale(GetAxis(argAxis));
		}

		bool getScaleMode(void)
		{
			return GetP()->getScaleMode();
		}
		
		bool glFocus(fk_Vector^ argV)
		{
			if(!argV) return false;
			return GetP()->glFocus(*argV->pVec);
		}

		bool glFocus(double argX, double argY, double argZ)
		{
			return GetP()->glFocus(argX, argY, argZ);
		}

		bool loFocus(fk_Vector^ argV)
		{
			if(!argV) return false;
			return GetP()->loFocus(*argV->pVec);
		}
		
		bool loFocus(double argX, double argY, double argZ)
		{
			return GetP()->loFocus(argX, argY, argZ);
		}

		bool glVec(fk_Vector^ argV)
		{
			if(!argV) return false;
			return GetP()->glVec(*argV->pVec);
		}

		bool glVec(double argX, double argY, double argZ)
		{
			return GetP()->glVec(argX, argY, argZ);
		}

		bool glUpvec(fk_Vector^ argV)
		{
			if(!argV) return false;
			return GetP()->glUpvec(*argV->pVec);
		}

		bool glUpvec(double argX, double argY, double argZ)
		{
			return GetP()->glUpvec(argX, argY, argZ);
		}

		bool loUpvec(fk_Vector^ argV)
		{
			if(!argV) return false;
			return GetP()->loUpvec(*argV->pVec);
		}

		bool loUpvec(double argX, double argY, double argZ)
		{
			return GetP()->loUpvec(argX, argY, argZ);
		}

		bool glAngle(fk_Angle^ argAngle)
		{
			if(!argAngle) return false;
			return GetP()->glAngle(*argAngle->pAngle);
		}

		bool glAngle(double argH, double argP, double argB)
		{
			return GetP()->glAngle(argH, argP, argB);
		}

		bool loAngle(fk_Angle^ argAngle)
		{
			if(!argAngle) return false;
			return GetP()->loAngle(*argAngle->pAngle);
		}			

		bool loAngle(double argH, double argP, double argB)
		{
			return GetP()->loAngle(argH, argP, argB);
		}

		bool glRotate(fk_Vector^ argOrigin, fk_Axis argAxis, double argTheta)
		{
			if(!argOrigin) return false;
			return GetP()->glRotate(*argOrigin->pVec, GetAxis(argAxis), argTheta);
		}

		bool glRotate(double argX, double argY, double argZ, fk_Axis argAxis, double argTheta)
		{
			return GetP()->glRotate(argX, argY, argZ, GetAxis(argAxis), argTheta);
		}

		bool glRotate(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
		{
			if(!argA || !argB) return false;
			return GetP()->glRotate(*argA->pVec, *argB->pVec, argTheta);
		}

		bool glRotate(double argAx, double argAy, double argAz,
					  double argBx, double argBy, double argBz, double argTheta)
		{
			return GetP()->glRotate(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
		}

		bool loRotate(fk_Vector^ argOrigin, fk_Axis argAxis, double argTheta)
		{
			if(!argOrigin) return false;
			return GetP()->loRotate(*argOrigin->pVec, GetAxis(argAxis), argTheta);
		}

		bool loRotate(double argX, double argY, double argZ, fk_Axis argAxis, double argTheta)
		{
			return GetP()->loRotate(argX, argY, argZ, GetAxis(argAxis), argTheta);
		}

		bool loRotate(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
		{
			if(!argA || !argB) return false;
			return GetP()->loRotate(*argA->pVec, *argB->pVec, argTheta);
		}

		bool loRotate(double argAx, double argAy, double argAz,
					  double argBx, double argBy, double argBz, double argTheta)
		{
			return GetP()->loRotate(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
		}

		bool glRotateWithVec(fk_Vector^ argOrigin, fk_Axis argAxis, double argTheta)
		{
			if(!argOrigin) return false;
			return GetP()->glRotateWithVec(*argOrigin->pVec, GetAxis(argAxis), argTheta);
		}

		bool glRotateWithVec(double argX, double argY, double argZ,
							 fk_Axis argAxis, double argTheta)
		{
			return GetP()->glRotateWithVec(argX, argY, argZ, GetAxis(argAxis), argTheta);
		}

		bool glRotateWithVec(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
		{
			if(!argA || !argB) return false;
			return GetP()->glRotateWithVec(*argA->pVec, *argB->pVec, argTheta);
		}

		bool glRotateWithVec(double argAx, double argAy, double argAz,
					  double argBx, double argBy, double argBz, double argTheta)
		{
			return GetP()->glRotateWithVec(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
		}

		bool loRotateWithVec(fk_Vector^ argOrigin, fk_Axis argAxis, double argTheta)
		{
			if(!argOrigin) return false;
			return GetP()->loRotateWithVec(*argOrigin->pVec, GetAxis(argAxis), argTheta);
		}

		bool loRotateWithVec(double argX, double argY, double argZ,
							 fk_Axis argAxis, double argTheta)
		{
			return GetP()->loRotateWithVec(argX, argY, argZ, GetAxis(argAxis), argTheta);
		}

		bool loRotateWithVec(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
		{
			if(!argA || !argB) return false;
			return GetP()->loRotateWithVec(*argA->pVec, *argB->pVec, argTheta);
		}

		bool loRotateWithVec(double argAx, double argAy, double argAz,
					  double argBx, double argBy, double argBz, double argTheta)
		{
			return GetP()->loRotateWithVec(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
		}

		bool glTranslate(fk_Vector^ argV)
		{
			if(!argV) return false;
			return GetP()->glTranslate(*argV->pVec);
		}

		bool glTranslate(double argX, double argY, double argZ)
		{
			return GetP()->glTranslate(argX, argY, argZ);
		}

		bool loTranslate(fk_Vector^ argV)
		{
			if(!argV) return false;
			return GetP()->loTranslate(*argV->pVec);
		}

		bool loTranslate(double argX, double argY, double argZ)
		{
			return GetP()->loTranslate(argX, argY, argZ);
		}

		bool glMoveTo(fk_Vector^ argV)
		{
			if(!argV) return false;
			return GetP()->glMoveTo(*argV->pVec);
		}

		bool glMoveTo(double argX, double argY, double argZ)
		{
			return GetP()->glMoveTo(argX, argY, argZ);
		}

		void setBMode(fk_BoundaryMode argMode)
		{
			switch(argMode) {
			  case FK_CLI::fk_BoundaryMode::SPHERE:
				GetP()->setBMode(FK_B_SPHERE);
				break;

			  case FK_CLI::fk_BoundaryMode::AABB:
				GetP()->setBMode(FK_B_AABB);
				break;
				
			  case FK_CLI::fk_BoundaryMode::OBB:
				GetP()->setBMode(FK_B_OBB);
				break;
				
			  case FK_CLI::fk_BoundaryMode::CAPSULE:
				GetP()->setBMode(FK_B_CAPSULE);
				break;

			  case FK_CLI::fk_BoundaryMode::NONE:
				GetP()->setBMode(FK_B_NONE);
				break;

			  default:
				break;
			}
		}

		fk_BoundaryMode getBMode(void)
		{
			switch(GetP()->getBMode()) {
			  case FK_B_SPHERE:
				return FK_CLI::fk_BoundaryMode::SPHERE;
				
			  case FK_B_AABB:
				return FK_CLI::fk_BoundaryMode::AABB;
				
			  case FK_B_OBB:
				return FK_CLI::fk_BoundaryMode::OBB;
				
			  case FK_B_CAPSULE:
				return FK_CLI::fk_BoundaryMode::CAPSULE;
				
			  default:
				break;
			}
			return FK_CLI::fk_BoundaryMode::NONE;
		}

		void setSphere(double argR)
		{
			GetP()->setSphere(argR);
		}

		double getSphere(void)
		{
			return GetP()->getSphere();
		}

		void setAABBSize(double argX, double argY, double argZ)
		{
			GetP()->setAABBSize(argX, argY, argZ);
		}

		void setAABBSize(fk_Vector^ argSize)
		{
			GetP()->setAABBSize(*argSize->pVec);
		}
		
		fk_Vector^ getAABBSize(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getAABBSize();
			return V;
		}

		void setOBBSize(double argX, double argY, double argZ)
		{
			GetP()->setOBBSize(argX, argY, argZ);
		}

		void setOBBSize(fk_Vector^ argSize)
		{
			GetP()->setOBBSize(*argSize->pVec);
		}
		
		fk_Vector^ getOBBSize(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getOBBSize();
			return V;
		}

		void setCapsule(fk_Vector^ argS, fk_Vector^ argE, double argR)
		{
			if(!argS || !argE) return;
			GetP()->setCapsule(*argS->pVec, *argE->pVec, argR);
		}

		double getCapsuleRadius(void)
		{
			return GetP()->getCapsuleRadius();
		}
		
		double getCapsuleLength(void)
		{
			return GetP()->getCapsuleLength();
		}

		fk_Vector^ getCapsuleStartPos(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getCapsuleStartPos();
			return V;
		}
				
		fk_Vector^ getCapsuleEndPos(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getCapsuleEndPos();
			return V;
		}
				
		void setBDrawToggle(bool argMode)
		{
			GetP()->setBDrawToggle(argMode);
		}
		
		bool getBDrawToggle(void)
		{
			return GetP()->getBDrawToggle();
		}
		
		void setBLineColor(fk_Color^ argC)
		{
			if(!argC) return;
			::fk_Color *pC = reinterpret_cast<::fk_Color *>(argC->pBase);
			GetP()->setBLineColor(*pC);
		}

		fk_Color^ getBLineColor(void)
		{
			fk_Color^ C = gcnew fk_Color();
			::fk_Color *pC = reinterpret_cast<::fk_Color *>(C->pBase);
			*pC = *GetP()->getBLineColor();
			return C;
		}

		void setBIntLineColor(fk_Color^ argC)
		{
			GetP()->setBIntLineColor(*(reinterpret_cast<::fk_Color *>(argC->pBase)));
		}
			  
		fk_Color^ getBIntLineColor(void)
		{
			fk_Color^ C = gcnew fk_Color();
			::fk_Color *pC = reinterpret_cast<::fk_Color *>(C->pBase);
			*pC = *GetP()->getBIntLineColor();
			return C;
		}

		void setBLineWidth(double argWidth)
		{
			GetP()->setBLineWidth(argWidth);
		}

		double getBLineWidth(void)
		{
			return GetP()->getBLineWidth();
		}

		unsigned int getID(void)
		{
			return GetP()->getID();
		}

		void setShape(fk_Shape^ argShape)
		{
			if(!argShape) return;
			::fk_Shape *pS = reinterpret_cast<::fk_Shape *>(argShape->pBase);
			GetP()->setShape(pS);
			shape = argShape;
		}

		fk_Shape^ getShape(void)
		{
			return shape;
		}
				
		void setMaterial(fk_Material^ argM)
		{
			if(!argM) return;
			::fk_Material *pM = reinterpret_cast<::fk_Material *>(argM->pBase);
			GetP()->setMaterial(*pM);
		}

		void setPointColor(fk_Color^ argC)
		{
			if(!argC) return;
			::fk_Color *pC = reinterpret_cast<::fk_Color *>(argC->pBase);
			GetP()->setPointColor(pC);
		}

		void setPointColor(float argR, float argG, float argB)
		{
			GetP()->setPointColor(argR, argG, argB);
		}

		void setLineColor(fk_Color^ argC)
		{
			if(!argC) return;
			::fk_Color *pC = reinterpret_cast<::fk_Color *>(argC->pBase);
			GetP()->setLineColor(pC);
		}

		void setLineColor(float argR, float argG, float argB)
		{
			GetP()->setLineColor(argR, argG, argB);
		}
		
		void deleteMaterial(void)
		{
			GetP()->deleteMaterial();
		}

		void deletePointColor(void)
		{
			GetP()->deletePointColor();
		}
		
		void deleteLineColor(void)
		{
			GetP()->deleteLineColor();
		}
		
		fk_Material^ getMaterial(void)
		{
			fk_Material^ M = gcnew fk_Material();
			::fk_Material *pM = reinterpret_cast<::fk_Material *>(M->pBase);
			*pM = *GetP()->getMaterial();
			return M;
		}

		fk_Material^ getInhMaterial(void)
		{
			fk_Material^ M = gcnew fk_Material();
			::fk_Material *pM = reinterpret_cast<::fk_Material *>(M->pBase);
			*pM = *GetP()->getInhMaterial();
			return M;
		}

		fk_Color^ getPointColor(void)
		{
			fk_Color^ C = gcnew fk_Color();
			::fk_Color *pC = reinterpret_cast<::fk_Color *>(C->pBase);
			*pC = *GetP()->getPointColor();
			return C;
		}

		fk_Color^ getInhPointColor(void)
		{
			fk_Color^ C = gcnew fk_Color();
			::fk_Color *pC = reinterpret_cast<::fk_Color *>(C->pBase);
			*pC = *GetP()->getInhPointColor();
			return C;
		}


		fk_Color^ getLineColor(void)
		{
			fk_Color^ C = gcnew fk_Color();
			::fk_Color *pC = reinterpret_cast<::fk_Color *>(C->pBase);
			*pC = *GetP()->getLineColor();
			return C;
		}

		fk_Color^ getInhLineColor(void)
		{
			fk_Color^ C = gcnew fk_Color();
			::fk_Color *pC = reinterpret_cast<::fk_Color *>(C->pBase);
			*pC = *GetP()->getInhLineColor();
			return C;
		}

		void setSize(double argSize)
		{
			GetP()->setSize(argSize);
		}

		void setWidth(double argWidth)
		{
			GetP()->setWidth(argWidth);
		}
		
		double getSize(void)
		{
			return GetP()->getSize();
		}
		
		double getWidth(void)
		{
			return GetP()->getWidth();
		}

		void setDrawMode(fk_DrawMode argMode)
		{
			unsigned int mode = static_cast<unsigned int>(argMode);
			GetP()->setDrawMode(mode);
		}

		fk_DrawMode getDrawMode(void)
		{
			return static_cast<fk_DrawMode>(GetP()->getDrawMode());
		}

		void setMaterialMode(fk_MaterialMode argMode)
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

		fk_MaterialMode getMaterialMode(void)
		{
			switch(GetP()->getMaterialMode()) {
			  case FK_PARENT_MODE:
				return fk_MaterialMode::PARENT;

			  case FK_CHILD_MODE:
				return fk_MaterialMode::CHILD;
			}
			return fk_MaterialMode::NONE;
		}

		void setPickMode(bool argMode)
		{
			GetP()->setPickMode(argMode);
		}

		bool getPickMode(void)
		{
			return GetP()->getPickMode();
		}
		
		void setSmoothMode(bool argMode)
		{
			GetP()->setSmoothMode(argMode);
		}

		bool getSmoothMode(void)
		{
			return GetP()->getSmoothMode();
		}
			
		void setReverseDrawMode(bool argMode)
		{
			GetP()->setReverseDrawMode(argMode);
		}
		
		bool getReverseDrawMode(void)
		{
			return GetP()->getReverseDrawMode();
		}
		
		fk_Matrix^ getInhMatrix(void)
		{
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = GetP()->getInhMatrix();
			return M;
		}
				
		fk_Matrix^ getInhInvMatrix(void)
		{
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = GetP()->getInhInvMatrix();
			return M;
		}
		fk_Matrix^ getInhBaseMatrix(void)
		{
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = GetP()->getInhBaseMatrix();
			return M;
		}

		fk_Matrix^ getInhInvBaseMatrix(void)
		{
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = GetP()->getInhInvBaseMatrix();
			return M;
		}

		fk_Vector^ getInhPosition(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getInhPosition();
			return V;
		}
				
		fk_Vector^ getInhVec(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getInhVec();
			return V;
		}

		fk_Vector^ getInhUpvec(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getInhUpvec();
			return V;
		}

		fk_Angle^ getInhAngle(void)
		{
			fk_Angle^ A = gcnew fk_Angle();
			*A->pAngle = GetP()->getInhAngle();
			return A;
		}				

		double getInhScale(void)
		{
			return GetP()->getInhScale();
		}

		bool setParent(fk_Model^ argM, bool argMode)
		{
			if(!argM) {
				parent = nullptr;
				return true;
			}
			::fk_Model *model = reinterpret_cast<::fk_Model *>(argM->pBase);
			if(GetP()->setParent(model, argMode) == true) {
				parent = argM;
				argM->childList->Add(this);
				return true;
			}
			return false;
		}
			
		bool setParent(fk_Model^ argM)
		{
			return setParent(argM, false);
		}

		void deleteParent(bool argMode)
		{
			if(!parent) {
				parent->childList->Remove(this);
				parent = nullptr;
			}
			GetP()->deleteParent(argMode);
		}
			
		void deleteParent(void)
		{
			deleteParent(false);
		}

		fk_Model^ getParent(void)
		{
			return parent;
		}

		bool entryChild(fk_Model^ argModel, bool argMode)
		{
			if(!argModel) return false;
			if(GetP()->entryChild(argModel->GetP(), argMode) == true) {
				argModel->parent = this;
				if(childList->Contains(argModel) == false) childList->Add(argModel);
				return true;
			}
			return false;
		}
		
		bool entryChild(fk_Model^ argModel)
		{
			return entryChild(argModel, false);
		}

		bool deleteChild(fk_Model^ argModel, bool argMode)
		{
			if(!argModel) return false;
			if(GetP()->deleteChild(argModel->GetP(), argMode) == true) {
				argModel->parent = nullptr;
				while(childList->Contains(argModel) == true) {
					childList->Remove(argModel);
				}
				return true;
			}
			return false;
		}

		bool deleteChild(fk_Model^ argModel)
		{
			return deleteChild(argModel, false);
		}

		void deleteChildren(bool argMode)
		{
			while(childList->Count != 0) {
				fk_Model^ m = childList[childList->Count-1];
				deleteChild(m, argMode);
			}
		}

		void deleteChildren(void)
		{
			deleteChildren(false);
		}

		List<fk_Model^>^ getChildren(void)
		{
			return childList;
		}

		void snapShot(void)
		{
			GetP()->snapShot();
		}

		bool restore(void)
		{
			return GetP()->restore();
		}
		
		bool restore(double argT)
		{
			return GetP()->restore(argT);
		}
		
		void adjustSphere(void)
		{
			GetP()->adjustSphere();
		}
		
		void adjustAABB(void)
		{
			GetP()->adjustAABB();
		}
		
		void adjustOBB(void)
		{
			GetP()->adjustOBB();
		}
		
		void adjustCapsule(fk_Vector^ argS, fk_Vector^ argE)
		{
			if(!argS || !argE) return;
			GetP()->adjustCapsule(*argS->pVec, *argE->pVec);
		}
			
		bool isInter(fk_Model^ argModel)
		{
			if(!argModel) return false;
			return GetP()->isInter(argModel->GetP());
		}

		bool isCollision(fk_Model^ argModel, double %argTime)
		{
			double tmpT;
			bool retVal = GetP()->isCollision(argModel->GetP(), &tmpT);
			argTime = tmpT;
			return retVal;
		}

		void setInterMode(bool argMode)
		{
			GetP()->setInterMode(argMode);
		}

		bool getInterMode(void)
		{
			return GetP()->getInterMode();
		}
		
		bool getInterStatus(void)
		{
			return GetP()->getInterStatus();
		}
		
		void resetInter(void)
		{
			GetP()->resetInter();
		}
		
		void setInterStopMode(bool argMode)
		{
			GetP()->setInterStopMode(argMode);
		}
		
		bool getInterStopMode(void)
		{
			return GetP()->getInterStopMode();
		}
		
		void entryInterModel(fk_Model^ argModel)
		{
			GetP()->entryInterModel(argModel->GetP());
		}

		void deleteInterModel(fk_Model^ argModel)
		{
			GetP()->deleteInterModel(argModel->GetP());
		}

		void clearInterModel(void)
		{
			GetP()->clearInterModel();
		}
	};
}
