#include "Loop_CLI.h"
#include "Half_CLI.h"

namespace FK_CLI {

	::fk_Loop * fk_Loop::GetP(void)
	{
		return (::fk_Loop *)(pBase);
	}

	fk_Loop::fk_Loop(bool argNewFlg) : fk_TopologyMaterial(false)
	{
	}

	fk_Loop::~fk_Loop()
	{
		this->!fk_Loop();
	}

	fk_Loop::!fk_Loop()
	{
	}

	fk_Half^ fk_Loop::OneHalf::get(void)
	{
		fk_Half^ H = gcnew fk_Half(false);
		H->pBase = GetP()->getOneHalf();
		H->dFlg = false;
		return H;
	}
		   
	fk_Vector^ fk_Loop::Normal::get(void)
	{
		return gcnew fk_Vector(GetP()->getNormal());
	}

	int fk_Loop::VertexNum::get(void)
	{
		return GetP()->getVNum();
	}

	void fk_Loop::TesselateMode::set(bool argMode)
	{
		GetP()->setTesselateMode(argMode);
	}

	bool fk_Loop::TesselateMode::get(void)
	{
		return GetP()->getTesselateMode();
	}

	bool fk_Loop::IsTesselated(void)
	{
		return GetP()->isTesselated();
	}
}
