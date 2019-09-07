/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
#include "Vector_CLI.h"

namespace FK_CLI {

	using namespace std;

	::FK::fk_Axis fk_Vector::GetAxis(FK_CLI::fk_Axis argAxis)
	{
		::FK::fk_Axis tmpAxis;

		switch(argAxis) {
		  case FK_CLI::fk_Axis::X:
			tmpAxis	= ::FK::fk_Axis::X;
			break;
				
		  case FK_CLI::fk_Axis::Y:
			tmpAxis = ::FK::fk_Axis::Y;
			break;

		  case FK_CLI::fk_Axis::Z:
			tmpAxis = ::FK::fk_Axis::Z;
			break;

		  default:
			tmpAxis = ::FK::fk_Axis::X;
			break;
		}
		return tmpAxis;
	}

	fk_Vector::operator ::FK::fk_Vector (fk_Vector^ argV)
	{
		::FK::fk_Vector	V(argV->x_, argV->y_, argV->z_);
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

	fk_Vector::fk_Vector(::FK::fk_Vector *argV)
		: x_(argV->x), y_(argV->y), z_(argV->z)
	{
		return;
	}

	fk_Vector::fk_Vector(::FK::fk_Vector argV)
		: x_(argV.x), y_(argV.y), z_(argV.z)
	{
		return;
	}

	// デストラクタ
	fk_Vector::~fk_Vector()
	{
	}

	bool fk_Vector::Equals(fk_Vector^ argV)
	{
		if(!argV) false;
		::FK::fk_Vector tmpA(x_, y_, z_);
		::FK::fk_Vector tmpB(argV->x_, argV->y_, argV->z_);
		return (tmpA == tmpB);
	}

	bool fk_Vector::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_Vector^ V = static_cast<fk_Vector^>(argObj);
			::FK::fk_Vector tmpA(x_, y_, z_);
			::FK::fk_Vector tmpB(V->x_, V->y_, V->z_);
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
		::FK::fk_Vector V1(argV1->x_, argV1->y_, argV1->z_);
		::FK::fk_Vector V2(argV2->x_, argV2->y_, argV2->z_);
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
		::FK::fk_Vector V(x_, y_, z_);
		return V.dist();
	}
		
	double fk_Vector::Dist2()
	{
		::FK::fk_Vector V(x_, y_, z_);
		return V.dist2();
	}

	bool fk_Vector::Normalize()
	{
		::FK::fk_Vector V(x_, y_, z_);
		if(V.normalize() == false) return false;
		Set(V.x, V.y, V.z);
		return true;
	}

	bool fk_Vector::IsZero()
	{
		::FK::fk_Vector V(x_, y_, z_);
		return V.isZero();
	}

	fk_Vector^ fk_Vector::Proj(fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		::FK::fk_Vector V(x_, y_, z_);
		return gcnew fk_Vector(V.proj(::FK::fk_Vector(argV->x_, argV->y_, argV->z_)));
	}

	fk_Vector^ fk_Vector::Perp(fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		::FK::fk_Vector V(x_, y_, z_);
		return gcnew fk_Vector(V.perp(::FK::fk_Vector(argV->x_, argV->y_, argV->z_)));
	}

	void fk_Vector::Init(void)
	{
		x_ = 0.0;
		y_ = 0.0;
		z_ = 0.0;
	}

	////////////////////////////////////////////////////////////////////

	fk_HVector::operator ::FK::fk_HVector (fk_HVector^ argV)
	{
		::FK::fk_HVector V(argV->x_, argV->y_, argV->z_, argV->w_);
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

	fk_HVector::fk_HVector(::FK::fk_HVector argV)
		: x_(argV.x), y_(argV.y), z_(argV.z), w_(argV.w)
	{
		return;
	}

	// デストラクタ
	fk_HVector::~fk_HVector()
	{
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
		::FK::fk_HVector H1(x_, y_, z_, w_);
		::FK::fk_HVector H2(argH->x_, argH->y_, argH->z_, argH->w_);
		return (H1 == H2);
	}
		
	bool fk_HVector::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_HVector^ V = static_cast<fk_HVector^>(argObj);
			::FK::fk_HVector H1(x_, y_, z_, w_);
			::FK::fk_HVector H2(V->x_, V->y_, V->z_, V->w_);
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

