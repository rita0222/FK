#include <FK/FK.h>

using namespace std;
using namespace FK;
using namespace FK::Material;

int main(int, char *[])
{
	fk_AppWindow	window;
	fk_SpriteModel	sprite;
	fk_Block		block(1.0, 1.0, 1.0);
	fk_Model		model;
	fk_Vector		origin(0.0, 0.0, 0.0);
	int				count;
	std::string		str;

	fk_System::setcwd();

	sprite.initFont("rm1b.ttf");
	sprite.setPositionLT(-280.0, 230.0);
	window.entry(sprite);

	model.setShape(&block);
	model.glMoveTo(0.0, 6.0, 0.0);
	model.setMaterial(Yellow);
	window.entry(model);

	window.setCameraPos(0.0, 5.0, 20.0);
	window.setCameraFocus(0.0, 5.0, 0.0);
	window.setSize(800, 600);
	window.setBGColor(0.6, 0.7, 0.8);
	window.open();
	window.showGuide(FKUT_GRID_XZ);

	count = 0;
	while(window.update() == true) {
		str = "count = " + std::to_string(count);
		sprite.drawText(str, true);
		sprite.setPositionLT(-280.0, 230.0);
		model.glRotateWithVec(origin, fk_Y, FK_PI/360.0);
		count++;
	}
	return 0;
}
