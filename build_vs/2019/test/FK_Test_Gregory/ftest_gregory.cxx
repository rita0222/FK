#define FK_DEF_SIZETYPE
#include <FK/FK.h>
#include <memory>

using namespace std;
using namespace FK;

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
	unique_ptr<fk_AppWindow> window(new fk_AppWindow());
	unique_ptr<fk_Light> light(new fk_Light());
	unique_ptr<fk_Model> lightModel(new fk_Model());
	unique_ptr<fk_Model> camera(new fk_Model());

	vector<unique_ptr<fk_Model>> model(2);
	vector<unique_ptr<fk_Gregory>> surf(2);

	for (auto &m : model) m.reset(new fk_Model());
	for (auto &s : surf) s.reset(new fk_Gregory());

	fk_Material::initDefault();

	window->clearModel();
	window->setCameraModel(camera.get());
	window->setSize(800, 800);
	window->setBGColor(0.6, 0.7, 0.8);
	window->setCameraPos(0.0, 0.0, 100.0);
	window->setCameraFocus(0.0, 0.0, 0.0);
	window->open();
	window->setTrackBallMode(true);

	vector<fk_Vector> ctrlP(4);
	for(_st i = 0; i < 2; i++) {
		surf[i]->setDiv(64);
		double x = double(i)*30.0 - 30.0;

		for(int j = 0; j <= 3; j++) {
			double d = 10.0*double(j);
			ctrlP[0].set(x + d, fk_Math::drand(13.0, 17.0), fk_Math::drand(-15.0, 15.0));
			ctrlP[1].set(x + d, fk_Math::drand(13.0, 17.0), fk_Math::drand(-15.0, 15.0));
			ctrlP[2].set(x, d - fk_Math::drand(13.0, 17.0), fk_Math::drand(-15.0, 15.0));
			ctrlP[3].set(x + 30.0, d - fk_Math::drand(13.0, 17.0), fk_Math::drand(-15.0, 15.0));

			for(int k = 0; k < 4; k++) {
				surf[i]->setBoundary(fk_UV(k), j, ctrlP[k]);
			}
		}

		surf[i]->adjustDerivative();
		model[i]->setShape(surf[i].get());
		modelInit(model[i].get());
		window->entry(model[i].get());
	}

	surf[1]->setBoundary(fk_UV::V_S, 0, surf[0]->getBoundary(fk_UV::V_E, 0));
	surf[1]->setBoundary(fk_UV::V_S, 3, surf[0]->getBoundary(fk_UV::V_E, 3));
	if (surf[1]->connect(surf[0].get(), fk_UV::V_S, fk_UV::V_E, true, true) == false) {
		fl_alert("Connect NG");
	}

	lightModel->setShape(light.get());
	lightModel->setMaterial(Material::TrueWhite);
	lightModel->glVec(0.0, 0.0, -1.0);
	window->entry(lightModel.get());

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
	return 0;
}
