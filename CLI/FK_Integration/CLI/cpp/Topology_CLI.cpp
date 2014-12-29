#include "Topology_CLI.h"

namespace FK_CLI {

	int fk_Topology::getID(void)
	{
		return GetP()->getID();
	}

	fk_TopologyType fk_Topology::getType(void)
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

	void fk_TopologyMaterial::setElemMaterialMode(fk_MaterialMode argMode)
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

	void fk_TopologyMaterial::setElemMaterialID(int argID)
	{
		GetP()->setElemMaterialID(argID);
	}

	fk_MaterialMode fk_TopologyMaterial::getElemMaterialMode(void)
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
				
	int fk_TopologyMaterial::getElemMaterialID(void)
	{
		return GetP()->getElemMaterialID();
	}
}
