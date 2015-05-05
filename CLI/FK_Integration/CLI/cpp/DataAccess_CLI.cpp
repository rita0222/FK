#include "DataAccess_CLI.h"
#include <list>

namespace FK_CLI {

	using namespace std;

	::fk_DataAccess * fk_DataAccess::GetP(void)
	{
		return (::fk_DataAccess *)(pBase);
	}

	fk_DataAccess::fk_DataAccess(bool argNewFlg) : fk_Reference(false)
	{
	}

	fk_DataAccess::~fk_DataAccess()
	{
		this->!fk_DataAccess();
	}

	fk_DataAccess::!fk_DataAccess()
	{
	}

	int fk_DataAccess::VNum::get()
	{
		return GetP()->getVNum();
	}


	int fk_DataAccess::HNum::get()
	{
		return GetP()->getHNum();
	}

	int fk_DataAccess::ENum::get()
	{
		return GetP()->getENum();
	}

	int fk_DataAccess::LNum::get()
	{
		return GetP()->getLNum();
	}

	bool fk_DataAccess::CheckDB(void)
	{
		return GetP()->checkDB();
	}

	bool fk_DataAccess::CheckTopology(void)
	{
		return GetP()->checkTopology();
	}

	bool fk_DataAccess::ExistVertex(fk_Vertex^ argV)
	{
		if(!argV) return false;
		return GetP()->existVertex(argV->GetP());
	}

	bool fk_DataAccess::ExistVertex(int argID)
	{
		return GetP()->existVertex(argID);
	}

	bool fk_DataAccess::ExistHalf(fk_Half^ argH)
	{
		if(!argH) return false;
		return GetP()->existHalf(argH->GetP());
	}

	bool fk_DataAccess::ExistHalf(int argID)
	{
		return GetP()->existHalf(argID);
	}

	bool fk_DataAccess::ExistEdge(fk_Edge^ argE)
	{
		if(!argE) return false;
		return GetP()->existEdge(argE->GetP());
	}

	bool fk_DataAccess::ExistEdge(int argID)
	{
		return GetP()->existEdge(argID);
	}

	bool fk_DataAccess::ExistLoop(fk_Loop^ argL)
	{
		if(!argL) return false;
		return GetP()->existLoop(argL->GetP());
	}

	bool fk_DataAccess::ExistLoop(int argID)
	{
		return GetP()->existLoop(argID);
	}

	fk_Vertex^ fk_DataAccess::GetVData(int argID)
	{
		::fk_Vertex *pV = GetP()->getVData(argID);
		if(pV == nullptr) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = pV;
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_DataAccess::GetHData(int argID)
	{
		::fk_Half *pH = GetP()->getHData(argID);
		if(pH == nullptr) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = pH;
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_DataAccess::GetEData(int argID)
	{
		::fk_Edge *pE = GetP()->getEData(argID);
		if(pE == nullptr) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	fk_Loop^ fk_DataAccess::GetLData(int argID)
	{
		::fk_Loop *pL = GetP()->getLData(argID);
		if(pL == nullptr) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = pL;
		L->dFlg = false;
		return L;
	}

	fk_Vertex^ fk_DataAccess::GetNextV(fk_Vertex^ argV)
	{
		::fk_Vertex *pV = (!argV) ? GetP()->getNextV(nullptr) : GetP()->getNextV(argV->GetP());
		if(pV == nullptr) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = pV;
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_DataAccess::GetNextH(fk_Half^ argH)
	{
		::fk_Half *pH = (!argH) ? GetP()->getNextH(nullptr) : GetP()->getNextH(argH->GetP());
		if(pH == nullptr) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = pH;
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_DataAccess::GetNextE(fk_Edge^ argE)
	{
		::fk_Edge *pE = (!argE) ? GetP()->getNextE(nullptr) : GetP()->getNextE(argE->GetP());
		if(pE == nullptr) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	fk_Loop^ fk_DataAccess::GetNextL(fk_Loop^ argL)
	{
		::fk_Loop *pL = (!argL) ? GetP()->getNextL(nullptr) : GetP()->getNextL(argL->GetP());
		if(pL == nullptr) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = pL;
		L->dFlg = false;
		return L;
	}

	fk_Vertex^ fk_DataAccess::GetLastV(void)
	{
		::fk_Vertex *pV = GetP()->getLastV();
		if(pV == nullptr) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = pV;
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_DataAccess::GetLastH(void)
	{
		::fk_Half *pH = GetP()->getLastH();
		if(pH == nullptr) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = pH;
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_DataAccess::GetLastE(void)
	{
		::fk_Edge *pE = GetP()->getLastE();
		if(pE == nullptr) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	fk_Loop^ fk_DataAccess::GetLastL(void)
	{
		::fk_Loop *pL = GetP()->getLastL();
		if(pL == nullptr) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = pL;
		L->dFlg = false;
		return L;
	}

	array<fk_Vertex^>^ fk_DataAccess::GetVertexArray(void)
	{
		list<::fk_Vertex *> vList;
		GetP()->getVertexList(&vList);
		array<fk_Vertex^>^ A = gcnew array<fk_Vertex^>(vList.size());
		int count = 0;
		for(auto v : vList) {
			A[count]->pBase = v;
			A[count]->dFlg = false;
			count++;
		}
		return A;
	}

	array<fk_Half^>^ fk_DataAccess::GetHalfArray(void)
	{
		list<::fk_Half *> hList;
		GetP()->getHalfList(&hList);
		array<fk_Half^>^ A = gcnew array<fk_Half^>(hList.size());
		int count = 0;
		for(auto h : hList) {
			A[count]->pBase = h;
			A[count]->dFlg = false;
			count++;
		}
		return A;
	}

	array<fk_Edge^>^ fk_DataAccess::GetEdgeArray(void)
	{
		list<::fk_Edge *> eList;
		GetP()->getEdgeList(&eList);
		array<fk_Edge^>^ A = gcnew array<fk_Edge^>(eList.size());
		int count = 0;
		for(auto e : eList) {
			A[count]->pBase = e;
			A[count]->dFlg = false;
			count++;
		}
		return A;
	}

	array<fk_Loop^>^ fk_DataAccess::GetLoopArray(void)
	{
		list<::fk_Loop *> lList;
		GetP()->getLoopList(&lList);
		array<fk_Loop^>^ A = gcnew array<fk_Loop^>(lList.size());
		int count = 0;
		for(auto l : lList) {
			A[count]->pBase = l;
			A[count]->dFlg = false;
			count++;
		}
		return A;
	}

}
