﻿#include <FK/FK.h>
#include <FL/Fl_File_Chooser.H>
#include <memory>

using namespace std;
using namespace FK;

string imageFileSelect(void)
{
	fk_Window::fontInit();

	unique_ptr<Fl_File_Chooser> fc(new Fl_File_Chooser(fk_System::get_cwd().c_str(),
													   "*.bmp",
													   Fl_File_Chooser::SINGLE,
													   "Image File Select"));
	fc->textfont(0);
	fc->show();
	while(fc->visible()) Fl::wait();
	if(fc->count() == 0) return string("");
	return string(fc->value());
}

int main(int, char *[])
{
	unique_ptr<fk_MeshTexture> tex(new fk_MeshTexture());
	unique_ptr<fk_Material> mat(new fk_Material());

	string fileName = imageFileSelect();

	if(fileName.length() == 0) {
		fl_alert("No Select Image File");
		exit(2);
	}

	if(tex->readBMP(fileName) == false) {
		fl_alert("Image File Read Error.");
		exit(1);
	}

	tex->setTriNum(4);

	// テクスチャ画像を置く位置の設定
	tex->setVertexPos(0, 0, -100.0, 100.0, 0.0);
	tex->setVertexPos(0, 1, -100.0, 0.0, 0.0);
	tex->setVertexPos(0, 2, 0.0, 100.0, 0.0);
	tex->setVertexPos(1, 0, -100.0, -100.0, 0.0);
	tex->setVertexPos(1, 1, 0.0, -100.0, 0.0);
	tex->setVertexPos(1, 2, -100.0, 0.0, 0.0);
	tex->setVertexPos(2, 0, 100.0, -100.0, 0.0);
	tex->setVertexPos(2, 1, 100.0, 0.0, 0.0);
	tex->setVertexPos(2, 2, 0.0, -100.0, 0.0);
	tex->setVertexPos(3, 0, 100.0, 100.0, 0.0);
	tex->setVertexPos(3, 1, 0.0, 100.0, 0.0);
	tex->setVertexPos(3, 2, 100.0, 0.0, 0.0);

	// テクスチャ座標の設定
	tex->setTextureCoord(0, 0, 0.0, 1.0);
	tex->setTextureCoord(0, 1, 0.0, 0.5);
	tex->setTextureCoord(0, 2, 0.5, 1.0);
	tex->setTextureCoord(1, 0, 0.0, 0.0);
	tex->setTextureCoord(1, 1, 0.5, 0.0);
	tex->setTextureCoord(1, 2, 0.0, 0.5);
	tex->setTextureCoord(2, 0, 1.0, 0.0);
	tex->setTextureCoord(2, 1, 1.0, 0.5);
	tex->setTextureCoord(2, 2, 0.5, 0.0);
	tex->setTextureCoord(3, 0, 1.0, 1.0);
	tex->setTextureCoord(3, 1, 0.5, 1.0);
	tex->setTextureCoord(3, 2, 1.0, 0.5);

	unique_ptr<fk_ShapeViewer> viewer(new fk_ShapeViewer(800, 600));

	mat->setAmbDiff(1.0, 1.0, 1.0);
	viewer->setShape(tex.get());
	viewer->setMaterial(0, *mat.get());

	while(viewer->draw() == true) { }

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
