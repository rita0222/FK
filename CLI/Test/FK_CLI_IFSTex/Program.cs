using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_IFSTex
{
	class Program
	{
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			win.setSize(960, 544);
			win.clearModel(true);

			var lightModel = new fk_Model();

			var ifsShape = new fk_IFSTexture();
			var sph = new fk_Sphere(8, 7.0);

			var spModel = new fk_Model();
			var ifsModel = new fk_Model();

			fk_Material.initDefault();
			lightModel.setShape(new fk_Light());
			lightModel.setMaterial(fk_Material.TrueWhite);
			lightModel.glMoveTo(0.0, 0.0, 0.0);
			lightModel.glFocus(-1.0, -1.0, -1.0);

			if(!ifsShape.readPNG("mqo/00tex_master.png")) {
				Console.WriteLine("Tex Load Error.");
			}
			if(!ifsShape.readMQOFile("mqo/meka.mqo", "body01")) {
				Console.WriteLine("IFS Load Error.");
			}
			ifsShape.setTexRendMode(fk_TexRendMode.SMOOTH);

			win.setBGColor(0.5, 0.5, 0.5);
			win.entry(lightModel);
			win.showGuide(fk_GuideMode.GRID_XZ);
			win.setTrackBallMode(true);

			spModel.setShape(sph);
			spModel.setMaterial(fk_Material.Yellow);
			spModel.setSmoothMode(true);
			spModel.glMoveTo(-20.0, 0.0, 0.0);
			win.entry(spModel);

			ifsModel.setShape(ifsShape);
			ifsModel.setMaterial(fk_Material.White);
			ifsModel.setSmoothMode(true);
			ifsModel.glMoveTo(20.0, 0.0, 0.0);
			win.entry(ifsModel);

			win.open();
			while(win.update() == true) {
				lightModel.glRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, 0.01);
			}
		}
	}
}
