#include "Particle_CLI.h"

namespace FK_CLI {

	using namespace std;

	void fk_Particle::init(void)
	{
		GetP()->init();
	}

	int fk_Particle::getID(void)
	{
		return GetP()->getID();
	}

	unsigned int fk_Particle::getCount(void)
	{
		return GetP()->getCount();
	}

	fk_Vector^ fk_Particle::getPosition(void)
	{
		return gcnew fk_Vector(GetP()->getPosition());
	}

	void fk_Particle::setPosition(fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->setPosition(*argPos->pVec);
	}

	void fk_Particle::setPosition(double x, double y, double z)
	{
		GetP()->setPosition(x, y, z);
	}

	fk_Vector^ fk_Particle::getVelocity(void)
	{
		return gcnew fk_Vector(GetP()->getVelocity());
	}

	void fk_Particle::setVelocity(fk_Vector^ argVel)
	{
		if(!argVel) return;
		GetP()->setVelocity(*argVel->pVec);
	}

	void fk_Particle::setVelocity(double argX, double argY, double argZ)
	{
		GetP()->setVelocity(argX, argY, argZ);
	}

	fk_Vector^ fk_Particle::getAccel(void)
	{
		return gcnew fk_Vector(GetP()->getAccel());
	}

	void fk_Particle::setAccel(fk_Vector^ argAcc)
	{
		if(!argAcc) return;
		GetP()->setAccel(*argAcc->pVec);
	}

	void fk_Particle::setAccel(double argX, double argY, double argZ)
	{
		GetP()->setAccel(argX, argY, argZ);
	}

	int fk_Particle::getColorID(void)
	{
		return GetP()->getColorID();
	}

	void fk_Particle::setColorID(int argID)
	{
		GetP()->setColorID(argID);
	}

	bool fk_Particle::getDrawMode(void)
	{
		return GetP()->getDrawMode();
	}
									  
	void fk_Particle::setDrawMode(bool argMode)
	{
		GetP()->setDrawMode(argMode);
	}

	void fk_Particle::handle(void)
	{
		GetP()->handle();
	}
}
