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

#define FK_DEF_SIZETYPE
#include <FK/Point.h>

using namespace std;

fk_Point::fk_Point(vector<fk_Vector> *argVertexSet)
{
	SetObjectType(FK_POINT);
	SetPaletteData(&localPal);
	allClear(false);
	MakePoint(argVertexSet);
	return;
}

fk_Point::~fk_Point()
{
	return;
}

bool fk_Point::MakePoint(int argNum, fk_Vector *argP)
{
	int			i;
	fk_FVector	tmp;

	if(argNum < 0) return false;
	if(argP == NULL) return true;

	vec.clear();

	drawMode.clear();
	drawCount = 0;

	colorID.clear();
	colorCount = 0;

	for(i = 0; i < argNum; i++) {
		tmp = argP[i];
		vec.push(tmp);
		drawMode.push_back(static_cast<char>(true));
		colorID.push_back(-1);
	}

	return true;
}

bool fk_Point::MakePoint(vector<fk_Vector> *argP)
{
	_st			i;
	fk_FVector	tmp;

	vec.clear();

	drawMode.clear();
	drawCount = 0;

	colorID.clear();
	colorCount = 0;

	if(argP == NULL) return true;
	for(i = 0; i < argP->size(); i++) {
		tmp = (*argP)[i];
		vec.push(tmp);
		drawMode.push_back(static_cast<char>(true));
		colorID.push_back(-1);
	}

	return true;
}

int fk_Point::pushVertex(fk_Vector argPos)
{
	fk_FVector	tmp;
	_st			id;

	tmp = argPos;
	id = static_cast<_st>(vec.push(tmp));
	if(id == drawMode.size()) {
		drawMode.push_back(static_cast<char>(true));
		colorID.push_back(-1);
	} else {
		drawMode[id] = static_cast<char>(true);
		colorID[id] = -1;
	}
	return static_cast<int>(id);
}

bool fk_Point::setVertex(int argID, fk_Vector argPos)
{
	fk_FVector		*p;

	if(vec.isAlive(argID) == false) return false;

	p = vec.at(argID);
	*p = argPos;

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
	if(vec.isAlive(argID) == false) return false;

	vec.remove(argID);
	return true;
}

fk_FVector * fk_Point::getVertex(int argID)
{
	if(vec.isAlive(argID) == false) return NULL;
	return vec.at(argID);
}

int fk_Point::getSize(void)
{
	return vec.size();
}

void fk_Point::setDrawMode(int argID, bool argFlag)
{
	_st		id = static_cast<_st>(argID);

	if(vec.isAlive(argID) == false) return;

	if(argFlag == false && drawMode[id] == static_cast<char>(true)) {
		drawCount++;
		drawMode[id] = static_cast<char>(false);
	}

	if(argFlag == true && drawMode[id] == static_cast<char>(false)) {
		drawCount--;
		drawMode[id] = static_cast<char>(true);
	}

	return;
}

bool fk_Point::getDrawMode(void)
{
	if(drawCount == 0) return true;
	return false;
}

bool fk_Point::getDrawMode(int argID)
{
	if(vec.isAlive(argID) == false) return false;
	//return static_cast<bool>(drawMode[static_cast<_st>(argID)]);
	return (drawMode[static_cast<_st>(argID)]) ? true : false;
}

void fk_Point::setColorID(int argID, int argCol)
{
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

	return;
}

bool fk_Point::getColorCount(void)
{
	return ((colorCount == 0) ? true : false);
}

int fk_Point::getColorID(int argID)
{
	if(vec.isAlive(argID) == false) return -2;
	return colorID[static_cast<_st>(argID)];
}

void fk_Point::allClear(bool argMateFlg)
{
	vec.clear();
	drawMode.clear();
	drawCount = 0;
	colorCount = 0;
	if(argMateFlg == true) clearMaterial();

	return;
}
