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
#include "SpriteModel_CLI.h"
#include <msclr/marshal_cppstd.h>


namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::FK::fk_SpriteModel * fk_SpriteModel::GetP(void)
	{
		return (::FK::fk_SpriteModel *)(pBase);
	}

	fk_SpriteModel::fk_SpriteModel() : fk_Model(false)
	{
		pBase = new ::FK::fk_SpriteModel();
	}

	fk_SpriteModel::fk_SpriteModel(bool argNewFlg) : fk_Model(false)
	{
		if(argNewFlg == true) pBase = new ::FK::fk_SpriteModel();
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

	fk_TextImage^ fk_SpriteModel::Text::get(void)
	{
		fk_TextImage^ TI = gcnew fk_TextImage();
		TI->pBase = &(GetP()->text);
		TI->dFlg = false;
		return TI;
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
		GetP()->drawText(marshal_as<string>(argStr), ::FK::fk_StringCode::SJIS);
	}

	void fk_SpriteModel::DrawText(String^ argStr, bool argMode)
	{
		if(!argStr) return;
		GetP()->drawText(marshal_as<string>(argStr), argMode, ::FK::fk_StringCode::SJIS);
	}

	void fk_SpriteModel::ClearText(void)
	{
		GetP()->clearText();
	}

	void fk_SpriteModel::MakePixelBase(fk_Dimension^ argWinSize, fk_Scene^ argScn)
	{
		if (!argWinSize || !argScn) return;
		GetP()->MakePixelBase(*(argWinSize->GetP()), argScn->GetP());
	}
}

