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
			win.setSize(500, 500);
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

			fk_Material.initDefault();
			model.setShape(cone);
			model.setMaterial(fk_Material.Yellow);
			model.glAngle(angle1);

			pointM.setShape(poly);
			pointM.setLineColor(1.0, 0.0, 0.0);

			win.setBGColor(0.3, 0.4, 0.5);
			win.entry(model);
			win.entry(pointM);
			win.setTrackBallMode(true);
			win.showGuide();
			win.open();

			q1.makeEuler(angle1);
			q2.makeEuler(angle2);

			double t = 0.0;
			while(win.update() == true) {
				q = fk_Math.quatInterSphere(q1, q2, t);
				model.glAngle(q.getEuler());
				if(t < 1.0) {
					poly.pushVertex(model.getMatrix() * pos);
					t += 0.005;
				}
			}
		}
	}
}
