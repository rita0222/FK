// Half_CLI.h

#pragma once

#include <FK/Loop.h>
#include "Topology_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	ref class fk_Half;
	
	public ref class fk_Loop : fk_TopologyMaterial {
	internal:
		::fk_Loop * GetP(void)
		{
			return (::fk_Loop *)(pBase);
		}

	public:
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

		fk_Half^ getOneHalf(void);
		fk_Vector^ getNormal(void);
		int getVNum(void);
		void setTesselateMode(bool);
		bool getTesselateMode(void);
		bool isTesselated(void);
	};
}
