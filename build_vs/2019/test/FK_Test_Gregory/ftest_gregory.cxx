#include <FK/FK.h>
#include <random>

using namespace std;
using namespace FK;

double r(double min, double max, mt19937 &mt)
{
	uniform_real_distribution<>	dist(0.0, 1.0);
	
	return min + (max - min)*dist(mt);
}

void modelInit(fk_Model *argM)
{
	argM->setLineColor(0.0, 0.0, 1.0);
	argM->setPointColor(1.0, 0.0, 0.0);
	argM->setCurveColor(0.0, 1.0, 0.0);
	argM->setMaterial(Material::Yellow);
	argM->setSmoothMode(true);
	argM->setPointSize(5.0);
	argM->setDrawMode(fk_Draw::GEOM_LINE | fk_Draw::GEOM_FACE | fk_Draw::LINE | fk_Draw::POINT);
}


int main(int, char *[])
{
	fk_AppWindow * window = new fk_AppWindow();
	fk_Light * light = new fk_Light();
	fk_Model* lightModel = new fk_Model();
	fk_Model* camera = new fk_Model();

	fk_Model* model[2];
	fk_Gregory* surf[2];

	random_device	rnd;
	mt19937			mt(rnd());
	
	fk_Material::initDefault();

	window->clearModel();
	window->setCameraModel(camera);
	window->setSize(800, 800);
	window->setBGColor(0.6, 0.7, 0.8);
	window->setCameraPos(0.0, 0.0, 100.0);
	window->setCameraFocus(0.0, 0.0, 0.0);
	window->open();
	window->setTrackBallMode(true);

	fk_Vector ctrlP[4];
	for(int i = 0; i < 2; i++) {
		model[i] = new fk_Model();
		surf[i] = new fk_Gregory();
		surf[i]->setDiv(64);
		double x = double(i)*30.0 - 30.0;

		for(int j = 0; j <= 3; j++) {
			double d = 10.0*double(j);
			ctrlP[0].set(x + d, -r(13.0, 17.0, mt), r(-15.0, 15.0, mt));
			ctrlP[1].set(x + d, r(13.0, 17.0, mt), r(-15.0, 15.0, mt));
			ctrlP[2].set(x, d - r(13.0, 17.0, mt), r(-15.0, 15.0, mt));
			ctrlP[3].set(x + 30.0, d - r(13.0, 17.0, mt), r(-15.0, 15.0, mt));

			for(int k = 0; k < 4; k++) {
				surf[i]->setBoundary(fk_UV(k), j, ctrlP[k]);
			}
		}

		surf[i]->adjustDerivative();
		model[i]->setShape(surf[i]);
		modelInit(model[i]);
		window->entry(model[i]);
	}

	surf[1]->setBoundary(fk_UV::V_S, 0, surf[0]->getBoundary(fk_UV::V_E, 0));
	surf[1]->setBoundary(fk_UV::V_S, 3, surf[0]->getBoundary(fk_UV::V_E, 3));
	if(surf[1]->connect(surf[0], fk_UV::V_S, fk_UV::V_E, true, true) == false) fl_alert("NG");

	lightModel->setShape(light);
	lightModel->setMaterial(Material::TrueWhite);
	lightModel->glVec(0.0, 0.0, -1.0);
	window->entry(lightModel);

	while(window->update() == true) {
		if(window->getKeyStatus('1', fk_Switch::DOWN)) {
			for(int i = 0; i < 2; i++) {
				model[i]->setDrawMode(fk_Draw::GEOM_LINE | fk_Draw::GEOM_FACE | fk_Draw::LINE | fk_Draw::POINT);
			}
		}
		if(window->getKeyStatus('2', fk_Switch::DOWN)) {
			for(int i = 0; i < 2; i++) {
				model[i]->setDrawMode(fk_Draw::GEOM_FACE | fk_Draw::LINE | fk_Draw::POINT);
			}
		}
		if(window->getKeyStatus('3', fk_Switch::DOWN)) {
			for(int i = 0; i < 2; i++) {
				model[i]->setDrawMode(fk_Draw::GEOM_FACE);
			}
		}
	}	

	delete window;
	delete lightModel;
	delete light;
	delete camera;
	for (int i = 0; i < 2; i++) {
		delete model[i];
		delete surf[i];
	}

	return 0;
}
