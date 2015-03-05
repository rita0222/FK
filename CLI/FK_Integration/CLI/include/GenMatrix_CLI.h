// GenMatrix_CLI.h

#pragma once

#include <FK/GenMatrix.h>
#include "GenVector_CLI.h"

namespace FK_CLI {

	public ref class fk_GenMatrix {
	internal:
		::fk_GenMatrix *pGMat;
	public:
		fk_GenMatrix();
		fk_GenMatrix(int argDeg);
		~fk_GenMatrix();
		!fk_GenMatrix();

 		property double default[int,int] {
			double get(int argI1, int argI2);
			void set(int argI1, int argI2, double argD);
		}

		property int Degree {
			void set(int);
			int get();
		}

		//////////////////// 比較演算子		
		bool Equals(fk_GenMatrix^ argM);
		virtual bool Equals(Object^ argObj) override;
		String^	ToString() override;

		static fk_GenVector^ operator*(fk_GenMatrix^ argM, fk_GenVector^ argV);
		static fk_GenMatrix^ operator*(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2);
		static fk_GenMatrix^ operator-(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2);
		static fk_GenMatrix^ operator+(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2);
		static void operator +=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2);
		static void operator -=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2);
		static void operator *=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2);
		static void operator *=(fk_GenVector^ argV, fk_GenMatrix^ argM);

		void Init(bool initFlg);
		void Init(void);
		bool Inverse(void);
		fk_GenMatrix^ GetInverse(void);
		void Negate(void);
		bool IsRegular(void);
		bool IsSingular(void);
	};
}
