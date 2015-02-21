#include "Block_CLI.h"

namespace FK_CLI {

	::fk_Block * fk_Block::GetP(void)
	{
		return (::fk_Block *)(pBase);
	}

	fk_Block::fk_Block() : fk_IndexFaceSet(false)
	{
		pBase = new ::fk_Block();
	}

	fk_Block::fk_Block(bool argNewFlg) : fk_IndexFaceSet(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_Block();
		}
				
	}

	fk_Block::fk_Block(double argX, double argY, double argZ) : fk_IndexFaceSet(false)
	{
		pBase = new ::fk_Block(argX, argY, argZ);
	}

	fk_Block::~fk_Block()
	{
		this->!fk_Block();
	}

	fk_Block::!fk_Block()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_Block::SetSize(double argX, double argY, double argZ)
	{
		GetP()->setSize(argX, argY, argZ);
	}

	void fk_Block::SetSize(double argLength, FK_CLI::fk_Axis argAxis)
	{
		GetP()->setSize(argLength, fk_Vector::GetAxis(argAxis));
	}
						 
	void fk_Block::SetScale(double argScale)
	{
		GetP()->setScale(argScale);
	}

	void fk_Block::SetScale(double argScale, fk_Axis argAxis)
	{
		GetP()->setScale(argScale, fk_Vector::GetAxis(argAxis));
	}
		
	void fk_Block::SetScale(double argX, double argY, double argZ)
	{
		GetP()->setScale(argX, argY, argZ);
	}
}
