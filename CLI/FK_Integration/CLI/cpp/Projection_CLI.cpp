#include "Projection_CLI.h"

namespace FK_CLI {

	::fk_ProjectBase * fk_ProjectBase::GetP(void)
	{
		return pProj;
	}

	fk_ProjectBase::fk_ProjectBase(bool argNewFlg) : dFlg(argNewFlg)
	{
		if(argNewFlg == true) pProj = new ::fk_ProjectBase();
	}

	fk_ProjectBase::fk_ProjectBase() : dFlg(true)
	{
		pProj = new ::fk_ProjectBase();
	}

	fk_ProjectBase::~fk_ProjectBase()
	{
		this->!fk_ProjectBase();
	}

	fk_ProjectBase::!fk_ProjectBase()
	{
		if(pProj == nullptr) return;
		if(dFlg == true) delete GetP();
		pProj = nullptr;
	}

	fk_ProjectMode fk_ProjectBase::Mode::get(void)
	{
		switch(GetP()->getMode()) {
		  case FK_PERSPECTIVE_MODE:
			return fk_ProjectMode::PERSPECTIVE_MODE;

		  case FK_FRUSTUM_MODE:
			return fk_ProjectMode::FRUSTUM_MODE;

		  case FK_ORTHO_MODE:
			return fk_ProjectMode::ORTHO_MODE;

		  default:
			break;
		}
		return fk_ProjectMode::NONE_PROJ_MODE;
	}

	////////////////////////////////////////////////////////////////////////	

	::fk_Perspective * fk_Perspective::GetP(void)
	{
		return (::fk_Perspective *)(pProj);
	}

	fk_Perspective::fk_Perspective(bool argNewFlg) : fk_ProjectBase(false)
	{
		if(argNewFlg == true) pProj = new ::fk_Perspective();
	}

	fk_Perspective::fk_Perspective() : fk_ProjectBase(false)
	{
		pProj = new ::fk_Perspective();
	}

	fk_Perspective::fk_Perspective(double argFovy, double argNear, double argFar)
		: fk_ProjectBase(false)
	{
		pProj = new ::fk_Perspective(argFovy, argNear, argFar);
	}

	fk_Perspective::~fk_Perspective()
	{
		this->!fk_Perspective();
	}

	fk_Perspective::!fk_Perspective()
	{
		if(dFlg == true) delete pProj;
		pProj = nullptr;
	}

	void fk_Perspective::Fovy::set(double argFovy)
	{
		GetP()->setFovy(argFovy);
	}			

	double fk_Perspective::Fovy::get(void)
	{
		return GetP()->getFovy();
	}

	void fk_Perspective::Near::set(double argNear)
	{
		GetP()->setNear(argNear);
	}

	double fk_Perspective::Near::get(void)
	{
		return GetP()->getNear();
	}

	void fk_Perspective::Far::set(double argFar)
	{
		GetP()->setFar(argFar);
	}

	double fk_Perspective::Far::get(void)
	{
		return GetP()->getFar();
	}

	void fk_Perspective::SetAll(double argFovy, double argNear, double argFar)
	{
		GetP()->setAll(argFovy, argNear, argFar);
	}

	////////////////////////////////////////////////////////////////////////

	::fk_Frustum * fk_Frustum::GetP(void)
	{
		return (::fk_Frustum *)(pProj);
	}

	fk_Frustum::fk_Frustum(bool argNewFlg) : fk_ProjectBase(false)
	{
		if(argNewFlg == true) pProj = new ::fk_Frustum();
	}

	fk_Frustum::fk_Frustum() : fk_ProjectBase(false)
	{
		pProj = new ::fk_Frustum();
	}

	fk_Frustum::fk_Frustum(double argL, double argR,
						   double argB, double argT,
						   double argN, double argF) : fk_ProjectBase(false)
	{
		pProj = new ::fk_Frustum(argL, argR, argB, argT, argN, argF);
	}

	fk_Frustum::~fk_Frustum()
	{
		this->!fk_Frustum();
	}

	fk_Frustum::!fk_Frustum()
	{
		if(dFlg == true) delete pProj;
		pProj = nullptr;
	}

	void fk_Frustum::Left::set(double argLeft)
	{
		GetP()->setLeft(argLeft);
	}

	double fk_Frustum::Left::get(void)
	{
		return GetP()->getLeft();
	}

	void fk_Frustum::Right::set(double argRight)
	{
		GetP()->setRight(argRight);
	}

	double fk_Frustum::Right::get(void)
	{
		return GetP()->getRight();
	}

	void fk_Frustum::Bottom::set(double argBottom)
	{
		GetP()->setBottom(argBottom);
	}

	double fk_Frustum::Bottom::get(void)
	{
		return GetP()->getBottom();
	}

	void fk_Frustum::Top::set(double argTop)
	{
		GetP()->setTop(argTop);
	}

	double fk_Frustum::Top::get(void)
	{
		return GetP()->getTop();
	}

	void fk_Frustum::Near::set(double argNear)
	{
		GetP()->setNear(argNear);
	}
		
	double fk_Frustum::Near::get(void)
	{
		return GetP()->getNear();
	}

	void fk_Frustum::Far::set(double argFar)
	{
		GetP()->setFar(argFar);
	}
		
	double fk_Frustum::Far::get(void)
	{
		return GetP()->getFar();
	}

	void fk_Frustum::SetAll(double argLeft, double argRight,
							double argBottom, double argTop,
							double argNear, double argFar)
	{
		GetP()->setAll(argLeft, argRight, argBottom, argTop, argNear, argFar);
	}

	////////////////////////////////////////////////////////////////////////	

	::fk_Ortho * fk_Ortho::GetP(void)
	{
		return (::fk_Ortho *)(pProj);
	}

	fk_Ortho::fk_Ortho(bool argNewFlg) : fk_ProjectBase(false)
	{
		if(argNewFlg == true) pProj = new ::fk_Ortho();
	}

	fk_Ortho::fk_Ortho() : fk_ProjectBase(false)
	{
		pProj = new ::fk_Ortho();
	}

	fk_Ortho::fk_Ortho(double argL, double argR,
					   double argB, double argT,
					   double argN, double argF) : fk_ProjectBase(false)
	{
		pProj = new ::fk_Ortho(argL, argR, argB, argT, argN, argF);
	}

	fk_Ortho::~fk_Ortho()
	{
		this->!fk_Ortho();
	}

	fk_Ortho::!fk_Ortho()
	{
		if(dFlg == true) delete pProj;
		pProj = nullptr;
	}

	void fk_Ortho::Left::set(double argLeft)
	{
		GetP()->setLeft(argLeft);
	}

	double fk_Ortho::Left::get(void)
	{
		return GetP()->getLeft();
	}

	void fk_Ortho::Right::set(double argRight)
	{
		GetP()->setRight(argRight);
	}

	double fk_Ortho::Right::get(void)
	{
		return GetP()->getRight();
	}

	void fk_Ortho::Bottom::set(double argBottom)
	{
		GetP()->setBottom(argBottom);
	}

	double fk_Ortho::Bottom::get(void)
	{
		return GetP()->getBottom();
	}

	void fk_Ortho::Top::set(double argTop)
	{
		GetP()->setTop(argTop);
	}

	double fk_Ortho::Top::get(void)
	{
		return GetP()->getTop();
	}

	void fk_Ortho::Near::set(double argNear)
	{
		GetP()->setNear(argNear);
	}
		
	double fk_Ortho::Near::get(void)
	{
		return GetP()->getNear();
	}

	void fk_Ortho::Far::set(double argFar)
	{
		GetP()->setFar(argFar);
	}
		
	double fk_Ortho::Far::get(void)
	{
		return GetP()->getFar();
	}

	void fk_Ortho::SetAll(double argLeft, double argRight,
						  double argBottom, double argTop,
						  double argNear, double argFar)
	{
		GetP()->setAll(argLeft, argRight, argBottom, argTop, argNear, argFar);
	}
}
/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
