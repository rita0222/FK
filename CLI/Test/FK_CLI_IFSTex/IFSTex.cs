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
			win.Size = new fk_Dimension(960, 544);
			win.ClearModel(true);

			var lightModel = new fk_Model();

			var ifsShape = new fk_IFSTexture();
			var sph = new fk_Sphere(8, 7.0);

			var spModel = new fk_Model();
			var ifsModel = new fk_Model();

			fk_Material.InitDefault();
			lightModel.Shape = new fk_Light();
			lightModel.Material = fk_Material.TrueWhite;
			lightModel.GlMoveTo(0.0, 0.0, 0.0);
			lightModel.GlFocus(-1.0, -1.0, -1.0);

			if(!ifsShape.ReadPNG("mqo/00tex_master.png")) {
				Console.WriteLine("Tex Load Error.");
			}
			if(!ifsShape.ReadMQOFile("mqo/meka.mqo", "body01")) {
				Console.WriteLine("IFS Load Error.");
			}
			ifsShape.RendMode = fk_TexRendMode.SMOOTH;

			win.BGColor = new fk_Color(0.5, 0.5, 0.5);
			win.Entry(lightModel);
			win.ShowGuide(fk_GuideMode.GRID_XZ);
			win.TrackBallMode = true;

			spModel.Shape = sph;
			spModel.Material = fk_Material.Yellow;
			spModel.SmoothMode = true;
			spModel.GlMoveTo(-20.0, 0.0, 0.0);
			win.Entry(spModel);

			ifsModel.Shape = ifsShape;
			ifsModel.Material = fk_Material.White;
			ifsModel.SmoothMode = true;
			ifsModel.GlMoveTo(20.0, 0.0, 0.0);
			win.Entry(ifsModel);

			win.Open();
			while(win.Update() == true) {
				lightModel.GlRotateWithVec(0.0, 0.0, 0.0, fk_Axis.Y, 0.01);
			}
		}
	}
}
