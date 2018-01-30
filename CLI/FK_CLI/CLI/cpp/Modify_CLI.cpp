#include "Modify_CLI.h"

namespace FK_CLI {

	using namespace std;
	using namespace System::Collections::Generic;
	
	::fk_Modify * fk_Modify::GetP(void)
	{
		return (::fk_Modify *)(pBase);
	}

	fk_Modify::fk_Modify(bool argNewFlg) : fk_Operation(false)
	{
	}

	fk_Modify::~fk_Modify()
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

	fk_Loop^ fk_Modify::MakePolygon(IEnumerable<fk_Vector^>^ argArray, bool argOpenFlg, bool argInitFlg)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray;

		for each (fk_Vector^ pos in argArray) {
			vArray.push_back(pos);
		}

		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->makePolygon(&vArray, argOpenFlg, argInitFlg);
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Modify::MakePolygon(IEnumerable<fk_Vector^>^ argArray, bool argOpenFlg)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray;

		for each (fk_Vector^ pos in argArray) {
			vArray.push_back(pos);
		}
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->makePolygon(&vArray, argOpenFlg);
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Modify::PushPolygon(IEnumerable<fk_Vector^>^ argArray, bool argOpenFlg)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray;

		for each (fk_Vector^ pos in argArray) {
			vArray.push_back(pos);
		}
		fk_Loop^ L = gcnew fk_Loop(false);
		L->pBase = GetP()->pushPolygon(&vArray, argOpenFlg);
		L->dFlg = false;
		return L;
	}

	fk_Loop^ fk_Modify::PushPolygon(IEnumerable<fk_Vector^>^ argArray)
	{
		if(!argArray) return nullptr;
		vector<::fk_Vector> vArray;

		for each (fk_Vector^ pos in argArray) {
			vArray.push_back(pos);
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

	void fk_Modify::MakePoint(IEnumerable<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray;

		for each (fk_Vector^ pos in argArray) {
			vArray.push_back(pos);
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

	void fk_Modify::MakeLines(IEnumerable<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray;
		
		for each (fk_Vector^ pos in argArray) {
			vArray.push_back(pos);
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
/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
