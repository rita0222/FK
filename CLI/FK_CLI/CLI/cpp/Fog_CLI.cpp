/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
#include <FK/Scene.h>
#include "Fog_CLI.h"

namespace FK_CLI {

	::FK::fk_Scene * fk_Fog::GetP(void)
	{
		return (::FK::fk_Scene *)(pBase);
	}

	fk_Fog::fk_Fog(bool argNewFlg) : fk_DisplayLink(false)
	{
	}

	fk_Fog::~fk_Fog()
	{
	}

	void fk_Fog::FogMode::set(fk_FogMode argMode)
	{
		switch(argMode) {
		  case fk_FogMode::LINEAR:
			GetP()->setFogMode(::FK::fk_FogMode::LINEAR);
			break;
				
		  case fk_FogMode::EXP:
			GetP()->setFogMode(::FK::fk_FogMode::EXP);
			break;
				
		  case fk_FogMode::EXP2:
			GetP()->setFogMode(::FK::fk_FogMode::EXP2);
			break;

		  default:
			GetP()->setFogMode(::FK::fk_FogMode::NONE);
			break;
		}
	}

	fk_FogMode fk_Fog::FogMode::get(void)
	{
		switch(GetP()->getFogMode()) {
		case ::FK::fk_FogMode::LINEAR:
			return fk_FogMode::LINEAR;

		case ::FK::fk_FogMode::EXP:
			return fk_FogMode::EXP;

		case ::FK::fk_FogMode::EXP2:
			return fk_FogMode::EXP2;

		  default:
			break;
		}
		return fk_FogMode::NONE;
	}
			   
	void fk_Fog::FogOption::set(fk_FogOption argOpt)
	{
		switch(argOpt) {
		  case fk_FogOption::FASTEST:
			GetP()->setFogOption(::FK::fk_FogMode::FASTEST);
			break;

		  case fk_FogOption::NICEST:
			GetP()->setFogOption(::FK::fk_FogMode::NICEST);
			break;

		  default:
			GetP()->setFogOption(::FK::fk_FogMode::NOOPTION);
			break;
		}
	}

	fk_FogOption fk_Fog::FogOption::get(void)
	{
		switch(GetP()->getFogOption()) {
		case ::FK::fk_FogMode::FASTEST:
			return fk_FogOption::FASTEST;
				
		case ::FK::fk_FogMode::NICEST:
			return fk_FogOption::NICEST;

		  default:
			break;
		}
		return fk_FogOption::NOOPTION;
	}

	void fk_Fog::FogDensity::set(double argD)
	{
		GetP()->setFogDensity(argD);
	}

	double fk_Fog::FogDensity::get(void)
	{
		return GetP()->getFogDensity();
	}

	void fk_Fog::FogLinearStart::set(double argS)
	{
		GetP()->setFogLinearMap(argS, GetP()->getFogLinearEnd());
	}

	double fk_Fog::FogLinearStart::get(void)
	{
		return GetP()->getFogLinearStart();
	}

	void fk_Fog::FogLinearEnd::set(double argE)
	{
		GetP()->setFogLinearMap(GetP()->getFogLinearStart(), argE);
	}
		
	double fk_Fog::FogLinearEnd::get(void)
	{
		return GetP()->getFogLinearEnd();
	}

	void fk_Fog::FogColor::set(fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setFogColor(*argCol->GetP());
	}

	fk_Color^ fk_Fog::FogColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		::FK::fk_Color tmpC = GetP()->getFogColor();
		C->Set(tmpC.getR(), tmpC.getG(), tmpC.getB(), tmpC.getA());
		return C;
	}
}


