// Line_CLI.h

#pragma once

#include <FK/Line.h>
#include "Vector_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	public ref class fk_Line : FK_CLI::fk_Shape {
	internal:
		::fk_Line * GetP(void)
		{
			return (::fk_Line *)(this->pBase);
		}

	public:
		fk_Line::fk_Line() : fk_Shape(false)
		{
			this->pBase = new ::fk_Line();
		}

		fk_Line::fk_Line(bool argNewFlg) : fk_Shape(false)
		{
			if(argNewFlg == true) this->pBase = new ::fk_Line();
		}

		fk_Line::~fk_Line()
		{
			this->!fk_Line();
		}

		fk_Line::!fk_Line()
		{
			if(dFlg == true) delete this->pBase;
			this->pBase = NULL;
		}

		void pushLine(array<fk_Vector^>^ array);
		void pushLine(fk_Vector^ startPos, fk_Vector^ endPos);
		bool changeLine(int lineID, fk_Vector^ startPos, fk_Vector^ endPos);
		bool setVertex(int vertexID, fk_Vector^ pos);
		bool setVertex(int lineID, int vertexID, fk_Vector^ pos);
		void setVertex(array<fk_Vector^>^ array);
	};
}
