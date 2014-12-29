#include "Matrix_CLI.h"

namespace FK_CLI {

	using namespace std;
	
	String^	fk_Matrix::ToString()
	{
		std::string	tmpBuf;
		int i, j;

		tmpBuf = "M: \n";
		for(i = 0; i < 4; i++) {
			for(j = 0; j < 3; j++) {
				tmpBuf += to_string((*pMatrix)[i][j]) + ", ";
			}
			tmpBuf += to_string((*pMatrix)[i][3]) + "\n";
		}

		return gcnew String(tmpBuf.c_str());
	}

	void fk_Matrix::init()
	{
		this->pMatrix->init();
	}

	void fk_Matrix::set(int argRow, int argCol, double argValue)
	{
		this->pMatrix->set(argRow, argCol, argValue);
	}

	void fk_Matrix::setRow(int argRow, fk_Vector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setRow(argRow, *argV->pVec);
	}

	void fk_Matrix::setRow(int argRow, fk_HVector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setRow(argRow, *argV->pHVec);
	}
		
	void fk_Matrix::setCol(int argCol, fk_Vector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setCol(argCol, *argV->pVec);
	}

	void fk_Matrix::setCol(int argCol, fk_HVector^ argV)
	{
		if(!argV) return;
		this->pMatrix->setCol(argCol, *argV->pHVec);
	}

	fk_HVector^ fk_Matrix::getRow(int argRow)
	{
		fk_HVector^ V = gcnew fk_HVector();
		*V->pHVec = this->pMatrix->getRow(argRow);
		return V;
	}

	fk_HVector^ fk_Matrix::getCol(int argCol)
	{
		fk_HVector^ V = gcnew fk_HVector();
		*V->pHVec = this->pMatrix->getCol(argCol);
		return V;
	}

	bool fk_Matrix::inverse()
	{
		return this->pMatrix->inverse();
	}

	void fk_Matrix::negate()
	{
		this->pMatrix->negate();
	}

	void fk_Matrix::makeRot(double argR, fk_Axis argAxis)
	{
		this->pMatrix->makeRot(argR, GetAxis(argAxis));
	}

	void fk_Matrix::makeTrans(fk_Vector^ argV)
	{
		if(!argV) return;
		this->pMatrix->makeTrans(*argV->pVec);
	}

	void fk_Matrix::makeEuler(double argH, double argP, double argB)
	{
		this->pMatrix->makeEuler(argH, argP, argB);
	}

	void fk_Matrix::makeEuler(fk_Angle^ argA)
	{
		if(!argA) return;
		this->pMatrix->makeEuler(*argA->pAngle);
	}

	bool fk_Matrix::isRegular()
	{
		return this->pMatrix->isRegular();
	}

	bool fk_Matrix::isSingular()
	{
		return this->pMatrix->isSingular();
	}

	void fk_Matrix::makeScale(double argX, double argY, double argZ)
	{
		this->pMatrix->makeScale(argX, argY, argZ);
	}

	void fk_Matrix::makeScale(fk_Vector^ argV)
	{
		if(!argV) return;
		this->pMatrix->makeScale(*argV->pVec);
	}
}
