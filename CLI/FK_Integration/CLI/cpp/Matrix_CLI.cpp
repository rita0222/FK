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
	}

	fk_Matrix::fk_Matrix(fk_Matrix^ argM)
	{
		pMatrix = new ::fk_Matrix(*(argM->pMatrix));
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
