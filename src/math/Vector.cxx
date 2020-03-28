#include <FK/Vector.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;
using namespace FK;

static int dCmp(double a, double b)
{
	if(fabs(a - b) < fk_Vector::VECTOREPS) {
		return 0;
	}

	if(a > b) return 1;
	return -1;
}

fk_Vector::fk_Vector(double dx, double dy, double dz)
{
	x = dx;
	y = dy;
	z = dz;
}

fk_Vector::fk_Vector(const fk_Vector &argVec)
{
	x = argVec.x;
	y = argVec.y;
	z = argVec.z;
}

fk_Vector::fk_Vector(const fk_Vector &&argVec)
{
	x = argVec.x;
	y = argVec.y;
	z = argVec.z;
}

fk_Vector::fk_Vector(const fk_FVector &argFVec)
{
	x = double(argFVec.x);
	y = double(argFVec.y);
	z = double(argFVec.z);
}

fk_Vector::fk_Vector(const fk_FVector &&argFVec)
{
	x = double(argFVec.x);
	y = double(argFVec.y);
	z = double(argFVec.z);
}

void fk_Vector::set(double argX, double argY, double argZ)
{
	x = argX;
	y = argY;
	z = argZ;
	return;
}

fk_Vector & fk_Vector::operator -(void) const
{
	static fk_Vector tmpVec;

	tmpVec.set(-x, -y, -z);

	return tmpVec;
}

bool fk_Vector::operator ==(const fk_Vector &v) const
{
	fk_Vector tmp(v.x - x, v.y - y, v.z - z);
	if(tmp.dist2() < VECTOREPS) {
		return true;
	}
	return false;
}

bool fk_Vector::operator !=(const fk_Vector &v) const
{
	return !(*this == v);
}

bool fk_Vector::operator <(const fk_Vector &v) const
{
	int			status;

	status = dCmp(x, v.x);
	switch(status) {
	  case -1:
		return true;
	  case 1:
		return false;
	}

	status = dCmp(y, v.y);
	switch(status) {
	  case -1:
		return true;
	  case 1:
		return false;
	}

	status = dCmp(z, v.z);
	switch(status) {
	  case -1:
		return true;
	  case 1:
		return false;
	}

	return false;
}

bool fk_Vector::operator >(const fk_Vector &v) const
{
	return (v < *this);
}


bool fk_Vector::operator >=(const fk_Vector &v) const
{
	return !(*this < v);
}

bool fk_Vector::operator <=(const fk_Vector &v) const
{
	return !(*this > v);
}

fk_Vector & fk_Vector::operator =(const fk_Vector &tmp)
{
	x = tmp.x;
	y = tmp.y;
	z = tmp.z;

	return *this;
}

fk_Vector & fk_Vector::operator =(const fk_Vector &&tmp)
{
	x = tmp.x;
	y = tmp.y;
	z = tmp.z;

	return *this;
}

fk_Vector & fk_Vector::operator =(const fk_FVector &tmp)
{
	x = double(tmp.x);
	y = double(tmp.y);
	z = double(tmp.z);

	return *this;
}

fk_Vector & fk_Vector::operator =(const fk_FVector &&tmp)
{
	x = double(tmp.x);
	y = double(tmp.y);
	z = double(tmp.z);

	return *this;
}

fk_Vector & fk_Vector::operator *=(double d)
{
	*this = *this * d;
	return *this;
}

fk_Vector & fk_Vector::operator /=(double d)
{
	*this = *this / d;
	return *this;
}

fk_Vector & fk_Vector::operator +=(const fk_Vector &a)
{
	*this = *this + a;
	return *this;
}

fk_Vector & fk_Vector::operator -=(const fk_Vector &a)
{
	*this = *this - a;
	return *this;
}

fk_Vector & fk_Vector::operator ^=(const fk_Vector &a)
{
	*this = *this ^ a;
	return *this;
}

double fk_Vector::dist(void) const
{
	return(sqrt(dist2()));
}

double fk_Vector::dist2(void) const
{
	return((*this) * (*this));
}

void fk_Vector::init(void)
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	return;
}

bool fk_Vector::isZero(void) const
{
	double	d = dist2();

	if(d < VECTOREPS) return true;
	return false;
}

bool fk_Vector::normalize(void)
{
	double	dd = dist2();

	if(dd < VECTOREPS) {
		return false;
	}

	*this /= sqrt(dd);
	return true;
}

fk_Vector fk_Vector::proj(const fk_Vector &argV) const
{
	fk_Vector	ans;
	double		d;

	d = argV.dist2();
	if(d < VECTOREPS) return ans;

	ans = (((*this) * argV)/d) * argV;
	return ans;
}

fk_Vector fk_Vector::proj(const fk_Vector &&argV) const
{
	fk_Vector	ans;
	double		d;

	d = argV.dist2();
	if(d < VECTOREPS) return ans;

	ans = (((*this) * argV)/d) * argV;
	return ans;
}

fk_Vector fk_Vector::perp(const fk_Vector &argV) const
{
	return ((*this) - proj(argV));
}

fk_Vector fk_Vector::perp(const fk_Vector &&argV) const
{
	return ((*this) - proj(argV));
}

string fk_Vector::OutStr(void) const
{
	stringstream		ss;

	ss << "(" << x << ", " << y << ", " << z << ")";
	return ss.str();
}

void fk_Vector::Print(void) const
{
	fk_PutError("Vector = " + OutStr());
	return;
}

void fk_Vector::Print(string argStr) const
{
	fk_PutError("Vector[" + argStr + "] = " + OutStr());
	return;
}

fk_HVector::fk_HVector(void)
{
	set(0.0, 0.0, 0.0, 1.0);
	return;
}

fk_HVector::fk_HVector(const fk_Vector &p, double dw)
{
	set(p.x, p.y, p.z, dw);
	return;
}

fk_HVector::fk_HVector(const fk_Vector &&p, double dw)
{
	set(p.x, p.y, p.z, dw);
	return;
}

fk_HVector::fk_HVector(double argX, double argY, double argZ, double argW)
{
	set(argX, argY, argZ, argW);
	return;
}

fk_HVector::fk_HVector(const fk_HVector &argHVec)
	: fk_Vector(argHVec.x, argHVec.y, argHVec.z)
{
	w = argHVec.w;
}

fk_HVector::fk_HVector(const fk_HVector &&argHVec)
	: fk_Vector(argHVec.x, argHVec.y, argHVec.z)
{
	w = argHVec.w;
}

bool fk_HVector::operator ==(const fk_HVector &a) const
{
	if(a.getV() == this->getV() &&
	   a.w - w < VECTOREPS && a.w - w > -VECTOREPS) {
		return true;
	} else {
		return false;
	}
}

bool fk_HVector::operator !=(const fk_HVector &a) const
{
	return !(*this == a);
}

fk_HVector & fk_HVector::operator =(const fk_HVector &tmp)
{
	x = tmp.x;
	y = tmp.y;
	z = tmp.z;
	w = tmp.w;

	return *this;
}

fk_HVector & fk_HVector::operator =(const fk_HVector &&tmp)
{
	x = tmp.x;
	y = tmp.y;
	z = tmp.z;
	w = tmp.w;

	return *this;
}

fk_HVector & fk_HVector::operator =(const fk_Vector &tmp)
{
	x = tmp.x;
	y = tmp.y;
	z = tmp.z;
	w = 1.0;

	return *this;
}

fk_HVector & fk_HVector::operator =(const fk_Vector &&tmp)
{
	x = tmp.x;
	y = tmp.y;
	z = tmp.z;
	w = 1.0;

	return *this;
}

void fk_HVector::set(const fk_Vector &a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = 1.0;
}

void fk_HVector::set(const fk_Vector &&a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = 1.0;
}

void fk_HVector::set(const fk_Vector &a, double weight)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = weight;
}

void fk_HVector::set(const fk_Vector &&a, double weight)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = weight;
}

void fk_HVector::set(double dx, double dy, double dz)
{
	x = dx;
	y = dy;
	z = dz;
	w = 1.0;
}

void fk_HVector::set(double dx, double dy, double dz, double dw)
{
	x = dx;
	y = dy;
	z = dz;
	w = dw;
}

fk_Vector fk_HVector::getV(void) const
{
	return fk_Vector(x, y, z);
}	 

void fk_HVector::setw(double dw)
{
	w = dw;
}

double fk_HVector::getw(void) const
{
	return(w);
}

void fk_HVector::ispos(void)
{
	w = 1.0;
	return;
}

void fk_HVector::isvec(void)
{
	w = 0.0;
	return;
}

void fk_HVector::init(void)
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 1.0;
}

string fk_HVector::OutStr(void) const
{
	stringstream		ss;

	ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
	return ss.str();
}

void fk_HVector::Print(void) const
{
	fk_PutError("HVector = " + OutStr());
}

void fk_HVector::Print(string argStr) const
{
	fk_PutError("HVector[" + argStr + "] = " + OutStr());
	return;
}

fk_FVector::fk_FVector(void)
{
	x = y = z = 0.0f;

	return;
}

fk_FVector::fk_FVector(const fk_FVector &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

fk_FVector::fk_FVector(const fk_FVector &&v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

fk_FVector::fk_FVector(const fk_Vector &v)
{
	x = float(v.x);
	y = float(v.y);
	z = float(v.z);
}

fk_FVector::fk_FVector(const fk_Vector &&v)
{
	x = float(v.x);
	y = float(v.y);
	z = float(v.z);
}

fk_FVector & fk_FVector::operator =(const fk_Vector &v)
{
	x = float(v.x);
	y = float(v.y);
	z = float(v.z);

	return *this;
}

fk_FVector & fk_FVector::operator =(const fk_Vector &&v)
{
	x = float(v.x);
	y = float(v.y);
	z = float(v.z);

	return *this;
}

// friend 宣言による外部関数化した二項演算子
namespace FK {
	double operator *(const fk_Vector &a, const fk_Vector &b)
	{
		return (a.x*b.x + a.y*b.y + a.z*b.z);
	}

	double operator *(const fk_HVector &a, const fk_HVector &b)
	{
		return (a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w);
	}

	fk_Vector operator +(const fk_Vector &a, const fk_Vector &b)
	{
		return fk_Vector(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	fk_Vector operator -(const fk_Vector &a, const fk_Vector &b)
	{
		return fk_Vector(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	fk_Vector operator *(const fk_Vector &a, double t)
	{
		return fk_Vector(a.x * t, a.y * t, a.z * t);
	}

	fk_Vector operator *(double t, const fk_Vector &a)
	{
		return (a * t);
	}

	fk_Vector operator /(const fk_Vector &a, double t)
	{
		return (a * (1.0/t));
	}

	fk_Vector operator ^(const fk_Vector &a, const fk_Vector &b)
	{
		fk_Vector tmp(a.y * b.z - a.z * b.y,
					  a.z * b.x - a.x * b.z,
					  a.x * b.y - a.y * b.x);
		return(tmp);
	}
}

fk_TexCoord::fk_TexCoord(double argX, double argY)
{
	set(argX, argY);
}

fk_TexCoord::fk_TexCoord(const fk_TexCoord &argCoord)
{
	x = argCoord.x;
	y = argCoord.y;
}

fk_TexCoord & fk_TexCoord::operator =(const fk_TexCoord &argCoord)
{
	x = argCoord.x;
	y = argCoord.y;

	return *this;
}

bool fk_TexCoord::operator ==(const fk_TexCoord &c) const
{
	fk_TexCoord	tmp(c.x - x, c.y - y);
	if(tmp.x * tmp.x + tmp.y * tmp.y < float(fk_Vector::VECTOREPS)) return true;
	return false;
}

bool fk_TexCoord::operator !=(const fk_TexCoord &c) const
{
	return !(*this == c);
}

void fk_TexCoord::set(double argX, double argY)
{
	x = float(argX);
	y = float(argY);
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
