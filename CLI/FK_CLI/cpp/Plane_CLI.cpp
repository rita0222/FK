/****************************************************************************
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
#include "Plane_CLI.h"

namespace FK_CLI {

	using namespace std;

	fk_Plane::fk_Plane()
	{
		pPlane = new ::FK::fk_Plane();
	}

	fk_Plane::fk_Plane(fk_Plane^ argP)
	{
		pPlane = new ::FK::fk_Plane(*(argP->pPlane));
	}

	fk_Plane::fk_Plane(::FK::fk_Plane *argP)
	{
		pPlane = new ::FK::fk_Plane();
		*pPlane = *argP;
	}

	fk_Plane::~fk_Plane()
	{
		this->!fk_Plane();
	}

	fk_Plane::!fk_Plane()
	{
		delete pPlane;
	}

	String^ fk_Plane::ToString()
	{
		string	tmpBuf;
		::FK::fk_Vector	base, u, v;

		base = pPlane->getBasePos();
		u = pPlane->getUVec();
		v = pPlane->getVVec();

		tmpBuf = "P: base = (";
		tmpBuf += to_string(base.x) + ", ";
		tmpBuf += to_string(base.y) + ", ";
		tmpBuf += to_string(base.z) + "), u = (";
		tmpBuf += to_string(u.x) + ", ";
		tmpBuf += to_string(u.y) + ", ";
		tmpBuf += to_string(u.z) + "), v = (";
		tmpBuf += to_string(v.x) + ", ";
		tmpBuf += to_string(v.y) + ", ";
		tmpBuf += to_string(v.z) + ")";
		return gcnew String(tmpBuf.c_str());
	}

	fk_Vector^ fk_Plane::BasePos::get()
	{
		return gcnew fk_Vector(pPlane->getBasePos());
	}

	fk_Vector^ fk_Plane::UVec::get()
	{
		return gcnew fk_Vector(pPlane->getUVec());
	}

	fk_Vector^ fk_Plane::VVec::get()
	{
		return gcnew fk_Vector(pPlane->getVVec());
	}

	fk_Vector^ fk_Plane::Normal::get()
	{
		return gcnew fk_Vector(pPlane->getNormal());
	}

	double fk_Plane::Dist::get()
	{
		return pPlane->getDist();
	}

	bool fk_Plane::SetPosNormal(fk_Vector^ argPos, fk_Vector^ argNorm)
	{
		if(!argPos || !argNorm) return false;
		return pPlane->setPosNormal(argPos, argNorm);
	}

	bool fk_Plane::Set3Pos(fk_Vector^ argPos1, fk_Vector^ argPos2, fk_Vector^ argPos3)
	{
		if(!argPos1 || !argPos2 || !argPos3) return false;
		return pPlane->set3Pos(argPos1, argPos2, argPos3);
	}

	bool fk_Plane::SetPosUVVec(fk_Vector ^argPos, fk_Vector ^argU, fk_Vector ^argV)
	{
		if(!argPos || !argU || !argV) return false;
		return pPlane->setPosUVVec(argPos, argU, argV);
	}

	double fk_Plane::GetDist(fk_Vector^ argPos)
	{
		if(!argPos) return pPlane->getDist();
		return pPlane->getDist(argPos);
	}

	fk_Vector^ fk_Plane::GetPos(double argU, double argV)
	{
		return gcnew fk_Vector(pPlane->getPos(argU, argV));
	}

	bool fk_Plane::IsParallel(fk_Vector^ argV)
	{
		if(!argV) return false;
		return pPlane->isParallel(argV);
	}

	bool fk_Plane::IsParallel(fk_Plane^ argP)
	{
		if(!argP) return false;
		return pPlane->isParallel(*(argP->pPlane));
	}

	bool fk_Plane::IsVertical(fk_Vector^ argV)
	{
		if(!argV) return false;
		return pPlane->isVertical(argV);
	}

	bool fk_Plane::IsVertical(fk_Plane^ argP)
	{
		if(!argP) return false;
		return pPlane->isVertical(*(argP->pPlane));
	}

	bool fk_Plane::CalcCrossPos(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argPos)
	{
		if(!argA || !argB || !argPos) return false;
		::FK::fk_Vector	retPos;

		bool ret = pPlane->calcCrossPos(argA, argB, &retPos);
		argPos->Set(retPos.x, retPos.y, retPos.z);
		return ret;
	}

	bool fk_Plane::CalcCrossLineParam(fk_Vector^ argA, fk_Vector^ argB, double %argT)
	{
		if(!argA || !argB) return false;
		bool	ret;
		double	t;
		ret = pPlane->calcCrossLineParam(argA, argB, &t);
		argT = t;
		return ret;
	}

	bool fk_Plane::CalcCrossPlaneParam(fk_Vector^ argA, fk_Vector^ argB,
									   double %argU, double %argV)
	{
		if(!argA || !argB) return false;
		bool	ret;
		double	u, v;

		ret = pPlane->calcCrossPlaneParam(argA, argB, &u, &v);
		argU = u;
		argV = v;
		return ret;
	}

	bool fk_Plane::CalcCrossAll(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argPos,
								double %argT, double %argU, double %argV)
	{
		if(!argA || !argB || !argPos) return false;
		::FK::fk_Vector	retPos;
		bool		ret;
		double		t, u, v;

		ret = pPlane->calcCrossAll(argA, argB, &retPos, &t, &u, &v);
		argPos->Set(retPos.x, retPos.y, retPos.z);
		argT = t;
		argU = u;
		argV = v;
		return ret;
	}
}



