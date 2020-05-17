using System;
using FK_CLI;

namespace FK_Core_Test_Particle
{
	class Program
	{
        static fk_ParticleSet ParticleSetup()
        {
            var particle = new fk_ParticleSet();
            particle.MaxSize = 1000; // パーティクル最大数
            particle.AllMode = true; // AllMethod() の有効化
            particle.IndivMode = true; // IndivMethod() の有効化

            // パーティクル生成時処理をラムダ式で設定
            particle.GenMethod = (P) =>
            {
                // 生成時の位置を(ランダムに)設定
                double y = fk_Math.DRand(-25.0, 25.0);
                double z = fk_Math.DRand(-25.0, 25.0);
                P.Position = new fk_Vector(50.0, y, z);
            };

            // パーティクル全体処理をラムダ式で設定
            particle.AllMethod = () =>
            {
                for (int i = 0; i < 5; i++)
                {
                    if (fk_Math.DRand() < 0.3)
                    {   // 発生確率は 30% (を5回)
                        particle.NewParticle(); // パーティクル生成処理
                    }
                }
            };

            // パーティクル個別処理をラムダ式で設定
            particle.IndivMethod = (P) =>
            {
                fk_Vector pos, vec, tmp1, tmp2;
                var water = new fk_Vector(-0.5, 0.0, 0.0);
                double R = 15.0;
                double minSpeed = 0.3;
                double maxSpeed = 0.6;
                double r;

                //Console.WriteLine("count A {0}", P.ID);
                pos = P.Position;        // パーティクル位置取得。
                pos.z = 0.0;
                r = pos.Dist();          // |p| を r に代入。

                // パーティクルの速度ベクトルを計算
                tmp1 = water / (r * r * r);
                tmp2 = ((3.0 * (water * pos)) / (r * r * r * r * r)) * pos;
                vec = water + ((R * R * R) / 2.0) * (tmp1 - tmp2);
                P.Velocity = vec;

                // パーティクルの色を計算
                double speed = vec.Dist();
                double s = (speed - minSpeed) / (maxSpeed - minSpeed);
				double t = Math.Min(1.0, Math.Max(0.0, s));
                double h = Math.PI * (4.0 + 2.0 * t)/3.0;
                var col = new fk_Color();
                col.SetHSV(h, 1.0, 1.0);
                P.Color = col;

                // パーティクルの x 成分が -50 以下になったら消去
                if (pos.x < -50.0)
                {
                    particle.RemoveParticle(P);
                }
            };

            // Main() にインスタンスを返す。
            return particle;
        }

        static fk_AppWindow WindowSetup()
        {
            var window = new fk_AppWindow();
            window.Size = new fk_Dimension(800, 800);
            window.BGColor = new fk_Color(0.0, 0.0, 0.0);
            window.TrackBallMode = true;
            window.FPS = 60;
            return window;
        }

        static void ParticleModelSetup(fk_ParticleSet argParticle, fk_AppWindow argWindow)
        {
            var model = new fk_Model();
            model.Shape = argParticle.Shape;
            model.DrawMode = fk_Draw.POINT;

            // パーティクルごとに色を変えたい場合の設定
            model.ElementMode = fk_ElementMode.ELEMENT;

            // パーティクル描画の際の大きさ (ピクセル)
            model.PointSize = 5.0;

            argWindow.Entry(model);
        }

        static void PrismSetup(fk_AppWindow argWindow)
        {
            var prism = new fk_Prism(40, 15.0, 15.0, 50.0);
            var prismModel = new fk_Model();
            prismModel.Shape = prism;
            prismModel.GlMoveTo(0.0, 0.0, 25.0);
            prismModel.DrawMode = fk_Draw.FACE | fk_Draw.LINE | fk_Draw.POINT;
            prismModel.Material = fk_Material.Yellow;
            prismModel.LineColor = new fk_Color(0.0, 0.0, 1.0);
            prismModel.PointColor = new fk_Color(0.0, 1.0, 0.0);
            argWindow.Entry(prismModel);
        }

        static void Main(string[] args)
		{
            // パーティクルセットの生成
            var particle = ParticleSetup();

            // ウィンドウ設定
            var window = WindowSetup();

            // パーティクルモデル設定
            ParticleModelSetup(particle, window);

            // 内部円柱設定
            PrismSetup(window);

            // ウィンドウ生成
            window.Open();

            // メインループ
            while (window.Update())
            {
                particle.Handle(); // パーティクルを 1 ステップ実行する。
            }
		}
	}
}
