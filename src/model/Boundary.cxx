/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
#include <FK/Model.h>

using namespace FK;

fk_Boundary::fk_Boundary(fk_ObjectType argType)
	: fk_MatrixAdmin(argType)
{
	bMode = FK_B_NONE;
	bDrawToggle = false;
	bLineWidth = 1.0;
	bLineColor = nullptr;
	bIntLineColor = nullptr;

	bSphereRad = 0.0;
	bAABBSize = nullptr;
	bOBBSize = nullptr;
	bCapSPos = nullptr;
	bCapEPos = nullptr;
	bCapRad = 0.0;

	bSphere = nullptr;
	bAABB = nullptr;
	bOBB = nullptr;
	bCapsule = nullptr;
	bCapModel = nullptr;

	return;
}

fk_Boundary::~fk_Boundary()
{
	delete bLineColor;
	delete bIntLineColor;

	delete bAABBSize;
	delete bOBBSize;
	delete bCapSPos;
	delete bCapEPos;

	delete bSphere;
	delete bAABB;
	delete bOBB;
	delete bCapsule;
	delete bCapModel;

	return;
}

void fk_Boundary::setSphere(double argRadius)
{
	if(argRadius <= 0.0) {
		bSphereRad = 0.0;
	} else {
		bSphereRad = argRadius;
	}

	if(bSphere == nullptr) {
		bSphere = new fk_IndexFaceSet;
		bSphere->makeSphere(4, bSphereRad);
	} else {
		bSphere->setSphereRadius(bSphereRad);
	}

	return;
}

double fk_Boundary::getSphere(void)
{
	return bSphereRad;
}

void fk_Boundary::setAABBSize(double argX, double argY, double argZ)
{
	if(bAABBSize == nullptr) bAABBSize = new fk_Vector;
	bAABBSize->set(argX, argY, argZ);

	if(bAABB == nullptr) {
		bAABB = new fk_IndexFaceSet;
		bAABB->makeBlock(argX, argY, argZ);
	} else {
		bAABB->setBlockSize(argX, argY, argZ);
	}

	return;
}

void fk_Boundary::setAABBSize(fk_Vector argV)
{
	setAABBSize(argV.x, argV.y, argV.z);
	return;
}

fk_Vector fk_Boundary::getAABBSize(void)
{
	if(bAABBSize == nullptr) return fk_Vector(0.0, 0.0, 0.0);
	return (*bAABBSize);
}

void fk_Boundary::setOBBSize(double argX, double argY, double argZ)
{
	if(bOBBSize == nullptr) bOBBSize = new fk_Vector;
	bOBBSize->set(argX, argY, argZ);

	if(bOBB == nullptr) {
		bOBB = new fk_IndexFaceSet;
		bOBB->makeBlock(argX, argY, argZ);
	} else {
		bOBB->setBlockSize(argX, argY, argZ);
	}

	return;
}

void fk_Boundary::setOBBSize(fk_Vector argV)
{
	setOBBSize(argV.x, argV.y, argV.z);
	return;
}

fk_Vector fk_Boundary::getOBBSize(void)
{
	if(bOBBSize == nullptr) return fk_Vector(0.0, 0.0, 0.0);
	return (*bOBBSize);
}

void fk_Boundary::setCapsule(fk_Vector argS, fk_Vector argE, double argRad)
{
	fk_Vector	pos, vec;

	if(bCapSPos == nullptr) bCapSPos = new fk_Vector;
	if(bCapEPos == nullptr) bCapEPos = new fk_Vector;
	if(argRad < 0.0) return;
	if(argS == argE) return;
	*bCapSPos = argS;
	*bCapEPos = argE;
	bCapRad = argRad;

	if(bCapModel == nullptr) bCapModel = new fk_Model;

	pos = (argS + argE)/2.0;
	vec = argE - argS;
	
	bCapModel->glMoveTo(pos);
	bCapModel->glVec(vec);

	if(bCapsule == nullptr) {
		bCapsule = new fk_IndexFaceSet;
		bCapsule->makeCapsule(4, vec.dist(), bCapRad);
	} else {
		bCapsule->setCapsuleSize(vec.dist(), bCapRad);
	}
}

double fk_Boundary::getCapsuleRadius(void)
{
	return bCapRad;
}

double fk_Boundary::getCapsuleLength(void)
{
	if(bCapSPos == nullptr || bCapEPos == nullptr) return 0.0;
	return ((*bCapSPos) - (*bCapEPos)).dist();
}

fk_Vector fk_Boundary::getCapsuleStartPos(void)
{
	if(bCapSPos == nullptr) return fk_Vector(0.0, 0.0, 0.0);
	return (*bCapSPos);
}

fk_Vector fk_Boundary::getCapsuleEndPos(void)
{
	if(bCapEPos == nullptr) return fk_Vector(0.0, 0.0, 0.0);
	return (*bCapEPos);
}

void fk_Boundary::setBMode(fk_BoundaryMode argMode)
{
	bMode = argMode;
}

fk_BoundaryMode fk_Boundary::getBMode(void)
{
	return bMode;
}

void fk_Boundary::setBDrawToggle(bool argToggle)
{
	bDrawToggle = argToggle;
}

bool fk_Boundary::getBDrawToggle(void)
{
	return bDrawToggle;
}

void fk_Boundary::setBLineColor(fk_Color argCol)
{
	if(bLineColor == nullptr) bLineColor = new fk_Color;
	*bLineColor = argCol;
}

fk_Color * fk_Boundary::getBLineColor(void)
{
	if(bLineColor == nullptr) bLineColor = new fk_Color;
	return bLineColor;
}

void fk_Boundary::setBIntLineColor(fk_Color argCol)
{
	if(bIntLineColor == nullptr) bIntLineColor = new fk_Color;
	*bIntLineColor = argCol;
}

fk_Color * fk_Boundary::getBIntLineColor(void)
{
	if(bIntLineColor == nullptr) bIntLineColor = new fk_Color;
	return bIntLineColor;
}

void fk_Boundary::setBLineWidth(double argWidth)
{
	bLineWidth = argWidth;
}

double fk_Boundary::getBLineWidth(void)
{
	return bLineWidth;
}

fk_IndexFaceSet * fk_Boundary::GetBShape(void)
{
	switch(bMode) {
	  case FK_B_SPHERE:
		return bSphere;

	  case FK_B_AABB:
		return bAABB;

	  case FK_B_OBB:
		return bOBB;

	  case FK_B_CAPSULE:
		return bCapsule;

	  case FK_B_NONE:
	  default:
		break;
	}
	return nullptr;
}

fk_Model * fk_Boundary::GetCapsuleModel(void)
{
	if(bCapModel == nullptr) bCapModel = new fk_Model;
	return bCapModel;
}

