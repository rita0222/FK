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
			delete this->pBase;
			this->pBase = NULL;
		}

		void setSize(double argX, double argY, double argZ)
		{
			::fk_Block *p = reinterpret_cast<::fk_Block *>(pBase);
			p->setSize(argX, argY, argZ);
		}

		void setSize(double argLength, FK_CLI::fk_Axis argAxis)
		{
			::fk_Block *p = reinterpret_cast<::fk_Block *>(pBase);

			switch(argAxis) {
			  case FK_CLI::fk_Axis::X:
				p->setSize(argLength, fk_X);
				break;

			  case FK_CLI::fk_Axis::Y:
				p->setSize(argLength, fk_Y);
				break;

			  case FK_CLI::fk_Axis::Z:
				p->setSize(argLength, fk_Z);
				break;

			  default:
				break;
			}
		}
						 
		void setScale(double argScale)
		{
			::fk_Block *p = reinterpret_cast<::fk_Block *>(pBase);
			p->setScale(argScale);
		}

		void setScale(double argScale, fk_Axis argAxis)
		{
			::fk_Block *p = reinterpret_cast<::fk_Block *>(pBase);

			switch(argAxis) {
			  case FK_CLI::fk_Axis::X:
				p->setScale(argScale, fk_X);
				break;

			  case FK_CLI::fk_Axis::Y:
				p->setScale(argScale, fk_Y);
				break;

			  case FK_CLI::fk_Axis::Z:
				p->setScale(argScale, fk_Z);
				break;

			  default:
				break;
			}
		}
		
		void setScale(double argX, double argY, double argZ)
		{
			::fk_Block *p = reinterpret_cast<::fk_Block *>(pBase);

			p->setScale(argX, argY, argZ);
		}
	};
}
