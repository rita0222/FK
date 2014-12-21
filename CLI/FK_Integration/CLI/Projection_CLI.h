// Shape_CLI.h

#pragma once

#include <FK/Projection.h>
#include "Base_CLI.h"

using namespace std;
using namespace System;

namespace FK_CLI
{
	public enum class fk_ProjectMode
	{
		NONE_PROJ_MODE,
		PERSPECTIVE_MODE,
		FRUSTUM_MODE,
		ORTHO_MODE
	};

	public ref class fk_ProjectBase : fk_BaseObject {
	internal:
		::fk_ProjectBase * GetP(void)
		{
			return reinterpret_cast<::fk_ProjectBase *>(this->pBase);
		}

	public:
		fk_ProjectBase::fk_ProjectBase(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				::fk_ProjectBase *p = new ::fk_ProjectBase();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_ProjectBase::~fk_ProjectBase()
		{
			this->!fk_ProjectBase();
		}

		fk_ProjectBase::!fk_ProjectBase()
		{
			delete this->pBase;
			this->pBase = NULL;
		}

		fk_ProjectMode getMode(void)
		{
			switch(GetP()->getMode()) {
			  case FK_PERSPECTIVE_MODE:
				return fk_ProjectMode::PERSPECTIVE_MODE;

			  case FK_FRUSTUM_MODE:
				return fk_ProjectMode::FRUSTUM_MODE;

			  case FK_ORTHO_MODE:
				return fk_ProjectMode::ORTHO_MODE;

			  default:
				break;
			}
			return fk_ProjectMode::NONE_PROJ_MODE;
		}
	};

	public ref class fk_Perspective : fk_ProjectBase {
	internal:
		::fk_Perspective * GetP(void)
		{
			return reinterpret_cast<::fk_Perspective *>(this->pBase);
		}

	public:
		fk_Perspective::fk_Perspective(bool argNewFlg) : fk_ProjectBase(false)
		{
			if(argNewFlg == true) {
				::fk_Perspective *p = new ::fk_Perspective();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_Perspective::fk_Perspective() : fk_ProjectBase(false)
		{
			::fk_Perspective *p = new ::fk_Perspective();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Perspective::fk_Perspective(double argFovy, double argNear, double argFar)
			: fk_ProjectBase(false)
		{
			::fk_Perspective *p = new ::fk_Perspective(argFovy, argNear, argFar);
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Perspective::~fk_Perspective()
		{
			this->!fk_Perspective();
		}

		fk_Perspective::!fk_Perspective()
		{
			delete this->pBase;
			this->pBase = NULL;
		}

		/*
		void			setFovy(double fovy);
		void			setNear(double near);
		void			setFar(double far);
		void			setAll(double fovy, double near, double far);
		double			getFovy(void) const;
		double			getNear(void) const;
		double			getFar(void) const;
		*/
	};

	public ref class fk_Frustum : fk_ProjectBase {
	internal:
		::fk_Frustum * GetP(void)
		{
			return reinterpret_cast<::fk_Frustum *>(this->pBase);
		}

	public:
		fk_Frustum::fk_Frustum(bool argNewFlg) : fk_ProjectBase(false)
		{
			if(argNewFlg == true) {
				::fk_Frustum *p = new ::fk_Frustum();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_Frustum::fk_Frustum() : fk_ProjectBase(false)
		{
			::fk_Frustum *p = new ::fk_Frustum();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Frustum::fk_Frustum(double argL, double argR,
							   double argB, double argT,
							   double argN, double argF) : fk_ProjectBase(false)
		{
			::fk_Frustum *p = new ::fk_Frustum(argL, argR, argB, argT, argN, argF);
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Frustum::~fk_Frustum()
		{
			this->!fk_Frustum();
		}

		fk_Frustum::!fk_Frustum()
		{
			delete this->pBase;
			this->pBase = NULL;
		}

		/*
		void		setLeft(double left);
		void		setRight(double right);
		void		setBottom(double bottom);
		void		setTop(double top);
		void			setNear(double near);
		void			setFar(double far);
		void			setAll(double left,
							   double right,
							   double bottom,
							   double top,
							   double near,
							   double far);
		double			getLeft(void) const;
		double			getRight(void) const;
		double			getBottom(void) const;
		double			getTop(void) const;
		double			getNear(void) const;
		double			getFar(void) const;
		*/
	};

	public ref class fk_Ortho : fk_ProjectBase {
	internal:
		::fk_Ortho * GetP(void)
		{
			return reinterpret_cast<::fk_Ortho *>(this->pBase);
		}

	public:
		fk_Ortho::fk_Ortho(bool argNewFlg) : fk_ProjectBase(false)
		{
			if(argNewFlg == true) {
				::fk_Ortho *p = new ::fk_Ortho();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_Ortho::fk_Ortho() : fk_ProjectBase(false)
		{
			::fk_Ortho *p = new ::fk_Ortho();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Ortho::fk_Ortho(double argL, double argR,
						   double argB, double argT,
						   double argN, double argF) : fk_ProjectBase(false)
		{
			::fk_Ortho *p = new ::fk_Ortho();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Ortho::~fk_Ortho()
		{
			this->!fk_Ortho();
		}

		fk_Ortho::!fk_Ortho()
		{
			delete this->pBase;
			this->pBase = NULL;
		}

		/*
		void			setLeft(double left);
		void			setRight(double right);
		void			setBottom(double bottom);
		void			setTop(double top);
		void			setNear(double near);
		void			setFar(double far);
		void			setAll(double left, double right,
							   double bottom, double top,
							   double near, double far);
		double			getLeft(void) const;
		double			getRight(void) const;
		double			getBottom(void) const;
		double			getTop(void) const;
		double			getNear(void) const;
		double			getFar(void) const;
		*/
	};
}
