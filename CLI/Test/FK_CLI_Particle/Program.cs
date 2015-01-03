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

		public MyParticle()
		{
			setMaxSize(1000);
			setIndivMode(true);
			setAllMode(true);
			setColorPalette(1, 0.0, 1.0, 0.6);
			rand = new Random();
		}
		
		public override void genMethod(fk_Particle P)
		{
			double y = rand.NextDouble()*50.0 - 25.0;
			double z = rand.NextDouble()*50.0 - 25.0;
			P.setPosition(50.0, y, z);
			P.setColorID(1);
		}

		public override void allMethod()
		{
			for(int i = 0; i < 5; i++) {
				if(rand.NextDouble() < 0.3) {
					newParticle();
				}
			}
		}
		
		public override void indivMethod(fk_Particle P)
		{
			fk_Vector pos, vec, tmp1, tmp2;
			var water = new fk_Vector(-0.2, 0.0, 0.0);
			double R = 15.0;
			double r;

			pos = P.getPosition();
			pos.z = 0.0;
			r = pos.dist();
			
			tmp1 = water/(r*r*r);
			tmp2 = ((3.0 * (water * pos))/(r*r*r*r*r)) * pos;
			vec = water + ((R*R*R)/2.0) * (tmp1 - tmp2);
			P.setVelocity(vec);

			if(pos.x < -50.0) {
				removeParticle(P);
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

			viewer.setShape(3, prism);
			viewer.setPosition(3, 0.0, 0.0, 25.0);
			viewer.setDrawMode(3, (uint)(fk_DrawMode.POLYMODE));
			viewer.setShape(2, particle.getShape());
			viewer.setDrawMode(2, (uint)(fk_DrawMode.POINTMODE));
			viewer.setScale(10.0);
 
			while(viewer.draw() == true) {
				for(int i = 0; i < 3; ++i) { // 3倍速再生
					particle.handle(); // パーティクルを 1 ステップ実行する。
				}
			}
		}
	}
}
