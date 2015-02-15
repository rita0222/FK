#include "Matrix_CLI.h"

namespace FK_CLI {

	using namespace std;
	
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
