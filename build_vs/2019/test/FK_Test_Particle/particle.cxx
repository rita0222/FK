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
#include <FK/FK.h>

using namespace std;
using namespace FK;

int main(int, char **)
{
	fk_ShapeViewer      viewer(800, 600);
	fk_ParticleSet      particle;
	fk_Prism			prism(32, 15.0, 15.0, 50.0, false);
	double				maxSpeed, minSpeed;
	fk_Vector       	water(-0.5, 0.0, 0.0);
	double          	R = 15.0;

	particle.setMaxSize(1000);   // パーティクルの最大数設定。
	particle.setIndivMode(true); // 個別処理 (indivMethod) を ON にしておく。
	particle.setAllMode(true);   // 全体処理 (allMethod) を ON にしておく。

	maxSpeed = 0.6;
	minSpeed = 0.3;

	particle.genMethod = [](fk_Particle *p) {
		p->setPosition(50.0, fk_Math::drand(-25.0, 25.0), fk_Math::drand(-25.0, 25.0));
	};

	particle.allMethod = [&](void) {
		for(int i = 0; i < 5; i++) {
			if(fk_Math::drand() < 0.3) {
				// 新たなパーティクルを生成。
				// 生成時に genMethod() が呼ばれる。
				particle.newParticle();
			}
		}
	};


	particle.indivMethod = [&](fk_Particle *p) {
		fk_Vector       pos, vec, tmp1, tmp2;
		fk_Color		col;
 
		// パーティクルの位置を取得。
		pos = p->getPosition();
		pos.z = 0.0;
		double r = pos.dist(); // |p| を r に代入。
 
		// パーティクルの速度ベクトルを計算
		tmp1 = water/(r*r*r);
		tmp2 = ((3.0 * (water * pos))/(r*r*r*r*r)) * pos;
		vec = water + ((R*R*R)/2.0) * (tmp1 - tmp2);
		//vec /= 5.0;
		// パーティクルの速度ベクトルを代入
		p->setVelocity(vec);

		double speed = vec.dist();
		double t = (speed - minSpeed)/(maxSpeed - minSpeed);
		double h = fk_Math::PI*4.0/3.0 + min(1.0, max(0.0, t)) * fk_Math::PI*2.0/3.0;
		col.setHSV(h, 1.0, 1.0);
		p->setColor(col);
		// パーティクルの x 座標が -50 以下になったら消去。
		if(pos.x < -50.0) {
			particle.removeParticle(p);
		}
	}; 

	viewer.setShape(2, particle.getShape());
	viewer.setDrawMode(2, fk_Draw::POINT);
	viewer.setElementMode(2, fk_ElementMode::ELEMENT);
	viewer.setPointSize(2, 3.0);

	viewer.setShape(3, &prism);
	viewer.setPosition(3, 0.0, 0.0, 25.0);
	viewer.setDrawMode(3, fk_Draw::LINE | fk_Draw::FACE);
	viewer.setVertexColor(3, fk_Color(0.0, 1.0, 0.0));
	viewer.setEdgeColor(3, fk_Color(0.0, 0.0, 1.0));

	viewer.setScale(10.0);

	for(int i = 0; viewer.draw() == true; i++) {
		particle.handle(); // パーティクルを 1 ステップ実行する。
	}
	return 0;
}
