// Block_CLI.h

#pragma once

#include <FK/Block.h>
#include "IndexFace_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	public ref class fk_Block : fk_IndexFaceSet {
	internal:
		::fk_Block * GetP(void);

	public:
		fk_Block();
		fk_Block(bool);
		fk_Block(double, double, double);
		~fk_Block();
		!fk_Block();

		void SetSize(double, double, double);
		void SetSize(double, fk_Axis);
		void SetScale(double);
		void SetScale(double, fk_Axis);
		void SetScale(double, double, double);
	};
}
