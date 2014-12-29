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

		::fk_ProjectBase * GetP(void)
		{
			return pProj;
		}

	public:
		fk_ProjectBase::fk_ProjectBase(bool argNewFlg) : dFlg(argNewFlg)
		{
			if(argNewFlg == true) pProj = new ::fk_ProjectBase();
		}

		fk_ProjectBase::~fk_ProjectBase()
		{
			this->!fk_ProjectBase();
		}

		fk_ProjectBase::!fk_ProjectBase()
		{
			if(dFlg == true) delete pProj;
			pProj = NULL;
		}

		fk_ProjectMode getMode(void);
	};

	public ref class fk_Perspective : fk_ProjectBase {
	internal:
		::fk_Perspective * GetP(void)
		{
			return (::fk_Perspective *)(pProj);
		}

	public:
		fk_Perspective::fk_Perspective(bool argNewFlg) : fk_ProjectBase(false)
		{
			if(argNewFlg == true) pProj = new ::fk_Perspective();
		}

		fk_Perspective::fk_Perspective() : fk_ProjectBase(false)
		{
			pProj = new ::fk_Perspective();
		}

		fk_Perspective::fk_Perspective(double argFovy, double argNear, double argFar)
			: fk_ProjectBase(false)
		{
			pProj = new ::fk_Perspective(argFovy, argNear, argFar);
		}

		fk_Perspective::~fk_Perspective()
		{
			this->!fk_Perspective();
		}

		fk_Perspective::!fk_Perspective()
		{
			if(dFlg == true) delete pProj;
			pProj = NULL;
		}

		void setFovy(double fovy);
		void setNear(double near);
		void setFar(double far);
		void setAll(double fovy, double near, double far);
		double getFovy(void);
		double getNear(void);
		double getFar(void);
	};

	public ref class fk_Frustum : fk_ProjectBase {
	internal:
		::fk_Frustum * GetP(void)
		{
			return (::fk_Frustum *)(pProj);
		}

	public:
		fk_Frustum::fk_Frustum(bool argNewFlg) : fk_ProjectBase(false)
		{
			if(argNewFlg == true) pProj = new ::fk_Frustum();
		}

		fk_Frustum::fk_Frustum() : fk_ProjectBase(false)
		{
			pProj = new ::fk_Frustum();
		}

		fk_Frustum::fk_Frustum(double argL, double argR,
							   double argB, double argT,
							   double argN, double argF) : fk_ProjectBase(false)
		{
			pProj = new ::fk_Frustum(argL, argR, argB, argT, argN, argF);
		}

		fk_Frustum::~fk_Frustum()
		{
			this->!fk_Frustum();
		}

		fk_Frustum::!fk_Frustum()
		{
			if(dFlg == true) delete pProj;
			pProj = NULL;
		}

		void setLeft(double left);
		void setRight(double right);
		void setBottom(double bottom);
		void setTop(double top);
		void setNear(double near);
		void setFar(double far);
		void setAll(double left, double right, double bottom,
					double top, double near, double far);
		double getLeft(void);
		double getRight(void);
		double getBottom(void);
		double getTop(void);
		double getNear(void);
		double getFar(void);
	};

	public ref class fk_Ortho : fk_ProjectBase {
	internal:
		::fk_Ortho * GetP(void)
		{
			return (::fk_Ortho *)(pProj);
		}

	public:
		fk_Ortho::fk_Ortho(bool argNewFlg) : fk_ProjectBase(false)
		{
			if(argNewFlg == true) pProj = new ::fk_Ortho();
		}

		fk_Ortho::fk_Ortho() : fk_ProjectBase(false)
		{
			pProj = new ::fk_Ortho();
		}

		fk_Ortho::fk_Ortho(double argL, double argR,
						   double argB, double argT,
						   double argN, double argF) : fk_ProjectBase(false)
		{
			pProj = new ::fk_Ortho(argL, argR, argB, argT, argN, argF);
		}

		fk_Ortho::~fk_Ortho()
		{
			this->!fk_Ortho();
		}

		fk_Ortho::!fk_Ortho()
		{
			if(dFlg == true) delete pProj;
			pProj = NULL;
		}

		void setLeft(double left);
		void setRight(double right);
		void setBottom(double bottom);
		void setTop(double top);
		void setNear(double near);
		void setFar(double far);
		void setAll(double left, double right, double bottom,
					double top, double near, double far);
		double getLeft(void);
		double getRight(void);
		double getBottom(void);
		double getTop(void);
		double getNear(void);
		double getFar(void);
	};
}
