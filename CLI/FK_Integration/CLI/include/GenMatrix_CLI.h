// GenMatrix_CLI.h

#pragma once

#include <FK/GenMatrix.h>
#include "GenVector_CLI.h"

namespace FK_CLI {

	public ref class fk_GenMatrix {
	internal:
		::fk_GenMatrix *pGMat;
	public:
		fk_GenMatrix::fk_GenMatrix()
		{
			pGMat = new ::fk_GenMatrix();
		}

		fk_GenMatrix::fk_GenMatrix(int argDeg)
		{
			pGMat = new ::fk_GenMatrix(argDeg);
		}

		fk_GenMatrix::~fk_GenMatrix()
		{
			this->!fk_GenMatrix();
		}

		fk_GenMatrix::!fk_GenMatrix()
		{
			delete pGMat;
		}

 		property double default[int,int] {
			double get(int argI1, int argI2)
			{
				return pGMat->get(argI1, argI2);
			}

			void set(int argI1, int argI2, double argD)
			{
				pGMat->set(argI1, argI2, argD);
			}
		}

		//////////////////// 比較演算子		
		bool Equals(fk_GenMatrix^ argM)
		{
			if(!argM) false;
			return (*argM->pGMat == *pGMat);
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_GenMatrix^ M = static_cast<fk_GenMatrix^>(argObj);
				return (*M->pGMat == *pGMat);
			}
			return false;
		}

		static fk_GenVector^ operator*(fk_GenMatrix^ argM, fk_GenVector^ argV)
		{
			if(!argM || !argV) return nullptr;
			fk_GenVector^ V = gcnew fk_GenVector();
			*V->pGVec = (*argM->pGMat) * (*argV->pGVec);
			return V;
		}

		static fk_GenMatrix^ operator*(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
		{
			if(!argM1 || !argM2) return nullptr;
			fk_GenMatrix^ M = gcnew fk_GenMatrix();
			*M->pGMat = (*argM1->pGMat) * (*argM2->pGMat);
			return M;
		}

		static fk_GenMatrix^ operator-(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
		{
			if(!argM1 || !argM2) return nullptr;
			fk_GenMatrix^ M = gcnew fk_GenMatrix();
			*M->pGMat = (*argM1->pGMat) - (*argM2->pGMat);
			return M;
		}

		static fk_GenMatrix^ operator+(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
		{
			if(!argM1 || !argM2) return nullptr;
			fk_GenMatrix^ M = gcnew fk_GenMatrix();
			*M->pGMat = (*argM1->pGMat) + (*argM2->pGMat);
			return M;
		}

		static void operator +=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
		{
			if(!argM1 || !argM2) return;
			*argM1->pGMat += *argM2->pGMat;
		}

		static void operator -=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
		{
			if(!argM1 || !argM2) return;
			*argM1->pGMat -= *argM2->pGMat;
		}

		static void operator *=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
		{
			if(!argM1 || !argM2) return;
			*argM1->pGMat *= *argM2->pGMat;
		}

		static void operator *=(fk_GenVector^ argV, fk_GenMatrix^ argM)
		{
			if(!argV || !argM) return;
			*argV->pGVec *= *argM->pGMat;
		}

		String^	fk_GenMatrix::ToString() override;

		void init(bool initFlg);
		void init(void);
		void setDeg(int deg);
		int getDeg(void);
		void set(int row, int col, double value);
		double get(int row, int col);
		bool inverse(void);
		fk_GenMatrix^ getInverse(void);
		void negate(void);
		bool isRegular(void);
		bool isSingular(void);
	};
}
