#include <FK/FK.h>
#include <random>

using namespace FK;
using namespace FK::Material;
using namespace std;

using _st = unsigned long;
const double AREA = 20.0;
const double SPEED = 0.1;

// [argMin, argMax] の範囲の一様乱数を生成
double getRand(double argMin, double argMax, mt19937 &argMT)
{
	uniform_real_distribution<> randR(argMin, argMax);
	return randR(argMT);
}

void pointMove(fk_Vector *argP, fk_Vector *argV)
{
	*argP = *argP + SPEED * (*argV);

	// 壁に当たったら反射
	if(fabs(argP->x) > AREA && argP->x * argV->x > 0.0) argV->x = -argV->x;
	if(fabs(argP->y) > AREA && argP->y * argV->y > 0.0) argV->y = -argV->y;

	return;
}

int main(int, char *[])
{
	fk_System::setcwd();
	fk_Material::initDefault();

	fk_AppWindow		window;
	fk_Model			model;
	fk_Point			point;
	fk_ShaderBinder		shader;
	vector<fk_Vector>	posArray, vecArray;
	fk_FVecArray		vecCopy;
	random_device		rnd;
	mt19937				mt(rnd());

	window.setSize(800, 800);
	window.setBGColor(0.6, 0.7, 0.8);
	window.showGuide(fk_Guide::GRID_XY);
	window.setCameraPos(0.0, 0.0, 80.0);
	window.setCameraFocus(0.0, 0.0, 0.0);
	window.open();

	vecCopy.setDim(2);
	for(int i = 0; i < 4; i++) {
		fk_Vector pos(getRand(-AREA, AREA, mt), getRand(-AREA, AREA, mt), 0.0);
		fk_Vector vec(getRand(-1.0, 1.0, mt), getRand(-1.0, 1.0, mt), 0.0);
		vec.normalize();
		posArray.push_back(pos);
		vecArray.push_back(vec);
		vecCopy.push(vec);
	}

	point.setVertex(&posArray);
	// 形状側での Attribute 変数登録
	point.setShaderAttribute("pointVec", 2, vecCopy.getP());
	//point.setShaderAttribute("pointVec", 2, vecCopy.getP(), true);
	point.setShaderAttribute("pointVec", 2, &vecArray);

	model.setShape(&point);
	model.setPointColor(1.0, 0.0, 0.0);
	model.setPointSize(5.0);
	window.entry(model);

	auto program = shader.getProgram();
	program->loadVertexShader("shader/geom_vs.glsl");
	program->loadGeometryShader("shader/geom_gs.glsl");
	program->loadFragmentShader("shader/geom_fs.glsl");

	if(program->validate()) {
		shader.bindModel(&model);
		// シェーダー側での Attribute 変数登録
		shader.getParameter()->reserveAttribute("pointVec");
	} else {
		fk_Window::putString(program->getLastError());
	}

	while(window.update() == true) {
		for(_st i = 0; i < 4; i++) {
			pointMove(&posArray[i], &vecArray[i]);
			point.setVertex(int(i), posArray[i]);
			vecCopy.set(int(i), vecArray[i]);
		}
		// Attribute 変数データを GPU に送信するための設定
		//point.modifyAttribute("pointVec");
		//point.setShaderAttribute("pointVec", 2, vecCopy.getP(), true);
		point.setShaderAttribute("pointVec", 2, &vecArray);
	}
	
	return 0;
}
