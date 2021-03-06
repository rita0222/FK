﻿#define FK_DEF_SIZETYPE

#include <FK/FK.h>
#include <memory>

using namespace FK;
using namespace std;

int main()
{
	unique_ptr<fk_ShapeViewer> viewer(new fk_ShapeViewer(600, 660));
	unique_ptr<fk_IndexFaceSet> shape(new fk_IndexFaceSet());
	vector<fk_Vector> pos(121);
	fk_Vector moveVec, movePos;
	vector< vector<int> > IFSet;
	vector<int> loop(4);
	int i, j;
	double x, y;

	// 各頂点位置の設定
	for(i = 0; i <= 10; i++) {
		for(j = 0; j <= 10; j++) {
			x = double(i - 5);	
			y = double(j - 5);
			pos[_st(i*11 + j)].set(x, y, (x*x - y*y)/10.0);
		}
	}

	// インデックスフェースセットの生成
	for(i = 0; i < 10; i++) {
		for(j = 0; j < 10; j++) {
			loop[0] = i*11 + j;
			loop[1] = (i+1)*11 + j;
			loop[2] = (i+1)*11 + j+1;
			loop[3] = i*11 + j+1;
			IFSet.push_back(loop);
		}
	}

	// 形状の生成
	shape->makeIFSet(&IFSet, &pos);

	// fk_ShapeViewer へ形状を設定
	viewer->setShape(0, shape.get());

	// 各種設定
	viewer->setDrawMode(fk_Draw::FRONTBACK_FACE | fk_Draw::LINE);
	viewer->setScale(10.0);

	for(int k = 0; viewer->draw() == true; k += 10) {
		for(i = 0; i <= 10; i++) {
			for(j = 0; j <= 10; j++) {
				// 各頂点の移動量計算
				moveVec.set(0.0, 0.0, sin(double(k+j*40)*0.05/fk_Math::PI));

				// 各頂点を移動場所を計算
				movePos = moveVec + pos[_st(i*11 + j)];

				// 各頂点を実際に移動
				shape->moveVPosition(i*11 + j, movePos);
			}
		}
	}

	return 0;
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
