#include "Operation_CLI.h"

namespace FK_CLI {

	fk_Vertex^ fk_Operation::makeVertex(fk_Vector^ argP)
	{
		if(!argP) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = GetP()->makeVertex(*argP->pVec);
		V->dFlg = false;
		return V;
	}

	bool fk_Operation::deleteVertex(fk_Vertex^ argV)
	{
		if(!argV) return false;
		return GetP()->deleteVertex(argV->GetP());
	}

	bool fk_Operation::moveVertex(fk_Vertex^ argV, fk_Vector^ argP)
	{
		if(!argV || !argP) return false;
		return GetP()->moveVertex(argV->GetP(), *argP->pVec);
	}

	fk_Edge^ fk_Operation::makeEdge(fk_Vertex^ argV1, fk_Vertex^ argV2,
									fk_Half^ argH11, fk_Half^ argH12,
									fk_Half^ argH21, fk_Half^ argH22)
	{
		if(!argV1 || !argV2 || !argH11 || !argH12 || !argH21 || !argH22) return nullptr;

		::fk_Edge *pE = GetP()->makeEdge(argV1->GetP(), argV2->GetP(),
										 argH11->GetP(), argH12->GetP(),
										 argH21->GetP(), argH22->GetP());
		if(pE == NULL) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	fk_Edge^ fk_Operation::makeEdge(fk_Vertex^ argV1, fk_Vertex^ argV2)
	{
		if(!argV1 || !argV2) return nullptr;

		::fk_Edge *pE = GetP()->makeEdge(argV1->GetP(), argV2->GetP());

		if(pE == NULL) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	bool fk_Operation::deleteEdge(fk_Edge^ argE)
	{
		if(!argE) return false;
		return GetP()->deleteEdge(argE->GetP());
	}

	fk_Loop^ fk_Operation::makeLoop(fk_Half^ argH)
	{
		if(!argH) return nullptr;
		::fk_Loop *pL = GetP()->makeLoop(argH->GetP());
		if(pL == NULL) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = pL;
		L->dFlg = false;
		return L;
	}

	bool fk_Operation::deleteLoop(fk_Loop^ argL)
	{
		if(!argL) return false;
		return GetP()->deleteLoop(argL->GetP());
	}

	fk_Edge^ fk_Operation::separateLoop(fk_Half^ argH1, fk_Half^ argH2)
	{
		if(!argH1 || !argH2) return nullptr;
		::fk_Edge *pE = GetP()->separateLoop(argH1->GetP(), argH2->GetP());
		if(pE == NULL) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	bool fk_Operation::uniteLoop(fk_Edge^ argE)
	{
		if(!argE) return false;
		return GetP()->uniteLoop(argE->GetP());
	}

	fk_Vertex^ fk_Operation::separateEdge(fk_Edge^ argE)
	{
		if(!argE) return nullptr;
		::fk_Vertex *pV = GetP()->separateEdge(argE->GetP());
		if(pV == NULL) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = pV;
		V->dFlg = false;
		return V;
	}
			
	bool fk_Operation::uniteEdge(fk_Vertex^ argV)
	{
		if(!argV) return false;
		return GetP()->uniteEdge(argV->GetP());
	}

	void fk_Operation::negateBody(void)
	{
		GetP()->negateBody();
	}

	void fk_Operation::setHistoryMode(bool argMode)
	{
		GetP()->setHistoryMode(argMode);
	}

	bool fk_Operation::getHistoryMode(void)
	{
		return GetP()->getHistoryMode();
	}

	void fk_Operation::setHistoryMark(void)
	{
		GetP()->setHistoryMark();
	}

	bool fk_Operation::undoHistory(void)
	{
		return GetP()->undoHistory();
	}

	bool fk_Operation::redoHistory(void)
	{
		return GetP()->redoHistory();
	}

	void fk_Operation::setTesselateMode(bool argMode)
	{
		GetP()->setTesselateMode(argMode);
	}

	bool fk_Operation::getTesselateMode(void)
	{
		return GetP()->getTesselateMode();
	}
}
