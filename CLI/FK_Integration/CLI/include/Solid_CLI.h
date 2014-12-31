// Solid_CLI.h

#pragma once

#include <FK/Solid.h>
#include "SolidBase_CLI.h"

namespace FK_CLI
{
	public ref class fk_Solid : fk_SolidBase {
	internal:
		::fk_Solid * GetP(void)
		{
			return (::fk_Solid *)(pBase);
		}

	public:
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
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void allClear(bool matFlg);
		void allClear(void);
		bool isEmpty(void);
		void cloneShape(fk_Solid^ solid);
		bool compareShape(fk_Solid^ solid);
		bool readSMFFile(String^ fileName);
		bool readSRFFile(String^ fileName);
		bool readVRMLFile(String^ fileName, bool materialFlg, bool solidFlg);
		bool readVRMLFile(String^ fileName, bool materialFlg);
		bool readVRMLFile(String^ fileName);
		bool readSTLFile(String^ fileName, bool solidFlg, double tolerance);
		bool readSTLFile(String^ fileName, bool solidFlg);
		bool readSTLFile(String^ fileName);
		bool readHRCFile(String^ fileName);
		bool readRDSFile(String^ fileName, bool solidFlg);
		bool readRDSFile(String^ fileName);
		bool readDXFFile(String^ fileName, bool solidFlg);
		bool readDXFFile(String^ fileName);
		bool readMQOFile(String^ fileName, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);
		bool readMQOFile(String^ fileName, String^ objName, bool solidFlg, bool contFlg);
		bool readMQOFile(String^ fileName, String^ objName, bool solidFlg);
		bool readMQOFile(String^ fileName, String^ objName);
		bool readMQOFile(String^ fileName, String^ objName, int materialID,
						 bool solidFlg, bool contFlg, bool materialFlg);
		bool readMQOFile(String^ fileName, String^ objName, int materialID,
						 bool solidFlg, bool contFlg);
		bool readMQOFile(String^ fileName, String^ objName, int materialID, bool solidFlg);
		bool readMQOFile(String^ fileName, String^ objName, int materialID);
		bool readD3DXFile(String^ fileName, String^ objName, bool solidFlg);
		bool readD3DXFile(String^ fileName, String^ objName);
		bool readD3DXFile(String^ fileName, String^ objName, int materialID, bool solidFlg);
		bool readD3DXFile(String^ fileName, String^ objName, int materialID);
		bool writeVRMLFile(String^ fileName, fk_Material^ material, bool triFlg);
		bool writeVRMLFile(String^ fileName, fk_Material^ material);
		bool writeVRMLFile(String^ fileName);
		bool writeVRMLFile(String^ fileName, array<double>^ time, array<fk_Vector^>^ pos,
						   fk_Material^ material, bool triFlg);
		bool writeVRMLFile(String^ fileName, array<double>^ time, array<fk_Vector^>^ pos,
						   fk_Material^ material);
		bool writeVRMLFile(String^ fileName, array<double>^ time, array<fk_Vector^>^ pos);
		bool writeSTLFile(String^ fileName);
		bool writeDXFFile(String^ fileName, bool triFlg);
		bool writeDXFFile(String^ fileName);
		bool writeMQOFile(String^ fileName);
	};
}
