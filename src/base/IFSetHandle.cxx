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
#include <FK/IFSetHandle.H>

#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Edge.h>
#include <FK/Loop.h>
#include <FK/DataBase.H>
#include <FK/Reference.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;

void fk_IFSetHandle::Init(void)
{
	SetDataBase(nullptr);
	return;
}


void fk_IFSetHandle::SetDataBase(fk_DataBase *argDB)
{
	DB = argDB;
	edgeCount.clear();
}

fk_DataBase * fk_IFSetHandle::GetDataBase(void)
{
	return DB;
}

bool fk_IFSetHandle::SetIndexFaceSet(vector<fk_Vector> *vData,
									 vector< vector<int> > *lIndex,
									 bool argSolidFlag)
{
	vector<fk_Vector>::iterator		vP;
	vector< vector<int> >::iterator	indexP;
	fk_IFS_EdgeSet					VPair;


	if(DB_Check() == false) return false;

	// 頂点の生成 
	for(vP = vData->begin(); vP != vData->end(); ++vP) {
		DB->GetNewVertex()->SetPosition(*vP);
	}

	// 稜線と面の生成 
	for(indexP = lIndex->begin(); indexP != lIndex->end(); ++indexP) {
		if(MakeLoopEdgeSet(indexP, &VPair, argSolidFlag) == false) {
			DB->AllClear();
			return false;
		}
	}

	if(argSolidFlag == true) {
		if(RefineTopology() == false) {
			DB->AllClear();
			return false;
		}
		if(DB->AllCheck() == false) {
			DB->AllClear();
			return false;
		}
	}

	return true;
}

fk_Edge * fk_IFSetHandle::CheckExistEdge(int vID1, int vID2,
										 fk_IFS_EdgeSet *VPair)
{
	int		tmpID1, tmpID2, mateID;
	auto	range = VPair->equal_range(vID1);

	// 既に稜線が Vt1 と Vt2 の間にあるかどうかの判定 
	for(auto ite = range.first; ite != range.second; ite++) {
		tmpID1 = ite->second->getRightHalf()->getVertex()->getID();
		tmpID2 = ite->second->getLeftHalf()->getVertex()->getID();
		mateID = (tmpID1 == vID1) ? tmpID2 : tmpID1;
		if(mateID == vID2) {
			return ite->second;
		}
	}

	return nullptr;
}
					  
fk_Half * fk_IFSetHandle::MakeNewEdge(int vID1, int vID2,
									  fk_IFS_EdgeSet *VPair)
{
	fk_Edge		*newE;
	fk_Half		*newH1, *newH2;

	// 新位相要素の生成 
	newE = DB->GetNewEdge();
	newH1 = DB->GetNewHalf();
	newH2 = DB->GetNewHalf();

	// 親子関係の設定 
	newE->SetRightHalf(newH1);
	newE->SetLeftHalf(newH2);
	newH1->SetParentEdge(newE);
	newH2->SetParentEdge(newE);

	// 半稜線に対する頂点の設定 
	newH1->SetVertex(DB->GetVData(vID1));
	newH2->SetVertex(DB->GetVData(vID2));

	// 頂点に対する半稜線の設定 
	DB->GetVData(vID1)->SetOneHalf(newH1);
	DB->GetVData(vID2)->SetOneHalf(newH2);

	// VPair へ接続関係を登録 
	VPair->insert(fk_IFS_Entry(vID1, newE));
	VPair->insert(fk_IFS_Entry(vID2, newE));

	return newH1;
}

void fk_IFSetHandle::MakeNewLoop(vector<fk_Half *> *HalfSet, bool argFlg)
{
	vector<fk_Half *>::iterator		halfI;
	fk_Half							*startH, *curH, *prevH, *lastH;
	fk_Loop							*newL;

	lastH = nullptr;
	// 新位相要素の生成 
	if(argFlg == true) {
		newL = DB->GetNewLoop();
	} else {
		newL = nullptr;
	}

	startH = *(HalfSet->begin());
	prevH = startH;

	// ループ上の半稜線に接続関係を設定 
	for(halfI = HalfSet->begin() + 1; halfI != HalfSet->end(); ++halfI) {
		curH = *halfI;
		curH->SetPrevHalf(prevH);
		prevH->SetNextHalf(curH);
		curH->SetParentLoop(newL);
		prevH = curH;
		lastH = curH;
	}

	startH->SetPrevHalf(lastH);
	lastH->SetNextHalf(startH);
	startH->SetParentLoop(newL);
	if(argFlg == true) newL->SetOneHalf(startH);

	return;
}

bool fk_IFSetHandle::MakeLoopEdgeSet(vector< vector<int> >::iterator indexP,
									 fk_IFS_EdgeSet *VPair,
									 bool argSolidFlg)
{
	vector<int>::iterator	polyP;
	int						Vt1ID, Vt2ID;
	vector<fk_Half *>		HalfStock1, HalfStock2;

	HalfStock1.clear();
	HalfStock2.clear();

	for(polyP = indexP->begin(); polyP + 1 != indexP->end(); ++polyP) {
		Vt1ID = *polyP;
		Vt2ID = *(polyP + 1);
		if(DefineNewEH(Vt1ID, Vt2ID, VPair,
					   &HalfStock1, &HalfStock2, argSolidFlg) == false) {
			return false;
		}
	}

	Vt1ID = *(indexP->end() - 1);
	Vt2ID = *(indexP->begin());
	if(DefineNewEH(Vt1ID, Vt2ID, VPair,
				   &HalfStock1, &HalfStock2, argSolidFlg) == false) {
		return false;
	}

	MakeNewLoop(&HalfStock1, true);

	if(argSolidFlg == false) {
		MakeNewLoop(&HalfStock2, false);
	}

	return true;
}

bool fk_IFSetHandle::DefineNewEH(int vID1, int vID2, fk_IFS_EdgeSet *VPair,
								 vector<fk_Half *> *HalfStock1,
								 vector<fk_Half *> *HalfStock2,
								 bool argSolidFlag)
{
	fk_Edge			*existE;
	fk_Half			*newH, *mateH;
	fk_Vector		tmpVec;
	fk_Vertex		*tmpRV, *tmpLV;
	stringstream	ss;
	
	// 頂点が存在するかどうかの判定 
	if(DB->ExistVertex(vID1) == false ||
	   DB->ExistVertex(vID2) == false) {
		fk_PutError("fk_IFSetHandle", "DefineNewEH", 1,
					"No Exist Vertex Error.");
		return false;
	}

	// 頂点間に既に稜線があるかどうかの判定 
	if(argSolidFlag == true) {
		existE = CheckExistEdge(vID1, vID2, VPair);
	} else {
		existE = nullptr;
	}

	if(existE == nullptr) {
		// 新しい稜線の生成 
		newH = MakeNewEdge(vID1, vID2, VPair);
		HalfStock1->push_back(newH);

		if(argSolidFlag == false) {
			mateH = newH->getParentEdge()->getLeftHalf();
			HalfStock2->push_back(mateH);
		}

		edgeCount[newH->getParentEdge()] = 1;
	} else {
		HalfStock1->push_back(existE->getLeftHalf());

		if(argSolidFlag == false) {
			HalfStock2->push_back(existE->getRightHalf());
		}

		edgeCount[existE]++;

		if(edgeCount[existE] > 2) {
			ss << "Edge ID ... " << existE->getID() << endl;

			tmpRV = existE->getRightHalf()->getVertex();
			tmpLV = existE->getLeftHalf()->getVertex();
			ss << "VID ... " << tmpRV->getID() << ", " << tmpLV->getID() << endl;

			tmpVec = tmpRV->getPosition();
			ss << "RPosition ... (";
			ss << tmpVec.x << ", " << tmpVec.y << ", " << tmpVec.z << "), ";

			tmpVec = tmpLV->getPosition();
			ss << "LPosition ... (";
			ss << tmpVec.x << ", " << tmpVec.y << ", " << tmpVec.z << ")" << endl;
			
			fk_PutError("fk_IFSetHandle", "DefineNewEH", 2, ss.str());
			return false;
		}
	}

	return true;
}

bool fk_IFSetHandle::RefineTopology(void)
{
	fk_Half	*CurHalf;

	if(DB_Check() == false) return false;

	for(CurHalf = DB->GetNextH(nullptr);
		CurHalf != nullptr; CurHalf = DB->GetNextH(CurHalf)) {
		if(CurHalf->getNextHalf() == nullptr) {
			if(SearchUndefLoop(CurHalf) == false) return false;
		}
	}

	return true;
}

bool fk_IFSetHandle::SearchUndefLoop(fk_Half *argHalf)
{
	fk_Half		*startH, *curH, *nextH, *tmpH;
	fk_Edge		*parentEdge;
	fk_Half		*mateHalf;
	fk_Vertex	*mateVertex;
	int			halfCount;

	startH = curH = argHalf;
	nextH = nullptr;
	while(nextH != startH) {
		parentEdge = curH->getParentEdge();
		mateHalf = (parentEdge->getRightHalf() == curH) ?
			parentEdge->getLeftHalf() : parentEdge->getRightHalf();
		mateVertex = mateHalf->getVertex();
	
		halfCount = 0;

		for(tmpH = DB->GetNextH(nullptr);
			tmpH != nullptr; tmpH = DB->GetNextH(tmpH)) {
			if(tmpH->getVertex() == mateVertex &&
			   tmpH->getPrevHalf() == nullptr) {
				nextH = tmpH;
				halfCount++;
			}
		}

		if(halfCount != 1) {
			fk_PutError("fk_IFSetHandle", "SearchUndefLoop", 1,
						"Half Edge Count Error.");
			return false;
		}

		curH->SetNextHalf(nextH);
		nextH->SetPrevHalf(curH);
		curH = nextH;
	}

	return true;
}

fk_IFSetHandle::fk_IFSetHandle(fk_DataBase *argDB)
{
	SetDataBase(argDB);

	return;
}

bool fk_IFSetHandle::DB_Check(void)
{
	if(DB == nullptr) return false;
	else return true;
}

int fk_IFSetHandle::GetEdgeCountNum(fk_Edge *argEdge)
{
	unordered_map<fk_Edge *, int>::iterator	p;

	if((p = edgeCount.find(argEdge)) == edgeCount.end()) {
		return 0;
	}

	return edgeCount[argEdge];
}
