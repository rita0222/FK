// GenVector_CLI.h

#pragma once

#include <FK/GenVector.h>
#include "Matrix_CLI.h"

namespace FK_CLI {
	using namespace System;

	public ref class fk_GenVector {
	internal:
		::fk_GenVector *pGVec;

	public:
		fk_GenVector::fk_GenVector()
		{
			pGVec = new ::fk_GenVector();
		}

		fk_GenVector::fk_GenVector(int deg)
		{
			pGVec = new ::fk_GenVector(deg);
		}

		fk_GenVector::fk_GenVector(::fk_GenVector *argV)
		{
			pGVec = new ::fk_GenVector(*argV);
		}

		fk_GenVector::fk_GenVector(array<double>^ argArray)
		{
			pin_ptr<double> pD = &argArray[0];
			pGVec = new ::fk_GenVector(argArray->Length, pD);
		}

		fk_GenVector::fk_GenVector(fk_Vector^ argV)
		{
			if(!argV) {
				pGVec = new ::fk_GenVector();
			} else {
				pGVec = new ::fk_GenVector(*argV->pVec);
			}
		}

		fk_GenVector::fk_GenVector(fk_HVector^ argH)
		{
			if(!argH) {
				pGVec = new ::fk_GenVector();
			} else {
				pGVec = new ::fk_GenVector(*argH->pHVec);
			}
		}
		
		fk_GenVector::fk_GenVector(fk_GenVector^ argGV)
		{
			if(!argGV) {
				pGVec = new ::fk_GenVector();
			} else {
				pGVec = new ::fk_GenVector(*argGV->pGVec);
			}
		}

		// デストラクタ
		fk_GenVector::~fk_GenVector()
		{
			this->!fk_GenVector();
		}

		// ファイナライザ
		fk_GenVector::!fk_GenVector()
		{
			delete pGVec;
		}


		property double default[int] {
			double get(int argID)
			{
				return pGVec->get(argID);
			}

			void set(int argID, double argD)
			{
				pGVec->set(argID, argD);
			}
		}

		//////////////////// 比較演算子		
		bool Equals(fk_GenVector^ argGV)
		{
			if(!argGV) false;
			return (*argGV->pGVec == *pGVec);
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_GenVector^ GV = static_cast<fk_GenVector^>(argObj);
				return (*GV->pGVec == *pGVec);
			}
			return false;
		}

		//////////////////// 単項演算子
		static fk_GenVector^ operator-(fk_GenVector^ argV)
		{
			if(!argV) return nullptr;
			fk_GenVector^ V = gcnew fk_GenVector();
			*V->pGVec = -(*argV->pGVec);
			return V;
		}

		static double operator*(fk_GenVector^ argV1, fk_GenVector^ argV2)
		{
			if(!argV1 || !argV2) return 0.0;
			return (*argV1->pGVec) * (*argV2->pGVec);
		}
		
		static fk_GenVector^ operator+(fk_GenVector^ argV1, fk_GenVector^ argV2)
		{
			if(!argV1 || !argV2) return nullptr;
			fk_GenVector^ V = gcnew fk_GenVector();
			*V->pGVec = (*argV1->pGVec) + (*argV2->pGVec);
			return V;
		}
			
		static fk_GenVector^ operator-(fk_GenVector^ argV1, fk_GenVector^ argV2)
		{
			if(!argV1 || !argV2) return nullptr;
			fk_GenVector^ V = gcnew fk_GenVector();
			*V->pGVec = (*argV1->pGVec) - (*argV2->pGVec);
			return V;
		}
			
		static fk_GenVector^ operator*(fk_GenVector^ argV, double argD)
		{
			if(!argV) return nullptr;
			fk_GenVector^ V = gcnew fk_GenVector();
			*V->pGVec = *argV->pGVec * argD;
			return V;
		}
						  
		static fk_GenVector^ operator*(double argD, fk_GenVector^ argV)
		{
			if(!argV) return nullptr;
			fk_GenVector^ V = gcnew fk_GenVector();
			*V->pGVec = *argV->pGVec * argD;
			return V;
		}
			
		static fk_GenVector^ operator/(fk_GenVector^ argV, double argD)
		{
			if(!argV) return nullptr;
			fk_GenVector^ V = gcnew fk_GenVector();
			*V->pGVec = *argV->pGVec/argD;
			return V;
		}
			
		static fk_GenVector^ operator ^(fk_GenVector^ argV1, fk_GenVector^ argV2)
		{
			if(!argV1 || !argV2) return nullptr;
			fk_GenVector^ V = gcnew fk_GenVector();
			*V->pGVec = (*argV1->pGVec) ^ (*argV2->pGVec);
			return V;
		}

		//代入演算子 
		static void operator *=(fk_GenVector^ argV, double argD)
		{
			if(!argV) return;
			*argV->pGVec *= argD;
		}

		static void operator /=(fk_GenVector^ argV, double argD)
		{
			if(!argV) return;
			*argV->pGVec /= argD;
		}

		static void operator +=(fk_GenVector^ argV1, fk_GenVector^ argV2)
		{
			if(!argV1 || !argV2) return;
			*argV1->pGVec += *argV2->pGVec;
		}

		static void operator -=(fk_GenVector^ argV1, fk_GenVector^ argV2)
		{
			if(!argV1 || !argV2) return;
			*argV1->pGVec -= *argV2->pGVec;
		}

		String^	fk_GenVector::ToString() override;

		void resize(int deg);
		bool set(int ID, double value);
		int size(void);
		double get(int ID);
		double norm(void);
		double norm2(void);
		bool normalize(void);
		void init(bool degFlg);
		void init(void);
		bool isZero(void);
		bool replace(int s, fk_GenVector^ Q);
		bool replace(int s, fk_Vector^ Q);
		bool replace(int s, fk_HVector^ Q);
		bool add(int s, fk_GenVector^ Q);
		bool add(int s, fk_Vector^ Q);
		bool add(int s, fk_HVector^ Q);
		bool sub(int s, fk_GenVector^ Q);
		bool sub(int s, fk_Vector^ Q);
		bool sub(int s, fk_HVector^ Q);
		fk_GenVector^ div(int s, int e);
	};
}

