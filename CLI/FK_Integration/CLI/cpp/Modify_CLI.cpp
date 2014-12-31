#include "Modify_CLI.h"

namespace FK_CLI {

	using namespace std;

	fk_Loop^ fk_Modify::removeVertexInLoop(fk_Vertex ^argV)
	{
		if(!argV) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->removeVertexInLoop(argV->GetP());
		L->dFlg = false;
		return L;
	}

	bool fk_Modify::contractEdge(fk_Edge ^argE, bool argR)
	{
		if(!argE) return false;
		return GetP()->contractEdge(argE->GetP(), argR);
	}

	bool fk_Modify::contractEdge(fk_Edge ^argE)
	{
		if(!argE) return false;
		return GetP()->contractEdge(argE->GetP());
	}
		
	bool fk_Modify::contractEdge(fk_Edge ^argE, fk_Vector ^argP, bool argR)
	{
		if(!argE) return false;
		return GetP()->contractEdge(argE->GetP(), *argP->pVec, argR);
	}

	bool fk_Modify::contractEdge(fk_Edge ^argE, fk_Vector ^argP)
	{
		if(!argE) return false;
		return GetP()->contractEdge(argE->GetP(), *argP->pVec);
	}

	bool fk_Modify::checkContract(fk_Edge ^argE)
	{
		if(!argE) return false;
		return GetP()->checkContract(argE->GetP());
	}

	fk_Loop^ fk_Modify::makePolygon(array<fk_Vector^>^ argArray, bool argOpenFlg, bool argInitFlg)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *argArray[i]->pVec;
		}
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->makePolygon(&vArray, argOpenFlg, argInitFlg);
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Modify::makePolygon(array<fk_Vector^>^ argArray, bool argOpenFlg)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *argArray[i]->pVec;
		}
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->makePolygon(&vArray, argOpenFlg);
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Modify::pushPolygon(array<fk_Vector^>^ argArray, bool argOpenFlg)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *argArray[i]->pVec;
		}
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->pushPolygon(&vArray, argOpenFlg);
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Modify::pushPolygon(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *argArray[i]->pVec;
		}
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->pushPolygon(&vArray);
		L->dFlg = false;
		return L;
	}

	void fk_Modify::pushPolygonVertex(fk_Vector ^argPos, bool argOpenFlg)
	{
		if(!argPos) return;
		GetP()->pushPolygonVertex(*argPos->pVec, argOpenFlg);
	}

	void fk_Modify::makePoint(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *argArray[i]->pVec;
		}
		GetP()->makePoint(&vArray);
	}

	fk_Vertex^ fk_Modify::pushPointVertex(fk_Vector ^argPos)
	{
		if(!argPos) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = GetP()->pushPointVertex(*argPos->pVec);
		V->dFlg = false;
		return V;
	}

	void fk_Modify::makeLines(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *argArray[i]->pVec;
		}
		GetP()->makeLines(&vArray);
	}

	fk_Edge^ fk_Modify::pushLines(fk_Vector ^argP1, fk_Vector ^argP2)
	{
		if(!argP1 || !argP2) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = GetP()->pushLines(*argP1->pVec, *argP2->pVec);
		E->dFlg = false;
		return E;
	}

	bool fk_Modify::setLinePos(int argID, fk_Vector ^argP)
	{
		if(!argP) return false;
		return GetP()->setLinePos(argID, *argP->pVec);
	}

	bool fk_Modify::setLinePos(int argEID, int argVID, fk_Vector^ argP)
	{
		if(!argP) return false;
		return GetP()->setLinePos(argEID, argVID, *argP->pVec);
	}

	bool fk_Modify::changeLine(int argEID, fk_Vector^ argP1, fk_Vector^ argP2)
	{
		if(!argP1 || !argP2) return false;
		return GetP()->changeLine(argEID, *argP1->pVec, *argP2->pVec);
	}

	void fk_Modify::makeBlock(double argX, double argY, double argZ)
	{
		GetP()->makeBlock(argX, argY, argZ);
	}

	void fk_Modify::setBlockSize(double argX, double argY, double argZ)
	{
		GetP()->setBlockSize(argX, argY, argZ);
	}

	void fk_Modify::setBlockSize(double argLength, fk_Axis argAxis)
	{
		GetP()->setBlockSize(argLength, fk_Vector::GetAxis(argAxis));
	}

	void fk_Modify::setBlockScale(double argScale)
	{
		GetP()->setBlockScale(argScale);
	}

	void fk_Modify::setBlockScale(double argScale, fk_Axis argAxis)
	{
		GetP()->setBlockScale(argScale, fk_Vector::GetAxis(argAxis));
	}

	void fk_Modify::setBlockScale(double argX, double argY, double argZ)
	{
		GetP()->setBlockScale(argX, argY, argZ);
	}

	void fk_Modify::makeCircle(int argDiv, double argRad)
	{
		GetP()->makeCircle(argDiv, argRad);
	}

	void fk_Modify::setCircleRadius(double argRad)
	{
		GetP()->setCircleRadius(argRad);
	}

	void fk_Modify::setCircleDivide(int argDiv)
	{
		GetP()->setCircleDivide(argDiv);
	}

	void fk_Modify::setCircleScale(double argScale)
	{
		GetP()->setCircleScale(argScale);
	}

	void fk_Modify::makeSphere(int argDiv, double argRad)
	{
		GetP()->makeSphere(argDiv, argRad);
	}

	void fk_Modify::setSphereRadius(double argRad)
	{
		GetP()->setSphereRadius(argRad);
	}

	void fk_Modify::setSphereDivide(int argDiv)
	{
		GetP()->setSphereDivide(argDiv);
	}

	void fk_Modify::setSphereScale(double argScale)
	{
		GetP()->setSphereScale(argScale);
	}

	void fk_Modify::makePrism(int argDiv, double argT, double argB, double argH)
	{
		GetP()->makePrism(argDiv, argT, argB, argH);
	}

	void fk_Modify::setPrismDivide(int argDiv)
	{
		GetP()->setPrismDivide(argDiv);
	}

	void fk_Modify::setPrismTopRadius(double argT)
	{
		GetP()->setPrismTopRadius(argT);
	}

	void fk_Modify::setPrismBottomRadius(double argB)
	{
		GetP()->setPrismBottomRadius(argB);
	}

	void fk_Modify::setPrismHeight(double argH)
	{
		GetP()->setPrismHeight(argH);
	}

	void fk_Modify::makeCone(int argDiv, double argRad, double argH)
	{
		GetP()->makeCone(argDiv, argRad, argH);
	}

	void fk_Modify::setConeDivide(int argDiv)
	{
		GetP()->setConeDivide(argDiv);
	}

	void fk_Modify::setConeRadius(double argRad)
	{
		GetP()->setConeRadius(argRad);
	}

	void fk_Modify::setConeHeight(double argH)
	{
		GetP()->setConeHeight(argH);
	}

	bool fk_Modify::moveVPosition(int argVID, fk_Vector ^argP, int argOrder)
	{
		if(!argP) return false;
		return GetP()->moveVPosition(argVID, *argP->pVec, argOrder);
	}

	bool fk_Modify::moveVPosition(int argVID, fk_Vector ^argP)
	{
		if(!argP) return false;
		return GetP()->moveVPosition(argVID, *argP->pVec);
	}

	bool fk_Modify::moveVPosition(int argVID, double argX, double argY, double argZ, int argOrder)
	{
		return GetP()->moveVPosition(argVID, argX, argY, argZ, argOrder);
	}

	bool fk_Modify::moveVPosition(int argVID, double argX, double argY, double argZ)
	{
		return GetP()->moveVPosition(argVID, argX, argY, argZ);
	}

	void fk_Modify::subdivShape(int argCount)
	{
		GetP()->subdivShape(argCount);
	}
}
