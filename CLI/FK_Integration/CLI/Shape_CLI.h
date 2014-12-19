// Shape_CLI.h

#pragma once

#include <FK/Shape.h>
#include "Attribute_CLI.h"
#include "Palette_CLI.h"

using namespace std;
using namespace System;

namespace FK_CLI
{
	public enum class fk_RealShapeType
	{
		FK_SHAPE_IFS,
		FK_SHAPE_SOLID,
		FK_SHAPE_TEXTURE,
		FK_SHAPE_POINT,
		FK_SHAPE_LIGHT,
		FK_SHAPE_OTHER
	};

	public ref class fk_Shape : fk_Attribute {
	public:
		fk_Shape::fk_Shape(bool argNewFlg) : fk_Attribute(false)
		{
			if(argNewFlg == true) {
				::fk_Shape *p = new ::fk_Shape();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_Shape::~fk_Shape()
		{
			this->!fk_Shape();
		}

		fk_Shape::!fk_Shape()
		{
			delete this->pBase;
			this->pBase = NULL;
		}

		fk_RealShapeType^ getRealShapeType(void)
		{
			fk_RealShapeType^ type = gcnew fk_RealShapeType();
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);

			switch(p->getRealShapeType()) {
			  case FK_SHAPE_IFS:
				type = FK_CLI::fk_RealShapeType::FK_SHAPE_IFS;
				break;
				
			  case FK_SHAPE_SOLID:
				type = FK_CLI::fk_RealShapeType::FK_SHAPE_SOLID;
				break;
				
			  case FK_SHAPE_TEXTURE:
				type = FK_CLI::fk_RealShapeType::FK_SHAPE_TEXTURE;
				break;
				
			  case FK_SHAPE_POINT:
				type = FK_CLI::fk_RealShapeType::FK_SHAPE_POINT;
				break;
				
			  case FK_SHAPE_LIGHT:
				type = FK_CLI::fk_RealShapeType::FK_SHAPE_LIGHT;
				break;
				
			  case FK_SHAPE_OTHER:
				type = FK_CLI::fk_RealShapeType::FK_SHAPE_OTHER;
				break;
				
			  default:
				break;
			}
			return type;
		}
			
		fk_Palette^ getPaletteData(void)
		{
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);
			::fk_Palette *pP = p->getPaletteData();
			if(pP == NULL) return nullptr;

			fk_Palette^ pal = gcnew fk_Palette();
			::fk_Palette *pP2 = reinterpret_cast<::fk_Palette *>(pal->pBase);
			*pP2 = *pP;
			return pal;
		}

		void clearMaterial(void)
		{
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);
			p->clearMaterial();
		}
		
		void setObjMaterialID(int argID)
		{
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);
			p->setObjMaterialID(argID);
		}
		
		void pushPalette(fk_Material^ argMat)
		{
			if(!argMat) return;
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);
			::fk_Material *pM = reinterpret_cast<::fk_Material *>(argMat->pBase);
			p->pushPalette(*pM);
		}

		void setPalette(fk_Material^ argMat, int argID)
		{
			if(!argMat) return;
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);
			::fk_Material *pM = reinterpret_cast<::fk_Material *>(argMat->pBase);
			p->setPalette(*pM, argID);
		}

		void setMaterialMode(FK_CLI::fk_MaterialMode argMode)
		{
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);

			switch(argMode) {
			  case FK_CLI::fk_MaterialMode::FK_CHILD_MODE:
				p->setMaterialMode(FK_CHILD_MODE);
				break;

			  case FK_CLI::fk_MaterialMode::FK_PARENT_MODE:
				p->setMaterialMode(FK_PARENT_MODE);
				break;

			  default:
				p->setMaterialMode(FK_NONE_MODE);
				break;
			}
		}

		FK_CLI::fk_MaterialMode getMaterialMode(void)
		{
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);

			switch(p->getMaterialMode()) {
			  case FK_CHILD_MODE:
				return FK_CLI::fk_MaterialMode::FK_CHILD_MODE;

			  case FK_PARENT_MODE:
				return FK_CLI::fk_MaterialMode::FK_PARENT_MODE;

			  default:
				break;
			}

			return FK_CLI::fk_MaterialMode::FK_NONE_MODE;
		}

		int getObjMaterialID(void)
		{
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);
			return p->getObjMaterialID();
		}

		int getPaletteSize(void)
		{
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);
			return p->getPaletteSize();
		}
		
		fk_Material^ getMaterial(int argID)
		{
			::fk_Shape *p = reinterpret_cast<::fk_Shape *>(pBase);
			fk_Material^ mat = gcnew fk_Material();
			*mat->pBase = *(p->getMaterial(argID));
			return mat;
		}

		array<fk_Material^>^ getMaterialVector(void)
		{
			fk_Palette^	pal = getPaletteData();
			if(!pal) return nullptr;
			return pal->getMaterialVector();
		}
	};
}
