#include "SolidBase_CLI.h"

namespace FK_CLI {

	using namespace std;

	void fk_SolidBase::makeIFSet(int argFNum, int argPNum, array<int>^ argIFSet,
								 int argVNum, array<fk_Vector^>^ argArray, int argOrder)
	{
		if(!argIFSet || !argArray) return;
		pin_ptr<int> pIFSet = &argIFSet[0];
		vector<::fk_Vector> vArray(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			vArray[i] = *argArray[i]->pVec;
		}
		GetP()->makeIFSet(argFNum, argPNum, pIFSet, argVNum, &vArray[0], argOrder);
	}

	void fk_SolidBase::makeIFSet(int argFNum, int argPNum, array<int>^ argIFSet,
								 int argVNum, array<fk_Vector^>^ argPos)
	{
		if(!argIFSet || !argPos) return;
		pin_ptr<int> pIFSet = &argIFSet[0];
		vector<::fk_Vector> vArray(argPos->Length);
		for(int i = 0; i < argPos->Length; ++i) {
			vArray[i] = *argPos[i]->pVec;
		}
		GetP()->makeIFSet(argFNum, argPNum, pIFSet, argVNum, &vArray[0]);
	}

	void fk_SolidBase::makeIFSet(array< array<int>^ >^ argIF, array<fk_Vector^>^ argPos, int argOrder)
	{
		int i, j;

		if(!argIF || !argPos) return;

		vector< vector<int> >	IFSet;
		vector<int> fSet;

		for(i = 0; i < argIF->Length; ++i) {
			array<int>^ fArray = argIF[i];
			fSet.clear();
			for(j = 0; j < fArray->Length; ++j) {
				fSet.push_back(fArray[j]);
			}
			IFSet.push_back(fSet);
		}

		vector<::fk_Vector> vArray(argPos->Length);
		for(i = 0; i < argPos->Length; ++i) {
			vArray[i] = *argPos[i]->pVec;
		}

		GetP()->makeIFSet(&IFSet, &vArray, argOrder);
	}

	void fk_SolidBase::makeIFSet(array< array<int>^ >^ argIF, array<fk_Vector^>^ argPos)
	{
		int i, j;

		if(!argIF || !argPos) return;

		vector< vector<int> >	IFSet;
		vector<int> fSet;

		for(i = 0; i < argIF->Length; ++i) {
			array<int>^ fArray = argIF[i];
			fSet.clear();
			for(j = 0; j < fArray->Length; ++j) {
				fSet.push_back(fArray[j]);
			}
			IFSet.push_back(fSet);
		}

		vector<::fk_Vector> vArray(argPos->Length);
		for(i = 0; i < argPos->Length; ++i) {
			vArray[i] = *argPos[i]->pVec;
		}

		GetP()->makeIFSet(&IFSet, &vArray);
	}
}
