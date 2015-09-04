/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/

﻿#include "IndexFace_CLI.h"
#include "Solid_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::fk_IndexFaceSet * fk_IndexFaceSet::GetP(void)
	{
		return (::fk_IndexFaceSet *)(this->pBase);
	}

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
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	int fk_IndexFaceSet::PosSize::get(void)
	{
		return GetP()->getPosSize();
	}

	int fk_IndexFaceSet::FaceSize::get(void)
	{
		return GetP()->getFaceSize();
	}

	fk_IFType^ fk_IndexFaceSet::FaceType::get(void)
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

	void fk_IndexFaceSet::BVHMotion::set(fk_BVHMotion^ argBVH)
	{
		if(!argBVH) return;
		GetP()->setBVHMotion(argBVH->pMotion);
	}

	void fk_IndexFaceSet::AnimationTime::set(double argTime)
	{
		GetP()->setAnimationTime(argTime);
	}

	void fk_IndexFaceSet::CloneShape(fk_IndexFaceSet^ argIFS)
	{
		if(!argIFS) return;
		GetP()->cloneShape((::fk_IndexFaceSet *)(argIFS->pBase));
	}

	bool fk_IndexFaceSet::ReadSMFFile(String^ argName)
	{
		return GetP()->readSMFFile(marshal_as<string>(argName));
	}

	bool fk_IndexFaceSet::ReadVRMLFile(String^ argName, bool argM, bool argS)
	{
		return GetP()->readVRMLFile(marshal_as<string>(argName), argM, argS);
	}

	bool fk_IndexFaceSet::ReadVRMLFile(String^ argName, bool argM)
	{
		return GetP()->readVRMLFile(marshal_as<string>(argName), argM, true);
	}

	bool fk_IndexFaceSet::ReadVRMLFile(String^ argName)
	{
		return GetP()->readVRMLFile(marshal_as<string>(argName), true, true);
	}

	bool fk_IndexFaceSet::ReadSTLFile(String^ argName, bool argS, double argT)
	{
		return GetP()->readSTLFile(marshal_as<string>(argName), argS, argT);
	}

	bool fk_IndexFaceSet::ReadSTLFile(String^ argName, bool argS)
	{
		return GetP()->readSTLFile(marshal_as<string>(argName), argS, 1.0e-08);
	}

	bool fk_IndexFaceSet::ReadSTLFile(String^ argName)
	{
		return GetP()->readSTLFile(marshal_as<string>(argName), true, 1.0e-08);
	}

	bool fk_IndexFaceSet::ReadHRCFile(String^ argName)
	{
		return GetP()->readHRCFile(marshal_as<string>(argName));
	}

	bool fk_IndexFaceSet::ReadRDSFile(String^ argName, bool argS)
	{
		return GetP()->readRDSFile(marshal_as<string>(argName), argS);
	}

	bool fk_IndexFaceSet::ReadRDSFile(String^ argName)
	{
		return GetP()->readRDSFile(marshal_as<string>(argName), true);
	}

	bool fk_IndexFaceSet::ReadDXFFile(String^ argName, bool argS)
	{
		return GetP()->readDXFFile(marshal_as<string>(argName), argS);
	}

	bool fk_IndexFaceSet::ReadDXFFile(String^ argName)
	{
		return GetP()->readDXFFile(marshal_as<string>(argName), true);
	}

	bool fk_IndexFaceSet::ReadMQOFile(String^ argFileName, String^ argObjName,
									  bool argS, bool argC, bool argM)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argS, argC, argM);
	}

	bool fk_IndexFaceSet::ReadMQOFile(String^ argFileName, String^ argObjName,
									  bool argS, bool argC)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argS, argC, false);
	}

	bool fk_IndexFaceSet::ReadMQOFile(String^ argFileName, String^ argObjName, bool argS)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argS, true, false);
	}

	bool fk_IndexFaceSet::ReadMQOFile(String^ argFileName, String^ argObjName)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   true, true, false);
	}

	bool fk_IndexFaceSet::ReadMQOFile(String^ argFileName, String^ argObjName,
									  int argMID, bool argS, bool argC, bool argM)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argMID, argS, argC, argM);
	}

	bool fk_IndexFaceSet::ReadMQOFile(String^ argFileName, String^ argObjName,
									  int argMID, bool argS, bool argC)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argMID, argS, argC, false);
	}

	bool fk_IndexFaceSet::ReadMQOFile(String^ argFileName, String^ argObjName,
									  int argMID, bool argS)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argMID, argS, true, false);
	}

	bool fk_IndexFaceSet::ReadMQOFile(String^ argFileName, String^ argObjName, int argMID)
	{
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argMID, true, true, false);
	}

	bool fk_IndexFaceSet::ReadMQOData(cli::array<Byte>^ argBuffer, String^ argObjName,
									  bool argS, bool argC, bool argM)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName), argS, argC, argM);
	}

	bool fk_IndexFaceSet::ReadMQOData(cli::array<Byte>^ argBuffer, String^ argObjName,
									  bool argS, bool argC)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName), argS, argC, false);
	}

	bool fk_IndexFaceSet::ReadMQOData(cli::array<Byte>^ argBuffer, String^ argObjName, bool argS)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName), argS, true, false);
	}

	bool fk_IndexFaceSet::ReadMQOData(cli::array<Byte>^ argBuffer, String^ argObjName)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName), true, true, false);
	}

	bool fk_IndexFaceSet::ReadMQOData(cli::array<Byte>^ argBuffer, String^ argObjName,
									  int argMID, bool argS, bool argC, bool argM)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
								   argMID, argS, argC, argM);
	}

	bool fk_IndexFaceSet::ReadMQOData(cli::array<Byte>^ argBuffer, String^ argObjName,
									  int argMID, bool argS, bool argC)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
								   argMID, argS, argC, false);
	}

	bool fk_IndexFaceSet::ReadMQOData(cli::array<Byte>^ argBuffer, String^ argObjName,
									  int argMID, bool argS)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
								   argMID, argS, true, false);
	}

	bool fk_IndexFaceSet::ReadMQOData(cli::array<Byte>^ argBuffer, String^ argObjName, int argMID)
	{
		pin_ptr<unsigned char> bP = &argBuffer[0];
		return GetP()->readMQOData(bP, marshal_as<string>(argObjName),
								   argMID, true, true, false);
	}

	bool fk_IndexFaceSet::ReadD3DXFile(String^ argFileName, String^ argObjName, bool argS)
	{
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName), argS);
	}

	bool fk_IndexFaceSet::ReadD3DXFile(String^ argFileName, String^ argObjName)
	{
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName), true);
	}

	bool fk_IndexFaceSet::ReadD3DXFile(String^ argFileName, String^ argObjName,
									   int argM, bool argS)
	{
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName), argM, argS);
	}

	bool fk_IndexFaceSet::ReadD3DXFile(String^ argFileName, String^ argObjName, int argM)
	{
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName), argM, true);
	}

	bool fk_IndexFaceSet::WriteVRMLFile(String^ argFileName, fk_Material^ argMat, bool argTriFlg)
	{
		::fk_Material *pM;

		pM = (!argMat) ? nullptr : argMat->pMat;
		return GetP()->writeVRMLFile(marshal_as<string>(argFileName), pM, argTriFlg);
	}

	bool fk_IndexFaceSet::WriteVRMLFile(String^ argFileName, fk_Material^ argMat)
	{
		::fk_Material *pM;

		pM = (!argMat) ? nullptr : argMat->pMat;
		return GetP()->writeVRMLFile(marshal_as<string>(argFileName), pM, false);
	}
	bool fk_IndexFaceSet::WriteVRMLFile(String^ argFileName)
	{
		return GetP()->writeVRMLFile(marshal_as<string>(argFileName), nullptr, false);
	}

	bool fk_IndexFaceSet::WriteVRMLFile(String^ argFileName, cli::array<double>^ argTime,
										cli::array<fk_Vector^>^ argPos, fk_Material^ argMat,
										bool argTriFlg)
	{
		::fk_Material *pM;

		if(!argFileName || !argTime || !argPos) return false;
		pM = (!argMat) ? nullptr : argMat->pMat;

		int i;
		int timeSize = argTime->Length;
		vector<double> timeArray(timeSize);
		for(i = 0; i < timeSize; ++i) timeArray[i] = argTime[i];

		int posSize = argPos->Length;
		vector<::fk_Vector> posArray(posSize);
		for(i = 0; i < posSize; ++i) posArray[i] = argPos[i];

		return GetP()->writeVRMLFile(marshal_as<string>(argFileName),
									 &timeArray, &posArray, pM, argTriFlg);
	}

	bool fk_IndexFaceSet::WriteVRMLFile(String^ argFileName, cli::array<double>^ argTime,
										cli::array<fk_Vector^>^ argPos, fk_Material^ argMat)
	{
		return WriteVRMLFile(argFileName, argTime, argPos, argMat, false);
	}

	bool fk_IndexFaceSet::WriteVRMLFile(String^ argFileName, cli::array<double>^ argTime,
										cli::array<fk_Vector^>^ argPos)
	{
		return WriteVRMLFile(argFileName, argTime, argPos, nullptr, false);
	}

	bool fk_IndexFaceSet::WriteSTLFile(String ^argFileName)
	{
		return GetP()->writeSTLFile(marshal_as<string>(argFileName));
	}

	bool fk_IndexFaceSet::WriteDXFFile(String ^argFileName, bool argTriFlg)
	{
		return GetP()->writeDXFFile(marshal_as<string>(argFileName), argTriFlg);
	}

	bool fk_IndexFaceSet::WriteDXFFile(String ^argFileName)
	{
		return GetP()->writeDXFFile(marshal_as<string>(argFileName), false);
	}

	bool fk_IndexFaceSet::WriteMQOFile(String^ argFileName)
	{
		return GetP()->writeMQOFile(marshal_as<string>(argFileName));
	}

	fk_Vector^ fk_IndexFaceSet::GetPosVec(int argVID)
	{
		return gcnew fk_Vector(GetP()->getPosVec(argVID));
	}

	cli::array<int>^ fk_IndexFaceSet::GetFaceData(int argFID)
	{
		int i;
		vector<int>	tmpA = GetP()->getFaceData(argFID);
		cli::array<int>^ retA = gcnew cli::array<int>(tmpA.size());
		for(i = 0; i < int(tmpA.size()); ++i) retA[i] = tmpA[i];
		return retA;
	}

	int	fk_IndexFaceSet::GetFaceData(int argFID, int argVNum)
	{
		return GetP()->getFaceData(argFID, argVNum);
	}

	fk_Vector^ fk_IndexFaceSet::GetPNorm(int argFID, int argOrder)
	{
		return gcnew fk_Vector(GetP()->getPNorm(argFID, argOrder));
	}

	fk_Vector^ fk_IndexFaceSet::GetPNorm(int argFID)
	{
		return GetPNorm(argFID, 0);
	}

	fk_Vector^ fk_IndexFaceSet::GetVNorm(int argVID, int argOrder)
	{
		return gcnew fk_Vector(GetP()->getVNorm(argVID, argOrder));
	}

	fk_Vector^ fk_IndexFaceSet::GetVNorm(int argVID)
	{
		return GetVNorm(argVID, 0);
	}

	int fk_IndexFaceSet::GetElemMaterialID(int argFID)
	{
		return GetP()->getElemMaterialID(argFID);
	}

	bool fk_IndexFaceSet::MoveVPosition(int argVID, fk_Vector^ argP, int argOrder)
	{
		if(!argP) return false;
		return GetP()->moveVPosition(argVID, argP, argOrder);
	}

	bool fk_IndexFaceSet::MoveVPosition(int argVID, fk_Vector^ argP)
	{
		return MoveVPosition(argVID, argP, 0);
	}

	bool fk_IndexFaceSet::MoveVPosition(int argVID, double x, double y, double z, int argOrder)
	{
		return GetP()->moveVPosition(argVID, x, y, z, argOrder);
	}

	bool fk_IndexFaceSet::MoveVPosition(int argVID, double x, double y, double z)
	{
		::fk_IndexFaceSet *p = (::fk_IndexFaceSet *)(pBase);
		return GetP()->moveVPosition(argVID, x, y, z, 0);
	}

	bool fk_IndexFaceSet::MoveVPosition(int argVID, cli::array<double>^ argArray, int argOrder)
	{
		if(!argArray) return false;
		pin_ptr<double> pD = &argArray[0];
		return GetP()->moveVPosition(argVID, pD, argOrder);
	}

	bool fk_IndexFaceSet::MoveVPosition(int argVID, cli::array<double>^ argArray)
	{
		return MoveVPosition(argVID, argArray, 0);
	}

	void fk_IndexFaceSet::MakeIFSet(int argFNum, int argPNum, cli::array<int>^ argIFSet,
				   int argVNum, cli::array<fk_Vector^>^ argPosArray, int argOrder)
	{
		if(!argIFSet || !argPosArray) return;

		pin_ptr<int> pIF = &argIFSet[0];
		int vSize = argPosArray->Length;
		vector<::fk_Vector> tmpV(vSize);
		for(int i = 0; i < vSize; i++) {
			tmpV[i] = argPosArray[i];
		}
		GetP()->makeIFSet(argFNum, argPNum, pIF, argVNum, &tmpV[0], argOrder);
	}

	void fk_IndexFaceSet::MakeIFSet(int argFNum, int argPNum, cli::array<int>^ argIFSet,
									int argVNum, cli::array<fk_Vector^>^ argPosArray)
	{
		MakeIFSet(argFNum, argPNum, argIFSet, argVNum, argPosArray, 0);
	}

	bool fk_IndexFaceSet::SetPNorm(int argFID, fk_Vector^ argN, int argOrder)
	{
		if(!argN) return false;
		return GetP()->setPNorm(argFID, argN, argOrder);
	}

	bool fk_IndexFaceSet::SetPNorm(int argFID, fk_Vector^ argN)
	{
		if(!argN) return false;
		return GetP()->setPNorm(argFID, argN, 0);
	}

	bool fk_IndexFaceSet::SetVNorm(int argVID, fk_Vector^ argN, int argOrder)
	{
		if(!argN) return false;
		return GetP()->setVNorm(argVID, argN, argOrder);
	}

	bool fk_IndexFaceSet::SetVNorm(int argVID, fk_Vector^ argN)
	{
		if(!argN) return false;
		return GetP()->setVNorm(argVID, argN, 0);
	}

	bool fk_IndexFaceSet::SetElemMaterialID(int argFID, int argMID)
	{
		return GetP()->setElemMaterialID(argFID, argMID);
	}

	void fk_IndexFaceSet::Flush(void)
	{
		return GetP()->flush();
	}

	void fk_IndexFaceSet::MakeBlock(double argX, double argY, double argZ)
	{
		GetP()->makeBlock(argX, argY, argZ);
	}

	void fk_IndexFaceSet::SetBlockSize(double argX, double argY, double argZ)
	{
		GetP()->setBlockSize(argX, argY, argZ);
	}

	void fk_IndexFaceSet::SetBlockSize(double argLength, fk_Axis argAxis)
	{
		GetP()->setBlockSize(argLength, fk_Vector::GetAxis(argAxis));
	}

	void fk_IndexFaceSet::SetBlockScale(double argScale)
	{
		GetP()->setBlockScale(argScale);
	}

	void fk_IndexFaceSet::SetBlockScale(double argScale, fk_Axis argAxis)
	{
		GetP()->setBlockScale(argScale, fk_Vector::GetAxis(argAxis));
	}

	void fk_IndexFaceSet::SetBlockScale(double argX, double argY, double argZ)
	{
		GetP()->setBlockScale(argX, argY, argZ);
	}

	void fk_IndexFaceSet::MakeCircle(int argDiv, double argRad)
	{
		GetP()->makeCircle(argDiv, argRad);
	}

	void fk_IndexFaceSet::SetCircleRadius(double argRad)
	{
		GetP()->setCircleRadius(argRad);
	}

	void fk_IndexFaceSet::SetCircleDivide(int argDiv)
	{
		GetP()->setCircleDivide(argDiv);
	}

	void fk_IndexFaceSet::SetCircleScale(double argScale)
	{
		GetP()->setCircleScale(argScale);
	}

	void fk_IndexFaceSet::MakeSphere(int argDiv, double argRad)
	{
		GetP()->makeSphere(argDiv, argRad);
	}

	void fk_IndexFaceSet::SetSphereRadius(double argRad)
	{
		GetP()->setSphereRadius(argRad);
	}

	void fk_IndexFaceSet::SetSphereDivide(int argDiv)
	{
		GetP()->setSphereDivide(argDiv);
	}

	void fk_IndexFaceSet::SetSphereScale(double argScale)
	{
		GetP()->setSphereScale(argScale);
	}

	void fk_IndexFaceSet::MakePrism(int argDiv, double argTop,
									double argBottom, double argHeight)
	{
		GetP()->makePrism(argDiv, argTop, argBottom, argHeight);
	}

	void fk_IndexFaceSet::SetPrismDivide(int argDiv)
	{
		GetP()->setPrismDivide(argDiv);
	}

	void fk_IndexFaceSet::SetPrismTopRadius(double argTop)
	{
		GetP()->setPrismTopRadius(argTop);
	}

	void fk_IndexFaceSet::SetPrismBottomRadius(double argBottom)
	{
		GetP()->setPrismBottomRadius(argBottom);
	}

	void fk_IndexFaceSet::SetPrismHeight(double argHeight)
	{
		GetP()->setPrismHeight(argHeight);
	}

	void fk_IndexFaceSet::MakeCone(int argDiv, double argRad, double argHeight)
	{
		GetP()->makeCone(argDiv, argRad, argHeight);
	}

	void fk_IndexFaceSet::SetConeDivide(int argDiv)
	{
		GetP()->setConeDivide(argDiv);
	}

	void fk_IndexFaceSet::SetConeRadius(double argRad)
	{
		GetP()->setConeRadius(argRad);
	}

	void fk_IndexFaceSet::SetConeHeight(double argHeight)
	{
		GetP()->setConeHeight(argHeight);
	}

	void fk_IndexFaceSet::MakeCapsule(int argDiv, double argLen, double argRad)
	{
		GetP()->makeCapsule(argDiv, argLen, argRad);
	}

	void fk_IndexFaceSet::SetCapsuleSize(double argLen, double argRad)
	{
		GetP()->setCapsuleSize(argLen, argRad);
	}

	void fk_IndexFaceSet::PutSolid(fk_Solid^ argSolid)
	{
		if(!argSolid) return;
		GetP()->putSolid(argSolid->GetP());
	}
}
