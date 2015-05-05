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

	public ref class fk_Topology : fk_Attribute {
	internal:
		::fk_Topology * GetP(void);

	public:
		fk_Topology(bool argNewFlg);
		~fk_Topology();
		!fk_Topology();

		property int ID {
			int get();
		}

		property fk_TopologyType Type {
			fk_TopologyType get();
		}
	};

	public ref class fk_TopologyMaterial : fk_Topology {
	internal:
		::fk_TopologyMaterial * GetP(void);

	public:
		fk_TopologyMaterial(bool argNewFlg);
		~fk_TopologyMaterial();
		!fk_TopologyMaterial();

		property fk_MaterialMode MaterialMode {
			fk_MaterialMode get();
			void set(fk_MaterialMode);
		}

		property int MaterialID {
			int get();
			void set(int);
		}
	};		
}
