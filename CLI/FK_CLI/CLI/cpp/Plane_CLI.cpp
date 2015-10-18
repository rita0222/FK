#include "Plane_CLI.h"

namespace FK_CLI {

	using namespace std;

	fk_Plane::fk_Plane()
	{
		pPlane = new ::fk_Plane();
	}

	fk_Plane::fk_Plane(fk_Plane^ argP)
	{
		pPlane = new ::fk_Plane(*(argP->pPlane));
	}

	fk_Plane::fk_Plane(::fk_Plane *argP)
	{
		pPlane = new ::fk_Plane();
		*pPlane = *argP;
	}

	fk_Plane::~fk_Plane()
	{
		this->!fk_Plane();
	}

	fk_Plane::!fk_Plane()
	{
		delete pPlane;
	}

	String^ fk_Plane::ToString()
	{
		string	tmpBuf;
		::fk_Vector	base, u, v;

		base = pPlane->getBasePos();
		u = pPlane->getUVec();
		v = pPlane->getVVec();

		tmpBuf = "P: base = (";
		tmpBuf += to_string(base.x) + ", ";
		tmpBuf += to_string(base.y) + ", ";
		tmpBuf += to_string(base.z) + "), u = (";
		tmpBuf += to_string(u.x) + ", ";
		tmpBuf += to_string(u.y) + ", ";
		tmpBuf += to_string(u.z) + "), v = (";
		tmpBuf += to_string(v.x) + ", ";
		tmpBuf += to_string(v.y) + ", ";
		tmpBuf += to_string(v.z) + ")";
		return gcnew String(tmpBuf.c_str());
	}

	fk_Vector^ fk_Plane::BasePos::get()
	{
		return gcnew fk_Vector(pPlane->getBasePos());
	}

	fk_Vector^ fk_Plane::UVec::get()
	{
		return gcnew fk_Vector(pPlane->getUVec());
	}

	fk_Vector^ fk_Plane::VVec::get()
	{
		return gcnew fk_Vector(pPlane->getVVec());
	}

	fk_Vector^ fk_Plane::Normal::get()
	{
		return gcnew fk_Vector(pPlane->getNormal());
	}

	double fk_Plane::Dist::get()
	{
		return pPlane->getDist();
	}

	bool fk_Plane::SetPosNormal(fk_Vector^ argPos, fk_Vector^ argNorm)
	{
		if(!argPos || !argNorm) return false;
		return pPlane->setPosNormal(argPos, argNorm);
	}

	bool fk_Plane::Set3Pos(fk_Vector^ argPos1, fk_Vector^ argPos2, fk_Vector^ argPos3)
	{
		if(!argPos1 || !argPos2 || !argPos3) return false;
		return pPlane->set3Pos(argPos1, argPos2, argPos3);
	}

	bool fk_Plane::SetPosUVVec(fk_Vector ^argPos, fk_Vector ^argU, fk_Vector ^argV)
	{
		if(!argPos || !argU || !argV) return false;
		return pPlane->setPosUVVec(argPos, argU, argV);
	}

	double fk_Plane::GetDist(fk_Vector^ argPos)
	{
		if(!argPos) return pPlane->getDist();
		return pPlane->getDist(argPos);
	}

	fk_Vector^ fk_Plane::GetPos(double argU, double argV)
	{
		return gcnew fk_Vector(pPlane->getPos(argU, argV));
	}

	bool fk_Plane::IsParallel(fk_Vector^ argV)
	{
		if(!argV) return false;
		return pPlane->isParallel(argV);
	}

	bool fk_Plane::IsParallel(fk_Plane^ argP)
	{
		if(!argP) return false;
		return pPlane->isParallel(*(argP->pPlane));
	}

	bool fk_Plane::IsVertical(fk_Vector^ argV)
	{
		if(!argV) return false;
		return pPlane->isVertical(argV);
	}

	bool fk_Plane::IsVertical(fk_Plane^ argP)
	{
		if(!argP) return false;
		return pPlane->isVertical(*(argP->pPlane));
	}

	bool fk_Plane::CalcCrossPos(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argPos)
	{
		if(!argA || !argB || !argPos) return false;
		::fk_Vector	retPos;

		bool ret = pPlane->calcCrossPos(argA, argB, &retPos);
		argPos->Set(retPos.x, retPos.y, retPos.z);
		return ret;
	}

	bool fk_Plane::CalcCrossLineParam(fk_Vector^ argA, fk_Vector^ argB, double %argT)
	{
		if(!argA || !argB) return false;
		bool	ret;
		double	t;
		ret = pPlane->calcCrossLineParam(argA, argB, &t);
		argT = t;
		return ret;
	}

	bool fk_Plane::CalcCrossPlaneParam(fk_Vector^ argA, fk_Vector^ argB,
									   double %argU, double %argV)
	{
		if(!argA || !argB) return false;
		bool	ret;
		double	u, v;

		ret = pPlane->calcCrossPlaneParam(argA, argB, &u, &v);
		argU = u;
		argV = v;
		return ret;
	}

	bool fk_Plane::CalcCrossAll(fk_Vector^ argA, fk_Vector^ argB, fk_Vector^ argPos,
								double %argT, double %argU, double %argV)
	{
		if(!argA || !argB || !argPos) return false;
		::fk_Vector	retPos;
		bool		ret;
		double		t, u, v;

		ret = pPlane->calcCrossAll(argA, argB, &retPos, &t, &u, &v);
		argPos->Set(retPos.x, retPos.y, retPos.z);
		argT = t;
		argU = u;
		argV = v;
		return ret;
	}
}


