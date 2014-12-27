// Polygon_CLI.h

#pragma once

#include <FK/Polygon.h>
#include "Vector_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

	public ref class fk_Polygon : FK_CLI::fk_Shape {
	internal:
		::fk_Polygon * GetP(void)
		{
			return (::fk_Polygon *)(pBase);
		}

	public:
		fk_Polygon::fk_Polygon() : fk_Shape(false)
		{
			pBase = new ::fk_Polygon();
		}

		fk_Polygon::fk_Polygon(array<fk_Vector^>^ argArray) : fk_Shape(false)
		{
			pBase = new ::fk_Polygon();
			setVertex(argArray);
		}

		fk_Polygon::fk_Polygon(bool argNewFlg) : fk_Shape(false)
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
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void pushVertex(fk_Vector^ argPos)
		{
			if(!argPos) return;
			GetP()->pushVertex(*argPos->pVec);
		}

		void setVertex(int argID, fk_Vector^ argPos)
		{
			if(!argPos) return;
			GetP()->setVertex(argID, *argPos->pVec);
		}

		void setVertex(array<fk_Vector^>^ argArray)
		{
			if(!argArray) return;
			vector<::fk_Vector> vArray(argArray->Length);
			for(int i = 0; i < argArray->Length; i++) {
				vArray[i] = *(argArray[i]->pVec);
			}
			GetP()->setVertex(&vArray);
		}
	};

	public ref class fk_Polyline : FK_CLI::fk_Shape {
	internal:
		::fk_Polyline * GetP(void)
		{
			return (::fk_Polyline *)(pBase);
		}

	public:
		fk_Polyline::fk_Polyline() : fk_Shape(false)
		{
			pBase = new ::fk_Polyline();
		}

		fk_Polyline::fk_Polyline(array<fk_Vector^>^ argArray) : fk_Shape(false)
		{
			pBase = new ::fk_Polyline();
			setVertex(argArray);
		}

		fk_Polyline::fk_Polyline(bool argNewFlg) : fk_Shape(false)
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

	
		void pushVertex(fk_Vector^ argPos)
		{
			if(!argPos) return;
			GetP()->pushVertex(*argPos->pVec);
		}

		void setVertex(int argID, fk_Vector^ argPos)
		{
			if(!argPos) return;
			GetP()->setVertex(argID, *argPos->pVec);
		}

		void setVertex(array<fk_Vector^>^ argArray)
		{
			if(!argArray) return;
			vector<::fk_Vector> vArray(argArray->Length);
			for(int i = 0; i < argArray->Length; i++) {
				vArray[i] = *(argArray[i]->pVec);
			}
			GetP()->setVertex(&vArray);
		}
	};

	public ref class fk_Closedline : FK_CLI::fk_Polygon {
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
