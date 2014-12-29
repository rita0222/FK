// Topology_CLI.h

#pragma once

#include <FK/Topology.h>
#include "Attribute_CLI.h"
#include "Palette_CLI.h"

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

		void setElemMaterialMode(fk_MaterialMode argMode)
		{
			switch(argMode) {
			  case fk_MaterialMode::PARENT:
				GetP()->setElemMaterialMode(FK_PARENT_MODE);
				break;

			  case fk_MaterialMode::CHILD:
				GetP()->setElemMaterialMode(FK_CHILD_MODE);
				break;

			  case fk_MaterialMode::NONE:
				GetP()->setElemMaterialMode(FK_NONE_MODE);
				break;
			}
		}

		void setElemMaterialID(int argID)
		{
			GetP()->setElemMaterialID(argID);
		}

		fk_MaterialMode getElemMaterialMode(void)
		{
			switch(GetP()->getElemMaterialMode()) {
			  case FK_PARENT_MODE:
				return fk_MaterialMode::PARENT;

			  case FK_CHILD_MODE:
				return fk_MaterialMode::CHILD;

			  default:
				break;
			}
			return fk_MaterialMode::PARENT;
		}
				
		int getElemMaterialID(void)
		{
			return GetP()->getElemMaterialID();
		}
	};		
}
