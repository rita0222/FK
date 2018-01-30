﻿/****************************************************************************
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
#ifdef FK_D3D
#include "WindowEvent_fltk_D3D.cxx"
#else

#include <FK/Window.h>
#include <FL/Fl.H>
#include <FK/Error.H>

#ifdef _FREEBSD_
#include <sys/resource.h>
#endif

using namespace std;
using namespace FK;

void fk_Window::PushPrevStatus(void)
{
	for(auto ite1 = keyStatus.begin(); ite1 != keyStatus.end(); ++ite1) {
		ite1->second = getKeyStatus(ite1->first, false);
	}

	for(auto ite2 = specialKeyStatus.begin(); ite2 != specialKeyStatus.end(); ++ite2) {
		ite2->second = getSpecialKeyStatus(ite2->first, false);
	}

	for(auto ite3 = mouseStatus.begin(); ite3 != mouseStatus.end(); ++ite3) {
		ite3->second = getMouseStatus(ite3->first, false);
	}
	return;
}	


int fk_Window::drawWindow(bool argDrawMode)
{
	const unsigned long		ONE_FRAME_TIME = 25;
	Fl_Window				*pWin;

	pWin = static_cast<Fl_Window *>(this->parent());
	if(pWin == NULL) return 0;
	// rita_ext: ESC キー抑制
	/*
	if(Fl::event_inside(pWin) != 0) {
		if(Fl::event_key() == FL_Escape) return 0;
	}
	*/

	if(argDrawMode == true) {

		PushPrevStatus();

		if(frameMode != FK_DEFAULT_FRAME) {
			unsigned long time;

			frameTime = getNow();

			if((frameMode & FK_SKIP_FRAME) != FK_DEFAULT_FRAME) {
				time = prevTime + frameInterval * static_cast<unsigned long>(skipCount);
				if(time < frameTime) {
					skipCount++;
					return 1;
				} else {
					skipCount = 1;
				}
			}

			if((frameMode & FK_WAIT_FRAME) != FK_DEFAULT_FRAME) {
				time = prevTime + frameInterval;
				while(time > frameTime + ONE_FRAME_TIME) {
					Fl::wait(static_cast<double>(time - frameTime - ONE_FRAME_TIME)/1000.0);
					frameTime = getNow();
				}
			}
		}

		if(fps != 0) {
			fps_admin.timeRegular();
		}
		if(fps_admin.getDrawFlag() || fps == 0) {
			redraw();
		}

		if(frameMode != FK_DEFAULT_FRAME) {
			prevTime = frameTime;
		}
	}

	return 1;
}

bool fk_Window::winOpenStatus(void)
{
	return winOpenFlag;
}

void fk_Window::resizeWindow(int argX, int argY, int argW, int argH)
{
	GLWinXPosition = argX;
	GLWinYPosition = argY;
	GLWinWSize = argW;
	GLWinHSize = argH;
	engine.ResizeWindow(argW, argH);
	resize(argX, argY, argW, argH);

	return;
}

bool fk_Window::getKeyStatus(char argKey, bool argInsideFlag)
{
	if(argInsideFlag == true && IsInsideWindow() == false) {
		return false;
	}

#ifdef _MACOSX_
	if(argKey >= 'a' && argKey <= 'z') {
		int tmpKey = static_cast<int>(argKey) - ('a' - 'A');
		argKey = static_cast<char>(tmpKey);
	}
#endif

	if(Fl::get_key(argKey) != 0) {
		if(keyStatus.find(argKey) == keyStatus.end()) keyStatus[argKey] = false;
		return true;
	}
	return false;
}

bool fk_Window::getKeyStatus(char argKey, fk_SwitchStatus argStatus, bool argInsideFlag)
{
	bool		tmpStatus = getKeyStatus(argKey, argInsideFlag);

	if(argInsideFlag == true && IsInsideWindow() == false) {
		return false;
	}

	switch(argStatus) {
	  case FK_SW_RELEASE:
		return !(tmpStatus);
		
	  case FK_SW_UP:
		if(keyStatus[argKey] == true && tmpStatus == false) return true;
		return false;

	  case FK_SW_DOWN:
		if(keyStatus[argKey] == false && tmpStatus == true) return true;
		return false;

	  case FK_SW_PRESS:
		return tmpStatus;

	  default:
		break;
	}
	return false;
}
	
bool fk_Window::getSpecialKeyStatus(fk_SpecialKey argKey, bool argInsideFlag)
{
	if(specialKeyStatus.find(argKey) == specialKeyStatus.end()) {
		specialKeyStatus[argKey] = false;
	}

	if(argInsideFlag == true && IsInsideWindow() == false) {
		return false;
	}

	switch(argKey) {
	  case FK_SHIFT_R:
		if(Fl::get_key(FL_Shift_R) != 0) return true;
		else return false;
	  case FK_SHIFT_L:
		if(Fl::get_key(FL_Shift_L) != 0) return true;
		else return false;
	  case FK_CTRL_R:
		if(Fl::get_key(FL_Control_R) != 0) return true;
		else return false;
	  case FK_CTRL_L:
		if(Fl::get_key(FL_Control_L) != 0) return true;
		else return false;
	  case FK_ALT_R:
		if(Fl::get_key(FL_Alt_R) != 0) return true;
		else return false;
	  case FK_ALT_L:
		if(Fl::get_key(FL_Alt_L) != 0) return true;
		else return false;
	  case FK_ENTER:
		if(Fl::get_key(FL_Enter) != 0) return true;
		else return false;
	  case FK_BACKSPACE:
		if(Fl::get_key(FL_BackSpace) != 0) return true;
		else return false;
	  case FK_DELETE:
		if(Fl::get_key(FL_Delete) != 0) return true;
		else return false;
	  case FK_CAPS_LOCK:
		if(Fl::get_key(FL_Caps_Lock) != 0) return true;
		else return false;
	  case FK_TAB:
		if(Fl::get_key(FL_Tab) != 0) return true;
		else return false;
	  case FK_PAGE_UP:
		if(Fl::get_key(FL_Page_Up) != 0) return true;
		else return false;
	  case FK_PAGE_DOWN:
		if(Fl::get_key(FL_Page_Down) != 0) return true;
		else return false;
	  case FK_HOME:
		if(Fl::get_key(FL_Home) != 0) return true;
		else return false;
	  case FK_END:
		if(Fl::get_key(FL_End) != 0) return true;
		else return false;
	  case FK_INSERT:
		if(Fl::get_key(FL_Insert) != 0) return true;
		else return false;
	  case FK_LEFT:
		if(Fl::get_key(FL_Left) != 0) return true;
		else return false;
	  case FK_RIGHT:
		if(Fl::get_key(FL_Right) != 0) return true;
		else return false;
	  case FK_UP:
		if(Fl::get_key(FL_Up) != 0) return true;
		else return false;
	  case FK_DOWN:
		if(Fl::get_key(FL_Down) != 0) return true;
		else return false;
	  case FK_F1:
		if(Fl::get_key(FL_F+1) != 0) return true;
		else return false;
	  case FK_F2:
		if(Fl::get_key(FL_F+2) != 0) return true;
		else return false;
	  case FK_F3:
		if(Fl::get_key(FL_F+3) != 0) return true;
		else return false;
	  case FK_F4:
		if(Fl::get_key(FL_F+4) != 0) return true;
		else return false;
	  case FK_F5:
		if(Fl::get_key(FL_F+5) != 0) return true;
		else return false;
	  case FK_F6:
		if(Fl::get_key(FL_F+6) != 0) return true;
		else return false;
	  case FK_F7:
		if(Fl::get_key(FL_F+7) != 0) return true;
		else return false;
	  case FK_F8:
		if(Fl::get_key(FL_F+8) != 0) return true;
		else return false;
	  case FK_F9:
		if(Fl::get_key(FL_F+9) != 0) return true;
		else return false;
	  case FK_F10:
		if(Fl::get_key(FL_F+10) != 0) return true;
		else return false;
	  case FK_F11:
		if(Fl::get_key(FL_F+11) != 0) return true;
		else return false;
	  case FK_F12:
		if(Fl::get_key(FL_F+12) != 0) return true;
		else return false;
	  default:
		break;
	}

	return false;
}

bool fk_Window::getSpecialKeyStatus(fk_SpecialKey argKey, fk_SwitchStatus argStatus,
									bool argInsideFlag)
{
	bool		tmpStatus = getSpecialKeyStatus(argKey, argInsideFlag);

	if(argInsideFlag == true && IsInsideWindow() == false) {
		return false;
	}

	switch(argStatus) {
	  case FK_SW_RELEASE:
		return !(tmpStatus);
		
	  case FK_SW_UP:
		if(specialKeyStatus[argKey] == true && tmpStatus == false) return true;
		return false;

	  case FK_SW_DOWN:
		if(specialKeyStatus[argKey] == false && tmpStatus == true) return true;
		return false;

	  case FK_SW_PRESS:
		return tmpStatus;

	  default:
		break;
	}
	return false;
}


char fk_Window::getLastKey(void)
{
	Fl_Group	*mainWin = GetInhParentWindow();

	if(Fl::focus() == mainWin) {
		lastKey = char(Fl::event_key());
	}

	return lastKey;
}

void fk_Window::getMousePosition(int *argX, int *argY, bool argInsideFlag)
{
	if(argInsideFlag == true && IsInsideWindow() == false) {
		*argX = *argY = -1;
		return;
	}

	*argX = Fl::event_x() - GLWinXPosition;
	*argY = Fl::event_y() - GLWinYPosition;

	return;
}

Fl_Group * fk_Window::GetInhParentWindow(void)
{
	Fl_Group	*mainWin = this;

	while(mainWin->parent() != NULL) {
		mainWin = mainWin->parent();
	}

	return mainWin;
}

bool fk_Window::IsInsideWindow(void)
{
	Fl_Group		*mainWin;
	int				posX, posY;

	mainWin = GetInhParentWindow();

#ifdef WIN32
	Fl::get_mouse(posX, posY);
	posX -= mainWin->x();
	posY -= mainWin->y();
#else
	posX = Fl::event_x_root() - mainWin->x();
	posY = Fl::event_y_root() - mainWin->y();
#endif

	if(posX < GLWinXPosition || posX >= GLWinXPosition + GLWinWSize ||
	   posY < GLWinYPosition || posY >= GLWinYPosition + GLWinHSize) {
		return false;
	}

	return true;
}

unsigned long fk_Window::getNow(void)
{
	return fk_FrameController::getNow();
}

bool fk_Window::getMouseStatus(fk_MouseButton argButton, bool argInsideFlag)
{
	if(mouseStatus.find(argButton) == mouseStatus.end()) {
		mouseStatus[argButton] = false;
	}

	if(argInsideFlag == true && IsInsideWindow() == false) {
		return false;
	}

	switch(argButton) {

	  case FK_MOUSE1:
		if(Fl::event_state(FL_BUTTON1) != 0) return true;
		else return false;
	  case FK_MOUSE2:
		if(Fl::event_state(FL_BUTTON2) != 0) return true;
		else return false;
	  case FK_MOUSE3:
		if(Fl::event_state(FL_BUTTON3) != 0) return true;
		else return false;
	  default:
		break;
	}
	return false;
}

bool fk_Window::getMouseStatus(fk_MouseButton argButton,
							   fk_SwitchStatus argStatus, bool argInsideFlag)
{
	bool	tmpStatus = getMouseStatus(argButton, argInsideFlag);

	if(argInsideFlag == true && IsInsideWindow() == false) {
		return false;
	}

	switch(argStatus) {
	  case FK_SW_RELEASE:
		return !(tmpStatus);
		
	  case FK_SW_UP:
		if(mouseStatus[argButton] == true && tmpStatus == false) return true;
		return false;

	  case FK_SW_DOWN:
		if(mouseStatus[argButton] == false && tmpStatus == true) return true;
		return false;

	  case FK_SW_PRESS:
		return tmpStatus;

	  default:
		break;
	}
	return false;
}

int fk_Window::getMouseWheelStatus(void)
{
	int retVal = Fl::e_dy;
	Fl::e_dy = 0;

	return retVal;
}

void fk_Window::getPickModel(fk_PickData *argPickData, int argPixSize)
{
	GetPickData(true, argPickData, argPixSize, -1, -1);
	return;
}

void fk_Window::getPickModel(fk_PickData *argPickData, int argPixSize,
							 int argMouseX, int argMouseY)
{
	GetPickData(false, argPickData, argPixSize, argMouseX, argMouseY);
	return;
}

void fk_Window::GetPickData(bool argFlag, fk_PickData *argPickData,
							int argPixSize, int argMouseX, int argMouseY)
{
	// if(argPickData == (fk_PickData *)NULL) return;

	if(argFlag == true) {
		SetPickViewPort(argMouseX, argMouseY);
	}
	engine.GetPickData(argPickData, argPixSize, argMouseX, argMouseY);

	return;
}

void fk_Window::setFrameMode(fk_FrameMode argMode)
{
	frameMode = argMode;
	if(argMode != FK_DEFAULT_FRAME) prevTime = getNow();

	return;
}

fk_FrameMode fk_Window::getFrameMode(void)
{
	return frameMode;
}

void fk_Window::setFrameInterval(int argInterval)
{
	if(argInterval < 0) return;
	frameInterval = static_cast<unsigned long>(argInterval);
	return;
}

int fk_Window::getFrameInterval(void)
{
	return static_cast<int>(frameInterval);
}

int fk_Window::getSkipFrame(void)
{
	return (skipCount - 1);
}

void fk_Window::setFPS(int argFPS)
{
	if(argFPS == 0) {
		fps = 0;
		fps_admin.setFrameSkipMode(false);
	} else {
		fps = argFPS;
		fps_admin.setFrameSkipMode(true);
		fps_admin.setFPS((unsigned long)(argFPS));
	}
}


#endif // FK_D3D
