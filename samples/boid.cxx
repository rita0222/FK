#include <FK/FK.h>
#include <random>

using namespace std;

// エージェント用クラス
class Agent {

private:
	fk_Model model;
	fk_Vector newVec;
	
public:
	Agent(double);
	fk_Vector getPos(void);
	void setVec(fk_Vector);
	fk_Vector getVec(void);
	void setShape(fk_Shape *);
	void entry(fk_AppWindow *);
	void forward(void);
};

Agent::Agent(double argSize)
{
	// コンストラクタ
	// 各モデルの位置と方向をランダムに設定する。
	random_device				rnd;
	mt19937						mt(rnd());
	uniform_real_distribution<>	randR(-1.0, 1.0);
		
	model.setMaterial(Red);
	model.glVec(randR(mt), randR(mt), 0.0);
	model.glMoveTo(randR(mt)*argSize, randR(mt)*argSize, 0.0);
}

fk_Vector Agent::getPos(void)
{
	return model.getPosition();
}

void Agent::setVec(fk_Vector argV)
{
	newVec = argV;
}

fk_Vector Agent::getVec(void)
{
	return model.getVec();
}

void Agent::setShape(fk_Shape *argS)
{
	model.setShape(argS);
}

void Agent::entry(fk_AppWindow *argWin)
{
	argWin->entry(model);
}

void Agent::forward()
{
	model.glVec(newVec);
	model.loTranslate(0.0, 0.0, -0.05);
}
	
// 群衆用クラス
class Boid {
private:
	const int IAREA = 15;
	const double AREASIZE = (double)(IAREA);
	vector<Agent *> agent;
	fk_Cone *cone;
	double paramA, paramB, paramC, paramLA, paramLB;

	// コンストラクタ
public:
	Boid(int);
	~Boid();
	void setParam(double, double, double, double, double);
	void setWindow(fk_AppWindow *);
	void forward(bool, bool, bool);
};

Boid::Boid(int argNum)
{
	// 形状インスタンスの性生
	fk_Material::initDefault();
	cone = new fk_Cone(16, 0.4, 1.0);
	if(argNum < 0) return;

	// エージェントインスタンスの作成
	for(int i = 0; i < argNum; ++i) {
		Agent *newAgent = new Agent(AREASIZE);
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
		fk_Vector vec = vArray[i];

		for(size_t j = 0; j < agent.size(); j++) {
			if(i == j) continue;
			diff = pArray[i] - pArray[j];
			double dist = diff.dist();

			// 分離 (Separation) 処理
			if(dist < paramLA && argSMode == true) {
				vec += paramA * diff / (dist*dist);
			}

			// 整列 (Alignment) 処理
			if(dist < paramLB && argAMode == true) {
				vec += paramB * vArray[j];
			}
		}

		// 結合 (Cohesion) 処理 (スペースキーが押されていたら無効化)
		if(argCMode == true) {
			vec += paramC * (gVec - pArray[i]);
		}

		// 領域の外側に近づいたら方向修正
		if(fabs(pArray[i].x) > AREASIZE && pArray[i].x * vArray[i].x > 0.0) {
			vec.x -= vec.x * (fabs(pArray[i].x) - AREASIZE)*0.2;
		}
		if(fabs(pArray[i].y) > AREASIZE && pArray[i].y * vArray[i].y > 0.0) {
			vec.y -= vec.y * (fabs(pArray[i].y) - AREASIZE)*0.2;
		}

		// 最終的な方向ベクトル演算結果を代入
		vec.z = 0.0;
		agent[i]->setVec(vec);
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

	win.setSize(600, 600);
	win.setBGColor(0.6, 0.7, 0.8);
	win.showGuide(FK_GRID_XY);
	win.setCameraPos(0.0, 0.0, 80.0);
	win.setCameraFocus(0.0, 0.0, 0.0);

	win.open();

	while(win.update() == true) {
		bool sMode = win.getKeyStatus('S', FK_SW_RELEASE);
		bool aMode = win.getKeyStatus('A', FK_SW_RELEASE);
		bool cMode = win.getKeyStatus('C', FK_SW_RELEASE);
		boid.forward(sMode, aMode, cMode);
	}
}
