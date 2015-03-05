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
		::fk_Half * GetP(void);

	public:
		fk_Half(bool argNewFlg);
		~fk_Half();
		!fk_Half();

		property fk_Vertex^ Vertex {
			fk_Vertex^ get();
		}

		property fk_Half^ NextHalf {
			fk_Half^ get();
		}
		
		property fk_Half^ PrevHalf {
			fk_Half^ get();
		}

		property fk_Edge^ ParentEdge {
			fk_Edge^ get();
		}
		
		property fk_Loop^ ParentLoop {
			fk_Loop^ get();
		}

		bool IsLeft(void);
		bool IsRight(void);
	};
}
