// Polygon_CLI.h

#pragma once

#include <FK/Polygon.h>
#include "Solid_CLI.h"

namespace FK_CLI
{
	public ref class fk_Polygon : fk_Solid {
	internal:
		::fk_Polygon * GetP(void)
		{
			return (::fk_Polygon *)(pBase);
		}

	public:
		fk_Polygon::fk_Polygon() : fk_Solid(false)
		{
			pBase = new ::fk_Polygon();
		}

		fk_Polygon::fk_Polygon(array<fk_Vector^>^ argArray) : fk_Solid(false)
		{
			pBase = new ::fk_Polygon();
			setVertex(argArray);
		}

		fk_Polygon::fk_Polygon(bool argNewFlg) : fk_Solid(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_Polygon();
			}
				
		}

		fk_Polygon::~fk_Polygon()
		{
			this->!fk_Polygon();
		}

		fk_Polygon::!fk_Polygon()
		{
			if(pBase == NULL) return;
			if(dFlg == true) delete GetP();
			pBase = NULL;
		}

		void pushVertex(fk_Vector^ pos);
		void setVertex(int ID, fk_Vector^ pos);
		void setVertex(array<fk_Vector^>^ array);
	};

	public ref class fk_Polyline : fk_Solid {
	internal:
		::fk_Polyline * GetP(void)
		{
			return (::fk_Polyline *)(pBase);
		}

	public:
		fk_Polyline::fk_Polyline() : fk_Solid(false)
		{
			pBase = new ::fk_Polyline();
		}

		fk_Polyline::fk_Polyline(array<fk_Vector^>^ argArray) : fk_Solid(false)
		{
			pBase = new ::fk_Polyline();
			setVertex(argArray);
		}

		fk_Polyline::fk_Polyline(bool argNewFlg) : fk_Solid(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_Polyline();
			}
				
		}

		fk_Polyline::~fk_Polyline()
		{
			this->!fk_Polyline();
		}

		fk_Polyline::!fk_Polyline()
		{
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}
	
		void pushVertex(fk_Vector^ pos);
		void setVertex(int argID, fk_Vector^ pos);
		void setVertex(array<fk_Vector^>^ array);
	};

	public ref class fk_Closedline : fk_Polygon {
	internal:
		::fk_Closedline * GetP(void)
		{
			return (::fk_Closedline *)(pBase);
		}

	public:
		fk_Closedline::fk_Closedline() : fk_Polygon(false)
		{
			pBase = new ::fk_Closedline();
		}

		fk_Closedline::fk_Closedline(array<fk_Vector^>^ argArray) : fk_Polygon(false)
		{
			pBase = new ::fk_Closedline();
			setVertex(argArray);
		}

		fk_Closedline::fk_Closedline(bool argNewFlg) : fk_Polygon(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_Closedline();
			}
		}

		fk_Closedline::~fk_Closedline()
		{
			this->!fk_Closedline();
		}

		fk_Closedline::!fk_Closedline()
		{
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}
	};		
}
