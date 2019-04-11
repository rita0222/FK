﻿/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
#include "Math_CLI.h"

namespace FK_CLI {
	
	using namespace std;

	double fk_Math::Clamp(double argA, double argMin, double argMax)
	{
		return ::FK::fk_Math::clamp(argA, argMin, argMax);
	}
	
	bool fk_Math::IsOnLine(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argP)
	{
		if(!argA || !argB || !argP) return false;
		return ::FK::fk_Math::isOnLine(argA, argB, argP);
	}

	bool fk_Math::IsOnLineSegment(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argP, bool openFlg)
	{
		if(!argA || !argB || !argP) return false;
		return ::FK::fk_Math::isOnLineSegment(argA, argB, argP, openFlg);
	}

	bool fk_Math::IsOnLineSegment(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argP)
	{
		if(!argA || !argB || !argP) return false;
		return ::FK::fk_Math::isOnLineSegment(argA, argB, argP);
	}

	bool fk_Math::IsCrossLine(fk_Vector^ argA, fk_Vector^ argB,
							  fk_Vector^ argC, fk_Vector^ argD)
	{
		if(!argA || !argB || !argC || !argD) return false;
		return ::FK::fk_Math::isCrossLine(argA, argB, argC, argD);
	}

	bool fk_Math::IsCrossLineSegment(fk_Vector^ argA, fk_Vector^ argB,
									 fk_Vector^ argC, fk_Vector^ argD, bool argFlg)
	{
		if(!argA || !argB || !argC || !argD) return false;
		return ::FK::fk_Math::isCrossLineSegment(argA, argB, argC, argD, argFlg);
	}
	
	bool fk_Math::IsCrossLineSegment(fk_Vector^ argA, fk_Vector^ argB,
									 fk_Vector^ argC, fk_Vector^ argD)
	{
		if(!argA || !argB || !argC || !argD) return false;
		return ::FK::fk_Math::isCrossLineSegment(argA, argB, argC, argD);

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

		::FK::fk_Vector P, Q;

		ret = ::FK::fk_Math::calcClosestPtSegToSeg(argA, argB, argC, argD, &s, &t, &P, &Q);
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
		::FK::fk_Vector P;

		::FK::fk_Math::calcClosestPtPtToSeg(argC, argA, argB, &t, &P);

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

		::FK::fk_Vector R;

		bool retVal = ::FK::fk_Math::calcCrossLineAndTri(argP, argQ, argA, argB, argC, &R);
		argR->Set(R.x, R.y, R.z);
		return retVal;
	}
	
	bool fk_Math::CalcCrossLineAndTri(fk_Vector^ argP, fk_Vector^ argQ,
									  fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argC)
	{
		if(!argP || !argQ || !argA || !argB || !argC) return false;

		return ::FK::fk_Math::calcCrossLineAndTri(argP, argQ, argA, argB, argC);
	}		

	double fk_Math::CalcCosine(fk_Vector^ argA, fk_Vector^ argB)
	{
		if(!argA || !argB) return 0.0;
		::FK::fk_Vector A(argA->x_, argA->y_, argA->z_);
		::FK::fk_Vector B(argB->x_, argB->y_, argB->z_);

		return ::FK::fk_Math::calcCosine(A, B);
	}
	
	fk_Vector^ fk_Math::DivideVec(fk_Vector^ argV, fk_Vector^ argA,
								  fk_Vector^ argB, fk_Vector^ argC)
	{
		if(!argV || !argA || !argB || !argC) return nullptr;
		::FK::fk_Vector R_;

		R_ = ::FK::fk_Math::divideVec(argV, argA, argB, argC);
		return gcnew fk_Vector(R_);
	}
	
	fk_Quaternion^ fk_Math::QuatInterLinear(fk_Quaternion^ argQ1,
											fk_Quaternion^ argQ2, double argT)
	{
		if(!argQ1 || !argQ2) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = ::FK::fk_Math::quatInterLinear(*argQ1->pQuat, *argQ2->pQuat, argT);
		return Q;
	}
	fk_Quaternion^ fk_Math::QuatInterSphere(fk_Quaternion^ argQ1,
											fk_Quaternion^ argQ2, double argT)
	{
		if(!argQ1 || !argQ2) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = ::FK::fk_Math::quatInterSphere(*argQ1->pQuat, *argQ2->pQuat, argT);
		return Q;
	}
}


