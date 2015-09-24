#include <FK/FK.h>
#include <FK/Audio.h>
#include <thread>

using namespace std;

void bgmPlay(double &, bool &);

int main(int, char *[])
{
	fk_AppWindow	window;
	fk_Block		block(1.0, 1.0, 1.0);
	fk_Model		blockModel;
	fk_Vector		origin(0.0, 0.0, 0.0);
	double			volume;
	bool			endFlg;
	thread			th;
	
	blockModel.setShape(&block);
	blockModel.glMoveTo(3.0, 3.0, 0.0);
	blockModel.setMaterial(Yellow);
	window.entry(blockModel);

	window.setCameraPos(0.0, 1.0, 20.0);
	window.setCameraFocus(0.0, 1.0, 0.0);

	window.setSize(1000, 800);
	window.setBGColor(0.6, 0.7, 0.8);
	window.open();
	window.showGuide(FK_GRID_XZ);

	volume = 0.5;
	endFlg = false;

	th = thread(bgmPlay, ref(volume), ref(endFlg));

	while(window.update() == true) {
		blockModel.glRotateWithVec(origin, fk_Y, FK_PI/360.0);

		if(window.getKeyStatus('Z') == FK_SW_DOWN && volume < 1.0) {
			volume += 0.1;
		}
		if(window.getKeyStatus('X') == FK_SW_DOWN && volume > 0.0) {
			volume -= 0.1;
		}
	}
	endFlg = true;
	th.join();
	return 0;
}

void bgmPlay(double &argVolume, bool &argFlg)
{
	fk_AudioStream			bgm;
	chrono::milliseconds 	ns(50);

	fk_System::setcwd();

	if(bgm.open("epoq.ogg") == false) {
		fl_alert("BGM Open Error");
		return;
	}
	bgm.setLoopMode(true);
	bgm.setGain(argVolume);

	while(argFlg == false) {
		bgm.setGain(argVolume);
		bgm.play();
		this_thread::sleep_for(ns);
	}
	return;
}
