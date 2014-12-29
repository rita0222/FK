// Model_CLI.h

#pragma once

#include <FK/Model.h>
#include "Shape_CLI.h"
#include "Vector_CLI.h"
#include "Matrix_CLI.h"
#include "Material_CLI.h"

namespace FK_CLI
{
	public enum class fk_BoundaryMode {
		SPHERE,
		AABB,
		OBB,
		CAPSULE,
		NONE
	};

	public enum class fk_DrawMode : unsigned int {
		NONEMODE			= 0x0000,
		POINTMODE			= 0x0001,
		LINEMODE			= 0x0002,
		POLYMODE			= 0x0004,
		BACK_POLYMODE		= (0x0008 | FK_POLYMODE),
		FRONTBACK_POLYMODE	= (0x0010 | FK_POLYMODE),
		TEXTUREMODE			= 0x0020
	};

	public ref class fk_Model {
	internal:

		bool dFlg;
		::fk_Model *pModel;


		::fk_Model * GetP(void)
		{
			return pModel;
		}

	public:
		fk_Model::fk_Model()
		{
			this->pModel = new ::fk_Model();
		}

		fk_Model::fk_Model(bool argNewFlg)
		{
			if(argNewFlg == true) this->pModel = new ::fk_Model();
		}

		fk_Model::~fk_Model()
		{
			this->!fk_Model();
		}

		fk_Model::!fk_Model()
		{
			if(dFlg == true) delete this->pModel;
			this->pModel = NULL;
		}

		fk_Vector^ getPosition(void);
		fk_Vector^ getVec(void);
		fk_Vector^ getUpvec(void);
		fk_Angle^ getAngle(void);
		fk_Matrix^ getMatrix(void);
		fk_Matrix^ getInvMatrix(void);
		fk_Matrix^ getBaseMatrix(void);
		fk_Matrix^ getInvBaseMatrix(void);
		bool setScale(double scale);
		bool setScale(double scale, fk_Axis axis);
		bool setScale(double x, double y, double z);
		bool prdScale(double scale);
		bool prdScale(double scale, fk_Axis axis);
		bool prdScale(double x, double y, double z);
		double getScale(void);
		double getScale(fk_Axis axis);
		bool getScaleMode(void);
		bool glFocus(fk_Vector^ V);
		bool glFocus(double x, double y, double z);
		bool loFocus(fk_Vector^ V);
		bool loFocus(double x, double y, double z);
		bool glVec(fk_Vector^ V);
		bool glVec(double x, double y, double z);
		bool glUpvec(fk_Vector^ V);
		bool glUpvec(double x, double y, double z);
		bool loUpvec(fk_Vector^ V);
		bool loUpvec(double x, double y, double z);
		bool glAngle(fk_Angle^ angle);
		bool glAngle(double head, double pitch, double bank);
		bool loAngle(fk_Angle^ angle);
		bool loAngle(double head, double pitch, double bank);
		bool glRotate(fk_Vector^ origin, fk_Axis axis, double theta);
		bool glRotate(double x, double y, double z, fk_Axis axis, double theta);
		bool glRotate(fk_Vector^ A, fk_Vector^ B, double theta);
		bool glRotate(double Ax, double Ay, double Az,
					  double Bx, double By, double Bz, double theta);
		bool loRotate(fk_Vector^ origin, fk_Axis axis, double theta);
		bool loRotate(double x, double y, double z, fk_Axis axis, double theta);
		bool loRotate(fk_Vector^ A, fk_Vector^ B, double theta);
		bool loRotate(double Ax, double Ay, double Az,
					  double Bx, double By, double Bz, double theta);
		bool glRotateWithVec(fk_Vector^ origin, fk_Axis axis, double theta);
		bool glRotateWithVec(double x, double y, double z, fk_Axis axis, double theta);
		bool glRotateWithVec(fk_Vector^ A, fk_Vector^ B, double theta);
		bool glRotateWithVec(double Ax, double Ay, double Az,
							 double Bx, double By, double Bz, double theta);
		bool loRotateWithVec(fk_Vector^ origin, fk_Axis axis, double theta);
		bool loRotateWithVec(double x, double y, double z, fk_Axis axis, double theta);
		bool loRotateWithVec(fk_Vector^ A, fk_Vector^ B, double theta);
		bool loRotateWithVec(double Ax, double Ay, double Az,
							 double Bx, double By, double Bz, double theta);
		bool glTranslate(fk_Vector^ V);
		bool glTranslate(double x, double y, double z);
		bool loTranslate(fk_Vector^ V);
		bool loTranslate(double x, double y, double z);
		bool glMoveTo(fk_Vector^ V);
		bool glMoveTo(double x, double y, double z);
		void setBMode(fk_BoundaryMode mode);
		fk_BoundaryMode getBMode(void);
		void setSphere(double radius);
		double getSphere(void);
		void setAABBSize(double x, double y, double z);
		void setAABBSize(fk_Vector^ argSize);
		fk_Vector^ getAABBSize(void);
		void setOBBSize(double x, double y, double z);
		void setOBBSize(fk_Vector^ sizeV);
		fk_Vector^ getOBBSize(void);
		void setCapsule(fk_Vector^ startPos, fk_Vector^ endPos, double radius);
		double getCapsuleRadius(void);
		double getCapsuleLength(void);
		fk_Vector^ getCapsuleStartPos(void);
		fk_Vector^ getCapsuleEndPos(void);
		void setBDrawToggle(bool mode);
		bool getBDrawToggle(void);
		void setBLineColor(fk_Color^ color);
		fk_Color^ getBLineColor(void);
		void setBIntLineColor(fk_Color^ color);
		fk_Color^ getBIntLineColor(void);
		void setBLineWidth(double width);
		double getBLineWidth(void);
		unsigned int getID(void);
		void setShape(fk_Shape^ argShape);
		fk_Shape^ getShape(void);
		void setMaterial(fk_Material^ material);
		void setPointColor(fk_Color^ color);
		void setPointColor(float r, float g, float b);
		void setLineColor(fk_Color^ color);
		void setLineColor(float r, float g, float b);
		void deleteMaterial(void);
		void deletePointColor(void);
		void deleteLineColor(void);
		fk_Material^ getMaterial(void);
		fk_Material^ getInhMaterial(void);
		fk_Color^ getPointColor(void);
		fk_Color^ getInhPointColor(void);
		fk_Color^ getLineColor(void);
		fk_Color^ getInhLineColor(void);
		void setSize(double size);
		void setWidth(double width);
		double getSize(void);
		double getWidth(void);
		void setDrawMode(fk_DrawMode mode);
		fk_DrawMode getDrawMode(void);
		void setMaterialMode(fk_MaterialMode mode);
		fk_MaterialMode getMaterialMode(void);
		void setPickMode(bool mode);
		bool getPickMode(void);
		void setSmoothMode(bool mode);
		bool getSmoothMode(void);
		void setReverseDrawMode(bool mode);
		bool getReverseDrawMode(void);
		fk_Matrix^ getInhMatrix(void);
		fk_Matrix^ getInhInvMatrix(void);
		fk_Matrix^ getInhBaseMatrix(void);
		fk_Matrix^ getInhInvBaseMatrix(void);
		fk_Vector^ getInhPosition(void);
		fk_Vector^ getInhVec(void);
		fk_Vector^ getInhUpvec(void);
		fk_Angle^ getInhAngle(void);
		double getInhScale(void);
		bool setParent(fk_Model^ model, bool mode);
		bool setParent(fk_Model^ model);
		void deleteParent(bool mode);
		void deleteParent(void);
		fk_Model^ getParent(void);
		bool entryChild(fk_Model^ model, bool mode);
		bool entryChild(fk_Model^ model);
		bool deleteChild(fk_Model^ model, bool mode);
		bool deleteChild(fk_Model^ model);
		void deleteChildren(bool mode);
		void deleteChildren(void);
		void snapShot(void);
		bool restore(void);
		bool restore(double time);
		void adjustSphere(void);
		void adjustAABB(void);
		void adjustOBB(void);
		void adjustCapsule(fk_Vector^ startPos, fk_Vector^ endPos);
		bool isInter(fk_Model^ model);
		bool isCollision(fk_Model^ model, double %time);
		void setInterMode(bool mode);
		bool getInterMode(void);
		bool getInterStatus(void);
		void resetInter(void);
		void setInterStopMode(bool mode);
		bool getInterStopMode(void);
		void entryInterModel(fk_Model^ model);
		void deleteInterModel(fk_Model^ model);
		void clearInterModel(void);
	};
}
