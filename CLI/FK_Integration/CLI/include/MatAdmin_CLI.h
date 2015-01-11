// MatAdmin_CLI.h

#pragma once

#include <FK/MatAdmin.h>
#include "Base_CLI.h"
#include "Matrix_CLI.h"

namespace FK_CLI
{
	public ref class fk_MatrixAdmin : fk_BaseObject {
	internal:
		::fk_MatrixAdmin * GetP(void)
		{
			return (::fk_MatrixAdmin *)(pBase);
		}

	public:
		fk_MatrixAdmin::fk_MatrixAdmin(bool argNewFlg) : fk_BaseObject(false)
		{
		}

		fk_MatrixAdmin::~fk_MatrixAdmin()
		{
			this->!fk_MatrixAdmin();
		}

		fk_MatrixAdmin::!fk_MatrixAdmin()
		{
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
	};
}
