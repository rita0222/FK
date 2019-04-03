#include "Color_CLI.h"

namespace FK_CLI {
	using namespace std;
	
	::FK::fk_Color * fk_Color::GetP(void)
	{
		return pCol;
	}

	fk_Color::fk_Color() : dFlg(true)
	{
		pCol = new ::FK::fk_Color();
	}

	fk_Color::operator ::FK::fk_Color(fk_Color ^argC)
	{
		::FK::fk_Color C(argC->r, argC->g, argC->b, argC->a);
		return C;
	}

	fk_Color::fk_Color(::FK::fk_Color argC) : dFlg(true)
	{
		pCol = new ::FK::fk_Color();
		pCol->init(argC.col[0], argC.col[1], argC.col[2], argC.col[3]);
	}

	fk_Color::fk_Color(bool argNewFlg) : dFlg(argNewFlg)
	{
		if(argNewFlg == true) pCol = new ::FK::fk_Color();
	}

	fk_Color::fk_Color(double argR, double argG, double argB) : dFlg(true)
	{
		pCol = new ::FK::fk_Color(argR, argG, argB);
	}

	fk_Color::fk_Color(double argR, double argG, double argB, double argA) : dFlg(true)
	{
		pCol = new ::FK::fk_Color();
		pCol->init(argR, argG, argB, argA);
	}

	fk_Color::fk_Color(float argR, float argG, float argB) : dFlg(true)
	{
		pCol = new ::FK::fk_Color(argR, argG, argB);
	}

	fk_Color::fk_Color(float argR, float argG, float argB, float argA) : dFlg(true)
	{
		pCol = new ::FK::fk_Color();
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
		GetP()->col[argI] = ::FK::fk_Color::clamp(argC);
	}

	float fk_Color::r::get()
	{
		return GetP()->col[0];
	}

	void fk_Color::r::set(float argF)
	{
		GetP()->col[0] = ::FK::fk_Color::clamp(argF);
	}
	
	float fk_Color::g::get()
	{
		return GetP()->col[1];
	}

	void fk_Color::g::set(float argF)
	{
		GetP()->col[1] = ::FK::fk_Color::clamp(argF);
	}

	float fk_Color::b::get()
	{
		return GetP()->col[2];
	}

	void fk_Color::b::set(float argF)
	{
		GetP()->col[2] = ::FK::fk_Color::clamp(argF);
	}

	float fk_Color::a::get()
	{
		return GetP()->col[3];
	}

	void fk_Color::a::set(float argF)
	{
		GetP()->col[3] = ::FK::fk_Color::clamp(argF);
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
