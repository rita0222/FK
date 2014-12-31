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
			
	public ref class fk_IndexFaceSet : FK_CLI::fk_Shape {
	internal:
		::fk_IndexFaceSet * GetP(void)
		{
			return (::fk_IndexFaceSet *)(this->pBase);
		}

	public:
		fk_IndexFaceSet::fk_IndexFaceSet(): fk_Shape(false)
		{
			this->pBase = new ::fk_IndexFaceSet();
		}

		fk_IndexFaceSet::fk_IndexFaceSet(bool argNewFlg) : fk_Shape(false)
		{
			if(argNewFlg == true) this->pBase = new ::fk_IndexFaceSet();

		}

		fk_IndexFaceSet::~fk_IndexFaceSet()
		{
			this->!fk_IndexFaceSet();
		}

		fk_IndexFaceSet::!fk_IndexFaceSet()
		{
			if(dFlg == true) delete this->pBase;
			this->pBase = NULL;
		}

		void cloneShape(fk_IndexFaceSet^ IFS);
		bool readSMFFile(String^ name);
		bool readVRMLFile(String^ name, bool materialFlg, bool solidFlg);
		bool readVRMLFile(String^ name, bool materialFlg);
		bool readVRMLFile(String^ name);
		bool readSTLFile(String^ name, bool solidFlg, double tolerance);
		bool readSTLFile(String^ name, bool solidFlg);
		bool readSTLFile(String^ name);
		bool readHRCFile(String^ name);
		bool readRDSFile(String^ name, bool solidFlg);
		bool readRDSFile(String^ name);
		bool readDXFFile(String^ name, bool solidFlg);
		bool readDXFFile(String^ name);
		bool readMQOFile(String^ fileName, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);
		bool readMQOFile(String^ fileName, String^ objName, bool solidFlg, bool contFlg);
		bool readMQOFile(String^ fileName, String^ objName, bool solidFlg);
		bool readMQOFile(String^ fileName, String^ objName);
		bool readMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg, bool contFlg, bool materialFlg);
		bool readMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg, bool contFlg);
		bool readMQOFile(String^ fileName, String^ objName,
						 int materialID, bool solidFlg);
		bool readMQOFile(String^ fileName, String^ objName, int materialID);
		bool readMQOData(array<Byte>^ buffer, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);
		bool readMQOData(array<Byte>^ buffer, String^ objName, bool solidFlg, bool contFlg);
		bool readMQOData(array<Byte>^ buffer, String^ objName, bool solidFlg);
		bool readMQOData(array<Byte>^ buffer, String^ objName);
		bool readMQOData(array<Byte>^ buffer, String^ objName,
						 int MID, bool solidFlg, bool contFlg, bool materialFlg);
		bool readMQOData(array<Byte>^ buffer, String^ objName,
						 int MID, bool solidFlg, bool contFlg);
		bool readMQOData(array<Byte>^ buffer, String^ objName, int materialID, bool solidFlg);
		bool readMQOData(array<Byte>^ buffer, String^ objName, int materialID);
		bool readD3DXFile(String^ fileName, String^ objName, bool solidFlg);
		bool readD3DXFile(String^ fileName, String^ objName);
		bool readD3DXFile(String^ fileName, String^ objName, int materialID, bool solidFlg);
		bool readD3DXFile(String^ fileName, String^ objName, int materialID);
		bool writeVRMLFile(String^ fileName, fk_Material^ material, bool triFlg);
		bool writeVRMLFile(String^ fileName, fk_Material^ material);
		bool writeVRMLFile(String^ fileName);
		bool writeVRMLFile(String^ fileName, array<double>^ time,
						   array<fk_Vector^>^ Pos, fk_Material^ material, bool triFlg);
		bool writeVRMLFile(String^ fileName, array<double>^ time,
						   array<fk_Vector^>^ Pos, fk_Material^ material);
		bool writeVRMLFile(String^ fileName, array<double>^ time,
						   array<fk_Vector^>^ pos);
		bool writeSTLFile(String ^fileName);
		bool writeDXFFile(String ^fileName, bool triFlg);
		bool writeDXFFile(String ^fileName);
		bool writeMQOFile(String^ fileName);
		int getPosSize(void);
		int getFaceSize(void);
		fk_Vector^ getPosVec(int vertexID);
		array<int>^ getFaceData(int faceID);
		int	getFaceData(int faceID, int vertexNum);
		fk_IFType^ getFaceType(void);
		fk_Vector^ getPNorm(int faceID, int order);
		fk_Vector^ getPNorm(int faceID);
		fk_Vector^ getVNorm(int vertexID, int order);
		fk_Vector^ getVNorm(int vertexID);
		int getElemMaterialID(int faceID);
		bool moveVPosition(int vertexID, fk_Vector^ pos, int order);
		bool moveVPosition(int vertexID, fk_Vector^ pos);
		bool moveVPosition(int vertexID, double x, double y, double z, int order);
		bool moveVPosition(int vertexID, double x, double y, double z);
		bool moveVPosition(int vertexID, array<double>^ array, int order);
		bool moveVPosition(int vertexID, array<double>^ array);
		void makeIFSet(int faceNum, int polyNum, array<int>^ IFSet,
					   int vertexNum, array<fk_Vector^>^ posArray, int order);
		void makeIFSet(int faceNum, int polyNum, array<int>^ IFSet,
					   int vertexNum, array<fk_Vector^>^ posArray);
		bool setPNorm(int faceID, fk_Vector^ N, int order);
		bool setPNorm(int faceID, fk_Vector^ N);
		bool setVNorm(int vertexID, fk_Vector^ N, int order);
		bool setVNorm(int vertexID, fk_Vector^ N);
		bool setElemMaterialID(int faceID, int materialID);
		void flush(void);
		void makeBlock(double x, double y, double z);
		void setBlockSize(double x, double y, double z);
		void setBlockSize(double length, fk_Axis axis);
		void setBlockScale(double scale);
		void setBlockScale(double scale, fk_Axis axis);
		void setBlockScale(double x, double y, double z);
		void makeCircle(int div, double rad);
		void setCircleRadius(double rad);
		void setCircleDivide(int div);
		void setCircleScale(double scale);
		void makeSphere(int div, double rad);
		void setSphereRadius(double rad);
		void setSphereDivide(int div);
		void setSphereScale(double scale);
		void makePrism(int div, double top, double bottom, double height);
		void setPrismDivide(int div);
		void setPrismTopRadius(double top);
		void setPrismBottomRadius(double bottom);
		void setPrismHeight(double height);
		void makeCone(int div, double rad, double height);
		void setConeDivide(int div);
		void setConeRadius(double rad);
		void setConeHeight(double height);
		void makeCapsule(int div, double length, double rad);
		void setCapsuleSize(double length, double rad);
		void setBVHMotion(fk_BVHMotion^ BVH);
		void setAnimationTime(double time);
		void putSolid(fk_Solid^ solid);
	};
}
