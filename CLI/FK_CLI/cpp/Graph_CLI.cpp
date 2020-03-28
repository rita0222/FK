#include "Graph_CLI.h"

namespace FK_CLI {

	using namespace std;
	using namespace System::Collections::Generic;

    fk_CostStatus fk_Graph::getCS(::FK::fk_CostStatus argS)
    {
        switch (argS) {
        case ::FK::fk_CostStatus::CONTINUE:
			return fk_CostStatus::CONTINUE;

		case ::FK::fk_CostStatus::FINISH:
            return fk_CostStatus::FINISH;

        default:
            break;
        }
        return fk_CostStatus::ERROR;
    }

	::FK::fk_Graph * fk_Graph::GetP(void)
	{
		return (::FK::fk_Graph *)(pBase);
	}

	fk_Graph::fk_Graph(unsigned int argNum) : fk_Shape(false)
	{
		pBase = new ::FK::fk_Graph(argNum);
	}

	fk_Graph::~fk_Graph()
	{
		this->!fk_Graph();
	}

	fk_Graph::!fk_Graph()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

    unsigned int fk_Graph::NodeSize::get()
    {
        return GetP()->getNodeSize();
    }

    unsigned int fk_Graph::MaxEdgeID::get()
    {
        return GetP()->getMaxEdgeID();
    }

    fk_GraphNode^ fk_Graph::GetNode(unsigned int argID)
    {
        return gcnew fk_GraphNode(GetP()->getNode(argID));
    }

    fk_GraphEdge^ fk_Graph::GetEdge(unsigned int argID)
    {
        return gcnew fk_GraphEdge(GetP()->getEdge(argID));
    }

    bool fk_Graph::IsConnect(fk_GraphNode^ argV1, fk_GraphNode^ argV2)
    {
        if (!argV1 || !argV2) return false;
        return GetP()->isConnect(argV1->GetP(), argV2->GetP());
    }

    fk_GraphEdge^ fk_Graph::MakeEdge(bool argMode, fk_GraphNode^ argV1, fk_GraphNode^ argV2)
    {
        if (!argV1 || !argV2) return nullptr;
        return gcnew fk_GraphEdge(GetP()->makeEdge(argMode, argV1->GetP(), argV2->GetP()));
    }

    bool fk_Graph::DeleteEdge(fk_GraphEdge^ argE)
    {
        if (!argE) return false;
        return GetP()->deleteEdge(argE->GetP());
    }

    bool fk_Graph::MakeCostTable(unsigned int argID, fk_CostType argType)
    {
        return GetP()->makeCostTable(argID, fk_GraphEdge::getCT(argType));
    }

    bool fk_Graph::SetCostDirection(unsigned int argID, fk_CostDirection argD)
    {
        return GetP()->setCostDirection(argID, fk_GraphEdge::getCD(argD));
    }

    bool fk_Graph::SetEdgeCostID(unsigned int argTableID, unsigned int argCostID)
    {
        return GetP()->setEdgeCostID(argTableID, argCostID);
    }

    unsigned int fk_Graph::GetNodeCostID(unsigned int argID)
    {
        return GetP()->getNodeCostID(argID);
    }

    void fk_Graph::SetStart(unsigned int argID, fk_GraphNode^ argNode)
    {
        if (!argNode) return;
        GetP()->setStart(argID, argNode->GetP());
    }

    void fk_Graph::AddGoal(unsigned int argID, fk_GraphNode^ argNode)
    {
        if (!argNode) return;
        GetP()->addGoal(argID, argNode->GetP());
    }

    bool fk_Graph::InitCostTable(unsigned int argID)
    {
        return GetP()->initCostTable(argID);
    }

    fk_CostStatus fk_Graph::UpdateCostTable(unsigned int argID)
    {
        return getCS(GetP()->updateCostTable(argID));
    }

    fk_CostStatus fk_Graph::GetCostStatus(unsigned int argID)
    {
        return getCS(GetP()->getCostStatus(argID));
    }

    List<fk_GraphNode^>^ fk_Graph::GetOnePath(unsigned int argID)
    {
        auto retList = gcnew List<fk_GraphNode^>();
        list<::FK::fk_GraphNode*> list;

        GetP()->getOnePath(argID, &list);
        for (auto n : list) {
            retList->Add(gcnew fk_GraphNode(n));
        }
        return retList;
    }
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
