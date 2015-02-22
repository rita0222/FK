// Line_CLI.h

#pragma once

#include <FK/Line.h>
#include "Solid_CLI.h"

namespace FK_CLI
{
	public ref class fk_Line : fk_Solid {
	internal:
		::fk_Line * GetP(void);

	public:
		fk_Line();
		fk_Line(bool argNewFlg);
		~fk_Line();
		!fk_Line();

		void PushLine(array<fk_Vector^>^ array);
		void PushLine(fk_Vector^ startPos, fk_Vector^ endPos);
		bool ChangeLine(int lineID, fk_Vector^ startPos, fk_Vector^ endPos);
		bool SetVertex(int vertexID, fk_Vector^ pos);
		bool SetVertex(int lineID, int vertexID, fk_Vector^ pos);
		void SetVertex(array<fk_Vector^>^ array);
	};
}
