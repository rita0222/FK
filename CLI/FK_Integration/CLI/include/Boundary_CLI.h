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

		void setBMode(fk_BoundaryMode mode);
		fk_BoundaryMode getBMode(void);
		void setSphere(double radius);
		double getSphere(void);
		void setAABBSize(double x, double y, double z);
		void setAABBSize(fk_Vector^ argSize);
		fk_Vector^ getAABBSize(void);
		void setOBBSize(double x, double y, double z);
		void setOBBSize(fk_Vector^ sizeV);
		fk_Vector^ getOBBSize(void);
		void setCapsule(fk_Vector^ startPos, fk_Vector^ endPos, double radius);
		double getCapsuleRadius(void);
		double getCapsuleLength(void);
		fk_Vector^ getCapsuleStartPos(void);
		fk_Vector^ getCapsuleEndPos(void);
		void setBDrawToggle(bool mode);
		bool getBDrawToggle(void);
		void setBLineColor(fk_Color^ color);
		fk_Color^ getBLineColor(void);
		void setBIntLineColor(fk_Color^ color);
		fk_Color^ getBIntLineColor(void);
		void setBLineWidth(double width);
		double getBLineWidth(void);
	};
}
