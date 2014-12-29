#include "Palette_CLI.h"

namespace FK_CLI {

	
	void fk_Palette::clearMaterial(void)
	{
		GetP()->clearMaterial();
	}

	void fk_Palette::setObjMaterialID(int argID)
	{
		GetP()->setObjMaterialID(argID);
	}

	void fk_Palette::pushPalette(fk_Material^ argMat)
	{
		if(!argMat) return;

		GetP()->pushPalette(argMat->pMat);
	}

	void fk_Palette::setPalette(fk_Material^ argMat, int argID)
	{
		if(!argMat) return;
		GetP()->setPalette(argMat->pMat, argID);
	}

	int fk_Palette::getObjMaterialID(void)
	{
		return GetP()->getObjMaterialID();
	}

	int fk_Palette::getPaletteSize(void)
	{
		return GetP()->getPaletteSize();
	}

	fk_Material^ fk_Palette::getMaterial(int argID)
	{
		fk_Material^ M = gcnew fk_Material();
		*M->pMat = *(GetP()->getMaterial(argID));
		return M;
	}

	array<fk_Material^>^ fk_Palette::getMaterialVector(void)
	{
		int i;
		int size = GetP()->getPaletteSize();
		array<fk_Material^>^ matArray = gcnew array<fk_Material^>(size);

		for(i = 0; i < size; i++) {
			matArray[i] = getMaterial(i);
		}

		return matArray;
	}
}
