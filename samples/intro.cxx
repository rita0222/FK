#include <FK/FK.h>

using namespace FK;

int main(int, char **)
{
	fk_Block		block(10.0, 20.0, 15.0);
	fk_Model		model;
	fk_AppWindow	fk_win;

	// 色パレットの初期化
	fk_Material::initDefault();			 

	// モデルに直方体を設定
	model.setShape(&block);

	// モデルの色を黄色に設定
	model.setMaterial(Material::Yellow);

	// カメラの位置と方向を設定
	fk_win.setCameraPos(0.0, 0.0, 100.0);
	fk_win.setCameraFocus(0.0, 0.0, 0.0);

	// ウィンドウにモデルを登録
	fk_win.entry(&model);

	// ウィンドウのサイズを設定
	fk_win.setSize(600, 600);

	// ウィンドウを開く
	fk_win.open();

	while(fk_win.update() == true) {

		// 直方体を Y 軸を中心に回転させる。
		model.glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::Y, 0.01);
	}
	return 0;
}
