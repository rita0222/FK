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

using namespace FK;
using namespace FK::Material;

int main(int, char *[])
{
	fk_AppWindow	window;
	fk_Model		camera, blockModel, lineModel[2];
	fk_Vector		pos[4];
	fk_Line			line[2];
	fk_Block		block(50.0, 70.0, 40.0);

	// マテリアルの初期化
	fk_Material::initDefault();

	// ウィンドウ設定
	window.setSize(800, 800);

	// 直方体の設定
	blockModel.setShape(&block);
	blockModel.setMaterial(Yellow);

	// 線分の設定
	pos[0].set(0.0, 100.0, 0.0);
	pos[1].set(100.0, 0.0, 0.0);
	pos[2] = -pos[0];
	pos[3] = -pos[1];
	line[0].setVertex(&pos[0]);
	line[1].setVertex(&pos[2]);
	lineModel[0].setShape(&line[0]);
	lineModel[1].setShape(&line[1]);

	// 線分の色設定
	lineModel[0].setLineColor(1.0f, 0.0f, 0.0f);
	lineModel[1].setLineColor(0.0f, 1.0f, 0.0f);

	// 直方体を線分の親モデルに設定
	lineModel[0].setParent(&blockModel);
	lineModel[1].setParent(&blockModel);

	// 視点の位置と姿勢を設定
	camera.glMoveTo(0.0, 0.0, 2000.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);

	// 各モデルをウィンドウに登録
	window.setCameraModel(&camera);
	window.entry(&blockModel);
	window.entry(&lineModel[0]);
	window.entry(&lineModel[1]);

	window.open();

	double speed = 5.0;

	for(int i = 0; window.update() == true; i++) {
		double z = camera.getPosition().z;

		// 視点を原点に近づける
		camera.glTranslate(0.0, 0.0, -speed);
        
		// 直方体(と子モデルの線分)を Y 軸中心に回転
		blockModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Y, speed * FK_PI/300.0);

		// カメラが 1000 より近くなったら Z 軸回転
		if(z < 1000.0) {
			camera.loRotateWithVec(0.0, 0.0, 0.0, fk_Z, speed * FK_PI/500.0);
		}

		// 視点が原点を越えたら、向きをもう一度原点に向かせる。
		if(z < -FK_EPS) {
			camera.glFocus(0.0, 0.0, 0.0);
		}

	}

	return 0;
}
