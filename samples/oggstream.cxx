#include <FK/FK.h>
#include <FK/Audio.h>
#include <thread>

using namespace std;
using namespace FK;

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
	blockModel.setMaterial(Material::Yellow);
	window.entry(blockModel);

	window.setCameraPos(0.0, 1.0, 20.0);
	window.setCameraFocus(0.0, 1.0, 0.0);

	window.setSize(1000, 800);
	window.setBGColor(0.6, 0.7, 0.8);
	window.open();
	window.showGuide(fk_Guide::GRID_XZ);
	window.setTrackBallMode(true);

	volume = 0.5;
	endFlg = false;

	th = thread(bgmPlay, ref(volume), ref(endFlg));

	while(window.update() == true) {
		blockModel.glRotateWithVec(origin, fk_Axis::Y, fk_Math::PI/360.0);

		if(window.getKeyStatus('Z') == fk_Switch::DOWN && volume < 1.0) {
			volume += 0.1;
		}
		if(window.getKeyStatus('X') == fk_Switch::DOWN && volume > 0.0) {
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

	fk_System::setcwd();

	if(bgm.open("data/epoq.ogg") == false) {
		fl_alert("BGM Open Error");
		return;
	}
	bgm.setLoopMode(true);
	bgm.setGain(argVolume);

	while(argFlg == false) {
		bgm.setGain(argVolume);
		bgm.play();
		fk_Time::sleep(0.05);
	}
	return;
}
