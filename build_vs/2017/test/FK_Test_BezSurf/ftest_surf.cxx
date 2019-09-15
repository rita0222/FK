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
	surf.setDiv(16);
	
	for(int i = 0; i <= 3; ++i) {
		for(int j = 0; j <= 3; ++j) {
			surf.setCtrl(i, j, fk_Vector(-30.0 + 20.0*double(i),
										 -30.0 + 20.0*double(j), 50.0*(sin(i)*cos(j))));
		}
	}

	model.setLineColor(0.0, 0.0, 1.0);
	model.setPointColor(1.0, 0.0, 0.0);
	model.setCurveColor(0.0, 1.0, 0.0);
	model.setMaterial(Material::Yellow);
	model.setSmoothMode(true);
	model.setPointSize(5.0);
	model.setShape(&surf);
	model.setDrawMode(fk_DrawMode::GEOM_LINE |
					  fk_DrawMode::GEOM_FACE |
					  fk_DrawMode::LINE |
					  fk_DrawMode::POINT);
	window.entry(&model);
	
	while(window.update() == true) {
	}

	return 0;
}
