﻿#include "Model_CLI.h"

class InnerModel : public ::FK::fk_Model
{
private:
	using callback_type = void(__stdcall *)(void);
	callback_type pPreShader;
	callback_type pPostShader;

public:
	InnerModel(void* pre, void* post)
	{
		pPreShader = (callback_type)pre;
		pPostShader = (callback_type)post;
	};

	void preShader()
	{
		pPreShader();
	};

	void postShader()
	{
		pPostShader();
	};
};

namespace FK_CLI {

	::FK::fk_Model * fk_Model::GetP(void)
	{
		return (::FK::fk_Model *)(pBase);
	}

	void fk_Model::MakeNativeModel(void)
	{
		using namespace System::Runtime::InteropServices;
		preShader = gcnew fk_DrawCallback(this, &fk_Model::OnPreShader);
		System::IntPtr p1 = Marshal::GetFunctionPointerForDelegate(preShader);
		postShader = gcnew fk_DrawCallback(this, &fk_Model::OnPostShader);
		System::IntPtr p2 = Marshal::GetFunctionPointerForDelegate(postShader);
		pBase = new ::InnerModel((void*)p1, (void*)p2);
	}

	fk_Model::fk_Model(): fk_Boundary(false), shape(nullptr)
	{
		MakeNativeModel();
		modelList->AddLast(this);
	}

	fk_Model::fk_Model(bool argNewFlg) : fk_Boundary(false), shape(nullptr)
	{
		if (argNewFlg) {
			MakeNativeModel();
		}
		modelList->AddLast(this);
	}

	fk_Model::fk_Model(::FK::fk_Model *argUnmanagedPtr) : fk_Boundary(false), shape(nullptr)
	{
		if (argUnmanagedPtr == nullptr) {
			MakeNativeModel();
		} else {
			pBase = argUnmanagedPtr;
			dFlg = false;
		}

		modelList->AddLast(this);
	}

	fk_Model::~fk_Model()
	{
		shape = nullptr;
		preShader = nullptr;
		postShader = nullptr;
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
		modelList->Remove(this);
	}

	fk_Model::!fk_Model()
	{
		shape = nullptr;
		preShader = nullptr;
		postShader = nullptr;
		if(pBase == nullptr) return;
		if(dFlg == true) {
			GetP()->SetTreeDelMode(false);
			delete GetP();
		}
		pBase = nullptr;
		modelList->Remove(this);
	}

	//////////////////////////////////////////////////////////////////////////

	unsigned int fk_Model::ID::get(void)
	{
		return GetP()->getID();
	}

	void fk_Model::Shape::set(fk_Shape^ argShape)
	{
		shape = argShape;
		if(!argShape) return;
		::FK::fk_Shape *pS = (::FK::fk_Shape *)(argShape->pBase);
		GetP()->setShape(pS);
	}

	fk_Shape^ fk_Model::Shape::get(void)
	{
		return shape;
	}

	void fk_Model::Material::set(fk_Material^ argM)
	{
		if(!argM) return;
		GetP()->setMaterial(*argM->pMat);
	}

	fk_Material^ fk_Model::Material::get(void)
	{
		fk_Material^ M = gcnew fk_Material();
		*M->pMat = *GetP()->getMaterial();
		return M;
	}

	fk_Color^ fk_Model::PointColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getPointColor();
		return C;
	}

	void fk_Model::PointColor::set(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setPointColor(argC->pCol);
	}

	void fk_Model::LineColor::set(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setLineColor(argC->pCol);
	}

	fk_Color^ fk_Model::LineColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getLineColor();
		return C;
	}
	
	void fk_Model::CurveColor::set(fk_Color^ argC)
	{
		if (!argC) return;
		GetP()->setCurveColor(argC->pCol);
	}

	fk_Color^ fk_Model::CurveColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = *GetP()->getCurveColor();
		return C;
	}

	void fk_Model::PointSize::set(double argSize)
	{
		GetP()->setSize(argSize);
	}

	double fk_Model::PointSize::get(void)
	{
		return GetP()->getSize();
	}
	
	void fk_Model::LineWidth::set(double argWidth)
	{
		GetP()->setWidth(argWidth);
	}

	double fk_Model::LineWidth::get(void)
	{
		return GetP()->getWidth();
	}

	void fk_Model::DrawMode::set(fk_Draw argMode)
	{
		GetP()->setDrawMode(static_cast<::FK::fk_Draw>(argMode));
	}

	fk_Draw fk_Model::DrawMode::get(void)
	{
		return static_cast<fk_Draw>(GetP()->getDrawMode());
	}

	void fk_Model::ElementMode::set(fk_ElementMode argMode)
	{
		switch (argMode) {
		case fk_ElementMode::NONE:
			GetP()->setElementMode(::FK::fk_ElementMode::NONE);
			break;

		case fk_ElementMode::MODEL:
			GetP()->setElementMode(::FK::fk_ElementMode::MODEL);
			break;

		case fk_ElementMode::ELEMENT:
			GetP()->setElementMode(::FK::fk_ElementMode::ELEMENT);
			break;

		default:
			break;
		}
		return;
	}

	fk_ElementMode fk_Model::ElementMode::get(void)
	{
		switch (GetP()->getElementMode()) {
		case ::FK::fk_ElementMode::MODEL:
			return fk_ElementMode::MODEL;

		case ::FK::fk_ElementMode::ELEMENT:
			return fk_ElementMode::ELEMENT;

		default:
			break;
		}

		return fk_ElementMode::NONE;
	}

	void fk_Model::ShadingMode::set(fk_ShadingMode argMode)
	{
		switch(argMode) {
		case fk_ShadingMode::GOURAUD:
			GetP()->setShadingMode(::FK::fk_ShadingMode::GOURAUD);
			break;

		case fk_ShadingMode::PHONG:
			GetP()->setShadingMode(::FK::fk_ShadingMode::PHONG);
			break;
		
		default:
			break;
		}
		return;
	}

	fk_ShadingMode fk_Model::ShadingMode::get(void)
	{
		switch(GetP()->getShadingMode()) {
		case ::FK::fk_ShadingMode::GOURAUD:
			return fk_ShadingMode::GOURAUD;

		case ::FK::fk_ShadingMode::PHONG:
			return fk_ShadingMode::PHONG;

		default:
			break;
		}

		return fk_ShadingMode::PHONG;
	}

	void fk_Model::SmoothMode::set(bool argMode)
	{
		GetP()->setSmoothMode(argMode);
	}

	bool fk_Model::SmoothMode::get(void)
	{
		return GetP()->getSmoothMode();
	}

	void fk_Model::ReverseDrawMode::set(bool argMode)
	{
		GetP()->setReverseDrawMode(argMode);
	}

	bool fk_Model::ReverseDrawMode::get(void)
	{
		return GetP()->getReverseDrawMode();
	}

	void fk_Model::DepthMode::set(fk_DepthMode argMode)
	{
		GetP()->setDepthMode(static_cast<::FK::fk_DepthMode>(argMode));
	}

	fk_DepthMode fk_Model::DepthMode::get(void)
	{
		return static_cast<fk_DepthMode>(GetP()->getDepthMode());
	}

	void fk_Model::BlendMode::set(fk_BlendMode argMode)
	{
		if (argMode == fk_BlendMode::CUSTOM) {
			::FK::fk_BlendFactor src, dst;
			GetP()->getBlendMode(&src, &dst);
			GetP()->setBlendMode(::FK::fk_BlendMode::CUSTOM, src, dst);
			return;
		}

		GetP()->setBlendMode(static_cast<::FK::fk_BlendMode>(argMode));
	}

	fk_BlendMode fk_Model::BlendMode::get(void)
	{
		return static_cast<fk_BlendMode>(GetP()->getBlendMode());
	}

	void fk_Model::BlendSrcFactor::set(fk_BlendFactor argMode)
	{
		::FK::fk_BlendFactor src, dst;
		GetP()->getBlendMode(&src, &dst);
		src = static_cast<::FK::fk_BlendFactor>(argMode);
		GetP()->setBlendMode(::FK::fk_BlendMode::CUSTOM, src, dst);
	}

	fk_BlendFactor fk_Model::BlendSrcFactor::get(void)
	{
		::FK::fk_BlendFactor src, dst;
		GetP()->getBlendMode(&src, &dst);
		return static_cast<fk_BlendFactor>(src);
	}

	void fk_Model::BlendDstFactor::set(fk_BlendFactor argMode)
	{
		::FK::fk_BlendFactor src, dst;
		GetP()->getBlendMode(&src, &dst);
		dst = static_cast<::FK::fk_BlendFactor>(argMode);
		GetP()->setBlendMode(::FK::fk_BlendMode::CUSTOM, src, dst);
	}

	fk_BlendFactor fk_Model::BlendDstFactor::get(void)
	{
		::FK::fk_BlendFactor src, dst;
		GetP()->getBlendMode(&src, &dst);
		return static_cast<fk_BlendFactor>(dst);
	}

	void fk_Model::ShadowEffect::set(bool argMode)
	{
		GetP()->setShadowEffect(argMode);
	}

	bool fk_Model::ShadowEffect::get(void)
	{
		return GetP()->getShadowEffect();
	}

	void fk_Model::ShadowDraw::set(bool argMode)
	{
		GetP()->setShadowDraw(argMode);
	}

	bool fk_Model::ShadowDraw::get(void)
	{
		return GetP()->getShadowDraw();
	}

	void fk_Model::FogMode::set(bool argMode)
	{
		GetP()->setFogMode(argMode);
	}

	bool fk_Model::FogMode::get(void)
	{
		return GetP()->getFogMode();
	}

	fk_Matrix^ fk_Model::InhMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhMatrix();
		return M;
	}

	fk_Matrix^ fk_Model::InhInvMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhInvMatrix();
		return M;
	}
	fk_Matrix^ fk_Model::InhBaseMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhBaseMatrix();
		return M;
	}

	fk_Matrix^ fk_Model::InhInvBaseMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInhInvBaseMatrix();
		return M;
	}

	fk_Vector^ fk_Model::InhPosition::get(void)
	{
		return gcnew fk_Vector(GetP()->getInhPosition());
	}

	fk_Vector^ fk_Model::InhVec::get(void)
	{
		return gcnew fk_Vector(GetP()->getInhVec());
	}

	fk_Vector^ fk_Model::InhUpvec::get(void)
	{
		return gcnew fk_Vector(GetP()->getInhUpvec());
	}

	fk_Angle^ fk_Model::InhAngle::get(void)
	{
		return gcnew fk_Angle(GetP()->getInhAngle());
	}

	double fk_Model::InhScale::get(void)
	{
		return GetP()->getInhScale();
	}

	void fk_Model::Parent::set(fk_Model^ argM)
	{
		SetParent(argM, false);
	}

	fk_Model^ fk_Model::Parent::get(void)
	{
		::FK::fk_Model *pM = GetP()->getParent();
		if(pM == nullptr) return nullptr;
		return gcnew fk_Model(pM);
	}

	void fk_Model::InterMode::set(bool argMode)
	{
		GetP()->setInterMode(argMode);
	}

	bool fk_Model::InterMode::get(void)
	{
		return GetP()->getInterMode();
	}

	bool fk_Model::InterStatus::get(void)
	{
		return GetP()->getInterStatus();
	}

	void fk_Model::InterStopMode::set(bool argMode)
	{
		GetP()->setInterStopMode(argMode);
	}

	bool fk_Model::InterStopMode::get(void)
	{
		return GetP()->getInterStopMode();
	}

	////////////////////////////////////////////////////////////////////////////////

	bool fk_Model::Equals(fk_Model^ argModel)
	{
		if (!argModel) return false;
		return ID == argModel->ID;
	}

	bool fk_Model::SetParent(fk_Model^ argM, bool argMode)
	{
		if(!argM) return false;

		return GetP()->setParent(argM->GetP(), argMode);
	}

	bool fk_Model::SetParent(fk_Model^ argM)
	{
		return SetParent(argM, false);
	}

	void fk_Model::DeleteParent(bool argMode)
	{
		GetP()->deleteParent(argMode);
	}

	void fk_Model::DeleteParent(void)
	{
		DeleteParent(false);
	}

	bool fk_Model::EntryChild(fk_Model^ argModel, bool argMode)
	{
		if(!argModel) return false;
		return GetP()->entryChild(argModel->GetP(), argMode);
	}

	bool fk_Model::EntryChild(fk_Model^ argModel)
	{
		return EntryChild(argModel, false);
	}

	bool fk_Model::DeleteChild(fk_Model^ argModel, bool argMode)
	{
		if(!argModel) return false;
		return GetP()->deleteChild(argModel->GetP(), argMode);
	}

	bool fk_Model::DeleteChild(fk_Model^ argModel)
	{
		return DeleteChild(argModel, false);
	}

	void fk_Model::DeleteChildren(bool argMode)
	{
		GetP()->deleteChildren(argMode);
	}

	void fk_Model::DeleteChildren(void)
	{
		DeleteChildren(false);
	}

	void fk_Model::SnapShot(void)
	{
		GetP()->snapShot();
	}

	bool fk_Model::Restore(void)
	{
		return GetP()->restore();
	}

	bool fk_Model::Restore(double argT)
	{
		return GetP()->restore(argT);
	}

	void fk_Model::AdjustSphere(void)
	{
		GetP()->adjustSphere();
	}

	void fk_Model::AdjustAABB(void)
	{
		GetP()->adjustAABB();
	}

	void fk_Model::AdjustOBB(void)
	{
		GetP()->adjustOBB();
	}

	void fk_Model::AdjustCapsule(fk_Vector^ argS, fk_Vector^ argE)
	{
		if(!argS || !argE) return;
		::FK::fk_Vector S(argS->x_, argS->y_, argS->z_);
		::FK::fk_Vector E(argE->x_, argE->y_, argE->z_);

		GetP()->adjustCapsule(S, E);
	}

	bool fk_Model::IsInter(fk_Model^ argModel)
	{
		if(!argModel) return false;
		return GetP()->isInter(argModel->GetP());
	}

	bool fk_Model::IsCollision(fk_Model^ argModel, double %argTime)
	{
		auto [retVal, tmpT] = GetP()->isCollision(argModel->GetP());
		argTime = tmpT;
		return retVal;
	}

	void fk_Model::ResetInter(void)
	{
		GetP()->resetInter();
	}

	void fk_Model::EntryInterModel(fk_Model^ argModel)
	{
		GetP()->entryInterModel(argModel->GetP());
	}

	void fk_Model::DeleteInterModel(fk_Model^ argModel)
	{
		GetP()->deleteInterModel(argModel->GetP());
	}

	void fk_Model::ClearInterModel(void)
	{
		GetP()->clearInterModel();
	}

	////////////////////////////////////////////////////////////////////////////////
	
	bool fk_Model::GlRotate(fk_Vector^ argO, fk_Axis argAxis, double argTheta)
	{
		if(!argO) return false;
		return GetP()->glRotate(argO, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::GlRotate(double argX, double argY, double argZ, fk_Axis argAxis, double argTheta)
	{
		return GetP()->glRotate(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::GlRotate(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->glRotate(argA, argB, argTheta);
	}

	bool fk_Model::GlRotate(double argAx, double argAy, double argAz,
							double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->glRotate(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::LoRotate(fk_Vector^ argO, fk_Axis argAxis, double argTheta)
	{
		if(!argO) return false;
		return GetP()->loRotate(argO, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::LoRotate(double argX, double argY, double argZ, fk_Axis argAxis, double argTheta)
	{
		return GetP()->loRotate(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::LoRotate(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->loRotate(argA, argB, argTheta);
	}

	bool fk_Model::LoRotate(double argAx, double argAy, double argAz,
							double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->loRotate(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::GlRotateWithVec(fk_Vector^ argO, fk_Axis argAxis, double argTheta)
	{
		if(!argO) return false;
		return GetP()->glRotateWithVec(argO, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::GlRotateWithVec(double argX, double argY, double argZ,
								   fk_Axis argAxis, double argTheta)
	{
		return GetP()->glRotateWithVec(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::GlRotateWithVec(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->glRotateWithVec(argA, argB, argTheta);
	}

	bool fk_Model::GlRotateWithVec(double argAx, double argAy, double argAz,
								   double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->glRotateWithVec(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::LoRotateWithVec(fk_Vector^ argO, fk_Axis argAxis, double argTheta)
	{
		if(!argO) return false;
		return GetP()->loRotateWithVec(argO, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::LoRotateWithVec(double argX, double argY, double argZ,
								   fk_Axis argAxis, double argTheta)
	{
		return GetP()->loRotateWithVec(argX, argY, argZ, fk_Vector::GetAxis(argAxis), argTheta);
	}

	bool fk_Model::LoRotateWithVec(fk_Vector^ argA, fk_Vector^ argB, double argTheta)
	{
		if(!argA || !argB) return false;
		return GetP()->loRotateWithVec(argA, argB, argTheta);
	}

	bool fk_Model::LoRotateWithVec(double argAx, double argAy, double argAz,
								   double argBx, double argBy, double argBz, double argTheta)
	{
		return GetP()->loRotateWithVec(argAx, argAy, argAz, argBx, argBy, argBz, argTheta);
	}

	bool fk_Model::GlTranslate(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glTranslate(argV);
	}

	bool fk_Model::GlTranslate(double argX, double argY, double argZ)
	{
		return GetP()->glTranslate(argX, argY, argZ);
	}

	bool fk_Model::LoTranslate(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->loTranslate(argV);
	}

	bool fk_Model::LoTranslate(double argX, double argY, double argZ)
	{
		return GetP()->loTranslate(argX, argY, argZ);
	}

	bool fk_Model::GlMoveTo(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glMoveTo(argV);
	}

	bool fk_Model::GlMoveTo(double argX, double argY, double argZ)
	{
		return GetP()->glMoveTo(argX, argY, argZ);
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
