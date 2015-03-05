// Vector_CLI.h

#pragma once

#include <FK/Vector.h>

namespace FK_CLI
{
	using namespace System;

	public enum	class fk_Axis {
		X,
		Y,
		Z
	};
	
	public ref class fk_Vector {
	internal:
		::fk_Vector *pVec;
		static ::fk_Axis GetAxis(fk_Axis);

	public:
		fk_Vector::fk_Vector();
		fk_Vector::fk_Vector(double, double, double);
		fk_Vector::fk_Vector(::fk_Vector *);
		fk_Vector::fk_Vector(::fk_Vector);

		// デストラクタ
		fk_Vector::~fk_Vector();
		// ファイナライザ
		fk_Vector::!fk_Vector();
		
		property double	x {
			double get();
			void set(double);
		}

		property double y {
			double get();
			void set(double);
		}

		property double z {
			double get();
			void set(double);
		}

		//////////////////// 比較演算子		
		bool Equals(fk_Vector^);
		virtual bool Equals(Object^) override;

		//////////////////// 単項演算子
		static fk_Vector^ operator-(fk_Vector^);

		//////////////////// 二項演算子
		static double operator*(fk_Vector^, fk_Vector^);
		static fk_Vector^ operator+(fk_Vector^, fk_Vector^);
		static fk_Vector^ operator-(fk_Vector^, fk_Vector^);
		static fk_Vector^ operator*(fk_Vector^, double);
		static fk_Vector^ operator*(double, fk_Vector^);
		static fk_Vector^ operator/(fk_Vector^, double);
		static fk_Vector^ operator^(fk_Vector^, fk_Vector^);

		//////////////////// 代入演算子
		static void operator *= (fk_Vector^, double);
		static void operator /= (fk_Vector^, double);
		static void operator += (fk_Vector^, fk_Vector^);
		static void operator -= (fk_Vector^, fk_Vector^);

		//////////////////// メンバ関数群
		String^	fk_Vector::ToString() override;
		void Set(double, double, double);
		void Set(double, double);
		double Dist();
		double Dist2();
		bool Normalize();
		bool IsZero();
		fk_Vector^ Proj(fk_Vector^);
		fk_Vector^ Perp(fk_Vector^);
	};

	public ref class fk_HVector {
	internal:
		::fk_HVector *pHVec;

	public:
		// コンストラクタ
		fk_HVector();
		fk_HVector(fk_Vector^);
		fk_HVector(fk_Vector^, double);

		// デストラクタ
		~fk_HVector();

		// ファイナライザ
		!fk_HVector();

		// プロパティ一覧
		property double x {
			double get();
			void set(double);
		}

		property double y {
			double get();
			void set(double);
		}

		property double z {
			double get();
			void set(double);
		}

		property double w {
			double get();
			void set(double);
		}

		static double operator* (fk_HVector^, fk_HVector^);

		// fk_Vectorとの変換
		static operator fk_HVector^ (fk_Vector^);
		static operator fk_Vector^ (fk_HVector^);

		//////////////////// 比較演算子		
		bool Equals(fk_HVector^);
		virtual bool Equals(Object^) override;
		String^ ToString() override;

		void Set(fk_Vector^, double);
		void Set(double, double, double, double);
		void Set(double, double, double);
		void Set(double, double);
		void Set(fk_Vector^);
		fk_Vector^ GetV(void);
		void IsPos(void);
		void IsVec(void);
		void Init(void);
	};

	public ref class fk_FVector {
	internal:
		::fk_FVector *pFVec;
	public:
		fk_FVector();
		~fk_FVector();
		!fk_FVector();

		static operator fk_Vector^(fk_FVector^);
		static operator fk_FVector ^ (fk_Vector^);
		String^ ToString() override;

  		property float x {
			float get();
			void set(float);
		}

		property float y {
			float get();
			void set(float);
		}

		property float z {
			float get();
			void set(float);
		}
	};
}
