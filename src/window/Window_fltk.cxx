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

#include <iostream>
#include <FK/Window.h>
#include <FK/Image.h>
#include <FL/Fl.H>
#include <FK/Error.H>
#include <FL/Fl_Multi_Browser.H>
#include <FL/x.H>
#include <FL/fl_ask.H>

using namespace std;
using namespace FK;

Fl_Window *			fk_Window::putWin = nullptr;
Fl_Multi_Browser *	fk_Window::browser = nullptr;
fk_PutStrMode		fk_Window::putStrMode = FK_PUTSTR_BROWSER;
ofstream			fk_Window::putStrOFS;
int					fk_Window::winNum = 0;
Fl_Window *			fk_Window::error_win = nullptr;
Fl_Multi_Browser *	fk_Window::err_browser = nullptr;

fk_Window::fk_Window(int argX, int argY, int argW, int argH, string argStr)
	: Fl_Gl_Window(argX, argY, argW, argH, &argStr[0])
{
	engine.Init(argW, argH);
	winOpenFlag = false;
	GLWinXPosition = argX;
	GLWinYPosition = argY;
	GLWinWSize = argW;
	GLWinHSize = argH;
	setFrameMode(FK_DEFAULT_FRAME);
	winNum++;
	mode(FL_RGB8 | FL_DOUBLE | FL_OPENGL3);

	stereoMode = false;

	setFPS(0);

	ErrorInit();
	return;
}

fk_Window::~fk_Window()
{
	snapBuffer.init();
	clearTextureMemory();
	winNum--;
	if(winNum == 0) {
		delete putWin;
		putWin = nullptr;
		browser = nullptr;
	}

	return;
}

void fk_Window::clearTextureMemory(void)
{
	engine.ClearTextureMemory();
	return;
}

unsigned long fk_Window::getUsingTextureMemory(void)
{	
	return engine.GetUsingTextureMemory();
}

void fk_Window::SetPickViewPort(int &argX, int &argY)
{
	int		mouseX = 0;
	int		mouseY = 0;

	while(getMouseStatus(FK_MOUSE1) == false &&
		  getMouseStatus(FK_MOUSE2) == false &&
		  getMouseStatus(FK_MOUSE3) == false) {
		if(Fl::check() == 0) break;
		if(winOpenStatus() == false) continue;
		getMousePosition(&mouseX, &mouseY);
	}
	argX = mouseX;
	argY = mouseY;
	return;
}

void fk_Window::drawScene(void)
{
	engine.Draw(false);
}

void fk_Window::drawSceneLeft(void)
{
	engine.StereoDrawMain(FK_STEREO_LEFT);
}

void fk_Window::drawSceneRight(void)
{
	engine.StereoDrawMain(FK_STEREO_RIGHT);
}

void fk_Window::draw(void)
{
	if(!valid()) {
		preInit();
		engine.OpenGLInit();
		postInit();
	}

	preDraw();

	for(auto it = preDrawList.begin(); it != preDrawList.end(); ++it) {
		get<1>(*it)();
	}
	
	if(stereoMode == true) {
		engine.StereoDrawPrep(FK_STEREO_LEFT);
		preDrawLeft();
		drawSceneLeft();
		postDrawLeft();
		engine.StereoDrawPrep(FK_STEREO_RIGHT);
		preDrawRight();
		drawSceneRight();
		postDrawRight();
	} else {
		engine.Draw(false);
	}
	postDraw();

	for(auto it = postDrawList.begin(); it != postDrawList.end(); ++it) {
		get<1>(*it)();
	}

	winOpenFlag = true;

	return;
}

void fk_Window::setScene(fk_Scene *argScene)
{
	engine.SetScene(argScene);
	return;
}

bool fk_Window::getProjectPosition(double argX, double argY,
								   double argDist, fk_Vector *retPos)
{
	return engine.GetProjectPosition(argX, argY, argDist, retPos);
}

bool fk_Window::getProjectPosition(double argX, double argY,
								   fk_Plane *argPlane, fk_Vector *retPos)
{
	return engine.GetProjectPosition(argX, argY, argPlane, retPos);
}

bool fk_Window::getWindowPosition(fk_Vector argPos, fk_Vector *retPos)
{
	return engine.GetWindowPosition(argPos, retPos);
}

void fk_Window::setOGLPointerMode(bool argFlg)
{
	engine.SetOGLPointerMode(argFlg);
	return;
}

bool fk_Window::getOGLPointerMode(void)
{
	return engine.GetOGLPointerMode();
}

void fk_Window::setOGLTextureBindMode(bool argFlg)
{
	engine.SetOGLTextureBindMode(argFlg);
	return;
}

bool fk_Window::getOGLTextureBindMode(void)
{
	return engine.GetOGLTextureBindMode();
}

// Stereo Mode
void fk_Window::setOGLStereoMode(bool argFlg)
{
	clearTextureMemory();
	if(argFlg == true) {
		GLboolean	val = GL_FALSE;
		Fl_Window	*pWin = dynamic_cast<Fl_Window *>(GetInhParentWindow());
		if(pWin == nullptr) return;

		pWin->show();
		mode(mode() | FL_STEREO);
		Fl::check();

		glGetBooleanv(GL_STEREO, &val);
		if(val == GL_TRUE) {
			stereoMode = true;
		} else {
			setOGLStereoMode(false);
		}
	} else {
		mode(mode() & (~FL_STEREO));
		Fl::check();
		stereoMode = false;
	}
	return;
}

bool fk_Window::getOGLStereoMode(void)
{
	return stereoMode;
}

bool fk_Window::snapImage(string argFName, fk_ImageType argType, fk_SnapProcMode argMode)
{
	redraw();
#ifdef WIN32
	if(argMode == FK_SNAP_WIN32_GDI) {
		if(SnapImageGDI(&snapBuffer) == false) return false;
	}
#else
	argMode = FK_SNAP_GL_FRONT;
#endif
	if(argMode != FK_SNAP_WIN32_GDI) {
		if(engine.SnapImage(&snapBuffer, argMode) == false) return false;
	}

	switch(argType) {
	  case FK_IMAGE_PNG:
		return snapBuffer.writePNG(argFName, false);
	  case FK_IMAGE_JPG:
		return snapBuffer.writeJPG(argFName);
	  case FK_IMAGE_BMP:
	  default:
		break;
	}
	return snapBuffer.writeBMP(argFName);
}

bool fk_Window::snapImage(fk_Image *argImage, fk_SnapProcMode argMode)
{
	redraw();
#ifdef WIN32
	if(argMode == FK_SNAP_WIN32_GDI) {
		return SnapImageGDI(argImage);
	}
#else
	argMode = FK_SNAP_GL_FRONT;
#endif
	return engine.SnapImage(argImage, argMode);
}

#ifdef WIN32
bool fk_Window::SnapImageGDI(fk_Image *argImage)
{
	int				iWidth = this->w(), iHeight = this->h();
	BITMAPINFO		bi;
	RECT			rect;
	unsigned char	*buf = nullptr;

	if(argImage == nullptr) return false;

	ZeroMemory(&bi, sizeof(bi));

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biWidth = iWidth;
	bi.bmiHeader.biHeight = iHeight;

	GetWindowRect(fl_xid(this), &rect);

	HDC hdcScreen = GetDC(nullptr);
	HDC _hdcShot = CreateCompatibleDC(hdcScreen);
	HBITMAP _bmpShot = CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS,
										(void **)(&buf), nullptr, 0);
	if(_bmpShot == 0) return false;
	if(buf == nullptr) return false;
	HBITMAP _bmpOld = (HBITMAP)SelectObject(_hdcShot, _bmpShot);
	BitBlt(_hdcShot, 0, 0, iWidth, iHeight, hdcScreen, rect.left, rect.top, SRCCOPY);
	ReleaseDC(nullptr, hdcScreen);

	argImage->newImage(iWidth, iHeight);

	for(int j = 0; j < iHeight; j++) {
		for(int k = 0; k < iWidth; k++) {
			argImage->setRGBA(k, j, buf[((iHeight-j-1)*iWidth + k)*4+2],
									buf[((iHeight-j-1)*iWidth + k)*4+1],
									buf[((iHeight-j-1)*iWidth + k)*4],
									buf[((iHeight-j-1)*iWidth + k)*4+3]);
		}
	}

	SelectObject(_hdcShot, _bmpOld);
	DeleteObject(_bmpShot);
	DeleteDC(_hdcShot);

	return true;
}
#endif

void fk_Window::setPutStrMode(const fk_PutStrMode argMode)
{
	putStrMode = argMode;
}

fk_PutStrMode fk_Window::getPutStrMode(void)
{
	return putStrMode;
}

bool fk_Window::setPutFile(const string &argFileName)
{
	if(putStrOFS.is_open() == true) putStrOFS.close();
	putStrOFS.open(argFileName);
	if(putStrOFS.fail()) return false;
	return true;
}

#ifndef FK_CLI_CODE
void fk_Window::printf(const char *argFormat, ...)
{
	va_list		ap;
	char		buffer[65536];

	va_start(ap, argFormat);
	vsnprintf(buffer, 65535, argFormat, ap);
	va_end(ap);
	putString(buffer);
	return;
}
#endif

void fk_Window::putString(const string &argStr)
{
	switch(putStrMode) {
	  case FK_PUTSTR_CONSOLE:
		cout << argStr << endl;
		return;

	  case FK_PUTSTR_ERR_CONSOLE:
		cerr << argStr << endl;
		return;

	  case FK_PUTSTR_BROWSER:
		PutBrowser(argStr);
		return;

	  case FK_PUTSTR_FILE:
		if(putStrOFS.is_open() == true) {
			putStrOFS << argStr << endl;
		}
		return;

	  case FK_PUTSTR_NONE:
	  default:
		break;
	}

	return;
}

void fk_Window::PutBrowser(const string &argStr)
{
	static const string		space = "			 ";
	string					outStr, tmpStr;
	string::size_type		index, old;

	if(putWin == nullptr) {
		putWin = new Fl_Window(320, 520, "FK PutStr Window");
		browser = new Fl_Multi_Browser(10, 10, 300, 500);
		putWin->size_range(320, 520);
		putWin->resizable(browser);
		putWin->end();
		putWin->show();
	}

	index = argStr.find('\n');
	outStr = argStr.substr(0, index);
	while(index != string::npos) {
		tmpStr = outStr + space;
		browser->add(tmpStr.c_str());
		old = index+1;
		index = argStr.find('\n', old);
		if(index == string::npos) {
			outStr = argStr.substr(old, index);
		} else {
			outStr = argStr.substr(old, index-old);
		}
	}

	if(outStr.length() != 0) {
		tmpStr = outStr + space;
		browser->add(tmpStr.c_str());
	}

	browser->bottomline(99999999);
	return;
}

void fk_Window::clearBrowser(void)
{
	if(putWin != nullptr) browser->clear();
	return;
}

void fk_Window::ErrorInit(void)
{
	fk_ErrorDataBase		*db = fk_GetErrorDB();

	if(db->errorBrowser == nullptr) {
		db->errorBrowser = new fk_ErrorBrowser();
		db->errorBrowser->PutBrowser = [&](const string argStr) {
			static const string		space = "			 ";
			string					output, str;
			string::size_type		index, old;

			if(error_win == nullptr) {
				error_win = new Fl_Window(320, 520, "FK Error Window");
				browser = new Fl_Multi_Browser(10, 10, 300, 500);
				error_win->size_range(320, 520);
				error_win->resizable(browser);
				error_win->end();
				error_win->show();
			}

			index = argStr.find('\n');
			output = argStr.substr(0, index);
			while(index != string::npos) {
				str = output + space;
				browser->add(str.c_str());
				old = index+1;
				index = argStr.find('\n', old);
				if(index == string::npos) {
					output = argStr.substr(old, index);
				} else {
					output = argStr.substr(old, index-old);
				}
			}

			if(output.length() != 0) {
				str = output + space;
				browser->add(str.c_str());
			}

			browser->bottomline(99999999);
		};

		db->errorBrowser->PutAlert = [&](const string argStr) {
			fl_alert("%s", argStr.c_str());
			return;
		};
	}
}
