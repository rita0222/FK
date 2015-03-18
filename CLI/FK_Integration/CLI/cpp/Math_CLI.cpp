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
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector C(argC->x_, argC->y_, argC->z_);
		::fk_Vector D(argD->x_, argD->y_, argD->z_);
		return ::fk_Math::isCrossLineSegment(A, B, C, D, argFlg);
	}
	
	bool fk_Math::IsCrossLineSegment(fk_Vector^ argA, fk_Vector^ argB,
									 fk_Vector^ argC, fk_Vector^ argD)
	{
		if(!argA || !argB || !argC || !argD) return false;
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector C(argC->x_, argC->y_, argC->z_);
		::fk_Vector D(argD->x_, argD->y_, argD->z_);
		return ::fk_Math::isCrossLineSegment(A, B, C, D);

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

		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector C(argC->x_, argC->y_, argC->z_);
		::fk_Vector D(argD->x_, argD->y_, argD->z_);

		::fk_Vector P, Q;

		ret = ::fk_Math::calcClosestPtSegToSeg(A, B, C, D, &s, &t, &P, &Q);
		argS = s;
		argT = t;
		argP->x_ = P.x; argP->y_ = P.y; argP->z_ = P.z;
		argQ->x_ = Q.x; argQ->y_ = Q.y; argQ->z_ = Q.z;
		return ret;
	}

	void fk_Math::CalcClosestPtPtToSeg(fk_Vector^ argC, fk_Vector^ argA, fk_Vector^ argB,
									   double %argT, fk_Vector^ argP)
	{
		if(!argC || !argA || !argB) return;
		if(!argP) argP = gcnew fk_Vector();
		double t;
		::fk_Vector C(argC->x_, argC->y_, argC->z_);
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector P;

		::fk_Math::calcClosestPtPtToSeg(C, A, B, &t, &P);

		argP->x_ = P.x; argP->y_ = P.y; argP->z_ = P.z;
		argT = t;
	}
	
	bool fk_Math::CalcCrossLineAndTri(fk_Vector^ argP, fk_Vector^ argQ,
									  fk_Vector^ argA, fk_Vector^ argB,
									  fk_Vector^ argC, fk_Vector^ argR)
	{
		if(!argP || !argQ || !argA || !argB || !argC) return false;
		if(!argR) argR = gcnew fk_Vector();

		::fk_Vector P(argP->x_, argP->y_, argP->z_);
		::fk_Vector Q(argQ->x_, argQ->y_, argQ->z_);
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector C(argC->x_, argC->y_, argC->z_);
		::fk_Vector R;

		return ::fk_Math::calcCrossLineAndTri(P, Q, A, B, C, &R);
		argR->x_ = R.x; argR->y_ = R.y; argR->z_ = R.z;
	}
	
	bool fk_Math::CalcCrossLineAndTri(fk_Vector^ argP, fk_Vector^ argQ,
									  fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argC)
	{
		if(!argP || !argQ || !argA || !argB || !argC) return false;

		::fk_Vector P(argP->x_, argP->y_, argP->z_);
		::fk_Vector Q(argQ->x_, argQ->y_, argQ->z_);
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector C(argC->x_, argC->y_, argC->z_);

		return ::fk_Math::calcCrossLineAndTri(P, Q, A, B, C);
	}		

	double fk_Math::CalcCosine(fk_Vector^ argA, fk_Vector^ argB)
	{
		if(!argA || !argB) return 0.0;
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);

		return ::fk_Math::calcCosine(A, B);
	}
	
	fk_Vector^ fk_Math::DivideVec(fk_Vector^ argV, fk_Vector^ argA,
								  fk_Vector^ argB, fk_Vector^ argC)
	{
		if(!argV || !argA || !argB || !argC) return nullptr;

		::fk_Vector V(argV->x_, argV->y_, argV->z_);
		::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::fk_Vector B(argB->x_, argB->y_, argB->z_);
		::fk_Vector C(argC->x_, argC->y_, argC->z_);
		::fk_Vector R_;

		R_ = ::fk_Math::divideVec(V, A, B, C);
		fk_Vector^ R = gcnew fk_Vector(R_.x, R_.y, R_.z);
		return R;
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

