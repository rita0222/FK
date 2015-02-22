using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Boid
{
	class Boid {
		private fk_Model [] agent;
		private fk_Cone cone;
		private const int IAREA = 15;
		private const double AREASIZE = (double)(IAREA);

		private double paramA, paramB, paramC, paramLA, paramLB;

		public Boid(int argNum)
		{
			fk_Material.InitDefault();
			cone = new fk_Cone(16, 0.4, 1.0);
			if(argNum < 0) return;
			agent = new fk_Model[argNum];
			var rand = new Random();
			for(int i = 0; i < argNum; ++i) {
				agent[i] = new fk_Model();
				agent[i].setShape(cone);
				agent[i].setMaterial(fk_Material.Red);
				agent[i].glVec(rand.NextDouble()*2.0 - 1.0,
					rand.NextDouble()*2.0 - 1.0, 0.0);
				agent[i].glMoveTo(rand.NextDouble() * AREASIZE * 2.0 - AREASIZE,
					rand.NextDouble() * AREASIZE * 2.0 - AREASIZE, 0.0);
			}
			paramA = 0.2;
			paramB = 0.02;
			paramC = 0.01;
			paramLA = 3.0;
			paramLB = 5.0;
		}

		public void setParam(double argA, double argB, double argC,
			double argLA, double argLB)
		{
			paramA = argA;
			paramB = argB;
			paramC = argC;
			paramLA = argLA;
			paramLB = argLB;
		}

		public void setWindow(fk_AppWindow argWin)
		{
			for(int i = 0; i < agent.Length; ++i) {
				argWin.Entry(agent[i]);
			}
		}

		public void forward(bool argGMode)
		{
			int i, j;
			var gVec = new fk_Vector();
			var pArray = new fk_Vector[agent.Length];
			var vArray = new fk_Vector[agent.Length];
			fk_Vector diff;
			
			for(i = 0; i < agent.Length; ++i) {
				pArray[i] = agent[i].getPosition();
				vArray[i] = agent[i].getVec();
				gVec += pArray[i];
			}

			gVec /= (double)(agent.Length);

			for(i = 0; i < agent.Length; ++i) {
				var vec = agent[i].getVec();
				for(j = 0; j < agent.Length; ++j) {
					if(i == j) continue;

					diff = pArray[i] - pArray[j];
					double dist = diff.Dist();
					if(dist < paramLA) {
						vec += paramA * diff / (dist*dist);
					}

					if(dist < paramLB) {
						vec += paramB * vArray[j];
					}
				}

				if(argGMode == true) {
					vec += paramC * (gVec - pArray[i]);
				}

				if((pArray[i].x > AREASIZE && vArray[i].x > 0.0) ||
					(pArray[i].x < -AREASIZE && vArray[i].x < 0.0)) {
					vec.x -= vec.x * 0.2;
				}

				if((pArray[i].y > AREASIZE && vArray[i].y > 0.0) ||
					(pArray[i].y < -AREASIZE && vArray[i].y < 0.0)) {
					vec.y -= vec.y * 0.2;
				}

				vec.z = 0.0;

				agent[i].glVec(vec);
				agent[i].loTranslate(0.0, 0.0, -0.05);
			}
		}
	}

	class Program {
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			var boid = new Boid(50);

			boid.setWindow(win);

			win.Size = new fk_Dimension(600, 600);
			win.BGColor = new fk_Color(0.6, 0.7, 0.8);
			win.ShowGuide(fk_GuideMode.GRID_XY);
			win.CameraPos = new fk_Vector(0.0, 0.0, 80.0);
			win.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);

			win.Open();

			while(win.Update() == true) {
				boid.forward(win.GetKeyStatus(' ', fk_SwitchStatus.RELEASE));
			}

		}
	}
}
