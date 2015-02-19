#include "Boundary_CLI.h"

namespace FK_CLI {
	
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
		GetP()->setCapsule(*argS->pVec, *argE->pVec, argR);
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
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getCapsuleStartPos();
		return V;
	}

	fk_Vector^ fk_Boundary::GetCapsuleEndPos(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = GetP()->getCapsuleEndPos();
		return V;
	}
}
