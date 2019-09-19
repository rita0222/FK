#include <FK/FK.h>
#include <FK/BezSurface.h>

using namespace std;
using namespace FK;

int main(int, char *[])
{
	fk_AppWindow	window;
	fk_Model		model;
	fk_BezSurface	surf;

	fk_Material::initDefault();
	window.setSize(800, 800);
	window.setBGColor(0.6, 0.7, 0.8);
	window.setCameraPos(0.0, 0.0, 200.0);
	window.setCameraFocus(0.0, 0.0, 0.0);
	window.open();
	window.setTrackBallMode(true);

	surf.setDegree(3);
	surf.setDiv(64);

	fk_Vector ctrlP;
	for(int i = 0; i <= 3; ++i) {
		ctrlP.x = -30.0 + 20.0*double(i);
		for(int j = 0; j <= 3; ++j) {
			ctrlP.y = -30.0 + 20.0*double(j);
			ctrlP.z = 50.0 * (sin(double(i)) * cos(double(j)));
			surf.setCtrl(i, j, ctrlP);
		}
	}

	model.setLineColor(0.0, 0.0, 1.0);
	model.setPointColor(1.0, 0.0, 0.0);
	model.setCurveColor(0.0, 1.0, 0.0);
	model.setMaterial(Material::Yellow);
	model.setSmoothMode(true);
	model.setPointSize(5.0);
	model.setShape(&surf);
	model.setDrawMode(fk_Draw::GEOM_LINE | fk_Draw::GEOM_FACE | fk_Draw::LINE | fk_Draw::POINT);
	window.entry(&model);
	
	while(window.update() == true) {
		if(window.getKeyStatus('1', fk_Switch::DOWN)) {
			model.setDrawMode(fk_Draw::GEOM_LINE |
							  fk_Draw::GEOM_FACE |
							  fk_Draw::LINE |
							  fk_Draw::POINT);
		}
		if(window.getKeyStatus('2', fk_Switch::DOWN)) {
			model.setDrawMode(fk_Draw::GEOM_FACE |
							  fk_Draw::LINE |
							  fk_Draw::POINT);
		}
		if(window.getKeyStatus('3', fk_Switch::DOWN)) {
			model.setDrawMode(fk_Draw::GEOM_FACE);
		}
	}

	return 0;
}
