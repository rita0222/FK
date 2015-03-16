/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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

#define FK_DEF_SIZETYPE
#include <FK/Base.h>
#include <FK/DataBase.H>

#ifdef FK_EXTERN
#undef FK_EXTERN
#endif
#define FK_EXTERN extern

#include <FK/Error.H>

#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Edge.h>
#include <FK/Loop.h>
#include <FK/ParserBase.H>

using namespace std;

fk_DataBase::fk_DataBase(void)
{
	AllClear();
}

fk_DataBase::~fk_DataBase()
{
	AllClear();
}

void fk_DataBase::AllClear(void)
{
	vAdmin.Init(1);
	hAdmin.Init(1);
	eAdmin.Init(1);
	lAdmin.Init(1);

	while(!vSet.empty()) {
		delete vSet.back();
		vSet.pop_back();
	}

	while(!hSet.empty()) {
		delete hSet.back();
		hSet.pop_back();
	}

	while(!eSet.empty()) {
		delete eSet.back();
		eSet.pop_back();
	}

	while(!lSet.empty()) {
		delete lSet.back();
		lSet.pop_back();
	}

	return;
}

void fk_DataBase::CloneData(fk_DataBase *argDB)
{
	if(argDB == this) return;

	ResizeData(argDB);

	vAdmin.CloneData(&argDB->vAdmin);
	hAdmin.CloneData(&argDB->hAdmin);
	eAdmin.CloneData(&argDB->eAdmin);
	lAdmin.CloneData(&argDB->lAdmin);

	VSetClone(&argDB->vSet);
	HSetClone(&argDB->hSet);
	ESetClone(&argDB->eSet);
	LSetClone(&argDB->lSet);

	return;
}

void fk_DataBase::ResizeData(fk_DataBase *argDB)
{
	ResizeData(static_cast<int>(argDB->vSet.size()),
			   static_cast<int>(argDB->hSet.size()),
			   static_cast<int>(argDB->eSet.size()),
			   static_cast<int>(argDB->lSet.size()));

	return;
}

void fk_DataBase::ResizeData(int argVNum, int argHNum,
							 int argENum, int argLNum)
{
	_st		i;

	for(i = vSet.size(); i < static_cast<_st>(argVNum); i++) {
		vSet.push_back(new fk_Vertex(static_cast<int>(i+1)));
	}

	for(i = static_cast<_st>(argVNum); i < vSet.size(); i++) {
		delete vSet.back();
		vSet.pop_back();
	}
		
	for(i = hSet.size(); i < static_cast<_st>(argHNum); i++) {
		hSet.push_back(new fk_Half(static_cast<int>(i+1)));
	}

	for(i = static_cast<_st>(argHNum); i < hSet.size(); i++) {
		delete hSet.back();
		hSet.pop_back();
	}
		
	for(i = eSet.size(); i < static_cast<_st>(argENum); i++) {
		eSet.push_back(new fk_Edge(static_cast<int>(i+1)));
	}

	for(i = static_cast<_st>(argENum); i < eSet.size(); i++) {
		delete eSet.back();
		eSet.pop_back();
	}
		
	for(i = lSet.size(); i < static_cast<_st>(argLNum); i++) {
		lSet.push_back(new fk_Loop(static_cast<int>(i+1)));
	}

	for(i = static_cast<_st>(argLNum); i < lSet.size(); i++) {
		delete lSet.back();
		lSet.pop_back();
	}

	return;
}

void fk_DataBase::VSetClone(vector<fk_Vertex *> *argVSet)
{
	_st			i;
	fk_Vertex	*orgV, *newV;

	for(i = 0; i < vSet.size(); i++) {
		newV = vSet[i];
		orgV = (*argVSet)[i];

		if(newV->CloneElem(orgV) == false) {
			continue;
		}
		newV->CloneMaterial(orgV);

		newV->position = orgV->position;
		newV->normal = orgV->normal;
		newV->normCalcFlag = orgV->normCalcFlag;
		newV->normFailFlag = orgV->normFailFlag;
		if(orgV->oneHalf == nullptr) {
			newV->oneHalf = nullptr;
		} else {
			newV->oneHalf = GetHData(orgV->oneHalf->getID());
		}
	}

	return;
}

void fk_DataBase::HSetClone(vector<fk_Half *> *argHSet)
{
	_st			i;
	fk_Half		*orgH, *newH;

	for(i = 0; i < hSet.size(); i++) {
		orgH = (*argHSet)[i];
		newH = hSet[i];

		if(newH->CloneElem(orgH) == false) {
			continue;
		}

		newH->vertex = GetVData(orgH->vertex->getID());
		newH->nextHalf = GetHData(orgH->nextHalf->getID());
		newH->prevHalf = GetHData(orgH->prevHalf->getID());
		newH->parentEdge = GetEData(orgH->parentEdge->getID());
		if(orgH->parentLoop == nullptr) {
			newH->parentLoop = nullptr;
		} else {
			newH->parentLoop = GetLData(orgH->parentLoop->getID());
		}
	}

	return;
}

void fk_DataBase::ESetClone(vector<fk_Edge *> *argESet)
{
	_st			i;
	fk_Edge		*orgE, *newE;

	for(i = 0; i < eSet.size(); i++) {
		orgE = (*argESet)[i];
		newE = eSet[i];

		if(newE->CloneElem(orgE) == false) continue;

		newE->CloneMaterial(orgE);

		newE->rightHalf = GetHData(orgE->rightHalf->getID());
		newE->leftHalf = GetHData(orgE->leftHalf->getID());
	}

	return;
}

void fk_DataBase::LSetClone(vector<fk_Loop *> *argLSet)
{
	_st			i;
	fk_Loop		*orgL, *newL;

	for(i = 0; i < lSet.size(); i++) {
		orgL = (*argLSet)[i];
		newL = lSet[i];

		if(newL->CloneElem(orgL) == false) continue;

		newL->CloneMaterial(orgL);

		newL->oneHalf = GetHData(orgL->oneHalf->getID());
		newL->norm = orgL->norm;
		newL->normFlag = orgL->normFlag;
	}

	return;
}

bool fk_DataBase::Compare(fk_DataBase *argDB)
{
	if(VCompare(argDB) == true &&
	   HCompare(argDB) == true &&
	   ECompare(argDB) == true &&
	   LCompare(argDB) == true) {
		return true;
	}

	return false;
}


bool fk_DataBase::VCompare(fk_DataBase *argDB)
{
	fk_Vertex		*v1, *v2;

	v1 = GetNextV(nullptr);
	v2 = argDB->GetNextV(nullptr);

	while(v1 != nullptr) {
		if(v1->Compare(v2) == false) return false;
		v1 = GetNextV(v1);
		v2 = argDB->GetNextV(v2);
	}

	if(v2 != nullptr) return false;
	return true;
}

bool fk_DataBase::HCompare(fk_DataBase *argDB)
{
	fk_Half		*h1, *h2;

	h1 = GetNextH(nullptr);
	h2 = argDB->GetNextH(nullptr);

	while(h1 != nullptr) {
		if(h1->Compare(h2) == false) return false;
		h1 = GetNextH(h1);
		h2 = argDB->GetNextH(h2);
	}

	if(h2 != nullptr) return false;
	return true;
}

bool fk_DataBase::ECompare(fk_DataBase *argDB)
{
	fk_Edge		*e1, *e2;

	e1 = GetNextE(nullptr);
	e2 = argDB->GetNextE(nullptr);

	while(e1 != nullptr) {
		if(e1->Compare(e2) == false) return false;
		e1 = GetNextE(e1);
		e2 = argDB->GetNextE(e2);
	}

	if(e2 != nullptr) return false;
	return true;
}

bool fk_DataBase::LCompare(fk_DataBase *argDB)
{
	fk_Loop		*l1, *l2;

	l1 = GetNextL(nullptr);
	l2 = argDB->GetNextL(nullptr);

	while(l1 != nullptr) {
		if(l1->Compare(l2) == false) return false;
		l1 = GetNextL(l1);
		l2 = argDB->GetNextL(l2);
	}

	if(l2 != nullptr) return false;
	return true;
}

fk_Vertex * fk_DataBase::GetNewVertex(void)
{
	int newID = vAdmin.CreateID();
	if(static_cast<int>(vSet.size())== newID - 1) {
		vSet.push_back(new fk_Vertex(newID));
	} else {
		vSet[static_cast<_st>(newID-1)]->Init(newID);
	}

	return vSet[static_cast<_st>(newID-1)];
}

fk_Vertex * fk_DataBase::GetNewVertex(int argID)
{
	if(vAdmin.CreateID(argID) == false) {
		return nullptr;
	}

	if(static_cast<int>(vSet.size()) == argID - 1) {
		vSet.push_back(new fk_Vertex(argID));
	} else {
		vSet[static_cast<_st>(argID-1)]->Init(argID);
	}

	return vSet[static_cast<_st>(argID-1)];
}

fk_Half * fk_DataBase::GetNewHalf(void)
{
	int newID = hAdmin.CreateID();

	if(static_cast<int>(hSet.size()) == newID - 1) {
		hSet.push_back(new fk_Half(newID));
	} else {
		hSet[static_cast<_st>(newID-1)]->Init(newID);
	}

	return hSet[static_cast<_st>(newID-1)];
}

fk_Half * fk_DataBase::GetNewHalf(int argID)
{
	if(hAdmin.CreateID(argID) == false) {
		return nullptr;
	}

	if(static_cast<int>(hSet.size()) == argID - 1) {
		hSet.push_back(new fk_Half(argID));
	} else {
		hSet[static_cast<_st>(argID-1)]->Init(argID);
	}

	return hSet[static_cast<_st>(argID-1)];
}

fk_Edge * fk_DataBase::GetNewEdge(void)
{
	int newID = eAdmin.CreateID();

	if(static_cast<int>(eSet.size()) == newID - 1) {
		eSet.push_back(new fk_Edge(newID));
	} else {
		eSet[static_cast<_st>(newID-1)]->MakeElem(newID);
	}

	return eSet[static_cast<_st>(newID-1)];
}

fk_Edge * fk_DataBase::GetNewEdge(int argID)
{
	if(eAdmin.CreateID(argID) == false) {
		return nullptr;
	}

	if(static_cast<int>(eSet.size()) == argID - 1) {
		eSet.push_back(new fk_Edge(argID));
	} else {
		eSet[static_cast<_st>(argID-1)]->MakeElem(argID);
	}

	return eSet[static_cast<_st>(argID-1)];
}

fk_Loop * fk_DataBase::GetNewLoop(void)
{
	int newID = lAdmin.CreateID();

	if(static_cast<int>(lSet.size()) == newID - 1) {
		lSet.push_back(new fk_Loop(newID));
	} else {
		lSet[static_cast<_st>(newID-1)]->MakeElem(newID);
	}

	return lSet[static_cast<_st>(newID-1)];
}

fk_Loop * fk_DataBase::GetNewLoop(int argID)
{
	if(lAdmin.CreateID(argID) == false) {
		return nullptr;
	}

	if(static_cast<int>(lSet.size()) == argID - 1) {
		lSet.push_back(new fk_Loop(argID));
	} else {
		lSet[static_cast<_st>(argID-1)]->MakeElem(argID);
	}

	return lSet[static_cast<_st>(argID-1)];
}

bool fk_DataBase::ExistVertex(fk_Vertex *argVx) const
{
	if(argVx == nullptr) return false;
	if(ExistVertex(argVx->getID()) == false) return false;
	if(vSet[static_cast<_st>(argVx->getID() - 1)] != argVx) return false;
	return true;
}

bool fk_DataBase::ExistVertex(int argID) const
{
	return vAdmin.ExistID(argID);
}

bool fk_DataBase::ExistHalf(fk_Half *argHf) const
{
	if(argHf == nullptr) return false;
	if(ExistHalf(argHf->getID()) == false) return false;
	if(hSet[static_cast<_st>(argHf->getID() - 1)] != argHf) return false;
	return true;
}

bool fk_DataBase::ExistHalf(int argID) const
{
	return hAdmin.ExistID(argID);
}

bool fk_DataBase::ExistEdge(fk_Edge *argEd) const
{
	if(argEd == nullptr) return false;
	if(ExistEdge(argEd->getID()) == false) return false;
	if(eSet[static_cast<_st>(argEd->getID() - 1)] != argEd) return false;
	return true;
}

bool fk_DataBase::ExistEdge(int argID) const
{
	return eAdmin.ExistID(argID);
}

bool fk_DataBase::ExistLoop(fk_Loop *argLp) const
{
	if(argLp == nullptr) return false;
	if(ExistLoop(argLp->getID()) == false) return false;
	if(lSet[static_cast<_st>(argLp->getID() - 1)] != argLp) return false;
	return true;
}

bool fk_DataBase::ExistLoop(int argID) const
{
	return lAdmin.ExistID(argID);
}

bool fk_DataBase::DeleteVertex(int argID)
{
	if(vAdmin.EraseID(argID) == false) return false;
	vSet[static_cast<_st>(argID-1)]->DeleteElem();
	return true;
}

bool fk_DataBase::DeleteHalf(int argID)
{
	if(hAdmin.EraseID(argID) == false) return false;
	hSet[static_cast<_st>(argID-1)]->DeleteElem();
	return true;
}

bool fk_DataBase::DeleteEdge(int argID)
{
	if(eAdmin.EraseID(argID) == false) return false;
	eSet[static_cast<_st>(argID-1)]->DeleteElem();
	return true;
}

bool fk_DataBase::DeleteLoop(int argID)
{
	if(lAdmin.EraseID(argID) == false) return false;
	lSet[static_cast<_st>(argID-1)]->DeleteElem();
	return true;
}

fk_Vertex * fk_DataBase::GetVData(int argVID) const
{
	if(vAdmin.ExistID(argVID) == false) return nullptr;
	return vSet[static_cast<_st>(argVID - 1)];
}

fk_Half * fk_DataBase::GetHData(int argHID) const
{
	if(hAdmin.ExistID(argHID) == false) return nullptr;
	return hSet[static_cast<_st>(argHID - 1)];
}

fk_Edge * fk_DataBase::GetEData(int argEID) const
{
	if(eAdmin.ExistID(argEID) == false) return nullptr;
	return eSet[static_cast<_st>(argEID - 1)];
}

fk_Loop * fk_DataBase::GetLData(int argLID) const
{
	if(lAdmin.ExistID(argLID) == false) return nullptr;
	return lSet[static_cast<_st>(argLID - 1)];
}

fk_Vertex * fk_DataBase::GetNextV(fk_Vertex *argV) const
{
	if(argV == nullptr) {
		return GetVData(vAdmin.GetNext(0));
	} else {
		return GetVData(vAdmin.GetNext(argV->getID()));
	}
}

fk_Half * fk_DataBase::GetNextH(fk_Half *argH) const
{
	if(argH == nullptr) {
		return GetHData(hAdmin.GetNext(0));
	} else {
		return GetHData(hAdmin.GetNext(argH->getID()));
	}
}

fk_Edge * fk_DataBase::GetNextE(fk_Edge *argE) const
{
	if(argE == nullptr) {
		return GetEData(eAdmin.GetNext(0));
	} else {
		return GetEData(eAdmin.GetNext(argE->getID()));
	}
}

fk_Loop * fk_DataBase::GetNextL(fk_Loop *argL) const
{
	if(argL == nullptr) {
		return GetLData(lAdmin.GetNext(0));
	} else {
		return GetLData(lAdmin.GetNext(argL->getID()));
	}
}

fk_Vertex * fk_DataBase::GetLastV(void) const
{
	return GetVData(vAdmin.GetMaxID());
}

fk_Half * fk_DataBase::GetLastH(void) const
{
	return GetHData(hAdmin.GetMaxID());
}

fk_Edge * fk_DataBase::GetLastE(void) const
{
	return GetEData(eAdmin.GetMaxID());
}

fk_Loop * fk_DataBase::GetLastL(void) const
{
	return GetLData(lAdmin.GetMaxID());
}

int fk_DataBase::GetVNum(void) const
{
	return vAdmin.GetIDNum();
}

int fk_DataBase::GetHNum(void) const
{
	return hAdmin.GetIDNum();
}

int fk_DataBase::GetENum(void) const
{
	return eAdmin.GetIDNum();
}

int fk_DataBase::GetLNum(void) const
{
	return lAdmin.GetIDNum();
}

void fk_DataBase::VPrint(int argID) const
{
	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < vSet.size(); i++) {
			if(vSet[i]->getID() != FK_UNDEFINED) vSet[i]->Print();
		}
	} else if(!vAdmin.ExistID(argID)) {
		fk_PutError("fk_DataBase", "VPrint", 1,
					"Vertex Admin Error.");
	} else {
		vSet[static_cast<_st>(argID-1)]->Print();
	}

	return;
}


void fk_DataBase::HPrint(int argID) const
{
	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < hSet.size(); i++) {
			if(hSet[i]->getID() != FK_UNDEFINED) hSet[i]->Print();
		}
	} else if(!hAdmin.ExistID(argID)) {
		fk_PutError("fk_DataBase", "HPrint", 1,
					"Half Edge Admin Error.");
	} else {
		hSet[static_cast<_st>(argID-1)]->Print();
	}

	return;
}

void fk_DataBase::EPrint(int argID) const
{
	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < eSet.size(); i++) {
			if(eSet[i]->getID() != FK_UNDEFINED) eSet[i]->Print();
		}
	} else if(!eAdmin.ExistID(argID)) {
		fk_PutError("fk_DataBase", "EPrint", 1,
					"Edge Admin Error.");
	} else {
		eSet[static_cast<_st>(argID-1)]->Print();
	}

	return;
}

void fk_DataBase::LPrint(int argID) const
{
	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < lSet.size(); i++) {
			if(lSet[i]->getID() != FK_UNDEFINED) lSet[i]->Print();
		}
	} else if(!lAdmin.ExistID(argID)) {
		fk_PutError("fk_DataBase", "LPrint", 1,
					"Loop Admin Error.");
	} else {
		lSet[static_cast<_st>(argID-1)]->Print();
	}

	return;
}

void	fk_DataBase::AllPrint(void) const
{
	VPrint(FK_UNDEFINED);
	HPrint(FK_UNDEFINED);
	EPrint(FK_UNDEFINED);
	LPrint(FK_UNDEFINED);

	return;
}

bool	fk_DataBase::VCheck(int argID) const
{
	bool	retBool = true;

	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < vSet.size(); i++) {
			if(vSet[i]->getID() != FK_UNDEFINED) {
				if(vSet[i]->Check() == false) {
					retBool = false;
				}
			}
		}
	} else if(!vAdmin.ExistID(argID)) {
		fk_PutError("fk_DataBase", "VCheck", 1,
					"Vertex Admin Error.");
		retBool = false;
	} else {
		retBool = vSet[static_cast<_st>(argID-1)]->Check();
	}

	return retBool;
}

bool	fk_DataBase::HCheck(int argID) const
{
	bool	retBool = true;

	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < hSet.size(); i++) {
			if(hSet[i]->getID() != FK_UNDEFINED) {
				if(hSet[i]->Check() == false) {
					retBool = false;
				}
			}
		}
	} else if(!hAdmin.ExistID(argID)) {
		fk_PutError("fk_DataBase", "HCheck", 1,
					"Half Edge Admin Error.");
		retBool = false;
	} else {
		retBool = hSet[static_cast<_st>(argID-1)]->Check();
	}

	return retBool;
}

bool	fk_DataBase::ECheck(int argID) const
{
	bool	retBool = true;

	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < eSet.size(); i++) {
			if(eSet[i]->getID() != FK_UNDEFINED) {
				if(eSet[i]->Check() == false) {
					retBool = false;
				}
			}
		}
	} else if(!eAdmin.ExistID(argID)) {
		fk_PutError("fk_DataBase", "ECheck", 1,
					"Edge Admin Error.");
		retBool = false;
	} else {
		retBool = eSet[static_cast<_st>(argID-1)]->Check();
	}

	return retBool;
}

bool fk_DataBase::LCheck(int argID) const
{
	bool	retBool = true;

	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < lSet.size(); i++) {
			if(lSet[i]->getID() != FK_UNDEFINED) {
				if(lSet[i]->Check() == false) {
					retBool = false;
				}
			}
		}
	} else if(!lAdmin.ExistID(argID)) {
		fk_PutError("fk_DataBase", "LCheck", 1,
					"Loop Admin Error");
		retBool = false;
	} else {
		retBool = lSet[static_cast<_st>(argID-1)]->Check();
	}

	return retBool;
}

bool fk_DataBase::AllCheck(void) const
{
	bool	retBool = true;

	if(VCheck() == false) retBool = false;
	if(HCheck() == false) retBool = false;
	if(ECheck() == false) retBool = false;
	if(LCheck() == false) retBool = false;

	return retBool;
}
