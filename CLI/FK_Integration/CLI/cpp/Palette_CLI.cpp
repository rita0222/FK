#include "Palette_CLI.h"

namespace FK_CLI {

	::fk_Palette * fk_Palette::GetP(void)
	{
		return pPalette;
	}
	
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

	void fk_Palette::MaterialID::set(int argID)
	{
		GetP()->setObjMaterialID(argID);
	}

	int fk_Palette::MaterialID::get(void)
	{
		return GetP()->getObjMaterialID();
	}

	int fk_Palette::Size::get(void)
	{
		return GetP()->getPaletteSize();
	}

	cli::array<fk_Material^>^ fk_Palette::MaterialVector::get(void)
	{
		int i;
		int size = GetP()->getPaletteSize();
		cli::array<fk_Material^>^ matArray = gcnew cli::array<fk_Material^>(size);

		for(i = 0; i < size; ++i) {
			matArray[i] = GetMaterial(i);
		}

		return matArray;
	}

	void fk_Palette::ClearMaterial(void)
	{
		GetP()->clearMaterial();
	}

	void fk_Palette::PushPalette(fk_Material^ argMat)
	{
		if(!argMat) return;

		GetP()->pushPalette(argMat->pMat);
	}

	void fk_Palette::SetPalette(fk_Material^ argMat, int argID)
	{
		if(!argMat) return;
		GetP()->setPalette(argMat->pMat, argID);
	}

	fk_Material^ fk_Palette::GetMaterial(int argID)
	{
		fk_Material^ M = gcnew fk_Material();
		*M->pMat = *(GetP()->getMaterial(argID));
		return M;
	}
}
