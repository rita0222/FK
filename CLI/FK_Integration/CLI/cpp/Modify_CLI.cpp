#include "Modify_CLI.h"

namespace FK_CLI {

	using namespace std;

	::fk_Modify * fk_Modify::GetP(void)
	{
		return (::fk_Modify *)(pBase);
	}

	fk_Modify::fk_Modify(bool argNewFlg) : fk_Operation(false)
	{
	}

	fk_Modify::~fk_Modify()
	{
		this->!fk_Modify();
	}

	fk_Modify::!fk_Modify()
	{
	}

	fk_Loop^ fk_Modify::RemoveVertexInLoop(fk_Vertex ^argV)
	{
		if(!argV) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->removeVertexInLoop(argV->GetP());
		L->dFlg = false;
		return L;
	}

	bool fk_Modify::ContractEdge(fk_Edge ^argE, bool argR)
	{
		if(!argE) return false;
		return GetP()->contractEdge(argE->GetP(), argR);
	}

	bool fk_Modify::ContractEdge(fk_Edge ^argE)
	{
		if(!argE) return false;
		return GetP()->contractEdge(argE->GetP());
	}
		
	bool fk_Modify::ContractEdge(fk_Edge ^argE, fk_Vector ^argP, bool argR)
	{
		if(!argE) return false;
		return GetP()->contractEdge(argE->GetP(), argP, argR);
	}

	bool fk_Modify::ContractEdge(fk_Edge ^argE, fk_Vector ^argP)
	{
		if(!argE) return false;
		return GetP()->contractEdge(argE->GetP(), argP);
	}

	bool fk_Modify::CheckContract(fk_Edge ^argE)
	{
		if(!argE) return false;
		return GetP()->checkContract(argE->GetP());
	}

	fk_Loop^ fk_Modify::MakePolygon(array<fk_Vector^>^ argArray, bool argOpenFlg, bool argInitFlg)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = argArray[i];
		}
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->makePolygon(&vArray, argOpenFlg, argInitFlg);
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Modify::MakePolygon(array<fk_Vector^>^ argArray, bool argOpenFlg)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = argArray[i];
		}
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->makePolygon(&vArray, argOpenFlg);
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Modify::PushPolygon(array<fk_Vector^>^ argArray, bool argOpenFlg)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = argArray[i];
		}
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->pushPolygon(&vArray, argOpenFlg);
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Modify::PushPolygon(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = argArray[i];
		}
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->pushPolygon(&vArray);
		L->dFlg = false;
		return L;
	}

	void fk_Modify::PushPolygonVertex(fk_Vector ^argP, bool argOpenFlg)
	{
		if(!argP) return;
		GetP()->pushPolygonVertex(argP, argOpenFlg);
	}

	void fk_Modify::MakePoint(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i]= argArray[i];
		}
		GetP()->makePoint(&vArray);
	}

	fk_Vertex^ fk_Modify::PushPointVertex(fk_Vector ^argP)
	{
		if(!argP) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = GetP()->pushPointVertex(argP);
		V->dFlg = false;
		return V;
	}

	void fk_Modify::MakeLines(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = argArray[i];
		}
		GetP()->makeLines(&vArray);
	}

	fk_Edge^ fk_Modify::PushLines(fk_Vector ^argP1, fk_Vector ^argP2)
	{
		if(!argP1 || !argP2) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = GetP()->pushLines(argP1, argP2);
		E->dFlg = false;
		return E;
	}

	bool fk_Modify::SetLinePos(int argID, fk_Vector ^argP)
	{
		if(!argP) return false;
		return GetP()->setLinePos(argID, argP);
	}

	bool fk_Modify::SetLinePos(int argEID, int argVID, fk_Vector^ argP)
	{
		if(!argP) return false;
		return GetP()->setLinePos(argEID, argVID, argP);
	}

	bool fk_Modify::ChangeLine(int argEID, fk_Vector^ argP1, fk_Vector^ argP2)
	{
		if(!argP1 || !argP2) return false;
		return GetP()->changeLine(argEID, argP1, argP2);
	}

	void fk_Modify::MakeBlock(double argX, double argY, double argZ)
	{
		GetP()->makeBlock(argX, argY, argZ);
	}

	void fk_Modify::SetBlockSize(double argX, double argY, double argZ)
	{
		GetP()->setBlockSize(argX, argY, argZ);
	}

	void fk_Modify::SetBlockSize(double argLength, fk_Axis argAxis)
	{
		GetP()->setBlockSize(argLength, fk_Vector::GetAxis(argAxis));
	}

	void fk_Modify::SetBlockScale(double argScale)
	{
		GetP()->setBlockScale(argScale);
	}

	void fk_Modify::SetBlockScale(double argScale, fk_Axis argAxis)
	{
		GetP()->setBlockScale(argScale, fk_Vector::GetAxis(argAxis));
	}

	void fk_Modify::SetBlockScale(double argX, double argY, double argZ)
	{
		GetP()->setBlockScale(argX, argY, argZ);
	}

	void fk_Modify::MakeCircle(int argDiv, double argRad)
	{
		GetP()->makeCircle(argDiv, argRad);
	}

	void fk_Modify::SetCircleRadius(double argRad)
	{
		GetP()->setCircleRadius(argRad);
	}

	void fk_Modify::SetCircleDivide(int argDiv)
	{
		GetP()->setCircleDivide(argDiv);
	}

	void fk_Modify::SetCircleScale(double argScale)
	{
		GetP()->setCircleScale(argScale);
	}

	void fk_Modify::MakeSphere(int argDiv, double argRad)
	{
		GetP()->makeSphere(argDiv, argRad);
	}

	void fk_Modify::SetSphereRadius(double argRad)
	{
		GetP()->setSphereRadius(argRad);
	}

	void fk_Modify::SetSphereDivide(int argDiv)
	{
		GetP()->setSphereDivide(argDiv);
	}

	void fk_Modify::SetSphereScale(double argScale)
	{
		GetP()->setSphereScale(argScale);
	}

	void fk_Modify::MakePrism(int argDiv, double argT, double argB, double argH)
	{
		GetP()->makePrism(argDiv, argT, argB, argH);
	}

	void fk_Modify::SetPrismDivide(int argDiv)
	{
		GetP()->setPrismDivide(argDiv);
	}

	void fk_Modify::SetPrismTopRadius(double argT)
	{
		GetP()->setPrismTopRadius(argT);
	}

	void fk_Modify::SetPrismBottomRadius(double argB)
	{
		GetP()->setPrismBottomRadius(argB);
	}

	void fk_Modify::SetPrismHeight(double argH)
	{
		GetP()->setPrismHeight(argH);
	}

	void fk_Modify::MakeCone(int argDiv, double argRad, double argH)
	{
		GetP()->makeCone(argDiv, argRad, argH);
	}

	void fk_Modify::SetConeDivide(int argDiv)
	{
		GetP()->setConeDivide(argDiv);
	}

	void fk_Modify::SetConeRadius(double argRad)
	{
		GetP()->setConeRadius(argRad);
	}

	void fk_Modify::SetConeHeight(double argH)
	{
		GetP()->setConeHeight(argH);
	}

	bool fk_Modify::MoveVPosition(int argVID, fk_Vector ^argP, int argOrder)
	{
		if(!argP) return false;
		return GetP()->moveVPosition(argVID, argP, argOrder);
	}

	bool fk_Modify::MoveVPosition(int argVID, fk_Vector ^argP)
	{
		if(!argP) return false;
		return GetP()->moveVPosition(argVID, argP);
	}

	bool fk_Modify::MoveVPosition(int argVID, double argX, double argY, double argZ, int argOrder)
	{
		return GetP()->moveVPosition(argVID, argX, argY, argZ, argOrder);
	}

	bool fk_Modify::MoveVPosition(int argVID, double argX, double argY, double argZ)
	{
		return GetP()->moveVPosition(argVID, argX, argY, argZ);
	}

	void fk_Modify::SubDivShape(int argCount)
	{
		GetP()->subdivShape(argCount);
	}
}
