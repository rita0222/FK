/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
#include <FK/FK.h>

using namespace FK;
using namespace FK::Material;

const double	DOWN_ACCEL		= 0.050;	// 降下時の加速度
const double	RISE_ACCEL		= 0.053;	// 上昇時の減速度
const int		DOWN_MODE		= 0;		// 降下モード
const int		RISE_MODE		= 1;		// 上昇モード
const int		LOW_MODE		= 0;		// ブロック視点モード
const int		HIGH_MODE		= 1;		// 鳥瞰モード
const int		LOD4_HIGH		= 200;		// 四分割距離 (鳥瞰)
const int		LOD3_HIGH		= 300;		// 三分割距離 (鳥瞰)
const int		LOD4_LOW		= 90;		// 四分割距離 (ブロック)
const int		LOD3_LOW		= 120;		// 三分割距離 (ブロック)
const double	TOP_BALL_POS	= 400.0;	// ボール始点高さ
const double	BTM_BALL_POS	= 12.0;		// ボール跳ね返り高さ
const double	BALL_SIZE		= 12.0;		// ボール半径
const double	ROTATE_SPEED	= 0.02;		// 地面回転速度
const int		BOUND_CYCLE		= 6;		// 視点初期化周期
const int		VIEW_CHANGE		= 4;		// 視点切り替えタイミング

class Ball {

private:
	int			direction;		// ボールの状態(DOWN_MODE or RISE_MODE)
	int			view_mode;		// 視点モード
	int			bound_count;	// バウンド回数を数える変数
	double		y_trs;			// ボールのｙ座標移動量
	fk_Model	ball_model;		// ボールのモデル
	fk_Sphere	BALL2;			// 二分割形状
	fk_Sphere	BALL3;			// 三分割形状
	fk_Sphere	BALL4;			// 四分割形状

public:

	Ball(void);
	void		init(void);
	fk_Model *	getModel(void);
	fk_Vector	getPosition(void);
	void		lod(fk_Vector);
	void		accel(void);
	void		bound(void);
	int			draw(fk_Vector);
};

// コンストラクタ
Ball::Ball(void)
{
	init();
}

// 初期化
void Ball::init(void)
{
	direction	= DOWN_MODE;
	y_trs		= 0.0;
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
		fl_alert("Err!! View Mode is wrong.");
		break;
	}

	return;
}

// ボールを加速させる関数
void Ball::accel(void)
{
	switch(direction) {
	  case DOWN_MODE:
		y_trs += DOWN_ACCEL;
		ball_model.glTranslate(0.0, -y_trs, 0.0);
		break;

	  case RISE_MODE:
		y_trs -= RISE_ACCEL;
		ball_model.glTranslate(0.0, y_trs,0.0);
		break;
		
	  default:
		fl_alert("Err!! Direction Mode is wrong.");
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
			if(bound_count % BOUND_CYCLE < VIEW_CHANGE) {
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
	if(bound_count > BOUND_CYCLE) init();
	return view_mode;
}

int main(int, char *[])
{
	int				view_mode = HIGH_MODE;
	Ball			ball;
	fk_Sphere		lightBall(4, 2.0);
	fk_Model		viewModel, groundModel, blockModel, lightModel, lightBallModel;
	fk_Light		light;
	fk_Circle		ground(4, 100.0);
	fk_Block		block(10.0, 10.0, 10.0);
	fk_Scene		scene;

	// ### WINDOW ###
	fk_AppWindow	win;
	win.setSize(800, 800);
	win.setScene(&scene);

	// ### Material 初期化 ###
	fk_Material::initDefault();

	// ### VIEW POINT ###
	// 上の方から見た視点
	viewModel.glMoveTo(0.0, 400.0, 80.0);
	viewModel.glFocus(0.0, 30.0, 0.0);
	viewModel.glUpvec(0.0, 1.0, 0.0);

	// ### LIGHT ###
	light.setLightType(fk_LightType::POINT);
	light.setAttenuation(0.0, 0.0);
	lightModel.setShape(&light);
	lightModel.setMaterial(WhiteLight);
	lightModel.glTranslate(-60.0, 60.0, 0.0);
	lightModel.glVec(0.0, -1.0, 0.0);

	lightBallModel.setShape(&lightBall);
	lightBallModel.setMaterial(TrueWhite);
	lightBallModel.glTranslate(lightModel.getInhPosition());
	light.setAttenuation(0.01, 0.0, 0.2);
	
	// ### GROUND ###
	groundModel.setShape(&ground);
	LightGreen.setSpecular(0.1, 0.1, 0.1);
	LightGreen.setShininess(80.0);
	groundModel.setMaterial(LightGreen);
	groundModel.setSmoothMode(true);
	groundModel.loRotateWithVec(0.0, 0.0, 0.0, fk_Axis::X, -fk_Math::PI/2.0);

	// ### VIEW BLOCK ###
	blockModel.setShape(&block);
	Blue.setSpecular(1.0, 1.0, 1.0);
	Blue.setShininess(70.0);
	blockModel.setMaterial(Blue);
	blockModel.glMoveTo(60.0, 30.0, 0.0);
	blockModel.setParent(&groundModel);

	// ### BALL ###
	Red.setSpecular(1.0, 1.0, 1.0);
	Red.setShininess(100.0);
	ball.getModel()->setMaterial(Red);
	ball.getModel()->setSmoothMode(true);
	
	// ### Model Entry ###
	scene.entryCamera(&viewModel);
	scene.entryModel(&lightModel);
	scene.entryModel(ball.getModel());
	scene.entryModel(&groundModel);
	scene.entryModel(&blockModel);
	scene.entryModel(&lightBallModel);

	win.open();

	// ### MAIN LOOP ###
	while(win.update() == true) {

		// ボールを弾ませて, カメラの状態を取得。
		view_mode = ball.draw(viewModel.getPosition());

		if(view_mode == HIGH_MODE) {
			// カメラを上からの視点にする。
			viewModel.glMoveTo(0.0, 400.0, 80.0);
			viewModel.glFocus(0.0, 30.0, 0.0);
			viewModel.glUpvec(0.0, 1.0, 0.0);
			scene.entryModel(&blockModel);
		} else {
			// カメラをブロックからの視点にする。
			viewModel.glMoveTo(blockModel.getInhPosition());
			viewModel.glTranslate(0.0, 10.0, 0.0);
			viewModel.glFocus(ball.getPosition());
			viewModel.glUpvec(0.0, 1.0, 0.0);
			scene.removeModel(&blockModel);
		}

		// 地面をくるくる回転させましょう。
		groundModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::Y, ROTATE_SPEED);
	}

	return 0;
}
