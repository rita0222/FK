// fk_TrackBallクラス
// マウスでの自由な視点操作を提供します。

#include <FK/TrackBall.h>

using namespace FK;
using namespace std;

static constexpr fk_MouseButton DISTBUTTON[2] = {fk_MouseButton::M1, fk_MouseButton::M3};
static constexpr fk_MouseButton MOVEBUTTON = fk_MouseButton::M2;
static constexpr fk_MouseButton LOOKBUTTON = fk_MouseButton::M3;

fk_TrackBall::Member::Member(fk_Window *argWindow, fk_Model *argCamera) :
	fk_win(argWindow), camera(argCamera),
	overCheck(false), nowX(0), nowY(0), oldX(0), oldY(0),
	// bEcho(false), echoX(0), echoY(0), 
	lookClick(false), distClick(false), moveClick(false)
{
	return;
}
	

// コンストラクタ
fk_TrackBall::fk_TrackBall(fk_Window *argWindow, fk_Model *argCamera) :
	_m(make_unique<Member>(argWindow, argCamera))
{
	return;
}

// カメラの変更
void fk_TrackBall::setCamera(fk_Model *argCamera)
{
	// ポインタ受け取り
	_m->camera = argCamera;

	return;
}

// 注視点の変更
void fk_TrackBall::setLookTo(fk_Vector vec)
{
	// 注視点受け取り
	_m->lookPos = vec;
	_m->camera->glFocus(_m->lookPos);

	return;
}

// カメラポインタは渡されているか
bool fk_TrackBall::isSetCamera(void)
{
	if(_m->camera != nullptr) return true;
	else return false;
}

// ３人称視点位置制御
void fk_TrackBall::ControlLookTo(void)
{
	if(_m->fk_win == nullptr || _m->camera == nullptr) return;
	// 初回クリック時
	fk_Vector cameraV = _m->camera->getVec();
	fk_Vector cameraU = _m->camera->getUpVec();
	fk_Vector cameraX = cameraV ^ cameraU;

	if(_m->fk_win->getMouseStatus(LOOKBUTTON, _m->overCheck) & !_m->lookClick) {
		tie(_m->oldX, _m->oldY) = _m->fk_win->getMousePosition(_m->overCheck);
		_m->lookClick = true;
		//_m->echoX = 0;
		//_m->echoY = 0;
	// クリック継続時
	} else if(_m->fk_win->getMouseStatus(LOOKBUTTON, _m->overCheck) & _m->lookClick) {
		tie(_m->nowX, _m->nowY) = _m->fk_win->getMousePosition(_m->overCheck);
		double divX = (double(_m->oldX) - double(_m->nowX))/DIVLOOK;
		double divY = (double(_m->oldY) - double(_m->nowY))/DIVLOOK;
		_m->camera->glRotateWithVec(_m->lookPos, _m->lookPos + cameraU, divX);
		_m->camera->glRotateWithVec(_m->lookPos, _m->lookPos + cameraX, divY);

		//_m->echoX = _m->oldX - _m->nowX;
		//_m->echoY = _m->oldY - _m->nowY;
		_m->oldX = _m->nowX;
		_m->oldY = _m->nowY;
	// リリース時
	} else {
		_m->lookClick = false;
		/*
		if(_m->bEcho) {
			_m->camera->glRotateWithVec(_m->lookPos, _m->lookPos + cameraU, double(echoX)/DIVLOOK);
			_m->camera->glRotateWithVec(_m->lookPos, _m->lookPos + cameraX, double(echoY)/DIVLOOK);
		}
		*/
	}
	// 注視点を向き続ける
	// camera->glFocus(lookPos);

	return;
}

// ３人称視点距離制御
void fk_TrackBall::ControlLookToDist(void)
{
	fk_Vector prePos(_m->camera->getPosition());

	bool bShiftState =
		_m->fk_win->getSpecialKeyStatus(fk_Key::SHIFT_L, false) ||
		_m->fk_win->getSpecialKeyStatus(fk_Key::SHIFT_R, false);

	_m->camera->loTranslate(0.0, 0.0, _m->fk_win->getMouseWheelStatus()*5.0);
	if((_m->lookPos - _m->camera->getPosition()).dist() < 5.0) _m->camera->glMoveTo(prePos);

	if((_m->fk_win->getMouseStatus(DISTBUTTON[0], _m->overCheck) &
		_m->fk_win->getMouseStatus(DISTBUTTON[1], _m->overCheck) &
		!_m->distClick) ||
	   (bShiftState &
		_m->fk_win->getMouseStatus(LOOKBUTTON, _m->overCheck) &
		!_m->distClick)) { // 初回クリック時
		

		tie(_m->oldX, _m->oldY) = _m->fk_win->getMousePosition(_m->overCheck);
		_m->distClick = true;

	} else if((_m->fk_win->getMouseStatus(DISTBUTTON[0], _m->overCheck) &
			   _m->fk_win->getMouseStatus(DISTBUTTON[1], _m->overCheck) &
			   _m->distClick) ||
			  (bShiftState &
			   _m->fk_win->getMouseStatus(LOOKBUTTON, _m->overCheck) &
			   _m->distClick)) { // クリック継続時

		tie(_m->nowX, _m->nowY) = _m->fk_win->getMousePosition(_m->overCheck);

		// 左右ドラッグでズーム操作を可能にした
		_m->camera->loTranslate(0.0, 0.0,
			(double(_m->nowY) - double(_m->oldY)) / DIVPOS +
			(double(_m->oldX) - double(_m->nowX)) / DIVPOS);

		if((_m->lookPos - _m->camera->getPosition()).dist() < DIVDIST) _m->camera->glMoveTo(prePos);
		tie(_m->oldX, _m->oldY) = _m->fk_win->getMousePosition(_m->overCheck);

	} else {
		// リリース時
		_m->distClick = false;
	}
	// 注視点を向き続ける
	// _m->camera->glFocus(_m->lookPos);

	return;
}

// ３人称視点注視点制御
void fk_TrackBall::ControlLookToMove(void)
{
	// 初回クリック時
	if(_m->fk_win->getMouseStatus(MOVEBUTTON, _m->overCheck) & !_m->moveClick) {
		tie(_m->oldX, _m->oldY) = _m->fk_win->getMousePosition(_m->overCheck);
		_m->moveClick = true;
	// クリック継続時
	} else if(_m->fk_win->getMouseStatus(MOVEBUTTON, _m->overCheck) & _m->moveClick) {
		fk_Vector prePos(_m->camera->getPosition());

		tie(_m->nowX, _m->nowY) = _m->fk_win->getMousePosition(_m->overCheck);
		_m->camera->loTranslate(-(double(_m->nowX) - double(_m->oldX))/DIVPOS,
			(double(_m->nowY) - double(_m->oldY))/DIVPOS, 0.0);
		_m->lookPos += _m->camera->getPosition() - prePos;
		tie(_m->oldX, _m->oldY) = _m->fk_win->getMousePosition(_m->overCheck);
	// リリース時
	} else {
		_m->moveClick = false;
	}
	// 注視点を向き続ける
	// _m->camera->glFocus(_m->lookPos);

	return;
}

void  fk_TrackBall::update(void)
{
	ControlLookToMove();
	ControlLookToDist();
	ControlLookTo();
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
