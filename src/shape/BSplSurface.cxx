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
#include <FK/BSplSurface.h>
#include <FK/BSplCurve.h>
#include <FK/BSplBase.H>

using namespace std;
using namespace FK;
using namespace FK::BSplBase;

//fk_Line まだ未実装

fk_BSplSurface::fk_BSplSurface(void)
{
	SetObjectType(FK_BSPLSURFACE);
	init();
	return;
}

fk_BSplSurface::~fk_BSplSurface()
{
	uKnot.clear();
	vKnot.clear();
	return;
}

void fk_BSplSurface::init(void)
{
	setOrdinate(3, 3);
	setNum(3, 3);
	return;
}

bool fk_BSplSurface::setOrdinate(int argUOrd, int argVOrd)
{
	if(argUOrd < 3 || argUOrd > 5 ||
	   argVOrd < 3 || argVOrd > 5) {
		return false;
	}

	uOrd = argUOrd;
	vOrd = argVOrd;
	return true;
}
	
bool fk_BSplSurface::setNum(int argUNum, int argVNum)
{
	if(argUNum < uOrd || argVNum < vOrd) return false;

	if(argUNum * argVNum > 32) return false;
	
	uNum = argUNum;
	vNum = argVNum;

	UpdateKnot(uOrd, uNum, uKnot);
	UpdateKnot(vOrd, vNum, vKnot);
	
	setCtrlSize(uNum*vNum);
	ctrlLine.allClear();

	fk_Vector zero(0.0, 0.0, 0.0);

	for(int i = 0; i < uNum*vNum; i++) fk_Surface::setCtrl(i, &zero);
	for(int i = 0; i < 2 * uNum * vNum - uNum - vNum; i++) ctrlLine.pushLine(zero, zero);
	return true;
}

bool fk_BSplSurface::setCtrl(int argUID, int argVID,
							 const fk_Vector &argPos)
{
	if(argUID < 0 || argUID >= uNum ||
	   argVID < 0 || argVID >= vNum) {
		return false;
	}

	fk_Surface::setCtrl(argVID*uNum + argUID, argPos);
	return true;
}

int fk_BSplSurface::getUOrdinate(void)
{
	return uOrd;
}

int fk_BSplSurface::getVOrdinate(void)
{
	return vOrd;
}

int fk_BSplSurface::getUNum(void)
{
	return uNum;
}

int fk_BSplSurface::getVNum(void)
{
	return vNum;
}

fk_Vector fk_BSplSurface::getCtrl(int argUID, int argVID)
{
	if(argUID < 0 || argUID >= uNum ||
	   argVID < 0 || argVID >= vNum) {
		return fk_Vector(0.0, 0.0, 0.0);
	}

	return ctrlPos.getV(argVID*uNum + argUID);
}

fk_Vector fk_BSplSurface::pos(double argU, double argV)
{
	fk_Vector	retPos(0.0, 0.0, 0.0);
	_st			i, j;
	int			index;

	tmpU.resize(_st(uNum));
	tmpV.resize(_st(vNum));
	
	for(i = 0; i < _st(uNum); i++) {
		tmpU[i] = PosBasis(int(i), uOrd, argU, uKnot);
	}
	for(i = 0; i < _st(vNum); i++) {
		tmpV[i] = PosBasis(int(i), vOrd, argV, vKnot);
	}

	for(i = 0; i < _st(vNum); i++) {
		for(j = 0; j < _st(uNum); j++) {
			index = int(i)*uNum + int(j);
			retPos += tmpU[j]*tmpV[i]*ctrlPos.getV(index);
		}
	}

	return retPos;
}

fk_Vector fk_BSplSurface::uDeriv(double argU, double argV)
{
	fk_BSplCurve	uC, vC;

	uC.setOrdinate(uOrd);
	uC.setNum(uNum);
	vC.setOrdinate(vOrd);
	vC.setNum(vNum);

	for(int i = 0; i < uNum; i++) {
		for(int j = 0; j < vNum; j++) {
			vC.setCtrl(j, ctrlPos.getV(j*uNum + i));
		}
		uC.setCtrl(i, vC.pos(argV));
	}
	return uC.diff(argU);
}


fk_Vector fk_BSplSurface::vDeriv(double argU, double argV)
{
	fk_BSplCurve	uC, vC;

	uC.setOrdinate(uOrd);
	uC.setNum(uNum);
	vC.setOrdinate(vOrd);
	vC.setNum(vNum);

	for(int j = 0; j < vNum; j++) {
		for(int i = 0; i < uNum; i++) {
			uC.setCtrl(i, ctrlPos.getV(j*uNum + i));
		}
		vC.setCtrl(j, uC.pos(argU));
	}
	return vC.diff(argV);
}
