// ShapeViewer_CLI.h

#pragma once

#include <FK/ShapeViewer.h>
#include "Matrix_CLI.h"
#include "Image_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	public ref class fk_ShapeViewer : fk_BaseObject {
	internal:
		::fk_ShapeViewer * GetP(void)
		{
			return (::fk_ShapeViewer *)(pBase);
		}

	public:
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

		bool draw(void);
		void setWindowSize(int w, int h);
		void setShape(fk_Shape^ shape);
		void setShape(int ID, fk_Shape^ shape);
		fk_Shape^ getShape(int ID);
		fk_Shape^ getShape(void);
		int getModelNum(void);
		void clearModel(void);
		void setDrawMode(fk_DrawMode mode);
		fk_DrawMode getDrawMode(void);
		void setBlendStatus(bool mode);
		bool getBlendStatus(void);
		void setBGColor(fk_Color^ col);
		void setBGColor(float r, float g, float b);
		fk_Color^ getBGColor(void);
		void setAxisMode(bool mode);
		bool getAxisMode(void);
		void setAxisScale(double scale);
		double getAxisScale(void);
		fk_Vector^ getCenter(void);
		void setDrawMode(int ID, fk_DrawMode mode);
		fk_DrawMode getDrawMode(int ID);
		void setLineWidth(int ID, double width);
		double getLineWidth(int ID);
		void setPointSize(int ID, double size);
		double getPointSize(int ID);
		void setMaterial(int ID, fk_Material^ mat);
		void setEdgeColor(int ID, fk_Color^ col);
		void setVertexColor(int ID, fk_Color^ col);
		void setHead(double angle);
		double getHead(void);
		void setPitch(double angle);
		double getPitch(void);
		void setBank(double angle);
		double getBank(void);
		void setScale(double scale);
		double getScale(void);
		void setPosition(int ID, fk_Vector^ pos);
		void setPosition(int ID, double x, double y, double z);
		void setAngle(int ID, fk_Angle^ angle);
		void setAngle(int ID, double h, double p, double b);
		void setVec(int ID, fk_Vector^ vec);
		void setVec(int ID, double x, double y, double z);
		void setUpvec(int ID, fk_Vector^ vec);
		void setUpvec(int ID, double x, double y, double z);
		bool snapImage(String^ fileName, fk_ImageType format);
		bool snapImage(fk_Image^ image);
	};
}
