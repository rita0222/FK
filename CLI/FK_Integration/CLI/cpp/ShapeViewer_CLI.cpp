#include "ShapeViewer_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	bool fk_ShapeViewer::draw(void)
	{
		return GetP()->draw();
	}

	void fk_ShapeViewer::setWindowSize(int argW, int argH)
	{
		GetP()->setWindowSize(argW, argH);
	}

	void fk_ShapeViewer::setShape(fk_Shape^ argShape)
	{
		if(!argShape) return;
		GetP()->setShape(argShape->GetP());
	}

	void fk_ShapeViewer::setShape(int argID, fk_Shape^ argShape)
	{
		if(!argShape) return;
		GetP()->setShape(argID, argShape->GetP());
	}

	fk_Shape^ fk_ShapeViewer::getShape(int argID)
	{
		fk_Shape^ S = gcnew fk_Shape(false);
		S->pBase = GetP()->getShape(argID);
		S->dFlg = false;
		return S;
	}

	fk_Shape^ fk_ShapeViewer::getShape(void)
	{
		fk_Shape^ S = gcnew fk_Shape(false);
		S->pBase = GetP()->getShape();
		S->dFlg = false;
		return S;
	}

	int fk_ShapeViewer::getModelNum(void)
	{
		return GetP()->getModelNum();
	}

	void fk_ShapeViewer::clearModel(void)
	{
		GetP()->clearModel();
	}

	void fk_ShapeViewer::setDrawMode(fk_DrawMode argMode)
	{
		unsigned int mode = static_cast<unsigned int>(argMode);
		GetP()->setDrawMode(mode);
	}

	fk_DrawMode fk_ShapeViewer::getDrawMode(void)
	{
		return static_cast<fk_DrawMode>(GetP()->getDrawMode());
	}

	void fk_ShapeViewer::setBlendStatus(bool argMode)
	{
		GetP()->setBlendStatus(argMode);
	}

	bool fk_ShapeViewer::getBlendStatus(void)
	{
		return GetP()->getBlendStatus();
	}

	void fk_ShapeViewer::setBGColor(fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setBGColor(*argCol->pCol);
	}

	void fk_ShapeViewer::setBGColor(float argR, float argG, float argB)
	{
		GetP()->setBGColor(argR, argG, argB);
	}

	fk_Color^ fk_ShapeViewer::getBGColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getBGColor();
		return C;
	}

	void fk_ShapeViewer::setAxisMode(bool argMode)
	{
		GetP()->setAxisMode(argMode);
	}

	bool fk_ShapeViewer::getAxisMode(void)
	{
		return GetP()->getAxisMode();
	}

	void fk_ShapeViewer::setAxisScale(double argScale)
	{
		GetP()->setAxisScale(argScale);
	}

	double fk_ShapeViewer::getAxisScale(void)
	{
		return GetP()->getAxisScale();
	}

	fk_Vector^ fk_ShapeViewer::getCenter(void)
	{
		return gcnew fk_Vector(GetP()->getCenter());
	}

	void fk_ShapeViewer::setDrawMode(int argID, fk_DrawMode argMode)
	{
		unsigned int mode = static_cast<unsigned int>(argMode);
		GetP()->setDrawMode(argID, mode);
	}

	fk_DrawMode fk_ShapeViewer::getDrawMode(int argID)
	{
		return static_cast<fk_DrawMode>(GetP()->getDrawMode(argID));
	}

	void fk_ShapeViewer::setLineWidth(int argID, double argWidth)
	{
		GetP()->setLineWidth(argID, argWidth);
	}

	double fk_ShapeViewer::getLineWidth(int argID)
	{
		return GetP()->getLineWidth(argID);
	}

	void fk_ShapeViewer::setPointSize(int argID, double argSize)
	{
		GetP()->setPointSize(argID, argSize);
	}

	double fk_ShapeViewer::getPointSize(int argID)
	{
		return GetP()->getPointSize(argID);
	}

	void fk_ShapeViewer::setMaterial(int argID, fk_Material^ argMat)
	{
		if(!argMat) return;
		GetP()->setMaterial(argID, *argMat->pMat);
	}

	void fk_ShapeViewer::setEdgeColor(int argID, fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setEdgeColor(argID, *argCol->pCol);
	}

	void fk_ShapeViewer::setVertexColor(int argID, fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setVertexColor(argID, *argCol->pCol);
	}

	void fk_ShapeViewer::setHead(double argAngle)
	{
		GetP()->setHead(argAngle);
	}

	double fk_ShapeViewer::getHead(void)
	{
		return GetP()->getHead();
	}

	void fk_ShapeViewer::setPitch(double argAngle)
	{
		GetP()->setPitch(argAngle);
	}

	double fk_ShapeViewer::getPitch(void)
	{
		return GetP()->getPitch();
	}

	void fk_ShapeViewer::setBank(double argAngle)
	{
		return GetP()->setBank(argAngle);
	}

	double fk_ShapeViewer::getBank(void)
	{
		return GetP()->getBank();
	}

	void fk_ShapeViewer::setScale(double argScale)
	{
		GetP()->setScale(argScale);
	}

	double fk_ShapeViewer::getScale(void)
	{
		return GetP()->getScale();
	}

	void fk_ShapeViewer::setPosition(int argID, fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->setPosition(argID, *argPos->pVec);
	}

	void fk_ShapeViewer::setPosition(int argID, double argX, double argY, double argZ)
	{
		GetP()->setPosition(argID, argX, argY, argZ);
	}

	void fk_ShapeViewer::setAngle(int argID, fk_Angle^ argAngle)
	{
		if(!argAngle) return;
		GetP()->setAngle(argID, *argAngle->pAngle);
	}

	void fk_ShapeViewer::setAngle(int argID, double argH, double argP, double argB)
	{
		GetP()->setAngle(argID, argH, argP, argB);
	}

	void fk_ShapeViewer::setVec(int argID, fk_Vector^ argVec)
	{
		if(!argVec) return;
		GetP()->setVec(argID, *argVec->pVec);
	}

	void fk_ShapeViewer::setVec(int argID, double argX, double argY, double argZ)
	{
		GetP()->setVec(argID, argX, argY, argZ);
	}

	void fk_ShapeViewer::setUpvec(int argID, fk_Vector^ argVec)
	{
		if(!argVec) return;
		GetP()->setUpvec(argID, *argVec->pVec);
	}

	void fk_ShapeViewer::setUpvec(int argID, double argX, double argY, double argZ)
	{
		GetP()->setUpvec(argID, argX, argY, argZ);
	}

	bool fk_ShapeViewer::snapImage(String^ argFileName, fk_ImageType argFormat)
	{
		string fileName = marshal_as<string>(argFileName);
		switch(argFormat) {
		  case fk_ImageType::BMP:
			return GetP()->snapImage(fileName, FK_IMAGE_BMP);

		  case fk_ImageType::PNG:
			return GetP()->snapImage(fileName, FK_IMAGE_PNG);

		  case fk_ImageType::JPG:
			return GetP()->snapImage(fileName, FK_IMAGE_JPG);

		  default:
			break;
		}
		return false;
	}

	bool fk_ShapeViewer::snapImage(fk_Image^ argImage)
	{
		if(!argImage) return false;
		return GetP()->snapImage(argImage->GetP());
	}
}

