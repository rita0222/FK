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
		
		::fk_Palette * GetP(void);

	public:
		fk_Palette();
		fk_Palette(bool argNewFlg);
		~fk_Palette();
		!fk_Palette();

		property int MaterialID {
			void set(int);
			int get();
		}

		property int Size {
			int get();
		}

		property array<fk_Material^>^ MaterialVector {
			array<fk_Material^>^ get();

		}
		void ClearMaterial(void);
		void PushPalette(fk_Material^ material);
		void SetPalette(fk_Material^ material, int ID);
		fk_Material^ GetMaterial(int ID);
	};
}
