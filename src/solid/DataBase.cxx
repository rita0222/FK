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
using namespace FK;

fk_DataBase::Member::Member(void)
{
	vAdmin.Init(1);
	hAdmin.Init(1);
	eAdmin.Init(1);
	lAdmin.Init(1);
}

fk_DataBase::fk_DataBase(void)
{
	AllClear();
}

fk_DataBase::~fk_DataBase()
{
	return;
}

void fk_DataBase::AllClear(void)
{
	_m->vAdmin.Init(1);
	_m->hAdmin.Init(1);
	_m->eAdmin.Init(1);
	_m->lAdmin.Init(1);

	while(!_m->vSet.empty()) {
		_m->vSet.pop_back();
	}

	while(!_m->hSet.empty()) {
		_m->hSet.pop_back();
	}

	while(!_m->eSet.empty()) {
		_m->eSet.pop_back();
	}

	while(!_m->lSet.empty()) {
		_m->lSet.pop_back();
	}

	return;
}

void fk_DataBase::CloneData(fk_DataBase *argDB)
{
	if(argDB == this || argDB == nullptr) return;

	ResizeData(argDB);

	_m->vAdmin.CloneData(&argDB->_m->vAdmin);
	_m->hAdmin.CloneData(&argDB->_m->hAdmin);
	_m->eAdmin.CloneData(&argDB->_m->eAdmin);
	_m->lAdmin.CloneData(&argDB->_m->lAdmin);

	VSetClone(&argDB->_m->vSet);
	HSetClone(&argDB->_m->hSet);
	ESetClone(&argDB->_m->eSet);
	LSetClone(&argDB->_m->lSet);

	return;
}

void fk_DataBase::ResizeData(fk_DataBase *argDB)
{
	ResizeData(int(argDB->_m->vSet.size()),
			   int(argDB->_m->hSet.size()),
			   int(argDB->_m->eSet.size()),
			   int(argDB->_m->lSet.size()));

	return;
}

void fk_DataBase::ResizeData(int argVNum, int argHNum,
							 int argENum, int argLNum)
{
	_st		i, orgSize;

	orgSize = _m->vSet.size();
	_m->vSet.resize(_st(argVNum));
	for(i = orgSize; i < _st(argVNum); ++i) _m->vSet[i].Init(this, int(i+1));
	for(i = _st(argVNum); i < orgSize; ++i) _m->vSet.pop_back();

	orgSize = _m->hSet.size();
	_m->hSet.resize(_st(argHNum));
	for(i = orgSize; i < _st(argHNum); ++i) _m->hSet[i].Init(this, int(i+1));
	for(i = _st(argHNum); i < orgSize; ++i) _m->hSet.pop_back();

	orgSize = _m->eSet.size();
	_m->eSet.resize(_st(argENum));
	for(i = orgSize; i < _st(argENum); ++i) _m->eSet[i].Init(this, int(i+1));
	for(i = _st(argENum); i < orgSize; ++i) _m->eSet.pop_back();
		
	orgSize = _m->lSet.size();
	_m->lSet.resize(_st(argLNum));
	for(i = orgSize; i < _st(argLNum); ++i) _m->lSet[i].Init(this, int(i+1));
	for(i = _st(argLNum); i < orgSize; ++i) _m->lSet.pop_back();

	return;
}

void fk_DataBase::VSetClone(vector<fk_Vertex> *argVSet)
{
	_st			i;
	fk_Vertex	*orgV, *newV;

	for(i = 0; i < _m->vSet.size(); ++i) {
		newV = &_m->vSet[i];
		orgV = &argVSet->at(i);

		if(newV->CloneElem(orgV) == false) {
			continue;
		}

		newV->position = orgV->position;
		newV->normal = orgV->normal;
		newV->normCalcFlag = orgV->normCalcFlag;
		newV->normFailFlag = orgV->normFailFlag;
		if(orgV->oneHalf == FK_UNDEFINED) {
			newV->oneHalf = FK_UNDEFINED;
		} else {
			newV->oneHalf = orgV->oneHalf;
		}
	}

	return;
}

void fk_DataBase::HSetClone(vector<fk_Half> *argHSet)
{
	_st			i;
	fk_Half		*orgH, *newH;

	for(i = 0; i < _m->hSet.size(); ++i) {
		orgH = &argHSet->at(i);
		newH = &_m->hSet[i];

		if(newH->CloneElem(orgH) == false) {
			continue;
		}

		newH->vertex = orgH->vertex;
		newH->nextHalf = orgH->nextHalf;
		newH->prevHalf = orgH->prevHalf;
		newH->parentEdge = orgH->parentEdge;
		if(orgH->parentLoop == FK_UNDEFINED) {
			newH->parentLoop = FK_UNDEFINED;
		} else {
			newH->parentLoop = orgH->parentLoop;
		}
	}

	return;
}

void fk_DataBase::ESetClone(vector<fk_Edge> *argESet)
{
	_st			i;
	fk_Edge		*orgE, *newE;

	for(i = 0; i < _m->eSet.size(); ++i) {
		orgE = &argESet->at(i);
		newE = &_m->eSet[i];

		if(newE->CloneElem(orgE) == false) continue;

		newE->_m->rightHalf = orgE->_m->rightHalf;
		newE->_m->leftHalf = orgE->_m->leftHalf;
	}

	return;
}

void fk_DataBase::LSetClone(vector<fk_Loop> *argLSet)
{
	_st			i;
	fk_Loop		*orgL, *newL;

	for(i = 0; i < _m->lSet.size(); ++i) {
		orgL = &argLSet->at(i);
		newL = &_m->lSet[i];

		if(newL->CloneElem(orgL) == false) continue;

		newL->oneHalf = orgL->oneHalf;
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
	int newID = _m->vAdmin.CreateID();
	if(int(_m->vSet.size())== newID - 1) {
		_m->vSet.resize(_m->vSet.size()+1);
		_m->vSet.back().Init(this, newID);
	} else {
		_m->vSet[_st(newID)-1].Init(this, newID);
	}

	return &_m->vSet[_st(newID)-1];
}

fk_Vertex * fk_DataBase::GetNewVertex(int argID)
{
	if(_m->vAdmin.CreateID(argID) == false) {
		return nullptr;
	}

	if(int(_m->vSet.size()) == argID - 1) {
		_m->vSet.resize(_m->vSet.size()+1);
		_m->vSet.back().Init(this, argID);
	} else {
		_m->vSet[_st(argID)-1].Init(this, argID);
	}

	return &_m->vSet[_st(argID)-1];
}

fk_Half * fk_DataBase::GetNewHalf(void)
{
	int newID = _m->hAdmin.CreateID();

	if(int(_m->hSet.size()) == newID - 1) {
		_m->hSet.resize(_m->hSet.size()+1);
		_m->hSet.back().Init(this, newID);
	} else {
		_m->hSet[_st(newID)-1].Init(this, newID);
	}

	return &_m->hSet[_st(newID)-1];
}

fk_Half * fk_DataBase::GetNewHalf(int argID)
{
	if(_m->hAdmin.CreateID(argID) == false) {
		return nullptr;
	}

	if(int(_m->hSet.size()) == argID - 1) {
		_m->hSet.resize(_m->hSet.size()+1);
		_m->hSet.back().Init(this, argID);
	} else {
		_m->hSet[_st(argID)-1].Init(this, argID);
	}

	return &_m->hSet[_st(argID)-1];
}

fk_Edge * fk_DataBase::GetNewEdge(void)
{
	int newID = _m->eAdmin.CreateID();

	if(int(_m->eSet.size()) == newID - 1) {
		_m->eSet.resize(_m->eSet.size()+1);
		_m->eSet.back().Init(this, newID);
	} else {
		_m->eSet[_st(newID)-1].Init(this, newID);
	}

	return &_m->eSet[_st(newID)-1];
}

fk_Edge * fk_DataBase::GetNewEdge(int argID)
{
	if(_m->eAdmin.CreateID(argID) == false) {
		return nullptr;
	}

	if(int(_m->eSet.size()) == argID - 1) {
		_m->eSet.resize(_m->eSet.size()+1);
		_m->eSet.back().Init(this, argID);
	} else {
		_m->eSet[_st(argID)-1].Init(this, argID);
	}

	return &_m->eSet[_st(argID)-1];
}

fk_Loop * fk_DataBase::GetNewLoop(void)
{
	int newID = _m->lAdmin.CreateID();
	if(int(_m->lSet.size()) == newID - 1) {
		_m->lSet.resize(_m->lSet.size()+1);
		_m->lSet.back().Init(this, newID);
	} else {
		_m->lSet[_st(newID)-1].Init(this, newID);
	}

	return &_m->lSet[_st(newID)-1];
}

fk_Loop * fk_DataBase::GetNewLoop(int argID)
{
	if(_m->lAdmin.CreateID(argID) == false) {
		return nullptr;
	}

	if(int(_m->lSet.size()) == argID - 1) {
		_m->lSet.resize(_m->lSet.size()+1);
		_m->lSet.back().Init(this, argID);
	} else {
		_m->lSet[_st(argID)-1].Init(this, argID);
	}

	return &_m->lSet[_st(argID)-1];
}

bool fk_DataBase::ExistVertex(fk_Vertex *argVx) const
{
	if(argVx == nullptr) return false;
	if(ExistVertex(argVx->getID()) == false) return false;
	if(&_m->vSet[_st(argVx->getID()) - 1] != argVx) return false;
	return true;
}

bool fk_DataBase::ExistVertex(int argID) const
{
	return _m->vAdmin.ExistID(argID);
}

bool fk_DataBase::ExistHalf(fk_Half *argHf) const
{
	if(argHf == nullptr) return false;
	if(ExistHalf(argHf->getID()) == false) return false;
	if(&_m->hSet[_st(argHf->getID()) - 1] != argHf) return false;
	return true;
}

bool fk_DataBase::ExistHalf(int argID) const
{
	return _m->hAdmin.ExistID(argID);
}

bool fk_DataBase::ExistEdge(fk_Edge *argEd) const
{
	if(argEd == nullptr) return false;
	if(ExistEdge(argEd->getID()) == false) return false;
	if(&_m->eSet[_st(argEd->getID()) - 1] != argEd) return false;
	return true;
}

bool fk_DataBase::ExistEdge(int argID) const
{
	return _m->eAdmin.ExistID(argID);
}

bool fk_DataBase::ExistLoop(fk_Loop *argLp) const
{
	if(argLp == nullptr) return false;
	if(ExistLoop(argLp->getID()) == false) return false;
	if(&_m->lSet[_st(argLp->getID()) - 1] != argLp) return false;
	return true;
}

bool fk_DataBase::ExistLoop(int argID) const
{
	return _m->lAdmin.ExistID(argID);
}

bool fk_DataBase::DeleteVertex(int argID)
{
	if(_m->vAdmin.EraseID(argID) == false) return false;
	_m->vSet[_st(argID)-1].DeleteElem();
	return true;
}

bool fk_DataBase::DeleteHalf(int argID)
{
	if(_m->hAdmin.EraseID(argID) == false) return false;
	_m->hSet[_st(argID)-1].DeleteElem();
	return true;
}

bool fk_DataBase::DeleteEdge(int argID)
{
	if(_m->eAdmin.EraseID(argID) == false) return false;
	_m->eSet[_st(argID)-1].DeleteElem();
	return true;
}

bool fk_DataBase::DeleteLoop(int argID)
{
	if(_m->lAdmin.EraseID(argID) == false) return false;
	_m->lSet[_st(argID)-1].DeleteElem();
	return true;
}

fk_Vertex * fk_DataBase::GetVData(int argVID)
{
	if(_m->vAdmin.ExistID(argVID) == false) return nullptr;
	return &_m->vSet[_st(argVID) - 1];
}

fk_Half * fk_DataBase::GetHData(int argHID)
{
	if(_m->hAdmin.ExistID(argHID) == false) return nullptr;
	return &_m->hSet[_st(argHID) - 1];
}

fk_Edge * fk_DataBase::GetEData(int argEID)
{
	if(_m->eAdmin.ExistID(argEID) == false) return nullptr;
	return &_m->eSet[_st(argEID) - 1];
}

fk_Loop * fk_DataBase::GetLData(int argLID)
{
	if(_m->lAdmin.ExistID(argLID) == false) return nullptr;
	return &_m->lSet[_st(argLID) - 1];
}

fk_Vertex * fk_DataBase::GetNextV(fk_Vertex *argV)
{
	if(argV == nullptr) {
		return GetVData(_m->vAdmin.GetNext(0));
	} else {
		return GetVData(_m->vAdmin.GetNext(argV->getID()));
	}
}

fk_Half * fk_DataBase::GetNextH(fk_Half *argH)
{
	if(argH == nullptr) {
		return GetHData(_m->hAdmin.GetNext(0));
	} else {
		return GetHData(_m->hAdmin.GetNext(argH->getID()));
	}
}

fk_Edge * fk_DataBase::GetNextE(fk_Edge *argE)
{
	if(argE == nullptr) {
		return GetEData(_m->eAdmin.GetNext(0));
	} else {
		return GetEData(_m->eAdmin.GetNext(argE->getID()));
	}
}

fk_Loop * fk_DataBase::GetNextL(fk_Loop *argL)
{
	if(argL == nullptr) {
		return GetLData(_m->lAdmin.GetNext(0));
	} else {
		return GetLData(_m->lAdmin.GetNext(argL->getID()));
	}
}

fk_Vertex * fk_DataBase::GetLastV(void)
{
	return GetVData(_m->vAdmin.GetMaxID());
}

fk_Half * fk_DataBase::GetLastH(void)
{
	return GetHData(_m->hAdmin.GetMaxID());
}

fk_Edge * fk_DataBase::GetLastE(void)
{
	return GetEData(_m->eAdmin.GetMaxID());
}

fk_Loop * fk_DataBase::GetLastL(void)
{
	return GetLData(_m->lAdmin.GetMaxID());
}

int fk_DataBase::GetVNum(void) const
{
	return _m->vAdmin.GetIDNum();
}

int fk_DataBase::GetHNum(void) const
{
	return _m->hAdmin.GetIDNum();
}

int fk_DataBase::GetENum(void) const
{
	return _m->eAdmin.GetIDNum();
}

int fk_DataBase::GetLNum(void) const
{
	return _m->lAdmin.GetIDNum();
}

void fk_DataBase::VPrint(int argID) const
{
	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < _m->vSet.size(); ++i) {
			if(_m->vSet[i].getID() != FK_UNDEFINED) _m->vSet[i].Print();
		}
	} else if(!_m->vAdmin.ExistID(argID)) {
		Error::Put("fk_DataBase", "VPrint", 1, "Vertex Admin Error.");
	} else {
		_m->vSet[_st(argID)-1].Print();
	}

	return;
}


void fk_DataBase::HPrint(int argID) const
{
	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < _m->hSet.size(); ++i) {
			if(_m->hSet[i].getID() != FK_UNDEFINED) _m->hSet[i].Print();
		}
	} else if(!_m->hAdmin.ExistID(argID)) {
		Error::Put("fk_DataBase", "HPrint", 1, "Half Edge Admin Error.");
	} else {
		_m->hSet[_st(argID)-1].Print();
	}

	return;
}

void fk_DataBase::EPrint(int argID) const
{
	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < _m->eSet.size(); ++i) {
			if(_m->eSet[i].getID() != FK_UNDEFINED) _m->eSet[i].Print();
		}
	} else if(!_m->eAdmin.ExistID(argID)) {
		Error::Put("fk_DataBase", "EPrint", 1, "Edge Admin Error.");
	} else {
		_m->eSet[_st(argID)-1].Print();
	}

	return;
}

void fk_DataBase::LPrint(int argID) const
{
	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < _m->lSet.size(); ++i) {
			if(_m->lSet[i].getID() != FK_UNDEFINED) _m->lSet[i].Print();
		}
	} else if(!_m->lAdmin.ExistID(argID)) {
		Error::Put("fk_DataBase", "LPrint", 1, "Loop Admin Error.");
	} else {
		_m->lSet[_st(argID)-1].Print();
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
		for(_st i = 0; i < _m->vSet.size(); ++i) {
			if(_m->vSet[i].getID() != FK_UNDEFINED) {
				if(_m->vSet[i].Check() == false) {
					retBool = false;
				}
			}
		}
	} else if(!_m->vAdmin.ExistID(argID)) {
		Error::Put("fk_DataBase", "VCheck", 1, "Vertex Admin Error.");
		retBool = false;
	} else {
		retBool = _m->vSet[_st(argID)-1].Check();
	}

	return retBool;
}

bool	fk_DataBase::HCheck(int argID) const
{
	bool	retBool = true;

	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < _m->hSet.size(); ++i) {
			if(_m->hSet[i].getID() != FK_UNDEFINED) {
				if(_m->hSet[i].Check() == false) {
					retBool = false;
				}
			}
		}
	} else if(!_m->hAdmin.ExistID(argID)) {
		Error::Put("fk_DataBase", "HCheck", 1, "Half Edge Admin Error.");
		retBool = false;
	} else {
		retBool = _m->hSet[_st(argID)-1].Check();
	}

	return retBool;
}

bool	fk_DataBase::ECheck(int argID) const
{
	bool	retBool = true;

	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < _m->eSet.size(); ++i) {
			if(_m->eSet[i].getID() != FK_UNDEFINED) {
				if(_m->eSet[i].Check() == false) {
					retBool = false;
				}
			}
		}
	} else if(!_m->eAdmin.ExistID(argID)) {
		Error::Put("fk_DataBase", "ECheck", 1, "Edge Admin Error.");
		retBool = false;
	} else {
		retBool = _m->eSet[_st(argID)-1].Check();
	}

	return retBool;
}

bool fk_DataBase::LCheck(int argID) const
{
	bool	retBool = true;

	if(argID == FK_UNDEFINED) {
		for(_st i = 0; i < _m->lSet.size(); ++i) {
			if(_m->lSet[i].getID() != FK_UNDEFINED) {
				if(_m->lSet[i].Check() == false) {
					retBool = false;
				}
			}
		}
	} else if(!_m->lAdmin.ExistID(argID)) {
		Error::Put("fk_DataBase", "LCheck", 1, "Loop Admin Error");
		retBool = false;
	} else {
		retBool = _m->lSet[_st(argID)-1].Check();
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

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
