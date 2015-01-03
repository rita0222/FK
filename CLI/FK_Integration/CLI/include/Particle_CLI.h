// Particle_CLI.h

#pragma once

#include <FK/Particle.h>
#include "Attribute_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	public ref class fk_Particle : fk_Attribute {
	internal:
		::fk_Particle * GetP(void)
		{
			return (::fk_Particle *)(pBase);
		}

	public:
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

		void init(void);
		int getID(void);
		unsigned int getCount(void);
		fk_Vector^ getPosition(void);
		void setPosition(fk_Vector^ pos);
		void setPosition(double x, double y, double z);
		fk_Vector^ getVelocity(void);
		void setVelocity(fk_Vector^ vel);
		void setVelocity(double x, double y, double z);
		fk_Vector^ getAccel(void);
		void setAccel(fk_Vector^ acc);
		void setAccel(double x, double y, double z);
		int getColorID(void);
		void setColorID(int ID);
		bool getDrawMode(void);
		void setDrawMode(bool mode);
		void handle(void);
	};
}
