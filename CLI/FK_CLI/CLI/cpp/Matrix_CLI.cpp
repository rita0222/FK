#include "Matrix_CLI.h"

namespace FK_CLI {

	using namespace std;

	fk_Angle::operator ::fk_Angle (fk_Angle^ argA)
	{
		::fk_Angle	A(argA->h_, argA->p_, argA->b_);
		return A;
	}

	fk_Angle::fk_Angle()
		: h_(0.0), p_(0.0), b_(0.0)
	{
		return;
	}

	fk_Angle::fk_Angle(double argH, double argP, double argB)
		: h_(argH), p_(argP), b_(argB)
	{
		return;
	}

	fk_Angle::fk_Angle(fk_Angle^ argA)
		: h_(0.0), p_(0.0), b_(0.0)
	{
		if(!argA) return;
		h_ = argA->h_;
		p_ = argA->p_;
		b_ = argA->b_;
	}

	fk_Angle::fk_Angle(::fk_Angle argA)
		: h_(argA.h), p_(argA.p), b_(argA.b)
	{
		return;
	}

	fk_Angle::~fk_Angle()
	{
		this->!fk_Angle();
	}

	fk_Angle::!fk_Angle()
	{
		return;
	}

	double fk_Angle::h::get()
	{
		return h_;
	}
	
	void fk_Angle::h::set(double value)
	{
		h_ = value;
	}

	double fk_Angle::p::get()
	{
		return p_;
	}
	
	void fk_Angle::p::set(double value)
	{
		p_ = value;
	}
	
	double fk_Angle::b::get()
	{
		return b_;
	}
	
	void fk_Angle::b::set(double value)
	{
		b_ = value;
	}

	void fk_Angle::Set(double argH, double argP, double argB)
	{
		h_ = argH;
		p_ = argP;
		b_ = argB;
	}

	////////////////////////////////////////////////////////////////////
	
	fk_Matrix::fk_Matrix()
	{
		pMatrix = new ::fk_Matrix();
		refArray = gcnew cli::array<float>(16);
	}

	fk_Matrix::fk_Matrix(fk_Matrix^ argM)
	{
		pMatrix = new ::fk_Matrix(*(argM->pMatrix));
		refArray = gcnew cli::array<float>(16);
	}

	fk_Matrix::~fk_Matrix()
	{
		this->!fk_Matrix();
	}

	fk_Matrix::!fk_Matrix()
	{
		delete pMatrix;
	}

	double fk_Matrix::default::get(int argI1, int argI2)
	{
		return (*pMatrix)[argI1][argI2];
	}

	void fk_Matrix::default::set(int argI1, int argI2, double argD)
	{
		(*pMatrix)[argI1][argI2] = argD;
	}

	cli::array<float>^ fk_Matrix::GetFloatArray()
	{
		for (int i = 0; i < 16; ++i)
		{
			refArray[i] = float((*pMatrix)[i % 4][i / 4]);
		}

		return refArray;
	}

	bool fk_Matrix::Equals(fk_Matrix^ argM)
	{
		if(!argM) false;
		return (*argM->pMatrix == *pMatrix);
	}

	bool fk_Matrix::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_Matrix^ M = static_cast<fk_Matrix^>(argObj);
			return (*M->pMatrix == *pMatrix);
		}
		return false;
	}

	String^	fk_Matrix::ToString()
	{
		std::string	tmpBuf;
		int i, j;

		tmpBuf = "M: \n";
		for(i = 0; i < 4; ++i) {
			for(j = 0; j < 3; ++j) {
				tmpBuf += to_string((*pMatrix)[i][j]) + ", ";
			}
			tmpBuf += to_string((*pMatrix)[i][3]) + "\n";
		}

		return gcnew String(tmpBuf.c_str());
	}

	fk_HVector^ fk_Matrix::operator*(fk_Matrix^ argM, fk_HVector^ argV)
	{
		if(!argM || !argV) return nullptr;
		::fk_HVector H((*argM->pMatrix) * ::fk_HVector(argV->x_, argV->y_, argV->z_, argV->w_));
		return gcnew fk_HVector(H);
	}

	fk_Matrix^ fk_Matrix::operator*(fk_Matrix^ argM1, fk_Matrix^ argM2)
	{
		if(!argM1 || !argM2) return nullptr;
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = (*argM1->pMatrix) * (*argM2->pMatrix);
		return M;
	}

	fk_Matrix^ fk_Matrix::operator*(double argD, fk_Matrix^ argM)
	{
		if(!argM) return nullptr;
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = argD * (*argM->pMatrix);
		return M;
	}

	fk_Matrix^ fk_Matrix::operator*(fk_Matrix^ argM, double argD)
	{
		if(!argM) return nullptr;
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = (*argM->pMatrix) * argD;
		return M;
	}

	fk_Matrix^ fk_Matrix::operator-(fk_Matrix^ argM1, fk_Matrix^ argM2)
	{
		if(!argM1 || !argM2) return nullptr;
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = (*argM1->pMatrix) - (*argM2->pMatrix);
		return M;
	}

	fk_Matrix^ fk_Matrix::operator+(fk_Matrix^ argM1, fk_Matrix^ argM2)
	{
		if(!argM1 || !argM2) return nullptr;
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = (*argM1->pMatrix) + (*argM2->pMatrix);
		return M;
	}

	void fk_Matrix::operator +=(fk_Matrix^ argM1, fk_Matrix^ argM2)
	{
		if(!argM1 || !argM2) return;
		*argM1->pMatrix += *argM2->pMatrix;
	}

	void fk_Matrix::operator -=(fk_Matrix^ argM1, fk_Matrix^ argM2)
	{
		if(!argM1 || !argM2) return;
		*argM1->pMatrix -= *argM2->pMatrix;
	}

	void fk_Matrix::operator *=(fk_Matrix^ argM1, fk_Matrix^ argM2)
	{
		if(!argM1 || !argM2) return;
		*argM1->pMatrix *= *argM2->pMatrix;
	}


	void fk_Matrix::Init()
	{
		this->pMatrix->init();
	}

	void fk_Matrix::Set(int argRow, int argCol, double argValue)
	{
		this->pMatrix->set(argRow, argCol, argValue);
	}

	void fk_Matrix::SetRow(int argRow, fk_Vector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setRow(argRow, argV);
	}

	void fk_Matrix::SetRow(int argRow, fk_HVector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setRow(argRow, argV);
	}
		
	void fk_Matrix::SetCol(int argCol, fk_Vector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setCol(argCol, argV);
	}

	void fk_Matrix::SetCol(int argCol, fk_HVector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setCol(argCol, argV);
	}

	fk_HVector^ fk_Matrix::GetRow(int argRow)
	{
		return gcnew fk_HVector(this->pMatrix->getRow(argRow));

	}

	fk_HVector^ fk_Matrix::GetCol(int argCol)
	{
		return gcnew fk_HVector(this->pMatrix->getCol(argCol));
	}

	bool fk_Matrix::Inverse()
	{
		return this->pMatrix->inverse();
	}

	fk_Matrix^ fk_Matrix::GetInverse()
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = !(*pMatrix);
		return M;
	}

	void fk_Matrix::Negate()
	{
		this->pMatrix->negate();
	}

	void fk_Matrix::MakeRot(double argR, fk_Axis argAxis)
	{
		this->pMatrix->makeRot(argR, fk_Vector::GetAxis(argAxis));
	}

	void fk_Matrix::MakeTrans(double argX, double argY, double argZ)
	{
		this->pMatrix->makeTrans(argX, argY, argZ);
	}

	void fk_Matrix::MakeTrans(fk_Vector^ argV)
	{
		if(!argV) return;
		this->pMatrix->makeTrans(argV);
	}

	void fk_Matrix::MakeEuler(double argH, double argP, double argB)
	{
		this->pMatrix->makeEuler(argH, argP, argB);
	}

	void fk_Matrix::MakeEuler(fk_Angle^ argA)
	{
		if(!argA) return;
		this->pMatrix->makeEuler(argA);
	}

	bool fk_Matrix::IsRegular()
	{
		return this->pMatrix->isRegular();
	}

	bool fk_Matrix::IsSingular()
	{
		return this->pMatrix->isSingular();
	}

	void fk_Matrix::MakeScale(double argX, double argY, double argZ)
	{
		this->pMatrix->makeScale(argX, argY, argZ);
	}

	void fk_Matrix::MakeScale(fk_Vector^ argV)
	{
		if(!argV) return;
		this->pMatrix->makeScale(argV);
	}
}
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
