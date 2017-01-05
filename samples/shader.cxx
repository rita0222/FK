#include <FK/FK.h>

using namespace std;
using namespace FK;
using namespace FK::Material;

const int WIN_W = 500; // ウィンドウ横幅
const int WIN_H = 500; // ウィンドウ縦幅
const double SP_X = -(double(WIN_W/2) - 10.0);
const double SP_Y = double(WIN_H/2) - 10.0;
//const double SP_X = 0.0;
//const double SP_Y = 0.0;

enum WinStatus {
	NORMAL, CONTINUE, BREAK
};


// 通常モデルのシェーダー設定
void ShaderSetup(fk_ShaderBinder *argBinder, fk_Model *argModel, fk_Material argMat,
				 fk_Vector argPos, string argVP, string argFP)
{
	argModel->setMaterial(argMat);
	argModel->setSmoothMode(true);
	argModel->glMoveTo(argPos);
	argBinder->getProgram()->loadVertexShader(argVP);
	argBinder->getProgram()->loadFragmentShader(argFP);
	if(argBinder->getProgram()->validate()) {
		argBinder->bindModel(argModel);
	} else {
		fl_alert("Shader Error 2");
	} 
}

// FBOシェーダー設定
void FBOSetup(fk_ShaderBinder *argBinder, fk_Window *argWindow,
			  float argTH, string argVP, string argFP)
{
	argBinder->getProgram()->loadVertexShader(argVP);
	argBinder->getProgram()->loadFragmentShader(argFP);
	if(argBinder->getProgram()->validate()) {
		argBinder->initializeFrameBufferObject(WIN_W, WIN_H);
		argBinder->getParameter()->setRegister("tex0", 0);
		argBinder->getParameter()->setRegister("Width", float(WIN_W));
		argBinder->getParameter()->setRegister("Height", float(WIN_H));
		argBinder->getParameter()->setRegister("Thresshold", argTH);
		argBinder->bindWindow(argWindow);
	} else {
		fl_alert("Shader Error 3");
	}
}

// ウィンドウの再描画と状況把握
WinStatus WindowUpdate(Fl_Window *argMainWin, fk_Window *argBaseWin, fk_Window *argFBOWin)
{
	if(argMainWin->visible() == 0) {
		if(Fl::wait() == 0) {
			return BREAK;
		} else {
			return CONTINUE;
		}
	}

	if(argBaseWin->drawWindow() == 0) return BREAK;;
	if(argFBOWin->drawWindow() == 0) return BREAK;
	if(Fl::check() == 0) return BREAK;
	if(argBaseWin->winOpenStatus() == false) return CONTINUE;
	if(argFBOWin->winOpenStatus() == false) return CONTINUE;

	return NORMAL;
}

int main(int, char **)
{
	fk_System::setcwd();

	Fl_Window		mainWindow(WIN_W*2, WIN_H, "Shader Test");
	fk_Model		camera, lightModel;
	fk_Material		mat;
	fk_Light		light;
	fk_Scene		scene;
	fk_Window		baseWindow(0, 0, WIN_W, WIN_H);
	fk_Window		fboWindow(WIN_W, 0, WIN_W, WIN_H);

	fk_GuideObject	guide;
	fk_TrackBall	tb(&baseWindow, &camera);

	fk_IFSTexture	ifsShape;
	fk_Sphere		sph(8, 7.0);

	fk_SpriteModel	sprite;

	fk_Model		modelDef, ifsModelDef;
	fk_ShaderBinder spBinder, ifsBinder, fboBinder;
	int				thresshold = 80;

	mainWindow.end();
	fk_InitMaterial();
	fk_SetErrorMode(FK_ERR_BROWSER_INTERACTIVE);

	// 照明の設定
	lightModel.setShape(&light);
	mat.setAmbDiff(1.0f, 1.0f, 1.0f);
	mat.setSpecular(1.0f, 1.0f, 1.0f);
	lightModel.setMaterial(mat);
	lightModel.glMoveTo(0.0, 0.0, 0.0);
	lightModel.glFocus(-1.0, -1.0, -1.0);

	// 球と読み込みデータの設定
	if(ifsShape.readBMP("shader_test/mqo/00tex_master.BMP") == false) {
		fl_alert("tex load err");
	}

	if(ifsShape.readMQOFile("shader_test/mqo/meka.mqo", "body01") == false) {
		fl_alert("ifs load err");
	}
	ifsShape.setTexRendMode(FK_TEX_REND_SMOOTH);
	modelDef.setShape(&sph);
	ifsModelDef.setShape(&ifsShape);

	// スプライト設定
	if(sprite.initFont("rm1b.ttf") == false) {
		fl_alert("Font Init Error");
	}
	sprite.setPositionLT(SP_X, SP_Y);
	
	// 各モデルをディスプレイリストに登録
	scene.setBlendStatus(true);
	scene.setBGColor(0.5f, 0.5f, 0.5f);
	scene.entryCamera(&camera);
	scene.entryModel(&lightModel);
	guide.entryScene(&scene);
	scene.entryModel(&modelDef);
	scene.entryModel(&ifsModelDef);

	// ウィンドウへディスプレイリストを登録
	baseWindow.setScene(&scene);
	fboWindow.setScene(&scene);

	// 視点の位置と姿勢を設定
	camera.glMoveTo(0.0, 0.0, 100.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);
	//sprite.entryFirst(&baseWindow, &scene, &camera);

	// ウィンドウ生成 (シェーダー設定の前に行う必要がある。)
	mainWindow.show();
	baseWindow.show();
	fboWindow.show();
	Fl::check();

	// 各種シェーダー設定
	ShaderSetup(&spBinder, &modelDef, Yellow, fk_Vector(-20.0, 0.0, 0.0),
				"shader_test/shader/model_vp.glsl", "shader_test/shader/model_fp.glsl");
	
	ShaderSetup(&ifsBinder, &ifsModelDef, White, fk_Vector(20.0, 0.0, 0.0),
				"shader_test/shader/model_vp.glsl", "shader_test/shader/modelTex_fp.glsl");

	FBOSetup(&fboBinder, &fboWindow, float(thresshold)/100.0f,
			 "shader_test/shader/fbo_vp.glsl", "shader_test/shader/fbo_fp.glsl");
	

	while(true) {

		// シーン描画
		switch(WindowUpdate(&mainWindow, &baseWindow, &fboWindow)) {
		  case BREAK:
			// プログラム終了
			return 0;

		  case CONTINUE:
			// メインループ処理を行わず再描画
			continue;

		  case NORMAL:
			// 以下の処理を行う。
			break;
		}
		
		// エッジ抽出用閾値の変更
		if(baseWindow.getSpecialKeyStatus(FK_UP, false) == true) {
			++thresshold;
		}
		if(baseWindow.getSpecialKeyStatus(FK_DOWN, false) == true) {
			if(thresshold > 0) --thresshold;
		}			
		
		// FBOシェーダーに閾値を送信
		fboBinder.getParameter()->setRegister("Thresshold", float(thresshold)/100.0f);

		// 光源回転
		lightModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Y, 0.01);

		sprite.drawText(to_string(double(thresshold)/100.0), true);
		sprite.setPositionLT(SP_X, SP_Y);
		sprite.entryFirst(&baseWindow, &scene, &camera);

		// マウスによるカメラ制御
		tb.update();
	}

	return 0;
}
