using System;
using FK_CLI;

namespace FK_Core_Test_Quaternion
{
	class Program
	{
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			win.Size = new fk_Dimension(800, 800);
			var model = new fk_Model();
			var pointM = new fk_Model();
			var cone = new fk_Cone(3, 4.0, 15.0);
			var pos = new fk_Vector(0.0, 0.0, -15.0);

            // オイラー角用変数の生成
			var angle1 = new fk_Angle(0.0, 0.0, 0.0);
			var angle2 = new fk_Angle(Math.PI/2.0, Math.PI/2.0 - 0.01, 0.0);

            // 四元数用変数の生成
			var q1 = new fk_Quaternion();
			var q2 = new fk_Quaternion();
			fk_Quaternion q;

            // 角錐頂点の軌跡用
			var point = new fk_Polyline();

			fk_Material.InitDefault();

			model.Shape = cone;
			model.Material = fk_Material.Yellow;
			model.GlAngle(angle1); // モデルのオイラー角を (0, 0, 0) に

			pointM.Shape = point;
			pointM.LineColor = new fk_Color(1.0, 0.0, 0.0);

            win.BGColor = new fk_Color(0.7, 0.8, 0.9);
			win.Entry(model);
			win.Entry(pointM);
			win.TrackBallMode = true;
			win.ShowGuide();
			win.Open();

			q1.Euler = angle1; // q1 にオイラー角 (0, 0, 0) を意味する四元数を設定
			q2.Euler = angle2; // q2 にオイラー角 (π/2, π/2-0.01, 0) を意味する四元数を設定

			double t = 0.0;

			while(win.Update() == true) {
                // q に q1 と q2 を球面補間した値を設定
				q = fk_Math.QuatInterSphere(q1, q2, t);

                // モデルの姿勢を q に設定
				model.GlAngle(q.Euler);

                // 頂点軌跡の追加
				if(t < 1.0) {
					point.PushVertex(model.Matrix * pos);
					t += 0.005;
				}
			}
		}
	}
}
