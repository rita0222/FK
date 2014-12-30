#include "Material_CLI.h"

namespace FK_CLI {
	using namespace std;
	
	String^ fk_Color::ToString()
	{
		string tmpBuf;

		tmpBuf = "C: ";
		for(int i = 0; i < 4; ++i) {
			tmpBuf += to_string(GetP()->col[i]);
			if(i != 3) {
				tmpBuf += ", ";
			} else {
				tmpBuf += "\n";
			}
		}
		return gcnew String(tmpBuf.c_str());
	}

	void fk_Color::init(void)
	{
		GetP()->init();
	}


	void fk_Color::init(float argR, float argG, float argB)
	{
		GetP()->init(argR, argG, argB, 1.0f);
	}

	void fk_Color::init(float argR, float argG, float argB, float argA)
	{
		GetP()->init(argR, argG, argB, argA);
	}

	void fk_Color::init(double argR, double argG, double argB)
	{
		GetP()->init(argR, argG, argB, 1.0);
	}

	void fk_Color::init(double argR, double argG, double argB, double argA)
	{
		GetP()->init(argR, argG, argB, argA);
	}

	void fk_Color::set(float argR, float argG, float argB)
	{
		GetP()->set(argR, argG, argB, 1.0f);
	}

	void fk_Color::set(float argR, float argG, float argB, float argA)
	{
		GetP()->set(argR, argG, argB, argA);
	}

	void fk_Color::set(double argR, double argG, double argB)
	{
		GetP()->set(argR, argG, argB, 1.0);
	}

	void fk_Color::set(double argR, double argG, double argB, double argA)
	{
		GetP()->set(argR, argG, argB, argA);
	}

	void fk_Color::setHSV(double argH, double argS, double argV)
	{
		GetP()->setHSV(argH, argS, argV);
	}

	///////////////////////////////////////////////////////////////////

	void fk_Material::init(void)
	{
		GetP()->init();
	}

	void fk_Material::setAmbient(float argR, float argG, float argB)
	{
		GetP()->setAmbient(argR, argG, argB);
	}

	void fk_Material::setAmbient(double argR, double argG, double argB)
	{
		GetP()->setAmbient(argR, argG, argB);
	}

	void fk_Material::setDiffuse(float argR, float argG, float argB)
	{
		GetP()->setDiffuse(argR, argG, argB);
	}

	void fk_Material::setDiffuse(double argR, double argG, double argB)
	{
		GetP()->setDiffuse(argR, argG, argB);
	}

	void fk_Material::setSpecular(float argR, float argG, float argB)
	{
		GetP()->setSpecular(argR, argG, argB);
	}

	void fk_Material::setSpecular(double argR, double argG, double argB)
	{
		GetP()->setSpecular(argR, argG, argB);
	}

	void fk_Material::setEmission(float argR, float argG, float argB)
	{
		GetP()->setEmission(argR, argG, argB);
	}

	void fk_Material::setEmission(double argR, double argG, double argB)
	{
		GetP()->setEmission(argR, argG, argB);
	}

	void fk_Material::setAmbDiff(float argR, float argG, float argB)
	{
		GetP()->setAmbDiff(argR, argG, argB);
	}

	void fk_Material::setAmbDiff(double argR, double argG, double argB)
	{
		GetP()->setAmbDiff(argR, argG, argB);
	}

	void fk_Material::setAmbDiff(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setAmbDiff(*argC->pCol);
	}

	void fk_Material::initDefault(void)
	{
		::fk_Material::initDefault();

		LightCyan = gcnew fk_Material();
		*LightCyan->pMat = ::LightCyan;

		AshGray = gcnew fk_Material();
		*AshGray->pMat = ::AshGray;

		BurntTitan = gcnew fk_Material();
		*BurntTitan->pMat = ::BurntTitan;

		IridescentGreen = gcnew fk_Material();
		*IridescentGreen->pMat = ::IridescentGreen;

		UltraMarine = gcnew fk_Material();
		*UltraMarine->pMat = ::UltraMarine;

		Ivory = gcnew fk_Material();
		*Ivory->pMat = ::Ivory;

		BambooGreen = gcnew fk_Material();
		*BambooGreen->pMat = ::BambooGreen;

		PearWhite = gcnew fk_Material();
		*PearWhite->pMat = ::PearWhite;

		Lilac = gcnew fk_Material();
		*Lilac->pMat = ::Lilac;

		HolidaySkyBlue = gcnew fk_Material();
		*HolidaySkyBlue->pMat = ::HolidaySkyBlue;

		DimYellow = gcnew fk_Material();
		*DimYellow->pMat = ::DimYellow;

		LavaRed = gcnew fk_Material();
		*LavaRed->pMat = ::LavaRed;

		GrassGreen = gcnew fk_Material();
		*GrassGreen->pMat = ::GrassGreen;

		Red = gcnew fk_Material();
		*Red->pMat = ::Red;

		Pink = gcnew fk_Material();
		*Pink->pMat = ::Pink;

		DarkRed = gcnew fk_Material();
		*DarkRed->pMat = ::DarkRed;

		Orange = gcnew fk_Material();
		*Orange->pMat = ::Orange;

		Flesh = gcnew fk_Material();
		*Flesh->pMat = ::Flesh;

		Brown = gcnew fk_Material();
		*Brown->pMat = ::Brown;

		Yellow = gcnew fk_Material();
		*Yellow->pMat = ::Yellow;

		Cream = gcnew fk_Material();
		*Cream->pMat = ::Cream;

		DarkYellow = gcnew fk_Material();
		*DarkYellow->pMat = ::DarkYellow;

		Green = gcnew fk_Material();
		*Green->pMat = ::Green;

		LightGreen = gcnew fk_Material();
		*LightGreen->pMat = ::LightGreen;

		Cyan = gcnew fk_Material();
		*Cyan->pMat = ::Cyan;

		PaleBlue = gcnew fk_Material();
		*PaleBlue->pMat = ::PaleBlue;

		Blue = gcnew fk_Material();
		*Blue->pMat = ::Blue;

		LightBlue = gcnew fk_Material();
		*LightBlue->pMat = ::LightBlue;

		DarkGreen = gcnew fk_Material();
		*DarkGreen->pMat = ::DarkGreen;

		DarkBlue = gcnew fk_Material();
		*DarkBlue->pMat = ::DarkBlue;

		DarkPurple = gcnew fk_Material();
		*DarkPurple->pMat = ::DarkPurple;

		Violet = gcnew fk_Material();
		*Violet->pMat = ::Violet;

		Purple = gcnew fk_Material();
		*Purple->pMat = ::Purple;

		LightViolet = gcnew fk_Material();
		*LightViolet->pMat = ::LightViolet;

		Coral = gcnew fk_Material();
		*Coral->pMat = ::Coral;

		White = gcnew fk_Material();
		*White->pMat = ::White;

		Gray1 = gcnew fk_Material();
		*Gray1->pMat = ::Gray1;

		Gray2 = gcnew fk_Material();
		*Gray2->pMat = ::Gray2;

		GlossBlack = gcnew fk_Material();
		*GlossBlack->pMat = ::GlossBlack;

		MatBlack = gcnew fk_Material();
		*MatBlack->pMat = ::MatBlack;

		TrueWhite = gcnew fk_Material();
		*TrueWhite->pMat = ::TrueWhite;
	}
}
