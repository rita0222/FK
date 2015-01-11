// Half_CLI.h

#pragma once

#include <FK/Half.h>
#include "Topology_CLI.h"
//#include "Edge_CLI.h"
//#include "Loop_CLI.h"

namespace FK_CLI
{
	ref class fk_Vertex;
	ref class fk_Edge;
	ref class fk_Loop;

	public ref class fk_Half : fk_Topology {
	internal:
		::fk_Half * GetP(void)
		{
			return (::fk_Half *)(pBase);
		}

	public:
		fk_Half::fk_Half(bool argNewFlg) : fk_Topology(false)
		{
		}

		fk_Half::~fk_Half()
		{
			this->!fk_Half();
		}

		fk_Half::!fk_Half()
		{
		}

		fk_Vertex^ getVertex(void);
		fk_Half^ getNextHalf(void);
		fk_Half^ getPrevHalf(void);
		fk_Edge^ getParentEdge(void);
		fk_Loop^ getParentLoop(void);
		bool isLeft(void);
		bool isRight(void);
	};
}
