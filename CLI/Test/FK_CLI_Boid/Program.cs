using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Boid
{

	class Agent
	{
		private fk_Model model;
		private fk_Cone cone;
		private fk_Vector newVec;
		public const int IAREA = 15;
		public const double AREASIZE = (double)(IAREA);

		public Agent()
		{
			var rand = new Random();

			model = new fk_Model();
			cone = new fk_Cone(16, 0.4, 1.0);
			model.Material = fk_Material.Red;
			model.Shape = cone;
			model.GlVec(rand.NextDouble()*2.0 - 1.0, rand.NextDouble()*2.0 - 1.0, 0.0);
			model.GlMoveTo(rand.NextDouble() * AREASIZE * 2.0 - AREASIZE, rand.NextDouble() * AREASIZE * 2.0 - AREASIZE, 0.0);
		}

		public fk_Vector Pos
		{
			set
			{
				model.GlMoveTo(value);
			}
			get
			{
				return model.Position;
			}
		}

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

		public fk_Shape Shape
		{
			set
			{
				model.Shape = value;
			}
		}

		public fk_Model Model
		{
			set
			{
				model = value;
			}

			get
			{
				return model;
			}
		}

		public void Forward()
		{
			model.GlVec(newVec);
			model.LoTranslate(0.0, 0.0, -0.05);
		}
	}

	class Boid {
		private Agent [] agent;
		private double paramA, paramB, paramC, paramLA, paramLB;

		public Boid(int argNum)
		{
			fk_Material.InitDefault();

			if(argNum < 0) return;
			agent = new Agent[argNum];

			for(int i = 0; i < argNum; ++i) {
				agent[i] = new Agent();
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
			for(int i = 0; i < agent.Length; i++) {
				argWin.Entry(agent[i].Model);
			}
		}

		public void Forward(bool argGMode)
		{
			var gVec = new fk_Vector();
			fk_Vector diff;

			foreach(Agent M in agent) {
				gVec += M.Pos;
			}

			gVec /= (double)(agent.Length);

			foreach(Agent A in agent) {
				var vec = A.Vec;

				foreach(Agent B in agent) {
					if(A == B) continue;

					diff = A.Pos - B.Pos;
					double dist = diff.Dist();
					if(dist < paramLA) {
						vec += paramA * diff / (dist*dist);
					}

					if(dist < paramLB) {
						vec += paramB * B.Vec;
					}
				}

				if(argGMode == true) {
					vec += paramC * (gVec - A.Pos);
				}

				if((A.Pos.x > Agent.AREASIZE && A.Vec.x > 0.0) ||
				   (A.Pos.x < -Agent.AREASIZE && A.Vec.x < 0.0)) {
					vec.x -= vec.x * (Math.Abs(A.Pos.x) - Agent.AREASIZE)*0.2;
				}

				if((A.Pos.y > Agent.AREASIZE && A.Vec.y > 0.0) ||
				   (A.Pos.y < -Agent.AREASIZE && A.Vec.y < 0.0)) {
					vec.y -= vec.y * (Math.Abs(A.Pos.y) - Agent.AREASIZE)*0.2;
				}

				vec.z = 0.0;

				A.Vec = vec;
			}

			foreach(Agent M in agent) {
				M.Forward();
			}
		}
	}

	class Program {
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			var boid = new Boid(50);

			boid.SetWindow(win);

			win.Size = new fk_Dimension(600, 600);
			win.BGColor = new fk_Color(0.6, 0.7, 0.8);
			win.ShowGuide(fk_GuideMode.GRID_XY);
			win.CameraPos = new fk_Vector(0.0, 0.0, 80.0);
			win.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);

			win.Open();

			while(win.Update() == true) {
				boid.Forward(win.GetKeyStatus(' ', fk_SwitchStatus.RELEASE));
			}

		}
	}
}
