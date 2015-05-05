// IndexFace_CLI.h

#pragma once

#include <FK/IndexFace.h>
#include "Shape_CLI.h"
#include "Vector_CLI.h"
#include "BVHMotion_CLI.h"

namespace FK_CLI
{

	ref class fk_Solid;

	public enum class fk_IFType {
		NONE,
		TRIANGLES,
		QUADS,
		POLYGON
	};
			
	public ref class fk_IndexFaceSet : fk_Shape {
	internal:
		::fk_IndexFaceSet * GetP(void);

	public:
		fk_IndexFaceSet();
		fk_IndexFaceSet(bool argNewFlg);
		~fk_IndexFaceSet();
		!fk_IndexFaceSet();

		property int PosSize {
			int get();
		}

		property int FaceSize {
			int get();
		}

		property fk_IFType^ FaceType {
			fk_IFType^ get();
		}

		property double AnimationTime {
			void set(double);
		}
		
		property fk_BVHMotion^ BVHMotion {
			void set(fk_BVHMotion^);
		}

		void CloneShape(fk_IndexFaceSet^ IFS);
		bool ReadSMFFile(String^ name);
		bool ReadVRMLFile(String^ name, bool materialFlg, bool solidFlg);
		bool ReadVRMLFile(String^ name, bool materialFlg);
		bool ReadVRMLFile(String^ name);
		bool ReadSTLFile(String^ name, bool solidFlg, double tolerance);
		bool ReadSTLFile(String^ name, bool solidFlg);
		bool ReadSTLFile(String^ name);
		bool ReadHRCFile(String^ name);
		bool ReadRDSFile(String^ name, bool solidFlg);
		bool ReadRDSFile(String^ name);
		bool ReadDXFFile(String^ name, bool solidFlg);
		bool ReadDXFFile(String^ name);
		bool ReadMQOFile(String^ fileName, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, bool solidFlg, bool contFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, bool solidFlg);
		bool ReadMQOFile(String^ fileName, String^ objName);
		bool ReadMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg, bool contFlg, bool materialFlg);
		bool ReadMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg, bool contFlg);
		bool ReadMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName, bool solidFlg, bool contFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName, bool solidFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName,
						 int MID, bool solidFlg, bool contFlg, bool materialFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName,
						 int MID, bool solidFlg, bool contFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName, int materialID, bool solidFlg);
		bool ReadMQOData(array<Byte>^ buffer, String^ objName, int materialID);
		bool ReadD3DXFile(String^ fileName, String^ objName, bool solidFlg);
		bool ReadD3DXFile(String^ fileName, String^ objName);
		bool ReadD3DXFile(String^ fileName, String^ objName, int materialID, bool solidFlg);
		bool ReadD3DXFile(String^ fileName, String^ objName, int materialID);
		bool WriteVRMLFile(String^ fileName, fk_Material^ material, bool triFlg);
		bool WriteVRMLFile(String^ fileName, fk_Material^ material);
		bool WriteVRMLFile(String^ fileName);
		bool WriteVRMLFile(String^ fileName, array<double>^ time,
						   array<fk_Vector^>^ Pos, fk_Material^ material, bool triFlg);
		bool WriteVRMLFile(String^ fileName, array<double>^ time,
						   array<fk_Vector^>^ Pos, fk_Material^ material);
		bool WriteVRMLFile(String^ fileName, array<double>^ time,
						   array<fk_Vector^>^ pos);
		bool WriteSTLFile(String ^fileName);
		bool WriteDXFFile(String ^fileName, bool triFlg);
		bool WriteDXFFile(String ^fileName);
		bool WriteMQOFile(String^ fileName);

		fk_Vector^ GetPosVec(int vertexID);
		array<int>^ GetFaceData(int faceID);
		int	GetFaceData(int faceID, int vertexNum);
		fk_Vector^ GetPNorm(int faceID, int order);
		fk_Vector^ GetPNorm(int faceID);
		fk_Vector^ GetVNorm(int vertexID, int order);
		fk_Vector^ GetVNorm(int vertexID);
		int GetElemMaterialID(int faceID);
		bool MoveVPosition(int vertexID, fk_Vector^ pos, int order);
		bool MoveVPosition(int vertexID, fk_Vector^ pos);
		bool MoveVPosition(int vertexID, double x, double y, double z, int order);
		bool MoveVPosition(int vertexID, double x, double y, double z);
		bool MoveVPosition(int vertexID, array<double>^ array, int order);
		bool MoveVPosition(int vertexID, array<double>^ array);
		void MakeIFSet(int faceNum, int polyNum, array<int>^ IFSet,
					   int vertexNum, array<fk_Vector^>^ posArray, int order);
		void MakeIFSet(int faceNum, int polyNum, array<int>^ IFSet,
					   int vertexNum, array<fk_Vector^>^ posArray);
		bool SetPNorm(int faceID, fk_Vector^ N, int order);
		bool SetPNorm(int faceID, fk_Vector^ N);
		bool SetVNorm(int vertexID, fk_Vector^ N, int order);
		bool SetVNorm(int vertexID, fk_Vector^ N);
		bool SetElemMaterialID(int faceID, int materialID);
		void Flush(void);
		void MakeBlock(double x, double y, double z);
		void SetBlockSize(double x, double y, double z);
		void SetBlockSize(double length, fk_Axis axis);
		void SetBlockScale(double scale);
		void SetBlockScale(double scale, fk_Axis axis);
		void SetBlockScale(double x, double y, double z);
		void MakeCircle(int div, double rad);
		void SetCircleRadius(double rad);
		void SetCircleDivide(int div);
		void SetCircleScale(double scale);
		void MakeSphere(int div, double rad);
		void SetSphereRadius(double rad);
		void SetSphereDivide(int div);
		void SetSphereScale(double scale);
		void MakePrism(int div, double top, double bottom, double height);
		void SetPrismDivide(int div);
		void SetPrismTopRadius(double top);
		void SetPrismBottomRadius(double bottom);
		void SetPrismHeight(double height);
		void MakeCone(int div, double rad, double height);
		void SetConeDivide(int div);
		void SetConeRadius(double rad);
		void SetConeHeight(double height);
		void MakeCapsule(int div, double length, double rad);
		void SetCapsuleSize(double length, double rad);
		void PutSolid(fk_Solid^ solid);
	};
}
