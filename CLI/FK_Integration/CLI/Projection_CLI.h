// Shape_CLI.h

#pragma once

#include <FK/Projection.h>
#include "Base_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

	public enum class fk_ProjectMode
	{
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

		void setFovy(double argFovy)
		{
			GetP()->setFovy(argFovy);
		}			

		void setNear(double argNear)
		{
			GetP()->setNear(argNear);
		}

		void setFar(double argFar)
		{
			GetP()->setFar(argFar);
		}

		void setAll(double argFovy, double argNear, double argFar)
		{
			GetP()->setAll(argFovy, argNear, argFar);
		}

		double getFovy(void)
		{
			return GetP()->getFovy();
		}

		double getNear(void)
		{
			return GetP()->getNear();
		}

		double getFar(void)
		{
			return GetP()->getFar();
		}
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

		void setLeft(double argLeft)
		{
			GetP()->setLeft(argLeft);
		}

		void setRight(double argRight)
		{
			GetP()->setRight(argRight);
		}

		void setBottom(double argBottom)
		{
			GetP()->setBottom(argBottom);
		}

		void setTop(double argTop)
		{
			GetP()->setTop(argTop);
		}

		void setNear(double argNear)
		{
			GetP()->setNear(argNear);
		}
		
		void setFar(double argFar)
		{
			GetP()->setFar(argFar);
		}
		
		void setAll(double argLeft, double argRight,
					double argBottom, double argTop,
					double argNear, double argFar)
		{
			GetP()->setAll(argLeft, argRight, argBottom, argTop, argNear, argFar);
		}

		double getLeft(void)
		{
			return GetP()->getLeft();
		}

		double getRight(void)
		{
			return GetP()->getRight();
		}

		double getBottom(void)
		{
			return GetP()->getBottom();
		}

		double getTop(void)
		{
			return GetP()->getTop();
		}

		double getNear(void)
		{
			return GetP()->getNear();
		}

		double getFar(void)
		{
			return GetP()->getFar();
		}
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

		void setLeft(double argLeft)
		{
			GetP()->setLeft(argLeft);
		}

		void setRight(double argRight)
		{
			GetP()->setRight(argRight);
		}

		void setBottom(double argBottom)
		{
			GetP()->setBottom(argBottom);
		}

		void setTop(double argTop)
		{
			GetP()->setTop(argTop);
		}

		void setNear(double argNear)
		{
			GetP()->setNear(argNear);
		}
		
		void setFar(double argFar)
		{
			GetP()->setFar(argFar);
		}
		
		void setAll(double argLeft, double argRight,
					double argBottom, double argTop,
					double argNear, double argFar)
		{
			GetP()->setAll(argLeft, argRight, argBottom, argTop, argNear, argFar);
		}

		double getLeft(void)
		{
			return GetP()->getLeft();
		}

		double getRight(void)
		{
			return GetP()->getRight();
		}

		double getBottom(void)
		{
			return GetP()->getBottom();
		}

		double getTop(void)
		{
			return GetP()->getTop();
		}

		double getNear(void)
		{
			return GetP()->getNear();
		}

		double getFar(void)
		{
			return GetP()->getFar();
		}
	};
}
