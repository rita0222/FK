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
		private fk_Vector newVec;

		public Agent(double argSize, Random argRand)
		{
			model = new fk_Model();
			model.Material = fk_Material.Red;
			model.GlVec(argRand.NextDouble()*2.0 - 1.0,
                        argRand.NextDouble()*2.0 - 1.0,
                        0.0);
			model.GlMoveTo(argRand.NextDouble() * argSize * 2.0 - argSize,
                           argRand.NextDouble() * argSize * 2.0 - argSize,
                           0.0);
		}

		public fk_Vector Pos
		{
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

		public void Entry(fk_AppWindow argWin)
		{
			argWin.Entry(model);
		}

		public void Forward()
		{
			model.GlVec(newVec);
			model.LoTranslate(0.0, 0.0, -0.05);
		}
	}

	class Boid
    {
		private Agent [] agent;
		private fk_Cone cone;
		private const double AREASIZE = 15.0;

		private double paramA, paramB, paramC, paramLA, paramLB;

		public Boid(int argNum)
		{
			var rand = new Random();

			fk_Material.InitDefault();
			cone = new fk_Cone(16, 0.4, 1.0);
			if(argNum < 0) return;
			agent = new Agent[argNum];

			for(int i = 0; i < argNum; ++i)
            {
				agent[i] = new Agent(AREASIZE, rand);
				agent[i].Shape = cone;
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
			foreach(Agent M in agent)
            {
				M.Entry(argWin);
			}
		}

		public void Forward(bool argGMode)
		{
			var gVec = new fk_Vector();
			fk_Vector diff = new fk_Vector();
			fk_Vector [] pArray = new fk_Vector[agent.Length];
			fk_Vector [] vArray = new fk_Vector[agent.Length];

			for(int i = 0; i < agent.Length; i++)
            {
				pArray[i] = agent[i].Pos;
				vArray[i] = agent[i].Vec;
				gVec += pArray[i];
			}

			gVec /= (double)(agent.Length);


			for(int i = 0; i < agent.Length; i++)
            {
                fk_Vector p = new fk_Vector(pArray[i]);
                fk_Vector v = new fk_Vector(vArray[i]);
				for(int j = 0; j < agent.Length; j++)
                {
					if(i == j) continue;
					diff = p - pArray[j];
					double dist = diff.Dist();
					if(dist < paramLA)
                    {
						v += paramA * diff / (dist*dist);
					}

					if(dist < paramLB)
                    {
						v += paramB * vArray[j];
					}
				}

				if(argGMode == true)
                {
					v += paramC * (gVec - pArray[i]);
				}

                if(Math.Abs(p.x) > AREASIZE && p.x * v.x > 0.0 && Math.Abs(v.x) > 0.01)
                {
					v.x -= v.x * (Math.Abs(pArray[i].x) - AREASIZE)*0.2;
				}

				if(Math.Abs(p.y) > AREASIZE && p.y * v.y > 0.0 && Math.Abs(v.y) > 0.01)
                {
					v.y -= v.y * (Math.Abs(pArray[i].y) - AREASIZE)*0.2;
				}

				v.z = 0.0;
				agent[i].Vec = v;
			}

			foreach(Agent M in agent) {
				M.Forward();
			}
		}
	}

	class Program
    {
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			var boid = new Boid(200);

			boid.SetWindow(win);

			win.Size = new fk_Dimension(600, 600);
			win.BGColor = new fk_Color(0.6, 0.7, 0.8);
			win.ShowGuide(fk_GuideMode.GRID_XY);
			win.CameraPos = new fk_Vector(0.0, 0.0, 80.0);
			win.CameraFocus = new fk_Vector(0.0, 0.0, 0.0);
			win.FPS = 0;

			win.Open();

			while(win.Update() == true)
            {
                boid.Forward(win.GetKeyStatus(' ', fk_SwitchStatus.RELEASE));
			}

		}
	}
}
