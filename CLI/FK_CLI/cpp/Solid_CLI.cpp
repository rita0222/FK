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
#include "Solid_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;
	using namespace System::Collections::Generic;
	
	::FK::fk_Solid * fk_Solid::GetP(void)
	{
		return (::FK::fk_Solid *)(pBase);
	}

	fk_Solid::fk_Solid() : fk_SolidBase(false)
	{
		pBase = new ::FK::fk_Solid();
	}

	fk_Solid::fk_Solid(bool argNewFlg) : fk_SolidBase(false)
	{
		if(argNewFlg == true) pBase = new ::FK::fk_Solid();
	}

	fk_Solid::~fk_Solid()
	{
		this->!fk_Solid();
	}

	fk_Solid::!fk_Solid()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_Solid::AllClear(bool argMatFlg)
	{
		GetP()->allClear(argMatFlg);
	}

	void fk_Solid::AllClear(void)
	{
		GetP()->allClear();
	}

	bool fk_Solid::IsEmpty(void)
	{
		return GetP()->isEmpty();
	}

	void fk_Solid::CloneShape(fk_Solid^ argSolid)
	{
		if(!argSolid) return;
		GetP()->cloneShape(argSolid->GetP());
	}

	bool fk_Solid::CompareShape(fk_Solid^ argSolid)
	{
		if(!argSolid) return false;
		return GetP()->compareShape(argSolid->GetP());
	}

	bool fk_Solid::ReadSMFFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readSMFFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::ReadSRFFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readSRFFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::ReadVRMLFile(String^ argFName, bool argMFlg, bool argSFlg)
	{
		if(!argFName) return false;
		return GetP()->readVRMLFile(marshal_as<string>(argFName), argMFlg, argSFlg);
	}

	bool fk_Solid::ReadVRMLFile(String^ argFName, bool argMFlg)
	{
		if(!argFName) return false;
		return GetP()->readVRMLFile(marshal_as<string>(argFName), argMFlg);
	}

	bool fk_Solid::ReadVRMLFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readVRMLFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::ReadSTLFile(String^ argFName, bool argSFlg, double argTolerance)
	{
		if(!argFName) return false;
		return GetP()->readSTLFile(marshal_as<string>(argFName), argSFlg, argTolerance);
	}

	bool fk_Solid::ReadSTLFile(String^ argFName, bool argSFlg)
	{
		if(!argFName) return false;
		return GetP()->readSTLFile(marshal_as<string>(argFName), argSFlg);		
	}

	bool fk_Solid::ReadSTLFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readSTLFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::ReadHRCFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readHRCFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::ReadRDSFile(String^ argFName, bool argSFlg)
	{
		if(!argFName) return false;
		return GetP()->readRDSFile(marshal_as<string>(argFName), argSFlg);
	}

	bool fk_Solid::ReadRDSFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readRDSFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::ReadDXFFile(String^ argFName, bool argSFlg)
	{
		if(!argFName) return false;
		return GetP()->readDXFFile(marshal_as<string>(argFName), argSFlg);
	}

	bool fk_Solid::ReadDXFFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readDXFFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::ReadMQOFile(String^ argFName, String^ argObjName,
							   bool argSFlg, bool argContFlg, bool argMFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName),
								   argSFlg, argContFlg, argMFlg);
	}

	bool fk_Solid::ReadMQOFile(String^ argFName, String^ argObjName,
							   bool argSFlg, bool argContFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName),
								   argSFlg, argContFlg);
	}

	bool fk_Solid::ReadMQOFile(String^ argFName, String^ argObjName, bool argSFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName),
								   argSFlg);
	}

	bool fk_Solid::ReadMQOFile(String^ argFName, String^ argObjName)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName));
	}

	bool fk_Solid::ReadMQOFile(String^ argFName, String^ argObjName, int argMID,
							   bool argSFlg, bool argContFlg, bool argMFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName), argMID,
								   argSFlg, argContFlg, argMFlg);
	}

	bool fk_Solid::ReadMQOFile(String^ argFName, String^ argObjName, int argMID,
							   bool argSFlg, bool argContFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName), argMID,
								   argSFlg, argContFlg);
	}

	bool fk_Solid::ReadMQOFile(String^ argFName, String^ argObjName, int argMID, bool argSFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName), argMID, argSFlg);
	}

	bool fk_Solid::ReadMQOFile(String^ argFName, String^ argObjName, int argMID)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName), argMID);
	}

	bool fk_Solid::ReadD3DXFile(String^ argFName, String^ argObjName, bool argSFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFName),
									marshal_as<string>(argObjName), argSFlg);
	}

	bool fk_Solid::ReadD3DXFile(String^ argFName, String^ argObjName)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFName),
									marshal_as<string>(argObjName));
	}

	bool fk_Solid::ReadD3DXFile(String^ argFName, String^ argObjName, int argMID, bool argSFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFName),
									marshal_as<string>(argObjName),
									argMID, argSFlg);
	}

	bool fk_Solid::ReadD3DXFile(String^ argFName, String^ argObjName, int argMID)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFName),
									marshal_as<string>(argObjName), argMID);
	}

	bool fk_Solid::WriteVRMLFile(String^ argFName, fk_Material^ argMat, bool triFlg)
	{
		if(!argFName || !argMat) return false;
		return GetP()->writeVRMLFile(marshal_as<string>(argFName),
									 argMat->GetP(), triFlg);
	}

	bool fk_Solid::WriteVRMLFile(String^ argFName, fk_Material^ argMat)
	{
		if(!argFName || !argMat) return false;
		return GetP()->writeVRMLFile(marshal_as<string>(argFName), argMat->GetP());
	}

	bool fk_Solid::WriteVRMLFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->writeVRMLFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::WriteVRMLFile(String^ argFName,
								 IEnumerable<double>^ argTime,
								 IEnumerable<fk_Vector^>^ argPos,
								 fk_Material^ argMat, bool triFlg)
	{
		if(!argFName || !argTime || !argPos || !argMat) return false;

		vector<double> timeArray;
		vector<::FK::fk_Vector> posArray;

		for each (double time in argTime) {
			timeArray.push_back(time);
		}

		for each (fk_Vector^ pos in argPos) {
			posArray.push_back(pos);
		}

		return GetP()->writeVRMLFile(marshal_as<string>(argFName),
									 &timeArray, &posArray, argMat->GetP(), triFlg);
	}

	bool fk_Solid::WriteVRMLFile(String^ argFName,
								 IEnumerable<double>^ argTime,
								 IEnumerable<fk_Vector^>^ argPos,
								 fk_Material^ argMat)
	{
		if(!argFName || !argTime || !argPos || !argMat) return false;
		vector<double> timeArray;
		vector<::FK::fk_Vector> posArray;

		for each (double time in argTime) {
			timeArray.push_back(time);
		}

		for each (fk_Vector^ pos in argPos) {
			posArray.push_back(pos);
		}

		return GetP()->writeVRMLFile(marshal_as<string>(argFName),
									 &timeArray, &posArray, argMat->GetP());
	}

	bool fk_Solid::WriteVRMLFile(String^ argFName,
								 IEnumerable<double>^ argTime,
								 IEnumerable<fk_Vector^>^ argPos)
	{
		if(!argFName || !argTime || !argPos) return false;
		vector<double> timeArray;
		vector<::FK::fk_Vector> posArray;

		for each (double time in argTime) {
			timeArray.push_back(time);
		}

		for each (fk_Vector^ pos in argPos) {
			posArray.push_back(pos);
		}

		return GetP()->writeVRMLFile(marshal_as<string>(argFName), &timeArray, &posArray);
	}

	bool fk_Solid::WriteSTLFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->writeSTLFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::WriteDXFFile(String^ argFName, bool triFlg)
	{
		if(!argFName) return false;
		return GetP()->writeDXFFile(marshal_as<string>(argFName), triFlg);
	}

	bool fk_Solid::WriteDXFFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->writeDXFFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::WriteMQOFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->writeMQOFile(marshal_as<string>(argFName));
	}
}

