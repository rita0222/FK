﻿#include "Material_CLI.h"

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

	float fk_Material::Shininess::get()
	{
		return GetP()->getShininess();
	}

	void fk_Material::Shininess::set(float argF)
	{
		GetP()->setShininess(argF);
	}

	void fk_Material::Init(void)
	{
		GetP()->init();
	}

	void fk_Material::InitDefault(void)
	{
		::fk_Material::initDefault();

		LightCyan = gcnew fk_Material();
		*LightCyan->pMat = ::FK::Material::LightCyan;

		AshGray = gcnew fk_Material();
		*AshGray->pMat = ::FK::Material::AshGray;

		BurntTitan = gcnew fk_Material();
		*BurntTitan->pMat = ::FK::Material::BurntTitan;

		IridescentGreen = gcnew fk_Material();
		*IridescentGreen->pMat = ::FK::Material::IridescentGreen;

		UltraMarine = gcnew fk_Material();
		*UltraMarine->pMat = ::FK::Material::UltraMarine;

		Ivory = gcnew fk_Material();
		*Ivory->pMat = ::FK::Material::Ivory;

		BambooGreen = gcnew fk_Material();
		*BambooGreen->pMat = ::FK::Material::BambooGreen;

		PearWhite = gcnew fk_Material();
		*PearWhite->pMat = ::FK::Material::PearWhite;

		Lilac = gcnew fk_Material();
		*Lilac->pMat = ::FK::Material::Lilac;

		HolidaySkyBlue = gcnew fk_Material();
		*HolidaySkyBlue->pMat = ::FK::Material::HolidaySkyBlue;

		DimYellow = gcnew fk_Material();
		*DimYellow->pMat = ::FK::Material::DimYellow;

		LavaRed = gcnew fk_Material();
		*LavaRed->pMat = ::FK::Material::LavaRed;

		GrassGreen = gcnew fk_Material();
		*GrassGreen->pMat = ::FK::Material::GrassGreen;

		Red = gcnew fk_Material();
		*Red->pMat = ::FK::Material::Red;

		Pink = gcnew fk_Material();
		*Pink->pMat = ::FK::Material::Pink;

		DarkRed = gcnew fk_Material();
		*DarkRed->pMat = ::FK::Material::DarkRed;

		Orange = gcnew fk_Material();
		*Orange->pMat = ::FK::Material::Orange;

		Flesh = gcnew fk_Material();
		*Flesh->pMat = ::FK::Material::Flesh;

		Brown = gcnew fk_Material();
		*Brown->pMat = ::FK::Material::Brown;

		Yellow = gcnew fk_Material();
		*Yellow->pMat = ::FK::Material::Yellow;

		Cream = gcnew fk_Material();
		*Cream->pMat = ::FK::Material::Cream;

		DarkYellow = gcnew fk_Material();
		*DarkYellow->pMat = ::FK::Material::DarkYellow;

		Green = gcnew fk_Material();
		*Green->pMat = ::FK::Material::Green;

		LightGreen = gcnew fk_Material();
		*LightGreen->pMat = ::FK::Material::LightGreen;

		Cyan = gcnew fk_Material();
		*Cyan->pMat = ::FK::Material::Cyan;

		PaleBlue = gcnew fk_Material();
		*PaleBlue->pMat = ::FK::Material::PaleBlue;

		Blue = gcnew fk_Material();
		*Blue->pMat = ::FK::Material::Blue;

		LightBlue = gcnew fk_Material();
		*LightBlue->pMat = ::FK::Material::LightBlue;

		DarkGreen = gcnew fk_Material();
		*DarkGreen->pMat = ::FK::Material::DarkGreen;

		DarkBlue = gcnew fk_Material();
		*DarkBlue->pMat = ::FK::Material::DarkBlue;

		DarkPurple = gcnew fk_Material();
		*DarkPurple->pMat = ::FK::Material::DarkPurple;

		Violet = gcnew fk_Material();
		*Violet->pMat = ::FK::Material::Violet;

		Purple = gcnew fk_Material();
		*Purple->pMat = ::FK::Material::Purple;

		LightViolet = gcnew fk_Material();
		*LightViolet->pMat = ::FK::Material::LightViolet;

		Coral = gcnew fk_Material();
		*Coral->pMat = ::FK::Material::Coral;

		White = gcnew fk_Material();
		*White->pMat = ::FK::Material::White;

		Gray1 = gcnew fk_Material();
		*Gray1->pMat = ::FK::Material::Gray1;

		Gray2 = gcnew fk_Material();
		*Gray2->pMat = ::FK::Material::Gray2;

		GlossBlack = gcnew fk_Material();
		*GlossBlack->pMat = ::FK::Material::GlossBlack;

		MatBlack = gcnew fk_Material();
		*MatBlack->pMat = ::FK::Material::MatBlack;

		TrueWhite = gcnew fk_Material();
		*TrueWhite->pMat = ::FK::Material::TrueWhite;
	}
}
/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
