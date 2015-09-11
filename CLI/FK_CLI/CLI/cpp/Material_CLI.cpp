#include "Material_CLI.h"

namespace FK_CLI {
	using namespace std;
	
	::fk_Color * fk_Color::GetP(void)
	{
		return pCol;
	}

	fk_Color::fk_Color() : dFlg(true)
	{
		pCol = new ::fk_Color();
	}

	fk_Color::fk_Color(bool argNewFlg) : dFlg(argNewFlg)
	{
		if(argNewFlg == true) pCol = new ::fk_Color();
	}

	fk_Color::fk_Color(double argR, double argG, double argB) : dFlg(true)
	{
		pCol = new ::fk_Color(argR, argG, argB);
	}

	fk_Color::fk_Color(double argR, double argG, double argB, double argA) : dFlg(true)
	{
		pCol = new ::fk_Color();
		pCol->init(argR, argG, argB, argA);
	}

	fk_Color::fk_Color(float argR, float argG, float argB) : dFlg(true)
	{
		pCol = new ::fk_Color(argR, argG, argB);
	}

	fk_Color::fk_Color(float argR, float argG, float argB, float argA) : dFlg(true)
	{
		pCol = new ::fk_Color();
		pCol->init(argR, argG, argB, argA);
	}

	fk_Color::~fk_Color()
	{
		this->!fk_Color();
	}

	fk_Color::!fk_Color()
	{
		if(pCol == nullptr) return;
		if(dFlg == true) delete GetP();
		pCol = nullptr;
	}

	float fk_Color::col::get(int argI)
	{
		return GetP()->col[argI];
	}

	void fk_Color::col::set(int argI, float argC)
	{
		GetP()->col[argI] = ::fk_Color::clamp(argC);
	}

	float fk_Color::r::get()
	{
		return GetP()->col[0];
	}

	void fk_Color::r::set(float argF)
	{
		GetP()->col[0] = ::fk_Color::clamp(argF);
	}
	
	float fk_Color::g::get()
	{
		return GetP()->col[1];
	}

	void fk_Color::g::set(float argF)
	{
		GetP()->col[1] = ::fk_Color::clamp(argF);
	}

	float fk_Color::b::get()
	{
		return GetP()->col[2];
	}

	void fk_Color::b::set(float argF)
	{
		GetP()->col[2] = ::fk_Color::clamp(argF);
	}

	float fk_Color::a::get()
	{
		return GetP()->col[3];
	}

	void fk_Color::a::set(float argF)
	{
		GetP()->col[3] = ::fk_Color::clamp(argF);
	}

	bool fk_Color::Equals(fk_Color^ argC)
	{
		if(!argC) false;
		return (*GetP() == *argC->GetP());
	}

	bool fk_Color::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_Color^ C = static_cast<fk_Color^>(argObj);
			return (*GetP() == *C->GetP());
		}
		return false;
	}

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

	fk_Color^ fk_Color::operator+(fk_Color^ argC1, fk_Color^ argC2)
	{
		if(!argC1 || !argC2) return nullptr;
		fk_Color^ C = gcnew fk_Color(argC1->GetP()->col[0] + argC2->GetP()->col[0],
									 argC1->GetP()->col[1] + argC2->GetP()->col[1],
									 argC1->GetP()->col[2] + argC2->GetP()->col[2],
									 argC1->GetP()->col[3] + argC2->GetP()->col[3]);
		return C;
	}

	fk_Color^ fk_Color::operator-(fk_Color^ argC1, fk_Color^ argC2)
	{
		if(!argC1 || !argC2) return nullptr;
		fk_Color^ C = gcnew fk_Color(argC1->GetP()->col[0] - argC2->GetP()->col[0],
									 argC1->GetP()->col[1] - argC2->GetP()->col[1],
									 argC1->GetP()->col[2] - argC2->GetP()->col[2],
									 argC1->GetP()->col[3] - argC2->GetP()->col[3]);
		return C;
	}

	fk_Color^ fk_Color::operator*(fk_Color^ argC, double argD)
	{
		if(!argC) return nullptr;
		fk_Color^ C = gcnew fk_Color(argC->GetP()->col[0] * float(argD),
									 argC->GetP()->col[1] * float(argD),
									 argC->GetP()->col[2] * float(argD),
									 argC->GetP()->col[3] * float(argD));
		return C;
	}
	
	fk_Color^ fk_Color::operator*(double argD, fk_Color^ argC)
	{
		if(!argC) return nullptr;
		fk_Color^ C = gcnew fk_Color(argC->GetP()->col[0] * float(argD),
									 argC->GetP()->col[1] * float(argD),
									 argC->GetP()->col[2] * float(argD),
									 argC->GetP()->col[3] * float(argD));
		return C;
	}

	fk_Color^ fk_Color::operator/(fk_Color^ argC, double argD)
	{
		if(!argC) return nullptr;
		fk_Color^ C = gcnew fk_Color(argC->GetP()->col[0] / float(argD),
									 argC->GetP()->col[1] / float(argD),
									 argC->GetP()->col[2] / float(argD),
									 argC->GetP()->col[3] / float(argD));
		return C;
	}

	void fk_Color::operator *= (fk_Color^ argC, double argD)
	{
		if(!argC) return;
		argC->Set(argC->r * float(argD),
				  argC->g * float(argD),
				  argC->b * float(argD),
				  argC->a * float(argD));
		return;
	}
	
	void fk_Color::operator /= (fk_Color^ argC, double argD)
	{
		if(!argC) return;
		argC->Set(argC->r / float(argD),
				  argC->g / float(argD),
				  argC->b / float(argD),
				  argC->a / float(argD));
		return;
	}
	
	void fk_Color::operator += (fk_Color^ argC1, fk_Color^ argC2)
	{
		if(!argC1 || !argC2) return;
		argC1->Set(argC1->r + argC2->r,
				   argC1->g + argC2->g,
				   argC1->b + argC2->b,
				   argC1->a + argC2->a);
		return;
	}

	void fk_Color::operator -= (fk_Color^ argC1, fk_Color^ argC2)
	{
		if(!argC1 || !argC2) return;
		argC1->Set(argC1->r - argC2->r,
				   argC1->g - argC2->g,
				   argC1->b - argC2->b,
				   argC1->a - argC2->a);
		return;
	}

	void fk_Color::Init(void)
	{
		GetP()->init();
		return;
	}


	void fk_Color::Init(float argR, float argG, float argB)
	{
		GetP()->init(argR, argG, argB, 1.0f);
		return;
	}

	void fk_Color::Init(float argR, float argG, float argB, float argA)
	{
		GetP()->init(argR, argG, argB, argA);
		return;
	}

	void fk_Color::Init(double argR, double argG, double argB)
	{
		GetP()->init(argR, argG, argB, 1.0);
		return;
	}

	void fk_Color::Init(double argR, double argG, double argB, double argA)
	{
		GetP()->init(argR, argG, argB, argA);
		return;
	}

	void fk_Color::Set(float argR, float argG, float argB)
	{
		GetP()->set(argR, argG, argB, 1.0f);
		return;
	}

	void fk_Color::Set(float argR, float argG, float argB, float argA)
	{
		GetP()->set(argR, argG, argB, argA);
		return;
	}

	void fk_Color::Set(double argR, double argG, double argB)
	{
		GetP()->set(argR, argG, argB, 1.0);
		return;
	}

	void fk_Color::Set(double argR, double argG, double argB, double argA)
	{
		GetP()->set(argR, argG, argB, argA);
		return;
	}

	void fk_Color::SetHSV(double argH, double argS, double argV)
	{
		GetP()->setHSV(argH, argS, argV);
		return;
	}

	///////////////////////////////////////////////////////////////////

	::fk_Material * fk_Material::GetP(void)
	{
		return pMat;
	}

	fk_Material::fk_Material() : dFlg(true)
	{
		pMat = new ::fk_Material();
	}

	fk_Material::fk_Material(bool argNewFlg) : dFlg(argNewFlg)
	{
		if(argNewFlg == true) pMat = new ::fk_Material();
	}

	fk_Material::~fk_Material()
	{
		this->!fk_Material();
	}

	fk_Material::!fk_Material()
	{
		if(dFlg == true) delete pMat;
		pMat = nullptr;
	}

	bool fk_Material::Equals(fk_Material^ argM)
	{
		if(!argM) false;
		return (*GetP() == *argM->GetP());
	}

	bool fk_Material::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_Material^ M = static_cast<fk_Material^>(argObj);
			return (*GetP() == *M->GetP());
		}
		return false;
	}

	float fk_Material::Alpha::get()
	{
		return GetP()->getAlpha();
	}

	void fk_Material::Alpha::set(float argF)
	{
		GetP()->setAlpha(argF);
	}

	fk_Color^ fk_Material::Ambient::get()
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *(GetP()->getAmbient());
		return C;
	}

	void fk_Material::Ambient::set(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setAmbient(*argC->pCol);
	}

	fk_Color^ fk_Material::Diffuse::get()
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *(GetP()->getDiffuse());
		return C;
	}

	void fk_Material::Diffuse::set(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setDiffuse(*argC->pCol);
	}

	fk_Color^ fk_Material::Specular::get()
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *(GetP()->getSpecular());				
		return C;
	}

	void fk_Material::Specular::set(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setSpecular(*argC->pCol);
	}

	fk_Color^ fk_Material::Emission::get()
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *(GetP()->getEmission());
		return C;
	}

	void fk_Material::Emission::set(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setEmission(*argC->pCol);
	}

	void fk_Material::Init(void)
	{
		GetP()->init();
	}

	void fk_Material::InitDefault(void)
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
