#include "Base_CLI.h"
namespace FK_CLI {
	
	fk_BaseObject::fk_BaseObject(bool argNewFlg) : dFlg(true)
	{
		if(argNewFlg == true) pBase = nullptr;
	}
		
	fk_BaseObject::~fk_BaseObject()
	{
		this->!fk_BaseObject();
	}

	fk_BaseObject::!fk_BaseObject()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete pBase;
		pBase = nullptr;
	}
}
