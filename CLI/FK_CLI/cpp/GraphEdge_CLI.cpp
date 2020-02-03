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
#include "GraphEdge_CLI.h"
#include "GraphNode_CLI.h"

namespace FK_CLI {

	using namespace std;
	using namespace System::Collections::Generic;
	
    ::FK::fk_CostType fk_GraphEdge::getCT(fk_CostType argType)
    {
        switch(argType) {
            case fk_CostType::INT:
                return ::FK::fk_CostType::INT;

            case fk_CostType::DOUBLE:
                return ::FK::fk_CostType::DOUBLE;

            default:
                break;
        }
        return ::FK::fk_CostType::LENGTH;
    }

    ::FK::fk_CostDirection fk_GraphEdge::getCD(fk_CostDirection argType)
    {
        if (argType == fk_CostDirection::FORWARD) return ::FK::fk_CostDirection::FORWARD;
        return ::FK::fk_CostDirection::BACK;
    }

	::FK::fk_GraphEdge * fk_GraphEdge::GetP(void)
	{
		return (::FK::fk_GraphEdge *)(pBase);
	}

    fk_GraphEdge::fk_GraphEdge(::FK::fk_GraphEdge* argE) : fk_BaseObject(false)
    {
        pBase = (::FK::fk_BaseObject*)argE;
        dFlg = false;
    }

    fk_GraphEdge::~fk_GraphEdge()
	{
		this->!fk_GraphEdge();
	}

	fk_GraphEdge::!fk_GraphEdge()
	{
		if(pBase == nullptr) return;
		pBase = nullptr;
	}

    unsigned int fk_GraphEdge::ID::get()
    {
        return GetP()->getID();
    }

    fk_GraphNode^ fk_GraphEdge::GetNode(bool argMode)
    {
        return gcnew fk_GraphNode(GetP()->getNode(argMode));
    }

    bool fk_GraphEdge::LengthMode::get()
    {
        return GetP()->getLengthMode();
    }

    void fk_GraphEdge::LengthMode::set(bool argMode)
    {
        GetP()->setLengthMode(argMode);
    }

    double fk_GraphEdge::Length::get()
    {
        return GetP()->getLength();
    }

    void fk_GraphEdge::SetCostMaxID(fk_CostType argType, unsigned int argMax)
    {
        GetP()->setCostMaxID(getCT(argType), argMax);
    }

    unsigned int fk_GraphEdge::GetCostMaxID(fk_CostType argType)
    {
        return GetP()->getCostMaxID(getCT(argType));
    }

    void fk_GraphEdge::SetIntCost(int argCost)
    {
        GetP()->setIntCost(argCost);
    }

    void fk_GraphEdge::SetIntCost(unsigned int argID, int argCost)
    {
        GetP()->setIntCost(argID, argCost);
    }

    void fk_GraphEdge::SetDoubleCost(double argCost)
    {
        GetP()->setDoubleCost(argCost);
    }

    void fk_GraphEdge::SetDoubleCost(unsigned int argID, double argCost)
    {
        GetP()->setDoubleCost(argID, argCost);
    }

    int fk_GraphEdge::GetIntCost(void)
    {
        return GetP()->getIntCost();
    }

    int fk_GraphEdge::GetIntCost(unsigned int argID)
    {
        return GetP()->getIntCost(argID);
    }

    double fk_GraphEdge::GetDoubleCost(void)
    {
        return GetP()->getDoubleCost();
    }

    double fk_GraphEdge::GetDoubleCost(unsigned int argID)
    {
        return GetP()->getDoubleCost(argID);
    }

    void fk_GraphEdge::Color::set(fk_Color^ argColor)
    {
        if (!argColor) return;
        GetP()->setColor(argColor->pCol);
    }
}
