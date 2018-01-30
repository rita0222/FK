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
#include <FK/GenVector.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;
using namespace FK;

fk_GenVector::fk_GenVector(int argSize)
{
	resize(argSize);
	return;
}

fk_GenVector::fk_GenVector(vector<double> &argArray)
{
	v = argArray;
	return;
}

fk_GenVector::fk_GenVector(int argSize, double *argArray)
{
	_st		i;

	init(true);
	if(argSize <= 0) return;

	resize(argSize);
	for(i = 0; i < static_cast<_st>(argSize); ++i) {
		v[i] = argArray[i];
	}

	return;
}

fk_GenVector::fk_GenVector(const fk_GenVector &argVec)
{
	v = argVec.v;
	return;
}

fk_GenVector::fk_GenVector(const fk_Vector &argVec)
{
	resize(3);

	v[0] = argVec.x;
	v[1] = argVec.y;
	v[2] = argVec.z;

	return;
}

fk_GenVector::fk_GenVector(const fk_HVector &argVec)
{
	resize(4);

	v[0] = argVec.x;
	v[1] = argVec.y;
	v[2] = argVec.z;
	v[3] = argVec.w;

	return;
}

fk_GenVector & fk_GenVector::operator -(void) const
{
	static fk_GenVector		tmpVec(size());
	_st						i;
	_st						end = static_cast<_st>(size());

	for(i = 0; i < end; ++i) {
		tmpVec.v[i] = -v[i];
	}

	return tmpVec;
}

bool fk_GenVector::operator ==(const fk_GenVector &argVec) const
{
	fk_GenVector		tmp(size());

	if(size() != argVec.size()) return false;
	tmp = *this - argVec;
	if(tmp.norm2() < FK_VECTOREPS) return true;
	return false;
}

bool fk_GenVector::operator !=(const fk_GenVector &argVec) const
{
	fk_GenVector		tmp(size());

	if(size() != argVec.size()) return true;
	tmp = *this - argVec;
	if(tmp.norm2() < FK_VECTOREPS) return false;
	return true;
}

fk_GenVector & fk_GenVector::operator =(const fk_GenVector &tmp)
{
	v = tmp.v;

	return *this;
}

fk_GenVector & fk_GenVector::operator =(const fk_Vector &tmp)
{
	resize(3);
	v[0] = tmp.x;
	v[1] = tmp.y;
	v[2] = tmp.z;

	return *this;
}

fk_GenVector & fk_GenVector::operator =(const fk_HVector &tmp)
{
	resize(4);
	v[0] = tmp.x;
	v[1] = tmp.y;
	v[2] = tmp.z;
	v[3] = tmp.w;

	return *this;
}

fk_GenVector & fk_GenVector::operator *=(double d)
{
	_st		i;
	_st		end = static_cast<_st>(size());

	for(i = 0; i < end; ++i) {
		v[i] *= d;
	}

	return *this;
}

fk_GenVector & fk_GenVector::operator /=(double d)
{
	_st		i;
	_st		end = static_cast<_st>(size());

	if(fabs(d) < FK_VECTOREPS) return *this;
	for(i = 0; i < end; ++i) {
		v[i] /= d;
	}

	return *this;
}

fk_GenVector & fk_GenVector::operator +=(const fk_GenVector &tmp)
{
	_st		i;
	_st		end = static_cast<_st>(size());

	if(end != static_cast<_st>(tmp.size())) return *this;
	for(i = 0; i < end; ++i) {
		v[i] += tmp.v[i];
	}

	return *this;
}

fk_GenVector & fk_GenVector::operator -=(const fk_GenVector &tmp)
{
	_st		i;
	_st		end = static_cast<_st>(size());

	if(end != static_cast<_st>(tmp.size())) return *this;
	for(i = 0; i < end; ++i) {
		v[i] -= tmp.v[i];
	}

	return *this;
}

void fk_GenVector::resize(int argSize)
{
	if(argSize < 0) return;

	v.resize(static_cast<_st>(argSize));
	return;
}

bool fk_GenVector::set(int argID, double argValue)
{
	if(argID < 0 || argID >= size()) return false;
	v[static_cast<_st>(argID)] = argValue;
	return true;
}

int fk_GenVector::size(void) const
{
	return static_cast<int>(v.size());
}

double fk_GenVector::get(int argID) const
{
	if(argID < 0 || argID >= size()) return 0.0;
	return v[static_cast<_st>(argID)];
}

double fk_GenVector::norm(void) const
{
	return sqrt(norm2());
}

double fk_GenVector::norm2(void) const
{
	double	len = 0.0;
	_st		i;
	_st		end = static_cast<_st>(size());

	for(i = 0; i < end; ++i) {
		len += v[i]*v[i];
	}

	return len;
}

bool fk_GenVector::normalize(void)
{
	double		len = norm();
	_st			i;
	_st			end;

	if(len < FK_VECTOREPS) return false;
	end = static_cast<_st>(size());
	for(i = 0; i < end; ++i) {
		v[i] /= len;
	}

	return true;
}

void fk_GenVector::init(bool argFlag)
{
	if(argFlag == true) {
		v.clear();
	} else {
		_st end = static_cast<_st>(size());
		for(_st i = 0; i < end; ++i) {
			v[i] = 0.0;
		}
	}
	return;
}

bool fk_GenVector::isZero(void) const
{
	double		d = norm2();

	if(d < FK_VECTOREPS) return true;
	return false;
}

bool fk_GenVector::replace(int argID, fk_GenVector &argVec)
{
	_st		i, start, end;

	if(argID < 0 || argID + argVec.size() > size()) return false;

	start = static_cast<_st>(argID);
	end = start + static_cast<_st>(argVec.size());

	for(i = start; i < end; ++i) {
		v[i] = argVec.v[i];
	}

	return true;
}

bool fk_GenVector::replace(int argID, fk_Vector &argVec)
{
	if(argID < 0 || argID + 3 > size()) return false;

	v[static_cast<_st>(argID)] = argVec.x;
	v[static_cast<_st>(argID+1)] = argVec.y;
	v[static_cast<_st>(argID+2)] = argVec.z;

	return true;
}

bool fk_GenVector::replace(int argID, fk_HVector &argVec)
{
	if(argID < 0 || argID + 4 > size()) return false;

	v[static_cast<_st>(argID)] = argVec.x;
	v[static_cast<_st>(argID+1)] = argVec.y;
	v[static_cast<_st>(argID+2)] = argVec.z;
	v[static_cast<_st>(argID+3)] = argVec.w;

	return true;
}

bool fk_GenVector::add(int argID, fk_GenVector &argVec)
{
	_st		i, start, end;

	if(argID < 0 || argID + argVec.size() > size()) return false;

	start = static_cast<_st>(argID);
	end = start + static_cast<_st>(argVec.size());

	for(i = start; i < end; ++i) {
		v[i] += argVec.v[i];
	}

	return true;
}

bool fk_GenVector::add(int argID, fk_Vector &argVec)
{
	if(argID < 0 || argID + 3 > size()) return false;

	v[static_cast<_st>(argID)] += argVec.x;
	v[static_cast<_st>(argID+1)] += argVec.y;
	v[static_cast<_st>(argID+2)] += argVec.z;

	return true;
}

bool fk_GenVector::add(int argID, fk_HVector &argVec)
{
	if(argID < 0 || argID + 4 > size()) return false;

	v[static_cast<_st>(argID)] += argVec.x;
	v[static_cast<_st>(argID+1)] += argVec.y;
	v[static_cast<_st>(argID+2)] += argVec.z;
	v[static_cast<_st>(argID+3)] += argVec.w;

	return true;
}

bool fk_GenVector::sub(int argID, fk_GenVector &argVec)
{
	_st		i, start, end;

	if(argID < 0 || argID + argVec.size() > size()) return false;

	start = static_cast<_st>(argID);
	end = start + static_cast<_st>(argVec.size());

	for(i = start; i < end; ++i) {
		v[i] -= argVec.v[i];
	}

	return true;
}

bool fk_GenVector::sub(int argID, fk_Vector &argVec)
{
	if(argID < 0 || argID + 3 > size()) return false;

	v[static_cast<_st>(argID)] -= argVec.x;
	v[static_cast<_st>(argID+1)] -= argVec.y;
	v[static_cast<_st>(argID+2)] -= argVec.z;

	return true;
}

bool fk_GenVector::sub(int argID, fk_HVector &argVec)
{
	if(argID < 0 || argID + 4 > size()) return false;

	v[static_cast<_st>(argID)] -= argVec.x;
	v[static_cast<_st>(argID+1)] -= argVec.y;
	v[static_cast<_st>(argID+2)] -= argVec.z;
	v[static_cast<_st>(argID+3)] -= argVec.w;

	return true;
}

fk_GenVector fk_GenVector::div(int argID, int argNum)
{
	static fk_GenVector		retVec;
	_st						i, start;

	if(argID < 0 || argNum <= 0 || argID + argNum > size()) return retVec;

	retVec.resize(argNum);

	start = static_cast<_st>(argID);
	for(i = 0; i < static_cast<_st>(argNum); ++i) {
		retVec.v[i] = v[i+start];
	}

	return retVec;
}

void fk_GenVector::Print(void) const
{
	_st				i;
	stringstream	ss;

	ss << "Vector = (";
	for(i = 0; i < static_cast<_st>(size()); ++i) {
		ss << v[i];
		if(i != static_cast<_st>(size())-1) ss << ", ";
	}
	ss << ")";

	fk_PutError(ss.str());
	return;
}

void fk_GenVector::Print(string argStr) const
{
	_st				i;
	stringstream	ss;

	ss << "Vector[";
	ss << argStr;
	ss << "] = (";
	for(i = 0; i < static_cast<_st>(size()); ++i) {
		ss << v[i];
		if(i != static_cast<_st>(size())-1) ss << ", ";
	}
	ss << ")";

	fk_PutError(ss.str());
	return;
}

// friend 宣言による外部関数化した二項演算子
namespace FK {
	double operator *(const fk_GenVector &a, const fk_GenVector &b)
	{
		int			size;
		_st			i;
		double		prod;

		if((size = a.size()) != b.size()) return 0.0;
		prod = 0.0;

		for(i = 0; i < static_cast<_st>(size); ++i) {
			prod += a.v[i] * b.v[i];
		}

		return prod;
	}

	fk_GenVector operator +(const fk_GenVector &a, const fk_GenVector &b)
	{
		int				size;
		_st				i;
		fk_GenVector	retVec;

		if((size = a.size()) != b.size()) return retVec;
		retVec.resize(size);

		for(i = 0; i < static_cast<_st>(size); ++i) {
			retVec.v[i] = a.v[i] + b.v[i];
		}

		return retVec;
	}

	fk_GenVector operator -(const fk_GenVector &a, const fk_GenVector &b)
	{
		int				size;
		_st				i;
		fk_GenVector	retVec;

		if((size = a.size()) != b.size()) return retVec;
		retVec.resize(size);

		for(i = 0; i < static_cast<_st>(size); ++i) {
			retVec.v[i] = a.v[i] - b.v[i];
		}

		return retVec;
	}

	fk_GenVector operator *(const fk_GenVector &v, double d)
	{
		fk_GenVector	retVec(v.size());
		_st				i;
		_st				size = static_cast<_st>(v.size());

		for(i = 0; i < size; ++i) {
			retVec.v[i] = v.v[i]*d;
		}

		return retVec;
	}

	fk_GenVector operator *(double d, const fk_GenVector &v)
	{
		fk_GenVector	retVec(v.size());
		_st				i;
		_st				size = static_cast<_st>(v.size());

		for(i = 0; i < size; ++i) {
			retVec.v[i] = v.v[i]*d;
		}

		return retVec;
	}

	fk_GenVector operator /(const fk_GenVector &v, double d)
	{
		fk_GenVector	retVec(v.size());
		_st				i;
		_st				size = static_cast<_st>(v.size());

		if(d < FK_VECTOREPS) return v;
		for(i = 0; i < size; ++i) {
			retVec.v[i] /= d;
		}

		return retVec;
	}

	fk_GenVector operator ^(const fk_GenVector &a, const fk_GenVector &b)
	{
		_st				i, size;
		fk_GenVector	retVec;

		size = static_cast<_st>(a.size());
		if(size < 3 || size != static_cast<_st>(b.size())) return retVec;

		for(i = 0; i < size-2; ++i) {
			retVec.v[i] = a.v[i+1]*b.v[i+2] - a.v[i+2]*b.v[i+1];
		}

		retVec.v[size-2] = a.v[size-1]*b.v[0] - a.v[0]*b.v[size-1];
		retVec.v[size-1] = a.v[0]*b.v[1] - a.v[1]*b.v[0];

		return retVec;
	}
}
