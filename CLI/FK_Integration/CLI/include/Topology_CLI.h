// Topology_CLI.h

#pragma once

#include <FK/Topology.h>
#include "Attribute_CLI.h"
#include "Palette_CLI.h"

namespace FK_CLI
{
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

		int getID(void);
		fk_TopologyType getType(void);
	};

	public ref class fk_TopologyMaterial : FK_CLI::fk_Topology {
	internal:
		::fk_TopologyMaterial * GetP(void)
		{
			return (::fk_TopologyMaterial *)(pBase);
		}

	public:
		fk_TopologyMaterial::fk_TopologyMaterial(bool argNewFlg) : fk_Topology(false)
		{
		}

		fk_TopologyMaterial::~fk_TopologyMaterial()
		{
			this->!fk_TopologyMaterial();
		}

		fk_TopologyMaterial::!fk_TopologyMaterial()
		{
		}

		void setElemMaterialMode(fk_MaterialMode mode);
		void setElemMaterialID(int ID);
		fk_MaterialMode getElemMaterialMode(void);
		int getElemMaterialID(void);
	};		
}
