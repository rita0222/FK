#include "Quaternion_CLI.h"

namespace FK_CLI {

	using namespace std;

	String^	fk_Quaternion::ToString()
	{
		string	tmpBuf;
		tmpBuf = "Q: " + to_string(pQuat->s) + ", ";
		tmpBuf += to_string(pQuat->v.x) + ", ";
		tmpBuf += to_string(pQuat->v.y) + ", ";
		tmpBuf += to_string(pQuat->v.z);
		return gcnew String(tmpBuf.c_str());
	}

	void fk_Quaternion::init(void)
	{
		pQuat->init();
	}
	
	void fk_Quaternion::set(double argS, double argX, double argY, double argZ)
	{
		pQuat->set(argS, argX, argY, argZ);
	}
	
	void fk_Quaternion::set(double argS, fk_Vector^ argV)
	{
		if(!argV) return;
		pQuat->set(argS, *argV->pVec);
	}
	
	void fk_Quaternion::setRotate(double argT, double argX, double argY, double argZ)
	{
		pQuat->setRotate(argT, argX, argY, argZ);
	}
	
	void fk_Quaternion::setRotate(double argT, fk_Vector^ argV)
	{
		if(!argV) return;
		pQuat->setRotate(argT, *argV->pVec);
	}

	void fk_Quaternion::makeEuler(double argH, double argP, double argB)
	{
		pQuat->makeEuler(argH, argP, argB);
	}
	
	void fk_Quaternion::makeEuler(fk_Angle^ argA)
	{
		if(!argA) return;
		pQuat->makeEuler(argA->pAngle->h, argA->pAngle->p, argA->pAngle->b);
	}
	
	fk_Angle^ fk_Quaternion::getEuler(void)
	{
		fk_Angle^ A = gcnew fk_Angle();
		*A->pAngle = pQuat->getEuler();
		return A;
	}
	
	double fk_Quaternion::norm(void)
	{
		return pQuat->norm();
	}
	
	double fk_Quaternion::abs(void)
	{
		return pQuat->abs();
	}

	bool fk_Quaternion::normalize(void)
	{
		return pQuat->normalize();
	}
	
	void fk_Quaternion::conj(void)
	{
		pQuat->conj();
	}
	
	bool fk_Quaternion::inverse(void)
	{
		return pQuat->inverse();
	}
	
	fk_Quaternion^ fk_Quaternion::getInverse(void)
	{
		fk_Quaternion^ Q = gcnew fk_Quaternion();
		*Q->pQuat = *pQuat;
		Q->inverse();
		return Q;
	}

	fk_Matrix^ fk_Quaternion::conv(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = pQuat->conv();
		return M;
	}
}

