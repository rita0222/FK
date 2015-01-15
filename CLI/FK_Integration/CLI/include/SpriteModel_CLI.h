// SpriteModel_CLI.h

#pragma once

#include <FK/SpriteModel.h>
#include "Model_CLI.h"
#include "Texture_CLI.h"

namespace FK_CLI
{
	public ref class fk_SpriteModel : fk_Model {
	internal:
		::fk_SpriteModel * GetP(void)
		{
			return (::fk_SpriteModel *)(pBase);
		}

	public:
		fk_SpriteModel::fk_SpriteModel() : fk_Model(false)
		{
			pBase = new ::fk_SpriteModel();
		}

		fk_SpriteModel::fk_SpriteModel(bool argNewFlg) : fk_Model(false)
		{
			if(argNewFlg == true) pBase = new ::fk_SpriteModel();
		}

		fk_SpriteModel::~fk_SpriteModel()
		{
			if(pBase == nullptr) return;
			if(dFlg == true) delete GetP();
			this->pBase = nullptr;
		}

		fk_SpriteModel::!fk_SpriteModel()
		{
			if(pBase == nullptr) return;
			if(dFlg == true) {
				GetP()->SetFinalizeMode();
				delete GetP();
			}
			this->pBase = nullptr;
		}

		bool readBMP(String^ filename);
		bool readPNG(String^ filename);
		bool readJPG(String^ filename);
		void setImage(fk_Image^ image);
		fk_Image^ getImage(void);
		void setPositionLT(double x, double y);
		void setSpriteArea(double x, double y, double w, double h);
		void setSpriteSize(double width, double height);
		fk_TexCoord^ getSpriteSize(void);
		void setSpriteSmoothMode(bool mode);
		bool getSpriteSmoothMode(void);
		bool initFont(String^ fontFileName);
		void drawText(String^ str);
		void drawText(String^ str, bool mode);
		void clearText(void);
	};
}
