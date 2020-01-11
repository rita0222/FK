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
// fk_TrackBallクラス
// マウスでの自由な視点操作を提供します。

#include <FK/TrackBall.h>

using namespace FK;
using namespace std;

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

	lookButton = fk_MouseButton::M3;
	distButton[0] = fk_MouseButton::M1;
	distButton[1] = fk_MouseButton::M3;
	moveButton = fk_MouseButton::M2;

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
	if(camera != nullptr) return true;
	else return false;
}

// ３人称視点位置制御
void fk_TrackBall::ControlLookTo()
{
	// 初回クリック時
	fk_Vector cameraV = camera->getVec();
	fk_Vector cameraU = camera->getUpVec();
	fk_Vector cameraX = cameraV ^ cameraU;

	if(fk_win->getMouseStatus(lookButton, overCheck) & !lookClick) {
		tie(oldX, oldY) = fk_win->getMousePosition(overCheck);
		lookClick = true;
		echoX = 0;
		echoY = 0;
	// クリック継続時
	} else if(fk_win->getMouseStatus(lookButton, overCheck) & lookClick) {
		tie(nowX, nowY) = fk_win->getMousePosition(overCheck);
		double divX = double(oldX - nowX)/divLook;
		double divY = double(oldY - nowY)/divLook;
		camera->glRotateWithVec(lookPos, lookPos + cameraU, divX);
		camera->glRotateWithVec(lookPos, lookPos + cameraX, divY);

		echoX = oldX - nowX;
		echoY = oldY - nowY;
		oldX = nowX;
		oldY = nowY;
	// リリース時
	} else {
		lookClick = false;
		if(bEcho) {
			camera->glRotateWithVec(lookPos, lookPos + cameraU, double(echoX)/divLook);
			camera->glRotateWithVec(lookPos, lookPos + cameraX, double(echoY)/divLook);
		}
	}
	// 注視点を向き続ける
	// camera->glFocus(lookPos);

	return;
}

// ３人称視点距離制御
void fk_TrackBall::ControlLookToDist()
{
	static fk_Vector	prePos;
	prePos = camera->getPosition();
	bool bShiftState =
		fk_win->getSpecialKeyStatus(fk_Key::SHIFT_L, false) ||
		fk_win->getSpecialKeyStatus(fk_Key::SHIFT_R, false);

	camera->loTranslate(0.0, 0.0, fk_win->getMouseWheelStatus()*5.0);
	if((lookPos - camera->getPosition()).dist() < 5.0) camera->glMoveTo(prePos);

	// 初回クリック時
	if( (fk_win->getMouseStatus(distButton[0], overCheck) &
		 fk_win->getMouseStatus(distButton[1], overCheck) & !distClick)
		|| (bShiftState & fk_win->getMouseStatus(lookButton, overCheck) & !distClick) ) {
		tie(oldX, oldY) = fk_win->getMousePosition(overCheck);
		distClick = true;
	// クリック継続時
	} else if( (fk_win->getMouseStatus(distButton[0], overCheck) &
				fk_win->getMouseStatus(distButton[1], overCheck) & distClick)
			   || (bShiftState & fk_win->getMouseStatus(lookButton, overCheck) & distClick) ) {
		tie(nowX, nowY) = fk_win->getMousePosition(overCheck);

		// 左右ドラッグでズーム操作を可能にした
		camera->loTranslate(0.0, 0.0,
							(double)(nowY - oldY)/divPos + (double)(oldX - nowX)/divPos);

		if((lookPos - camera->getPosition()).dist() < divDist) camera->glMoveTo(prePos);
		tie(oldX, oldY) = fk_win->getMousePosition(overCheck);

	} else {
		// リリース時
		distClick = false;
	}
	// 注視点を向き続ける
	// camera->glFocus(lookPos);

	return;
}

// ３人称視点注視点制御
void fk_TrackBall::ControlLookToMove()
{
	// 初回クリック時
	if(fk_win->getMouseStatus(moveButton, overCheck) & !moveClick) {
		tie(oldX, oldY) = fk_win->getMousePosition(overCheck);
		moveClick = true;
	// クリック継続時
	} else if(fk_win->getMouseStatus(moveButton, overCheck) & moveClick) {
		static fk_Vector prePos;

		prePos = camera->getPosition();
		tie(nowX, nowY) = fk_win->getMousePosition(overCheck);
		camera->loTranslate(-(double)(nowX - oldX)/divPos, (double)(nowY - oldY)/divPos, 0.0);
		lookPos += camera->getPosition() - prePos;
		tie(oldX, oldY) = fk_win->getMousePosition(overCheck);
	// リリース時
	} else {
		moveClick = false;
	}
	// 注視点を向き続ける
	// camera->glFocus(lookPos);

	return;
}

void  fk_TrackBall::update(void)
{
	ControlLookToMove();
	ControlLookToDist();
	ControlLookTo();
}
