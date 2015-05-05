#include "ShapeViewer_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::fk_ShapeViewer * fk_ShapeViewer::GetP(void)
	{
		return (::fk_ShapeViewer *)(pBase);
	}

	fk_ShapeViewer::fk_ShapeViewer() : fk_BaseObject(false)
	{
		pBase = new ::fk_ShapeViewer();
	}

	fk_ShapeViewer::fk_ShapeViewer(bool argNewFlg) : fk_BaseObject(false)
	{
		if(argNewFlg == true) pBase = new ::fk_ShapeViewer();
	}

	fk_ShapeViewer::fk_ShapeViewer(int argW, int argH) : fk_BaseObject(false)
	{
		pBase = new ::fk_ShapeViewer(argW, argH);
	}

	fk_ShapeViewer::~fk_ShapeViewer()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_ShapeViewer::!fk_ShapeViewer()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) {
			GetP()->SetFinalizeMode();
			delete GetP();
		}
		pBase = nullptr;
	}

	//////////////////////////////////////////////////////////////////////
	
	void fk_ShapeViewer::WindowSize::set(fk_Dimension^ argD)
	{
		if(!argD) return;
		GetP()->setWindowSize(argD->pDim->w, argD->pDim->h);
	}

	void fk_ShapeViewer::Shape::set(fk_Shape^ argShape)
	{
		if(!argShape) return;
		GetP()->setShape(argShape->GetP());
	}

	fk_Shape^ fk_ShapeViewer::Shape::get()
	{
		fk_Shape^ S = gcnew fk_Shape(false);
		S->pBase = GetP()->getShape();
		S->dFlg = false;
		return S;
	}

	int fk_ShapeViewer::ModelNum::get(void)
	{
		return GetP()->getModelNum();
	}

	void fk_ShapeViewer::DrawMode::set(fk_DrawMode argMode)
	{
		unsigned int mode = static_cast<unsigned int>(argMode);
		GetP()->setDrawMode(mode);
	}

	fk_DrawMode fk_ShapeViewer::DrawMode::get(void)
	{
		return static_cast<fk_DrawMode>(GetP()->getDrawMode());
	}

	void fk_ShapeViewer::BlendStatus::set(bool argMode)
	{
		GetP()->setBlendStatus(argMode);
	}

	bool fk_ShapeViewer::BlendStatus::get(void)
	{
		return GetP()->getBlendStatus();
	}

	void fk_ShapeViewer::BGColor::set(fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setBGColor(*argCol->pCol);
	}

	fk_Color^ fk_ShapeViewer::BGColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getBGColor();
		return C;
	}

	void fk_ShapeViewer::AxisMode::set(bool argMode)
	{
		GetP()->setAxisMode(argMode);
	}

	bool fk_ShapeViewer::AxisMode::get(void)
	{
		return GetP()->getAxisMode();
	}

	void fk_ShapeViewer::AxisScale::set(double argScale)
	{
		GetP()->setAxisScale(argScale);
	}

	double fk_ShapeViewer::AxisScale::get(void)
	{
		return GetP()->getAxisScale();
	}

	fk_Vector^ fk_ShapeViewer::Center::get(void)
	{
		return gcnew fk_Vector(GetP()->getCenter());
	}

	void fk_ShapeViewer::Head::set(double argAngle)
	{
		GetP()->setHead(argAngle);
	}

	double fk_ShapeViewer::Head::get(void)
	{
		return GetP()->getHead();
	}

	void fk_ShapeViewer::Pitch::set(double argAngle)
	{
		GetP()->setPitch(argAngle);
	}

	double fk_ShapeViewer::Pitch::get(void)
	{
		return GetP()->getPitch();
	}

	void fk_ShapeViewer::Bank::set(double argAngle)
	{
		return GetP()->setBank(argAngle);
	}

	double fk_ShapeViewer::Bank::get(void)
	{
		return GetP()->getBank();
	}

	void fk_ShapeViewer::Scale::set(double argScale)
	{
		GetP()->setScale(argScale);
	}

	double fk_ShapeViewer::Scale::get(void)
	{
		return GetP()->getScale();
	}

	//////////////////////////////////////////////////////////////////////

	bool fk_ShapeViewer::Draw(void)
	{
		return GetP()->draw();
	}

	void fk_ShapeViewer::SetShape(int argID, fk_Shape^ argShape)
	{
		if(!argShape) return;
		GetP()->setShape(argID, argShape->GetP());
	}

	fk_Shape^ fk_ShapeViewer::GetShape(int argID)
	{
		fk_Shape^ S = gcnew fk_Shape(false);
		S->pBase = GetP()->getShape(argID);
		S->dFlg = false;
		return S;
	}

	void fk_ShapeViewer::ClearModel(void)
	{
		GetP()->clearModel();
	}

	void fk_ShapeViewer::SetDrawMode(int argID, fk_DrawMode argMode)
	{
		unsigned int mode = static_cast<unsigned int>(argMode);
		GetP()->setDrawMode(argID, mode);
	}

	fk_DrawMode fk_ShapeViewer::GetDrawMode(int argID)
	{
		return static_cast<fk_DrawMode>(GetP()->getDrawMode(argID));
	}

	void fk_ShapeViewer::SetLineWidth(int argID, double argWidth)
	{
		GetP()->setLineWidth(argID, argWidth);
	}

	double fk_ShapeViewer::GetLineWidth(int argID)
	{
		return GetP()->getLineWidth(argID);
	}

	void fk_ShapeViewer::SetPointSize(int argID, double argSize)
	{
		GetP()->setPointSize(argID, argSize);
	}

	double fk_ShapeViewer::GetPointSize(int argID)
	{
		return GetP()->getPointSize(argID);
	}

	void fk_ShapeViewer::SetMaterial(int argID, fk_Material^ argMat)
	{
		if(!argMat) return;
		GetP()->setMaterial(argID, *argMat->pMat);
	}

	void fk_ShapeViewer::SetEdgeColor(int argID, fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setEdgeColor(argID, *argCol->pCol);
	}

	void fk_ShapeViewer::SetVertexColor(int argID, fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setVertexColor(argID, *argCol->pCol);
	}

	void fk_ShapeViewer::SetPosition(int argID, fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->setPosition(argID, argPos);
	}

	void fk_ShapeViewer::SetPosition(int argID, double argX, double argY, double argZ)
	{
		GetP()->setPosition(argID, argX, argY, argZ);
	}

	void fk_ShapeViewer::SetAngle(int argID, fk_Angle^ argAngle)
	{
		if(!argAngle) return;
		GetP()->setAngle(argID, argAngle);
	}

	void fk_ShapeViewer::SetAngle(int argID, double argH, double argP, double argB)
	{
		GetP()->setAngle(argID, argH, argP, argB);
	}

	void fk_ShapeViewer::SetVec(int argID, fk_Vector^ argVec)
	{
		if(!argVec) return;
		GetP()->setVec(argID, argVec);
	}

	void fk_ShapeViewer::SetVec(int argID, double argX, double argY, double argZ)
	{
		GetP()->setVec(argID, argX, argY, argZ);
	}

	void fk_ShapeViewer::SetUpvec(int argID, fk_Vector^ argVec)
	{
		if(!argVec) return;
		GetP()->setUpvec(argID, argVec);
	}

	void fk_ShapeViewer::SetUpvec(int argID, double argX, double argY, double argZ)
	{
		GetP()->setUpvec(argID, argX, argY, argZ);
	}

	bool fk_ShapeViewer::SnapImage(String^ argFileName, fk_ImageType argFormat)
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

	bool fk_ShapeViewer::SnapImage(fk_Image^ argImage)
	{
		if(!argImage) return false;
		return GetP()->snapImage(argImage->GetP());
	}
}

