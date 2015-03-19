#include "SpriteModel_CLI.h"
#include <msclr/marshal_cppstd.h>


namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::fk_SpriteModel * fk_SpriteModel::GetP(void)
	{
		return (::fk_SpriteModel *)(pBase);
	}

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

	void fk_SpriteModel::Image::set(fk_Image^ argImage)
	{
		if(!argImage) return;
		GetP()->setImage(*argImage->GetP());
	}

	fk_Image^ fk_SpriteModel::Image::get(void)
	{
		fk_Image ^I = gcnew fk_Image();
		I->pBase = GetP()->getImage();
		I->dFlg = false;
		return I;
	}

	void fk_SpriteModel::Size::set(fk_TexCoord^ argC)
	{
		if(!argC) return;
		GetP()->setSpriteSize(argC->x_, argC->y_);
	}

	fk_TexCoord^ fk_SpriteModel::Size::get(void)
	{
		return gcnew fk_TexCoord(GetP()->getSpriteSize());
	}

	void fk_SpriteModel::SmoothMode::set(bool argMode)
	{
		GetP()->setSpriteSmoothMode(argMode);
	}

	bool fk_SpriteModel::SmoothMode::get(void)
	{
		return GetP()->getSpriteSmoothMode();
	}

	bool fk_SpriteModel::ReadBMP(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readBMP(marshal_as<string>(argFileName));
	}

	bool fk_SpriteModel::ReadPNG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readPNG(marshal_as<string>(argFileName));
	}
		
	bool fk_SpriteModel::ReadJPG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readJPG(marshal_as<string>(argFileName));
	}

	void fk_SpriteModel::SetPositionLT(double argX, double argY)
	{
		GetP()->setPositionLT(argX, argY);
	}

	void fk_SpriteModel::SetSpriteArea(double argX, double argY, double argW, double argH)
	{
		GetP()->setSpriteArea(argX, argY, argW, argH);
	}

	bool fk_SpriteModel::InitFont(String^ argFont)
	{
		if(!argFont) return false;
		return GetP()->initFont(marshal_as<string>(argFont));
	}

	void fk_SpriteModel::DrawText(String^ argStr)
	{
		if(!argStr) return;
		GetP()->drawText(marshal_as<string>(argStr), FK_STR_SJIS);
	}

	void fk_SpriteModel::DrawText(String^ argStr, bool argMode)
	{
		if(!argStr) return;
		GetP()->drawText(marshal_as<string>(argStr), argMode, FK_STR_SJIS);
	}

	void fk_SpriteModel::ClearText(void)
	{
		GetP()->clearText();
	}
}
