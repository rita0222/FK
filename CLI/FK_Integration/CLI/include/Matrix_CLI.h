// Matrix_CLI.h

#pragma once

#include <FK/Matrix.h>
#include "Vector_CLI.h"

namespace FK_CLI {

	//! オイラー角を表すクラス
	/*!
	 *	オイラー角は、3次元での姿勢を表す方法の一つで、
	 *	空間中の全ての姿勢を表現することが可能です。
	 *	FK におけるオイラー角は Z-X-Y 座標系を意味します。
	 *	ヘディング角を h、ピッチ角を p、バンク角を b としたとき、
	 *	このオイラー角は以下の回転変換と同意です。
	 *	\f[
	 *		R_y(-h) \cdot R_x(p) \cdot R_z(-b)
	 *	\f]
	 *	角度の単位はすべて弧度法(ラジアン)です。
	 */

	public ref class fk_Angle {
	internal:
		double h_, p_, b_;

		static operator ::fk_Angle (fk_Angle^);

	public:
		fk_Angle();
		fk_Angle(double, double, double);
		fk_Angle(fk_Angle^);
		fk_Angle(::fk_Angle);
		~fk_Angle();
		!fk_Angle();

		//! ヘディング角
		property double h {
			double get();
			void set(double value);
		}

		//! ピッチ角
		property double p {
			double get();
			void set(double value);
		}

		//! バンク角
		property double b {
			double get();
			void set(double value);
		}

		//! 設定用関数
		/*!
		 *	\param[in]	h	ヘディング角
		 *	\param[in]	p	ピッチ角
		 *	\param[in]	b	バンク角
		 */
		void Set(double h, double p, double b);
	};

	public ref class fk_Matrix {
	internal:
		::fk_Matrix *pMatrix;
	public:
		fk_Matrix();
		fk_Matrix(fk_Matrix^);
		~fk_Matrix();
		!fk_Matrix();

 		property double default[int, int] {
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
