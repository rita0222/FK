﻿ /****************************************************************************
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

#define FK_DEF_SIZETYPE
#include <FK/Point.h>
//#include <FK/Window.h>

using namespace std;
using namespace FK;

fk_Point::fk_Point(vector<fk_Vector> *argVertexSet)
{
	SetObjectType(FK_POINT);
	//SetPaletteData(&localPal);
	allClear(false);
	MakePoint(argVertexSet);

	setShaderAttribute("position", 3, &posArray);
	setShaderAttribute("fk_p_elem_color", 4, &colArray);
	setShaderAttribute("alive", 1, &aliveArray);
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

	posArray.clear();
	colArray.clear();
	aliveArray.clear();

	for(i = 0; i < argNum; i++) {
		pushVertex(argP[i]);
	}

	return true;
}

bool fk_Point::MakePoint(vector<fk_Vector> *argP)
{
	if(argP == nullptr) return false;
	return MakePoint(int(argP->size()), &(argP->at(0)));
}

int fk_Point::pushVertex(fk_Vector argPos)
{
	fk_Color	tmpCol(0.0, 0.0, 0.0, 0.0);

	posArray.push_back(float(argPos.x));
	posArray.push_back(float(argPos.y));
	posArray.push_back(float(argPos.z));

	colArray.push_back(0.0f);
	colArray.push_back(0.0f);
	colArray.push_back(0.0f);
	colArray.push_back(1.0f);

	aliveArray.push_back(FK_SHAPE_ALIVE);

	return int(aliveArray.size() - 1);
}

bool fk_Point::setVertex(int argID, fk_Vector argPos)
{
	if(argID < 0 || argID >= int(aliveArray.size())) return false;
	if(aliveArray[_st(argID)] == FK_SHAPE_DEAD) return false;
	_st i = _st(argID) * 3;
	posArray[i] = float(argPos.x);
	posArray[i+1] = float(argPos.y);
	posArray[i+2] = float(argPos.z);
	return true;
}

bool fk_Point::setVertex(int argNum, fk_Vector *argPosArray)
{
	return MakePoint(argNum, argPosArray);
}

bool fk_Point::setVertex(vector<fk_Vector> *argPosArray)
{
	return MakePoint(argPosArray);
}

bool fk_Point::removeVertex(int argID)
{
	if(aliveArray[_st(argID)] == FK_SHAPE_DEAD) return false;
	aliveArray[_st(argID)] = FK_SHAPE_DEAD;

	return true;
}

fk_Vector fk_Point::getVertex(int argID)
{
	fk_Vector tmp(0.0, 0.0, 0.0);
	_st i = _st(argID) * 3;
	if(aliveArray[_st(argID)] == FK_SHAPE_DEAD) return tmp;
	
	tmp.set(posArray[i], posArray[i+1], posArray[i+2]);
	return tmp;
}

int fk_Point::getSize(void)
{
	return int(aliveArray.size());
}

void fk_Point::setDrawMode(int argID, bool argFlag)
{
	if(argID < 0 || argID >= int(aliveArray.size())) return;
	if(argFlag == false) {
		//if(aliveArray[_st(argID)] == FK_SHAPE_ALIVE) {
		//fk_Window::printf("%d Dead", argID);
		//}
		aliveArray[_st(argID)] = FK_SHAPE_DEAD;
	} else {
		aliveArray[_st(argID)] = FK_SHAPE_ALIVE;
	}
	return;
}

bool fk_Point::getDrawMode(int argID)
{
	if(argID < 0 || argID >= int(aliveArray.size())) return false;
	if(aliveArray[_st(argID)] == FK_SHAPE_ALIVE) return true;
	return false;
}

void fk_Point::setColorID(int argID, int argCol)
{
	FK_UNUSED(argID);
	FK_UNUSED(argCol);

	/*
	_st		id = static_cast<_st>(argID);

	if(vec.isAlive(argID) == false) return;

	if(argCol >= 0) {
		if(colorID[id] < 0) {
			colorCount++;
		}
		colorID[id] = argCol;
	}

	if(argCol < 0) {
		if(colorID[id] >= 0) {
			colorCount--;
		}
		colorID[id] = -1;
	}
	*/

	return;
}

int fk_Point::getColorID(int argID)
{
	FK_UNUSED(argID);
	/*
	if(vec.isAlive(argID) == false) return -2;
	return colorID[static_cast<_st>(argID)];
	*/

	return 0;
}

void fk_Point::allClear(bool argMateFlg)
{
	posArray.clear();
	colArray.clear();
	aliveArray.clear();
	if(argMateFlg == true) clearMaterial();

	return;
}
