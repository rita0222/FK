/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#include <FK/Solid.h>
#include <FK/DataBase.H>
#include <FK/FileInput.H>
#include <FK/FileOutput.H>
#include <FK/SMFParser.H>
#include <FK/SRFParser.H>
#include <FK/STLParser.H>
#include <FK/HRCParser.H>
#include <FK/RDSParser.H>
#include <FK/DXFParser.H>
#include <FK/VRMLParser.H>
#include <FK/MQOParser.H>
#include <FK/D3DXParser.H>
#include <FK/VRMLOut.H>
#include <FK/STLOut.H>
#include <FK/DXFOut.H>
#include <FK/MQOOut.H>

using namespace std;

fk_Solid::fk_Solid(void)
{
	SolidDB = new fk_DataBase;

	SetObjectType(FK_SOLID);
	SetDataBase(SolidDB);
	SetPaletteData(&localPal);
	return;
}

fk_Solid::~fk_Solid()
{
	delete SolidDB;

	return;
}

void fk_Solid::allClear(bool argMateFlg)
{
	SolidDB->AllClear();
	AttrInit();
	if(argMateFlg == true) {
		clearMaterial();
	}
	AllCacheClear();

	return;
}

bool fk_Solid::isEmpty(void)
{
	return (getVNum() == 0 ? true : false);
}

void fk_Solid::cloneShape(fk_Solid *argS)
{
	AllCacheClear();
	SolidDB->CloneData(argS->SolidDB);
	AllCacheMake();
	return;
}

bool fk_Solid::compareShape(fk_Solid *argS)
{
	return SolidDB->Compare(argS->SolidDB);
}

bool fk_Solid::AllCheck(void)
{
	return SolidDB->AllCheck();
}

bool fk_Solid::readSMFFile(string argFileName)
{
	fk_SMFParser	*smfParser = new fk_SMFParser();
	bool			retFlg;

	smfParser->SetMeshData(this);
	AllCacheClear();
	retFlg = smfParser->ReadSMFFile(argFileName);
	delete smfParser;
	return retFlg;
}

bool fk_Solid::readSRFFile(string argFileName)
{
	fk_SRFParser	*srfParser = new fk_SRFParser();
	bool			retFlg;

	srfParser->SetMeshData(this);
	AllCacheClear();
	retFlg = srfParser->ReadSRFFile(argFileName);
	delete srfParser;
	return retFlg;
}

bool fk_Solid::readSTLFile(string argFileName,
						   bool argSolidFlag, double argEPS)
{
	fk_STLParser	*stlParser = new fk_STLParser();
	bool			retFlg;

	stlParser->SetMeshData(this);
	AllCacheClear();
	retFlg = stlParser->ReadSTLFile(argFileName, argSolidFlag, argEPS);
	delete stlParser;
	return retFlg;
}

bool fk_Solid::readHRCFile(string argFileName)
{
	fk_HRCParser	*hrcParser = new fk_HRCParser();
	bool			retFlg;

	hrcParser->SetMeshData(this);
	AllCacheClear();
	retFlg = hrcParser->ReadHRCFile(argFileName);
	delete hrcParser;
	return retFlg;
}

bool fk_Solid::readRDSFile(string argFileName, bool argSolidFlg)
{
	fk_RDSParser	*rdsParser = new fk_RDSParser();
	bool			retFlg;

	rdsParser->SetMeshData(this);
	AllCacheClear();
	retFlg = rdsParser->ReadRDSFile(argFileName, argSolidFlg);
	delete rdsParser;
	return retFlg;
}

bool fk_Solid::readDXFFile(string argFileName, bool argSolidFlg)
{
	fk_DXFParser	*dxfParser = new fk_DXFParser();
	bool			retFlg;

	dxfParser->SetMeshData(this);
	AllCacheClear();
	retFlg = dxfParser->ReadDXFFile(argFileName, argSolidFlg);
	delete dxfParser;
	return retFlg;
}

bool fk_Solid::readMQOFile(string argFileName,
						   string argObjName,
						   bool argSolidFlg,
						   bool argContFlg,
						   bool argMatFlg)
{
	return readMQOFile(argFileName, argObjName, -1, argSolidFlg,
					   argContFlg, argMatFlg);
}

bool fk_Solid::readMQOFile(string argFileName, string argObjName,
						   int argMateID, bool argSolidFlg,
						   bool argContFlg, bool argMatFlg)
{
	fk_MQOParser	*mqoParser = new fk_MQOParser();
	bool			retFlg;

	mqoParser->SetMeshData(this);
	AllCacheClear();
	mqoParser->SetContMode(argContFlg);
	mqoParser->SetMaterialMode(argMatFlg);
	retFlg = mqoParser->ReadMQOFile(argFileName, argObjName,
									argMateID, argSolidFlg);
	delete mqoParser;
	return retFlg;
}

bool fk_Solid::readD3DXFile(string argFileName,
							string argObjName, bool argSolidFlg)
{
	return readD3DXFile(argFileName, argObjName, -1, argSolidFlg);
}

bool fk_Solid::readD3DXFile(string argFileName, string argObjName,
							int argTexID, bool argSolidFlg)
{
	fk_D3DXParser	*d3dxParser = new fk_D3DXParser();
	bool			retFlg;
	bool			animFlg;

	d3dxParser->SetMeshData(this);
	AllCacheClear();
	retFlg = d3dxParser->ReadD3DXFile(argFileName, argObjName,
									  argTexID, argSolidFlg, &animFlg);
	delete d3dxParser;
	return retFlg;
}

bool fk_Solid::readVRMLFile(string argFileName,
							bool argMaterialFlag, bool argSolidFlag)
{
	fk_VRMLParser	*vrmlParser = new fk_VRMLParser();
	bool			retFlg;

	vrmlParser->SetMeshData(this);
	AllCacheClear();
	retFlg = vrmlParser->ReadVRMLFile(argFileName, argMaterialFlag,
									  argSolidFlag);
	delete vrmlParser;
	return retFlg;
}

bool fk_Solid::writeVRMLFile(string argFileName, fk_Material *argMaterial,
							 bool triFlag)
{
	fk_VRMLOut		*vrmlOut = new fk_VRMLOut(this);
	bool			retFlg;

	retFlg = vrmlOut->WriteVRMLFile(argFileName, argMaterial, triFlag);
	delete vrmlOut;
	return retFlg;
}

bool fk_Solid::writeVRMLFile(string argFileName,
							 vector<double> *argTime,
							 vector<fk_Vector> *argPos,
							 fk_Material *argMaterial, bool triFlag)
{
	fk_VRMLOut		*vrmlOut = new fk_VRMLOut(this);
	bool			retFlg;

	retFlg = vrmlOut->WriteVRMLFile(argFileName, argTime, argPos,
									argMaterial, triFlag);
	delete vrmlOut;
	return retFlg;
}

bool fk_Solid::writeSTLFile(string argFileName)
{
	fk_STLOut		*stlOut = new fk_STLOut(this);
	bool			retFlg;

	retFlg = stlOut->WriteSTLFile(argFileName);
	delete stlOut;
	return retFlg;
}

bool fk_Solid::writeDXFFile(string argFileName, bool argTriFlg)
{
	fk_DXFOut		*dxfOut = new fk_DXFOut(this);
	bool			retFlg;

	retFlg = dxfOut->WriteDXFFile(argFileName, argTriFlg);
	delete dxfOut;
	return retFlg;
}

bool fk_Solid::writeMQOFile(string argFileName)
{
	fk_MQOOut		*mqoOut = new fk_MQOOut(this);
	bool			retFlg;

	retFlg = mqoOut->WriteMQOFile(argFileName);
	delete mqoOut;
	return retFlg;
}

bool fk_Solid::writeData(string argFileName, fk_DataFormatMode argMode)
{
	fk_FileOutput	fileOutput;

	fileOutput.SetDataBase(SolidDB);
	return(fileOutput.PutShapeData(argFileName, argMode));
}

bool fk_Solid::readData(string argFileName, bool argSizeMode)
{
	fk_FileInput	fileInput;

	fileInput.SetDataBase(SolidDB);
	fileInput.SetSizeMode(argSizeMode);
	AllCacheClear();
	if(fileInput.GetShapeData(argFileName) == false) {
		SolidDB->AllClear();
		return false;
	}

	return true;
}

void fk_Solid::PrintMat(string argTag)
{
	localPal.Print(0, argTag);
	return;
}

