// Point_CLI.h

#pragma once

#include <FK/Point.h>
#include "Vector_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	public ref class fk_Point : fk_Shape {
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
			if(pBase == NULL) return;
			if(dFlg == true) delete GetP();
			pBase = NULL;
		}

		int pushVertex(fk_Vector^ pos);
		bool setVertex(int ID, fk_Vector^ pos);
		bool setVertex(array<fk_Vector^>^ array);
		bool removeVertex(int ID);
		fk_Vector^ getVertex(int ID);
		int getSize(void);
		void setDrawMode(int ID, bool mode);
		bool getDrawMode(void);
		bool getDrawMode(int ID);
		void setColorID(int vertexID, int colorID);
		bool getColorCount(void);
		int getColorID(int vertexID);
		void allClear(bool materialFlag);
		void allClear(void);
	};
}
