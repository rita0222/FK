#include <FK/FK.h>
#include <memory>

using namespace std;
using namespace FK;

// エージェント用クラス
class Agent {

private:
	unique_ptr<fk_Model> model;
	fk_Vector newVec;
	
public:
	Agent(void);

	fk_Vector getPos(void);
	void setVec(fk_Vector);
	fk_Vector getVec(void);
	void setShape(fk_Shape *);
	void entry(fk_AppWindow *);
	void forward(void);
	static constexpr double SPEED = 0.05;
	static constexpr double AREASIZE = 15.0;
};

// 群衆用クラス
class Boid {
private:
	vector< unique_ptr<Agent> >	agent;
	unique_ptr<fk_Cone> cone;
	double paramA, paramB, paramC, paramLA, paramLB;

	vector<fk_Vector> pArray, vArray;

public:
	Boid(int);

	void setParam(double, double, double, double, double);
	void setWindow(fk_AppWindow *);
	void forward(bool, bool, bool);
};

// コンストラクタ
Agent::Agent(void)
{
	model = make_unique<fk_Model>();

	model->setMaterial(Material::Red);
	// モデルの方向と位置をランダムに設定
	model->glVec(fk_Math::drand(-1.0, 1.0), fk_Math::drand(-1.0, 1.0), 0.0);
	model->glMoveTo(fk_Math::drand(-AREASIZE, AREASIZE),
					fk_Math::drand(-AREASIZE, AREASIZE), 0.0);
}

// 位置取得
fk_Vector Agent::getPos(void)
{
	return model->getPosition();
}

// 方向設定
void Agent::setVec(fk_Vector argV)
{
	newVec = argV;
}

// 方向取得
fk_Vector Agent::getVec(void)
{
	return model->getVec();
}

// 形状設定
void Agent::setShape(fk_Shape *argS)
{
	model->setShape(argS);
}

// ウィンドウ登録
void Agent::entry(fk_AppWindow *argWin)
{
	argWin->entry(model.get());
}

// 前進
void Agent::forward()
{
	model->glVec(newVec);
	model->loTranslate(0.0, 0.0, -SPEED);
}
	
// 群集のコンストラクタ
Boid::Boid(int argNum)
{
	// 形状インスタンス生成
	cone = make_unique<fk_Cone>(16, 0.4, 1.0, true);

	if(argNum < 0) return;

	// エージェントインスタンスの作成
	for(int i = 0; i < argNum; ++i) {
		/*
		unique_ptr<Agent> newAgent = make_unique<Agent>();
		newAgent->setShape(cone.get());
		agent.push_back(move(newAgent));
		*/
		agent.push_back(make_unique<Agent>());
		agent.back()->setShape(cone.get());
	}
	pArray.resize(vector<fk_Vector>::size_type(argNum));
	vArray.resize(vector<fk_Vector>::size_type(argNum));

	// 各種パラメータ設定
	paramA = 0.2;
	paramB = 0.02;
	paramC = 0.01;
	paramLA = 3.0;
	paramLB = 5.0;
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
	for(auto &A : agent) A->entry(argWin);
}

// 各エージェント動作メソッド
void Boid::forward(bool argSMode, bool argAMode, bool argCMode)
{
	fk_Vector gVec, diff;
	//vector<fk_Vector> pArray(agent.size()); // 位置ベクトル格納用配列
	//vector<fk_Vector> vArray(agent.size()); // 方向ベクトル格納用配列

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
		if(fabs(p.x) > Agent::AREASIZE && p.x * v.x > 0.0 && fabs(v.x) > 0.01) {
			v.x -= v.x * (fabs(p.x) - Agent::AREASIZE)*0.2;
		}
		if(fabs(p.y) > Agent::AREASIZE && p.y * v.y > 0.0 && fabs(v.y) > 0.01) {
			v.y -= v.y * (fabs(p.y) - Agent::AREASIZE)*0.2;
		}

		// 最終的な方向ベクトル演算結果を代入
		v.z = 0.0;
		agent[i]->setVec(v);
	}

	// 全エージェントを前進
	for(auto &A : agent) A->forward();
}

int main(int, char **)
{
	fk_Material::initDefault();
	unique_ptr<fk_AppWindow> win(new fk_AppWindow());
	unique_ptr<Boid> boid(new Boid(200));

	boid->setWindow(win.get());

	// ウィンドウ各種設定
	win->setSize(800, 800);
	win->setBGColor(0.6, 0.7, 0.8);
	win->showGuide(fk_Guide::GRID_XY);
	win->setCameraPos(0.0, 0.0, 80.0);
	win->setCameraFocus(0.0, 0.0, 0.0);
	win->setTrackBallMode(true);

	win->open();

	while(win->update() == true) {
		// Sキーで「Separate(分離)」を OFF に
		bool sMode = win->getKeyStatus('S', fk_Switch::RELEASE);

		// Aキーで「Alignment(整列)」を OFF に
		bool aMode = win->getKeyStatus('A', fk_Switch::RELEASE);

		// Cキーで「Cohesion(結合)」を OFF に
		bool cMode = win->getKeyStatus('C', fk_Switch::RELEASE);

		// 群集の前進処理
		boid->forward(sMode, aMode, cMode);
	}
}

/****************************************************************************
 *
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2020, Fine Kernel Project, All rights reserved.
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
