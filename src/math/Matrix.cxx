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
#include <FK/Matrix.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;

///////////// inline 関数群 

// 0 との比較関数 (実数用) 
inline bool AlmostZero(double x)
{
	if(x < FK_MATRIX_EPS && x > -FK_MATRIX_EPS) return true;
	else return false;
}


// 実数比較 
inline bool AlmostEqual(double x, double y)
{
	return(AlmostZero(x - y));
}

// 行列展開用関数 (retHVector = Mat*argHVector) 
void fk_OrthoMatrix::MultVec(fk_HVector &retHVector,
							const fk_HVector &argHVector) const
{
	int			i, j;
	double		Vec[4];
	double		Ret[4];

	Vec[0] = argHVector.x;
	Vec[1] = argHVector.y;
	Vec[2] = argHVector.z;
	Vec[3] = argHVector.w;

	for(i = 0; i < 4; ++i) {
		Ret[i] = 0.0;
		for(j = 0; j < 4; ++j) {
			Ret[i] += Vec[j]*m[i][j];
		}
	}

	retHVector.set(Ret[0], Ret[1], Ret[2], Ret[3]);
}


// 単位行列生成用 static 関数 
static void MakeIdentMatrix(double Mat[4][4])
{
	int		i, j;

	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			if(i == j) Mat[i][j] = 1.0;
			else Mat[i][j] = 0.0;
		}
	}
}

// 零行列生成用 static 関数 
static void MakeZeroMatrix(double Mat[4][4])
{
	int		i, j;

	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			Mat[i][j] = 0.0;
		}
	}
}

// 逆行列演算 LU 分解関数 1 
static bool fk_LUDecomposition(double Mat[4][4], int index[4])
{
	int		i, iMax, j, k;
	double	big, dum, sum, tmp;
	double	vv[4];
	
	
	// Get Scaling Information.;

	iMax = 0;
	for(i = 0; i < 4; ++i) {
		big = 0.0;
		for(j = 0; j < 4; ++j) {
			tmp = fabs(Mat[i][j]);
			if(tmp > big) big = tmp;
		}
		if(AlmostZero(big) == true) {
			return false;
		}
		vv[i] = 1.0/big;
	}
	
	// Crout's Algorithm ';

	for(j = 0; j < 4; ++j) {
		for(i = 0; i < j; ++i) {
			sum = Mat[i][j];
			for(k = 0; k < i; ++k) {
				sum -= Mat[i][k]*Mat[k][j];
			}
			Mat[i][j] = sum;
		}
	
		big = 0.0;
		for(i = j; i < 4; ++i) {
			sum = Mat[i][j];
			for(k = 0; k < j; ++k) {
				sum -= Mat[i][k]*Mat[k][j];
			}
			Mat[i][j] = sum;
			dum = vv[i]*fabs(sum);
			if(dum >= big) {
				big = dum;
				iMax = i;
			}
		}
		if(j != iMax) {
			// Row Exchange;
			for(k = 0; k < 4; ++k) {
				dum = Mat[iMax][k];
				Mat[iMax][k] = Mat[j][k];
				Mat[j][k] = dum;
			}
			vv[iMax] = vv[j];
		}
	
		index[j] = iMax;

		if(AlmostZero(Mat[j][j]) == true) {
			Mat[j][j] = FK_MATRIX_EPS2;
		}

		if(j != 3) {
			dum = 1.0/(Mat[j][j]);
			for(i = j+1; i < 4; ++i) Mat[i][j] *= dum;
		}
	}
	return true;
}

// 逆行列演算 LU 分解関数 2 
static void fk_LUBackSubsutitution(double mat[4][4], 
								   int index[4], double vector[4])
{
	int		i, ip, j;
	bool	iFlg;
	double	sum;
	
	iFlg = false;

	for(i = 0; i < 4; ++i) {
		// Forward Subsutitution;
		ip = index[i];
		sum = vector[ip];
		vector[ip] = vector[i];
		if(iFlg == false) {
			for(j = 0; j < i; ++j) {
				sum -= mat[i][j]*vector[j];
			}
		} else if(AlmostZero(sum) == true) iFlg = true;
		vector[i] = sum;
	}
	
	for(i = 3; i >= 0; --i) {
		// Backward Subsutitution;
		sum = vector[i];
		for(j = i+1; j < 4; ++j) sum -= mat[i][j]*vector[j];
		vector[i] = sum/mat[i][i];
	}
}

// 逆行列演算 LU 分解関数本体 
static bool fk_MatrixInverse(double mat[4][4])
{
	double	dummy[4][4], vector[4];
	int		i, j, index[4];
	
	if(fk_LUDecomposition(mat, index) == false) return false;

	for(i = 0; i < 4; ++i) {
		if(AlmostZero(mat[i][i]) == true) {
			return false;
		}
	}

	for(j = 0; j < 4; ++j) {
		for(i = 0; i < 4; ++i) vector[i] = 0.0;
		vector[j] = 1.0;
		fk_LUBackSubsutitution(mat, index, vector);
		for(i = 0; i < 4; ++i) dummy[i][j] = vector[i];
	}
	
	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) mat[i][j] = dummy[i][j];
	}

	return true;
}

// 直交行列用逆行列演算 
static void fk_OrthoMatrixInverse(double mat[4][4])
{
	double	t[3], tmp;
	int		i, j;

	for(i = 0; i < 3; ++i) {
		t[i] = mat[i][3];
	}

	mat[0][3] = -mat[0][0]*t[0] - mat[1][0]*t[1] - mat[2][0]*t[2];
	mat[1][3] = -mat[0][1]*t[0] - mat[1][1]*t[1] - mat[2][1]*t[2];
	mat[2][3] = -mat[0][2]*t[0] - mat[1][2]*t[1] - mat[2][2]*t[2];

	for(i = 1; i < 3; ++i) {
		for(j = 0; j < i; ++j) {
			tmp = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = tmp;
		}
	}

	return;
}


// 行列複写 (m1 = m2) 
static void CopyMatrix(double m1[4][4], const double m2[4][4])
{
	int		i, j;

	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			m1[i][j] = m2[i][j];
		}
	}
}

// 行列和 (m1 += m2) 
static void AddMatrix(double m1[4][4], const double m2[4][4])
{
	int		i, j;

	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			m1[i][j] += m2[i][j];
		}
	}
}


// 行列差 (m1 -= m2) 
static void SubMatrix(double m1[4][4], const double m2[4][4])
{
	int		i, j;

	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			m1[i][j] -= m2[i][j];
		}
	}
}


// 行列積 (m1 = m2 * m3, 但し m1 と m2, m3 は同一ではいけない。) 
static void MultMatrix(double m1[4][4],
					   const double m2[4][4], const double m3[4][4])
{
	int		i, j, k;


	MakeZeroMatrix(m1);

	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			for(k = 0; k < 4; ++k) {
				m1[i][j] += m2[i][k] * m3[k][j];
			}
		}
	}
}


////////// 直交行列用メンバ関数群 

// コンストラクタ 
fk_OrthoMatrix::fk_OrthoMatrix(void)
	: buf(nullptr), updateStatus(true)
{
	MakeIdentMatrix(m);
}

// コピーコンストラクタ 
fk_OrthoMatrix::fk_OrthoMatrix(const fk_OrthoMatrix &ArgMat)
{
	CopyMatrix(m, ArgMat.m);
}

fk_OrthoMatrix::~fk_OrthoMatrix()
{
	if(buf != nullptr) delete [] buf;
}

// 初期化関数 (単位行列の生成) 
void fk_OrthoMatrix::init(void)
{
	MakeIdentMatrix(m);
	updateStatus = true;
	return;
}

void fk_OrthoMatrix::set(int argR, int argC, double argValue)
{
	if(argR < 0 || argR > 3 || argC < 0 || argC > 3) {
		fk_PutError("fk_OrthoMatrix", "set", 1, "ID Error");
		return;
	}

	m[argR][argC] = argValue;

	updateStatus = true;
	return;
}

void fk_OrthoMatrix::setRow(int argR, const fk_Vector &argV)
{
	if(argR < 0 || argR > 3) {
		fk_PutError("fk_OrthoMatrix", "setRow", 1, "ID Error");
		return;
	}

	m[argR][0] = argV.x;
	m[argR][1] = argV.y;
	m[argR][2] = argV.z;

	updateStatus = true;
	return;
}

void fk_OrthoMatrix::setRow(int argR, const fk_HVector &argV)
{
	if(argR < 0 || argR > 3) {
		fk_PutError("fk_OrthoMatrix", "setRow", 2, "ID Error");
		return;
	}

	m[argR][0] = argV.x;
	m[argR][1] = argV.y;
	m[argR][2] = argV.z;
	m[argR][3] = argV.w;

	updateStatus = true;
	return;
}

void fk_OrthoMatrix::setCol(int argC, const fk_Vector &argV)
{
	if(argC < 0 || argC > 3) {
		fk_PutError("fk_OrthoMatrix", "setCol", 1, "ID Error");
		return;
	}

	m[0][argC] = argV.x;
	m[1][argC] = argV.y;
	m[2][argC] = argV.z;

	updateStatus = true;
	return;
}

void fk_OrthoMatrix::setCol(int argC, const fk_HVector &argV)
{
	if(argC < 0 || argC > 3) {
		fk_PutError("fk_OrthoMatrix", "setCol", 2, "ID Error");
		return;
	}

	m[0][argC] = argV.x;
	m[1][argC] = argV.y;
	m[2][argC] = argV.z;
	m[3][argC] = argV.w;

	updateStatus = true;
	return;
}

fk_HVector fk_OrthoMatrix::getRow(int argR)
{
	fk_HVector	retV;

	if(argR < 0 || argR > 3) {
		fk_PutError("fk_OrthMatrix", "getRow", 1, "ID Error");
		return retV;
	}
	retV.set(m[argR][0], m[argR][1], m[argR][2], m[argR][3]);

	return retV;
}

fk_HVector fk_OrthoMatrix::getCol(int argC)
{
	fk_HVector	retV;

	if(argC < 0 || argC > 3) {
		fk_PutError("fk_OrthMatrix", "getCol", 1, "ID Error");
		return retV;
	}
	retV.set(m[0][argC], m[1][argC], m[2][argC], m[3][argC]);

	return retV;
}

bool fk_OrthoMatrix::inverse(void)
{
	fk_OrthoMatrixInverse(m);

	updateStatus = true;
	return true;
}

void fk_OrthoMatrix::negate(void)
{
	int			i, j;
	double		tmp;

	for(i = 1; i < 4; ++i) {
		for(j = 0; j < i; ++j) {
			tmp = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = tmp;
		}
	}

	updateStatus = true;
	return;
}

void fk_OrthoMatrix::makeRot(double Angle, fk_Axis Axis)
{
	MakeIdentMatrix(m);

	double sinValue = sin(Angle);
	double cosValue = cos(Angle);

	switch(Axis) {
	  case fk_X:
		m[1][1] =  cosValue; m[1][2] = -sinValue;
		m[2][1] =  sinValue; m[2][2] =	cosValue;
		break;

	  case fk_Y:
		m[0][0] =  cosValue; m[0][2] =	sinValue;
		m[2][0] = -sinValue; m[2][2] =	cosValue;
		break;

	  case fk_Z:
		m[0][0] =  cosValue; m[0][1] = -sinValue;
		m[1][0] =  sinValue; m[1][1] =	cosValue;
		break;
	  default:
		break;
	}

	updateStatus = true;
	return;
}

void fk_OrthoMatrix::makeTrans(double x, double y, double z)
{
	MakeIdentMatrix(m);

	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;

	updateStatus = true;
	return;
}

void fk_OrthoMatrix::makeTrans(const fk_Vector &Vec)
{
	MakeIdentMatrix(m);

	m[0][3] = Vec.x;
	m[1][3] = Vec.y;
	m[2][3] = Vec.z;

	updateStatus = true;
	return;
}


void fk_OrthoMatrix::makeEuler(double h, double p, double b)
{
	fk_OrthoMatrix	hM, pM, bM;

	hM.makeRot(-h, fk_Y);
	pM.makeRot(p, fk_X);
	bM.makeRot(-b, fk_Z);

	*this = hM * pM * bM;

	updateStatus = true;
	return;
}

void fk_OrthoMatrix::makeEuler(const fk_Angle &argAngle)
{
	makeEuler(argAngle.h, argAngle.p, argAngle.b);
	return;
}

void fk_OrthoMatrix::Print(string argStr) const
{
	int				i, j;
	stringstream	ss;

	if(argStr.size() == 0) {
		fk_PutError("Matrix = ");
	} else {
		fk_PutError("Matrix[" + argStr + "] = ");
	}

	ss.clear();
	for(i = 0; i < 4; ++i) {
		ss << "t| ";
		for(j = 0; j < 4; ++j) ss << m[i][j] << " ";
		ss << "|";
		if(i != 3) ss << endl;
	}
	fk_PutError(ss.str());
	return;
}

float * fk_OrthoMatrix::GetBuffer(void)
{
	if(buf == nullptr) buf = new float[16];
	if(updateStatus == true) {
		for(int i = 0; i < 16; ++i) {
			buf[i] = float(m[i%4][i/4]);
		}
		updateStatus = false;
	}
	return buf;
}


fk_OrthoMatrix fk_OrthoMatrix::operator !(void) const
{
	fk_OrthoMatrix	ret;
	ret = *this;
	ret.inverse();
	return ret;
}

double * fk_OrthoMatrix::operator [](int index)
{
	return m[index];
}

// 比較演算子 
bool fk_OrthoMatrix::operator ==(const fk_OrthoMatrix &Mat) const
{
	int		i, j;

	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			if(AlmostEqual(m[i][j], Mat.m[i][j]) == false) return false;
		}
	}

	return true;
}

bool fk_OrthoMatrix::operator !=(const fk_OrthoMatrix &Mat) const
{
	int		i, j;

	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			if(AlmostEqual(m[i][j], Mat.m[i][j]) == false) return true;
		}
	}

	return false;
}

// 代入演算子 
fk_OrthoMatrix & fk_OrthoMatrix::operator =(const fk_OrthoMatrix &ArgMat)
{
	CopyMatrix(m, ArgMat.m);

	updateStatus = true;
	return *this;
}

fk_OrthoMatrix & fk_OrthoMatrix::operator *=(const fk_OrthoMatrix &ArgMat)
{
	fk_OrthoMatrix tmp;

	MultMatrix(tmp.m, m, ArgMat.m);
	CopyMatrix(m, tmp.m);

	updateStatus = true;
	return *this;
}

fk_Vector & fk_Vector::operator *=(const fk_OrthoMatrix &argMat)
{
	fk_HVector	tmp1, tmp2;
	tmp1 = *this;
	argMat.MultVec(tmp2, tmp1);
	*this = tmp2;

	return *this;
}

fk_HVector & fk_HVector::operator *=(const fk_OrthoMatrix &argMat)
{
	fk_HVector	tmp = *this;
	argMat.MultVec(*this, tmp);
	return *this;
}

// 二項演算子 
namespace FK {
	fk_HVector operator *(const fk_OrthoMatrix &Mat, const fk_HVector &Vec)
	{
		fk_HVector Ret;

		Mat.MultVec(Ret, Vec);

		return Ret;
	}

	fk_OrthoMatrix operator *(const fk_OrthoMatrix &m1, const fk_OrthoMatrix &m2)
	{
		fk_OrthoMatrix Ret;

		MultMatrix(Ret.m, m1.m, m2.m);

		return Ret;
	}
}

/////////// 4x4 汎用行列クラス 

// コンストラクタ 
fk_Matrix::fk_Matrix(void)
{
	MakeIdentMatrix(m);
}

// コピーコンストラクタ 
fk_Matrix::fk_Matrix(const fk_Matrix &argMat)
	: fk_OrthoMatrix()
{
	CopyMatrix(m, argMat.m);
}

// 逆行列演算関数 
bool fk_Matrix::inverse(void)
{
	if(fk_MatrixInverse(m)) {
		updateStatus = true;
		return true;
	}
	return false;
}

// 特異行列判定関数 
bool fk_Matrix::isSingular(void) const
{
	int			i;
	double		mat[4][4];
	int			index[4];

	CopyMatrix(mat, m);

	if(fk_LUDecomposition(mat, index) == false) return true;
	for(i = 0; i < 4; ++i) {
		if(AlmostZero(mat[i][i]) == true) {
			return true;
		}
	}

	return false;
}

bool fk_Matrix::isRegular(void) const
{
	return (!isSingular());
}

// 拡大縮小行列生成関数 
void fk_Matrix::makeScale(double x, double y, double z)
{
	MakeIdentMatrix(m);
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;

	updateStatus = true;
	return;
}

void fk_Matrix::makeScale(const fk_Vector &Vec)
{
	MakeIdentMatrix(m);
	m[0][0] = Vec.x;
	m[1][1] = Vec.y;
	m[2][2] = Vec.z;

	return;
}

// 逆行列出力演算子 
fk_Matrix fk_Matrix::operator !(void) const
{
	fk_Matrix		ret;
	ret = *this;
	ret.inverse();
	return ret;
}

// 比較演算子 
bool fk_Matrix::operator ==(const fk_Matrix &Mat) const
{
	int		i, j;

	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			if(AlmostEqual(m[i][j], Mat.m[i][j]) == false) return false;
		}
	}

	return true;
}

bool fk_Matrix::operator !=(const fk_Matrix &Mat) const
{
	int		i, j;

	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			if(AlmostEqual(m[i][j], Mat.m[i][j]) == false) return true;
		}
	}

	return false;
}

// 代入演算子 
fk_Matrix & fk_Matrix::operator =(const fk_Matrix &ArgMat)
{
	CopyMatrix(m, ArgMat.m);
	return *this;
}

fk_Matrix & fk_Matrix::operator =(const fk_OrthoMatrix &ArgMat)
{
	CopyMatrix(m, ArgMat.m);
	return *this;
}

fk_Matrix & fk_Matrix::operator +=(const fk_Matrix &ArgMat)
{
	AddMatrix(m, ArgMat.m);
	return *this;
}

fk_Matrix & fk_Matrix::operator +=(const fk_OrthoMatrix &ArgMat)
{
	AddMatrix(m, ArgMat.m);
	return *this;
}

fk_Matrix & fk_Matrix::operator -=(const fk_Matrix &ArgMat)
{
	SubMatrix(m, ArgMat.m);
	return *this;
}

fk_Matrix & fk_Matrix::operator -=(const fk_OrthoMatrix &ArgMat)
{
	SubMatrix(m, ArgMat.m);
	return *this;
}

fk_Matrix & fk_Matrix::operator *=(const fk_Matrix &ArgMat)
{
	fk_Matrix tmp;

	MultMatrix(tmp.m, m, ArgMat.m);
	CopyMatrix(m, tmp.m);

	return *this;
}

fk_Matrix & fk_Matrix::operator *=(const fk_OrthoMatrix &ArgMat)
{
	fk_Matrix tmp;

	MultMatrix(tmp.m, m, ArgMat.m);
	CopyMatrix(m, tmp.m);

	return *this;
}

fk_Vector & fk_Vector::operator *=(const fk_Matrix &argMat)
{
	fk_HVector	tmp1, tmp2;
	tmp1 = *this;
	argMat.MultVec(tmp2, tmp1);
	*this = tmp2;
	return *this;
}

fk_HVector & fk_HVector::operator *=(const fk_Matrix &argMat)
{
	fk_HVector	tmp = *this;
	argMat.MultVec(*this, tmp);
	return *this;
}

namespace FK {
	fk_HVector operator *(const fk_Matrix &Mat, const fk_HVector &Vec)
	{
		fk_HVector Ret;

		Mat.MultVec(Ret, Vec);

		return Ret;
	}

	fk_Matrix operator +(const fk_Matrix &m1, const fk_Matrix &m2)
	{
		fk_Matrix Ret;

		Ret = m1;
		AddMatrix(Ret.m, m2.m);

		return Ret;
	}

	fk_Matrix operator +(const fk_Matrix &m1, const fk_OrthoMatrix &m2)
	{
		fk_Matrix Ret;

		Ret = m1;
		AddMatrix(Ret.m, m2.m);

		return Ret;
	}

	fk_Matrix operator +(const fk_OrthoMatrix &m1, const fk_Matrix &m2)
	{
		fk_Matrix Ret;

		Ret = m1;
		AddMatrix(Ret.m, m2.m);

		return Ret;
	}

	fk_Matrix operator -(const fk_Matrix &m1, const fk_Matrix &m2)
	{
		fk_Matrix Ret;

		Ret = m1;
		SubMatrix(Ret.m, m2.m);

		return Ret;
	}

	fk_Matrix operator -(const fk_Matrix &m1, const fk_OrthoMatrix &m2)
	{
		fk_Matrix Ret;

		Ret = m1;
		SubMatrix(Ret.m, m2.m);

		return Ret;
	}

	fk_Matrix operator -(const fk_OrthoMatrix &m1, const fk_Matrix &m2)
	{
		fk_Matrix Ret;

		Ret = m1;
		SubMatrix(Ret.m, m2.m);

		return Ret;
	}

	fk_Matrix operator *(const fk_Matrix &m1, const fk_Matrix &m2)
	{
		fk_Matrix Ret;

		MultMatrix(Ret.m, m1.m, m2.m);

		return Ret;
	}

	fk_Matrix operator *(const fk_Matrix &m1, const fk_OrthoMatrix &m2)
	{
		fk_Matrix Ret;

		MultMatrix(Ret.m, m1.m, m2.m);

		return Ret;
	}

	fk_Matrix operator *(const fk_OrthoMatrix &m1, const fk_Matrix &m2)
	{
		fk_Matrix Ret;

		MultMatrix(Ret.m, m1.m, m2.m);

		return Ret;
	}

	fk_Matrix operator *(double d, const fk_Matrix &m)
	{
		fk_Matrix	Ret;
		int			i, j;

		for(i = 0; i < 4; ++i) {
			for(j = 0; j < 4; ++j) {
				Ret.m[i][j] = d*m.m[i][j];
			}
		}

		return Ret;
	}

	fk_Matrix operator *(const fk_Matrix &m, double d)
	{
		fk_Matrix	Ret;
		int			i, j;

		for(i = 0; i < 4; ++i) {
			for(j = 0; j < 4; ++j) {
				Ret.m[i][j] = d*m.m[i][j];
			}
		}

		return Ret;
	}
}

fk_Vector fk_DivideVec(const fk_Vector &orgVec,
					   const fk_Vector &vec1,
					   const fk_Vector &vec2,
					   const fk_Vector &vec3)
{
	fk_Matrix		mat;
	fk_Vector		retVec(0.0, 0.0, 0.0);

	mat[0][0] = vec1.x; mat[0][1] = vec2.x; mat[0][2] = vec3.x;
	mat[1][0] = vec1.y; mat[1][1] = vec2.y; mat[1][2] = vec3.y;
	mat[2][0] = vec1.z; mat[2][1] = vec2.z; mat[2][2] = vec3.z;

	if(mat.inverse() == false) {
		return retVec;
	}

	retVec = mat * orgVec;
	return retVec;
}

fk_Angle::fk_Angle(double argH, double argP, double argB)
{
	h = argH;
	p = argP;
	b = argB;
	return;
}

void fk_Angle::set(double argH, double argP, double argB)
{
	h = argH;
	p = argP;
	b = argB;
	return;
}

void fk_Angle::Print(void)
{
	stringstream	ss;

	ss << "Angle = (" << h << ", " << p << ", " << b << ")";
	fk_PutError("fk_Angle", "Print", 1, ss.str());

	return;
}

void fk_Angle::Print(string argStr)
{
	stringstream	ss;
	
	ss << "Angle(" << argStr << ") = (" << h << ", " << p << ", " << b << ")";
	fk_PutError("fk_Angle", "Print", 2, ss.str());

	return;
}
