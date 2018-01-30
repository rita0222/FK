/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
#include <FK/DataAccess.h>
#include <FK/DataBase.H>
#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Edge.h>
#include <FK/Loop.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_DataAccess::fk_DataAccess(void)
{
	SetDataBase(nullptr);

	return;
}

fk_DataAccess::~fk_DataAccess()
{
	return;
}

void fk_DataAccess::SetDataBase(fk_DataBase *argOp)
{
	ope_DB = argOp;
	return;
}

bool fk_DataAccess::checkDB(void) const
{
	if(ope_DB == nullptr) return false;
	else return true;
}

bool fk_DataAccess::checkTopology(void)
{
	return ope_DB->AllCheck();
}

void fk_DataAccess::printTopology(void)
{
	ope_DB->AllPrint();
	return;
}

fk_DataBase * fk_DataAccess::GetDB(void)
{
	return ope_DB;
}

fk_Vertex *	fk_DataAccess::GetNewVertexObj_(void)
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNewVertex();
}

fk_Vertex * fk_DataAccess::GetNewVertexObj_(int argID)
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNewVertex(argID);
}

fk_Half * fk_DataAccess::GetNewHalfObj_(void)
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNewHalf();
}

fk_Half * fk_DataAccess::GetNewHalfObj_(int argID)
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNewHalf(argID);
}

fk_Edge * fk_DataAccess::GetNewEdgeObj_(void)
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNewEdge();
}

fk_Edge * fk_DataAccess::GetNewEdgeObj_(int argID)
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNewEdge(argID);
}

fk_Loop * fk_DataAccess::GetNewLoopObj_(void)
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNewLoop();
}

fk_Loop * fk_DataAccess::GetNewLoopObj_(int argID)
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNewLoop(argID);
}

bool fk_DataAccess::DeleteVertexObj_(fk_Vertex *argV)
{
	if(checkDB() == false) return false;
	return ope_DB->DeleteVertex(argV->getID());
}

bool fk_DataAccess::DeleteHalfObj_(fk_Half *argH)
{
	if(checkDB() == false) return false;
	return ope_DB->DeleteHalf(argH->getID());
}

bool fk_DataAccess::DeleteEdgeObj_(fk_Edge *argE)
{
	if(checkDB() == false) return false;
	return ope_DB->DeleteEdge(argE->getID());
}

bool fk_DataAccess::DeleteLoopObj_(fk_Loop *argL)
{
	if(checkDB() == false) return false;
	return ope_DB->DeleteLoop(argL->getID());
}

void fk_DataAccess::AllDBClear_(void)
{
	if(checkDB() == true) {
		ope_DB->AllClear();
	}
	return;
}

bool fk_DataAccess::existVertex(fk_Vertex *argV) const
{
	if(checkDB() == false) return false;
	return ope_DB->ExistVertex(argV);
}

bool fk_DataAccess::existVertex(int argID) const
{
	if(checkDB() == false) return false;
	return ope_DB->ExistVertex(argID);
}

bool fk_DataAccess::existHalf(fk_Half *argH) const
{
	if(checkDB() == false) return false;
	return ope_DB->ExistHalf(argH);
}

bool fk_DataAccess::existHalf(int argID) const
{
	if(checkDB() == false) return false;
	return ope_DB->ExistHalf(argID);
}

bool fk_DataAccess::existEdge(fk_Edge *argE) const
{
	if(checkDB() == false) return false;
	return ope_DB->ExistEdge(argE);
}

bool fk_DataAccess::existEdge(int argID) const
{
	if(checkDB() == false) return false;
	return ope_DB->ExistEdge(argID);
}

bool fk_DataAccess::existLoop(fk_Loop *argL) const
{
	if(checkDB() == false) return false;
	return ope_DB->ExistLoop(argL);
}

bool fk_DataAccess::existLoop(int argID) const
{
	if(checkDB() == false) return false;
	return ope_DB->ExistLoop(argID);
}

fk_Vertex * fk_DataAccess::getVData(int argID) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetVData(argID);
}

fk_Half * fk_DataAccess::getHData(int argID) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetHData(argID);
}

fk_Edge * fk_DataAccess::getEData(int argID) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetEData(argID);
}

fk_Loop * fk_DataAccess::getLData(int argID) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetLData(argID);
}

fk_Vertex * fk_DataAccess::getNextV(fk_Vertex *argV) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNextV(argV);
}

fk_Half * fk_DataAccess::getNextH(fk_Half *argH) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNextH(argH);
}

fk_Edge * fk_DataAccess::getNextE(fk_Edge *argE) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNextE(argE);
}

fk_Loop * fk_DataAccess::getNextL(fk_Loop *argL) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetNextL(argL);
}

fk_Vertex * fk_DataAccess::getLastV(void) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetLastV();
}
	
fk_Half * fk_DataAccess::getLastH(void) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetLastH();
}

fk_Edge * fk_DataAccess::getLastE(void) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetLastE();
}

fk_Loop * fk_DataAccess::getLastL(void) const
{
	if(checkDB() == false) return nullptr;
	return ope_DB->GetLastL();
}

int fk_DataAccess::getVNum(void) const
{
	if(checkDB() == false) return -1;
	return ope_DB->GetVNum();
}

int fk_DataAccess::getHNum(void) const
{
	if(checkDB() == false) return -1;
	return ope_DB->GetHNum();
}

int fk_DataAccess::getENum(void) const
{
	if(checkDB() == false) return -1;
	return ope_DB->GetENum();
}

int fk_DataAccess::getLNum(void) const
{
	if(checkDB() == false) return -1;
	return ope_DB->GetLNum();
}

void fk_DataAccess::getVertexList(list<fk_Vertex *> *argList)
{
	fk_Vertex		*v;

	if(argList == nullptr) return;
	argList->clear();

	for(v = getNextV(nullptr); v != nullptr; v = getNextV(v)) {
		argList->push_back(v);
	}
	return;
}

void fk_DataAccess::getHalfList(list<fk_Half *> *argList)
{
	fk_Half		*h;

	if(argList == nullptr) return;
	argList->clear();

	for(h = getNextH(nullptr); h != nullptr; h = getNextH(h)) {
		argList->push_back(h);
	}
	return;
}

void fk_DataAccess::getEdgeList(list<fk_Edge *> *argList)
{
	fk_Edge		*e;

	if(argList == nullptr) return;
	argList->clear();

	for(e = getNextE(nullptr); e != nullptr; e = getNextE(e)) {
		argList->push_back(e);
	}
	return;
}

void fk_DataAccess::getLoopList(list<fk_Loop *> *argList)
{
	fk_Loop		*l;

	if(argList == nullptr) return;
	argList->clear();

	for(l = getNextL(nullptr); l != nullptr; l = getNextL(l)) {
		argList->push_back(l);
	}
	return;
}
