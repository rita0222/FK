#include "Projection_CLI.h"

namespace FK_CLI {

	fk_ProjectMode fk_ProjectBase::getMode(void)
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

	
	void fk_Perspective::setFovy(double argFovy)
	{
		GetP()->setFovy(argFovy);
	}			

	void fk_Perspective::setNear(double argNear)
	{
		GetP()->setNear(argNear);
	}

	void fk_Perspective::setFar(double argFar)
	{
		GetP()->setFar(argFar);
	}

	void fk_Perspective::setAll(double argFovy, double argNear, double argFar)
	{
		GetP()->setAll(argFovy, argNear, argFar);
	}

	double fk_Perspective::getFovy(void)
	{
		return GetP()->getFovy();
	}

	double fk_Perspective::getNear(void)
	{
		return GetP()->getNear();
	}

	double fk_Perspective::getFar(void)
	{
		return GetP()->getFar();
	}

	
	void fk_Frustum::setLeft(double argLeft)
	{
		GetP()->setLeft(argLeft);
	}

	void fk_Frustum::setRight(double argRight)
	{
		GetP()->setRight(argRight);
	}

	void fk_Frustum::setBottom(double argBottom)
	{
		GetP()->setBottom(argBottom);
	}

	void fk_Frustum::setTop(double argTop)
	{
		GetP()->setTop(argTop);
	}

	void fk_Frustum::setNear(double argNear)
	{
		GetP()->setNear(argNear);
	}
		
	void fk_Frustum::setFar(double argFar)
	{
		GetP()->setFar(argFar);
	}
		
	void fk_Frustum::setAll(double argLeft, double argRight,
				double argBottom, double argTop,
				double argNear, double argFar)
	{
		GetP()->setAll(argLeft, argRight, argBottom, argTop, argNear, argFar);
	}

	double fk_Frustum::getLeft(void)
	{
		return GetP()->getLeft();
	}

	double fk_Frustum::getRight(void)
	{
		return GetP()->getRight();
	}

	double fk_Frustum::getBottom(void)
	{
		return GetP()->getBottom();
	}

	double fk_Frustum::getTop(void)
	{
		return GetP()->getTop();
	}

	double fk_Frustum::getNear(void)
	{
		return GetP()->getNear();
	}

	double fk_Frustum::getFar(void)
	{
		return GetP()->getFar();
	}

	

	void fk_Ortho::setLeft(double argLeft)
	{
		GetP()->setLeft(argLeft);
	}

	void fk_Ortho::setRight(double argRight)
	{
		GetP()->setRight(argRight);
	}

	void fk_Ortho::setBottom(double argBottom)
	{
		GetP()->setBottom(argBottom);
	}

	void fk_Ortho::setTop(double argTop)
	{
		GetP()->setTop(argTop);
	}

	void fk_Ortho::setNear(double argNear)
	{
		GetP()->setNear(argNear);
	}
		
	void fk_Ortho::setFar(double argFar)
	{
		GetP()->setFar(argFar);
	}
		
	void fk_Ortho::setAll(double argLeft, double argRight,
				double argBottom, double argTop,
				double argNear, double argFar)
	{
		GetP()->setAll(argLeft, argRight, argBottom, argTop, argNear, argFar);
	}

	double fk_Ortho::getLeft(void)
	{
		return GetP()->getLeft();
	}

	double fk_Ortho::getRight(void)
	{
		return GetP()->getRight();
	}

	double fk_Ortho::getBottom(void)
	{
		return GetP()->getBottom();
	}

	double fk_Ortho::getTop(void)
	{
		return GetP()->getTop();
	}

	double fk_Ortho::getNear(void)
	{
		return GetP()->getNear();
	}

	double fk_Ortho::getFar(void)
	{
		return GetP()->getFar();
	}
}
