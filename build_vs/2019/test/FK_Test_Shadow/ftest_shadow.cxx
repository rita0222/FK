﻿#include <FK/FK.h>

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

int main(int, char **)
{
	fk_System::setcwd();
	fk_SetErrorMode(fk_ErrorMode::BROWSER_INTERACTIVE);

	fk_AppWindow	window;
	fk_Material		mat;

	fk_IFSTexture	ifsShape;
	fk_Sphere		sph(8, 7.0);
	fk_Block		floor(200.0, 2.0, 200.0);

	fk_Model		spModel, ifsModel, floorModel;

	fk_Material::initDefault();
	window.setSize(WIN_W, WIN_H);
	window.open();
	window.update();
	Fl::check();
	window.setTrackBallMode(true);

	window.setCameraPos(0.0, 50.0, 200.0);
	window.setCameraFocus(0.0, 0.0, 0.0);
	window.setDefaultLightVec(1.0, -1.0, 1.0);
	window.setDefaultLightMaterial(Material::TrueWhite);

	// モデル
	if(ifsShape.readBMP("00tex_master.BMP") == false) {
		fl_alert("tex load err");
	}

	if(ifsShape.readMQOFile("meka.mqo", "body01") == false) {
		fl_alert("ifs load err");
	}

	ifsShape.setTexRendMode(fk_TexRendMode::SMOOTH);
	spModel.setShape(&sph);
	ifsModel.setShape(&ifsShape);
	floorModel.setShape(&floor);
	
	// 各モデルをディスプレイリストに登録
	//window.setBlendStatus(true);
	window.setBGColor(0.5f, 0.5f, 0.5f);
	window.entry(&spModel);
	window.entry(&ifsModel);
	window.entry(&floorModel);
	window.showGuide();

	window.setShadowMode(true);
	window.setShadowVec(1.0, -1.0, 1.0);
	window.setShadowAreaSize(500.0);
	window.setShadowDistance(500.0);
	window.setShadowResolution(2048);
	window.setShadowVisibility(0.8);

	ModelSetup(&spModel, Material::Yellow, fk_Vector(-20.0, 20.0, 0.0));
	ModelSetup(&ifsModel, Material::White, fk_Vector(20.0, 5.0, 0.0));
	ModelSetup(&floorModel, Material::White, fk_Vector(0.0, -1.0, 0.0));

	while(window.update()) {
		BallMove(&window, &spModel);
		RobotRotate(&window, &ifsModel);
	}

	return 0;
}
