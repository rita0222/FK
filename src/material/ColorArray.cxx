/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
#include <FK/ColorArray.H>

using namespace std;
using namespace FK;

fk_ColorArray::fk_ColorArray(void)
	: allFlg(false)
{
	array.clear();
	elemFlg.clear();
}

fk_ColorArray::fk_ColorArray(int argSize)
{
	array.resize(_st(argSize*4));
	elemFlg.resize(_st(argSize));
	for(_st i = 0; i < elemFlg.size(); ++i) elemFlg[i] = char(true);
	allFlg = true;
}

fk_ColorArray::~fk_ColorArray() {}

int fk_ColorArray::getSize(void)
{
	return int(elemFlg.size());
}

void fk_ColorArray::resize(int argSize)
{
	array.resize(_st(argSize*4));
	elemFlg.resize(_st(argSize));
	for(_st i = 0; i < elemFlg.size(); ++i) elemFlg[i] = char(true);
	allFlg = true;
}

void fk_ColorArray::clear(void)
{
	array.clear();
	elemFlg.clear();
	allFlg = true;
}

void fk_ColorArray::push(const fk_Color &argC)
{
	for(_st i = 0; i < 4; ++i) array.push_back(argC.col[i]);
	elemFlg.push_back(char(true));
	allFlg = true;
}

void fk_ColorArray::push(double argR, double argG, double argB, double argA)
{
	array.push_back(float(argR));
	array.push_back(float(argG));
	array.push_back(float(argB));
	array.push_back(float(argA));
	elemFlg.push_back(char(true));
	allFlg = true;
}

void fk_ColorArray::push(float argR, float argG, float argB, float argA)
{
	array.push_back(argR);
	array.push_back(argG);
	array.push_back(argB);
	array.push_back(argA);
	elemFlg.push_back(char(true));
	allFlg = true;
}

bool fk_ColorArray::set(int argID, const fk_Color &argC)
{
	if(argID < 0 || argID >= getSize()) return false;

	_st	id = _st(argID*4);
	for(_st i = 0; i < 4; ++i) {
		array[id+i] = argC.col[i];
	}
	elemFlg[_st(argID)] = true;
	allFlg = true;

	return true;
}

bool fk_ColorArray::set(int argID, double argR, double argG, double argB, double argA)
{
	if(argID < 0 || argID >= getSize()) return false;

	_st	id = _st(argID*4);
	array[id] = float(argR);
	array[id+1] = float(argG);
	array[id+2] = float(argB);
	array[id+3] = float(argA);
	elemFlg[_st(argID)] = true;
	allFlg = true;

	return true;
}

bool fk_ColorArray::set(int argID, float argR, float argG, float argB, float argA)
{
	if(argID < 0 || argID >= getSize()) return false;

	_st	id = _st(argID*4);
	array[id] = argR;
	array[id+1] = argG;
	array[id+2] = argB;
	array[id+3] = argA;
	elemFlg[_st(argID)] = true;
	allFlg = true;

	return true;
}

fk_Color fk_ColorArray::get(int argID)
{
	fk_Color tmp(0.0, 0.0, 0.0, 1.0);
	if(argID < 0 || argID >= getSize()) return tmp;

	_st	id = _st(argID*4);
	for(_st i = 0; i < 4; ++i) {
		tmp.col[i] = array[id+i];
	}
	return tmp;
}

vector<float> * fk_ColorArray::getP(void)
{
	return &array;
}

bool fk_ColorArray::isModify(void)
{
	return allFlg;
}

bool fk_ColorArray::isModify(int argID)
{
	if(argID < 0 || argID >= getSize()) return false;
	return elemFlg[_st(argID)];
}

void fk_ColorArray::reset(void)
{
	if(allFlg == false) return;
	allFlg = false;
	for(_st i = 0; i < elemFlg.size(); ++i) elemFlg[i] = char(false);
}
