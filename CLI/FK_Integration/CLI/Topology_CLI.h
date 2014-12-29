// Topology_CLI.h

#pragma once

#include <FK/Topology.h>
#include "Attribute_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

	public enum class fk_TopologyType {
		VERTEX,
		HALF,
		EDGE,
		LOOP,
		INDEXFACE,
		UNDEFINED
	};

	public ref class fk_Topology : FK_CLI::fk_Attribute {
	internal:
		::fk_Topology * GetP(void)
		{
			return (::fk_Topology *)(pBase);
		}

	public:
		fk_Topology::fk_Topology(bool argNewFlg) : fk_Attribute(false)
		{
		}

		fk_Topology::~fk_Topology()
		{
			this->!fk_Topology();
		}

		fk_Topology::!fk_Topology()
		{
		}

		int getID(void)
		{
			return GetP()->getID();
		}

		fk_TopologyType getType(void)
		{
			switch(GetP()->getType()) {
			  case ::FK_VERTEX_TYPE:
				return fk_TopologyType::VERTEX;
				
			  case ::FK_HALF_TYPE:
				return fk_TopologyType::HALF;
				
			  case ::FK_EDGE_TYPE:
				return fk_TopologyType::EDGE;
				
			  case ::FK_LOOP_TYPE:
				return fk_TopologyType::LOOP;
				
			  case ::FK_INDEXFACE_TYPE:
				return fk_TopologyType::INDEXFACE;
				
			  default:
				break;
			}
			return fk_TopologyType::UNDEFINED;
		}
	};
}
