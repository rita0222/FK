using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Sprite
{
	class Program
	{
		static void Main(string[] args)
		{
			var window = new fk_AppWindow();
			fk_Material.InitDefault();
			
			var sprite = new fk_SpriteModel();
			var block = new fk_Block(1.0, 1.0, 1.0);
			var model = new fk_Model();
			var origin = new fk_Vector(0.0, 0.0, 0.0);
			int count;
			string str, space;
 
			if(sprite.InitFont("mona.ttf") == false) {
				System.Console.WriteLine("Font Error");
			}

			sprite.SetPositionLT(-240.0, 230.0);

			sprite.Text.MonospaceMode = true;
			sprite.Text.MonospaceSize = 12;
			window.Entry(sprite);
 
			model.Shape = block;
			model.GlMoveTo(0.0, 6.0, 0.0);
			model.Material = fk_Material.Yellow;
			window.Entry(model);
			window.CameraPos = new fk_Vector(0.0, 5.0, 20.0);
			window.CameraFocus = new fk_Vector(0.0, 5.0, 0.0);
			window.Size = new fk_Dimension(800, 600);
			window.BGColor = new fk_Color(0.6, 0.7, 0.8);
			window.Open();
			window.ShowGuide(fk_GuideMode.GRID_XZ);
 
			count = 0;
			while(window.Update() == true) {
                if (count < 10) space = "   ";
				else if(count < 100) space = "  ";
				else if(count < 1000) space = " ";
				else space = "";
				str = "count = " + space + count.ToString();
				sprite.DrawText(str, true);
				model.GlRotateWithVec(origin, fk_Axis.Y, Math.PI/360.0);
				count++;
			}
		}
	}
}
