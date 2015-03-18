﻿#include "Polygon_CLI.h"

namespace FK_CLI {

	using namespace std;
	
	::fk_Polygon * fk_Polygon::GetP(void)
	{
		return (::fk_Polygon *)(pBase);
	}

	fk_Polygon::fk_Polygon() : fk_Solid(false)
	{
		pBase = new ::fk_Polygon();
	}

	fk_Polygon::fk_Polygon(array<fk_Vector^>^ argArray) : fk_Solid(false)
	{
		pBase = new ::fk_Polygon();
		SetVertex(argArray);
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
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_Polygon::PushVertex(fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->pushVertex(::fk_Vector(argPos->x_, argPos->y_, argPos->z_));
	}

	void fk_Polygon::SetVertex(int argID, fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->setVertex(argID, ::fk_Vector(argPos->x_, argPos->y_, argPos->z_));
	}

	void fk_Polygon::SetVertex(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i].set(argArray[i]->x_, argArray[i]->y_, argArray[i]->z_);
		}
		GetP()->setVertex(&vArray);
	}

	::fk_Polyline * fk_Polyline::GetP(void)
	{
		return (::fk_Polyline *)(pBase);
	}

	fk_Polyline::fk_Polyline() : fk_Solid(false)
	{
		pBase = new ::fk_Polyline();
	}

	fk_Polyline::fk_Polyline(array<fk_Vector^>^ argArray) : fk_Solid(false)
	{
		pBase = new ::fk_Polyline();
		SetVertex(argArray);
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
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_Polyline::PushVertex(fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->pushVertex(::fk_Vector(argPos->x_, argPos->y_, argPos->z_));
	}

	void fk_Polyline::SetVertex(int argID, fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->setVertex(argID, ::fk_Vector(argPos->x_, argPos->y_, argPos->z_));
	}

	void fk_Polyline::SetVertex(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i].set(argArray[i]->x_, argArray[i]->y_, argArray[i]->z_);
		}
		GetP()->setVertex(&vArray);
	}

	::fk_Closedline * fk_Closedline::GetP(void)
	{
		return (::fk_Closedline *)(pBase);
	}

	fk_Closedline::fk_Closedline() : fk_Polygon(false)
	{
		pBase = new ::fk_Closedline();
	}

	fk_Closedline::fk_Closedline(array<fk_Vector^>^ argArray) : fk_Polygon(false)
	{
		pBase = new ::fk_Closedline();
		SetVertex(argArray);
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
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}
}

