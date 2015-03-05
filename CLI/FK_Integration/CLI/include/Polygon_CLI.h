// Polygon_CLI.h

#pragma once

#include <FK/Polygon.h>
#include "Solid_CLI.h"

namespace FK_CLI
{
	public ref class fk_Polygon : fk_Solid {
	internal:
		::fk_Polygon * GetP(void);

	public:
		fk_Polygon();
		fk_Polygon(array<fk_Vector^>^ argArray);
		fk_Polygon(bool argNewFlg);
		~fk_Polygon();
		!fk_Polygon();

		void PushVertex(fk_Vector^ pos);
		void SetVertex(int ID, fk_Vector^ pos);
		void SetVertex(array<fk_Vector^>^ array);
	};

	public ref class fk_Polyline : fk_Solid {
	internal:
		::fk_Polyline * GetP(void);

	public:
		fk_Polyline();
		fk_Polyline(array<fk_Vector^>^ argArray);
		fk_Polyline(bool argNewFlg);
		~fk_Polyline();
		!fk_Polyline();
	
		void PushVertex(fk_Vector^ pos);
		void SetVertex(int argID, fk_Vector^ pos);
		void SetVertex(array<fk_Vector^>^ array);
	};

	public ref class fk_Closedline : fk_Polygon {
	internal:
		::fk_Closedline * GetP(void);

	public:
		fk_Closedline();
		fk_Closedline(array<fk_Vector^>^ argArray);
		fk_Closedline(bool argNewFlg);
		~fk_Closedline();
		!fk_Closedline();
	};		
}
