#include "Reference_CLI.h"

namespace FK_CLI {

	using namespace std;

	::fk_ReferenceL3 * fk_Reference::GetP(void)
	{
		return (::fk_ReferenceL3 *)(pBase);
	}

	fk_Reference::fk_Reference(bool argNewFlg) : fk_Shape(false)
	{
	}

	fk_Reference::~fk_Reference()
	{
		this->!fk_Reference();
	}

	fk_Reference::!fk_Reference()
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
		if(!argE) return fk_EdgeStatus::NONE_EDGE;
		switch(GetP()->getEdgeStatus(argE->GetP())) {
		  case FK_UNDEF_EDGE:
			return fk_EdgeStatus::UNDEF_EDGE;

		  case FK_HALFDEF_EDGE:
			return fk_EdgeStatus::HALFDEF_EDGE;

		  case FK_BOTHDEF_EDGE:
			return fk_EdgeStatus::BOTHDEF_EDGE;

		  default:
			break;
		}
		return fk_EdgeStatus::NONE_EDGE;
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

	array<fk_Half^>^ fk_Reference::GetAllHOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		vector<::fk_Half *> hA = GetP()->getAllHOnV(argV->GetP());
		array<fk_Half^>^ A = gcnew array<fk_Half^>(hA.size());
		for(int i = 0; i < int(hA.size()); ++i) {
			A[i] = gcnew fk_Half(false);
			A[i]->pBase = hA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	array<fk_Edge^>^ fk_Reference::GetAllEOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		vector<::fk_Edge *> eA = GetP()->getAllEOnV(argV->GetP());
		array<fk_Edge^>^ A = gcnew array<fk_Edge^>(eA.size());
		for(int i = 0; i < int(eA.size()); ++i) {
			A[i] = gcnew fk_Edge(false);
			A[i]->pBase = eA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	array<fk_Loop^>^ fk_Reference::GetAllLOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		vector<::fk_Loop *> lA = GetP()->getAllLOnV(argV->GetP());
		array<fk_Loop^>^ A = gcnew array<fk_Loop^>(lA.size());
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

	array<fk_Vertex^>^ fk_Reference::GetAllVOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		vector<::fk_Vertex *> vA = GetP()->getAllVOnL(argL->GetP());
		array<fk_Vertex^>^ A = gcnew array<fk_Vertex^>(vA.size());
		for(int i = 0; i < int(vA.size()); ++i) {
			A[i] = gcnew fk_Vertex(false);
			A[i]->pBase = vA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	array<fk_Half^>^ fk_Reference::GetAllHOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		vector<::fk_Half *> hA = GetP()->getAllHOnL(argL->GetP());
		array<fk_Half^>^ A = gcnew array<fk_Half^>(hA.size());
		for(int i = 0; i < int(hA.size()); ++i) {
			A[i] = gcnew fk_Half(false);
			A[i]->pBase = hA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	array<fk_Edge^>^ fk_Reference::GetAllEOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		vector<::fk_Edge *> eA = GetP()->getAllEOnL(argL->GetP());
		array<fk_Edge^>^ A = gcnew array<fk_Edge^>(eA.size());
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
	array<fk_Vertex^>^ fk_Reference::GetAllNeighborVOnV(fk_Vertex^ argV)
	{
		if(!argV) return nullptr;
		vector<::fk_Vertex *> vA = GetP()->getAllNeighborVOnV(argV->GetP());
		array<fk_Vertex^>^ A = gcnew array<fk_Vertex^>(vA.size());
		for(int i = 0; i < int(vA.size()); ++i) {
			A[i] = gcnew fk_Vertex(false);
			A[i]->pBase = vA[i];
			A[i]->dFlg = false;
		}
		return A;
	}

	array<fk_Edge^>^ fk_Reference::GetEOnVV(fk_Vertex^ argV1, fk_Vertex^ argV2)
	{
		if(!argV1 || !argV2) nullptr;
		vector<::fk_Edge *> eA = GetP()->getEOnVV(argV1->GetP(), argV2->GetP());
		array<fk_Edge^>^ A = gcnew array<fk_Edge^>(eA.size());
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

	array<fk_Loop^>^ fk_Reference::GetAllNeighborLOnL(fk_Loop^ argL)
	{
		if(!argL) return nullptr;
		vector<::fk_Loop *> lA = GetP()->getAllNeighborLOnL(argL->GetP());
		array<fk_Loop^>^ A = gcnew array<fk_Loop^>(lA.size());
		for(int i = 0; i < int(lA.size()); ++i) {
			A[i] = gcnew fk_Loop(false);
			A[i]->pBase = lA[i];
			A[i]->dFlg = false;
		}
		return A;
	}
}
