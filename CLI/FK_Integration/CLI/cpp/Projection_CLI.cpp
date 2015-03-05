#include "Projection_CLI.h"

namespace FK_CLI {

	::fk_ProjectBase * fk_ProjectBase::GetP(void)
	{
		return pProj;
	}

	fk_ProjectBase::fk_ProjectBase(bool argNewFlg) : dFlg(argNewFlg)
	{
		if(argNewFlg == true) pProj = new ::fk_ProjectBase();
	}

	fk_ProjectBase::fk_ProjectBase() : dFlg(true)
	{
		pProj = new ::fk_ProjectBase();
	}

	fk_ProjectBase::~fk_ProjectBase()
	{
		this->!fk_ProjectBase();
	}

	fk_ProjectBase::!fk_ProjectBase()
	{
		if(pProj == nullptr) return;
		if(dFlg == true) delete GetP();
		pProj = nullptr;
	}

	fk_ProjectMode fk_ProjectBase::Mode::get(void)
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

	////////////////////////////////////////////////////////////////////////	

	::fk_Perspective * fk_Perspective::GetP(void)
	{
		return (::fk_Perspective *)(pProj);
	}

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
		pProj = nullptr;
	}

	void fk_Perspective::Fovy::set(double argFovy)
	{
		GetP()->setFovy(argFovy);
	}			

	double fk_Perspective::Fovy::get(void)
	{
		return GetP()->getFovy();
	}

	void fk_Perspective::Near::set(double argNear)
	{
		GetP()->setNear(argNear);
	}

	double fk_Perspective::Near::get(void)
	{
		return GetP()->getNear();
	}

	void fk_Perspective::Far::set(double argFar)
	{
		GetP()->setFar(argFar);
	}

	double fk_Perspective::Far::get(void)
	{
		return GetP()->getFar();
	}

	void fk_Perspective::SetAll(double argFovy, double argNear, double argFar)
	{
		GetP()->setAll(argFovy, argNear, argFar);
	}

	////////////////////////////////////////////////////////////////////////

	::fk_Frustum * fk_Frustum::GetP(void)
	{
		return (::fk_Frustum *)(pProj);
	}

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
		pProj = nullptr;
	}

	void fk_Frustum::Left::set(double argLeft)
	{
		GetP()->setLeft(argLeft);
	}

	double fk_Frustum::Left::get(void)
	{
		return GetP()->getLeft();
	}

	void fk_Frustum::Right::set(double argRight)
	{
		GetP()->setRight(argRight);
	}

	double fk_Frustum::Right::get(void)
	{
		return GetP()->getRight();
	}

	void fk_Frustum::Bottom::set(double argBottom)
	{
		GetP()->setBottom(argBottom);
	}

	double fk_Frustum::Bottom::get(void)
	{
		return GetP()->getBottom();
	}

	void fk_Frustum::Top::set(double argTop)
	{
		GetP()->setTop(argTop);
	}

	double fk_Frustum::Top::get(void)
	{
		return GetP()->getTop();
	}

	void fk_Frustum::Near::set(double argNear)
	{
		GetP()->setNear(argNear);
	}
		
	double fk_Frustum::Near::get(void)
	{
		return GetP()->getNear();
	}

	void fk_Frustum::Far::set(double argFar)
	{
		GetP()->setFar(argFar);
	}
		
	double fk_Frustum::Far::get(void)
	{
		return GetP()->getFar();
	}

	void fk_Frustum::SetAll(double argLeft, double argRight,
							double argBottom, double argTop,
							double argNear, double argFar)
	{
		GetP()->setAll(argLeft, argRight, argBottom, argTop, argNear, argFar);
	}

	////////////////////////////////////////////////////////////////////////	

	::fk_Ortho * fk_Ortho::GetP(void)
	{
		return (::fk_Ortho *)(pProj);
	}

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
		pProj = nullptr;
	}

	void fk_Ortho::Left::set(double argLeft)
	{
		GetP()->setLeft(argLeft);
	}

	double fk_Ortho::Left::get(void)
	{
		return GetP()->getLeft();
	}

	void fk_Ortho::Right::set(double argRight)
	{
		GetP()->setRight(argRight);
	}

	double fk_Ortho::Right::get(void)
	{
		return GetP()->getRight();
	}

	void fk_Ortho::Bottom::set(double argBottom)
	{
		GetP()->setBottom(argBottom);
	}

	double fk_Ortho::Bottom::get(void)
	{
		return GetP()->getBottom();
	}

	void fk_Ortho::Top::set(double argTop)
	{
		GetP()->setTop(argTop);
	}

	double fk_Ortho::Top::get(void)
	{
		return GetP()->getTop();
	}

	void fk_Ortho::Near::set(double argNear)
	{
		GetP()->setNear(argNear);
	}
		
	double fk_Ortho::Near::get(void)
	{
		return GetP()->getNear();
	}

	void fk_Ortho::Far::set(double argFar)
	{
		GetP()->setFar(argFar);
	}
		
	double fk_Ortho::Far::get(void)
	{
		return GetP()->getFar();
	}

	void fk_Ortho::SetAll(double argLeft, double argRight,
						  double argBottom, double argTop,
						  double argNear, double argFar)
	{
		GetP()->setAll(argLeft, argRight, argBottom, argTop, argNear, argFar);
	}
}
