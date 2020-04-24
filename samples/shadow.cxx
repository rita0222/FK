#include <FK/FK.h>

using namespace std;
using namespace FK;

const int WIN_W = 1024; // ウィンドウ横幅
const int WIN_H = 1024; // ウィンドウ縦幅

// 通常モデルのシェーダー設定
void ModelSetup(fk_Model *argModel, fk_Material argMat, fk_Vector argPos)
{
	argModel->setMaterial(argMat);
	argModel->setSmoothMode(true);
	argModel->glMoveTo(argPos);
}

void BallMove(fk_AppWindow *argWindow, fk_Model *argModel)
{
	double step = 0.5;

	if(argWindow->getSpecialKeyStatus(fk_Key::UP, fk_Switch::PRESS)) {
		argModel->glTranslate(0.0, 0.0, -step);
	}
	if(argWindow->getSpecialKeyStatus(fk_Key::DOWN, fk_Switch::PRESS)) {
		argModel->glTranslate(0.0, 0.0, step);
	}
	if(argWindow->getSpecialKeyStatus(fk_Key::RIGHT, fk_Switch::PRESS)) {
		argModel->glTranslate(step, 0.0, 0.0);
	}
	if(argWindow->getSpecialKeyStatus(fk_Key::LEFT, fk_Switch::PRESS)) {
		argModel->glTranslate(-step, 0.0, 0.0);
	}
}

void RobotRotate(fk_AppWindow *argWindow, fk_Model *argModel)
{
	fk_Vector origin;
	if(argWindow->getKeyStatus('z', fk_Switch::PRESS)) {
		argModel->loRotateWithVec(origin, fk_Axis::Y, fk_Math::PI/60.0);
	}
	if(argWindow->getKeyStatus('x', fk_Switch::PRESS)) {
		argModel->loRotateWithVec(origin, fk_Axis::Y, -fk_Math::PI/60.0);
	}
}

void ShadowChange(int argCount, fk_Model *argModel)
{
	if((argCount/100) % 2 == 0) {
		argModel->setShadowEffect(true);
	} else {
		argModel->setShadowEffect(false);
	}
}

int main(int, char **)
{
	fk_System::setcwd();
	Error::SetMode(Error::Mode::BROWSER_INTERACTIVE);

	fk_AppWindow *window = new fk_AppWindow();
	fk_Material *mat = new fk_Material();

	fk_IFSTexture *ifsShape = new fk_IFSTexture();
	fk_Sphere *sph = new fk_Sphere(8, 7.0);
	fk_Block *floor = new fk_Block(200.0, 2.0, 200.0);
	fk_Model *spModel = new fk_Model();
	fk_Model *ifsModel = new fk_Model();
	fk_Model *floorModel = new fk_Model();

	fk_Color bgColor(0.5, 0.5, 0.5);

	fk_Material::initDefault();
	window->setSize(WIN_W, WIN_H);
	window->setTrackBallMode(true);
	window->showGuide();

	window->setCameraPos(0.0, 50.0, 200.0);
	window->setCameraFocus(0.0, 0.0, 0.0);
	window->setDefaultLightVec(1.0, -1.0, 1.0);
	window->setDefaultLightMaterial(Material::WhiteLight);

	window->setFogMode(fk_FogMode::EXP2);
	window->setFogColor(bgColor);
	window->setFogLinearMap(20.0, 300.0);
	window->setFogDensity(0.005);

	// モデル
	if(ifsShape->readBMP("data/model/00tex_master.BMP") == false) {
		fl_alert("tex load err");
	}

	if(ifsShape->readMQOFile("data/model/meka.mqo", "body01") == false) {
		fl_alert("ifs load err");
	}

	ifsShape->setTexRendMode(fk_TexRendMode::SMOOTH);
	spModel->setShape(sph);
	ifsModel->setShape(ifsShape);
	floorModel->setShape(floor);

	spModel->setShadowEffect(true);
	spModel->setShadowDraw(true);
	ifsModel->setShadowEffect(false);
	ifsModel->setShadowDraw(true);
	floorModel->setShadowDraw(true);

	//spModel->setFogMode(false);
	ifsModel->setFogMode(false);
	
	// 各モデルをディスプレイリストに登録
	window->setBGColor(bgColor);
	window->entry(floorModel);
	window->entry(spModel);
	window->entry(ifsModel);

	//fk_ShadowMode mode = fk_ShadowMode::OFF;
	//fk_ShadowMode mode = fk_ShadowMode::HARD;
	//fk_ShadowMode mode = fk_ShadowMode::SOFT_FAST;
	fk_ShadowMode mode = fk_ShadowMode::SOFT_NICE;
	window->setShadowMode(mode);
	window->setShadowVec(1.0, -1.0, 1.0);
	window->setShadowAreaSize(500.0);
	window->setShadowDistance(300.0);
	window->setShadowResolution(1024);
	window->setShadowVisibility(1.0);
	window->setShadowBias(0.005);

	ModelSetup(spModel, Material::Yellow, fk_Vector(-20.0, 20.0, 0.0));
	ModelSetup(ifsModel, Material::White, fk_Vector(20.0, 5.0, 0.0));
	ModelSetup(floorModel, Material::White, fk_Vector(0.0, -1.0, 0.0));

	window->open();
	for(int count = 0; window->update(); ++count) {
		BallMove(window, spModel);
		RobotRotate(window, ifsModel);
		ShadowChange(count, ifsModel);
	}


	delete floorModel;
	delete ifsModel;
	delete spModel;
	delete floor;
	delete sph;
	delete ifsShape;
	delete mat;
	delete window;

	return 0;
}
