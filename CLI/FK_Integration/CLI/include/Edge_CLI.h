// Half_CLI.h

#pragma once

#include <FK/Edge.h>
#include "Topology_CLI.h"

namespace FK_CLI
{
	ref class fk_Half;
	
	public enum class fk_EdgeStatus {
		NONE_EDGE,
		UNDEF_EDGE,
		HALFDEF_EDGE,
		BOTHDEF_EDGE
	};

	public ref class fk_Edge : FK_CLI::fk_TopologyMaterial {
	internal:
		::fk_Edge * GetP(void)
		{
			return (::fk_Edge *)(pBase);
		}

	public:
		fk_Edge::fk_Edge(bool argNewFlg) : fk_TopologyMaterial(false)
		{
		}

		fk_Edge::~fk_Edge()
		{
			this->!fk_Edge();
		}

		fk_Edge::!fk_Edge()
		{
		}

		fk_Half^ getLeftHalf(void);
		fk_Half^ getRightHalf(void);
		double getDrawWidth(void);
		void setDrawWidth(double);
	};
}
