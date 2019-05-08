#include <FK/FK.h>

using namespace FK;
using namespace FK::Material;

int main(int, char *[])
{
	fk_AppWindow	window;
	fk_Model		model;
	fk_Block		block(50.0, 70.0, 40.0);

	// マテリアルの初期化
	fk_Material::initDefault();

	// ウィンドウ設定
	window.setSize(800, 800);

	// モデルの設定
	model.setShape(&block);
	model.setMaterial(Yellow);

	// 視点の位置と姿勢を設定
	window.setCameraPos(0.0, 0.0, 500.0);
	window.setCameraFocus(0.0, 0.0, 0.0);

	// モデルをウィンドウに登録
	window.entry(&model);
	window.open();

	while(window.update() == true) {
		// 直方体を Y 軸中心に回転
		model.glRotateWithVec(0.0, 0.0, 0.0, fk_Y, FK_PI/300.0);
	}

	return 0;
}
