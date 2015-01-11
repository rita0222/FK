/****************************************************************************
 *
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2014, Fine Kernel Project, All rights reserved.
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
#include <FK/D3D/Window.h>
#include <FK/Image.h>
#include <FL/Fl.h>
#include <FK/Error.h>
#include <FL/Fl_Multi_Browser.h>
#include <FL/x.h>

using namespace std;

Fl_Window *			fk_Window::putWin = NULL;
Fl_Multi_Browser *	fk_Window::browser = NULL;
fk_PutStrMode		fk_Window::putStrMode = FK_PUTSTR_BROWSER;
FILE *				fk_Window::putStrFP = NULL;
int					fk_Window::winNum = 0;

char fk_Window::valid(void)
{
	if(bValid == 0) {
		bValid = 1;
		return 0;
	}

	return bValid;
}

fk_Window::fk_Window(int argX, int argY, int argW, int argH, string argStr)
	: Fl_Window(argX, argY, argW, argH, &argStr[0]),
	  fk_BaseObject(FK_WINDOW)
{
	// これを小ウィンドウ化されると困るので封印
	end();

	engine.Init(argW, argH);
	bValid = 0;
	winOpenFlag = false;
	GLWinXPosition = argX;
	GLWinYPosition = argY;
	GLWinWSize = argW;
	GLWinHSize = argH;
	setFrameMode(FK_DEFAULT_FRAME);
	winNum++;

	return;
}

fk_Window::~fk_Window()
{
	snapBuffer.init();
	clearTextureMemory();
	winNum--;
	if(winNum == 0) {
		delete putWin;
		putWin = NULL;
		browser = NULL;
		if(putStrFP != NULL) fclose(putStrFP);
	}

	return;
}

bool fk_Window::createD3D(void)
{
	if(fl_xid(this) != NULL) {
		engine.InitD3D(fl_xid(this));

		return true;
	}

	return false;
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

void fk_Window::SetPickViewPort(bool argFlag, int argPixSize,
								int &argX, int &argY)
{
	int		mouseX, mouseY;

	// glViewport(0, 0, GLWinWSize, GLWinHSize);

	if(argFlag == true) {
		while(getMouseStatus(FK_MOUSE1) == false &&
			  getMouseStatus(FK_MOUSE2) == false &&
			  getMouseStatus(FK_MOUSE3) == false) {
			if(Fl::check() == 0) break;
			if(winOpenStatus() == false) continue;
			getMousePosition(&mouseX, &mouseY);
		}
		argX = mouseX;
		argY = mouseY;
	}
	/*
	else {
		mouseX = argX;
		mouseY = argY;
	}
	*/

	// engine.SetPickViewPort(argPixSize, mouseX, mouseY);

	return;
}

void fk_Window::show(void)
{
	createD3D();
	Fl_Window::show();

	return;
}

void fk_Window::draw(void)
{
	if(!valid()) {
		if(!createD3D()) return;
		preInit();
		engine.D3DStateInit();
		postInit();
	}

	preDraw();
	engine.Draw(false);
	postDraw();

	engine.Flip();
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
	// engine.SetOGLPointerMode(argFlg);
	return;
}

bool fk_Window::getOGLPointerMode(void)
{
	// return engine.GetOGLPointerMode();
	return false;
}

void fk_Window::setOGLTextureBindMode(bool argFlg)
{
	// engine.SetOGLTextureBindMode(argFlg);
	return;
}

bool fk_Window::getOGLTextureBindMode(void)
{
	// return engine.GetOGLTextureBindMode();
	return false;
}

bool fk_Window::snapImage(string argFName, fk_ImageType argType, fk_SnapProcMode argMode)
{
	redraw();
	if(argMode == FK_SNAP_WIN32_GDI) {
		if(SnapImageGDI(&snapBuffer) == false) return false;
	} else {
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
	if(argMode == FK_SNAP_WIN32_GDI) {
		return SnapImageGDI(argImage);
	}
	return engine.SnapImage(argImage, argMode);
}

bool fk_Window::SnapImageGDI(fk_Image *argImage)
{
	int				iWidth = this->w(), iHeight = this->h();
	BITMAPINFO		bi;
	RECT			rect;
	unsigned char	*buf = NULL;

	if(argImage == (fk_Image *)NULL) return false;

	ZeroMemory(&bi, sizeof(bi));

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biWidth = iWidth;
	bi.bmiHeader.biHeight = iHeight;

	GetWindowRect(fl_xid(this), &rect);

	HDC hdcScreen = GetDC(NULL);
	HDC _hdcShot = CreateCompatibleDC(hdcScreen);
	HBITMAP _bmpShot = CreateDIBSection(NULL, &bi, DIB_RGB_COLORS,
										(void **)(&buf), NULL, 0);
	HBITMAP _bmpOld = (HBITMAP)SelectObject(_hdcShot, _bmpShot);
	BitBlt(_hdcShot, 0, 0, iWidth, iHeight, hdcScreen, rect.left, rect.top, SRCCOPY);
	ReleaseDC(NULL, hdcScreen);

	argImage->newImage(iWidth, iHeight);

	for(int j = 0; j < iHeight; j++) {
		for(int i = 0; i < iWidth; i++) {
			argImage->setRGBA(i, j,  buf[((iHeight-j-1)*iWidth + i)*4+2],
									buf[((iHeight-j-1)*iWidth + i)*4+1],
									buf[((iHeight-j-1)*iWidth + i)*4],
									buf[((iHeight-j-1)*iWidth + i)*4+3]);
		}
	}

	SelectObject(_hdcShot, _bmpOld);
	DeleteObject(_bmpShot);
	DeleteDC(_hdcShot);

	return true;
}

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
	if(putStrFP != NULL) {
		fclose(putStrFP);
	}

	if((putStrFP = fopen(argFileName.c_str(), "a")) == NULL) return false;
	return true;
}

void fk_Window::printf(const char *argFormat, ...)
{
	va_list		ap;
	char		buffer[1024];

	va_start(ap, argFormat);
	vsnprintf(buffer, 1023, argFormat, ap);
	va_end(ap);
	putString(buffer);
	return;
}

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
		if(putStrFP != NULL) {
			fprintf(putStrFP, "%s\n", argStr.c_str());
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

	if(putWin == NULL) {
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
	return;
}

void fk_Window::clearBrowser(void)
{
	if(putWin != NULL) browser->clear();
	return;
}
