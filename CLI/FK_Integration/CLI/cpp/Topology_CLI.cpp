#include "Topology_CLI.h"

namespace FK_CLI {

	::fk_Topology * fk_Topology::GetP(void)
	{
		return (::fk_Topology *)(pBase);
	}

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

	int fk_Topology::ID::get(void)
	{
		return GetP()->getID();
	}

	fk_TopologyType fk_Topology::Type::get(void)
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

	///////////////////////////////////////////////////////////////////////
	
	::fk_TopologyMaterial * fk_TopologyMaterial::GetP(void)
	{
		return (::fk_TopologyMaterial *)(pBase);
	}

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

	void fk_TopologyMaterial::MaterialMode::set(fk_MaterialMode argMode)
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

	fk_MaterialMode fk_TopologyMaterial::MaterialMode::get(void)
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

	void fk_TopologyMaterial::MaterialID::set(int argID)
	{
		GetP()->setElemMaterialID(argID);
	}
				
	int fk_TopologyMaterial::MaterialID::get(void)
	{
		return GetP()->getElemMaterialID();
	}
}
