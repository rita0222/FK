using System;
using FK_CLI;

namespace FK_CLI_Boid
{
    // エージェント用クラス
	class Agent
	{
		private fk_Model model;
		private fk_Vector newVec;
        private const double SPEED = 0.05;   // 速度設定値
        public const double AREASIZE = 15.0; // 移動領域の広さ設定値

        // コンストラクタ
		public Agent()
		{
			model = new fk_Model();
			model.Material = fk_Material.Red;
			model.GlVec(fk_Math.DRand(-1.0, 1.0), fk_Math.DRand(-1.0, 1.0), 0.0);
            model.GlMoveTo(fk_Math.DRand(-AREASIZE, AREASIZE), fk_Math.DRand(-AREASIZE, AREASIZE), 0.0);
		}

        // 位置ベクトル用プロパティ
		public fk_Vector Pos
		{
			get
			{
				return model.Position;
			}
		}

        // 方向ベクトル用プロパティ
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

        // 形状参照プロパティ
		public fk_Shape Shape
		{
			set
			{
				model.Shape = value;
			}
		}

        // ウィンドウへのモデル登録
		public void Entry(fk_AppWindow argWin)
		{
			argWin.Entry(model);
		}

        // 前進処理
		public void Forward()
		{
			model.GlVec(newVec);
			model.LoTranslate(0.0, 0.0, -SPEED);
		}
	}

    // 群衆用クラス
	class Boid
    {
		private Agent [] agent; // エージェント用配列
		private fk_Cone cone;   // 形状 (円錐)

		private double paramA, paramB, paramC, paramLA, paramLB;

		public Boid(int argNum)
		{
			fk_Material.InitDefault();
			cone = new fk_Cone(16, 0.4, 1.0);
			if(argNum < 0) return;
			agent = new Agent[argNum];

			for(int i = 0; i < argNum; ++i)
            {
				agent[i] = new Agent();
				agent[i].Shape = cone;
			}

			paramA = 0.2;
			paramB = 0.02;
			paramC = 0.01;
			paramLA = 3.0;
			paramLB = 5.0;
		}

		public void SetParam(double argA, double argB, double argC, double argLA, double argLB)
		{
			paramA = argA;
			paramB = argB;
			paramC = argC;
			paramLA = argLA;
			paramLB = argLB;
		}

		public void SetWindow(fk_AppWindow argWin)
		{
			foreach(Agent M in agent)
            {
				M.Entry(argWin);
			}
		}

        // 群集の更新処理
		public void Update(bool argSMode, bool argAMode, bool argCMode)
		{
			var gVec = new fk_Vector();
			var diff = new fk_Vector();
			fk_Vector [] pArray = new fk_Vector[agent.Length];
			fk_Vector [] vArray = new fk_Vector[agent.Length];

            // 位置ベクトルと速度ベクトルのコピー
			for(int i = 0; i < agent.Length; i++)
            {
				pArray[i] = agent[i].Pos;
				vArray[i] = agent[i].Vec;
				gVec += pArray[i];
			}

            // 群集重心の算出
			gVec /= (double)(agent.Length);

			for(int i = 0; i < agent.Length; i++)
            {
                fk_Vector p = new fk_Vector(pArray[i]);
                fk_Vector v = new fk_Vector(vArray[i]);
				for(int j = 0; j < agent.Length; j++)
                {
					if(i == j) continue;
					diff = p - pArray[j];
					double dist = diff.Dist();

                    // 分離 (Separation) 処理
                    if (dist < paramLA && argSMode == true)
                    {
						v += paramA * diff / (dist*dist);
					}

                    // 整列 (Alignment) 処理
					if(dist < paramLB && argAMode == true)
                    {
						v += paramB * vArray[j];
					}
				}

                // 結合 (Cohesion) 処理
				if(argCMode == true)
                {
					v += paramC * (gVec - pArray[i]);
				}

                // 領域の外側に近づいたら方向修正
                if (Math.Abs(p.x) > Agent.AREASIZE && p.x * v.x > 0.0 && Math.Abs(v.x) > 0.01)
                {
					v.x -= v.x * (Math.Abs(pArray[i].x) - Agent.AREASIZE)*0.2;
				}

				if(Math.Abs(p.y) > Agent.AREASIZE && p.y * v.y > 0.0 && Math.Abs(v.y) > 0.01)
                {
					v.y -= v.y * (Math.Abs(pArray[i].y) - Agent.AREASIZE)*0.2;
				}

				v.z = 0.0;
				agent[i].Vec = v;
			}

			foreach(Agent M in agent) {
				M.Forward();
			}
		}
	}

	class Program
    {
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			var boid = new Boid(200);

			boid.SetWindow(win);

            // ウィンドウ各種設定
			win.Size = new fk_Dimension(800, 800);
			win.BGColor = new fk_Color(0.6, 0.7, 0.8);
			win.ShowGuide(fk_Guide.GRID_XY);
			win.CameraPos = new fk_Vector(0.0, 0.0, 80.0);
			win.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
            win.TrackBallMode = true;

			win.Open();

			while(win.Update() == true)
            {
                // Sキーで「Separate(分離)」を無効に
                bool sMode = win.GetKeyStatus('S', fk_Switch.RELEASE);

                // Aキーで「Alignment(整列)」を無効に
                bool aMode = win.GetKeyStatus('A', fk_Switch.RELEASE);

                // Cキーで「Cohesion(結合)」を無効に
                bool cMode = win.GetKeyStatus('C', fk_Switch.RELEASE);

                // 群集の更新処理
                boid.Update(sMode, aMode, cMode);
			}
		}
	}
}
