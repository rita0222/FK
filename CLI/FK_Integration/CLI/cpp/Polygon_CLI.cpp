#include "Polygon_CLI.h"

namespace FK_CLI {

	using namespace std;
	
	void fk_Polygon::pushVertex(fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->pushVertex(*argPos->pVec);
	}

	void fk_Polygon::setVertex(int argID, fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->setVertex(argID, *argPos->pVec);
	}

	void fk_Polygon::setVertex(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *(argArray[i]->pVec);
		}
		GetP()->setVertex(&vArray);
	}

	void fk_Polyline::pushVertex(fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->pushVertex(*argPos->pVec);
	}

	void fk_Polyline::setVertex(int argID, fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->setVertex(argID, *argPos->pVec);
	}

	void fk_Polyline::setVertex(array<fk_Vector^>^ argArray)
	{
		if(!argArray) return;
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *(argArray[i]->pVec);
		}
		GetP()->setVertex(&vArray);
	}
}
