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
#include <FK/Gregory.h>
#include <FK/Plane.h>
#include <FK/Math.h>
#include <FK/Error.h>

using namespace std;

fk_Gregory::fk_Gregory(void)
{
	SetObjectType(FK_GREGORY);
	init();
	return;
}

fk_Gregory::~fk_Gregory()
{
	return;
}

int fk_Gregory::MapID(bool argMode, int argUV, int argID)
{
	if(argUV < 0 || argUV > 3) return -1;

	if(argMode == true)
	{
		// 境界線
		if(argID < 0 || argID > 3) return -1;

		switch(argUV) {
		  case 0:
			return argID;

		  case 1:
			return argID + 12;

		  case 2:
			return argID * 4;

		  case 3:
			return argID * 4 + 3;

		  default:
			break;
		}
	} else {
		// 内部
		if(argID < 0 || argID > 3) return -1;

		switch(argUV) {
		  case 0:
			return argID + 4;

		  case 1:
			return argID + 8;

		  case 2:
			if(argID == 1 || argID == 2) return argID + 15;
			return argID * 4 + 1;

		  case 3:
			if(argID == 1 || argID == 2) return argID + 17;
			return argID * 4 + 2;

		  default:
			break;
		}
	}

	return -1;
}

void fk_Gregory::BezSet(double argU, double argV)
{
	fk_Vector tmpC[4];
	double u = argU;
	double v = argV;
	double uu = 1.0 - argU;
	double vv = 1.0 - argV;
	tmpC[0] = (u * ctrl[5] + v * ctrl[16])/(u + v);
	tmpC[1] = (uu * ctrl[6] + v * ctrl[18])/(uu + v);
	tmpC[2] = (u * ctrl[9] + vv * ctrl[17])/(u + vv);
	tmpC[3] = (uu * ctrl[10] + vv * ctrl[19])/(uu + vv);

	bez.setCtrl(1, 1, tmpC[0]);
	bez.setCtrl(2, 1, tmpC[1]);
	bez.setCtrl(1, 2, tmpC[2]);
	bez.setCtrl(2, 2, tmpC[3]);
}	

fk_Vector fk_Gregory::pos(double argU, double argV)
{
	if(fabs(argU) < FK_EPS) {
		if(fabs(argV) < FK_EPS) return ctrl[0];
		if(fabs(1.0 - argV) < FK_EPS) return ctrl[12];
	} else if(fabs(1.0 - argU) < FK_EPS) {
		if(fabs(argV) < FK_EPS) return ctrl[3];
		if(fabs(1.0 - argV) < FK_EPS) return ctrl[15];
	}

	BezSet(argU, argV);
	return bez.pos(argU, argV);
}

fk_Vector fk_Gregory::uDeriv(double argU, double argV)
{
	if(fabs(argU) < FK_EPS) {
		if(fabs(argV) < FK_EPS) return (3.0 * (ctrl[1] - ctrl[0]));
		if(fabs(1.0 - argV) < FK_EPS) return (3.0 * (ctrl[13] - ctrl[12]));
	} else if(fabs(1.0 - argU) < FK_EPS) {
		if(fabs(argV) < FK_EPS) return (3.0 * (ctrl[3] - ctrl[2]));
		if(fabs(1.0 - argV) < FK_EPS) return (3.0 * (ctrl[15] - ctrl[14]));
	}

	BezSet(argU, argV);
	return bez.uDeriv(argU, argV);
}
	
fk_Vector fk_Gregory::vDeriv(double argU, double argV)
{
	if(fabs(argU) < FK_EPS) {
		if(fabs(argV) < FK_EPS) return (3.0 * (ctrl[4] - ctrl[0]));
		if(fabs(1.0 - argV) < FK_EPS) return (3.0 * (ctrl[12] - ctrl[8]));
	} else if(fabs(1.0 - argU) < FK_EPS) {
		if(fabs(argV) < FK_EPS) return (3.0 * (ctrl[7] - ctrl[3]));
		if(fabs(1.0 - argV) < FK_EPS) return (3.0 * (ctrl[15] - ctrl[11]));
	}

	BezSet(argU, argV);
	return bez.vDeriv(argU, argV);
}

void fk_Gregory::init(void)
{
	for(_st i = 0; i < 20; i++) ctrl[i].init();
	bez.init();
	return;
}

bool fk_Gregory::setBoundary(int argUV, int argID, const fk_Vector &argPos)
{
	int mapID = MapID(true, argUV, argID);
	if(mapID == -1) return false;

	ctrl[_st(mapID)] = argPos;
	bez.setCtrl(mapID % 4, mapID/4, argPos);
	
	return true;
}

bool fk_Gregory::setCtrl(int argUV, int argID, const fk_Vector &argPos)
{
	int mapID = MapID(false, argUV, argID);
	if(mapID == -1) return false;

	ctrl[_st(mapID)] = argPos;
	if(argID == 0 || argID == 3) bez.setCtrl(mapID % 4, mapID/4, argPos);
	return true;
}

fk_Vector fk_Gregory::getBoundary(int argUV, int argID)
{
	int mapID = MapID(true, argUV, argID);
	if(mapID == -1) return fk_Vector();

	return ctrl[_st(mapID)];
}

fk_Vector fk_Gregory::getCtrl(int argUV, int argID)
{
	int mapID = MapID(false, argUV, argID);
	if(mapID == -1) return fk_Vector();

	return ctrl[_st(mapID)];
}

void fk_Gregory::adjustCtrl(int argUV)
{
	fk_Vector A = ctrl[_st(MapID(false, argUV, 0))] - ctrl[_st(MapID(true, argUV, 0))];
	fk_Vector B = ctrl[_st(MapID(false, argUV, 3))] - ctrl[_st(MapID(true, argUV, 3))];

	setCtrl(argUV, 1, 2.0*A/3.0 + B/3.0 + ctrl[_st(MapID(true, argUV, 1))]);
	setCtrl(argUV, 2, A/3.0 + 2.0*B/3.0 + ctrl[_st(MapID(true, argUV, 2))]);

	return;
}
		

void fk_Gregory::adjustCtrl(void)
{
	for(int i = 0; i < 4; i++) adjustCtrl(i);
	return;
}

bool fk_Gregory::connect(fk_Gregory *argSurf, int argThisUV, int argOtherUV, bool negateFlg, bool modeFlg)
{
	fk_Vector	oC[8], A, B, C, D, param;
	fk_Plane	plane;
	int			i, index;
	double		s0, s1, t0, t1;

	if(argSurf == nullptr ||
	   argThisUV < 0 || argThisUV > 3 ||
	   argOtherUV < 0 || argOtherUV > 3) {
		return false;
	}

	// 相手側曲面の内部制御点を事前に補正
	argSurf->adjustCtrl(argOtherUV);
	
	// 相手側曲面から制御点情報を取得
	for(i = 0; i < 4; i++) {
		index = (negateFlg == true) ? i : 3-i;
		oC[i] = argSurf->ctrl[_st(MapID(true, argOtherUV, index))];
		oC[i+4] = argSurf->ctrl[_st(MapID(false, argOtherUV, index))];
	}

	// 端点チェック
	if(oC[0] != ctrl[_st(MapID(true, argThisUV, 0))]) return false;
	if(oC[3] != ctrl[_st(MapID(true, argThisUV, 3))]) return false;

	// 境界線上制御点の補正
	setBoundary(argThisUV, 1, oC[1]);
	setBoundary(argThisUV, 2, oC[2]);

	// 境界線端点の接平面が一致するように、自身境界線の制御点を補正
	if(modeFlg == false) {
		plane.set3Pos(oC[0], oC[1], oC[4]);
		A = plane.proj(getCtrl(argThisUV, 0));
		if((oC[0] - oC[4])*(oC[0] - A) > 0.0) A = 2.0*oC[0] - oC[4];
		setCtrl(argThisUV, 0, A);
	
		plane.set3Pos(oC[3], oC[2], oC[7]);
		A = plane.proj(getCtrl(argThisUV, 3));
		if((oC[3] - oC[7])*(oC[3] - A) > 0.0) A = 2.0*oC[3] - oC[7];
		setCtrl(argThisUV, 3, A);
	} else {
		setCtrl(argThisUV, 0, 2.0*oC[0] - oC[4]);
		setCtrl(argThisUV, 3, 2.0*oC[3] - oC[7]);
	}		

	// 分解パラメータの算出
	A = oC[0] - oC[4];
	B = oC[1] - oC[0];
	C = A ^ B;
	D = ctrl[_st(MapID(false, argThisUV, 0))] - ctrl[_st(MapID(true, argThisUV, 0))];
	param = fk_Math::divideVec(D, A, B, C);
	s0 = param.x;
	t0 = param.y;

	A = oC[3] - oC[7];
	B = oC[3] - oC[2];
	C = A ^ B;
	D = ctrl[_st(MapID(false, argThisUV, 3))] - ctrl[_st(MapID(true, argThisUV, 3))];
	param = fk_Math::divideVec(D, A, B, C);
	s1 = param.x;
	t1 = param.y;
	
	// 内部制御点算出
	A = oC[0] - oC[4];
	B = oC[1] - oC[5];
	C = oC[2] - oC[1];
	D = oC[1] - oC[0];

	setCtrl(argThisUV, 1, (s1 - s0)*A/3.0 + s0*B + 2.0*t0*C/3.0 + t1*D/3.0 + oC[1]);

	A = oC[2] - oC[6];
	B = oC[3] - oC[7];
	C = oC[3] - oC[2];
	D = oC[2] - oC[1];

	setCtrl(argThisUV, 2, s1*A - (s1 - s0)*B/3.0 + t0*C/3.0 + 2.0*t1*D/3.0 + oC[2]);

	return true;
}
