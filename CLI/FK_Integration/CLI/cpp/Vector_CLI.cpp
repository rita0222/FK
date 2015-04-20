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

	fk_Vector::operator ::fk_Vector (fk_Vector^ argV)
	{
		::fk_Vector	V(argV->x_, argV->y_, argV->z_);
		return V;
	}
	
	/////////////////////////////////////////////////////////////


	fk_Vector::fk_Vector()
		: x_(0.0), y_(0.0), z_(0.0)
	{
		return;
	}

	fk_Vector::fk_Vector(double argX, double argY, double argZ)
		: x_(argX), y_(argY), z_(argZ)
	{
		return;
	}

	fk_Vector::fk_Vector(fk_Vector^ argV)
		: x_(argV->x_), y_(argV->y_), z_(argV->z_)
	{
		return;
	}

	fk_Vector::fk_Vector(::fk_Vector *argV)
		: x_(argV->x), y_(argV->y), z_(argV->z)
	{
		return;
	}

	fk_Vector::fk_Vector(::fk_Vector argV)
		: x_(argV.x), y_(argV.y), z_(argV.z)
	{
		return;
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

	fk_HVector::operator ::fk_HVector (fk_HVector^ argV)
	{
		::fk_HVector V(argV->x_, argV->y_, argV->z_, argV->w_);
		return V;
	}

	// コンストラクタ
	fk_HVector::fk_HVector()
		: x_(0.0), y_(0.0), z_(0.0), w_(0.0)
	{
		return;
	}

	fk_HVector::fk_HVector(fk_Vector^ argV)
		: x_(0.0), y_(0.0), z_(0.0), w_(1.0)
	{
		if(!argV) return;
		Set(argV->x_, argV->y_, argV->z_);
		return;
	}
 
	fk_HVector::fk_HVector(fk_Vector^ argV, double argW)
		: x_(0.0), y_(0.0), z_(0.0), w_(argW)
	{
		if(!argV) return;
		Set(argV->x_, argV->y_, argV->z_, argW);
	}

	fk_HVector::fk_HVector(fk_HVector^ argHV)
		: x_(0.0), y_(0.0), z_(0.0), w_(1.0)
	{
		if(!argHV) return;
		Set(argHV->x_, argHV->y_, argHV->z_, argHV->w_);
	}

	fk_HVector::fk_HVector(::fk_HVector argV)
		: x_(argV.x), y_(argV.y), z_(argV.z), w_(argV.w)
	{
		return;
	}

	// デストラクタ
	fk_HVector::~fk_HVector()
	{
		this->!fk_HVector();
	}

	// ファイナライザ
	fk_HVector::!fk_HVector()
	{
		return;
	}

	double fk_HVector::x::get()
	{
		return x_;
	}

	void fk_HVector::x::set(double argV)
	{
		x_ = argV;
	}
	
	double fk_HVector::y::get()
	{
		return y_;
	}

	void fk_HVector::y::set(double argV)
	{
		y_ = argV;
	}
	
	double fk_HVector::z::get()
	{
		return z_;
	}

	void fk_HVector::z::set(double argV)
	{
		z_ = argV;
	}
	
	double fk_HVector::w::get()
	{
		return w_;
	}

	void fk_HVector::w::set(double argV)
	{
		w_ = argV;
	}

	double fk_HVector::operator* (fk_HVector^ argH1, fk_HVector^ argH2)
	{
		if(!argH1 || !argH2) return 0.0;
		return (argH1->x_ * argH2->x_ +
				argH1->y_ * argH2->y_ +
				argH1->z_ * argH2->z_ +
				argH1->w_ * argH2->w_);
	}


	// fk_Vectorとの変換
	fk_HVector::operator fk_HVector^ (fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		return gcnew fk_HVector(argV);
	}

	fk_HVector::operator fk_Vector^ (fk_HVector^ argH)
	{
		if(argH == nullptr) return nullptr;
		return gcnew fk_Vector(argH->x_, argH->y_, argH->z_);
	}

	bool fk_HVector::Equals(fk_HVector^ argH)
	{
		if(argH == nullptr) false;
		::fk_HVector H1(x_, y_, z_, w_);
		::fk_HVector H2(argH->x_, argH->y_, argH->z_, argH->w_);
		return (H1 == H2);
	}
		
	bool fk_HVector::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_HVector^ V = static_cast<fk_HVector^>(argObj);
			::fk_HVector H1(x_, y_, z_, w_);
			::fk_HVector H2(V->x_, V->y_, V->z_, V->w_);
			return (H1 == H2);
		}
		return false;
	}

	String^ fk_HVector::ToString()
	{
		std::string tmpBuf;
		tmpBuf = "H: " + to_string(x_) + ", ";
		tmpBuf += to_string(y_) + ", ";
		tmpBuf += to_string(z_) + ", ";
		tmpBuf += to_string(w_);
		return gcnew System::String(tmpBuf.c_str());
	}

	void fk_HVector::Set(fk_Vector^ argV, double argW)
	{
		if(!argV) return;
		x_ = argV->x_;
		y_ = argV->y_;
		z_ = argV->z_;
		w_ = argW;
		return;
	}

	void fk_HVector::Set(double argX, double argY, double argZ, double argW)
	{
		x_ = argX;
		y_ = argY;
		z_ = argZ;
		w_ = argW;
		return;
	}

	void fk_HVector::Set(double argX, double argY, double argZ)
	{
		x_ = argX;
		y_ = argY;
		z_ = argZ;
		return;
	}

	void fk_HVector::Set(double argX, double argY)
	{
		x_ = argX;
		y_ = argY;
		return;
	}

	void fk_HVector::Set(fk_Vector^ argV)
	{
		if(!argV) return;
		x_ = argV->x_;
		y_ = argV->y_;
		z_ = argV->z_;
		return;
	}

	fk_Vector^ fk_HVector::GetV(void)
	{
		return gcnew fk_Vector(x_, y_, z_);
	}

	void fk_HVector::IsPos(void)
	{
		w_ = 1.0;
		return;
	}

	void fk_HVector::IsVec(void)
	{
		w_ = 0.0;
		return;
	}

	void fk_HVector::Init(void)
	{
		x_ = 0.0;
		y_ = 0.0;
		z_ = 0.0;
		w_ = 1.0;
	}

	////////////////////////////////////////////////////////////////////

	fk_FVector::fk_FVector()
		: x_(0.0f), y_(0.0f), z_(0.0f)
	{
		return;
	}

	fk_FVector::fk_FVector(float argX, float argY, float argZ)
		: x_(argX), y_(argY), z_(argZ)
	{
		return;
	}

	fk_FVector::fk_FVector(fk_FVector^ argFV)
		: x_(0.0f), y_(0.0f), z_(0.0f)
	{
		if(!argFV) return;
		x_ = argFV->x_;
		y_ = argFV->y_;
		z_ = argFV->z_;
		return;
	}

	fk_FVector::~fk_FVector()
	{
		this->!fk_FVector();
	}

	fk_FVector::!fk_FVector()
	{
		return;
	}

	fk_FVector::operator fk_FVector ^ (fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		return gcnew fk_FVector(static_cast<float>(argV->x_),
								static_cast<float>(argV->y_),
								static_cast<float>(argV->z_));
	}


	System::String^ fk_FVector::ToString()
	{
		std::string tmpBuf;
		tmpBuf = "F: " + to_string(x_) + ", ";
		tmpBuf += to_string(y_) + ", ";
		tmpBuf += to_string(z_);
		return gcnew System::String(tmpBuf.c_str());
	}

	float fk_FVector::x::get()
	{
		return x_;
	}

	void fk_FVector::x::set(float argV)
	{
		x_ = argV;
	}

	float fk_FVector::y::get()
	{
		return y_;
	}

	void fk_FVector::y::set(float argV)
	{
		y_ = argV;
	}

	float fk_FVector::z::get()
	{
		return z_;
	}

	void fk_FVector::z::set(float argV)
	{
		z_ = argV;
	}
}
