﻿#define FK_DEF_SIZETYPE
#include <FK/Point.h>

using namespace std;
using namespace FK;

fk_Point::Member::Member(void)
{
	return;
}

fk_Point::fk_Point(vector<fk_Vector> *argVertexSet) : _m(make_unique<Member>())
{
	FlushAttr = [this]() {
		if (_m->posArray.isModify() == true) {
			modifyAttribute(vertexName);
			_m->posArray.reset();
		}
		if (_m->colArray.isModify() == true) {
			modifyAttribute(pointElementColorName);
			_m->colArray.reset();
		}
	};

	_m->posArray.setDim(3);
	_m->colArray.setDim(4);
	realType = fk_RealShapeType::POINT;
	SetObjectType(fk_Type::POINT);
	allClear();
	MakePoint(argVertexSet);

	setShaderAttribute(vertexName, 3, _m->posArray.getP());
	setShaderAttribute(pointElementColorName, 4, _m->colArray.getP());
	setShaderAttribute(pointElementAliveName, 1, &(_m->aliveArray));
	return;
}

fk_Point::~fk_Point()
{
	return;
}

bool fk_Point::MakePoint(int argNum, fk_Vector *argP)
{
	int				i;

	if(argNum < 0) return false;
	if(argP == nullptr) return false;

	_m->posArray.clear();
	_m->colArray.clear();
	_m->aliveArray.clear();

	for(i = 0; i < argNum; i++) {
		pushVertex(argP[i]);
	}

	modifyAttribute(vertexName);
	modifyAttribute(pointElementColorName);
	modifyAttribute(pointElementAliveName);

	return true;
}

bool fk_Point::MakePoint(vector<fk_Vector> *argP)
{
	if(argP == nullptr) return false;
	return MakePoint(int(argP->size()), argP->data());
}

int fk_Point::pushVertex(const fk_Vector &argPos)
{
	_m->posArray.push(argPos);
	_m->colArray.push(0.0, 0.0, 0.0, 1.0);
	_m->aliveArray.push_back(fk_Shape::ALIVE);

	modifyAttribute(vertexName);
	modifyAttribute(pointElementColorName);
	modifyAttribute(pointElementAliveName);

	return int(_m->aliveArray.size() - 1);
}

bool fk_Point::setVertex(int argID, const fk_Vector &argPos)
{
	if(argID < 0 || argID >= _m->posArray.getSize()) return false;
	if(_m->aliveArray[_st(argID)] == fk_Shape::DEAD) return false;
	_m->posArray.set(argID, argPos);

	modifyAttribute(vertexName);

	return true;
}

bool fk_Point::setVertex(vector<fk_Vector> *argPosArray)
{
	return MakePoint(argPosArray);
}

bool fk_Point::removeVertex(int argID)
{
	if(argID < 0 || argID >= int(_m->aliveArray.size())) return false;
	if(_m->aliveArray[_st(argID)] == fk_Shape::DEAD) return true;
	_m->aliveArray[_st(argID)] = fk_Shape::DEAD;

	modifyAttribute(pointElementAliveName);

	return true;
}

fk_Vector fk_Point::getVertex(int argID)
{
	fk_Vector tmp(0.0, 0.0, 0.0);
	if(_m->aliveArray[_st(argID)] == fk_Shape::DEAD) return tmp;
	
	return _m->posArray.getV(argID);
}

int fk_Point::getSize(void)
{
	return int(_m->aliveArray.size());
}

void fk_Point::allClear(void)
{
	_m->posArray.clear();
	_m->colArray.clear();
	_m->aliveArray.clear();

	modifyAttribute(vertexName);
	modifyAttribute(pointElementColorName);
	modifyAttribute(pointElementAliveName);

	return;
}

void fk_Point::setColor(int argID, fk_Color argCol)
{
	if(argID < 0 || argID >= _m->colArray.getSize()) return;
	_m->colArray.set(argID, argCol);
	modifyAttribute(pointElementColorName);
	return;
}

void fk_Point::setColor(int argID, fk_Color *argCol)
{
	if(argCol == nullptr) return;
	if(argID < 0 || argID >= _m->colArray.getSize()) return;
	_m->colArray.set(argID, *argCol);
	modifyAttribute(pointElementColorName);
	return;
}

fk_Color fk_Point::getColor(int argID)
{
	return _m->colArray.getC(argID);
}

void fk_Point::setDrawMode(int argID, bool argMode)
{
	if(argID < 0 || argID >= int(_m->aliveArray.size())) return;
	_m->aliveArray[_st(argID)] = (argMode) ? fk_Shape::ALIVE : fk_Shape::DEAD;
	modifyAttribute(pointElementAliveName);
}

bool fk_Point::getDrawMode(int argID)
{
	if(argID < 0 || argID >= int(_m->aliveArray.size())) return false;
	if(_m->aliveArray[_st(argID)] == fk_Shape::ALIVE) return true;
	return false;
}


void fk_Point::setColorID(int, int) { return; }
int fk_Point::getColorID(int) { return 0; }

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
