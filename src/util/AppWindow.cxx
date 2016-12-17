/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
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

#define _APPWINDOWSRC_

#include <FK/AppWindow.h>
#ifndef _MINGW_
#include <FL/x.H>
#endif
#include <FK/System.h>
#include <FK/MatExample.h>

#ifdef FK_CLI_CODE
class InnerWindow : public ::fk_Window
{
private:
	void(*pPreInit)();
	void(*pPostInit)();
	void(*pPreDraw)();
	void(*pPostDraw)();
	void(*pPreDrawLeft)();
	void(*pPostDrawLeft)();
	void(*pPreDrawRight)();
	void(*pPostDrawRight)();

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
		pPreInit = (void(__cdecl *)(void))argCallbacks[0];
		pPostInit = (void(__cdecl *)(void))argCallbacks[1];
		pPreDraw = (void(__cdecl *)(void))argCallbacks[2];
		pPostDraw = (void(__cdecl *)(void))argCallbacks[3];
		pPreDrawLeft = (void(__cdecl *)(void))argCallbacks[4];
		pPostDrawLeft = (void(__cdecl *)(void))argCallbacks[5];
		pPreDrawRight = (void(__cdecl *)(void))argCallbacks[6];
		pPostDrawRight = (void(__cdecl *)(void))argCallbacks[7];
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

const static fk_SwitchStatus stArray[4] = {
	FK_SW_UP,
	FK_SW_DOWN,
	FK_SW_RELEASE
};

void fk_AppWindow::PushPrevStatus(void)
{
	int	i;

	for(i = 0; i < inputCount; ++i) {
		prevInput[i] = nowInput[i];
	}

	return;
}

// スクリーンモードのハンドリング処理
void fk_AppWindow::ToggleScreen(void)
{
	// ALT+ENTERでフルスクリーンとウィンドウモードを切り替え
	if(getSpecialKeyStatus(FK_ALT_L) >= FK_SW_DOWN
	|| getSpecialKeyStatus(FK_ALT_R) >= FK_SW_DOWN) {
		if(getSpecialKeyStatus(FK_ENTER) == FK_SW_DOWN) {
			if(fsc.isFullscreen() == true) {
				fsc.changeToWindow();
			} else {
				fsc.changeToFullscreen();
			}
		}
	}
	// ウィンドウのフォーカスが外れたらウィンドウモードに戻す
	if(Fl::focus() != mainWin) {
		toWindow();
	}

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

	mainWin = new Fl_Window(512, 512, "FKAPP Window");
#ifdef FK_CLI_CODE
#ifdef _WIN64
	drawWin = new InnerWindow(argCallbacks, 0, 0, 512, 512);
#else
	drawWin = new InnerWindow(argCallbacks, 0, 0, 512, 512);
#endif // _WIN64
#else
	drawWin = new fk_Window(0, 0, 512, 512);
#endif // FK_CLI_CODE
	mainWin->end();

	fk_Material::initDefault();

	light.setShape(&lightShape);
	light.setMaterial(White);
	light.getMaterial()->setAmbDiff(1.0, 1.0, 1.0);
	light.glMoveTo(0.0, 0.0, 0.0);
	light.glFocus(-1.0, -1.0, -1.0);

	scene.setBlendStatus(true);
	scene.entryCamera(&camera);
	scene.entryModel(&light);

	drawWin->setScene(&scene);

	setFPS(60);

	camera.glMoveTo(0.0, 0.0, 100.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);

	tb = new fk_TrackBall(drawWin, &camera);
	tbFlag = false;
	childMode = false;
	ref_child = NULL;

	ref_camera = &camera;
	ref_scene = &scene;

	inputCount = 0;

	PushPrevStatus();

	return;
}

fk_AppWindow::fk_AppWindow(fk_AppWindow &argParent)
{
	mainWin = argParent.mainWin;
	mainWin->begin();
	argParent.drawWin->resizeWindow(0, 0, mainWin->w(), mainWin->h()/2);
	drawWin = new fk_Window(0, mainWin->h()/2, mainWin->w(), mainWin->h()/2);
	mainWin->end();

	fk_Material::initDefault();

	light.setShape(&lightShape);
	light.setMaterial(White);
	light.getMaterial()->setAmbDiff(1.0, 1.0, 1.0);
	light.glMoveTo(0.0, 0.0, 0.0);
	light.glFocus(-1.0, -1.0, -1.0);

	scene.setBlendStatus(true);
	scene.entryCamera(&camera);
	scene.entryModel(&light);

	drawWin->setScene(&scene);

	setFPS(60);

	camera.glMoveTo(0.0, 0.0, 100.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);

	tb = new fk_TrackBall(drawWin, &camera);
	tbFlag = false;
	childMode = true;
	ref_child = NULL;
	argParent.ref_child = this;

	ref_camera = &camera;
	ref_scene = &scene;

	inputCount = 0;

	PushPrevStatus();

	return;
}

fk_AppWindow::~fk_AppWindow(void)
{
	input.uninit();
	drawWin->hide();
	mainWin->hide();

	delete tb;
	delete drawWin;
	if(!childMode) delete mainWin;
}

void fk_AppWindow::setWindowName(const std::string &name)
{
	mainWin->label(fk_Code::utf8(name.c_str(), FK_STR_SJIS));
	return;
}

void fk_AppWindow::setSize(int argW, int argH)
{
	mainWin->resize(mainWin->x(), mainWin->y(), argW, argH);
	if(!childMode) drawWin->resizeWindow(0, 0, argW, argH);
}

void fk_AppWindow::setInnerSize(int argX, int argY, int argW, int argH)
{
	drawWin->resizeWindow(argX, argY, argW, argH);
}

void fk_AppWindow::setBGColor(double r, double g, double b)
{
	ref_scene->setBGColor((float)r, (float)g, (float)b);
}

void fk_AppWindow::setBGColor(const fk_Color &argColor)
{
	ref_scene->setBGColor(argColor);
}

void fk_AppWindow::setFPS(int argFPS)
{
#if defined(_MACOSX_) || defined(_MINGW_)
	argFPS = 0;
#endif //_MACOSX_ || _MINGW_

	if(argFPS == 0) {
		fps = 0;
		fps_admin.setFrameSkipMode(false);
	} else {
		fps = argFPS;
		fps_admin.setFrameSkipMode(true);
		fps_admin.setFPS((unsigned long)(argFPS));
	}
}

void fk_AppWindow::setTrackBallMode(bool mode)
{
	tbFlag = mode;
}

void fk_AppWindow::showGuide(fk_GuideMode mode)
{
	guide.entryScene(ref_scene, mode);
}

void fk_AppWindow::hideGuide(void)
{
	guide.removeScene(ref_scene);
}

void fk_AppWindow::setCameraPos(double x, double y, double z)
{
	ref_camera->glMoveTo(x, y, z);
}

void fk_AppWindow::setCameraPos(const fk_Vector &argPos)
{
	ref_camera->glMoveTo(argPos);
}

void fk_AppWindow::setCameraFocus(double x, double y, double z)
{
	ref_camera->glFocus(x, y, z);
	tb->setLookTo(fk_Vector(x, y, z));
}

void fk_AppWindow::setCameraFocus(const fk_Vector &argPos)
{
	ref_camera->glFocus(argPos);
	tb->setLookTo(argPos);
}

void fk_AppWindow::setCameraModel(fk_Model &model)
{
	ref_camera = &model;
	tb->setCamera(&model);
	ref_scene->entryCamera(ref_camera);
}

void fk_AppWindow::setCameraModel(fk_Model *argModel)
{
	ref_camera = argModel;
	tb->setCamera(argModel);
	ref_scene->entryCamera(ref_camera);
}

fk_Model * fk_AppWindow::getCameraModel(void)
{
	return ref_camera;
}

void fk_AppWindow::setCameraDefault(void)
{
	setCameraModel(camera);
}

void fk_AppWindow::setScene(fk_Scene &argScene, bool argLightAndCamera)
{
	this->setScene(&argScene, argLightAndCamera);
}

void fk_AppWindow::setScene(fk_Scene *argScene, bool argLightAndCamera)
{
	ref_scene = argScene;
	ref_camera = const_cast<fk_Model *>(ref_scene->getCamera());
	ref_scene->setBlendStatus(true);
	drawWin->setScene(ref_scene);
	if(argLightAndCamera) {
		ref_scene->entryCamera(&camera);
		ref_scene->entryModel(&light);
	}
}

fk_Scene * fk_AppWindow::getScene(void)
{
	return ref_scene;
}

void fk_AppWindow::setSceneDefault(void)
{
	setScene(scene, true);
}

void fk_AppWindow::entry(fk_Model &model)
{
	ref_scene->entryModel(&model);
}

void fk_AppWindow::remove(fk_Model &model)
{
	ref_scene->removeModel(&model);
}

void fk_AppWindow::entry(fk_Model &model, fk_GuideObject &argGuide)
{
	argGuide.setParent(&model);
	argGuide.entryScene(ref_scene);
	ref_scene->entryModel(&model);
}

void fk_AppWindow::remove(fk_Model &model, fk_GuideObject &argGuide)
{
	argGuide.setParent(NULL);
	argGuide.removeScene(ref_scene);
	ref_scene->removeModel(&model);
}

void fk_AppWindow::entry(fk_SpriteModel &model)
{
	model.MakePixelBase(fk_Dimension(drawWin->w(), drawWin->h()), ref_scene);
	ref_scene->entryOverlayModel(&model);
}

void fk_AppWindow::remove(fk_SpriteModel &model)
{
	ref_scene->removeOverlayModel(&model);
}

void fk_AppWindow::entry(fk_Performer &chara)
{
	chara.entryScene(ref_scene);
}

void fk_AppWindow::remove(fk_Performer &chara)
{
	chara.removeScene(ref_scene);
}

void fk_AppWindow::entry(fk_Model *model)
{
	ref_scene->entryModel(model);
}

void fk_AppWindow::remove(fk_Model *model)
{
	ref_scene->removeModel(model);
}

void fk_AppWindow::entry(fk_Model *model, fk_GuideObject *argGuide)
{
	argGuide->setParent(model);
	argGuide->entryScene(ref_scene);
	ref_scene->entryModel(model);
}

void fk_AppWindow::remove(fk_Model *model, fk_GuideObject *argGuide)
{
	argGuide->setParent(NULL);
	argGuide->removeScene(ref_scene);
	ref_scene->removeModel(model);
}

void fk_AppWindow::entry(fk_SpriteModel *model)
{
	model->MakePixelBase(fk_Dimension(drawWin->w(), drawWin->h()), ref_scene);
	ref_scene->entryOverlayModel(model);
}

void fk_AppWindow::remove(fk_SpriteModel *model)
{
	ref_scene->removeOverlayModel(model);
}

void fk_AppWindow::entry(fk_Performer *chara)
{
	chara->entryScene(ref_scene);
}

void fk_AppWindow::remove(fk_Performer *chara)
{
	chara->removeScene(ref_scene);
}

void fk_AppWindow::clearModel(bool argLightAndCamera)
{
	ref_scene->clearDisplay();
	if(argLightAndCamera) {
		ref_scene->entryCamera(&camera);
		ref_scene->entryModel(&light);
		ref_camera = &camera;
		tb->setCamera(&camera);
	}
}

void fk_AppWindow::open(void)
{
	mainWin->show();
	drawWin->show();

#if defined(WIN32) && !defined(_MINGW_)
	if(S_OK == input.init(fl_display, fl_xid(mainWin))) {
		inputCount = input.getJoyCount();
		input.update();
		for(int i = 0; i < inputCount; ++i) {
			prevInput[i] = nowInput[i] = input.getInputStatus(i);
		}
	}
#endif

	fsc.init(mainWin, drawWin);

	return;
}

void fk_AppWindow::close(void)
{
	drawWin->hide();
	if(!childMode) {
		toWindow();
		mainWin->hide();
	}

	return;
}

bool fk_AppWindow::update(bool argForceDraw)
{
	if(childMode) return false;

	PushPrevStatus();
	if(fps != 0) fps_admin.timeRegular();

	if(mainWin->visible() == 0) {
		if(Fl::wait() == 0) {
			return false;
		} else {
			return true;
		}
	}

	if(fps_admin.getDrawFlag() || fps == 0 || argForceDraw) {
		drawWin->drawWindow();
		if(ref_child != NULL) ref_child->drawWin->drawWindow();
	}
	if(Fl::check() == 0) return false;

	ToggleScreen();

	if(inputCount != 0) {
		input.update();
		for(int i = 0; i < inputCount; ++i) {
			nowInput[i] = input.getInputStatus(i);
		}
	}

	if(tbFlag) tb->update();
	if(ref_child != NULL) {
		ref_child->tb->update();
	}

	return true;
}

fk_SwitchStatus GetSwitchStatus(bool now, bool pre)
{
	switch((int)now*2 + (int)pre) {
	case 0:
		return FK_SW_RELEASE;
	case 1:
		return FK_SW_UP;
	case 2:
		return FK_SW_DOWN;
	case 3:
		return FK_SW_PRESS;
	default:
		return FK_SW_RELEASE;
	}
}

bool fk_AppWindow::getKeyStatus(char argKey, fk_SwitchStatus argStatus, bool argInsideFlg)
{
	return drawWin->getKeyStatus(argKey, argStatus, argInsideFlg);
}

fk_SwitchStatus fk_AppWindow::getKeyStatus(char argKey)
{
	//return GetSwitchStatus(drawWin->getKeyStatus(argKey, false), prevKeySt[(int)argKey]);

	for(int i = 0; i < 3; ++i) {
		if(getKeyStatus(argKey, stArray[i], false) == true) return stArray[i];
	}
	return FK_SW_PRESS;
}

bool fk_AppWindow::getSpecialKeyStatus(fk_SpecialKey argKey,
									   fk_SwitchStatus argStatus, bool argInsideFlg)
{
	return drawWin->getSpecialKeyStatus(argKey, argStatus, argInsideFlg);
}

fk_SwitchStatus fk_AppWindow::getSpecialKeyStatus(fk_SpecialKey argKey)
{
	//return GetSwitchStatus(drawWin->getSpecialKeyStatus(argKey, false), prevSPKeySt[(int)argKey]);

	for(int i = 0; i < 3; ++i) {
		if(getSpecialKeyStatus(argKey, stArray[i], false) == true) return stArray[i];
	}
	return FK_SW_PRESS;
}

bool fk_AppWindow::getMouseStatus(fk_MouseButton argButton,
								  fk_SwitchStatus argStatus, bool argInsideFlg)
{
	return drawWin->getMouseStatus(argButton, argStatus, argInsideFlg);
}

fk_SwitchStatus fk_AppWindow::getMouseStatus(fk_MouseButton argButton)
{
	//return GetSwitchStatus(drawWin->getMouseStatus(argButton, false), prevMouseSt[(int)argButton]);

	for(int i = 0; i < 3; ++i) {
		if(getMouseStatus(argButton, stArray[i], false) == true) return stArray[i];
	}
	return FK_SW_PRESS;
}

fk_Vector fk_AppWindow::getMousePosition(void)
{
	int			x, y;
	fk_Vector	retPos;

	drawWin->getMousePosition(&x, &y, false);

	retPos.x = (double)x;
	retPos.y = (double)y;
	retPos.z = 0.0;

	return retPos;
}

int fk_AppWindow::getPadCount(void)
{
	return inputCount;
}

fk_SwitchStatus fk_AppWindow::getPadButtonStatus(int padID, int buttonID)
{
	//	if(padID > inputCount || buttonID > 32+4) return FK_SW_RELEASE;
	if(padID > inputCount) return FK_SW_RELEASE;

	switch(buttonID) {
	case FK_PAD_UP:
		return GetSwitchStatus(nowInput[padID].up, prevInput[padID].up);
	case FK_PAD_DOWN:
		return GetSwitchStatus(nowInput[padID].down, prevInput[padID].down);
	case FK_PAD_LEFT:
		return GetSwitchStatus(nowInput[padID].left, prevInput[padID].left);
	case FK_PAD_RIGHT:
		return GetSwitchStatus(nowInput[padID].right, prevInput[padID].right);
	default:
	  break;	
	}
	if(buttonID > 32) return FK_SW_RELEASE;
	return GetSwitchStatus(nowInput[padID].button[buttonID],
						   prevInput[padID].button[buttonID]);
}

fk_Vector fk_AppWindow::getPadDirection(int padID, int axisID)
{
	fk_Vector	retVec;
	if(padID > inputCount || axisID >= 3) return retVec;

	retVec.x = nowInput[padID].x[axisID] * 0.001;
	retVec.y = nowInput[padID].y[axisID] * 0.001;

	return retVec;
}

fk_Input * fk_AppWindow::getPadManager(void)
{
	return &input;
}

bool fk_AppWindow::isModelPicked(fk_Model *model, int pixel, int mouseX, int mouseY)
{
	static fk_PickData	pick;
	const bool orgMode = model->getPickMode();

	if(mouseX == -1 || mouseY == -1) {
		drawWin->getMousePosition(&mouseX, &mouseY);
	}
	if(mouseX == -1 || mouseY == -1) return false;

	model->setPickMode(true);
	drawWin->getPickModel(&pick, pixel, mouseX, mouseY);
	model->setPickMode(orgMode);

	for(int i = 0; i < pick.getSize(); i++) {
		if(pick.getModel(i) == model) return true;
	}

	return false;
}

bool fk_AppWindow::isModelPicked(fk_Model &model, int pixel, int mouseX, int mouseY)
{
	return this->isModelPicked(&model, pixel, mouseX, mouseY);
}

void fk_AppWindow::setGuideAxisWidth(double width)
{
	guide.setAxisWidth(width);
}

void fk_AppWindow::setGuideGridWidth(double width)
{
	guide.setGridWidth(width);
}

void fk_AppWindow::setGuideScale(double scale)
{
	guide.setScale(scale);
}

void fk_AppWindow::setGuideNum(int num)
{
	guide.setNum(num);
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
		SetCursorPos(mainWin->x()+mainWin->w()/2, mainWin->y()+mainWin->h()/2);
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
	diffX = nowX - prevX;
	diffY = nowY - prevY;
	camera->glRotateWithVec(camera->getPosition(), fk_Y, -diffX*spinX);
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
	if(!fsc.isFullscreen()) fsc.changeToFullscreen();
}

void fk_AppWindow::toWindow(void)
{
	if(fsc.isFullscreen()) fsc.changeToWindow();
}

void fk_AppWindow::SetFinalizeMode(void)
{
	camera.SetTreeDelMode(false);
	light.SetTreeDelMode(false);
}

bool fk_AppWindow::getProjectPosition(double argX, double argY,
									  fk_Plane *argPlane, fk_Vector *argPos)
{
	return drawWin->getProjectPosition(argX, argY, argPlane, argPos);
}
	
bool fk_AppWindow::getProjectPosition(double argX, double argY,
									  double argDist, fk_Vector *argPos)
{
	return drawWin->getProjectPosition(argX, argY, argDist, argPos);
}

bool fk_AppWindow::getWindowPosition(fk_Vector argPos_3D, fk_Vector *argPos_2D)
{
	return drawWin->getWindowPosition(argPos_3D, argPos_2D);
}
