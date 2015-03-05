// MatAdmin_CLI.h

#pragma once

#include <FK/MatAdmin.h>
#include "Base_CLI.h"
#include "Matrix_CLI.h"

namespace FK_CLI
{
	public ref class fk_MatrixAdmin : fk_BaseObject {
	internal:
		::fk_MatrixAdmin * GetP(void);

	public:
		fk_MatrixAdmin::fk_MatrixAdmin(bool argNewFlg);
		fk_MatrixAdmin::~fk_MatrixAdmin();
		fk_MatrixAdmin::!fk_MatrixAdmin();

		property fk_Vector^ Position {
			fk_Vector^ get();
		}

		property fk_Vector^ Vec {
			fk_Vector^ get();
		}

		property fk_Vector^ Upvec {
			fk_Vector^ get();
		}

		property fk_Angle^ Angle {
			fk_Angle^ get();
		}

		property fk_Matrix^ Matrix {
			fk_Matrix^ get();
		}

		property fk_Matrix^ InvMatrix {
			fk_Matrix^ get();
		}

		property fk_Matrix^ BaseMatrix {
			fk_Matrix^ get();
		}

		property fk_Matrix^ InvBaseMatrix {
			fk_Matrix^ get();
		}

		property bool ScaleMode {
			bool get();
		}

		property double Scale {
			double get();
			void set(double);
		}
		
		bool SetScale(double scale, fk_Axis axis);
		bool SetScale(double x, double y, double z);
		bool PrdScale(double scale);
		bool PrdScale(double scale, fk_Axis axis);
		bool PrdScale(double x, double y, double z);
		double GetScale(fk_Axis axis);

		bool GlFocus(fk_Vector^ V);
		bool GlFocus(double x, double y, double z);
		bool LoFocus(fk_Vector^ V);
		bool LoFocus(double x, double y, double z);
		bool GlVec(fk_Vector^ V);
		bool GlVec(double x, double y, double z);
		bool GlUpvec(fk_Vector^ V);
		bool GlUpvec(double x, double y, double z);
		bool LoUpvec(fk_Vector^ V);
		bool LoUpvec(double x, double y, double z);
		bool GlAngle(fk_Angle^ angle);
		bool GlAngle(double head, double pitch, double bank);
		bool LoAngle(fk_Angle^ angle);
		bool LoAngle(double head, double pitch, double bank);
	};
}
