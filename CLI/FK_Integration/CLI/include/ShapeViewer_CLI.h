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
		::fk_ShapeViewer * GetP(void);

	public:
		fk_ShapeViewer();
		fk_ShapeViewer(bool argNewFlg);
		fk_ShapeViewer(int argW, int argH);
		~fk_ShapeViewer();
		!fk_ShapeViewer();

		property fk_Dimension^ WindowSize {
			void set(fk_Dimension^);
		}

		property fk_Shape^ Shape {
			void set(fk_Shape^);
			fk_Shape^ get();
		}

		property int ModelNum {
			int get();
		}

		property fk_DrawMode DrawMode {
			fk_DrawMode get();
			void set(fk_DrawMode);
		}

		property bool BlendStatus {
			bool get();
			void set(bool);
		}

		property fk_Color^ BGColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		property bool AxisMode {
			bool get();
			void set(bool);
		}

		property double AxisScale {
			double get();
			void set(double);
		}

		property fk_Vector^ Center {
			fk_Vector^ get();
		}

		property double Head {
			double get();
			void set(double);
		}
		
		property double Pitch {
			double get();
			void set(double);
		}

		property double Bank {
			double get();
			void set(double);
		}

		property double Scale {
			double get();
			void set(double);
		}
		
		bool		Draw(void);
		void		SetShape(int ID, fk_Shape^ shape);
		fk_Shape^	GetShape(int ID);
		void		ClearModel(void);
		void		SetDrawMode(int ID, fk_DrawMode mode);
		fk_DrawMode	GetDrawMode(int ID);
		void		SetLineWidth(int ID, double width);
		double		GetLineWidth(int ID);
		void		SetPointSize(int ID, double size);
		double		GetPointSize(int ID);
		void		SetMaterial(int ID, fk_Material^ mat);
		void		SetEdgeColor(int ID, fk_Color^ col);
		void		SetVertexColor(int ID, fk_Color^ col);
		void		SetPosition(int ID, fk_Vector^ pos);
		void		SetPosition(int ID, double x, double y, double z);
		void		SetAngle(int ID, fk_Angle^ angle);
		void		SetAngle(int ID, double h, double p, double b);
		void		SetVec(int ID, fk_Vector^ vec);
		void		SetVec(int ID, double x, double y, double z);
		void		SetUpvec(int ID, fk_Vector^ vec);
		void		SetUpvec(int ID, double x, double y, double z);
		bool		SnapImage(String^ fileName, fk_ImageType format);
		bool		SnapImage(fk_Image^ image);
	};
}
