#include "Model_CLI.h"

namespace FK_CLI {

	::fk_MatrixAdmin * fk_MatrixAdmin::GetP(void)
	{
		return (::fk_MatrixAdmin *)(pBase);
	}

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

	fk_Vector^ fk_MatrixAdmin::Position::get(void)
	{
		return gcnew fk_Vector(GetP()->getPosition());
	}

	fk_Vector^ fk_MatrixAdmin::Vec::get(void)
	{
		return gcnew fk_Vector(GetP()->getVec());
	}

	fk_Vector^ fk_MatrixAdmin::Upvec::get(void)
	{
		return gcnew fk_Vector(GetP()->getUpvec());
	}

	fk_Angle^ fk_MatrixAdmin::Angle::get(void)
	{
		fk_Angle^ A = gcnew fk_Angle();
		*A->pAngle = GetP()->getAngle();
		return A;
	}

	fk_Matrix^ fk_MatrixAdmin::Matrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getMatrix();
		return M;
	}

	fk_Matrix^ fk_MatrixAdmin::InvMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInvMatrix();
		return M;
	}

	fk_Matrix^ fk_MatrixAdmin::BaseMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getBaseMatrix();
		return M;
	}

	fk_Matrix^ fk_MatrixAdmin::InvBaseMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInvBaseMatrix();
		return M;
	}

	bool fk_MatrixAdmin::ScaleMode::get(void)
	{
		return GetP()->getScaleMode();
	}

	void fk_MatrixAdmin::Scale::set(double argScale)
	{
		GetP()->setScale(argScale);
	}

	double fk_MatrixAdmin::Scale::get(void)
	{
		return GetP()->getScale();
	}

	bool fk_MatrixAdmin::SetScale(double argScale, fk_Axis argAxis)
	{
		return GetP()->setScale(argScale, fk_Vector::GetAxis(argAxis));
	}

	bool fk_MatrixAdmin::SetScale(double argX, double argY, double argZ)
	{
		return GetP()->setScale(argX, argY, argZ);
	}
	bool fk_MatrixAdmin::PrdScale(double argScale)
	{
		return GetP()->prdScale(argScale);
	}

	bool fk_MatrixAdmin::PrdScale(double argScale, fk_Axis argAxis)
	{
		return GetP()->prdScale(argScale, fk_Vector::GetAxis(argAxis));
	}

	bool fk_MatrixAdmin::PrdScale(double argX, double argY, double argZ)
	{
		return GetP()->prdScale(argX, argY, argZ);
	}

	double fk_MatrixAdmin::GetScale(fk_Axis argAxis)
	{
		return GetP()->getScale(fk_Vector::GetAxis(argAxis));
	}

	bool fk_MatrixAdmin::GlFocus(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glFocus(argV->x_, argV->y_, argV->z_);
	}

	bool fk_MatrixAdmin::GlFocus(double argX, double argY, double argZ)
	{
		return GetP()->glFocus(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::LoFocus(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->loFocus(argV->x_, argV->y_, argV->z_);
	}

	bool fk_MatrixAdmin::LoFocus(double argX, double argY, double argZ)
	{
		return GetP()->loFocus(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::GlVec(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glVec(argV->x_, argV->y_, argV->z_);
	}

	bool fk_MatrixAdmin::GlVec(double argX, double argY, double argZ)
	{
		return GetP()->glVec(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::GlUpvec(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glUpvec(argV->x_, argV->y_, argV->z_);
	}

	bool fk_MatrixAdmin::GlUpvec(double argX, double argY, double argZ)
	{
		return GetP()->glUpvec(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::LoUpvec(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->loUpvec(argV->x_, argV->y_, argV->z_);
	}

	bool fk_MatrixAdmin::LoUpvec(double argX, double argY, double argZ)
	{
		return GetP()->loUpvec(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::GlAngle(fk_Angle^ argAngle)
	{
		if(!argAngle) return false;
		return GetP()->glAngle(*argAngle->pAngle);
	}

	bool fk_MatrixAdmin::GlAngle(double argH, double argP, double argB)
	{
		return GetP()->glAngle(argH, argP, argB);
	}

	bool fk_MatrixAdmin::LoAngle(fk_Angle^ argAngle)
	{
		if(!argAngle) return false;
		return GetP()->loAngle(*argAngle->pAngle);
	}

	bool fk_MatrixAdmin::LoAngle(double argH, double argP, double argB)
	{
		return GetP()->loAngle(argH, argP, argB);
	}
}
