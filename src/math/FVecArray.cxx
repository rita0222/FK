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
#define FK_DEF_SIZETYPE
#include <FK/FVecArray.H>

using namespace std;
using namespace FK;

fk_FVecArray::fk_FVecArray(void)
{
	array.clear();
}

fk_FVecArray::fk_FVecArray(int argSize)
{
	array.resize(_st(argSize*3));
}

fk_FVecArray::~fk_FVecArray() {}

int fk_FVecArray::getSize(void)
{
	return int(array.size()/3);
}

void fk_FVecArray::resize(int argSize)
{
	array.resize(_st(argSize*3));
}

void fk_FVecArray::clear(void)
{
	array.clear();
}

void fk_FVecArray::push(const fk_Vector &argV)
{
	array.push_back(float(argV.x));
	array.push_back(float(argV.y));
	array.push_back(float(argV.z));
}

void fk_FVecArray::push(const fk_FVector &argF)
{
	array.push_back(argF.x);
	array.push_back(argF.y);
	array.push_back(argF.z);
}

void fk_FVecArray::push(double argX, double argY, double argZ)
{
	array.push_back(float(argX));
	array.push_back(float(argY));
	array.push_back(float(argZ));
}

void fk_FVecArray::push(float argX, float argY, float argZ)
{
	array.push_back(argX);
	array.push_back(argY);
	array.push_back(argZ);
}

bool fk_FVecArray::set(int argID, const fk_Vector &argV)
{
	if(argID < 0 || argID >= getSize()) return false;

	_st	id = _st(argID*3);
	array[id] = float(argV.x);
	array[id+1] = float(argV.y);
	array[id+2] = float(argV.z);
	return true;
}

bool fk_FVecArray::set(int argID, const fk_FVector &argF)
{
	if(argID < 0 || argID >= getSize()) return false;

	_st	id = _st(argID*3);
	array[id] = argF.x;
	array[id+1] = argF.y;
	array[id+2] = argF.z;
	return true;
}

bool fk_FVecArray::set(int argID, double argX, double argY, double argZ)
{
	if(argID < 0 || argID >= getSize()) return false;

	_st	id = _st(argID*3);
	array[id] = float(argX);
	array[id+1] = float(argY);
	array[id+2] = float(argZ);
	return true;
}

bool fk_FVecArray::set(int argID, float argX, float argY, float argZ)
{
	if(argID < 0 || argID >= getSize()) return false;

	_st	id = _st(argID*3);
	array[id] = argX;
	array[id+1] = argY;
	array[id+2] = argZ;
	return true;
}

fk_Vector fk_FVecArray::getV(int argID)
{
	fk_Vector tmp(0.0, 0.0, 0.0);
	if(argID < 0 || argID >= getSize()) return tmp;

	_st	id = _st(argID*3);
	tmp.set(array[id], array[id+1], array[id+2]);
	return tmp;
}


fk_FVector fk_FVecArray::getF(int argID)
{
	fk_FVector tmp;
	tmp.x = tmp.y = tmp.z = 0.0f;
	if(argID < 0 || argID >= getSize()) return tmp;

	_st	id = _st(argID*3);
	tmp.x = array[id];
	tmp.y = array[id+1];
	tmp.z = array[id+2];
	return tmp;
}

float * fk_FVecArray::getP(void)
{
	if(array.empty()) return nullptr;
	return array.data();
}
