// Vertex_CLI.h

#pragma once

#include <FK/Vertex.h>
#include "Topology_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI {
	using namespace std;
	using namespace System;

	ref class fk_Half;

	public ref class fk_Vertex : FK_CLI::fk_TopologyMaterial {
	internal:
		::fk_Vertex * GetP(void)
		{
			return (::fk_Vertex *)(pBase);
		}

	public:
		fk_Vertex::fk_Vertex(bool argNewFlg) : fk_TopologyMaterial(false)
		{
		}

		fk_Vertex::~fk_Vertex()
		{
			this->!fk_Vertex();
		}

		fk_Vertex::!fk_Vertex()
		{
		}

		fk_Vector^ getPosition(void);
		fk_Half^ getOneHalf(void);
		fk_Vector^ getNormal(void);
		double getDrawSize(void);
		void setDrawSize(double argSize);
	};
}
