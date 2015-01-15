// Line_CLI.h

#pragma once

#include <FK/Line.h>
#include "Solid_CLI.h"

namespace FK_CLI
{
	public ref class fk_Line : fk_Solid {
	internal:
		::fk_Line * GetP(void)
		{
			return (::fk_Line *)(pBase);
		}

	public:
		fk_Line::fk_Line() : fk_Solid(false)
		{
			pBase = new ::fk_Line();
		}

		fk_Line::fk_Line(bool argNewFlg) : fk_Solid(false)
		{
			if(argNewFlg == true) pBase = new ::fk_Line();
		}

		fk_Line::~fk_Line()
		{
			this->!fk_Line();
		}

		fk_Line::!fk_Line()
		{
			if(pBase == nullptr) return;
			if(dFlg == true) delete GetP();
			pBase = nullptr;
		}

		void pushLine(array<fk_Vector^>^ array);
		void pushLine(fk_Vector^ startPos, fk_Vector^ endPos);
		bool changeLine(int lineID, fk_Vector^ startPos, fk_Vector^ endPos);
		bool setVertex(int vertexID, fk_Vector^ pos);
		bool setVertex(int lineID, int vertexID, fk_Vector^ pos);
		void setVertex(array<fk_Vector^>^ array);
	};
}
