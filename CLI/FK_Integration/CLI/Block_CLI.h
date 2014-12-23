// IndexFace_CLI.h

#pragma once

#include <FK/Block.h>
#include "IndexFace_CLI.h"
#include "Vector_CLI.h"

using namespace std;
using namespace System;

namespace FK_CLI
{
	public ref class fk_Block : fk_IndexFaceSet {
	internal:
		::fk_Block * GetP(void)
		{
			return reinterpret_cast<::fk_Block *>(this->pBase);
		}

	public:
		fk_Block::fk_Block() : fk_IndexFaceSet(false)
		{
			::fk_Block *p = new ::fk_Block();
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Block::fk_Block(bool argNewFlg) : fk_IndexFaceSet(false)
		{
			if(argNewFlg == true) {
				::fk_Block *p = new ::fk_Block();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_Block::fk_Block(double argX, double argY, double argZ) : fk_IndexFaceSet(false)
		{
			::fk_Block *p = new ::fk_Block(argX, argY, argZ);
			this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
		}

		fk_Block::~fk_Block()
		{
			this->!fk_Block();
		}

		fk_Block::!fk_Block()
		{
			if(dFlg == true) delete this->pBase;
			this->pBase = NULL;
		}

		void setSize(double argX, double argY, double argZ)
		{
			GetP()->setSize(argX, argY, argZ);
		}

		void setSize(double argLength, FK_CLI::fk_Axis argAxis)
		{
			GetP()->setSize(argLength, GetAxis(argAxis));
		}
						 
		void setScale(double argScale)
		{
			GetP()->setScale(argScale);
		}

		void setScale(double argScale, fk_Axis argAxis)
		{
			GetP()->setScale(argScale, GetAxis(argAxis));
		}
		
		void setScale(double argX, double argY, double argZ)
		{
			GetP()->setScale(argX, argY, argZ);
		}
	};
}
