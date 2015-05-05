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
		::fk_ParticleSet * GetP(void);

	public:
		fk_ParticleSet();
		fk_ParticleSet(bool argNewFlg);
		~fk_ParticleSet();
		!fk_ParticleSet();

		property fk_Shape^ Shape {
			fk_Shape^ get();
		}

		property unsigned int Count {
			unsigned int get();
		}

		property unsigned int ParticleNum {
			unsigned int get();
		}

		property unsigned int MaxSize {
			unsigned int get();
			void set(unsigned int);
		}

		property bool AllMode {
			bool get();
			void set(bool);
		}
		
		property bool IndivMode {
			bool get();
			void set(bool);
		}

		void Handle(void);
		fk_Particle^ NewParticle(void);
		fk_Particle^ NewParticle(fk_Vector^ pos);
		fk_Particle^ NewParticle(double x, double y, double z);
		bool RemoveParticle(fk_Particle ^p);
		bool RemoveParticle(int ID);
		fk_Particle^ GetParticle(int ID);
		fk_Particle^ GetNextParticle(fk_Particle^ p);
		void SetColorPalette(int ID, fk_Color^ col);
		void SetColorPalette(int ID, float R, float G, float B);
		void SetColorPalette(int ID, double R, double G, double B);
		virtual void GenMethod(fk_Particle^ p);
		virtual void AllMethod(void);
		virtual void IndivMethod(fk_Particle^ p);
	};
}
