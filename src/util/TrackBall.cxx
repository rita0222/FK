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
// fk_TrackBallクラス
// マウスでの自由な視点操作を提供します。

#include <FK/TrackBall.h>

// コンストラクタ
fk_TrackBall::fk_TrackBall(fk_Window *p_fk_win, fk_Model *p_camera)
{
	// ポインタ受け取り
	fk_win = p_fk_win;
	camera = p_camera;
	// ウィンドウオーバー時に座標を返さないかどうか
	overCheck = false;
	// 処理量初期値
	divPos = 10.0;
	divLook = 200.0;
	divDist = 1.0;

	echoX = 0;
	echoY = 0;

	lookButton = FK_MOUSE3;
	distButton[0] = FK_MOUSE1;
	distButton[1] = FK_MOUSE3;
	moveButton = FK_MOUSE2;

	bEcho = false;

	return;
}

// カメラの変更
void fk_TrackBall::setCamera(fk_Model *p_camera)
{
	// ポインタ受け取り
	camera = p_camera;

	return;
}

// 注視点の変更
void fk_TrackBall::setLookTo(fk_Vector vec)
{
	// 注視点受け取り
	lookPos = vec;
	camera->glFocus(lookPos);

	return;
}

// カメラポインタは渡されているか
bool fk_TrackBall::isSetCamera()
{
	if(camera != NULL) return true;
	else return false;
}

// ３人称視点位置制御
void fk_TrackBall::controlLookTo()
{
	// 初回クリック時
	if(fk_win->getMouseStatus(lookButton, overCheck) & !lookClick) {
		fk_win->getMousePosition(&oldX, &oldY, overCheck);
		lookClick = true;
		echoX = 0;
		echoY = 0;
	// クリック継続時
	} else if(fk_win->getMouseStatus(lookButton, overCheck) & lookClick) {
		fk_win->getMousePosition(&nowX, &nowY, overCheck);
		camera->glRotateWithVec(lookPos, fk_Y, (double)(oldX - nowX)/divLook);
		camera->glRotateWithVec(lookPos, lookPos+(camera->getVec()^camera->getUpVec()), (double)(oldY - nowY)/divLook);
		echoX = oldX - nowX;
		echoY = oldY - nowY;
		oldX = nowX;
		oldY = nowY;
	// リリース時
	} else {
		lookClick = false;
		if(bEcho) {
			camera->glRotateWithVec(lookPos, fk_Y, (double)echoX/divLook);
			camera->glRotateWithVec(lookPos, lookPos+(camera->getVec()^camera->getUpVec()), (double)echoY/divLook);
		}
	}
	// 注視点を向き続ける
	// camera->glFocus(lookPos);

	return;
}

// ３人称視点距離制御
void fk_TrackBall::controlLookToDist()
{
	static fk_Vector	prePos;
	prePos = camera->getPosition();
	bool bShiftState = fk_win->getSpecialKeyStatus(FK_SHIFT_L, false) || fk_win->getSpecialKeyStatus(FK_SHIFT_R, false);

	camera->loTranslate(0.0, 0.0, fk_win->getMouseWheelStatus()*5.0);
	if((lookPos - camera->getPosition()).dist() < 5.0) camera->glMoveTo(prePos);

	// 初回クリック時
	if( (fk_win->getMouseStatus(distButton[0], overCheck) & fk_win->getMouseStatus(distButton[1], overCheck) & !distClick)
		|| (bShiftState & fk_win->getMouseStatus(lookButton, overCheck) & !distClick) ) {
		fk_win->getMousePosition(&oldX, &oldY, overCheck);
		distClick = true;
	// クリック継続時
	} else if( (fk_win->getMouseStatus(distButton[0], overCheck) & fk_win->getMouseStatus(distButton[1], overCheck) & distClick)
		|| (bShiftState & fk_win->getMouseStatus(lookButton, overCheck) & distClick) ) {
		fk_win->getMousePosition(&nowX, &nowY, overCheck);
		camera->loTranslate(0.0, 0.0, (double)(nowY - oldY)/divPos + (double)(oldX - nowX)/divPos);	// 左右ドラッグでズーム操作を可能にした
		if((lookPos - camera->getPosition()).dist() < divDist) camera->glMoveTo(prePos);
		fk_win->getMousePosition(&oldX, &oldY, overCheck);
	// リリース時
	} else {
		distClick = false;
	}
	// 注視点を向き続ける
	// camera->glFocus(lookPos);

	return;
}

// ３人称視点注視点制御
void fk_TrackBall::controlLookToMove()
{
	// 初回クリック時
	if(fk_win->getMouseStatus(moveButton, overCheck) & !moveClick) {
		fk_win->getMousePosition(&oldX, &oldY, overCheck);
		moveClick = true;
	// クリック継続時
	} else if(fk_win->getMouseStatus(moveButton, overCheck) & moveClick) {
		static fk_Vector prePos;

		prePos = camera->getPosition();
		fk_win->getMousePosition(&nowX, &nowY, overCheck);
		camera->loTranslate(-(double)(nowX - oldX)/divPos, (double)(nowY - oldY)/divPos, 0.0);
		lookPos += camera->getPosition() - prePos;
		fk_win->getMousePosition(&oldX, &oldY, overCheck);
	// リリース時
	} else {
		moveClick = false;
	}
	// 注視点を向き続ける
	// camera->glFocus(lookPos);

	return;
}

// ３人称視点ショートカット制御
void fk_TrackBall::controlLookToSC()
{
	static double prevDist;
	prevDist = camera->getPosition().dist();

	if(fk_win->getKeyStatus('2', false) || Fl::get_key(FL_KP+'2')) {
		camera->glMoveTo(cos(FK_PI/2.0)*prevDist, 0.0, sin(FK_PI/2.0)*prevDist);
	} else if(fk_win->getKeyStatus('3', false) || Fl::get_key(FL_KP+'3')) {
		camera->glMoveTo(cos(FK_PI/4.0)*prevDist, 0.0, sin(FK_PI/4.0)*prevDist);
	} else if(fk_win->getKeyStatus('6', false) || Fl::get_key(FL_KP+'6')) {
		camera->glMoveTo(cos(0.0)*prevDist, 0.0, sin(0.0)*prevDist);
	} else if(fk_win->getKeyStatus('9', false) || Fl::get_key(FL_KP+'9')) {
		camera->glMoveTo(cos(-FK_PI/4.0)*prevDist, 0.0, sin(-FK_PI/4.0)*prevDist);
	} else if(fk_win->getKeyStatus('8', false) || Fl::get_key(FL_KP+'8')) {
		camera->glMoveTo(cos(-FK_PI/2.0)*prevDist, 0.0, sin(-FK_PI/2.0)*prevDist);
	} else if(fk_win->getKeyStatus('7', false) || Fl::get_key(FL_KP+'7')) {
		camera->glMoveTo(cos(-FK_PI*3.0/4.0)*prevDist, 0.0, sin(-FK_PI*3.0/4.0)*prevDist);
	} else if(fk_win->getKeyStatus('4', false) || Fl::get_key(FL_KP+'4')) {
		camera->glMoveTo(cos(-FK_PI)*prevDist, 0.0, sin(-FK_PI)*prevDist);
	} else if(fk_win->getKeyStatus('1', false) || Fl::get_key(FL_KP+'1')) {
		camera->glMoveTo(cos(FK_PI*3.0/4.0)*prevDist, 0.0, sin(FK_PI*3.0/4.0)*prevDist);
	} else if(fk_win->getKeyStatus('5', false) || Fl::get_key(FL_KP+'5')) {
		camera->glMoveTo(0.0, prevDist, 0.0);
	} else if(fk_win->getKeyStatus('0', false) || Fl::get_key(FL_KP+'0')) {
		fk_Vector	tmpVec(cos(FK_PI*3.0/4.0)*prevDist, 0.66*prevDist, sin(FK_PI*3.0/4.0)*prevDist);
		tmpVec.normalize();
		camera->glMoveTo(tmpVec*prevDist);
	}

	// 注視点を向き続ける
	// camera->glFocus(lookPos);

	return;
}

void  fk_TrackBall::update(void)
{
	controlLookToMove();
	controlLookToDist();
	controlLookTo();
}
