// Shape_CLI.h

#pragma once

#include <FK/Projection.h>

namespace FK_CLI
{
	using namespace System;

	public enum class fk_ProjectMode {
		NONE_PROJ_MODE,
		PERSPECTIVE_MODE,
		FRUSTUM_MODE,
		ORTHO_MODE
	};

	public ref class fk_ProjectBase {
	internal:
		bool dFlg;
		::fk_ProjectBase *pProj;

		::fk_ProjectBase * GetP(void);

	public:
		fk_ProjectBase(bool argNewFlg);
		fk_ProjectBase();
		~fk_ProjectBase();
		!fk_ProjectBase();

		property fk_ProjectMode Mode {
			fk_ProjectMode get();
		}
	};

	public ref class fk_Perspective : fk_ProjectBase {
	internal:
		::fk_Perspective * GetP(void);

	public:
		fk_Perspective(bool argNewFlg);
		fk_Perspective();
		fk_Perspective(double argFovy, double argNear, double argFar);
		~fk_Perspective();
		!fk_Perspective();

		property double Fovy {
			void set(double);
			double get();
		}
		
		property double Near {
			void set(double);
			double get();
		}

		property double Far {
			void set(double);
			double get();
		}

		void SetAll(double fovy, double near, double far);
	};

	public ref class fk_Frustum : fk_ProjectBase {
	internal:
		::fk_Frustum * GetP(void);

	public:
		fk_Frustum(bool argNewFlg);
		fk_Frustum();
		fk_Frustum(double argL, double argR, double argB, double argT, double argN, double argF);
		~fk_Frustum();
		!fk_Frustum();

		property double Left {
			void set(double);
			double get();
		}

		property double Right {
			void set(double);
			double get();
		}

		property double Bottom {
			void set(double);
			double get();
		}

		property double Top {
			void set(double);
			double get();
		}

		property double Near {
			void set(double);
			double get();
		}

		property double Far {
			void set(double);
			double get();
		}

		void SetAll(double left, double right, double bottom,
					double top, double near, double far);
	};

	public ref class fk_Ortho : fk_ProjectBase {
	internal:
		::fk_Ortho * GetP(void);

	public:
		fk_Ortho(bool argNewFlg);
		fk_Ortho();
		fk_Ortho(double argL, double argR, double argB, double argT, double argN, double argF);
		~fk_Ortho();
		!fk_Ortho();

		property double Left {
			void set(double);
			double get();
		}

		property double Right {
			void set(double);
			double get();
		}

		property double Bottom {
			void set(double);
			double get();
		}

		property double Top {
			void set(double);
			double get();
		}

		property double Near {
			void set(double);
			double get();
		}

		property double Far {
			void set(double);
			double get();
		}

		void SetAll(double left, double right, double bottom,
					double top, double near, double far);
	};
}
