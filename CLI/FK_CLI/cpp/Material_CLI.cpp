#include "Material_CLI.h"

namespace FK_CLI {
	using namespace std;

	::FK::fk_Material * fk_Material::GetP(void)
	{
		return pMat;
	}

	fk_Material::fk_Material() : dFlg(true)
	{
		pMat = new ::FK::fk_Material();
	}

	fk_Material::fk_Material(bool argNewFlg) : dFlg(argNewFlg)
	{
		if(argNewFlg == true) pMat = new ::FK::fk_Material();
	}

	fk_Material::fk_Material(fk_Material^ argM) : dFlg(true)
	{
		if (argM == nullptr) {
			fk_Material();
			return;
		}
		::FK::fk_Material *pM = argM->GetP();
		pMat = new ::FK::fk_Material(*pM);
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
		::FK::fk_Material::initDefault();

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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
