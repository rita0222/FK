using System;
using FK_CLI;

namespace FK_CLI_Particle
{
	class Program
	{
		static void Main(string[] args)
		{
			var viewer = new fk_ShapeViewer(600, 600);
			var particle = new fk_ParticleSet();
			var prism = new fk_Prism(40, 15.0, 15.0, 50.0);

            particle.MaxSize = 1000;
            particle.AllMode = true;
            particle.IndivMode = true;
            int num = 0;

            particle.GenMethod = (P) =>
            {
                // 生成時の位置を(ランダムに)設定
                double y = fk_Math.DRand(-25.0, 25.0);
                double z = fk_Math.DRand(-25.0, 25.0);
                P.Position = new fk_Vector(50.0, y, z);
            };

            particle.AllMethod = () =>
            {
                for (int i = 0; i < 5; i++)
                {
                    if (fk_Math.DRand() < 0.3)
                    {   // 発生確率は 30% (を5回)
                        particle.NewParticle();              // パーティクル生成処理
                        num++;
                    }
                }
            };

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

                double speed = vec.Dist();
                double t = (speed - minSpeed) / (maxSpeed - minSpeed);
                double h = Math.PI * 4.0 / 3.0 + Math.Min(1.0, Math.Max(0.0, t)) * Math.PI * 2.0 / 3.0;
                var col = new fk_Color();
                col.SetHSV(h, 1.0, 1.0);
                P.Color = col;

                // パーティクルの x 成分が -50 以下になったら消去
                if (pos.x < -50.0)
                {
                    particle.RemoveParticle(P);
                }
            };

			viewer.SetShape(2, particle.Shape);
			viewer.SetDrawMode(2, fk_Draw.POINT);
            viewer.SetElementMode(2, fk_ElementMode.ELEMENT);

            viewer.SetShape(3, prism);
			viewer.SetPosition(3, 0.0, 0.0, 25.0);
			viewer.SetDrawMode(3, fk_Draw.FACE | fk_Draw.LINE | fk_Draw.POINT);
            viewer.Scale = 10.0;
            viewer.FPS = 0;

            while (viewer.Draw())
            {
                particle.Handle(); // パーティクルを 1 ステップ実行する。
            }
		}
	}
}