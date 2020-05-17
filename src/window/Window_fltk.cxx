#define FK_DEF_SIZETYPE

#include <iostream>
#include <FK/Window.h>
#include <FK/Image.h>
#include <FL/Fl.H>
#include <FK/Error.H>
#include <FL/Fl_Multi_Browser.H>
#include <FL/x.H>
#include <FL/fl_ask.H>
#include <FL/fl_draw.H>

using namespace std;
using namespace FK;

unique_ptr<Fl_Window> fk_Window::_s_putWin;
Fl_Multi_Browser * fk_Window::_s_browser;
fk_PutStrMode fk_Window::_s_putStrMode = fk_PutStrMode::BROWSER;
unique_ptr<ofstream> fk_Window::_s_putStrOFS;
int fk_Window::_s_winNum = 0;
unique_ptr<Fl_Window> fk_Window::_s_error_win;
Fl_Multi_Browser * fk_Window::_s_err_browser;

fk_Window::Member::Member(int argX, int argY, int argW, int argH)
	: winOpenFlag(false),
	  GLWinXPosition(argX), GLWinYPosition(argY),
	  GLWinWSize(argW), GLWinHSize(argH),
	  lastKey(char(0)),
	  frameTime(0.0), prevTime(0.0), frameInterval(0.0),
	  skipCount(0), fps(0), stereoMode(false)
{
	return;
}

fk_Window::fk_Window(int argX, int argY, int argW, int argH, string argStr) :
	Fl_Gl_Window(argX, argY, argW, argH, &argStr[0]),
	_m(make_unique<Member>(argX, argY, argW, argH)),
	_m_engine(make_unique<fk_GraphicsEngine>(true))
{
	if(_s_winNum == 0) fontInit();
	_m_engine->Init(argW, argH);
	_s_winNum++;

	mode(FL_RGB |
		 FL_DOUBLE |
		 FL_ALPHA |
		 FL_STENCIL |
		 FL_DEPTH |
		 FL_OPENGL3 |
		 FL_MULTISAMPLE
		);

	ErrorInit();
	return;
}

fk_Window::~fk_Window()
{
	_m->snapBuffer.init();
	_s_winNum--;
	if(_s_winNum == 0) {
		_s_putWin.reset();
		_s_browser = nullptr;
	}
	return;
}

void fk_Window::drawScene(void)
{
	_m_engine->Draw();
}

void fk_Window::drawSceneLeft(void)
{
	//engine.StereoDrawMain(FK_STEREO_LEFT);
}

void fk_Window::drawSceneRight(void)
{
	//engine.StereoDrawMain(FK_STEREO_RIGHT);
}

void fk_Window::draw(void)
{
	if(!valid()) {
		preInit();
		_m_engine->OpenGLInit();
		postInit();
	}

	preDraw();

	for(auto it = preDrawList.begin(); it != preDrawList.end(); ++it) {
		get<1>(*it)();
	}
	
	if(_m->stereoMode == true) {
		/*
		engine.StereoDrawPrep(FK_STEREO_LEFT);
		preDrawLeft();
		drawSceneLeft();
		postDrawLeft();
		engine.StereoDrawPrep(FK_STEREO_RIGHT);
		preDrawRight();
		drawSceneRight();
		postDrawRight();
		*/
	} else {
		_m_engine->Draw();
	}
	postDraw();

	for(auto it = postDrawList.begin(); it != postDrawList.end(); ++it) {
		get<1>(*it)();
	}

	_m->winOpenFlag = true;

	return;
}

void fk_Window::setScene(fk_Scene *argScene)
{
	_m_engine->SetScene(argScene);
	return;
}

tuple<bool, fk_Vector> fk_Window::getProjectPosition(double argX, double argY, double argDist)
{
	return _m_engine->GetProjectPosition(argX, argY, argDist);
}

#ifndef FK_OLD_NONSUPPORT
bool fk_Window::getProjectPosition(double argX, double argY, double argDist, fk_Vector *retPos)
{
	bool status;
	tie(status, *retPos) = getProjectPosition(argX, argY, argDist);
	return status;
}
#endif

tuple<bool, fk_Vector> fk_Window::getProjectPosition(double argX, double argY, fk_Plane &argPlane)
{
	return _m_engine->GetProjectPosition(argX, argY, argPlane);
}

#ifndef FK_OLD_NONSUPPORT
bool fk_Window::getProjectPosition(double argX, double argY,
								   fk_Plane *argPlane, fk_Vector *retPos)
{
	bool status;
	tie(status, *retPos) = _m_engine->GetProjectPosition(argX, argY, *argPlane);
	return status;
}
#endif

tuple<bool, fk_Vector> fk_Window::getWindowPosition(fk_Vector &argPos)
{
	return _m_engine->GetWindowPosition(argPos);
}

#ifndef FK_OLD_NONSUPPORT
bool fk_Window::getWindowPosition(fk_Vector argPos, fk_Vector *retPos)
{
	bool status;
	tie(status, *retPos) = _m_engine->GetWindowPosition(argPos);
	return status;
}
#endif

// Stereo Mode
void fk_Window::setOGLStereoMode(bool argFlg)
{
	if(argFlg == true) {
		GLboolean val = GL_FALSE;
		Fl_Window *pWin = dynamic_cast<Fl_Window *>(GetInhParentWindow());
		if(pWin == nullptr) return;

		pWin->show();
		mode(mode() | FL_STEREO);
		Fl::check();

		glGetBooleanv(GL_STEREO, &val);
		if(val == GL_TRUE) {
			_m->stereoMode = true;
		} else {
			setOGLStereoMode(false);
		}
	} else {
		mode(mode() & (~FL_STEREO));
		Fl::check();
		_m->stereoMode = false;
	}
	return;
}

bool fk_Window::getOGLStereoMode(void)
{
	return _m->stereoMode;
}

bool fk_Window::snapImage(string argFName, fk_ImageType argType, fk_SnapProcMode argMode)
{
	redraw();
#ifdef WIN32
	if(argMode == fk_SnapProcMode::WIN32_GDI) {
		if(SnapImageGDI(&_m->snapBuffer) == false) return false;
	}
#else
	argMode = fk_SnapProcMode::FRONT;
#endif
	if(argMode != fk_SnapProcMode::WIN32_GDI) {
		if(_m_engine->SnapImage(&_m->snapBuffer, argMode) == false) return false;
	}

	switch(argType) {
	  case fk_ImageType::PNG:
		return _m->snapBuffer.writePNG(argFName, false);
	  case fk_ImageType::JPG:
		return _m->snapBuffer.writeJPG(argFName);
	  case fk_ImageType::BMP:
	  default:
		break;
	}
	return _m->snapBuffer.writeBMP(argFName);
}

bool fk_Window::snapImage(fk_Image *argImage, fk_SnapProcMode argMode)
{
	redraw();
#ifdef WIN32
	if(argMode == fk_SnapProcMode::WIN32_GDI) {
		return SnapImageGDI(argImage);
	}
#else
	argMode = fk_SnapProcMode::FRONT;
#endif
	return _m_engine->SnapImage(argImage, argMode);
}

#ifdef WIN32
bool fk_Window::SnapImageGDI(fk_Image *argImage)
{
	int iWidth = this->w(), iHeight = this->h();
	BITMAPINFO bi;
	RECT rect;
	unsigned char *buf = nullptr;

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
	_s_putStrMode = argMode;
}

fk_PutStrMode fk_Window::getPutStrMode(void)
{
	return _s_putStrMode;
}

bool fk_Window::setPutFile(const string &argFileName)
{
	if(_s_putStrOFS == nullptr) _s_putStrOFS = make_unique<ofstream>();
	if(_s_putStrOFS->is_open() == true) _s_putStrOFS->close();
	_s_putStrOFS->open(argFileName);
	if(_s_putStrOFS->fail()) return false;
	return true;
}

#ifndef FK_CLI_CODE
void fk_Window::printf(const char *argFormat, ...)
{
	va_list ap;
	vector<char> buffer(8192);

	va_start(ap, argFormat);
	vsnprintf(buffer.data(), 8191, argFormat, ap);
	va_end(ap);
	putString(string(buffer.data()));
	return;
}
#endif

void fk_Window::putString(const string &argStr)
{
	switch(_s_putStrMode) {
	  case fk_PutStrMode::CONSOLE:
		cout << argStr << endl;
		return;

	  case fk_PutStrMode::ERR_CONSOLE:
		cerr << argStr << endl;
		return;

	  case fk_PutStrMode::BROWSER:
		PutBrowser(argStr);
		return;

	  case fk_PutStrMode::FILE:
		if(_s_putStrOFS->is_open() == true) {
			*_s_putStrOFS << argStr << endl;
		}
		return;

	  case fk_PutStrMode::NONE:
	  default:
		break;
	}

	return;
}

void fk_Window::PutBrowser(const string &argStr)
{
	static const string space = "                ";

	if(_s_putWin == nullptr) {
		fontInit();
		_s_putWin = make_unique<Fl_Window>(320, 520, "FK PutStr Window");
		_s_browser = new Fl_Multi_Browser(10, 10, 300, 500);
		_s_putWin->size_range(320, 520);
		_s_putWin->resizable(_s_browser);
		_s_putWin->end();
		_s_putWin->show();
	}

	_st index = argStr.find('\n');
	string outStr = argStr.substr(0, index);
	while(index != string::npos) {
		string tmpStr = outStr + space;
		_s_browser->add(tmpStr.c_str());
		_st old = index+1;
		index = argStr.find('\n', old);
		if(index == string::npos) {
			outStr = argStr.substr(old, index);
		} else {
			outStr = argStr.substr(old, index-old);
		}
	}

	if(outStr.length() != 0) {
		string tmpStr = outStr + space;
		_s_browser->add(tmpStr.c_str());
	}

	_s_browser->bottomline(99999999);
	return;
}

void fk_Window::clearBrowser(void)
{
	if(_s_putWin != nullptr) _s_browser->clear();
	return;
}

void fk_Window::ErrorInit(void)
{
	Error::DataBase *db = Error::GetDB();
	Error::Browser *_browser = db->GetBrowser();

	if(_browser == nullptr) {
		fontInit();
		_browser = db->MakeBrowser();
		_browser->PutBrowser = [&](const string argStr) {
			static const string space = "                ";

			if(_s_error_win == nullptr) {
				_s_error_win = make_unique<Fl_Window>(320, 520, "FK Error Window");
				_s_browser = new Fl_Multi_Browser(10, 10, 300, 500);
				_s_error_win->size_range(320, 520);
				_s_error_win->resizable(_s_browser);
				_s_error_win->end();
				_s_error_win->show();
			}

			_st index = argStr.find('\n');
			string output = argStr.substr(0, index);
			while(index != string::npos) {
				string str = output + space;
				_s_browser->add(str.c_str());
				_st old = index+1;
				index = argStr.find('\n', old);
				if(index == string::npos) {
					output = argStr.substr(old, index);
				} else {
					output = argStr.substr(old, index-old);
				}
			}

			if(output.length() != 0) {
				string str = output + space;
				_s_browser->add(str.c_str());
			}

			_s_browser->bottomline(99999999);
		};

		_browser->PutAlert = [&](const string argStr) {
			fl_alert("%s", argStr.c_str());
			return;
		};
	}
}

fk_GraphicsEngine * fk_Window::GetEngine(void)
{
	return _m_engine.get();
}

void fk_Window::fontInit(void)
{
#ifdef _LINUX_
	Fl::set_font(0, "mono");
	Fl::set_font(1, "mono");
	fl_font(0, 36);
#endif
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
