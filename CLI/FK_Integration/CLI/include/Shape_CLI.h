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
		::fk_Shape * GetP(void);

	public:
		fk_Shape(bool argNewFlg);
		~fk_Shape();
		!fk_Shape();

		property fk_RealShapeType^ RealShapeType {
			fk_RealShapeType^ get();
		}

		property fk_Palette^ Palette {
			fk_Palette^ get();
		}

		property fk_MaterialMode MaterialMode {
			fk_MaterialMode get();
			void set(fk_MaterialMode);
		}

		property int MaterialID {
			int get();
			void set(int);
		}

		property int PaletteSize {
			int get();
		}

		property array<fk_Material^>^ MaterialVector {
			array<fk_Material^>^ get();
		}
		
		void			ClearMaterial(void);
		void			PushPalette(fk_Material^ material);
		void			SetPalette(fk_Material^ material, int ID);
		fk_Material^	GetMaterial(int ID);
	};
}
