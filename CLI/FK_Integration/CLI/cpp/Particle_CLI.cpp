#include "Particle_CLI.h"

namespace FK_CLI {

	using namespace std;

	::fk_Particle * fk_Particle::GetP(void)
	{
		return (::fk_Particle *)(pBase);
	}

	fk_Particle::fk_Particle(bool argNewFlg) : fk_Attribute(false)
	{
	}

	fk_Particle::fk_Particle() : fk_Attribute(false)
	{
	}

	fk_Particle::~fk_Particle()
	{
		this->!fk_Particle();
	}

	fk_Particle::!fk_Particle()
	{
	}

	int fk_Particle::ID::get(void)
	{
		return GetP()->getID();
	}

	unsigned int fk_Particle::Count::get(void)
	{
		return GetP()->getCount();
	}

	fk_Vector^ fk_Particle::Position::get(void)
	{
		return gcnew fk_Vector(GetP()->getPosition());
	}

	void fk_Particle::Position::set(fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->setPosition(::fk_Vector(argPos->x_, argPos->y_, argPos->z_));
	}

	fk_Vector^ fk_Particle::Velocity::get(void)
	{
		return gcnew fk_Vector(GetP()->getVelocity());
	}

	void fk_Particle::Velocity::set(fk_Vector^ argVel)
	{
		if(!argVel) return;
		GetP()->setVelocity(::fk_Vector(argVel->x_, argVel->y_, argVel->z_));
	}

	fk_Vector^ fk_Particle::Accel::get(void)
	{
		return gcnew fk_Vector(GetP()->getAccel());
	}

	void fk_Particle::Accel::set(fk_Vector^ argAcc)
	{
		if(!argAcc) return;
		GetP()->setAccel(::fk_Vector(argAcc->x_, argAcc->y_, argAcc->z_));
	}

	int fk_Particle::ColorID::get(void)
	{
		return GetP()->getColorID();
	}

	void fk_Particle::ColorID::set(int argID)
	{
		GetP()->setColorID(argID);
	}

	bool fk_Particle::DrawMode::get(void)
	{
		return GetP()->getDrawMode();
	}
									  
	void fk_Particle::DrawMode::set(bool argMode)
	{
		GetP()->setDrawMode(argMode);
	}

	void fk_Particle::Init(void)
	{
		GetP()->init();
	}

	void fk_Particle::Handle(void)
	{
		GetP()->handle();
	}
}
