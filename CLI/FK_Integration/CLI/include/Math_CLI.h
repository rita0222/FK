// Math_CLI.h

#pragma once

#include <FK/Math.h>
#include "Quaternion_CLI.h"

namespace FK_CLI
{
	using namespace System;
	public ref class fk_Math {
	public:
		static double Clamp(double a, double min, double max);
		static bool IsOnLine(fk_Vector^ A, fk_Vector^ B, fk_Vector^ P);
		static bool IsOnLineSegment(fk_Vector^ A, fk_Vector^ B, fk_Vector^ P, bool openFlg);
		static bool IsOnLineSegment(fk_Vector^ A, fk_Vector^ B, fk_Vector^ P);
		static bool IsCrossLine(fk_Vector^ A, fk_Vector^ B, fk_Vector^ C, fk_Vector^ D);
		static bool IsCrossLineSegment(fk_Vector^ A, fk_Vector^ B,
									   fk_Vector^ C, fk_Vector^ D, bool openFlg);
		static bool IsCrossLineSegment(fk_Vector^ A, fk_Vector^ B, fk_Vector^ C, fk_Vector^ D);
		static double CalcClosestPtSegToSeg(fk_Vector^ A, fk_Vector^ B, fk_Vector^ C, fk_Vector^ D,
											double %s, double %t, fk_Vector^ P, fk_Vector^ Q);
		static void CalcClosestPtPtToSeg(fk_Vector^ C, fk_Vector^ A, fk_Vector^ B,
										 double %t, fk_Vector^ P);
		static bool CalcCrossLineAndTri(fk_Vector^ P, fk_Vector^ Q, fk_Vector^ A, fk_Vector^ B,
										fk_Vector^ C, fk_Vector^ R);
		static bool CalcCrossLineAndTri(fk_Vector^ P, fk_Vector^ Q,
										fk_Vector^ A, fk_Vector^ B, fk_Vector^ C);
		static double CalcCosine(fk_Vector^ A, fk_Vector^ B);
		static fk_Vector^ DivideVec(fk_Vector^ V, fk_Vector^ A, fk_Vector^ B, fk_Vector^ C);
		static fk_Quaternion^ QuatInterLinear(fk_Quaternion^ Q1, fk_Quaternion^ Q2, double t);
		static fk_Quaternion^ QuatInterSphere(fk_Quaternion^ Q1, fk_Quaternion^ Q2, double t);
	};
}
