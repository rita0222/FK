﻿#include "Scene_CLI.h"

namespace FK_CLI {

	::FK::fk_Scene * fk_Scene::GetP(void)
	{
		return (::FK::fk_Scene *)(pBase);
	}

	fk_Scene::fk_Scene(bool argNewFlg) : fk_Fog(false)
	{
		if(argNewFlg == true) {
			pBase = new ::FK::fk_Scene();
			CameraUpdate();
		}
	}

	fk_Scene::fk_Scene() : fk_Fog(false)
	{
		pBase = new ::FK::fk_Scene();
		CameraUpdate();
	}

	fk_Scene::~fk_Scene()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_Scene::!fk_Scene()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) {
			GetP()->SetFinalizeMode();
			delete GetP();
		}
		pBase = nullptr;
	}

	void fk_Scene::BGColor::set(fk_Color^ argCol)
	{
		GetP()->setBGColor(*argCol->GetP());
	}

	fk_Color^ fk_Scene::BGColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		::FK::fk_Color tmpC = GetP()->getBGColor();
		C->Set(tmpC.getR(), tmpC.getG(), tmpC.getB(), tmpC.getA());
		return C;
	}

	void fk_Scene::BlendStatus::set(bool argMode)
	{
		GetP()->setBlendStatus(argMode);
	}

	bool fk_Scene::BlendStatus::get(void)
	{
		return GetP()->getBlendStatus();
	}

    void fk_Scene::ShadowMode::set(fk_ShadowMode argMode)
    {
        switch (argMode) {
        case fk_ShadowMode::HARD:
            GetP()->setShadowMode(::FK::fk_ShadowMode::HARD);
            break;

        case fk_ShadowMode::SOFT_FAST:
            GetP()->setShadowMode(::FK::fk_ShadowMode::SOFT_FAST);
            break;

        case fk_ShadowMode::SOFT_NICE:
            GetP()->setShadowMode(::FK::fk_ShadowMode::SOFT_NICE);
            break;

        case fk_ShadowMode::OFF:
            GetP()->setShadowMode(::FK::fk_ShadowMode::OFF);
            break;

        default:
            break;
        }
    }

    fk_ShadowMode fk_Scene::ShadowMode::get(void)
    {
        switch (GetP()->getShadowMode()) {
        case ::FK::fk_ShadowMode::HARD:
            return fk_ShadowMode::HARD;

        case ::FK::fk_ShadowMode::SOFT_FAST:
            return fk_ShadowMode::SOFT_FAST;

        case ::FK::fk_ShadowMode::SOFT_NICE:
            return fk_ShadowMode::SOFT_NICE;

        case ::FK::fk_ShadowMode::OFF:
            return fk_ShadowMode::OFF;

        default:
            break;
        }
        return fk_ShadowMode::OFF;
    }

    void fk_Scene::ShadowVec::set(fk_Vector^ argV)
    {
        if (!argV) return;
        GetP()->setShadowVec(::FK::fk_Vector(argV->x_, argV->y_, argV->z_));
    }

    fk_Vector^ fk_Scene::ShadowVec::get(void)
    {
        return gcnew fk_Vector(GetP()->getShadowVec());
    }

    void fk_Scene::ShadowResolution::set(int argRes)
    {
        GetP()->setShadowResolution(argRes);
    }

    int fk_Scene::ShadowResolution::get(void)
    {
        return GetP()->getShadowResolution();
    }

    void fk_Scene::ShadowAreaSize::set(double argSize)
    {
        GetP()->setShadowAreaSize(argSize);
    }

    double fk_Scene::ShadowAreaSize::get(void)
    {
        return GetP()->getShadowAreaSize();
    }

    void fk_Scene::ShadowDistance::set(double argDist)
    {
        GetP()->setShadowDistance(argDist);
    }

    double fk_Scene::ShadowDistance::get(void)
    {
        return GetP()->getShadowDistance();
    }

    void fk_Scene::ShadowVisibility::set(double argV)
    {
        GetP()->setShadowVisibility(argV);
    }

    double fk_Scene::ShadowVisibility::get(void)
    {
        return GetP()->getShadowVisibility();
    }

    void fk_Scene::ShadowBias::set(double argV)
    {
        GetP()->setShadowBias(argV);
    }

    double fk_Scene::ShadowBias::get(void)
    {
        return GetP()->getShadowBias();
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
