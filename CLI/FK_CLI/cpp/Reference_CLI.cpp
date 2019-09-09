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
#include "Reference_CLI.h"

namespace FK_CLI {

	using namespace std;

	::FK::fk_ReferenceL3 * fk_Reference::GetP(void)
	{
		return (::FK::fk_ReferenceL3 *)(pBase);
	}

	fk_Reference::fk_Reference(bool argNewFlg) : fk_Shape(false)
	{
	}

	fk_Reference::~fk_Reference()
	{
	}

	fk_Half^ fk_Reference::GetOneHOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getOneHOnV(argV->GetP());
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_Reference::GetOneEOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = GetP()->getOneEOnV(argV->GetP());
		E->dFlg = false;
		return E;
	}

	fk_Vertex^ fk_Reference::GetVOnH(fk_Half^ argH)
	{
		if(!argH) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = GetP()->getVOnH(argH->GetP());
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_Reference::GetMateHOnH(fk_Half^ argH)
	{
		if(!argH) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getMateHOnH(argH->GetP());
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_Reference::GetParentEOnH(fk_Half^ argH)
	{
		if(!argH) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = GetP()->getParentEOnH(argH->GetP());
		E->dFlg = false;
		return E;
	}

	fk_Loop^ fk_Reference::GetParentLOnH(fk_Half^ argH)
	{
		if(!argH) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->getParentLOnH(argH->GetP());
		L->dFlg = false;
		return L;
	}

	fk_Vertex^ fk_Reference::GetRightVOnE(fk_Edge^ argE)
	{
		if(!argE) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = GetP()->getRightVOnE(argE->GetP());
		V->dFlg = false;
		return V;
	}

	fk_Vertex^ fk_Reference::GetLeftVOnE(fk_Edge^ argE)
	{
		if(!argE) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = GetP()->getLeftVOnE(argE->GetP());
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_Reference::GetRightHOnE(fk_Edge^ argE)
	{
		if(!argE) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getRightHOnE(argE->GetP());
		H->dFlg = false;
		return H;
	}

	fk_Half^ fk_Reference::GetLeftHOnE(fk_Edge^ argE)
	{
		if(!argE) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getLeftHOnE(argE->GetP());
		H->dFlg = false;
		return H;
	}

	fk_Loop^ fk_Reference::GetRightLOnE(fk_Edge^ argE)
	{
		if(!argE) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->getRightLOnE(argE->GetP());
		L->dFlg = false;
		return L;

	}

	fk_Loop^ fk_Reference::GetLeftLOnE(fk_Edge^ argE)
	{
		if(!argE) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->getLeftLOnE(argE->GetP());
		L->dFlg = false;
		return L;

	}

	fk_EdgeStatus fk_Reference::GetEdgeStatus(fk_Edge^ argE)
	{
		if(!argE) return fk_EdgeStatus::NONE;
		switch(GetP()->getEdgeStatus(argE->GetP())) {
		case ::FK::fk_EdgeStatus::UNDEF:
			return fk_EdgeStatus::UNDEF;

		case ::FK::fk_EdgeStatus::HALF:
			return fk_EdgeStatus::HALF;

		case ::FK::fk_EdgeStatus::BOTH:
			return fk_EdgeStatus::BOTH;

		  default:
			break;
		}
		return fk_EdgeStatus::NONE;
	}

	fk_Vertex^ fk_Reference::GetOneVOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = GetP()->getOneVOnL(argL->GetP());
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_Reference::GetOneHOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getOneHOnL(argL->GetP());
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_Reference::GetOneEOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = GetP()->getOneEOnL(argL->GetP());
		E->dFlg = false;
		return E;
	}


	// from ReferenceL2
	fk_Vertex^ fk_Reference::GetOneNeighborVOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = GetP()->getOneNeighborVOnV(argV->GetP());
		V->dFlg = false;
		return V;
	}

	cli::array<fk_Half^>^ fk_Reference::GetAllHOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		vector<::FK::fk_Half *> hA = GetP()->getAllHOnV(argV->GetP());
		cli::array<fk_Half^>^ A = gcnew cli::array<fk_Half^>(int(hA.size()));
		for(int i = 0; i < int(hA.size()); ++i) {
			A[i] = gcnew fk_Half(false);
			A[i]->pBase = hA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	cli::array<fk_Edge^>^ fk_Reference::GetAllEOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		vector<::FK::fk_Edge *> eA = GetP()->getAllEOnV(argV->GetP());
		cli::array<fk_Edge^>^ A = gcnew cli::array<fk_Edge^>(int(eA.size()));
		for(int i = 0; i < int(eA.size()); ++i) {
			A[i] = gcnew fk_Edge(false);
			A[i]->pBase = eA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	cli::array<fk_Loop^>^ fk_Reference::GetAllLOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		vector<::FK::fk_Loop *> lA = GetP()->getAllLOnV(argV->GetP());
		cli::array<fk_Loop^>^ A = gcnew cli::array<fk_Loop^>(int(lA.size()));
		for(int i = 0; i < int(lA.size()); ++i) {
			A[i] = gcnew fk_Loop(false);
			A[i]->pBase = lA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	int fk_Reference::GetENumOnV(fk_Vertex^ argV)
	{
		if(!argV) return 0;
		return GetP()->getENumOnV(argV->GetP());
	}

	cli::array<fk_Vertex^>^ fk_Reference::GetAllVOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		vector<::FK::fk_Vertex *> vA = GetP()->getAllVOnL(argL->GetP());
		cli::array<fk_Vertex^>^ A = gcnew cli::array<fk_Vertex^>(int(vA.size()));
		for(int i = 0; i < int(vA.size()); ++i) {
			A[i] = gcnew fk_Vertex(false);
			A[i]->pBase = vA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	cli::array<fk_Half^>^ fk_Reference::GetAllHOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		vector<::FK::fk_Half *> hA = GetP()->getAllHOnL(argL->GetP());
		cli::array<fk_Half^>^ A = gcnew cli::array<fk_Half^>(int(hA.size()));
		for(int i = 0; i < int(hA.size()); ++i) {
			A[i] = gcnew fk_Half(false);
			A[i]->pBase = hA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	cli::array<fk_Edge^>^ fk_Reference::GetAllEOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		vector<::FK::fk_Edge *> eA = GetP()->getAllEOnL(argL->GetP());
		cli::array<fk_Edge^>^ A = gcnew cli::array<fk_Edge^>(int(eA.size()));
		for(int i = 0; i < int(eA.size()); ++i) {
			A[i] = gcnew fk_Edge(false);
			A[i]->pBase = eA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	fk_Loop^ fk_Reference::GetOneNeighborLOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->getOneNeighborLOnL(argL->GetP());
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Reference::GetNeighborLOnLH(fk_Loop^ argL, fk_Half^ argH)
	{
		if(!argL || !argH) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->getNeighborLOnLH(argL->GetP(), argH->GetP());
		L->dFlg = false;
		return L;
	}

	int fk_Reference::GetVNumOnL(fk_Loop^ argL)
	{
		if(!argL) return 0;
		return GetP()->getVNumOnL(argL->GetP());
	}

	// from ReferenceL3
	cli::array<fk_Vertex^>^ fk_Reference::GetAllNeighborVOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		vector<::FK::fk_Vertex *> vA = GetP()->getAllNeighborVOnV(argV->GetP());
		cli::array<fk_Vertex^>^ A = gcnew cli::array<fk_Vertex^>(int(vA.size()));
		for(int i = 0; i < int(vA.size()); ++i) {
			A[i] = gcnew fk_Vertex(false);
			A[i]->pBase = vA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	cli::array<fk_Edge^>^ fk_Reference::GetEOnVV(fk_Vertex^ argV1, fk_Vertex^ argV2)
	{
		if(!argV1 || !argV2) nullptr;
		vector<::FK::fk_Edge *> eA = GetP()->getEOnVV(argV1->GetP(), argV2->GetP());
		cli::array<fk_Edge^>^ A = gcnew cli::array<fk_Edge^>(int(eA.size()));
		for(int i = 0; i < int(eA.size()); ++i) {
			A[i] = gcnew fk_Edge(false);
			A[i]->pBase = eA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	fk_Loop^ fk_Reference::GetOneLOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->getOneLOnV(argV->GetP());
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Reference::GetNeighborLOnLE(fk_Loop^ argL, fk_Edge^ argE)
	{
		if(!argL || !argE) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->getNeighborLOnLE(argL->GetP(), argE->GetP());
		L->dFlg = false;
		return L;
	}

	cli::array<fk_Loop^>^ fk_Reference::GetAllNeighborLOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		vector<::FK::fk_Loop *> lA = GetP()->getAllNeighborLOnL(argL->GetP());
		cli::array<fk_Loop^>^ A = gcnew cli::array<fk_Loop^>(int(lA.size()));
		for(int i = 0; i < int(lA.size()); ++i) {
			A[i] = gcnew fk_Loop(false);
			A[i]->pBase = lA[i];
			A[i]->dFlg = false;
		}
		return A;
	}
}

