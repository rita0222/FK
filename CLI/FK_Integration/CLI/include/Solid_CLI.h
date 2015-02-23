// Solid_CLI.h

#pragma once

#include <FK/Solid.h>
#include "SolidBase_CLI.h"

namespace FK_CLI
{
	public ref class fk_Solid : fk_SolidBase {
	internal:
		::fk_Solid * GetP(void);

	public:
		fk_Solid();
		fk_Solid(bool argNewFlg);
		~fk_Solid();
		!fk_Solid();

		void AllClear(bool matFlg);
		void AllClear(void);
		bool IsEmpty(void);
		void CloneShape(fk_Solid^ solid);
		bool CompareShape(fk_Solid^ solid);
		bool ReadSMFFile(String^ fileName);
		bool ReadSRFFile(String^ fileName);
		bool ReadVRMLFile(String^ fileName, bool materialFlg, bool solidFlg);
		bool ReadVRMLFile(String^ fileName, bool materialFlg);
		bool ReadVRMLFile(String^ fileName);
		bool ReadSTLFile(String^ fileName, bool solidFlg, double tolerance);
		bool ReadSTLFile(String^ fileName, bool solidFlg);
		bool ReadSTLFile(String^ fileName);
		bool ReadHRCFile(String^ fileName);
		bool ReadRDSFile(String^ fileName, bool solidFlg);
		bool ReadRDSFile(String^ fileName);
		bool ReadDXFFile(String^ fileName, bool solidFlg);
		bool ReadDXFFile(String^ fileName);
		bool ReadMQOFile(String^ fileName, String^ objName,
						 bool solidFlg, bool contFlg, bool materialFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, bool solidFlg, bool contFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, bool solidFlg);
		bool ReadMQOFile(String^ fileName, String^ objName);
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID,
						 bool solidFlg, bool contFlg, bool materialFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID,
						 bool solidFlg, bool contFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID, bool solidFlg);
		bool ReadMQOFile(String^ fileName, String^ objName, int materialID);
		bool ReadD3DXFile(String^ fileName, String^ objName, bool solidFlg);
		bool ReadD3DXFile(String^ fileName, String^ objName);
		bool ReadD3DXFile(String^ fileName, String^ objName, int materialID, bool solidFlg);
		bool ReadD3DXFile(String^ fileName, String^ objName, int materialID);
		bool WriteVRMLFile(String^ fileName, fk_Material^ material, bool triFlg);
		bool WriteVRMLFile(String^ fileName, fk_Material^ material);
		bool WriteVRMLFile(String^ fileName);
		bool WriteVRMLFile(String^ fileName, array<double>^ time, array<fk_Vector^>^ pos,
						   fk_Material^ material, bool triFlg);
		bool WriteVRMLFile(String^ fileName, array<double>^ time, array<fk_Vector^>^ pos,
						   fk_Material^ material);
		bool WriteVRMLFile(String^ fileName, array<double>^ time, array<fk_Vector^>^ pos);
		bool WriteSTLFile(String^ fileName);
		bool WriteDXFFile(String^ fileName, bool triFlg);
		bool WriteDXFFile(String^ fileName);
		bool WriteMQOFile(String^ fileName);
	};
}
