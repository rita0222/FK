#include "DataAccess_CLI.h"
#include <list>

namespace FK_CLI {

	using namespace std;

	bool fk_DataAccess::checkDB(void)
	{
		return GetP()->checkDB();
	}

	bool fk_DataAccess::checkTopology(void)
	{
		return GetP()->checkTopology();
	}

	bool fk_DataAccess::existVertex(fk_Vertex^ argV)
	{
		if(!argV) return false;
		return GetP()->existVertex(argV->GetP());
	}

	bool fk_DataAccess::existVertex(int argID)
	{
		return GetP()->existVertex(argID);
	}

	bool fk_DataAccess::existHalf(fk_Half^ argH)
	{
		if(!argH) return false;
		return GetP()->existHalf(argH->GetP());
	}

	bool fk_DataAccess::existHalf(int argID)
	{
		return GetP()->existHalf(argID);
	}

	bool fk_DataAccess::existEdge(fk_Edge^ argE)
	{
		if(!argE) return false;
		return GetP()->existEdge(argE->GetP());
	}

	bool fk_DataAccess::existEdge(int argID)
	{
		return GetP()->existEdge(argID);
	}

	bool fk_DataAccess::existLoop(fk_Loop^ argL)
	{
		if(!argL) return false;
		return GetP()->existLoop(argL->GetP());
	}

	bool fk_DataAccess::existLoop(int argID)
	{
		return GetP()->existLoop(argID);
	}

	fk_Vertex^ fk_DataAccess::getVData(int argID)
	{
		::fk_Vertex *pV = GetP()->getVData(argID);
		if(pV == nullptr) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = pV;
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_DataAccess::getHData(int argID)
	{
		::fk_Half *pH = GetP()->getHData(argID);
		if(pH == nullptr) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = pH;
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_DataAccess::getEData(int argID)
	{
		::fk_Edge *pE = GetP()->getEData(argID);
		if(pE == nullptr) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	fk_Loop^ fk_DataAccess::getLData(int argID)
	{
		::fk_Loop *pL = GetP()->getLData(argID);
		if(pL == nullptr) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = pL;
		L->dFlg = false;
		return L;
	}

	fk_Vertex^ fk_DataAccess::getNextV(fk_Vertex^ argV)
	{
		::fk_Vertex *pV = (!argV) ? GetP()->getNextV(nullptr) : GetP()->getNextV(argV->GetP());
		if(pV == nullptr) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = pV;
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_DataAccess::getNextH(fk_Half^ argH)
	{
		::fk_Half *pH = (!argH) ? GetP()->getNextH(nullptr) : GetP()->getNextH(argH->GetP());
		if(pH == nullptr) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = pH;
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_DataAccess::getNextE(fk_Edge^ argE)
	{
		::fk_Edge *pE = (!argE) ? GetP()->getNextE(nullptr) : GetP()->getNextE(argE->GetP());
		if(pE == nullptr) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	fk_Loop^ fk_DataAccess::getNextL(fk_Loop^ argL)
	{
		::fk_Loop *pL = (!argL) ? GetP()->getNextL(nullptr) : GetP()->getNextL(argL->GetP());
		if(pL == nullptr) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = pL;
		L->dFlg = false;
		return L;
	}

	fk_Vertex^ fk_DataAccess::getLastV(void)
	{
		::fk_Vertex *pV = GetP()->getLastV();
		if(pV == nullptr) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = pV;
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_DataAccess::getLastH(void)
	{
		::fk_Half *pH = GetP()->getLastH();
		if(pH == nullptr) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = pH;
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_DataAccess::getLastE(void)
	{
		::fk_Edge *pE = GetP()->getLastE();
		if(pE == nullptr) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	fk_Loop^ fk_DataAccess::getLastL(void)
	{
		::fk_Loop *pL = GetP()->getLastL();
		if(pL == nullptr) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = pL;
		L->dFlg = false;
		return L;
	}

	int fk_DataAccess::getVNum(void)
	{
		return GetP()->getVNum();
	}

	int fk_DataAccess::getHNum(void)
	{
		return GetP()->getHNum();
	}

	int fk_DataAccess::getENum(void)
	{
		return GetP()->getENum();
	}

	int fk_DataAccess::getLNum(void)
	{
		return GetP()->getLNum();
	}

	array<fk_Vertex^>^ fk_DataAccess::getVertexList(void)
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

	array<fk_Half^>^ fk_DataAccess::getHalfList(void)
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

	array<fk_Edge^>^ fk_DataAccess::getEdgeList(void)
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

	array<fk_Loop^>^ fk_DataAccess::getLoopList(void)
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
