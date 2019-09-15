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
#include <FK/Gregory.h>
#include <FK/Math.h>
#include <FK/Window.h>

using namespace std;
using namespace FK;

vector< vector< tuple<int, int, bool> > >		fk_Gregory::CLinePos;

fk_Gregory::fk_Gregory(void)
{
	SetObjectType(fk_Type::BEZSURFACE);
	init();
	return;
}

fk_Gregory::~fk_Gregory()
{
	ctrlPos.clear();
	return;
}

int fk_Gregory::GetCID(fk_SurfDirection argD, int argID)
{
	if(argID < 0 || argID > 3) return -1;

	switch(argD) {
	  case fk_SurfDirection::U_S:
		return argID;

	  case fk_SurfDirection::U_E:
		return argID + 4;
		
	  case fk_SurfDirection::V_S:
		switch(argID) {
		  case 0:
			return 0;

		  case 3:
			return 4;

		  default:
			break;
		}
		return argID + 7;
		
	  case fk_SurfDirection::V_E:
		switch(argID) {
		  case 0:
			return 3;

		  case 3:
			return 7;

		  default:
			break;
		}
		return argID + 9;

	  default:
		break;
	}
	return -1;
}

int fk_Gregory::GetDID(fk_SurfDirection argD, int argID)
{
	if(argID != 1 && argID != 2) return -1;
	switch(argD){
	  case fk_SurfDirection::U_S:
		return argID + 11;
		
	  case fk_SurfDirection::U_E:
		return argID + 13;
		
	  case fk_SurfDirection::V_S:
		return argID + 15;
		
	  case fk_SurfDirection::V_E:
		return argID + 17;

	  default:
		break;
	}
	return -1;
}

		
void fk_Gregory::SetCLine(fk_SurfDirection argD, int argID, const fk_Vector &argP)
{
	fk_Vector S, E;
	int lineID;
	int alt;
	bool arrow;

	_st id = _st(static_cast<int>(argD) * 4 + argID);
	for(auto line : CLinePos[id]) {
		lineID = get<0>(line);
		alt = get<1>(line);
		arrow = get<2>(line);
		if(arrow == true) {
			S = argP;
			E = ctrlPos.getV(alt);
		} else {
			S = ctrlPos.getV(alt);
			E = argP;
		}
		ctrlLine.changeLine(lineID, S, E);
	}
}


void fk_Gregory::init(void)
{
	setCtrlSize(20);
	setCtrlNum(20);
	fk_Vector zero;

	for(int i = 0; i < 20; i++) ctrlLine.pushLine(zero, zero);
	if(CLinePos.empty() == true) MakeCLinePos();
	return;
}

void fk_Gregory::MakeCLinePos(void)
{
	tuple<int, int, bool> line;
	vector< tuple<int, int, bool> > array;
	
	CLinePos.clear();

	// (U_S, 0)
	array.clear();
	line = make_tuple(0, 1, true);
	array.push_back(line);
	line = make_tuple(6, 8, true);
	array.push_back(line);
	CLinePos.push_back(array);

	// (U_S, 1)
	array.clear();
	line = make_tuple(0, 0, false);
	array.push_back(line);
	line = make_tuple(1, 2, true);
	array.push_back(line);
	line = make_tuple(12, 12, true);
	array.push_back(line);
	CLinePos.push_back(array);
	
	// (U_S, 2)
	array.clear();
	line = make_tuple(1, 1, false);
	array.push_back(line);
	line = make_tuple(2, 3, true);
	array.push_back(line);
	line = make_tuple(13, 13, true);
	array.push_back(line);
	CLinePos.push_back(array);

	// (U_S, 3)
	array.clear();
	line = make_tuple(2, 2, false);
	array.push_back(line);
	line = make_tuple(9, 10, true);
	array.push_back(line);
	CLinePos.push_back(array);
	
	// (U_E, 0)
	array.clear();
	line = make_tuple(3, 5, true);
	array.push_back(line);
	line = make_tuple(8, 9, false);
	array.push_back(line);
	CLinePos.push_back(array);

	// (U_E, 1)
	array.clear();
	line = make_tuple(3, 4, false);
	array.push_back(line);
	line = make_tuple(4, 6, true);
	array.push_back(line);
	line = make_tuple(14, 14, true);
	array.push_back(line);
	CLinePos.push_back(array);
	
	// (U_E, 2)
	array.clear();
	line = make_tuple(4, 5, false);
	array.push_back(line);
	line = make_tuple(5, 7, true);
	array.push_back(line);
	line = make_tuple(15, 15, true);
	array.push_back(line);
	CLinePos.push_back(array);

	// (U_E, 3)
	array.clear();
	line = make_tuple(5, 6, false);
	array.push_back(line);
	line = make_tuple(11, 11, false);
	array.push_back(line);
	CLinePos.push_back(array);

	// (V_S, 0)
	array.clear();
	line = make_tuple(0, 1, true);
	array.push_back(line);
	line = make_tuple(6, 8, true);
	array.push_back(line);
	CLinePos.push_back(array);

	// (V_S, 1)
	array.clear();
	line = make_tuple(6, 0, false);
	array.push_back(line);
	line = make_tuple(7, 9, true);
	array.push_back(line);
	line = make_tuple(16, 16, true);
	array.push_back(line);
	CLinePos.push_back(array);
	
	// (V_S, 2)
	array.clear();
	line = make_tuple(7, 8, false);
	array.push_back(line);
	line = make_tuple(8, 4, true);
	array.push_back(line);
	line = make_tuple(17, 17, true);
	array.push_back(line);
	CLinePos.push_back(array);

	// (V_S, 3)
	array.clear();
	line = make_tuple(3, 5, true);
	array.push_back(line);
	line = make_tuple(8, 9, false);
	array.push_back(line);
	CLinePos.push_back(array);

	// (V_E, 0)
	array.clear();
	line = make_tuple(2, 2, false);
	array.push_back(line);
	line = make_tuple(9, 10, true);
	array.push_back(line);
	CLinePos.push_back(array);

	// (V_E, 1)
	array.clear();
	line = make_tuple(9, 3, false);
	array.push_back(line);
	line = make_tuple(10, 11, true);
	array.push_back(line);
	line = make_tuple(18, 18, true);
	array.push_back(line);
	CLinePos.push_back(array);
	
	// (V_E, 2)
	array.clear();
	line = make_tuple(10, 10, false);
	array.push_back(line);
	line = make_tuple(11, 7, true);
	array.push_back(line);
	line = make_tuple(19, 19, true);
	array.push_back(line);
	CLinePos.push_back(array);

	// (V_E, 3)
	array.clear();
	line = make_tuple(5, 6, false);
	array.push_back(line);
	line = make_tuple(11, 11, false);
	array.push_back(line);
	CLinePos.push_back(array);
}

	
bool fk_Gregory::setCurveCtrl(fk_SurfDirection argD, int argVID, const fk_Vector &argPos)
{
	if(argVID < 0 || argVID > 3) return false;

	fk_Surface::setCtrl(GetCID(argD, argVID), argPos);
	SetCLine(argD, argVID, argPos);
	
	return true;
}

bool fk_Gregory::setDerivCtrl(fk_SurfDirection argD, int argVID, const fk_Vector &argPos)
{
	if(argVID != 1 && argVID != 2) return false;
	int trueID = GetDID(argD, argVID);

	fk_Surface::setCtrl(trueID, argPos);
	ctrlLine.changeLine(trueID, ctrlPos.getV(GetCID(argD, argVID)), argPos);

	return true;
}

fk_Vector fk_Gregory::getCurveCtrl(fk_SurfDirection argD, int argVID)
{
	if(argVID < 0 || argVID > 3) return fk_Vector(0.0, 0.0, 0.0);

	return ctrlPos.getV(GetCID(argD, argVID));
}

fk_Vector fk_Gregory::getDerivCtrl(fk_SurfDirection argD, int argVID)
{
	if(argVID != 1 && argVID != 2) return fk_Vector(0.0, 0.0, 0.0);

	return ctrlPos.getV(GetDID(argD, argVID));
}

fk_Vector fk_Gregory::GetIntC(double argU, double argV, int argUID, int argVID)
{
	return (argU * ctrlPos.getV(argUID) + argV * ctrlPos.getV(argVID))/(argU + argV);
}

void fk_Gregory::MakeBezier(fk_Vector argC[4][4], double argU, double argV)
{
	for(int i = 0; i <= 3; ++i) {
		argC[0][i] = ctrlPos.getV(i);
		argC[3][i] = ctrlPos.getV(4+i);
	}

	argC[1][0] = ctrlPos.getV(8);
	argC[1][3] = ctrlPos.getV(10);
	argC[2][0] = ctrlPos.getV(9);
	argC[2][3] = ctrlPos.getV(11);

	argC[1][1] = GetIntC(argU, argV, 12, 16);
	argC[1][2] = GetIntC(1.0 - argU, argV, 13, 18);
	argC[2][1] = GetIntC(argU, 1.0 - argV, 14, 17);
	argC[2][2] = GetIntC(1.0 - argU, 1.0 - argV, 15, 19);
}

fk_Vector fk_Gregory::pos(double argU, double argV)
{
	if(argU < fk_Math::EPS) {
		if(argV < fk_Math::EPS) return ctrlPos.getV(0);
		if(argV > 1.0 - fk_Math::EPS) return ctrlPos.getV(4);
	}

	if(argU > 1.0 - fk_Math::EPS) {
		if(argV < fk_Math::EPS) return ctrlPos.getV(3);
		if(argV > 1.0 - fk_Math::EPS) return ctrlPos.getV(7);
	}
	
	fk_Vector	bezCtrl[4][4], retP(0.0, 0.0, 0.0);
	double u[4], v[4];

	MakeBezier(bezCtrl, argU, argV);

	for(int i = 0; i <= 3; ++i) {
		u[i] = Bezier(3, i, argU);
		v[i] = Bezier(3, i, argV);
	}

	for(int i = 0; i <= 3; i++) {
		for(int j = 0; j <= 3; j++) {
			retP += u[i]*v[j]*bezCtrl[i][j];
		}
	}

	return retP;
}

fk_Vector fk_Gregory::uDeriv(double argU, double argV)
{
	if(argU < fk_Math::EPS) {
		if(argV < fk_Math::EPS) return 3.0 * (ctrlPos.getV(1) - ctrlPos.getV(0));
		if(argV > 1.0 - fk_Math::EPS) return 3.0 * (ctrlPos.getV(5) - ctrlPos.getV(4));
	}

	if(argU > 1.0 - fk_Math::EPS) {
		if(argV < fk_Math::EPS) return 3.0 * (ctrlPos.getV(3) - ctrlPos.getV(2));
		if(argV > 1.0 - fk_Math::EPS) return 3.0 * (ctrlPos.getV(7) - ctrlPos.getV(6));
	}

	fk_Vector	bezCtrl[4][4], retP(0.0, 0.0, 0.0);
	double u[3], v[4];

	MakeBezier(bezCtrl, argU, argV);

	for(int i = 0; i <= 3; ++i) {
		if(i != 3) u[i] = Bezier(2, i, argU);
		v[i] = Bezier(3, i, argV);
	}

	for(int i = 0; i <= 2; i++) {
		for(int j = 0; j <= 3; j++) {
			fk_Vector dU =  bezCtrl[i+1][j] - bezCtrl[i][j];
			retP += u[i] * v[j] * dU;
		}
	}

	return retP;
}

fk_Vector fk_Gregory::vDeriv(double argU, double argV)
{
	if(argU < fk_Math::EPS) {
		if(argV < fk_Math::EPS) return 3.0 * (ctrlPos.getV(8) - ctrlPos.getV(0));
		if(argV > 1.0 - fk_Math::EPS) return 3.0 * (ctrlPos.getV(4) - ctrlPos.getV(9));
	}

	if(argU > 1.0 - fk_Math::EPS) {
		if(argV < fk_Math::EPS) return 3.0 * (ctrlPos.getV(10) - ctrlPos.getV(3));
		if(argV > 1.0 - fk_Math::EPS) return 3.0 * (ctrlPos.getV(7) - ctrlPos.getV(11));
	}

	fk_Vector	bezCtrl[4][4], retP(0.0, 0.0, 0.0);
	double u[4], v[3];

	MakeBezier(bezCtrl, argU, argV);

	for(int i = 0; i <= 3; ++i) {
		u[i] = Bezier(3, i, argU);
		if(i != 3) v[i] = Bezier(2, i, argV);
	}

	for(int i = 0; i <= 3; i++) {
		for(int j = 0; j <= 2; j++) {
			fk_Vector dV =  bezCtrl[i][j+1] - bezCtrl[i][j];
			retP += u[i] * v[j] * dV;
		}
	}

	return retP;
}
