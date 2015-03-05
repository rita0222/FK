#include "Half_CLI.h"
#include "Vertex_CLI.h"
#include "Edge_CLI.h"
#include "Loop_CLI.h"

namespace FK_CLI {

	::fk_Half * fk_Half::GetP(void)
	{
		return (::fk_Half *)(pBase);
	}

	fk_Half::fk_Half(bool argNewFlg) : fk_Topology(false)
	{
	}

	fk_Half::~fk_Half()
	{
		this->!fk_Half();
	}

	fk_Half::!fk_Half()
	{
	}

	fk_Vertex^ fk_Half::Vertex::get(void)
	{
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = GetP()->getVertex();
		V->dFlg = false;
		return V;
	}
				
	fk_Half^ fk_Half::NextHalf::get(void)
	{
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getNextHalf();
		H->dFlg = false;
		return H;
	}
				
	fk_Half^ fk_Half::PrevHalf::get(void)
	{
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getPrevHalf();
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_Half::ParentEdge::get(void)
	{
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = GetP()->getParentEdge();
		E->dFlg = false;
		return E;
	}
		
	fk_Loop^ fk_Half::ParentLoop::get(void)
	{
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->getParentLoop();
		L->dFlg = false;
		return L;
	}

	bool fk_Half::IsLeft(void)
	{
		return GetP()->isLeft();
	}

	bool fk_Half::IsRight(void)
	{
		return GetP()->isRight();
	}
}
