#include "Loop_CLI.h"
#include "Half_CLI.h"

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
		return gcnew fk_Vector(GetP()->getNormal());
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
