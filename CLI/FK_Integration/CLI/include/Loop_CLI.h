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
		::fk_Loop * GetP(void);

	public:
		fk_Loop(bool argNewFlg);
		~fk_Loop();
		!fk_Loop();

		property fk_Half^ OneHalf {
			fk_Half^ get();
		}

		property fk_Vector^ Normal {
			fk_Vector^ get();
		}

		property int VertexNum {
			int get();
		}

		property bool TesselateMode {
			bool get();
			void set(bool);
		}

		bool IsTesselated(void);
	};
}
