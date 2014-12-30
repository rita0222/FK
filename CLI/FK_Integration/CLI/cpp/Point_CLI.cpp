#include "Point_CLI.h"

namespace FK_CLI {

	using namespace std;

	int fk_Point::pushVertex(fk_Vector^ argPos)
	{
		if(!argPos) return -1;
		return GetP()->pushVertex(*argPos->pVec);
	}

	bool fk_Point::setVertex(int argID, fk_Vector^ argPos)
	{
		if(!argPos) return false;
		return GetP()->setVertex(argID, *argPos->pVec);
	}

	bool fk_Point::setVertex(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return false;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *(argArray[i]->pVec);
		}
		return GetP()->setVertex(&vArray);
	}
				
	bool fk_Point::removeVertex(int argID)
	{
		return GetP()->removeVertex(argID);
	}

	fk_Vector^ fk_Point::getVertex(int argID)
	{
		::fk_FVector *fV = GetP()->getVertex(argID);
		fk_Vector^ V = gcnew fk_Vector(double(fV->x), double(fV->y), double(fV->z));
		return V;
	}
				
	int fk_Point::getSize(void)
	{
		return GetP()->getSize();
	}
		
	void fk_Point::setDrawMode(int argID, bool argMode)
	{
		GetP()->setDrawMode(argID, argMode);
	}
		
	bool fk_Point::getDrawMode(void)
	{
		return GetP()->getDrawMode();
	}

	bool fk_Point::getDrawMode(int argID)
	{
		return GetP()->getDrawMode(argID);
	}

	void fk_Point::setColorID(int argVID, int argCID)
	{
		GetP()->setColorID(argVID, argCID);
	}
		
	bool fk_Point::getColorCount(void)
	{
		return GetP()->getColorCount();
	}

	int fk_Point::getColorID(int argVID)
	{
		return GetP()->getColorID(argVID);
	}
		
	void fk_Point::allClear(bool argMatFlag)
	{
		GetP()->allClear(argMatFlag);
	}
		
	void fk_Point::allClear(void)
	{
		GetP()->allClear(true);
	}
}
