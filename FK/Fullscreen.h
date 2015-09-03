/****************************************************************************
 *
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2015, Fine Kernel Project, All rights reserved.
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
#ifndef __FK_FULLSCREEN_HEADER__
#define __FK_FULLSCREEN_HEADER__

#include <FK/Window.h>

#if defined(WIN32) && !defined(_MINGW_)

#include <FL/x.h>
#include <windows.h>

#endif //WIN32

//! フルスクリーン制御クラス
/*!
 *	このクラスは、WIN32APIを利用した完全なフルスクリーンモードを提供します。
 *
 *	\attention
 *		本クラスの機能は、
 *		FLTK と Windows に依存していますので、
 *		それ以外の環境では利用できません。
 *
 *	\sa fk_Window
 */
class fk_FullscreenController {
private:

#if defined(WIN32) && !defined(_MINGW_) && !defined(FK_CLI_CODE)

	////////// ウインドウ保存関係 //////////
	#define MAX_NAMELENGTH		512
	#define MAX_WINDOWNUMBER	128

	enum{
		SCMODE_FULLSCREEN,				// フルスクリーンモード
		SCMODE_WINDOW					// ウインドウモード
	};

	Fl_Window	*pFlWnd;
	fk_Window	*pFkWnd;
	HWND		hFlWnd;
	int			nWndX, nWndY, nWndW, nWndH;
	int			fscW, fscH;
	bool		mode;

	BOOL		SaveWindowPosition(void);
	BOOL		LoadWindowPosition(void);
	BOOL		ChangeScreen(HWND, int, int, int);

#endif //WIN32

public:
	//! コンストラクタ
	fk_FullscreenController(void);
	//! デストラクタ
	~fk_FullscreenController(void);

	//! 初期化関数
	/*!
	 *	フルスクリーン化したい Fl_Window と fk_Window を指定して初期化を行います。
	 *
	 *	\param[in] fl_win	Fl_Window のポインタ
	 *	\param[in] fk_win	fk_Window のポインタ
	 */
	void	init(Fl_Window *fl_win, fk_Window *fk_win);

	//! フルスクリーンモード取得関数
	/*!
	 *	現在フルスクリーン化しているか否かを取得します。
	 *
	 *	\return フルスクリーンなら true を、ウィンドウなら false を返します。
	 */
	bool	isFullscreen(void);

	//! フルスクリーン化関数
	/*!
	 *	フルスクリーン化します。モニタの解像度が対応していない場合は失敗します。
	 *
	 *	\return 成功したら true を、失敗したら false を返します。
	 */
	bool	changeToFullscreen(void);

	//! ウィンドウ化関数
	/*!
	 *	ウィンドウに戻します。
	 */
	void	changeToWindow(void);
};

#if defined(WIN32) && !defined(_MINGW_) && !defined(FK_CLI_CODE)
#ifndef FK_DOXYGEN_USER_PROCESS

//! ウインドウ状態を保持する構造体
typedef struct{
	HWND hWnd;
	WINDOWPLACEMENT WindowPlacement;
} windowstate;

#endif //!FK_DOXYGEN_USER_PROCESS
#endif //WIN32

#endif //!__FK_FULLSCREEN_HEADER__
