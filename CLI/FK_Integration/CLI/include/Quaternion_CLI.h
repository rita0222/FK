// Quaternion_CLI.h

#pragma once

#include <FK/Quaternion.h>
#include "Matrix_CLI.h"

namespace FK_CLI
{
	using namespace System;

	public ref class fk_Quaternion {
	internal:
		::fk_Quaternion *pQuat;

	public:
		fk_Quaternion();
		fk_Quaternion(double argS, double argX, double argY, double argZ);
		fk_Quaternion(double argS, fk_Vector^ argV);
		fk_Quaternion(::fk_Quaternion *argQ);
		fk_Quaternion(::fk_Quaternion argQ);
		~fk_Quaternion();
		!fk_Quaternion();


		//////////////////// 比較演算子		
		bool Equals(fk_Quaternion^ argQ);
		virtual bool Equals(Object^ argObj) override;

		//////////////////// 単項演算子
		static fk_Quaternion^ operator-(fk_Quaternion^ argQ);
		static fk_Quaternion^ operator~(fk_Quaternion^ argQ);

		//////////////////// 二項演算子
		static fk_Quaternion^ operator*(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2);
		static fk_Quaternion^ operator+(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2);
		static fk_Quaternion^ operator-(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2);
		static fk_Quaternion^ operator*(fk_Quaternion^ argQ, double argD);
		static fk_Quaternion^ operator*(double argD, fk_Quaternion^ argQ);
		static fk_Quaternion^ operator/(fk_Quaternion^ argQ, double argD);
		static fk_Vector^ operator*(fk_Quaternion^ argQ, fk_Vector^ argV);
		static double operator^(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2);

		//////////////////// 代入演算子
		static void operator *= (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2);
		static void operator *= (fk_Quaternion^ argQ1, double argD);
		static void operator /= (fk_Quaternion^ argQ, double argD);
		static void operator += (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2);
		static void operator -= (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2);

		//////////////////// 

		property double	s {
			double get();
			void set(double value);
		}

		property double	x {
			double get();
			void set(double value);
		}

		property double y {
			double get();
			void set(double value);
		}

		property double z {
			double get();
			void set(double value);
		}

		property fk_Vector^ v {
			fk_Vector^ get();
			void set(fk_Vector^ argV);
		}					

		property fk_Angle^ Euler {
			fk_Angle^ get();
			void set(fk_Angle^);
		}

		property double Norm {
			double get();
		}

		property double Abs {
			double get();
		}

		property fk_Matrix^ Matrix {
			fk_Matrix^ get();
		}
		
		//////////////////// メンバ関数群
		String^	ToString() override;

		void Init(void);
		void Set(double s, double x, double y, double z);
		void Set(double s, fk_Vector^ v);
		void SetRotate(double theta, double x, double y, double z);
		void SetRotate(double theta, fk_Vector^ V);
		bool Normalize(void);
		void Conj(void);
		bool Inverse(void);
		fk_Quaternion^ GetInverse(void);
	};
}
