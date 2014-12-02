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
#include "Ball.h"

// コンストラクタ
Ball::Ball(void)
{
	init();
}

// 初期化
void Ball::init(void)
{
	direction	= DOWN_MODE;
	y_trs		= 0.1;
	view_mode	= HIGH_MODE;
	bound_count	= 1;
	BALL2.setRadius(BALL_SIZE);
	BALL2.setDivide(6);
	BALL3.setRadius(BALL_SIZE);
	BALL3.setDivide(8);
	BALL4.setRadius(BALL_SIZE);
	BALL4.setDivide(10);

	ball_model.glMoveTo(0.0, TOP_BALL_POS, 0.0);
	ball_model.setShape(&BALL2);
}

// fk_Model を返す関数
fk_Model * Ball::getModel(void)
{
	return &ball_model;
}

// ボールの現在位置を返す関数
fk_Vector Ball::getPosition(void)
{
	return ball_model.getPosition();
}

// 視点からの距離によってボールの分割数を変える関数 (Level Of Detail)
void Ball::lod(fk_Vector pos){
	double	Distance;

	Distance = (ball_model.getPosition() - pos).dist();

	switch(view_mode) {
	  case HIGH_MODE:

		if(Distance < LOD4_HIGH) {
			ball_model.setShape(&BALL4);
		} else if(Distance < LOD3_HIGH) {
			ball_model.setShape(&BALL3);
		} else {
			ball_model.setShape(&BALL2);
		}
		break;

	  case LOW_MODE:

		if(Distance < LOD4_LOW) {
			ball_model.setShape(&BALL4);
		} else if(Distance < LOD3_LOW) {
			ball_model.setShape(&BALL3);
		} else {
			ball_model.setShape(&BALL2);
		}
		break;

	  default:
		break;
	}

	return;
}

// ボールを加速させる関数
void Ball::accel(void)
{
	switch(direction) {
	  case DOWN_MODE:
		y_trs *= DOWN_ACCEL;
		ball_model.glTranslate(0.0, -y_trs, 0.0);
		break;

	  case RISE_MODE:
		y_trs /= RISE_ACCEL;
		ball_model.glTranslate(0.0, y_trs,0.0);
		break;
		
	  default:
		break;
	}
}

// ボールの跳ね返り判定をする関数
void Ball::bound(void)
{
	if(ball_model.getPosition().y < BTM_BALL_POS) {
		direction = RISE_MODE;
	} else if(y_trs < 0.01) {
		if(direction == RISE_MODE) {
			if(bound_count % 4 < 2) {
				view_mode = HIGH_MODE;
			} else {
				view_mode = LOW_MODE;
			}
			bound_count++;
		}
		direction = DOWN_MODE;
	}

	return;
}

// ボールの運動に関する関数. 返り値は視点モード
int Ball::draw(fk_Vector pos)
{
	lod(pos);
	bound();
	accel();
	//４回跳ね返ると初期化
	if(bound_count > 4) init();
	return view_mode;
}
