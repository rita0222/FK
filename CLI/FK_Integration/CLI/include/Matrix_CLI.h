// Matrix_CLI.h

#pragma once

#include <FK/Matrix.h>
#include "Vector_CLI.h"

namespace FK_CLI {
	public ref class fk_Angle {
	internal:
	    ::fk_Angle *pAngle;

	public:
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

		property double h {
			double get()
			{
				return pAngle->h;
			}

			void set(double value)
			{
				pAngle->h = value;
			}
		}
		property double p {
			double get()
			{
				return pAngle->p;
			}

			void set(double value)
			{
				pAngle->p = value;
			}
		}
		property double b {
			double get()
			{
				return pAngle->b;
			}

			void set(double value)
			{
				pAngle->b = value;
			}
		}

		void Set(double argH, double argP, double argB)
		{
			pAngle->set(argH, argP, argB);
		}
	};

	public ref class fk_Matrix {
	internal:
		::fk_Matrix *pMatrix;
	public:
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

 		property double default[int,int] {
			double get(int argI1, int argI2)
			{
				return (*pMatrix)[argI1][argI2];
			}

			void set(int argI1, int argI2, double argD)
			{
				(*pMatrix)[argI1][argI2] = argD;
			}
		}

		//////////////////// 比較演算子		
		bool Equals(fk_Matrix^ argM)
		{
			if(!argM) false;
			return (*argM->pMatrix == *pMatrix);
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_Matrix^ M = static_cast<fk_Matrix^>(argObj);
				return (*M->pMatrix == *pMatrix);
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

		String^	fk_Matrix::ToString() override;

		void Init();
		void Set(int row, int col, double value);
		void SetRow(int row, fk_Vector^ vec);
		void SetRow(int row, fk_HVector^ vec);
		void SetCol(int col, fk_Vector^ vec);
		void SetCol(int col, fk_HVector^ vec);
		fk_HVector^ GetRow(int row);
		fk_HVector^ GetCol(int col);
		bool Inverse();
		fk_Matrix^ GetInverse();
		void Negate();
		void MakeRot(double theta, fk_Axis axis);
		void MakeTrans(fk_Vector^ vec);
		void MakeEuler(double head, double pitch, double bank);
		void MakeEuler(fk_Angle^ angle);
		bool IsRegular();
		bool IsSingular();
		void MakeScale(double x, double y, double z);
		void MakeScale(fk_Vector^ scaleVec);
	};
}
