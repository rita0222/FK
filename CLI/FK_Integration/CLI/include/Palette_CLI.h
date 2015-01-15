// Palette_CLI.h

#pragma once

#include <FK/Palette.h>
#include "Material_CLI.h"

namespace FK_CLI
{
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
			if(pPalette == nullptr) return;
			if(dFlg == true) delete GetP();
			pPalette = nullptr;
		}

		void clearMaterial(void);
		void setObjMaterialID(int ID);
		void pushPalette(fk_Material^ material);
		void setPalette(fk_Material^ material, int ID);
		int getObjMaterialID(void);
		int getPaletteSize(void);
		fk_Material^ getMaterial(int ID);
		array<fk_Material^>^ getMaterialVector(void);
	};
}
