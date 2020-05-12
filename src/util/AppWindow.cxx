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

fk_AppWindow::Member::Member(void) :
	drawWin(nullptr), ref_child(nullptr), tb(nullptr),
	ref_scene(&scene), ref_camera(&camera),
	fps(0), tbFlag(false), childMode(false)
{
	return;
}



#ifdef FK_CLI_CODE
#ifdef _WIN64
fk_AppWindow::fk_AppWindow(uint64_t *argCallbacks) : _m(make_unique<Member>())
#else
fk_AppWindow::fk_AppWindow(uint32_t *argCallbacks) : _m(make_unique<Member>())
#endif // _WIN64
#else
fk_AppWindow::fk_AppWindow(void) : _m(make_unique<Member>())
#endif // FK_CLI_CODE
{
	fk_System::setcwd();

	_m->mainWin = make_shared<Fl_Window>(512, 512, "FKAPP Window");
#ifdef FK_CLI_CODE
	unique_ptr<InnerWindow> ptr(new InnerWindow(argCallbacks, 0, 0, 512, 512));
	_m->drawWin = move(ptr);
#else
	_m->drawWin = make_unique<fk_Window>(0, 0, 512, 512);
#endif // FK_CLI_CODE
	_m->mainWin->end();

	_m->light.setShape(&_m->lightShape);
	_m->light.setMaterial(WhiteLight);
	_m->light.glMoveTo(0.0, 0.0, 0.0);
	_m->light.glFocus(-1.0, -1.0, -1.0);

	_m->scene.setBlendStatus(true);
	_m->scene.entryCamera(&_m->camera);
	_m->scene.entryModel(&_m->light);

	_m->drawWin->setScene(&_m->scene);

#ifdef FK_CLI_CODE
	setFPS(60);
#else
	setFPS(0);
#endif

	_m->camera.glMoveTo(0.0, 0.0, 100.0);
	_m->camera.glFocus(0.0, 0.0, 0.0);
	_m->camera.glUpvec(0.0, 1.0, 0.0);

	_m->tb = make_unique<fk_TrackBall>(_m->drawWin.get(), &_m->camera);

	return;
}

fk_AppWindow::fk_AppWindow(fk_AppWindow &argParent) : _m(make_unique<Member>())
{
	_m->mainWin = argParent._m->mainWin;
	_m->mainWin->begin();
	argParent._m->drawWin->resizeWindow(0, 0, _m->mainWin->w(), _m->mainWin->h()/2);
	_m->drawWin = make_unique<fk_Window>(0, _m->mainWin->h() / 2,
		_m->mainWin->w(), _m->mainWin->h() / 2);
	_m->mainWin->end();

	_m->light.setShape(&_m->lightShape);
	_m->light.setMaterial(WhiteLight);
	_m->light.glMoveTo(0.0, 0.0, 0.0);
	_m->light.glFocus(-1.0, -1.0, -1.0);

	_m->scene.setBlendStatus(true);
	_m->scene.entryCamera(&_m->camera);
	_m->scene.entryModel(&_m->light);

	_m->drawWin->setScene(&_m->scene);

#ifdef FK_CLI_CODE
	setFPS(60);
#else
	setFPS(0);
#endif

	_m->camera.glMoveTo(0.0, 0.0, 100.0);
	_m->camera.glFocus(0.0, 0.0, 0.0);
	_m->camera.glUpvec(0.0, 1.0, 0.0);

	_m->tb = make_unique<fk_TrackBall>(_m->drawWin.get(), &_m->camera);
	_m->childMode = true;
	argParent._m->ref_child = this;

	return;
}

fk_AppWindow::~fk_AppWindow(void)
{
	_m->drawWin->hide();
	_m->mainWin->hide();

	//delete _m->tb;
	//delete _m->drawWin;
	//if(!_m->childMode) delete _m->mainWin;
}

// スクリーンモードのハンドリング処理
void fk_AppWindow::ToggleScreen(void)
{
	// ALT+ENTERでフルスクリーンとウィンドウモードを切り替え
	if (getSpecialKeyStatus(fk_Key::ALT_L) >= fk_Switch::DOWN
		|| getSpecialKeyStatus(fk_Key::ALT_R) >= fk_Switch::DOWN) {
		if (getSpecialKeyStatus(fk_Key::ENTER) == fk_Switch::DOWN) {
			if (_m->fsc.isFullscreen() == true) {
				_m->fsc.changeToWindow();
			}
			else {
				_m->fsc.changeToFullscreen();
			}
		}
	}
	// ウィンドウのフォーカスが外れたらウィンドウモードに戻す
	if (Fl::focus() != _m->mainWin.get()) {
		toWindow();
	}

	return;
}

void fk_AppWindow::setWindowName(const std::string &argName)
{
	_m->mainWin->label(argName.c_str());
	return;
}

void fk_AppWindow::setSize(int argW, int argH)
{
	_m->mainWin->resize(_m->mainWin->x(), _m->mainWin->y(), argW, argH);
	if(!_m->childMode) _m->drawWin->resizeWindow(0, 0, argW, argH);
}

void fk_AppWindow::setInnerSize(int argX, int argY, int argW, int argH)
{
	_m->drawWin->resizeWindow(argX, argY, argW, argH);
}

void fk_AppWindow::setBGColor(double argR, double argG, double argB)
{
	_m->ref_scene->setBGColor(float(argR), float(argG), float(argB));
}

void fk_AppWindow::setBGColor(const fk_Color &argColor)
{
	_m->ref_scene->setBGColor(argColor);
}

void fk_AppWindow::setFPS(int argFPS)
{
	if(argFPS == 0) {
		_m->fps = 0;
		_m->fps_admin.setFrameSkipMode(false);
	} else {
		_m->fps = argFPS;
		_m->fps_admin.setFrameSkipMode(true);
		_m->fps_admin.setFPS(argFPS);
	}
}

void fk_AppWindow::setTrackBallMode(bool argMode)
{
	_m->tbFlag = argMode;
}

void fk_AppWindow::showGuide(fk_Guide argMode)
{
	_m->guide.entryScene(_m->ref_scene, argMode);
}

void fk_AppWindow::hideGuide(void)
{
	_m->guide.removeScene(_m->ref_scene);
}

void fk_AppWindow::setCameraPos(double argX, double argY, double argZ)
{
	_m->ref_camera->glMoveTo(argX, argY, argZ);
}

void fk_AppWindow::setCameraPos(const fk_Vector &argPos)
{
	_m->ref_camera->glMoveTo(argPos);
}

void fk_AppWindow::setCameraFocus(double argX, double argY, double argZ)
{
	_m->ref_camera->glFocus(argX, argY, argZ);
	_m->tb->setLookTo(fk_Vector(argX, argY, argZ));
}

void fk_AppWindow::setCameraFocus(const fk_Vector &argPos)
{
	_m->ref_camera->glFocus(argPos);
	_m->tb->setLookTo(argPos);
}

void fk_AppWindow::setCameraModel(fk_Model &argModel)
{
	_m->ref_camera = &argModel;
	_m->tb->setCamera(&argModel);
	_m->ref_scene->entryCamera(_m->ref_camera);
}

void fk_AppWindow::setCameraModel(fk_Model *argModel)
{
	_m->ref_camera = argModel;
	_m->tb->setCamera(argModel);
	_m->ref_scene->entryCamera(_m->ref_camera);
}

fk_Model * fk_AppWindow::getCameraModel(void)
{
	return _m->ref_camera;
}

void fk_AppWindow::setCameraDefault(void)
{
	setCameraModel(_m->camera);
}

void fk_AppWindow::setLightDefault(void)
{
	_m->ref_scene->entryModel(&_m->light);
}

void fk_AppWindow::setDefaultLightVec(const fk_Vector &argV)
{
	_m->light.glVec(argV);
}

void fk_AppWindow::setDefaultLightVec(double argX, double argY, double argZ)
{
	_m->light.glVec(argX, argY, argZ);
}

fk_Vector fk_AppWindow::getDefaultLightVec(void)
{
	return _m->light.getVec();
}

void fk_AppWindow::setDefaultLightMaterial(const fk_Material &argM)
{
	_m->light.setMaterial(argM);
}

fk_Material * fk_AppWindow::getDefaultLightMaterial(void)
{
	return _m->light.getMaterial();
}

void fk_AppWindow::setScene(fk_Scene &argScene, bool argLightAndCamera)
{
	this->setScene(&argScene, argLightAndCamera);
}

void fk_AppWindow::setScene(fk_Scene *argScene, bool argLightAndCamera)
{
	if(argScene == nullptr) {
		_m->ref_scene = &_m->scene;
	} else {
		_m->ref_scene = argScene;
	}

	_m->ref_camera = const_cast<fk_Model *>(_m->ref_scene->getCamera());
	_m->ref_scene->setBlendStatus(true);
	_m->drawWin->setScene(_m->ref_scene);
	if(argLightAndCamera) {
		_m->ref_scene->entryCamera(&_m->camera);
		_m->ref_scene->entryModel(&_m->light);
	}
}

fk_Scene * fk_AppWindow::getScene(void)
{
	return _m->ref_scene;
}

void fk_AppWindow::setSceneDefault(void)
{
	setScene(_m->scene, true);
}

void fk_AppWindow::entry(fk_Model &argModel)
{
	_m->ref_scene->entryModel(&argModel);
}

void fk_AppWindow::remove(fk_Model &argModel)
{
	_m->ref_scene->removeModel(&argModel);
}

void fk_AppWindow::entry(fk_Model &argModel, fk_GuideObject &argGuide)
{
	argGuide.setParent(&argModel);
	argGuide.entryScene(_m->ref_scene);
	_m->ref_scene->entryModel(&argModel);
}

void fk_AppWindow::remove(fk_Model &argModel, fk_GuideObject &argGuide)
{
	argGuide.setParent(nullptr);
	argGuide.removeScene(_m->ref_scene);
	_m->ref_scene->removeModel(&argModel);
}

void fk_AppWindow::entry(fk_SpriteModel &argModel)
{
	argModel.MakePixelBase(fk_Dimension(_m->drawWin->w(),
		_m->drawWin->h()), _m->ref_scene);
	_m->ref_scene->entryOverlayModel(&argModel);
}

void fk_AppWindow::remove(fk_SpriteModel &argModel)
{
	_m->ref_scene->removeOverlayModel(&argModel);
}

void fk_AppWindow::entry(fk_Performer &argChara)
{
	argChara.entryScene(_m->ref_scene);
}

void fk_AppWindow::remove(fk_Performer &argChara)
{
	argChara.removeScene(_m->ref_scene);
}

void fk_AppWindow::entry(fk_Model *argModel)
{
	_m->ref_scene->entryModel(argModel);
}

void fk_AppWindow::remove(fk_Model *argModel)
{
	_m->ref_scene->removeModel(argModel);
}

void fk_AppWindow::entry(fk_Model *argModel, fk_GuideObject *argGuide)
{
	argGuide->setParent(argModel);
	argGuide->entryScene(_m->ref_scene);
	_m->ref_scene->entryModel(argModel);
}

void fk_AppWindow::remove(fk_Model *argModel, fk_GuideObject *argGuide)
{
	argGuide->setParent(nullptr);
	argGuide->removeScene(_m->ref_scene);
	_m->ref_scene->removeModel(argModel);
}

void fk_AppWindow::entry(fk_SpriteModel *argModel)
{
	argModel->MakePixelBase(fk_Dimension(_m->drawWin->w(),
		_m->drawWin->h()), _m->ref_scene);
	_m->ref_scene->entryOverlayModel(argModel);
}

void fk_AppWindow::remove(fk_SpriteModel *argModel)
{
	_m->ref_scene->removeOverlayModel(argModel);
}

void fk_AppWindow::entry(fk_Performer *argChara)
{
	argChara->entryScene(_m->ref_scene);
}

void fk_AppWindow::remove(fk_Performer *argChara)
{
	argChara->removeScene(_m->ref_scene);
}

void fk_AppWindow::clearModel(bool argLightAndCamera)
{
	_m->ref_scene->clearDisplay();
	if(argLightAndCamera) {
		_m->ref_scene->entryCamera(&_m->camera);
		_m->ref_scene->entryModel(&_m->light);
		_m->ref_camera = &_m->camera;
		_m->tb->setCamera(&_m->camera);
	}
}

void fk_AppWindow::open(void)
{
	_m->mainWin->show();
	_m->drawWin->show();

	_m->fsc.init(_m->mainWin.get(), _m->drawWin.get());
	Fl::check();

	return;
}

void fk_AppWindow::close(void)
{
	_m->drawWin->hide();
	if(!_m->childMode) {
		toWindow();
		_m->mainWin->hide();
	}

	return;
}

bool fk_AppWindow::update(bool argForceDraw)
{
	if(_m->childMode) return false;

	if(_m->fps != 0) _m->fps_admin.timeRegular();

	if(_m->mainWin->visible() == 0) {
		if(Fl::wait() == 0) {
			return false;
		} else {
			return true;
		}
	}

	if(_m->fps_admin.getDrawFlag() || _m->fps == 0 || argForceDraw) {
		_m->drawWin->drawWindow();
		if(_m->ref_child != nullptr) _m->ref_child->_m->drawWin->drawWindow();
	}
	if(Fl::check() == 0) return false;

	ToggleScreen();

	if(_m->tbFlag) _m->tb->update();
	if(_m->ref_child != nullptr) {
		_m->ref_child->_m->tb->update();
	}

	return true;
}

fk_Switch GetSwitchStatus(bool argNow, bool argPre)
{
	switch(int(argNow)*2 + int(argPre)) {
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
	return _m->drawWin->getKeyStatus(argKey, argStatus, argInsideFlg);
}

fk_Switch fk_AppWindow::getKeyStatus(char argKey)
{
	//return GetSwitchStatus(drawWin->getKeyStatus(argKey, false), prevKeySt[(int)argKey]);

	for(int i = 0; i < 3; ++i) {
		if(getKeyStatus(argKey, stArray[i], false) == true) return stArray[i];
	}
	return fk_Switch::PRESS;
}

bool fk_AppWindow::getSpecialKeyStatus(fk_Key argKey,
									   fk_Switch argStatus, bool argInsideFlg)
{
	return _m->drawWin->getSpecialKeyStatus(argKey, argStatus, argInsideFlg);
}

fk_Switch fk_AppWindow::getSpecialKeyStatus(fk_Key argKey)
{
	//return GetSwitchStatus(drawWin->getSpecialKeyStatus(argKey, false), prevSPKeySt[(int)argKey]);

	for(int i = 0; i < 3; ++i) {
		if(getSpecialKeyStatus(argKey, stArray[i], false) == true) return stArray[i];
	}
	return fk_Switch::PRESS;
}

bool fk_AppWindow::getMouseStatus(fk_MouseButton argButton,
								  fk_Switch argStatus, bool argInsideFlg)
{
	return _m->drawWin->getMouseStatus(argButton, argStatus, argInsideFlg);
}

fk_Switch fk_AppWindow::getMouseStatus(fk_MouseButton argButton)
{
	//return GetSwitchStatus(drawWin->getMouseStatus(argButton, false), prevMouseSt[(int)argButton]);

	for(int i = 0; i < 3; ++i) {
		if(getMouseStatus(argButton, stArray[i], false) == true) return stArray[i];
	}
	return fk_Switch::PRESS;
}

fk_Vector fk_AppWindow::getMousePosition(void)
{
	auto [x, y] = _m->drawWin->getMousePosition(false);
	return fk_Vector(double(x), double(y), 0.0);
}

void fk_AppWindow::setGuideAxisWidth(double width)
{
	_m->guide.setAxisWidth(width);
}

void fk_AppWindow::setGuideGridWidth(double width)
{
	_m->guide.setGridWidth(width);
}

void fk_AppWindow::setGuideScale(double scale)
{
	_m->guide.setScale(scale);
}

void fk_AppWindow::setGuideNum(int num)
{
	_m->guide.setNum(num);
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
		SetCursorPos(_m->mainWin->x() + _m->mainWin->w()/2,
			_m->mainWin->y() + _m->mainWin->h()/2);
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
	if(!_m->fsc.isFullscreen()) _m->fsc.changeToFullscreen();
}

void fk_AppWindow::toWindow(void)
{
	if(_m->fsc.isFullscreen()) _m->fsc.changeToWindow();
}

void fk_AppWindow::SetFinalizeMode(void)
{
	_m->camera.SetTreeDelMode(false);
	_m->light.SetTreeDelMode(false);
}

tuple<bool, fk_Vector> fk_AppWindow::getProjectPosition(double argX, double argY,
														fk_Plane &argPlane)
{
	return _m->drawWin->getProjectPosition(argX, argY, argPlane);
}

#ifndef FK_OLD_NONSUPPORT
bool fk_AppWindow::getProjectPosition(double argX, double argY,
									  fk_Plane *argPlane, fk_Vector *argPos)
{
	return drawWin->getProjectPosition(argX, argY, argPlane, argPos);
}
#endif

tuple<bool, fk_Vector> fk_AppWindow::getProjectPosition(double argX, double argY, double argDist)
{
	return _m->drawWin->getProjectPosition(argX, argY, argDist);
}

#ifndef FK_OLD_NONSUPPORT
bool fk_AppWindow::getProjectPosition(double argX, double argY,
									  double argDist, fk_Vector *argPos)
{
	return drawWin->getProjectPosition(argX, argY, argDist, argPos);
}
#endif

tuple<bool, fk_Vector> fk_AppWindow::getWindowPosition(fk_Vector &argPos_3D)
{
	return _m->drawWin->getWindowPosition(argPos_3D);
}

#ifndef FK_OLD_NONSUPPORT
bool fk_AppWindow::getWindowPosition(fk_Vector argPos_3D, fk_Vector *argPos_2D)
{
	return drawWin->getWindowPosition(argPos_3D, argPos_2D);
}
#endif

bool fk_AppWindow::snapImage(string argFileName, fk_ImageType argFormat, fk_SnapProcMode argMode)
{
	return _m->drawWin->snapImage(argFileName, argFormat, argMode);
}

bool fk_AppWindow::snapImage(fk_Image *argImage, fk_SnapProcMode argMode)
{
	return _m->drawWin->snapImage(argImage, argMode);
}


void fk_AppWindow::setShadowMode(fk_ShadowMode argMode)
{
	_m->ref_scene->setShadowMode(argMode);
}

fk_ShadowMode fk_AppWindow::getShadowMode(void)
{
	return _m->ref_scene->getShadowMode();
}

void fk_AppWindow::setShadowVec(const fk_Vector &argV)
{
	_m->ref_scene->setShadowVec(argV);
}

void fk_AppWindow::setShadowVec(double argX, double argY, double argZ)
{
	_m->ref_scene->setShadowVec(argX, argY, argZ);
}

fk_Vector fk_AppWindow::getShadowVec(void)
{
	return _m->ref_scene->getShadowVec();
}

void fk_AppWindow::setShadowResolution(int argRes)
{
	_m->ref_scene->setShadowResolution(argRes);
}
	
int fk_AppWindow::getShadowResolution(void)
{
	return _m->ref_scene->getShadowResolution();
}

void fk_AppWindow::setShadowAreaSize(double argSize)
{
	_m->ref_scene->setShadowAreaSize(argSize);
}

double fk_AppWindow::getShadowAreaSize(void)
{
	return _m->ref_scene->getShadowAreaSize();
}

void fk_AppWindow::setShadowDistance(double argDis)
{
	_m->ref_scene->setShadowDistance(argDis);
}

double fk_AppWindow::getShadowDistance(void)
{
	return _m->ref_scene->getShadowDistance();
}

void fk_AppWindow::setShadowVisibility(double argVal)
{
	_m->ref_scene->setShadowVisibility(argVal);
}

double fk_AppWindow::getShadowVisibility(void)
{
	return _m->ref_scene->getShadowVisibility();
}

void fk_AppWindow::setShadowBias(double argBias)
{
	_m->ref_scene->setShadowBias(argBias);
}

double fk_AppWindow::getShadowBias(void)
{
	return _m->ref_scene->getShadowBias();
}

void fk_AppWindow::setFogMode(const fk_FogMode argMode)
{
	_m->ref_scene->setFogMode(argMode);
}

void fk_AppWindow::setFogDensity(const double argD)
{
	_m->ref_scene->setFogDensity(argD);
}

void fk_AppWindow::setFogLinearMap(const double argS, const double argE)

{
	_m->ref_scene->setFogLinearMap(argS, argE);
}

void fk_AppWindow::setFogColor(const fk_Color &argCol)
{
	_m->ref_scene->setFogColor(argCol);
}

void fk_AppWindow::setFogColor(float argR, float argG, float argB, float argA)
{
	_m->ref_scene->setFogColor(argR, argG, argB, argA);
}

void fk_AppWindow::setFogColor(double argR, double argG, double argB, double argA)
{
	_m->ref_scene->setFogColor(argR, argG, argB, argA);
}

fk_FogMode fk_AppWindow::getFogMode(void) const
{
	return _m->ref_scene->getFogMode();
}

double fk_AppWindow::getFogDensity(void) const
{
	return _m->ref_scene->getFogDensity();
}

double fk_AppWindow::getFogLinearStart(void) const
{
	return _m->ref_scene->getFogLinearStart();
}

double fk_AppWindow::getFogLinearEnd(void) const
{
	return _m->ref_scene->getFogLinearEnd();
}

fk_Color fk_AppWindow::getFogColor(void) const
{
	return _m->ref_scene->getFogColor();
}

fk_Window * fk_AppWindow::GetDrawWin(void) const
{
	return _m->drawWin.get();
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
