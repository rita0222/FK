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
#include <FK/Plane.h>

using namespace std;
using namespace FK;

const static int BIDTable[4][4] = {
	{0, 1, 2, 3},
	{4, 5, 6, 7},
	{0, 8, 9, 4},
	{3, 10, 11, 7}
};

const static int DIDTable[4][4] = {
	{8, 12, 13, 10},
	{9, 14, 15, 11},
	{1, 16, 17, 5},
	{2, 18, 19, 6}
};

static vector< vector< vector<_st> > > DerivTable, BoundTable;

using line_ = tuple<int, bool, fk_UV, int>;
static vector< vector< vector<line_> > > BLineTable, DLineTable;

fk_Gregory::fk_Gregory(void)
{
	SetObjectType(fk_Type::GREGORY);
	init();
	return;
}

fk_Gregory::~fk_Gregory()
{
	ctrlPos.clear();
	return;
}

void fk_Gregory::init(void)
{
	setCtrlSize(25);
	setCtrlNum(20);
	fk_Vector zero;

	if(DerivTable.empty()) MakeTable();

	ctrlLine.allClear();
	for(int i = 0; i < 20; ++i) ctrlLine.pushLine(zero, zero);
	for(int i = 0; i <= 3; ++i) {
		for(int j = 0; j <= 3; ++j) {
			boundary[i][j] = zero;
			deriv[i][j] = zero;
			bezier[i][j] = zero;
		}
	}
}

bool fk_Gregory::setBoundary(fk_UV argUV, int argVID, const fk_Vector &argV)
{
	if(_st(argUV) > 3 || argVID < 0 || argVID > 3) return false;

	boundary[_st(argUV)][_st(argVID)] = argV;

	vector<_st>	v = BoundTable[_st(argUV)][_st(argVID)];
	if(argVID == 0 || argVID == 3) {
		boundary[v[0]][v[1]] = argV;
	} else {
		deriv[v[0]][v[1]] = argV;
	}
	
	bezier[v[2]][v[3]] = argV;
	setCtrl(BIDTable[_st(argUV)][argVID], argV);

	vector<line_> lineSet = BLineTable[_st(argUV)][_st(argVID)];
	for(auto [lineID, flg, segID, ctrlID] : lineSet) {
		fk_Vector oP = (flg) ? boundary[_st(segID)][ctrlID] : deriv[_st(segID)][ctrlID];
		ctrlLine.changeLine(lineID, argV, oP);
	}

	return true;
}

fk_Vector fk_Gregory::getBoundary(fk_UV argUV, int argID)
{
	if(_st(argUV) > 3 || argID < 0 || argID > 3) return fk_Vector(0.0, 0.0, 0.0);
	return boundary[_st(argUV)][argID];
}

bool fk_Gregory::setDerivative(fk_UV argUV, int argVID, const fk_Vector &argV)
{
	if(_st(argUV) > 3 || argVID < 0 || argVID > 3) return false;

	vector<_st> v = DerivTable[_st(argUV)][_st(argVID)];
	if(argVID == 1 || argVID == 2) {
		deriv[v[0]][v[1]] = argV;
		setCtrl(DIDTable[_st(argUV)][argVID], argV);
	} else {
		setBoundary(fk_UV(v[0]), int(v[1]), argV);
	}

	vector<line_> lineSet = DLineTable[_st(argUV)][_st(argVID)];
	for(auto [lineID, flg, segID, ctrlID] : lineSet) {
		fk_Vector oP = (flg) ? boundary[_st(segID)][ctrlID] : deriv[_st(segID)][ctrlID];
		ctrlLine.changeLine(lineID, argV, oP);
	}

	return true;
}
	
fk_Vector fk_Gregory::getDerivative(fk_UV argUV, int argID)
{
	if(_st(argUV) > 3 || argID < 0 || argID > 3) return fk_Vector(0.0, 0.0, 0.0);
	return deriv[_st(argUV)][argID];
}

void fk_Gregory::adjustDerivative(fk_UV argUV)
{
	fk_Vector A = getDerivative(argUV, 0) - getBoundary(argUV, 0);
	fk_Vector B = getDerivative(argUV, 3) - getBoundary(argUV, 3);

	setDerivative(argUV, 1, 2.0*A/3.0 + B/3.0 + getBoundary(argUV, 1));
	setDerivative(argUV, 2, A/3.0 + 2.0*B/3.0 + getBoundary(argUV, 2));

	return;
}

void fk_Gregory::adjustDerivative(void)
{
	adjustDerivative(fk_UV::U_S);
	adjustDerivative(fk_UV::U_E);
	adjustDerivative(fk_UV::V_S);
	adjustDerivative(fk_UV::V_E);
}

bool fk_Gregory::connect(fk_Gregory *argSurf,
						 fk_UV argThisUV,
						 fk_UV argOtherUV,
						 bool argNegateFlg,
						 bool argModeFlg)
{
	fk_Vector	oC[8];
	int			i, index;

	if(argSurf == nullptr || _st(argThisUV) > 3 || _st(argOtherUV) > 3) return false;

	// 相手側曲面の内部制御点を事前に補正
	argSurf->adjustDerivative(argOtherUV);
	
	// 相手側曲面から制御点情報を取得
	for(i = 0; i <= 3; ++i) {
		index = (argNegateFlg == true) ? i : 3-i;
		oC[i] = argSurf->getBoundary(argOtherUV, index);
		oC[i+4] = argSurf->getDerivative(argOtherUV, index);
	}

	// 端点チェック
	if(oC[0] != getBoundary(argThisUV, 0)) return false;
	if(oC[3] != getBoundary(argThisUV, 3)) return false;

	// 境界線上制御点の補正
	setBoundary(argThisUV, 1, oC[1]);
	setBoundary(argThisUV, 2, oC[2]);

	// 接続処理
	if(argModeFlg == true) {
		C1Connect(argThisUV, oC);
	} else {
		G1Connect(argThisUV, oC); 
	}

	return true;
}

void fk_Gregory::C1Connect(fk_UV argUV, fk_Vector *argOC)
{
	for(int i = 0; i <= 3; ++i) {
		setDerivative(argUV, i, 2.0*argOC[i] - argOC[i+4]);
	}
	return;
}

void fk_Gregory::G1Connect(fk_UV argUV, fk_Vector *argOC)
{
	double		s0, s1, t0, t1;
	fk_Vector	A, B, C, D, param;
	fk_Plane	plane;

	// 境界線端点の接平面が一致するように、自身境界線の制御点を補正
	plane.set3Pos(argOC[0], argOC[1], argOC[4]);
	A = plane.proj(getDerivative(argUV, 0));
	if((argOC[0] - argOC[4])*(argOC[0] - A) > 0.0) A = 2.0*argOC[0] - argOC[4];
	setDerivative(argUV, 0, A);
	
	plane.set3Pos(argOC[3], argOC[2], argOC[7]);
	A = plane.proj(getDerivative(argUV, 3));
	if((argOC[3] - argOC[7])*(argOC[3] - A) > 0.0) A = 2.0*argOC[3] - argOC[7];
	setDerivative(argUV, 3, A);

	// 分解パラメータの算出
	A = argOC[0] - argOC[4];
	B = argOC[1] - argOC[0];
	C = A ^ B;
	D = getDerivative(argUV, 0) - getBoundary(argUV, 0);
	param = fk_Math::divideVec(D, A, B, C);
	s0 = param.x;
	t0 = param.y;

	A = argOC[3] - argOC[7];
	B = argOC[3] - argOC[2];
	C = A ^ B;
	D = getDerivative(argUV, 3) - getBoundary(argUV, 3);
	param = fk_Math::divideVec(D, A, B, C);
	s1 = param.x;
	t1 = param.y;
	
	// 内部制御点算出
	A = argOC[0] - argOC[4];
	B = argOC[1] - argOC[5];
	C = argOC[2] - argOC[1];
	D = argOC[1] - argOC[0];

	setDerivative(argUV, 1, (s1 - s0)*A/3.0 + s0*B + 2.0*t0*C/3.0 + t1*D/3.0 + argOC[1]);

	A = argOC[2] - argOC[6];
	B = argOC[3] - argOC[7];
	C = argOC[3] - argOC[2];
	D = argOC[2] - argOC[1];

	setDerivative(argUV, 2, s1*A - (s1 - s0)*B/3.0 + t0*C/3.0 + 2.0*t1*D/3.0 + argOC[2]);

	return;
}

void fk_Gregory::MakeBezier(double argU, double argV)
{
	double u = argU;
	double v = argV;
	double ou = 1.0 - argU;
	double ov = 1.0 - argV;
	
	bezier[1][1] = (u * deriv[0][1] + v * deriv[2][1])/(u + v);
	bezier[1][2] = (ou * deriv[0][2] + v * deriv[3][1])/(ou + v);
	bezier[2][1] = (u * deriv[1][1] + ov * deriv[2][2])/(u + ov);
	bezier[2][2] = (ou * deriv[1][2] + ov * deriv[3][2])/(ou + ov);
}
	


fk_Vector fk_Gregory::pos(double argU, double argV)
{
	double u = argU;
	double v = argV;
	double ou = 1.0 - argU;
	double ov = 1.0 - argV;
	fk_Vector retP(0.0, 0.0, 0.0);
	double	uA[4], vA[4];

	if(u < fk_Math::EPS) {
		if(v < fk_Math::EPS) {
			return boundary[_st(fk_UV::U_S)][0];
		} else if(ov < fk_Math::EPS) {
			return boundary[_st(fk_UV::U_E)][0];
		}
	} else if(ou < fk_Math::EPS) {
		if(v < fk_Math::EPS) {
			return boundary[_st(fk_UV::U_S)][3];
		} else if(ov < fk_Math::EPS) {
			return boundary[_st(fk_UV::U_E)][3];
		}
	}

	MakeBezier(u, v);

	for(int i = 0; i <= 3; ++i) {
		uA[i] = Bernstein(3, i, u);
		vA[i] = Bernstein(3, i, v);
	}

	for(int i = 0; i <= 3; ++i) {
		for(int j = 0; j <= 3; ++j) {
			retP += uA[j] * vA[i] * bezier[i][j];
		}
	}

	return retP;
}

fk_Vector fk_Gregory::uDeriv(double argU, double argV)
{
	double u = argU;
	double v = argV;
	double ou = 1.0 - argU;
	double ov = 1.0 - argV;
	fk_Vector retV(0.0, 0.0, 0.0);
	double	uA[3], vA[4];


	if(u < fk_Math::EPS) {
		if(v < fk_Math::EPS) {
			return 3.0 * (boundary[0][1] - boundary[0][0]);
		} else if(ov < fk_Math::EPS) {
			return 3.0 * (boundary[1][1] - boundary[1][0]);
		}
	} else if(ou < fk_Math::EPS) {
		if(v < fk_Math::EPS) {
			return 3.0 * (boundary[0][3] - boundary[0][2]);
		} else if(ov < fk_Math::EPS) {
			return 3.0 * (boundary[1][3] - boundary[1][2]);
		}
	}

	MakeBezier(u, v);

	for(int i = 0; i <= 3; ++i) {
		if(i != 3) uA[i] = Bernstein(2, i, u);
		vA[i] = Bernstein(3, i, v);
	}

	for(int i = 0; i <= 3; ++i) {
		for(int j = 0; j <= 2; ++j) {
			fk_Vector dU = bezier[i][j+1] - bezier[i][j];
			retV += uA[j] * vA[i] * dU;
		}
	}

	return retV;
}

fk_Vector fk_Gregory::vDeriv(double argU, double argV)
{
	double u = argU;
	double v = argV;
	double ou = 1.0 - argU;
	double ov = 1.0 - argV;
	fk_Vector retV(0.0, 0.0, 0.0);
	double	uA[4], vA[3];

	if(u < fk_Math::EPS) {
		if(v < fk_Math::EPS) {
			return 3.0 * (boundary[2][1] - boundary[2][0]);
		} else if(ov < fk_Math::EPS) {
			return 3.0 * (boundary[2][3] - boundary[2][2]);
		}
	} else if(ou < fk_Math::EPS) {
		if(v < fk_Math::EPS) {
			return 3.0 * (boundary[3][1] - boundary[3][0]);
		} else if(ov < fk_Math::EPS) {
			return 3.0 * (boundary[3][3] - boundary[3][2]);
		}
	}

	MakeBezier(u, v);

	for(int i = 0; i <= 3; ++i) {
		uA[i] = Bernstein(3, i, u);
		if(i != 3) vA[i] = Bernstein(2, i, v);
	}

	for(int i = 0; i <= 2; ++i) {
		for(int j = 0; j <= 3; ++j) {
			fk_Vector dV = bezier[i+1][j] - bezier[i][j];
			retV += uA[j] * vA[i] * dV;
		}
	}

	return retV;
}


void fk_Gregory::MakeTable(void)
{
	DerivTable.clear();
	BoundTable.clear();
	BLineTable.clear();
	DLineTable.clear();
	
	vector< vector<_st> > array;

	array.clear();
	array.push_back({2, 1});
	array.push_back({0, 1});
	array.push_back({0, 2});
	array.push_back({3, 1});
	DerivTable.push_back(array);

	array.clear();
	array.push_back({2, 2});
	array.push_back({1, 1});
	array.push_back({1, 2});
	array.push_back({3, 2});
	DerivTable.push_back(array);

	array.clear();
	array.push_back({0, 1});
	array.push_back({2, 1});
	array.push_back({2, 2});
	array.push_back({1, 1});
	DerivTable.push_back(array);

	array.clear();
	array.push_back({0, 2});
	array.push_back({3, 1});
	array.push_back({3, 2});
	array.push_back({1, 2});
	DerivTable.push_back(array);

	array.clear();
	array.push_back({2, 0, 0, 0});
	array.push_back({2, 0, 0, 1});
	array.push_back({3, 0, 0, 2});
	array.push_back({3, 0, 0, 3});
	BoundTable.push_back(array);
	
	array.clear();
	array.push_back({2, 3, 3, 0});
	array.push_back({2, 3, 3, 1});
	array.push_back({3, 3, 3, 2});
	array.push_back({3, 3, 3, 3});
	BoundTable.push_back(array);

	array.clear();
	array.push_back({0, 0, 0, 0});
	array.push_back({0, 0, 1, 0});
	array.push_back({1, 0, 2, 0});
	array.push_back({1, 0, 3, 0});
	BoundTable.push_back(array);

	array.clear();
	array.push_back({0, 3, 0, 3});
	array.push_back({0, 3, 1, 3});
	array.push_back({1, 3, 2, 3});
	array.push_back({1, 3, 3, 3});
	BoundTable.push_back(array);

	vector<line_> lineSet;
	vector< vector<line_> > segment;

	// Boundary::U_S[0]
	lineSet.clear();
	//lineSet.push_back(make_tuple(0, true, fk_UV::U_S, 1));
	lineSet.push_back({0, true, fk_UV::U_S, 1});
	lineSet.push_back({6, true, fk_UV::V_S, 1});
	segment.push_back(lineSet);

	// Boundary::U_S[1]
	lineSet.clear();
	lineSet.push_back({0, true, fk_UV::U_S, 0});
	lineSet.push_back({1, true, fk_UV::U_S, 2});
	lineSet.push_back({12, false, fk_UV::U_S, 1});
	segment.push_back(lineSet);

	// Boundary::U_S[2]
	lineSet.clear();
	lineSet.push_back({1, true, fk_UV::U_S, 1});
	lineSet.push_back({2, true, fk_UV::U_S, 3});
	lineSet.push_back({13, false, fk_UV::U_S, 2});
	segment.push_back(lineSet);
	
	// Boundary::U_S[3]
	lineSet.clear();
	lineSet.push_back({2, true, fk_UV::U_S, 2});
	lineSet.push_back({9, true, fk_UV::V_E, 1});
	segment.push_back(lineSet);

	// Boundary::U_S
	BLineTable.push_back(segment);
	segment.clear();
	
	// Boundary::U_E[0]
	lineSet.clear();
	lineSet.push_back({3, true, fk_UV::U_E, 1});
	lineSet.push_back({8, true, fk_UV::V_S, 2});
	segment.push_back(lineSet);

	// Boundary::U_E[1]
	lineSet.clear();
	lineSet.push_back({3, true, fk_UV::U_E, 0});
	lineSet.push_back({4, true, fk_UV::U_E, 2});
	lineSet.push_back({14, false, fk_UV::U_E, 1});
	segment.push_back(lineSet);

	// Boundary::U_E[2]
	lineSet.clear();
	lineSet.push_back({4, true, fk_UV::U_E, 1});
	lineSet.push_back({5, true, fk_UV::U_E, 3});
	lineSet.push_back({15, false, fk_UV::U_E, 2});
	segment.push_back(lineSet);
	
	// Boundary::U_E[3]
	lineSet.clear();
	lineSet.push_back({5, true, fk_UV::U_E, 2});
	lineSet.push_back({11, true, fk_UV::V_E, 2});
	segment.push_back(lineSet);

	// Boundary::U_E
	BLineTable.push_back(segment);
	segment.clear();
	
	// Boundary::V_S[0]
	lineSet.clear();
	lineSet.push_back({0, true, fk_UV::U_S, 1});
	lineSet.push_back({6, true, fk_UV::V_S, 1});
	segment.push_back(lineSet);

	// Boundary::V_S[1]
	lineSet.clear();
	lineSet.push_back({6, true, fk_UV::V_S, 0});
	lineSet.push_back({7, true, fk_UV::V_S, 2});
	lineSet.push_back({16, false, fk_UV::V_S, 1});
	segment.push_back(lineSet);

	// Boundary::V_S[2]
	lineSet.clear();
	lineSet.push_back({7, true, fk_UV::V_S, 1});
	lineSet.push_back({8, true, fk_UV::V_S, 3});
	lineSet.push_back({17, false, fk_UV::V_S, 2});
	segment.push_back(lineSet);
	
	// Boundary::V_S[3]
	lineSet.clear();
	lineSet.push_back({3, true, fk_UV::U_E, 1});
	lineSet.push_back({8, true, fk_UV::V_S, 2});
	segment.push_back(lineSet);

	// Boundary::V_S
	BLineTable.push_back(segment);
	segment.clear();

	// Boundary::V_E[0]
	lineSet.clear();
	lineSet.push_back({2, true, fk_UV::V_S, 2});
	lineSet.push_back({9, true, fk_UV::V_E, 1});
	segment.push_back(lineSet);

	// Boundary::V_E[1]
	lineSet.clear();
	lineSet.push_back({9, true, fk_UV::V_E, 0});
	lineSet.push_back({10, true, fk_UV::V_E, 2});
	lineSet.push_back({18, false, fk_UV::V_E, 1});
	segment.push_back(lineSet);

	// Boundary::V_E[2]
	lineSet.clear();
	lineSet.push_back({10, true, fk_UV::V_E, 1});
	lineSet.push_back({11, true, fk_UV::V_E, 3});
	lineSet.push_back({19, false, fk_UV::V_E, 2});
	segment.push_back(lineSet);
	
	// Boundary::V_E[3]
	lineSet.clear();
	lineSet.push_back({5, true, fk_UV::U_E, 2});
	lineSet.push_back({11, true, fk_UV::V_E, 2});
	segment.push_back(lineSet);

	// Boundary::V_E
	BLineTable.push_back(segment);
	segment.clear();

	// Derivative::U_S[0]
	segment.push_back(BLineTable[_st(fk_UV::V_S)][1]);

	// Derivative::U_S[1]
	lineSet.clear();
	lineSet.push_back({12, true, fk_UV::U_S, 1});
	segment.push_back(lineSet);

	// Derivative::U_S[2]
	lineSet.clear();
	lineSet.push_back({13, true, fk_UV::U_S, 2});
	segment.push_back(lineSet);
	
	// Derivative::U_S[3]
	segment.push_back(BLineTable[_st(fk_UV::V_E)][1]);

	// Derivative::U_S
	DLineTable.push_back(segment);
	segment.clear();

	// Derivative::U_E[0]
	segment.push_back(BLineTable[_st(fk_UV::V_S)][2]);

	// Derivative::U_E[1]
	lineSet.clear();
	lineSet.push_back({14, true, fk_UV::U_E, 1});
	segment.push_back(lineSet);

	// Derivative::U_E[2]
	lineSet.clear();
	lineSet.push_back({15, true, fk_UV::U_E, 2});
	segment.push_back(lineSet);
	
	// Derivative::U_E[3]
	segment.push_back(BLineTable[_st(fk_UV::V_E)][2]);

	// Derivative::U_E
	DLineTable.push_back(segment);
	segment.clear();

	// Derivative::V_S[0]
	segment.push_back(BLineTable[_st(fk_UV::U_S)][1]);

	// Derivative::V_S[1]
	lineSet.clear();
	lineSet.push_back({16, true, fk_UV::V_S, 1});
	segment.push_back(lineSet);

	// Derivative::V_S[2]
	lineSet.clear();
	lineSet.push_back({17, true, fk_UV::V_S, 2});
	segment.push_back(lineSet);
	
	// Derivative::V_S[3]
	segment.push_back(BLineTable[_st(fk_UV::U_E)][1]);

	// Derivative::V_S
	DLineTable.push_back(segment);
	segment.clear();

	// Derivative::V_E[0]
	segment.push_back(BLineTable[_st(fk_UV::U_S)][2]);

	// Derivative::V_E[1]
	lineSet.clear();
	lineSet.push_back({18, true, fk_UV::V_E, 1});
	segment.push_back(lineSet);

	// Derivative::V_E[2]
	lineSet.clear();
	lineSet.push_back({19, true, fk_UV::V_E, 2});
	segment.push_back(lineSet);
	
	// Derivative::V_E[3]
	segment.push_back(BLineTable[_st(fk_UV::U_E)][2]);

	// Derivative::U_E
	DLineTable.push_back(segment);
	segment.clear();
}		
