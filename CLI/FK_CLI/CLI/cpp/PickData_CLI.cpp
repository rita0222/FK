#include "PickData_CLI.h"

namespace FK_CLI {
	using namespace std;

	fk_PickData::fk_PickData(
		fk_Model^ argModel, fk_PickedTopologyType^ argType,
			int argID, double argFar, double argNear)
		: _model(argModel), _type(argType),
			_id(argID), _farDepth(argFar), _nearDepth(argNear)
	{
	}
	
	// デストラクタ
	fk_PickData::~fk_PickData()
	{
		this->!fk_PickData();
	}

	// ファイナライザ
	fk_PickData::!fk_PickData()
	{
	}

	fk_Model^ fk_PickData::Model::get(void) {
		return _model;
	}

	fk_PickedTopologyType^ fk_PickData::Type::get(void) {
		return _type;
	}

	int fk_PickData::ID::get(void) {
		return _id;
	}

	double fk_PickData::FarDepth::get(void) {
		return _farDepth;
	}

	double fk_PickData::NearDepth::get(void) {
		return _nearDepth;
	}
}
