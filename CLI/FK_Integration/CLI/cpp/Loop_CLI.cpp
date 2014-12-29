#include "../Loop_CLI.h"
#include "../Half_CLI.h"

namespace FK_CLI {

	fk_Half^ fk_Loop::getOneHalf(void)
	{
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getOneHalf();
		H->dFlg = false;
		return H;
	}
		   
	fk_Vector^ fk_Loop::getNormal(void)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*V->pVec = *GetP()->getNormal();
		return V;
	}

	int fk_Loop::getVNum(void)
	{
		return GetP()->getVNum();
	}

	void fk_Loop::setTesselateMode(bool argMode)
	{
		GetP()->setTesselateMode(argMode);
	}

	bool fk_Loop::getTesselateMode(void)
	{
		return GetP()->getTesselateMode();
	}

	bool fk_Loop::isTesselated(void)
	{
		return GetP()->isTesselated();
	}
}
