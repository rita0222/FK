#define FK_DEF_SIZETYPE
#include <FK/FVecArray.h>
#include <FK/Material.h>

using namespace std;
using namespace FK;

fk_FVecArray::Member::Member(void)
	: dim(3), size(0), allFlg(false)
{
	return;
}

fk_FVecArray::fk_FVecArray(void) : _m(make_unique<Member>())
{
	return;
}

fk_FVecArray::~fk_FVecArray()
{
	return;
}

fk_FVecArray & fk_FVecArray::operator =(const fk_FVecArray &argV)
{
	_m->dim = argV._m->dim;
	_m->size = argV._m->size;
	_m->allFlg = argV._m->allFlg;
	_m->array = argV._m->array;
	_m->elemFlg = argV._m->elemFlg;

	return *this;
}

fk_FVecArray::fk_FVecArray(const fk_FVecArray &argV)
{
	_m->dim = argV._m->dim;
	_m->size = argV._m->size;
	_m->allFlg = argV._m->allFlg;
	_m->array = argV._m->array;
	_m->elemFlg = argV._m->elemFlg;
}	

void fk_FVecArray::setDim(int argDim)
{
	if(argDim < 2 || argDim > 4) return;
	_m->dim = argDim;
}

int fk_FVecArray::getDim(void)
{
	return _m->dim;
}

int fk_FVecArray::getSize(void)
{
	return _m->size;
}

void fk_FVecArray::resize(int argSize)
{
	_m->size = argSize;
	_m->array.resize(_st(argSize)*_st(_m->dim));
	_m->elemFlg.resize(_st(argSize));
	fill(_m->elemFlg.begin(), _m->elemFlg.end(), char(true));
	_m->allFlg = true;
}

void fk_FVecArray::clear(void)
{
	_m->array.clear();
	_m->elemFlg.clear();
	_m->allFlg = true;
	_m->size = 0;
}

void fk_FVecArray::push(const fk_Vector &argV)
{
	push(argV.x, argV.y, argV.z);
}

void fk_FVecArray::push(const fk_FVector &argF)
{
	push(argF.x, argF.y, argF.z);
}

void fk_FVecArray::push(const fk_HVector &argV)
{
	push(argV.x, argV.y, argV.z, argV.w);
}

void fk_FVecArray::push(const fk_TexCoord &argC)
{
	push(argC.x, argC.y);
}

void fk_FVecArray::push(const fk_Color &argC)
{
	push(argC.col[0], argC.col[1], argC.col[2], argC.col[3]);
}

void fk_FVecArray::push(double argX, double argY, double argZ, double argW)
{
	++_m->size;
	_m->array.push_back(float(argX));
	_m->array.push_back(float(argY));
	if(_m->dim >= 3) _m->array.push_back(float(argZ));
	if(_m->dim == 4) _m->array.push_back(float(argW));
	_m->elemFlg.push_back(char(true));
	_m->allFlg = true;
}

void fk_FVecArray::push(float argX, float argY, float argZ, float argW)
{
	++_m->size;
	_m->array.push_back(argX);
	_m->array.push_back(argY);
	if(_m->dim >= 3) _m->array.push_back(argZ);
	if(_m->dim == 4) _m->array.push_back(argW);
	_m->elemFlg.push_back(char(true));
	_m->allFlg = true;
}

bool fk_FVecArray::set(int argID, const fk_Vector &argV)
{
	return set(argID, argV.x, argV.y, argV.z);
}

bool fk_FVecArray::set(int argID, const fk_FVector &argF)
{
	return set(argID, argF.x, argF.y, argF.z);
}

bool fk_FVecArray::set(int argID, const fk_HVector &argV)
{
	return set(argID, argV.x, argV.y, argV.z, argV.w);
}

bool fk_FVecArray::set(int argID, const fk_TexCoord &argC)
{
	return set(argID, argC.x, argC.y);
}

bool fk_FVecArray::set(int argID, const fk_Color &argC)
{
	return set(argID, argC.col[0], argC.col[1], argC.col[2], argC.col[3]);
}

bool fk_FVecArray::set(int argID, double argX, double argY)
{
	if(argID < 0 || argID >= _m->size) return false;

	_st	id = _st(argID)*_st(_m->dim);
	_m->array[id] = float(argX);
	_m->array[id+1] = float(argY);
	_m->elemFlg[_st(argID)] = true;
	_m->allFlg = true;

	return true;
}

bool fk_FVecArray::set(int argID, double argX, double argY, double argZ)
{
	if(argID < 0 || argID >= _m->size) return false;

	_st	id = _st(argID)*_st(_m->dim);
	_m->array[id] = float(argX);
	_m->array[id+1] = float(argY);
	if(_m->dim >= 3) _m->array[id+2] = float(argZ);
	_m->elemFlg[_st(argID)] = true;
	_m->allFlg = true;

	return true;
}

bool fk_FVecArray::set(int argID, double argX, double argY, double argZ, double argW)
{
	if(argID < 0 || argID >= _m->size) return false;

	_st	id = _st(argID)*_st(_m->dim);
	_m->array[id] = float(argX);
	_m->array[id+1] = float(argY);
	if(_m->dim >= 3) _m->array[id+2] = float(argZ);
	if(_m->dim == 4) _m->array[id+3] = float(argW);
	_m->elemFlg[_st(argID)] = true;
	_m->allFlg = true;

	return true;
}

bool fk_FVecArray::set(int argID, float argX, float argY)
{
	if(argID < 0 || argID >= _m->size) return false;

	_st	id = _st(argID)*_st(_m->dim);
	_m->array[id] = argX;
	_m->array[id+1] = argY;
	_m->elemFlg[_st(argID)] = true;
	_m->allFlg = true;

	return true;
}

bool fk_FVecArray::set(int argID, float argX, float argY, float argZ)
{
	if(argID < 0 || argID >= _m->size) return false;

	_st	id = _st(argID)*_st(_m->dim);
	_m->array[id] = argX;
	_m->array[id+1] = argY;
	if(_m->dim >= 3) _m->array[id+2] = argZ;
	_m->elemFlg[_st(argID)] = true;
	_m->allFlg = true;

	return true;
}

bool fk_FVecArray::set(int argID, float argX, float argY, float argZ, float argW)
{
	if(argID < 0 || argID >= _m->size) return false;

	_st	id = _st(argID)*_st(_m->dim);
	_m->array[id] = argX;
	_m->array[id+1] = argY;
	if(_m->dim >= 3) _m->array[id+2] = argZ;
	if(_m->dim == 4) _m->array[id+3] = argW;
	_m->elemFlg[_st(argID)] = true;
	_m->allFlg = true;

	return true;
}

fk_Vector fk_FVecArray::getV(int argID)
{
	fk_Vector tmp;
	if(argID < 0 || argID >= getSize()) return tmp;

	_st	id = _st(argID)*_st(_m->dim);
	tmp.x = double(_m->array[id]);
	tmp.y = double(_m->array[id+1]);
	if(_m->dim >= 3) tmp.z = double(_m->array[id+2]);
	return tmp;
}


fk_FVector fk_FVecArray::getF(int argID)
{
	fk_FVector tmp;
	if(argID < 0 || argID >= getSize()) return tmp;

	_st	id = _st(argID)*_st(_m->dim);
	tmp.x = _m->array[id];
	tmp.y = _m->array[id+1];
	if(_m->dim >= 3) tmp.z = _m->array[id+2];
	return tmp;
}

fk_HVector fk_FVecArray::getHV(int argID)
{
	fk_HVector tmp;
	if(argID < 0 || argID >= getSize()) return tmp;

	_st	id = _st(argID)*_st(_m->dim);
	tmp.x = double(_m->array[id]);
	tmp.y = double(_m->array[id+1]);
	if(_m->dim >= 3) tmp.z = double(_m->array[id+2]);
	if(_m->dim == 4) tmp.w = double(_m->array[id+3]);
	return tmp;
}

fk_TexCoord fk_FVecArray::getT(int argID)
{
	fk_TexCoord tmp;
	if(argID < 0 || argID >= getSize()) return tmp;

	_st	id = _st(argID)*_st(_m->dim);
	tmp.x = _m->array[id];
	tmp.y = _m->array[id+1];
	return tmp;
}

fk_Color fk_FVecArray::getC(int argID)
{
	fk_Color tmp;
	if(argID < 0 || argID >= getSize()) return tmp;

	_st	id = _st(argID)*_st(_m->dim);
	tmp.col[0] = _m->array[id];
	tmp.col[1] = _m->array[id+1];
	if(_m->dim >= 3) tmp.col[2] = _m->array[id+2];
	if(_m->dim == 4) tmp.col[3] = _m->array[id+3];
	return tmp;
}

vector<float> * fk_FVecArray::getP(void)
{
	return &_m->array;
}

bool fk_FVecArray::isModify(void)
{
	return _m->allFlg;
}

bool fk_FVecArray::isModify(int argID)
{
	if(argID < 0 || argID >= _m->size) return false;
	return _m->elemFlg[_st(argID)];
}

void fk_FVecArray::reset(void)
{
	if(_m->allFlg == false) return;
	_m->allFlg = false;
	fill(_m->elemFlg.begin(), _m->elemFlg.end(), char(false));
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
