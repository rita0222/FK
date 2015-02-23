#include "Shape_CLI.h"

namespace FK_CLI {

	::fk_Shape * fk_Shape::GetP(void)
	{
		return (::fk_Shape *)(pBase);
	}

	fk_Shape::fk_Shape(bool argNewFlg) : fk_Attribute(false)
	{
		if(argNewFlg == true) pBase = new ::fk_Shape();
	}

	fk_Shape::~fk_Shape()
	{
		this->!fk_Shape();
	}

	fk_Shape::!fk_Shape()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_RealShapeType^ fk_Shape::RealShapeType::get(void)
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
			

	fk_Palette^ fk_Shape::Palette::get(void)
	{
		::fk_Palette *pP = GetP()->getPaletteData();
		if(pP == nullptr) return nullptr;

		fk_Palette^ pal = gcnew fk_Palette();
		::fk_Palette *pP2 = pal->GetP();
		*pP2 = *pP;
		return pal;
	}

	void fk_Shape::MaterialMode::set(fk_MaterialMode argMode)
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

	fk_MaterialMode fk_Shape::MaterialMode::get(void)
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

	void fk_Shape::MaterialID::set(int argID)
	{
		GetP()->setObjMaterialID(argID);
	}
		
	int fk_Shape::MaterialID::get(void)
	{
		return GetP()->getObjMaterialID();
	}

	int fk_Shape::PaletteSize::get(void)
	{
		return GetP()->getPaletteSize();
	}
		
	array<fk_Material^>^ fk_Shape::MaterialVector::get(void)
	{
		fk_Palette^	pal = Palette::get();
		if(!pal) return nullptr;
		return pal->MaterialVector;
	}

	void fk_Shape::ClearMaterial(void)
	{
		GetP()->clearMaterial();
	}
		
	void fk_Shape::PushPalette(fk_Material^ argMat)
	{
		if(!argMat) return;
		GetP()->pushPalette(*argMat->pMat);
	}

	void fk_Shape::SetPalette(fk_Material^ argMat, int argID)
	{
		if(!argMat) return;
		GetP()->setPalette(*argMat->pMat, argID);
	}

	fk_Material^ fk_Shape::GetMaterial(int argID)
	{
		fk_Material^ mat = gcnew fk_Material();
		*mat->pMat = *(GetP()->getMaterial(argID));
		return mat;
	}

}
