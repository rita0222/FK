using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Particle
{
	class MyParticle : fk_ParticleSet {
		private Random rand;
		private fk_Color red, blue;
		private double maxSpeed, minSpeed;

		public MyParticle()
		{
			MaxSize = 1000;
			IndivMode = true;
			AllMode = true;
			for(int i = 0; i < MaxSize; i++) {
				SetColorPalette(i, 0.0, 1.0, 0.6);
			}
			rand = new Random();
			red = new fk_Color(1.0, 0.0, 0.0);
			blue = new fk_Color(0.0, 0.0, 0.5);
			maxSpeed = 0.3;
			minSpeed = 0.1;
		}
		
		public override void GenMethod(fk_Particle P)
		{
			double y = rand.NextDouble()*50.0 - 25.0;
			double z = rand.NextDouble()*50.0 - 25.0;
			P.Position = new fk_Vector(50.0, y, z);
			P.ColorID = P.ID;
		}
		public override void AllMethod()
		{
			for(int i = 0; i < 5; i++) {
				if(rand.NextDouble() < 0.3) {
					NewParticle();
				}
			}
		}
		
		public override void IndivMethod(fk_Particle P)
		{
			fk_Vector pos, vec, tmp1, tmp2;
			var water = new fk_Vector(-0.2, 0.0, 0.0);
			double R = 15.0;
			double r;

			pos = P.Position;
			pos.z = 0.0;
			r = pos.Dist();
			
			tmp1 = water/(r*r*r);
			tmp2 = ((3.0 * (water * pos))/(r*r*r*r*r)) * pos;
			vec = water + ((R*R*R)/2.0) * (tmp1 - tmp2);
			P.Velocity = vec;
			double speed = vec.Dist();
			double t = (speed - minSpeed)/(maxSpeed - minSpeed);
			if(t > 1.0) t = 1.0;
			if(t < 0.0) t = 0.0;
			fk_Color newCol = (1.0 - t)*blue + t*red;
			SetColorPalette(P.ID, newCol);

			if(pos.x < -50.0) {
				RemoveParticle(P);
			}
		} 
	}			


	class Program
	{
		static void Main(string[] args)
		{
			fk_ShapeViewer viewer = new fk_ShapeViewer(600, 600);
			MyParticle particle = new MyParticle();
			fk_Prism prism = new fk_Prism(40, 15.0, 15.0, 50.0);

			viewer.SetShape(3, prism);
			viewer.SetPosition(3, 0.0, 0.0, 25.0);
			viewer.SetDrawMode(3, (uint)(fk_DrawMode.POLYMODE));
			viewer.SetShape(2, particle.Shape);
			viewer.SetDrawMode(2, (uint)(fk_DrawMode.POINTMODE));
			viewer.Scale = 10.0;
 
			while(viewer.Draw() == true) {
				for(int i = 0; i < 3; ++i) { // 3倍速再生
					particle.Handle(); // パーティクルを 1 ステップ実行する。
				}
			}

			
		}
	}
}
