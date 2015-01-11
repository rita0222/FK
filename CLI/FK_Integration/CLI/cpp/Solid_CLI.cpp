#include "Solid_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {

	using namespace std;
	using namespace msclr::interop;

	void fk_Solid::allClear(bool argMatFlg)
	{
		GetP()->allClear(argMatFlg);
	}

	void fk_Solid::allClear(void)
	{
		GetP()->allClear();
	}

	bool fk_Solid::isEmpty(void)
	{
		return GetP()->isEmpty();
	}

	void fk_Solid::cloneShape(fk_Solid^ argSolid)
	{
		if(!argSolid) return;
		GetP()->cloneShape(argSolid->GetP());
	}

	bool fk_Solid::compareShape(fk_Solid^ argSolid)
	{
		if(!argSolid) return false;
		return GetP()->compareShape(argSolid->GetP());
	}

	bool fk_Solid::readSMFFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readSMFFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::readSRFFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readSRFFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::readVRMLFile(String^ argFName, bool argMFlg, bool argSFlg)
	{
		if(!argFName) return false;
		return GetP()->readVRMLFile(marshal_as<string>(argFName), argMFlg, argSFlg);
	}

	bool fk_Solid::readVRMLFile(String^ argFName, bool argMFlg)
	{
		if(!argFName) return false;
		return GetP()->readVRMLFile(marshal_as<string>(argFName), argMFlg);
	}

	bool fk_Solid::readVRMLFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readVRMLFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::readSTLFile(String^ argFName, bool argSFlg, double argTolerance)
	{
		if(!argFName) return false;
		return GetP()->readSTLFile(marshal_as<string>(argFName), argSFlg, argTolerance);
	}

	bool fk_Solid::readSTLFile(String^ argFName, bool argSFlg)
	{
		if(!argFName) return false;
		return GetP()->readSTLFile(marshal_as<string>(argFName), argSFlg);		
	}

	bool fk_Solid::readSTLFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readSTLFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::readHRCFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readHRCFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::readRDSFile(String^ argFName, bool argSFlg)
	{
		if(!argFName) return false;
		return GetP()->readRDSFile(marshal_as<string>(argFName), argSFlg);
	}

	bool fk_Solid::readRDSFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readRDSFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::readDXFFile(String^ argFName, bool argSFlg)
	{
		if(!argFName) return false;
		return GetP()->readDXFFile(marshal_as<string>(argFName), argSFlg);
	}

	bool fk_Solid::readDXFFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->readDXFFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::readMQOFile(String^ argFName, String^ argObjName,
							   bool argSFlg, bool argContFlg, bool argMFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName),
								   argSFlg, argContFlg, argMFlg);
	}

	bool fk_Solid::readMQOFile(String^ argFName, String^ argObjName,
							   bool argSFlg, bool argContFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName),
								   argSFlg, argContFlg);
	}

	bool fk_Solid::readMQOFile(String^ argFName, String^ argObjName, bool argSFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName),
								   argSFlg);
	}

	bool fk_Solid::readMQOFile(String^ argFName, String^ argObjName)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName));
	}

	bool fk_Solid::readMQOFile(String^ argFName, String^ argObjName, int argMID,
							   bool argSFlg, bool argContFlg, bool argMFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName), argMID,
								   argSFlg, argContFlg, argMFlg);
	}

	bool fk_Solid::readMQOFile(String^ argFName, String^ argObjName, int argMID,
							   bool argSFlg, bool argContFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName), argMID,
								   argSFlg, argContFlg);
	}

	bool fk_Solid::readMQOFile(String^ argFName, String^ argObjName, int argMID, bool argSFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName), argMID, argSFlg);
	}

	bool fk_Solid::readMQOFile(String^ argFName, String^ argObjName, int argMID)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFName),
								   marshal_as<string>(argObjName), argMID);
	}

	bool fk_Solid::readD3DXFile(String^ argFName, String^ argObjName, bool argSFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFName),
									marshal_as<string>(argObjName), argSFlg);
	}

	bool fk_Solid::readD3DXFile(String^ argFName, String^ argObjName)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFName),
									marshal_as<string>(argObjName));
	}

	bool fk_Solid::readD3DXFile(String^ argFName, String^ argObjName, int argMID, bool argSFlg)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFName),
									marshal_as<string>(argObjName),
									argMID, argSFlg);
	}

	bool fk_Solid::readD3DXFile(String^ argFName, String^ argObjName, int argMID)
	{
		if(!argFName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFName),
									marshal_as<string>(argObjName), argMID);
	}

	bool fk_Solid::writeVRMLFile(String^ argFName, fk_Material^ argMat, bool triFlg)
	{
		if(!argFName || !argMat) return false;
		return GetP()->writeVRMLFile(marshal_as<string>(argFName),
									 argMat->GetP(), triFlg);
	}

	bool fk_Solid::writeVRMLFile(String^ argFName, fk_Material^ argMat)
	{
		if(!argFName || !argMat) return false;
		return GetP()->writeVRMLFile(marshal_as<string>(argFName), argMat->GetP());
	}

	bool fk_Solid::writeVRMLFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->writeVRMLFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::writeVRMLFile(String^ argFName, array<double>^ argTime,
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
			pos[i] = *argPos[i]->pVec;
		}
		return GetP()->writeVRMLFile(marshal_as<string>(argFName),
									 &time, &pos, argMat->GetP(), triFlg);
	}

	bool fk_Solid::writeVRMLFile(String^ argFName, array<double>^ argTime,
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
			pos[i] = *argPos[i]->pVec;
		}
		return GetP()->writeVRMLFile(marshal_as<string>(argFName),
									 &time, &pos, argMat->GetP());
	}

	bool fk_Solid::writeVRMLFile(String^ argFName, array<double>^ argTime, array<fk_Vector^>^ argPos)
	{
		int i;

		if(!argFName || !argTime || !argPos) return false;
		vector<double> time(argTime->Length);
		vector<::fk_Vector> pos(argPos->Length);

		for(i = 0; i < argTime->Length; ++i) {
			time[i] = argTime[i];
		}
		for(i = 0; i < argPos->Length; ++i) {
			pos[i] = *argPos[i]->pVec;
		}
		return GetP()->writeVRMLFile(marshal_as<string>(argFName), &time, &pos);
	}

	bool fk_Solid::writeSTLFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->writeSTLFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::writeDXFFile(String^ argFName, bool triFlg)
	{
		if(!argFName) return false;
		return GetP()->writeDXFFile(marshal_as<string>(argFName), triFlg);
	}

	bool fk_Solid::writeDXFFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->writeDXFFile(marshal_as<string>(argFName));
	}

	bool fk_Solid::writeMQOFile(String^ argFName)
	{
		if(!argFName) return false;
		return GetP()->writeMQOFile(marshal_as<string>(argFName));
	}
}
