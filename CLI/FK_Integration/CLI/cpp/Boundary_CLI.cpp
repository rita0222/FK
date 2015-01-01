#include "Boundary_CLI.h"

namespace FK_CLI {

	void fk_Boundary::setBMode(fk_BoundaryMode argMode)
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

	fk_BoundaryMode fk_Boundary::getBMode(void)
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

	void fk_Boundary::setSphere(double argR)
	{
		GetP()->setSphere(argR);
	}

	double fk_Boundary::getSphere(void)
	{
		return GetP()->getSphere();
	}

	void fk_Boundary::setAABBSize(double argX, double argY, double argZ)
	{
		GetP()->setAABBSize(argX, argY, argZ);
	}

	void fk_Boundary::setAABBSize(fk_Vector^ argSize)
	{
		GetP()->setAABBSize(*argSize->pVec);
	}

	fk_Vector^ fk_Boundary::getAABBSize(void)
	{
		return gcnew fk_Vector(GetP()->getAABBSize());
	}

	void fk_Boundary::setOBBSize(double argX, double argY, double argZ)
	{
		GetP()->setOBBSize(argX, argY, argZ);
	}

	void fk_Boundary::setOBBSize(fk_Vector^ argSize)
	{
		GetP()->setOBBSize(*argSize->pVec);
	}

	fk_Vector^ fk_Boundary::getOBBSize(void)
	{
		return gcnew fk_Vector(GetP()->getOBBSize());
	}

	void fk_Boundary::setCapsule(fk_Vector^ argS, fk_Vector^ argE, double argR)
	{
		if(!argS || !argE) return;
		GetP()->setCapsule(*argS->pVec, *argE->pVec, argR);
	}

	double fk_Boundary::getCapsuleRadius(void)
	{
		return GetP()->getCapsuleRadius();
	}

	double fk_Boundary::getCapsuleLength(void)
	{
		return GetP()->getCapsuleLength();
	}

	fk_Vector^ fk_Boundary::getCapsuleStartPos(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getCapsuleStartPos();
		return V;
	}

	fk_Vector^ fk_Boundary::getCapsuleEndPos(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getCapsuleEndPos();
		return V;
	}

	void fk_Boundary::setBDrawToggle(bool argMode)
	{
		GetP()->setBDrawToggle(argMode);
	}

	bool fk_Boundary::getBDrawToggle(void)
	{
		return GetP()->getBDrawToggle();
	}

	void fk_Boundary::setBLineColor(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setBLineColor(*argC->pCol);
	}

	fk_Color^ fk_Boundary::getBLineColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getBLineColor();
		return C;
	}

	void fk_Boundary::setBIntLineColor(fk_Color^ argC)
	{
		GetP()->setBIntLineColor(*argC->pCol);
	}

	fk_Color^ fk_Boundary::getBIntLineColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getBIntLineColor();
		return C;
	}

	void fk_Boundary::setBLineWidth(double argWidth)
	{
		GetP()->setBLineWidth(argWidth);
	}

	double fk_Boundary::getBLineWidth(void)
	{
		return GetP()->getBLineWidth();
	}
}
