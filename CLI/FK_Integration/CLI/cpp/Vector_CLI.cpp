#include "Vector_CLI.h"

namespace FK_CLI {

	using namespace std;

	::fk_Axis GetAxis(FK_CLI::fk_Axis argAxis)
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

	void fk_Vector::set(double argX, double argY, double argZ)
	{
		pVec->set(argX, argY, argZ);
	}

	void fk_Vector::set(double argX, double argY)
	{
		pVec->set(argX, argY, 0.0);
	}

	double fk_Vector::dist()
	{
		return pVec->dist();
	}
		
	double fk_Vector::dist2()
	{
		return pVec->dist2();
	}

	bool fk_Vector::normalize()
	{
		return pVec->normalize();
	}

	bool fk_Vector::isZero()
	{
		return pVec->isZero();
	}

	fk_Vector^ fk_Vector::proj(fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = pVec->proj(*argV->pVec);
		return V;
	}

	fk_Vector^ fk_Vector::perp(fk_Vector^ argV)
	{
		if(!argV) return nullptr;
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = pVec->perp(*argV->pVec);
		return V;
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

	void fk_HVector::set(fk_Vector^ argV, double argW)
	{
		if(!argV) return;
		pHVec->set(*(argV->pVec), argW);
	}

	void fk_HVector::set(double argX, double argY, double argZ, double argW)
	{
		pHVec->set(argX, argY, argZ, argW);
	}

	void fk_HVector::set(double argX, double argY, double argZ)
	{
		pHVec->set(argX, argY, argZ, 1.0);
	}

	void fk_HVector::set(double argX, double argY)
	{
		pHVec->set(argX, argY, 0.0, 1.0);
	}

	void fk_HVector::set(fk_Vector^ argV)
	{
		if(!argV) return;
		pHVec->set(*argV->pVec);
	}

	fk_Vector^ fk_HVector::getV(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		V->pVec->set(pHVec->x, pHVec->y, pHVec->z);
		return V;
	}

	void fk_HVector::ispos(void)
	{
		pHVec->ispos();
	}

	void fk_HVector::isvec(void)
	{
		pHVec->isvec();
	}

	void fk_HVector::init(void)
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

