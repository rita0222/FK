﻿// Shape_CLI.h

#pragma once

#include <FK/Shape.h>
#include "Attribute_CLI.h"
#include "Palette_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

	public enum class fk_RealShapeType
	{
		FK_SHAPE_IFS,
		FK_SHAPE_SOLID,
		FK_SHAPE_TEXTURE,
		FK_SHAPE_POINT,
		FK_SHAPE_LIGHT,
		FK_SHAPE_OTHER
	};

	public ref class fk_Shape : FK_CLI::fk_Attribute {
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
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		fk_RealShapeType^ getRealShapeType(void)
		{
			fk_RealShapeType^ type = gcnew fk_RealShapeType();

			switch(GetP()->getRealShapeType()) {
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
			::fk_Palette *pP = GetP()->getPaletteData();
			if(pP == NULL) return nullptr;

			fk_Palette^ pal = gcnew fk_Palette();
			::fk_Palette *pP2 = pal->GetP();
			*pP2 = *pP;
			return pal;
		}

		void clearMaterial(void)
		{
			GetP()->clearMaterial();
		}
		
		void setObjMaterialID(int argID)
		{
			GetP()->setObjMaterialID(argID);
		}
		
		void pushPalette(fk_Material^ argMat)
		{
			if(!argMat) return;
			GetP()->pushPalette(*argMat->pMat);
		}

		void setPalette(fk_Material^ argMat, int argID)
		{
			if(!argMat) return;
			GetP()->setPalette(*argMat->pMat, argID);
		}

		void setMaterialMode(FK_CLI::fk_MaterialMode argMode)
		{
			switch(argMode) {
			  case FK_CLI::fk_MaterialMode::CHILD:
				GetP()->setMaterialMode(FK_CHILD_MODE);
				break;

			  case FK_CLI::fk_MaterialMode::PARENT:
				GetP()->setMaterialMode(FK_PARENT_MODE);
				break;

			  default:
				GetP()->setMaterialMode(FK_NONE_MODE);
				break;
			}
		}

		FK_CLI::fk_MaterialMode getMaterialMode(void)
		{
			switch(GetP()->getMaterialMode()) {
			  case FK_CHILD_MODE:
				return FK_CLI::fk_MaterialMode::CHILD;

			  case FK_PARENT_MODE:
				return FK_CLI::fk_MaterialMode::PARENT;

			  default:
				break;
			}

			return FK_CLI::fk_MaterialMode::NONE;
		}

		int getObjMaterialID(void)
		{
			return GetP()->getObjMaterialID();
		}

		int getPaletteSize(void)
		{
			return GetP()->getPaletteSize();
		}
		
		fk_Material^ getMaterial(int argID)
		{
			fk_Material^ mat = gcnew fk_Material();
			*mat->pMat = *(GetP()->getMaterial(argID));
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
