#include <FK/FK.h>
#include <memory>

using namespace FK;
using namespace std;

int main(int, char **)
{
	unique_ptr<fk_Block> block(new fk_Block(10.0, 20.0, 15.0));
	unique_ptr<fk_Model> blockModel(new fk_Model());
	unique_ptr<fk_Model> fCamera(new fk_Model());
	unique_ptr<fk_Model> lightModel(new fk_Model());
	unique_ptr<fk_Light> light(new fk_Light());
	unique_ptr<fk_Scene> fScene(new fk_Scene());

	unique_ptr<fk_RectTexture> texture(new fk_RectTexture());
	unique_ptr<fk_Model> texModel(new fk_Model());
	unique_ptr<fk_Model> camera(new fk_Model());
	unique_ptr<fk_Scene> scene(new fk_Scene());
	unique_ptr<fk_AppWindow> window(new fk_AppWindow());

	window->setSize(600, 600);
	window->open();
	window->update();
	
	unique_ptr<fk_Renderer> renderer(new fk_Renderer(1024, 768));

	fk_Material::initDefault();			 

	lightModel->setShape(light.get());
	lightModel->setMaterial(Material::TrueWhite);
	lightModel->glVec(0.0, 0.0, -1.0);

	blockModel->setShape(block.get());
	blockModel->setMaterial(Material::Yellow);

	fCamera->glMoveTo(0.0, 0.0, 100.0);
	fCamera->glFocus(0.0, 0.0, 0.0);
	fScene->entryModel(blockModel.get());
	fScene->entryModel(lightModel.get());
	fScene->entryCamera(fCamera.get());
	fScene->setBGColor(1.0f, 0.0f, 1.0f);
	renderer->setScene(fScene.get());
	texModel->setShape(texture.get());
	texModel->setMaterial(Material::White);
	texture->setTextureSize(10.24 * 4.0, 7.68 * 4.0);
	texture->setFrameBuffer(renderer->getColorBuffer());

	camera->glMoveTo(0.0, 0.0, 100.0);
	camera->glFocus(0.0, 0.0, 0.0);

	scene->entryModel(texModel.get());
	scene->entryModel(lightModel.get());
	scene->entryCamera(camera.get());
	scene->setBGColor(0.1f, 0.4f, 0.5f);

	// ウィンドウにモデルを登録
	window->setScene(scene.get());

	while(window->update() == true) {

		blockModel->glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::Y, fk_Math::PI/60.0);
		renderer->draw();

		texModel->glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::X, fk_Math::PI/180.0);
		if(texModel->getVec().z > 0.0) {
			texModel->glRotateWithVec(0.0, 0.0, 0.0, fk_Axis::X, fk_Math::PI);
		}
	}
	return 0;
}
