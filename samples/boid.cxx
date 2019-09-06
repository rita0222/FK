#include <FK/FK.h>
#include <random>

using namespace std;
using namespace FK;
using namespace FK::Material;

// エージェント用クラス
class Agent {

private:
	static const double		SPEED;

	fk_Model		model;
	fk_Vector		newVec;
	
public:
	Agent(double, mt19937 &);

	fk_Vector		getPos(void);
	void			setVec(fk_Vector);
	fk_Vector		getVec(void);
	void			setShape(fk_Shape *);
	void			entry(fk_AppWindow *);
	void			forward(void);
};

const double Agent::SPEED = 0.05;

// 群衆用クラス
class Boid {
private:
	const double	AREASIZE = 15.0;
	vector<Agent *>	agent;
	fk_Cone			*cone;
	double			paramA, paramB, paramC, paramLA, paramLB;

public:
	Boid(int);
	~Boid();

	void			setParam(double, double, double, double, double);
	void			setWindow(fk_AppWindow *);
	void			forward(bool, bool, bool);
};

// コンストラクタ
Agent::Agent(double argSize, mt19937 &argMT)
{
	uniform_real_distribution<>	randR(-1.0, 1.0);

	model.setMaterial(Red);
	model.setShadingMode(FK_SHADING_GOURAUD);
	// モデルの方向と位置をランダムに設定
	model.glVec(randR(argMT), randR(argMT), 0.0);
	model.glMoveTo(randR(argMT)*argSize, randR(argMT)*argSize, 0.0);
}

// 位置取得
fk_Vector Agent::getPos(void)
{
	return model.getPosition();
}

// 方向設定
void Agent::setVec(fk_Vector argV)
{
	newVec = argV;
}

// 方向取得
fk_Vector Agent::getVec(void)
{
	return model.getVec();
}

// 形状設定
void Agent::setShape(fk_Shape *argS)
{
	model.setShape(argS);
}

// ウィンドウ登録
void Agent::entry(fk_AppWindow *argWin)
{
	argWin->entry(model);
}

// 前進
void Agent::forward()
{
	model.glVec(newVec);
	model.loTranslate(0.0, 0.0, -SPEED);
}
	
// 群集のコンストラクタ
Boid::Boid(int argNum)
{
	// -1 〜 1 までの乱数発生器生成
	random_device				rnd;
	mt19937						mt(rnd());

	// 形状インスタンス生成
	fk_Material::initDefault();
	cone = new fk_Cone(16, 0.4, 1.0);
	if(argNum < 0) return;

	// エージェントインスタンスの作成
	for(int i = 0; i < argNum; ++i) {
		Agent *newAgent = new Agent(AREASIZE, mt);
		newAgent->setShape(cone);
		agent.push_back(newAgent);
	}

	// 各種パラメータ設定
	paramA = 0.2;
	paramB = 0.02;
	paramC = 0.01;
	paramLA = 3.0;
	paramLB = 5.0;
}

// 群集のデストラクタ
Boid::~Boid()
{
	for(auto M : agent) {
		delete M;
	}
	delete cone;
}	

// パラメータ設定メソッド
void Boid::setParam(double argA, double argB, double argC, double argLA, double argLB)
{
	paramA = argA;
	paramB = argB;
	paramC = argC;
	paramLA = argLA;
	paramLB = argLB;
}

// ウィンドウへのエージェント登録メソッド
void Boid::setWindow(fk_AppWindow *argWin)
{
	for(auto M : agent) {
		M->entry(argWin);
	}
}

// 各エージェント動作メソッド
void Boid::forward(bool argSMode, bool argAMode, bool argCMode)
{
	fk_Vector gVec, diff;
	vector<fk_Vector> pArray(agent.size()); // 位置ベクトル格納用配列
	vector<fk_Vector> vArray(agent.size()); // 方向ベクトル格納用配列

	// 全体の重心計算
	for(size_t i = 0; i < agent.size(); i++) {
		pArray[i] = agent[i]->getPos();
		vArray[i] = agent[i]->getVec();
		gVec += pArray[i];
	}
	gVec /= (double)(agent.size());

	// エージェントごとの動作算出演算
	for(size_t i = 0; i < agent.size(); i++) {
		fk_Vector p = pArray[i];
		fk_Vector v = vArray[i];

		for(size_t j = 0; j < agent.size(); j++) {
			if(i == j) continue;
			diff = p - pArray[j];
			double dist = diff.dist();

			// 分離 (Separation) 処理
			if(dist < paramLA && argSMode == true) {
				v += paramA * diff / (dist*dist);
			}

			// 整列 (Alignment) 処理
			if(dist < paramLB && argAMode == true) {
				v += paramB * vArray[j];
			}
		}

		// 結合 (Cohesion) 処理 (スペースキーが押されていたら無効化)
		if(argCMode == true) {
			v += paramC * (gVec - p);
		}

		// 領域の外側に近づいたら方向修正
		if(fabs(p.x) > AREASIZE && p.x * v.x > 0.0 && fabs(v.x) > 0.01) {
			v.x -= v.x * (fabs(p.x) - AREASIZE)*0.2;
		}
		if(fabs(p.y) > AREASIZE && p.y * v.y > 0.0 && fabs(v.y) > 0.01) {
			v.y -= v.y * (fabs(p.y) - AREASIZE)*0.2;
		}

		// 最終的な方向ベクトル演算結果を代入
		v.z = 0.0;
		agent[i]->setVec(v);
	}

	// 全エージェントを前進
	for(auto M : agent) {
		M->forward();
	}
}

int main(int, char **)
{
	fk_AppWindow win;
	Boid boid(200);

	boid.setWindow(&win);

	// ウィンドウ各種設定
	win.setSize(800, 800);
	win.setBGColor(0.6, 0.7, 0.8);
	win.showGuide(FK_GRID_XY);
	win.setCameraPos(0.0, 0.0, 80.0);
	win.setCameraFocus(0.0, 0.0, 0.0);
	win.open();

	while(win.update() == true) {
		// Sキーで「Separate(分離)」を OFF に
		bool sMode = win.getKeyStatus('S', fk_Switch::RELEASE);

		// Aキーで「Alignment(整列)」を OFF に
		bool aMode = win.getKeyStatus('A', fk_Switch::RELEASE);

		// Cキーで「Cohesion(結合)」を OFF に
		bool cMode = win.getKeyStatus('C', fk_Switch::RELEASE);

		// 群集の前進処理
		boid.forward(sMode, aMode, cMode);
	}
}
