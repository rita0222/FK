using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Boid
{
    // エージェント用クラス
    class Agent
	{
		private fk_Model model;
		private fk_Vector newVec;

		public Agent(double argSize, Random argRand)
		{
            // コンストラクタ
            // 各モデルの位置と方向をランダムに設定する。
			model = new fk_Model();
			model.Material = fk_Material.Red;
			model.GlVec(argRand.NextDouble()*2.0 - 1.0, argRand.NextDouble()*2.0 - 1.0, 0.0);
			model.GlMoveTo(argRand.NextDouble() * argSize * 2.0 - argSize,
                           argRand.NextDouble() * argSize * 2.0 - argSize, 0.0);
		}

        // 位置ベクトルプロパティ
        public fk_Vector Pos
		{
			get
			{
				return model.Position;
			}
		}

        // 方向ベクトルプロパティ
        public fk_Vector Vec
		{
			set
			{
				newVec = value;
			}
			get
			{
				return model.Vec;
			}
		}

        // 形状インスタンスプロパティ
        public fk_Shape Shape
		{
			set
			{
				model.Shape = value;
			}
		}

        // ウィンドウ登録メソッド
		public void Entry(fk_AppWindow argWin)
		{
			argWin.Entry(model);
		}

        // 前進メソッド
        public void Forward()
		{
			model.GlVec(newVec);
			model.LoTranslate(0.0, 0.0, -0.05);
		}
	}

    // 群衆用クラス
    class Boid {
		private Agent [] agent;
		private fk_Cone cone;
		private const int IAREA = 15;
		private const double AREASIZE = (double)(IAREA);

		private double paramA, paramB, paramC, paramLA, paramLB;

        // コンストラクタ
		public Boid(int argNum)
		{
            // 乱数発生器の初期化
            var rand = new Random();

            // 形状インスタンスの性生
			fk_Material.InitDefault();
            cone = new fk_Cone(16, 0.4, 1.0);
			if(argNum < 0) return;

            // エージェント配列作成
            agent = new Agent[argNum];

            // エージェントインスタンスの作成
            for(int i = 0; i < argNum; ++i) {
				agent[i] = new Agent(AREASIZE, rand);
				agent[i].Shape = cone;
			}

            // 各種パラメータ設定
            paramA = 0.2;
			paramB = 0.02;
			paramC = 0.01;
			paramLA = 3.0;
			paramLB = 5.0;
		}

        // パラメータ設定メソッド
        public void SetParam(double argA, double argB, double argC,
                             double argLA, double argLB)
		{
			paramA = argA;
			paramB = argB;
			paramC = argC;
			paramLA = argLA;
			paramLB = argLB;
		}

        // ウィンドウへのエージェント登録メソッド
        public void SetWindow(fk_AppWindow argWin)
		{
			foreach(Agent M in agent) {
				M.Entry(argWin);
			}
		}

        // 各エージェント動作メソッド
        public void Forward(bool argSMode, bool argAMode, bool argCMode)
		{
			var gVec = new fk_Vector();
			fk_Vector diff = new fk_Vector();
			fk_Vector [] pArray = new fk_Vector[agent.Length]; // 位置ベクトル格納用配列
			fk_Vector [] vArray = new fk_Vector[agent.Length]; // 方向ベクトル格納用配列

            // 全体の重心計算
            for(int i = 0; i < agent.Length; i++) {
				pArray[i] = agent[i].Pos;
				vArray[i] = agent[i].Vec;
				gVec += pArray[i];
			}
			gVec /= (double)(agent.Length);

            // エージェントごとの動作算出演算
			for(int i = 0; i < agent.Length; i++) {
				fk_Vector vec = new fk_Vector(vArray[i]);

                for(int j = 0; j < agent.Length; j++) {
					if(i == j) continue;
					diff = pArray[i] - pArray[j];
					double dist = diff.Dist();

                    // 分離 (Separation) 処理
					if(dist < paramLA && argSMode) {
						vec += paramA * diff / (dist*dist);
					}

                    // 整列 (Alignment) 処理
                    if(dist < paramLB && argAMode) {
						vec += paramB * vArray[j];
					}
				}

                // 結合 (Cohesion) 処理 (スペースキーが押されていたら無効化)
                if(argCMode == true) {
					vec += paramC * (gVec - pArray[i]);
				}

                // 領域の外側に近づいたら方向修正
                if(Math.Abs(pArray[i].x) > AREASIZE && pArray[i].x * vArray[i].x > 0.0) {
					vec.x -= vec.x * (Math.Abs(pArray[i].x) - AREASIZE)*0.2;
				}
				if(Math.Abs(pArray[i].y) > AREASIZE && pArray[i].y * vArray[i].y > 0.0) {
					vec.y -= vec.y * (Math.Abs(pArray[i].y) - AREASIZE)*0.2;
				}

                // 最終的な方向ベクトル演算結果を代入
                vec.z = 0.0;
				agent[i].Vec = vec;
			}

            // 全エージェントを前進
            foreach(Agent M in agent) {
				M.Forward();
			}
		}
	}

	class Program {
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			var boid = new Boid(200);

			boid.SetWindow(win);

			win.Size = new fk_Dimension(600, 600);
			win.BGColor = new fk_Color(0.6, 0.7, 0.8);
			win.ShowGuide(fk_GuideMode.GRID_XY);
			win.CameraPos = new fk_Vector(0.0, 0.0, 80.0);
			win.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
			win.FPS = 0;

			win.Open();

			while(win.Update() == true) {
                bool sMode = win.GetKeyStatus('S', fk_SwitchStatus.RELEASE);
                bool aMode = win.GetKeyStatus('A', fk_SwitchStatus.RELEASE);
                bool cMode = win.GetKeyStatus('C', fk_SwitchStatus.RELEASE);
				boid.Forward(sMode, aMode, cMode);
			}

		}
	}
}
