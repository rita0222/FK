using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FK_CLI;

namespace FK_CLI_Audio
{
	class Program
	{
		static void Main(string[] args)
		{
			var win = new fk_AppWindow();
			var block = new fk_Block(1.0, 1.0, 1.0);
			var blockModel = new fk_Model();
			var origin = new fk_Vector(0.0, 0.0, 0.0);


			fk_Material.initDefault();			
			blockModel.setShape(block);
			blockModel.glMoveTo(3.0, 3.0, 0.0);
			blockModel.setMaterial(fk_Material.Yellow);
			win.entry(blockModel);
			win.setCameraPos(0.0, 1.0, 20.0);
			win.setCameraFocus(0.0, 1.0, 0.0);

			win.setSize(800, 600);
			win.setBGColor(0.6, 0.7, 0.8);
			win.open();
			win.showGuide(fk_GuideMode.GRID_XZ);

			while(win.update()) {
				blockModel.glRotateWithVec(origin, fk_Axis.Y, FK.PI/360.0);
			}
		}
	}
}
