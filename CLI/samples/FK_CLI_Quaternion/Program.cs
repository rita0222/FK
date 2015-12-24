using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Quaternion
{
	class Program
	{
		static void Main(string[] args)
		{
            // 各種変数生成
			fk_Material.InitDefault();
			var win = new fk_AppWindow();
			var model = new fk_Model();
			var pointM = new fk_Model();
			var cone = new fk_Cone(3, 4.0, 15.0);
			var pos = new fk_Vector(0.0, 0.0, -15.0);
            var poly = new fk_Polyline();

            // オイラー角の初期値設定
            var angle1 = new fk_Angle(0.0, 0.0, 0.0);
			var angle2 = new fk_Angle(FK.PI/2.0, FK.PI/2.0 - 0.01, 0.0);

            // 四元数変数作成
            var q1 = new fk_Quaternion();
			var q2 = new fk_Quaternion();
			fk_Quaternion q;

            // 三角錐モデルの設定
            model.Shape = cone;
			model.Material = fk_Material.Yellow;
			model.GlAngle(angle1);

            // 軌跡用ポリラインモデルの設定
            pointM.Shape = poly;
			pointM.LineColor = new fk_Color(1.0, 0.0, 0.0);

            // ウィンドウ設定
			win.Size = new fk_Dimension(500, 500);
            win.BGColor = new fk_Color(0.3, 0.4, 0.5);
			win.Entry(model);
			win.Entry(pointM);
			win.TrackBallMode = true;
			win.ShowGuide();

            win.Open();

            // オイラー角の初期値を四元数に設定
            q1.Euler = angle1;
			q2.Euler = angle2;

			for(int i = 0;  win.Update() == true; i++) {
                double t = i / 200.0;
				if(t < 1.0) {
                    // パラメータ t で球面線形補間
                    q = fk_Math.QuatInterSphere(q1, q2, t);

                    // q をモデルの姿勢(オイラー角)に変換
                    model.GlAngle(q.Euler);

                    // 軌跡用に点を追加
					poly.PushVertex(model.Matrix * pos);
				}
			}
		}
	}
}