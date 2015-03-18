#include "Math_CLI.h"

namespace FK_CLI {
	
	using namespace std;

	double fk_Math::Clamp(double argA, double argMin, double argMax)
	{
		return ::fk_Math::clamp(argA, argMin, argMax);
	}
	
	bool fk_Math::IsOnLine(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argP)
	{
		if(!argA || !argB || !argP) return false;
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector P(argP->x_, argP->y_, argP->z_);
		return ::fk_Math::isOnLine(A, B, P);
	}

	bool fk_Math::IsOnLineSegment(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argP, bool openFlg)
	{
		if(!argA || !argB || !argP) return false;
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector P(argP->x_, argP->y_, argP->z_);
		return ::fk_Math::isOnLineSegment(A, B, P, openFlg);
	}

	bool fk_Math::IsOnLineSegment(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argP)
	{
		if(!argA || !argB || !argP) return false;
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector P(argP->x_, argP->y_, argP->z_);
		return ::fk_Math::isOnLineSegment(A, B, P);
	}

	bool fk_Math::IsCrossLine(fk_Vector^ argA, fk_Vector^ argB,
							  fk_Vector^ argC, fk_Vector^ argD)
	{
		if(!argA || !argB || !argC || !argD) return false;
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector C(argC->x_, argC->y_, argC->z_);
		::fk_Vector D(argD->x_, argD->y_, argD->z_);
		return ::fk_Math::isCrossLine(A, B, C, D);
	}

	bool fk_Math::IsCrossLineSegment(fk_Vector^ argA, fk_Vector^ argB,
									 fk_Vector^ argC, fk_Vector^ argD, bool argFlg)
	{
		if(!argA || !argB || !argC || !argD) return false;
		return ::fk_Math::isCrossLineSegment(*argA->pVec, *argB->pVec,
											 *argC->pVec, *argD->pVec, argFlg);
	}
	
	bool fk_Math::IsCrossLineSegment(fk_Vector^ argA, fk_Vector^ argB,
									 fk_Vector^ argC, fk_Vector^ argD)
	{
		if(!argA || !argB || !argC || !argD) return false;
		return ::fk_Math::isCrossLineSegment(*argA->pVec, *argB->pVec,
											 *argC->pVec, *argD->pVec);
	}

	double fk_Math::CalcClosestPtSegToSeg(fk_Vector^ argA, fk_Vector^ argB,
										  fk_Vector^ argC, fk_Vector^ argD,
										  double %argS, double %argT,
										  fk_Vector^ argP, fk_Vector^ argQ)
	{
		if(!argA || !argB || !argC || !argD) return 0.0;
		if(!argP) argP = gcnew fk_Vector();
		if(!argQ) argQ = gcnew fk_Vector();
		double s, t, ret;
		ret = ::fk_Math::calcClosestPtSegToSeg(*argA->pVec, *argB->pVec,
											   *argC->pVec, *argD->pVec,
											   &s, &t, argP->pVec, argQ->pVec);
		argS = s;
		argT = t;
		return ret;
	}

	void fk_Math::CalcClosestPtPtToSeg(fk_Vector^ argC, fk_Vector^ argA, fk_Vector^ argB,
									   double %argT, fk_Vector^ argP)
	{
		if(!argC || !argA || !argB) return;
		if(!argP) argP = gcnew fk_Vector();
		double t;
		::fk_Math::calcClosestPtPtToSeg(*argC->pVec, *argA->pVec, *argB->pVec, &t, argP->pVec);
		argT = t;
	}
	
	bool fk_Math::CalcCrossLineAndTri(fk_Vector^ argP, fk_Vector^ argQ,
									  fk_Vector^ argA, fk_Vector^ argB,
									  fk_Vector^ argC, fk_Vector^ argR)
	{
		if(!argP || !argQ || !argA || !argB || !argC) return false;
		if(!argR) argR = gcnew fk_Vector();
		return ::fk_Math::calcCrossLineAndTri(*argP->pVec, *argQ->pVec,
											  *argA->pVec, *argB->pVec,
											  *argC->pVec, argR->pVec);
	}
	
	bool fk_Math::CalcCrossLineAndTri(fk_Vector^ argP, fk_Vector^ argQ,
									  fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argC)
	{
		if(!argP || !argQ || !argA || !argB || !argC) return false;
		return ::fk_Math::calcCrossLineAndTri(*argP->pVec, *argQ->pVec,
											  *argA->pVec, *argB->pVec, *argC->pVec);
	}		

	double fk_Math::CalcCosine(fk_Vector^ argA, fk_Vector^ argB)
	{
		if(!argA || !argB) return 0.0;
		return ::fk_Math::calcCosine(*argA->pVec, *argB->pVec);
	}
	
	fk_Vector^ fk_Math::DivideVec(fk_Vector^ argV, fk_Vector^ argA,
								  fk_Vector^ argB, fk_Vector^ argC)
	{
		if(!argV || !argA || !argB || !argC) return nullptr;
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = ::fk_Math::divideVec(*argV->pVec, *argA->pVec, *argB->pVec, *argC->pVec);
		return V;
	}
	
	fk_Quaternion^ fk_Math::QuatInterLinear(fk_Quaternion^ argQ1,
											fk_Quaternion^ argQ2, double argT)
	{
		if(!argQ1 || !argQ2) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = ::fk_Math::quatInterLinear(*argQ1->pQuat, *argQ2->pQuat, argT);
		return Q;
	}
	fk_Quaternion^ fk_Math::QuatInterSphere(fk_Quaternion^ argQ1,
											fk_Quaternion^ argQ2, double argT)
	{
		if(!argQ1 || !argQ2) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = ::fk_Math::quatInterSphere(*argQ1->pQuat, *argQ2->pQuat, argT);
		return Q;
	}
}

