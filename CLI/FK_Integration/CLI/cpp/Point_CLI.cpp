#include "Point_CLI.h"

namespace FK_CLI {

	using namespace std;

	::fk_Point * fk_Point::GetP(void)
	{
		return (::fk_Point *)(pBase);
	}

	fk_Point::fk_Point() : fk_Shape(false)
	{
		pBase = new ::fk_Point();
	}

	fk_Point::fk_Point(array<fk_Vector^>^ argArray) : fk_Shape(false)
	{
		pBase = new ::fk_Point();
		SetVertex(argArray);
	}

	fk_Point::fk_Point(bool argNewFlg) : fk_Shape(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_Point();
		}
	}

	fk_Point::~fk_Point()
	{
		this->!fk_Point();
	}

	fk_Point::!fk_Point()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	int fk_Point::Num::get(void)
	{
		return GetP()->getSize();
	}
		
	bool fk_Point::ColorCount::get(void)
	{
		return GetP()->getColorCount();
	}

	int fk_Point::PushVertex(fk_Vector^ argPos)
	{
		if(!argPos) return -1;
		return GetP()->pushVertex(::fk_Vector(argPos->x_, argPos->y_, argPos->z_));
	}

	bool fk_Point::SetVertex(int argID, fk_Vector^ argPos)
	{
		if(!argPos) return false;
		return GetP()->setVertex(argID, ::fk_Vector(argPos->x_, argPos->y_, argPos->z_));
	}

	bool fk_Point::SetVertex(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return false;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i].set(argArray[i]->x_, argArray[i]->y_, argArray[i]->z_);
		}
		return GetP()->setVertex(&vArray);
	}
				
	bool fk_Point::RemoveVertex(int argID)
	{
		return GetP()->removeVertex(argID);
	}

	fk_Vector^ fk_Point::GetVertex(int argID)
	{
		::fk_FVector *fV = GetP()->getVertex(argID);
		return gcnew fk_Vector(double(fV->x), double(fV->y), double(fV->z));
	}
				
	void fk_Point::SetDrawMode(int argID, bool argMode)
	{
		GetP()->setDrawMode(argID, argMode);
	}
		
	bool fk_Point::GetDrawMode(void)
	{
		return GetP()->getDrawMode();
	}

	bool fk_Point::GetDrawMode(int argID)
	{
		return GetP()->getDrawMode(argID);
	}

	void fk_Point::SetColorID(int argVID, int argCID)
	{
		GetP()->setColorID(argVID, argCID);
	}

	int fk_Point::GetColorID(int argVID)
	{
		return GetP()->getColorID(argVID);
	}
		
	void fk_Point::AllClear(bool argMatFlag)
	{
		GetP()->allClear(argMatFlag);
	}
		
	void fk_Point::AllClear(void)
	{
		GetP()->allClear(true);
	}
}
