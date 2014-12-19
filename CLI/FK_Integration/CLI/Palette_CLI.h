// Palette_CLI.h

#pragma once

#include <FK/Palette.h>
#include "Material_CLI.h"

using namespace std;
using namespace System;

namespace FK_CLI
{
	public enum class fk_MaterialMode : int {
		FK_NONE_MODE = 0,
		FK_CHILD_MODE = 1,
		FK_PARENT_MODE = 2
	};

	public ref class fk_Palette : fk_BaseObject {
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
			delete this->pBase;
			this->pBase = NULL;
		}

		void clearMaterial(void)
		{
			::fk_Palette *p = reinterpret_cast<::fk_Palette *>(pBase);
			p->clearMaterial();
		}

		void setObjMaterialID(int argID)
		{
			::fk_Palette *p = reinterpret_cast<::fk_Palette *>(pBase);
			p->setObjMaterialID(argID);
		}

		void pushPalette(fk_Material^ argMat)
		{
			if(!argMat) return;

			::fk_Palette *p = reinterpret_cast<::fk_Palette *>(pBase);
			::fk_Material *pM = reinterpret_cast<::fk_Material *>(argMat->pBase);
			p->pushPalette(pM);
		}

		void setPalette(fk_Material^ argMat, int argID)
		{
			if(!argMat) return;
			::fk_Palette *p = reinterpret_cast<::fk_Palette *>(pBase);
			::fk_Material *pM = reinterpret_cast<::fk_Material *>(argMat->pBase);
			p->setPalette(pM, argID);
		}

		int getObjMaterialID(void)
		{
			::fk_Palette *p = reinterpret_cast<::fk_Palette *>(pBase);
			return p->getObjMaterialID();
		}

		int getPaletteSize(void)
		{
			::fk_Palette *p = reinterpret_cast<::fk_Palette *>(pBase);
			return p->getPaletteSize();
		}

		fk_Material^ getMaterial(int argID)
		{
			::fk_Palette *p = reinterpret_cast<::fk_Palette *>(pBase);
			fk_Material^ M = gcnew fk_Material();
			::fk_Material *pM = reinterpret_cast<::fk_Material *>(M->pBase);
			*pM = *(p->getMaterial(argID));
			return M;
		}

		array<fk_Material^>^ getMaterialVector(void)
		{
			::fk_Palette *p = reinterpret_cast<::fk_Palette *>(pBase);
			int i;
			int size = p->getPaletteSize();
			array<fk_Material^>^ matArray = gcnew array<fk_Material^>(size);

			for(i = 0; i < size; i++) {
				matArray[i] = getMaterial(i);
			}

			return matArray;
		}

	   };
}
