// Vector_CLI.h

#pragma once

#include <string>
#include <FK/Vector.h>

using namespace std;
using namespace System;

namespace FK_CLI
{
	public enum	class fk_Axis
	{
		X,
		Y,
		Z
	};
	
	::fk_Axis GetAxis(FK_CLI::fk_Axis argAxis);

	public ref class fk_Vector {
	internal:
		::fk_Vector *pVec;
	public:
		fk_Vector::fk_Vector()
		{
			this->pVec = new ::fk_Vector();
		}

		fk_Vector::fk_Vector(double argX, double argY, double argZ)
		{
			this->pVec = new ::fk_Vector(argX, argY, argZ);
		}

		// デストラクタ
		fk_Vector::~fk_Vector()
		{
			this->!fk_Vector();
		}

		// ファイナライザ
		fk_Vector::!fk_Vector()
		{
			delete this->pVec;
		}

		property double	x
		{
			double get()
			{
				return pVec->x;
			}

			void set(double value)
			{
				pVec->x = value;
			}
		}

		property double y
		{
			double get()
			{
				return pVec->y;
			}

			void set(double value)
			{
				pVec->y = value;
			}
		}

		property double z
		{
			double get()
			{
				return pVec->z;
			}

			void set(double value)
			{
				pVec->z = value;
			}
		}
		String^	fk_Vector::ToString() override
		{
			std::string	tmpBuf;
			tmpBuf = "V: " + to_string(this->pVec->x) + ", ";
			tmpBuf += to_string(this->pVec->y) + ", ";
			tmpBuf += to_string(this->pVec->z);
			return gcnew String(tmpBuf.c_str());
		}

		//////////////////// 比較演算子		
		bool Equals(fk_Vector^ argV)
		{
			if(!argV) false;
			return (*argV->pVec == *this->pVec);
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_Vector^ V = static_cast<fk_Vector^>(argObj);
				return (*V->pVec == *this->pVec);
			}
			return false;
		}

		//////////////////// 単項演算子
		static fk_Vector^ operator-(fk_Vector^ argV)
		{
			if(!argV) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = -(*argV->pVec);
			return V;
		}

		//////////////////// 二項演算子
		static double operator*(fk_Vector^ argV1, fk_Vector^ argV2)
		{
			if(!argV1 || !argV2) return 0.0;
			return (*argV1->pVec) * (*argV2->pVec);
		}
		
		static fk_Vector^ operator+(fk_Vector^ argV1, fk_Vector^ argV2)
		{
			if(!argV1 || !argV2) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = *argV1->pVec + *argV2->pVec;
			return V;
		}

		static fk_Vector^ operator-(fk_Vector^ argV1, fk_Vector^ argV2)
		{
			if(!argV1 || !argV2) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = *argV1->pVec - *argV2->pVec;
			return V;
		}
			
		static fk_Vector^ operator*(fk_Vector^ argV, double argD)
		{
			if(!argV) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = *argV->pVec * argD;
			return V;
		}

		static fk_Vector^ operator*(double argD, fk_Vector^ argV)
		{
			if(!argV) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = *argV->pVec * argD;
			return V;
		}

		static fk_Vector^ operator/(fk_Vector^ argV, double argD)
		{
			if(!argV) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = *argV->pVec / argD;
			return V;
		}

		static fk_Vector^ operator^(fk_Vector^ argV1, fk_Vector^ argV2)
		{
			if(!argV1 || !argV2) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = *argV1->pVec ^ *argV2->pVec;
			return V;
		}

		//////////////////// 代入演算子
		static void operator *= (fk_Vector^ argV1, double argD)
		{
			if(!argV1) return;
			*argV1->pVec *= argD;
		}

		static void operator /= (fk_Vector^ argV, double argD)
		{
			if(!argV) return;
			*argV->pVec /= argD;
		}


		static void operator += (fk_Vector^ argV1, fk_Vector^ argV2)
		{
			if(!argV1 || !argV2) return;
			*argV1->pVec += *argV2->pVec;
		}

		static void operator -= (fk_Vector^ argV1, fk_Vector^ argV2)
		{
			if(!argV1 || !argV2) return;
			*argV1->pVec -= *argV2->pVec;
		}


		//////////////////// メンバ関数群
		void set(double argX, double argY, double argZ)
		{
			this->pVec->set(argX, argY, argZ);
		}

		void set(double argX, double argY)
		{
			this->pVec->set(argX, argY, 0.0);
		}

		double dist()
		{
			return this->pVec->dist();
		}
		
		double dist2()
		{
			return this->pVec->dist2();
		}

		bool normalize()
		{
			return this->pVec->normalize();
		}

		bool isZero()
		{
			return this->pVec->isZero();
		}

		fk_Vector^ proj(fk_Vector^ argV)
		{
			if(!argV) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = this->pVec->proj(*argV->pVec);
			return V;
		}

		fk_Vector^ perp(fk_Vector^ argV)
		{
			if(!argV) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = this->pVec->perp(*argV->pVec);
			return V;
		}
	};

	public ref class fk_HVector {
	internal:
		::fk_HVector *pHVec;

	public:
		// コンストラクタ
		fk_HVector()
		{
			this->pHVec = new ::fk_HVector();
		}

		fk_HVector(fk_Vector^ argV)
		{
			if(!argV) return;
			this->pHVec = new ::fk_HVector();
			this->pHVec->set(*argV->pVec, 1.0);
		}

		fk_HVector(fk_Vector^ argV, double argW)
		{
			this->pHVec = new ::fk_HVector();
			if(!argV) return;
			this->pHVec->set(*argV->pVec, argW);
		}

		// デストラクタ
		~fk_HVector()
		{
			this->!fk_HVector();
		}

		// ファイナライザ
		!fk_HVector()
		{
			delete this->pHVec;
		}

		// ToString追加
		System::String^ ToString() override
		{
			std::string tmpBuf;
			tmpBuf = "H: " + to_string(this->pHVec->x) + ", ";
			tmpBuf += to_string(this->pHVec->y) + ", ";
			tmpBuf += to_string(this->pHVec->z) + ", ";
			tmpBuf += to_string(this->pHVec->w);
			return gcnew System::String(tmpBuf.c_str());
		}

		// プロパティ一覧
		property double x
		{
			double get()
			{
				return pHVec->x;
			}
			
			void set(double argX)
			{
				pHVec->x = argX;
			}
		}

		property double y
		{
			double get()
			{
				return pHVec->y;
			}
			
			void set(double argY)
			{
				pHVec->y = argY;
			}
		}

		property double z
		{
			double get()
			{
				return pHVec->z;
			}
			
			void set(double argZ)
			{
				pHVec->z = argZ;
			}
		}

		property double w
		{
			double get()
			{
				return pHVec->w;
			}
			
			void set(double argW)
			{
				pHVec->w = argW;
			}
		}

		static double operator* (fk_HVector^ argH1, fk_HVector^ argH2)
		{
			if(!argH1 || !argH2) return 0.0;
			return ((*argH1->pHVec) * (*argH2->pHVec));
		}


		// fk_Vectorとの変換
		static operator fk_HVector^ (fk_Vector^ argV)
		{
			if(!argV) return nullptr;
			fk_HVector^ H = gcnew fk_HVector(argV);
			return H;
		}

		static operator fk_Vector^ (fk_HVector^ argH)
		{
			if(argH == nullptr) return nullptr;
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = *argH->pHVec;
			return V;
		}

		//////////////////// 比較演算子		
		bool Equals(fk_HVector^ argH)
		{
			if(argH == nullptr) false;
			return (*argH->pHVec == *this->pHVec);
		}
		
		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_HVector^ V = static_cast<fk_HVector^>(argObj);
				return (*V->pHVec == *this->pHVec);
			}
			return false;
		}

		void set(fk_Vector^ argV, double argW)
		{
			if(!argV) return;
			this->pHVec->set(*(argV->pVec), argW);
		}

		void set(double argX, double argY, double argZ, double argW)
		{
			this->pHVec->set(argX, argY, argZ, argW);
		}

		void set(double argX, double argY, double argZ)
		{
			this->pHVec->set(argX, argY, argZ, 1.0);
		}

		void set(double argX, double argY)
		{
			this->pHVec->set(argX, argY, 0.0, 1.0);
		}

		void set(fk_Vector^ argV)
		{
			if(!argV) return;
			this->pHVec->set(*argV->pVec);
		}

		fk_Vector^ getV(void)
		{
			fk_Vector^ V = gcnew fk_Vector();
			V->pVec->set(this->pHVec->x, this->pHVec->y, this->pHVec->z);
			return V;
		}

		void ispos(void)
		{
			this->pHVec->ispos();
		}

		void isvec(void)
		{
			this->pHVec->isvec();
		}

		void init(void)
		{
			this->pHVec->init();
		}
	};

	public ref class fk_FVector {
	internal:
		::fk_FVector *pFVec;
	public:
		fk_FVector()
		{
			this->pFVec = new ::fk_FVector();
		}

		~fk_FVector()
		{
			this->!fk_FVector();
		}

		!fk_FVector()
		{
			delete this->pFVec;
		}

		static operator fk_Vector^(fk_FVector^ argF)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*(V->pVec) = *(argF->pFVec);
			return V;
		}

		static operator fk_FVector ^ (fk_Vector^ argV)
		{
			fk_FVector^ F = gcnew fk_FVector();
			*(F->pFVec) = *(argV->pVec);
			return F;
		}

		System::String^ ToString() override
		{
			std::string tmpBuf;
			tmpBuf = "F: " + to_string(this->pFVec->x) + ", ";
			tmpBuf += to_string(this->pFVec->y) + ", ";
			tmpBuf += to_string(this->pFVec->z);
			return gcnew System::String(tmpBuf.c_str());
		}
	};
}
