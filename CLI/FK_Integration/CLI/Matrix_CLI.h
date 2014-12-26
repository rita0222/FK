// Matrix_CLI.h

#pragma once

#include <string>
#include "Vector_CLI.h"
#include <FK/Matrix.h>

namespace FK_CLI {
	using namespace std;
	using namespace System;

	public ref class fk_Angle {
	internal:
	    ::fk_Angle *pAngle;

	public:
		fk_Angle::fk_Angle()
		{
			this->pAngle = new ::fk_Angle();
		}

		fk_Angle::~fk_Angle()
		{
			this->!fk_Angle();
		}

		fk_Angle::!fk_Angle()
		{
			delete this->pAngle;
		}

		property double h
		{
			double get()
			{
				return pAngle->h;
			}

			void set(double value)
			{
				pAngle->h = value;
			}
		}
		property double p
		{
			double get()
			{
				return pAngle->p;
			}

			void set(double value)
			{
				pAngle->p = value;
			}
		}
		property double b
		{
			double get()
			{
				return pAngle->b;
			}

			void set(double value)
			{
				pAngle->b = value;
			}
		}

		void set(double argH, double argP, double argB)
		{
			this->pAngle->set(argH, argP, argB);
		}
	};

	public ref class fk_Matrix {
	internal:
		::fk_Matrix *pMatrix;
	public:
		fk_Matrix::fk_Matrix()
		{
			this->pMatrix = new ::fk_Matrix();
		}

		fk_Matrix::~fk_Matrix()
		{
			this->!fk_Matrix();
		}

		fk_Matrix::!fk_Matrix()
		{
			delete this->pMatrix;
		}

 		property double default[int,int]
		{
			double get(int argI1, int argI2)
			{
				return (*pMatrix)[argI1][argI2];
			}

			void set(int argI1, int argI2, double argD)
			{
				(*pMatrix)[argI1][argI2] = argD;
			}
		}

		String^	fk_Matrix::ToString() override
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

		//////////////////// 比較演算子		
		bool Equals(fk_Matrix^ argM)
		{
			if(!argM) false;
			return (*argM->pMatrix == *this->pMatrix);
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_Matrix^ M = static_cast<fk_Matrix^>(argObj);
				return (*M->pMatrix == *this->pMatrix);
			}
			return false;
		}

		static fk_HVector^ operator*(fk_Matrix^ argM, fk_HVector^ argV)
		{
			if(!argM || !argV) return nullptr;
			fk_HVector^ V = gcnew fk_HVector();
			*V->pHVec = *argM->pMatrix * *argV->pHVec;
			return V;
		}

		static fk_Matrix^ operator*(fk_Matrix^ argM1, fk_Matrix^ argM2)
		{
			if(!argM1 || !argM2) return nullptr;
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = (*argM1->pMatrix) * (*argM2->pMatrix);
			return M;
		}

		static fk_Matrix^ operator*(double argD, fk_Matrix^ argM)
		{
			if(!argM) return nullptr;
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = argD * (*argM->pMatrix);
			return M;
		}

		static fk_Matrix^ operator*(fk_Matrix^ argM, double argD)
		{
			if(!argM) return nullptr;
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = (*argM->pMatrix) * argD;
			return M;
		}

		static fk_Matrix^ operator-(fk_Matrix^ argM1, fk_Matrix^ argM2)
		{
			if(!argM1 || !argM2) return nullptr;
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = (*argM1->pMatrix) - (*argM2->pMatrix);
			return M;
		}

		static fk_Matrix^ operator+(fk_Matrix^ argM1, fk_Matrix^ argM2)
		{
			if(!argM1 || !argM2) return nullptr;
			fk_Matrix^ M = gcnew fk_Matrix();
			*M->pMatrix = (*argM1->pMatrix) + (*argM2->pMatrix);
			return M;
		}

		static void operator +=(fk_Matrix^ argM1, fk_Matrix^ argM2)
		{
			if(!argM1 || !argM2) return;
			*argM1->pMatrix += *argM2->pMatrix;
		}

		static void operator -=(fk_Matrix^ argM1, fk_Matrix^ argM2)
		{
			if(!argM1 || !argM2) return;
			*argM1->pMatrix -= *argM2->pMatrix;
		}

		static void operator *=(fk_Matrix^ argM1, fk_Matrix^ argM2)
		{
			if(!argM1 || !argM2) return;
			*argM1->pMatrix *= *argM2->pMatrix;
		}

		void init()
		{
			this->pMatrix->init();
		}

		void set(int argRow, int argCol, double argValue)
		{
			this->pMatrix->set(argRow, argCol, argValue);
		}

		void setRow(int argRow, fk_Vector^ argV)
		{
			if(!argV) return;
			this->pMatrix->setRow(argRow, *argV->pVec);
		}

		void setRow(int argRow, fk_HVector^ argV)
		{
			if(!argV) return;
			this->pMatrix->setRow(argRow, *argV->pHVec);
		}
		
		void setCol(int argCol, fk_Vector^ argV)
		{
			if(!argV) return;
			this->pMatrix->setCol(argCol, *argV->pVec);
		}

		void setCol(int argCol, fk_HVector^ argV)
		{
			if(!argV) return;
			this->pMatrix->setCol(argCol, *argV->pHVec);
		}

		fk_HVector^ getRow(int argRow)
		{
			fk_HVector^ V = gcnew fk_HVector();
			*V->pHVec = this->pMatrix->getRow(argRow);
			return V;
		}

		fk_HVector^ getCol(int argCol)
		{
			fk_HVector^ V = gcnew fk_HVector();
			*V->pHVec = this->pMatrix->getCol(argCol);
			return V;
		}

		bool inverse()
		{
			return this->pMatrix->inverse();
		}

		void negate()
		{
			this->pMatrix->negate();
		}

		void makeRot(double argR, fk_Axis argAxis)
		{
			this->pMatrix->makeRot(argR, GetAxis(argAxis));
		}

		void makeTrans(fk_Vector^ argV)
		{
			if(!argV) return;
			this->pMatrix->makeTrans(*argV->pVec);
		}

		void makeEuler(double argH, double argP, double argB)
		{
			this->pMatrix->makeEuler(argH, argP, argB);
		}

		void makeEuler(fk_Angle^ argA)
		{
			if(!argA) return;
			this->pMatrix->makeEuler(*argA->pAngle);
		}

		bool isRegular()
		{
			return this->pMatrix->isRegular();
		}

		bool isSingular()
		{
			return this->pMatrix->isSingular();
		}

		void makeScale(double argX, double argY, double argZ)
		{
			this->pMatrix->makeScale(argX, argY, argZ);
		}

		void makeScale(fk_Vector^ argV)
		{
			if(!argV) return;
			this->pMatrix->makeScale(*argV->pVec);
		}
	};
}
