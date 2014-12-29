#include "IndexFace_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	void fk_IndexFaceSet::cloneShape(fk_IndexFaceSet^ argIFS)
	{
		if(!argIFS) return;
		GetP()->cloneShape((::fk_IndexFaceSet *)(argIFS->pBase));
	}

	bool fk_IndexFaceSet::readSMFFile(String^ argName)
	{
		return GetP()->readSMFFile(marshal_as<string>(argName));
	}

	bool fk_IndexFaceSet::readVRMLFile(String^ argName, bool argM, bool argS)
	{
		return GetP()->readVRMLFile(marshal_as<string>(argName), argM, argS);
	}

	bool fk_IndexFaceSet::readVRMLFile(String^ argName, bool argM)
	{
		return GetP()->readVRMLFile(marshal_as<string>(argName), argM, true);
	}

	bool fk_IndexFaceSet::readVRMLFile(String^ argName)
	{
		return GetP()->readVRMLFile(marshal_as<string>(argName), true, true);
	}

	bool fk_IndexFaceSet::readSTLFile(String^ argName, bool argS, double argT)
	{
		return GetP()->readSTLFile(marshal_as<string>(argName), argS, argT);
	}

	bool fk_IndexFaceSet::readSTLFile(String^ argName, bool argS)
	{
		return GetP()->readSTLFile(marshal_as<string>(argName), argS, 1.0e-08);
	}

	bool fk_IndexFaceSet::readSTLFile(String^ argName)
	{
		return GetP()->readSTLFile(marshal_as<string>(argName), true, 1.0e-08);
	}

	bool fk_IndexFaceSet::readHRCFile(String^ argName)
	{
		return GetP()->readHRCFile(marshal_as<string>(argName));
	}

	bool fk_IndexFaceSet::readRDSFile(String^ argName, bool argS)
	{
		return GetP()->readRDSFile(marshal_as<string>(argName), argS);
	}

	bool fk_IndexFaceSet::readRDSFile(String^ argName)
	{
		return GetP()->readRDSFile(marshal_as<string>(argName), true);
	}

	bool fk_IndexFaceSet::readDXFFile(String^ argName, bool argS)
	{
		return GetP()->readDXFFile(marshal_as<string>(argName), argS);
	}

	bool fk_IndexFaceSet::readDXFFile(String^ argName)
	{
		return GetP()->readDXFFile(marshal_as<string>(argName), true);
	}

	bool fk_IndexFaceSet::readMQOFile(String^ argFileName, String^ argObjName,
									  bool argS, bool argC, bool argM)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argS, argC, argM);
	}

	bool fk_IndexFaceSet::readMQOFile(String^ argFileName, String^ argObjName,
									  bool argS, bool argC)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argS, argC, false);
	}

	bool fk_IndexFaceSet::readMQOFile(String^ argFileName, String^ argObjName, bool argS)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argS, true, false);
	}

	bool fk_IndexFaceSet::readMQOFile(String^ argFileName, String^ argObjName)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   true, true, false);
	}

	bool fk_IndexFaceSet::readMQOFile(String^ argFileName, String^ argObjName,
									  int argMID, bool argS, bool argC, bool argM)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argMID, argS, argC, argM);
	}

	bool fk_IndexFaceSet::readMQOFile(String^ argFileName, String^ argObjName,
									  int argMID, bool argS, bool argC)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argMID, argS, argC, false);
	}

	bool fk_IndexFaceSet::readMQOFile(String^ argFileName, String^ argObjName,
									  int argMID, bool argS)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argMID, argS, true, false);
	}

	bool fk_IndexFaceSet::readMQOFile(String^ argFileName, String^ argObjName, int argMID)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argMID, true, true, false);
	}

	bool fk_IndexFaceSet::readMQOData(array<Byte>^ argBuffer, String^ argObjName,
									  bool argS, bool argC, bool argM)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName), argS, argC, argM);
	}

	bool fk_IndexFaceSet::readMQOData(array<Byte>^ argBuffer, String^ argObjName,
									  bool argS, bool argC)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName), argS, argC, false);
	}

	bool fk_IndexFaceSet::readMQOData(array<Byte>^ argBuffer, String^ argObjName, bool argS)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName), argS, true, false);
	}

	bool fk_IndexFaceSet::readMQOData(array<Byte>^ argBuffer, String^ argObjName)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName), true, true, false);
	}

	bool fk_IndexFaceSet::readMQOData(array<Byte>^ argBuffer, String^ argObjName,
									  int argMID, bool argS, bool argC, bool argM)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
								   argMID, argS, argC, argM);
	}

	bool fk_IndexFaceSet::readMQOData(array<Byte>^ argBuffer, String^ argObjName,
									  int argMID, bool argS, bool argC)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
								   argMID, argS, argC, false);
	}

	bool fk_IndexFaceSet::readMQOData(array<Byte>^ argBuffer, String^ argObjName,
									  int argMID, bool argS)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
								   argMID, argS, true, false);
	}

	bool fk_IndexFaceSet::readMQOData(array<Byte>^ argBuffer, String^ argObjName, int argMID)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
								   argMID, true, true, false);
	}

	bool fk_IndexFaceSet::readD3DXFile(String^ argFileName, String^ argObjName, bool argS)
	{
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName), argS);
	}

	bool fk_IndexFaceSet::readD3DXFile(String^ argFileName, String^ argObjName)
	{
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName), true);
	}

	bool fk_IndexFaceSet::readD3DXFile(String^ argFileName, String^ argObjName,
									   int argM, bool argS)
	{
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName), argM, argS);
	}

	bool fk_IndexFaceSet::readD3DXFile(String^ argFileName, String^ argObjName, int argM)
	{
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName), argM, true);
	}

	bool fk_IndexFaceSet::writeVRMLFile(String^ argFileName, fk_Material^ argMat, bool argTriFlg)
	{
		::fk_Material *pM;

		pM = (!argMat) ? NULL : argMat->pMat;
		return GetP()->writeVRMLFile(marshal_as<string>(argFileName), pM, argTriFlg);
	}

	bool fk_IndexFaceSet::writeVRMLFile(String^ argFileName, fk_Material^ argMat)
	{
		::fk_Material *pM;

		pM = (!argMat) ? NULL : argMat->pMat;
		return GetP()->writeVRMLFile(marshal_as<string>(argFileName), pM, false);
	}
	bool fk_IndexFaceSet::writeVRMLFile(String^ argFileName)
	{
		return GetP()->writeVRMLFile(marshal_as<string>(argFileName), NULL, false);
	}

	bool fk_IndexFaceSet::writeVRMLFile(String^ argFileName, array<double>^ argTime,
										array<fk_Vector^>^ argPos, fk_Material^ argMat,
										bool argTriFlg)
	{
		::fk_Material *pM;

		if(!argFileName || !argTime || !argPos) return false;
		pM = (!argMat) ? NULL : argMat->pMat;

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

	bool fk_IndexFaceSet::writeVRMLFile(String^ argFileName, array<double>^ argTime,
										array<fk_Vector^>^ argPos, fk_Material^ argMat)
	{
		return writeVRMLFile(argFileName, argTime, argPos, argMat, false);
	}

	bool fk_IndexFaceSet::writeVRMLFile(String^ argFileName, array<double>^ argTime,
										array<fk_Vector^>^ argPos)
	{
		return writeVRMLFile(argFileName, argTime, argPos, nullptr, false);
	}

	bool fk_IndexFaceSet::writeSTLFile(String ^argFileName)
	{
		return GetP()->writeSTLFile(marshal_as<string>(argFileName));
	}

	bool fk_IndexFaceSet::writeDXFFile(String ^argFileName, bool argTriFlg)
	{
		return GetP()->writeDXFFile(marshal_as<string>(argFileName), argTriFlg);
	}

	bool fk_IndexFaceSet::writeDXFFile(String ^argFileName)
	{
		return GetP()->writeDXFFile(marshal_as<string>(argFileName), false);
	}

	bool fk_IndexFaceSet::writeMQOFile(String^ argFileName)
	{
		return GetP()->writeMQOFile(marshal_as<string>(argFileName));
	}

	int fk_IndexFaceSet::getPosSize(void)
	{
		return GetP()->getPosSize();
	}

	int fk_IndexFaceSet::getFaceSize(void)
	{
		return GetP()->getFaceSize();
	}

	fk_Vector^ fk_IndexFaceSet::getPosVec(int argVID)
	{
		fk_Vector^ v = gcnew fk_Vector();
		*(v->pVec) = GetP()->getPosVec(argVID);
		return v;
	}

	array<int>^ fk_IndexFaceSet::getFaceData(int argFID)
	{
		int i;
		vector<int>	tmpA = GetP()->getFaceData(argFID);
		array<int>^ retA = gcnew array<int>(tmpA.size());
		for(i = 0; i < int(tmpA.size()); i++) retA[i] = tmpA[i];
		return retA;
	}

	int	fk_IndexFaceSet::getFaceData(int argFID, int argVNum)
	{
		return GetP()->getFaceData(argFID, argVNum);
	}

	fk_IFType^ fk_IndexFaceSet::getFaceType(void)
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

	fk_Vector^ fk_IndexFaceSet::getPNorm(int argFID, int argOrder)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*(V->pVec) = GetP()->getPNorm(argFID, argOrder);
		return V;
	}

	fk_Vector^ fk_IndexFaceSet::getPNorm(int argFID)
	{
		return getPNorm(argFID, 0);
	}

	fk_Vector^ fk_IndexFaceSet::getVNorm(int argVID, int argOrder)
	{
		fk_Vector^ V = gcnew fk_Vector();
		*(V->pVec) = GetP()->getVNorm(argVID, argOrder);
		return V;
	}

	fk_Vector^ fk_IndexFaceSet::getVNorm(int argVID)
	{
		return getVNorm(argVID, 0);
	}

	int fk_IndexFaceSet::getElemMaterialID(int argFID)
	{
		return GetP()->getElemMaterialID(argFID);
	}

	bool fk_IndexFaceSet::moveVPosition(int argVID, fk_Vector^ argP, int argOrder)
	{
		if(!argP) return false;
		return GetP()->moveVPosition(argVID, *argP->pVec, argOrder);
	}

	bool fk_IndexFaceSet::moveVPosition(int argVID, fk_Vector^ argP)
	{
		return moveVPosition(argVID, argP, 0);
	}

	bool fk_IndexFaceSet::moveVPosition(int argVID, double x, double y, double z, int argOrder)
	{
		return GetP()->moveVPosition(argVID, x, y, z, argOrder);
	}

	bool fk_IndexFaceSet::moveVPosition(int argVID, double x, double y, double z)
	{
		::fk_IndexFaceSet *p = (::fk_IndexFaceSet *)(pBase);
		return GetP()->moveVPosition(argVID, x, y, z, 0);
	}

	bool fk_IndexFaceSet::moveVPosition(int argVID, array<double>^ argArray, int argOrder)
	{
		if(!argArray) return false;
		pin_ptr<double> pD = &argArray[0];
		return GetP()->moveVPosition(argVID, pD, argOrder);
	}

	bool fk_IndexFaceSet::moveVPosition(int argVID, array<double>^ argArray)
	{
		return moveVPosition(argVID, argArray, 0);
	}

	void fk_IndexFaceSet::makeIFSet(int argFNum, int argPNum, array<int>^ argIFSet,
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

	void fk_IndexFaceSet::makeIFSet(int argFNum, int argPNum, array<int>^ argIFSet,
									int argVNum, array<fk_Vector^>^ argPosArray)
	{
		makeIFSet(argFNum, argPNum, argIFSet, argVNum, argPosArray, 0);
	}

	bool fk_IndexFaceSet::setPNorm(int argFID, fk_Vector^ argN, int argOrder)
	{
		if(!argN) return false;
		return GetP()->setPNorm(argFID, *argN->pVec, argOrder);
	}

	bool fk_IndexFaceSet::setPNorm(int argFID, fk_Vector^ argN)
	{
		if(!argN) return false;
		return GetP()->setPNorm(argFID, *argN->pVec, 0);
	}

	bool fk_IndexFaceSet::setVNorm(int argVID, fk_Vector^ argN, int argOrder)
	{
		if(!argN) return false;
		return GetP()->setVNorm(argVID, *argN->pVec, argOrder);
	}

	bool fk_IndexFaceSet::setVNorm(int argVID, fk_Vector^ argN)
	{
		if(!argN) return false;
		return GetP()->setVNorm(argVID, *argN->pVec, 0);
	}

	bool fk_IndexFaceSet::setElemMaterialID(int argFID, int argMID)
	{
		return GetP()->setElemMaterialID(argFID, argMID);
	}

	void fk_IndexFaceSet::flush(void)
	{
		return GetP()->flush();
	}

	void fk_IndexFaceSet::makeBlock(double argX, double argY, double argZ)
	{
		GetP()->makeBlock(argX, argY, argZ);
	}

	void fk_IndexFaceSet::setBlockSize(double argX, double argY, double argZ)
	{
		GetP()->setBlockSize(argX, argY, argZ);
	}

	void fk_IndexFaceSet::setBlockSize(double argLength, fk_Axis argAxis)
	{
		GetP()->setBlockSize(argLength, GetAxis(argAxis));
	}

	void fk_IndexFaceSet::setBlockScale(double argScale)
	{
		GetP()->setBlockScale(argScale);
	}

	void fk_IndexFaceSet::setBlockScale(double argScale, fk_Axis argAxis)
	{
		GetP()->setBlockScale(argScale, GetAxis(argAxis));
	}

	void fk_IndexFaceSet::setBlockScale(double argX, double argY, double argZ)
	{
		GetP()->setBlockScale(argX, argY, argZ);
	}

	void fk_IndexFaceSet::makeCircle(int argDiv, double argRad)
	{
		GetP()->makeCircle(argDiv, argRad);
	}

	void fk_IndexFaceSet::setCircleRadius(double argRad)
	{
		GetP()->setCircleRadius(argRad);
	}

	void fk_IndexFaceSet::setCircleDivide(int argDiv)
	{
		GetP()->setCircleDivide(argDiv);
	}

	void fk_IndexFaceSet::setCircleScale(double argScale)
	{
		GetP()->setCircleScale(argScale);
	}

	void fk_IndexFaceSet::makeSphere(int argDiv, double argRad)
	{
		GetP()->makeSphere(argDiv, argRad);
	}

	void fk_IndexFaceSet::setSphereRadius(double argRad)
	{
		GetP()->setSphereRadius(argRad);
	}

	void fk_IndexFaceSet::setSphereDivide(int argDiv)
	{
		GetP()->setSphereDivide(argDiv);
	}

	void fk_IndexFaceSet::setSphereScale(double argScale)
	{
		GetP()->setSphereScale(argScale);
	}

	void fk_IndexFaceSet::makePrism(int argDiv, double argTop,
									double argBottom, double argHeight)
	{
		GetP()->makePrism(argDiv, argTop, argBottom, argHeight);
	}

	void fk_IndexFaceSet::setPrismDivide(int argDiv)
	{
		GetP()->setPrismDivide(argDiv);
	}

	void fk_IndexFaceSet::setPrismTopRadius(double argTop)
	{
		GetP()->setPrismTopRadius(argTop);
	}

	void fk_IndexFaceSet::setPrismBottomRadius(double argBottom)
	{
		GetP()->setPrismBottomRadius(argBottom);
	}

	void fk_IndexFaceSet::setPrismHeight(double argHeight)
	{
		GetP()->setPrismHeight(argHeight);
	}

	void fk_IndexFaceSet::makeCone(int argDiv, double argRad, double argHeight)
	{
		GetP()->makeCone(argDiv, argRad, argHeight);
	}

	void fk_IndexFaceSet::setConeDivide(int argDiv)
	{
		GetP()->setConeDivide(argDiv);
	}

	void fk_IndexFaceSet::setConeRadius(double argRad)
	{
		GetP()->setConeRadius(argRad);
	}

	void fk_IndexFaceSet::setConeHeight(double argHeight)
	{
		GetP()->setConeHeight(argHeight);
	}

	void fk_IndexFaceSet::makeCapsule(int argDiv, double argLen, double argRad)
	{
		GetP()->makeCapsule(argDiv, argLen, argRad);
	}

	void fk_IndexFaceSet::setCapsuleSize(double argLen, double argRad)
	{
		GetP()->setCapsuleSize(argLen, argRad);
	}

	void fk_IndexFaceSet::setBVHMotion(fk_BVHMotion^ argBVH)
	{
		if(!argBVH) return;
		GetP()->setBVHMotion(argBVH->pMotion);
	}

	void fk_IndexFaceSet::setAnimationTime(double argTime)
	{
		GetP()->setAnimationTime(argTime);
	}
}
