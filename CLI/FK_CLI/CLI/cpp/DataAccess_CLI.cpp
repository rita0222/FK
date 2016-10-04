#include "DataAccess_CLI.h"
#include <list>

namespace FK_CLI {

	using namespace std;

	::fk_DataAccess * fk_DataAccess::GetP(void)
	{
		return (::fk_DataAccess *)(pBase);
	}

	fk_DataAccess::fk_DataAccess(bool argNewFlg) : fk_Reference(false)
	{
	}

	fk_DataAccess::~fk_DataAccess()
	{
		this->!fk_DataAccess();
	}

	fk_DataAccess::!fk_DataAccess()
	{
	}

	int fk_DataAccess::VNum::get()
	{
		return GetP()->getVNum();
	}


	int fk_DataAccess::HNum::get()
	{
		return GetP()->getHNum();
	}

	int fk_DataAccess::ENum::get()
	{
		return GetP()->getENum();
	}

	int fk_DataAccess::LNum::get()
	{
		return GetP()->getLNum();
	}

	bool fk_DataAccess::CheckDB(void)
	{
		return GetP()->checkDB();
	}

	bool fk_DataAccess::CheckTopology(void)
	{
		return GetP()->checkTopology();
	}

	bool fk_DataAccess::ExistVertex(fk_Vertex^ argV)
	{
		if(!argV) return false;
		return GetP()->existVertex(argV->GetP());
	}

	bool fk_DataAccess::ExistVertex(int argID)
	{
		return GetP()->existVertex(argID);
	}

	bool fk_DataAccess::ExistHalf(fk_Half^ argH)
	{
		if(!argH) return false;
		return GetP()->existHalf(argH->GetP());
	}

	bool fk_DataAccess::ExistHalf(int argID)
	{
		return GetP()->existHalf(argID);
	}

	bool fk_DataAccess::ExistEdge(fk_Edge^ argE)
	{
		if(!argE) return false;
		return GetP()->existEdge(argE->GetP());
	}

	bool fk_DataAccess::ExistEdge(int argID)
	{
		return GetP()->existEdge(argID);
	}

	bool fk_DataAccess::ExistLoop(fk_Loop^ argL)
	{
		if(!argL) return false;
		return GetP()->existLoop(argL->GetP());
	}

	bool fk_DataAccess::ExistLoop(int argID)
	{
		return GetP()->existLoop(argID);
	}

	fk_Vertex^ fk_DataAccess::GetVData(int argID)
	{
		::fk_Vertex *pV = GetP()->getVData(argID);
		if(pV == nullptr) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = pV;
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_DataAccess::GetHData(int argID)
	{
		::fk_Half *pH = GetP()->getHData(argID);
		if(pH == nullptr) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = pH;
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_DataAccess::GetEData(int argID)
	{
		::fk_Edge *pE = GetP()->getEData(argID);
		if(pE == nullptr) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	fk_Loop^ fk_DataAccess::GetLData(int argID)
	{
		::fk_Loop *pL = GetP()->getLData(argID);
		if(pL == nullptr) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = pL;
		L->dFlg = false;
		return L;
	}

	fk_Vertex^ fk_DataAccess::GetNextV(fk_Vertex^ argV)
	{
		::fk_Vertex *pV = (!argV) ? GetP()->getNextV(nullptr) : GetP()->getNextV(argV->GetP());
		if(pV == nullptr) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = pV;
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_DataAccess::GetNextH(fk_Half^ argH)
	{
		::fk_Half *pH = (!argH) ? GetP()->getNextH(nullptr) : GetP()->getNextH(argH->GetP());
		if(pH == nullptr) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = pH;
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_DataAccess::GetNextE(fk_Edge^ argE)
	{
		::fk_Edge *pE = (!argE) ? GetP()->getNextE(nullptr) : GetP()->getNextE(argE->GetP());
		if(pE == nullptr) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	fk_Loop^ fk_DataAccess::GetNextL(fk_Loop^ argL)
	{
		::fk_Loop *pL = (!argL) ? GetP()->getNextL(nullptr) : GetP()->getNextL(argL->GetP());
		if(pL == nullptr) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = pL;
		L->dFlg = false;
		return L;
	}

	fk_Vertex^ fk_DataAccess::GetLastV(void)
	{
		::fk_Vertex *pV = GetP()->getLastV();
		if(pV == nullptr) return nullptr;
		fk_Vertex^ V = gcnew fk_Vertex(false);
		V->pBase = pV;
		V->dFlg = false;
		return V;
	}

	fk_Half^ fk_DataAccess::GetLastH(void)
	{
		::fk_Half *pH = GetP()->getLastH();
		if(pH == nullptr) return nullptr;
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = pH;
		H->dFlg = false;
		return H;
	}

	fk_Edge^ fk_DataAccess::GetLastE(void)
	{
		::fk_Edge *pE = GetP()->getLastE();
		if(pE == nullptr) return nullptr;
		fk_Edge^ E = gcnew fk_Edge(false);
		E->pBase = pE;
		E->dFlg = false;
		return E;
	}

	fk_Loop^ fk_DataAccess::GetLastL(void)
	{
		::fk_Loop *pL = GetP()->getLastL();
		if(pL == nullptr) return nullptr;
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = pL;
		L->dFlg = false;
		return L;
	}

	cli::array<fk_Vertex^>^ fk_DataAccess::GetVertexArray(void)
	{
		list<::fk_Vertex *> vList;
		GetP()->getVertexList(&vList);
		cli::array<fk_Vertex^>^ A = gcnew cli::array<fk_Vertex^>(vList.size());
		int count = 0;
		for(auto v : vList) {
			A[count]->pBase = v;
			A[count]->dFlg = false;
			count++;
		}
		return A;
	}

	cli::array<fk_Half^>^ fk_DataAccess::GetHalfArray(void)
	{
		list<::fk_Half *> hList;
		GetP()->getHalfList(&hList);
		cli::array<fk_Half^>^ A = gcnew cli::array<fk_Half^>(hList.size());
		int count = 0;
		for(auto h : hList) {
			A[count]->pBase = h;
			A[count]->dFlg = false;
			count++;
		}
		return A;
	}

	cli::array<fk_Edge^>^ fk_DataAccess::GetEdgeArray(void)
	{
		list<::fk_Edge *> eList;
		GetP()->getEdgeList(&eList);
		cli::array<fk_Edge^>^ A = gcnew cli::array<fk_Edge^>(eList.size());
		int count = 0;
		for(auto e : eList) {
			A[count]->pBase = e;
			A[count]->dFlg = false;
			count++;
		}
		return A;
	}

	cli::array<fk_Loop^>^ fk_DataAccess::GetLoopArray(void)
	{
		list<::fk_Loop *> lList;
		GetP()->getLoopList(&lList);
		cli::array<fk_Loop^>^ A = gcnew cli::array<fk_Loop^>(lList.size());
		int count = 0;
		for(auto l : lList) {
			A[count]->pBase = l;
			A[count]->dFlg = false;
			count++;
		}
		return A;
	}

}

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
