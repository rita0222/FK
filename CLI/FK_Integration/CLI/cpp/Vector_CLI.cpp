#include "Vector_CLI.h"

namespace FK_CLI {

	using namespace std;

	::fk_Axis fk_Vector::GetAxis(FK_CLI::fk_Axis argAxis)
	{
		::fk_Axis tmpAxis;

		switch(argAxis) {
		  case FK_CLI::fk_Axis::X:
			tmpAxis	= fk_X;
			break;
				
		  case FK_CLI::fk_Axis::Y:
			tmpAxis = fk_Y;
			break;

		  case FK_CLI::fk_Axis::Z:
			tmpAxis = fk_Z;
			break;

		  default:
			tmpAxis = fk_X;
			break;
		}
		return tmpAxis;
	}

	/////////////////////////////////////////////////////////////


	fk_Vector::fk_Vector()
	{
		x_ = y_ = z_ = 0.0;
	}

	fk_Vector::fk_Vector(double argX, double argY, double argZ)
	{
		x_ = argX;
		y_ = argY;
		z_ = argZ;
	}

	fk_Vector::fk_Vector(fk_Vector^ argV)
	{
		x_ = argV->x_;
		y_ = argV->y_;
		z_ = argV->z_;
	}

	fk_Vector::fk_Vector(::fk_Vector *argV)
	{
		x_ = argV->x;
		y_ = argV->y;
		z_ = argV->z;
	}

	fk_Vector::fk_Vector(::fk_Vector argV)
	{
		x_ = argV.x;
		y_ = argV.y;
		z_ = argV.z;
	}

	// デストラクタ
	fk_Vector::~fk_Vector()
	{
		this->!fk_Vector();
	}

	// ファイナライザ
	fk_Vector::!fk_Vector()
	{
	}
	
	bool fk_Vector::Equals(fk_Vector^ argV)
	{
		if(!argV) false;
		::fk_Vector tmpA(x_, y_, z_);
		::fk_Vector tmpB(argV->x_, argV->y_, argV->z_);
		return (tmpA == tmpB);
	}

	bool fk_Vector::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_Vector^ V = static_cast<fk_Vector^>(argObj);
			::fk_Vector tmpA(x_, y_, z_);
			::fk_Vector tmpB(V->x_, V->y_, V->z_);
			return (tmpA == tmpB);
		}
		return false;
	}
	
	String^	fk_Vector::ToString()
	{
		std::string	tmpBuf;
		tmpBuf = "V: " + to_string(x_) + ", ";
		tmpBuf += to_string(y_) + ", ";
		tmpBuf += to_string(z_);
		return gcnew String(tmpBuf.c_str());
	}

	fk_Vector^ fk_Vector::operator-(fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		fk_Vector^ V = gcnew fk_Vector(-argV->x_, -argV->y_, -argV->z_);
		return V;
	}
	
	double fk_Vector::operator*(fk_Vector^ argV1, fk_Vector^ argV2)
	{
		if(!argV1 || !argV2) return 0.0;
		return (argV1->x_ * argV2->x_ + argV1->y_ * argV2->y_ + argV1->z_ * argV2->z_);
	}
		
	fk_Vector^ fk_Vector::operator+(fk_Vector^ argV1, fk_Vector^ argV2)
	{
		if(!argV1 || !argV2) return nullptr;
		fk_Vector^ V = gcnew fk_Vector(argV1->x_ + argV2->x_,
									   argV1->y_ + argV2->y_,
									   argV1->z_ + argV2->z_);
		return V;
	}

	fk_Vector^ fk_Vector::operator-(fk_Vector^ argV1, fk_Vector^ argV2)
	{
		if(!argV1 || !argV2) return nullptr;
		fk_Vector^ V = gcnew fk_Vector(argV1->x_ - argV2->x_,
									   argV1->y_ - argV2->y_,
									   argV1->z_ - argV2->z_);
		return V;
	}
			
	fk_Vector^ fk_Vector::operator*(fk_Vector^ argV, double argD)
	{
		if(!argV) return nullptr;
		fk_Vector^ V = gcnew fk_Vector(argV->x_ * argD, argV->y_ * argD, argV->z_ * argD);
		return V;
	}

	fk_Vector^ fk_Vector::operator*(double argD, fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		fk_Vector^ V = gcnew fk_Vector(argV->x_ * argD, argV->y_ * argD, argV->z_ * argD);
		return V;
	}

	fk_Vector^ fk_Vector::operator/(fk_Vector^ argV, double argD)
	{
		if(!argV) return nullptr;
		fk_Vector^ V = gcnew fk_Vector(argV->x_ / argD, argV->y_ / argD, argV->z_ / argD);
		return V;
	}

	fk_Vector^ fk_Vector::operator^(fk_Vector^ argV1, fk_Vector^ argV2)
	{
		if(!argV1 || !argV2) return nullptr;
		::fk_Vector V1(argV1->x_, argV1->y_, argV1->z_);
		::fk_Vector V2(argV2->x_, argV2->y_, argV2->z_);
		fk_Vector^ V = gcnew fk_Vector(V1 ^ V2);
		return V;
	}

	void fk_Vector::operator *= (fk_Vector^ argV1, double argD)
	{
		if(!argV1) return;
		argV1->x_ *= argD;
		argV1->y_ *= argD;
		argV1->z_ *= argD;
	}

	void fk_Vector::operator /= (fk_Vector^ argV, double argD)
	{
		if(!argV) return;
		argV->x_ /= argD;
		argV->y_ /= argD;
		argV->z_ /= argD;
	}


	void fk_Vector::operator += (fk_Vector^ argV1, fk_Vector^ argV2)
	{
		if(!argV1 || !argV2) return;
		argV1->x_ += argV2->x_;
		argV1->y_ += argV2->y_;
		argV1->z_ += argV2->z_;
	}

	void fk_Vector::operator -= (fk_Vector^ argV1, fk_Vector^ argV2)
	{
		if(!argV1 || !argV2) return;
		argV1->x_ -= argV2->x_;
		argV1->y_ -= argV2->y_;
		argV1->z_ -= argV2->z_;
	}

	double fk_Vector::x::get()
	{
		return x_;
	}

	void fk_Vector::x::set(double value)
	{
		x_ = value;
	}

	double fk_Vector::y::get()
	{
		return y_;
	}

	void fk_Vector::y::set(double value)
	{
		y_ = value;
	}

	double fk_Vector::z::get()
	{
		return z_;
	}

	void fk_Vector::z::set(double value)
	{
		z_ = value;
	}
	
	void fk_Vector::Set(double argX, double argY, double argZ)
	{
		x_ = argX;
		y_ = argY;
		z_ = argZ;
	}

	void fk_Vector::Set(double argX, double argY)
	{
		x_ = argX;
		y_ = argY;
		z_ = 0.0;
	}

	double fk_Vector::Dist()
	{
		::fk_Vector V(x_, y_, z_);
		return V.dist();
	}
		
	double fk_Vector::Dist2()
	{
		::fk_Vector V(x_, y_, z_);
		return V.dist2();
	}

	bool fk_Vector::Normalize()
	{
		::fk_Vector V(x_, y_, z_);
		if(V.normalize() == false) return false;
		Set(V.x, V.y, V.z);
		return true;
	}

	bool fk_Vector::IsZero()
	{
		::fk_Vector V(x_, y_, z_);
		return V.isZero();
	}

	fk_Vector^ fk_Vector::Proj(fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		::fk_Vector V(x_, y_, z_);
		return gcnew fk_Vector(V.proj(::fk_Vector(argV->x_, argV->y_, argV->z_)));
	}

	fk_Vector^ fk_Vector::Perp(fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		::fk_Vector V(x_, y_, z_);
		return gcnew fk_Vector(V.perp(::fk_Vector(argV->x_, argV->y_, argV->z_)));
	}

	////////////////////////////////////////////////////////////////////
	// コンストラクタ
	fk_HVector::fk_HVector()
	{
		pHVec = new ::fk_HVector();
	}

	fk_HVector::fk_HVector(fk_Vector^ argV)
	{
		if(!argV) return;
		pHVec = new ::fk_HVector();
		pHVec->set(argV->x_, argV->y_, argV->z_, 1.0);
	}

	fk_HVector::fk_HVector(fk_Vector^ argV, double argW)
	{
		pHVec = new ::fk_HVector();
		if(!argV) return;
		pHVec->set(argV->x_, argV->y_, argV->z_, argW);
	}

	fk_HVector::fk_HVector(fk_HVector^ argHV)
	{
		if(!argHV) return;
		pHVec = new ::fk_HVector();
		pHVec->set(*argHV->pHVec);
	}

	// デストラクタ
	fk_HVector::~fk_HVector()
	{
		this->!fk_HVector();
	}

	// ファイナライザ
	fk_HVector::!fk_HVector()
	{
		delete pHVec;
	}

	double fk_HVector::x::get()
	{
		return pHVec->x;
	}

	void fk_HVector::x::set(double argV)
	{
		pHVec->x = argV;
	}
	
	double fk_HVector::y::get()
	{
		return pHVec->y;
	}

	void fk_HVector::y::set(double argV)
	{
		pHVec->y = argV;
	}
	
	double fk_HVector::z::get()
	{
		return pHVec->z;
	}

	void fk_HVector::z::set(double argV)
	{
		pHVec->z = argV;
	}
	
	double fk_HVector::w::get()
	{
		return pHVec->w;
	}

	void fk_HVector::w::set(double argV)
	{
		pHVec->w = argV;
	}

	double fk_HVector::operator* (fk_HVector^ argH1, fk_HVector^ argH2)
	{
		if(!argH1 || !argH2) return 0.0;
		return ((*argH1->pHVec) * (*argH2->pHVec));
	}


	// fk_Vectorとの変換
	fk_HVector::operator fk_HVector^ (fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		fk_HVector^ H = gcnew fk_HVector(argV);
		return H;
	}

	fk_HVector::operator fk_Vector^ (fk_HVector^ argH)
	{
		if(argH == nullptr) return nullptr;
		return gcnew fk_Vector(*argH->pHVec);
	}

	bool fk_HVector::Equals(fk_HVector^ argH)
	{
		if(argH == nullptr) false;
		return (*argH->pHVec == *pHVec);
	}
		
	bool fk_HVector::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_HVector^ V = static_cast<fk_HVector^>(argObj);
			return (*V->pHVec == *pHVec);
		}
		return false;
	}

	String^ fk_HVector::ToString()
	{
		std::string tmpBuf;
		tmpBuf = "H: " + to_string(pHVec->x) + ", ";
		tmpBuf += to_string(pHVec->y) + ", ";
		tmpBuf += to_string(pHVec->z) + ", ";
		tmpBuf += to_string(pHVec->w);
		return gcnew System::String(tmpBuf.c_str());
	}

	void fk_HVector::Set(fk_Vector^ argV, double argW)
	{
		if(!argV) return;
		pHVec->set(argV->x_, argV->y_, argV->z_, argW);
	}

	void fk_HVector::Set(double argX, double argY, double argZ, double argW)
	{
		pHVec->set(argX, argY, argZ, argW);
	}

	void fk_HVector::Set(double argX, double argY, double argZ)
	{
		pHVec->set(argX, argY, argZ, 1.0);
	}

	void fk_HVector::Set(double argX, double argY)
	{
		pHVec->set(argX, argY, 0.0, 1.0);
	}

	void fk_HVector::Set(fk_Vector^ argV)
	{
		if(!argV) return;
		pHVec->set(argV->x_, argV->y_, argV->z_);
	}

	fk_Vector^ fk_HVector::GetV(void)
	{
		return gcnew fk_Vector(pHVec->x, pHVec->y, pHVec->z);
	}

	void fk_HVector::IsPos(void)
	{
		pHVec->ispos();
	}

	void fk_HVector::IsVec(void)
	{
		pHVec->isvec();
	}

	void fk_HVector::Init(void)
	{
		pHVec->init();
	}

	////////////////////////////////////////////////////////////////////

	fk_FVector::fk_FVector()
	{
		pFVec = new ::fk_FVector();
	}

	fk_FVector::fk_FVector(fk_FVector^ argFV)
	{
		pFVec = new ::fk_FVector(*(argFV->pFVec));
	}

	fk_FVector::~fk_FVector()
	{
		this->!fk_FVector();
	}

	fk_FVector::!fk_FVector()
	{
		delete pFVec;
	}
	
	fk_FVector::operator fk_Vector^(fk_FVector^ argF)
	{
		return gcnew fk_Vector(*argF->pFVec);
	}

	fk_FVector::operator fk_FVector ^ (fk_Vector^ argV)
	{
		fk_FVector^ F = gcnew fk_FVector();
		F->pFVec->x = static_cast<float>(argV->x_);
		F->pFVec->y = static_cast<float>(argV->y_);
		F->pFVec->z = static_cast<float>(argV->z_);
		return F;
	}


	System::String^ fk_FVector::ToString()
	{
		std::string tmpBuf;
		tmpBuf = "F: " + to_string(pFVec->x) + ", ";
		tmpBuf += to_string(pFVec->y) + ", ";
		tmpBuf += to_string(pFVec->z);
		return gcnew System::String(tmpBuf.c_str());
	}

	float fk_FVector::x::get()
	{
		return pFVec->x;
	}

	void fk_FVector::x::set(float argV)
	{
		pFVec->x = argV;
	}

	float fk_FVector::y::get()
	{
		return pFVec->y;
	}

	void fk_FVector::y::set(float argV)
	{
		pFVec->y = argV;
	}

	float fk_FVector::z::get()
	{
		return pFVec->z;
	}

	void fk_FVector::z::set(float argV)
	{
		pFVec->z = argV;
	}
}
