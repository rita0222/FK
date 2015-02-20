#include "Matrix_CLI.h"

namespace FK_CLI {

	using namespace std;

	fk_Angle::fk_Angle()
	{
		pAngle = new ::fk_Angle();
	}

	fk_Angle::fk_Angle(double argH, double argP, double argB)
	{
		pAngle = new ::fk_Angle(argH, argP, argB);
	}

	fk_Angle::~fk_Angle()
	{
		this->!fk_Angle();
	}

	fk_Angle::!fk_Angle()
	{
		delete pAngle;
	}

	double fk_Angle::h::get()
	{
		return pAngle->h;
	}
	
	void fk_Angle::h::set(double value)
	{
		pAngle->h = value;
	}

	double fk_Angle::p::get()
	{
		return pAngle->p;
	}
	
	void fk_Angle::p::set(double value)
	{
		pAngle->p = value;
	}
	
	double fk_Angle::b::get()
	{
		return pAngle->b;
	}
	
	void fk_Angle::b::set(double value)
	{
		pAngle->b = value;
	}

	void fk_Angle::Set(double argH, double argP, double argB)
	{
		pAngle->set(argH, argP, argB);
	}

	////////////////////////////////////////////////////////////////////
	
	fk_Matrix::fk_Matrix()
	{
		pMatrix = new ::fk_Matrix();
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
		fk_HVector^ V = gcnew fk_HVector();
		*V->pHVec = *argM->pMatrix * *argV->pHVec;
		return V;
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
		this->pMatrix->setRow(argRow, *argV->pVec);
	}

	void fk_Matrix::SetRow(int argRow, fk_HVector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setRow(argRow, *argV->pHVec);
	}
		
	void fk_Matrix::SetCol(int argCol, fk_Vector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setCol(argCol, *argV->pVec);
	}

	void fk_Matrix::SetCol(int argCol, fk_HVector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setCol(argCol, *argV->pHVec);
	}

	fk_HVector^ fk_Matrix::GetRow(int argRow)
	{
		fk_HVector^ V = gcnew fk_HVector();
		*V->pHVec = this->pMatrix->getRow(argRow);
		return V;
	}

	fk_HVector^ fk_Matrix::GetCol(int argCol)
	{
		fk_HVector^ V = gcnew fk_HVector();
		*V->pHVec = this->pMatrix->getCol(argCol);
		return V;
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
		this->pMatrix->makeTrans(*argV->pVec);
	}

	void fk_Matrix::MakeEuler(double argH, double argP, double argB)
	{
		this->pMatrix->makeEuler(argH, argP, argB);
	}

	void fk_Matrix::MakeEuler(fk_Angle^ argA)
	{
		if(!argA) return;
		this->pMatrix->makeEuler(*argA->pAngle);
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
		this->pMatrix->makeScale(*argV->pVec);
	}
}
