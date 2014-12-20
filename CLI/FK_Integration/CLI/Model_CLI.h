// Model_CLI.h

#pragma once

#include <FK/Model.h>
#include "Base_CLI.h"

using namespace std;
using namespace System;

namespace FK_CLI
{
	public ref class fk_Model : fk_BaseObject {
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
		/*
		fk_Vector		getPosition(void) const;
		fk_Vector		getVec(void) const;
		fk_Vector		getUpvec(void) const;
		fk_Angle		getAngle(void) const;
		fk_Matrix		getMatrix(void) const;
		fk_Matrix		getInvMatrix(void) const;
		fk_Matrix	getBaseMatrix(void) const;
		fk_Matrix	getInvBaseMatrix(void) const;
		bool			setScale(const double scale);
		bool			setScale(const double scale, fk_Axis axis);
		bool			setScale(const double x, const double y, const double z);
		bool			prdScale(const double scale);
		bool			prdScale(const double scale, fk_Axis axis);
		bool			prdScale(const double x, const double y, const double z);
		double			getScale(void) const;
		double			getScale(fk_Axis axis) const;
		bool			getScaleMode(void) const;
		bool			glFocus(fk_Vector p);
		bool			glFocus(double x, double y, double z);
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
		unsigned int	getID(void) const;
		void	setShape(fk_Shape *shape);
		fk_Shape *	getShape(void) const;
		void	setMaterial(const fk_Material &mat);
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
		void	setSize(const double size);
		void	setWidth(const double width);
		double	getSize(void) const;
		double	getWidth(void) const;
		void	setDrawMode(const fk_DrawMode mode);
		fk_DrawMode		getDrawMode(void) const;
		void	setMaterialMode(const fk_MaterialMode mode);
		fk_MaterialMode		getMaterialMode(void) const;
		void	setPickMode(const bool mode);
		bool	getPickMode(void) const;
		void	setSmoothMode(const bool mode);
		bool	getSmoothMode(void) const;
		void	setReverseDrawMode(const bool mode);
		bool	getReverseDrawMode(void) const;
		fk_Matrix	getInhMatrix(void) const;
		fk_Matrix	getInhInvMatrix(void) const;
		fk_OrthoMatrix	getInhBaseMatrix(void) const;
		fk_OrthoMatrix	getInhInvBaseMatrix(void) const;
		fk_Vector	getInhPosition(void) const;
		fk_Vector	getInhVec(void) const;
		fk_Vector	getInhUpvec(void) const;
		fk_Angle	getInhAngle(void) const;
		double	getInhScale(void) const;
		bool	setParent(fk_Model *model, bool setMode = false);
		void	deleteParent(bool setMode = false);
		fk_Model *	getParent(void) const;
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
