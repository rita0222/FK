using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Boid
{

	class Agent {
		private fk_Model model;
		public const int IAREA = 15;
		public const double AREASIZE = (double)(IAREA);

		public Agent()
		{
			var rand = new Random();

			model = new fk_Model();
			model.Material = fk_Material.Red;
			model.GlVec(rand.NextDouble()*2.0 - 1.0, rand.NextDouble()*2.0 - 1.0, 0.0);
			model.GlMoveTo(rand.NextDouble() * AREASIZE * 2.0 - AREASIZE, rand.NextDouble() * AREASIZE * 2.0 - AREASIZE, 0.0);
		}

		public fk_Vector Pos {
			set {
				model.GlMoveTo(value);
			}
			get {
				return model.Position;
			}
		}

		public fk_Vector Vec {
			set {
				model.GlVec(value);
			}
			get {
				return model.Vec;
			}
		}

		public fk_Shape Shape {
			set {
				model.Shape = value;
			}
		}

		public void Forward()
		{
			model.LoTranslate(0.0, 0.0, -0.05);
		}

		public void Entry(fk_AppWindow argWin)
		{
			argWin.Entry(model);
		}
	}

	class Boid {
		private Agent [] agent;
		private double paramA, paramB, paramC, paramLA, paramLB;

		public Boid(int argNum)
		{
			fk_Material.InitDefault();
			fk_Cone cone = new fk_Cone(16, 0.4, 1.0);
			if(argNum < 0) return;
			agent = new Agent[argNum];

			for(int i = 0; i < argNum; ++i) {
				agent[i] = new Agent();
			}
			foreach(Agent model in agent) {				
				model.Shape = cone;
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
				agent[i].Entry(argWin);
			}
		}

		public void forward(bool argGMode)
		{
			int i, j;
			var gVec = new fk_Vector();
			fk_Vector diff;
			
			for(i = 0; i < agent.Length; ++i) {
				gVec += agent[i].Pos;
			}

			gVec /= (double)(agent.Length);

			for(i = 0; i < agent.Length; ++i) {
				var vec = agent[i].Vec;
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

				if((pArray[i].x > Agent.AREASIZE && vArray[i].x > 0.0) ||
					(pArray[i].x < -Agent.AREASIZE && vArray[i].x < 0.0)) {
					vec.x -= vec.x * (Math.Abs(pArray[i].x) - Agent.AREASIZE)*0.2;
				}

				if((pArray[i].y > Agent.AREASIZE && vArray[i].y > 0.0) ||
					(pArray[i].y < -Agent.AREASIZE && vArray[i].y < 0.0)) {
					vec.y -= vec.y * (Math.Abs(pArray[i].y) - Agent.AREASIZE)*0.2;
				}

				vec.z = 0.0;

				agent[i].Vec = vec;
				agent[i].Forward();
			}
		}
	}

	class Program {
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			var boid = new Boid(100);

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
