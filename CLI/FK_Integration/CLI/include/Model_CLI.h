// Model_CLI.h

#pragma once

#include <FK/Model.h>
#include "Boundary_CLI.h"
#include "Shape_CLI.h"

namespace FK_CLI
{
	using namespace System::Collections::Generic;

	public enum class fk_DrawMode : unsigned int {
		NONEMODE			= 0x0000,
		POINTMODE			= 0x0001,
		LINEMODE			= 0x0002,
		POLYMODE			= 0x0004,
		BACK_POLYMODE		= (0x0008 | FK_POLYMODE),
		FRONTBACK_POLYMODE	= (0x0010 | FK_POLYMODE),
		TEXTUREMODE			= 0x0020
	};

	public ref class fk_Model : fk_Boundary {
	internal:

		static List<fk_Model^>^ modelList = gcnew List<fk_Model^>();
		fk_Shape^ shape;
		
		::fk_Model * GetP(void);
		
	public:
		fk_Model::fk_Model();
		fk_Model::fk_Model(bool argNewFlg);
		fk_Model::~fk_Model();
		fk_Model::!fk_Model();

		property unsigned int ID {
			unsigned int get();
		}

		property fk_Shape^ Shape {
			fk_Shape^ get();
			void set(fk_Shape^);
		}

		property fk_Material^ Material {
			void set(fk_Material^);
			fk_Material^ get();
		}

		property fk_Material^ InhMaterial {
			fk_Material^ get();
		}

		property fk_Color^ PointColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		property fk_Color^ InhPointColor {
			fk_Color^ get();
		}

		property fk_Color^ LineColor {
			fk_Color^ get();
			void set(fk_Color^);
		}

		property fk_Color^ InhLineColor {
			fk_Color^ get();
		}

		property double PointSize {
			void set(double);
			double get();
		}
		
		property double LineWidth {
			void set(double);
			double get();
		}

		property fk_DrawMode DrawMode {
			void set(fk_DrawMode);
			fk_DrawMode get();
		}

		property fk_MaterialMode MaterialMode {
			void set(fk_MaterialMode);
			fk_MaterialMode get();
		}

		property bool PickMode {
			void set(bool);
			bool get(void);
		}

		property bool SmoothMode {
			void set(bool);
			bool get(void);
		}
			
		property bool ReverseDrawMode {
			void set(bool);
			bool get(void);
		}

		property fk_Matrix^ InhMatrix {
			fk_Matrix^ get();
		}

		property fk_Matrix^ InhInvMatrix {
			fk_Matrix^ get();
		}

		property fk_Matrix^ InhBaseMatrix {
			fk_Matrix^ get();
		}

		property fk_Matrix^ InhInvBaseMatrix {
			fk_Matrix^ get();
		}
		
		property fk_Vector^ InhPosition {
			fk_Vector^ get();
		}

		property fk_Vector^ InhVec {
			fk_Vector^ get();
		}

		property fk_Vector^ InhUpvec {
			fk_Vector^ get();
		}

		property fk_Angle^ InhAngle {
			fk_Angle^ get();
		}

		property double InhScale {
			double get();
		}

		property fk_Model^ Parent {
			void set(fk_Model^);
			fk_Model^ get();
		}

		property bool InterMode {
			void set(bool);
			bool get();
		}
		
		property bool InterStatus {
			bool get();
		}

		property bool InterStopMode {
			void set(bool);
			bool get();
		}

		//////////////////////////////////////////////////////////////
		void DeleteMaterial(void);
		void DeletePointColor(void);
		void DeleteLineColor(void);

		bool SetParent(fk_Model^ model, bool mode);
		bool SetParent(fk_Model^ model);
		void DeleteParent(bool mode);
		void DeleteParent(void);

		bool EntryChild(fk_Model^ model, bool mode);
		bool EntryChild(fk_Model^ model);
		bool DeleteChild(fk_Model^ model, bool mode);
		bool DeleteChild(fk_Model^ model);
		void DeleteChildren(bool mode);
		void DeleteChildren(void);

		void SnapShot(void);
		bool Restore(void);
		bool Restore(double time);

		void AdjustSphere(void);
		void AdjustAABB(void);
		void AdjustOBB(void);
		void AdjustCapsule(fk_Vector^ startPos, fk_Vector^ endPos);

		bool IsInter(fk_Model^ model);
		bool IsCollision(fk_Model^ model, double %time);
		void ResetInter(void);

		void EntryInterModel(fk_Model^ model);
		void DeleteInterModel(fk_Model^ model);
		void ClearInterModel(void);

		//////////////////////////////////////////////////////////////
		bool GlRotate(fk_Vector^ origin, fk_Axis axis, double theta);
		bool GlRotate(double x, double y, double z, fk_Axis axis, double theta);
		bool GlRotate(fk_Vector^ A, fk_Vector^ B, double theta);
		bool GlRotate(double Ax, double Ay, double Az,
					  double Bx, double By, double Bz, double theta);
		bool LoRotate(fk_Vector^ origin, fk_Axis axis, double theta);
		bool LoRotate(double x, double y, double z, fk_Axis axis, double theta);
		bool LoRotate(fk_Vector^ A, fk_Vector^ B, double theta);
		bool LoRotate(double Ax, double Ay, double Az,
					  double Bx, double By, double Bz, double theta);
		bool GlRotateWithVec(fk_Vector^ origin, fk_Axis axis, double theta);
		bool GlRotateWithVec(double x, double y, double z, fk_Axis axis, double theta);
		bool GlRotateWithVec(fk_Vector^ A, fk_Vector^ B, double theta);
		bool GlRotateWithVec(double Ax, double Ay, double Az,
							 double Bx, double By, double Bz, double theta);
		bool LoRotateWithVec(fk_Vector^ origin, fk_Axis axis, double theta);
		bool LoRotateWithVec(double x, double y, double z, fk_Axis axis, double theta);
		bool LoRotateWithVec(fk_Vector^ A, fk_Vector^ B, double theta);
		bool LoRotateWithVec(double Ax, double Ay, double Az,
							 double Bx, double By, double Bz, double theta);
		bool GlTranslate(fk_Vector^ V);
		bool GlTranslate(double x, double y, double z);
		bool LoTranslate(fk_Vector^ V);
		bool LoTranslate(double x, double y, double z);
		bool GlMoveTo(fk_Vector^ V);
		bool GlMoveTo(double x, double y, double z);
	};
}
