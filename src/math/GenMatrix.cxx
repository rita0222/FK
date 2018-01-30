/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
#include <FK/GenMatrix.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;
using namespace FK;

// 0 との比較関数 (実数用) 
inline bool AlmostZero(double x)
{
	if(x < FK_MATRIX_EPS && x > -FK_MATRIX_EPS) return true;
	return false;
}

// 実数比較 
inline bool AlmostEqual(double x, double y)
{
	return(AlmostZero(x - y));
}

void CopyMatrix(_st deg, vector<double> &m1, const vector<double> &m2)
{
	_st		i;
	for(i = 0; i < deg*deg; ++i) {
		m1[i] = m2[i];
	}
	return;
}

static void AddMatrix(_st deg, vector<double> &m1, const vector<double> &m2)
{
	_st		i;
	for(i = 0; i < deg*deg; ++i) {
		m1[i] += m2[i];
	}
	return;
}

static void SubMatrix(_st deg, vector<double> &m1, const vector<double> &m2)
{
	_st		i;
	for(i = 0; i < deg*deg; ++i) {
		m1[i] -= m2[i];
	}
	return;
}

static void MultMatrix(_st deg, vector<double> &m1,
					   const vector<double> &m2, const vector<double> &m3)
{
	_st		i, j, k;
	
	for(i = 0; i < deg*deg; ++i) m1[i] = 0.0;
	
	for(i = 0; i < deg; ++i) {
		for(j = 0; j < deg; ++j) {
			for(k = 0; k < deg; ++k) {
				m1[i*deg + j] += m2[i*deg + k] * m3[k*deg + j];
			}
		}
	}
	return;
}

// 逆行列演算 LU 分解関数 1 
static bool LUDecomposition(_st deg, vector<double> &mat,
							vector<int> &index)
{
	_st		i, iMax, j, k;
	double	big, dum, sum, tmp;

	static vector<double>	vv;

	if(vv.size() < deg) vv.resize(deg);

	// Get Scaling Information.;

	iMax = 0;
	for(i = 0; i < deg; ++i) {
		big = 0.0;
		for(j = 0; j < deg; ++j) {
			tmp = fabs(mat[i*deg+j]);
			if(tmp > big) big = tmp;
		}
		if(AlmostZero(big) == true) {
			return false;
		}
		vv[i] = 1.0/big;
	}
	
	// Crout's Algorithm ';

	for(j = 0; j < deg; ++j) {
		for(i = 0; i < j; ++i) {
			sum = mat[i*deg+j];
			for(k = 0; k < i; ++k) {
				sum -= mat[i*deg+k]*mat[k*deg+j];
			}
			mat[i*deg+j] = sum;
		}
	
		big = 0.0;
		for(i = j; i < deg; ++i) {
			sum = mat[i*deg+j];
			for(k = 0; k < j; ++k) {
				sum -= mat[i*deg+k]*mat[k*deg+j];
			}
			mat[i*deg+j] = sum;
			dum = vv[i]*fabs(sum);
			if(dum >= big) {
				big = dum;
				iMax = i;
			}
		}
		if(j != iMax) {
			// Row Exchange;
			for(k = 0; k < deg; ++k) {
				dum = mat[iMax*deg+k];
				mat[iMax*deg+k] = mat[j*deg+k];
				mat[j*deg+k] = dum;
			}
			vv[iMax] = vv[j];
		}
	
		index[j] = static_cast<int>(iMax);

		if(AlmostZero(mat[j*deg+j]) == true) {
			mat[j*deg+j] = FK_MATRIX_EPS2;
		}

		if(j != deg-1) {
			dum = 1.0/(mat[j*deg+j]);
			for(i = j+1; i < deg; ++i) mat[i*deg+j] *= dum;
		}
	}

	return true;
}

// 逆行列演算 LU 分解関数 2 
static void LUBackSubsutitution(_st deg,
								vector<double> &mat,
								vector<int> &index,
								vector<double> &vec)
{
	_st		i, ip, j;
	bool	iFlg;
	double	sum;
	int		k;

	iFlg = false;

	for(i = 0; i < deg; ++i) {
		// Forward Subsutitution;
		ip = static_cast<_st>(index[i]);
		sum = vec[ip];
		vec[ip] = vec[i];
		if(iFlg == false) {
			for(j = 0; j < i; ++j) {
				sum -= mat[i*deg+j]*vec[j];
			}
		} else if(AlmostZero(sum) == true) iFlg = true;
		vec[i] = sum;
	}
	
	for(k = static_cast<int>(deg)-1; k >= 0; --k) {
		i = static_cast<_st>(k);
		// Backward Subsutitution;
		sum = vec[i];
		for(j = i+1; j < deg; ++j) sum -= mat[i*deg+j]*vec[j];
		vec[i] = sum/mat[i*deg+i];
	}
}

// 行列展開用関数 (retVec = Mat*argVec) 
void fk_GenMatrix::MultVec(fk_GenVector &retVec,
						   const fk_GenVector &argVec) const
{
	_st		i, j;

	for(i = 0; i < deg; ++i) {
		retVec.v[i] = 0.0;
		for(j = 0; j < deg; ++j) {
			retVec.v[i] += argVec.v[j]*m[i*deg+j];
		}
	}
	return;
}

void fk_GenMatrix::MakeIdentMatrix(void)
{
	_st		i;

	for(i = 0; i < deg*deg; ++i) m[i] = 0.0;

	for(i = 0; i < deg; ++i) {
		m[i*deg + i] = 1.0;
	}
	return;
}

void fk_GenMatrix::MakeZeroMatrix(void)
{
	_st		i;

	for(i = 0; i < deg*deg; ++i) {
		m[i] = 0.0;
	}
	return;
}

// 逆行列演算 LU 分解関数本体 
bool fk_GenMatrix::MatrixInverse(void)
{
	_st						i, j;
	static vector<double>	vec;
	static vector<double>	dummy;
	static vector<double>	mat;
	static vector<int>		index;

	if(index.size() < deg) {
		mat.resize(deg*deg);
		vec.resize(deg);
		dummy.resize(deg*deg);
		index.resize(deg);
	}
	
	for(i = 0; i < deg*deg; ++i) mat[i] = m[i];

	if(LUDecomposition(deg, mat, index) == false) {
		return false;
	}

	for(i = 0; i < deg; ++i) {
		if(AlmostZero(mat[i*deg+i]) == true) {
			return false;
		}
	}

	for(j = 0; j < deg; ++j) {
		for(i = 0; i < deg; ++i) vec[i] = 0.0;
		vec[j] = 1.0;
		LUBackSubsutitution(deg, mat, index, vec);
		for(i = 0; i < deg; ++i) dummy[i*deg+j] = vec[i];
	}
	
	for(i = 0; i < deg*deg; ++i) m[i] = dummy[i];

	return true;
}

fk_GenMatrix::fk_GenMatrix(int argDeg)
{
	setDeg(argDeg);
	return;
}

fk_GenMatrix::fk_GenMatrix(const fk_GenMatrix &argM)
{
	_st		i;

	setDeg(static_cast<int>(argM.deg));
	for(i = 0; i < deg*deg; ++i) {
		m[i] = argM.m[i];
	}
}

void fk_GenMatrix::init(bool argFlg)
{
	if(argFlg == true) {
		MakeIdentMatrix();
	} else {
		MakeZeroMatrix();
	}

	return;
}

void fk_GenMatrix::setDeg(int argDeg)
{
	if(argDeg < 0) {
		deg = 0;
		m.clear();
	} else {
		deg = static_cast<_st>(argDeg);
		m.resize(deg*deg);
	}
	init();

	return;
}

int fk_GenMatrix::getDeg(void) const
{
	return static_cast<int>(deg);
}

void fk_GenMatrix::set(int argRow, int argCol, double argValue)
{
	_st		index = static_cast<_st>(argRow)*deg + static_cast<_st>(argCol);

	if(argRow < 0 || argRow >= static_cast<int>(deg) ||
	   argCol < 0 || argCol >= static_cast<int>(deg)) return;
	m[index] = argValue;
	return;
}

double fk_GenMatrix::get(int argRow, int argCol) const
{
	_st		index = static_cast<_st>(argRow)*deg + static_cast<_st>(argCol);

	if(argRow < 0 || argRow >= static_cast<int>(deg) ||
	   argCol < 0 || argCol >= static_cast<int>(deg)) return 0.0;
	return m[index];
}

bool fk_GenMatrix::inverse(void)
{
	return MatrixInverse();
}

void fk_GenMatrix::negate(void)
{
	_st		i, j;
	double	tmp;

	for(i = 0; i < deg; ++i) {
		for(j = 0; j < i; ++j) {
			tmp = m[i*deg + j];
			m[i*deg + j] = m[j*deg + i];
			m[j*deg + i] = tmp;
		}
	}

	return;
}

bool fk_GenMatrix::isSingular(void) const
{
	static vector<double>	mat;
	static vector<int>		index;
	_st						i;

	if(index.size() < deg) {
		mat.resize(deg*deg);
		index.resize(deg);
	}

	for(i = 0; i < deg*deg; ++i) mat[i] = m[i];

	if(LUDecomposition(deg, mat, index) == false) {
		return false;
	}

	for(i = 0; i < deg; ++i) {
		if(AlmostZero(mat[i*deg+i]) == true) {
			return true;
		}
	}

	return false;
}

bool fk_GenMatrix::isRegular(void) const
{
	return (!isSingular());
}

fk_GenMatrix fk_GenMatrix::operator !(void) const
{
	fk_GenMatrix	ret;
	ret = *this;
	ret.inverse();
	return ret;
}

bool fk_GenMatrix::operator ==(const fk_GenMatrix &argMat) const
{
	_st		i;
	
	if(deg != argMat.deg) return false;
	for(i = 0; i < deg*deg; ++i) {
		if(AlmostEqual(m[i], argMat.m[i]) == false) return false;
	}
	return true;
}

bool fk_GenMatrix::operator !=(const fk_GenMatrix &argMat) const
{
	_st 	i;
	
	if(deg != argMat.deg) return true;
	for(i = 0; i < deg*deg; ++i) {
		if(AlmostEqual(m[i], argMat.m[i]) == false) return true;
	}
	return false;
}

fk_GenMatrix & fk_GenMatrix::operator =(const fk_GenMatrix &argMat)
{
	setDeg(static_cast<int>(argMat.deg));
	CopyMatrix(deg, m, argMat.m);
	return *this;
}

fk_GenMatrix & fk_GenMatrix::operator *=(const fk_GenMatrix &argMat)
{
	fk_GenMatrix	tmp;
	
	if(deg != argMat.deg) return *this;
	tmp = *this * argMat;
	*this = tmp;
	return *this;
}

fk_GenVector & fk_GenVector::operator *=(const fk_GenMatrix &argMat)
{
	fk_GenVector	tmp;
	int				deg;
	
	deg = size();
	if(deg != static_cast<int>(argMat.deg)) return *this;
	tmp.resize(deg);
	argMat.MultVec(tmp, *this);
	*this = tmp;
	return *this;
}

fk_GenMatrix & fk_GenMatrix::operator +=(const fk_GenMatrix &argMat)
{
	if(deg != argMat.deg) return *this;
	AddMatrix(deg, m, argMat.m);
	return *this;
}

fk_GenMatrix & fk_GenMatrix::operator -=(const fk_GenMatrix &argMat)
{
	if(deg != argMat.deg) return *this;
	SubMatrix(deg, m, argMat.m);
	return *this;
}

void fk_GenMatrix::Print(string argStr) const
{
	_st				i, j;
	stringstream	ss;

	if(argStr.size() == 0) {
		fk_PutError("Matrix = ");
	} else {
		fk_PutError("Matrix[" + argStr + "] = ");
	}

	for(i = 0; i < deg; ++i) {
		ss.clear();
		ss << "\t| ";
		for(j = 0; j < deg; ++j) {
			ss << m[i*deg + j] << " ";
		}
		ss << "|";
		fk_PutError(ss.str());
	}

	return;
}

namespace FK {
	fk_GenVector operator *(const fk_GenMatrix &mat, const fk_GenVector &vec)
	{
		fk_GenVector	ret(0);

		if(vec.size() != mat.getDeg()) return ret;
		ret.resize(vec.size());

		mat.MultVec(ret, vec);
		return ret;
	}

	fk_GenMatrix operator +(const fk_GenMatrix &m1, const fk_GenMatrix &m2)
	{
		fk_GenMatrix	ret;

		if(m1.deg != m2.deg) return ret;
		ret = m1;
		AddMatrix(m1.deg, ret.m, m2.m);
		return ret;
	}

	fk_GenMatrix operator -(const fk_GenMatrix &m1, const fk_GenMatrix &m2)
	{
		fk_GenMatrix	ret;

		if(m1.deg != m2.deg) return ret;
		ret = m1;
		SubMatrix(m1.deg, ret.m, m2.m);
		return ret;
	}

	fk_GenMatrix operator *(const fk_GenMatrix &m1, const fk_GenMatrix &m2)
	{
		fk_GenMatrix	ret;

		if(m1.deg != m2.deg) return ret;
		ret.setDeg(static_cast<int>(m1.deg));
		MultMatrix(m1.deg, ret.m, m1.m, m2.m);
		return ret;
	}
}
