#include "GenVector_CLI.h"

namespace FK_CLI {

	using namespace std;
		
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

	void fk_GenVector::resize(int argDeg)
	{
		pGVec->resize(argDeg);
	}
	
	bool fk_GenVector::set(int argID, double argValue)
	{
		return pGVec->set(argID, argValue);
	}
	
	int fk_GenVector::size(void)
	{
		return pGVec->size();
	}
	
	double fk_GenVector::get(int argID)
	{
		return pGVec->get(argID);
	}
	
	double fk_GenVector::norm(void)
	{
		return pGVec->norm();
	}
	
	double fk_GenVector::norm2(void)
	{
		return pGVec->norm2();
	}
	
	bool fk_GenVector::normalize(void)
	{
		return pGVec->normalize();
	}
	
	void fk_GenVector::init(bool argDegFlg)
	{
		pGVec->init(argDegFlg);
	}
	
	void fk_GenVector::init(void)
	{
		pGVec->init();
	}
	
	bool fk_GenVector::isZero(void)
	{
		return pGVec->isZero();
	}
	
	bool fk_GenVector::replace(int argS, fk_GenVector^ argV)
	{
		if(!argV) return false;
		return pGVec->replace(argS, *argV->pGVec);
	}
	
	bool fk_GenVector::replace(int argS, fk_Vector^ argV)
	{
		if(!argV) return false;
		return pGVec->replace(argS, *argV->pVec);
	}

	bool fk_GenVector::replace(int argS, fk_HVector^ argV)
	{
		if(!argV) return false;
		return pGVec->replace(argS, *argV->pHVec);
	}

	bool fk_GenVector::add(int argS, fk_GenVector^ argV)
	{
		if(!argV) return false;
		return pGVec->add(argS, *argV->pGVec);
	}

	bool fk_GenVector::add(int argS, fk_Vector^ argV)
	{
		if(!argV) return false;
		return pGVec->add(argS, *argV->pVec);
	}

	bool fk_GenVector::add(int argS, fk_HVector^ argV)
	{
		if(!argV) return false;
		return pGVec->add(argS, *argV->pHVec);
	}

	bool fk_GenVector::sub(int argS, fk_GenVector^ argV)
	{
		if(!argV) return false;
		return pGVec->sub(argS, *argV->pGVec);
	}

	bool fk_GenVector::sub(int argS, fk_Vector^ argV)
	{
		if(!argV) return false;
		return pGVec->sub(argS, *argV->pVec);
	}

	bool fk_GenVector::sub(int argS, fk_HVector^ argV)
	{
		if(!argV) return false;
		return pGVec->sub(argS, *argV->pHVec);
	}

	fk_GenVector^ fk_GenVector::div(int argS, int argE)
	{
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = pGVec->div(argS, argE);
		return V;
	}
}

