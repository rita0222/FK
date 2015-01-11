// Math_CLI.h

#pragma once

#include <FK/Math.h>
#include "Quaternion_CLI.h"

namespace FK_CLI
{
	using namespace System;
	public ref class fk_Math {
	public:
		static double clamp(double a, double min, double max);
		static bool isOnLine(fk_Vector^ A, fk_Vector^ B, fk_Vector^ P);
		static bool isOnLineSegment(fk_Vector^ A, fk_Vector^ B, fk_Vector^ P, bool openFlg);
		static bool isOnLineSegment(fk_Vector^ A, fk_Vector^ B, fk_Vector^ P);
		static bool isCrossLine(fk_Vector^ A, fk_Vector^ B, fk_Vector^ C, fk_Vector^ D);
		static bool isCrossLineSegment(fk_Vector^ A, fk_Vector^ B,
									   fk_Vector^ C, fk_Vector^ D, bool openFlg);
		static bool isCrossLineSegment(fk_Vector^ A, fk_Vector^ B, fk_Vector^ C, fk_Vector^ D);
		static double calcClosestPtSegToSeg(fk_Vector^ A, fk_Vector^ B, fk_Vector^ C, fk_Vector^ D,
											double %s, double %t, fk_Vector^ P, fk_Vector^ Q);
		static void calcClosestPtPtToSeg(fk_Vector^ C, fk_Vector^ A, fk_Vector^ B,
										 double %t, fk_Vector^ P);
		static bool calcCrossLineAndTri(fk_Vector^ P, fk_Vector^ Q, fk_Vector^ A, fk_Vector^ B,
										fk_Vector^ C, fk_Vector^ R);
		static bool calcCrossLineAndTri(fk_Vector^ P, fk_Vector^ Q,
										fk_Vector^ A, fk_Vector^ B, fk_Vector^ C);
		static double calcCosine(fk_Vector^ A, fk_Vector^ B);
		static fk_Vector^ divideVec(fk_Vector^ V, fk_Vector^ A, fk_Vector^ B, fk_Vector^ C);
		static fk_Quaternion^ quatInterLinear(fk_Quaternion^ Q1, fk_Quaternion^ Q2, double t);
		static fk_Quaternion^ quatInterSphere(fk_Quaternion^ Q1, fk_Quaternion^ Q2, double t);
	};
}
