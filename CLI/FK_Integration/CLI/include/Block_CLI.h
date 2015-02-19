// Block_CLI.h

#pragma once

#include <FK/Block.h>
#include "IndexFace_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	public ref class fk_Block : fk_IndexFaceSet {
	internal:
		::fk_Block * GetP(void)
		{
			return (::fk_Block *)(pBase);
		}

	public:
		fk_Block::fk_Block() : fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Block();
		}

		fk_Block::fk_Block(bool argNewFlg) : fk_IndexFaceSet(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_Block();
			}
				
		}

		fk_Block::fk_Block(double argX, double argY, double argZ) : fk_IndexFaceSet(false)
		{
			pBase = new ::fk_Block(argX, argY, argZ);
		}

		fk_Block::~fk_Block()
		{
			this->!fk_Block();
		}

		fk_Block::!fk_Block()
		{
			if(pBase == nullptr) return;
			if(dFlg == true) delete GetP();
			pBase = nullptr;
		}

		void SetSize(double x, double y, double z);
		void SetSize(double length, fk_Axis axis);
		void SetScale(double scale);
		void SetScale(double scale, fk_Axis axis);
		void SetScale(double x, double y, double z);
	};
}
