#include <FK/FK.h>
#include <FK/Renderer.h>

using namespace FK;

int main(int, char **)
{
	fk_Block		block(10.0, 20.0, 15.0);
	fk_Model		blockModel, fCamera, lightModel;
	fk_Light		light;
	fk_Scene		fScene;

	fk_RectTexture	texture;
	fk_Model		texModel, camera;
	fk_Scene		scene;
	fk_AppWindow	window;

	window.setSize(600, 600);
	window.open();
	window.update();
	
	fk_Renderer		renderer(1024, 768);

	lightModel.setShape(&light);
	lightModel.setMaterial(Material::TrueWhite);
	lightModel.glVec(0.0, 0.0, -1.0);

	blockModel.setShape(&block);
	blockModel.setMaterial(Material::Yellow);

	fCamera.glMoveTo(0.0, 0.0, 100.0);
	fCamera.glFocus(0.0, 0.0, 0.0);
	fScene.entryModel(&blockModel);
	fScene.entryModel(&lightModel);
	fScene.entryCamera(&fCamera);
	fScene.setBGColor(1.0f, 0.0f, 1.0f);
	renderer.setScene(&fScene);
	texModel.setShape(&texture);
	texModel.setMaterial(Material::White);
	texture.setTextureSize(10.24 * 4.0, 7.68 * 4.0);
	texture.setFrameBuffer(renderer.getColorBuffer());

	camera.glMoveTo(0.0, 0.0, 100.0);
	camera.glFocus(0.0, 0.0, 0.0);

	scene.entryModel(&texModel);
	scene.entryModel(&lightModel);
	scene.entryCamera(&camera);
	scene.setBGColor(0.1f, 0.4f, 0.5f);

	// ウィンドウにモデルを登録
	window.setScene(&scene);

	while(window.update() == true) {

		blockModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::Y, fk_Math::PI/60.0);
		renderer.draw();

		texModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::X, fk_Math::PI/180.0);
		if(texModel.getVec().z > 0.0) {
			texModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::X, fk_Math::PI);
		}
	}
	return 0;
}
