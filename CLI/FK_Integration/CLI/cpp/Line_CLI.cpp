#include "Line_CLI.h"

namespace FK_CLI {

	using namespace std;
	
	::fk_Line * fk_Line::GetP(void)
	{
		return (::fk_Line *)(pBase);
	}

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

	void fk_Line::PushLine(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = argArray[i];
		}
		GetP()->pushLine(&vArray[0]);
	}

	void fk_Line::PushLine(fk_Vector^ argS, fk_Vector^ argE)
	{
		if(!argS || !argE) return;
		GetP()->pushLine(argS, argE);
	}

	bool fk_Line::ChangeLine(int argLineID, fk_Vector^ argS, fk_Vector^ argE)
	{
		if(!argS || !argE) return false;
		return GetP()->changeLine(argLineID, argS, argE);
	}

	bool fk_Line::SetVertex(int argVID, fk_Vector^ argPos)
	{
		if(!argPos) return false;
		return GetP()->setVertex(argVID, argPos);
	}

	bool fk_Line::SetVertex(int argLID, int argVID, fk_Vector^ argPos)
	{
		if(!argPos) return false;
		return GetP()->setVertex(argLID, argVID, argPos);
	}

	void fk_Line::SetVertex(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = argArray[i];
		}
		GetP()->setVertex(&vArray);
	}
}
