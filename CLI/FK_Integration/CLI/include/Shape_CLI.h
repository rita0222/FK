// Shape_CLI.h

#pragma once

#include <FK/Shape.h>
#include "Attribute_CLI.h"
#include "Palette_CLI.h"

namespace FK_CLI
{
	public enum class fk_RealShapeType {
		FK_SHAPE_IFS,
		FK_SHAPE_SOLID,
		FK_SHAPE_TEXTURE,
		FK_SHAPE_POINT,
		FK_SHAPE_LIGHT,
		FK_SHAPE_OTHER
	};

	public ref class fk_Shape : fk_Attribute {
	internal:
		::fk_Shape * GetP(void)
		{
			return (::fk_Shape *)(pBase);
		}

	public:
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

		fk_RealShapeType^ getRealShapeType(void);
		fk_Palette^ getPaletteData(void);
		void clearMaterial(void);
		void setObjMaterialID(int ID);
		void pushPalette(fk_Material^ material);
		void setPalette(fk_Material^ material, int ID);
		void setMaterialMode(fk_MaterialMode mode);
		fk_MaterialMode getMaterialMode(void);
		int getObjMaterialID(void);
		int getPaletteSize(void);
		fk_Material^ getMaterial(int ID);
		array<fk_Material^>^ getMaterialVector(void);
	};
}
