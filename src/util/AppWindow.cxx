#define _APPWINDOWSRC_

#include <FK/AppWindow.h>
#ifndef _MINGW_
#include <FL/x.H>
#endif
#include <FK/System.h>
#include <FK/MatExample.h>

using namespace FK;
using namespace FK::Material;
using namespace std;

#ifdef FK_CLI_CODE
class InnerWindow : public ::fk_Window
{
private:
	using callback_type = void(__stdcall *)(void);
	callback_type pPreInit;
	callback_type pPostInit;
	callback_type pPreDraw;
	callback_type pPostDraw;
	callback_type pPreDrawLeft;
	callback_type pPostDrawLeft;
	callback_type pPreDrawRight;
	callback_type pPostDrawRight;

public:
#ifdef _WIN64
	InnerWindow(
		uint64_t *argCallbacks,
		int x = 0, int y = 0,
		int w = 300, int h = 300, std::string name = "FK Window") : fk_Window(x, y, w, h, name)
#else
	InnerWindow(
		uint32_t *argCallbacks,
		int x = 0, int y = 0,
		int w = 300, int h = 300, std::string name = "FK Window") : fk_Window(x, y, w, h, name)
#endif
	{
		pPreInit = (callback_type)argCallbacks[0];
		pPostInit = (callback_type)argCallbacks[1];
		pPreDraw = (callback_type)argCallbacks[2];
		pPostDraw = (callback_type)argCallbacks[3];
		pPreDrawLeft = (callback_type)argCallbacks[4];
		pPostDrawLeft = (callback_type)argCallbacks[5];
		pPreDrawRight = (callback_type)argCallbacks[6];
		pPostDrawRight = (callback_type)argCallbacks[7];
	};

	void preInit() { pPreInit(); };
	void postInit() { pPostInit(); };
	void preDraw() { pPreDraw(); };
	void postDraw() { pPostDraw(); };
	void preDrawLeft() { pPreDrawLeft(); };
	void postDrawLeft() { pPostDrawLeft(); };
	void preDrawRight() { pPreDrawRight(); };
	void postDrawRight() { pPostDrawRight(); };
};
#endif

const static fk_Switch stArray[3] = {
	fk_Switch::UP,
	fk_Switch::DOWN,
	fk_Switch::RELEASE
};

fk_AppWindow::fk_AWData::fk_AWData(void) :
	ref_child(nullptr), ref_scene(&scene), ref_camera(&camera), tbFlag(false)
{
	light.setShape(&lightShape);
	light.setMaterial(WhiteLight);
	light.glMoveTo(0.0, 0.0, 0.0);
	light.glFocus(-1.0, -1.0, -1.0);

	scene.setBlendStatus(true);
	scene.entryCamera(&camera);
	scene.entryModel(&light);

	camera.glMoveTo(0.0, 0.0, 100.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);

	return;
}

#ifdef FK_CLI_CODE
#ifdef _WIN64
fk_AppWindow::fk_AppWindow(uint64_t *argCallbacks)
#else
fk_AppWindow::fk_AppWindow(uint32_t *argCallbacks)
#endif // _WIN64
#else
fk_AppWindow::fk_AppWindow(void)
#endif // FK_CLI_CODE
{
	fk_System::setcwd();
	fk_Material::initDefault();

	data = make_unique<fk_AWData>();

	data->mainWin = make_shared<Fl_Window>(512, 512, "FKAPP Window");
#ifdef FK_CLI_CODE
#ifdef _WIN64
	data->drawWin = make_unique<fk_Window>(InnerWindow(argCallbacks, 0, 0, 512, 512));
#else
	data->drawWin = make_unique<fk_Window>(InnerWindow(argCallbacks, 0, 0, 512, 512));
#endif // _WIN64
#else
	data->drawWin = make_unique<fk_Window>(0, 0, 512, 512);
#endif // FK_CLI_CODE
	data->mainWin->end();

	data->drawWin->setScene(&(data->scene));

#ifdef FK_CLI_CODE
	setFPS(60);
#else
	setFPS(0);
#endif

	data->tb = make_unique<fk_TrackBall>(data->drawWin.get(), &(data->camera));
	data->childMode = false;

	return;
}

fk_AppWindow::fk_AppWindow(fk_AppWindow &argParent)
{
	fk_System::setcwd();
	fk_Material::initDefault();
	data = make_unique<fk_AWData>();

	data->mainWin = argParent.data->mainWin;
	data->mainWin->begin();
	argParent.data->drawWin->resizeWindow(0, 0, data->mainWin->w(), data->mainWin->h()/2);
	data->drawWin = make_unique<fk_Window>(0, data->mainWin->h()/2,
										   data->mainWin->w(), data->mainWin->h()/2);
	data->mainWin->end();
	data->drawWin->setScene(&(data->scene));

#ifdef FK_CLI_CODE
	setFPS(60);
#else
	setFPS(0);
#endif

	data->tb = make_unique<fk_TrackBall>(data->drawWin.get(), &(data->camera));
	data->childMode = true;
	argParent.data->ref_child = this;

	return;
}

fk_AppWindow::~fk_AppWindow(void)
{
	data->drawWin->hide();
	data->mainWin->hide();

	//delete tb;
	//delete drawWin;
	//if(!childMode) delete mainWin;
}

void fk_AppWindow::setWindowName(const std::string &name)
{
	data->mainWin->label(name.c_str());
	return;
}

void fk_AppWindow::setSize(int argW, int argH)
{
	data->mainWin->resize(data->mainWin->x(), data->mainWin->y(), argW, argH);
	if(!data->childMode) data->drawWin->resizeWindow(0, 0, argW, argH);
}

void fk_AppWindow::setInnerSize(int argX, int argY, int argW, int argH)
{
	data->drawWin->resizeWindow(argX, argY, argW, argH);
}

void fk_AppWindow::setBGColor(double r, double g, double b)
{
	data->ref_scene->setBGColor((float)r, (float)g, (float)b);
}

void fk_AppWindow::setBGColor(const fk_Color &argColor)
{
	data->ref_scene->setBGColor(argColor);
}

void fk_AppWindow::setFPS(int argFPS)
{
	if(argFPS == 0) {
		data->fps = 0;
		data->fps_admin.setFrameSkipMode(false);
	} else {
		data->fps = argFPS;
		data->fps_admin.setFrameSkipMode(true);
		data->fps_admin.setFPS(argFPS);
	}
}

void fk_AppWindow::setTrackBallMode(bool argMode)
{
	data->tbFlag = argMode;
}

void fk_AppWindow::showGuide(fk_Guide argMode)
{
	data->guide.entryScene(data->ref_scene, argMode);
}

void fk_AppWindow::hideGuide(void)
{
	data->guide.removeScene(data->ref_scene);
}

void fk_AppWindow::setCameraPos(double argX, double argY, double argZ)
{
	data->ref_camera->glMoveTo(argX, argY, argZ);
}

void fk_AppWindow::setCameraPos(const fk_Vector &argPos)
{
	data->ref_camera->glMoveTo(argPos);
}

void fk_AppWindow::setCameraFocus(double argX, double argY, double argZ)
{
	data->ref_camera->glFocus(argX, argY, argZ);
	data->tb->setLookTo(fk_Vector(argX, argY, argZ));
}

void fk_AppWindow::setCameraFocus(const fk_Vector &argPos)
{
	data->ref_camera->glFocus(argPos);
	data->tb->setLookTo(argPos);
}

void fk_AppWindow::setCameraModel(fk_Model &model)
{
	data->ref_camera = &model;
	data->tb->setCamera(&model);
	data->ref_scene->entryCamera(data->ref_camera);
}

void fk_AppWindow::setCameraModel(fk_Model *argModel)
{
	data->ref_camera = argModel;
	data->tb->setCamera(argModel);
	data->ref_scene->entryCamera(data->ref_camera);
}

fk_Model * fk_AppWindow::getCameraModel(void)
{
	return data->ref_camera;
}

void fk_AppWindow::setCameraDefault(void)
{
	setCameraModel(&(data->camera));
}

void fk_AppWindow::setLightDefault(void)
{
	data->ref_scene->entryModel(&(data->light));
}

void fk_AppWindow::setDefaultLightVec(const fk_Vector &argV)
{
	data->light.glVec(argV);
}

void fk_AppWindow::setDefaultLightVec(double argX, double argY, double argZ)
{
	data->light.glVec(argX, argY, argZ);
}

fk_Vector fk_AppWindow::getDefaultLightVec(void)
{
	return data->light.getVec();
}

void fk_AppWindow::setDefaultLightMaterial(const fk_Material &argM)
{
	data->light.setMaterial(argM);
}

fk_Material * fk_AppWindow::getDefaultLightMaterial(void)
{
	return data->light.getMaterial();
}

void fk_AppWindow::setScene(fk_Scene &argScene, bool argLightAndCamera)
{
	this->setScene(&argScene, argLightAndCamera);
}

void fk_AppWindow::setScene(fk_Scene *argScene, bool argLightAndCamera)
{
	if(argScene == nullptr) {
		data->ref_scene = &(data->scene);
	} else {
		data->ref_scene = argScene;
	}

	data->ref_camera = const_cast<fk_Model *>(data->ref_scene->getCamera());
	data->ref_scene->setBlendStatus(true);
	data->drawWin->setScene(data->ref_scene);
	if(argLightAndCamera) {
		data->ref_scene->entryCamera(&(data->camera));
		data->ref_scene->entryModel(&(data->light));
	}
}

fk_Scene * fk_AppWindow::getScene(void)
{
	return data->ref_scene;
}

void fk_AppWindow::setSceneDefault(void)
{
	setScene(&(data->scene), true);
}

void fk_AppWindow::entry(fk_Model &model)
{
	data->ref_scene->entryModel(&model);
}

void fk_AppWindow::remove(fk_Model &model)
{
	data->ref_scene->removeModel(&model);
}

void fk_AppWindow::entry(fk_Model &model, fk_GuideObject &argGuide)
{
	argGuide.setParent(&model);
	argGuide.entryScene(data->ref_scene);
	data->ref_scene->entryModel(&model);
}

void fk_AppWindow::remove(fk_Model &model, fk_GuideObject &argGuide)
{
	argGuide.setParent(nullptr);
	argGuide.removeScene(data->ref_scene);
	data->ref_scene->removeModel(&model);
}

void fk_AppWindow::entry(fk_SpriteModel &model)
{
	model.MakePixelBase(fk_Dimension(data->drawWin->w(), data->drawWin->h()), data->ref_scene);
	data->ref_scene->entryOverlayModel(&model);
}

void fk_AppWindow::remove(fk_SpriteModel &model)
{
	data->ref_scene->removeOverlayModel(&model);
}

void fk_AppWindow::entry(fk_Performer &chara)
{
	chara.entryScene(data->ref_scene);
}

void fk_AppWindow::remove(fk_Performer &chara)
{
	chara.removeScene(data->ref_scene);
}

void fk_AppWindow::entry(fk_Model *model)
{
	data->ref_scene->entryModel(model);
}

void fk_AppWindow::remove(fk_Model *model)
{
	data->ref_scene->removeModel(model);
}

void fk_AppWindow::entry(fk_Model *model, fk_GuideObject *argGuide)
{
	argGuide->setParent(model);
	argGuide->entryScene(data->ref_scene);
	data->ref_scene->entryModel(model);
}

void fk_AppWindow::remove(fk_Model *model, fk_GuideObject *argGuide)
{
	argGuide->setParent(nullptr);
	argGuide->removeScene(data->ref_scene);
	data->ref_scene->removeModel(model);
}

void fk_AppWindow::entry(fk_SpriteModel *model)
{
	model->MakePixelBase(fk_Dimension(data->drawWin->w(), data->drawWin->h()), data->ref_scene);
	data->ref_scene->entryOverlayModel(model);
}

void fk_AppWindow::remove(fk_SpriteModel *model)
{
	data->ref_scene->removeOverlayModel(model);
}

void fk_AppWindow::entry(fk_Performer *chara)
{
	chara->entryScene(data->ref_scene);
}

void fk_AppWindow::remove(fk_Performer *chara)
{
	chara->removeScene(data->ref_scene);
}

void fk_AppWindow::clearModel(bool argLightAndCamera)
{
	data->ref_scene->clearDisplay();
	if(argLightAndCamera) {
		data->ref_scene->entryCamera(&(data->camera));
		data->ref_scene->entryModel(&(data->light));
		data->ref_camera = &(data->camera);
		data->tb->setCamera(&(data->camera));
	}
}

void fk_AppWindow::open(void)
{
	data->mainWin->show();
	data->drawWin->show();

	data->fsc.init(data->mainWin.get(), data->drawWin.get());
	Fl::check();

	return;
}

void fk_AppWindow::close(void)
{
	data->drawWin->hide();
	if(!data->childMode) {
		toWindow();
		data->mainWin->hide();
	}

	return;
}

bool fk_AppWindow::update(bool argForceDraw)
{
	if(data->childMode) return false;

	if(data->fps != 0) data->fps_admin.timeRegular();

	if(data->mainWin->visible() == 0) {
		if(Fl::wait() == 0) {
			return false;
		} else {
			return true;
		}
	}

	if(data->fps_admin.getDrawFlag() || data->fps == 0 || argForceDraw) {
		data->drawWin->drawWindow();
		if(data->ref_child != nullptr) data->ref_child->data->drawWin->drawWindow();
	}
	if(Fl::check() == 0) return false;

	ToggleScreen();

	if(data->tbFlag) data->tb->update();
	if(data->ref_child != nullptr) {
		data->ref_child->data->tb->update();
	}

	return true;
}

fk_Switch GetSwitchStatus(bool now, bool pre)
{
	switch((int)now*2 + (int)pre) {
	case 0:
		return fk_Switch::RELEASE;
	case 1:
		return fk_Switch::UP;
	case 2:
		return fk_Switch::DOWN;
	case 3:
		return fk_Switch::PRESS;
	default:
		return fk_Switch::RELEASE;
	}
}

bool fk_AppWindow::getKeyStatus(char argKey, fk_Switch argStatus, bool argInsideFlg)
{
	return data->drawWin->getKeyStatus(argKey, argStatus, argInsideFlg);
}

fk_Switch fk_AppWindow::getKeyStatus(char argKey)
{
	//return GetSwitchStatus(data->drawWin->getKeyStatus(argKey, false), prevKeySt[(int)argKey]);

	for(int i = 0; i < 3; ++i) {
		if(getKeyStatus(argKey, stArray[i], false) == true) return stArray[i];
	}
	return fk_Switch::PRESS;
}

bool fk_AppWindow::getSpecialKeyStatus(fk_Key argKey,
									   fk_Switch argStatus, bool argInsideFlg)
{
	return data->drawWin->getSpecialKeyStatus(argKey, argStatus, argInsideFlg);
}

fk_Switch fk_AppWindow::getSpecialKeyStatus(fk_Key argKey)
{
	//return GetSwitchStatus(data->drawWin->getSpecialKeyStatus(argKey, false), prevSPKeySt[(int)argKey]);

	for(int i = 0; i < 3; ++i) {
		if(getSpecialKeyStatus(argKey, stArray[i], false) == true) return stArray[i];
	}
	return fk_Switch::PRESS;
}

bool fk_AppWindow::getMouseStatus(fk_MouseButton argButton,
								  fk_Switch argStatus, bool argInsideFlg)
{
	return data->drawWin->getMouseStatus(argButton, argStatus, argInsideFlg);
}

fk_Switch fk_AppWindow::getMouseStatus(fk_MouseButton argButton)
{
	//return GetSwitchStatus(data->drawWin->getMouseStatus(argButton, false), prevMouseSt[(int)argButton]);

	for(int i = 0; i < 3; ++i) {
		if(getMouseStatus(argButton, stArray[i], false) == true) return stArray[i];
	}
	return fk_Switch::PRESS;
}

fk_Vector fk_AppWindow::getMousePosition(void)
{
	auto [x, y] = data->drawWin->getMousePosition(false);
	return fk_Vector(double(x), double(y), 0.0);
}

void fk_AppWindow::setGuideAxisWidth(double width)
{
	data->guide.setAxisWidth(width);
}

void fk_AppWindow::setGuideGridWidth(double width)
{
	data->guide.setGridWidth(width);
}

void fk_AppWindow::setGuideScale(double scale)
{
	data->guide.setScale(scale);
}

void fk_AppWindow::setGuideNum(int num)
{
	data->guide.setNum(num);
}

#if defined(WIN32) && !defined(_MINGW_)
void fk_AppWindow::setCursorState(bool visible, bool center)
{
	if(visible) {
		ShowCursor(TRUE);
	} else {
		ShowCursor(FALSE);
	}
	if(center) {
		SetCursorPos(data->mainWin->x()+data->mainWin->w()/2, data->mainWin->y()+data->mainWin->h()/2);
	}
	return;
}
#else
void fk_AppWindow::setCursorState(bool, bool)
{
	return;
}
#endif

#if defined(WIN32) && !defined(_MINGW_)
void fk_AppWindow::procMouseView(fk_Model *camera, double spinX, double spinY, bool lockSW)
{
	static POINT	po;
	static int		nowX, nowY, prevX, prevY, nowZ;
	static double	diffX, diffY;
	static bool		once = false;

	GetCursorPos(&po);
	if(once == false) {
		prevX = po.x;
		prevY = po.y;
		once = true;
	}

	nowX = po.x;
	nowY = po.y;
	diffX = double(nowX) - double(prevX);
	diffY = double(nowY) - double(prevY);
	camera->glRotateWithVec(camera->getPosition(), fk_Axis::Y, -diffX*spinX);
	camera->glRotateWithVec(camera->getPosition(), camera->getPosition()+(camera->getVec()^camera->getUpVec()), -diffY*spinY);
	if(lockSW == true){
		SetCursorPos(prevX, prevY);
	} else {
		prevX = nowX;
		prevY = nowY;
	}
}

void fk_AppWindow::procMouseView(fk_Model &camera, double spinX, double spinY, bool lockSW)
{
	this->procMouseView(&camera, spinX, spinY, lockSW);
}
#else
void fk_AppWindow::procMouseView(fk_Model *, double, double, bool)
{
	return;
}
void fk_AppWindow::procMouseView(fk_Model &, double, double, bool)
{
	return;
}
#endif

void fk_AppWindow::toFullscreen(void)
{
	if(!data->fsc.isFullscreen()) data->fsc.changeToFullscreen();
}

void fk_AppWindow::toWindow(void)
{
	if(data->fsc.isFullscreen()) data->fsc.changeToWindow();
}

void fk_AppWindow::SetFinalizeMode(void)
{
	data->camera.SetTreeDelMode(false);
	data->light.SetTreeDelMode(false);
}

tuple<bool, fk_Vector> fk_AppWindow::getProjectPosition(double argX, double argY,
														fk_Plane &argPlane)
{
	return data->drawWin->getProjectPosition(argX, argY, argPlane);
}

#ifndef FK_OLD_NONSUPPORT
bool fk_AppWindow::getProjectPosition(double argX, double argY,
									  fk_Plane *argPlane, fk_Vector *argPos)
{
	return data->drawWin->getProjectPosition(argX, argY, argPlane, argPos);
}
#endif

tuple<bool, fk_Vector> fk_AppWindow::getProjectPosition(double argX, double argY, double argDist)
{
	return data->drawWin->getProjectPosition(argX, argY, argDist);
}

#ifndef FK_OLD_NONSUPPORT
bool fk_AppWindow::getProjectPosition(double argX, double argY,
									  double argDist, fk_Vector *argPos)
{
	return data->drawWin->getProjectPosition(argX, argY, argDist, argPos);
}
#endif

tuple<bool, fk_Vector> fk_AppWindow::getWindowPosition(fk_Vector &argPos_3D)
{
	return data->drawWin->getWindowPosition(argPos_3D);
}

#ifndef FK_OLD_NONSUPPORT
bool fk_AppWindow::getWindowPosition(fk_Vector argPos_3D, fk_Vector *argPos_2D)
{
	return data->drawWin->getWindowPosition(argPos_3D, argPos_2D);
}
#endif

bool fk_AppWindow::snapImage(string argFileName, fk_ImageType argFormat, fk_SnapProcMode argMode)
{
	return data->drawWin->snapImage(argFileName, argFormat, argMode);
}

bool fk_AppWindow::snapImage(fk_Image *argImage, fk_SnapProcMode argMode)
{
	return data->drawWin->snapImage(argImage, argMode);
}


void fk_AppWindow::setShadowMode(fk_ShadowMode argMode)
{
	data->ref_scene->setShadowMode(argMode);
}

fk_ShadowMode fk_AppWindow::getShadowMode(void)
{
	return data->ref_scene->getShadowMode();
}

void fk_AppWindow::setShadowVec(const fk_Vector &argV)
{
	data->ref_scene->setShadowVec(argV);
}

void fk_AppWindow::setShadowVec(double argX, double argY, double argZ)
{
	data->ref_scene->setShadowVec(argX, argY, argZ);
}

fk_Vector fk_AppWindow::getShadowVec(void)
{
	return data->ref_scene->getShadowVec();
}

void fk_AppWindow::setShadowResolution(int argRes)
{
	data->ref_scene->setShadowResolution(argRes);
}
	
int fk_AppWindow::getShadowResolution(void)
{
	return data->ref_scene->getShadowResolution();
}

void fk_AppWindow::setShadowAreaSize(double argSize)
{
	data->ref_scene->setShadowAreaSize(argSize);
}

double fk_AppWindow::getShadowAreaSize(void)
{
	return data->ref_scene->getShadowAreaSize();
}

void fk_AppWindow::setShadowDistance(double argDis)
{
	data->ref_scene->setShadowDistance(argDis);
}

double fk_AppWindow::getShadowDistance(void)
{
	return data->ref_scene->getShadowDistance();
}

void fk_AppWindow::setShadowVisibility(double argVal)
{
	data->ref_scene->setShadowVisibility(argVal);
}

double fk_AppWindow::getShadowVisibility(void)
{
	return data->ref_scene->getShadowVisibility();
}

void fk_AppWindow::setShadowBias(double argBias)
{
	data->ref_scene->setShadowBias(argBias);
}

double fk_AppWindow::getShadowBias(void)
{
	return data->ref_scene->getShadowBias();
}

void fk_AppWindow::setFogMode(const fk_FogMode argMode)
{
	data->ref_scene->setFogMode(argMode);
}

void fk_AppWindow::setFogDensity(const double argD)
{
	data->ref_scene->setFogDensity(argD);
}

void fk_AppWindow::setFogLinearMap(const double argS, const double argE)
{
	data->ref_scene->setFogLinearMap(argS, argE);
}

void fk_AppWindow::setFogColor(const fk_Color &argCol)
{
	data->ref_scene->setFogColor(argCol);
}

void fk_AppWindow::setFogColor(float argR, float argG, float argB, float argA)
{
	data->ref_scene->setFogColor(argR, argG, argB, argA);
}

void fk_AppWindow::setFogColor(double argR, double argG, double argB, double argA)
{
	data->ref_scene->setFogColor(argR, argG, argB, argA);
}

fk_FogMode fk_AppWindow::getFogMode(void) const
{
	return data->ref_scene->getFogMode();
}

double fk_AppWindow::getFogDensity(void) const
{
	return data->ref_scene->getFogDensity();
}

double fk_AppWindow::getFogLinearStart(void) const
{
	return data->ref_scene->getFogLinearStart();
}

double fk_AppWindow::getFogLinearEnd(void) const
{
	return data->ref_scene->getFogLinearEnd();
}

fk_Color fk_AppWindow::getFogColor(void) const
{
	return data->ref_scene->getFogColor();
}

fk_Window * fk_AppWindow::GetDrawWin(void) const
{
	return data->drawWin.get();
}

// スクリーンモードのハンドリング処理
void fk_AppWindow::ToggleScreen(void)
{
	// ALT+ENTERでフルスクリーンとウィンドウモードを切り替え
	if(getSpecialKeyStatus(fk_Key::ALT_L) >= fk_Switch::DOWN
	|| getSpecialKeyStatus(fk_Key::ALT_R) >= fk_Switch::DOWN) {
		if(getSpecialKeyStatus(fk_Key::ENTER) == fk_Switch::DOWN) {
			if(data->fsc.isFullscreen() == true) {
				data->fsc.changeToWindow();
			} else {
				data->fsc.changeToFullscreen();
			}
		}
	}
	// ウィンドウのフォーカスが外れたらウィンドウモードに戻す
	if(Fl::focus() != data->mainWin.get()) {
		toWindow();
	}

	return;
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
