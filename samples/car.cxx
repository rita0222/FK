/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
#include <list>
#include <FK/FK.h>

using namespace std;
using namespace FK;
using namespace FK::Material;

class Car {

public:
	static constexpr double	BUILDWIDTH	= 25.0;		// 建物幅の基本単位
	static constexpr double	CIRCUITX	= 150.0;	// コースの X 方向幅
	static constexpr double	CIRCUITY	= 250.0;	// コースの Y 方向幅

	Car(void) {}		// コンストラクタ

	void		init(void);
	void		entryScene(fk_Scene *, bool);	
	fk_Vector	getCarPosition(void);
	fk_Model *	getBirdModel(void);
	void		forward(double);
	bool		isRotate(void);
	void		rotate(double);

private:
	fk_Model	carModel;		// 車全体モデル
	fk_Model	bodyModel;		// 車体モデル
	fk_Model	tireModel[4];	// 各タイヤモデル
	fk_Model	driverModel[2];	// 運転者モデル
	fk_Model	birdModel;		// 鳥瞰視点モデル

	fk_Block	body;			// 車体形状
	fk_Circle	tire;			// タイヤ形状
	fk_Sphere	driver;			// 運転者形状
};

class Build {
private:
	fk_Model	buildModel;
	fk_Block	buildShape;

public:
	Build(void);

	void		makeBuild(fk_Vector, double, fk_Material &);
	fk_Model *	getModel(void);
};

class World {
private:
	fk_Model			groundModel;
	fk_Block			buildShape, groundShape;
	fk_Light			lightShape;
	list<Build *>		builds;
	list<fk_Model *>	lightModels;

	void		defLight(fk_Vector);
	void		defBuild(fk_Vector, double, fk_Material &);

public:
	World(void) {}
	~World();

	void		init(void);
	void		entryScene(fk_Scene *);
};

void Car::init(void)
{
	int			i;
	fk_Vector	X(1.0, 0.0, 0.0);
	double		tx = 4.0, ty = 1.0, tz = 8.0;

	body.setSize(7.0, 6.0, 20.0);
	tire.setRadius(2.0);
	tire.setDivide(2);
	driver.setRadius(2.0);
	driver.setDivide(2);

	bodyModel.setShape(&body);
	bodyModel.glMoveTo(0.0, 5.0, 0.0);
	bodyModel.setMaterial(Yellow);
	bodyModel.setParent(&carModel);

	tireModel[0].glMoveTo(-tx, ty, -tz);
	tireModel[0].glVec(X);
	tireModel[1].glMoveTo(tx, ty, -tz);
	tireModel[1].glVec(-X);
	tireModel[2].glMoveTo(-tx, ty, tz);
	tireModel[2].glVec(X);
	tireModel[3].glMoveTo(tx, ty, tz);
	tireModel[3].glVec(-X);

	for(i = 0; i < 4; i++) {
		tireModel[i].setShape(&tire);
		tireModel[i].setMaterial(Gray2);
		tireModel[i].setParent(&carModel);
	}

	driverModel[0].setShape(&driver);
	driverModel[1].setShape(&driver);
	driverModel[0].glMoveTo(-2.0, 10.0, 0.0);
	driverModel[1].glMoveTo(2.0, 10.0, 0.0);
	driverModel[0].setMaterial(Cream);
	driverModel[1].setMaterial(Cream);
	driverModel[0].setSmoothMode(true);
	driverModel[1].setSmoothMode(true);
	driverModel[0].setParent(&carModel);
	driverModel[1].setParent(&carModel);

	birdModel.glMoveTo(0.0, 100.0, 200.0);
	birdModel.glFocus(0.0, 5.0, 0.0);
	birdModel.glUpvec(0.0, 1.0, 0.0);
	birdModel.setParent(&carModel);

	carModel.glMoveTo(CIRCUITX, CIRCUITY, 0.0);
	carModel.glAngle(0.0, -fk_Math::PI/2.0, fk_Math::PI);

	return;
}

void Car::entryScene(fk_Scene *scene, bool viewFlag)
{
	int		i;

	scene->entryModel(&bodyModel);

	for(i = 0; i < 4; i++) {
		scene->entryModel(&tireModel[i]);
	}

	scene->entryModel(&driverModel[0]);

	if(viewFlag == true) {
		scene->entryModel(&driverModel[1]);
	} else {
		scene->entryCamera(&driverModel[1]);
	}

	return;
}

fk_Vector Car::getCarPosition(void)
{
	return carModel.getPosition();
}

fk_Model * Car::getBirdModel(void)
{
	return &birdModel;
}

void Car::forward(double argSpeed)
{
	carModel.loTranslate(0.0, 0.0, -argSpeed); // 前進
	return;
}

bool Car::isRotate(void)
{
	fk_Vector		XVec(1.0, 0.0, 0.0);
	fk_Vector		YVec(0.0, 1.0, 0.0);
	fk_Vector		carVec = carModel.getVec();
	fk_Vector		carPos = carModel.getPosition();

	// サーキットの外にでた場合、回転する。
	// 車の方向ベクトルと、壁の法線ベクトルとの内積がマイナスのときに回転
	if(carPos.x > Car::CIRCUITX	&& carVec * (-XVec)	< -fk_Math::EPS) return true;
	if(carPos.x < -Car::CIRCUITX && carVec * XVec	< -fk_Math::EPS) return true;
	if(carPos.y > Car::CIRCUITY	&& carVec * (-YVec)	< -fk_Math::EPS) return true;
	if(carPos.y < -Car::CIRCUITY && carVec * YVec	< -fk_Math::EPS) return true;

	return false;
}

void Car::rotate(double argAngle)
{
	carModel.loAngle(argAngle, 0.0, 0.0);
}

Build::Build(void)
{
	buildModel.setShape(&buildShape);
}

void Build::makeBuild(fk_Vector argPos, double argHeight, fk_Material &argMat)
{
	buildShape.setSize(Car::BUILDWIDTH, Car::BUILDWIDTH, argHeight);
	buildModel.glMoveTo(argPos.x, argPos.y, argHeight/2.0);
	buildModel.setMaterial(argMat);
}

fk_Model * Build::getModel(void)
{
	return &buildModel;
}

World::~World()
{
	for(auto b : builds) {
		delete b;
	}

	for(auto m : lightModels) {
		delete m;
	}
}

void World::defLight(fk_Vector argV)
{
	fk_Model		*model = new fk_Model;

	model->setShape(&lightShape);
	model->setMaterial(White);
	model->glFocus(argV);
	lightModels.push_back(model);

	return;
}

void World::defBuild(fk_Vector argPos, double argHeight, fk_Material &argMat)
{
	Build *b = new Build;

	b->makeBuild(argPos, argHeight, argMat);
	builds.push_back(b);
}

void World::init(void)
{

	// 照明の設定
	defLight(fk_Vector(1.0, 1.0, -1.0));
	defLight(fk_Vector(-1.0, -1.0, -1.0));

	// 建物の設定
	defBuild(fk_Vector(-250.0, 100.0), 125.0, Red);
	defBuild(fk_Vector(-150.0, 400.0), 50.0, DimYellow);
	defBuild(fk_Vector(50.0, 250.0), 100.0, Blue); 
	defBuild(fk_Vector(300.0, 200.0), 75.0, Gray1); 
	defBuild(fk_Vector(250.0, -250.0), 12.5, Green);
	defBuild(fk_Vector(-50.0, -350.0), 150.0, Orange);

	// 地面の設定
	groundShape.setSize(1000, 1000, 2.0);
	groundModel.setShape(&groundShape);
	groundModel.glTranslate(0.0, 0.0, -1.0);
	groundModel.setMaterial(Brown);

	return;
}

void World::entryScene(fk_Scene *scene)
{
	scene->entryModel(&groundModel);

	for(fk_Model *m : lightModels) scene->entryModel(m);

	for(Build *b : builds) scene->entryModel(b->getModel());

	return;
}


int main(int, char *[])
{
	fk_Material::initDefault();

	Car				carObj;
	World			worldObj;
	Fl_Window		mainWindow(1240, 420, "MultiWindow Test");
	fk_Scene		carViewScene, buildViewScene, birdViewScene;
	fk_Window		carViewWindow(10, 10, 400, 400);
	fk_Window		buildViewWindow(420, 10, 400, 400);
	fk_Window		birdViewWindow(830, 10, 400, 400);
	fk_Color		bgColor(0.2, 0.7, 1.0);

	fk_Model		buildViewModel, birdViewModel;
	double			speed = 2.0;

	mainWindow.end();
	fk_Material::initDefault();

	carObj.init();
	worldObj.init();

	// 各ウィンドウにバックグラウンドカラー設定
	carViewScene.setBGColor(bgColor);
	buildViewScene.setBGColor(bgColor);
	birdViewScene.setBGColor(bgColor);

	// 各モデルをディスプレイリストに登録
	worldObj.entryScene(&carViewScene);
	worldObj.entryScene(&buildViewScene);
	worldObj.entryScene(&birdViewScene);

	carObj.entryScene(&carViewScene, false);
	carObj.entryScene(&buildViewScene, true);
	carObj.entryScene(&birdViewScene, true);

	// 建物ウィンドウの視点設定
	buildViewModel.glMoveTo(-250.0, 100.0, 100.0);
	buildViewModel.glFocus(carObj.getCarPosition());
	buildViewModel.glUpvec(0.0, 0.0, 1.0);
	buildViewScene.entryCamera(&buildViewModel);

	// 鳥瞰ウィンドウの視点設定
	birdViewScene.entryCamera(carObj.getBirdModel());

	// ウィンドウへディスプレイリストを登録
	carViewWindow.setScene(&carViewScene);
	buildViewWindow.setScene(&buildViewScene);
	birdViewWindow.setScene(&birdViewScene);

	mainWindow.show();
	carViewWindow.show();
	buildViewWindow.show();
	birdViewWindow.show();

	while(true) {

		if(mainWindow.visible() == 0) {
			if(Fl::wait() == 0) {
				break;
			} else {
				continue;
			}
		}

		if(carViewWindow.drawWindow() == 0 ||
		   buildViewWindow.drawWindow() == 0 ||
		   birdViewWindow.drawWindow() == 0) break;

		if(Fl::check() == 0) break;

		if(carViewWindow.winOpenStatus() == false ||
		   buildViewWindow.winOpenStatus() == false ||
		   birdViewWindow.winOpenStatus() == false) {
			continue;
		}	  

		carObj.forward(speed);
		if(carObj.isRotate() == true) carObj.rotate(speed * fk_Math::PI/200.0);

		buildViewModel.glFocus(carObj.getCarPosition());
		buildViewModel.glUpvec(0.0, 0.0, 1.0);
	}
	
	return 0;
}
