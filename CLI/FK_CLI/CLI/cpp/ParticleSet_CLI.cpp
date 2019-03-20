#include "ParticleSet_CLI.h"

namespace FK_CLI
{
	using namespace std;

	::FK::fk_ParticleSet * fk_ParticleSet::GetP(void)
	{
		return (::FK::fk_ParticleSet *)(pBase);
	}

	fk_ParticleSet::fk_ParticleSet() : fk_BaseObject(false)
	{
		pBase = new ::FK::fk_ParticleSet();
	}

	fk_ParticleSet::fk_ParticleSet(bool argNewFlg) : fk_BaseObject(false)
	{
		if(argNewFlg == true) {
			pBase = new ::FK::fk_ParticleSet();
		}
	}

	fk_ParticleSet::~fk_ParticleSet()
	{
		this->!fk_ParticleSet();
	}

	fk_ParticleSet::!fk_ParticleSet()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_Shape^ fk_ParticleSet::Shape::get(void)
	{
		fk_Shape^ S = gcnew fk_Shape(false);
		S->pBase = GetP()->getShape();
		S->dFlg = false;
		return S;
	}

	unsigned int fk_ParticleSet::Count::get(void)
	{
		return GetP()->getCount();
	}

	unsigned int fk_ParticleSet::ParticleNum::get(void)
	{
		return GetP()->getParticleNum();
	}

	void fk_ParticleSet::MaxSize::set(unsigned int argMax)
	{
		GetP()->setMaxSize(argMax);
	}

	unsigned int fk_ParticleSet::MaxSize::get(void)
	{
		return GetP()->getMaxSize();
	}

	void fk_ParticleSet::AllMode::set(bool argMode)
	{
		GetP()->setAllMode(argMode);
	}

	bool fk_ParticleSet::AllMode::get(void)
	{
		return GetP()->getAllMode();
	}

	void fk_ParticleSet::IndivMode::set(bool argMode)
	{
		GetP()->setIndivMode(argMode);
	}

	bool fk_ParticleSet::IndivMode::get(void)
	{
		return GetP()->getIndivMode();
	}

	fk_Particle^ fk_ParticleSet::NewParticle(void)
	{
		auto newP = GetP()->newParticle();
		if (newP == nullptr) return nullptr;
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = newP;
		P->dFlg = false;
		GenMethod(P);
		return P;
	}

	fk_Particle^ fk_ParticleSet::NewParticle(fk_Vector^ argPos)
	{
		if(!argPos) return nullptr;
		auto newP = GetP()->newParticle();
		if (newP == nullptr) return nullptr;
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = newP;
		P->dFlg = false;
		GenMethod(P);
		return P;
	}

	fk_Particle^ fk_ParticleSet::NewParticle(double argX, double argY, double argZ)
	{
		auto newP = GetP()->newParticle();
		if (newP == nullptr) return nullptr;
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = GetP()->newParticle(argX, argY, argZ);
		P->dFlg = false;
		GenMethod(P);
		return P;
	}

	bool fk_ParticleSet::RemoveParticle(fk_Particle ^argP)
	{
		return GetP()->removeParticle(argP->GetP());
	}

	bool fk_ParticleSet::RemoveParticle(int argID)
	{
		return GetP()->removeParticle(argID);
	}

	fk_Particle^ fk_ParticleSet::GetParticle(int argID)
	{
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = GetP()->getParticle(argID);
		P->dFlg = false;
		return P;
	}

	fk_Particle^ fk_ParticleSet::GetNextParticle(fk_Particle^ argP)
	{
		::FK::fk_Particle *pP = (!argP) ? nullptr : argP->GetP();
		pP = GetP()->getNextParticle(pP);
		if(pP == nullptr) return nullptr;
		fk_Particle^ P = gcnew fk_Particle();
		P->pBase = pP;
		P->dFlg = false;
		return P;
	}

	void fk_ParticleSet::Handle(void)
	{
		if(AllMode == true) {
			AllMethod();
		}

		if(IndivMode == true) {
			fk_Particle^ P;

			for(P = GetNextParticle(nullptr); P != nullptr; P = GetNextParticle(P)) {
				IndivMethod(P);
			}
		}

		GetP()->handle();
	}

	void fk_ParticleSet::GenMethod(fk_Particle^)
	{
		return;
	}

	void fk_ParticleSet::AllMethod(void)
	{
		return;
	}

	void fk_ParticleSet::IndivMethod(fk_Particle^)
	{
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
