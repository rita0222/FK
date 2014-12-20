﻿// IndexFace_CLI.h

#pragma once

#include <FK/Block.h>
#include "IndexFace_CLI.h"
#include "Vector_CLI.h"

using namespace std;
using namespace System;
using namespace msclr::interop;

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
			if(argNewFlg == true) this->pBase = new ::fk_Block();
		}

		fk_Block::fk_Block(double argX, double argY, double argZ) : fk_IndexFaceSet(false)
		{
			this->pBase = new ::fk_Block(argX, argY, argZ);
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
			p->setSize(argLength, GetAxis(argAxis));
		}
						 
		void setScale(double argScale)
		{
			::fk_Block *p = reinterpret_cast<::fk_Block *>(pBase);
			p->setScale(argScale);
		}

		void setScale(double argScale, fk_Axis argAxis)
		{
			::fk_Block *p = reinterpret_cast<::fk_Block *>(pBase);
			p->setScale(argScale, GetAxis(argAxis));
		}
		
		void setScale(double argX, double argY, double argZ)
		{
			::fk_Block *p = reinterpret_cast<::fk_Block *>(pBase);

			p->setScale(argX, argY, argZ);
		}
	};
}
