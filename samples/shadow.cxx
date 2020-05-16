#include <FK/FK.h>
#include <FL/fl_draw.H>
#include <memory>

using namespace std;
using namespace FK;

const int WIN_W = 1024; // ウィンドウ横幅
const int WIN_H = 1024; // ウィンドウ縦幅

#ifdef WIN32
#define CODE(x) fk_Code::utf8(x)
#else
#define CODE(x) x
#endif

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

void ShadowVecChange(int argCount, fk_AppWindow *argWindow)
{
	fk_Matrix rotMat;
	rotMat.makeRot(double(argCount)/100.0, fk_Axis::Y);

	fk_Vector vec = rotMat * fk_Vector(1.0, -1.0, 0.0);
	argWindow->setShadowVec(vec);
	argWindow->setDefaultLightVec(vec);
}

void ShadowChange(fk_AppWindow *argWindow, fk_Model *argModel, char argC1, char argC2)
{
	if(argWindow->getKeyStatus(argC1, fk_Switch::DOWN)) {
		argModel->setShadowEffect((argModel->getShadowEffect()) ? false : true);
	}
	if(argWindow->getKeyStatus(argC2, fk_Switch::DOWN)) {
		argModel->setShadowDraw((argModel->getShadowDraw()) ? false : true);
	}
}

int main(int, char **)
{
	fk_System::setcwd();
	Error::SetMode(Error::Mode::BROWSER_INTERACTIVE);
#ifdef _LINUX_
	Fl::set_font(0, "mono");
	fl_font(0, 36);
#endif

	unique_ptr<fk_AppWindow> window(new fk_AppWindow());
	unique_ptr<fk_Material> mat(new fk_Material());

	unique_ptr<fk_IFSTexture> ifsShape(new fk_IFSTexture());
	unique_ptr<fk_Sphere> sph(new fk_Sphere(8, 7.0));
	unique_ptr<fk_Block> floor(new fk_Block(200.0, 2.0, 200.0));
	unique_ptr<fk_Model> spModel(new fk_Model());
	unique_ptr<fk_Model> ifsModel(new fk_Model());
	unique_ptr<fk_Model> floorModel(new fk_Model());

	fk_Color bgColor(0.5, 0.5, 0.5);

	window->setSize(WIN_W, WIN_H);
	window->setTrackBallMode(true);
	window->showGuide();

	window->setCameraPos(0.0, 50.0, 200.0);
	window->setCameraFocus(0.0, 0.0, 0.0);
	window->setDefaultLightVec(1.0, -1.0, 1.0);
	window->setDefaultLightMaterial(Material::WhiteLight);

	// モデル
	if(ifsShape->readBMP("data/model/00tex_master.BMP") == false) {
		fl_alert("tex load err");
	}

	if(ifsShape->readMQOFile("data/model/meka.mqo", "body01") == false) {
		fl_alert("ifs load err");
	}

	ifsShape->setTexRendMode(fk_TexRendMode::SMOOTH);
	spModel->setShape(sph.get());
	ifsModel->setShape(ifsShape.get());
	floorModel->setShape(floor.get());

	// 各モデルをディスプレイリストに登録
	window->setBGColor(bgColor);
	window->entry(floorModel.get());
	window->entry(spModel.get());
	window->entry(ifsModel.get());

	//fk_ShadowMode mode = fk_ShadowMode::OFF;
	//fk_ShadowMode mode = fk_ShadowMode::HARD;
	//fk_ShadowMode mode = fk_ShadowMode::SOFT_FAST;
	fk_ShadowMode mode = fk_ShadowMode::SOFT_NICE;
	window->setShadowMode(mode);
	window->setShadowVec(1.0, 0.0, 1.0);
	window->setShadowAreaSize(500.0);
	window->setShadowDistance(300.0);
	window->setShadowResolution(1024);
	window->setShadowVisibility(1.0);
	window->setShadowBias(0.005);

	ModelSetup(spModel.get(), Material::Yellow, fk_Vector(-20.0, 20.0, 0.0));
	ModelSetup(ifsModel.get(), Material::White, fk_Vector(20.0, 5.0, 0.0));
	ModelSetup(floorModel.get(), Material::White, fk_Vector(0.0, -1.0, 0.0));

	window->open();

#ifdef WIN32
	fk_Code::setInputCoding(fk_StringCode::SJIS);
#endif

	fk_Window::putString(CODE("1 : 球影効果 ON/OFF"));
	fk_Window::putString(CODE("2 : 球影描画 ON/OFF"));
	fk_Window::putString(CODE("3 : ロボット影効果 ON/OFF"));
	fk_Window::putString(CODE("4 : ロボット影描画 ON/OFF"));
	fk_Window::putString(CODE("z : ロボット 反時計回り回転"));
	fk_Window::putString(CODE("x : ロボット 時計回り回転"));
	fk_Window::putString(CODE("矢印 : 球移動"));
	
	for(int count = 0; window->update(); ++count) {
		BallMove(window.get(), spModel.get());
		RobotRotate(window.get(), ifsModel.get());
		ShadowVecChange(count, window.get());
		ShadowChange(window.get(), spModel.get(), '1', '2');
		ShadowChange(window.get(), ifsModel.get(), '3', '4');
	}

	return 0;
}
