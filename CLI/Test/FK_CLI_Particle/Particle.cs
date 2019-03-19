using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Particle
{
	class MyParticle : fk_ParticleSet {
		private Random rand;
		private fk_Color red, blue;
		private double maxSpeed, minSpeed;

        // コンストラクタ。
        // ここに様々な初期設定を記述しておく。
        public MyParticle()
		{
            MaxSize = 1000;                      // パーティクルの最大数設定
            IndivMode = true;                    // 個別処理 (IndivMethod) を有効にしておく。
			AllMode = true;                      // 全体処理 (AllMethod) を有効にしておく。
            rand = new Random();                 // 乱数発生器の初期化
			red = new fk_Color(1.0, 0.0, 0.0);
			blue = new fk_Color(0.0, 0.0, 0.5);
			maxSpeed = 0.3;                      // これより速いパーティクルは全て赤
			minSpeed = 0.1;                      // これより遅いパーティクルは全て青
		}
		
        // ここにパーティクル生成時の処理を記述する。
        // 引数 P には新たなパーティクルインスタンスが入る。
		public override void GenMethod(fk_Particle P)
		{
            // 生成時の位置を(ランダムに)設定
			double y = rand.NextDouble()*50.0 - 25.0;
			double z = rand.NextDouble()*50.0 - 25.0;
            P.Position = new fk_Vector(50.0, y, z);
		}

        // ここの毎ループ時の全体処理を記述する。
        public override void AllMethod()
		{
            for(int i = 0; i < 5; i++) {
				if(rand.NextDouble() < 0.3) {   // 発生確率は 30% (を5回)
					NewParticle();              // パーティクル生成処理
				}
			}
		}

        // ここに毎ループ時のパーティクル個別処理を記述する。
        public override void IndivMethod(fk_Particle P)
		{
			fk_Vector pos, vec, tmp1, tmp2;
			var water = new fk_Vector(-0.2, 0.0, 0.0);
			double R = 15.0;
			double r;

            pos = P.Position;        // パーティクル位置取得。
			pos.z = 0.0;
            r = pos.Dist();          // |p| を r に代入。

            // パーティクルの速度ベクトルを計算
            tmp1 = water/(r*r*r);
			tmp2 = ((3.0 * (water * pos))/(r*r*r*r*r)) * pos;
			vec = water + ((R*R*R)/2.0) * (tmp1 - tmp2);
			P.Velocity = vec;

            // パーティクルの x 成分が -50 以下になったら消去
            if(pos.x < -50.0) {
				RemoveParticle(P);
			}
		} 
	}			


	class Program
	{
		static void Main(string[] args)
		{
			fk_ShapeViewer viewer = new fk_ShapeViewer(600, 600);
			MyParticle particle = new MyParticle();
			fk_Prism prism = new fk_Prism(40, 15.0, 15.0, 50.0);

			viewer.SetShape(3, prism);
			viewer.SetPosition(3, 0.0, 0.0, 25.0);
			viewer.SetDrawMode(3, fk_DrawMode.POLYMODE);
			viewer.SetShape(2, particle.Shape);
			viewer.SetDrawMode(2, fk_DrawMode.POINTMODE);
			viewer.Scale = 10.0;
 
			while(viewer.Draw() == true) {
				for(int i = 0; i < 3; ++i) { // 3倍速再生
					particle.Handle(); // パーティクルを 1 ステップ実行する。
				}
			}

		}
	}
}