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

#define FK_DEF_SIZETYPE
#include <FK/BezSurface.h>
#include <FK/Math.h>
#include <FK/Window.h>

using namespace std;
using namespace FK;

//fk_Line まだ未実装

fk_BezSurface::fk_BezSurface(void)
{
	SetObjectType(fk_Type::BEZSURFACE);
	init();
	return;
}

fk_BezSurface::~fk_BezSurface()
{
	ctrlPos.clear();
	return;
}

void fk_BezSurface::init(void)
{
	deg = 3;
	setCtrlSize(25);
	setCtrlNum(16);
	fk_Vector zero;

	for(int i = 0; i < 2*deg*(deg+1); i++) ctrlLine.pushLine(zero, zero);
	return;
}

bool fk_BezSurface::setDegree(int argDeg)
{
	if(argDeg < 2 || argDeg > 4) return false;

	deg = argDeg;
	fk_Vector zero(0.0, 0.0, 0.0);
	for(int i = 0; i < (deg+1)*(deg+1); i++) fk_Surface::setCtrl(i, zero);
	ctrlLine.allClear();
	for(int i = 0; i < 2*deg*(deg+1); i++) ctrlLine.pushLine(zero, zero);
	return true;
}

int fk_BezSurface::getDegree(void)
{
	return deg;
}

bool fk_BezSurface::setCtrl(int argUID, int argVID,
							const fk_Vector &argPos)
{
	if(argUID < 0 || argUID > deg ||
	   argVID < 0 || argVID > deg) return false;

	fk_Surface::setCtrl(GetID(argUID, argVID), argPos);
	SetLine(argUID, argVID, argPos);
	return true;
}

fk_Vector fk_BezSurface::getCtrl(int argUID, int argVID)
{
	if(argUID < 0 || argUID > deg ||
	   argVID < 0 || argVID > deg) return fk_Vector(0.0, 0.0, 0.0);

	return fk_Surface::getCtrl(GetID(argUID, argVID));
}

fk_Vector fk_BezSurface::pos(double argU, double argV)
{
	fk_Vector	retP(0.0, 0.0, 0.0);
	double		u[5], v[5];

	for(int i = 0; i <= deg; i++) {
		u[i] = Bernstein(deg, i, argU);
		v[i] = Bernstein(deg, i, argV);
	}

	for(int i = 0; i <= deg; i++) {
		for(int j = 0; j <= deg; j++) {
			retP += u[i]*v[j]*ctrlPos.getV(GetID(i, j));
		}
	}

	return retP;
}

fk_Vector fk_BezSurface::uDeriv(double argU, double argV)
{
	fk_Vector	retV(0.0, 0.0, 0.0);
	double		u[4], v[5];

	for(int i = 0; i <= deg-1; i++) {
		u[i] = Bernstein(deg-1, i, argU);
	}

	for(int i = 0; i <= deg; i++) {
		v[i] = Bernstein(deg, i, argV);
	}

	for(int i = 0; i <= deg-1; i++) {
		for(int j = 0; j <= deg; j++) {
			fk_Vector dV = ctrlPos.getV(GetID(i+1, j)) - ctrlPos.getV(GetID(i, j));
			retV += u[i] * v[j] * dV;
		}
	}

	return retV;
}

fk_Vector fk_BezSurface::vDeriv(double argU, double argV)
{
	fk_Vector	retV(0.0, 0.0, 0.0);
	double		u[5], v[4];

	for(int i = 0; i <= deg; i++) {
		u[i] = Bernstein(deg, i, argU);
	}

	for(int i = 0; i <= deg-1; i++) {
		v[i] = Bernstein(deg-1, i, argV);
	}

	for(int i = 0; i <= deg; i++) {
		for(int j = 0; j <= deg-1; j++) {
			fk_Vector dV = ctrlPos.getV(GetID(i, j+1)) - ctrlPos.getV(GetID(i, j));
			retV += u[i]*v[j]*dV;
		}
	}

	return retV;
}

int fk_BezSurface::GetID(int argU, int argV)
{
	return (deg + 1) * argV + argU;
}

// +u = 1, -u = 2, +v = 3, -v = 4
int fk_BezSurface::GetLID(int argU, int argV, int argD)
{
	switch(argD)
	{
	  case 1:
		return deg * argV + argU;

	  case 2:
		return deg * argV + argU - 1;

	  case 3:
		return (deg+1) * deg + deg * argU + argV;

	  case 4:
		return (deg+1) * deg + deg * argU + argV - 1;

	  default:
		break;
	}
	return -1;
}

void fk_BezSurface::SetLine(int argU, int argV, const fk_Vector &argP)
{
	int LID, VID;
	if(argU < deg) {
		LID = GetLID(argU, argV, 1);
		VID = GetID(argU + 1, argV);
		ctrlLine.changeLine(LID, argP, ctrlPos.getV(VID));
	}

	if(argU > 0) {
		LID = GetLID(argU, argV, 2);
		VID = GetID(argU - 1, argV);
		ctrlLine.changeLine(LID, ctrlPos.getV(VID), argP);
	}

	if(argV < deg) {
		LID = GetLID(argU, argV, 3);
		VID = GetID(argU, argV + 1);
		ctrlLine.changeLine(LID, argP, ctrlPos.getV(VID));
	}

	if(argV > 0) {
		LID = GetLID(argU, argV, 4);
		VID = GetID(argU, argV - 1);
		ctrlLine.changeLine(LID, ctrlPos.getV(VID), argP);
	}
	return;
}
