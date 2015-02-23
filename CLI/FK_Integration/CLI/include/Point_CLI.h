// Point_CLI.h

#pragma once

#include <FK/Point.h>
#include "Vector_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	public ref class fk_Point : fk_Shape {
	internal:
		::fk_Point * GetP(void);

	public:
		fk_Point();
		fk_Point(array<fk_Vector^>^ argArray);
		fk_Point(bool argNewFlg);
		~fk_Point();
		!fk_Point();

		property int Num {
			int get();
		}

		property bool ColorCount {
			bool get();
		}
		
		int			PushVertex(fk_Vector^ pos);
		bool		SetVertex(int ID, fk_Vector^ pos);
		bool		SetVertex(array<fk_Vector^>^ array);
		bool		RemoveVertex(int ID);
		fk_Vector^	GetVertex(int ID);
		void		SetDrawMode(int ID, bool mode);
		bool		GetDrawMode(void);
		bool		GetDrawMode(int ID);
		void		SetColorID(int vertexID, int colorID);
		int			GetColorID(int vertexID);

		void		AllClear(bool materialFlag);
		void		AllClear(void);
	};
}
