#define FK_DEF_SIZETYPE
#include <FK/LineBase.H>

using namespace std;
using namespace FK;

fk_LineBase::Member::Member(void)
{
	return;
}

fk_LineBase::fk_LineBase(vector<fk_Vector> *argVertexPos) : _m(make_unique<Member>())
{
	FlushAttr = [this]() {
		if(_m->posArray.isModify() == true) {
			modifyAttribute(vertexName);
			_m->posArray.reset();
		}

		if(_m->colArray.isModify() == true) {
			modifyAttribute(lineElementColorName);
			_m->colArray.reset();
		}
	};
	
	_m->posArray.setDim(3);
	_m->colArray.setDim(4);
	realType = fk_RealShapeType::LINE;
	AllClear();
	MakeLines(argVertexPos);

	setShaderAttribute(vertexName, 3, _m->posArray.getP());
	setShaderAttribute(lineElementColorName, 4, _m->colArray.getP());
	setShaderAttribute(lineElementAliveName, 1, &(_m->aliveArray));
	return;
}

fk_LineBase::~fk_LineBase()
{
	return;
}

void fk_LineBase::AllClear(void)
{
	_m->posArray.clear();
	_m->colArray.clear();
	_m->aliveArray.clear();
	Touch();
}

void fk_LineBase::SetPos(int argEID, int argVID, fk_Vector *argV)
{
	_m->posArray.set(argEID*2 + argVID, *argV);
	modifyAttribute(vertexName);
	return;
}

fk_Vector fk_LineBase::GetPos(int argEID, int argVID)
{
	return _m->posArray.getV(argEID*2 + argVID);
}

void fk_LineBase::SetCol(int argEID, int argVID, fk_Color *argC)
{
	_m->colArray.set(argEID*2 + argVID, *argC);
	modifyAttribute(lineElementColorName);
	return;
}

fk_Color fk_LineBase::GetCol(int argEID, int argVID)
{
	return _m->colArray.getC(argEID*2 + argVID);
}

void fk_LineBase::SetAlive(int argEID, bool argMode)
{
	int mode = (argMode == true) ? fk_Shape::ALIVE : fk_Shape::DEAD;
	_m->aliveArray[_st(argEID)*2] = _m->aliveArray[_st(argEID)*2+1] = mode;
	modifyAttribute(lineElementAliveName);
}

bool fk_LineBase::GetAlive(int argEID)
{
	return ((_m->aliveArray[_st(argEID)*2] == fk_Shape::ALIVE) ? true : false);
}

void fk_LineBase::MakeLines(vector<fk_Vector> *argVPos)
{
	if(argVPos == nullptr) {
		_m->posArray.clear();
		_m->colArray.clear();
		_m->aliveArray.clear();
		return;
	}

	fk_Color col(0.0, 0.0, 0.0, 1.0);

	_m->posArray.resize(int(argVPos->size()));
	_m->colArray.resize(int(argVPos->size()));
	_m->aliveArray.resize(argVPos->size());

	for(int i = 0; i < _m->posArray.getSize()/2; ++i) {
		SetPos(i, 0, &(*argVPos)[_st(i)*2]);
		SetPos(i, 1, &(*argVPos)[_st(i)*2+1]);
		SetCol(i, 0, &col);
		SetCol(i, 1, &col);
		SetAlive(i, true);
	}
	Touch();
	return;
}

void fk_LineBase::MakeLines(fk_Vector *argVPos)
{
	if(argVPos == nullptr) {
		_m->posArray.clear();
		_m->colArray.clear();
		_m->aliveArray.clear();
		return;
	}

	PushLines(&argVPos[0], &argVPos[1]);
	return;
}

void fk_LineBase::PushLines(fk_Vector *argS, fk_Vector *argE)
{
	_m->posArray.push(*argS);
	_m->posArray.push(*argE);
	_m->colArray.push(0.0f, 0.0f, 0.0f, 1.0f);
	_m->colArray.push(0.0f, 0.0f, 0.0f, 1.0f);
	_m->aliveArray.push_back(fk_Shape::ALIVE);
	_m->aliveArray.push_back(fk_Shape::ALIVE);
	Touch();
}

void fk_LineBase::Resize(int argSize)
{
	_m->posArray.resize(argSize*2);
	_m->colArray.resize(argSize*2);
	_m->aliveArray.resize(_st(argSize)*2);
	Touch();
}

int fk_LineBase::Size(void)
{
	return int(_m->posArray.getSize()/2);
}

void fk_LineBase::Touch(void)
{
	modifyAttribute(vertexName);
	modifyAttribute(lineElementColorName);
	modifyAttribute(lineElementAliveName);
}

fk_Vector fk_LineBase::GetLast(void)
{
	int size = Size();
	switch(size) {
	  case 0:
		return fk_Vector(0.0, 0.0, 0.0);

	  case 1:
		return _m->posArray.getV(1);

	  default:
		break;
	}
	return _m->posArray.getV(_m->posArray.getSize()-1);
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
