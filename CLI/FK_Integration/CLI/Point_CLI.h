// Point_CLI.h

#pragma once

#include <FK/Point.h>
#include "Vector_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

	public ref class fk_Point : FK_CLI::fk_Shape {
	internal:
		::fk_Point * GetP(void)
		{
			return (::fk_Point *)(pBase);
		}

	public:
		fk_Point::fk_Point() : fk_Shape(false)
		{
			pBase = new ::fk_Point();
		}

		fk_Point::fk_Point(array<fk_Vector^>^ argArray) : fk_Shape(false)
		{
			pBase = new ::fk_Point();
			setVertex(argArray);
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
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		int pushVertex(fk_Vector^ argPos)
		{
			if(!argPos) return -1;
			return GetP()->pushVertex(*argPos->pVec);
		}

		bool setVertex(int argID, fk_Vector^ argPos)
		{
			if(!argPos) return false;
			return GetP()->setVertex(argID, *argPos->pVec);
		}

		bool setVertex(array<fk_Vector^>^ argArray)
		{
			if(!argArray) return false;
			vector<::fk_Vector> vArray(argArray->Length);
			for(int i = 0; i < argArray->Length; i++) {
				vArray[i] = *(argArray[i]->pVec);
			}
			return GetP()->setVertex(&vArray);
		}
				
		bool removeVertex(int argID)
		{
			return GetP()->removeVertex(argID);
		}

		fk_Vector^ getVertex(int argID)
		{
			::fk_FVector *fV = GetP()->getVertex(argID);
			fk_Vector^ V = gcnew fk_Vector(double(fV->x), double(fV->y), double(fV->z));
			return V;
		}
				
		int getSize(void)
		{
			return GetP()->getSize();
		}
		
		void setDrawMode(int argID, bool argMode)
		{
			GetP()->setDrawMode(argID, argMode);
		}
		
		bool getDrawMode(void)
		{
			return GetP()->getDrawMode();
		}

		bool getDrawMode(int argID)
		{
			return GetP()->getDrawMode(argID);
		}

		void setColorID(int argVID, int argCID)
		{
			GetP()->setColorID(argVID, argCID);
		}
		
		bool getColorCount(void)
		{
			return GetP()->getColorCount();
		}

		int getColorID(int argVID)
		{
			return GetP()->getColorID(argVID);
		}
		
		void allClear(bool argMatFlag)
		{
			GetP()->allClear(argMatFlag);
		}
		
		void allClear(void)
		{
			GetP()->allClear(true);
		}
	};
}
