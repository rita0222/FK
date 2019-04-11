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
#include "Boundary_CLI.h"

namespace FK_CLI {

	::FK::fk_Model * fk_Boundary::GetP(void)
	{
		return (::FK::fk_Model *)(pBase);
	}

	fk_Boundary::fk_Boundary(bool argNewFlg) : fk_MatrixAdmin(false)
	{
	}

	fk_Boundary::~fk_Boundary()
	{
	}
		
	fk_BoundaryMode fk_Boundary::BMode::get()
	{
		switch(GetP()->getBMode()) {
		case ::FK::FK_B_SPHERE:
			return FK_CLI::fk_BoundaryMode::SPHERE;

		case ::FK::FK_B_AABB:
			return FK_CLI::fk_BoundaryMode::AABB;

		case ::FK::FK_B_OBB:
			return FK_CLI::fk_BoundaryMode::OBB;

		case ::FK::FK_B_CAPSULE:
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
			GetP()->setBMode(::FK::FK_B_SPHERE);
			break;

		  case FK_CLI::fk_BoundaryMode::AABB:
			GetP()->setBMode(::FK::FK_B_AABB);
			break;

		  case FK_CLI::fk_BoundaryMode::OBB:
			GetP()->setBMode(::FK::FK_B_OBB);
			break;

		  case FK_CLI::fk_BoundaryMode::CAPSULE:
			GetP()->setBMode(::FK::FK_B_CAPSULE);
			break;

		  case FK_CLI::fk_BoundaryMode::NONE:
			GetP()->setBMode(::FK::FK_B_NONE);
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
	
	void fk_Boundary::SetCapsule(fk_Vector^ argS, fk_Vector^ argE, double argR)
	{
		if(!argS || !argE) return;

		::FK::fk_Vector S(argS->x_, argS->y_, argS->z_);
		::FK::fk_Vector E(argE->x_, argE->y_, argE->z_);

		GetP()->setCapsule(S, E, argR);
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


