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

﻿#include "Model_CLI.h"

namespace FK_CLI {

	::fk_MatrixAdmin * fk_MatrixAdmin::GetP(void)
	{
		return (::fk_MatrixAdmin *)(pBase);
	}

	fk_MatrixAdmin::fk_MatrixAdmin(bool argNewFlg) : fk_BaseObject(false)
	{
	}

	fk_MatrixAdmin::~fk_MatrixAdmin()
	{
		this->!fk_MatrixAdmin();
	}

	fk_MatrixAdmin::!fk_MatrixAdmin()
	{
	}

	fk_Vector^ fk_MatrixAdmin::Position::get(void)
	{
		return gcnew fk_Vector(GetP()->getPosition());
	}

	fk_Vector^ fk_MatrixAdmin::Vec::get(void)
	{
		return gcnew fk_Vector(GetP()->getVec());
	}

	fk_Vector^ fk_MatrixAdmin::Upvec::get(void)
	{
		return gcnew fk_Vector(GetP()->getUpvec());
	}

	fk_Angle^ fk_MatrixAdmin::Angle::get(void)
	{
		return gcnew fk_Angle(GetP()->getAngle());
	}

	fk_Matrix^ fk_MatrixAdmin::Matrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getMatrix();
		return M;
	}

	fk_Matrix^ fk_MatrixAdmin::InvMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInvMatrix();
		return M;
	}

	fk_Matrix^ fk_MatrixAdmin::BaseMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getBaseMatrix();
		return M;
	}

	fk_Matrix^ fk_MatrixAdmin::InvBaseMatrix::get(void)
	{
		fk_Matrix^ M = gcnew fk_Matrix();
		*M->pMatrix = GetP()->getInvBaseMatrix();
		return M;
	}

	bool fk_MatrixAdmin::ScaleMode::get(void)
	{
		return GetP()->getScaleMode();
	}

	void fk_MatrixAdmin::Scale::set(double argScale)
	{
		GetP()->setScale(argScale);
	}

	double fk_MatrixAdmin::Scale::get(void)
	{
		return GetP()->getScale();
	}

	bool fk_MatrixAdmin::SetScale(double argScale, fk_Axis argAxis)
	{
		return GetP()->setScale(argScale, fk_Vector::GetAxis(argAxis));
	}

	bool fk_MatrixAdmin::SetScale(double argX, double argY, double argZ)
	{
		return GetP()->setScale(argX, argY, argZ);
	}
	bool fk_MatrixAdmin::PrdScale(double argScale)
	{
		return GetP()->prdScale(argScale);
	}

	bool fk_MatrixAdmin::PrdScale(double argScale, fk_Axis argAxis)
	{
		return GetP()->prdScale(argScale, fk_Vector::GetAxis(argAxis));
	}

	bool fk_MatrixAdmin::PrdScale(double argX, double argY, double argZ)
	{
		return GetP()->prdScale(argX, argY, argZ);
	}

	double fk_MatrixAdmin::GetScale(fk_Axis argAxis)
	{
		return GetP()->getScale(fk_Vector::GetAxis(argAxis));
	}

	bool fk_MatrixAdmin::GlFocus(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glFocus(argV->x_, argV->y_, argV->z_);
	}

	bool fk_MatrixAdmin::GlFocus(double argX, double argY, double argZ)
	{
		return GetP()->glFocus(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::LoFocus(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->loFocus(argV->x_, argV->y_, argV->z_);
	}

	bool fk_MatrixAdmin::LoFocus(double argX, double argY, double argZ)
	{
		return GetP()->loFocus(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::GlVec(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glVec(argV->x_, argV->y_, argV->z_);
	}

	bool fk_MatrixAdmin::GlVec(double argX, double argY, double argZ)
	{
		return GetP()->glVec(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::GlUpvec(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->glUpvec(argV->x_, argV->y_, argV->z_);
	}

	bool fk_MatrixAdmin::GlUpvec(double argX, double argY, double argZ)
	{
		return GetP()->glUpvec(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::LoUpvec(fk_Vector^ argV)
	{
		if(!argV) return false;
		return GetP()->loUpvec(argV->x_, argV->y_, argV->z_);
	}

	bool fk_MatrixAdmin::LoUpvec(double argX, double argY, double argZ)
	{
		return GetP()->loUpvec(argX, argY, argZ);
	}

	bool fk_MatrixAdmin::GlAngle(fk_Angle^ argAngle)
	{
		if(!argAngle) return false;
		return GetP()->glAngle(argAngle);
	}

	bool fk_MatrixAdmin::GlAngle(double argH, double argP, double argB)
	{
		return GetP()->glAngle(argH, argP, argB);
	}

	bool fk_MatrixAdmin::LoAngle(fk_Angle^ argAngle)
	{
		if(!argAngle) return false;
		return GetP()->loAngle(argAngle);
	}

	bool fk_MatrixAdmin::LoAngle(double argH, double argP, double argB)
	{
		return GetP()->loAngle(argH, argP, argB);
	}
}
