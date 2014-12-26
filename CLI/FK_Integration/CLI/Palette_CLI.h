// Palette_CLI.h

#pragma once

#include <FK/Palette.h>
#include "Material_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

	public enum class fk_MaterialMode : int {
		NONE = 0,
		CHILD = 1,
		PARENT = 2
	};

	public ref class fk_Palette {
	internal:
		::fk_Palette *pPalette;
		bool dFlg;
		
		::fk_Palette * GetP(void)
		{
			return pPalette;
		}

	public:
		fk_Palette::fk_Palette() : dFlg(true)
		{
			pPalette = new ::fk_Palette();
		}

		fk_Palette::fk_Palette(bool argNewFlg) : dFlg(argNewFlg)
		{
			if(argNewFlg == true) pPalette = new ::fk_Palette();
		}

		fk_Palette::~fk_Palette()
		{
			this->!fk_Palette();
		}

		fk_Palette::!fk_Palette()
		{
			if(dFlg == true) delete pPalette;
			pPalette = NULL;
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

			GetP()->pushPalette(argMat->pMat);
		}

		void setPalette(fk_Material^ argMat, int argID)
		{
			if(!argMat) return;
			GetP()->setPalette(argMat->pMat, argID);
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
			*M->pMat = *(GetP()->getMaterial(argID));
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
