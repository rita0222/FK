﻿/****************************************************************************
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
#include <FK/BezCurve.h>
#include <FK/Error.H>

using namespace std;

fk_BezCurve::fk_BezCurve(void)
{
	SetObjectType(FK_BEZCURVE);

	setDegree(3);
	return;
}

fk_BezCurve::~fk_BezCurve()
{
	ctrlPos.clear();

	return;
}

void fk_BezCurve::init(void)
{
	ctrlPos.clear();
	setDegree(3);
}

bool fk_BezCurve::setDegree(int argDeg)
{
	if(argDeg < 2 || argDeg > 4) {
		return false;
	}

	deg = argDeg;
	ctrlPos.resize(static_cast<_st>(deg+1));
	divPos.clear();
	changeFlg = true;
	return true;
}

bool fk_BezCurve::setCtrl(int argID, const fk_Vector &argVec)
{
	if(argID < 0 || argID > deg) {
		return false;
	}

	ctrlPos[static_cast<_st>(argID)] = argVec;
	changeFlg = true;
	return true;
}

int fk_BezCurve::getDegree(void)
{
	return deg;
}

fk_Vector fk_BezCurve::getCtrl(int argID)
{
	fk_Vector	dummy(0.0, 0.0, 0.0);

	if(argID < 0 || argID > deg) {
		return dummy;
	}

	return ctrlPos[static_cast<_st>(argID)];
}

fk_Vector fk_BezCurve::pos(double t)
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

	for(_st i = 0; i <= static_cast<_st>(deg); i++) {
		vec += ctrlPos[i]*tmp[i];
	}

	return vec;
}

fk_Vector fk_BezCurve::diff(double t)
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

	for(_st i = 0; i < static_cast<_st>(deg); i++) {
		vec += (ctrlPos[i+1] - ctrlPos[i])*tmp[i];
	}

	return (vec*double(deg));
}

void fk_BezCurve::MakeDiv(double argT)
{
	_st i, j, d;

	d = _st(deg);

	if(divPos.empty() == true) {
		divPos.resize(d+1);

		for(i = 0; i <= d; ++i) {
			divPos[i].resize(d+1-i);
		}
	}

	for(i = 0; i <= d; ++i) {
		divPos[0][i] = ctrlPos[i];
	}

	for(i = 1; i <= d; ++i) {
		for(j = 0; j <= d - i; ++j) {
			divPos[i][j] = (1.0 - argT) * divPos[i-1][j] + argT * divPos[i-1][j+1];
		}
	}
	return;
}

bool fk_BezCurve::split(double argT, vector<fk_Vector> *argP)
{
	_st		i, d;

	if(argP == nullptr) return false;
	if(argT < -FK_EPS || argT > 1.0 + FK_EPS) return false;

	d = _st(deg);
	argP->clear();

	MakeDiv(argT);
	for(i = 0; i <= d; ++i) argP->push_back(divPos[i][0]);
	for(i = 1; i <= d; ++i) argP->push_back(divPos[d-i][i]);
	return true;
}

		
double fk_BezCurve::CrossZero(fk_Vector &argA, fk_Vector &argB)
{
	if(fabs(argA.y - argB.y) < FK_EPS) return -1.0;

	if((argA.y >= 0.0 && argB.y < 0.0) ||
	   (argA.y < 0.0 && argB.y >= 0.0)) {
		return (argA.y/(argA.y - argB.y))*(argB.x - argA.x) + argA.x;
	}
	return -1.0;
}

bool fk_BezCurve::CrossCH(vector<fk_Vector> *argC, double *argMin, double *argMax)
{
	static _st id[6][2] =
		{{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};

	double min = 1.0;
	double max = 0.0;

	int count = 0;
	for(_st i = 0; i < 6; i++) {
		double ans = CrossZero(argC->at(id[i][0]), argC->at(id[i][1]));
		if(ans < -0.5) continue;
		count++;
		if(ans < min) min = ans;
		if(ans > max) max = ans;
	}
	if(count < 2) return false;

	*argMin = min;
	*argMax = max;
	return true;
}	

void fk_BezCurve::CrossFunc(vector<fk_Vector> *argC, double argMin,
							double argMax, vector<double> *argA)
{
	_st					i, j;
	vector<fk_Vector>	clip, tmpClip;
	fk_BezCurve			curv;
	double				min_o, min_n, max_o, max_n;
	double				t1, t2, t;

	for(i = 0; i <= 3; ++i) {
		clip.push_back(fk_Vector(double(i)/3.0, argC->at(i).y, 0.0));
		curv.setCtrl(int(i), clip[i]);
	}
	min_o = min_n = 0.0;
	max_o = max_n = 1.0;
	
	if(CrossCH(&clip, &min_n, &max_n) == false) return;

	for(j = 0;; ++j) {
		if(j == 4 || max_n - min_n < FK_EPS) break;

		t1 = (min_n - min_o)/(max_o - min_o);
		t2 = (max_n - min_n)/(max_o - min_n);
		
		curv.split(t1, &tmpClip);
		for(i = 0; i <= 3; ++i) curv.setCtrl(int(i), tmpClip[i+3]);

		curv.split(t2, &tmpClip);
		for(i = 0; i <= 3; ++i) {
			curv.setCtrl(int(i), tmpClip[i]);
			clip[i] = tmpClip[i];
		}
		min_o = min_n;
		max_o = max_n;
		CrossCH(&clip, &min_n, &max_n);
	}

	if(max_n - min_n > 0.001) {
		for(i = 0; i <= 3; ++i) {
			clip[i] = fk_Vector(double(i)/3.0, argC->at(i).y, 0.0);
			curv.setCtrl(int(i), clip[i]);
		}
		curv.split(0.5, &tmpClip);
		for(i = 0; i <= 3; ++i) clip[i] = tmpClip[i+3];
		CrossFunc(&tmpClip, argMin, (argMax + argMin)/2.0, argA);
		CrossFunc(&clip, (argMax + argMin)/2.0, argMax, argA);
	} else {
		t = (min_n + max_n)/2.0;
		argA->push_back((1.0 - t) * argMin + t * argMax);
	}
	return;
}

void fk_BezCurve::calcCrossParam(fk_Vector argS, fk_Vector argE, vector<double> *argA)
{
	vector<fk_Vector>	ctrl;
	fk_Vector			p = argS;
	fk_Vector			v = argE - argS;
	fk_Matrix			m;
	v.normalize();

	m[0][0] = m[1][1] = v.x;
	m[0][1] = v.y;
	m[1][0] = -v.y;

	for(_st i = 0; i < ctrlPos.size(); ++i) {
		ctrl.push_back(m * (ctrlPos[i] - argS));
	}
	
	CrossFunc(&ctrl, 0.0, 1.0, argA);
}

void fk_BezCurve::calcCrossParam(fk_Matrix argM, fk_Vector argS,
								 fk_Vector argE, vector<double> *argA)
{
	vector<fk_Vector>	ctrl;
	fk_Vector			p = argS;
	fk_Vector			v = argE - argS;
	fk_Matrix			m;
	v.normalize();

	m[0][0] = m[1][1] = v.x;
	m[0][1] = v.y;
	m[1][0] = -v.y;

	for(_st i = 0; i < ctrlPos.size(); ++i) {
		ctrl.push_back(m * ((argM * ctrlPos[i]) - argS));
	}
	
	CrossFunc(&ctrl, 0.0, 1.0, argA);
}
