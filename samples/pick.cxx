/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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

int main(int, char *[])
{
	Fl_Window		mainWin(520, 520, "Pick Test");
	int				mX, mY, i;
	double			step;
	fk_Solid		solid;
	fk_Scene		scene;
	fk_Vertex		*curV;
	fk_Edge			*curE;
	fk_DrawMode		curMode;
	fk_PickData		pickData;
	fk_Model		camera, shapeModel;
	fk_Window		fkWin(10, 10, 500, 500);


	mainWin.end();
	fk_Material::initDefault();

	Red.setAmbDiff(1.0, 0.0, 0.0);
	Green.setAmbDiff(0.0, 1.0, 0.0);
	Blue.setAmbDiff(0.0, 0.0, 1.0);
	solid.setPalette(Red, 0);
	solid.setPalette(Green, 1);
	solid.setPalette(Blue, 2);

	solid.makeSphere(10, 50.0);
	shapeModel.setShape(&solid);
	shapeModel.setDrawMode(FK_POINTMODE | FK_LINEMODE);
	shapeModel.setSize(3.0);

	shapeModel.setPickMode(true);
	solid.setMaterialMode(FK_PARENT_MODE);
	shapeModel.setMaterialMode(FK_PARENT_MODE);

	for(curV = solid.getNextV(NULL); curV != NULL; curV = solid.getNextV(curV)) {
		curV->setElemMaterialID(2);
		curV->setElemMaterialMode(FK_CHILD_MODE);
	}

	for(curE = solid.getNextE(NULL); curE != NULL; curE = solid.getNextE(curE)) {
		curE->setElemMaterialID(2);
		curE->setElemMaterialMode(FK_CHILD_MODE);
	}

	camera.glMoveTo(50.0, 100.0, 300.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);

	scene.entryModel(&shapeModel);
	scene.entryCamera(&camera);

	fkWin.setScene(&scene);

	mainWin.show();
	fkWin.show();

	step = FK_PI/5000.0;
	while(true) {

		if(mainWin.visible() == 0) {
			if(Fl::wait() == 0) {
				break;
			} else {
				continue;
			}
		}

		if(fkWin.drawWindow() == 0) break;
		if(Fl::check() == 0) break;
		if(fkWin.winOpenStatus() == false) continue;

		fkWin.getMousePosition(&mX, &mY);
		curMode = shapeModel.getDrawMode();
		shapeModel.setDrawMode(FK_POINTMODE | FK_LINEMODE);
		fkWin.getPickModel(&pickData, 10, mX, mY);

		for(i = 0; i < pickData.getSize(); i++) {
			if(pickData.getType(i) == FK_VERTEX) {
				curV = solid.getVData(pickData.getID(i));
				curV->setElemMaterialID(0);
			} else if(pickData.getType(i) == FK_EDGE) {
				curE = solid.getEData(pickData.getID(i));
				curE->setElemMaterialID(1);
			}
		}

		shapeModel.setDrawMode(curMode);
		shapeModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Y, step);
	}

	return 0;
}
