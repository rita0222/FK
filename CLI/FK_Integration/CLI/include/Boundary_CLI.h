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
		::fk_Boundary * GetP(void)
		{
			return (::fk_Boundary *)(pBase);
		}

	public:
		fk_Boundary::fk_Boundary(bool argNewFlg) : fk_MatrixAdmin(false)
		{
		}

		fk_Boundary::~fk_Boundary()
		{
			this->!fk_Boundary();
		}

		fk_Boundary::!fk_Boundary()
		{
		}
		
		property fk_BoundaryMode BMode {
			fk_BoundaryMode get()
			{
				switch(GetP()->getBMode()) {
				  case FK_B_SPHERE:
					return FK_CLI::fk_BoundaryMode::SPHERE;

				  case FK_B_AABB:
					return FK_CLI::fk_BoundaryMode::AABB;

				  case FK_B_OBB:
					return FK_CLI::fk_BoundaryMode::OBB;

				  case FK_B_CAPSULE:
					return FK_CLI::fk_BoundaryMode::CAPSULE;

				  default:
					break;
				}
				return FK_CLI::fk_BoundaryMode::NONE;
			}

			void set(fk_BoundaryMode argMode)
			{
				switch(argMode) {
				  case FK_CLI::fk_BoundaryMode::SPHERE:
					GetP()->setBMode(FK_B_SPHERE);
					break;

				  case FK_CLI::fk_BoundaryMode::AABB:
					GetP()->setBMode(FK_B_AABB);
					break;

				  case FK_CLI::fk_BoundaryMode::OBB:
					GetP()->setBMode(FK_B_OBB);
					break;

				  case FK_CLI::fk_BoundaryMode::CAPSULE:
					GetP()->setBMode(FK_B_CAPSULE);
					break;

				  case FK_CLI::fk_BoundaryMode::NONE:
					GetP()->setBMode(FK_B_NONE);
					break;

				  default:
					break;
				}
			}
		}			   

		property double sphereRad {
			double get()
			{
				return GetP()->getSphere();
			}

			void set(double argRad)
			{
				GetP()->setSphere(argRad);
			}
		}			


		property fk_Vector^ AABB {
			fk_Vector^ get()
			{
				return gcnew fk_Vector(GetP()->getAABBSize());
			}

			void set(fk_Vector^ argSize)
			{
				if(!argSize) return;
				GetP()->setAABBSize(*argSize->pVec);
			}
		}

		property fk_Vector^ OBB {
			fk_Vector^ get()
			{
				return gcnew fk_Vector(GetP()->getOBBSize());
			}

			void set(fk_Vector^ argSize)
			{
				if(!argSize) return;
				GetP()->setOBBSize(*argSize->pVec);
			}
		}

		property bool BDraw {
			bool get()
			{
				return GetP()->getBDrawToggle();
			}

			void set(bool argMode)
			{
				GetP()->setBDrawToggle(argMode);
			}
		}

		property fk_Color^ BLineColor {
			fk_Color^ get()
			{
				fk_Color^ C = gcnew fk_Color();
				*C->pCol = *GetP()->getBLineColor();
				return C;
			}

			void set(fk_Color^ argC)
			{
				if(!argC) return;
				GetP()->setBLineColor(*argC->pCol);
			}
		}

		property fk_Color^ BIntLineColor {
			fk_Color^ get()
			{
				fk_Color^ C = gcnew fk_Color();
				*C->pCol = *GetP()->getBIntLineColor();
				return C;
			}

			void set(fk_Color^ argC)
			{
				if(!argC) return;
				GetP()->setBIntLineColor(*argC->pCol);
			}
		}

		property double BLineWidth {
			double get()
			{
				return GetP()->getBLineWidth();
			}

			void set(double argW)
			{
				GetP()->setBLineWidth(argW);
			}
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
