#include <FK/FK.h>

using namespace FK;
using namespace FK::Material;

int main(int, char **)
{
	fk_AppWindow	window;
	fk_Model		lightModel;
	fk_Light		light;

	fk_IFSTexture	ifsShape;
	fk_Sphere		sph(8, 7.0);

	fk_Model		modelDef, ifsModelDef;
	fk_Model		sphShockModel;

	fk_InitMaterial();
	fk_System::setcwd();

	window.setSize(800, 600);
	window.clearModel();
	window.setCameraDefault();
	window.showGuide();
	window.setTrackBallMode(true);
	window.setBGColor(0.5f, 0.5f, 0.5f);

	// 照明の設定
	lightModel.setShape(&light);
	lightModel.setMaterial(White);
	lightModel.getMaterial()->setAmbDiff(1.0f, 1.0f, 1.0f);
	lightModel.getMaterial()->setSpecular(1.0f, 1.0f, 1.0f);
	lightModel.glMoveTo(0.0, 0.0, 0.0);
	lightModel.glFocus(-1.0, -1.0, -1.0);
	window.entry(&lightModel);

	// モデルの読み込み
	if(!ifsShape.readBMP("mqo/00tex_master.BMP")) fl_alert("tex load err");
	if(!ifsShape.readMQOFile("mqo/meka.mqo", "body01")) fl_alert("ifs load err");
	ifsShape.setTexRendMode(fk_TexRendMode::SMOOTH);

	window.open();
	if(window.update() == false) return 0;

	// この時点でGLSL関連の命令が解禁されるので、
	// ここまでにシェーダを使うモデルのエントリーや描画をしないようにする

	fk_ShaderBinder spBinder;
	modelDef.setShape(&sph);
	modelDef.setMaterial(Yellow);
	modelDef.setSmoothMode(true);
	modelDef.glMoveTo(-20.0, 0.0, 0.0);
	spBinder.getProgram()->loadVertexShader("shader/model_vp.glsl");
	spBinder.getProgram()->loadFragmentShader("shader/model_fp.glsl");
	if(spBinder.getProgram()->validate()) {
		spBinder.bindModel(&modelDef);
	} else {
		fk_Window::putString(spBinder.getProgram()->getLastError());
	}
	window.entry(&modelDef);

	fk_ShaderBinder ifsBinder;
	ifsModelDef.setShape(&ifsShape);
	ifsModelDef.setMaterial(White);
	ifsModelDef.setSmoothMode(true);
	ifsModelDef.glMoveTo(20.0, 0.0, 0.0);
	ifsBinder.getProgram()->loadVertexShader("shader/model_vp.glsl");
	ifsBinder.getProgram()->loadFragmentShader("shader/modelTex_fp.glsl");
	if(ifsBinder.getProgram()->validate()) {
		ifsBinder.bindModel(&ifsModelDef);
	} else {
		fk_Window::putString(ifsBinder.getProgram()->getLastError());
	}
		
	window.entry(&ifsModelDef);

	fk_ShaderBinder shockBinder;
	sphShockModel.setShape(&sph);
	sphShockModel.setMaterial(Red);
	sphShockModel.setSmoothMode(true);
	sphShockModel.setScale(0.01);
	sphShockModel.setBlendMode(fk_BlendMode::ADDITION);
	shockBinder.getProgram()->loadVertexShader("shader/shockSph_vp.glsl");
	shockBinder.getProgram()->loadFragmentShader("shader/shockSph_fp.glsl");
	if(shockBinder.getProgram()->validate()) {
		shockBinder.bindModel(&sphShockModel);
	} else {
		fk_Window::putString(shockBinder.getProgram()->getLastError());
	}
	window.entry(&sphShockModel);

	while(window.update()) {
		// 光源を回転させる。
		lightModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::Y, 0.01);

		// スペースキーで、衝撃波を大きくする。
		if(window.getKeyStatus(' ', fk_Switch::PRESS) == true) {
			sphShockModel.setScale(sphShockModel.getScale()+0.1);
		}

		// エンターキーで衝撃波の初期化。
		if(window.getSpecialKeyStatus(fk_SpecialKey::ENTER, fk_Switch::DOWN) == true) {
			sphShockModel.setScale(0.01);
		}
	}

	return 0;
}
