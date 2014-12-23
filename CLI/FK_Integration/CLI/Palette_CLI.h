// Palette_CLI.h

#pragma once

#include <FK/Palette.h>
#include "Material_CLI.h"

using namespace std;
using namespace System;

namespace FK_CLI
{
	public enum class fk_MaterialMode : int {
		NONE = 0,
		CHILD = 1,
		PARENT = 2
	};

	public ref class fk_Palette : fk_BaseObject {
	internal:
		::fk_Palette * GetP(void)
		{
			return reinterpret_cast<::fk_Palette *>(this->pBase);
		}

	public:
		fk_Palette::fk_Palette() : fk_BaseObject(false)
		{
			::fk_Palette *p = new ::fk_Palette();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Palette::fk_Palette(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				::fk_Palette *p = new ::fk_Palette();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_Palette::~fk_Palette()
		{
			this->!fk_Palette();
		}

		fk_Palette::!fk_Palette()
		{
			if(dFlg == true) delete this->pBase;
			this->pBase = NULL;
		}

		void clearMaterial(void)
		{
			GetP()->clearMaterial();
		}

		void setObjMaterialID(int argID)
		{
			GetP()->setObjMaterialID(argID);
		}

		void pushPalette(fk_Material^ argMat)
		{
			if(!argMat) return;

			::fk_Material *pM = reinterpret_cast<::fk_Material *>(argMat->pBase);
			GetP()->pushPalette(pM);
		}

		void setPalette(fk_Material^ argMat, int argID)
		{
			if(!argMat) return;
			::fk_Material *pM = reinterpret_cast<::fk_Material *>(argMat->pBase);
			GetP()->setPalette(pM, argID);
		}

		int getObjMaterialID(void)
		{
			return GetP()->getObjMaterialID();
		}

		int getPaletteSize(void)
		{
			return GetP()->getPaletteSize();
		}

		fk_Material^ getMaterial(int argID)
		{
			fk_Material^ M = gcnew fk_Material();
			::fk_Material *pM = reinterpret_cast<::fk_Material *>(M->pBase);
			*pM = *(GetP()->getMaterial(argID));
			return M;
		}

		array<fk_Material^>^ getMaterialVector(void)
		{
			int i;
			int size = GetP()->getPaletteSize();
			array<fk_Material^>^ matArray = gcnew array<fk_Material^>(size);

			for(i = 0; i < size; i++) {
				matArray[i] = getMaterial(i);
			}

			return matArray;
		}
	};
}
