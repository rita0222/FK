#include "Solid_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;

	::fk_Solid * fk_Solid::GetP(void)
	{
		return (::fk_Solid *)(pBase);
	}

	fk_Solid::fk_Solid() : fk_SolidBase(false)
	{
		pBase = new ::fk_Solid();
	}

	fk_Solid::fk_Solid(bool argNewFlg) : fk_SolidBase(false)
	{
		if(argNewFlg == true) pBase = new ::fk_Solid();
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

	bool fk_Solid::WriteVRMLFile(String^ argFName, array<double>^ argTime,
								 array<fk_Vector^>^ argPos,
								 fk_Material^ argMat, bool triFlg)
	{
		int i;

		if(!argFName || !argTime || !argPos || !argMat) return false;
		vector<double> time(argTime->Length);
		vector<::fk_Vector> pos(argPos->Length);

		for(i = 0; i < argTime->Length; ++i) {
			time[i] = argTime[i];
		}
		for(i = 0; i < argPos->Length; ++i) {
			pos[i].set(argPos[i]->x_, argPos[i]->y_, argPos[i]->z_);
		}
		return GetP()->writeVRMLFile(marshal_as<string>(argFName),
									 &time, &pos, argMat->GetP(), triFlg);
	}

	bool fk_Solid::WriteVRMLFile(String^ argFName, array<double>^ argTime,
								 array<fk_Vector^>^ argPos, fk_Material^ argMat)
	{
		int i;

		if(!argFName || !argTime || !argPos || !argMat) return false;
		vector<double> time(argTime->Length);
		vector<::fk_Vector> pos(argPos->Length);

		for(i = 0; i < argTime->Length; ++i) {
			time[i] = argTime[i];
		}
		for(i = 0; i < argPos->Length; ++i) {
			pos[i].set(argPos[i]->x_, argPos[i]->y_, argPos[i]->z_);
		}
		return GetP()->writeVRMLFile(marshal_as<string>(argFName),
									 &time, &pos, argMat->GetP());
	}

	bool fk_Solid::WriteVRMLFile(String^ argFName, array<double>^ argTime, array<fk_Vector^>^ argPos)
	{
		int i;

		if(!argFName || !argTime || !argPos) return false;
		vector<double> time(argTime->Length);
		vector<::fk_Vector> pos(argPos->Length);

		for(i = 0; i < argTime->Length; ++i) {
			time[i] = argTime[i];
		}
		for(i = 0; i < argPos->Length; ++i) {
			pos[i].set(argPos[i]->x_, argPos[i]->y_, argPos[i]->z_);
		}
		return GetP()->writeVRMLFile(marshal_as<string>(argFName), &time, &pos);
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
