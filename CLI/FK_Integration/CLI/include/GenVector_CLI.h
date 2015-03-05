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
		fk_GenVector();
		fk_GenVector(int deg);
		fk_GenVector(::fk_GenVector *argV);
		fk_GenVector(array<double>^ argArray);
		fk_GenVector(fk_Vector^ argV);
		fk_GenVector(fk_HVector^ argH);
		fk_GenVector(fk_GenVector^ argGV);
		~fk_GenVector();
		!fk_GenVector();

		//////////////////// 比較演算子		
		bool Equals(fk_GenVector^ argGV);
		virtual bool Equals(Object^ argObj) override;

		//////////////////// 単項演算子
		static fk_GenVector^ operator-(fk_GenVector^ argV);
		static double operator*(fk_GenVector^ argV1, fk_GenVector^ argV2);
		static fk_GenVector^ operator+(fk_GenVector^ argV1, fk_GenVector^ argV2);
		static fk_GenVector^ operator-(fk_GenVector^ argV1, fk_GenVector^ argV2);
		static fk_GenVector^ operator*(fk_GenVector^ argV, double argD);
		static fk_GenVector^ operator*(double argD, fk_GenVector^ argV);
		static fk_GenVector^ operator/(fk_GenVector^ argV, double argD);
		static fk_GenVector^ operator ^(fk_GenVector^ argV1, fk_GenVector^ argV2);

		//代入演算子
		static void operator *=(fk_GenVector^ argV, double argD);
		static void operator /=(fk_GenVector^ argV, double argD);
		static void operator +=(fk_GenVector^ argV1, fk_GenVector^ argV2);
		static void operator -=(fk_GenVector^ argV1, fk_GenVector^ argV2);

		// プロパティ
		property double default[int] {
			double get(int argID);
			void set(int argID, double argD);
		}

		property int Size {
			void set(int);
			int get();
		}

		property double Norm {
			double get();
		}

		property double Norm2 {
			double get();
		}
		
		String^	ToString() override;

		bool Normalize(void);
		void Init(bool degFlg);
		void Init(void);
		bool IsZero(void);
		bool Replace(int s, fk_GenVector^ Q);
		bool Replace(int s, fk_Vector^ Q);
		bool Replace(int s, fk_HVector^ Q);
		bool Add(int s, fk_GenVector^ Q);
		bool Add(int s, fk_Vector^ Q);
		bool Add(int s, fk_HVector^ Q);
		bool Sub(int s, fk_GenVector^ Q);
		bool Sub(int s, fk_Vector^ Q);
		bool Sub(int s, fk_HVector^ Q);
		fk_GenVector^ Div(int s, int e);
	};
}

