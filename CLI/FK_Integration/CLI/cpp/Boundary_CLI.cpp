#include "Boundary_CLI.h"

namespace FK_CLI {

	::fk_Boundary * fk_Boundary::GetP(void)
	{
		return (::fk_Boundary *)(pBase);
	}

	fk_Boundary::fk_Boundary(bool argNewFlg) : fk_MatrixAdmin(false)
	{
	}

	fk_Boundary::~fk_Boundary()
	{
		this->!fk_Boundary();
	}

	fk_Boundary::!fk_Boundary()
	{
	}
		
	fk_BoundaryMode fk_Boundary::BMode::get()
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

	void fk_Boundary::BMode::set(fk_BoundaryMode argMode)
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

	double fk_Boundary::SphereRadius::get()
	{
		return GetP()->getSphere();
	}

	void fk_Boundary::SphereRadius::set(double argRad)
	{
		GetP()->setSphere(argRad);
	}



	fk_Vector^ fk_Boundary::AABB::get()
	{
		return gcnew fk_Vector(GetP()->getAABBSize());
	}

	void fk_Boundary::AABB::set(fk_Vector^ argSize)
	{
		if(!argSize) return;
		GetP()->setAABBSize(argSize);
	}

	fk_Vector^ fk_Boundary::OBB::get()
	{
		return gcnew fk_Vector(GetP()->getOBBSize());
	}

	void fk_Boundary::OBB::set(fk_Vector^ argSize)
	{
		if(!argSize) return;
		GetP()->setOBBSize(argSize);
	}

	bool fk_Boundary::BDraw::get()
	{
		return GetP()->getBDrawToggle();
	}

	void fk_Boundary::BDraw::set(bool argMode)
	{
		GetP()->setBDrawToggle(argMode);
	}

	fk_Color^ fk_Boundary::BLineColor::get()
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getBLineColor();
		return C;
	}

	void fk_Boundary::BLineColor::set(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setBLineColor(*argC->pCol);
	}

	fk_Color^ fk_Boundary::BIntLineColor::get()
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getBIntLineColor();
		return C;
	}

	void fk_Boundary::BIntLineColor::set(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setBIntLineColor(*argC->pCol);
	}

	double fk_Boundary::BLineWidth::get()
	{
		return GetP()->getBLineWidth();
	}

	void fk_Boundary::BLineWidth::set(double argW)
	{
		GetP()->setBLineWidth(argW);
	}
	
	void fk_Boundary::SetAABBSize(double argX, double argY, double argZ)
	{
		GetP()->setAABBSize(argX, argY, argZ);
	}

	void fk_Boundary::SetOBBSize(double argX, double argY, double argZ)
	{
		GetP()->setOBBSize(argX, argY, argZ);
	}

	void fk_Boundary::SetCapsule(fk_Vector^ argS, fk_Vector^ argE, double argR)
	{
		if(!argS || !argE) return;
		GetP()->setCapsule(argS, argE, argR);
	}

	double fk_Boundary::GetCapsuleRadius(void)
	{
		return GetP()->getCapsuleRadius();
	}

	double fk_Boundary::GetCapsuleLength(void)
	{
		return GetP()->getCapsuleLength();
	}

	fk_Vector^ fk_Boundary::GetCapsuleStartPos(void)
	{
		fk_Vector^ V = gcnew fk_Vector(GetP()->getCapsuleStartPos());
		return V;
	}

	fk_Vector^ fk_Boundary::GetCapsuleEndPos(void)
	{
		fk_Vector^ V = gcnew fk_Vector(GetP()->getCapsuleEndPos());
		return V;
	}
}
