#include "GenMatrix_CLI.h"

namespace FK_CLI {
	using namespace std;

	fk_GenMatrix::fk_GenMatrix()
	{
		pGMat = new ::fk_GenMatrix();
	}

	fk_GenMatrix::fk_GenMatrix(int argDeg)
	{
		pGMat = new ::fk_GenMatrix(argDeg);
	}

	fk_GenMatrix::~fk_GenMatrix()
	{
		this->!fk_GenMatrix();
	}

	fk_GenMatrix::!fk_GenMatrix()
	{
		delete pGMat;
	}


	double fk_GenMatrix::default::get(int argI1, int argI2)
	{
		return pGMat->get(argI1, argI2);
	}

	void fk_GenMatrix::default::set(int argI1, int argI2, double argD)
	{
		pGMat->set(argI1, argI2, argD);
	}

	void fk_GenMatrix::Degree::set(int argDeg)
	{
		pGMat->setDeg(argDeg);
	}

	int fk_GenMatrix::Degree::get(void)
	{
		return pGMat->getDeg();
	}

	bool fk_GenMatrix::Equals(fk_GenMatrix^ argM)
	{
		if(!argM) return false;
		return (*argM->pGMat == *pGMat);
	}

	bool fk_GenMatrix::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_GenMatrix^ M = static_cast<fk_GenMatrix^>(argObj);
			return (*M->pGMat == *pGMat);
		}
		return false;
	}

	String^	fk_GenMatrix::ToString()
	{
		string tmpBuf;
		int deg = pGMat->getDeg();

		tmpBuf += "GM = \n";
		for(int i = 0; i < deg; ++i) {
			tmpBuf += "\t";
			for(int j = 0; j < deg; j++) {
				tmpBuf += to_string(pGMat->get(i, j));
				if(j != deg - 1) tmpBuf += ", ";
			}
			tmpBuf += "\n";
		}
		return gcnew String(tmpBuf.c_str());
	}
				
	fk_GenVector^ fk_GenMatrix::operator*(fk_GenMatrix^ argM, fk_GenVector^ argV)
	{
		if(!argM || !argV) return nullptr;
		fk_GenVector^ V = gcnew fk_GenVector();
		*V->pGVec = (*argM->pGMat) * (*argV->pGVec);
		return V;
	}

	fk_GenMatrix^ fk_GenMatrix::operator*(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return nullptr;
		fk_GenMatrix^ M = gcnew fk_GenMatrix();
		*M->pGMat = (*argM1->pGMat) * (*argM2->pGMat);
		return M;
	}

	fk_GenMatrix^ fk_GenMatrix::operator-(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return nullptr;
		fk_GenMatrix^ M = gcnew fk_GenMatrix();
		*M->pGMat = (*argM1->pGMat) - (*argM2->pGMat);
		return M;
	}

	fk_GenMatrix^ fk_GenMatrix::operator+(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return nullptr;
		fk_GenMatrix^ M = gcnew fk_GenMatrix();
		*M->pGMat = (*argM1->pGMat) + (*argM2->pGMat);
		return M;
	}

	void fk_GenMatrix::operator +=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return;
		*argM1->pGMat += *argM2->pGMat;
	}

	void fk_GenMatrix::operator -=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return;
		*argM1->pGMat -= *argM2->pGMat;
	}

	void fk_GenMatrix::operator *=(fk_GenMatrix^ argM1, fk_GenMatrix^ argM2)
	{
		if(!argM1 || !argM2) return;
		*argM1->pGMat *= *argM2->pGMat;
	}

	void fk_GenMatrix::operator *=(fk_GenVector^ argV, fk_GenMatrix^ argM)
	{
		if(!argV || !argM) return;
		*argV->pGVec *= *argM->pGMat;
	}

	void fk_GenMatrix::Init(bool argInitFlg)
	{
		pGMat->init(argInitFlg);
	}
	
	void fk_GenMatrix::Init(void)
	{
		pGMat->init();
	}
	
	bool fk_GenMatrix::Inverse(void)
	{
		return pGMat->inverse();
	}

	fk_GenMatrix^ fk_GenMatrix::GetInverse(void)
	{
		fk_GenMatrix^ M = gcnew fk_GenMatrix();
		*M->pGMat = !(*pGMat);
		return M;
	}
	
	void fk_GenMatrix::Negate(void)
	{
		pGMat->negate();
	}
	
	bool fk_GenMatrix::IsRegular(void)
	{
		return pGMat->isRegular();
	}
	
	bool fk_GenMatrix::IsSingular(void)
	{
		return pGMat->isSingular();
	}
}
