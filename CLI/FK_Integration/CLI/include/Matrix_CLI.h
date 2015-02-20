// Matrix_CLI.h

#pragma once

#include <FK/Matrix.h>
#include "Vector_CLI.h"

namespace FK_CLI {
	public ref class fk_Angle {
	internal:
	    ::fk_Angle *pAngle;

	public:
		fk_Angle::fk_Angle();
		fk_Angle::fk_Angle(double, double, double);
		fk_Angle::~fk_Angle();
		fk_Angle::!fk_Angle();

		property double h {
			double get();
			void set(double value);
		}

		property double p {
			double get();
			void set(double value);
		}

		property double b {
			double get();
			void set(double value);
		}

		void Set(double, double, double);
	};

	public ref class fk_Matrix {
	internal:
		::fk_Matrix *pMatrix;
	public:
		fk_Matrix::fk_Matrix();
		fk_Matrix::~fk_Matrix();
		fk_Matrix::!fk_Matrix();

 		property double default[int,int] {
			double get(int, int);
			void set(int, int, double);
		}

		//////////////////// 比較演算子		
		bool Equals(fk_Matrix^ argM);
		virtual bool Equals(Object^ argObj) override;
		String^	fk_Matrix::ToString() override;

		static fk_HVector^ operator*(fk_Matrix^, fk_HVector^);
		static fk_Matrix^ operator*(fk_Matrix^, fk_Matrix^);
		static fk_Matrix^ operator*(double, fk_Matrix^);
		static fk_Matrix^ operator*(fk_Matrix^, double);
		static fk_Matrix^ operator-(fk_Matrix^, fk_Matrix^);
		static fk_Matrix^ operator+(fk_Matrix^, fk_Matrix^);
		static void operator +=(fk_Matrix^, fk_Matrix^);
		static void operator -=(fk_Matrix^, fk_Matrix^);
		static void operator *=(fk_Matrix^, fk_Matrix^);

		void Init();
		void Set(int, int, double);
		void SetRow(int, fk_Vector^);
		void SetRow(int, fk_HVector^);
		void SetCol(int, fk_Vector^);
		void SetCol(int, fk_HVector^);
		fk_HVector^ GetRow(int);
		fk_HVector^ GetCol(int);
		bool Inverse();
		fk_Matrix^ GetInverse();
		void Negate();
		void MakeRot(double, fk_Axis);
		void MakeTrans(fk_Vector^);
		void MakeEuler(double, double, double);
		void MakeEuler(fk_Angle^);
		bool IsRegular();
		bool IsSingular();
		void MakeScale(double, double, double);
		void MakeScale(fk_Vector^);
	};
}
