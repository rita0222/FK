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
#include "ShapeViewer_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::FK::fk_ShapeViewer * fk_ShapeViewer::GetP(void)
	{
		return (::FK::fk_ShapeViewer *)(pBase);
	}

	fk_ShapeViewer::fk_ShapeViewer() : fk_BaseObject(false)
	{
		pBase = new ::FK::fk_ShapeViewer();
	}

	fk_ShapeViewer::fk_ShapeViewer(bool argNewFlg) : fk_BaseObject(false)
	{
		if(argNewFlg == true) pBase = new ::FK::fk_ShapeViewer();
	}

	fk_ShapeViewer::fk_ShapeViewer(int argW, int argH) : fk_BaseObject(false)
	{
		pBase = new ::FK::fk_ShapeViewer(argW, argH);
	}

	fk_ShapeViewer::~fk_ShapeViewer()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_ShapeViewer::!fk_ShapeViewer()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) {
			GetP()->SetFinalizeMode();
			delete GetP();
		}
		pBase = nullptr;
	}

	//////////////////////////////////////////////////////////////////////
	
	void fk_ShapeViewer::WindowSize::set(fk_Dimension^ argD)
	{
		if(!argD) return;
		GetP()->setWindowSize(argD->pDim->w, argD->pDim->h);
	}

	void fk_ShapeViewer::Shape::set(fk_Shape^ argShape)
	{
		if(!argShape) return;
		GetP()->setShape(argShape->GetP());
	}

	fk_Shape^ fk_ShapeViewer::Shape::get()
	{
		fk_Shape^ S = gcnew fk_Shape(false);
		S->pBase = GetP()->getShape();
		S->dFlg = false;
		return S;
	}

	int fk_ShapeViewer::ModelNum::get(void)
	{
		return GetP()->getModelNum();
	}

	void fk_ShapeViewer::DrawMode::set(fk_DrawMode argMode)
	{
		unsigned int mode = static_cast<unsigned int>(argMode);
		GetP()->setDrawMode(mode);
	}

	fk_DrawMode fk_ShapeViewer::DrawMode::get(void)
	{
		return static_cast<fk_DrawMode>(GetP()->getDrawMode());
	}

	void fk_ShapeViewer::ElementMode::set(fk_ElementMode argMode)
	{
		switch (argMode) {
		case fk_ElementMode::NONE:
			GetP()->setElementMode(::FK::FK_ELEM_NONE);
			break;

		case fk_ElementMode::MODEL:
			GetP()->setElementMode(::FK::FK_ELEM_MODEL);
			break;

		case fk_ElementMode::ELEMENT:
			GetP()->setElementMode(::FK::FK_ELEM_ELEMENT);
			break;

		default:
			break;
		}
		return;
	}

	fk_ElementMode fk_ShapeViewer::ElementMode::get(void)
	{
		switch (GetP()->getElementMode()) {
		case ::FK::FK_ELEM_MODEL:
			return fk_ElementMode::MODEL;

		case ::FK::FK_ELEM_ELEMENT:
			return fk_ElementMode::ELEMENT;

		default:
			break;
		}
		return fk_ElementMode::NONE;
	}

	void fk_ShapeViewer::BlendStatus::set(bool argMode)
	{
		GetP()->setBlendStatus(argMode);
	}

	bool fk_ShapeViewer::BlendStatus::get(void)
	{
		return GetP()->getBlendStatus();
	}

	void fk_ShapeViewer::BGColor::set(fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setBGColor(*argCol->pCol);
	}

	fk_Color^ fk_ShapeViewer::BGColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getBGColor();
		return C;
	}

	void fk_ShapeViewer::AxisMode::set(bool argMode)
	{
		GetP()->setAxisMode(argMode);
	}

	bool fk_ShapeViewer::AxisMode::get(void)
	{
		return GetP()->getAxisMode();
	}

	void fk_ShapeViewer::AxisScale::set(double argScale)
	{
		GetP()->setAxisScale(argScale);
	}

	double fk_ShapeViewer::AxisScale::get(void)
	{
		return GetP()->getAxisScale();
	}

	fk_Vector^ fk_ShapeViewer::Center::get(void)
	{
		return gcnew fk_Vector(GetP()->getCenter());
	}

	void fk_ShapeViewer::Head::set(double argAngle)
	{
		GetP()->setHead(argAngle);
	}

	double fk_ShapeViewer::Head::get(void)
	{
		return GetP()->getHead();
	}

	void fk_ShapeViewer::Pitch::set(double argAngle)
	{
		GetP()->setPitch(argAngle);
	}

	double fk_ShapeViewer::Pitch::get(void)
	{
		return GetP()->getPitch();
	}

	void fk_ShapeViewer::Bank::set(double argAngle)
	{
		return GetP()->setBank(argAngle);
	}

	double fk_ShapeViewer::Bank::get(void)
	{
		return GetP()->getBank();
	}

	void fk_ShapeViewer::Scale::set(double argScale)
	{
		GetP()->setScale(argScale);
	}

	double fk_ShapeViewer::Scale::get(void)
	{
		return GetP()->getScale();
	}

	//////////////////////////////////////////////////////////////////////

	bool fk_ShapeViewer::Draw(void)
	{
		return GetP()->draw();
	}

	void fk_ShapeViewer::SetShape(int argID, fk_Shape^ argShape)
	{
		if(!argShape) return;
		GetP()->setShape(argID, argShape->GetP());
	}

	fk_Shape^ fk_ShapeViewer::GetShape(int argID)
	{
		fk_Shape^ S = gcnew fk_Shape(false);
		S->pBase = GetP()->getShape(argID);
		S->dFlg = false;
		return S;
	}

	void fk_ShapeViewer::ClearModel(void)
	{
		GetP()->clearModel();
	}

	void fk_ShapeViewer::SetDrawMode(int argID, fk_DrawMode argMode)
	{
		unsigned int mode = static_cast<unsigned int>(argMode);
		GetP()->setDrawMode(argID, mode);
	}

	fk_DrawMode fk_ShapeViewer::GetDrawMode(int argID)
	{
		return static_cast<fk_DrawMode>(GetP()->getDrawMode(argID));
	}

	void fk_ShapeViewer::SetElementMode(int argID, fk_ElementMode argMode)
	{
		switch (argMode) {
		case fk_ElementMode::NONE:
			GetP()->setElementMode(argID, ::FK::FK_ELEM_NONE);
			break;

		case fk_ElementMode::MODEL:
			GetP()->setElementMode(argID, ::FK::FK_ELEM_MODEL);
			break;

		case fk_ElementMode::ELEMENT:
			GetP()->setElementMode(argID, ::FK::FK_ELEM_ELEMENT);
			break;

		default:
			break;
		}
		return;		
	}

	fk_ElementMode fk_ShapeViewer::GetElementMode(int argID)
	{
		switch (GetP()->getElementMode(argID)) {
		case ::FK::FK_ELEM_MODEL:
			return fk_ElementMode::MODEL;

		case ::FK::FK_ELEM_ELEMENT:
			return fk_ElementMode::ELEMENT;

		default:
			break;
		}

		return fk_ElementMode::NONE;
	}

	void fk_ShapeViewer::SetLineWidth(int argID, double argWidth)
	{
		GetP()->setLineWidth(argID, argWidth);
	}

	double fk_ShapeViewer::GetLineWidth(int argID)
	{
		return GetP()->getLineWidth(argID);
	}

	void fk_ShapeViewer::SetPointSize(int argID, double argSize)
	{
		GetP()->setPointSize(argID, argSize);
	}

	double fk_ShapeViewer::GetPointSize(int argID)
	{
		return GetP()->getPointSize(argID);
	}

	void fk_ShapeViewer::SetMaterial(int argID, fk_Material^ argMat)
	{
		if(!argMat) return;
		GetP()->setMaterial(argID, *argMat->pMat);
	}

	void fk_ShapeViewer::SetEdgeColor(int argID, fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setEdgeColor(argID, *argCol->pCol);
	}

	void fk_ShapeViewer::SetVertexColor(int argID, fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setVertexColor(argID, *argCol->pCol);
	}

	void fk_ShapeViewer::SetPosition(int argID, fk_Vector^ argPos)
	{
		if(!argPos) return;
		GetP()->setPosition(argID, argPos);
	}

	void fk_ShapeViewer::SetPosition(int argID, double argX, double argY, double argZ)
	{
		GetP()->setPosition(argID, argX, argY, argZ);
	}

	void fk_ShapeViewer::SetAngle(int argID, fk_Angle^ argAngle)
	{
		if(!argAngle) return;
		GetP()->setAngle(argID, argAngle);
	}

	void fk_ShapeViewer::SetAngle(int argID, double argH, double argP, double argB)
	{
		GetP()->setAngle(argID, argH, argP, argB);
	}

	void fk_ShapeViewer::SetVec(int argID, fk_Vector^ argVec)
	{
		if(!argVec) return;
		GetP()->setVec(argID, argVec);
	}

	void fk_ShapeViewer::SetVec(int argID, double argX, double argY, double argZ)
	{
		GetP()->setVec(argID, argX, argY, argZ);
	}

	void fk_ShapeViewer::SetUpvec(int argID, fk_Vector^ argVec)
	{
		if(!argVec) return;
		GetP()->setUpvec(argID, argVec);
	}

	void fk_ShapeViewer::SetUpvec(int argID, double argX, double argY, double argZ)
	{
		GetP()->setUpvec(argID, argX, argY, argZ);
	}

	bool fk_ShapeViewer::SnapImage(String^ argFileName, fk_ImageType argFormat)
	{
		string fileName = marshal_as<string>(argFileName);
		switch(argFormat) {
		  case fk_ImageType::BMP:
			return GetP()->snapImage(fileName, ::FK::FK_IMAGE_BMP);

		  case fk_ImageType::PNG:
			return GetP()->snapImage(fileName, ::FK::FK_IMAGE_PNG);

		  case fk_ImageType::JPG:
			return GetP()->snapImage(fileName, ::FK::FK_IMAGE_JPG);

		  default:
			break;
		}
		return false;
	}

	bool fk_ShapeViewer::SnapImage(fk_Image^ argImage)
	{
		if(!argImage) return false;
		return GetP()->snapImage(argImage->GetP());
	}
}


