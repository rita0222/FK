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
#include <FK/Reference.h>

#include <FK/Vertex.h>
#include <FK/Half.h>
#include <FK/Edge.h>
#include <FK/Loop.h>

fk_Half * fk_ReferenceL1::getOneHOnV(fk_Vertex *argV) const
{
	if(argV == nullptr) return nullptr;
	return argV->getOneHalf();
}

fk_Edge * fk_ReferenceL1::getOneEOnV(fk_Vertex *argV) const
{
	fk_Half *tmpH;

	if(argV == nullptr) return nullptr;
	tmpH = argV->getOneHalf();
	if(tmpH == nullptr) return nullptr;
	return tmpH->getParentEdge();
}

fk_Vertex * fk_ReferenceL1::getVOnH(fk_Half *argH) const
{
	if(argH == nullptr) return nullptr;
	return argH->getVertex();
}

fk_Half * fk_ReferenceL1::getMateHOnH(fk_Half *argH) const
{
	fk_Edge *pE;
	fk_Half *retH, *rH, *lH;

	if(argH == nullptr) return nullptr;
	pE = argH->getParentEdge();
	rH = pE->getRightHalf();
	lH = pE->getLeftHalf();
	retH = (rH != argH) ? rH : lH;

	return retH;
}

fk_Edge * fk_ReferenceL1::getParentEOnH(fk_Half *argH) const
{
	if(argH == nullptr) return nullptr;
	return argH->getParentEdge();
}

fk_Loop * fk_ReferenceL1::getParentLOnH(fk_Half *argH) const
{
	if(argH == nullptr) return nullptr;
	return argH->getParentLoop();
}

fk_Vertex * fk_ReferenceL1::getRightVOnE(fk_Edge *argE) const
{
	if(argE == nullptr) return nullptr;
	return argE->getRightHalf()->getVertex();
}

fk_Vertex * fk_ReferenceL1::getLeftVOnE(fk_Edge *argE) const
{
	if(argE == nullptr) return nullptr;
	return argE->getLeftHalf()->getVertex();
}

fk_Half * fk_ReferenceL1::getRightHOnE(fk_Edge *argE) const
{
	if(argE == nullptr) return nullptr;
	return argE->getRightHalf();
}

fk_Half * fk_ReferenceL1::getLeftHOnE(fk_Edge *argE) const
{
	if(argE == nullptr) return nullptr;
	return argE->getLeftHalf();
}

fk_Loop * fk_ReferenceL1::getRightLOnE(fk_Edge *argE) const
{
	if(argE == nullptr) return nullptr;
	return argE->getRightHalf()->getParentLoop();
}

fk_Loop * fk_ReferenceL1::getLeftLOnE(fk_Edge *argE) const
{
	if(argE == nullptr) return nullptr;
	return argE->getLeftHalf()->getParentLoop();
}

fk_EdgeStatus fk_ReferenceL1::getEdgeStatus(fk_Edge *argE) const
{
	fk_Loop *rL, *lL;

	if(argE == nullptr) return FK_NONE_EDGE;
	rL = argE->getRightHalf()->getParentLoop();
	lL = argE->getLeftHalf()->getParentLoop();

	if(rL == nullptr && lL == nullptr) {
		return FK_UNDEF_EDGE;
	}

	if(rL != nullptr && lL != nullptr) {
		return FK_BOTHDEF_EDGE;
	}

	return FK_HALFDEF_EDGE;
}

fk_Vertex * fk_ReferenceL1::getOneVOnL(fk_Loop *argL) const
{
	if(argL == nullptr) return nullptr;
	return argL->getOneHalf()->getVertex();
}

fk_Half * fk_ReferenceL1::getOneHOnL(fk_Loop *argL) const
{
	if(argL == nullptr) return nullptr;
	return argL->getOneHalf();
}

fk_Edge * fk_ReferenceL1::getOneEOnL(fk_Loop *argL) const
{
	if(argL == nullptr) return nullptr;
	return argL->getOneHalf()->getParentEdge();
}
