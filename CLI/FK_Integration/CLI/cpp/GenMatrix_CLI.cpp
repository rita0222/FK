#include "GenMatrix_CLI.h"

namespace FK_CLI {
	using namespace std;

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
				
	void fk_GenMatrix::init(bool argInitFlg)
	{
		pGMat->init(argInitFlg);
	}
	
	void fk_GenMatrix::init(void)
	{
		pGMat->init();
	}
	
	void fk_GenMatrix::setDeg(int argDeg)
	{
		pGMat->setDeg(argDeg);
	}

	int fk_GenMatrix::getDeg(void)
	{
		return pGMat->getDeg();
	}
	
	void fk_GenMatrix::set(int argR, int argC, double argV)
	{
		pGMat->set(argR, argC, argV);
	}
	
	double fk_GenMatrix::get(int argR, int argC)
	{
		return pGMat->get(argR, argC);
	}
	
	bool fk_GenMatrix::inverse(void)
	{
		return pGMat->inverse();
	}

	fk_GenMatrix^ fk_GenMatrix::getInverse(void)
	{
		fk_GenMatrix^ M = gcnew fk_GenMatrix();
		*M->pGMat = !(*pGMat);
		return M;
	}
	
	void fk_GenMatrix::negate(void)
	{
		pGMat->negate();
	}
	
	bool fk_GenMatrix::isRegular(void)
	{
		return pGMat->isRegular();
	}
	
	bool fk_GenMatrix::isSingular(void)
	{
		return pGMat->isSingular();
	}
}

