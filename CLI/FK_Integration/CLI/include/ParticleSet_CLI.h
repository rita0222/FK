// Particle_CLI.h

#pragma once

#include <FK/Particle.h>
#include "Particle_CLI.h"
#include "Material_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	public ref class fk_ParticleSet : fk_BaseObject {
	internal:
		::fk_ParticleSet * GetP(void)
		{
			return (::fk_ParticleSet *)(pBase);
		}


	public:
		fk_ParticleSet::fk_ParticleSet() : fk_BaseObject(false)
		{
			pBase = new ::fk_ParticleSet();
		}

		fk_ParticleSet::fk_ParticleSet(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_ParticleSet();
			}
		}

		fk_ParticleSet::~fk_ParticleSet()
		{
			this->!fk_ParticleSet();
		}

		fk_ParticleSet::!fk_ParticleSet()
		{
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void handle(void);
		fk_Shape^ getShape(void);
		fk_Particle^ newParticle(void);
		fk_Particle^ newParticle(fk_Vector^ pos);
		fk_Particle^ newParticle(double x, double y, double z);
		bool removeParticle(fk_Particle ^p);
		bool removeParticle(int ID);
		unsigned int getCount(void);
		fk_Particle^ getParticle(int ID);
		fk_Particle^ getNextParticle(fk_Particle^ p);
		unsigned int getParticleNum(void);
		void setMaxSize(unsigned int max);
		unsigned int getMaxSize(void);
		void setColorPalette(int ID, fk_Color^ col);
		void setColorPalette(int ID, float R, float G, float B);
		void setColorPalette(int ID, double R, double G, double B);
		virtual void genMethod(fk_Particle^ p);
		virtual void allMethod(void);
		virtual void indivMethod(fk_Particle^ p);
		void setAllMode(bool mode);
		bool getAllMode(void);
		void setIndivMode(bool mode);
		bool getIndivMode(void);
	};
}
