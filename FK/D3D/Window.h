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
// fk_Window for Direct3D

#ifndef __FK_WINDOW_HEADER__
#define __FK_WINDOW_HEADER__

#include <stdarg.h>

// for Graphics Header.
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Multi_Browser.h>

// for FK Header.
#include <FK/Engine.h>

// for Graphics Routine
typedef unsigned int fk_FrameMode;

const fk_FrameMode FK_DEFAULT_FRAME			= 0x0000;
const fk_FrameMode FK_WAIT_FRAME			= 0x0001;
const fk_FrameMode FK_SKIP_FRAME			= 0x0002;

enum fk_SpecialKey {
	FK_SHIFT_R, FK_SHIFT_L,
	FK_CTRL_R, FK_CTRL_L,
	FK_ALT_R, FK_ALT_L,
	FK_ENTER, FK_BACKSPACE,
	FK_DELETE, FK_CAPS_LOCK, FK_TAB,
	FK_PAGE_UP, FK_PAGE_DOWN,
	FK_HOME, FK_END, FK_INSERT,
	FK_LEFT, FK_RIGHT, FK_UP, FK_DOWN,
	FK_F1, FK_F2, FK_F3, FK_F4, FK_F5, FK_F6,
	FK_F7, FK_F8, FK_F9, FK_F10, FK_F11, FK_F12
};

enum fk_MouseButton {
	FK_MOUSE1, FK_MOUSE2, FK_MOUSE3
};

enum fk_PutStrMode {
	FK_PUTSTR_NONE,
	FK_PUTSTR_CONSOLE,
	FK_PUTSTR_ERR_CONSOLE,
	FK_PUTSTR_BROWSER,
	FK_PUTSTR_FILE
};

class fk_Window : public Fl_Window, public fk_BaseObject {

 private:

	fk_GraphicsEngine		engine;

	fk_Image				snapBuffer;

	char					bValid;

	bool					winOpenFlag;
	int						GLWinWSize;
	int						GLWinHSize;
	int						GLWinXPosition;
	int						GLWinYPosition;
	char					lastKey;

	fk_FrameMode			frameMode;
	unsigned long			frameTime, prevTime;
	unsigned long			frameInterval;
	int						skipCount;

	static Fl_Window		*putWin;
	static Fl_Multi_Browser	*browser;
	static fk_PutStrMode	putStrMode;
	static FILE				*putStrFP;
	static int				winNum;

	void				SetPickViewPort(bool, int, int &, int &);
	unsigned long		GetNow(void);
	bool				IsInsideWindow(void);
	Fl_Group *			GetInhParentWindow(void);
	void				GetPickData(bool, fk_PickData *, int, int, int);

	void				draw();	// もしかしてredrawの前にフックしてるだけ？

	static void			PutBrowser(const std::string &);

	bool				SnapImageGDI(fk_Image *);

 public:
	 fk_Window(int = 0, int = 0, int = 300, int = 300, std::string = "FK Window");
	~fk_Window();

	static unsigned long	getNow(void);

	bool				createD3D(void);
	void				show(void);
	char				valid(void);

	int					drawWindow(bool = true);

	void				setScene(fk_Scene *);
	bool				winOpenStatus(void);
	void				resizeWindow(int, int, int, int);

	bool				getKeyStatus(char, bool = true);
	bool				getSpecialKeyStatus(fk_SpecialKey, bool = true);
	char				getLastKey(void);
	void				getMousePosition(int *, int *, bool = true);
	bool				getMouseStatus(fk_MouseButton, bool = true);
	int					getMouseWheelStatus(void);

	void				setFrameMode(fk_FrameMode);
	fk_FrameMode		getFrameMode(void);
	void				setFrameInterval(int);
	int					getFrameInterval(void);
	int					getSkipFrame(void);
	bool				getProjectPosition(double, double,
										   fk_Plane *, fk_Vector *);
	bool				getProjectPosition(double, double,
										   double, fk_Vector *);
	bool				getWindowPosition(fk_Vector, fk_Vector *);

	void				setOGLPointerMode(bool);
	bool				getOGLPointerMode(void);

	void				setOGLTextureBindMode(bool);
	bool				getOGLTextureBindMode(void);

	bool				snapImage(std::string, fk_ImageType = FK_IMAGE_BMP, fk_SnapProcMode = FK_SNAP_D3D_WINDOW);
	bool				snapImage(fk_Image *, fk_SnapProcMode = FK_SNAP_D3D_WINDOW);

	void				clearTextureMemory(void);
	unsigned long		getUsingTextureMemory(void);
	
	void				getPickModel(fk_PickData *, int);
	void				getPickModel(fk_PickData *, int, int, int);

	virtual void		preInit(void) {}
	virtual void		postInit(void) {}
	virtual void		preDraw(void) {}
	virtual void		postDraw(void) {}

	static void				setPutStrMode(const fk_PutStrMode);
	static fk_PutStrMode	getPutStrMode(void);
	static bool				setPutFile(const std::string &);
	static void				putString(const std::string &);
	static void				printf(const char *, ...);
	static void				clearBrowser(void);
};


#endif /* !__FK_WINDOW_HEADER__ */
