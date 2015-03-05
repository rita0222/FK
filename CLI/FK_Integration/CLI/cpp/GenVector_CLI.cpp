#include "GenVector_CLI.h"

namespace FK_CLI {

	using namespace std;
		
	fk_GenVector::fk_GenVector()
	{
		pGVec = new ::fk_GenVector();
	}

	fk_GenVector::fk_GenVector(int deg)
	{
		pGVec = new ::fk_GenVector(deg);
	}

	fk_GenVector::fk_GenVector(::fk_GenVector *argV)
	{
		pGVec = new ::fk_GenVector(*argV);
	}

	fk_GenVector::fk_GenVector(array<double>^ argArray)
	{
		pin_ptr<double> pD = &argArray[0];
		pGVec = new ::fk_GenVector(argArray->Length, pD);
	}

	fk_GenVector::fk_GenVector(fk_Vector^ argV)
	{
		if(!argV) {
			pGVec = new ::fk_GenVector();
		} else {
			pGVec = new ::fk_GenVector(*argV->pVec);
		}
	}

	fk_GenVector::fk_GenVector(fk_HVector^ argH)
	{
		if(!argH) {
			pGVec = new ::fk_GenVector();
		} else {
			pGVec = new ::fk_GenVector(*argH->pHVec);
		}
	}
		
	fk_GenVector::fk_GenVector(fk_GenVector^ argGV)
	{
		if(!argGV) {
			pGVec = new ::fk_GenVector();
		} else {
			pGVec = new ::fk_GenVector(*argGV->pGVec);
		}
	}

	fk_GenVector::~fk_GenVector()
	{
		this->!fk_GenVector();
	}

	fk_GenVector::!fk_GenVector()
	{
		delete pGVec;
	}

	bool fk_GenVector::Equals(fk_GenVector^ argGV)
	{
		if(!argGV) false;
		return (*argGV->pGVec == *pGVec);
	}

	bool fk_GenVector::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_GenVector^ GV = static_cast<fk_GenVector^>(argObj);
			return (*GV->pGVec == *pGVec);
		}
		return false;
	}

	//////////////////// 単項演算子
	fk_GenVector^ fk_GenVector::operator-(fk_GenVector^ argV)
	{
		if(!argV) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = -(*argV->pGVec);
		return V;
	}

	double fk_GenVector::operator*(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return 0.0;
		return (*argV1->pGVec) * (*argV2->pGVec);
	}
		
	fk_GenVector^ fk_GenVector::operator+(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = (*argV1->pGVec) + (*argV2->pGVec);
		return V;
	}
			
	fk_GenVector^ fk_GenVector::operator-(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = (*argV1->pGVec) - (*argV2->pGVec);
		return V;
	}
			
	fk_GenVector^ fk_GenVector::operator*(fk_GenVector^ argV, double argD)
	{
		if(!argV) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = *argV->pGVec * argD;
		return V;
	}
						  
	fk_GenVector^ fk_GenVector::operator*(double argD, fk_GenVector^ argV)
	{
		if(!argV) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = *argV->pGVec * argD;
		return V;
	}
			
	fk_GenVector^ fk_GenVector::operator/(fk_GenVector^ argV, double argD)
	{
		if(!argV) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = *argV->pGVec/argD;
		return V;
	}
			
	fk_GenVector^ fk_GenVector::operator ^(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = (*argV1->pGVec) ^ (*argV2->pGVec);
		return V;
	}

	//代入演算子 
	void fk_GenVector::operator *=(fk_GenVector^ argV, double argD)
	{
		if(!argV) return;
		*argV->pGVec *= argD;
	}

	void fk_GenVector::operator /=(fk_GenVector^ argV, double argD)
	{
		if(!argV) return;
		*argV->pGVec /= argD;
	}

	void fk_GenVector::operator +=(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return;
		*argV1->pGVec += *argV2->pGVec;
	}

	void fk_GenVector::operator -=(fk_GenVector^ argV1, fk_GenVector^ argV2)
	{
		if(!argV1 || !argV2) return;
		*argV1->pGVec -= *argV2->pGVec;
	}


	String^	fk_GenVector::ToString()
	{
		string tmpBuf;
		int size = pGVec->size();

		tmpBuf += "GV = ";
		for(int i = 0; i < size; ++i) {
			tmpBuf += to_string(pGVec->get(i));
			if(i != size-1) tmpBuf += ", ";
		}
		return gcnew String(tmpBuf.c_str());
	}

	void fk_GenVector::default::set(int argID, double argValue)
	{
		pGVec->set(argID, argValue);
	}
	
	double fk_GenVector::default::get(int argID)
	{
		return pGVec->get(argID);
	}

	void fk_GenVector::Size::set(int argDeg)
	{
		pGVec->resize(argDeg);
	}
	
	int fk_GenVector::Size::get(void)
	{
		return pGVec->size();
	}
	
	double fk_GenVector::Norm::get(void)
	{
		return pGVec->norm();
	}
	
	double fk_GenVector::Norm2::get(void)
	{
		return pGVec->norm2();
	}
	
	bool fk_GenVector::Normalize(void)
	{
		return pGVec->normalize();
	}
	
	void fk_GenVector::Init(bool argDegFlg)
	{
		pGVec->init(argDegFlg);
	}
	
	void fk_GenVector::Init(void)
	{
		pGVec->init();
	}
	
	bool fk_GenVector::IsZero(void)
	{
		return pGVec->isZero();
	}
	
	bool fk_GenVector::Replace(int argS, fk_GenVector^ argV)
	{
		if(!argV) return false;
		return pGVec->replace(argS, *argV->pGVec);
	}
	
	bool fk_GenVector::Replace(int argS, fk_Vector^ argV)
	{
		if(!argV) return false;
		return pGVec->replace(argS, *argV->pVec);
	}

	bool fk_GenVector::Replace(int argS, fk_HVector^ argV)
	{
		if(!argV) return false;
		return pGVec->replace(argS, *argV->pHVec);
	}

	bool fk_GenVector::Add(int argS, fk_GenVector^ argV)
	{
		if(!argV) return false;
		return pGVec->add(argS, *argV->pGVec);
	}

	bool fk_GenVector::Add(int argS, fk_Vector^ argV)
	{
		if(!argV) return false;
		return pGVec->add(argS, *argV->pVec);
	}

	bool fk_GenVector::Add(int argS, fk_HVector^ argV)
	{
		if(!argV) return false;
		return pGVec->add(argS, *argV->pHVec);
	}

	bool fk_GenVector::Sub(int argS, fk_GenVector^ argV)
	{
		if(!argV) return false;
		return pGVec->sub(argS, *argV->pGVec);
	}

	bool fk_GenVector::Sub(int argS, fk_Vector^ argV)
	{
		if(!argV) return false;
		return pGVec->sub(argS, *argV->pVec);
	}

	bool fk_GenVector::Sub(int argS, fk_HVector^ argV)
	{
		if(!argV) return false;
		return pGVec->sub(argS, *argV->pHVec);
	}

	fk_GenVector^ fk_GenVector::Div(int argS, int argE)
	{
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = pGVec->div(argS, argE);
		return V;
	}
}

