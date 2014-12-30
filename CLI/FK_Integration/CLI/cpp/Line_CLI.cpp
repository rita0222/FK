#include "Line_CLI.h"

namespace FK_CLI {

	using namespace std;
	
	void fk_Line::pushLine(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *(argArray[i]->pVec);
		}
		GetP()->pushLine(&vArray[0]);
	}

	void fk_Line::pushLine(fk_Vector^ argS, fk_Vector^ argE)
	{
		if(!argS || !argE) return;
		GetP()->pushLine(*argS->pVec, *argE->pVec);
	}

	bool fk_Line::changeLine(int argLineID, fk_Vector^ argS, fk_Vector^ argE)
	{
		if(!argS || !argE) return false;
		return GetP()->changeLine(argLineID, *argS->pVec, *argE->pVec);
	}

	bool fk_Line::setVertex(int argVID, fk_Vector^ argPos)
	{
		if(!argPos) return false;
		return GetP()->setVertex(argVID, *argPos->pVec);
	}

	bool fk_Line::setVertex(int argLID, int argVID, fk_Vector^ argPos)
	{
		if(!argPos) return false;
		return GetP()->setVertex(argLID, argVID, *argPos->pVec);
	}

	void fk_Line::setVertex(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *argArray[i]->pVec;
		}
		GetP()->setVertex(&vArray);
	}
}
