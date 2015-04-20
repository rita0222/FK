#include "Quaternion_CLI.h"

namespace FK_CLI {

	using namespace std;

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
			pQuat = new ::fk_Quaternion(argS, argV->x_, argV->y_, argV->z_);
		}
	}

	fk_Quaternion::fk_Quaternion(fk_Quaternion^ argQ)
	{
		pQuat = new ::fk_Quaternion(*(argQ->pQuat));
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

	double fk_Quaternion::s::get()
	{
		return pQuat->s;
	}

	void fk_Quaternion::s::set(double value)
	{
		pQuat->s = value;
	}

	double fk_Quaternion::x::get()
	{
		return pQuat->v.x;
	}

	void fk_Quaternion::x::set(double value)
	{
		pQuat->v.x = value;
	}

	double fk_Quaternion::y::get()
	{
		return pQuat->v.y;
	}

	void fk_Quaternion::y::set(double value)
	{
		pQuat->v.y = value;
	}

	double fk_Quaternion::z::get()
	{
		return pQuat->v.z;
	}

	void fk_Quaternion::z::set(double value)
	{
		pQuat->v.z = value;
	}

	fk_Vector^ fk_Quaternion::v::get()
	{
		return gcnew fk_Vector(pQuat->v);
	}

	void fk_Quaternion::v::set(fk_Vector^ argV)
	{
		if(!argV) return;
		pQuat->v = argV;
	}

	void fk_Quaternion::Euler::set(fk_Angle^ argA)
	{
		if(!argA) return;
		pQuat->makeEuler(argA);
	}
	
	fk_Angle^ fk_Quaternion::Euler::get(void)
	{
		return gcnew fk_Angle(pQuat->getEuler());
	}

	double fk_Quaternion::Norm::get(void)
	{
		return pQuat->norm();
	}
	
	double fk_Quaternion::Abs::get(void)
	{
		return pQuat->abs();
	}

	fk_Matrix^ fk_Quaternion::Matrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = pQuat->conv();
		return M;
	}

	fk_Quaternion^ fk_Quaternion::operator-(fk_Quaternion^ argQ)
	{
		if(!argQ) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = -(*argQ->pQuat);
		return Q;
	}

	fk_Quaternion^ fk_Quaternion::operator~(fk_Quaternion^ argQ)
	{
		if(!argQ) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = ~(*argQ->pQuat);
		return Q;
	}

	//////////////////// 二項演算子
	fk_Quaternion^ fk_Quaternion::operator*(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = (*argQ1->pQuat) * (*argQ2->pQuat);
		return Q;
	}
		
	fk_Quaternion^ fk_Quaternion::operator+(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *argQ1->pQuat + *argQ2->pQuat;
		return Q;
	}

	fk_Quaternion^ fk_Quaternion::operator-(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *argQ1->pQuat - *argQ2->pQuat;
		return Q;
	}
			
	fk_Quaternion^ fk_Quaternion::operator*(fk_Quaternion^ argQ, double argD)
	{
		if(!argQ) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *argQ->pQuat * argD;
		return Q;
	}

	fk_Quaternion^ fk_Quaternion::operator*(double argD, fk_Quaternion^ argQ)
	{
		if(!argQ) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *argQ->pQuat * argD;
		return Q;
	}

	fk_Quaternion^ fk_Quaternion::operator/(fk_Quaternion^ argQ, double argD)
	{
		if(!argQ) return nullptr;
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *argQ->pQuat / argD;
		return Q;
	}

	fk_Vector^ fk_Quaternion::operator*(fk_Quaternion^ argQ, fk_Vector^ argV)
	{
		if(!argQ || !argV) return nullptr;
		fk_Vector^ V = gcnew fk_Vector((*argQ->pQuat) * argV);
		return V;
	}
		
	double fk_Quaternion::operator^(fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return 0.0;
		return (*argQ1->pQuat ^ *argQ2->pQuat);
	}

	//////////////////// 代入演算子
	void fk_Quaternion::operator *= (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return;
		*argQ1->pQuat *= *argQ2->pQuat;
	}


	void fk_Quaternion::operator *= (fk_Quaternion^ argQ1, double argD)
	{
		if(!argQ1) return;
		*argQ1->pQuat *= argD;
	}

	void fk_Quaternion::operator /= (fk_Quaternion^ argQ, double argD)
	{
		if(!argQ) return;
		*argQ->pQuat /= argD;
	}


	void fk_Quaternion::operator += (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return;
		*argQ1->pQuat += *argQ2->pQuat;
	}

	void fk_Quaternion::operator -= (fk_Quaternion^ argQ1, fk_Quaternion^ argQ2)
	{
		if(!argQ1 || !argQ2) return;
		*argQ1->pQuat -= *argQ2->pQuat;
	}

	bool fk_Quaternion::Equals(fk_Quaternion^ argQ)
	{
		if(!argQ) false;
		return (*argQ->pQuat == *pQuat);
	}

	bool fk_Quaternion::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_Quaternion^ V = static_cast<fk_Quaternion^>(argObj);
			return (*V->pQuat == *pQuat);
		}
		return false;
	}

	String^	fk_Quaternion::ToString()
	{
		string	tmpBuf;
		tmpBuf = "Q: " + to_string(pQuat->s) + ", ";
		tmpBuf += to_string(pQuat->v.x) + ", ";
		tmpBuf += to_string(pQuat->v.y) + ", ";
		tmpBuf += to_string(pQuat->v.z);
		return gcnew String(tmpBuf.c_str());
	}

	void fk_Quaternion::Init(void)
	{
		pQuat->init();
	}
	
	void fk_Quaternion::Set(double argS, double argX, double argY, double argZ)
	{
		pQuat->set(argS, argX, argY, argZ);
	}
	
	void fk_Quaternion::Set(double argS, fk_Vector^ argV)
	{
		if(!argV) return;
		pQuat->set(argS, argV);
	}
	
	void fk_Quaternion::SetRotate(double argT, double argX, double argY, double argZ)
	{
		pQuat->setRotate(argT, argX, argY, argZ);
	}
	
	void fk_Quaternion::SetRotate(double argT, fk_Vector^ argV)
	{
		if(!argV) return;
		pQuat->setRotate(argT, argV);
	}

	bool fk_Quaternion::Normalize(void)
	{
		return pQuat->normalize();
	}
	
	void fk_Quaternion::Conj(void)
	{
		pQuat->conj();
	}
	
	bool fk_Quaternion::Inverse(void)
	{
		return pQuat->inverse();
	}
	
	fk_Quaternion^ fk_Quaternion::GetInverse(void)
	{
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *pQuat;
		Q->Inverse();
		return Q;
	}
}

