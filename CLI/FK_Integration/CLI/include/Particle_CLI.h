// Particle_CLI.h

#pragma once

#include <FK/Particle.h>
#include "Attribute_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	public ref class fk_Particle : fk_Attribute {
	internal:
		::fk_Particle * GetP(void);

	public:
		fk_Particle(bool argNewFlg);
		fk_Particle();
		~fk_Particle();
		!fk_Particle();

		property int ID {
			int get();
		}

		property unsigned int Count {
			unsigned int get();
		}

		property fk_Vector^ Position {
			fk_Vector^ get();
			void set(fk_Vector^);
		}

		property fk_Vector^ Velocity {
			fk_Vector^ get();
			void set(fk_Vector^);
		}

		property fk_Vector^ Accel {
			fk_Vector^ get();
			void set(fk_Vector^);
		}

		property int ColorID {
			int get();
			void set(int);
		}

		property bool DrawMode {
			bool get();
			void set(bool);
		}
		
		void Init(void);
		void Handle(void);
	};
}
