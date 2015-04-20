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
		return ::fk_Math::isOnLine(argA, argB, argP);
	}

	bool fk_Math::IsOnLineSegment(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argP, bool openFlg)
	{
		if(!argA || !argB || !argP) return false;
		return ::fk_Math::isOnLineSegment(argA, argB, argP, openFlg);
	}

	bool fk_Math::IsOnLineSegment(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argP)
	{
		if(!argA || !argB || !argP) return false;
		return ::fk_Math::isOnLineSegment(argA, argB, argP);
	}

	bool fk_Math::IsCrossLine(fk_Vector^ argA, fk_Vector^ argB,
							  fk_Vector^ argC, fk_Vector^ argD)
	{
		if(!argA || !argB || !argC || !argD) return false;
		return ::fk_Math::isCrossLine(argA, argB, argC, argD);
	}

	bool fk_Math::IsCrossLineSegment(fk_Vector^ argA, fk_Vector^ argB,
									 fk_Vector^ argC, fk_Vector^ argD, bool argFlg)
	{
		if(!argA || !argB || !argC || !argD) return false;
		return ::fk_Math::isCrossLineSegment(argA, argB, argC, argD, argFlg);
	}
	
	bool fk_Math::IsCrossLineSegment(fk_Vector^ argA, fk_Vector^ argB,
									 fk_Vector^ argC, fk_Vector^ argD)
	{
		if(!argA || !argB || !argC || !argD) return false;
		return ::fk_Math::isCrossLineSegment(argA, argB, argC, argD);

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

		::fk_Vector P, Q;

		ret = ::fk_Math::calcClosestPtSegToSeg(argA, argB, argC, argD, &s, &t, &P, &Q);
		argS = s;
		argT = t;
		argP->Set(P.x, P.y, P.z);
		argQ->Set(Q.x, Q.y, Q.z);
		return ret;
	}


	void fk_Math::CalcClosestPtPtToSeg(fk_Vector^ argC, fk_Vector^ argA, fk_Vector^ argB,
									   double %argT, fk_Vector^ argP)
	{
		if(!argC || !argA || !argB) return;
		if(!argP) argP = gcnew fk_Vector();

		double t;
		::fk_Vector P;

		::fk_Math::calcClosestPtPtToSeg(argC, argA, argB, &t, &P);

		argP->Set(P.x, P.y, P.z);
		argT = t;
		return;
	}
	
	bool fk_Math::CalcCrossLineAndTri(fk_Vector^ argP, fk_Vector^ argQ,
									  fk_Vector^ argA, fk_Vector^ argB,
									  fk_Vector^ argC, fk_Vector^ argR)
	{
		if(!argP || !argQ || !argA || !argB || !argC) return false;
		if(!argR) argR = gcnew fk_Vector();

		::fk_Vector R;

		bool retVal = ::fk_Math::calcCrossLineAndTri(argP, argQ, argA, argB, argC, &R);
		argR->Set(R.x, R.y, R.z);
		return retVal;
	}
	
	bool fk_Math::CalcCrossLineAndTri(fk_Vector^ argP, fk_Vector^ argQ,
									  fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argC)
	{
		if(!argP || !argQ || !argA || !argB || !argC) return false;

		return ::fk_Math::calcCrossLineAndTri(argP, argQ, argA, argB, argC);
	}		

	double fk_Math::CalcCosine(fk_Vector^ argA, fk_Vector^ argB)
	{
		if(!argA || !argB) return 0.0;

		return ::fk_Math::calcCosine(argA, argB);
	}
	
	fk_Vector^ fk_Math::DivideVec(fk_Vector^ argV, fk_Vector^ argA,
								  fk_Vector^ argB, fk_Vector^ argC)
	{
		if(!argV || !argA || !argB || !argC) return nullptr;
		::fk_Vector R_;

		R_ = ::fk_Math::divideVec(argV, argA, argB, argC);
		return gcnew fk_Vector(R_);
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

