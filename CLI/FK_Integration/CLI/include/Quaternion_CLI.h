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
		fk_Quaternion::fk_Quaternion()
		{
			pQuat = new ::fk_Quaternion();
		}

		fk_Quaternion::fk_Quaternion(double argS, double argX, double argY, double argZ)
		{
			pQuat = new ::fk_Quaternion(argS, argX, argY, argZ);
		}

		fk_Quaternion::fk_Quaternion(double argS, fk_Vector^ argV)
		{
			if(!argV) {
				pQuat = new ::fk_Quaternion(argS, 0.0, 0.0, 0.0);
			} else {
				pQuat = new ::fk_Quaternion(argS, *argV->pVec);
			}
		}

		fk_Quaternion::fk_Quaternion(::fk_Quaternion *argQ)
		{
			pQuat = new ::fk_Quaternion(argQ->s, argQ->v);
		}

		fk_Quaternion::fk_Quaternion(::fk_Quaternion argQ)
		{
			pQuat = new ::fk_Quaternion(argQ.s, argQ.v);
		}

		// デストラクタ
		fk_Quaternion::~fk_Quaternion()
		{
			this->!fk_Quaternion();
		}

		// ファイナライザ
		fk_Quaternion::!fk_Quaternion()
		{
			delete pQuat;
		}

		property double	s {
			double get()
			{
				return pQuat->s;
			}

			void set(double value)
			{
				pQuat->s = value;
			}
		}

		property double	x {
			double get()
			{
				return pQuat->v.x;
			}

			void set(double value)
			{
				pQuat->v.x = value;
			}
		}

		property double y {
			double get()
			{
				return pQuat->v.y;
			}

			void set(double value)
			{
				pQuat->v.y = value;
			}
		}

		property double z {
			double get()
			{
				return pQuat->v.z;
			}

			void set(double value)
			{
				pQuat->v.z = value;
			}
		}

		property fk_Vector^ v {
			fk_Vector^ get()
			{
				return gcnew fk_Vector(pQuat->v);
			}

			void set(fk_Vector^ argV)
			{
				if(!argV) return;
				pQuat->v = *argV->pVec;
			}
		}					

		//////////////////// 比較演算子		
		bool Equals(fk_Quaternion^ argQ)
		{
			if(!argQ) false;
			return (*argQ->pQuat == *pQuat);
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_Quaternion^ V = static_cast<fk_Quaternion^>(argObj);
				return (*V->pQuat == *pQuat);
			}
			return false;
		}

		//////////////////// 単項演算子
		static fk_Quaternion^ operator-(fk_Quaternion^ argQ)
		{
			if(!argQ) return nullptr;
			fk_Quaternion^ Q = gcnew fk_Quaternion();
			*Q->pQuat = -(*argQ->pQuat);
			return Q;
		}

		static fk_Quaternion^ operator~(fk_Quaternion^ argQ)
		{
			if(!argQ) return nullptr;
			fk_Quaternion^ Q = gcnew fk_Quaternion();
			*Q->pQuat = ~(*argQ->pQuat);
			return Q;
		}

		//////////////////// 二項演算子
		static fk_Quaternion^ operator*(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
		{
			if(!argQ1 || !argQ2) return nullptr;
			fk_Quaternion^ Q = gcnew fk_Quaternion();
			*Q->pQuat = (*argQ1->pQuat) * (*argQ2->pQuat);
			return Q;
		}
		
		static fk_Quaternion^ operator+(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
		{
			if(!argQ1 || !argQ2) return nullptr;
			fk_Quaternion^ Q = gcnew fk_Quaternion();
			*Q->pQuat = *argQ1->pQuat + *argQ2->pQuat;
			return Q;
		}

		static fk_Quaternion^ operator-(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
		{
			if(!argQ1 || !argQ2) return nullptr;
			fk_Quaternion^ Q = gcnew fk_Quaternion();
			*Q->pQuat = *argQ1->pQuat - *argQ2->pQuat;
			return Q;
		}
			
		static fk_Quaternion^ operator*(fk_Quaternion^ argQ, double argD)
		{
			if(!argQ) return nullptr;
			fk_Quaternion^ Q = gcnew fk_Quaternion();
			*Q->pQuat = *argQ->pQuat * argD;
			return Q;
		}

		static fk_Quaternion^ operator*(double argD, fk_Quaternion^ argQ)
		{
			if(!argQ) return nullptr;
			fk_Quaternion^ Q = gcnew fk_Quaternion();
			*Q->pQuat = *argQ->pQuat * argD;
			return Q;
		}

		static fk_Quaternion^ operator/(fk_Quaternion^ argQ, double argD)
		{
			if(!argQ) return nullptr;
			fk_Quaternion^ Q = gcnew fk_Quaternion();
			*Q->pQuat = *argQ->pQuat / argD;
			return Q;
		}

		static fk_Vector^ operator*(fk_Quaternion^ argQ, fk_Vector^ argV)
		{
			if(!argQ || !argV) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = (*argQ->pQuat) * (*argV->pVec);
			return V;
		}
		
		static double operator^(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
		{
			if(!argQ1 || !argQ2) return 0.0;
			return (*argQ1->pQuat ^ *argQ2->pQuat);
		}

		//////////////////// 代入演算子
		static void operator *= (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
		{
			if(!argQ1 || !argQ2) return;
			*argQ1->pQuat *= *argQ2->pQuat;
		}


		static void operator *= (fk_Quaternion^ argQ1, double argD)
		{
			if(!argQ1) return;
			*argQ1->pQuat *= argD;
		}

		static void operator /= (fk_Quaternion^ argQ, double argD)
		{
			if(!argQ) return;
			*argQ->pQuat /= argD;
		}


		static void operator += (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
		{
			if(!argQ1 || !argQ2) return;
			*argQ1->pQuat += *argQ2->pQuat;
		}

		static void operator -= (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
		{
			if(!argQ1 || !argQ2) return;
			*argQ1->pQuat -= *argQ2->pQuat;
		}


		//////////////////// メンバ関数群
		String^	fk_Quaternion::ToString() override;

		void init(void);
		void set(double s, double x, double y, double z);
		void set(double s, fk_Vector^ v);
		void setRotate(double theta, double x, double y, double z);
		void setRotate(double theta, fk_Vector^ V);
		void makeEuler(double h, double p, double b);
		void makeEuler(fk_Angle^ angle);
		fk_Angle^ getEuler(void);
		double norm(void);
		double abs(void);
		bool normalize(void);
		void conj(void);
		bool inverse(void);
		fk_Quaternion^ getInverse(void);
		fk_Matrix^ conv(void);
	};
}
