// Vertex_CLI.h

#pragma once

#include <FK/Vertex.h>
#include "Topology_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI {

	ref class fk_Half;

	public ref class fk_Vertex : fk_TopologyMaterial {
	internal:
		::fk_Vertex * GetP(void);

	public:
		fk_Vertex(bool argNewFlg);
		~fk_Vertex();
		!fk_Vertex();

		property fk_Vector^ Position {
			fk_Vector^ get();
		}

		property fk_Vector^ Normal {
			fk_Vector^ get();
		}

		property fk_Half^ OneHalf {
			fk_Half^ get();
		}
		
		property double DrawSize {
			double get();
			void set(double);
		}
	};
}
