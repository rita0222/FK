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

			var win = new fk_AppWindow();
			win.Size = new fk_Dimension(500, 500);
			var model = new fk_Model();
			var pointM = new fk_Model();
			var cone = new fk_Cone(3, 4.0, 15.0);
			var pos = new fk_Vector(0.0, 0.0, -15.0);


			var angle1 = new fk_Angle(0.0, 0.0, 0.0);
			var angle2 = new fk_Angle(FK.PI/2.0, FK.PI/2.0 - 0.01, 0.0);

			var q1 = new fk_Quaternion();
			var q2 = new fk_Quaternion();
			fk_Quaternion q;
			var poly = new fk_Polyline();

			fk_Material.InitDefault();

			model.Shape = cone;
			model.Material = fk_Material.Yellow;
			model.GlAngle(angle1);

			pointM.Shape = poly;
			pointM.LineColor = new fk_Color(1.0, 0.0, 0.0);

			win.BGColor = new fk_Color(0.3, 0.4, 0.5);
			win.Entry(model);
			win.Entry(pointM);
			win.SetTrackBallMode(true);
			win.ShowGuide();
			win.Open();
			q1.makeEuler(angle1);
			q2.makeEuler(angle2);

			double t = 0.0;

			while(win.Update() == true) {
				q = fk_Math.QuatInterSphere(q1, q2, t);
				model.GlAngle(q.getEuler());
				if(t < 1.0) {
					poly.pushVertex(model.Matrix * pos);
					t += 0.005;
				}
			}
		}
	}
}
