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

	String^	fk_Vector::ToString()
	{
		std::string	tmpBuf;
		tmpBuf = "V: " + to_string(pVec->x) + ", ";
		tmpBuf += to_string(pVec->y) + ", ";
		tmpBuf += to_string(pVec->z);
		return gcnew String(tmpBuf.c_str());
	}

	double fk_Vector::x::get()
	{
		return pVec->x;
	}

	void fk_Vector::x::set(double value)
	{
		pVec->x = value;
	}

	double fk_Vector::y::get()
	{
		return pVec->y;
	}

	void fk_Vector::y::set(double value)
	{
		pVec->y = value;
	}

	double fk_Vector::z::get()
	{
		return pVec->z;
	}

	void fk_Vector::z::set(double value)
	{
		pVec->z = value;
	}
	
	void fk_Vector::Set(double argX, double argY, double argZ)
	{
		pVec->set(argX, argY, argZ);
	}

	void fk_Vector::Set(double argX, double argY)
	{
		pVec->set(argX, argY, 0.0);
	}

	double fk_Vector::Dist()
	{
		return pVec->dist();
	}
		
	double fk_Vector::Dist2()
	{
		return pVec->dist2();
	}

	bool fk_Vector::Normalize()
	{
		return pVec->normalize();
	}

	bool fk_Vector::IsZero()
	{
		return pVec->isZero();
	}

	fk_Vector^ fk_Vector::Proj(fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		return gcnew fk_Vector(pVec->proj(*argV->pVec));
	}

	fk_Vector^ fk_Vector::Perp(fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		return gcnew fk_Vector(pVec->perp(*argV->pVec));
	}

	////////////////////////////////////////////////////////////////////

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
		pHVec->set(*(argV->pVec), argW);
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
		pHVec->set(*argV->pVec);
	}

	fk_Vector^ fk_HVector::GetV(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		V->pVec->set(pHVec->x, pHVec->y, pHVec->z);
		return V;
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


	System::String^ fk_FVector::ToString()
	{
		std::string tmpBuf;
		tmpBuf = "F: " + to_string(pFVec->x) + ", ";
		tmpBuf += to_string(pFVec->y) + ", ";
		tmpBuf += to_string(pFVec->z);
		return gcnew System::String(tmpBuf.c_str());
	}
}
