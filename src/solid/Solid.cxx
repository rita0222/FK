#include <FK/Solid.h>
#include <FK/DataBase.H>
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
using namespace FK;

fk_Solid::Member::Member(void)
{
	return;
}

fk_Solid::fk_Solid(void) : _m(make_unique<Member>())
{
	realType = fk_RealShapeType::SOLID;

	SetObjectType(fk_Type::SOLID);
	SetDataBase(&_m->SolidDB);
	//SetPaletteData(&localPal);
	return;
}

fk_Solid::~fk_Solid()
{
	return;
}

void fk_Solid::allClear(bool argMateFlg)
{
	_m->SolidDB.AllClear();
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
	_m->SolidDB.CloneData(&argS->_m->SolidDB);
	AllCacheMake();
	return;
}

bool fk_Solid::compareShape(fk_Solid *argS)
{
	return _m->SolidDB.Compare(&argS->_m->SolidDB);
}

bool fk_Solid::AllCheck(void)
{
	return _m->SolidDB.AllCheck();
}

bool fk_Solid::readSMFFile(string argFileName)
{
	unique_ptr<fk_SMFParser> smfParser(new fk_SMFParser());

	smfParser->SetMeshData(this);
	AllCacheClear();
	return smfParser->ReadSMFFile(argFileName);
}

bool fk_Solid::readSRFFile(string argFileName)
{
	unique_ptr<fk_SRFParser> srfParser(new fk_SRFParser());

	srfParser->SetMeshData(this);
	AllCacheClear();
	return srfParser->ReadSRFFile(argFileName);
}

bool fk_Solid::readSTLFile(string argFileName,
						   bool argSolidFlag, double argEPS)
{
	unique_ptr<fk_STLParser> stlParser(new fk_STLParser());

	stlParser->SetMeshData(this);
	AllCacheClear();
	return stlParser->ReadSTLFile(argFileName, argSolidFlag, argEPS);
}

bool fk_Solid::readHRCFile(string argFileName)
{
	unique_ptr<fk_HRCParser> hrcParser(new fk_HRCParser());

	hrcParser->SetMeshData(this);
	AllCacheClear();
	return hrcParser->ReadHRCFile(argFileName);
}

bool fk_Solid::readRDSFile(string argFileName, bool argSolidFlg)
{
	unique_ptr<fk_RDSParser> rdsParser(new fk_RDSParser());

	rdsParser->SetMeshData(this);
	AllCacheClear();
	return rdsParser->ReadRDSFile(argFileName, argSolidFlg);
}

bool fk_Solid::readDXFFile(string argFileName, bool argSolidFlg)
{
	unique_ptr<fk_DXFParser> dxfParser(new fk_DXFParser());

	dxfParser->SetMeshData(this);
	AllCacheClear();
	return dxfParser->ReadDXFFile(argFileName, argSolidFlg);
}

bool fk_Solid::readMQOFile(string argFileName,
						   string argObjName,
						   bool argSolidFlg,
						   bool argContFlg,
						   bool argMatFlg)
{
	return readMQOFile(argFileName, argObjName, -1, argSolidFlg, argContFlg, argMatFlg);
}

bool fk_Solid::readMQOFile(string argFileName, string argObjName,
						   int argMateID, bool argSolidFlg,
						   bool argContFlg, bool argMatFlg)
{
	unique_ptr<fk_MQOParser> mqoParser(new fk_MQOParser());

	mqoParser->SetMeshData(this);
	AllCacheClear();
	mqoParser->SetContMode(argContFlg);
	mqoParser->SetMaterialMode(argMatFlg);
	return mqoParser->ReadMQOFile(argFileName, argObjName, argMateID, argSolidFlg);
}

bool fk_Solid::readD3DXFile(string argFileName,
							string argObjName, bool argSolidFlg)
{
	return readD3DXFile(argFileName, argObjName, -1, argSolidFlg);
}

bool fk_Solid::readD3DXFile(string argFileName, string argObjName,
							int argTexID, bool argSolidFlg)
{
	unique_ptr<fk_D3DXParser> d3dxParser(new fk_D3DXParser());
	bool animFlg;

	d3dxParser->SetMeshData(this);
	AllCacheClear();
	return d3dxParser->ReadD3DXFile(argFileName, argObjName, argTexID, argSolidFlg, &animFlg);
}

bool fk_Solid::readVRMLFile(string argFileName,
							bool argMaterialFlag, bool argSolidFlag)
{
	unique_ptr<fk_VRMLParser> vrmlParser(new fk_VRMLParser());

	vrmlParser->SetMeshData(this);
	AllCacheClear();
	return vrmlParser->ReadVRMLFile(argFileName, argMaterialFlag, argSolidFlag);
}

bool fk_Solid::writeVRMLFile(string argFileName, fk_Material *argMaterial,
							 bool triFlag)
{
	unique_ptr<fk_VRMLOut> vrmlOut(new fk_VRMLOut(this));
	return vrmlOut->WriteVRMLFile(argFileName, argMaterial, triFlag);
}

bool fk_Solid::writeVRMLFile(string argFileName,
							 vector<double> *argTime,
							 vector<fk_Vector> *argPos,
							 fk_Material *argMaterial, bool triFlag)
{
	unique_ptr<fk_VRMLOut> vrmlOut(new fk_VRMLOut(this));

	return vrmlOut->WriteVRMLFile(argFileName, argTime, argPos, argMaterial, triFlag);
}

bool fk_Solid::writeSTLFile(string argFileName)
{
	unique_ptr<fk_STLOut> stlOut(new fk_STLOut(this));
	return stlOut->WriteSTLFile(argFileName);
}

bool fk_Solid::writeDXFFile(string argFileName, bool argTriFlg)
{
	unique_ptr<fk_DXFOut> dxfOut(new fk_DXFOut(this));
	return dxfOut->WriteDXFFile(argFileName, argTriFlg);
}

bool fk_Solid::writeMQOFile(string argFileName)
{
	unique_ptr<fk_MQOOut> mqoOut(new fk_MQOOut(this));
	return mqoOut->WriteMQOFile(argFileName);
}

void fk_Solid::PrintMat(string argTag)
{
	FK_UNUSED(argTag);
	//localPal.Print(0, argTag);
	return;
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
