// Model_CLI.h

#pragma once

#include <FK/Model.h>
#include "Shape_CLI.h"
#include "Vector_CLI.h"
#include "Matrix_CLI.h"
#include "Material_CLI.h"

using namespace std;
using namespace System;

namespace FK_CLI
{
	public ref class fk_Model : fk_BaseObject {
	internal:
		::fk_Model * GetP(void)
		{
			return (reinterpret_cast<::fk_Model *>(this->pBase));
		}

	public:
		fk_Model::fk_Model(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				::fk_Model *p = new ::fk_Model();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
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
		/*
		bool glFocus(double x, double y, double z)
		{
			
		bool			loFocus(fk_Vector p);
		bool			loFocus(double x, double y, double z);
		bool			glVec(fk_Vector v);
		bool			glVec(double x, double y, double z);
		bool			glUpvec(fk_Vector v);
		bool			glUpvec(double x, double y, double z);
		bool			loUpvec(fk_Vector v);
		bool			loUpvec(double x, double y, double z);
		bool			glAngle(fk_Angle angle);
		bool			glAngle(double h, double p, double b);
		bool			loAngle(fk_Angle angle);
		bool			loAngle(double h, double p, double b);
		bool	glRotate(fk_Vector origin, fk_Axis axis, double theta);
		bool 	glRotate(double orgX, double orgY, double orgZ, fk_Axis axis, double theta);
		bool 	glRotate(fk_Vector A, fk_Vector B, double theta);
		bool	glRotate(double Ax, double Ay, double Az,
						 double Bx, double By, double Bz, double theta);
		bool	loRotate(fk_Vector origin, fk_Axis axis, double theta);
		bool	loRotate(double orgX, double orgY, double orgZ, fk_Axis axis, double theta);
		bool	loRotate(fk_Vector A, fk_Vector B, double theta);
		bool	loRotate(double Ax, double Ay, double Az,
						 double Bx, double By, double Bz, double theta);
		bool	glRotateWithVec(fk_Vector origin, fk_Axis axis, double theta);
		bool	glRotateWithVec(double orgX, double orgY, double orgZ, fk_Axis axis, double theta);
		bool	glRotateWithVec(fk_Vector A, fk_Vector B, double theta);
		bool	glRotateWithVec(double Ax, double Ay, double Az,
								double Bx, double By, double Bz, double theta);
		bool	loRotateWithVec(fk_Vector origin, fk_Axis axis, double theta);
		bool	loRotateWithVec(double orgX, double orgY, double orgZ, fk_Axis axis, double theta);
		bool	loRotateWithVec(fk_Vector A, fk_Vector B, double theta);
		bool	loRotateWithVec(double Ax, double Ay, double Az,
								double Bx, double By, double Bz, double theta);
		bool	glTranslate(fk_Vector v);
		bool	glTranslate(double x, double y, double z);
		bool	loTranslate(fk_Vector v);
		bool	loTranslate(double x, double y, double z);
		bool	glMoveTo(fk_Vector p);
		bool	glMoveTo(double x, double y, double z);
		void		setBMode(fk_BoundaryMode mode);
		fk_BoundaryMode			getBMode(void);
		void		setSphere(double r);
		double		getSphere(void);
		void		setAABBSize(double x, double y, double z);
		void		setAABBSize(fk_Vector size);
		fk_Vector	getAABBSize(void);
		void		setOBBSize(double x, double y, double z);
		void		setOBBSize(fk_Vector size);
		fk_Vector	getOBBSize(void);
		void		setCapsule(fk_Vector sPos, fk_Vector ePos, double r);
		double		getCapsuleRadius(void);
		double		getCapsuleLength(void);
		fk_Vector	getCapsuleStartPos(void);
		fk_Vector	getCapsuleEndPos(void);
		void		setBDrawToggle(bool mode);
		bool		getBDrawToggle(void);
		void		setBLineColor(fk_Color col);
		fk_Color *	getBLineColor(void);
		void		setBIntLineColor(fk_Color col);
		fk_Color *	getBIntLineColor(void);
		void		setBLineWidth(double width);
		double		getBLineWidth(void);
		unsigned int	getID(void);
		void	setShape(fk_Shape *shape);
		fk_Shape *	getShape(void);
		void	setMaterial(fk_Material &mat);
		void	setPointColor(fk_Color *col);
		void	setPointColor(float r, float g, float b);
		void	setLineColor(fk_Color *col);
		void	setLineColor(float r, float g, float b);
		void	deleteMaterial(void);
		void	deletePointColor(void);
		void	deleteLineColor(void);
		fk_Material *	getMaterial(void);
		fk_Material *	getInhMaterial(void);
		fk_Color *	getPointColor(void);
		fk_Color *	getInhPointColor(void);
		fk_Color *	getLineColor(void);
		fk_Color *	getInhLineColor(void);
		void	setSize(double size);
		void	setWidth(double width);
		double	getSize(void);
		double	getWidth(void);
		void	setDrawMode(fk_DrawMode mode);
		fk_DrawMode		getDrawMode(void);
		void	setMaterialMode(fk_MaterialMode mode);
		fk_MaterialMode		getMaterialMode(void);
		void	setPickMode(bool mode);
		bool	getPickMode(void);
		void	setSmoothMode(bool mode);
		bool	getSmoothMode(void);
		void	setReverseDrawMode(bool mode);
		bool	getReverseDrawMode(void);
		fk_Matrix	getInhMatrix(void);
		fk_Matrix	getInhInvMatrix(void);
		fk_OrthoMatrix	getInhBaseMatrix(void);
		fk_OrthoMatrix	getInhInvBaseMatrix(void);
		fk_Vector	getInhPosition(void);
		fk_Vector	getInhVec(void);
		fk_Vector	getInhUpvec(void);
		fk_Angle	getInhAngle(void);
		double	getInhScale(void);
		bool	setParent(fk_Model *model, bool setMode = false);
		void	deleteParent(bool setMode = false);
		fk_Model *	getParent(void);
		bool	entryChild(fk_Model *model, bool setMode = false);
		bool	deleteChild(fk_Model *model, bool setMode = false);
		void	deleteChildren(bool setMode = false);
		fk_Model *	foreachChild(fk_Model *model);
		void	snapShot(void);
		bool	restore(void);
		bool	restore(double t);
		void	adjustSphere(void);
		void	adjustAABB(void);
		void	adjustOBB(void);
		void	adjustCapsule(fk_Vector S, fk_Vector E);
		bool	isInter(fk_Model *model);
		bool	isCollision(fk_Model *model, double *time);
		void	setInterMode(bool mode);
		bool	getInterMode(void);
		bool	getInterStatus(void);
		void	resetInter(void);
		void	setInterStopMode(bool mode);
		bool	getInterStopMode(void);
		void	entryInterModel(fk_Model *model);
		void	deleteInterModel(fk_Model *model);
		void	clearInterModel(void);
		*/
	};
}
