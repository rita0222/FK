// IndexFace_CLI.h

#pragma once

#include <FK/IndexFace.h>
#include "Shape_CLI.h"
#include "Vector_CLI.h"

using namespace std;
using namespace System;
using namespace msclr::interop;

namespace FK_CLI
{
	public enum class fk_IFType
	{
		NONE,
		TRIANGLES,
		QUADS,
		POLYGON
	};
			
	public ref class fk_IndexFaceSet : fk_Shape {
	internal:
		::fk_IndexFaceSet * GetP(void)
		{
			return reinterpret_cast<::fk_IndexFaceSet *>(this->pBase);
		}

	public:
		fk_IndexFaceSet::fk_IndexFaceSet() : fk_Shape(false)
		{
			::fk_IndexFaceSet *p = new ::fk_IndexFaceSet();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_IndexFaceSet::fk_IndexFaceSet(bool argNewFlg) : fk_Shape(false)
		{
			if(argNewFlg == true) {
				::fk_IndexFaceSet *p = new ::fk_IndexFaceSet();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
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

		void cloneShape(fk_IndexFaceSet^ argIFS)
		{
			if(!argIFS) return;
			GetP()->cloneShape(reinterpret_cast<::fk_IndexFaceSet *>(argIFS->pBase));
		}

		bool readSMFFile(String^ argName)
		{
			return GetP()->readSMFFile(marshal_as<string>(argName));
		}

		bool readVRMLFile(String^ argName, bool argM, bool argS)
		{
			return GetP()->readVRMLFile(marshal_as<string>(argName), argM, argS);
		}

		bool readVRMLFile(String^ argName, bool argM)
		{
			return GetP()->readVRMLFile(marshal_as<string>(argName), argM, true);
		}

		bool readVRMLFile(String^ argName)
		{
			return GetP()->readVRMLFile(marshal_as<string>(argName), true, true);
		}

		bool readSTLFile(String^ argName, bool argS, double argT)
		{
			return GetP()->readSTLFile(marshal_as<string>(argName), argS, argT);
		}

		bool readSTLFile(String^ argName, bool argS)
		{
			return GetP()->readSTLFile(marshal_as<string>(argName), argS, 1.0e-08);
		}

		bool readSTLFile(String^ argName)
		{
			return GetP()->readSTLFile(marshal_as<string>(argName), true, 1.0e-08);
		}

		bool readHRCFile(String^ argName)
		{
			return GetP()->readHRCFile(marshal_as<string>(argName));
		}

		bool readRDSFile(String^ argName, bool argS)
		{
			return GetP()->readRDSFile(marshal_as<string>(argName), argS);
		}

		bool readRDSFile(String^ argName)
		{
			return GetP()->readRDSFile(marshal_as<string>(argName), true);
		}

		bool readDXFFile(String^ argName, bool argS)
		{
			return GetP()->readDXFFile(marshal_as<string>(argName), argS);
		}

		bool readDXFFile(String^ argName)
		{
			return GetP()->readDXFFile(marshal_as<string>(argName), true);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName,
						 bool argS, bool argC, bool argM)
		{
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName),
									   argS, argC, argM);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName, bool argS, bool argC)
		{
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName),
									   argS, argC, false);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName, bool argS)
		{
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName),
									   argS, true, false);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName)
		{
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName),
									   true, true, false);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName,
						 int argMID, bool argS, bool argC, bool argM)
		{
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName),
									   argMID, argS, argC, argM);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName,
						 int argMID, bool argS, bool argC)
		{
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName),
									   argMID, argS, argC, false);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName,
						 int argMID, bool argS)
		{
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName),
									   argMID, argS, true, false);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName, int argMID)
		{
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName),
									   argMID, true, true, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName,
						 bool argS, bool argC, bool argM)
		{
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return GetP()->readMQOData(bP, marshal_as<string>(argObjName), argS, argC, argM);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName, bool argS, bool argC)
		{
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return GetP()->readMQOData(bP, marshal_as<string>(argObjName), argS, argC, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName, bool argS)
		{
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return GetP()->readMQOData(bP, marshal_as<string>(argObjName), argS, true, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName)
		{
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return GetP()->readMQOData(bP, marshal_as<string>(argObjName), true, true, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName,
						 int argMID, bool argS, bool argC, bool argM)
		{
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
									   argMID, argS, argC, argM);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName,
						 int argMID, bool argS, bool argC)
		{
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
									   argMID, argS, argC, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName, int argMID, bool argS)
		{
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
									   argMID, argS, true, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName, int argMID)
		{
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
									   argMID, true, true, false);
		}

		bool readD3DXFile(String^ argFileName, String^ argObjName, bool argS)
		{
			return GetP()->readD3DXFile(marshal_as<string>(argFileName),
										marshal_as<string>(argObjName), argS);
		}

		bool readD3DXFile(String^ argFileName, String^ argObjName)
		{
			return GetP()->readD3DXFile(marshal_as<string>(argFileName),
										marshal_as<string>(argObjName), true);
		}
		
		bool readD3DXFile(String^ argFileName, String^ argObjName, int argM, bool argS)
		{
			return GetP()->readD3DXFile(marshal_as<string>(argFileName),
										marshal_as<string>(argObjName), argM, argS);
		}

		bool readD3DXFile(String^ argFileName, String^ argObjName, int argM)
		{
			return GetP()->readD3DXFile(marshal_as<string>(argFileName),
										marshal_as<string>(argObjName), argM, true);
		}

		bool writeVRMLFile(String^ argFileName, fk_Material^ argMat, bool argTriFlg)
		{
			::fk_Material *pM;

			pM = (!argMat) ? NULL : reinterpret_cast<::fk_Material *>(argMat->pBase);
			return GetP()->writeVRMLFile(marshal_as<string>(argFileName), pM, argTriFlg);
		}			

		bool writeVRMLFile(String^ argFileName, fk_Material^ argMat)
		{
			::fk_Material *pM;

			pM = (!argMat) ? NULL : reinterpret_cast<::fk_Material *>(argMat->pBase);
			return GetP()->writeVRMLFile(marshal_as<string>(argFileName), pM, false);
		}			
		bool writeVRMLFile(String^ argFileName)
		{
			return GetP()->writeVRMLFile(marshal_as<string>(argFileName), NULL, false);
		}			

		bool writeVRMLFile(String^ argFileName, array<double>^ argTime,
						   array<fk_Vector^>^ argPos, fk_Material^ argMat, bool argTriFlg)
		{
			::fk_Material *pM;

			if(!argFileName || !argTime || !argPos) return false;
			pM = (!argMat) ? NULL : reinterpret_cast<::fk_Material *>(argMat->pBase);

			int i;
			int timeSize = argTime->Length;
			vector<double> timeArray(timeSize);
			for(i = 0; i < timeSize; i++) timeArray[i] = argTime[i];

			int posSize = argPos->Length;
			vector<::fk_Vector> posArray(posSize);
			for(i = 0; i < posSize; i++) posArray[i] = *(argPos[i]->pVec);

			return GetP()->writeVRMLFile(marshal_as<string>(argFileName),
										 &timeArray, &posArray, pM, argTriFlg);
		}

		bool writeVRMLFile(String^ argFileName, array<double>^ argTime,
						   array<fk_Vector^>^ argPos, fk_Material^ argMat)
		{
			return writeVRMLFile(argFileName, argTime, argPos, argMat, false);
		}

		bool writeVRMLFile(String^ argFileName, array<double>^ argTime,
						   array<fk_Vector^>^ argPos)
		{
			return writeVRMLFile(argFileName, argTime, argPos, nullptr, false);
		}
		
		bool writeSTLFile(String ^argFileName)
		{
			return GetP()->writeSTLFile(marshal_as<string>(argFileName));
		}

		bool writeDXFFile(String ^argFileName, bool argTriFlg)
		{
			return GetP()->writeDXFFile(marshal_as<string>(argFileName), argTriFlg);
		}

		bool writeDXFFile(String ^argFileName)
		{
			return GetP()->writeDXFFile(marshal_as<string>(argFileName), false);
		}

		bool writeMQOFile(String^ argFileName)
		{
			return GetP()->writeMQOFile(marshal_as<string>(argFileName));
		}

		int getPosSize(void)
		{
			return GetP()->getPosSize();
		}

		int getFaceSize(void)
		{
			return GetP()->getFaceSize();
		}

		fk_Vector^ getPosVec(int argVID)
		{
			fk_Vector^ v = gcnew fk_Vector();
			*(v->pVec) = GetP()->getPosVec(argVID);
			return v;
		}

		array<int>^ getFaceData(int argFID)
		{
			int i;
			vector<int>	tmpA = GetP()->getFaceData(argFID);
			array<int>^ retA = gcnew array<int>(tmpA.size());
			for(i = 0; i < int(tmpA.size()); i++) retA[i] = tmpA[i];
			return retA;
		}

		int	getFaceData(int argFID, int argVNum)
		{
			return GetP()->getFaceData(argFID, argVNum);
		}

		fk_IFType^ getFaceType(void)
		{
			fk_IFType^ type = gcnew fk_IFType();

			switch(GetP()->getFaceType()) {
			  case FK_IF_TRIANGLES:
				type = FK_CLI::fk_IFType::NONE;
				break;

			  case FK_IF_QUADS:
				type = FK_CLI::fk_IFType::NONE;
				break;

			  case FK_IF_POLYGON:
				type = FK_CLI::fk_IFType::NONE;
				break;

			  case FK_IF_NONE:
			  default:
				type = FK_CLI::fk_IFType::NONE;
				break;
			}
			return type;
		}

		fk_Vector^ getPNorm(int argFID, int argOrder)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*(V->pVec) = GetP()->getPNorm(argFID, argOrder);
			return V;
		}

		fk_Vector^ getPNorm(int argFID)
		{
			return getPNorm(argFID, 0);
		}

		fk_Vector^ getVNorm(int argVID, int argOrder)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*(V->pVec) = GetP()->getVNorm(argVID, argOrder);
			return V;
		}

		fk_Vector^ getVNorm(int argVID)
		{
			return getVNorm(argVID, 0);
		}

		int getElemMaterialID(int argFID)
		{
			return GetP()->getElemMaterialID(argFID);
		}

		bool moveVPosition(int argVID, fk_Vector^ argP, int argOrder)
		{
			if(!argP) return false;
			return GetP()->moveVPosition(argVID, *argP->pVec, argOrder);
		}

		bool moveVPosition(int argVID, fk_Vector^ argP)
		{
			return moveVPosition(argVID, argP, 0);
		}

		bool moveVPosition(int argVID, double x, double y, double z, int argOrder)
		{
			return GetP()->moveVPosition(argVID, x, y, z, argOrder);
		}

		bool moveVPosition(int argVID, double x, double y, double z)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return GetP()->moveVPosition(argVID, x, y, z, 0);
		}

		bool moveVPosition(int argVID, array<double>^ argArray, int argOrder)
		{
			if(!argArray) return false;
			pin_ptr<double> pD = &argArray[0];
			return GetP()->moveVPosition(argVID, pD, argOrder);
		}

		bool moveVPosition(int argVID, array<double>^ argArray)
		{
			return moveVPosition(argVID, argArray, 0);
		}

		void makeIFSet(int argFNum, int argPNum, array<int>^ argIFSet,
					   int argVNum, array<fk_Vector^>^ argPosArray, int argOrder)
		{
			if(!argIFSet || !argPosArray) return;

			pin_ptr<int> pIF = &argIFSet[0];
			int vSize = argPosArray->Length;
			vector<::fk_Vector> tmpV(vSize);
			for(int i = 0; i < vSize; i++) {
				tmpV[i] = *(argPosArray[i]->pVec);
			}
			GetP()->makeIFSet(argFNum, argPNum, pIF, argVNum, &tmpV[0], argOrder);
		}
		
		void makeIFSet(int argFNum, int argPNum, array<int>^ argIFSet,
					   int argVNum, array<fk_Vector^>^ argPosArray)
		{
			makeIFSet(argFNum, argPNum, argIFSet, argVNum, argPosArray, 0);
		}

		bool setPNorm(int argFID, fk_Vector^ argN, int argOrder)
		{
			if(!argN) return false;
			return GetP()->setPNorm(argFID, *argN->pVec, argOrder);
		}

		bool setPNorm(int argFID, fk_Vector^ argN)
		{
			if(!argN) return false;
			return GetP()->setPNorm(argFID, *argN->pVec, 0);
		}

		bool setVNorm(int argVID, fk_Vector^ argN, int argOrder)
		{
			if(!argN) return false;
			return GetP()->setVNorm(argVID, *argN->pVec, argOrder);
		}

		bool setVNorm(int argVID, fk_Vector^ argN)
		{
			if(!argN) return false;
			return GetP()->setVNorm(argVID, *argN->pVec, 0);
		}

		bool setElemMaterialID(int argFID, int argMID)
		{
			return GetP()->setElemMaterialID(argFID, argMID);
		}

		void flush(void)
		{
			return GetP()->flush();
		}

		void makeBlock(double argX, double argY, double argZ)
		{
			GetP()->makeBlock(argX, argY, argZ);
		}

		void setBlockSize(double argX, double argY, double argZ)
		{
			GetP()->setBlockSize(argX, argY, argZ);
		}
		
		void setBlockSize(double argLength, fk_Axis argAxis)
		{
			GetP()->setBlockSize(argLength, GetAxis(argAxis));
		}

		void setBlockScale(double argScale)
		{
			GetP()->setBlockScale(argScale);
		}

		void setBlockScale(double argScale, fk_Axis argAxis)
		{
			GetP()->setBlockScale(argScale, GetAxis(argAxis));
		}			

		void setBlockScale(double argX, double argY, double argZ)
		{
			GetP()->setBlockScale(argX, argY, argZ);
		}

		void makeCircle(int argDiv, double argRad)
		{
			GetP()->makeCircle(argDiv, argRad);
		}

		void setCircleRadius(double argRad)
		{
			GetP()->setCircleRadius(argRad);
		}

		void setCircleDivide(int argDiv)
		{
			GetP()->setCircleDivide(argDiv);
		}

		void setCircleScale(double argScale)
		{
			GetP()->setCircleScale(argScale);
		}
		
		void makeSphere(int argDiv, double argRad)
		{
			GetP()->makeSphere(argDiv, argRad);
		}

		void setSphereRadius(double argRad)
		{
			GetP()->setSphereRadius(argRad);
		}

		void setSphereDivide(int argDiv)
		{
			GetP()->setSphereDivide(argDiv);
		}

		void setSphereScale(double argScale)
		{
			GetP()->setSphereScale(argScale);
		}

		void makePrism(int argDiv, double argTop, double argBottom, double argHeight)
		{
			GetP()->makePrism(argDiv, argTop, argBottom, argHeight);
		}

		void setPrismDivide(int argDiv)
		{
			GetP()->setPrismDivide(argDiv);
		}
			
		void setPrismTopRadius(double argTop)
		{
			GetP()->setPrismTopRadius(argTop);
		}

		void setPrismBottomRadius(double argBottom)
		{
			GetP()->setPrismBottomRadius(argBottom);
		}

		void setPrismHeight(double argHeight)
		{
			GetP()->setPrismHeight(argHeight);
		}

		void makeCone(int argDiv, double argRad, double argHeight)
		{
			GetP()->makeCone(argDiv, argRad, argHeight);
		}
			
		void setConeDivide(int argDiv)
		{
			GetP()->setConeDivide(argDiv);
		}
		
		void setConeRadius(double argRad)
		{
			GetP()->setConeRadius(argRad);
		}

		void setConeHeight(double argHeight)
		{
			GetP()->setConeHeight(argHeight);
		}

		void makeCapsule(int argDiv, double argLen, double argRad)
		{
			GetP()->makeCapsule(argDiv, argLen, argRad);
		}

		void setCapsuleSize(double argLen, double argRad)
		{
			GetP()->setCapsuleSize(argLen, argRad);
		}

		//void putSolid(fk_Solid *solid);
		//void setBVHMotion(fk_BVHMotion *bvh);
		//void setAnimationTime(double argTime)
	};
}
