﻿#include <FK/FK.h>
#include <memory>

using namespace std;
using namespace FK;

constexpr int WIN_W = 512; // ウィンドウ横幅
constexpr int WIN_H = 512; // ウィンドウ縦幅

enum class WinStatus {
	NORMAL, CONTINUE, BREAK
};

// 通常モデルのシェーダー設定
void ShaderSetup(fk_ShaderBinder *argBinder, fk_Model *argModel, fk_Material argMat,
				 fk_Vector argPos, string argVP, string argFP)
{
	auto prog = argBinder->getProgram();

	argModel->setMaterial(argMat);
	argModel->setSmoothMode(true);
	argModel->glMoveTo(argPos);
	prog->loadVertexShader(argVP);
	prog->loadFragmentShader(argFP);
	if(prog->validate()) {
		argBinder->bindModel(argModel);
	} else {
		fk_Window::printf("Shader Error (Original Side)");
		fk_Window::putString(prog->getLastError());
	} 
}

// FBOシェーダー設定
void FBOSetup(fk_ShaderBinder *argBinder, fk_Window *argWindow, float argTH, string argFP)
{
	auto prog = argBinder->getProgram();

	argBinder->initializeFrameBufferObject(WIN_W, WIN_H);
	prog->loadFragmentShader(argFP);
	if(prog->validate()) {
		argBinder->getParameter()->setRegister("Thresshold", argTH);
		argBinder->bindWindow(argWindow);
	} else {
		fk_Window::printf("Shader Error (FBO Side)");
		fk_Window::putString(argBinder->getProgram()->getLastError());
	}
}

// ウィンドウの再描画と状況把握
WinStatus WindowUpdate(Fl_Window *argMainWin, fk_Window *argBaseWin,
					   fk_Window *argEdgeWin, fk_Window *argDepthWin)
{
	if(argMainWin->visible() == 0) {
		if(Fl::wait() == 0) {
			return WinStatus::BREAK;
		} else {
			return WinStatus::CONTINUE;
		}
	}

	if(argBaseWin->drawWindow() == 0) return WinStatus::BREAK;
	if(argEdgeWin->drawWindow() == 0) return WinStatus::BREAK;
	if(argDepthWin->drawWindow() == 0) return WinStatus::BREAK;
	if(Fl::check() == 0) return WinStatus::BREAK;
	if(argBaseWin->winOpenStatus() == false) return WinStatus::CONTINUE;
	if(argEdgeWin->winOpenStatus() == false) return WinStatus::CONTINUE;
	if(argDepthWin->winOpenStatus() == false) return WinStatus::CONTINUE;

	return WinStatus::NORMAL;
}

int main(int, char **)
{
	fk_System::setcwd();

	unique_ptr<Fl_Window> mainWindow(new Fl_Window(WIN_W*3, WIN_H, "Shader Test"));
	unique_ptr<fk_Model> camera(new fk_Model());
	unique_ptr<fk_Model> lightModel(new fk_Model());
	unique_ptr<fk_Material> mat(new fk_Material());
	unique_ptr<fk_Light> light(new fk_Light());
	unique_ptr<fk_Scene> scene(new fk_Scene());
	unique_ptr<fk_Window> baseWindow(new fk_Window(0, 0, WIN_W, WIN_H));
	unique_ptr<fk_Window> edgeWindow(new fk_Window(WIN_W, 0, WIN_W, WIN_H));
	unique_ptr<fk_Window> depthWindow(new fk_Window(WIN_W*2, 0, WIN_W, WIN_H));

	unique_ptr<fk_GuideObject> guide(new fk_GuideObject());
	unique_ptr<fk_TrackBall> tb(new fk_TrackBall(baseWindow.get(), camera.get()));

	unique_ptr<fk_IFSTexture> ifsShape(new fk_IFSTexture());
	unique_ptr<fk_Sphere> sph(new fk_Sphere(8, 7.0));

	unique_ptr<fk_SpriteModel> sprite(new fk_SpriteModel());

	unique_ptr<fk_Model> modelDef(new fk_Model());
	unique_ptr<fk_Model> ifsModelDef(new fk_Model());
	
	unique_ptr<fk_ShaderBinder> spBinder(new fk_ShaderBinder());
	unique_ptr<fk_ShaderBinder> ifsBinder(new fk_ShaderBinder());
	unique_ptr<fk_ShaderBinder> edgeBinder(new fk_ShaderBinder());
	unique_ptr<fk_ShaderBinder> depthBinder(new fk_ShaderBinder());

	int thresshold = 80;
	constexpr double SP_X = -(double(WIN_W/2) - 10.0);
	constexpr double SP_Y = double(WIN_H/2) - 10.0;

	mainWindow->end();
	fk_Material::initDefault();

	// 照明の設定
	lightModel->setShape(light.get());
	lightModel->setMaterial(Material::TrueWhite);
	lightModel->glMoveTo(0.0, 0.0, 0.0);
	lightModel->glFocus(-1.0, -1.0, -1.0);

	// 球と読み込みデータの設定
	if(ifsShape->readBMP("data/model/00tex_master.BMP") == false) {
		fl_alert("tex load err");
	}

	if(ifsShape->readMQOFile("data/model/meka.mqo", "body01") == false) {
		fl_alert("ifs load err");
	}
	ifsShape->setTexRendMode(fk_TexRendMode::SMOOTH);
	modelDef->setShape(sph.get());
	ifsModelDef->setShape(ifsShape.get());

	// スプライト設定

	if(sprite->initFont("data/font/rm1b.ttf") == false) {
		fl_alert("Font Init Error");
	}
	sprite->setPositionLT(SP_X, SP_Y);
	
	// 各モデルをディスプレイリストに登録
	scene->setBlendStatus(true);
	scene->setBGColor(0.5f, 0.5f, 0.5f);
	scene->entryCamera(camera.get());
	scene->entryModel(lightModel.get());
	guide->entryScene(scene.get());
	scene->entryModel(modelDef.get());
	scene->entryModel(ifsModelDef.get());

	// ウィンドウへディスプレイリストを登録
	baseWindow->setScene(scene.get());
	edgeWindow->setScene(scene.get());
	depthWindow->setScene(scene.get());

	// 視点の位置と姿勢を設定
	camera->glMoveTo(0.0, 0.0, 100.0);
	camera->glFocus(0.0, 0.0, 0.0);
	camera->glUpvec(0.0, 1.0, 0.0);
	sprite->entryFirst(baseWindow.get(), scene.get(), camera.get());

	// ウィンドウ生成 (シェーダー設定の前に行う必要がある。)
	mainWindow->show();
	baseWindow->show();
	edgeWindow->show();
	depthWindow->show();
	Fl::check();

	// 各種シェーダー設定
	ShaderSetup(spBinder.get(), modelDef.get(), Material::Yellow, fk_Vector(-20.0, 0.0, 0.0),
				"data/shader/model_vp.glsl", "data/shader/model_fp.glsl");
	
	ShaderSetup(ifsBinder.get(), ifsModelDef.get(), Material::White, fk_Vector(20.0, 0.0, 0.0),
				"data/shader/model_vp.glsl", "data/shader/modelTex_fp.glsl");

	FBOSetup(edgeBinder.get(), edgeWindow.get(), float(thresshold)/100.0f, "data/shader/fbo_edge.glsl");
	FBOSetup(depthBinder.get(), depthWindow.get(), 0.0f, "data/shader/fbo_depth.glsl");

	while(true) {

		// シーン描画
		switch(WindowUpdate(mainWindow.get(), baseWindow.get(),
							edgeWindow.get(), depthWindow.get())) {
		  case WinStatus::BREAK:
			// プログラム終了
			return 0;

		  case WinStatus::CONTINUE:
			// メインループ処理を行わず再描画
			continue;

		  case WinStatus::NORMAL:
			// 以下の処理を行う。
			break;
		}
		
		// エッジ抽出用閾値の変更
		if(baseWindow->getSpecialKeyStatus(fk_Key::UP, false) == true) {
			++thresshold;
		}
		if(baseWindow->getSpecialKeyStatus(fk_Key::DOWN, false) == true) {
			if(thresshold > 0) --thresshold;
		}			
		
		// FBOシェーダーに閾値を送信
		edgeBinder->getParameter()->setRegister("Thresshold", float(thresshold)/100.0f);

		// 光源回転
		lightModel->glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::Y, 0.05);

		sprite->drawText(to_string(double(thresshold)/100.0), true);
		sprite->setPositionLT(SP_X, SP_Y);
		sprite->entryFirst(baseWindow.get(), scene.get(), camera.get());
		// マウスによるカメラ制御
		tb->update();
	}

	return 0;
}

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
