#include "Shape_CLI.h"

namespace FK_CLI {

	fk_RealShapeType^ fk_Shape::getRealShapeType(void)
	{
		fk_RealShapeType^ type = gcnew fk_RealShapeType();

		switch(GetP()->getRealShapeType()) {
		  case FK_SHAPE_IFS:
			type = fk_RealShapeType::FK_SHAPE_IFS;
			break;
				
		  case FK_SHAPE_SOLID:
			type = fk_RealShapeType::FK_SHAPE_SOLID;
			break;
				
		  case FK_SHAPE_TEXTURE:
			type = fk_RealShapeType::FK_SHAPE_TEXTURE;
			break;
				
		  case FK_SHAPE_POINT:
			type = fk_RealShapeType::FK_SHAPE_POINT;
			break;
				
		  case FK_SHAPE_LIGHT:
			type = fk_RealShapeType::FK_SHAPE_LIGHT;
			break;
				
		  case FK_SHAPE_OTHER:
			type = fk_RealShapeType::FK_SHAPE_OTHER;
			break;
				
		  default:
			break;
		}
		return type;
	}
			
	fk_Palette^ fk_Shape::getPaletteData(void)
	{
		::fk_Palette *pP = GetP()->getPaletteData();
		if(pP == nullptr) return nullptr;

		fk_Palette^ pal = gcnew fk_Palette();
		::fk_Palette *pP2 = pal->GetP();
		*pP2 = *pP;
		return pal;
	}

	void fk_Shape::clearMaterial(void)
	{
		GetP()->clearMaterial();
	}
		
	void fk_Shape::setObjMaterialID(int argID)
	{
		GetP()->setObjMaterialID(argID);
	}
		
	void fk_Shape::pushPalette(fk_Material^ argMat)
	{
		if(!argMat) return;
		GetP()->pushPalette(*argMat->pMat);
	}

	void fk_Shape::setPalette(fk_Material^ argMat, int argID)
	{
		if(!argMat) return;
		GetP()->setPalette(*argMat->pMat, argID);
	}

	void fk_Shape::setMaterialMode(fk_MaterialMode argMode)
	{
		switch(argMode) {
		  case fk_MaterialMode::CHILD:
			GetP()->setMaterialMode(FK_CHILD_MODE);
			break;

		  case fk_MaterialMode::PARENT:
			GetP()->setMaterialMode(FK_PARENT_MODE);
			break;

		  default:
			GetP()->setMaterialMode(FK_NONE_MODE);
			break;
		}
	}

	fk_MaterialMode fk_Shape::getMaterialMode(void)
	{
		switch(GetP()->getMaterialMode()) {
		  case FK_CHILD_MODE:
			return fk_MaterialMode::CHILD;

		  case FK_PARENT_MODE:
			return fk_MaterialMode::PARENT;

		  default:
			break;
		}

		return fk_MaterialMode::NONE;
	}

	int fk_Shape::getObjMaterialID(void)
	{
		return GetP()->getObjMaterialID();
	}

	int fk_Shape::getPaletteSize(void)
	{
		return GetP()->getPaletteSize();
	}
		
	fk_Material^ fk_Shape::getMaterial(int argID)
	{
		fk_Material^ mat = gcnew fk_Material();
		*mat->pMat = *(GetP()->getMaterial(argID));
		return mat;
	}

	array<fk_Material^>^ fk_Shape::getMaterialVector(void)
	{
		fk_Palette^	pal = getPaletteData();
		if(!pal) return nullptr;
		return pal->getMaterialVector();
	}
}

