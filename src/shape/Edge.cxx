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

#include <FK/Edge.h>
#include <FK/Half.h>
#include <FK/Curve.h>
#include <FK/Error.H>
#include <sstream>

using namespace std;
using namespace FK;

fk_Edge::fk_Edge(int argID)
{
	DB = nullptr;
	SetID(argID);
	return;
}

fk_Edge::~fk_Edge()
{
	return;
}

void fk_Edge::Init(fk_DataBase *argDB, int argID)
{
	InitTopology(argDB, argID, fk_TopologyType::EDGE);
	leftHalf = FK_UNDEFINED;
	rightHalf = FK_UNDEFINED;
	curv = nullptr;
	width = -1.0;

	return;
}

fk_Half * fk_Edge::getLeftHalf(void) const
{
	if(DB == nullptr) return nullptr;
	return DB->GetHData(leftHalf);
}

fk_Half * fk_Edge::getRightHalf(void) const
{
	if(DB == nullptr) return nullptr;
	return DB->GetHData(rightHalf);
}

int fk_Edge::SetLeftHalf(int argHf)
{
	int retHf = leftHalf;
	leftHalf = argHf;
	return retHf;
}

int fk_Edge::SetRightHalf(int argHf)
{
	int retHf = rightHalf;
	rightHalf = argHf;
	return retHf;
}

void fk_Edge::SwapHalf(void)
{
	int tmpH = rightHalf;
	rightHalf = leftHalf;
	leftHalf = tmpH;
	return;
}

double fk_Edge::getDrawWidth(void) const
{
	return width;
}

void fk_Edge::setDrawWidth(double argWidth)
{
	if(argWidth < 0.0) {
		width = -1.0;
	} else {
		width = argWidth;
	}
	return;
}

void fk_Edge::Print(void) const
{
	stringstream	ss;

	ss << "Edge[" << getID() << "] = {";
	fk_PutError(ss.str());
	ss.clear();
	
	ss << "\tlH = " << leftHalf;
	fk_PutError(ss.str());
	ss.clear();

	ss << "\trH = " << rightHalf;
	fk_PutError(ss.str());
	ss.clear();

	fk_PutError("}");

	return;
}

bool fk_Edge::Check(void) const
{
	bool			retBool = true;
	stringstream	ss;

	if(DB == nullptr) return false;

	if(leftHalf != FK_UNDEFINED) {
		if(DB->GetHData(leftHalf)->getParentEdge() != this) {
			ss << "Edge[" << getID() << "] ... leftH[";
			ss << leftHalf << "] ERROR!!";
			fk_PutError("fk_Edge", "Check", 1, ss.str());
			retBool = false;
		}
	}

	if(rightHalf != FK_UNDEFINED) {
		if(DB->GetHData(rightHalf)->getParentEdge() != this) {
			ss << "Edge[" << getID() << "] ... rightH[";
			ss << rightHalf << "] ERROR!!";
			fk_PutError("fk_Edge", "Check", 2, ss.str());
			retBool = false;
		}
	}

	return retBool;
}

bool fk_Edge::Compare(fk_Edge *argE) const
{
	if(DB == nullptr) return false;
	if(argE == nullptr) return false;
	if(argE == this) return true;
	if(DB != argE->DB) return false;
	if(getID() != argE->getID()) return false;
	if(getID() == FK_UNDEFINED) return true;

	if(leftHalf != argE->leftHalf) return false;
	if(rightHalf != argE->rightHalf) return false;
	return true;
}

void fk_Edge::setCurveGeometry(fk_Curve *argCurv)
{
	curv = argCurv;

	return;
}

fk_Curve * fk_Edge::getCurveGeometry(void)
{
	return curv;
}
