// Model_CLI.h

#pragma once

#include <FK/Model.h>
#include "MatAdmin_CLI.h"
#include "Material_CLI.h"

namespace FK_CLI
{
	public enum class fk_BoundaryMode {
		SPHERE,
		AABB,
		OBB,
		CAPSULE,
		NONE
	};

	public ref class fk_Boundary : fk_MatrixAdmin {
	internal:
		::fk_Boundary * GetP(void);

	public:
		fk_Boundary(bool);
		~fk_Boundary();
		!fk_Boundary();
		
		property fk_BoundaryMode BMode {
			fk_BoundaryMode get();
			void set(fk_BoundaryMode argMode);
		}			   

		property double SphereRadius {
			double get();
			void set(double argRad);
		}			

		property fk_Vector^ AABB {
			fk_Vector^ get();
			void set(fk_Vector^ argSize);
		}

		property fk_Vector^ OBB {
			fk_Vector^ get();
			void set(fk_Vector^ argSize);
		}

		property bool BDraw {
			bool get();
			void set(bool argMode);
		}

		property fk_Color^ BLineColor {
			fk_Color^ get();
			void set(fk_Color^ argC);
		}

		property fk_Color^ BIntLineColor {
			fk_Color^ get();
			void set(fk_Color^ argC);
		}

		property double BLineWidth {
			double get();
			void set(double argW);
		}
		
		void SetAABBSize(double x, double y, double z);
		void SetOBBSize(double x, double y, double z);
		void SetCapsule(fk_Vector^ startPos, fk_Vector^ endPos, double radius);
		double GetCapsuleRadius(void);
		double GetCapsuleLength(void);
		fk_Vector^ GetCapsuleStartPos(void);
		fk_Vector^ GetCapsuleEndPos(void);
	};
}
