﻿#define FK_DEF_SIZETYPE
#include <FK/Closedline.h>

using namespace std;
using namespace FK;

fk_Closedline::Member::Member(void) : num(0)
{
	return;
}

fk_Closedline::fk_Closedline(vector<fk_Vector> *argVertexSet) : _m(make_unique<Member>())
{
	SetObjectType(fk_Type::POLYLINE);
	setVertex(argVertexSet);
	return;
}

fk_Closedline::~fk_Closedline()
{
	return;
}

void fk_Closedline::allClear(void)
{
	AllClear();
	Touch();
	_m->num = 0;
}

void fk_Closedline::pushVertex(fk_Vector argPos)
{
	fk_Vector S, V;
	switch(_m->num) {
	  case 0:
		Resize(1);
		SetPos(0, 0, &argPos);
		break;

	  case 1:
		SetPos(0, 1, &argPos);
		break;

	  case 2:
		S = GetPos(0, 0);
		V = GetPos(0, 1);
		PushLines(&V, &argPos);
		PushLines(&argPos, &S);
		break;
		
	  default:
		S = GetPos(0, 0);
		V = GetPos(Size()-1, 0);
		SetPos(Size()-1, 1, &argPos);
		PushLines(&argPos, &S);
		break;
	}
	_m->num++;
	Touch();
}

void fk_Closedline::setVertex(int argID, fk_Vector argPos)
{
	if(argID < 0 || argID >= _m->num) return;
	SetPos(argID, 0, &argPos);
	if(argID == 0) {
		SetPos(_m->num-1, 1, &argPos);
	} else {
		SetPos(argID-1, 1, &argPos);
	}
	Touch();
}

void fk_Closedline::setVertex(vector<fk_Vector> *argPosArray)
{
	allClear();
	if(argPosArray == nullptr) return;
	if(argPosArray->empty() == true) return;
	if(argPosArray->size() == 1) {
		pushVertex(argPosArray->at(1));
		return;
	}

	vector<fk_Vector>	array;

	for(_st i = 0; i < argPosArray->size(); ++i) {
		array.push_back(argPosArray->at(i));
		if(i != 0 && i != argPosArray->size()-1) {
			array.push_back(argPosArray->at(i));
		}
	}
	array.push_back(argPosArray->back());
	array.push_back(argPosArray->front());
	MakeLines(&array);

	return;
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
