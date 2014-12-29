#include "Block_CLI.h"

namespace FK_CLI {

	void fk_Block::setSize(double argX, double argY, double argZ)
	{
		GetP()->setSize(argX, argY, argZ);
	}

	void fk_Block::setSize(double argLength, FK_CLI::fk_Axis argAxis)
	{
		GetP()->setSize(argLength, GetAxis(argAxis));
	}
						 
	void fk_Block::setScale(double argScale)
	{
		GetP()->setScale(argScale);
	}

	void fk_Block::setScale(double argScale, fk_Axis argAxis)
	{
		GetP()->setScale(argScale, GetAxis(argAxis));
	}
		
	void fk_Block::setScale(double argX, double argY, double argZ)
	{
		GetP()->setScale(argX, argY, argZ);
	}
}
