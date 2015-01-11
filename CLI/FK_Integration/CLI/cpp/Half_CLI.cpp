#include "Half_CLI.h"
#include "Vertex_CLI.h"
#include "Edge_CLI.h"
#include "Loop_CLI.h"

namespace FK_CLI {
	fk_Vertex^ fk_Half::getVertex(void)
	{
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = GetP()->getVertex();
		V->dFlg = false;
		return V;
	}
				
	fk_Half^ fk_Half::getNextHalf(void)
	{
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getNextHalf();
		H->dFlg = false;
		return H;
	}
				
	fk_Half^ fk_Half::getPrevHalf(void)
	{
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getPrevHalf();
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_Half::getParentEdge(void)
	{
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = GetP()->getParentEdge();
		E->dFlg = false;
		return E;
	}
		
	fk_Loop^ fk_Half::getParentLoop(void)
	{
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->getParentLoop();
		L->dFlg = false;
		return L;
	}

	bool fk_Half::isLeft(void)
	{
		return GetP()->isLeft();
	}

	bool fk_Half::isRight(void)
	{
		return GetP()->isRight();
	}
}
