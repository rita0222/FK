/****************************************************************************
 *
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2018, Fine Kernel Project, All rights reserved.
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
#include <FK/BSplBase.H>
#include <FK/Base.h>

using namespace std;
using namespace FK;

bool BSplBase::IsSame(double a, double b)
{
	return ((a + FK_EPS) > b && (a - FK_EPS) < b);
}

bool BSplBase::IsBig(double a, double b)
{
	return ((a + FK_EPS) >= b);
}

bool BSplBase::UpdateKnot(int o, int n, vector<double> &knotVec)
{
	int				i;
	double			knot;
	double			d;

	if(o > n) return false;
	knotVec.clear();

	for(i = 0; i < o; i++) {
		knotVec.push_back(0.0);
	}

	d = double(n - o + 1);

	knot = 0.0;
	for(i = 0; i < n - o; i++) {
		knot += 1.0/d;
		knotVec.push_back(knot);
	}

	for(i = 0; i < o; i++) {
		knotVec.push_back(1.0);
	}

	return true;
}

double BSplBase::PosBasis(int argI, int argK, double t,
							 const vector<double> &knotVec)
{
	double		p, q;
	_st			i, k;

	i = static_cast<_st>(argI);
	k = static_cast<_st>(argK);

	if(IsSame(t, 0.0)) {
		if(i == 0) return 1.0;
		else return 0.0;
	}

	if(IsSame(t, knotVec[knotVec.size()-1])) {
		if(i == knotVec.size()-k-1) return 1.0;
		else return 0.0;
	}

	if(k == 1) {
		if(IsSame(knotVec[i], t)) return 1.0;
		else if(IsSame(knotVec[i], knotVec[i+1])) return 0.0;
		else if(IsSame(knotVec[i+1], t)) return 0.0;
		else if(knotVec[i] < t && t < knotVec[i+1]) return 1.0;
		else return 0.0;
	}

	if(IsSame(knotVec[i+k-1], knotVec[i]) || IsSame(t, knotVec[i])) {
		p = 0.0;
	} else {
		p = ((t - knotVec[i])/(knotVec[i+k-1] - knotVec[i])) *
			PosBasis(static_cast<int>(i), static_cast<int>(k-1), t, knotVec);
	}

	if(IsSame(knotVec[i+k], knotVec[i+1]) || IsSame(knotVec[i+k], t)) {
		q = 0.0;
	} else {
		q = ((knotVec[i+k] - t)/(knotVec[i+k] - knotVec[i+1])) *
			PosBasis(static_cast<int>(i+1), static_cast<int>(k-1), t, knotVec);
	}

	return (p + q);
}

double BSplBase::DiffBasis(int argI, int argK, double t,
							  const vector<double> &knotVec)
{
	double		p, q;
	_st			i, k;

	i = static_cast<_st>(argI);
	k = static_cast<_st>(argK);

	if(k == 1) return 0.0;

	if(IsSame(knotVec[i+k-1], knotVec[i])) {
		p = 0.0;
	} else {
		double a = PosBasis(static_cast<int>(i),
							static_cast<int>(k-1), t, knotVec) +
			(t - knotVec[i])*DiffBasis(static_cast<int>(i),
									   static_cast<int>(k-1), t, knotVec);
		p = a/(knotVec[i+k-1] - knotVec[i]);
	}

	if(IsSame(knotVec[i+k], knotVec[i+1])) {
		q = 0.0;
	} else {
		double b = (knotVec[i+k] - t) *
			DiffBasis(static_cast<int>(i+1),
					  static_cast<int>(k-1), t, knotVec) -
			PosBasis(static_cast<int>(i+1), static_cast<int>(k-1), t, knotVec);
		q = b/(knotVec[i+k] - knotVec[i+1]);
	}

	return (p + q);
}
