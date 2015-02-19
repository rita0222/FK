#include "Block_CLI.h"

namespace FK_CLI {

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
