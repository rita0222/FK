[!if SRC_RADIO_OPTION1]

[!else]
[!if SRC_RADIO_OPTION2]

int main(int argc, char *argv[])
{

	return 0;
}
[!else]
[!if GUI_LISTBOX == "FLTK"]
#include <FK/FK.h>

int main(int argc, char *argv[])
{
	Fl_Window		mainWindow(512, 512, "FK TEST");
	fk_Model		camera, blockModel, lightModel;
	fk_Light		light;
	fk_Block		block(50.0, 70.0, 40.0);
	fk_Scene		scene;
	fk_Window		window(0, 0, 512, 512);

	mainWindow.end();
	fk_InitMaterial();

	// 照明の設定
	lightModel.setShape(&light);
	lightModel.setMaterial(White);
	lightModel.glMoveTo(0.0, 0.0, 0.0);
	lightModel.glFocus(-1.0, -1.0, -1.0);

	// 直方体の設定
	blockModel.setShape(&block);
	blockModel.setMaterial(Yellow);

	// 各モデルをディスプレイリストに登録
	scene.entryCamera(&camera);
	scene.entryModel(&blockModel);
	scene.entryModel(&lightModel);

	// ウィンドウへディスプレイリストを登録
	window.setScene(&scene);

	// 視点の位置と姿勢を設定
	camera.glMoveTo(0.0, 0.0, 1000.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);

	mainWindow.show();
	window.show();

	while(true) {

		if(mainWindow.visible() == 0) {
			if(Fl::wait() == 0) {
				break;
			} else {
				continue;
			}
		}

		if(window.drawWindow() == 0) break;
		if(Fl::check() == 0) break;
		if(window.winOpenStatus() == false) continue;

		// 直方体を Y 軸中心に回転
		blockModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Y, FK_PI/100.0);

	}

	return 0;
}
[!else]
#define LLCONFIG_FK
#include <Lily/Lily.h>
#include <mmsystem.h>

fk_Window		*window = NULL;

// 終了イベント
void close(LLEventState es)
{
	Lily::end();
}

void resize1(LLEventState es){
	if(window != NULL){
		window->resize(0, 0, es.stage->w(), es.stage->h());
	}
}

void move1(LLEventState es){
	cout << es.stageX << "," << es.stageY << endl;
}

int main(int argc, char *argv[])
{
	LLExWindow		mainWin(0, 0, 512, 512);
	mainWin.entryApplication();

	fk_Model		camera, blockModel, lightModel;
	fk_Light		light;
	fk_Block		block(50.0, 70.0, 40.0);
	fkll_Scene		scene;
	window = new fk_Window(0, 0, 512, 512);

	LLEventConnector	*evc, *evc2;
	mainWin.entryChild(window);

	evc = new LLEventConnector(&mainWin);
	evc->addEvent(LLEVENT_CLOSE, &close);
	evc->addEvent(LLEVENT_RESIZE, &resize1);

	evc2 = new LLEventConnector(window);
	evc2->addEvent(LLEVENT_MOUSEMOVE, &move1);

	fk_InitMaterial();

	// 照明の設定
	lightModel.setShape(&light);
	lightModel.setMaterial(White);
	lightModel.glMoveTo(0.0, 0.0, 0.0);
	lightModel.glFocus(-1.0, -1.0, -1.0);

	// 直方体の設定
	blockModel.setShape(&block);
	blockModel.setMaterial(Yellow);

	// 各モデルをディスプレイリストに登録
	scene.entryCamera(&camera);
	scene.entryModel(&blockModel);
	scene.entryModel(&lightModel);

	// ウィンドウへディスプレイリストを登録
	window->setScene(&scene);

	// 視点の位置と姿勢を設定
	camera.glMoveTo(0.0, 0.0, 1000.0);
	camera.glFocus(0.0, 0.0, 0.0);
	camera.glUpvec(0.0, 1.0, 0.0);

	window->show();
	mainWin.show();

	while(true) {

		if(Lily::update() == 0) { break; }

		if(window->drawWindow() == 0) break;

		// 直方体を Y 軸中心に回転
		blockModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Y, FK_PI/100.0);

	}

	return 0;
}
[!endif]
[!endif]
[!endif]
