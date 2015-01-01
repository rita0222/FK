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
			fk_Material.initDefault();
			
			var sprite = new fk_SpriteModel();
			var block = new fk_Block(1.0, 1.0, 1.0);
			var model = new fk_Model();
			var origin = new fk_Vector(0.0, 0.0, 0.0);
			int count;
			string str;
 
			if(sprite.initFont("mona.ttf") == false) {
				System.Console.WriteLine("Font Error");
			}

			sprite.setPositionLT(-280.0, 230.0);
			window.entry(sprite);
 
			model.setShape(block);
			model.glMoveTo(0.0, 6.0, 0.0);
			model.setMaterial(fk_Material.Yellow);
			window.entry(model);
 
			window.setCameraPos(0.0, 5.0, 20.0);
			window.setCameraFocus(0.0, 5.0, 0.0);
			window.setSize(800, 600);
			window.setBGColor(0.6, 0.7, 0.8);
			window.open();
			window.showGuide(fk_GuideMode.GRID_XZ);
 
			count = 0;
			while(window.update() == true) {
				str = "count = " + count.ToString();
				sprite.drawText(str, true);
				model.glRotateWithVec(origin, fk_Axis.Y, FK.PI/360.0);
				count++;
			}
		}
	}
}
