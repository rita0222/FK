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

	public ref class fk_Edge : fk_TopologyMaterial {
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

		property fk_Half^ LeftHalf {
			fk_Half^ get();
		}

		property fk_Half^ RightHalf {
			fk_Half^ get();
		}

		property double DrawWidth {
			double get();
			void set(double argW);
		}
	};
}
