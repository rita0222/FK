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
		FK_IF_NONE,
		FK_IF_TRIANGLES,
		FK_IF_QUADS,
		FK_IF_POLYGON
	};
			
	public ref class fk_IndexFaceSet : fk_Shape {
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
			delete this->pBase;
			this->pBase = NULL;
		}

		void cloneShape(fk_IndexFaceSet^ argIFS)
		{
			if(!argIFS) return;
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			::fk_IndexFaceSet *pI = reinterpret_cast<::fk_IndexFaceSet *>(argIFS->pBase);
			p->cloneShape(pI);
		}

		bool readSMFFile(String^ argName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readSMFFile(marshal_as<string>(argName));
		}

		bool readVRMLFile(String^ argName, bool argM, bool argS)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readVRMLFile(marshal_as<string>(argName), argM, argS);
		}

		bool readVRMLFile(String^ argName, bool argM)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readVRMLFile(marshal_as<string>(argName), argM, true);
		}

		bool readVRMLFile(String^ argName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readVRMLFile(marshal_as<string>(argName), true, true);
		}

		bool readSTLFile(String^ argName, bool argS, double argT)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readSTLFile(marshal_as<string>(argName), argS, argT);
		}

		bool readSTLFile(String^ argName, bool argS)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readSTLFile(marshal_as<string>(argName), argS, 1.0e-08);
		}

		bool readSTLFile(String^ argName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readSTLFile(marshal_as<string>(argName), true, 1.0e-08);
		}

		bool readHRCFile(String^ argName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readHRCFile(marshal_as<string>(argName));
		}

		bool readRDSFile(String^ argName, bool argS)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readRDSFile(marshal_as<string>(argName), argS);
		}

		bool readRDSFile(String^ argName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readRDSFile(marshal_as<string>(argName), true);
		}

		bool readDXFFile(String^ argName, bool argS)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readDXFFile(marshal_as<string>(argName), argS);
		}

		bool readDXFFile(String^ argName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readDXFFile(marshal_as<string>(argName), true);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName,
						 bool argS, bool argC, bool argM)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readMQOFile(marshal_as<string>(argFileName),
								  marshal_as<string>(argObjName), argS, argC, argM);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName, bool argS, bool argC)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readMQOFile(marshal_as<string>(argFileName),
								  marshal_as<string>(argObjName), argS, argC, false);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName, bool argS)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readMQOFile(marshal_as<string>(argFileName),
								  marshal_as<string>(argObjName), argS, true, false);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readMQOFile(marshal_as<string>(argFileName),
								  marshal_as<string>(argObjName), true, true, false);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName,
						 int argMID, bool argS, bool argC, bool argM)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readMQOFile(marshal_as<string>(argFileName),
								  marshal_as<string>(argObjName), argMID, argS, argC, argM);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName,
						 int argMID, bool argS, bool argC)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readMQOFile(marshal_as<string>(argFileName),
								  marshal_as<string>(argObjName), argMID, argS, argC, false);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName,
						 int argMID, bool argS)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readMQOFile(marshal_as<string>(argFileName),
								  marshal_as<string>(argObjName), argMID, argS, true, false);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName, int argMID)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readMQOFile(marshal_as<string>(argFileName),
								  marshal_as<string>(argObjName), argMID, true, true, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName,
						 bool argS, bool argC, bool argM)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return p->readMQOData(bP, marshal_as<string>(argObjName), argS, argC, argM);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName, bool argS, bool argC)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return p->readMQOData(bP, marshal_as<string>(argObjName), argS, argC, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName, bool argS)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return p->readMQOData(bP, marshal_as<string>(argObjName), argS, true, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return p->readMQOData(bP, marshal_as<string>(argObjName), true, true, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName,
						 int argMID, bool argS, bool argC, bool argM)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return p->readMQOData(bP, marshal_as<string>(argObjName),
								  argMID, argS, argC, argM);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName,
						 int argMID, bool argS, bool argC)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return p->readMQOData(bP, marshal_as<string>(argObjName),
								  argMID, argS, argC, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName, int argMID, bool argS)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return p->readMQOData(bP, marshal_as<string>(argObjName),
											argMID, argS, true, false);
		}

		bool readMQOData(array<Byte>^ argBuffer, String^ argObjName, int argMID)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			pin_ptr<unsigned char> bP = &argBuffer[0];
			return p->readMQOData(bP, marshal_as<string>(argObjName),
								  argMID, true, true, false);
		}

		bool readD3DXFile(String^ argFileName, String^ argObjName, bool argS)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readD3DXFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName), argS);
		}

		bool readD3DXFile(String^ argFileName, String^ argObjName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readD3DXFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName), true);
		}
		
		bool readD3DXFile(String^ argFileName, String^ argObjName, int argM, bool argS)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readD3DXFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName), argM, argS);
		}

		bool readD3DXFile(String^ argFileName, String^ argObjName, int argM)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->readD3DXFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName), argM, true);
		}

		bool writeVRMLFile(String^ argFileName, fk_Material^ argMat, bool argTriFlg)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			::fk_Material *pM;

			pM = (!argMat) ? NULL : reinterpret_cast<::fk_Material *>(argMat->pBase);
			return p->writeVRMLFile(marshal_as<string>(argFileName), pM, argTriFlg);
		}			

		bool writeVRMLFile(String^ argFileName, fk_Material^ argMat)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			::fk_Material *pM;

			pM = (!argMat) ? NULL : reinterpret_cast<::fk_Material *>(argMat->pBase);
			return p->writeVRMLFile(marshal_as<string>(argFileName), pM, false);
		}			
		bool writeVRMLFile(String^ argFileName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->writeVRMLFile(marshal_as<string>(argFileName), NULL, false);
		}			

		bool writeVRMLFile(String^ argFileName, array<double>^ argTime,
						   array<fk_Vector^>^ argPos, fk_Material^ argMat, bool argTriFlg)
		{
			if(!argFileName || !argTime || !argPos) return false;
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			::fk_Material *pM;
			pM = (!argMat) ? NULL : reinterpret_cast<::fk_Material *>(argMat->pBase);

			int i;
			int timeSize = argTime->Length;
			vector<double> timeArray(timeSize);
			for(i = 0; i < timeSize; i++) timeArray[i] = argTime[i];

			int posSize = argPos->Length;
			vector<::fk_Vector> posArray(posSize);
			for(i = 0; i < posSize; i++) posArray[i] = *(argPos[i]->pVec);

			return p->writeVRMLFile(marshal_as<string>(argFileName),
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
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->writeSTLFile(marshal_as<string>(argFileName));
		}

		bool writeDXFFile(String ^argFileName, bool argTriFlg)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->writeDXFFile(marshal_as<string>(argFileName), argTriFlg);
		}

		bool writeDXFFile(String ^argFileName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->writeDXFFile(marshal_as<string>(argFileName), false);
		}

		bool writeMQOFile(String^ argFileName)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->writeMQOFile(marshal_as<string>(argFileName));
		}

		int getPosSize(void)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->getPosSize();
		}

		int getFaceSize(void)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->getFaceSize();
		}

		fk_Vector^ getPosVec(int argVID)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			fk_Vector^ v = gcnew fk_Vector();
			*(v->pVec) = p->getPosVec(argVID);
			return v;
		}

		array<int>^ getFaceData(int argFID)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			int i;
			vector<int>	tmpA = p->getFaceData(argFID);
			array<int>^ retA = gcnew array<int>(tmpA.size());
			for(i = 0; i < int(tmpA.size()); i++) retA[i] = tmpA[i];
			return retA;
		}

		int	getFaceData(int argFID, int argVNum)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->getFaceData(argFID, argVNum);
		}

		fk_IFType^ getFaceType(void)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			fk_IFType^ type = gcnew fk_IFType();

			switch(p->getFaceType()) {
			  case FK_IF_TRIANGLES:
				type = FK_CLI::fk_IFType::FK_IF_NONE;
				break;

			  case FK_IF_QUADS:
				type = FK_CLI::fk_IFType::FK_IF_NONE;
				break;

			  case FK_IF_POLYGON:
				type = FK_CLI::fk_IFType::FK_IF_NONE;
				break;

			  case FK_IF_NONE:
			  default:
				type = FK_CLI::fk_IFType::FK_IF_NONE;
				break;
			}
			return type;
		}

		fk_Vector^ getPNorm(int argFID, int argOrder)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			fk_Vector^ V = gcnew fk_Vector();
			*(V->pVec) = p->getPNorm(argFID, argOrder);
			return V;
		}

		fk_Vector^ getPNorm(int argFID)
		{
			return getPNorm(argFID, 0);
		}

		fk_Vector^ getVNorm(int argVID, int argOrder)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			fk_Vector^ V = gcnew fk_Vector();
			*(V->pVec) = p->getVNorm(argVID, argOrder);
			return V;
		}

		fk_Vector^ getVNorm(int argVID)
		{
			return getVNorm(argVID, 0);
		}

		int getElemMaterialID(int argFID)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->getElemMaterialID(argFID);
		}

		bool moveVPosition(int argVID, fk_Vector^ argP, int argOrder)
		{
			if(!argP) return false;
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->moveVPosition(argVID, *argP->pVec, argOrder);
		}

		bool moveVPosition(int argVID, fk_Vector^ argP)
		{
			return moveVPosition(argVID, argP, 0);
		}

		bool moveVPosition(int argVID, double x, double y, double z, int argOrder)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->moveVPosition(argVID, x, y, z, argOrder);
		}

		bool moveVPosition(int argVID, double x, double y, double z)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->moveVPosition(argVID, x, y, z, 0);
		}

		bool moveVPosition(int argVID, array<double>^ argArray, int argOrder)
		{
			if(!argArray) return false;
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			pin_ptr<double> pD = &argArray[0];
			return p->moveVPosition(argVID, pD, argOrder);
		}

		bool moveVPosition(int argVID, array<double>^ argArray)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return moveVPosition(argVID, argArray, 0);
		}

		void makeIFSet(int argFNum, int argPNum, array<int>^ argIFSet,
					   int argVNum, array<fk_Vector^>^ argPosArray, int argOrder)
		{
			if(!argIFSet || !argPosArray) return;

			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			pin_ptr<int> pIF = &argIFSet[0];
			int vSize = argPosArray->Length;
			vector<::fk_Vector> tmpV(vSize);
			for(int i = 0; i < vSize; i++) {
				tmpV[i] = *(argPosArray[i]->pVec);
			}
			p->makeIFSet(argFNum, argPNum, pIF, argVNum, &tmpV[0], argOrder);
		}
		
		void makeIFSet(int argFNum, int argPNum, array<int>^ argIFSet,
					   int argVNum, array<fk_Vector^>^ argPosArray)
		{
			makeIFSet(argFNum, argPNum, argIFSet, argVNum, argPosArray, 0);
		}

		bool setPNorm(int argFID, fk_Vector^ argN, int argOrder)
		{
			if(!argN) return false;
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->setPNorm(argFID, *argN->pVec, argOrder);
		}

		bool setPNorm(int argFID, fk_Vector^ argN)
		{
			if(!argN) return false;
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->setPNorm(argFID, *argN->pVec, 0);
		}

		bool setVNorm(int argVID, fk_Vector^ argN, int argOrder)
		{
			if(!argN) return false;
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->setVNorm(argVID, *argN->pVec, argOrder);
		}

		bool setVNorm(int argVID, fk_Vector^ argN)
		{
			if(!argN) return false;
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->setVNorm(argVID, *argN->pVec, 0);
		}

		bool setElemMaterialID(int argFID, int argMID)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->setElemMaterialID(argFID, argMID);
		}

		void flush(void)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			return p->flush();
		}

		void makeBlock(double argX, double argY, double argZ)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->makeBlock(argX, argY, argZ);
		}

		void setBlockSize(double argX, double argY, double argZ)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setBlockSize(argX, argY, argZ);
		}
		
		void setBlockSize(double argLength, fk_Axis argAxis)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setBlockSize(argLength, GetAxis(argAxis));
		}

		void setBlockScale(double argScale)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setBlockScale(argScale);
		}

		void setBlockScale(double argScale, fk_Axis argAxis)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setBlockScale(argScale, GetAxis(argAxis));
		}			

		void setBlockScale(double argX, double argY, double argZ)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setBlockScale(argX, argY, argZ);
		}

		void makeCircle(int argDiv, double argRad)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->makeCircle(argDiv, argRad);
		}

		void setCircleRadius(double argRad)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setCircleRadius(argRad);
		}

		void setCircleDivide(int argDiv)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setCircleDivide(argDiv);
		}

		void setCircleScale(double argScale)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setCircleScale(argScale);
		}
		
		void makeSphere(int argDiv, double argRad)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->makeSphere(argDiv, argRad);
		}

		void setSphereRadius(double argRad)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setSphereRadius(argRad);
		}

		void setSphereDivide(int argDiv)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setSphereDivide(argDiv);
		}

		void setSphereScale(double argScale)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setSphereScale(argScale);
		}

		void makePrism(int argDiv, double argTop, double argBottom, double argHeight)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->makePrism(argDiv, argTop, argBottom, argHeight);
		}

		void setPrismDivide(int argDiv)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setPrismDivide(argDiv);
		}
			
		void setPrismTopRadius(double argTop)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setPrismTopRadius(argTop);
		}

		void setPrismBottomRadius(double argBottom)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setPrismBottomRadius(argBottom);
		}

		void setPrismHeight(double argHeight)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setPrismHeight(argHeight);
		}

		void makeCone(int argDiv, double argRad, double argHeight)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->makeCone(argDiv, argRad, argHeight);
		}
			
		void setConeDivide(int argDiv)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setConeDivide(argDiv);
		}
		
		void setConeRadius(double argRad)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setConeRadius(argRad);
		}

		void setConeHeight(double argHeight)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setConeHeight(argHeight);
		}

		void makeCapsule(int argDiv, double argLen, double argRad)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->makeCapsule(argDiv, argLen, argRad);
		}
		void setCapsuleSize(double argLen, double argRad)
		{
			::fk_IndexFaceSet *p = reinterpret_cast<::fk_IndexFaceSet *>(pBase);
			p->setCapsuleSize(argLen, argRad);
		}

		//void putSolid(fk_Solid *solid);
		//void setBVHMotion(fk_BVHMotion *bvh);
		//void setAnimationTime(double argTime)
	};
}
