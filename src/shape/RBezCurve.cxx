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
#include <FK/RBezCurve.h>
#include <FK/Math.h>
#include <FK/Error.H>

using namespace std;
using namespace FK;

fk_RBezCurve::fk_RBezCurve(void)
{
	SetObjectType(fk_Type::RBEZCURVE);
	w.clear();
	setCtrlSize(5);
	w.resize(5);
	wCtrl.resize(5);
	for(int i = 0; i < 5; ++i) setWeight(i, 1.0);

	setDegree(3);
	return;
}

fk_RBezCurve::~fk_RBezCurve()
{
	return;
}

void fk_RBezCurve::init(void)
{
	setDegree(3);
}

bool fk_RBezCurve::setDegree(int argDeg)
{
	if(argDeg < 2 || argDeg > 4) {
		return false;
	}

	deg = argDeg;
	setCtrlSize(deg+1);
	
	return true;
}

int fk_RBezCurve::getDegree(void)
{
	return deg;
}

bool fk_RBezCurve::setCtrl(int argID, fk_Vector argPos)
{
	if(fk_Curve::setCtrl(argID, argPos) == false) return false;
	wCtrl[_st(argID)] = w[_st(argID)] * argPos;
	return true;
}

bool fk_RBezCurve::setWeight(int argID, double argWeight)
{
	if(fk_Curve::setWeight(argID, argWeight) == false) return false;
	_st i = _st(argID);
	w[i] = argWeight;
	wCtrl[i] = getCtrl(argID) * argWeight;
	return true;
}

double fk_RBezCurve::getWeight(int argID)
{
	if(argID < 0 || argID > getDegree()) return 0.0;
	return double(w[_st(argID)]);
}


fk_Vector fk_RBezCurve::PosBasis(double t)
{
	fk_Vector	vec(0.0, 0.0, 0.0);
	double		tmp[5];

	switch(deg) {
	  case 2:
		tmp[0] = (1.0 - t)*(1.0 - t);
		tmp[1] = 2.0 * (1.0 - t) * t;
		tmp[2] = t * t;
		break;

	  case 3:
		tmp[0] = (1.0 - t)*(1.0 - t)*(1.0 - t);
		tmp[1] = 3.0 * (1.0 - t)*(1.0 - t)*t;
		tmp[2] = 3.0 * (1.0 - t)*t*t;
		tmp[3] = t*t*t;
		break;

	  case 4:
		tmp[0] = (1.0 - t)*(1.0 - t)*(1.0 - t)*(1.0 - t);
		tmp[1] = 4.0 * (1.0 - t)*(1.0 - t)*(1.0 - t)*t;
		tmp[2] = 6.0 * (1.0 - t)*(1.0 - t)*t*t;
		tmp[3] = 4.0 * (1.0 - t)*t*t*t;
		tmp[4] = t*t*t*t;
		break;

	  default:
		return vec;
	}	

	for(_st i = 0; i <= _st(deg); ++i) {
		vec += wCtrl[i] * tmp[i];
	}

	return vec;
}

double fk_RBezCurve::WeightBasis(double t)
{
	double		tmp[5], sumW = 0.0;

	switch(deg) {
	  case 2:
		tmp[0] = (1.0 - t)*(1.0 - t);
		tmp[1] = 2.0 * (1.0 - t) * t;
		tmp[2] = t * t;
		break;

	  case 3:
		tmp[0] = (1.0 - t)*(1.0 - t)*(1.0 - t);
		tmp[1] = 3.0 * (1.0 - t)*(1.0 - t)*t;
		tmp[2] = 3.0 * (1.0 - t)*t*t;
		tmp[3] = t*t*t;
		break;

	  case 4:
		tmp[0] = (1.0 - t)*(1.0 - t)*(1.0 - t)*(1.0 - t);
		tmp[1] = 4.0 * (1.0 - t)*(1.0 - t)*(1.0 - t)*t;
		tmp[2] = 6.0 * (1.0 - t)*(1.0 - t)*t*t;
		tmp[3] = 4.0 * (1.0 - t)*t*t*t;
		tmp[4] = t*t*t*t;
		break;

	  default:
		return 0.0;
	}	

	for(_st i = 0; i <= _st(deg); ++i) {
		sumW += w[i] * tmp[i];
	}

	return sumW;
}

fk_Vector fk_RBezCurve::PosDiff(double t)
{
	fk_Vector	vec(0.0, 0.0, 0.0);
	double		tmp[4];

	switch(deg) {
	  case 2:
		tmp[0] = 1.0 - t;
		tmp[1] = t;
		break;

	  case 3:
		tmp[0] = (1.0 - t)*(1.0 - t);
		tmp[1] = 2.0 * (1.0 - t) * t;
		tmp[2] = t * t;
		break;

	  case 4:
		tmp[0] = (1.0 - t)*(1.0 - t)*(1.0 - t);
		tmp[1] = 3.0 * (1.0 - t)*(1.0 - t)*t;
		tmp[2] = 3.0 * (1.0 - t)*t*t;
		tmp[3] = t*t*t;
		break;

	  default:
		return vec;
	}	

	for(_st i = 0; i < _st(deg); ++i) {
		vec += (wCtrl[i+1] - wCtrl[i]) * tmp[i];
	}

	return (vec*double(deg));
}

double fk_RBezCurve::WeightDiff(double t)
{
	double		tmp[4], sumW = 0.0;

	switch(deg) {
	  case 2:
		tmp[0] = 1.0 - t;
		tmp[1] = t;
		break;

	  case 3:
		tmp[0] = (1.0 - t)*(1.0 - t);
		tmp[1] = 2.0 * (1.0 - t) * t;
		tmp[2] = t * t;
		break;

	  case 4:
		tmp[0] = (1.0 - t)*(1.0 - t)*(1.0 - t);
		tmp[1] = 3.0 * (1.0 - t)*(1.0 - t)*t;
		tmp[2] = 3.0 * (1.0 - t)*t*t;
		tmp[3] = t*t*t;
		break;

	  default:
		return 0.0;
	}	

	for(_st i = 0; i < _st(deg); ++i) {
		sumW += (w[i+1] - w[i]) * tmp[i];
	}
	return (sumW * double(deg));
}

fk_Vector fk_RBezCurve::pos(double t)
{
	return PosBasis(t) / WeightBasis(t);
}

fk_Vector fk_RBezCurve::diff(double t)
{
	fk_Vector C = PosBasis(t);
	fk_Vector dC = PosDiff(t);
	double s = WeightBasis(t);
	double ds = WeightDiff(t);

	return (dC/s) - (ds * C)/(s * s);
}
