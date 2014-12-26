// Line_CLI.h

#pragma once

#include <FK/Line.h>
#include "Vector_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;
	using namespace msclr::interop;

	public ref class fk_Line : fk_Shape {
	internal:
		::fk_Line * GetP(void)
		{
			return reinterpret_cast<::fk_Line *>(this->pBase);
		}

	public:
		fk_Line::fk_Line() : fk_Shape(false)
		{
			::fk_Line *p = new ::fk_Line();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Line::fk_Line(bool argNewFlg) : fk_Shape(false)
		{
			if(argNewFlg == true) {
				::fk_Line *p = new ::fk_Line();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
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

		void pushLine(array<fk_Vector^>^ argArray)
		{
			if(!argArray) return;
			vector<::fk_Vector> vArray(argArray->Length);
			for(int i = 0; i < argArray->Length; i++) {
				vArray[i] = *(argArray[i]->pVec);
			}
			GetP()->pushLine(&vArray[0]);
		}

		void pushLine(fk_Vector^ argS, fk_Vector^ argE)
		{
			if(!argS || !argE) return;
			GetP()->pushLine(*argS->pVec, *argE->pVec);
		}

		bool changeLine(int argLineID, fk_Vector^ argS, fk_Vector^ argE)
		{
			if(!argS || !argE) return false;
			return GetP()->changeLine(argLineID, *argS->pVec, *argE->pVec);
		}

		bool setVertex(int argVID, fk_Vector^ argPos)
		{
			if(!argPos) return false;
			return GetP()->setVertex(argVID, *argPos->pVec);
		}

		bool setVertex(int argLID, int argVID, fk_Vector^ argPos)
		{
			if(!argPos) return false;
			return GetP()->setVertex(argLID, argVID, *argPos->pVec);
		}

		void setVertex(array<fk_Vector^>^ argArray)
		{
			if(!argArray) return;
			vector<::fk_Vector> vArray(argArray->Length);
			for(int i = 0; i < argArray->Length; i++) {
				vArray[i] = *argArray[i]->pVec;
			}
			GetP()->setVertex(&vArray);
		}
	};
}
