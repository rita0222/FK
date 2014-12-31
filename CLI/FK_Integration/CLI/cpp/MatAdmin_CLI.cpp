#include "Model_CLI.h"

namespace FK_CLI {

	fk_Vector^ fk_MatrixAdmin::getPosition(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getPosition();
		return V;
	}

	fk_Vector^ fk_MatrixAdmin::getVec(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getVec();
		return V;
	}

	fk_Vector^ fk_MatrixAdmin::getUpvec(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getUpvec();
		return V;
	}

	fk_Angle^ fk_MatrixAdmin::getAngle(void)
	{
		fk_Angle^ A = gcnew fk_Angle();
		*A->pAngle = GetP()->getAngle();
		return A;
	}

	fk_Matrix^ fk_MatrixAdmin::getMatrix(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getMatrix();
		return M;
	}

	fk_Matrix^ fk_MatrixAdmin::getInvMatrix(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInvMatrix();
		return M;
	}

	fk_Matrix^ fk_MatrixAdmin::getBaseMatrix(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getBaseMatrix();
		return M;
	}

	fk_Matrix^ fk_MatrixAdmin::getInvBaseMatrix(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInvBaseMatrix();
		return M;
	}

	bool fk_MatrixAdmin::setScale(double argScale)
	{
		return GetP()->setScale(argScale);
	}

	bool fk_MatrixAdmin::setScale(double argScale, fk_Axis argAxis)
	{
		return GetP()->setScale(argScale, fk_Vector::GetAxis(argAxis));
	}

	bool fk_MatrixAdmin::setScale(double argX, double argY, double argZ)
	{
		return GetP()->setScale(argX, argY, argZ);
	}
	bool fk_MatrixAdmin::prdScale(double argScale)
	{
		return GetP()->prdScale(argScale);
	}

	bool fk_MatrixAdmin::prdScale(double argScale, fk_Axis argAxis)
	{
		return GetP()->prdScale(argScale, fk_Vector::GetAxis(argAxis));
	}

	bool fk_MatrixAdmin::prdScale(double argX, double argY, double argZ)
	{
		return GetP()->prdScale(argX, argY, argZ);
	}

	double fk_MatrixAdmin::getScale(void)
	{
		return GetP()->getScale();
	}

	double fk_MatrixAdmin::getScale(fk_Axis argAxis)
	{
		return GetP()->getScale(fk_Vector::GetAxis(argAxis));
	}

	bool fk_MatrixAdmin::getScaleMode(void)
	{
		return GetP()->getScaleMode();
	}

	bool fk_MatrixAdmin::glFocus(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glFocus(*argV->pVec);
	}

	bool fk_MatrixAdmin::glFocus(double argX, double argY, double argZ)
	{
		return GetP()->glFocus(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::loFocus(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->loFocus(*argV->pVec);
	}

	bool fk_MatrixAdmin::loFocus(double argX, double argY, double argZ)
	{
		return GetP()->loFocus(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::glVec(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glVec(*argV->pVec);
	}

	bool fk_MatrixAdmin::glVec(double argX, double argY, double argZ)
	{
		return GetP()->glVec(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::glUpvec(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glUpvec(*argV->pVec);
	}

	bool fk_MatrixAdmin::glUpvec(double argX, double argY, double argZ)
	{
		return GetP()->glUpvec(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::loUpvec(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->loUpvec(*argV->pVec);
	}

	bool fk_MatrixAdmin::loUpvec(double argX, double argY, double argZ)
	{
		return GetP()->loUpvec(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::glAngle(fk_Angle^ argAngle)
	{
		if(!argAngle) return false;
		return GetP()->glAngle(*argAngle->pAngle);
	}

	bool fk_MatrixAdmin::glAngle(double argH, double argP, double argB)
	{
		return GetP()->glAngle(argH, argP, argB);
	}

	bool fk_MatrixAdmin::loAngle(fk_Angle^ argAngle)
	{
		if(!argAngle) return false;
		return GetP()->loAngle(*argAngle->pAngle);
	}

	bool fk_MatrixAdmin::loAngle(double argH, double argP, double argB)
	{
		return GetP()->loAngle(argH, argP, argB);
	}
}
