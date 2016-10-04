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

#define FK_DEF_SIZETYPE
#include <FK/BezSurface.h>

using namespace std;

fk_BezSurface::fk_BezSurface(void)
{
	SetObjectType(FK_BEZSURFACE);

	init();
	return;
}

fk_BezSurface::~fk_BezSurface()
{
	ctrlPos.clear();
	return;
}

double fk_BezSurface::bezier(int argN, int argI, double argT)
{
	double		t = argT;
	double		ret = 0.0;

	switch(argN) {
	  case 1:
		switch(argI) {
		  case 0:
			ret = 1.0 - t;
			break;

		  case 1:
			ret = t;
			break;

		  default:
			break;
		}
		break;

	  case 2:
		switch(argI) {
		  case 0:
			ret = (1.0 - t)*(1.0 - t);
			break;

		  case 1:
			ret = 2.0 * (1.0 - t) * t;
			break;

		  case 2:
			ret = t * t;
			break;

		  default:
			break;
		}
		break;

	  case 3:
		switch(argI) {
		  case 0:
			ret = (1.0 - t)*(1.0 - t)*(1.0 - t);
			break;

		  case 1:
			ret = 3.0 * (1.0 - t)*(1.0 - t)*t;
			break;

		  case 2:
			ret = 3.0 * (1.0 - t)*t*t;
			break;

		  case 3:
			ret = t*t*t;
			break;

		  default:
			break;
		}
		break;

	  case 4:
		switch(argI) {
		  case 0:
			ret = (1.0 - t)*(1.0 - t)*(1.0 - t)*(1.0 - t);
			break;

		  case 1:
			ret = 4.0 * (1.0 - t)*(1.0 - t)*(1.0 - t)*t;
			break;

		  case 2:
			ret = 6.0 * (1.0 - t)*(1.0 - t)*t*t;
			break;

		  case 3:
			ret = 4.0 * (1.0 - t)*t*t*t;
			break;

		  case 4:
			ret = t*t*t*t;
			break;

		  default:
			break;
		}
		break;

	  default:
		break;
	}

	return ret;
}

void fk_BezSurface::init(void)
{
	uDeg = vDeg = 3;
	ctrlPos.resize(16);
	return;
}

bool fk_BezSurface::setDegree(int argUD, int argVD)
{
	if(argUD < 2 || argUD > 4 ||
	   argVD < 2 || argVD > 4) return false;

	uDeg = argUD;
	vDeg = argVD;

	ctrlPos.resize(static_cast<_st>((uDeg+1)*(vDeg+1)));
	for(_st i = 0; i < static_cast<_st>((uDeg+1)*(vDeg+1)); i++) {
		ctrlPos[i].set(0.0, 0.0, 0.0);
	}
	return true;
}

bool fk_BezSurface::setCtrl(int argUID, int argVID,
							const fk_Vector &argPos)
{
	if(argUID < 0 || argUID >= uDeg ||
	   argVID < 0 || argVID >= vDeg) return false;

	ctrlPos[static_cast<_st>((vDeg+1)*argVID + argUID)] = argPos;
	return true;
}

fk_Vector fk_BezSurface::pos(double argU, double argV)
{
	fk_Vector	retP(0.0, 0.0, 0.0);
	_st			i, j, index;
	double		u[5], v[5];

	for(j = 0; j <= static_cast<_st>(uDeg); j++) {
		u[j] = bezier(uDeg, static_cast<int>(j), argU);
	}
	for(i = 0; i <= static_cast<_st>(vDeg); i++) {
		v[i] = bezier(vDeg, static_cast<int>(i), argV);
	}

	for(i = 0; i <= static_cast<_st>(vDeg); i++) {
		for(j = 0; j <= static_cast<_st>(uDeg); j++) {
			index = static_cast<_st>(vDeg+1)*i + j;
			retP += u[j]*v[i]*ctrlPos[index];
		}
	}

	return retP;
}

fk_Vector fk_BezSurface::uDeriv(double argU, double argV)
{
	fk_Vector	retV(0.0, 0.0, 0.0);
	_st			i, j, index;
	double		u[4], v[5];

	for(j = 0; j <= static_cast<_st>(uDeg-1); j++) {
		u[j] = bezier(uDeg-1, static_cast<int>(j), argU);
	}
	for(i = 0; i <= static_cast<_st>(vDeg); i++) {
		v[i] = bezier(vDeg, static_cast<int>(i), argV);
	}

	for(i = 0; i <= static_cast<_st>(vDeg); i++) {
		for(j = 0; j <= static_cast<_st>(uDeg-1); j++) {
			index = static_cast<_st>(vDeg+1)*i + j;
			retV += u[j]*v[i]*(ctrlPos[index+1] - ctrlPos[index]);
		}
	}

	return retV;
}

fk_Vector fk_BezSurface::vDeriv(double argU, double argV)
{
	fk_Vector	retV(0.0, 0.0, 0.0);
	_st			i, j, index1, index2;
	double		u[5], v[4];

	for(j = 0; j <= static_cast<_st>(uDeg); j++) {
		u[j] = bezier(uDeg, static_cast<int>(j), argU);
	}
	for(i = 0; i <= static_cast<_st>(vDeg-1); i++) {
		v[i] = bezier(vDeg-1, static_cast<int>(i), argV);
	}

	for(i = 0; i <= static_cast<_st>(vDeg-1); i++) {
		for(j = 0; j <= static_cast<_st>(uDeg); j++) {
			index1 = static_cast<_st>(vDeg+1)*i + j;
			index2 = index1 + static_cast<_st>(vDeg) + 1;
			retV += u[j]*v[i]*(ctrlPos[index2] - ctrlPos[index1]);
		}
	}

	return retV;
}
